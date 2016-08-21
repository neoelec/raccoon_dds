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
 * File Name : raccoon_dds.h
 *
 * File Description :
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 14/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_H__
#define __RACCOON_DDS_H__

#include "raccoon_dds_hw.h"
#include "raccoon_dds_sw.h"

#define ARRAY_SIZE(_a)		(sizeof(_a) / sizeof(_a[0]))

extern raccoon_dds_hw *dds_hw;
extern raccoon_dds_sw *dds_sw;
extern raccoon_dds_menu *dds_menu;

#endif /* __RACCOON_DDS_H__ */
