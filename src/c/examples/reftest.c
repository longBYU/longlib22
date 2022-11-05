
#include "my.h"

/* Table of constant values */
static integer c_n1011 = -1011;
static integer c_n3 = -3;
static integer c_n2 = -2;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__6 = 6;
static integer c__7 = 7;
static integer c__8 = 8;
static integer c__11 = 11;
static integer c__12 = 12;
static integer c__13 = 13;
static integer c__16 = 16;
static integer c__18 = 18;
static integer c__20 = 20;
static integer c__21 = 21;
static integer c__200 = 200;
static integer c__300 = 300;
static integer c__302 = 302;
static integer c__400 = 400;
static integer c__500 = 500;
static integer c__900 = 900;

static real c_b5 = (float)1.;
static real c_b8 = (float)5.1;
static real c_b9 = (float)4.85;
static real c_b10 = (float).2;
static real c_b12 = (float)0.;
static real c_b16 = (float)4.45;
static real c_b23 = (float)4.;
static real c_b30 = (float)200.;
static real c_b34 = (float)3.45;
static real c_b35 = (float)7.3;
static real c_b36 = (float)5.35;
static real c_b38 = (float)4.7;
static real c_b39 = (float)3.7;
static real c_b41 = (float)360.;
static real c_b42 = (float)5.;
static real c_b45 = (float)130.;
static real c_b48 = (float)1.5;
static real c_b49 = (float)3.3;
static real c_b50 = (float).25;
static real c_b52 = (float)45.;
static real c_b55 = (float)240.;
static real c_b59 = (float)3.75;
static real c_b60 = (float).3;
static real c_b65 = (float)50.;
static real c_b68 = (float)-.3;
static real c_b72 = (float)90.;
static real c_b75 = (float)-1.;
static real c_b79 = (float)13.;
static real c_b82 = (float)12.;
static real c_b83 = (float)14.0104;
static real c_b84 = (float)-.2;
static real c_b85 = (float)1002.;
static real c_b97 = (float).5;
static real c_b99 = (float).18;
static real c_b104 = (float).45;
static real c_b106 = (float).6;
static real c_b107 = (float)-135.;
static real c_b108 = (float).12;
static real c_b111 = (float)225.;
static real c_b114 = (float)3.2;
static real c_b115 = (float)2.9;
static real c_b118 = (float)1.25;
static real c_b122 = (float)180.;
static real c_b128 = (float)1600.;
static real c_b136 = (float)2.5;
static real c_b137 = (float)2.4;
static real c_b139 = (float)3.95;
static real c_b149 = (float)2.05;
static real c_b150 = (float)2.35;
static real c_b156 = (float)4.15;
static real c_b158 = (float)4.35;
static real c_b165 = (float)1.65;
static real c_b170 = (float)30.;
static real c_b174 = (float)6.2;
static real c_b181 = (float)100.;
static real c_b187 = (float).15;
static real c_b188 = (float)-30.;
static real c_b196 = (float)9.;
static real c_b199 = (float)128.;
static real c_b202 = (float)2.;
static real c_b204 = (float)8.;
static real c_b207 = (float)195.;
static real c_b210 = (float)3.;
static real c_b212 = (float)7.;
static real c_b215 = (float)70.;
static real c_b225 = (float)255.;

int main()
{
    /* External functions */
    extern /* Subroutine */ int rmwriteword_();
    extern /* Subroutine */ int rect_();
    extern /* Subroutine */ int plot_(), syms_(), axis3_();
    extern /* Subroutine */ int shade_();
    extern /* Subroutine */ int frame_(), rterm_(), arrow_();
    extern /* Subroutine */ int circle_();
    extern /* Subroutine */ int newpen_(), rmwind_(), plotnd_(), symbol_();
    extern /* Subroutine */ int rmstart_();
    extern integer irmchan_();

    /* Local variables */
    static integer idev;
    static integer ierr;
    static shortint m[400];
    static integer ichan;
    static real x[10], y[10];
    static integer ic;
    static integer ix, iy;
    static real xx;

/* 	PROGRAM TO TEST THE RAMTEK EMULATION FILE ROUTINES IN */
/* 	LONGLIB.  INTEGER*2 IS USED IN THE TRANSFER OF IMAGE MODE */
/* 	DATA TO RAMTEK */

/* 	WRITTEN BY: DGL AUG, 1987 */

/* 	FIRST INITIALIZE LONGLIB WITH NO METAFILE AND RAMTEK OUTPUT */

    frame_(&c_n3, &c_n2, &c_b5, &c_b5, &c_b5);

/* 	INITIALLY WE WILL PRODUCE SOME SIMPLE LINE GRAPHICS EXAMPLES */
/* 	THEN SHOW SOME IMAGE MODE EXAMPLES */

    symbol_(&c_b8, &c_b9, &c_b10, "REFTEST", &c_b12, &c__7, &c_n1, 7L);
    symbol_(&c_b8, &c_b16, &c_b10, "Program", &c_b12, &c__7, &c_n1, 7L);
    symbol_(&c_b8, &c_b23, &c_b10, "Output", &c_b12, &c__6, &c_n1, 6L);

/* 	ENCLOSE TITLE IN BOX WITH FAT SOLID LINE */

    newpen_(&c__20);
    plot_(&c_b30, &c_b12, &c__0);
    rect_(&c_b8, &c_b34, &c_b35, &c_b36);

/* 	MAKE A VERY LARGE CIRCLE */

    newpen_(&c_n1);
    circle_(&c_b38, &c_b39, &c_b12, &c_b41, &c_b42, &c_b42, &c_b12);

/* 	SHOW SOME MORE TEXT EXAMPLES IN DIFFERENT COLORS */

    plot_(&c_b45, &c_b12, &c__0);
    symbol_(&c_b48, &c_b49, &c_b50, "SYMBOL Text ", &c_b52, &c__11, &c_n1, 
	    12L);
    plot_(&c_b55, &c_b12, &c__0);
    syms_(&c_b48, &c_b59, &c_b60, "SYMS Font 0 ", &c_b52, &c__12, &c_n1, 12L);

    plot_(&c_b65, &c_b12, &c__0);
    syms_(&c_b68, &c_b5, &c_b10, "|4SYMS Font 4 Text", &c_b72, &c__18, &c_n1, 
	    18L);

/* 	SHOW AXES FOR SCALE AND ORIGIN LOCATION */

    axis3_(&c_b75, &c_b12, "X DIRECTION", &c__11, &c_b79, &c_b12, &c_b75, &
	    c_b82, &c_b83, &c_b84, &c_b85, &ic, 11L);
    axis3_(&c_b12, &c_b75, "Y DIRECTION", &c_n1011, &c_b79, &c_b72, &c_b75, &
	    c_b82, &c_b83, &c_b84, &c_b85, &ic, 11L);

/* 	IDENTIFY LOCAL RELATIVE ORIGIN WITH LABEL AND ARROW */

    symbol_(&c_b97, &c_b97, &c_b99, "RELATIVE ORIGIN (1,1)", &c_b12, &c__21, &
	    c_n1, 21L);
    arrow_(&c_b104, &c_b97, &c_b106, &c_b107, &c_b108, &c_b52);

/* 	DRAW FULL CIRCLE WITH WIDE DOTTED LINE AND COLOR 225 */

    newpen_(&c__21);
    plot_(&c_b111, &c_b12, &c__0);
    circle_(&c_b114, &c_b115, &c_b12, &c_b41, &c_b118, &c_b118, &c_b12);

/* 	DRAW SOME MORE STUFF SUCH AS A SPIRAL, TRIANGLE, AND A HEXAGON */
/* 	WITH A UNIT WIDTH LINE TYPES */

    newpen_(&c_n1);
    plot_(&c_b122, &c_b12, &c__0);
    circle_(&c_b114, &c_b115, &c_b12, &c_b128, &c_b10, &c_b5, &c_b12);
    newpen_(&c__3);
    plot_(&c_b114, &c_b39, &c__3);
    plot_(&c_b136, &c_b137, &c__2);
    plot_(&c_b139, &c_b137, &c__2);
    plot_(&c_b114, &c_b39, &c__2);
    newpen_(&c__2);
    plot_(&c_b72, &c_b12, &c__0);
    plot_(&c_b149, &c_b150, &c__3);
    plot_(&c_b149, &c_b34, &c__2);
    plot_(&c_b114, &c_b156, &c__2);
    plot_(&c_b158, &c_b34, &c__2);
    plot_(&c_b158, &c_b150, &c__2);
    plot_(&c_b114, &c_b165, &c__2);
    plot_(&c_b149, &c_b150, &c__2);

/* 	MAKE AN ARBITRARY REGION AND FILL IT IN USING SHADE, WE WILL */
/* 	LABEL EXAMPLE USING NORMAL SOLID LINE TYPE AND COLOR 30 BUT SHADE */
/* 	WITH COLOR 150 */

    plot_(&c_b170, &c_b12, &c__0);
    newpen_(&c__0);
    symbol_(&c_b174, &c_b115, &c_b10, "SHADE EXAMPLE", &c_b12, &c__13, &c_n1, 
	    13L);
    x[0] = (float)6.;
    y[0] = (float)2.;
    x[1] = (float)7.2;
    y[1] = (float)2.7;
    x[2] = (float)8.;
    y[2] = (float)1.6;
    x[3] = (float)7.5;
    y[3] = (float).5;
    x[4] = (float)6.2;
    y[4] = (float)1.;
    x[5] = (float)6.5;
    y[5] = (float)1.8;
    x[6] = (float)5.5;
    y[6] = (float)1.;
    x[7] = (float)5.9;
    y[7] = (float)2.;
    plot_(&c_b181, &c_b12, &c__0);
    shade_(x, y, &c__8, &c__1, &c__3, &c_b187, &c_b188, &xx, &c__1, &c_b12, &
	    c_b5, &c_b12, &c_b5);

/* 	PLOT A FEW SIMPLE FORMS OF VARIOUS COLORS AND LINE TYPES */

    rect_(&c_b5, &c_b5, &c_b196, &c_b196);
    newpen_(&c__21);
    plot_(&c_b199, &c_b12, &c__0);
    rect_(&c_b202, &c_b202, &c_b204, &c_b204);
    newpen_(&c__302);
    plot_(&c_b207, &c_b12, &c__0);
    rect_(&c_b210, &c_b210, &c_b212, &c_b212);
    newpen_(&c__0);
    plot_(&c_b215, &c_b12, &c__0);
    circle_(&c_b42, &c_b42, &c_b12, &c_b41, &c_b48, &c_b48, &c_b12);
    plot_(&c_b225, &c_b12, &c__0);
    symbol_(&c_b97, &c_b48, &c_b50, "REF Routine Test", &c_b12, &c__16, &c_n1,
	     16L);
    plot_(&c_b12, &c_b12, &c__3);

/* 	IN THE REMAINDER OF THIS PROGRAM WE WILL USE THE IMAGE MODE */
/* 	OF THE SIMULATED RAMTEK. WE WILL PRODUCE SIMPLE TEST IMAGES. */
/* 	FIRST MAKE A SIMPLE GREY SCALE.  FIRST GET CHANNEL NUMBER. */

    ichan = irmchan_(&idev);

/* 	SET UP OUTPUT IMAGE WINDOW */

    rmwind_(&ichan, &c__500, &c__500, &c__900, &c__900, &ierr);

/* 	MAKE SMALL GREY SCALE */

    for (ix = 1; ix <= 400; ++ix) {
	m[ix - 1] = ix / 2;
/* L5: */
    }

/* 	DUPLICATE GREY SCALE VERTICIALLY */

    for (iy = 500; iy <= 700; ++iy) {
	rmstart_(&ichan, &c__500, &iy, &ierr);
	rmwriteword_(&ichan, m, &c__400, &ierr);
/* L10: */
    }

/* 	NOW MAKE A SOLID FILL WITH COLOR 255 (THE DEFAULT) */

    rmwind_(&ichan, &c__200, &c__200, &c__300, &c__300, &ierr);
    for (ix = 1; ix <= 200; ++ix) {
	m[ix - 1] = 255;
/* L15: */
    }

/* 	FILL REGION TWO LINES AT TIME */

    for (iy = 200; iy <= 300; iy += 2) {
	rmstart_(&ichan, &c__200, &iy, &ierr);
	rmwriteword_(&ichan, m, &c__200, &ierr);
/* L20: */
    }

/* 	NOW FINISH UP BY CALLING PLOTND */

    rterm_(&c__2);
    plotnd_();

}
