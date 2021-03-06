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
 * File Name : raccoon_dds_sw_lookup_triangle.ino
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/pgmspace.h>

#include "raccoon_dds_sw_triangle.h"

static const char __raccoon_dds_sw_triangle_name[] PROGMEM = "Triangle";

#define RACCOON_DDS_MACH_TRIANGLE_LOOKUP_TBL		\
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,	\
	0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,	\
	0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e,	\
	0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,	\
	0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e,	\
	0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e,	\
	0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e,	\
	0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,	\
	0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e,	\
	0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e,	\
	0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae,	\
	0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe,	\
	0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce,	\
	0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde,	\
	0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee,	\
	0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xff,	\
	0xff, 0xfc, 0xfa, 0xf8, 0xf6, 0xf4, 0xf2, 0xf0,	\
	0xee, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0,	\
	0xde, 0xdc, 0xda, 0xd8, 0xd6, 0xd4, 0xd2, 0xd0,	\
	0xce, 0xcc, 0xca, 0xc8, 0xc6, 0xc4, 0xc2, 0xc0,	\
	0xbe, 0xbc, 0xba, 0xb8, 0xb6, 0xb4, 0xb2, 0xb0,	\
	0xae, 0xac, 0xaa, 0xa8, 0xa6, 0xa4, 0xa2, 0xa0,	\
	0x9e, 0x9c, 0x9a, 0x98, 0x96, 0x94, 0x92, 0x90,	\
	0x8e, 0x8c, 0x8a, 0x88, 0x86, 0x84, 0x82, 0x80,	\
	0x7e, 0x7c, 0x7a, 0x78, 0x76, 0x74, 0x72, 0x70,	\
	0x6e, 0x6c, 0x6a, 0x68, 0x66, 0x64, 0x62, 0x60,	\
	0x5e, 0x5c, 0x5a, 0x58, 0x56, 0x54, 0x52, 0x50,	\
	0x4e, 0x4c, 0x4a, 0x48, 0x46, 0x44, 0x42, 0x40,	\
	0x3e, 0x3c, 0x3a, 0x38, 0x36, 0x34, 0x32, 0x30,	\
	0x2e, 0x2c, 0x2a, 0x28, 0x26, 0x24, 0x22, 0x20,	\
	0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x14, 0x12, 0x10,	\
	0x0e, 0x0c, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x00

static const uint8_t __raccoon_dds_sw_triangle_lookup_tbl[] PROGMEM = {
	RACCOON_DDS_MACH_TRIANGLE_LOOKUP_TBL,
	RACCOON_DDS_MACH_TRIANGLE_LOOKUP_TBL
};

raccoon_dds_sw_triangle::raccoon_dds_sw_triangle(const uint8_t *lookup_tbl)
{
	this->lookup_tbl = lookup_tbl;

	name = __raccoon_dds_sw_triangle_name;
}

static raccoon_dds_sw_triangle __raccoon_dds_sw_triangle(__raccoon_dds_sw_triangle_lookup_tbl);

raccoon_dds_sw_triangle *raccoon_dds_sw_triangle::singleton =
		&__raccoon_dds_sw_triangle;

raccoon_dds_sw_triangle *raccoon_dds_sw_triangle::get_instance(void)
{
	return singleton;
}
