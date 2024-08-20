#pragma once

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

void cursorMoveToOrigin();
void cursorMoveTo(unsigned int line, unsigned int col);
void cursorMoveUp(unsigned int lines);
void cursorMoveDown(unsigned int lines);
void cursorMoveRight(unsigned int cols);
void cursorMoveLeft(unsigned int cols);
void cursorMoveDownToLeft(unsigned int lines);
void cursorMoveUpToLeft(unsigned int lines);
void cursorMoveToCol(unsigned int col);

// struct CursorPos cursorGetPosition();
void cursorMoveOnceUpWithScroll();
void cursorSavePosition();
void cursorRestorePosition();

void cursorSetVisible(bool visible);

void displayEraseFromCursor();
void displayEraseToCursor();
void displayEraseAll();
void displayEraseSavedLines();
void displayEraseLineFromCursor();
void displayEraseLineToCursor();
void displayEraseLine();

void displaySave();
void displayRestore();

void displayEnterAltBuffer();
void displayLeaveAltBuffer();
