#include <sim.h>
#include <type.h>
#include <riscv.h>

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