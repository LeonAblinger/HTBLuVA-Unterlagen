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
../../../Source/RS232.c \
../../../Source/TestRS232.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
HtlStddef.o \
Ringbuffer.o \
RS232.o \
TestRS232.o

OBJS_AS_ARGS +=  \
HtlStddef.o \
Ringbuffer.o \
RS232.o \
TestRS232.o

C_DEPS +=  \
HtlStddef.d \
Ringbuffer.d \
RS232.d \
TestRS232.d

C_DEPS_AS_ARGS +=  \
HtlStddef.d \
Ringbuffer.d \
RS232.d \
TestRS232.d

OUTPUT_FILE_PATH +=TestRS232.elf

OUTPUT_FILE_PATH_AS_ARGS +=TestRS232.elf

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
	

./RS232.o: ../../../Source/RS232.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./TestRS232.o: ../../../Source/TestRS232.c
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
	$(QUOTE)D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="TestRS232.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega644p -B "D:\Program Files\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega644p"  
	@echo Finished building target: $@
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "TestRS232.elf" "TestRS232.hex"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "TestRS232.elf" "TestRS232.eep" || exit 0
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "TestRS232.elf" > "TestRS232.lss"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "TestRS232.elf" "TestRS232.srec"
	"D:\Program Files\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "TestRS232.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "TestRS232.elf" "TestRS232.a" "TestRS232.hex" "TestRS232.lss" "TestRS232.eep" "TestRS232.map" "TestRS232.srec" "TestRS232.usersignatures"
	