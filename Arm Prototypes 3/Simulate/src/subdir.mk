################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ArmCode.cpp \
../src/Robot.cpp \
../src/Xbox.cpp 

OBJS += \
./src/ArmCode.o \
./src/Robot.o \
./src/Xbox.o 

CPP_DEPS += \
./src/ArmCode.d \
./src/Robot.d \
./src/Xbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Robotics\workspace\Arm Prototypes 3/src" -IC:\Users\Team 114/wpilib/cpp/current/sim/include -I/usr/include -I/usr/include/gazebo-3.1 -I/usr/include/sdformat-2.2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


