/*
 * sensor.h
 *
 *  Created on: 14 aug. 2019
 *      Author: admin
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "stdint.h"
#include "stdbool.h"


#define SENSORLENGTH 20
#define HDC_ADDR 0x40
#define BMP_ADDR 0x76

typedef enum {
    BMP_DEVICE_ID = 0x00,
} BMP388_Pointers;

typedef enum {
    HDC_TEMPERATURE = 0x00,
    HDC_HUMIDITY = 0x01,
    HDC_CONFIGURATION = 0x02,
    HDC_MANUFACTURER_ID = 0xFE,
    HDC_DEVICE_ID = 0xFF,
    HDC_SERIAL_ID_FIRST = 0xFB,
    HDC_SERIAL_ID_MID = 0xFC,
    HDC_SERIAL_ID_LAST = 0xFD,
} HDC1010_Pointers;

typedef union {
    uint8_t rawData;
    struct {
        uint8_t HumidityMeasurementResolution : 2;
        uint8_t TemperatureMeasurementResolution : 1;
        uint8_t BatteryStatus : 1;
        uint8_t ModeOfAcquisition : 1;
        uint8_t Heater : 1;
        uint8_t ReservedAgain : 1;
        uint8_t SoftwareReset : 1;
    };
} HDC1010_Registers;

static void Array_sort(uint32_t *array , int n);
uint32_t Find_median(uint32_t array[] , int n);
//void timerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);
static bool I2C_send(uint8_t slave_addr, uint8_t txBuffer[], uint8_t writeCount);
uint16_t BMP_readData(uint8_t slave_addr, uint8_t ptr);
uint16_t HDC_readData(uint8_t slave_addr, uint8_t ptr);
void enableSensors();
void disableSensors();
uint16_t readRawHumidity(uint8_t addr);
uint16_t readRawTemperature(uint8_t addr);
uint16_t readRawPressure(uint8_t addr);
uint16_t readRawLight(uint8_t addr);
uint16_t readRawBattery(uint8_t addr);
void fetchSensorData();
void InitSensors();





#endif /* SENSOR_H_ */
