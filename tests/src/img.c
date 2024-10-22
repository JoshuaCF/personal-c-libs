#include <stdio.h>

#include "img.h"
#include "term_ctrl.h"

int main() {
	struct TermCtrlQueue queue = TermCtrlQueue_new(stdout);
	queueTermCtrlCursorMoveToOrigin(&queue);
	queueTermCtrlDisplayEraseAll(&queue);
	TermCtrlQueue_exec(&queue);

	struct Image img = Image_new(21, 21);

	for (size_t y = 0; y < 21; y++) {
		unsigned char g = (char)((float)(y)/(20.0) * 255);
		for (size_t x = 0; x < 21; x++) {
			unsigned char r = (char)((float)(x)/(20.0) * 255);
			struct Pixel* cur_pixel = Image_getPixel(&img, x, y);
			cur_pixel->col.r = r;
			cur_pixel->col.g = g;
			cur_pixel->col.b = 100;
			cur_pixel->transparency = 0;
		}
	}

	Image_draw(&img, stdout);
	queueTermCtrlCursorMoveTo(&queue, 5, 30);
	TermCtrlQueue_exec(&queue);
	Image_draw(&img, stdout);
	queueTermCtrlCursorMoveTo(&queue, 8, 19);
	TermCtrlQueue_exec(&queue);
	Image_draw(&img, stdout);

	Image_free(&img);
}
