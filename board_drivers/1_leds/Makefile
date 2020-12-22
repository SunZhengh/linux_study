led.bin:leds.s
	arm-linux-gnueabihf-gcc -g -c leds.s -o leds.o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 leds.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S led.elf led.bin
	arm-linux-gnueabihf-objdump -D led.elf > led.dis 

.PHONY: clean

clean: 
	rm -rf *.o *.bin *.elf *.dis 
