/*
 * def.h
 *
 *  Created on: Oct 13, 2015
 *      Author: arkadi
 */

#ifndef DEF_H_
#define DEF_H_

enum information_type {
	SET_BRIGHTNESS,
	SET_SCREEN_SAVER_ENABLE,
	SET_SCREEN_SAVER_TIME,
	SET_SCREEN_SAVER_TYPE,
	SET_SCREEN_SAVER_TIME_UNIT,
	SHOW_SERIAL_NUMBER,
	SHOW_APP_VERSION,
	SHOW_PART_NUMBER,
	SHOW_MAC_ADDRESS,
	SHOW_POWER_STATE,
	SHOW_COMPUTER_POWER,
	SHOW_CPU_FREQUENCY,
	SHOW_HDD_SIZE,
	SHOW_MEMORY_SIZE,
	SHOW_HDD_TEMPERTURE,
	SHOW_CPU_TEMPERTURE,
	SHOW_GPU_TEMPERTURE,
	SHOW_AMBIENT_TEMPERATURE,
	SET_BOIS_STATE,
	SHOW_POST_CODE,
	SHOW_RTC_HOUR,
	SHOW_RTC_MIN,
	SHOW_RTC_SEC,
	SHOW_RTC_YEAR,
	SHOW_RTC_MONTH,
	SHOW_RTC_DAY,
};

enum frame_type {
	FRAME_REGULAR,
	FRAME_DASHBOARD,
};

enum action_type {
	ACTION_TYPE_NONE,
	ACTION_TYPE_SHOW_MENU,
	ACTION_TYPE_SHOW_DMI_MENU,
	ACTION_TYPE_SHOW_FRAME,
	ACTION_TYPE_SET_BIOS_STATE
};

enum power_state {
	POWER_OFF = 0x00,
	POWER_STD = 0x01,
	POWER_STR = 0x03,
	POWER_ON = 0x07,
};

enum screen_saver_time_unit {
	SCREEN_SAVER_SECOND_UNIT = 0X00,
	SCREEN_SAVER_MINUTE_UNIT = 0X01,
	SCREEN_SAVER_HOUR_UNIT = 0X02,
};

enum display_state {
	DISPLAY_MENU,
	DISPLAY_FRAME,
	DISPLAY_ACTION_FRAME,
	DISPLAY_LOGO,
	DISPLAY_DASHBOARD,
	DISPLAY_DIM,
	DISPLAY_CLOCK,
};


#endif /* DEF_H_ */
