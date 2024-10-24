#include "bench.h"
#ifdef BENCH_LATENCY
#include <string.h>
#endif

#if BENCH == BENCH_C2C_BUFFER

#define BUFFER_OWNER_MAIN_VAL 32
#define BUFFER_OWNER_SECOND_VAL 16

// _Atomic(u32) *const c2c_state = (_Atomic(u32) *const)(BUFFER_START + MAIN_CORE * BUFFER_SIZE + D_CACHE_SIZE * 2);
_Atomic(u32) *c2c_state = (_Atomic(u32) *)(BUFFER_START + 4 * BUFFER_SIZE + MAIN_CORE * 4);
u32 *second_sum = (u32 *)(BUFFER_START + MAIN_CORE * BUFFER_SIZE + D_CACHE_SIZE * 3);

#define SHARED_BUFFER_SIZE (D_CACHE_SIZE / 8)
#define SHARED_BUFFER_START (BUFFER_START + MAIN_CORE * BUFFER_SIZE)
#define SHARED_BUFFER_END (BUFFER_START + MAIN_CORE * BUFFER_SIZE + SHARED_BUFFER_SIZE)

#define FLUSH_BUFFER_START (BUFFER_START + SECOND_CORE * BUFFER_SIZE)
#define FLUSH_BUFFER_END (BUFFER_START + (SECOND_CORE + 1) * BUFFER_SIZE)

__attribute__((unused)) static void flush_dcache(void)
{
#ifdef NO_FLUSH_INSTR
    cache_miss_access(FLUSH_BUFFER_START, FLUSH_BUFFER_END, &sum);
#else
    asm volatile(".word(0x500F)\n");
#endif
}

#endif

#if BENCH == BENCH_C2C_CAS

#define PING_VAL 32
#define PONG_VAL 16

_Atomic(u32) *const c2c_state = (_Atomic(u32) *const)(BUFFER_START + MAIN_CORE * BUFFER_SIZE + BUFFER_SIZE / 2);
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
    put_str("Waiting initial delay of ");
    put_num(INIT_DELAY);
    put_str(" cycles.\n");

    u32 delay_c = get_time();
    while (get_time() - delay_c < INIT_DELAY)
        ;
    put_str("   [done]\n");

    set_prios(MAIN_PRIO, MAIN_PRIO, MAIN_PRIO);

    /* Initialize Benchmarks */
#if BENCH == BENCH_LATENCY
    // Prepare buffer for the latency benchmark
    memset((void *)(BUFFER_START + MAIN_CORE * BUFFER_SIZE), CACHE_LINE_SIZE, BUFFER_SIZE - 1);
#elif BENCH == BENCH_C2C_BUFFER
    memset((void *)SHARED_BUFFER_START, CACHE_LINE_SIZE, SHARED_BUFFER_SIZE);
#elif BENCH == BENCH_C2C_CAS
    _Atomic(u32) PING_PONG[2] = {PING_VAL, PONG_VAL};
    // _Atomic(u32) PONG = PONG_VAL;

    put_str("Warmup...\n");
    // Warmup
    for (int ping_id = 0; ping_id < 20; ping_id++)
    {
        while (PING_PONG[0] != atomic_cmpxchg(c2c_state, &PING_PONG[0], PING_PONG[1]))
            ;
    }
    put_str("   [done]\n");
#endif

    put_str("BufferSize=");
    put_num(BUFFER_SIZE);
    put_str("\n");

    put_str("Runs=");
    put_num(N_RUNS);
    put_str("\n");

    /* Run the Benchmarks */
    for (int run_id = 0; run_id < N_RUNS; run_id++)
    {
        // Declare a checksum variable to enforce dummy work to be kept by the compiler
        u32 sum = 0;
#if BENCH == BENCH_C2C_BUFFER
        __atomic_store_n(c2c_state, BUFFER_OWNER_MAIN_VAL, __ATOMIC_SEQ_CST);

        // Flush Cache
        flush_dcache();

        // Wait for other thread to signal it has read the block
        while (BUFFER_OWNER_SECOND_VAL != __atomic_load_n(c2c_state, __ATOMIC_SEQ_CST))
            ;
#endif

        u32 start_t = get_time();
#if BENCH == BENCH_BANDWIDTH
        cache_miss_access(BUFFER_START + MAIN_CORE * BUFFER_SIZE, BUFFER_START + (MAIN_CORE + 1) * BUFFER_SIZE, &sum);
#elif BENCH == BENCH_LATENCY
        latency_bench(BUFFER_START + MAIN_CORE * BUFFER_SIZE, BUFFER_START + (MAIN_CORE + 1) * BUFFER_SIZE, &sum);
#elif BENCH == BENCH_C2C_BUFFER
        latency_bench(SHARED_BUFFER_START, SHARED_BUFFER_END, &sum);
#elif BENCH == BENCH_C2C_CAS
        for (int ping_id = 0; ping_id < N_PINGS; ping_id++)
        {
            // while (PING_PONG[0] != atomic_cmpxchg(c2c_state, &PING_PONG[0], PING_PONG[1]))
            //     ;
            (PING_PONG[0] != atomic_cmpxchg(c2c_state, &PING_PONG[0], PING_PONG[1]));
        }
#else
#error "No benchmark to run"
#endif
        u32 end_t = get_time();

        put_str("RunResult{ \"run_id\":");
        put_num(run_id);
        put_str(", \"time\":");
        put_num(end_t - start_t);
        put_str(", \"checksum\":\"");
#if BENCH == BENCH_C2C_BUFFER
        put_num(sum + *second_sum);
        put_str("\"");
        put_str(", \"pings\":");
        put_num(SHARED_BUFFER_SIZE / CACHE_LINE_SIZE);
#elif BENCH == BENCH_C2C_CAS
        put_num(sum);
        put_str("\"");
        put_str(", \"pings\":");
        put_num(N_PINGS);
#else
        put_num(sum);
        put_str("\"");
#endif
        put_str(" }\n");
    }
}

void bench_second()
{
    set_prios(SECOND_PRIO, SECOND_PRIO, SECOND_PRIO);

#if BENCH == BENCH_C2C_BUFFER
    __atomic_store_n(c2c_state, 0, __ATOMIC_SEQ_CST);

    while (TRUE)
    {
        u32 sum = 0;
        cache_miss_access(SHARED_BUFFER_START, SHARED_BUFFER_END, &sum);
        __atomic_store_n(c2c_state, BUFFER_OWNER_SECOND_VAL, __ATOMIC_SEQ_CST);

        while (BUFFER_OWNER_MAIN_VAL != __atomic_load_n(c2c_state, __ATOMIC_SEQ_CST))
            ;
        *second_sum = sum;
    }
#elif BENCH == BENCH_C2C_CAS
    __atomic_store_n(c2c_state, PING_VAL, __ATOMIC_SEQ_CST);
    _Atomic(u32) PING = PING_VAL;
    _Atomic(u32) PONG = PONG_VAL;

    while (TRUE)
    {
        while (PONG != atomic_cmpxchg(c2c_state, &PONG, PING))
            ;
    }
#endif
}
