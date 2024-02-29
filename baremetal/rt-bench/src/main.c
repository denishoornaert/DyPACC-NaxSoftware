#include <sim.h>
#include <type.h>
#include <riscv.h>

// The benchmark init function, which will be defined by the benchmark itself
extern int benchmark_init(int parameters_num, void **parameters);

// The benchmark execution function, which will be defined by the benchmark itself
extern void benchmark_execution(int parameters_num, void **parameters);

// The benchmark teardown function, which will be defined by the benchmark itself
extern void benchmark_teardown(int parameters_num, void **parameters);

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
#define MAIN_PRIO 0
#endif

/* Inefficient function to print a number in base 10 */
void sim_put_num(u32 value)
{
    int i = 1000000000;
    while (value / i == 0 && i > 1)
        i /= 10;

    while (i > 0)
    {
        sim_putchar('0' + (value / i) % 10);
        i /= 10;
    }
}

/* Access data between start and end, (hopefully) causing cache misses */
void dummy_work(const u32 start, const u32 end, u32 *sum)
{
    for (u8 *p = (u8 *)start; p < (u8 *)end; p += CACHE_LINE_SIZE)
        (*sum) += (*p); // should perform memory access
}

/* Cause cache misses forever */
__attribute__((noreturn)) void endless_work(u32 hart_id)
{
    u32 new_prio = hart_id == MAIN_PRIO ? MAIN_CORE : hart_id;
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

    sim_puts("RT-BENCH init: ");
    benchmark_init(0, 0); // ToDo: Check Return Value

    u32 start_t = sim_time();
    u32 start_c = csr_read(mcycle);

    // benchmark_execution(0, 0); // ToDo: Check Return Value

    u32 end_c = csr_read(mcycle);
    u32 end_t = sim_time();

    /* Can probably be ignored on bare metal */
    // benchmark_teardown(0, 0); // ToDo: Check Return Value

    sim_puts("BufferSize: 0x");
    sim_puthex(BUFFER_SIZE);
    sim_puts(" = ");
    sim_put_num(BUFFER_SIZE);
    sim_puts("\n");
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
