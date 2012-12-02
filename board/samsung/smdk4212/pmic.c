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
#include <asm/arch/pmic.h>

void I2C_MAX8997_EnableReg(PMIC_RegNum eRegNum, u8 ucEnable);

void Delay(void)
{
	unsigned long i;
	for(i=0;i<DELAY;i++);
}

void IIC0_SCLH_SDAH(void)
{
	IIC0_ESCL_Hi;
	IIC0_ESDA_Hi;
	Delay();
}

void IIC0_SCLH_SDAL(void)
{
	IIC0_ESCL_Hi;
	IIC0_ESDA_Lo;
	Delay();
}

void IIC0_SCLL_SDAH(void)
{
	IIC0_ESCL_Lo;
	IIC0_ESDA_Hi;
	Delay();
}

void IIC0_SCLL_SDAL(void)
{
	IIC0_ESCL_Lo;
	IIC0_ESDA_Lo;
	Delay();
}

void IIC1_SCLH_SDAH(void)
{
	IIC1_ESCL_Hi;
	IIC1_ESDA_Hi;
	Delay();
}

void IIC1_SCLH_SDAL(void)
{
	IIC1_ESCL_Hi;
	IIC1_ESDA_Lo;
	Delay();
}

void IIC1_SCLL_SDAH(void)
{
	IIC1_ESCL_Lo;
	IIC1_ESDA_Hi;
	Delay();
}

void IIC1_SCLL_SDAL(void)
{
	IIC1_ESCL_Lo;
	IIC1_ESDA_Lo;
	Delay();
}

void IIC3_SCLH_SDAH(void)
{
	IIC3_ESCL_Hi;
	IIC3_ESDA_Hi;
	Delay();
}

void IIC3_SCLH_SDAL(void)
{
	IIC3_ESCL_Hi;
	IIC3_ESDA_Lo;
	Delay();
}

void IIC3_SCLL_SDAH(void)
{
	IIC3_ESCL_Lo;
	IIC3_ESDA_Hi;
	Delay();
}

void IIC3_SCLL_SDAL(void)
{
	IIC3_ESCL_Lo;
	IIC3_ESDA_Lo;
	Delay();
}

void IIC0_ELow(void)
{
	IIC0_SCLL_SDAL();
	IIC0_SCLH_SDAL();
	IIC0_SCLH_SDAL();
	IIC0_SCLL_SDAL();
}

void IIC0_EHigh(void)
{
	IIC0_SCLL_SDAH();
	IIC0_SCLH_SDAH();
	IIC0_SCLH_SDAH();
	IIC0_SCLL_SDAH();
}

void IIC1_ELow(void)
{
	IIC1_SCLL_SDAL();
	IIC1_SCLH_SDAL();
	IIC1_SCLH_SDAL();
	IIC1_SCLL_SDAL();
}

void IIC1_EHigh(void)
{
	IIC1_SCLL_SDAH();
	IIC1_SCLH_SDAH();
	IIC1_SCLH_SDAH();
	IIC1_SCLL_SDAH();
}

void IIC3_ELow(void)
{
	IIC3_SCLL_SDAL();
	IIC3_SCLH_SDAL();
	IIC3_SCLH_SDAL();
	IIC3_SCLL_SDAL();
}

void IIC3_EHigh(void)
{
	IIC3_SCLL_SDAH();
	IIC3_SCLH_SDAH();
	IIC3_SCLH_SDAH();
	IIC3_SCLL_SDAH();
}

void IIC0_EStart(void)
{
	IIC0_SCLH_SDAH();
	IIC0_SCLH_SDAL();
	Delay();
	IIC0_SCLL_SDAL();
}

void IIC0_EEnd(void)
{
	IIC0_SCLL_SDAL();
	IIC0_SCLH_SDAL();
	Delay();
	IIC0_SCLH_SDAH();
}

void IIC0_EAck_write(void)
{
	unsigned long ack;

	IIC0_ESDA_INP;			// Function <- Input

	IIC0_ESCL_Lo;
	Delay();
	IIC0_ESCL_Hi;
	Delay();
	ack = GPD1DAT;
	IIC0_ESCL_Hi;
	Delay();
	IIC0_ESCL_Hi;
	Delay();

	IIC0_ESDA_OUTP;			// Function <- Output (SDA)

	ack = (ack>>0)&0x1;
//	while(ack!=0);

	IIC0_SCLL_SDAL();
}

void IIC1_EAck_read(void)
{
	IIC1_ESDA_OUTP;			// Function <- Output

	IIC1_ESCL_Lo;
	IIC1_ESCL_Lo;
	//IIC1_ESDA_Lo;
	IIC1_ESDA_Hi;
	IIC1_ESCL_Hi;
	IIC1_ESCL_Hi;

	IIC1_ESDA_INP;			// Function <- Input (SDA)

	IIC1_SCLL_SDAL();
}

void IIC1_EStart(void)
{
	IIC1_SCLH_SDAH();
	IIC1_SCLH_SDAL();
	Delay();
	IIC1_SCLL_SDAL();
}

void IIC1_EEnd(void)
{
	IIC1_SCLL_SDAL();
	IIC1_SCLH_SDAL();
	Delay();
	IIC1_SCLH_SDAH();
}

void IIC1_EAck_write(void)
{
	unsigned long ack;

	IIC1_ESDA_INP;			// Function <- Input

	IIC1_ESCL_Lo;
	Delay();
	IIC1_ESCL_Hi;
	Delay();
	ack = GPD1DAT;
	IIC1_ESCL_Hi;
	Delay();
	IIC1_ESCL_Hi;
	Delay();

	IIC1_ESDA_OUTP;			// Function <- Output (SDA)

	ack = (ack>>2)&0x1;
//	while(ack!=0);

	IIC1_SCLL_SDAL();
}

void IIC0_EAck_read(void)
{
	IIC0_ESDA_OUTP;			// Function <- Output

	IIC0_ESCL_Lo;
	IIC0_ESCL_Lo;
	//IIC0_ESDA_Lo;
	IIC0_ESDA_Hi;
	IIC0_ESCL_Hi;
	IIC0_ESCL_Hi;

	IIC0_ESDA_INP;			// Function <- Input (SDA)

	IIC0_SCLL_SDAL();
}

void IIC3_EStart(void)
{
	IIC3_SCLH_SDAH();
	IIC3_SCLH_SDAL();
	Delay();
	IIC3_SCLL_SDAL();
}

void IIC3_EEnd(void)
{
	IIC3_SCLL_SDAL();
	IIC3_SCLH_SDAL();
	Delay();
	IIC3_SCLH_SDAH();
}

void IIC3_EAck(void)
{
	unsigned long ack;

	IIC3_ESDA_INP;			// Function <- Input

	IIC3_ESCL_Lo;
	Delay();
	IIC3_ESCL_Hi;
	Delay();
	ack = GPA1DAT;
	IIC3_ESCL_Hi;
	Delay();
	IIC3_ESCL_Hi;
	Delay();

	IIC3_ESDA_OUTP;			// Function <- Output (SDA)

	ack = (ack>>2)&0x1;
//	while(ack!=0);

	IIC3_SCLL_SDAL();
}


void IIC0_ESetport(void)
{
	GPD1PUD &= ~(0xf<<0);	// Pull Up/Down Disable	SCL, SDA

	IIC0_ESCL_Hi;
	IIC0_ESDA_Hi;

	IIC0_ESCL_OUTP;		// Function <- Output (SCL)
	IIC0_ESDA_OUTP;		// Function <- Output (SDA)

	Delay();
}

void IIC1_ESetport(void)
{
	GPD1PUD &= ~(0xf<<4);	// Pull Up/Down Disable	SCL, SDA

	IIC1_ESCL_Hi;
	IIC1_ESDA_Hi;

	IIC1_ESCL_OUTP;		// Function <- Output (SCL)
	IIC1_ESDA_OUTP;		// Function <- Output (SDA)

	Delay();
}

void IIC3_ESetport(void)
{
	GPA1PUD &= ~(0xf<<4);	// Pull Up/Down Disable	SCL, SDA

	IIC3_ESCL_Hi;
	IIC3_ESDA_Hi;

	IIC3_ESCL_OUTP;		// Function <- Output (SCL)
	IIC3_ESDA_OUTP;		// Function <- Output (SDA)

	Delay();
}

void IIC0_EWrite (unsigned char ChipId, unsigned char IicAddr, unsigned char IicData)
{
	unsigned long i;

	IIC0_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_ELow();	// write

	IIC0_EAck_write();	// ACK

////////////////// write reg. addr. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicAddr >> (i-1)) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_EAck_write();	// ACK

////////////////// write reg. data. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicData >> (i-1)) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_EAck_write();	// ACK

	IIC0_EEnd();
}

void IIC0_ERead (unsigned char ChipId, unsigned char IicAddr, unsigned char *IicData)
{
	unsigned long i, reg;
	unsigned char data = 0;

	IIC0_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_ELow();	// write

	IIC0_EAck_write();	// ACK

////////////////// write reg. addr. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicAddr >> (i-1)) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_EAck_write();	// ACK

	IIC0_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC0_EHigh();
		else
			IIC0_ELow();
	}

	IIC0_EHigh();	// read

	IIC0_EAck_write();	// ACK

////////////////// read reg. data. //////////////////
	IIC0_ESDA_INP;

	for(i = 8; i>0; i--)
	{
		IIC0_ESCL_Lo;
		Delay();
		IIC0_ESCL_Hi;
		Delay();
		reg = GPD1DAT;
		IIC0_ESCL_Hi;
		Delay();
		IIC0_ESCL_Hi;
		Delay();

		reg = (reg >> 0) & 0x1;
		data |= reg << (i-1);
	}

	IIC0_EAck_read();	// ACK
	IIC0_ESDA_OUTP;

	IIC0_EEnd();

	*IicData = data;
}


void IIC1_EWrite (unsigned char ChipId, unsigned char IicAddr, unsigned char IicData)
{
	unsigned long i;

	IIC1_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_ELow();	// write 'W'

	IIC1_EAck_write();	// ACK

////////////////// write reg. addr. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicAddr >> (i-1)) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_EAck_write();	// ACK

////////////////// write reg. data. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicData >> (i-1)) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_EAck_write();	// ACK

	IIC1_EEnd();
}

void IIC1_ERead (unsigned char ChipId, unsigned char IicAddr, unsigned char *IicData)
{
	unsigned long i, reg;
	unsigned char data = 0;

	IIC1_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_ELow();	// write

	IIC1_EAck_write();	// ACK

////////////////// write reg. addr. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicAddr >> (i-1)) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_EAck_write();	// ACK

	IIC1_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC1_EHigh();
		else
			IIC1_ELow();
	}

	IIC1_EHigh();	// read

	IIC1_EAck_write();	// ACK

////////////////// read reg. data. //////////////////
	IIC1_ESDA_INP;

	for(i = 8; i>0; i--)
	{
		IIC1_ESCL_Lo;
		Delay();
		IIC1_ESCL_Hi;
		Delay();
		reg = GPD1DAT;
		IIC1_ESCL_Hi;
		Delay();
		IIC1_ESCL_Hi;
		Delay();

		reg = (reg >> 0) & 0x1;
		data |= reg << (i-1);
	}

	IIC1_EAck_read();	// ACK
	IIC1_ESDA_OUTP;

	IIC1_EEnd();

	*IicData = data;
}

void IIC3_EWrite (unsigned char ChipId, unsigned char IicAddr, unsigned char IicData)
{
	unsigned long i;

	IIC3_EStart();

////////////////// write chip id //////////////////
	for(i = 7; i>0; i--)
	{
		if((ChipId >> i) & 0x0001)
			IIC3_EHigh();
		else
			IIC3_ELow();
	}

	IIC3_ELow();	// write 'W'

	IIC3_EAck();	// ACK

////////////////// write reg. addr. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicAddr >> (i-1)) & 0x0001)
			IIC3_EHigh();
		else
			IIC3_ELow();
	}

	IIC3_EAck();	// ACK

////////////////// write reg. data. //////////////////
	for(i = 8; i>0; i--)
	{
		if((IicData >> (i-1)) & 0x0001)
			IIC3_EHigh();
		else
			IIC3_ELow();
	}

	IIC3_EAck();	// ACK

	IIC3_EEnd();
}


void I2C_MAX8997_VolSetting(PMIC_RegNum eRegNum, u8 ucVolLevel, u8 ucEnable)
{
	u8 reg_addr, reg_bitpos, reg_bitmask, vol_level;
	u8 read_data;

	reg_bitpos = 0;
	reg_bitmask = 0x3F;
	if(eRegNum == 0)
	{
		reg_addr = 0x19;
	}
	else if(eRegNum == 1)
	{
		reg_addr = 0x22;
	}
	else if(eRegNum == 2)
	{
		reg_addr = 0x2B;
	}
	else if(eRegNum == 3)
	{
		reg_addr = 0x2D;
	}
	else if(eRegNum == 4)
	{
		reg_addr = 0x48;
	}
	else if(eRegNum == 5)
	{
		reg_addr = 0x44;
	}
	else
		while(1);

	vol_level = ucVolLevel&reg_bitmask;

	IIC0_ERead(MAX8997_ADDR, reg_addr, &read_data);

	read_data = (read_data & (~(reg_bitmask<<reg_bitpos))) | (vol_level<<reg_bitpos);

	IIC0_EWrite(MAX8997_ADDR, reg_addr, read_data);

	I2C_MAX8997_EnableReg(eRegNum, ucEnable);
}

void I2C_MAX8997_EnableReg(PMIC_RegNum eRegNum, u8 ucEnable)
{
	u8 reg_addr, reg_bitpos;
	u8 read_data;

	reg_bitpos = 0;
	if(eRegNum == 0)
	{
		reg_addr = 0x18;
	}
	else if(eRegNum == 1)
	{
		reg_addr = 0x21;
	}
	else if(eRegNum == 2)
	{
		reg_addr = 0x2A;
	}
	else if(eRegNum == 3)
	{
		reg_addr = 0x2C;
	}
	else if(eRegNum == 4)
	{
		reg_addr = 0x48;
		reg_bitpos = 0x6;
	}
	else if(eRegNum == 5)
	{
		reg_addr = 0x44;
		reg_bitpos = 0x6;
	}

	else
		while(1);

	IIC0_ERead(MAX8997_ADDR, reg_addr, &read_data);

	read_data = (read_data & (~(1<<reg_bitpos))) | (ucEnable<<reg_bitpos);

	IIC0_EWrite(MAX8997_ADDR, reg_addr, read_data);
}

void pmic_s5m8767_update_reg(uint8_t reg_id, uint8_t value, uint8_t mask)
{
	uint8_t read_val;
	value &= mask; //just for sanity	
	IIC1_ERead(S5M8767_ADDR, reg_id, &read_val);
	read_val &= ~mask;
	read_val |= value;	
	IIC1_EWrite(S5M8767_ADDR, reg_id, read_val);
}

void I2C_S5M8767_SetupBuck(PMIC_RegNum eRegNum, unsigned char ucVolLevel, unsigned char ucEnable)
{
	unsigned char reg_addr, reg_bitpos, reg_bitmask, vol_level;

	reg_bitpos = 0;
	reg_bitmask = 0xFF;
	
	if(eRegNum == PMIC_BUCK1)  // BUCK1
	{
		reg_addr = 0x33;
	}
	else if(eRegNum == PMIC_BUCK2)  // BUCK2
	{
		reg_addr = 0x35;
	}
	else if(eRegNum == PMIC_BUCK3)  //  BUCK3
	{
		reg_addr = 0x3E;
	}
	else if(eRegNum == PMIC_BUCK4)  // BUCK4
	{
		reg_addr = 0x47;
	}
	else if(eRegNum == PMIC_BUCK5) // BUCK5
	{
		reg_addr = 0x50;
	}
	else
	      while(1);

	vol_level = ucVolLevel & reg_bitmask ;
	IIC1_EWrite(S5M8767_ADDR, reg_addr, vol_level);
}
void pmic_max77686_print(void)
{	
	u8 read_vol_arm;
	u8 read_vol_int;
	u8 read_vol_g3d;
	u8 read_vol_mif;
	u8 read_vol_mem;
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK2TV_DVS1, &read_vol_arm);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK3TV_DVS1, &read_vol_int);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK4TV_DVS1, &read_vol_g3d);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK1OUT, &read_vol_mif);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK5OUT, &read_vol_mem);
	
	printf("ARM: %dmV\t", ((unsigned int)(read_vol_arm >> 1) * 25) + 600);
	printf("INT: %dmV\t", ((unsigned int)(read_vol_int >> 1) * 25) + 600);
	printf("G3D: %dmV\n", ((unsigned int)(read_vol_g3d >> 1)* 25) + 600);
	printf("MIF: %dmV\t", ((unsigned int)(read_vol_mif & 0x3F) * 50) + 750);
	printf("MEM: %dmV\n", ((unsigned int)(read_vol_mem & 0x3F) * 50) + 750);
}

void pmic_max77686_init(void)
{
	
	/* set DVS1,2,3 as 0 by GPL0 */
	*((volatile unsigned int *)0x110000c0) = 0x11111111;
	*((volatile unsigned int *)0x110000c4) = 0x7;
	*((volatile unsigned int *)0x110000c4) = 0x0;
	*((volatile unsigned int *)0x110000c4) = 0x7;
	*((volatile unsigned int *)0x110000c4) = 0x0;
	*((volatile unsigned int *)0x110000c0) = 0x0;
	
		
	/* VDD_MIF */
	IIC0_EWrite(MAX77686_ADDR, 0x11, CALC_MAXIM77686_BUCK156789_VOLT(CONFIG_PM_VDD_MIF));
	/* VDD_ARM */
	IIC0_EWrite(MAX77686_ADDR, 0x14, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_ARM));
	/* VDD_INT */
	IIC0_EWrite(MAX77686_ADDR, 0x1E, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_INT));
	/* VDD_G3D */
	IIC0_EWrite(MAX77686_ADDR, 0x28, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_G3D));

}

void pmic_s5m8767_print(void)
{
	u8 read_data;
	IIC1_ESetport();
	printf("====================\n");
	printf("S5M8767 PMIC registers \n");
	printf("====================\n");
	IIC1_ERead(S5M8767_ADDR, 0, &read_data);
	printf("ID = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 0xE0, &read_data);
	printf("ONSRC = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 7, &read_data);
	printf("STATUS1 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 8, &read_data);
	printf("STATUS2 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 9, &read_data);
	printf("STATUS3 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 1, &read_data);
	printf("IRQ1 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 2, &read_data);
	printf("IRQ2 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 3, &read_data);
	printf("IRQ3 = 0x%02x \n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 0xE1, &read_data);
	printf("PWROFFSRC = 0x%02x \n", read_data);
	
	IIC1_ERead(PMIC_RTC_ADDR, 0x1B, &read_data);
	printf("PMIC_RTC_WTSR_SMPL_REG = 0x%02x\n", read_data);
	
	IIC1_ERead(S5M8767_ADDR, 0xE, &read_data);
	printf("S5M8767_REG_BUCHG = 0x%02x\n", read_data);	
	
}

int is_ldo_1_2_6_7_8_15(uint8_t ldo_id)
{
	if (ldo_id <= 0xE && (1 << ldo_id) & 0x40E3 )
		return 1;
	return 0;
}

struct pmic_s5m8767_init_reg_entry
{
	uint8_t reg_id;
	uint8_t value;
	uint8_t mask;
};
struct pmic_s5m8767_init_ldo_val
{
	uint8_t en1;
	uint8_t en2;
	uint16_t voltage;
};
struct pmic_s5m8767_init_reg_entry pmic_s5m8767_init_data[] = {
	{0xE, 0x6F, 0},
	{0x5A, 0x58, 0},
	{0x5B, 0xB4, 0},
	{0xA, 0xE, 0xE},
	{0xFF, 0xFF, 0}
};
struct pmic_s5m8767_init_ldo_val pmic_s5m8767_init_ldos[29] =
{
  { 0x3, 0x3, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x3, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0, 0, 1800 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 1950 },
  { 0x3, 0x1, 0 },
  { 0x3, 0, 0 },
  { 0x3, 0x1, 1950 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x3, 0 },
  { 0, 0, 0 },
  { 0, 0x1, 1800 },
  { 0, 0, 3300 },
  { 0, 0, 3300 },
  { 0, 0, 2800 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 1500 },
  { 0, 0, 0 },
  { 0xFF, 0xFF, 0 }
};

void pmic_s5m8767_init(void)
{
	struct pmic_s5m8767_init_reg_entry* cur_reg;
	struct pmic_s5m8767_init_ldo_val* cur_ldo;
	uint8_t val;
	int ldo_id;
	int ldo_reg_id;
	cur_reg = pmic_s5m8767_init_data;
	while(cur_reg->reg_id != 0xFF)
	{
		val = cur_reg->value;
		if(cur_reg->mask)
		{
			IIC1_ERead(S5M8767_ADDR, cur_reg->reg_id, &val);
			val = ~cur_reg->mask;
			val |= cur_reg->value;
		}
		IIC1_EWrite(S5M8767_ADDR, cur_reg->reg_id, val);
		cur_reg++;
	}
	ldo_id = 0;
	cur_ldo = pmic_s5m8767_init_ldos;
	while(cur_ldo->en1 != 0xFF)
	{		
		if (ldo_id > 1) //after LDO2 there are LDO2_2 LDO2_3 LDO2_4, jump over them
			ldo_reg_id = ldo_id + 95;
		else
			ldo_reg_id = ldo_id + 92;
		if(cur_ldo->en1 == cur_ldo->en2) {
			if(is_ldo_1_2_6_7_8_15(ldo_id))
				pmic_s5m8767_update_reg(ldo_reg_id, CALC_S5M8767_LDO1267815_VOLT(cur_ldo->voltage), 0x3F);
			else				
				pmic_s5m8767_update_reg(ldo_reg_id, CALC_S5M8767_ALL_LDO_VOLT(cur_ldo->voltage), 0x3F);
		}
		else if(cur_ldo->voltage) {
		    if(is_ldo_1_2_6_7_8_15(ldo_id))
				pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6) | CALC_S5M8767_LDO1267815_VOLT(cur_ldo->voltage), 0xFF);
			else				
				pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6) | CALC_S5M8767_ALL_LDO_VOLT(cur_ldo->voltage), 0xFF);				
		}
		else {		
			pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6), 0xC0);	
		}		
		cur_ldo++;
		ldo_id++;
	}
}

void pmic_print_info(void)
{	
	uint8_t pmic_id;
	IIC0_ESetport();
	IIC1_ESetport();
	IIC0_ERead(MAX8997_ADDR, 0, &pmic_id);
	if (pmic_id == 0x77) {
		printf("PMIC: MAX8997\n");

	} else if(pmic_id >= 0x0 && pmic_id <= 0x5) {
		printf("PMIC: S5M8767\n");
		pmic_s5m8767_print();
	} else {
		printf("PMIC: MAX77686\n");
		pmic_max77686_print();
	}
}

void pmic_init(void)
{
	u8 pmic_id;

	IIC0_ESetport();
	IIC1_ESetport();
#if 0
	/* read ID */
	IIC0_ERead(MAX8997_ADDR, 0, &pmic_id);
	if (pmic_id == 0x77) {
		I2C_MAX8997_VolSetting(PMIC_BUCK1, CALC_MAXIM_BUCK1245_VOLT(CONFIG_PM_VDD_ARM), 1);
		I2C_MAX8997_VolSetting(PMIC_BUCK2, CALC_MAXIM_BUCK1245_VOLT(CONFIG_PM_VDD_INT), 1);
		I2C_MAX8997_VolSetting(PMIC_BUCK3, CALC_MAXIM_BUCK37_VOLT(CONFIG_PM_VDD_G3D), 1);

		/* LDO14 config */
		I2C_MAX8997_VolSetting(PMIC_LDO14, CALC_MAXIM_ALL_LDO(CONFIG_PM_VDD_LDO14), 3);

	} else if(pmic_id >= 0x0 && pmic_id <= 0x5) {
		pmic_s5m8767_init();
	} else {
		pmic_max77686_init();
	}
#endif
	//GPA1PUD |= (0x5<<4);	// restore reset value: Pull Up/Down Enable SCL, SDA
}
