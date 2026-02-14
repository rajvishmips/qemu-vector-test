CC=/projects/mipssw/toolchains/riscv-elf/v3.10/bin/riscv32-mti-elf-gcc 
OBJDUMP=/projects/mipssw/toolchains/riscv-elf/v3.09/bin/riscv32-mti-elf-objdump
CFLAGS=-O2 -mlittle-endian -mtune=m8500 -mrvv-max-lmul=m8 -mabi=ilp32d -misa-spec=20191213 -mtls-dialect=trad -march=rv32imafdv_zicsr_zifencei_zaamo_zalrsc_zve32f_zve32x_zve64d_zve64f_zve64x_zvl128b_zvl32b_zvl64b -mlittle-endian -g -O3 -ffast-math -funroll-loops -finline-functions -ftree-vectorize
LDFLAGS=-O2 -mlittle-endian -mtune=m8500 -mrvv-max-lmul=m8 -misa-spec=20191213 -mtls-dialect=trad -mlittle-endian -g -O3 -ffast-math -funroll-loops -finline-functions -ftree-vectorize

HEADERS := $(wildcard *.h)
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:rvv

rvv :  $(HEADERS) $(OBJS)
	$(CC) $(OBJ) $(LDFLAGS) -o $@  $^
clean:
	- rm -f *.o rvv
 
