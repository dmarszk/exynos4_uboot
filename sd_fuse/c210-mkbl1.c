/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE			*fp;
	unsigned char	*Buf, *Buf1, *a;
	int				BufLen;
	int				nbytes, fileLen;
	unsigned long	checksum;
	int		i;

//////////////////////////////////////////////////////////////
	if (argc != 4)
	{
		printf("Usage: mkbl1 <source file> <destination file> <size> \n");
		return -1;
	}

//////////////////////////////////////////////////////////////
	BufLen = atoi(argv[3]);
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);
	
	Buf1 = (char *)malloc(BufLen);
	memset(Buf1, 0x00, BufLen);
	
//////////////////////////////////////////////////////////////
	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	fileLen = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if ( BufLen > fileLen )
	{
		printf("Usage: unsupported size\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);

//////////////////////////////////////////////////////////////
	for(i = 0, checksum = 0;i < 16368;i++)
	{
		Buf1[i+16] = Buf[i];
		checksum += Buf1[i+16];
	}

	*(unsigned long *)(Buf1+0) = 0x1f;
	*(unsigned long *)(Buf1+4) = checksum;

	Buf1[ 0] ^= 0x53;
	Buf1[ 1] ^= 0x35;
	Buf1[ 2] ^= 0x50;
	Buf1[ 3] ^= 0x43;
	Buf1[ 4] ^= 0x32;
	Buf1[ 5] ^= 0x31;
	Buf1[ 6] ^= 0x30;
	Buf1[ 7] ^= 0x20;
	Buf1[ 8] ^= 0x48;
	Buf1[ 9] ^= 0x45;
	Buf1[10] ^= 0x41;
	Buf1[11] ^= 0x44;
	Buf1[12] ^= 0x45;
	Buf1[13] ^= 0x52;
	Buf1[14] ^= 0x20;
	Buf1[15] ^= 0x20;

	for(i = 1; i < 16; i++)
	{
		Buf1[i] ^= Buf1[i-1];
	}

//////////////////////////////////////////////////////////////
	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf1;
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		free(Buf1);
		fclose(fp);
		return -1;
	}

	free(Buf);
	free(Buf1);
	fclose(fp);

	return 0;
}
