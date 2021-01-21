CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET		  ?= spi

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
				 bsp/key_filter\
				 bsp/uart\
				 bsp/lcd\
				 bsp/rtc\
				 bsp/i2c\
				 bsp/spi\
				 devices/ap3216c\
				 devices/icm20608\
				 stdio/include

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
			 bsp/key_filter\
			 bsp/uart\
			 bsp/lcd\
			 bsp/rtc\
			 bsp/i2c\
			 bsp/spi\
			 devices/ap3216c\
			 devices/icm20608\
			 stdio/lib

INCLUDE := $(patsubst %, -I %, $(INCLUDIR))
SDIRFILES  := $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.s))
CDIRFILES  := $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))

SFILES := $(notdir $(SDIRFILES))
CFILES := $(notdir $(CDIRFILES))

SOBJS	:= $(patsubst %, obj/%, $(SFILES:.s=.o))
COBJS	:= $(patsubst %, obj/%, $(CFILES:.c=.o))

OBJS := $(SOBJS)$(COBJS)

VPATH = $(SRCDIR)

LIBPATH := -lgcc -L /usr/local/arm/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/7.5.0

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<
$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -fno-builtin  -c -O2 $(INCLUDE) -o $@ $<

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
