#ifndef BENCH_H
#define BENCH_H

#include "common.h"

/* Runs the main benchmark on the current hart */
void bench_main();

/* Runs the second part of the benchmark on the current hart */
void bench_second();

#endif