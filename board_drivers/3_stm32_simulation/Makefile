objs  	:= start.o main.o
gcc		:= arm-linux-gnueabihf-gcc
ld		:= arm-linux-gnueabihf-ld
objcopy := arm-linux-gnueabihf-objcopy
objdump := arm-linux-gnueabihf-objdump

ledc.bin : $(objs)
	$(ld) -Timx6u.lds -o ledc.elf $^
	$(objcopy) -O binary -S ledc.elf $@
	$(objdump) -D -m arm ledc.elf > ledc.dis

%.o : %.c
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.s
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

.PHONY : clean

clean: 
	rm -rf *.o *.bin *.elf *.dis
