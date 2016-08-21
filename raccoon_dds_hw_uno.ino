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
 * File Name : raccoon_dds_hw_uno.ino
 *
 * File Description :
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 27/Aug/2016
 * Version : Baby-Raccoon
 */

#include <avr/pgmspace.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "pcint.h"
#include "raccoon_dds_hw.h"
#include "raccoon_dds_hw_uno.h"

/* FIXME: is this a good idea? */
static LiquidCrystal_I2C __raccoon_dds_hw_uno_lcd(
		RACCOON_DDS_HW_UNO_LCD_SLAVE,
		RACCOON_DDS_HW_UNO_LCD_COL,
		RACCOON_DDS_HW_UNO_LCD_ROW);

raccoon_dds_hw_uno::raccoon_dds_hw_uno()
		: button_pin(A0),
		power_led_pin(12), run_led_pin(13),
		lcd(&__raccoon_dds_hw_uno_lcd),
		lcd_row_max(RACCOON_DDS_HW_UNO_LCD_ROW - 1),
		lcd_col_max(RACCOON_DDS_HW_UNO_LCD_COL - 1)
{
}

static raccoon_dds_hw_uno __raccoon_dds_hw_uno;

raccoon_dds_hw_uno *raccoon_dds_hw_uno::singleton =
		&__raccoon_dds_hw_uno;

raccoon_dds_hw_uno *raccoon_dds_hw_uno::get_instance(void)
{
	return singleton;
}

void raccoon_dds_hw_uno::init(void)
{
	RACCOON_DDS_HW_DDR = 0xFF;
	RACCOON_DDS_HW_PORT = 0x00;

	Serial.end();

	pinMode(button_pin, INPUT);
	pcint_enable(button_pin);

	pinMode(power_led_pin, OUTPUT);
	digitalWrite(power_led_pin, HIGH);

	pinMode(run_led_pin, OUTPUT);
	digitalWrite(run_led_pin, LOW);

	lcd->begin();
	lcd->backlight();
	lcd_row = lcd_col = 0;
}

raccoon_dds_keystate_t raccoon_dds_hw_uno::button_state(void)
{
	return digitalRead(button_pin) ? E_RACCOON_DDS_KEYSTATE_NOT_PRESSED
			: E_RACCOON_DDS_KEYSTATE_PRESSED;
}

#define __M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(__resistor_lower,		\
		__resistor_upper)					\
	((__resistor_lower) * 1024 / (__resistor_upper + __resistor_lower) + \
	 RACCOON_DDS_HW_UNO_KEYADC_MARGIN)

#define M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(__nr_pulldn)			\
	__M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(__nr_pulldn *		\
			(RACCOON_DDS_HW_UNO_KEYADC_PULLDN),		\
			RACCOON_DDS_HW_UNO_KEYADC_PULLUP)

#define RACCOON_DDS_HW_UNO_KEYADC_LEFT					\
		M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(0)
#define RACCOON_DDS_HW_UNO_KEYADC_DOWN					\
		M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(1)
#define RACCOON_DDS_HW_UNO_KEYADC_UP					\
		M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(2)
#define RACCOON_DDS_HW_UNO_KEYADC_RIGHT					\
		M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(3)
#define RACCOON_DDS_HW_UNO_KEYADC_RUN					\
		M_RACCOON_DDS_HW_UNO_KEYADC_VALUE(4)

#define RACCOON_DDS_HW_UNO_KEYADC_NR_RETRY		20

#define min(a, b)		((a) < (b) ? (a) : (b))
#define max(a, b)		((a) > (b) ? (a) : (b))

raccoon_morse_keycode_t raccoon_dds_hw_uno::button_keycode(void)
{
	int adc_tmp = analogRead(button_pin);
	int adc_raw, adc_min, adc_max;
	size_t i;

	adc_raw = adc_tmp;
	adc_max = adc_tmp;
	adc_min = adc_tmp;
	for (i = 0; i < RACCOON_DDS_HW_UNO_KEYADC_NR_RETRY - 1; i++) {
		adc_tmp = analogRead(button_pin);
		adc_raw += adc_tmp;
		adc_min = min(adc_tmp, adc_min);
		adc_max = max(adc_tmp, adc_max);
	}

	adc_raw -= (adc_min + adc_max);
	adc_raw /= (RACCOON_DDS_HW_UNO_KEYADC_NR_RETRY - 2);

	if (RACCOON_DDS_HW_UNO_KEYADC_RUN < adc_raw)
		return E_RACCOON_DDS_HW_KEYCODE_INVALID;
	else if (RACCOON_DDS_HW_UNO_KEYADC_RIGHT < adc_raw)
		return E_RACCOON_DDS_HW_KEYCODE_RUN;
	else if (RACCOON_DDS_HW_UNO_KEYADC_UP < adc_raw)
		return E_RACCOON_DDS_HW_KEYCODE_RIGHT;
	else if (RACCOON_DDS_HW_UNO_KEYADC_DOWN < adc_raw)
		return E_RACCOON_DDS_HW_KEYCODE_UP;
	else if (RACCOON_DDS_HW_UNO_KEYADC_LEFT < adc_raw)
		return E_RACCOON_DDS_HW_KEYCODE_DOWN;

	return E_RACCOON_DDS_HW_KEYCODE_LEFT;
}

void raccoon_dds_hw_uno::power_led_on(void)
{
	digitalWrite(power_led_pin, HIGH);
}

void raccoon_dds_hw_uno::power_led_off(void)
{
	digitalWrite(power_led_pin, LOW);
}

void raccoon_dds_hw_uno::run_led_on(void)
{
	digitalWrite(run_led_pin, HIGH);
}

void raccoon_dds_hw_uno::run_led_off(void)
{
	digitalWrite(run_led_pin, LOW);
}

void raccoon_dds_hw_uno::lcd_clear(void)
{
	lcd->clear();
	lcd->home();
	lcd->noBlink();

	lcd_row = 0;
	lcd_col = 0;
}

void raccoon_dds_hw_uno::lcd_clear_row(uint8_t row)
{
	uint8_t i;

	lcd->setCursor(0, row);
	for (i = 0; i <= lcd_col_max; i++)
		lcd->print(' ');
	lcd->setCursor(0, row);
}

void raccoon_dds_hw_uno::lcd_set_cursor(uint8_t col, uint8_t row)
{
	if (col > lcd_col_max || row > lcd_col_max)
		return;

	lcd->setCursor(col, row);
	lcd_row = row;
	lcd_col = col;
}

void raccoon_dds_hw_uno::lcd_blink(void)
{
	lcd->blink();
}

void raccoon_dds_hw_uno::lcd_no_blink(void)
{
	lcd->noBlink();
}

void raccoon_dds_hw_uno::lcd_print(char ch)
{
	if ('\n' == ch || '\r' == ch)
		ch = ' ';

	if (lcd_col > lcd_col_max) {
		lcd_col = 0;
		if (++lcd_row > lcd_row_max)
			lcd_row = 0;

		lcd_clear_row(lcd_row);
	}

	lcd->print(ch);

	lcd_col++;
}

void raccoon_dds_hw_uno::lcd_print(const char *str)
{
	while (*str)
		lcd_print(*str++);
}

void raccoon_dds_hw_uno::lcd_print_P(const char *str)
{
	char ch;

	while (ch = pgm_read_byte(str++))
		lcd_print(ch);
}
