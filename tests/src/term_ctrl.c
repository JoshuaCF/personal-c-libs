#include <stdio.h>

#include "term_color_defs.h"
#include "term_ctrl.h"

int main() {
	/* Tests to perform:
	 * Alternate screen buffer
	 * Different input modes
	 * General cursor movement
	 * General text styling
	 */

#ifndef WINDOWS
	// POSIX
	Terminal term = stdout;
#else
	// Windows
#endif
	
	// General text styling
	printf("Testing general text styling.\n");
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);
	printf("\tTerm colors:\n");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_RED);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_WHITE);
	queueTermCtrlWriteString(&batch, "Red on white ");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_GREEN);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_YELLOW);
	queueTermCtrlWriteString(&batch, "Green on yellow ");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_BLUE);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_MAGENTA);
	queueTermCtrlWriteString(&batch, "Blue on magenta ");
	queueTermCtrlStyleSetColor(&batch, STYLE_RESET);
	queueTermCtrlWriteString(&batch, "Reset ");
	TermCtrlQueue_exec(&batch);
	printf("\n");
	printf("\t24-bit colors:\n");
	queueTermCtrlStyleSetForegroundRGB(&batch, 0xFF, 0x77, 0x33);
	queueTermCtrlStyleSetBackgroundRGB(&batch, 0x33, 0x77, 0xFF);
	queueTermCtrlWriteString(&batch, "#FF7733 on #3377FF ");
	queueTermCtrlStyleSetColor(&batch, STYLE_RESET);
	queueTermCtrlWriteString(&batch, "Reset ");
	TermCtrlQueue_exec(&batch);
	printf("\n");

	TermCtrlQueue_free(&batch);

	return 0;
}
