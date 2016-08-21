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
 * File Name : raccoon_dds_sw_lookup.h
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_SW_LOOKUP_H__
#define __RACCOON_DDS_SW_LOOKUP_H__

#include <stdint.h>

#include "raccoon_dds_sw.h"

#define RACCOON_DDS_MACH_LOOKUP_STATUS_REG	GPIOR0
#define RACCOON_DDS_MACH_LOOKUP_STATUS_BIT	GPIOR00

#define RACCOON_DDS_MACH_LOOKUP_TBL_SZ		256

class raccoon_dds_sw_lookup : public raccoon_dds_sw {
public:
	virtual void start(void);
	virtual void stop(void);

protected:
	virtual void prologue(void);
	virtual void text(void);
	virtual void epilogue(void);

	const uint8_t *lookup_tbl;
};

#endif /* __RACCOON_DDS_SW_LOOKUP_H__ */
