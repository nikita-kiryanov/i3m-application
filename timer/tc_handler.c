/*
 * tc_handler.c
 *
 *  Created on: Oct 13, 2015
 *      Author: arkadi
 */

#include "tc-handler.h"

#define MENU_SHOW_TIME		1500
#define SLEEP_TIME			5000

void tc_handle()
{
	if (tc_counter % 50 == 0)
		update_adc();
	if (tc_counter == MENU_SHOW_TIME && !present_menu->visible)
		gfx_action_menu_init(present_menu, true);
	else if (tc_counter == SLEEP_TIME)
		show_splash();
}