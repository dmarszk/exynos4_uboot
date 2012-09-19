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
 
#include <common.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clk.h>

unsigned long (*get_uart_clk)(int dev_index);
unsigned long (*get_pwm_clk)(void);
unsigned long (*get_arm_clk)(void);
unsigned long (*get_pll_clk)(int);

void s5p_clock_init(void)
{
}

/* ------------------------------------------------------------------------- */
/* NOTE: This describes the proper use of this file.
 *
 * CONFIG_SYS_CLK_FREQ should be defined as the input frequency of the PLL.
 *
 * get_FCLK(), get_HCLK(), get_PCLK() and get_UCLK() return the clock of
 * the specified bus in HZ.
 */
/* ------------------------------------------------------------------------- */

static ulong get_PLLCLK(int pllreg)
{
	ulong r, m, p, s, k = 0, fout;
	unsigned int freq, pll_div2_sel, fout_sel;

	if (pllreg == APLL) {
		r = APLL_CON0_REG;
		m = (r>>16) & 0x3ff;
	} else if (pllreg == MPLL) {
		r = MPLL_CON0_REG;
		m = (r>>16) & 0x3ff;
	} else if (pllreg == BPLL) {
		r = BPLL_CON0_REG;
		m = (r>>16) & 0x3ff;
	} else if (pllreg == EPLL) {
		r = EPLL_CON0_REG;
		m = (r>>16) & 0x1ff;
		k = EPLL_CON1_REG;
		k = k & 0xffff;
	} else if (pllreg == VPLL) {
		r = VPLL_CON0_REG;
		m = (r>>16) & 0x1ff;
		k = VPLL_CON1_REG;
		k = k & 0xfff;
	} else
		hang();

	p = (r>>8) & 0x3f;
	s = r & 0x7;

	freq = CONFIG_SYS_CLK_FREQ;
	if (pllreg == EPLL) {
		/* FOUT = (MDIV + K / 65536) * FIN / (PDIV * 2^SDIV) */
		fout = (m + k / 65536) * (freq / (p * (1 << s)));
	} else if (pllreg == VPLL) {
		/* FOUT = (MDIV + K / 1024) * FIN / (PDIV * 2^SDIV) */
		fout = (m + k / 1024) * (freq / (p * (1 << s)));
	} else {
		if (s < 1)
			s = 1;

		/* FOUT = MDIV * FIN / (PDIV * 2^(SDIV - 1)) */
		fout = m * (freq / (p * (1 << (s - 1))));
	}

	/* According to the user manual, in EVT1 MPLL and BPLL always gives
	 * 1.6GHz clock, so divide by 2 to get 800MHz MPLL clock.*/
	if (pllreg == MPLL || pllreg == BPLL) {
		pll_div2_sel = __raw_readl(ELFIN_CLOCK_BASE + PLL_DIV2_SEL_OFFSET);

		switch (pllreg) {
		case MPLL:
			fout_sel = (pll_div2_sel >> 4) & 0x1;
			break;
		case BPLL:
			fout_sel = (pll_div2_sel >> 0) & 0x1;
			break;
		default:
			fout_sel = -1;
			break;
		}

		if (fout_sel == 0)
			fout /= 2;
	}

	return fout;
}

ulong get_APLL_CLK(void)
{
	return (get_PLLCLK(APLL));
}

ulong get_MPLL_CLK(void)
{
	return (get_PLLCLK(MPLL));
}

ulong get_EPLL_CLK(void)
{
	return (get_PLLCLK(EPLL));
}

ulong get_VPLL_CLK(void)
{
	return (get_PLLCLK(VPLL));
}

ulong get_BPLL_CLK(void)
{
	return (get_PLLCLK(BPLL));
}

