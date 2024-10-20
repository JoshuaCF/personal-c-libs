#include <stdio.h>
#include <stdlib.h>

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
	// Single shot:
	printf("\tSingle shot:\n");
	printf("\t\tTerm colors:\n");
	doTermCtrlStyleSetColor(term, STYLE_FG_RED);
	doTermCtrlStyleSetColor(term, STYLE_BG_WHITE);
	doTermCtrlWrite(term, "Red on white ");
	doTermCtrlStyleSetColor(term, STYLE_FG_GREEN);
	doTermCtrlStyleSetColor(term, STYLE_BG_YELLOW);
	doTermCtrlWrite(term, "Green on yellow ");
	doTermCtrlStyleSetColor(term, STYLE_FG_BLUE);
	doTermCtrlStyleSetColor(term, STYLE_BG_MAGENTA);
	doTermCtrlWrite(term, "Blue on magenta ");
	doTermCtrlStyleSetColor(term, STYLE_RESET);
	doTermCtrlWrite(term, "Reset ");
	printf("\n");
	printf("\t\t24-bit colors:\n");
	doTermCtrlStyleSetForegroundRGB(term, 0xFF, 0x77, 0x33);
	doTermCtrlStyleSetBackgroundRGB(term, 0x33, 0x77, 0xFF);
	doTermCtrlWrite(term, "#FF7733 on #3377FF ");
	doTermCtrlStyleSetColor(term, STYLE_RESET);
	doTermCtrlWrite(term, "Reset ");
	printf("\n");
	
	// Batched:
	printf("\tBatched:\n");
	struct TermCtrlQueue batch = TermCtrlQueue_new(term);
	printf("\t\tTerm colors:\n");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_RED);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_WHITE);
	queueTermCtrlWrite(&batch, "Red on white ");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_GREEN);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_YELLOW);
	queueTermCtrlWrite(&batch, "Green on yellow ");
	queueTermCtrlStyleSetColor(&batch, STYLE_FG_BLUE);
	queueTermCtrlStyleSetColor(&batch, STYLE_BG_MAGENTA);
	queueTermCtrlWrite(&batch, "Blue on magenta ");
	queueTermCtrlStyleSetColor(&batch, STYLE_RESET);
	queueTermCtrlWrite(&batch, "Reset ");
	TermCtrlQueue_exec(&batch);
	printf("\n");
	printf("\t\t24-bit colors:\n");
	queueTermCtrlStyleSetForegroundRGB(&batch, 0xFF, 0x77, 0x33);
	queueTermCtrlStyleSetBackgroundRGB(&batch, 0x33, 0x77, 0xFF);
	queueTermCtrlWrite(&batch, "#FF7733 on #3377FF ");
	queueTermCtrlStyleSetColor(&batch, STYLE_RESET);
	queueTermCtrlWrite(&batch, "Reset ");
	TermCtrlQueue_exec(&batch);
	printf("\n");

	TermCtrlQueue_free(&batch);

	return 0;
}
