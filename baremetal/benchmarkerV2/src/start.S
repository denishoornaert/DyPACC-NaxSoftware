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
    la		t0, waiting_idx
1:	lw		t1, 0(t0)
	beqz	t1, 1b
    j startMain

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
    la		t0, waiting_idx
	li		t1, 1
	sw		t1, 0(t0)

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

.pushsection .data
.balign 4
waiting_idx:
	.word	0x0
.popsection

/* Interrupt Handler */
.align 4 
trap_handler:
    j startMain

	.globl _init
_init:
    ret

