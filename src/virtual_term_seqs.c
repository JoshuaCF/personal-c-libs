#include <stdio.h>

#include "virtual_term_seqs.h"

// Color codes for terminal colors
const char * FG_DEFAULT = "39";
const char * BG_DEFAULT = "49";
const char * RESET = "0";

const char * FG_BLACK = "30";
const char * FG_RED = "31";
const char * FG_GREEN = "32";
const char * FG_YELLOW = "33";
const char * FG_BLUE = "34";
const char * FG_MAGENTA = "35";
const char * FG_CYAN = "36";
const char * FG_WHITE = "37";

const char * BG_BLACK = "40";
const char * BG_RED = "41";
const char * BG_GREEN = "42";
const char * BG_YELLOW = "43";
const char * BG_BLUE = "44";
const char * BG_MAGENTA = "45";
const char * BG_CYAN = "46";
const char * BG_WHITE = "47";

const char * FG_BRIGHT_BLACK = "90";
const char * FG_BRIGHT_RED = "91";
const char * FG_BRIGHT_GREEN = "92";
const char * FG_BRIGHT_YELLOW = "93";
const char * FG_BRIGHT_BLUE = "94";
const char * FG_BRIGHT_MAGENTA = "95";
const char * FG_BRIGHT_CYAN = "96";
const char * FG_BRIGHT_WHITE = "97";

const char * BG_BRIGHT_BLACK = "100";
const char * BG_BRIGHT_RED = "101";
const char * BG_BRIGHT_GREEN = "102";
const char * BG_BRIGHT_YELLOW = "103";
const char * BG_BRIGHT_BLUE = "104";
const char * BG_BRIGHT_MAGENTA = "105";
const char * BG_BRIGHT_CYAN = "106";
const char * BG_BRIGHT_WHITE = "107";

static const char * getStyleString(enum TermColorStyle style) {
	switch(style) {
		case STYLE_FG_DEFAULT:
			return FG_DEFAULT;
		case STYLE_BG_DEFAULT:
			return BG_DEFAULT;
		case STYLE_RESET:
			return RESET;

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

		case STYLE_FG_BRIGHT_BLACK:
			return FG_BRIGHT_BLACK;
		case STYLE_FG_BRIGHT_RED:
			return FG_BRIGHT_RED;
		case STYLE_FG_BRIGHT_GREEN:
			return FG_BRIGHT_GREEN;
		case STYLE_FG_BRIGHT_YELLOW:
			return FG_BRIGHT_YELLOW;
		case STYLE_FG_BRIGHT_BLUE:
			return FG_BRIGHT_BLUE;
		case STYLE_FG_BRIGHT_MAGENTA:
			return FG_BRIGHT_MAGENTA;
		case STYLE_FG_BRIGHT_CYAN:
			return FG_BRIGHT_CYAN;
		case STYLE_FG_BRIGHT_WHITE:
			return FG_BRIGHT_WHITE;

		case STYLE_BG_BRIGHT_BLACK:
			return BG_BRIGHT_BLACK;
		case STYLE_BG_BRIGHT_RED:
			return BG_BRIGHT_RED;
		case STYLE_BG_BRIGHT_GREEN:
			return BG_BRIGHT_GREEN;
		case STYLE_BG_BRIGHT_YELLOW:
			return BG_BRIGHT_YELLOW;
		case STYLE_BG_BRIGHT_BLUE:
			return BG_BRIGHT_BLUE;
		case STYLE_BG_BRIGHT_MAGENTA:
			return BG_BRIGHT_MAGENTA;
		case STYLE_BG_BRIGHT_CYAN:
			return BG_BRIGHT_CYAN;
		case STYLE_BG_BRIGHT_WHITE:
			return BG_BRIGHT_WHITE;
	}
}

int bufWriteCursorMoveToOrigin(char* out) { return sprintf(out, "\033[H"); }
int bufWriteCursorMoveTo(char* out, unsigned int line, unsigned int col) { return sprintf(out, "\033[%u;%uf", line, col); }
int bufWriteCursorMoveUp(char* out, unsigned int lines) { return sprintf(out, "\033[%uA", lines); }
int bufWriteCursorMoveDown(char* out, unsigned int lines) { return sprintf(out, "\033[%uB", lines); }
int bufWriteCursorMoveRight(char* out, unsigned int cols) { return sprintf(out, "\033[%uC", cols); }
int bufWriteCursorMoveLeft(char* out, unsigned int cols) { return sprintf(out, "\033[%uD", cols); }
int bufWriteCursorMoveDownToLeft(char* out, unsigned int lines) { return sprintf(out, "\033[%uE", lines); }
int bufWriteCursorMoveUpToLeft(char* out, unsigned int lines) { return sprintf(out, "\033[%uF", lines); }
int bufWriteCursorMoveToCol(char* out, unsigned int col) { return sprintf(out, "\033[%uG", col); }

int bufWriteCursorGetPosition(char* out) { return sprintf(out, "\033[6n"); }
int bufWriteCursorMoveOnceUpWithScroll(char* out) { return sprintf(out, "\033M"); }
int bufWriteCursorSavePosition(char* out) { return sprintf(out, "\0337"); }
int bufWriteCursorRestorePosition(char* out) { return sprintf(out, "\0338"); }

int bufWriteCursorSetVisible(char* out) { return sprintf(out, "\033[?25h"); }
int bufWriteCursorSetInvisible(char* out) { return sprintf(out, "\033[?25l"); }

int bufWriteDisplayEraseFromCursor(char* out) { return sprintf(out, "\033[0J"); }
int bufWriteDisplayEraseToCursor(char* out) { return sprintf(out, "\033[1J"); }
int bufWriteDisplayEraseAll(char* out) { return sprintf(out, "\033[2J"); }
int bufWriteDisplayEraseSavedLines(char* out) { return sprintf(out, "\033[3J"); } // I don't know what this does?
int bufWriteDisplayEraseLineFromCursor(char* out) { return sprintf(out, "\033[0K"); }
int bufWriteDisplayEraseLineToCursor(char* out) { return sprintf(out, "\033[1K"); }
int bufWriteDisplayEraseLine(char* out) { return sprintf(out, "\033[2K"); }

int bufWriteDisplaySave(char* out) { return sprintf(out, "\033[?47h"); }
int bufWriteDisplayRestore(char* out) { return sprintf(out, "\033[?47l"); }

int bufWriteDisplayEnterAltBuffer(char* out) { return sprintf(out, "\033[?1049h"); }
int bufWriteDisplayLeaveAltBuffer(char* out) { return sprintf(out, "\033[?1049l"); }

int bufWriteStyleResetModes(char* out) { return sprintf(out, "\033[0m"); }
int bufWriteStyleSetBold(char* out) { return sprintf(out, "\033[1m"); }
int bufWriteStyleResetBold(char* out) { return sprintf(out, "\033[22m"); }
int bufWriteStyleSetDim(char* out) { return sprintf(out, "\033[2m"); }
int bufWriteStyleResetDim(char* out) { return sprintf(out, "\033[22m"); }
int bufWriteStyleSetItalics(char* out) { return sprintf(out, "\033[3m"); }
int bufWriteStyleResetItalics(char* out) { return sprintf(out, "\033[23m"); }
int bufWriteStyleSetUnderline(char* out) { return sprintf(out, "\033[4m"); }
int bufWriteStyleResetUnderlin(char* out) { return sprintf(out, "\033[24m"); }
int bufWriteStyleSetBlinking(char* out) { return sprintf(out, "\033[5m"); };
int bufWriteStyleResetBlinking(char* out) { return sprintf(out, "\033[25m"); }
int bufWriteStyleSetInverse(char* out) { return sprintf(out, "\033[7m"); }
int bufWriteStyleResetInverse(char* out) { return sprintf(out, "\033[27m"); }
int bufWriteStyleSetHidden(char* out) { return sprintf(out, "\033[8m"); }
int bufWriteStyleResetHidden(char* out) { return sprintf(out, "\033[28m"); }
int bufWriteStyleSetStrikethrough(char* out) { return sprintf(out, "\033[9m"); }
int bufWriteStyleResetStrikethrough(char* out) { return sprintf(out, "\033[29m"); }
int bufWriteStyleSetColor(char* out, enum TermColorStyle style) {
	return sprintf(out, "\033[%sm", getStyleString(style));
}
int bufWriteStyleSetForegroundRGB(char* out, unsigned char r, unsigned char g, unsigned char b) {
	return sprintf(out, "\033[38;2;%hhu;%hhu;%hhum", r, g, b);
}
int bufWriteStyleSetBackgroundRGB(char* out, unsigned char r, unsigned char g, unsigned char b) {
	return sprintf(out, "\033[48;2;%hhu;%hhu;%hhum", r, g, b);
}
