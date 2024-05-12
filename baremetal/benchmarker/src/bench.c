#include "bench.h"
#ifdef BENCH_LATENCY
#include <string.h>
#endif

#ifdef BENCH_C2C

#define atomic_cmpxchg(obj, exp, val)                     \
    __extension__({                                       \
        __typeof__(obj) __obj = (obj);                    \
        __typeof__(obj) __exp = (exp);                    \
        __typeof__(*(obj)) __val = (val);                 \
        __typeof__(*(obj)) __result;                      \
        register unsigned int __ret;                      \
        __asm__ volatile(                                 \
            "0:  lr.w %0, %2\n"                           \
            "    bne  %0, %z3, 1f\n"                      \
            "    sc.w %1, %z4, %2\n"                      \
            "    bnez %1, 0b  \n"                         \
            "1:\n"                                        \
            : "=&r"(__result), "=&r"(__ret), "+A"(*__obj) \
            : "r"(*__exp), "r"(__val)                     \
            : "memory");                                  \
        __result;                                         \
    })

_Atomic(u32) PING = 32;
_Atomic(u32) PONG = 16;

_Atomic(u32) c2c_state = 32;
#endif

/* Perform a latency Benchmark, TODO: does this work or not? */
void latency_bench(const u32 start, const u32 end, u32 *sum)
{
    u8 *p = (u8 *)start;
    while (p < (u8 *)end)
    {
        p += (*p);
    }
    (*sum) = (u32)p;
}

void bench_main()
{
    /* Wait initial delay */
    sim_puts("Waiting initial delay of ");
    sim_put_num(INIT_DELAY);
    sim_puts(" cycles.\n");

    u32 delay_c = sim_time();
    while (sim_time() - delay_c < INIT_DELAY)
        ;
    sim_puts("   [done]\n");

    set_prios(MAIN_PRIO, MAIN_PRIO, MAIN_PRIO);

    /* Initialize Benchmarks */
#if BENCH == BENCH_LATENCY
    // Prepare buffer for the latency benchmark
    memset((void *)(BUFFER_START + MAIN_CORE * BUFFER_SIZE), CACHE_LINE_SIZE, BUFFER_SIZE - 1);
#endif

    sim_puts("BufferSize=");
    sim_put_num(BUFFER_SIZE);
    sim_puts("\n");

    sim_puts("Runs=");
    sim_put_num(N_RUNS);
    sim_puts("\n");

    /* Run the Benchmarks */
    for (int run_id = 0; run_id < N_RUNS; run_id++)
    {
        // Declare a checksum variable to enforce dummy work to be kept by the compiler
        u32 sum = 0;

        u32 start_t = sim_time();
#if BENCH == BENCH_BANDWIDTH
        cache_miss_access(BUFFER_START + MAIN_CORE * BUFFER_SIZE, BUFFER_START + (MAIN_CORE + 1) * BUFFER_SIZE, &sum);
#elif BENCH == BENCH_LATENCY
        latency_bench(BUFFER_START + MAIN_CORE * BUFFER_SIZE, BUFFER_START + (MAIN_CORE + 1) * BUFFER_SIZE, &sum);
#elif BENCH == BENCH_C2C
        for (int ping_id = 0; ping_id < N_PINGS; ping_id++)
        {
            while (PING != atomic_cmpxchg(&c2c_state, &PING, PONG))
                ;
        }
#else
#error "No benchmark to run"
#endif
        u32 end_t = sim_time();

        sim_puts("RunResult{ \"run_id\"=");
        sim_put_num(run_id);
        sim_puts(", \"time\"=");
        sim_put_num(end_t - start_t);
        sim_puts(", \"checksum\"=\"0x");
        sim_puthex(sum);
        sim_puts("\"");
#if BENCH == BENCH_C2C
        sim_puts(", \"pings\"=");
        sim_put_num(N_PINGS);
#endif
        sim_puts(" }\n");
    }
}

void bench_second()
{
#if BENCH == BENCH_C2C
    while (TRUE)
    {
        while (PONG != atomic_cmpxchg(&c2c_state, &PONG, PING))
            ;
    }
#endif
}
