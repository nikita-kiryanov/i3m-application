/*
 * gpu.c
 *
 * Created: 3/21/2017 2:01:28 PM
 *  Author: Nikita
 */

#include "screens/string_formats.h"
#include "gfx/gfx_components/gfx_information.h"
#include "sensors.h"
#include <string.h>

static void sprintf_gpu_temp(struct gfx_information *info, char *output_str)
{
	if (computer_data.details.gpu_temp_set)
		sprintf_temperature(output_str, computer_data.details.gpu_temp);
	else
		sprintf_inval_data(output_str);
}

int gfx_information_init_show_gpu_temp(struct gfx_information *info)
{
	info->to_string = sprintf_gpu_temp;
	return 0;
}
