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
 * File Name : raccoon_dds_menu.ino
 *
 * File Description :
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 27/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <stdio.h>

#include "raccoon_dds.h"
#include "raccoon_dds_menu.h"
#include "raccoon_dds_sw_ecg.h"
#include "raccoon_dds_sw_ramp.h"
#include "raccoon_dds_sw_sawtooth.h"
#include "raccoon_dds_sw_sine.h"
#include "raccoon_dds_sw_square.h"
#include "raccoon_dds_sw_triangle.h"

static const char __raccoon_dds_menu_magic[] PROGMEM = __DATE__ " " __TIME__;

struct raccoon_dds_menu_save_data {
	char magic[ARRAY_SIZE(__raccoon_dds_menu_magic)];
	raccoon_dds_sw *dds_sw;
	unsigned long frequency;
};

static raccoon_dds_menu_save_data *__raccoon_dds_menu_save_data;

static bool __raccoon_dds_menu_verify_magic(void)
{
	size_t i;
	char tmp_e, tmp_p;

	for (i = 0; i < ARRAY_SIZE(__raccoon_dds_menu_magic); i++) {
		tmp_e = EEPROM.read((int)(&__raccoon_dds_menu_save_data->magic[i]));
		tmp_p = pgm_read_byte(&__raccoon_dds_menu_magic[i]);
		if (tmp_p != tmp_e)
			return false;
	}

	return true;
}

static void __raccoon_dds_menu_save_magic(void)
{
	size_t i;
	char tmp_p;

	for (i = 0; i < ARRAY_SIZE(__raccoon_dds_menu_magic); i++) {
		tmp_p = pgm_read_byte(&__raccoon_dds_menu_magic[i]);
		EEPROM.write((int)(&__raccoon_dds_menu_save_data->magic[i]), tmp_p);
	}
}

static void __raccoon_dds_menu_load_dds_sw(void)
{
	union {
		raccoon_dds_sw *dds_sw;
		unsigned long frequency;
		uint8_t b[];
	} saved;
	uint8_t *ptr;
	size_t i;

	ptr = (uint8_t *)&__raccoon_dds_menu_save_data->dds_sw;
	for (i = 0; i < sizeof(raccoon_dds_sw *); i++)
		saved.b[i] = EEPROM.read((int)ptr + i);
	dds_sw = saved.dds_sw;

	ptr = (uint8_t *)&__raccoon_dds_menu_save_data->frequency;;
	for (i = 0; i < sizeof(unsigned long ); i++)
		saved.b[i] = EEPROM.read((int)ptr + i);
	dds_sw->set_frequency(saved.frequency);
}

static void __raccoon_dds_menu_save_dds_sw(void)
{
	union {
		raccoon_dds_sw *dds_sw;
		unsigned long frequency;
		uint8_t b[];
	} saved;
	uint8_t *ptr;
	size_t i;

	saved.dds_sw = dds_sw;
	ptr = (uint8_t *)&__raccoon_dds_menu_save_data->dds_sw;
	for (i = 0; i < sizeof(raccoon_dds_sw *); i++)
		EEPROM.write((int)ptr + i, saved.b[i]);

	saved.frequency = dds_sw->get_frequency();
	ptr = (uint8_t *)&__raccoon_dds_menu_save_data->frequency;;
	for (i = 0; i < sizeof(unsigned long ); i++)
		EEPROM.write((int)ptr + i, saved.b[i]);
}

/* */

class raccoon_dds_submenu_mode : public raccoon_dds_submenu {
public:
	raccoon_dds_submenu_mode();
	static raccoon_dds_submenu_mode *get_instance(void)
	{
		return singleton;
	}

	virtual void init(void);
	virtual void key_up(void);
	virtual void key_down(void);

private:
	void change_item(void);

	static raccoon_dds_submenu_mode *singleton;

	raccoon_dds_sw *item_current;
	raccoon_dds_sw **item_list;
	size_t item_nr;
	size_t item_idx;
};

#define RACCOON_DDS_SUBMENU_MODE_SW_MAX	6
static raccoon_dds_sw *__raccoon_dds_submenu_mode_item_list[RACCOON_DDS_SUBMENU_MODE_SW_MAX];

raccoon_dds_submenu_mode::raccoon_dds_submenu_mode()
{
	item_nr = 0;
	item_list = __raccoon_dds_submenu_mode_item_list;

	item_list[item_nr++] = raccoon_dds_sw_sine::get_instance();
	item_list[item_nr++] = raccoon_dds_sw_square::get_instance();
	item_list[item_nr++] = raccoon_dds_sw_triangle::get_instance();
	item_list[item_nr++] = raccoon_dds_sw_ramp::get_instance();
	item_list[item_nr++] = raccoon_dds_sw_sawtooth::get_instance();
	item_list[item_nr++] = raccoon_dds_sw_ecg::get_instance();

	item_idx = 0;
	item_current = item_list[item_idx];
}

static raccoon_dds_submenu_mode __raccoon_dds_submenu_mode;

raccoon_dds_submenu_mode *raccoon_dds_submenu_mode::singleton =
		&__raccoon_dds_submenu_mode;

static const char __menu_change_mode[] PROGMEM = "- Change Func.";

void raccoon_dds_submenu_mode::init(void)
{
	dds_hw->lcd_clear();
	dds_hw->lcd_print_P(__menu_change_mode);

	if (dds_sw != item_current) {
		item_idx = 0;
		while (dds_sw != item_current)
			item_current = item_list[++item_idx];
	}

	change_item();
}

void raccoon_dds_submenu_mode::key_up(void)
{
	if (item_idx)
		item_idx--;
	else
		item_idx = item_nr - 1;
	change_item();
}

void raccoon_dds_submenu_mode::key_down(void)
{
	item_idx++;
	item_idx = item_idx % item_nr;
	change_item();
}

void raccoon_dds_submenu_mode::change_item(void)
{
	char buf[8];

	dds_hw->lcd_clear_row(1);

	dds_hw->lcd_set_cursor(0, 1);
	sprintf(buf, "%u. ", item_idx + 1);
	dds_hw->lcd_print(buf);

	item_current = item_list[item_idx];
	dds_hw->lcd_print_P(item_current->get_name());

	item_current->set_frequency(dds_sw->get_frequency());
	dds_sw = item_current;
}

/* */

void raccoon_dds_submenu::init(void)
{
}

void raccoon_dds_submenu::loop(void)
{
}

void raccoon_dds_submenu::key_up(void)
{
}

void raccoon_dds_submenu::key_down(void)
{
}

/* */

class raccoon_dds_submenu_frequency : public raccoon_dds_submenu {
public:
	raccoon_dds_submenu_frequency(unsigned long step);

	virtual void init(void);
	virtual void key_up(void);
	virtual void key_down(void);

private:
	void display_frequency(void);
	void increase_frequency(unsigned long step);
	void decrease_frequency(unsigned long step);

	unsigned long frequency;
	unsigned long step;
	uint8_t lcd_col;
};

static const char __menu_mode_change_frequency_0[] PROGMEM = "- Change Freq.";
static const char __menu_mode_change_frequency_1[] PROGMEM = "Freq : ";

raccoon_dds_submenu_frequency::raccoon_dds_submenu_frequency(unsigned long step)
{
	this->step = step;

	lcd_col = (uint8_t)(11. - log10f((float)step));
}

void raccoon_dds_submenu_frequency::init(void)
{
	dds_hw->lcd_clear();
	dds_hw->lcd_print_P(__menu_mode_change_frequency_0);

	frequency = dds_sw->get_frequency();
	display_frequency();
	dds_hw->lcd_blink();
}

void raccoon_dds_submenu_frequency::key_up(void)
{
	frequency += step;
	if (frequency > RACCOON_DDS_HW_MAX_FREQUENCY)
		frequency = RACCOON_DDS_HW_MAX_FREQUENCY;

	dds_sw->set_frequency(frequency);
	display_frequency();
}

void raccoon_dds_submenu_frequency::key_down(void)
{
	if (frequency > step)
		frequency -= step;
	else
		frequency = RACCOON_DDS_HW_MIN_FREQUENCY;

	if (frequency < RACCOON_DDS_HW_MIN_FREQUENCY)
		frequency = RACCOON_DDS_HW_MIN_FREQUENCY;

	dds_sw->set_frequency(frequency);
	display_frequency();
}

void raccoon_dds_submenu_frequency::display_frequency(void)
{
	char buf[16];

	dds_hw->lcd_set_cursor(0, 1);
	dds_hw->lcd_print_P(__menu_mode_change_frequency_1);
	sprintf(buf, "%05lu Hz", frequency);
	dds_hw->lcd_print(buf);
	dds_hw->lcd_set_cursor(lcd_col, 1);
}

static raccoon_dds_submenu_frequency __raccoon_dds_submenu_frequency_10k(10000);
static raccoon_dds_submenu_frequency __raccoon_dds_submenu_frequency_1k(1000);
static raccoon_dds_submenu_frequency __raccoon_dds_submenu_frequency_100(100);
static raccoon_dds_submenu_frequency __raccoon_dds_submenu_frequency_10(10);
static raccoon_dds_submenu_frequency __raccoon_dds_submenu_frequency_1(1);

/* */

#define RACCOON_DDS_MENU_SUBMENU_MAX		6

static raccoon_dds_submenu *__raccoon_dds_menu_submenu_list[RACCOON_DDS_MENU_SUBMENU_MAX];

raccoon_dds_menu::raccoon_dds_menu()
{
	submenu_nr = 0;
	submenu_list = __raccoon_dds_menu_submenu_list;

	submenu_list[submenu_nr++] = raccoon_dds_submenu_mode::get_instance();
	submenu_list[submenu_nr++] = &__raccoon_dds_submenu_frequency_1;
	submenu_list[submenu_nr++] = &__raccoon_dds_submenu_frequency_10;
	submenu_list[submenu_nr++] = &__raccoon_dds_submenu_frequency_100;
	submenu_list[submenu_nr++] = &__raccoon_dds_submenu_frequency_1k;
	submenu_list[submenu_nr++] = &__raccoon_dds_submenu_frequency_10k;

	submenu_idx = 0;
	submenu_current = submenu_list[submenu_idx];
}

static raccoon_dds_menu __raccoon_dds_menu;

raccoon_dds_menu *raccoon_dds_menu::singleton = &__raccoon_dds_menu;

raccoon_dds_menu *raccoon_dds_menu::get_instance(void)
{
	return singleton;
}

void raccoon_dds_menu::init(void)
{
	state = E_RACCOON_DDS_MENU_ENTERED;
	keycode = E_RACCOON_DDS_HW_KEYCODE_INVALID;

	if (!__raccoon_dds_menu_verify_magic()) {
		dds_sw = raccoon_dds_sw_sine::get_instance();
		dds_sw->set_frequency(1000);
		__raccoon_dds_menu_save_magic();
		__raccoon_dds_menu_save_dds_sw();
	} else {
		__raccoon_dds_menu_load_dds_sw();
	}
}

bool raccoon_dds_menu::run(void)
{
	switch (state) {
	case E_RACCOON_DDS_MENU_ENTERED:
		dds_hw->run_led_off();
		change_submenu();
		sw_previous = dds_sw;
		freq_previous = dds_sw->get_frequency();
		state = E_RACCOON_DDS_MENU_SUBMENU;
		break;
	case E_RACCOON_DDS_MENU_SUBMENU:
		switch (keycode) {
		case E_RACCOON_DDS_HW_KEYCODE_RUN:
			if (dds_sw != sw_previous ||
			    freq_previous != dds_sw->get_frequency())
				__raccoon_dds_menu_save_dds_sw();
			display_current_setting();
			dds_hw->run_led_on();
			dds_sw->start();
			state = E_RACCOON_DDS_MENU_DEACTIVE;
			return false;
		case E_RACCOON_DDS_HW_KEYCODE_LEFT:
			if (submenu_idx)
				submenu_idx--;
			else
				submenu_idx = submenu_nr - 1;
			change_submenu();
			break;
		case E_RACCOON_DDS_HW_KEYCODE_RIGHT:
			submenu_idx++;
			submenu_idx = submenu_idx % submenu_nr;
			change_submenu();
			break;
		case E_RACCOON_DDS_HW_KEYCODE_UP:
			submenu_current->key_up();
			break;
		case E_RACCOON_DDS_HW_KEYCODE_DOWN:
			submenu_current->key_down();
			break;
		default:
			break;
		}
		keycode = E_RACCOON_DDS_HW_KEYCODE_INVALID;
		state = E_RACCOON_DDS_MENU_REDY_KEY;
		break;
	default:
		submenu_current->loop();
	}

	return true;
}

void raccoon_dds_menu::loop(void)
{
	if (E_RACCOON_DDS_MENU_DEACTIVE == state)
		return;

	while (run()) ;
}

void raccoon_dds_menu::handler(void)
{
	raccoon_dds_keystate_t keystate;

	keystate = dds_hw->button_state();
	keycode = dds_hw->button_keycode();

	if (E_RACCOON_DDS_KEYSTATE_PRESSED != keystate) {
		keycode = E_RACCOON_DDS_HW_KEYCODE_INVALID;
		return;
	}

	if (E_RACCOON_DDS_MENU_DEACTIVE == state &&
	    E_RACCOON_DDS_HW_KEYCODE_RUN == keycode) {
		state = E_RACCOON_DDS_MENU_ENTERED;
		dds_sw->stop();
		keycode = E_RACCOON_DDS_HW_KEYCODE_INVALID;
	} else if (E_RACCOON_DDS_MENU_REDY_KEY == state) {
		state = E_RACCOON_DDS_MENU_SUBMENU;
	} else {
		keycode = E_RACCOON_DDS_HW_KEYCODE_INVALID;
	}
}

void raccoon_dds_menu::change_submenu(void)
{
	submenu_current = submenu_list[submenu_idx];
	submenu_current->init();
}

void raccoon_dds_menu::display_current_setting(void)
{
	char buf[16];

	dds_hw->lcd_clear();
	dds_hw->lcd_set_cursor(0, 0);
	dds_hw->lcd_print("Func : ");
	dds_hw->lcd_print_P(dds_sw->get_name());
	dds_hw->lcd_set_cursor(0, 1);
	dds_hw->lcd_print("Freq : ");
	sprintf(buf, "%-5lu Hz", dds_sw->get_frequency());
	dds_hw->lcd_print(buf);
}
