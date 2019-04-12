CLEANUP = rm -f
MKDIR = mkdir -p

.PHONY: clean test project

PATH_SRC = src/
PATH_SRC_LIB = ../nxtiot/src/
PATH_INC_LIB = ../nxtiot/include/
PATH_BLD = build/
PATH_OBJ = build/objs/
BASENAME = button_nxtiot_gcc
PROJECT_ELF = $(PATH_BLD)$(BASENAME).elf
PROJECT_HEX = $(PATH_BLD)$(BASENAME).hex

BUILD_PATHS = $(PATH_BLD) $(PATH_OBJ)

SRC = $(wildcard $(PATH_SRC)*.c)
SRC_LIB = $(wildcard $(PATH_SRC_LIB)*.c)

OBJ = $(patsubst $(PATH_SRC)%.c,$(PATH_OBJ)%.o,$(SRC))
OBJ_LIB = $(patsubst $(PATH_SRC_LIB)%.c,$(PATH_OBJ)%.o,$(SRC_LIB))

###############################################################################
#
# -Os tells the compiler to optimize the code for efficient space usage
# -g is used to embed debug info
#
###############################################################################
MCU = atmega328p
FCPU = 16000000
COMPILER = avr-gcc
LINKER = avr-gcc
OBJCOPY = avr-objcopy -j .text -j .data -O ihex
INCLUDE = -I$(PATH_INC_LIB)
CFLAGS = -c -ggdb -O3 -w -Wall -std=c11 -mmcu=$(MCU) -DF_CPU=$(FCPU)
LFLAGS = -Os -ggdb -mmcu=$(MCU)

all: project

project: $(BUILD_PATHS) $(PROJECT_HEX)

flash: $(PROJECT_HEX)
	avrdude -v -p $(MCU) -c arduino -P /dev/tty.usbserial-AI05GFTR -D -U flash:w:$<:i

bin: $(PROJECT_HEX)
	avr-objcopy -I ihex -O binary $< $(PATH_BLD)$(BASENAME).bin

$(PROJECT_HEX): $(OBJ) $(OBJ_LIB)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC AVR Linker'
	$(LINKER) $(LFLAGS) -o $(PROJECT_ELF) $^
	$(OBJCOPY) $(PROJECT_ELF) $@
	@echo 'Finished building target: $@'
	@echo ' '

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC AVR Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDE) $< -o $@
	@echo 'Finished building: $<'
	@echo ' '

$(PATH_OBJ)%.o: $(PATH_SRC_LIB)%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC AVR Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDE) $< -o $@
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_PATHS):
	$(MKDIR) $(PATH_BLD)
	$(MKDIR) $(PATH_OBJ)

clean:
	$(CLEANUP) $(PATH_OBJ)*.o
	$(CLEANUP) $(PATH_BLD)*.hex
	$(CLEANUP) $(PATH_BLD)*.elf

.PRECIOUS: $(PATH_OBJ)%.o
