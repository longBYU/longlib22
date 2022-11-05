
/* *** LAST REVISED ON 20-JAN-1994 13:35:48.99 */
/* *** SOURCE FILE: [LONGD]LINETYPE.C */

#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__0 = 0;
static real c_b3 = (float).2;
static real c_b4 = (float).3;
static real c_b5 = (float)2.;
static real c_b6 = (float).15;
static real c_b7 = (float).1;
static real c_b10 = (float)90.;
static real c_b11 = (float)2.;
static integer c__39 = 39;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c_n11 = -11;
static real c_b20 = (float)0.;
static real c_b26 = (float)999.;
static integer c__1 = 1;

/* 	PROGRAM TO DEMONSTRATE THE AVAILABLE LINE TYPES AND COLORS */

int main()
{
    /* System generated locals */
    integer i__1;
    real r__1;

    /* Local variables */
    static integer icnt;
    extern /* Subroutine */ int plot_();
    static real x, y;
    extern /* Subroutine */ int frame_(), cterm_(), rterm_();
    static integer itype, icolor, iwidth;
    extern /* Subroutine */ int number_(), newpen_(), plotnd_(), symbol_(), 
	    newpage_();

    frame_(&c__3, &c__0, &c_b3, &c_b4, &c_b5);
    plot_(&c_b11, &c_b11, &c__0);

/* 	PLOT A PAGE TITLE */

    symbol_(&c_b6, &c_b7, &c_b6, "(Type,Width,Color) Available Line Types", &
	    c_b10, &c__39, &c_n1);

/* 	PLOT A SAMPLE OF EACH LINE TYPE, WIDTH, AND COLOR */

    icnt = 0;
    for (iwidth = 1; iwidth <= 5; ++iwidth) {
	for (itype = 1; itype <= 9; ++itype) {
	    for (icolor = 1; icolor <= 6; ++icolor) {
L10:
		x = icnt / 35 * (float)1.7 + (float).21;
		y = icnt % 35 * (float).2;
		if (x > (float)10.) {		/* NEW PAGE */
		    newpage_();
		    rterm_(&c__2);
		    cterm_(&c__2);
		    cterm_(&c_n1);
		    icnt = 0;
		    goto L10;
		}
		++icnt;

/* 	SET TO SOLID LINE OF WIDTH 1 */

		newpen_(&c_n11);
		plot_(&c_b5, &c_b20, &c__0);
		r__1 = (real) itype;
		number_(&x, &y, &c_b6, &r__1, &c_b20, &c_b20, &c_n1);
		symbol_(&c_b26, &c_b26, &c_b6, ",", &c_b20, &c__1, &c_n1, 1L);

		r__1 = (real) iwidth;
		number_(&c_b26, &c_b26, &c_b6, &r__1, &c_b20, &c_b20, &c_n1);
		symbol_(&c_b26, &c_b26, &c_b6, ",", &c_b20, &c__1, &c_n1, 1L);

		r__1 = (real) icolor;
		number_(&c_b26, &c_b26, &c_b6, &r__1, &c_b20, &c_b20, &c_n1);

		r__1 = (real) icolor;
		plot_(&r__1, &c_b20, &c__0);
		i__1 = itype + iwidth * 10;
		newpen_(&i__1);
		x += (float).8;
		plot_(&x, &y, &c__3);
		r__1 = x + (float).75;
		plot_(&r__1, &y, &c__2);
		plot_(&x, &y, &c__3);
/* L100: */
	    }
	}
    }
    cterm_(&c__2);
    rterm_(&c__2);
    plotnd_();
}

