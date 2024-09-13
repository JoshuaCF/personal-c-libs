#include <stdio.h>
#include <stdlib.h>

#include "img.h"
#include "term_ctrl.h"

int main() {
	cursorMoveToOrigin(stdout);
	displayEraseAll(stdout);

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

	Image_draw(&img);
	cursorMoveTo(5, 30, stdout);
	Image_draw(&img);
	cursorMoveTo(8, 19, stdout);
	Image_draw(&img);

	Image_free(&img);
}
