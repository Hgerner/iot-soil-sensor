/*
 * sensor.c
 *
 *  Created on: 14 aug. 2019
 *      Author: admin
 */

/* XDCtools Header files */
#include <Sensor.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

/* Board Header files */
#include "Board.h"
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/drivers/timer/GPTimerCC26XX.h>

#define SENSORTASKSTACKSIZE   1024
Task_Struct sensorTaskStruct;
char sensorTaskStack[SENSORTASKSTACKSIZE];


/*********************************************************************
*  EXTERNAL VARIABLES
*/
#define GPT_STACKSTACKSIZE 1024
Task_Struct gtpTask;
char gptTaskStack[GPT_STACKSTACKSIZE];

GPTimerCC26XX_Handle hTimer;
PIN_Handle timerPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State timerPinState;

/* Timer buffer */
#define TIMERBUFSIZE 8
uint8_t timerBufIndex = 0;
uint8_t intervalBufIndex = 0;
uint32_t timerBuf[TIMERBUFSIZE] = {0};
uint32_t intervalBuf[TIMERBUFSIZE] = {0};
static bool firstTimeFlag;

struct SensorData {
    uint16_t Temperature;
    uint16_t AirHumidity;
    uint16_t Pressure;
    uint16_t SoilHumidity;
    uint16_t LightIntensity;
    uint16_t BatteryVoltage;
};

static struct SensorData sensordata[SENSORLENGTH] = {0};
static int sensor_index = 0;

// I2C Handlers
I2C_Handle      i2c;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction;

/* Pin driver handle */
static PIN_Handle outputPinHandle;
static PIN_State outputPinState;

PIN_Config outputPinTable[] = {
    Board_PWR | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

PIN_Config gptPinTable[] = {
    Board_SENSOR_SOIL   | PIN_GPIO_OUTPUT_DIS | PIN_INPUT_EN | PIN_HYSTERESIS,
    PIN_TERMINATE
};

static void Array_sort(uint32_t *array , int n)
{
    // declare some local variables
    int i=0 , j=0;
    uint32_t temp=0;

    for(i=0 ; i<n ; i++)
    {
        for(j=0 ; j<n-1 ; j++)
        {
            if(array[j]>array[j+1])
            {
                temp        = array[j];
                array[j]    = array[j+1];
                array[j+1]  = temp;
            }
        }
    }

//    printf("\nThe array after sorting is..\n");
    for(i=0 ; i<n ; i++)
    {
        System_printf("\narray_1[%d] : %d",i,array[i]);
    }
}

// function to calculate the median of the array
uint32_t Find_median(uint32_t array[] , int n)
{
    uint32_t median = 0;

    // if number of elements are even
    if(n%2 == 0)
        median = (array[(n-1)/2] + array[n/2])/2.0;
    // if number of elements are odd
    else
        median = array[n/2];

    return median;
}


void timerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask)
{
    // get the tick value when last rising edge is captured
    timerBuf[timerBufIndex] = GPTimerCC26XX_getValue(handle);
    // translate the tick value into Hz
    if (!firstTimeFlag)
    {
        if (timerBuf[timerBufIndex] > timerBuf[timerBufIndex-1])
        {
          intervalBuf[intervalBufIndex] =  48000000/(timerBuf[timerBufIndex]- timerBuf[timerBufIndex-1]+1);
        }
        else
        {
           intervalBuf[intervalBufIndex] =  48000000/(timerBuf[timerBufIndex]+ 0xFFFFFF-timerBuf[timerBufIndex-1]+1);
        }
    }

    timerBufIndex++;
    intervalBufIndex++;
    if (firstTimeFlag)
    {
        firstTimeFlag = FALSE;
    }

    uint32_t median = 0;

    if(timerBufIndex == TIMERBUFSIZE)
    {
        GPTimerCC26XX_stop(handle);
        timerBufIndex = 0;
        intervalBufIndex = 0;

        Array_sort(intervalBuf, TIMERBUFSIZE);
        median = Find_median(intervalBuf, TIMERBUFSIZE);

        sensordata[sensor_index].SoilHumidity = median;
    }
}

static bool I2C_send(uint8_t slave_addr, uint8_t txBuffer[], uint8_t writeCount)
{
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.readCount  = 0;

    i2cTransaction.writeCount = writeCount;
    i2cTransaction.slaveAddress = slave_addr;

    if (!I2C_transfer(i2c, &i2cTransaction)) {
        return false;
    }
    return true;
}

uint16_t BMP_readData(uint8_t slave_addr, uint8_t ptr)
{
    uint8_t txBuffer[1] = {ptr};
    uint8_t rxBuffer[2] = {0};

    i2cTransaction.slaveAddress = slave_addr;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.readCount  = 1;
    i2cTransaction.writeCount = 1;

    if (!I2C_transfer(i2c, &i2cTransaction)) {
        return 0xFFFF;
    }
    else
        return rxBuffer[0];
/*
    Task_sleep(20000);

    i2cTransaction.readCount  = 1;
    i2cTransaction.writeCount = 0;

    if (!I2C_transfer(i2c, &i2cTransaction)) {
        return 0xFFFE;
    }
    else
        return rxBuffer[1] << 8 | rxBuffer[0];
*/
}

uint16_t HDC_readData(uint8_t slave_addr, uint8_t ptr)
{
    uint8_t txBuffer[1] = {ptr};
    uint8_t rxBuffer[2] = {0};

    i2cTransaction.slaveAddress = slave_addr;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.readCount  = 0;
    i2cTransaction.writeCount = 1;

    if (!I2C_transfer(i2c, &i2cTransaction)) {
        return 0xFFFF;
    }

    Task_sleep(20000);

    i2cTransaction.readCount  = 2;
    i2cTransaction.writeCount = 0;

    if (!I2C_transfer(i2c, &i2cTransaction)) {
        return 0xFFFF;
    }

    return (rxBuffer[1] << 8 | rxBuffer[0]);
}


void enableSensors()
{
    PIN_setOutputValue(outputPinHandle, Board_PWR, Board_PWR_ON);
}

void disableSensors()
{
    PIN_setOutputValue(outputPinHandle, Board_PWR, Board_PWR_OFF);
}


uint16_t readRawHumidity(uint8_t addr)
{
    return HDC_readData(addr, HDC_HUMIDITY);
}

uint16_t readRawTemperature(uint8_t addr)
{
    return HDC_readData(addr, HDC_TEMPERATURE);
}

uint16_t readRawPressure(uint8_t addr)
{
    return BMP_readData(addr, HDC_DEVICE_ID);
}

uint16_t readRawLight(uint8_t addr)
{
    return 0x0000;
}

uint16_t readRawBattery(uint8_t addr)
{
    return 0x0000;
}

void fetchSensorData()
{
    // Enable sensor voltage and wait for the sensors to stabilize
    PIN_setOutputValue(outputPinHandle, Board_PWR, Board_PWR_ON);
    Task_sleep(20000);

    //HDC1010 Configuration parameters
    uint8_t txBuffer[3] = {HDC_CONFIGURATION, 0x00, 0x00};
    I2C_send(0x40, txBuffer, 3);

    while (1)
    {
        firstTimeFlag = true;
        GPTimerCC26XX_start(hTimer);

        uint16_t temp = readRawTemperature(HDC_ADDR);
        uint16_t airhumidity = readRawHumidity(HDC_ADDR);
        uint16_t airpressure = readRawPressure(BMP_ADDR);
//        uint16_t lightintensity = readRawLight();

        struct SensorData *tempSensorData = &sensordata[sensor_index];

        while (tempSensorData->SoilHumidity == 0);

        tempSensorData->Temperature = temp;
        tempSensorData->AirHumidity = airhumidity;
        tempSensorData->Pressure = airpressure;
        tempSensorData->LightIntensity = 0;
        tempSensorData->BatteryVoltage = 60000;


        sensor_index = sensor_index++ % SENSORLENGTH;
        //disableSensors();
        Task_sleep(200000);
    }
}

void InitSensors()
{
    /* Open LED pins */
    outputPinHandle = PIN_open(&outputPinState, outputPinTable);
    if(!outputPinHandle) {
        System_abort("Error initializing board OUTPUT pins\n");
    }

    Task_Params sensorTaskParams;
    /* Construct heartBeat Task  thread */
    Task_Params_init(&sensorTaskParams);
    sensorTaskParams.stackSize = SENSORTASKSTACKSIZE;
    sensorTaskParams.stack = &sensorTaskStack;
    sensorTaskParams.priority = 3;
    Task_construct(&sensorTaskStruct, (Task_FuncPtr)fetchSensorData, &sensorTaskParams, NULL);

    // Configure GPTimer used to capture soil-sensor frequency
    Power_setDependency(PowerCC26XX_XOSC_HF);
    /* Set up GPTimer 0A in edge time capture mode */
    GPTimerCC26XX_Params timerParams;
    GPTimerCC26XX_Params_init(&timerParams);
    timerParams.mode  = GPT_MODE_EDGE_TIME_UP;
    timerParams.width = GPT_CONFIG_16BIT;
    hTimer = GPTimerCC26XX_open(Board_GPTIMER0A, &timerParams);
    /* Register interrupt when capture happens */
    GPTimerCC26XX_registerInterrupt(hTimer, timerCallback, GPT_INT_CAPTURE);
    /* Open pin handle and route pin to timer */
    timerPinHandle = PIN_open(&timerPinState, gptPinTable);
    GPTimerCC26XX_PinMux pinMux = GPTimerCC26XX_getPinMux(hTimer);
    PINCC26XX_setMux(timerPinHandle, PIN_ID(PIN_ID(Board_SENSOR_SOIL)), pinMux);
    // max period could be 5Hz=0.2s= 48000000/5-1 ticks = 0x927BFF
    //Therefore the count up time out should be 0xFFFFFF
    GPTimerCC26XX_setLoadValue(hTimer, 0xFFFFFF);

    // Configure & open I2C communication link
    I2C_init();
    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;

    i2c = I2C_open(Board_I2C0, &i2cParams);
    if (i2c == NULL) {
        System_abort("Could not open I2C.");
    }
}


