################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../../Source/HtlStddef.c \
../../../Source/Ringbuffer.c \
../../../Source/TestRingbuffer.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
HtlStddef.o \
Ringbuffer.o \
TestRingbuffer.o

OBJS_AS_ARGS +=  \
HtlStddef.o \
Ringbuffer.o \
TestRingbuffer.o

C_DEPS +=  \
HtlStddef.d \
Ringbuffer.d \
TestRingbuffer.d

C_DEPS_AS_ARGS +=  \
HtlStddef.d \
Ringbuffer.d \
TestRingbuffer.d

OUTPUT_FILE_PATH +=TestRingbuffer.elf

OUTPUT_FILE_PATH_AS_ARGS +=TestRingbuffer.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./HtlStddef.o: ../../../Source/HtlStddef.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./Ringbuffer.o: ../../../Source/Ringbuffer.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./TestRingbuffer.o: ../../../Source/TestRingbuffer.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="TestRingbuffer.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p"  
	@echo Finished building target: $@
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "TestRingbuffer.elf" "TestRingbuffer.hex"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "TestRingbuffer.elf" "TestRingbuffer.eep" || exit 0
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "TestRingbuffer.elf" > "TestRingbuffer.lss"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "TestRingbuffer.elf" "TestRingbuffer.srec"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "TestRingbuffer.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "TestRingbuffer.elf" "TestRingbuffer.a" "TestRingbuffer.hex" "TestRingbuffer.lss" "TestRingbuffer.eep" "TestRingbuffer.map" "TestRingbuffer.srec" "TestRingbuffer.usersignatures"
	