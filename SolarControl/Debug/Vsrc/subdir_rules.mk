################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Vsrc/%.obj: ../Vsrc/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/CMS2810_IDEws/SolarControl" --include_path="C:/CMS2810_IDEws/SolarControl/Vinclude" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --include_path="C:/CMS2810_IDEws/SolarControl/include" --define=CANTORS_ENA --define=MODBUS_ENA -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Vsrc/$(basename $(<F)).d_raw" --obj_directory="Vsrc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


