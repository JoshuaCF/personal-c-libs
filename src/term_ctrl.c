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


int cursorMoveToOrigin(FILE* stream) { return fprintf(stream, "\e[H"); }
int cursorMoveTo(unsigned int line, unsigned int col, FILE* stream) { return fprintf(stream, "\e[%u;%uf", line, col); }
int cursorMoveUp(unsigned int lines, FILE* stream) { return fprintf(stream, "\e[%uA", lines); }
int cursorMoveDown(unsigned int lines, FILE* stream) { return fprintf(stream, "\e[%uB", lines); }
int cursorMoveRight(unsigned int cols, FILE* stream) { return fprintf(stream, "\e[%uC", cols); }
int cursorMoveLeft(unsigned int cols, FILE* stream) { return fprintf(stream, "\e[%uD", cols); }
int cursorMoveDownToLeft(unsigned int lines, FILE* stream) { return fprintf(stream, "\e[%uE", lines); }
int cursorMoveUpToLeft(unsigned int lines, FILE* stream) { return fprintf(stream, "\e[%uF", lines); }
int cursorMoveToCol(unsigned int col, FILE* stream) { return fprintf(stream, "\e[%uG", col); }

// struct CursorPos cursorGetPosition();
int cursorMoveOnceUpWithScroll(FILE* stream) { return fprintf(stream, "\eM"); }
int cursorSavePosition(FILE* stream) { return fprintf(stream, "\e7"); }
int cursorRestorePosition(FILE* stream) { return fprintf(stream, "\e8"); }

int cursorSetVisible(bool visible, FILE* stream) { return fprintf(stream, "\e[?25%c", visible ? 'h' : 'l'); }

int displayEraseFromCursor(FILE* stream) { return fprintf(stream, "\e[0J"); }
int displayEraseToCursor(FILE* stream) { return fprintf(stream, "\e[1J"); }
int displayEraseAll(FILE* stream) { return fprintf(stream, "\e[2J"); }
int displayEraseSavedLines(FILE* stream) { return fprintf(stream, "\e[3J"); } // I don't know what this does?
int displayEraseLineFromCursor(FILE* stream) { return fprintf(stream, "\e[0K"); }
int displayEraseLineToCursor(FILE* stream) { return fprintf(stream, "\e[1K"); }
int displayEraseLine(FILE* stream) { return fprintf(stream, "\e[2K"); }

int displaySave(FILE* stream) { return fprintf(stream, "\e[?47h"); }
int displayRestore(FILE* stream) { return fprintf(stream, "\e[?47l"); }

int displayEnterAltBuffer(FILE* stream) { return fprintf(stream, "\e[?1049h"); }
int displayLeaveAltBuffer(FILE* stream) { return fprintf(stream, "\e[?1049l"); }

int styleResetModes(FILE* stream) { return fprintf(stream, "\e[0m"); }
int styleSetBold(FILE* stream) { return fprintf(stream, "\e[1m"); }
int styleResetBold(FILE* stream) { return fprintf(stream, "\e[22m"); }
int styleSetDim(FILE* stream) { return fprintf(stream, "\e[2m"); }
int styleResetDim(FILE* stream) { return fprintf(stream, "\e[22m"); }
int styleSetItalics(FILE* stream) { return fprintf(stream, "\e[3m"); }
int styleResetItalics(FILE* stream) { return fprintf(stream, "\e[23m"); }
int styleSetUnderline(FILE* stream) { return fprintf(stream, "\e[4m"); }
int styleResetUnderlin(FILE* stream) { return fprintf(stream, "\e[24m"); }
int styleSetBlinking(FILE* stream) { return fprintf(stream, "\e[5m"); };
int styleResetBlinking(FILE* stream) { return fprintf(stream, "\e[25m"); }
int styleSetInverse(FILE* stream) { return fprintf(stream, "\e[7m"); }
int styleResetInverse(FILE* stream) { return fprintf(stream, "\e[27m"); }
int styleSetHidden(FILE* stream) { return fprintf(stream, "\e[8m"); }
int styleResetHidden(FILE* stream) { return fprintf(stream, "\e[28m"); }
int styleSetStrikethrough(FILE* stream) { return fprintf(stream, "\e[9m"); }
int styleResetStrikethrough(FILE* stream) { return fprintf(stream, "\e[29m"); }
int styleSetForegroundRGB(unsigned char r, unsigned char g, unsigned char b, FILE* stream) {
	return fprintf(stream, "\e[38;2;%hhu;%hhu;%hhum", r, g, b);
}
int styleSetBackgroundRGB(unsigned char r, unsigned char g, unsigned char b, FILE* stream) {
	return fprintf(stream, "\e[48;2;%hhu;%hhu;%hhum", r, g, b);
}


int sCursorMoveToOrigin(char* out) { return sprintf(out, "\e[H"); }
int sCursorMoveTo(unsigned int line, unsigned int col, char* out) { return sprintf(out, "\e[%u;%uf", line, col); }
int sCursorMoveUp(unsigned int lines, char* out) { return sprintf(out, "\e[%uA", lines); }
int sCursorMoveDown(unsigned int lines, char* out) { return sprintf(out, "\e[%uB", lines); }
int sCursorMoveRight(unsigned int cols, char* out) { return sprintf(out, "\e[%uC", cols); }
int sCursorMoveLeft(unsigned int cols, char* out) { return sprintf(out, "\e[%uD", cols); }
int sCursorMoveDownToLeft(unsigned int lines, char* out) { return sprintf(out, "\e[%uE", lines); }
int sCursorMoveUpToLeft(unsigned int lines, char* out) { return sprintf(out, "\e[%uF", lines); }
int sCursorMoveToCol(unsigned int col, char* out) { return sprintf(out, "\e[%uG", col); }

// struct CursorPos cursorGetPosition();
int sCursorMoveOnceUpWithScroll(char* out) { return sprintf(out, "\eM"); }
int sCursorSavePosition(char* out) { return sprintf(out, "\e7"); }
int sCursorRestorePosition(char* out) { return sprintf(out, "\e8"); }

int sCursorSetVisible(bool visible, char* out) { return sprintf(out, "\e[?25%c", visible ? 'h' : 'l'); }

int sDisplayEraseFromCursor(char* out) { return sprintf(out, "\e[0J"); }
int sDisplayEraseToCursor(char* out) { return sprintf(out, "\e[1J"); }
int sDisplayEraseAll(char* out) { return sprintf(out, "\e[2J"); }
int sDisplayEraseSavedLines(char* out) { return sprintf(out, "\e[3J"); } // I don't know what this does?
int sDisplayEraseLineFromCursor(char* out) { return sprintf(out, "\e[0K"); }
int sDisplayEraseLineToCursor(char* out) { return sprintf(out, "\e[1K"); }
int sDisplayEraseLine(char* out) { return sprintf(out, "\e[2K"); }

int sDisplaySave(char* out) { return sprintf(out, "\e[?47h"); }
int sDisplayRestore(char* out) { return sprintf(out, "\e[?47l"); }

int sDisplayEnterAltBuffer(char* out) { return sprintf(out, "\e[?1049h"); }
int sDisplayLeaveAltBuffer(char* out) { return sprintf(out, "\e[?1049l"); }

int sStyleResetModes(char* out) { return sprintf(out, "\e[0m"); }
int sStyleSetBold(char* out) { return sprintf(out, "\e[1m"); }
int sStyleResetBold(char* out) { return sprintf(out, "\e[22m"); }
int sStyleSetDim(char* out) { return sprintf(out, "\e[2m"); }
int sStyleResetDim(char* out) { return sprintf(out, "\e[22m"); }
int sStyleSetItalics(char* out) { return sprintf(out, "\e[3m"); }
int sStyleResetItalics(char* out) { return sprintf(out, "\e[23m"); }
int sStyleSetUnderline(char* out) { return sprintf(out, "\e[4m"); }
int sStyleResetUnderlin(char* out) { return sprintf(out, "\e[24m"); }
int sStyleSetBlinking(char* out) { return sprintf(out, "\e[5m"); };
int sStyleResetBlinking(char* out) { return sprintf(out, "\e[25m"); }
int sStyleSetInverse(char* out) { return sprintf(out, "\e[7m"); }
int sStyleResetInverse(char* out) { return sprintf(out, "\e[27m"); }
int sStyleSetHidden(char* out) { return sprintf(out, "\e[8m"); }
int sStyleResetHidden(char* out) { return sprintf(out, "\e[28m"); }
int sStyleSetStrikethrough(char* out) { return sprintf(out, "\e[9m"); }
int sStyleResetStrikethrough(char* out) { return sprintf(out, "\e[29m"); }
int sStyleSetForegroundRGB(unsigned char r, unsigned char g, unsigned char b, char* out) {
	return sprintf(out, "\e[38;2;%hhu;%hhu;%hhum", r, g, b);
}
int sStyleSetBackgroundRGB(unsigned char r, unsigned char g, unsigned char b, char* out) {
	return sprintf(out, "\e[48;2;%hhu;%hhu;%hhum", r, g, b);
}
