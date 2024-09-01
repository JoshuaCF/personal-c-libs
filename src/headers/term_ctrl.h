#pragma once

#include <stdbool.h>
#include <stdio.h>

enum TermColorStyle {
	STYLE_FG_BLACK,
	STYLE_FG_RED,
	STYLE_FG_GREEN,
	STYLE_FG_YELLOW,
	STYLE_FG_BLUE,
	STYLE_FG_MAGENTA,
	STYLE_FG_CYAN,
	STYLE_FG_WHITE,
	STYLE_FG_DEFAULT,

	STYLE_BG_BLACK,
	STYLE_BG_RED,
	STYLE_BG_GREEN,
	STYLE_BG_YELLOW,
	STYLE_BG_BLUE,
	STYLE_BG_MAGENTA,
	STYLE_BG_CYAN,
	STYLE_BG_WHITE,
	STYLE_BG_DEFAULT,

	STYLE_RESET,
};

int cursorMoveToOrigin(FILE* stream);
int cursorMoveTo(unsigned int line, unsigned int col, FILE* stream);
int cursorMoveUp(unsigned int lines, FILE* stream);
int cursorMoveDown(unsigned int lines, FILE* stream);
int cursorMoveRight(unsigned int cols, FILE* stream);
int cursorMoveLeft(unsigned int cols, FILE* stream);
int cursorMoveDownToLeft(unsigned int lines, FILE* stream);
int cursorMoveUpToLeft(unsigned int lines, FILE* stream);
int cursorMoveToCol(unsigned int col, FILE* stream);

// struct CursorPos cursorGetPosition();
int cursorMoveOnceUpWithScroll(FILE* stream);
int cursorSavePosition(FILE* stream);
int cursorRestorePosition(FILE* stream);

int cursorSetVisible(bool visible, FILE* stream);

int displayEraseFromCursor(FILE* stream);
int displayEraseToCursor(FILE* stream);
int displayEraseAll(FILE* stream);
int displayEraseSavedLines(FILE* stream);
int displayEraseLineFromCursor(FILE* stream);
int displayEraseLineToCursor(FILE* stream);
int displayEraseLine(FILE* stream);

int displaySave(FILE* stream);
int displayRestore(FILE* stream);

int displayEnterAltBuffer(FILE* stream);
int displayLeaveAltBuffer(FILE* stream);

// int styleSetModes(FILE* stream);
int styleResetModes(FILE* stream);
int styleSetBold(FILE* stream);
int styleResetBold(FILE* stream);
int styleSetDim(FILE* stream);
int styleResetDim(FILE* stream);
int styleSetItalics(FILE* stream);
int styleResetItalics(FILE* stream);
int styleSetUnderline(FILE* stream);
int styleResetUnderlin(FILE* stream);
int styleSetBlinking(FILE* stream);
int styleResetBlinking(FILE* stream);
int styleSetInverse(FILE* stream);
int styleResetInverse(FILE* stream);
int styleSetHidden(FILE* stream);
int styleResetHidden(FILE* stream);
int styleSetStrikethrough(FILE* stream);
int styleResetStrikethrough(FILE* stream);
int styleSetForegroundRGB(unsigned char r, unsigned char g, unsigned char b, FILE* stream);
int styleSetBackgroundRGB(unsigned char r, unsigned char g, unsigned char b, FILE* stream);


int sCursorMoveToOrigin(char* out);
int sCursorMoveTo(unsigned int line, unsigned int col, char* out);
int sCursorMoveUp(unsigned int lines, char* out);
int sCursorMoveDown(unsigned int lines, char* out);
int sCursorMoveRight(unsigned int cols, char* out);
int sCursorMoveLeft(unsigned int cols, char* out);
int sCursorMoveDownToLeft(unsigned int lines, char* out);
int sCursorMoveUpToLeft(unsigned int lines, char* out);
int sCursorMoveToCol(unsigned int col, char* out);

// struct CursorPos cursorGetPosition();
int sCursorMoveOnceUpWithScroll(char* out);
int sCursorSavePosition(char* out);
int sCursorRestorePosition(char* out);

int sCursorSetVisible(bool visible, char* out);

int sDisplayEraseFromCursor(char* out);
int sDisplayEraseToCursor(char* out);
int sDisplayEraseAll(char* out);
int sDisplayEraseSavedLines(char* out);
int sDisplayEraseLineFromCursor(char* out);
int sDisplayEraseLineToCursor(char* out);
int sDisplayEraseLine(char* out);

int sDisplaySave(char* out);
int sDisplayRestore(char* out);

int sDisplayEnterAltBuffer(char* out);
int sDisplayLeaveAltBuffer(char* out);

int sStyleResetModes(char* out);
int sStyleSetBold(char* out);
int sStyleResetBold(char* out);
int sStyleSetDim(char* out);
int sStyleResetDim(char* out);
int sStyleSetItalics(char* out);
int sStyleResetItalics(char* out);
int sStyleSetUnderline(char* out);
int sStyleResetUnderlin(char* out);
int sStyleSetBlinking(char* out);
int sStyleResetBlinking(char* out);
int sStyleSetInverse(char* out);
int sStyleResetInverse(char* out);
int sStyleSetHidden(char* out);
int sStyleResetHidden(char* out);
int sStyleSetStrikethrough(char* out);
int sStyleResetStrikethrough(char* out);
int sStyleSetForegroundRGB(unsigned char r, unsigned char g, unsigned char b, char* out);
int sStyleSetBackgroundRGB(unsigned char r, unsigned char g, unsigned char b, char* out);
