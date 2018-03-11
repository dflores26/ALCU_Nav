################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/command.c \
../src/distance.c \
../src/gpio.c \
../src/gps.c \
../src/gps_app.c \
../src/nav_app.c \
../src/navigate.c \
../src/sensor_read.c \
../src/vt_100.c 

OBJS += \
./src/command.o \
./src/distance.o \
./src/gpio.o \
./src/gps.o \
./src/gps_app.o \
./src/nav_app.o \
./src/navigate.o \
./src/sensor_read.o \
./src/vt_100.o 

C_DEPS += \
./src/command.d \
./src/distance.d \
./src/gpio.d \
./src/gps.d \
./src/gps_app.d \
./src/nav_app.d \
./src/navigate.d \
./src/sensor_read.d \
./src/vt_100.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARTIK GCC C Compiler'
	arm-none-eabi-gcc  -D__TINYARA__ -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/include/apps" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/framework_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/apps_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/apps_include/netutils" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/base" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/connectivity" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/systemio" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/wifi" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/lwm2m" -I"C:/ARTIK/SDK/A053/v1.7/libsdk/typical/artik-sdk_include/mqtt" -std=gnu99 -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -Wstrict-prototypes -Wshadow -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-but-set-variable -DAPP_STACKSIZE=18432 -DAPP_PRIORITY=100 -mcpu=cortex-r4 -mfpu=vfpv3 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


