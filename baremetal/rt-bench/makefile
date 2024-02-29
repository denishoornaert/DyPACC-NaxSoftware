PROJ_NAME=rt-bench

CFLAGS += -lm

DEBUG=no
BENCH=no
STANDALONE = ..

SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S) \
		src/image-filters/src/grayscale.c \
		src/image-filters/src/filters.c \
		src/patches/common.c \
        ${STANDALONE}/common/start.S

RISCV_PATH?=/opt/riscv32/
RISCV_NAME?= riscv32-unknown-elf

MARCH=rv32ima_zicsr

include ../common/app.mk

