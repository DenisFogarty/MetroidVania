################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Calculations.cpp \
../Collision.cpp \
../Display.cpp \
../GameScreen.cpp \
../Items.cpp \
../KeyboardInput.cpp \
../Level.cpp \
../LevelEditor.cpp \
../Main.cpp \
../Movement.cpp \
../Shoot.cpp \
../Sprites.cpp 

OBJS += \
./Calculations.o \
./Collision.o \
./Display.o \
./GameScreen.o \
./Items.o \
./KeyboardInput.o \
./Level.o \
./LevelEditor.o \
./Main.o \
./Movement.o \
./Shoot.o \
./Sprites.o 

CPP_DEPS += \
./Calculations.d \
./Collision.d \
./Display.d \
./GameScreen.d \
./Items.d \
./KeyboardInput.d \
./Level.d \
./LevelEditor.d \
./Main.d \
./Movement.d \
./Shoot.d \
./Sprites.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


