#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#define BENCH_BANDWIDTH 0
#define BENCH_LATENCY 1
#define BENCH_C2C 2

#define TRUE 1
#define FALSE 0

// Defines benchmark that should be performed, default is bandwidth
#ifndef BENCH
#define BENCH BENCH_BANDWIDTH
#warning "No benchmark specified, using default"
#endif

// Defines the number of harts that will attempt to cause cache misses
#ifndef WORKER_NUM
#define WORKER_NUM 7
#warning "No worker_num specified, using default"
#endif

// Defines the core under analysis
#ifndef MAIN_CORE
#define MAIN_CORE 0
#warning "No main_core specified, using default"
#endif

// Defines the second core under analysis in C2C
#if !defined(SECOND_CORE) && BENCH == BENCH_C2C
#define SECOND_CORE 1
#warning "No second_core specified, using default"
#endif

// Defines the priority of the core under analysis
#ifndef MAIN_PRIO
#define MAIN_PRIO 7
#warning "No main_prio specified, using default"
#endif

// Defines the priority of the second core under analysis in C2C
#if !defined(SECOND_PRIO) && BENCH == BENCH_C2C
#define SECOND_PRIO 0
#warning "No second_prio specified, using default"
#endif

// Defines the minimum delay in cycles before the benchmarks are run (can be used as seed)
#ifndef INIT_DELAY
#define INIT_DELAY 0
#warning "No init_delay specified, using default"
#endif

// Defines the number of runs that are benchmarked
#ifndef N_RUNS
#define N_RUNS 3
#warning "No n_runs specified, using default"
#endif

#endif