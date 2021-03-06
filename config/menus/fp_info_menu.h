/*
 * fp_info_menu.h
 *
 *  Created on: Sep 27, 2015
 *      Author: arkadi
 */

#ifndef FP_INFO_MENU_H
#define FP_INFO_MENU_H
#include "config/cnf_blk_components.h"
#include "config/fonts.h"
#include "menus_id.h"

char __attribute__((section (".configData"))) airtop_info_menu_title[] = "Information";
char __attribute__((section (".configData"))) mac1_title_progmem[] = "LAN1";
char __attribute__((section (".configData"))) mac2_title_progmem[] = "LAN2";
char __attribute__((section (".configData"))) app_version_title_progmem[] = "I3M Version";
char __attribute__((section (".configData"))) production_codes_title_progmem[] = "Part/Serial #";
char __attribute__((section (".configData"))) mac_address_title_progmem[] = "MAC Addresses";
char __attribute__((section (".configData"))) airtop_info_go_back_to_main_progmem[] = "Back";

struct gfx_mono_menu  __attribute__((section (".configData"))) airtop_info_menu = {
	.title = airtop_info_menu_title,
	.strings[0] = mac_address_title_progmem,
	.strings[1] = production_codes_title_progmem,
	.strings[2] = app_version_title_progmem,
	.strings[3] = airtop_info_go_back_to_main_progmem,
	.num_elements = 4,
	.current_selection = 0
};

struct cnf_info_node __attribute__((section (".configData"))) serial_number_info = {
	.info = {
		.info_type = SHOW_SERIAL_NUMBER,
		.information = 20,
		.x = 0,
		.y = 36,
		.max_length = 40
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0
};

struct cnf_info_node __attribute__((section (".configData"))) part_number_info = {
	.info = {
		.info_type = SHOW_PART_NUMBER,
		.x = 1,
		.y = 0,
		.max_length = 90
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = &serial_number_info
};

struct cnf_info_node __attribute__((section (".configData"))) app_version1_info = {
	.info = {
		.info_type = SHOW_APP_VERSION,
		.information = 1,
		.x = 1,
		.y = 15,
		.max_length = 15
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0,
};

struct cnf_info_node __attribute__((section (".configData"))) app_version0_info = {
	.info = {
		.info_type = SHOW_APP_VERSION,
		.information = 0,
		.x = 1,
		.y = 5,
		.max_length = 15
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = &app_version1_info,
};

struct cnf_info_node __attribute__((section (".configData"))) mac2_address_info = {
	.info = {
			.info_type = SHOW_MAC_ADDRESS,
			.information = 1,
			.x = 0,
			.y = 30,
			.max_length = 22
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0
};

struct cnf_label_node __attribute__((section (".configData"))) mac2_title = {
	.label = {
		.text = mac2_title_progmem,
		.x = 0,
		.y = 20,
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0
};

struct cnf_label_node __attribute__((section (".configData"))) mac1_title = {
	.label = {
		.text = mac1_title_progmem,
		.x = 0,
		.y = 0,
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = &mac2_title,
};

struct cnf_label_node __attribute__((section (".configData"))) app_version_title = {
	.label = {
		.text = app_version_title_progmem,
		.x = (128 - 5 * 11) / 2,
		.y = 54,
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0
};

struct cnf_frame __attribute__((section (".configData"))) app_version_frame = {
	.labels_head = &app_version_title,
	.infos_head = &app_version0_info,
	.images_head = 0
};

struct cnf_info_node __attribute__((section (".configData"))) mac_address_info = {
	.info = {
		.info_type = SHOW_MAC_ADDRESS,
		.information = 0,
		.x = 0,
		.y = 10,
		.max_length = 22
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = &mac2_address_info,
};

struct cnf_label_node __attribute__((section (".configData"))) production_codes_title = {
	.label = {
		.text = production_codes_title_progmem,
		.x = (128 - 5 * 13) / 2,
		.y = 54,
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = 0
};

struct cnf_label_node __attribute__((section (".configData"))) mac_address_title = {
	.label = {
		.text = mac_address_title_progmem,
		.x = (128 - 5 * 13) / 2,
		.y = 54,
	},
	.font_id = GLCD_FONT_SYSFONT_5X7,
	.next = &mac1_title,
};

struct cnf_frame __attribute__((section (".configData"))) production_codes_frame = {
	.labels_head = &production_codes_title,
	.infos_head = &part_number_info,
	.images_head = 0
};

struct cnf_frame __attribute__((section (".configData"))) mac_address_frame = {
	.labels_head = &mac_address_title,
	.infos_head = &mac_address_info,
	.images_head = 0
};

struct cnf_action_node __attribute__((section (".configData"))) info_menu_go_back_action = {
	.action = {
		.type = ACTION_TYPE_SHOW_MENU,
		.menu_id = MAIN_MENU_ID
	},
	.next = 0
};

struct cnf_action_node __attribute__((section (".configData"))) app_version_action = {
	.action = {
		.type = ACTION_TYPE_SHOW_FRAME,
		.frame = &app_version_frame
	},
	.next = &info_menu_go_back_action
};

struct cnf_action_node __attribute__((section (".configData"))) production_codes_action = {
	.action = {
		.type = ACTION_TYPE_SHOW_FRAME,
		.frame = &production_codes_frame
	},
	.next = &app_version_action
};

struct cnf_action_node __attribute__((section (".configData"))) mac_address_action = {
	.action = {
		.type = ACTION_TYPE_SHOW_FRAME,
		.frame = &mac_address_frame
	},
	.next = &production_codes_action
};

struct cnf_image_node  __attribute__((section (".configData"))) info_back_to_main_menu_image = {
	.image = {
		.bitmap_progmem = back_bits,
		.width = logo_width,
		.height = logo_height
	},
	.next = 0
};

struct cnf_image_node  __attribute__((section (".configData"))) app_version_image = {
	.image = {
		.bitmap_progmem = app_version_bits,
		.width = logo_width,
		.height = logo_height
	},
	.next = &info_back_to_main_menu_image
};

struct cnf_image_node  __attribute__((section (".configData"))) info_part_number_image = {
	.image = {
		.bitmap_progmem = part_number_bits,
		.width = logo_width,
		.height = logo_height
	},
	.next = &app_version_image
};

struct cnf_image_node  __attribute__((section (".configData"))) info_mac_address_image = {
	.image = {
		.bitmap_progmem = mac_bits,
		.width = logo_width,
		.height = logo_height
	},
	.next = &info_part_number_image
};

struct cnf_menu   __attribute__((section (".configData"))) airtop_info_menu_cnf = {
	.menu = &airtop_info_menu,
	.actions_head = &mac_address_action,
	.id = AIRTOP_INFORMATION_MENU_ID,
	.images_items_head = &info_mac_address_image
};

#endif /* FP_INFO_MENU_H */
