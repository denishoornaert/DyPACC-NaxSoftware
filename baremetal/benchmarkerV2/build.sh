#!/bin/bash

make clean


make LITEX=TRUE \
    PRIO_SUPPORT=FALSE \
    BENCH_L2=TRUE \
    N_RUNS=128 \
    MAIN_CORE=0 \
    SECOND_CORE=1 \
    BENCHMARK=BENCH_BANDWIDTH \
    WORKER_NUM=7
  

# make LITEX=TRUE \
#     PRIO_SUPPORT=FALSE \
#     BENCH_L2=FALSE \
#     N_RUNS=124 \
#     MAIN_CORE=0 \
#     SECOND_CORE=1 \
#     BENCHMARK=BENCH_C2C_CAS \
#     WORKER_NUM=2 \
#     USE_PING_GROUP=TRUE \
#     PG2=2 PG3=2 \
#     PG4=4 PG5=4 \
#     PG6=6 PG7=6


# make LITEX=TRUE \
#     PRIO_SUPPORT=FALSE \
#     INIT_DELAY=0 \
#     BENCH_L2=FALSE \
#     N_RUNS=32 \
#     MAIN_CORE=0 \
#     SECOND_CORE=1 \
#     BENCHMARK=BENCH_C2C_CAS \
#     WORKER_NUM=4 \
#     USE_PING_GROUP=TRUE \
#     PG2=2 PG3=2 \
#     PG4=2 PG5=2 \
#     PG6=7 PG7=7