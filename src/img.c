#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
void writeImageCharacter(struct ImageCharacter c) {
	printf("\e[0m"); // reset
	if (c.topHidden && c.bottomHidden) {
		printf(" ");
	} else if (c.bottomHidden) {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.topColor.r, c.topColor.g, c.topColor.b);	
		printf("▀");
	} else if (c.topHidden) {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		printf("▄");
	} else {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.topColor.r, c.topColor.g, c.topColor.b);	
		printf("\e[48;2;%hhu;%hhu;%hhum", c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		printf("▀");
	}
}

void Image_draw(struct Image* img) {
	printf("\n");
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
			writeImageCharacter(imgChar);
		}
		printf("\e[0m\n");
	}
}

void Image_free(struct Image* img) {
	free(img->data);
}
