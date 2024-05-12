#include <riscv.h>
#include "common.h"

void cache_miss_access(const u32 start, const u32 end, u32 *sum)
{
    for (u8 *p = (u8 *)start; p < (u8 *)end; p += CACHE_LINE_SIZE)
        (*sum) += (*p); // should perform memory access
}

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

void set_prios(u8 instr_prio, u8 data_prio, u8 io_prio)
{
#if PRIO_SUPPORT == TRUE
    u32 old_data_prio = csr_swap(0xBC0, data_prio);
    u32 old_fetch_prio = csr_swap(0xBC4, instr_prio);
    u32 old_peri_prio = csr_swap(0xBC8, io_prio);
#endif
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
        sim_puts("    Waiting for Core ");
        sim_put_num(i);
        sim_puts("...\n");
        while (TRUE)
        {
            u32 val = __atomic_load_n(&init_vec[i], __ATOMIC_SEQ_CST);
            if (val == 1)
                break;

            sim_puts("        is [");
            for (int i = 0; i < 8; i++)
            {
                sim_put_num(__atomic_load_n(&init_vec[i], __ATOMIC_SEQ_CST));
                sim_puts(", ");
            }
            sim_puts("]\n");
        }
        sim_puts("         [ok]\n");
    }
}