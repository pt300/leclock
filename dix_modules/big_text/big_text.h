#ifndef BIG_TEXT_H
#define BIG_TEXT_H

#include "../../dix/dix.h"

typedef struct {
	unsigned int *lookup;
	char **characters;
} font_t;

view_t *create_big_text_view(UINT x, UINT y, UINT width, UINT height);
void big_text_set_font(view_t *view, font_t *font);
void big_text_set_text(view_t *view, char *text);

#endif //BIG_TEXT_H
