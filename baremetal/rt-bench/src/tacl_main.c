#include <sim.h>
#include <type.h>
#include <riscv.h>
#include "putnum.h"

#if defined(BENCH_THRESHOLD) || defined(BENCH_GRAYSCALE) || defined(BENCH_SEPIA) || defined(BENCH_SOBEL) || defined(BENCH_GAUSSIAN_NOISE)
// ignore
#else
extern int benchmark_init(int parameters_num, void **parameters);
extern void benchmark_execution(int parameters_num, void **parameters);

static void *params[4] = {0, 0, 0, 0};

void tacl_main()
{

    sim_puts("Running TACL-BENCH: \n");
    sim_puts("  tacl-init... \n");
    benchmark_init(4, (void **)&params);
    sim_puts("    done\n  executing benchmark...");

    u32 start_t = sim_time();
    u32 start_c = sim_time();

    benchmark_execution(4, (void **)&params);

    u32 end_c = sim_time();
    u32 end_t = sim_time();

    sim_puts("    done\n");
    sim_puts("Cycles: 0x");
    sim_puthex(end_c - start_c);
    sim_puts(" = ");
    sim_put_num(end_c - start_c);
    sim_puts("\n");
    sim_puts("Time: 0x");
    sim_puthex(end_t - start_t);
    sim_puts(" = ");
    sim_put_num(end_t - start_t);
    sim_puts("\n");

    // Wait for output to stabalize before finishing
    while (csr_read(mcycle) - end_c < 1000)
        ;
}
#endif