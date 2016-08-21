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
 * File Name : raccoon_dds_hw.h
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 27/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_HW_H__
#define __RACCOON_DDS_HW_H__

#include <stdint.h>

#define RACCOON_DDS_HW_PORT		PORTD
#define RACCOON_DDS_HW_DDR		DDRD
#define RACCOON_DDS_HW_F_CPU		16000000UL
#define RACCOON_DDS_HW_MIN_FREQUENCY	1
#define RACCOON_DDS_HW_MAX_FREQUENCY	62500

typedef enum {
	E_RACCOON_DDS_HW_KEYCODE_RUN = 0,
	E_RACCOON_DDS_HW_KEYCODE_LEFT,
	E_RACCOON_DDS_HW_KEYCODE_RIGHT,
	E_RACCOON_DDS_HW_KEYCODE_UP,
	E_RACCOON_DDS_HW_KEYCODE_DOWN,
	E_RACCOON_DDS_HW_KEYCODE_INVALID,
} raccoon_morse_keycode_t;

typedef enum {
	E_RACCOON_DDS_KEYSTATE_NOT_PRESSED = 0,
	E_RACCOON_DDS_KEYSTATE_PRESSED,
} raccoon_dds_keystate_t;

class raccoon_dds_hw {
public:
	virtual void init(void) = 0;

	virtual raccoon_dds_keystate_t button_state(void) = 0;
	virtual raccoon_morse_keycode_t button_keycode(void) = 0;

	virtual void power_led_on(void) = 0;
	virtual void power_led_off(void) = 0;

	virtual void run_led_on(void) = 0;
	virtual void run_led_off(void) = 0;

	virtual void lcd_clear(void) = 0;
	virtual void lcd_clear_row(uint8_t row) = 0;
	virtual void lcd_set_cursor(uint8_t col, uint8_t row) = 0;
	virtual void lcd_blink(void) = 0;
	virtual void lcd_no_blink(void) = 0;
	virtual void lcd_print(char ch) = 0;
	virtual void lcd_print(const char *str) = 0;
	virtual void lcd_print_P(const char *str) = 0;
};

#endif /* __RACCOON_DDS_HW_H__ */
