################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI" --include_path="C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI" --include_path="C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI/easylink" --include_path="C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI/smartrf_settings" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-473806495:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-473806495-inproc

build-473806495-inproc: ../rfExamples.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC1310F128 -r release -c "C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS" --compileOptions "-mv7M3 --code_state=16 --float_support=vfplib -me --include_path=\"C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI\" --include_path=\"C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI\" --include_path=\"C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI/easylink\" --include_path=\"C:/Users/admin/workspace_v9/rfWsnConcentrator_CC1310_LAUNCHXL_TI/smartrf_settings\" --include_path=\"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272\" --include_path=\"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include\" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-473806495 ../rfExamples.cfg
configPkg/compiler.opt: build-473806495
configPkg/: build-473806495


