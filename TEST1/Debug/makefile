################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf tinyara.bin tinyara_head.bin "TEST1.map"

# All of the sources participating in the build are defined here
-include sources.mk
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
all: TEST1 secondary-outputs

# Tool invocations
TEST1: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARTIK GCC C Linker'
	arm-none-eabi-ld  -T"C:/ARTIK/SDK/A053/v1.7/common/scripts/flash.ld" -nostartfiles -nodefaultlibs -L"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/libs" -L"C:/ARTIK/toolchains/gcc-arm-none-eabi/v4.9-2015q3/lib/gcc/arm-none-eabi/4.9.3" -Map="TEST1.map" --gc-sections --entry=__start "C:/ARTIK/SDK/A053/v1.7/libsdk/typical/libs/arm_vectortab.o" -o "TEST1" --start-group $(OBJS) $(USER_OBJS) $(LIBS) --end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

tinyara.bin: TEST1
	@echo 'Invoking: ARTIK GCC Create Flash Image'
	arm-none-eabi-objcopy -O binary "TEST1"  "tinyara.bin"
	@echo 'Finished building: $@'
	@echo ' '

tinyara_head.bin: tinyara.bin
	@echo 'Invoking: ARTIK GCC Create Head Bin'
	C:/ARTIK/SDK/A053/v1.7/common/tools/s5jchksum.py "tinyara.bin"  "tinyara_head.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(ASM_DEPS)$(S_UPPER_DEPS)$(SECONDARY_HEADBIN)$(C_DEPS) TEST1
	-@echo ' '

post-build:
	-echo "Next step is to generate .bin file"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_HEADBIN)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
