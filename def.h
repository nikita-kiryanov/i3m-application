/*
 * def.h
 *
 *  Created on: Oct 13, 2015
 *      Author: arkadi
 */

#ifndef DEF_H_
#define DEF_H_

enum information_type{
	SET_BRIGHTNESS,
	SHOW_SERIAL_NUMBER,
	SHOW_PART_NUMBER,
	SHOW_MAC_ADDRESS,
	SHOW_POWER_STATE,
	SHOW_POWER,
	SHOW_CPU_FREQUENCY,
	SHOW_HDD_SIZE,
	SHOW_MEMORY_SIZE,
	SHOW_HDD_TEMPERTURE,
	SHOW_CPU_TEMPERTURE,
	SHOW_GPU_TEMPERTURE,
	SHOW_AMBIENT_TEMPERATURE,
	SHOW_POST_CODE
};

enum action_type {
	ACTION_TYPE_NONE,
	ACTION_TYPE_SHOW_MENU,
	ACTION_TYPE_SHOW_DMI_MENU,
	ACTION_TYPE_SHOW_FRAME,
	ACTION_TYPE_SET_BIOS_STATE
};

enum power_state{
	POWER_OFF = 0x00,
	POWER_STD = 0x01,
	POWER_STR = 0x03,
	POWER_ON = 0x07,
};


#endif /* DEF_H_ */
