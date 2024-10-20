#pragma once


// POSIX/Windows agnostic functions for controlling the terminal
// Includes things such as cursor positioning, colors, input options,
// window title, etc..
//
// A small bit of setup still needs to be OS specific. In Linux, a
// FILE* for which terminal to write to is needed. In Windows, a
// HANDLE is required instead. These will be `typedef`'d under `Terminal`
// and this header provides no OS agnostic way of getting the needed
// FILE*/HANDLE, as it could come from nearly anywhere and is out of
// the scope of this lib.
//
// Depending on whether or not WINDOWS is defined, term_ctrl.c will
// use primarily virtual terminal sequences (and some POSIX stdlib
// stuff) or entirely Win32 calls (requires Windows SDK, of course)
// Win32 calls are used in favor of virtual terminal sequences for 
// performance. Windows Terminal parses the sequences quite slowly.
//
// Actions can be executed in one of two ways: directly with an
// associated function call, or batched into a `TermCtrlQueue` to run
// as a group. The latter method is preferred when many actions are
// performed, as it allows optimizations to be made.

#include <stdint.h>
#include <stdio.h>

#include "term_color_defs.h"
#include "queue.h"

#ifndef WINDOWS
typedef FILE* Terminal;
#else
typedef HANDLE Terminal;
#endif

struct TermCtrlQueue {
	Terminal term;
	struct Queue action_queue;
};

struct TermCtrlQueue TermCtrlQueue_new(Terminal term);
void TermCtrlQueue_exec(struct TermCtrlQueue* queue);
void TermCtrlQueue_free(struct TermCtrlQueue* queue);

void doTermCtrlWrite(Terminal term, char* str);

void doTermCtrlStyleSetColor(Terminal term, enum TermColorStyle style);
void doTermCtrlStyleSetForegroundRGB(Terminal term, uint8_t r, uint8_t g, uint8_t b);
void doTermCtrlStyleSetBackgroundRGB(Terminal term, uint8_t r, uint8_t g, uint8_t b);

void queueTermCtrlWrite(struct TermCtrlQueue* queue, char* str);

void queueTermCtrlStyleSetColor(struct TermCtrlQueue* queue, enum TermColorStyle style);
void queueTermCtrlStyleSetForegroundRGB(struct TermCtrlQueue* queue, uint8_t r, uint8_t g, uint8_t b);
void queueTermCtrlStyleSetBackgroundRGB(struct TermCtrlQueue* queue, uint8_t r, uint8_t g, uint8_t b);
