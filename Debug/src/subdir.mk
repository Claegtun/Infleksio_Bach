################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ASTNode.cpp \
../src/Lexer.cpp \
../src/Parser.cpp \
../src/Token.cpp \
../src/functions.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/ASTNode.d \
./src/Lexer.d \
./src/Parser.d \
./src/Token.d \
./src/functions.d \
./src/main.d 

OBJS += \
./src/ASTNode.o \
./src/Lexer.o \
./src/Parser.o \
./src/Token.o \
./src/functions.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ASTNode.d ./src/ASTNode.o ./src/Lexer.d ./src/Lexer.o ./src/Parser.d ./src/Parser.o ./src/Token.d ./src/Token.o ./src/functions.d ./src/functions.o ./src/main.d ./src/main.o

.PHONY: clean-src

