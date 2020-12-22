ARM		?= arm-linux-gnueabihf-
TARGET	?= beep

INCLUDE_DIR := imx6ul \
				bsp/beep \
				bsp/clk \
				bsp/delay
SRC_DIR := project \
			bsp/beep \
			bsp/clk \
			bsp/delay

INCLUDE := $(patsubst %, -I %, $(INCLUDE_DIR))
S_FILES_DIR := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.s))
C_FILES_DIR := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))

S_FILES := $(notdir $(S_FILES_DIR))
C_FILES := $(notdir $(C_FILES_DIR))

S_OBJ := $(patsubst %, obj/%, $(S_FILES:.s=.o))
C_OBJ := $(patsubst %, obj/%, $(C_FILES:.c=.o))

VPATH = $(SRC_DIR)

$(TARGET).bin : $(S_OBJ)$(C_OBJ)
	$(ARM)ld -Timx6u.lds -o $(TARGET).elf $^
	$(ARM)objcopy -O binary -S $(TARGET).elf $@
	$(ARM)objdump -D -m arm $(TARGET).elf > $(TARGET).dis

$(S_OBJ) : $(S_FILES)
	$(ARM)gcc -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(C_OBJ) : obj/%.o : %.c	
	$(ARM)gcc -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

.PHONY : clean

clean:
	rm -rf $(S_OBJ) $(C_OBJ) *.bin *.dis *.elf *.imx

print:
	@echo S_FILES_DIR = $(S_FILE_DIR)
	@echo C_FILES_DIR = $(C_FILE_DIR)
	@echo S_FILES = $(S_FILES)
	@echo C_FILES = $(C_FILES)
	@echo S_OBJ = $(S_OBJ)
	@echo C_OBJ = $(C_OBJ)


