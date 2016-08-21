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
 * File Name : raccoon_dds_sw.ino
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#include "raccoon_dds_sw.h"

raccoon_dds_sw::raccoon_dds_sw()
		: running(false)
{
}

const char *raccoon_dds_sw::get_name(void)
{
	return name;
}

void raccoon_dds_sw::set_frequency(unsigned long frequency)
{
	this->frequency = frequency;
}

unsigned long raccoon_dds_sw::get_frequency(void)
{
	return frequency;
}

void raccoon_dds_sw::loop(void)
{
	prologue();
	while (running)
		text();
	epilogue();
}

void raccoon_dds_sw::start(void)
{
	running = true;
}

void raccoon_dds_sw::stop(void)
{
	running = false;
}
