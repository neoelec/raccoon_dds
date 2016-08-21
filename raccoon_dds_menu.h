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
 * File Name : raccoon_dds_menu.h
 *
 * File Description :
 *
 * Author : Joo, Young Jin <neoelec@gmail.com>
 * Dept : Raccoon's Cave
 * Created Date : 27/Aug/2016
 * Version : Baby-Raccoon
 */

#ifndef __RACCOON_DDS_MENU_H__
#define __RACCOON_DDS_MENU_H__

#include "raccoon_dds_sw.h"

class raccoon_dds_submenu {
public:
	virtual void init(void);
	virtual void loop(void);
	virtual void key_up(void);
	virtual void key_down(void);
};

typedef enum {
	E_RACCOON_DDS_MENU_DEACTIVE = 0,
	E_RACCOON_DDS_MENU_ENTERED,
	E_RACCOON_DDS_MENU_REDY_KEY,
	E_RACCOON_DDS_MENU_SUBMENU,
} raccoon_menu_state_t;

class raccoon_dds_menu {
public:
	raccoon_dds_menu();
	static raccoon_dds_menu *get_instance(void);

	void init(void);
	void loop(void);
	void handler(void);

private:
	bool run(void);
	void change_submenu(void);
	void display_current_setting(void);

	static raccoon_dds_menu *singleton;

	raccoon_dds_submenu **submenu_list;
	raccoon_dds_submenu *submenu_current;
	size_t submenu_nr;
	size_t submenu_idx;

	raccoon_menu_state_t state;
	raccoon_morse_keycode_t keycode;
	raccoon_dds_sw *sw_previous;
	unsigned long freq_previous;
};

#endif /* __RACCOON_DDS_MENU_H__ */
