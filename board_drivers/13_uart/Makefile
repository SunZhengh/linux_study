CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET		  ?= high_ac_delay

CC			  := $(CROSS_COMPILE)gcc
LD            := $(CROSS_COMPILE)ld
OBJCOPY       := $(CROSS_COMPILE)objcopy
OBJDUMP       := $(CROSS_COMPILE)objdump

INCLUDIR	  := imx6ul \
			 	 bsp/led \
				 bsp/clk \
				 bsp/delay\
				 bsp/key\
				 bsp/beep\
				 bsp/exti\
				 bsp/gpio\
				 bsp/interrupt\
				 bsp/epit\
				 bsp/key_filter

SRCDIR    := project \
			 bsp/led \
			 bsp/clk \
			 bsp/delay\
			 bsp/key\
			 bsp/beep\
			 bsp/exti\
			 bsp/gpio\
			 bsp/interrupt\
			 bsp/epit\
			 bsp/key_filter

INCLUDE := $(patsubst %, -I %, $(INCLUDIR))
SDIRFILES  := $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.s))
CDIRFILES  := $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))

SFILES := $(notdir $(SDIRFILES))
CFILES := $(notdir $(CDIRFILES))

SOBJS	:= $(patsubst %, obj/%, $(SFILES:.s=.o))
COBJS	:= $(patsubst %, obj/%, $(CFILES:.c=.o))

OBJS := $(SOBJS)$(COBJS)

VPATH = $(SRCDIR)

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<
$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

.PHONY : clean

clean:
	rm -rf $(OBJS) *.bin *.dis *.elf *.imx
print:
	@echo INCLUDE = $(INCLUDE)
	@echo SFILES = $(SFILES)
	@echo CFILES = $(CFILES)
	@echo SOBJS = $(SOBJS)
	@echo COBJS = $(COBJS)
	@echo OBJS = $(OBJS)
