PROJ_NAME=benchmarker

WORKER_NUM?=7
MAIN_CORE?=0
MAIN_PRIO?=0
CFLAGS += -DWORKER_NUM=$(WORKER_NUM) -DMAIN_CORE=$(MAIN_CORE) -DMAIN_PRIO=$(MAIN_PRIO)

BENCH?=BENCH_BANDWIDTH
CFLAGS += -D$(BENCH)

DEBUG=no
BENCH=no
STANDALONE = ..

SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S) \
        ${STANDALONE}/common/start.S

RISCV_PATH?=/opt/riscv32/
RISCV_NAME?= riscv32-unknown-elf

MARCH=rv32ima_zicsr

include ../common/app.mk

