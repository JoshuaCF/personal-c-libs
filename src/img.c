#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "term_ctrl.h"
#include "img.h"


struct Image Image_new(size_t width, size_t height) {
	struct Image img;
	img.width = width;
	img.height = height;
	img.data = malloc(width * height * sizeof(struct Pixel));
	return img;
}

struct Pixel* Image_getPixel(struct Image* img, size_t x, size_t y) {
	return &img->data[y*img->width + x];
}

struct ImageCharacter {
	bool topHidden, bottomHidden;
	struct Color topColor, bottomColor;
};
void writeImageCharacter(struct ImageCharacter c, struct TermCtrlQueue* queue) {
	queueTermCtrlStyleResetModes(queue);
	if (c.topHidden && c.bottomHidden) {
		queueTermCtrlWriteChar(queue, ' ');
	} else if (c.bottomHidden) {
		queueTermCtrlStyleSetForegroundRGB(queue, c.topColor.r, c.topColor.g, c.topColor.b);
		queueTermCtrlWriteString(queue, "▀");
	} else if (c.topHidden) {
		queueTermCtrlStyleSetForegroundRGB(queue, c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		queueTermCtrlWriteString(queue, "▄");
	} else {
		queueTermCtrlStyleSetForegroundRGB(queue, c.topColor.r, c.topColor.g, c.topColor.b);
		queueTermCtrlStyleSetBackgroundRGB(queue, c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		queueTermCtrlWriteString(queue, "▀");
	}
}

void Image_draw(struct Image* img, Terminal term) {
	struct TermCtrlQueue queue = TermCtrlQueue_new(term);

	for (size_t y = 0; y < img->height; y += 2) {
		for (size_t x = 0; x < img->width; x++) {
			struct ImageCharacter imgChar;
			imgChar.topHidden = true;
			imgChar.bottomHidden = true;

			struct Pixel* curPixelTop = Image_getPixel(img, x, y);

			if (curPixelTop->transparency == 0) {
				imgChar.topHidden = false;
				imgChar.topColor = curPixelTop->col;
			}
			
			if (y+1 < img->height) {
				struct Pixel* curPixelBottom = Image_getPixel(img, x, y+1);
				if (curPixelBottom->transparency == 0) {
					imgChar.bottomHidden = false;
					imgChar.bottomColor = curPixelBottom->col;
				}
			}
			writeImageCharacter(imgChar, &queue);
		}
		queueTermCtrlStyleResetModes(&queue);
		queueTermCtrlCursorMoveLeft(&queue, img->width);
		queueTermCtrlCursorMoveDown(&queue, 1);
	}

	TermCtrlQueue_exec(&queue);
	TermCtrlQueue_free(&queue);
}

void Image_free(struct Image* img) {
	free(img->data);
}
