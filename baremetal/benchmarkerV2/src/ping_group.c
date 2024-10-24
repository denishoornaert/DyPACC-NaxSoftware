#include "ping_group.h"

#if BENCH == BENCH_C2C_CAS && USE_PING_GROUP == TRUE

const int ping_group[CORE_COUNT] = {PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7};

void endless_ping(u32 hart_id)
{
    // 1. Determine Address of Atomic
    // _Atomic(u32) *const pg_state = (_Atomic(u32) *const)(BUFFER_START + ping_group[hart_id] * BUFFER_SIZE + BUFFER_SIZE / 2);
    _Atomic(u32) *pg_state = (_Atomic(u32) *)(BUFFER_START + 4 * BUFFER_SIZE + ping_group[hart_id] * 4);

    // 2. Determine Value to insert
    // first determine what value should be replaced, be determining what the hart_id of the next lower core (wrapping) in the ping group is
    _Atomic(u32) ping_val = -1;
    int idx = hart_id;
    while (ping_val == -1)
    {
        idx = (CORE_COUNT + (idx - 1)) % CORE_COUNT;
        if (ping_group[idx] == ping_group[hart_id])
            ping_val = idx;
    }

    _Atomic(u32) pong_val = hart_id;
    __atomic_store_n(pg_state, pong_val, __ATOMIC_SEQ_CST);

    signal_hart_ready();

    set_target_prio(hart_id);

    while (TRUE)
    {
        while (pong_val != atomic_cmpxchg(pg_state, &pong_val, ping_val))
            ;
    }

    while (TRUE)
    {
        asm("wfi");
    }
}

#endif