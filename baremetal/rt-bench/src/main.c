#include <sim.h>
#include <type.h>
#include <riscv.h>
#include "putnum.h"
#include "filter_main.h"
#include "tacl_main.h"

#define NUM_CORES 8
#define BUFFER_START (0x80000000 + (512 << 10))
#define D_CACHE_SIZE (16 << 10)
#define BUFFER_SIZE (D_CACHE_SIZE * 4)
#define CACHE_LINE_SIZE 64

// Defines the number of harts that will attempt to cause cache misses
#ifndef WORKER_NUM
#define WORKER_NUM 7
#endif

// Defines the core under analysis
#ifndef MAIN_CORE
#define MAIN_CORE 0
#endif

// Defines the priority of the core under analysis
#ifndef MAIN_PRIO
#define MAIN_PRIO 7
#endif

/* Access data between start and end, (hopefully) causing cache misses */
void dummy_work(const u32 start, const u32 end, u32 *sum)
{
    for (u8 *p = (u8 *)start; p < (u8 *)end; p += CACHE_LINE_SIZE)
        (*sum) += (*p); // should perform memory access
}

/* Cause cache misses forever */
__attribute__((noreturn)) void endless_work(u32 hart_id)
{
    u32 target_prio = 7 - hart_id;
    u32 new_prio = target_prio == MAIN_PRIO ? (7 - MAIN_CORE) : target_prio;
    u32 old_data_prio = csr_swap(0xBC0, new_prio);
    u32 old_fetch_prio = csr_swap(0xBC4, new_prio);
    u32 old_peri_prio = csr_swap(0xBC8, new_prio);

    u32 sum = 0;
    while (1)
    {
        dummy_work(BUFFER_START + hart_id * BUFFER_SIZE, BUFFER_START + (hart_id + 1) * BUFFER_SIZE, &sum);
    }
}

/* Wait forever */
__attribute__((noreturn)) void endless_wait()
{
    while (1)
    {
        asm("wfi");
    }
}

void main()
{
    u32 hart_id = csr_read(mhartid);
    if (hart_id != MAIN_CORE && (hart_id < WORKER_NUM || (MAIN_CORE < WORKER_NUM && hart_id <= WORKER_NUM)))
        endless_work(hart_id);
    else if (hart_id != MAIN_CORE)
        endless_wait();

    u32 new_fetch_prio = MAIN_PRIO;
    u32 new_data_prio = MAIN_PRIO;
    u32 new_peri_prio = MAIN_PRIO;
    u32 old_data_prio = csr_swap(0xBC0, new_data_prio);
    u32 old_fetch_prio = csr_swap(0xBC4, new_fetch_prio);
    u32 old_peri_prio = csr_swap(0xBC8, new_peri_prio);
    sim_puts("DataBus prio changed from ");
    sim_puthex(old_data_prio);
    sim_puts(" to ");
    sim_put_num(new_data_prio);
    sim_puts("\n");
    sim_puts("InstructionBus prio changed from ");
    sim_puthex(old_fetch_prio);
    sim_puts(" to ");
    sim_put_num(new_fetch_prio);
    sim_puts("\n");
    sim_puts("PeripheralBus prio changed from ");
    sim_puthex(old_peri_prio);
    sim_puts(" to ");
    sim_put_num(new_peri_prio);
    sim_puts("\n");

#if defined(BENCH_THRESHOLD) || defined(BENCH_GRAYSCALE) || defined(BENCH_SEPIA) || defined(BENCH_SOBEL) || defined(BENCH_GAUSSIAN_NOISE)
    filter_main();
#else
    tacl_main();
#endif
}
