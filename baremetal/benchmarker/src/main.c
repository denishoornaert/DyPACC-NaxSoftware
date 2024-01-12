#include <sim.h>
#include <type.h>
#include <riscv.h>

#define NUM_CORES 8
#define BUFFER_START (0x80000000 + (512 << 10))
#define D_CACHE_SIZE (16 << 10)
#define BUFFER_SIZE (D_CACHE_SIZE * 4)
#define CACHE_LINE_SIZE 64

// Defines the number of harts that will attempt to cause cache misses
#ifndef WORKER_NUM
#define WORKER_NUM 7
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
void dummy_work(const u32 start, const u32 end, u32* sum)
{
    for (u8 *p = (u8 *)start; p < (u8 *)end; p += CACHE_LINE_SIZE)
        (*sum) += (*p); // should perform memory access 
}

/* Cause cache misses forever */
__attribute__((noreturn)) void endless_work(u32 hart_id)
{
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
    if (hart_id > 0 && hart_id <= WORKER_NUM)
        endless_work(hart_id);
    else if (hart_id > 0)
        endless_wait();

    // Declare a checksum variable to enforce dummy work to be kept by the compiler
    u32 sum = 0;
    /* Hart 0 is being benchmarked */
    u32 start_t = sim_time();
    u32 start_c = csr_read(mcycle);
    dummy_work(BUFFER_START, BUFFER_START + BUFFER_SIZE, &sum); // because hart_id is 0
    u32 end_c = csr_read(mcycle);
    u32 end_t = sim_time();

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
    // The printing here is necessary to ensure that the 'sum' variable is not optimized away!
    sim_puts("Checksum: 0x");
    sim_puthex(sum);
    sim_puts("\n");

    // Wait for output to stabalize before finishing
    while (csr_read(mcycle) - end_c < 1000)
        ;
}
