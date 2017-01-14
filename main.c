#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "dix/dix.h"
#include "dix_modules/big_text/big_text.h"
#include "big.h"

int main(void) {
	view_t *text;
	char text_time[9];
	SYSTEMTIME something;

	init_dix();

	set_screen_size(52, 6);
	set_screen_title(L"%TIME%");

	text = create_big_text_view(0, 0, 52, 6);
	big_text_set_font(text, &big_font);

	attach_to_screen(text);

	while(!kbhit()) {
		GetLocalTime(&something);
		sprintf(text_time, "%02u:%02u:%02u", something.wHour, something.wMinute, something.wSecond);
		big_text_set_text(text, text_time);
		render(SCREEN);
		Sleep(1000);
	}

	deinit_dix();
	return EXIT_SUCCESS;
}