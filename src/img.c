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
int writeImageCharacter(struct ImageCharacter c, char* buf) {
	char* start = buf;
	buf += sStyleResetModes(buf);
	if (c.topHidden && c.bottomHidden) {
		buf += sprintf(buf, " ");
	} else if (c.bottomHidden) {
		buf += sStyleSetForegroundRGB(c.topColor.r, c.topColor.g, c.topColor.b, buf);
		buf += sprintf(buf, "▀");
	} else if (c.topHidden) {
		buf += sStyleSetForegroundRGB(c.bottomColor.r, c.bottomColor.g, c.bottomColor.b, buf);
		buf += sprintf(buf, "▄");
	} else {
		buf += sStyleSetForegroundRGB(c.topColor.r, c.topColor.g, c.topColor.b, buf);
		buf += sStyleSetBackgroundRGB(c.bottomColor.r, c.bottomColor.g, c.bottomColor.b, buf);
		buf += sprintf(buf, "▀");
	}
	return buf-start;
}

void Image_draw(struct Image* img) {
	char buf[4096];
	char* write_pos = buf;

	flockfile(stdout);
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
			write_pos += writeImageCharacter(imgChar, write_pos);
			if (write_pos - buf < 256) {
				printf("%s", buf);
				write_pos = buf;
			}
		}
		write_pos += sStyleResetModes(write_pos);
		write_pos += sCursorMoveLeft(img->width, write_pos);
		write_pos += sCursorMoveDown(1, write_pos);
	}
	if (write_pos != buf)
		printf("%s", buf);
	funlockfile(stdout);
}

void Image_free(struct Image* img) {
	free(img->data);
}
