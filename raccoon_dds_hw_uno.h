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
 * File Name : raccoon_dds_hw_uno.h
 *
 * File Description :
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 27/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_HW_UNO_H__
#define __RACCOON_DDS_HW_UNO_H__

#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "raccoon_dds_hw.h"

// if PCF8574 is used then use the bellow slave address.
#define RACCOON_DDS_HW_UNO_LCD_SLAVE		0x27
// if PCF8574A is used then use the bellow slave address.
//#define RACCOON_DDS_HW_UNO_LCD_SLAVE		0x3F
#define RACCOON_DDS_HW_UNO_LCD_COL		16
#define RACCOON_DDS_HW_UNO_LCD_ROW		2

#define RACCOON_DDS_HW_UNO_KEYADC_MARGIN		20

/* FIXME: select a LARGE pull-up resistance as possible as to prevent error
 * while 'analogRead' is called very frequently. */
/* TODO: slect a pull-up resistor whick make about 150 adc value when
 * highest pull-down resistance connected. in this hw, one 75K and 4 2K
 * resistors are used to handling 5 tack switches. */
#define RACCOON_DDS_HW_UNO_KEYADC_PULLUP		75	/* 75k */
#define RACCOON_DDS_HW_UNO_KEYADC_PULLDN		2	/* 2k */

class raccoon_dds_hw_uno : public raccoon_dds_hw {
public:
	raccoon_dds_hw_uno();
	static raccoon_dds_hw_uno *get_instance(void);

	virtual void init(void);

	virtual raccoon_dds_keystate_t button_state(void);
	virtual raccoon_morse_keycode_t button_keycode(void);

	virtual void power_led_on(void);
	virtual void power_led_off(void);

	virtual void run_led_on(void);
	virtual void run_led_off(void);

	virtual void lcd_clear(void);
	virtual void lcd_clear_row(uint8_t row);
	virtual void lcd_set_cursor(uint8_t col, uint8_t row);
	virtual void lcd_blink(void);
	virtual void lcd_no_blink(void);
	virtual void lcd_print(char ch);
	virtual void lcd_print(const char *str);
	virtual void lcd_print_P(const char *str);

private:
	static raccoon_dds_hw_uno *singleton;

	uint8_t button_pin;
	uint8_t power_led_pin;
	uint8_t run_led_pin;

	LiquidCrystal_I2C *lcd;
	uint8_t lcd_row_max, lcd_col_max;
	uint8_t lcd_row, lcd_col;
};

#endif /* __RACCOON_DDS_HW_UNO_H__ */
