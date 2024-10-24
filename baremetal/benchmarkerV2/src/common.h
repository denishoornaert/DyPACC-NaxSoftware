#ifndef COMMON_H
#define COMMON_H

#include "default_config.h"
#include <type.h>

#if LITEX == FALSE
#include <sim.h>

#define NUM_CORES 8
#define BUFFER_START (0x80000000 + (512 << 10))
#define D_CACHE_SIZE (16 << 10)
#define BUFFER_SIZE (D_CACHE_SIZE * 4)
#define CACHE_LINE_SIZE 64

#else

#define CON_PUTC 0xf0001000
#define CON_TXFULL 0xf0001004
#define CLINT_TIME 0xf001bff8

#define NUM_CORES 8
#define BUFFER_START (0x40040000)

#if BENCH_L2 == FALSE
#define D_CACHE_SIZE (16 << 10)
#else
#define D_CACHE_SIZE (1024 * 1024)
#endif

#define BUFFER_SIZE (D_CACHE_SIZE * 4)
#define CACHE_LINE_SIZE 64

#endif

/* Access data between start and end, (hopefully) causing cache misses */
void cache_miss_access(const u32 start, const u32 end, u32 *sum);

/* Inefficient function to print a number in base 10 */
void put_num(u32 value);

/* Print a String */
void put_str(char *c);

/* Measure the current time */
long get_time();

/* Sets the bus priorities to the specified values if supported */
void set_prios(u8 instr_prio, u8 data_prio, u8 io_prio);

/* Signals to the main core that this hart has finished it's setup */
void signal_hart_ready();

/* Waits for all harts to finish with their setup */
void wait_for_all_harts();

/* Print the benchmark configuration */
void print_config();

/* Sets the target prio of a coworker */
void set_target_prio();

#if BENCH == BENCH_C2C_CAS

// #define atomic_cmpxchg(obj, exp, val)                     \
//     __extension__({                                       \
//         __typeof__(obj) __obj = (obj);                    \
//         __typeof__(obj) __exp = (exp);                    \
//         __typeof__(*(obj)) __val = (val);                 \
//         __typeof__(*(obj)) __result;                      \
//         register unsigned int __ret;                      \
//         __asm__ volatile(                                 \
//             "0:  lr.w %0, %2\n"                           \
//             "    bne  %0, %z3, 1f\n"                      \
//             "    sc.w %1, %z4, %2\n"                      \
//             "    bnez %1, 0b  \n"                         \
//             "1:\n"                                        \
//             : "=&r"(__result), "=&r"(__ret), "+A"(*__obj) \
//             : "r"(*__exp), "r"(__val)                     \
//             : "memory");                                  \
//         __result;                                         \
//     })

// #define atomic_cmpxchg(obj, exp, val)                     \
//     __extension__({                                       \
//         __typeof__(obj) __obj = (obj);                    \
//         __typeof__(obj) __exp = (exp);                    \
//         __typeof__(*(obj)) __val = (val);                 \
//         __typeof__(*(obj)) __result;                      \
//         register unsigned int __ret;                      \
//         __asm__ volatile(                                 \
//             "0:  lr.w %0, %2\n"                           \
//             "    bne  %0, %z3, 1f\n"                      \
//             "    sc.w %1, %z4, %2\n"                      \
//             "    bnez %1, 0b  \n"                         \
//             "1:\n"                                        \
//             : "=&r"(__result), "=&r"(__ret), "+A"(*__obj) \
//             : "r"(*__exp), "r"(__val)                     \
//             : "memory");                                  \
//         __result;                                         \
//     })

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
            "    nop  \n"                                 \
            "1:\n"                                        \
            : "=&r"(__result), "=&r"(__ret), "+A"(*__obj) \
            : "r"(*__exp), "r"(__val)                     \
            : "memory");                                  \
        __result;                                         \
    })

#endif

#endif