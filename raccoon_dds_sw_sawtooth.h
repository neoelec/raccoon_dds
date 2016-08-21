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
 * File Name : raccoon_dds_sw_lookup_sawtooth.h
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_SW_SAWTOOTH_H__
#define __RACCOON_DDS_SW_SAWTOOTH_H__

#include "raccoon_dds_sw_lookup.h"

class raccoon_dds_sw_sawtooth : public raccoon_dds_sw_lookup {
public:
	raccoon_dds_sw_sawtooth(const uint8_t *lookup_tbl);
	static raccoon_dds_sw_sawtooth *get_instance(void);

private:
	static raccoon_dds_sw_sawtooth *singleton;
};

#endif /* __RACCOON_DDS_SW_SAWTOOTH_H__ */
