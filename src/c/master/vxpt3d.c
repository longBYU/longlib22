
/* *** LAST REVISED ON  7-JAN-1994 12:59:30.92 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]VXPT3D.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xscale, yscale, zscale, amin, alph, bet;
} locate_;

#define locate_1 locate_

/* Subroutine */ int vxpt3d_(x, y, aval, ix, iz, nx)
real *x, *y, *aval;
integer *ix, *iz, *nx;
{
    /* Builtin functions */
    double cos(), sin();

/* 	CREATED BY DAVID LONG    AUG, 1982	AT JPL */
/* 	SUBPROGRAM OF VAX3D */

/* 	ROUTINE TO DETERMINE X,Y VALUE OF A POINT ON 3-D SURFACE */
/* 	FOR VAX3DX */

    *x = locate_1.xscale * (real) (*ix - 1) * cos(locate_1.alph) + (real) (*
	    iz - 1) * cos(locate_1.bet) * locate_1.zscale;
    *y = locate_1.yscale * (*aval - locate_1.amin) + (real) (*nx - *ix + 1) * 
	    sin(locate_1.alph) * locate_1.xscale + (real) (*iz - 1) * sin(
	    locate_1.bet) * locate_1.zscale;
    return 0;
} /* vxpt3d_ */

