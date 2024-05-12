.section .init
.globl _start
.type _start,@function


.globl pass
.type pass,@function

.globl fail
.type fail,@function


#include "../driver/riscv_asm.h"

_start:
#ifdef USE_GP
.option push
.option norelax
	la gp, __global_pointer$
.option pop
#endif


init:
	/* Calculate Stackpointer per hart 
	   Each Hart has a 4K stack (max 8 harts) */
	la sp, _sp
	csrr t0, mhartid
	slli t0, t0, 12
	add sp, sp, t0

    /* All but hart 0 wait for initialization */
    beq t0, zero, 2f

    // Setup trap handler
    la      t0, trap_handler
    csrw    mtvec, t0

    // Enable Machine Software Interrupt
    li      t0, 8
    csrw    mie, t0
1:
    // Wait until hart 0 finishes setup
    csrr    t0, mip // check if msi bit is set
    andi    t0, t0, 8
    bne     t0, zero, startMain
    j 1b
2:
	/* Load data section */
	la a0, _data_lma
	la a1, _data
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:

	/* Clear bss section */
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:

#ifndef NO_LIBC_INIT_ARRAY
	call __libc_init_array
#endif

    // Wake the other harts
    li      t0, 1
    li      t1, 0x10010000 // address of clint
    sw      t0, 4(t1)   // hart 1 
    sw      t0, 8(t1)   // hart 2 
    sw      t0, 12(t1)  // hart 3 
    sw      t0, 16(t1)  // hart 4 
    sw      t0, 20(t1)  // hart 5 
    sw      t0, 24(t1)  // hart 6 
    sw      t0, 28(t1)  // hart 7

startMain:
    li x1, MSTATUS_FS_MASK
    csrc mstatus, x1
    li x1, MSTATUS_FS_INITIAL
    csrs mstatus, x1

	call main
mainDone:
pass:
    j mainDone
    nop
fail:
    j fail
    nop

/* Interrupt Handler */
.align 4 
trap_handler:
    j startMain

	.globl _init
_init:
    ret

