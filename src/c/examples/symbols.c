
/* *** LAST REVISED ON 26-DEC-1993 02:11:32.82 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.EXAMPLES]SYMBOLS.C */

#include "my.h"

/* Table of constant values */
static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__15 = 15;
static integer c__17 = 17;
static integer c__32 = 32;
static integer c__60 = 60;
static integer c__99 = 99;
static real c_b3 = (float)1.;
static real c_b5 = (float)0.8;
static real c_b6 = (float)0.;
static real c_b7 = (float)2.;
static real c_b8 = (float).2;
static real c_b10 = (float)90.;
static real c_b15 = (float).18;
static real c_b33 = (float)1.2;
static real c_b34 = (float)-.5;
static real c_b36 = (float).8;
static real c_b39 = (float).25;
static real c_b43 = (float)-.6;
static real c_b48 = (float)-1.3;
static real c_b49 = (float).5;
static real c_b54 = (float).9;
static real c_b63 = (float)-.35;
static real c_b64 = (float).15;
static real c_b69 = (float)999.;
static real c_b76 = (float).23;

int main()
{
    /* Initialized data */

    static char string[] = "\\6r\\_0\\[=\\1 S \\6a\\^2\\]\\[\\_\\0n\\]\\[\\]\\]\\]\\U\\Ln=1\\]\\]\\@\\O\\R\\6K";
    //static char string2[] = "\\\\6r\\\\_0\\\\[=\\\\1 S \\\\6a\\\\^2\\\\]\\\\[\\\\_\\\\0n\\\\]\\\\[\\\\]\\\\]\\\\]\\\\U\\\\Ln=1\\\\]\\\\]\\\\@\\\\O\\\\R\\\\6K";

    /* System generated locals */
    real r__1, r__2;

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ real syms_(), symss_();
    extern /* Subroutine */ int frame_(), cterm_(), rterm_();
    extern /* Subroutine */ int factor_(), number_(), plotnd_(), 
	    symbol_(), newpage_();

    /* Local variables */
    static integer isym;
    static integer i, j, k;
    static char t[5], ch;
    static real y;
    static real x1;

/* 	A SIMPLE PROGRAM TO PLOT A SAMPLE OF EACH PLOTTING SYMBOL */

    frame_(&c__3, &c__0, &c_b3, &c_b3, &c_b3);	/* INTIALIZE PLOT PACKAGE */
    factor_(&c_b5);
    x1 = (float).5;
    y = (float)1.;

/* 	FIRST PLOT "SYMBOL" CHARACTER FONT */

    symbol_(&c_b6, &c_b7, &c_b8, "SYMBOL Characters", &c_b10, &c__17, &c_n1);
    for (isym = 0; isym < 23; ++isym) {
	for (j = 0; j <= 6; ++j) {
	    y = (real) j * (float)1.1;
	    k = j * 23 + isym;
	    if (k >= 128) {
		goto L26;
	    }
	    r__1 = x1 + (float).01;
	    r__2 = (real) k;
	    number_(&r__1, &y, &c_b15, &r__2, &c_b10, &c_b6, &c_n1);
	    r__1 = y + (float).65;
	    ch = k;
	    symbol_(&x1, &r__1, &c_b8, &ch, &c_b10, &c__1, &c_n1);
L26:
	    ;
	}
	x1 += (float).24;
/* L25: */
    }
    cterm_(&c__2);
    rterm_(&c__2);
    newpage_();

/* 	NOW PLOT "SYMS" CHARACTER FONTS */

    cterm_(&c_n1);
    symbol_(&c_b6, &c_b7, &c_b8, "SYMS Characters", &c_b10, &c__15, &c_n1);
    plot_(&c_b33, &c_b34, &c_n3);
    factor_(&c_b36);
    for (i = 1; i <= 32; ++i) {
	x1 = (i - 1) * (float).25;
	ch = i - 1;
	r__1 = (real) (i - 1);
	number_(&x1, &c_b43, &c_b15, &r__1, &c_b10, &c_b6, &c_n1);
	plot_(&x1, &c_b6, &c__3);
	syms_(&x1, &c_b6, &c_b39, &ch, &c_b6, &c__1, &c_n1);
    }
    syms_(&c_b48, &c_b49, &c_b8, string, &c_b6, &c__99, &c_n1);
    symbol_(&c_b54, &c_b49, &c_b8, string, &c_b6, &c__60, &c_n1);
    for (i = 1; i <= 9; ++i) {
	t[0] = '\\';
	t[1] = i + 47;
	t[2] = 0;
	r__1 = i * (float).9;
	symbol_(&c_b63, &r__1, &c_b64, "Font ", &c_b10, &c__5, &c_n1);
	symbol_(&c_b69, &c_b69, &c_b64, &t[1], &c_b10, &c__1, &c_n1);
	r__1 = i * (float).9;
	syms_(&c_b6, &r__1, &c_b76, t, &c_b6, &c__2, &c_n1, 2L); /* CHANGE FONT AND LOCATION */
	syms_(&c_b69, &c_b69, &c_b76, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", &
		c_b6, &c__32, &c_n1);
	r__1 = i * (float).9 + (float).3;
	syms_(&c_b6, &r__1, &c_b76, t, &c_b6, &c__2, &c_n1); /* CHANGE LOCATION */
	syms_(&c_b69, &c_b69, &c_b76, "`abcdefghijklmnopqrstuvwxyz{|}~", &
		c_b6, &c__32, &c_n1, 32L);
	r__1 = i * (float).9 + (float).6;
	syms_(&c_b6, &r__1, &c_b76, t, &c_b6, &c__2, &c_n1); /* CHANGE LOCATION */
	syms_(&c_b69, &c_b69, &c_b76, " !\"#$%&\'()*+,-./0123456789:;<=>?", &
		c_b6, &c__32, &c_n1);
    }
    plot_(&c_b6, &c_b6, &c__3);

    cterm_(&c__2);
    rterm_(&c__2);
    plotnd_();
}







