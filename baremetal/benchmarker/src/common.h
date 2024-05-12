#ifndef COMMON_H
#define COMMON_H

#include <sim.h>
#include <type.h>
#include "default_config.h"

#define NUM_CORES 8
#define BUFFER_START (0x80000000 + (512 << 10))
#define D_CACHE_SIZE (16 << 10)
#define BUFFER_SIZE (D_CACHE_SIZE * 4)
#define CACHE_LINE_SIZE 64

/* Access data between start and end, (hopefully) causing cache misses */
void cache_miss_access(const u32 start, const u32 end, u32 *sum);

/* Inefficient function to print a number in base 10 */
void sim_put_num(u32 value);

/* Sets the bus priorities to the specified values if supported */
void set_prios(u8 instr_prio, u8 data_prio, u8 io_prio);

/* Signals to the main core that this hart has finished it's setup */
void signal_hart_ready();

/* Waits for all harts to finish with their setup */
void wait_for_all_harts();

#endif