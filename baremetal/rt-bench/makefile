PROJ_NAME=rt-bench

WORKER_NUM?=7
MAIN_CORE?=0
MAIN_PRIO?=7
CFLAGS += -DWORKER_NUM=$(WORKER_NUM) -DMAIN_CORE=$(MAIN_CORE) -DMAIN_PRIO=$(MAIN_PRIO)

BENCH?=BENCH_THRESHOLD
CFLAGS += -D$(BENCH)

CFLAGS += -fno-zero-initialized-in-bss -lm

DEBUG=no
BENCH=no
STANDALONE = ..
	
# $(wildcard src/image-filters/src/*.c)	
SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S) \
		src/image-filters/src/filters.c \
		src/patches/common_filters.c \
		src/patches/file.S \
		src/patches/math.c \
		$(wildcard src/tacl-bench/${BENCH}/*.c) \
		src/patches/start.S

RISCV_PATH?=/opt/riscv32/
RISCV_NAME?= riscv32-unknown-elf

MARCH=rv32ima_zicsr

include ../common/app.mk

