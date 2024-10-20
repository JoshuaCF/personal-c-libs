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

int bufWriteCursorMoveToOrigin(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[H"); }
int bufWriteCursorMoveTo(char* out, size_t bufsz, unsigned int line, unsigned int col) { return snprintf(out, bufsz, "\033[%u;%uf", line, col); }
int bufWriteCursorMoveUp(char* out, size_t bufsz, unsigned int lines) { return snprintf(out, bufsz, "\033[%uA", lines); }
int bufWriteCursorMoveDown(char* out, size_t bufsz, unsigned int lines) { return snprintf(out, bufsz, "\033[%uB", lines); }
int bufWriteCursorMoveRight(char* out, size_t bufsz, unsigned int cols) { return snprintf(out, bufsz, "\033[%uC", cols); }
int bufWriteCursorMoveLeft(char* out, size_t bufsz, unsigned int cols) { return snprintf(out, bufsz, "\033[%uD", cols); }
int bufWriteCursorMoveDownToLeft(char* out, size_t bufsz, unsigned int lines) { return snprintf(out, bufsz, "\033[%uE", lines); }
int bufWriteCursorMoveUpToLeft(char* out, size_t bufsz, unsigned int lines) { return snprintf(out, bufsz, "\033[%uF", lines); }
int bufWriteCursorMoveToCol(char* out, size_t bufsz, unsigned int col) { return snprintf(out, bufsz, "\033[%uG", col); }

int bufWriteCursorGetPosition(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[6n"); }
int bufWriteCursorMoveOnceUpWithScroll(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033M"); }
int bufWriteCursorSavePosition(char* out, size_t bufsz) { return snprintf(out, bufsz, "\0337"); }
int bufWriteCursorRestorePosition(char* out, size_t bufsz) { return snprintf(out, bufsz, "\0338"); }

int bufWriteCursorSetVisible(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?25h"); }
int bufWriteCursorSetInvisible(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?25l"); }

int bufWriteDisplayEraseFromCursor(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[0J"); }
int bufWriteDisplayEraseToCursor(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[1J"); }
int bufWriteDisplayEraseAll(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[2J"); }
int bufWriteDisplayEraseSavedLines(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[3J"); } // I don't know what this does?
int bufWriteDisplayEraseLineFromCursor(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[0K"); }
int bufWriteDisplayEraseLineToCursor(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[1K"); }
int bufWriteDisplayEraseLine(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[2K"); }

int bufWriteDisplaySave(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?47h"); }
int bufWriteDisplayRestore(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?47l"); }

int bufWriteDisplayEnterAltBuffer(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?1049h"); }
int bufWriteDisplayLeaveAltBuffer(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[?1049l"); }

int bufWriteStyleResetModes(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[0m"); }
int bufWriteStyleSetBold(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[1m"); }
int bufWriteStyleResetBold(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[22m"); }
int bufWriteStyleSetDim(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[2m"); }
int bufWriteStyleResetDim(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[22m"); }
int bufWriteStyleSetItalics(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[3m"); }
int bufWriteStyleResetItalics(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[23m"); }
int bufWriteStyleSetUnderline(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[4m"); }
int bufWriteStyleResetUnderline(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[24m"); }
int bufWriteStyleSetBlinking(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[5m"); };
int bufWriteStyleResetBlinking(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[25m"); }
int bufWriteStyleSetInverse(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[7m"); }
int bufWriteStyleResetInverse(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[27m"); }
int bufWriteStyleSetHidden(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[8m"); }
int bufWriteStyleResetHidden(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[28m"); }
int bufWriteStyleSetStrikethrough(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[9m"); }
int bufWriteStyleResetStrikethrough(char* out, size_t bufsz) { return snprintf(out, bufsz, "\033[29m"); }
int bufWriteStyleSetColor(char* out, size_t bufsz, enum TermColorStyle style) {
	return snprintf(out, bufsz, "\033[%sm", getStyleString(style));
}
int bufWriteStyleSetForegroundRGB(char* out, size_t bufsz, unsigned char r, unsigned char g, unsigned char b) {
	return snprintf(out, bufsz, "\033[38;2;%hhu;%hhu;%hhum", r, g, b);
}
int bufWriteStyleSetBackgroundRGB(char* out, size_t bufsz, unsigned char r, unsigned char g, unsigned char b) {
	return snprintf(out, bufsz, "\033[48;2;%hhu;%hhu;%hhum", r, g, b);
}
