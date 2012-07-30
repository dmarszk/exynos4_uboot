/*
 * (C) Copyright 2011 Samsung Electronics Co. Ltd
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <config.h>
#include <asm/arch/cpu.h>

#define CONFIG_LOW_POWER_CTRL	1
#define CONFIG_DMC_BRB

	.globl mem_ctrl_asm_init
mem_ctrl_asm_init:
	push	{lr}

	ldr	r0, =CHIP_ID_BASE
	ldr	r1, [r0, #0x0]
	and	r1, #0xf00
	mov	r2, #0x200
	mov	r0, #800	@nMEMCLK
	cmp	r1, r2
	beq	mem_ctrl_init_lpddr3
#if defined(CONFIG_LPDDR3)
	b	mem_ctrl_init_lpddr3
#else
	b	mem_ctrl_init_ddr3
#endif

	.globl	mem_ctrl_init_done
mem_ctrl_init_done:

#if defined(CONFIG_DMC_BRB)
	/* DMC BRB QoS */
	ldr r0, =DMC_CTRL_BASE
	ldr r1, =0x66668666
	str r1, [r0, #DMC_BRBRSVCONFIG]
	ldr r1, =0xFF
	str r1, [r0, #DMC_BRBRSVCONTROL]
	ldr r1, =0x1
	str r1, [r0, #DMC_BRBQOSCONFIG]
#endif
	pop	{lr}
	mov	pc, lr

	.globl dmc_delay
dmc_delay:
	subs    r0, r0, #1
	bne     dmc_delay
	mov     pc, lr

