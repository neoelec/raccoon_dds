/**
 * Copyright (C) 2016. Joo, Young Jin <neoelec@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/**
 * Project Name : Raccoon's DDS
 *
 * Project Description :
 *
 * Comments : tabstop = 8, shiftwidth = 8, noexpandtab
 */

/**
 * File Name : raccoon_dds_sw_lookup.ino
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <stdint.h>

#include "raccoon_dds_hw.h"

void raccoon_dds_sw_lookup::start(void)
{
	raccoon_dds_sw::start();

	RACCOON_DDS_MACH_LOOKUP_STATUS_REG &=
			~(1 << RACCOON_DDS_MACH_LOOKUP_STATUS_BIT);
}

void raccoon_dds_sw_lookup::stop(void)
{
	RACCOON_DDS_MACH_LOOKUP_STATUS_REG |=
			1 << RACCOON_DDS_MACH_LOOKUP_STATUS_BIT;

	raccoon_dds_sw::stop();
}

/* DDS signal generation function
 * Original idea is taken from
 * http://www.myplace.nu/avr/minidds/index.htm
 *
 * The modified one is found ate here.
 * http://www.scienceprog.com/avr-dds-signal-generator-v20/
 */
static void inline __raccoon_dds_sw_lookup_loop(const uint8_t *lookup_tbl, uint32_t add)
{
	uintptr_t __lookup_tbl = (uintptr_t)lookup_tbl;
	uint8_t ad0, ad1, ad2;

	ad0 = (uint8_t)(add & 0xFF);
	ad1 = (uint8_t)((add >> 8) & 0xFF);
	ad2 = (uint8_t)((add >> 16) & 0xFF);

	if ((__lookup_tbl & ~0xFF) != __lookup_tbl)
		__lookup_tbl = (__lookup_tbl & ~0xFF) + 0x100;

	__asm__ volatile (
		"eor	r18, r18	;r18<-0"			"\n\t"
		"eor	r19, r19	;r19<-0"			"\n\t"
		"1:"							"\n\t"
		"add	r18, %0		;1 cycle"			"\n\t"
		"adc	r19, %1		;1 cycle"			"\n\t"
		"adc	%A3, %2		;1 cycle"			"\n\t"
		"lpm 			;3 cycles"			"\n\t"
		"out	%4, __tmp_reg__	;1 cycle"			"\n\t"
		"sbis	%5, %6		;1 cycle if no skip"		"\n\t"
		"rjmp	1b		;2 cycles. Total 10 cycles"	"\n\t"
		:
		:"r" (ad0),"r" (ad1),"r" (ad2),"e" (__lookup_tbl),
			"I" (_SFR_IO_ADDR(RACCOON_DDS_HW_PORT)),
			"I" (_SFR_IO_ADDR(RACCOON_DDS_MACH_LOOKUP_STATUS_REG)),
			"I" (RACCOON_DDS_MACH_LOOKUP_STATUS_BIT)
		:"r18", "r19"
	);
}

void raccoon_dds_sw_lookup::prologue(void)
{
	// FIXME: to prevent the jitter error cause of internal timer interrupt
	// which used in time utilities.
	TIMSK0 &= ~(1 << TOIE0);
}

#define RACCOON_DDS_MACH_LOOKUP_SIG_TICKS	10
#define RACCOON_DDS_MACH_LOOKUP_ACC_FRAC_BITS	16

void raccoon_dds_sw_lookup::text(void)
{
	uint32_t add;
	float resolution;

	resolution = (float)RACCOON_DDS_HW_F_CPU;
	resolution /= (float)RACCOON_DDS_MACH_LOOKUP_SIG_TICKS;
	resolution /= (float)RACCOON_DDS_MACH_LOOKUP_TBL_SZ;
	resolution /= (float)((uint32_t)1 << RACCOON_DDS_MACH_LOOKUP_ACC_FRAC_BITS);

	add = (uint32_t)roundf((float)frequency / resolution);

	__raccoon_dds_sw_lookup_loop(lookup_tbl, add);
}

void raccoon_dds_sw_lookup::epilogue(void)
{
	RACCOON_DDS_HW_PORT = 0x00;
	TIMSK0 |= 1 << TOIE0;
}
