PROJ_NAME=litex_hello

DEBUG=no
BENCH=no
STANDALONE = ..

SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S)

RISCV_PATH?=/opt/riscv32/
RISCV_NAME?= riscv32-unknown-elf

MARCH=rv32ima_zicsr

LDSCRIPT=../common/litex_app.ld

include ../common/app.mk

