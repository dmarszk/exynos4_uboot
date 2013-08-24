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
#include <asm/arch/gpio.h>

#if defined(CONFIG_HKDK4212)
	#include <asm/arch/pmic_hkdk4212.h>
#endif

unsigned int OmPin;

DECLARE_GLOBAL_DATA_PTR;
extern int nr_dram_banks;
#ifdef CONFIG_EVT1
unsigned int dmc_density = 0xffffffff;
#endif
unsigned int second_boot_info = 0xffffffff;

#define SROM_DATA16_WIDTH(x)	(1<<((x*4)+0))
#define SROM_WAIT_ENABLE(x)	(1<<((x*4)+1))
#define SROM_BYTE_ENABLE(x)	(1<<((x*4)+2))

#define	PS_HOLD		*(volatile unsigned long *)(0x1002330C)
u32 board_rev;

void configure_tz(struct tz_info* tzi)
{
	tzi->field_0 = 0x10000;
	tzi->info_size = sizeof(struct tz_info);
	tzi->field_8 = 0x2027FE0;
	tzi->val_0x20 = 0x20;
	tzi->bl1_ver[0] = *((u32*)(0x02022fc8));
	tzi->bl1_ver[1] = *((u32*)(0x02022fcc));
	tzi->cpu_id = 0x4412;
	tzi->val_0x10C0C = 0x10C0C;
	tzi->val_0 = 0;
	tzi->conditional_cpu_id = 0x4412;
	tzi->conditional_tag_ISLS = 0x49534C53; //"ISLS"
	tzi->sdram_start = CONFIG_SYS_SDRAM_BASE;
	tzi->sdram_size = (CONFIG_NR_DRAM_BANKS * SDRAM_BANK_SIZE);
	tzi->tzram_start = 0x7FF00000;
	tzi->tzram_size = 0x100000;
	tzi->tag_ISLS = 0x49534C53;
}

u32 get_board_rev(void)
{
	return board_rev;
}

int board_init(void)
{
	char bl1_version[9] = {0};
	
	GPIO_Init();
	
	GPIO_SetFunctionEach(eGPIO_X0, eGPIO_1, 0);
	GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_1, 0);
	GPIO_SetFunctionEach(eGPIO_X0, eGPIO_4, 0);
	GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_4, 0);
	GPIO_SetFunctionEach(eGPIO_X0, eGPIO_5, 0);
	GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_5, 0);
	
	
	GPIO_SetFunctionEach(eGPIO_X1, eGPIO_3, 0);
	GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_3, 0);
	GPIO_SetFunctionEach(eGPIO_X1, eGPIO_4, 0);
	GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_4, 0);
	GPIO_SetFunctionEach(eGPIO_X2, eGPIO_0, 0);
	GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_0, 0);	
	GPIO_SetFunctionEach(eGPIO_X2, eGPIO_1, 0);
	GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_1, 0);	
	GPIO_SetFunctionEach(eGPIO_X2, eGPIO_2, 0);
	GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_2, 0);	
	GPIO_SetFunctionEach(eGPIO_X2, eGPIO_7, 0);
	GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_7, 0);
	GPIO_SetFunctionEach(eGPIO_X3, eGPIO_3, 0);
	GPIO_SetPullUpDownEach(eGPIO_X3, eGPIO_3, 0);
	
	GPIO_SetFunctionEach(eGPIO_M1, eGPIO_2, 0);
	GPIO_SetPullUpDownEach(eGPIO_M1, eGPIO_2, 0);
	GPIO_SetFunctionEach(eGPIO_M1, eGPIO_3, 0);
	GPIO_SetPullUpDownEach(eGPIO_M1, eGPIO_3, 0);
	GPIO_SetFunctionEach(eGPIO_M1, eGPIO_4, 0);
	GPIO_SetPullUpDownEach(eGPIO_M1, eGPIO_4, 0);
	GPIO_SetFunctionEach(eGPIO_M1, eGPIO_5, 0);
	GPIO_SetPullUpDownEach(eGPIO_M1, eGPIO_5, 0);
	
	board_rev = 
	(GPIO_GetDataEach(eGPIO_M1, eGPIO_5) << 3) |
	(GPIO_GetDataEach(eGPIO_M1, eGPIO_4) << 2) |
	(GPIO_GetDataEach(eGPIO_M1, eGPIO_3) << 1) | 
	(GPIO_GetDataEach(eGPIO_M1, eGPIO_2) << 0);
	
	printf("Board revision: 0x%X\n", board_rev);
	
	pmic_init();
	
	/* display BL1 version */
#ifdef CONFIG_TRUSTZONE
	printf("BL1 version: N/A (TrustZone Enabled BSP)\n");
#else
	strncpy(&bl1_version[0], (char *)0x02022fc8, 8);
	printf("BL1 version: %s\n", &bl1_version[0]);
#endif

#ifdef CONFIG_SMDKC220
	gd->bd->bi_arch_number = MACH_TYPE_C220;
#else
	if(((PRO_ID & 0x300) >> 8) == 2)
		gd->bd->bi_arch_number = MACH_TYPE_C210;
	else
		gd->bd->bi_arch_number = MACH_TYPE_V310;
#endif

	gd->bd->bi_boot_params = (PHYS_SDRAM_1+0x100);

#ifdef CONFIG_EXYNOS4_GALAXY
	printf("\nOverwriting Boot Mode to BOOT_MMCSD... ");
	INF_REG3_REG = BOOT_MMCSD;
#endif

   	OmPin = INF_REG3_REG;
	printf("\nChecking Boot Mode... ");
	if(OmPin == BOOT_ONENAND) {
		printf("OneNand\n");
	} else if (OmPin == BOOT_NAND) {
		printf("NAND\n");
	} else if (OmPin == BOOT_MMCSD) {
		printf("SDMMC\n");
	} else if (OmPin == BOOT_EMMC) {
		printf("EMMC4.3\n");
	} else if (OmPin == BOOT_EMMC_4_4) {
		printf("EMMC4.41\n");
	} else {
		printf("Unknown! (Not implemented?)\n");
	}
    // denis added
    writel(0x6666, S5PV310_CLOCK_BASE + 0xC234); // CLK_SRC_LCD0

	return 0;
}

int dram_init(void)
{
	//gd->ram_size = get_ram_size((long *)PHYS_SDRAM_1, PHYS_SDRAM_1_SIZE);
	
	return 0;
}

void dram_init_banksize(void)
{
#ifdef CONFIG_SMDKC220
		nr_dram_banks = CONFIG_NR_DRAM_BANKS;
		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
		gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
		gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
		gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
		gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
#else
	if(((PRO_ID & 0x300) >> 8) == 2){
#ifdef CONFIG_EVT1
		printf("EVT1 ");
		if(dmc_density == 6){
			printf("POP_B\n");
			nr_dram_banks = 4;
			gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
			gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
			gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
			gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
			gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
			gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
			gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
			gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
		}
		else if(dmc_density == 5){
			printf("POP_A\n");
			nr_dram_banks = 2;
			gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
			gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
			gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
			gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
		}
		else{
			printf("unknown POP type\n");
			nr_dram_banks = 2;
			gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
			gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
			gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
			gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
		}
#else
		nr_dram_banks = 2;
		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
#endif
	}
	else{
		nr_dram_banks = 8;
		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
		gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
		gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
		gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
		gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
		gd->bd->bi_dram[4].start = PHYS_SDRAM_5;
		gd->bd->bi_dram[4].size = PHYS_SDRAM_5_SIZE;
		gd->bd->bi_dram[5].start = PHYS_SDRAM_6;
		gd->bd->bi_dram[5].size = PHYS_SDRAM_6_SIZE;
		gd->bd->bi_dram[6].start = PHYS_SDRAM_7;
		gd->bd->bi_dram[6].size = PHYS_SDRAM_7_SIZE;
		gd->bd->bi_dram[7].start = PHYS_SDRAM_8;
		gd->bd->bi_dram[7].size = PHYS_SDRAM_8_SIZE;
	}
#endif

#ifdef CONFIG_TRUSTZONE
	gd->bd->bi_dram[nr_dram_banks - 1].size -= CONFIG_TRUSTZONE_RESERVED_DRAM;
#endif
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;

	return rc;
}

#ifdef CONFIG_DISPLAY_BOARDINFO
int checkboard(void)
{
	printf("Board:\tSMDKV310\n");
	
	return 0;

}
#endif

int board_late_init (void)
{
	/*
	GPIO_Init();
	GPIO_SetFunctionEach(eGPIO_X0, eGPIO_0, 0);
	GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_0, 0);

	udelay(10);
	if (GPIO_GetDataEach(eGPIO_X0, eGPIO_0) == 0 || second_boot_info == 1){
		setenv ("bootcmd", CONFIG_BOOTCOMMAND2);
	}
	*/

#ifdef CONFIG_HKDK4412
	GPIO_SetFunctionEach(eGPIO_X2, eGPIO_2, eGPI);
	GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_2, 1); 	// pull-down

	udelay(10);
	if (GPIO_GetDataEach(eGPIO_X2, eGPIO_2) == 0){
		printf("ModeKey Check... run normal_boot \n");
	}
	else {
		char run_cmd[80];
		
		printf("ModeKey Check... run fastboot \n");

		sprintf(run_cmd, "fastboot");
		run_command(run_cmd, 0);
	}
#endif

	return 0;
}

int board_mmc_init(bd_t *bis)
{
	int i;
	printf("...Time to turn eMMC back on...\n");
	for(i = 10; i > 0; i--)
	{
		printf("%d ", i);
		udelay(1000000);
	}
	printf("\n");
#ifdef CONFIG_S3C_HSMMC
	setup_hsmmc_clock();
	setup_hsmmc_cfg_gpio();
	if (OmPin == BOOT_EMMC_4_4 || OmPin == BOOT_EMMC) {
#ifdef CONFIG_S5PC210
		smdk_s5p_mshc_init();
#endif
		smdk_s3c_hsmmc_init();
	} else {
		smdk_s3c_hsmmc_init();
#ifdef CONFIG_S5PC210
		smdk_s5p_mshc_init();
#endif
	}
#endif
	return 0;
}

#ifdef CONFIG_ENABLE_MMU
ulong virt_to_phy_s5pv310(ulong addr)
{
	if ((0xc0000000 <= addr) && (addr < 0xe0000000))
		return (addr - 0xc0000000 + 0x40000000);

	return addr;
}
#endif

