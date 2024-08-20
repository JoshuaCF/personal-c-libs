#include <stdbool.h>
#include <stdio.h>

#include "term_ctrl.h"

const char * FG_BLACK = "30";
const char * FG_RED = "31";
const char * FG_GREEN = "32";
const char * FG_YELLOW = "33";
const char * FG_BLUE = "34";
const char * FG_MAGENTA = "35";
const char * FG_CYAN = "36";
const char * FG_WHITE = "37";
const char * FG_DEFAULT = "39";

const char * BG_BLACK = "40";
const char * BG_RED = "41";
const char * BG_GREEN = "42";
const char * BG_YELLOW = "43";
const char * BG_BLUE = "44";
const char * BG_MAGENTA = "45";
const char * BG_CYAN = "46";
const char * BG_WHITE = "47";
const char * BG_DEFAULT = "49";

const char * RESET = "0";

const char * getStyleString(enum TermColorStyle style) {
	switch(style) {
		case STYLE_FG_BLACK:
			return FG_BLACK;
		case STYLE_FG_RED:
			return FG_RED;
		case STYLE_FG_GREEN:
			return FG_GREEN;
		case STYLE_FG_YELLOW:
			return FG_YELLOW;
		case STYLE_FG_BLUE:
			return FG_BLUE;
		case STYLE_FG_MAGENTA:
			return FG_MAGENTA;
		case STYLE_FG_CYAN:
			return FG_CYAN;
		case STYLE_FG_WHITE:
			return FG_WHITE;
		case STYLE_FG_DEFAULT:
			return FG_DEFAULT;

		case STYLE_BG_BLACK:
			return BG_BLACK;
		case STYLE_BG_RED:
			return BG_RED;
		case STYLE_BG_GREEN:
			return BG_GREEN;
		case STYLE_BG_YELLOW:
			return BG_YELLOW;
		case STYLE_BG_BLUE:
			return BG_BLUE;
		case STYLE_BG_MAGENTA:
			return BG_MAGENTA;
		case STYLE_BG_CYAN:
			return BG_CYAN;
		case STYLE_BG_WHITE:
			return BG_WHITE;
		case STYLE_BG_DEFAULT:
			return BG_DEFAULT;

		case STYLE_RESET:
			return RESET;
	}
}


void cursorMoveToOrigin() { printf("\e[H"); }
void cursorMoveTo(unsigned int line, unsigned int col) { printf("\e[%u;%uf", line, col); }
void cursorMoveUp(unsigned int lines) { printf("\e[%uA", lines); }
void cursorMoveDown(unsigned int lines) { printf("\e[%uB", lines); }
void cursorMoveRight(unsigned int cols) { printf("\e[%uC", cols); }
void cursorMoveLeft(unsigned int cols) { printf("\e[%uD", cols); }
void cursorMoveDownToLeft(unsigned int lines) { printf("\e[%uE", lines); }
void cursorMoveUpToLeft(unsigned int lines) { printf("\e[%uF", lines); }
void cursorMoveToCol(unsigned int col) { printf("\e[%uG", col); }

// struct CursorPos cursorGetPosition();
void cursorMoveOnceUpWithScroll() { printf("\e M"); }
void cursorSavePosition() { printf("\e 7"); }
void cursorRestorePosition() { printf("\e 8"); }

void cursorSetVisible(bool visible) { printf("\e[?25%c", visible ? 'h' : 'l'); }

void displayEraseFromCursor() { printf("\e[0J"); }
void displayEraseToCursor() { printf("\e[1J"); }
void displayEraseAll() { printf("\e[2J"); }
void displayEraseSavedLines() { printf("\e[3J"); } // I don't know what this does?
void displayEraseLineFromCursor() { printf("\e[0K"); }
void displayEraseLineToCursor() { printf("\e[1K"); }
void displayEraseLine() { printf("\e[2K"); }

void displaySave() { printf("\e[?47h"); }
void displayRestore() { printf("\e[?47l"); }

void displayEnterAltBuffer() { printf("\e[?1049h"); }
void displayLeaveAltBuffer() { printf("\e[?1049l"); }

void styleSetModes() {} // TODO: Need a struct or something as input to this
void styleResetModes() { printf("\e[0m"); }
void styleSetBold() { printf("\e[1m"); }
void styleResetBold() { printf("\e[22m"); }
void styleSetDim() { printf("\e[2m"); }
void styleResetDim() { printf("\e[22m"); }
void styleSetItalics() { printf("\e[3m"); }
void styleResetItalics() { printf("\e[23m"); }
void styleSetUnderline() { printf("\e[4m"); }
void styleResetUnderlin() { printf("\e[24m"); }
void styleSetBlinking() { printf("\e[5"); };
void styleResetBlinking() { printf("\e[25"); }
void styleSetInverse() { printf("\e[7"); }
void styleResetInverse() { printf("\e[27"); }
void styleSetHidden() { printf("\e[8"); }
void styleResetHidden() { printf("\e[28m"); }
void styleSetStrikethrough() { printf("\e[9m"); }
void styleResetStrikethrough() { printf("\e[29m"); }
void styleSetForegroundRGB(unsigned char r, unsigned char g, unsigned char b) {
	printf("\e[38;2;%hhu;%hhu;%hhum", r, g, b);
}
void styleSetBackgroundRGB(unsigned char r, unsigned char g, unsigned char b) {
	printf("\e[48;2;%hhu;%hhu;%hhum", r, g, b);
}
