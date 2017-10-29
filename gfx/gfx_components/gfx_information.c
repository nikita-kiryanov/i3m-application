/*
 * gfx_information.c
 *
 * Created: 3/27/2017 3:40:46 PM
 *  Author: Nikita
 */

#include "gfx_information.h"
#include "gfx_item.h"
#include "gfx/gfx_components/gfx_graphic_menu.h"
#include "display/display_render.h"
#include "screens/screens.h"
#include "work-queue/work.h"

void gfx_information_draw_string(struct gfx_information *info)
{
	info->to_string(info, info->text.text);
	draw_string_in_buffer(info->text.text, info->postion.x, info->postion.y, info->text.font);
}

static void sprintf_sprintf(struct gfx_information *info, char *output_str)
{
	sprintf(output_str, info->text.text);
}

static bool information_is_valid(struct gfx_information *info)
{
	return true;
}

static int gfx_information_init_generic(struct gfx_information *info, enum information_type info_type,
										uint8_t info_data, uint8_t max_length, uint8_t x, uint8_t y, uint8_t font_id)
{
	gfx_item_init(&info->postion, x, y, 0, 0);
	char *text = malloc_locked(max_length);
	if (text == NULL)
		return -1;

	gfx_text_init(&info->text, text, max_length, false, font_id);
	info->info_type = info_type;
	info->metadata = info_data;
	info->to_string = sprintf_sprintf;
	info->draw_data = gfx_information_draw_string;
	info->draw_controls = NULL;
	info->handle_buttons = NULL;
	info->is_valid = information_is_valid;

	return 0;
}

static int gfx_information_init_type(struct gfx_information *info, enum information_type info_type)
{
	switch(info_type) {
	case SET_BRIGHTNESS:
		return gfx_information_init_set_brightness(info);
	case SET_SCREEN_SAVER_ENABLE:
		return gfx_information_init_set_screen_saver_enable(info);
	case SET_SCREEN_SAVER_TIME:
		return gfx_information_init_set_screen_saver_time(info);
	case SET_SCREEN_SAVER_TYPE:
		return gfx_information_init_set_screen_saver_type(info);
	case SHOW_SERIAL_NUMBER:
		return gfx_information_init_show_serial_number(info);
	case SHOW_APP_VERSION:
		return gfx_information_init_show_app_version(info);
	case SHOW_PART_NUMBER:
		return gfx_information_init_show_part_number(info);
	case SHOW_MAC_ADDRESS:
		return gfx_information_init_show_mac_address(info);
	case SHOW_POWER_STATE:
		return gfx_information_init_show_power_state(info);
	case SHOW_COMPUTER_POWER:
		return gfx_information_init_show_power_data(info);
	case SHOW_CPU_FREQUENCY:
		return gfx_information_init_show_cpu_freq(info);
	case SHOW_HDD_SIZE:
		return gfx_information_init_show_hdd_size(info);
	case SHOW_MEMORY_SIZE:
		return gfx_information_init_show_memory_size(info);
	case SHOW_HDD_TEMPERTURE:
		return gfx_information_init_show_hdd_temp(info);
	case SHOW_CPU_TEMPERTURE:
		return gfx_information_init_show_cpu_temp(info);
	case SHOW_GPU_TEMPERTURE:
		return gfx_information_init_show_gpu_temp(info);
	case SHOW_AMBIENT_TEMPERATURE:
		return gfx_information_init_show_ambient_temp(info);
	case SHOW_POST_CODE:
		return gfx_information_init_show_post_code(info);
	case SHOW_RTC_HOUR:
		return gfx_information_init_show_rtc_hour(info);
	case SHOW_RTC_MIN:
		return gfx_information_init_show_rtc_min(info);
	case SHOW_RTC_SEC:
		return gfx_information_init_show_rtc_sec(info);
	case SHOW_USB_SERIAL_INPUT://TODO:THIS IS TEMPORARY, KILL THIS WHEN NO LONGER NEEDED
		//info->to_string = set_usb_serial_string;
		return 0;
	default:
		return -1;
	}
};

//TODO: for some reason font_id is part of cnf_info_node, instead of cnf_info.
//Fix this later.
int gfx_information_init(struct gfx_information *info, struct cnf_info *cnf_info, uint8_t font_id)
{
	int retval = gfx_information_init_generic(info,
											  cnf_info->info_type,
											  cnf_info->information,
											  cnf_info->max_length,
											  cnf_info->x,
											  cnf_info->y,
											  font_id);
	if (retval)
		return -1;

	return gfx_information_init_type(info, cnf_info->info_type);
}
