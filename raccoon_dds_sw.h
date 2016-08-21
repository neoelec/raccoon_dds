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
 * File Name : raccoon_dds_sw.h
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_SW_H__
#define __RACCOON_DDS_SW_H__

class raccoon_dds_sw {
public:
	raccoon_dds_sw();

	const char *get_name(void);
	void set_frequency(unsigned long frequency);
	unsigned long get_frequency(void);

	virtual void loop(void);
	virtual void start(void);
	virtual void stop(void);

protected:
	virtual void prologue(void) = 0;
	virtual void text(void) = 0;
	virtual void epilogue(void) = 0;

	const char *name;
	bool running;

	unsigned long frequency;
};

#endif /* __RACCOON_DDS_SW_H__ */
