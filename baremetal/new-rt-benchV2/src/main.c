#include <type.h>
#include <riscv.h>
#include "common.h"
#include "bench.h"

/* Cause cache misses forever */
__attribute__((noreturn)) void endless_work(u32 hart_id)
{

    signal_hart_ready();

    set_target_prio(hart_id);

    u32 sum = 0;
    while (1)
    {
        cache_miss_access(BUFFER_START + hart_id * BUFFER_SIZE, BUFFER_START + (hart_id + 1) * BUFFER_SIZE, &sum);
    }
}

/* Wait forever */
__attribute__((noreturn)) void endless_wait()
{
    signal_hart_ready();

    while (1)
    {
        asm("wfi");
    }
}

void main()
{
    u32 hart_id = csr_read(mhartid);
    u32 worker_bound = WORKER_NUM + 1;
    if (MAIN_CORE > worker_bound)
        worker_bound -= 1;

    if (hart_id == MAIN_CORE)
    {
        put_str("Setting up for:\n");
        print_config();

        signal_hart_ready();

        put_str("Waiting for all cores to signal ready\n");

        wait_for_all_harts();

        put_str("Starting benchmark\n");

        bench_main();
    }
    else
    {
        if (hart_id != MAIN_CORE && (hart_id < worker_bound))
            endless_work(hart_id);
        else if (hart_id != MAIN_CORE)
            endless_wait(hart_id);
    }

    put_str("::BENCHMARKS DONE::\n");
}
