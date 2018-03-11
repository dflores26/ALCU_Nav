################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf tinyara.bin tinyara_head.bin "gps_test.map"

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
tinyara.bin \

SECONDARY_HEADBIN += \
tinyara_head.bin \


# All Target
all: gps_test secondary-outputs

# Tool invocations
gps_test: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARTIK GCC C Linker'
	arm-none-eabi-ld  -T"C:/ARTIK/SDK/A053/v1.7/common/scripts/flash.ld" -nostartfiles -nodefaultlibs -L"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/libs" -L"C:/ARTIK/toolchains/gcc-arm-none-eabi/v4.9-2015q3/lib/gcc/arm-none-eabi/4.9.3" -Map="gps_test.map" --gc-sections -u _printf_float --entry=__start "C:/ARTIK/SDK/A053/v1.7/libsdk/typical/libs/arm_vectortab.o" -o "gps_test" --start-group $(OBJS) $(USER_OBJS) $(LIBS) --end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

tinyara.bin: gps_test
	@echo 'Invoking: ARTIK GCC Create Flash Image'
	arm-none-eabi-objcopy -O binary "gps_test"  "tinyara.bin"
	@echo 'Finished building: $@'
	@echo ' '

tinyara_head.bin: tinyara.bin
	@echo 'Invoking: ARTIK GCC Create Head Bin'
	C:/ARTIK/SDK/A053/v1.7/common/tools/s5jchksum.py "tinyara.bin"  "tinyara_head.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(ASM_DEPS)$(S_UPPER_DEPS)$(SECONDARY_HEADBIN)$(C_DEPS) gps_test
	-@echo ' '

post-build:
	-echo "Next step is to generate .bin file"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_HEADBIN)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
