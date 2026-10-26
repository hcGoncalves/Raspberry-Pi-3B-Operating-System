CFILES = $(wildcard src/*.c)
ASMFILES = $(wildcard src/*.s)
OFILES = $(patsubst src/%.c, build/%.o, $(CFILES))
OSMFILES = $(patsubst src/%.s, build/%.o, $(ASMFILES))

LIBFDTFILES = $(wildcard libfdt/*.c)
OLIBFDTFILES = $(patsubst libfdt/%.c, build/%.o, $(LIBFDTFILES))


GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -mstrict-align -Iinclude -Ilibfdt/include
GCCPATH = ~/CompilersAndSDKs/arm-gnu-toolchain-15.3.rel1-x86_64-aarch64-none-elf/bin/

build/%.o: src/%.s
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

build/%.o: src/%.c
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

build/%.o: libfdt/%.c
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: $(OSMFILES) $(OFILES) $(OLIBFDTFILES)
	$(GCCPATH)/aarch64-none-elf-ld -nostdlib $(OSMFILES) $(OFILES) $(OLIBFDTFILES) -T link.ld -o kernel8.elf
	$(GCCPATH)/aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

#clean:
#	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true
