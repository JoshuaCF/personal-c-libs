#pragma once

// A library designed simply to format and write ANSI escape sequences to a buffer
// Functionality intentionally kept simple and scope narrow -- meant to be used to
// build more advanced controls.
//
// Based off of the information here:
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

#include "term_color_defs.h"

int bufWriteCursorMoveToOrigin(char* out);
int bufWriteCursorMoveTo(char* out, unsigned int line, unsigned int col);
int bufWriteCursorMoveUp(char* out, unsigned int lines);
int bufWriteCursorMoveDown(char* out, unsigned int lines);
int bufWriteCursorMoveRight(char* out, unsigned int cols);
int bufWriteCursorMoveLeft(char* out, unsigned int cols);
int bufWriteCursorMoveDownToLeft(char* out, unsigned int lines);
int bufWriteCursorMoveUpToLeft(char* out, unsigned int lines);
int bufWriteCursorMoveToCol(char* out, unsigned int col);

int bufWriteCursorGetPosition(char* out);
int bufWriteCursorMoveOnceUpWithScroll(char* out);
int bufWriteCursorSavePosition(char* out);
int bufWriteCursorRestorePosition(char* out);

int bufWriteCursorSetVisible(char* out);
int bufWriteCursorSetInvisible(char* out);

int bufWriteDisplayEraseFromCursor(char* out);
int bufWriteDisplayEraseToCursor(char* out);
int bufWriteDisplayEraseAll(char* out);
int bufWriteDisplayEraseSavedLines(char* out); // I don't know what this does?
int bufWriteDisplayEraseLineFromCursor(char* out);
int bufWriteDisplayEraseLineToCursor(char* out);
int bufWriteDisplayEraseLine(char* out);

int bufWriteDisplaySave(char* out);
int bufWriteDisplayRestore(char* out);

int bufWriteDisplayEnterAltBuffer(char* out);
int bufWriteDisplayLeaveAltBuffer(char* out);

int bufWriteStyleResetModes(char* out);
int bufWriteStyleSetBold(char* out);
int bufWriteStyleResetBold(char* out);
int bufWriteStyleSetDim(char* out);
int bufWriteStyleResetDim(char* out);
int bufWriteStyleSetItalics(char* out);
int bufWriteStyleResetItalics(char* out);
int bufWriteStyleSetUnderline(char* out);
int bufWriteStyleResetUnderline(char* out);
int bufWriteStyleSetBlinking(char* out);;
int bufWriteStyleResetBlinking(char* out);
int bufWriteStyleSetInverse(char* out);
int bufWriteStyleResetInverse(char* out);
int bufWriteStyleSetHidden(char* out);
int bufWriteStyleResetHidden(char* out);
int bufWriteStyleSetStrikethrough(char* out);
int bufWriteStyleResetStrikethrough(char* out);
int bufWriteStyleSetColor(char* out, enum TermColorStyle style);
int bufWriteStyleSetForegroundRGB(char* out, unsigned char r, unsigned char g, unsigned char b);
int bufWriteStyleSetBackgroundRGB(char* out, unsigned char r, unsigned char g, unsigned char b);
