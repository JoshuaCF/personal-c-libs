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
	CTRL_WRITE,

	CTRL_STYLE_SET_COLOR,
	CTRL_STYLE_SET_FOREGROUND_RGB,
	CTRL_STYLE_SET_BACKGROUND_RGB,
};

/*
struct Ctrl_Args {
};
struct Ctrl_Args Ctrl_Args_new() {
}
void Ctrl_Args_free(struct Ctrl_Args* args) {
}
*/

struct CtrlWriteArgs {
	char* str; // Owned! Will be copied into
};
struct CtrlWriteArgs* CtrlWriteArgs_new(const char* str) {
	struct CtrlWriteArgs* args = malloc(sizeof(struct CtrlWriteArgs));

	args->str = malloc(strlen(str) + 1);
	strcpy(args->str, str);

	return args;
}
static void CtrlWriteArgs_free(struct CtrlWriteArgs* args) {
	free(args->str);
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
		case CTRL_WRITE:
			CtrlWriteArgs_free(ctrl->args);
			break;
		// No special free behavior needed
		case CTRL_STYLE_SET_COLOR:
		case CTRL_STYLE_SET_FOREGROUND_RGB:
		case CTRL_STYLE_SET_BACKGROUND_RGB:
			break;
	}
	free(ctrl->args);
}

struct TermCtrlQueue TermCtrlQueue_new(Terminal term) {
	struct TermCtrlQueue queue;
	queue.term = term;
	queue.action_queue = Queue_new(sizeof(struct Ctrl), 32);

	return queue;
}
void TermCtrlQueue_exec(struct TermCtrlQueue* queue) {
	struct Ctrl cur_ctrl;

#ifndef WINDOWS
	// Simple implementation that does not optimize
	char* write_buf = malloc(sizeof(char) * 4096);
	while (Queue_next(&queue->action_queue, &cur_ctrl) == QUEUE_OK) {
		switch (cur_ctrl.type) {
			case CTRL_WRITE: {
				struct CtrlWriteArgs* args = cur_ctrl.args;
				snprintf(write_buf, 4095, "%s", args->str);
				fprintf(queue->term, "%s", write_buf);
				break;
			}
			case CTRL_STYLE_SET_COLOR: {
				struct CtrlStyleSetColorArgs* args = cur_ctrl.args;
				bufWriteStyleSetColor(write_buf, args->style);
				fprintf(queue->term, "%s", write_buf);
				break;
			}
			case CTRL_STYLE_SET_FOREGROUND_RGB: {
				struct CtrlStyleSetForegroundRGBArgs* args = cur_ctrl.args;
				bufWriteStyleSetForegroundRGB(write_buf, args->r, args->g, args->b);
				fprintf(queue->term, "%s", write_buf);
				break;
			}
			case CTRL_STYLE_SET_BACKGROUND_RGB: {
				struct CtrlStyleSetBackgroundRGBArgs* args = cur_ctrl.args;
				bufWriteStyleSetBackgroundRGB(write_buf, args->r, args->g, args->b);
				fprintf(queue->term, "%s", write_buf);
				break;
			}
		}
	}
	free(write_buf);
#else
		switch (cur_ctrl.type) {

		}
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

void queueTermCtrlWrite(struct TermCtrlQueue* queue, char* str) {
	struct Ctrl ctrl;
	ctrl.type = CTRL_WRITE;

	struct CtrlWriteArgs* args = CtrlWriteArgs_new(str);
	ctrl.args = args;

	Queue_queue(&queue->action_queue, &ctrl);
}

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

// I don't want to rewrite all of the queue functionality, so I'm going to make this shitty
// until I refactor things
void doTermCtrlWrite(Terminal term, char* str) {
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);

	queueTermCtrlWrite(&batch, str);
	TermCtrlQueue_exec(&batch);

	TermCtrlQueue_free(&batch);
}

void doTermCtrlStyleSetColor(Terminal term, enum TermColorStyle style) {
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);

	queueTermCtrlStyleSetColor(&batch, style);
	TermCtrlQueue_exec(&batch);

	TermCtrlQueue_free(&batch);
}
void doTermCtrlStyleSetForegroundRGB(Terminal term, uint8_t r, uint8_t g, uint8_t b) {
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);

	queueTermCtrlStyleSetForegroundRGB(&batch, r, g, b);
	TermCtrlQueue_exec(&batch);

	TermCtrlQueue_free(&batch);
}
void doTermCtrlStyleSetBackgroundRGB(Terminal term, uint8_t r, uint8_t g, uint8_t b) {
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);

	queueTermCtrlStyleSetBackgroundRGB(&batch, r, g, b);
	TermCtrlQueue_exec(&batch);

	TermCtrlQueue_free(&batch);
}
