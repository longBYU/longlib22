
/* *** LAST REVISED ON 20-JAN-1994 08:46:21.98 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.EXAMPLES]PLOTTESTS.C */

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

/* Common Block Declarations */

struct {
    real xmr, dxr, ymr, dyr;
} cscatpl_;
#define cscatpl_1 cscatpl_

struct {
    real xm, dx, ym, dy;
} cseispl_;
#define cseispl_1 cseispl_

struct {
    real xm, dx, ym, dy;
} cphist_;
#define cphist_1 cphist_

extern struct {
    real xm, dx, ym, dy;
} cplotlg_;
#define cplotlg_1 cplotlg_

struct {
    real xscale, yscale, zscale, amin, alph, bet;
} locate_;
#define locate_1 locate_

struct {
    real xm, dx, ym, dy;
} cplotlg2_;
#define cplotlg2_1 cplotlg2_

struct {
    real xm, dx, ym, dy;
} csplots_;
#define csplots_1 csplots_

/* Table of constant values */

static integer c__0 = 0;
static real c_b4 = (float)1.;
static real c_b7 = (float)9.7;
static real c_b8 = (float)7.4;
static integer c__4 = 4;
static real c_b10 = (float)-.99;
static real c_b12 = (float)9.69;
static real c_b13 = (float)7.39;
static real c_b14 = (float)5.1;
static real c_b15 = (float)4.85;
static real c_b16 = (float).2;
static real c_b18 = (float)0.;
static integer c__9 = 9;
static integer c_n1 = -1;
static real c_b22 = (float)4.45;
static integer c__7 = 7;
static real c_b29 = (float)4.;
static integer c__6 = 6;
static real c_b36 = (float)3.6;
static integer c__8 = 8;
static integer c__21 = 21;
static real c_b43 = (float)2.;
static real c_b46 = (float)4.8;
static real c_b47 = (float)3.45;
static real c_b48 = (float)7.3;
static real c_b49 = (float)5.35;
static real c_b51 = (float)4.7;
static real c_b52 = (float)3.7;
static real c_b54 = (float)360.;
static real c_b55 = (float)5.;
static real c_b58 = (float)3.;
static real c_b61 = (float)1.5;
static real c_b62 = (float)3.3;
static real c_b63 = (float).25;
static real c_b65 = (float)45.;
static integer c__11 = 11;
static real c_b72 = (float)3.75;
static real c_b73 = (float).3;
static integer c__12 = 12;
static real c_b81 = (float)-.3;
static real c_b85 = (float)90.;
static integer c__18 = 18;
static real c_b88 = (float)-1.;
static real c_b92 = (float)13.;
static real c_b95 = (float)12.;
static real c_b96 = (float)14.0104;
static real c_b97 = (float)-.2;
static real c_b98 = (float)1002.;
static integer c_n1011 = -1011;
static real c_b110 = (float).5;
static real c_b112 = (float).18;
static real c_b117 = (float).45;
static real c_b119 = (float).6;
static real c_b120 = (float)-135.;
static real c_b121 = (float).12;
static integer c__22 = 22;
static real c_b124 = (float)7.;
static real c_b127 = (float)3.2;
static real c_b128 = (float)2.9;
static real c_b131 = (float)1.25;
static real c_b135 = (float)8.;
static real c_b141 = (float)1600.;
static integer c__3 = 3;
static real c_b149 = (float)2.5;
static real c_b150 = (float)2.4;
static integer c__2 = 2;
static real c_b152 = (float)3.95;
static real c_b159 = (float)9.;
static real c_b162 = (float)2.05;
static real c_b163 = (float)2.35;
static real c_b169 = (float)4.15;
static real c_b171 = (float)4.35;
static real c_b178 = (float)1.65;
static integer c__1 = 1;
static real c_b187 = (float)6.2;
static integer c__13 = 13;
static real c_b200 = (float).15;
static real c_b201 = (float)-30.;
static integer c_b216 = -10002;
static real c_b217 = (float)-40.;
static real c_b221 = (float).21;
static integer c__16 = 16;
static real c_b225 = (float).1;
static integer c_n3 = -3;
static real c_b232 = (float)1.8;
static real c_b238 = (float)6.;
static integer c__31 = 31;
static real c_b245 = (float)6.8;
static real c_b246 = (float)5.8;
static real c_b247 = (float)13.4;
static integer c__25 = 25;
static integer c_b254 = -10073;
static integer c__5 = 5;
static integer c_n7 = -7;
static real c_b269 = (float)-8.;
static integer c_b275 = -10014;
static integer c_n6 = -6;
static real c_b286 = (float)10.;
static integer c_n15 = -15;
static integer c_b324 = -10054;
static integer c_n107 = -107;
static real c_b336 = (float)20.;
static real c_b339 = (float)6.5;
static real c_b342 = (float)-6.5;
static real c_b348 = (float)25.;
static real c_b349 = (float)15.;
static real c_b351 = (float)3.8;
static integer c_b353 = -10001;
static integer c_n11 = -11;
static integer c__14 = 14;
static real c_b357 = (float)-10.;
static real c_b362 = (float)-.15;
static real c_b397 = (float)4.2;
static real c_b400 = (float)-6.;
static integer c__30 = 30;
static integer c_n9 = -9;
static real c_b419 = (float).4;
static real c_b420 = (float)-14.;
static real c_b423 = (float)14.;
static real c_b435 = (float)3.4;
static integer c__10 = 10;
static real c_b493 = (float)30.;
static real c_b494 = (float)40.;
static real c_b500 = (float)2.75;
static real c_b512 = (float)-5.;
static real c_b516 = (float)-.255;
static integer c_b543 = -10042;
static integer c__15 = 15;
static real c_b547 = (float)-2.;
static integer c_b576 = -10064;
static real c_b580 = (float)6.0102;
static real c_b582 = (float)5.02;
static real c_b585 = (float)4.05;
static real c_b587 = (float)6.03;
static integer c_n112 = -112;
static integer c__20 = 20;
static integer c_b604 = -10034;
static real c_b606 = (float)-.1;
static integer c_b627 = -10024;
static real c_b629 = (float).22;

int main()
{
    /* Initialized data */

    static char *labels[7] = {"Plot Routines","Auxliary Rou.",
	"MASTER Routns","MAP Routines","Cursor Routns","3D Plot Rou",
        "Internal Rou."};
    static real vals[7] = { (float)51.,(float)34.,(float)-32.,(float)6.,(
	    float)6.,(float)21.,(float)43. };
    static integer ish[7] = { 0,1,2,3,4,5,6 };
    static integer iwt[7] = { 2,2,3,2,2,2,2 };
    static real tpi = (float)3.141592654;
    static integer is = 9881821;

    /* System generated locals */
    integer i__1;
    real r__1, r__2, r__3, r__4;

    /* Builtin functions */
    double cos(), sqrt(), sin();

    /* Local variables */
    static real xcenter1, ycenter1, xcenter2, ycenter2;
    static integer icol[255];
    static real smaj;
    extern /* Subroutine */ int rect_();
    static real smin;
    extern /* Subroutine */ int plot_(), syms_(), axis3_();
    static real d[625]	/* was [25][25] */;
    static integer i, j;
    static real xrms1, yrms1, xrms2, yrms2;
    extern /* Subroutine */ int shade_();
    static real x[125], y[10];
    extern /* Subroutine */ int frame_();
    static integer iline[255];
    extern /* Subroutine */ int cterm_();
    static real d1, d2, d3, d4;
    extern /* Subroutine */ int rterm_(), arrow_(), phist_();
    static real t1, t2, x2[50]	/* was [25][2] */, y2[50]	/* was [25][2]
	     */, y3[75]	/* was [25][3] */;
    extern /* Subroutine */ int cvax3d_(), mvax3d_(), cnt3dx_(), vax3dx_();
    static integer ip[100];
    extern /* Subroutine */ int circle_();
    static real xp, yp;
    extern /* Subroutine */ int factor_();
    static real xx[100];
    extern /* Subroutine */ int scatpl_(), pichrt_(), newpen_(), seispl_(), 
	    plotnd_(), glplot_(), symbol_(), splots_(), plotvt_();
    static real xy1, xy2;
    extern /* Subroutine */ int plotlg2_();
    extern doublereal ran_();
    extern /* Subroutine */ int newpage_(), ellipse_(), vfactor_(), covarit_()
	    , cntrplt_();

/* 	WRITTEN BY: DGL */

/* 	THIS PROGRAM TESTS SOME OF THE LONGLIB MASTER PLOTTING ROUTINES */
/* 	NOTE: ALTHOUGH THE "MASTER" ROUTINES HAVE A LOT OF OPTIONS ONLY */
/* 	ONE OPTION FOR EACH ROUTINE WILL BE ILLUSTRATED.  THE PROGRAM WILL, */

/* 	HOWEVER, TRY TO SHOW SOME OF THE UNIQUE THINGS THEY CAN EACH DO. */
/* 	SINCE MANY MASTER ROUTINES HAVE SIMILAR GRID SPECS WE WILL TRY TO SHOW
 */
/* 	ONE OF EACH KIND OF GRID.  WE WILL USE THE AUTO-SCALING OPTION MOST */

/* 	OF THE TIME. */


/* 	MASTER ROUTINE SCATPL COMMON BLOCK USED FOR ELLIPSE SCALLING, ETC. */
/* 	AFTER THE CALL TO SCATPL -- ILLUSTRATES RETURNED SCALING USAGE. */


/* 	PIE CHART DATA */


/* 	INITIALIZE THE COLOR ARRAY (WE WILL ALWAYS USE */
/* 	COLOR FOR THESE TESTS) */

    for (i = 1; i <= 255; ++i) {
	icol[i - 1] = i;
/* L1: */
    }

/*	OPEN THE PLOT PACKAGE, USING PROMPTS FOR BOTH METAFILE AND SCREEN DEVIC
E*/
/* 	NOTE:  	FOR THESE TESTS WE WILL OPEN THE PLOT PACKAGE BEFORE THE */
/* 		MASTER ROUTINE CALLS.  WE WILL SET THE IFLAG VALUES TO NOT */
/* 		REOPEN THE PLOT PACKAGE AND ALSO TO LEAVE IS OPEN AFTER THE */
/* 		THE CALL TO THEM.  THIS WILL ILLUSTRATE HOW MULTIPLE MASTER */
/* 		ROUTINES CAN BE CALLED TOGETHER. */

    frame_(&c__0, &c__0, &c_b4, &c_b4, &c_b4);

/* 	SET UP CLIPPING WINDOW WITHIN 11X8.5 INCH PAGE, THIS IS OPTIONAL */
/* 	AND WILL RESULT IN CLIPPING OF PORTIONS OF PLOTTED LINES ETC. */

    plot_(&c_b7, &c_b8, &c__4);

/* 	PLOT A BOX AROUND THE CLIPPING WINDOW */

    rect_(&c_b10, &c_b10, &c_b12, &c_b13);

/* 	INITIALLY WE WILL PLOT A PAGE OF GRAPHICS OUTPUT EXAMPLES TO */
/* 	ILLUSTRATE SOME MINOR ROUTINES AND THE WINDOW CLIPPING ABILITY */

    symbol_(&c_b14, &c_b15, &c_b16, "PLOTTESTS", &c_b18, &c__9, &c_n1);
    symbol_(&c_b14, &c_b22, &c_b16, "Program", &c_b18, &c__7, &c_n1);
    symbol_(&c_b14, &c_b29, &c_b16, "MASTER", &c_b18, &c__6, &c_n1);
    symbol_(&c_b14, &c_b36, &c_b16, "Routines", &c_b18, &c__8, &c_n1);

/* 	ENCLOSE TITLE IN BOX WITH FAT SOLID LINE */

    newpen_(&c__21);
    plot_(&c_b43, &c_b18, &c__0);
    rect_(&c_b46, &c_b47, &c_b48, &c_b49);

/* 	MAKE A VERY LARGE CIRCLE WHICH SHOULD BE CLIPPED OFF AT THE */
/* 	PAGE/SCREEN EDGES */

    newpen_(&c_n1);
    circle_(&c_b51, &c_b52, &c_b18, &c_b54, &c_b55, &c_b55, &c_b18);

/* 	SHOW SOME MORE TEXT EXAMPLES IN DIFFERENT COLORS */

    plot_(&c_b58, &c_b18, &c__0);
    symbol_(&c_b61, &c_b62, &c_b63, "SYMBOL Text ", &c_b65, &c__11, &c_n1);
    plot_(&c_b29, &c_b18, &c__0);
    syms_(&c_b61, &c_b72, &c_b73, "SYMS Font 0 ", &c_b65, &c__12, &c_n1);

    plot_(&c_b55, &c_b18, &c__0);
    syms_(&c_b81, &c_b4, &c_b16, "\\4SYMS Font 4 Text", &c_b85, &c__18, &c_n1);

/* 	SHOW AXES FOR SCALE AND ORIGIN LOCATION */

    axis3_(&c_b88, &c_b18, "X DIRECTION", &c__11, &c_b92, &c_b18, &c_b88, &
	    c_b95, &c_b96, &c_b97, &c_b98);
    axis3_(&c_b18, &c_b88, "Y DIRECTION", &c_n1011, &c_b92, &c_b85, &c_b88, &
	    c_b95, &c_b96, &c_b97, &c_b98);

/* 	IDENTIFY LOCAL RELATIVE ORIGIN WITH LABEL AND ARROW */

    symbol_(&c_b110, &c_b110, &c_b112, "RELATIVE ORIGIN (1,1)", &c_b18, &c__21, &c_n1);
    arrow_(&c_b117, &c_b110, &c_b119, &c_b120, &c_b121, &c_b65);

/* 	DRAW FULL CIRCLE WITH WIDE DOTTED LINE AND COLOR 7 */

    newpen_(&c__22);
    plot_(&c_b124, &c_b18, &c__0);
    circle_(&c_b127, &c_b128, &c_b18, &c_b54, &c_b131, &c_b131, &c_b18);

/* 	DRAW SOME MORE STUFF SUCH AS A SPIRAL, TRIANGLE, AND A HEXAGON */
/* 	WITH A UNIT WIDTH LINE TYPES */

    newpen_(&c_n1);
    plot_(&c_b135, &c_b18, &c__0);
    circle_(&c_b127, &c_b128, &c_b18, &c_b141, &c_b16, &c_b4, &c_b18);
    newpen_(&c__4);
    plot_(&c_b127, &c_b52, &c__3);
    plot_(&c_b149, &c_b150, &c__2);
    plot_(&c_b152, &c_b150, &c__2);
    plot_(&c_b127, &c_b52, &c__2);
    newpen_(&c__3);
    plot_(&c_b159, &c_b18, &c__0);
    plot_(&c_b162, &c_b163, &c__3);
    plot_(&c_b162, &c_b47, &c__2);
    plot_(&c_b127, &c_b169, &c__2);
    plot_(&c_b171, &c_b47, &c__2);
    plot_(&c_b171, &c_b163, &c__2);
    plot_(&c_b127, &c_b178, &c__2);
    plot_(&c_b162, &c_b163, &c__2);

/* 	MAKE AN ARBITRARY REGION AND FILL IT IN USING SHADE, WE WILL */
/* 	LABEL EXAMPLE USING NORMAL SOLID LINE TYPE AND COLOR 3 BUT SHADE */
/* 	WITH COLOR 1 */

    plot_(&c_b58, &c_b18, &c__0);
    newpen_(&c__1);
    symbol_(&c_b187, &c_b128, &c_b16, "SHADE EXAMPLE", &c_b18, &c__13, &c_n1);
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
    plot_(&c_b43, &c_b18, &c__0);

    shade_(x, y, &c__8, &c__1, &c__3, &c_b200, &c_b201, xx, &c__1, &c_b18, &
	    c_b4, &c_b18, &c_b4);

/* 	PROMPT USER FOR CLEAR SREEN, NOTE PEN UP COMMAND TO FORCE SCREEN */
/* 	OUTPUT BEFORE THE PROMPT.  THEN SEND NEW PAGE COMMAND TO METAFILE */

    plot_(&c_b18, &c_b18, &c__3);

    rterm_(&c__2);
    cterm_(&c__2);
    newpage_();

/* 	NOW PLOT MASTER ROUTINE EXAMPLES. */
/* 	FIRST EXAMPLE WILL BE A FULL PAGE PIE CHART */
/* 	SHOWING THE RELATIVE PROPORTIONS OF ROUTINE NAMES IN LONGLIB */

    pichrt_(&c_b58, &c_b58, &c_b43, &c_b63, &c_b216, &c_b217, &c__7, vals, 
	    ish, iwt, labels, &c__13, &c_b121, &c_b221, "LONGLIB Routines", &
	    c__16, &c_b16, &c_b225, &d1, icol);

/* 	PROMPT FOR SCREEN CLEAR ON TERMINAL AND RAMTEK THEN FORCE */
/* 	NEW METAFILE PAGE */

    cterm_(&c__2);
    rterm_(&c__2);
    newpage_();

/* 	FOR THE REMAINING MASTER ROUTINE EXAMPLES WE WILL DISPLAY SEVERAL */
/* 	ROUTINES ON A SINGLE PAGE OF THE METAFILE */
/* 	AND A SINGLE SCREEN OF THE RAMTEK, BUT LET'S PUT ONLY ONE PLOT PER */
/* 	SCREEN ON THE VT100. THIS WILL ILLUSTRATE HOW TO USE MULTIPLE PLOT */
/* 	OUTPUT DEVICES TOGETHER AND HOW TO SHIFT THE ORIGINS OF PLOTS. */
/* 	THIS ILLUSTRATES HOW THE DIFFERENT DEVICE PACKAGES CAN BE INDEPENDENT 
*/

    plot_(&c_b18, &c_b81, &c_n3);
    factor_(&c_b110);
    vfactor_(&c_b232);
    plotvt_(&c_b18, &c_b16, &c_n3);

/* 	PUT TERMINAL BACK INTO GRAPHICS MODE */

    cterm_(&c_n1);

/* 	START WITH A SIMPLE TITLE */

    symbol_(&c_b124, &c_b238, &c_b119, "CHART TITLE", &c_b18, &c__11, &c_n1);

/* 	WITH A THICK-LINED BOX AROUND IT */

    newpen_(&c__31);
    rect_(&c_b245, &c_b246, &c_b247, &c_b245);

/* 	RESTORE NORMAL PENWIDTH */

    newpen_(&c_n1);

/* 	FILL SOME ARRAYS WITH DATA WE CAN PLOT, LET'S PICK SOME NICE FUNCTIONS */
/* 	FIRST SOME ONE DIMENSIONAL DATA */

    for (j = 1; j <= 25; ++j) {
	x[j - 1] = (real) j;
/* Computing 2nd power */
	i__1 = j;
	y2[j - 1] = i__1 * i__1 + (float)5.;
	y2[j + 24] = (real) j;
/* L2: */
    }

/* 	THEN SOME TWO DIMENSIONAL */

    for (j = 1; j <= 25; ++j) {
	for (i = 1; i <= 25; ++i) {
	    d[j + i * 25 - 26] = cos(tpi * (real) (j - 1) / (float)12.) * cos(
		    tpi * (real) (i - 1) / (float)12.);
/* L3: */
	}
    }

/* 	SET UP A MAX,MIN PAIR FOR AN ILLUSTRATION */

    d1 = (float)-1.;
    d2 = (float)1.;

/* 	EXAMPLE OF PLOTLG2 WITH A LOG/LOG SCALE AND GRIDE */

    plotlg2_(x, y2, &c__2, &c__25, &c_b254, &c__5, &c_b238, &c_b55, "X AXIS", 
	    &c__6, "Y AXIS", &c__6, "PLOTLG2", &c_n7, &d1, &d2, &d3, &d4, 
	    icol);

/* 	CHANGE LINE TYPE TO SOLID */

    newpen_(&c__1);

/* 	MOVE ORIGIN ON SCREEN AND METAFILE/RAMTEK DIFFERENTLY */
/* 	PROMPT FOR SCREEN CLEAR ON TERMINAL */

    plot_(&c_b18, &c_b135, &c_n3);
    plotvt_(&c_b18, &c_b269, &c_n3);
    cterm_(&c__2);

/* 	MORE DATA (RANDOM) FOR THE SCATTER PLOT */

    for (i = 1; i <= 25; ++i) {
	x2[i - 1] = ran_(&is) * (float).5 + (float)1.;
	x2[i + 24] = ran_(&is) - (float).5;
	y2[i - 1] = ran_(&is) * (float).3 + (float)1.;
	y2[i + 24] = ran_(&is) * (float)2. - (float).1;

/* 	COMPUTE STATISTICS OF RANDOM VALUES */

	xcenter1 += x2[i - 1] / (float)25.;
	ycenter1 += y2[i - 1] / (float)25.;
/* Computing 2nd power */
	r__1 = x2[i - 1];
	xrms1 += r__1 * r__1 / (float)25.;
/* Computing 2nd power */
	r__1 = y2[i - 1];
	yrms1 += r__1 * r__1 / (float)25.;
	xcenter2 += x2[i + 24] / (float)25.;
	ycenter2 += y2[i + 24] / (float)25.;
/* Computing 2nd power */
	r__1 = x2[i + 24];
	xrms2 += r__1 * r__1 / (float)25.;
/* Computing 2nd power */
	r__1 = y2[i + 24];
	yrms2 += r__1 * r__1 / (float)25.;
	xy1 += x2[i - 1] * y2[i - 1] / (float)25.;
	xy2 += x2[i + 24] * y2[i + 24] / (float)25.;
/* L6: */
    }

/* 	COMPUTE STATISTICS */

/* Computing 2nd power */
    r__1 = xcenter1;
    xrms1 -= r__1 * r__1;
/* Computing 2nd power */
    r__1 = ycenter1;
    yrms1 -= r__1 * r__1;
/* Computing 2nd power */
    r__1 = xcenter2;
    xrms2 -= r__1 * r__1;
/* Computing 2nd power */
    r__1 = ycenter2;
    yrms2 -= r__1 * r__1;
    xy1 -= xcenter1 * ycenter1;
    xy2 -= xcenter2 * ycenter2;

/* 	EXAMPLE OF USING SCATPL WITH TWO SET OF DATA AND LINEAR/LINEAR AXIES 
*/

    scatpl_(x2, y2, &c__2, &c__25, &c_b275, icol, &c_b225, &c_b135, &c_b55, 
	    "X AXIS", &c_n6, "Y AXIS", &c_n6, "SCATPL", &c_n6, &d1, &d2, &d3, 
	    &d4, icol);

/* 	LET'S ADD A ELLIPSE TO INDICATE THE GROUPINGS AND ALSO TO ILLUSTRATE 
*/
/* 	HOW TO PLOT AFTER A MASTER ROUTINE CALL.  WE WILL USE THE PLOTTING */
/* 	SCALE FACTORS COMPUTED IN SCATPL TO CONVERT NORMAL UNITS INTO */
/* 	PLOTTING UNITS. */

/* 	PUT TERMINAL SCREEN BACK INTO PLOT MODE, CHANGE COLOR AND */
/* 	PLOT AN ELLIPSE */

    cterm_(&c_n1);
    plot_(&c_b286, &c_b18, &c__0);
    xp = (xcenter1 - cscatpl_1.xmr) / cscatpl_1.dxr;
    yp = (ycenter1 - cscatpl_1.ymr) / cscatpl_1.dyr;
    covarit_(&xrms1, &yrms1, &xcenter1, &ycenter1, &xy1, &t1);
    smaj = sqrt(xrms1) / cscatpl_1.dxr;
    smin = sqrt(yrms1) / cscatpl_1.dyr;
    ellipse_(&xp, &yp, &smaj, &smin, &t1, &c_b18, &c_b54);
    plot_(&c_b18, &c_b18, &c__3);

/* 	DASHED LINE */

    newpen_(&c__4);
    plot_(&c_b4, &c_b18, &c__0);
    r__1 = xp - smaj;
    r__2 = yp - smaj;
    r__3 = xp + smaj;
    r__4 = yp + smaj;
    rect_(&r__1, &r__2, &r__3, &r__4);
    xp = (xcenter2 - cscatpl_1.xmr) / cscatpl_1.dxr;
    yp = (ycenter2 - cscatpl_1.ymr) / cscatpl_1.dyr;
    covarit_(&xrms2, &yrms2, &xcenter2, &ycenter2, &xy2, &t2);
    smaj = sqrt(xrms2) / cscatpl_1.dxr;
    smin = sqrt(yrms2) / cscatpl_1.dyr;

/* 	CHANGE PEN TO DOTTED LINE FOR ELLIPSE THEN DASHED FOR BOX */

    plot_(&c_b18, &c_b18, &c__3);
    newpen_(&c__2);
    ellipse_(&xp, &yp, &smaj, &smin, &t2, &c_b18, &c_b54);
    newpen_(&c__6);
    r__1 = xp - smin;
    r__2 = yp - smaj;
    r__3 = xp + smin;
    r__4 = yp + smaj;
    rect_(&r__1, &r__2, &r__3, &r__4);
    plot_(&c_b18, &c_b18, &c__3);

/* 	RESTORE PEN TYPE TO SOLID, PROMPT FOR TERMINAL SCREEN CLEAR */
/* 	AND MOVE ORIGINS */

    newpen_(&c__1);
    cterm_(&c__2);
    plot_(&c_b135, &c_b269, &c_n3);
    plotvt_(&c_b269, &c_b135, &c_n3);

/* 	SET UP LINE TYPE ARRAY FOR CONTOURS */

    for (i = 1; i <= 255; ++i) {
	iline[i - 1] = (i - 1) % 10;
/* L431: */
    }

/* 	EXAMPLE OF A SIMPLE CONTOUR PLOT USING THE MOST ROBUST */
/* 	CONTOURING ALGORITHM (WHICH ALSO REQUIRES ALOT OF PEN MOTIONS) */

    cntrplt_(d, &c__25, &c__25, &c__25, &c__25, &c_n15, &c_b88, &c_b4, &
	    c_b324, &c_b55, &c_b55, "X TITLE", &c__7, "Y TITLE", &c__7, 
	    "CNTRPLT", &c_n107, &c_b58, &c_b286, &c_b4, &c_b336, icol, iline);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR AND MOVE ORIGINS */

    cterm_(&c__2);
    plot_(&c_b232, &c_b339, &c_n3);
    plotvt_(&c_b18, &c_b342, &c_n3);

/* 	NOW PLOT 3-D SURFACE USING SLICES WITH AXIS */

    vax3dx_(d, &c__25, &c__25, &c__25, &c__25, &c_b348, &c_b349, &c_b238, &
	    c_b351, &c_b55, &c_b353, &c_n11, "VAX3DX X TITLE", &c__14, &
	    c_b357, &c_b286, &c__4, &c__0, &c__4, &c_b362, &c__1, &c_b225, 
	    "VAX3DX Y TITLE", &c__14, &c__1, &c__0, &c__3, &c_b362, &c__1, &
	    c_b225, "Z TITLE", &c__7, &c_b88, &c_b4, &c__3, &c__2, &c__2, &
	    c_b362, &c__1, &c_b225, &c_b88, &c_b4, icol);

/* 	ADD A LABEL AFTER MASTER ROUTINE CALL */

    cterm_(&c_n1);
    symbol_(&c_b110, &c_b4, &c_b63, "VAX3DX", &c_b18, &c__6, &c_n1);

/* 	NOTE THE PEN UP TO FORCE LAST PART OF OUTPUT TO TERMINAL BEFORE */
/* 	THE PROMPT FOR SCREEN CLEAR COMMAND */

    plot_(&c_b18, &c_b18, &c__3);
    cterm_(&c__2);

/* 	MOVE ORIGINS */

    plot_(&c_b397, &c_b342, &c_n3);
    plotvt_(&c_b400, &c_b339, &c_n3);

/* 	MORE DATA TO LOOK NICE */

    for (i = 1; i <= 125; ++i) {
	x[i - 1] = sin((real) i * (float)3.14 / (float)30.) * (float)10.;
/* L25: */
    }

/* 	PLOT A HISTOGRAM WITH THE MEAN AND STANDARD DEVIATION SHOWING */

    phist_(x, &c__30, "Histogram", &c_n9, &c_b238, &c_b55, "PHIST Subtitle", &
	    c__14, "X TITLE", &c__7, &c_b88, &c_b4, &c_b286, &c_b353, &c__1, &
	    c_b18, &c_b419, icol);

/* 	PROMPT FOR SCREEN CLEAR AND MOVE ORIGINS */
/* 	PUT NEXT PLOT ON NEXT PAGE */

    plot_(&c_b420, &c_b18, &c_n3);
    plotvt_(&c_b423, &c_b18, &c_n3);
    cterm_(&c__2);
    rterm_(&c__2);
    newpage_();

/* 	PLOT 3D CONTOUR PLOT */

    cnt3dx_(d, &c__25, &c__25, &c__25, &c__25, &c_b348, &c_b349, &c_b238, &
	    c_b435, &c_b55, &c__10, &c_b88, &c_b4, &c__1, &c_b353, &c_n11, 
	    "CNT3DX X TITLE", &c__14, &c_b357, &c_b286, &c__4, &c__0, &c__4, &
	    c_b362, &c__1, &c_b225, "CNT3DX Y TITLE", &c__14, &c__1, &c__0, &
	    c__3, &c_b362, &c__1, &c_b225, "Z TITLE", &c__7, &c_b88, &c_b4, &
	    c__3, &c__2, &c__2, &c_b362, &c__1, &c_b225, &c_b88, &c_b4, icol);

/* 	ADD LABEL AFTER MASTER ROUTINE CALL */

    cterm_(&c_n1);
    symbol_(&c_b18, &c_b18, &c_b16, "CNT3DX", &c_b18, &c__6, &c_n1);

/* 	MOVE ORIGIN */

    plot_(&c_b286, &c_b18, &c_n3);
    plotvt_(&c_b357, &c_b18, &c_n3);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR */

    cterm_(&c__2);

/* 	NOW PLOT 3-D SURFACE USING 3-D MESH (HIDDEN LINES) WITH A */
/* 	CONTOUR PLOT AND INTERCONNECT PATH */

    for (i = 1; i <= 25; ++i) {
	xx[i - 1] = (i - 1) * (float).2 - (float)1.;
	j = (i - 1) * 3 + 1;
	ip[j - 1] = 2;
	ip[j] = i;
	ip[j + 1] = i;
	if (i > 12) {
	    ip[j] = 12;
	}
	ip[j + 2] = 0;
/* L42: */
    }
    iline[0] = 1;

    cvax3d_(d, &c__25, &c__25, &c__25, &c__25, &c_b493, &c_b494, &c_b238, &
	    c_b435, &c_b29, &c_b216, &c__21, &c_b500, &c__11, xx, &c_n1, &
	    c_n3, iline, ip, "X TITLE", &c__7, &c_b18, &c_b286, "Y TITLE", &
	    c__7, "Z TITLE", &c__7, &c_b512, &c_b55, &d1, &d2, icol);

/* 	RESTORE LINETYPE AND ADD LABEL AFTER MASTER ROUTINE CALL */

    newpen_(&c__1);
    cterm_(&c_n1);
    symbol_(&c_b516, &c_b18, &c_b63, "CVAX3D", &c_b85, &c__6, &c_n1);

/* 	PROMPT FOR SCREEN CLEAR, NOTE PENUP AFTER SYMBOL */
/* 	CALL TO FORCE OUTPUT TO SCREEN BEFORE CTERM CALL */

    plot_(&c_b18, &c_b18, &c__3);
    cterm_(&c__2);
    rterm_(&c__2);
    newpage_();

/* 	MOVE ORIGINS */

    plot_(&c_b357, &c_b18, &c_n3);
    plotvt_(&c_b286, &c_b18, &c_n3);

/* 	NOW PLOT 3-D HISTOGRAM WITH HIDDEN LINES REMOVED, WITH AXIS, ETC. */

    mvax3d_(d, &c__25, &c__25, &c__25, &c__25, &c_b493, &c_b494, &c_b238, &
	    c_b58, &c_b29, &c_b543, &c_n1, "MVAX3DX X TITLE", &c__15, &c_b547,
	     &c_b43, "MVAX3DX Y TITLE", &c__15, "Z TITLE", &c__7, &c_b88, &
	    c_b4, &c_b88, &c_b4, icol);

/* 	ADD LABEL AFTER MASTER ROUTINE CALL */

    cterm_(&c_n1);
    symbol_(&c_b18, &c_b18, &c_b63, "MVAX3DX", &c_b18, &c__6, &c_n1);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR AND MOVE ORIGINS */

    plot_(&c_b18, &c_b135, &c_n3);
    plotvt_(&c_b18, &c_b269, &c_n3);
    cterm_(&c__2);

/* 	NOW FOR AN EXAMPLE OF GLPLOT WITH FORMATTED AXIES */

    glplot_(x, y2, &c__2, &c__25, &c__2, &c__15, &c_b576, &c__3, &c_b124, &
	    c_b55, &c_b580, &c_b362, &c_b582, "X Axis", &c__6, &c_b585, &
	    c_b16, &c_b587, "Y Axis", &c__6, "GLPLOT Title", &c_n112, &d1, &
	    d2, &d3, &d4, icol, iline);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR AND MOVE ORIGINS */

    cterm_(&c__2);
    plot_(&c_b286, &c_b269, &c_n3);
    plotvt_(&c_b357, &c_b135, &c_n3);

/* 	SET UP SOME DATA TO PLOT USING EXISTING ARRAYS */

    for (i = 1; i <= 25; ++i) {

/* 	DETERMANTISTIC FUNCTION FOR SIESPL */

	x[i - 1] = (real) i;
	y2[i - 1] = sin(i * (float).9);
	y2[i + 24] = cos(i * (float)2.);

/* 	FUNCTION PLUS ERROR BARS TO ILLUSTRATE SPLOTS */

	y3[i - 1] = sin(i * (float).4);
	y3[i + 24] = y3[i - 1] - ran_(&is) * (float).5;
	y3[i + 49] = y3[i - 1] + ran_(&is) * (float).7;
/* L30: */
    }
    xx[0] = (float)0.;
    xx[1] = (float)1.4;

/* 	AN EXAMPLE OF SIESPL */

    seispl_(x, y2, xx, &c__2, &c__25, &c__2, &c__20, &c_b604, &c_n6, &c_b606, 
	    &c_b18, &c_b238, &c_b29, "X Title", &c__7, "Y Title", &c__7, 
	    "SIESPL", &c_n6, &d1, &d2, &d3, &d4, icol);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR AND MOVE ORIGINS */

    cterm_(&c__2);
    plot_(&c_b18, &c_b135, &c_n3);
    plotvt_(&c_b18, &c_b269, &c_n3);

/* 	AN EXAMPLE OF SPLOTS */

    splots_(x, y3, &c__3, &c__25, &c__1, &c__25, &c_b627, &c__11, &c_b629, &
	    c_b238, &c_b29, "X Title", &c__7, "Y Title", &c__7, "SPLOTS", &
	    c__6);

/* 	PROMPT FOR TERMINAL SCREEN CLEAR AND MOVE ORIGINS */
/* 	NEWPAGE ON METAFILE */

    cterm_(&c__2);
    rterm_(&c__2);
    plot_(&c_b357, &c_b269, &c_n3);
    plotvt_(&c_b286, &c_b135, &c_n3);
    plotnd_();

    exit(0);
    
}



/* Subroutine */ int covarit_(xrms, yrms, xcenter, ycenter, xy, t)
real *xrms, *yrms, *xcenter, *ycenter, *xy, *t;
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(), atan2();

    /* Local variables */
    static real r, x, y, ev1, ev2, xy1;


/* 	SUBROUTINE TO COMPUTE COVARIANCE MATRIX ROTATION ANGLE */

/* Computing 2nd power */
    r__1 = *xrms + *yrms;
/* Computing 2nd power */
    r__2 = *xy;
    r = r__1 * r__1 - (*xrms * *yrms - r__2 * r__2) * 4;
    xy1 = *xy;
    *t = (float)0.;
    if (*xy == (float)0.) {
	goto L10;
    }

/* 	TEST FOR BAD COVARIANCE MATRIX */

    if (r < (float)0.) {
/* Computing 2nd power */
	r__1 = *xrms + *yrms;
	xy1 = sqrt(*xrms * *yrms - r__1 * r__1 / (float)4.);
	ev1 = (*xrms + *yrms) / (float)2.;
	ev2 = ev1;
    } else {
	ev1 = (*xrms + *yrms + sqrt(r)) / (float)2.;
	ev2 = (*xrms + *yrms - sqrt(r)) / (float)2.;
    }
/* Computing 2nd power */
    r__1 = *yrms - ev1;
/* Computing 2nd power */
    r__2 = xy1;
/* Computing 2nd power */
    r__3 = *yrms - ev1;
    x = sqrt(r__1 * r__1 / (r__2 * r__2 + r__3 * r__3));
/* Computing 2nd power */
    r__1 = xy1;
/* Computing 2nd power */
    r__2 = xy1;
/* Computing 2nd power */
    r__3 = *yrms - ev1;
    y = sqrt(r__1 * r__1 / (r__2 * r__2 + r__3 * r__3));
    *t = atan2(y, x) * (float)180. / (float)3.141592654;
    *xrms = ev1;
    *yrms = ev2;
L10:
    return 0;
} /* covarit_ */


doublereal ran_(is)
integer *is;
{
    /* System generated locals */
    real ret_val, r__1;

    /* Builtin functions */
    double cos();

    *is = (*is + 9898911) % 1121241;
    ret_val = (r__1 = cos((real) (*is)), dabs(r__1));
    return ret_val;
} /* ran_ */

