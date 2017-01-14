#include "big_text.h"
#include "../../dix/dix.h"

typedef struct {
	font_t *font;
	char *string;
} big_text_data_t;

int lookup(UINT *table, char value) {
	int i;

	for(i = 0; table[i] != 0; i++) {
		if(table[i] == value) {
			return i;
		}
	}

	return -1;
}

void render_big_text(view_t *view, render_buf_t *out) {
	big_text_data_t *data;
	UINT x, y, max_x, max_y, width, width_max, ix, iy;
	char *str, *ch;
	int postion;


	data = view_get_data(view);
	max_x = min(view->width + view->x, out->width);
	max_y = min(view->height + view->y, out->height);
	x = view->x;
	y = view->y;

	if(data->string == NULL || data->font == NULL) {
		return;
	}

	str = data->string;

	while(*str != '\0' && x < max_x) {
		postion = lookup(data->font->lookup, *str);
		if(postion != -1) {
			ch = data->font->characters[postion];

			for(iy = y, width_max = 0; iy < max_y && *ch != '\0'; iy++) {
				width = 0;
				for(ix = x; ix < max_x && *ch != '\n' && *ch != '\0'; ix++, width++) {
					out->buff[ix + iy * out->width] = *(ch++);
				}

				if(*ch == '\n') {
					ch++;
				}

				if(width > width_max) {
					width_max = width;
				}
			}

			x += width_max;
		}
		str++;
	}
}

void destroy_big_text(void *data) {
	if(((big_text_data_t *) data)->string != NULL) {
		free(((big_text_data_t *) data)->string);
	}

	free(data);
}

view_t *create_big_text_view(UINT x, UINT y, UINT width, UINT height) {
	view_t *view;

	view = create_view(x, y, width, height);
	view_set_data(view, calloc(1, sizeof(big_text_data_t)));
	view_set_destroy_function(view, destroy_big_text);
	view_set_render_function(view, render_big_text);

	return view;
}

void big_text_set_font(view_t *view, font_t *font) {
	big_text_data_t *data;

	data = view_get_data(view);
	data->font = font;
}

void big_text_set_text(view_t *view, char *text) {
	big_text_data_t *data;

	data = view_get_data(view);
	if(data->string != NULL) {
		free(data->string);
	}

	if(text != NULL) {
		data->string = malloc((strlen(text) + 1) * sizeof *data->string);
		strcpy(data->string, text);
	}
	else {
		data->string = NULL;
	}
}