################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gps.c \
../src/gps_app.c 

OBJS += \
./src/gps.o \
./src/gps_app.o 

C_DEPS += \
./src/gps.d \
./src/gps_app.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARTIK GCC C Compiler'
	arm-none-eabi-gcc  -D__TINYARA__ -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/include/apps" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/framework_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/apps_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/apps_include/netutils" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/base" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/connectivity" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/systemio" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/wifi" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/lwm2m" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/mqtt" -std=gnu99 -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -Wstrict-prototypes -Wshadow -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-but-set-variable -DAPP_STACKSIZE=18432 -DAPP_PRIORITY=100 -mcpu=cortex-r4 -mfpu=vfpv3 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


