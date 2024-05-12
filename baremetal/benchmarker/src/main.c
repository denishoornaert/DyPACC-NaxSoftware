#include <sim.h>
#include <type.h>
#include <riscv.h>
#include "common.h"
#include "bench.h"

/* Cause cache misses forever */
__attribute__((noreturn)) void endless_work(u32 hart_id)
{

    signal_hart_ready();

    // C0 to C7 have decreasing priorities
    u32 target_prio = 7 - hart_id;
    // If main core has same prio as this coworker default, use the main cores default instead
    u32 new_prio = target_prio == MAIN_PRIO ? (7 - MAIN_CORE) : target_prio;

    set_prios(new_prio, new_prio, new_prio);

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
#if BENCH != BENCH_C2C
    u32 worker_bound = WORKER_NUM + 1;
    if (MAIN_CORE > worker_bound)
        worker_bound -= 1;
#else
    u32 worker_bound = WORKER_NUM + 2;
    u32 runner_max = (MAIN_CORE > SECOND_CORE ? MAIN_CORE : SECOND_CORE);
    u32 runner_min = (MAIN_CORE < SECOND_CORE ? MAIN_CORE : SECOND_CORE);
    if (runner_max > worker_bound)
        worker_bound -= 1;
    if (runner_min > worker_bound)
        worker_bound -= 1;
#endif

    if (hart_id == MAIN_CORE)
    {

        signal_hart_ready();

        sim_puts("Waiting for all cores to signal ready\n");

        wait_for_all_harts();

        bench_main();
    }
#if BENCH == BENCH_C2C
    else if (hart_id == SECOND_CORE)
    {

        signal_hart_ready();

        bench_second();
    }
#endif
    else
    {
        if (hart_id != MAIN_CORE && (hart_id < worker_bound))
            endless_work(hart_id);
        else if (hart_id != MAIN_CORE)
            endless_wait(hart_id);
    }
}
