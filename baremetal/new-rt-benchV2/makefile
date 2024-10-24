PROJ_NAME=rt-bench

LITEX?=FALSE

WORKER_NUM?=7
MAIN_CORE?=0
MAIN_PRIO?=7
N_RUNS?=5
INIT_DELAY?=0
BENCHMARK?=BENCH_THRESHOLD
PRIO_SUPPORT?=TRUE
BENCH_L2?=TRUE
CFLAGS += -DWORKER_NUM=$(WORKER_NUM) -DLITEX=$(LITEX) -DBENCH_L2=$(BENCH_L2) -DMAIN_CORE=$(MAIN_CORE) -DMAIN_PRIO=$(MAIN_PRIO) -DN_RUNS=$(N_RUNS) -DINIT_DELAY=$(INIT_DELAY) -DBENCH=$(BENCHMARK) -DPRIO_SUPPORT=$(PRIO_SUPPORT) -DN_PINGS=$(N_PINGS) -DSECOND_PRIO=$(SECOND_PRIO) -DSECOND_CORE=$(SECOND_CORE)

INCLUDE_SQCIF?=FALSE
ifeq ($(INCLUDE_SQCIF), TRUE)
	CFLAGS += -DINCLUDE_SQCIF
endif
INCLUDE_CIF?=FALSE
ifeq ($(INCLUDE_CIF), TRUE)
	CFLAGS += -DINCLUDE_CIF
endif
INCLUDE_VGA?=FALSE
ifeq ($(INCLUDE_VGA), TRUE)
	CFLAGS += -DINCLUDE_VGA
endif
INCLUDE_FULLHD?=FALSE
ifeq ($(INCLUDE_FULLHD), TRUE)
	CFLAGS += -DINCLUDE_FULLHD
endif
INCLUDE_4K?=FALSE
ifeq ($(INCLUDE_4K), TRUE)
	CFLAGS += -DINCLUDE_4K
endif

CFLAGS += -fno-zero-initialized-in-bss -lm

DEBUG=no
BENCH=yes
STANDALONE = ..
	
# $(wildcard src/image-filters/src/*.c)	
SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S) \
		src/image-filters/src/filters.c \
		src/patches/common_filters.c \
		src/patches/file.S \
		src/patches/math.c \
		$(wildcard src/tacl-bench/$(BENCHMARK)/*.c)


RISCV_PATH?=/opt/riscv32/
RISCV_NAME?= riscv32-unknown-elf

MARCH=rv32ima_zicsr

ifeq ($(LITEX), TRUE)
	LDSCRIPT=../common/litex_rt_app.ld
endif

include ../common/app.mk

