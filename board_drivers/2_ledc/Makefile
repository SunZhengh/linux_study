obj := start.o main.o
led_c.bin: $(obj)
	arm-linux-gnueabihf-ld -Tled_c.lds $^ -o led_c.elf 	
	arm-linux-gnueabihf-objcopy -O binary -S led_c.elf $@
	arm-linux-gnueabihf-objdump -D -m arm led_c.elf > led_c.dis
%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

.PHONY:clean
clean:
	rm -rf *.o *.dis *.bin *.elf





