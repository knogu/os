TARGET = kernel.bin
CFLAGS = -Wall -Wextra -nostdinc -nostdlib -fno-builtin -fno-common -Iinclude
LDFLAGS = -Map kernel.map -s -x -T kernel.ld

$(TARGET): main.o fbcon.o fb.o font.o
	x86_64-elf-ld $(LDFLAGS) -o $@ $+

%.o: %.c
	x86_64-elf-gcc $(CFLAGS) -c -o $@ $<

# run: $(TARGET)
# 	cp $(TARGET) ../fs/
# 	qemu-system-x86_64 -m 4G -bios OVMF.fd -hda fat:../fs

clean:
	rm -f *~ *.o *.map $(TARGET)

.PHONY: run clean
