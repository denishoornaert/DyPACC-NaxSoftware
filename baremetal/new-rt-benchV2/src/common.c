#include <riscv.h>
#include "common.h"

void cache_miss_access(const u32 start, const u32 end, u32 *sum)
{
    for (u8 *p = (u8 *)start; p < (u8 *)end; p += CACHE_LINE_SIZE)
        (*sum) += (*p); // should perform memory access
}

u64 get_time()
{
    u32 counter_lo;
    u32 counter_hi;
    u32 hi_old;

    __asm__ volatile(
        "1: rdcycleh %0\n"
        "rdcycle %1\n"
        "rdcycleh %2\n"
        "bne %0, %2, 1b"
        : "=r"(hi_old), "=r"(counter_lo), "=r"(counter_hi));

    return ((u64)counter_hi << 32) + (u64)counter_lo;
}

void put_c(char c)
{
#if LITEX == FALSE
    sim_putchar(c);
#else
    if (c == '\n')
        put_c('\r');

    while (*((volatile unsigned int *)CON_TXFULL) != 0)
        ;

    *((volatile unsigned int *)CON_PUTC) = c;
#endif
}

void put_str(char *c)
{
    while (*c)
        put_c(*c++);
}

void put_num(u64 value)
{
    u64 i = 1000000000000000000;
    while (value / i == 0 && i > 1)
        i /= 10;

    while (i > 0)
    {
        put_c('0' + (value / i) % 10);
        i /= 10;
    }
}

void set_prios(u8 instr_prio, u8 data_prio, u8 io_prio)
{
#if PRIO_SUPPORT == TRUE
    u32 old_data_prio = csr_swap(0xBC0, data_prio);
    u32 old_fetch_prio = csr_swap(0xBC4, instr_prio);
    u32 old_peri_prio = csr_swap(0xBC8, io_prio);
#endif
}

void set_target_prio(u32 hart_id)
{
    // C0 to C7 have decreasing priorities
    u32 target_prio = 7 - hart_id;
    u32 new_prio = target_prio == MAIN_PRIO ? (7 - MAIN_CORE) : target_prio;
    set_prios(new_prio, new_prio, new_prio);
}

static _Atomic(u8) init_vec[8] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

void signal_hart_ready()
{
    u32 hart_id = csr_read(mhartid);
    __atomic_store_n(&init_vec[hart_id], 1, __ATOMIC_SEQ_CST);
}

void wait_for_all_harts()
{
    for (int i = 0; i < 8; i++)
    {
        put_str("    Waiting for Core ");
        put_num(i);
        put_str("...\n");
        while (TRUE)
        {
            u32 val = __atomic_load_n(&init_vec[i], __ATOMIC_SEQ_CST);
            if (val == 1)
                break;

            put_str("        is [");
            for (int i = 0; i < 8; i++)
            {
                put_num(__atomic_load_n(&init_vec[i], __ATOMIC_SEQ_CST));
                put_str(", ");
            }
            put_str("]\n");
        }
        put_str("         [ok]\n");
    }
}

void print_config()
{
    put_str("RTBench{\n");

    put_str("  worker_num=");
    put_num(WORKER_NUM);
    put_str(",\n");

    put_str("  main_core=");
    put_num(MAIN_CORE);
    put_str(",\n");

    put_str("  prio_support=");
    put_num(PRIO_SUPPORT);
    put_str(",\n");

#if PRIO_SUPPORT == TRUE
    put_str("  main_prio=");
    put_num(MAIN_PRIO);
    put_str(",\n");

#endif

    put_str("  init_delay=");
    put_num(INIT_DELAY);
    put_str(",\n");

    put_str("  n_runs=");
    put_num(N_RUNS);
    put_str(",\n");

    put_str("}\n");
}