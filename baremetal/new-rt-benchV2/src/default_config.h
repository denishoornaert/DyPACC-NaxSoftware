#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#ifndef BENCH_THRESHOLD
#define BENCH_THRESHOLD 1
#endif

#ifndef BENCH_GRAYSCALE
#define BENCH_GRAYSCALE 2
#endif

#ifndef BENCH_SEPIA
#define BENCH_SEPIA 3
#endif

#ifndef BENCH_SOBEL
#define BENCH_SOBEL 4
#endif

#ifndef BENCH_GAUSSIAN_NOISE
#define BENCH_GAUSSIAN_NOISE 5
#endif

#define TRUE 1
#define FALSE 0

// Defines the cache that should be thrashed, default is L1
#ifndef BENCH_L2
#define BENCH_L2 FALSE
#warning "No cache specified, using default"
#endif

// Defines benchmark that should be performed, default is bandwidth
#ifndef BENCH
#define BENCH BENCH_THRESHOLD
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

// Defines the priority of the core under analysis
#ifndef MAIN_PRIO
#define MAIN_PRIO 7
#warning "No main_prio specified, using default"
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

// Defines whether prios are supported
#ifndef PRIO_SUPPORT
#define PRIO_SUPPORT FALSE
#warning "No prio support specified, using default"
#endif

#endif