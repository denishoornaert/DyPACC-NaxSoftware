#include <riscv.h>

#define CON_PUTC 0xf0001000
#define CON_TXFULL 0xf0001004

void my_putc(int c)
{
    while (*((volatile unsigned int *)CON_TXFULL) != 0)
        ;

    *((volatile unsigned int *)CON_PUTC) = (c == '\n' ? '\r' : c);
}

void my_puts(const char *s)
{
    while (*s != '\0')
        my_putc(*s++);
}

void main()
{
    my_puts("Hello Litex World!\n");
}
