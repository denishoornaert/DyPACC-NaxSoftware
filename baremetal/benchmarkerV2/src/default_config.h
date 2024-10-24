#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#define BENCH_BANDWIDTH 1
#define BENCH_LATENCY 2
#define BENCH_C2C_BUFFER 3
#define BENCH_C2C_CAS 4

#define TRUE 1
#define FALSE 0

// Defines the cache that should be thrashed, default is L1
#ifndef BENCH_L2
#define BENCH_L2 FALSE
#warning "No cache specified, using default"
#endif

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
#if !defined(SECOND_CORE) && (BENCH == BENCH_C2C_BUFFER || BENCH == BENCH_C2C_CAS)
#define SECOND_CORE 1
#warning "No second_core specified, using default"
#endif

// Defines the priority of the core under analysis
#ifndef MAIN_PRIO
#define MAIN_PRIO 7
#warning "No main_prio specified, using default"
#endif

// Defines the priority of the second core under analysis in C2C
#if !defined(SECOND_PRIO) && (BENCH == BENCH_C2C_BUFFER || BENCH == BENCH_C2C_CAS)
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

// Defines the number of pings for c2c
#if !defined(N_PINGS) && (BENCH == BENCH_C2C_BUFFER || BENCH == BENCH_C2C_CAS)
#define N_PINGS 100
#warning "No pings specified, using default"
#endif

#if !defined(USE_PING_GROUP) && (BENCH == BENCH_C2C_BUFFER || BENCH == BENCH_C2C_CAS)
#define USE_PING_GROUP FALSE
#warning "No ping group usage specified, using default"
#endif

// Defines the number of runs that are benchmarked
#ifndef PRIO_SUPPORT
#define PRIO_SUPPORT FALSE
#warning "No prio support specified, using default"
#endif

#if USE_PING_GROUP == TRUE
#define CORE_COUNT 8

#ifndef PG0
#define PG0 0
#endif
#ifndef PG1
#define PG1 1
#endif
#ifndef PG2
#define PG2 2
#endif
#ifndef PG3
#define PG3 3
#endif
#ifndef PG4
#define PG4 4
#endif
#ifndef PG5
#define PG5 5
#endif
#ifndef PG6
#define PG6 6
#endif
#ifndef PG7
#define PG7 7
#endif
#endif

#endif