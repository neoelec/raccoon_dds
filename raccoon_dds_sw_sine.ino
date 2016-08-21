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
 * File Name : raccoon_dds_sw_lookup_sine.ino
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/pgmspace.h>

#include "raccoon_dds_sw_sine.h"

static const char __raccoon_dds_sw_sine_name[] PROGMEM = "Sine";

#define RACCOON_DDS_MACH_SINE_LOOKUP_TBL		\
	0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95,	\
	0x98, 0x9b, 0x9e, 0xa2, 0xa5, 0xa7, 0xaa, 0xad,	\
	0xb0, 0xb3, 0xb6, 0xb9, 0xbc, 0xbe, 0xc1, 0xc4,	\
	0xc6, 0xc9, 0xcb, 0xce, 0xd0, 0xd3, 0xd5, 0xd7,	\
	0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8,	\
	0xea, 0xeb, 0xed, 0xee, 0xf0, 0xf1, 0xf3, 0xf4,	\
	0xf5, 0xf6, 0xf8, 0xf9, 0xfa, 0xfa, 0xfb, 0xfc,	\
	0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff,	\
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfd,	\
	0xfd, 0xfc, 0xfb, 0xfa, 0xfa, 0xf9, 0xf8, 0xf6,	\
	0xf5, 0xf4, 0xf3, 0xf1, 0xf0, 0xee, 0xed, 0xeb,	\
	0xea, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0, 0xde, 0xdc,	\
	0xda, 0xd7, 0xd5, 0xd3, 0xd0, 0xce, 0xcb, 0xc9,	\
	0xc6, 0xc4, 0xc1, 0xbe, 0xbc, 0xb9, 0xb6, 0xb3,	\
	0xb0, 0xad, 0xaa, 0xa7, 0xa5, 0xa2, 0x9e, 0x9b,	\
	0x98, 0x95, 0x92, 0x8f, 0x8c, 0x89, 0x86, 0x83,	\
	0x7f, 0x7c, 0x79, 0x76, 0x73, 0x70, 0x6d, 0x6a,	\
	0x67, 0x64, 0x61, 0x5d, 0x5a, 0x58, 0x55, 0x52,	\
	0x4f, 0x4c, 0x49, 0x46, 0x43, 0x41, 0x3e, 0x3b,	\
	0x39, 0x36, 0x34, 0x31, 0x2f, 0x2c, 0x2a, 0x28,	\
	0x25, 0x23, 0x21, 0x1f, 0x1d, 0x1b, 0x19, 0x17,	\
	0x15, 0x14, 0x12, 0x11, 0x0f, 0x0e, 0x0c, 0x0b,	\
	0x0a, 0x09, 0x07, 0x06, 0x05, 0x05, 0x04, 0x03,	\
	0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,	\
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02,	\
	0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x09,	\
	0x0a, 0x0b, 0x0c, 0x0e, 0x0f, 0x11, 0x12, 0x14,	\
	0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f, 0x21, 0x23,	\
	0x25, 0x28, 0x2a, 0x2c, 0x2f, 0x31, 0x34, 0x36,	\
	0x39, 0x3b, 0x3e, 0x41, 0x43, 0x46, 0x49, 0x4c,	\
	0x4f, 0x52, 0x55, 0x58, 0x5a, 0x5d, 0x61, 0x64,	\
	0x67, 0x6a, 0x6d, 0x70, 0x73, 0x76, 0x79, 0x7c

static const uint8_t __raccoon_dds_sw_sine_lookup_tbl[] PROGMEM = {
	RACCOON_DDS_MACH_SINE_LOOKUP_TBL,
	RACCOON_DDS_MACH_SINE_LOOKUP_TBL
};

raccoon_dds_sw_sine::raccoon_dds_sw_sine(const uint8_t *lookup_tbl)
{
	this->lookup_tbl = lookup_tbl;

	name = __raccoon_dds_sw_sine_name;
}

static raccoon_dds_sw_sine __raccoon_dds_sw_sine(__raccoon_dds_sw_sine_lookup_tbl);

raccoon_dds_sw_sine *raccoon_dds_sw_sine::singleton =
		&__raccoon_dds_sw_sine;

raccoon_dds_sw_sine *raccoon_dds_sw_sine::get_instance(void)
{
	return singleton;
}
