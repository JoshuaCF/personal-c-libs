#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "term_color_defs.h"

#ifndef WINDOWS
#include "virtual_term_seqs.h"
#else
#include "Windows.h"
#endif

#include "term_ctrl.h"

enum CtrlType {
	CTRL_WRITE_STRING,
	CTRL_WRITE_CHAR,

	CTRL_CURSOR_MOVE_TO_ORIGIN,
	CTRL_CURSOR_MOVE_TO,
	CTRL_CURSOR_MOVE_UP,
	CTRL_CURSOR_MOVE_DOWN,
	CTRL_CURSOR_MOVE_RIGHT,
	CTRL_CURSOR_MOVE_LEFT,
	CTRL_CURSOR_MOVE_DOWN_TO_LEFT,
	CTRL_CURSOR_MOVE_UP_TO_LEFT,
	CTRL_CURSOR_MOVE_TO_COL,

	CTRL_CURSOR_GET_POSITION,
	CTRL_CURSOR_MOVE_ONCE_UP_WITH_SCROLL,
	CTRL_CURSOR_SAVE_POSITION,
	CTRL_CURSOR_RESTORE_POSITION,

	CTRL_CURSOR_SET_VISIBLE,
	CTRL_CURSOR_SET_INVISIBLE,

	CTRL_DISPLAY_ERASE_FROM_CURSOR,
	CTRL_DISPLAY_ERASE_TO_CURSOR,
	CTRL_DISPLAY_ERASE_ALL,
	CTRL_DISPLAY_ERASE_SAVED_LINES,
	CTRL_DISPLAY_ERASE_LINE_FROM_CURSOR,
	CTRL_DISPLAY_ERASE_LINE_TO_CURSOR,
	CTRL_DISPLAY_ERASE_LINE,

	CTRL_DISPLAY_SAVE,
	CTRL_DISPLAY_RESTORE,

	CTRL_DISPLAY_ENTER_ALT_BUFFER,
	CTRL_DISPLAY_LEAVE_ALT_BUFFER,

	CTRL_STYLE_RESET_MODES,
	CTRL_STYLE_SET_BOLD,
	CTRL_STYLE_RESET_BOLD,
	CTRL_STYLE_SET_DIM,
	CTRL_STYLE_RESET_DIM,
	CTRL_STYLE_SET_ITALICS,
	CTRL_STYLE_RESET_ITALICS,
	CTRL_STYLE_SET_UNDERLINE,
	CTRL_STYLE_RESET_UNDERLINE,
	CTRL_STYLE_SET_BLINKING,
	CTRL_STYLE_RESET_BLINKING,
	CTRL_STYLE_SET_INVERSE,
	CTRL_STYLE_RESET_INVERSE,
	CTRL_STYLE_SET_HIDDEN,
	CTRL_STYLE_RESET_HIDDEN,
	CTRL_STYLE_SET_STRIKETHROUGH,
	CTRL_STYLE_RESET_STRIKETHROUGH,
	CTRL_STYLE_SET_COLOR,
	CTRL_STYLE_SET_FOREGROUND_RGB,
	CTRL_STYLE_SET_BACKGROUND_RGB,
};

// ARG STRUCTS
struct CtrlWriteStringArgs {
	char* str; // Owned! Will be copied into
};
struct CtrlWriteStringArgs* CtrlWriteStringArgs_new(const char* str) {
	struct CtrlWriteStringArgs* args = malloc(sizeof(struct CtrlWriteStringArgs));

	args->str = malloc(strlen(str) + 1);
	strcpy(args->str, str);

	return args;
}
static void CtrlWriteStringArgs_free(struct CtrlWriteStringArgs* args) {
	free(args->str);
}

struct CtrlWriteCharArgs {
	char c;
};
struct CtrlWriteCharArgs* CtrlWriteCharArgs_new(char c) {
	struct CtrlWriteCharArgs* args = malloc(sizeof(struct CtrlWriteCharArgs));
	args->c = c;
	
	return args;
}

struct CtrlCursorMoveToArgs {
	unsigned int line;
	unsigned int col;
};
struct CtrlCursorMoveToArgs* CtrlCursorMoveToArgs_new(unsigned int line, unsigned int col) {
	struct CtrlCursorMoveToArgs* args = malloc(sizeof(struct CtrlCursorMoveToArgs));
	args->line = line;
	args->col = col;

	return args;
}

struct CtrlCursorMoveUpArgs {
	unsigned int lines;
};
struct CtrlCursorMoveUpArgs* CtrlCursorMoveUpArgs_new(unsigned int lines) {
	struct CtrlCursorMoveUpArgs* args = malloc(sizeof(struct CtrlCursorMoveUpArgs));
	args->lines = lines;

	return args;
}

struct CtrlCursorMoveDownArgs {
	unsigned int lines;
};
struct CtrlCursorMoveDownArgs* CtrlCursorMoveDownArgs_new(unsigned int lines) {
	struct CtrlCursorMoveDownArgs* args = malloc(sizeof(struct CtrlCursorMoveDownArgs));
	args->lines = lines;

	return args;
}

struct CtrlCursorMoveRightArgs {
	unsigned int cols;
};
struct CtrlCursorMoveRightArgs* CtrlCursorMoveRightArgs_new(unsigned int cols) {
	struct CtrlCursorMoveRightArgs* args = malloc(sizeof(struct CtrlCursorMoveRightArgs));
	args->cols = cols;

	return args;
}

struct CtrlCursorMoveLeftArgs {
	unsigned int cols;
};
struct CtrlCursorMoveLeftArgs* CtrlCursorMoveLeftArgs_new(unsigned int cols) {
	struct CtrlCursorMoveLeftArgs* args = malloc(sizeof(struct CtrlCursorMoveLeftArgs));
	args->cols = cols;

	return args;
}

struct CtrlCursorMoveDownToLeftArgs {
	unsigned int lines;
};
struct CtrlCursorMoveDownToLeftArgs* CtrlCursorMoveDownToLeftArgs_new(unsigned int lines) {
	struct CtrlCursorMoveDownToLeftArgs* args = malloc(sizeof(struct CtrlCursorMoveDownToLeftArgs));
	args->lines = lines;

	return args;
}

struct CtrlCursorMoveUpToLeftArgs {
	unsigned int lines;
};
struct CtrlCursorMoveUpToLeftArgs* CtrlCursorMoveUpToLeftArgs_new(unsigned int lines) {
	struct CtrlCursorMoveUpToLeftArgs* args = malloc(sizeof(struct CtrlCursorMoveUpToLeftArgs));
	args->lines = lines;

	return args;
}

struct CtrlCursorMoveToColArgs {
	unsigned int col;
};
struct CtrlCursorMoveToColArgs* CtrlCursorMoveToColArgs_new(unsigned int col) {
	struct CtrlCursorMoveToColArgs* args = malloc(sizeof(struct CtrlCursorMoveToColArgs));
	args->col = col;

	return args;
}

struct CtrlStyleSetColorArgs {
	enum TermColorStyle style;
};
struct CtrlStyleSetColorArgs* CtrlStyleSetColorArgs_new(enum TermColorStyle style) {
	struct CtrlStyleSetColorArgs* args = malloc(sizeof(struct CtrlStyleSetColorArgs));
	args->style = style;

	return args;
}

struct CtrlStyleSetForegroundRGBArgs {
	uint8_t r, g, b;
};
struct CtrlStyleSetForegroundRGBArgs* CtrlStyleSetForegroundRGBArgs_new(uint8_t r, uint8_t g, uint8_t b) {
	struct CtrlStyleSetForegroundRGBArgs* args = malloc(sizeof(struct CtrlStyleSetForegroundRGBArgs));
	args->r = r;
	args->g = g;
	args->b = b;

	return args;
}

struct CtrlStyleSetBackgroundRGBArgs {
	uint8_t r, g, b;
};
struct CtrlStyleSetBackgroundRGBArgs* CtrlStyleSetBackgroundRGBArgs_new(uint8_t r, uint8_t g, uint8_t b) {
	struct CtrlStyleSetBackgroundRGBArgs* args = malloc(sizeof(struct CtrlStyleSetBackgroundRGBArgs));
	args->r = r;
	args->g = g;
	args->b = b;

	return args;
}

struct Ctrl {
	enum CtrlType type;
	void* args;
};

static void Ctrl_free(struct Ctrl* ctrl) {
	switch (ctrl->type) {
		// Args require freeing
		case CTRL_WRITE_STRING:
			CtrlWriteStringArgs_free(ctrl->args);
			break;
		// No special free behavior needed
		case CTRL_WRITE_CHAR:

		case CTRL_CURSOR_MOVE_TO_ORIGIN:
		case CTRL_CURSOR_MOVE_TO:
		case CTRL_CURSOR_MOVE_UP:
		case CTRL_CURSOR_MOVE_DOWN:
		case CTRL_CURSOR_MOVE_RIGHT:
		case CTRL_CURSOR_MOVE_LEFT:
		case CTRL_CURSOR_MOVE_DOWN_TO_LEFT:
		case CTRL_CURSOR_MOVE_UP_TO_LEFT:
		case CTRL_CURSOR_MOVE_TO_COL:

		case CTRL_CURSOR_GET_POSITION:
		case CTRL_CURSOR_MOVE_ONCE_UP_WITH_SCROLL:
		case CTRL_CURSOR_SAVE_POSITION:
		case CTRL_CURSOR_RESTORE_POSITION:

		case CTRL_CURSOR_SET_VISIBLE:
		case CTRL_CURSOR_SET_INVISIBLE:

		case CTRL_DISPLAY_ERASE_FROM_CURSOR:
		case CTRL_DISPLAY_ERASE_TO_CURSOR:
		case CTRL_DISPLAY_ERASE_ALL:
		case CTRL_DISPLAY_ERASE_SAVED_LINES:
		case CTRL_DISPLAY_ERASE_LINE_FROM_CURSOR:
		case CTRL_DISPLAY_ERASE_LINE_TO_CURSOR:
		case CTRL_DISPLAY_ERASE_LINE:

		case CTRL_DISPLAY_SAVE:
		case CTRL_DISPLAY_RESTORE:

		case CTRL_DISPLAY_ENTER_ALT_BUFFER:
		case CTRL_DISPLAY_LEAVE_ALT_BUFFER:

		case CTRL_STYLE_RESET_MODES:
		case CTRL_STYLE_SET_BOLD:
		case CTRL_STYLE_RESET_BOLD:
		case CTRL_STYLE_SET_DIM:
		case CTRL_STYLE_RESET_DIM:
		case CTRL_STYLE_SET_ITALICS:
		case CTRL_STYLE_RESET_ITALICS:
		case CTRL_STYLE_SET_UNDERLINE:
		case CTRL_STYLE_RESET_UNDERLINE:
		case CTRL_STYLE_SET_BLINKING:
		case CTRL_STYLE_RESET_BLINKING:
		case CTRL_STYLE_SET_INVERSE:
		case CTRL_STYLE_RESET_INVERSE:
		case CTRL_STYLE_SET_HIDDEN:
		case CTRL_STYLE_RESET_HIDDEN:
		case CTRL_STYLE_SET_STRIKETHROUGH:
		case CTRL_STYLE_RESET_STRIKETHROUGH:
		case CTRL_STYLE_SET_COLOR:
		case CTRL_STYLE_SET_FOREGROUND_RGB:
		case CTRL_STYLE_SET_BACKGROUND_RGB:
			break;
	}
	free(ctrl->args);
}

#ifndef WINDOWS
// Takes ownership of the structure and frees associated data
// NOTE: current implementation has an issue with order of execution.
// If several controls are executed in series, there is no indication
// in the return type that something required writing to the buffer or
// was executed immediately.
static int Ctrl_exec(struct Ctrl ctrl, char* buf, size_t bufsz) {
	int chars_written;

	switch (ctrl.type) {
		case CTRL_WRITE_STRING: {
			struct CtrlWriteStringArgs* args = ctrl.args;
			chars_written = snprintf(buf, bufsz, "%s", args->str);
			break;
		}
		case CTRL_WRITE_CHAR: {
			struct CtrlWriteCharArgs* args = ctrl.args;
			chars_written = 1;
			*buf = args->c;
			break;
		}

		case CTRL_CURSOR_MOVE_TO_ORIGIN: {
			chars_written = bufWriteCursorMoveToOrigin(buf, bufsz);
			break;
		}
		case CTRL_CURSOR_MOVE_TO: {
			struct CtrlCursorMoveToArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveTo(buf, bufsz, args->line, args->col);
			break;
		}
		case CTRL_CURSOR_MOVE_UP: {
			struct CtrlCursorMoveUpArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveUp(buf, bufsz, args->lines);
			break;
		}
		case CTRL_CURSOR_MOVE_DOWN: {
			struct CtrlCursorMoveDownArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveDown(buf, bufsz, args->lines);
			break;
		}
		case CTRL_CURSOR_MOVE_RIGHT: {
			struct CtrlCursorMoveRightArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveRight(buf, bufsz, args->cols);
				break;
		}
		case CTRL_CURSOR_MOVE_LEFT: {
			struct CtrlCursorMoveLeftArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveLeft(buf, bufsz, args->cols);
			break;
		}
		case CTRL_CURSOR_MOVE_DOWN_TO_LEFT: {
			struct CtrlCursorMoveDownToLeftArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveDownToLeft(buf, bufsz, args->lines);
			break;
		}
		case CTRL_CURSOR_MOVE_UP_TO_LEFT: {
			struct CtrlCursorMoveUpToLeftArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveUpToLeft(buf, bufsz, args->lines);
			break;
		}
		case CTRL_CURSOR_MOVE_TO_COL: {
			struct CtrlCursorMoveToColArgs* args = ctrl.args;
			chars_written = bufWriteCursorMoveToCol(buf, bufsz, args->col);
			break;
		}

		case CTRL_CURSOR_GET_POSITION: {
			chars_written = bufWriteCursorGetPosition(buf, bufsz);
			break;
		}
		case CTRL_CURSOR_MOVE_ONCE_UP_WITH_SCROLL: {
			chars_written = bufWriteCursorMoveOnceUpWithScroll(buf, bufsz);
			break;
		}
		case CTRL_CURSOR_SAVE_POSITION: {
			chars_written = bufWriteCursorSavePosition(buf, bufsz);
			break;
		}
		case CTRL_CURSOR_RESTORE_POSITION: {
			chars_written = bufWriteCursorRestorePosition(buf, bufsz);
			break;
		}

		case CTRL_CURSOR_SET_VISIBLE: {
			chars_written = bufWriteCursorSetVisible(buf, bufsz);
			break;
		}
		case CTRL_CURSOR_SET_INVISIBLE: {
			chars_written = bufWriteCursorSetInvisible(buf, bufsz);
			break;
		}

		case CTRL_DISPLAY_ERASE_FROM_CURSOR: {
			chars_written = bufWriteDisplayEraseFromCursor(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_TO_CURSOR: {
			chars_written = bufWriteDisplayEraseToCursor(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_ALL: {
			chars_written = bufWriteDisplayEraseAll(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_SAVED_LINES: {
			chars_written = bufWriteDisplayEraseSavedLines(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_LINE_FROM_CURSOR: {
			chars_written = bufWriteDisplayEraseLineFromCursor(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_LINE_TO_CURSOR: {
			chars_written = bufWriteDisplayEraseLineToCursor(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_ERASE_LINE: {
			chars_written = bufWriteDisplayEraseLine(buf, bufsz);
			break;
		}

		case CTRL_DISPLAY_SAVE: {
			chars_written = bufWriteDisplaySave(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_RESTORE: {
			chars_written = bufWriteDisplayRestore(buf, bufsz);
			break;
		}

		case CTRL_DISPLAY_ENTER_ALT_BUFFER: {
			chars_written = bufWriteDisplayEnterAltBuffer(buf, bufsz);
			break;
		}
		case CTRL_DISPLAY_LEAVE_ALT_BUFFER: {
			chars_written = bufWriteDisplayLeaveAltBuffer(buf, bufsz);
			break;
		}

		case CTRL_STYLE_RESET_MODES: {
			chars_written = bufWriteStyleResetModes(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_BOLD: {
			chars_written = bufWriteStyleSetBold(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_BOLD: {
			chars_written = bufWriteStyleResetBold(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_DIM: {
			chars_written = bufWriteStyleSetDim(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_DIM: {
			chars_written = bufWriteStyleResetDim(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_ITALICS: {
			chars_written = bufWriteStyleSetItalics(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_ITALICS: {
			chars_written = bufWriteStyleResetItalics(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_UNDERLINE: {
			chars_written = bufWriteStyleSetUnderline(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_UNDERLINE: {
			chars_written = bufWriteStyleResetUnderline(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_BLINKING: {
			chars_written = bufWriteStyleSetBlinking(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_BLINKING: {
			chars_written = bufWriteStyleResetBlinking(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_INVERSE: {
			chars_written = bufWriteStyleSetInverse(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_INVERSE: {
			chars_written = bufWriteStyleResetInverse(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_HIDDEN: {
			chars_written = bufWriteStyleSetHidden(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_HIDDEN: {
			chars_written = bufWriteStyleResetHidden(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_STRIKETHROUGH: {
			chars_written = bufWriteStyleSetStrikethrough(buf, bufsz);
			break;
		}
		case CTRL_STYLE_RESET_STRIKETHROUGH: {
			chars_written = bufWriteStyleResetStrikethrough(buf, bufsz);
			break;
		}
		case CTRL_STYLE_SET_COLOR: {
			struct CtrlStyleSetColorArgs* args = ctrl.args;
			chars_written = bufWriteStyleSetColor(buf, bufsz, args->style);
			break;
		}
		case CTRL_STYLE_SET_FOREGROUND_RGB: {
			struct CtrlStyleSetForegroundRGBArgs* args = ctrl.args;
			chars_written = bufWriteStyleSetForegroundRGB(buf, bufsz, args->r, args->g, args->b);
			break;
		}
		case CTRL_STYLE_SET_BACKGROUND_RGB: {
			struct CtrlStyleSetBackgroundRGBArgs* args = ctrl.args;
			chars_written = bufWriteStyleSetBackgroundRGB(buf, bufsz, args->r, args->g, args->b);
			break;
		}
	}

	Ctrl_free(&ctrl);
	return chars_written;
}
#else
#endif

struct TermCtrlQueue TermCtrlQueue_new(Terminal term) {
	struct TermCtrlQueue queue;
	queue.term = term;
	queue.action_queue = Queue_new(sizeof(struct Ctrl), 32);

	return queue;
}
void TermCtrlQueue_exec(struct TermCtrlQueue* queue) {
	struct Ctrl cur_ctrl;

#ifndef WINDOWS
#define WRITE_BUF_SIZE 8192
#define WRITE_THRESHOLD (WRITE_BUF_SIZE-2048)
	flockfile(queue->term);
	char write_buf[WRITE_BUF_SIZE];
	size_t write_offset = 0;
	while (Queue_next(&queue->action_queue, &cur_ctrl) == QUEUE_OK) {
		write_offset += Ctrl_exec(cur_ctrl, write_buf + write_offset, WRITE_BUF_SIZE - write_offset);
		if (write_offset >= WRITE_THRESHOLD) {
			fwrite(write_buf, 1, write_offset, queue->term);
			write_offset = 0;
		}
	}
	fwrite(write_buf, 1, write_offset, queue->term);
	funlockfile(queue->term);
#else
#endif
}
void TermCtrlQueue_free(struct TermCtrlQueue* queue) {
	struct Ctrl cur_ctrl;
	while (Queue_next(&queue->action_queue, &cur_ctrl) == QUEUE_OK) {
		Ctrl_free(&cur_ctrl);
	}

	Queue_free(&queue->action_queue);
	return;
}

// Queued controls
void queueTermCtrlWriteString(struct TermCtrlQueue* queue, char* str) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_WRITE_STRING;

	struct CtrlWriteStringArgs* args = CtrlWriteStringArgs_new(str);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}

void queueTermCtrlWriteChar(struct TermCtrlQueue* queue, char c) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_WRITE_CHAR;

	struct CtrlWriteCharArgs* args = CtrlWriteCharArgs_new(c);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}

void queueTermCtrlCursorMoveToOrigin(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_TO_ORIGIN;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveTo(struct TermCtrlQueue* queue, unsigned int line, unsigned int col) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_TO;

	struct CtrlCursorMoveToArgs* args = CtrlCursorMoveToArgs_new(line, col);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveUp(struct TermCtrlQueue* queue, unsigned int lines) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_UP;

	struct CtrlCursorMoveUpArgs* args = CtrlCursorMoveUpArgs_new(lines);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveDown(struct TermCtrlQueue* queue, unsigned int lines) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_DOWN;

	struct CtrlCursorMoveDownArgs* args = CtrlCursorMoveDownArgs_new(lines);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveRight(struct TermCtrlQueue* queue, unsigned int cols) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_RIGHT;

	struct CtrlCursorMoveRightArgs* args = CtrlCursorMoveRightArgs_new(cols);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveLeft(struct TermCtrlQueue* queue, unsigned int cols) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_LEFT;

	struct CtrlCursorMoveLeftArgs* args = CtrlCursorMoveLeftArgs_new(cols);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveDownToLeft(struct TermCtrlQueue* queue, unsigned int lines) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_DOWN_TO_LEFT;

	struct CtrlCursorMoveDownToLeftArgs* args = CtrlCursorMoveDownToLeftArgs_new(lines);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveUpToLeft(struct TermCtrlQueue* queue, unsigned int lines) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_UP_TO_LEFT;

	struct CtrlCursorMoveUpToLeftArgs* args = CtrlCursorMoveUpToLeftArgs_new(lines);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveToCol(struct TermCtrlQueue* queue, unsigned int col) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_TO_COL;

	struct CtrlCursorMoveToColArgs* args = CtrlCursorMoveToColArgs_new(col);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlCursorGetPosition(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_GET_POSITION;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorMoveOnceUpWithScroll(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_MOVE_ONCE_UP_WITH_SCROLL;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorSavePosition(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_SAVE_POSITION;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorRestorePosition(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_RESTORE_POSITION;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlCursorSetVisible(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_SET_VISIBLE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlCursorSetInvisible(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_CURSOR_SET_INVISIBLE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlDisplayEraseFromCursor(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_FROM_CURSOR;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseToCursor(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_TO_CURSOR;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseAll(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_ALL;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseSavedLines(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_SAVED_LINES;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseLineFromCursor(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_LINE_FROM_CURSOR;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseLineToCursor(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_LINE_TO_CURSOR;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayEraseLine(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ERASE_LINE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlDisplaySave(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_SAVE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayRestore(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_RESTORE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlDisplayEnterAltBuffer(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_ENTER_ALT_BUFFER;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlDisplayLeaveAltBuffer(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_DISPLAY_LEAVE_ALT_BUFFER;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};

void queueTermCtrlStyleResetModes(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_MODES;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetBold(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_BOLD;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetBold(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_BOLD;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetDim(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_DIM;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetDim(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_DIM;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetItalics(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_ITALICS;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetItalics(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_ITALICS;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetUnderline(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_UNDERLINE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetUnderline(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_UNDERLINE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetBlinking(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_BLINKING;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};;
void queueTermCtrlStyleResetBlinking(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_BLINKING;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetInverse(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_INVERSE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetInverse(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_INVERSE;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetHidden(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_HIDDEN;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetHidden(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_HIDDEN;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetStrikethrough(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_STRIKETHROUGH;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleResetStrikethrough(struct TermCtrlQueue* queue) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_RESET_STRIKETHROUGH;
	ctrl.args = NULL;

	Queue_queue(&queue->action_queue, &ctrl);
};
void queueTermCtrlStyleSetColor(struct TermCtrlQueue* queue, enum TermColorStyle style) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_COLOR;

	struct CtrlStyleSetColorArgs* args = CtrlStyleSetColorArgs_new(style);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}
void queueTermCtrlStyleSetForegroundRGB(struct TermCtrlQueue* queue, uint8_t r, uint8_t g, uint8_t b) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_FOREGROUND_RGB;

	struct CtrlStyleSetForegroundRGBArgs* args = CtrlStyleSetForegroundRGBArgs_new(r, g, b);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}
void queueTermCtrlStyleSetBackgroundRGB(struct TermCtrlQueue* queue, uint8_t r, uint8_t g, uint8_t b) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_STYLE_SET_BACKGROUND_RGB;

	struct CtrlStyleSetBackgroundRGBArgs* args = CtrlStyleSetBackgroundRGBArgs_new(r, g, b);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}
