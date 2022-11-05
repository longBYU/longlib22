
/* *** LAST REVISED ON 24-DEC-1993 07:19:36.17 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]RECT.C */

#include "my.h"

/* Table of constant values */
static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int rect_(x0, y0, x1, y1)
real *x0, *y0, *x1, *y1;
{

    /* External functions */
    extern /* Subroutine */ int plot_();

/* 	ROUTINE TO PLOT A RECTANGLE */
/* 	X0,Y0	(R) LOWER LEFT HAND CORNER */
/* 	X1,Y1	(R) UPPER RIGHT HAND CORNER */

/* 	NOTE: PEN ENDS UP DOWN AT LOWER-LEFT HAND CORNER */

    plot_(x0, y0, &c__3);
    plot_(x1, y0, &c__2);
    plot_(x1, y1, &c__2);
    plot_(x0, y1, &c__2);
    plot_(x0, y0, &c__2);
    return 0;
} /* rect_ */

