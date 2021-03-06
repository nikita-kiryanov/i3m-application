/*
 * gfx_text.c
 *
 * Created: 11-Apr-17 10:37:52 PM
 *  Author: Nikita
 */

#include "gfx_text.h"
#include "display/glcd-0.5.2/glcd_font.h"
#include <stdbool.h>

void gfx_text_init(struct gfx_text *text, char *str, uint8_t max_text_size, uint8_t font_id)
{
	text->text = str;
	text->font = get_font_by_type(font_id);
	text->max_text_size = max_text_size;
}