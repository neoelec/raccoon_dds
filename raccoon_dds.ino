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
 * File Name : raccoon_dds.ino
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 21/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/pgmspace.h>

#include "pcint.h"

#include "raccoon_dds_hw.h"
#include "raccoon_dds_hw_uno.h"
#include "raccoon_dds_sw.h"
#include "raccoon_dds_menu.h"

raccoon_dds_hw *dds_hw;
raccoon_dds_sw *dds_sw;
raccoon_dds_menu *dds_menu;

static void dds_pcint_handler(void)
{
	dds_menu->handler();
}

static const char __dds_banner[] PROGMEM = "Raccoon's DDS";

void setup(void)
{
	// put your setup code here, to run once:
	dds_hw = raccoon_dds_hw_uno::get_instance();

	dds_hw->init();
	dds_hw->lcd_print_P(__dds_banner);

	delay(1000);

	dds_menu = raccoon_dds_menu::get_instance();
	dds_menu->init();

	pcint_attach(E_PCINT1, dds_pcint_handler);
}

void loop(void)
{
	// put your main code here, to run repeatedly:
	dds_menu->loop();
	dds_sw->loop();
}
