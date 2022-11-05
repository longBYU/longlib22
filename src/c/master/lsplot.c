
/* *** LAST REVISED ON 21-JAN-1994 11:30:54.74 */
/* *** SOURCE FILE: [LONGD]LSPLOT.C */

#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static real c_b3 = (float)1.5;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__1 = 1;
static real c_b16 = (float)0.;
static real c_b43 = (float)90.;
static integer c__0 = 0;

/* Subroutine */ int lsplot_(x, y, ndp, ndl, iflag, f, c, nc)
real *x, *y;
integer *ndp, *ndl, *iflag;
real *f;
char *c[];
integer *nc;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer x_dim1, x_offset, y_dim1, y_offset, i__1, i__2, i__3, i__4;
    real r__1, r__2, r__3;
    char ch__1[1];

    /* Builtin functions */
    double r_lg10();

    /* Local variables */
    static real ebar;
    static integer nbar;
    static real glen;
    static integer jcol, ipen;
    extern /* Subroutine */ int rect_();
    static real xleg, yleg, xlen, ylen, zref;
    extern /* Subroutine */ int plot_();
    static integer isym, jsym, ksym;
    extern /* Subroutine */ int axis3_();
    static integer i, j, k;
    static integer jebar, kebar, icoff;
    extern /* Subroutine */ int scale_(), frame_();
    static real csleg;
    static integer jgrid, iloff, jline;
    extern /* Subroutine */ int lgrid_();
    static integer jconn;
    extern /* Subroutine */ int cterm_(), lgaxs_();
    static real xtick, ytick;
    static integer jxlog, jylog, jxrax, jyrax, jxuse, jxnum, jynum;
    static real x1, x2, y1, y2, x3, y3;
    static integer ic[4], na, jf, ng, nl;
    static real dx, dy;
    static integer np;
    static real fx, fy;
    static integer jlegnd;
    static real xm, ym;
    static integer jlegli;
    static real xx, yx, xy;
    static integer jvline;
    extern /* Subroutine */ int newpen_();
    static integer jxlgax, jylgax, jlegsy;
    extern /* Subroutine */ int plotnd_();
    static integer jszref, jtcntr;
    extern /* Subroutine */ int symbol_();
    static integer jxauto, jyauto, jxnums, jynums, jsymst;
    static real symsiz;
    static integer icc;
    static real tcs, xcs, smo[2], ycs;
    static integer jxticks, jyticks, jxtitle, jytitle, jxexpsc, jyexpsc;


/* 	ROUTINE FOR PLOTTING LINES */

/* 	WRITTEN:  DGL SEPT. 1987 */


/* 	X	(R) X INPUT ARRAY DIMENSIONED X(NDP,NDL) */
/* 		    NOTE: DEPENDING ON OPTIONS SELECTED, X */
/* 		    ACTUALLY MAY BE DIMENSIONED X(NDP) */
/* 	Y	(R) Y INPUT ARRAY DIMENSIONED Y(NDP,NDL) */
/* 	NDP	(I) NUMBER OF POINTS PER LINE DIMENSION */
/* 	NDL	(I) NUMBER OF LINES DIMENSION */
/* 	IFLAG	(R) PLOTTING FLAG */
/* 		    < 0 DON'T CLOSE PLOT PACKAGE */
/* 		    = 0 CLOSE PLOT PACKAGE WITHOUT PLOTTING */
/* 		    > 0 CLOSE PLOT PACKAGE */
/* 		MAG > 10000 INIT PLOT PACKAGE */
/* 	(HUNDRED'S) = SCREEN GRAPHICS DEVICE (SEE FRAME) */
/* 	F	(R) OPTIONS ARRAY (DESCRIBED BELOW) */
/* 	C	(R) TITLES ARRAY */
/* 		     C(1) X AXIS TITLE */
/* 		     C(2) Y AXIS TITLE */
/* 		     C(3) CHART TITLE */
/* 		     C(4) LEGEND TEXT FOR LINE 1 (IF LEGEND ENABLED) */
/* 		     C(5) LEGEND TEXT FOR LINE 2 (IF LEGEND ENABLED) */
/* 		     ...   ... */
/* 	NC	(I) NUMBER OF CHARACTERS IN TITLE ARRAY */
/* 		    NC(1) NUMBER OF CHARACTERS IN C(1) */
/* 		    NC(2) NUMBER OF CHARACTERS IN C(2) */
/* 		    ...    ... */
/* 		    ETC.  NOTE: IF NC(I) IS ZERO C(I) IS NOT PLOTTED */

/* 	THE ELEMENTS OF F ARE INTERPRETTED ACCORDING THE THE FOLLOWING: */
/* 	DEFAULT VALUES ARE SHOWN IN SQUARE BRACKETS */

/*   INDEX OF F	VALUE    ACTION */
/*  ____________ _____   ___________________ */
/* 	1      0<.<=NDP NUMBER OF POINTS PLOTTED [NDP] */
/* 	2      0<.<=NDL NUMBER OF LINES PLOTTED [NL] */
/* 	3	-1/0/1	X AUTO SCALING: 0=AUTO,SMOOTH; 1=AUTO,NOSMOOTH; -1=USER */
/* 	4	XMIN    USER SUPPLIED SCALE VALUE (USED IF F(3)<0) */
/* 	5	XMAX    USER SUPPLIED SCALE VALUE (USED IF F(3)<0) */
/* 	6	-1/0/1	Y AUTO SCALING: 0=AUTO,SMOOTH; 1=AUTO,NOSMOOTH; -1=USER */
/* 	7	YMIN    USER SUPPLIED SCALE VALUE (USED IF F(6)<0) */
/* 	8	YMAX    USER SUPPLIED SCALE VALUE (USED IF F(6)<0) */
/* 	9	0/1	USE X VALUES WITH Y VALUES: 0=ONLY FIRST LINE OF */
/* 			X DATA USED FOR ALL Y LINES; 1=LINES OF X/Y USED */
/* 	10	0/1	CONNECT PLOTTED POINTS: 0=YES; 1=NO */
/* 	11	>=0	SYMBOL PLOTTED EVERY ()TH POINT: 0=NO SYMBOLS */
/* 	12	>=0	SYMBOL SIZE [0.1]: 0=USE DEFAULT */
/* 	13	>=0	SYMBOL NUMBER FOR FIRST DATA LINE */
/* 	14     -8<.<8	SHOW ERROR BARS: 0=NO ERROR BARS */
/* 			WHEN NON-ZERO, CHANGES INTERPRETATION OF LINES */
/* 			POINTS EVERY THIRD LINE ARE PLOTTED.  RELATIVE */
/* 			ERROR (UPPER,LOWER) ARE THE FOLLOWING TWO LINES. */
/* 			PLOTTED RELATIVE ERROR COMPUTED AS SUM OF FIRST */
/* 			LINE PLUS SECOND/THIRD. */
/* 		  <0    AN X IS MADE AT THE CENTER POINT */

/* 		ABS(.)  TYPE OF ERROR BAR */
/* 		------  --------------------------------------------------- */
/* 		  1	LINE CONNECTING 2ND/3RD RELATIVE ERRORS */
/* 		  2	1+HORIZONTAL BARS OF WIDTH EBAR AT 2ND/3RD REL ERR */
/* 		  3	1+VERTICAL BARS OF WIDTH EBAR AT 2ND/3RD REL ERR */
/* 		  4	2 LINES SPACED EBAR/2+HORIZONTAL BARS WIDTH=EBAR */
/* 		  5	2 LINES SPACED EBAR/2+VERTICAL BARS WIDTH=EBAR */
/* 		  6	VERTICAL RECTANGLE FROM 2ND/3RD WITH WIDTH=EBAR */
/* 		  7     RECTANGLE WITH CORNER AT 2ND/3RD REL ERROR */

/* 	16	>=0	ERROR BAR SIZE [0.1]: 0=DEFAULT USED */
/* 	17	0/1	VERTICAL DRAWN LINE FROM POINT TO REFERENCE VALUE: */
/* 			0=NO; 1=YES */
/* 	18		REFERENCE VALUE */
/* 	19	-1/0/1	X AXIS TYPE: 0=LINEAR; 1=LOG AXIS, -1=NO AXIS */
/* 	20	-1/0/1	Y AXIS TYPE: 0=LINEAR; 1=LOG AXIS, -1=NO AXIS */
/* 	21	>=0	X AXIS LENGTH [7.0]: 0=DEFAULT USED */
/* 	22	>=0	Y AXIS LENGTH [5.0]: 0=DEFAULT USED */
/* 	23	>=0	X AXIS TICK PATTERN (SEE AXIS3) [7.00]: 0=DEFAULT */
/* 	24	>=0	Y AXIS TICK PATTERN (SEE AXIS3) [5.00]: 0=DEFAULT */
/* 	25	0/1	X AXIS TITLE SIDE OF AXIS: 0=BELOW; 1=ABOVE */
/* 	26	0/1	Y AXIS TITLE SIDE OF AXIS: 0=LEFT; 1=RIGHT */
/* 	27	0/1	X AXIS AUTO EXPONENT ENABLE: 0=ENABLE; 1=DISABLE */
/* 	28	0/1	Y AXIS AUTO EXPONENT ENABLE: 0=ENABLE; 1=DISABLE */
/* 	29	0/1	X AXIS TICK SIDE: 0=BELOW; 1=ABOVE */
/* 	30	0/1	Y AXIS TICK SIDE: 0=LEFT; 1=RIGHT */
/* 	31	0/1	X AXIS NUMBERS ORIENTATION: 0=HORIZONTAL; 1=VERTICAL */
/* 	32	0/1	Y AXIS NUMBERS ORIENTATION: 0=VERTICAL; 1=HORIZONTAL */
/* 	33	0/1	X AXIS NUMBERS/TITLE SHWON: 0=SHOWN; 1=NOT SHOWN */
/* 	34	0/1	Y AXIS NUMBERS/TITLE SHWON: 0=SHOWN; 1=NOT SHOWN */
/* 	35	0/1	TAKE LOG10(ABS(X VALUES)+1.E-34): 0=NO; 1=YES */
/* 	36	0/1	TAKE LOG10(ABS(Y VALUES)+1.E-34): 0=NO; 1=YES */
/* 	37	-1/0/1	ADD MIRROR X AXIS: 0=NO; 1=WITH LABELS; -1:W/O LABELS */
/* 	38	-1/0/1	ADD MIRROR Y AXIS: 0=NO; 1=WITH LABELS; -1:W/O LABELS */
/* 	39	>=0	X AXIS LABEL SIZE [0.15]: 0=USE DEFAULT */
/* 	40	>=0	Y AXIS LABEL SIZE [0.15]: 0=USE DEFAULT */
/* 	41	>=0	TOP TITLE CHARACTER SIZE [0.18]: 0=USE DEFAULT */
/* 	42	0/1/2/3	GRID OPTION: 0=NO GRID; 1=SOLID; 2=DOTTED; 3=TICKED */
/* 	43	-1/0/1	LINE/SYMBOL LEGEND: 0=NO LEGEND; 1=AUTO PLACE; -1=USER */
/* 	44	X	USER SPECIFIED LOWER-LEFT CORNER OF LEGEND */
/* 	45	Y	USER SPECIFIED LOWER-LEFT CORNER OF LEGEND */
/* 	46	0/1	SHOW PLOT SYMBOL WITH LEGEND: 0=NO; 1=YES */
/* 	47	0/1	SHOW LINE SEGMENT ON LEGEND: 0=NO; 1=YES */
/* 	48	>=0	LEGEND CHARACTER HEIGHT [0.12]: 0=USE DEFAULT */
/* 	49	>=0	LEGEND SEGMENT LENGTH [0.5]: 0=USE DEFAULT */
/* 	50	-1/0/1	TOP TITLE JUSTIFY: 0=CENTER; -1:LEFT; 1:RIGHT */
/* 	51	0/1	PLOT HORIZONTAL REFERENCE LINE: 0=NO; 1=YES */
/* 	52	0/1	USE LINE TYPE ARRAY VALUES: 0=NO; 1=YES */
/* 	53	0/1	USE COLOR ARRAY VALUES: 0=NO; 1=YES */
/* 	54	>=0	COLOR INDEX 1: 0=COLOR 1 USED */
/* 	55	>=0	LINETYPE INDEX 1 */
/* 	56	>=0	COLOR INDEX 2: 0=COLOR 1 USED */
/* 	57	>=0	LINETYPE INDEX 2 */
/* 	...		... ETC ... */

/* 	INDEX		COLOR USAGE	LINETYPE USAGE */
/* 	-------		------------    -------------- */
/* 	  1	        X AXIS		X AXIS */
/* 	  2	      X AXIS NUMBERS	Y AXIS */
/* 	  3	      X AXIS TITLE	TITLE */
/* 	  4	      X AXIS EXPONENT	LEGEND TITLES */
/* 	  5		Y AXIS		ZERO REF LINETYPE */
/* 	  6	      Y AXIS NUMBERS	ERROR BAR LINETYPES */
/* 	  7	      Y AXIS TITLE	LINE 1 LINETYPE */
/* 	  8	      Y AXIS EXPONENT     ETC. */
/* 	  9	        TITLE		  ... */
/* 	 10		LEGEND TITLES	  ... */
/* 	 11		ZERO REF LINE	  ... */
/* 	 12		GRID COLOR	  ... */
/* 	 13		LINE 1 COLOR	  ... */
/* 	...		... ETC. ...      ... */

    /* Parameter adjustments */
    --nc;
    --f;
    y_dim1 = *ndp;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    x_dim1 = *ndp;
    x_offset = x_dim1 + 1;
    x -= x_offset;

    /* Function Body */

/* 	INTIALIZE ROUTINE AND PLOT PACKAGE IF REQUIRED */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();		/* CLOSE PLOTTER */
	}
	repeat = FALSE_;
	return 0;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	jf /= 100;				/* GRAPHICS DEVICE CODE */
	frame_(&c__3, &jf, &c_b3, &c_b4, &c_b4);/* INTIALIZE */
    } else {
	cterm_(&c_n1);				/* PUT TERMINAL IN PLOT MODE */
    }

/* 	ESTABLISH DEFAULTS */

    np = *ndp;					/* NUMBER OF POINTS/LINE */
    nl = *ndl;					/* NUMBER OF LINES */
    xm = x[x_dim1 + 1];				/* MIN X VALUE */
    xx = xm;					/* MAX X VALUE */
    ym = y[y_dim1 + 1];				/* MIN Y VALUE */
    yx = ym;					/* MAX Y VALUE */
    fx = (float)5.01;				/* X AXIS NUMBER FORMAT */
    fy = (float)5.01;				/* Y AXIS NUMBER FORMAT */
    xlen = (float)7.;				/* X AXIS LENGTH */
    ylen = (float)5.;				/* Y AXIS LENGTH */
    xtick = (float)7.;				/* X AXIS TICK PATTERN */
    ytick = (float)6.;				/* Y AXIS TICK PATTERN */
    xcs = (float).15;				/* X AXIS TITLE SIZE */
    ycs = (float).15;				/* Y AXIS TITLE SIZE */
    tcs = (float).18;				/* OVERALL TITLE SIZE */
    ebar = (float).1;				/* ERROR BAR SIZE */
    symsiz = (float).1;				/* SYMBOL SIZE */
    csleg = (float).12;				/* LEGEND CHARACTER SIZE */
    glen = (float).5;				/* LEGEND LINE LENGTH */

/* 	READ OPTIONS ARRAY */

    if (f[1] > (float)0.) {
	np = f[1];				/* NUMBER OF POINT/LINE */
    }
    if (np > *ndp) {
	np = *ndp;
    }
    if (f[2] > (float)0.) {
	nl = f[2];				/* NUMBER OF LINES */
    }
    if (nl > *ndl) {
	nl = *ndl;
    }
    jxauto = f[3];		/* AUTO SCALE X, 0=YES/SMOOTH,-1=NO/USER */
/* 				  		 1=YES/NO SMOOTH	 */

    if ((real) jxauto < (float)0.) {	/* INPUT X AXIS SCALE FACTORS */
	xm = f[4];			/* MIN X (OTHERWISE RETURNED) */
	xx = f[5];			/* MAX X */
    }
    jyauto = f[6];		/* AUTO SCALE Y, 0=YES/SMOOTH,-1=NO/USER */
/* 						 1=YES/NO SMOOTH 	 */

    if ((real) jyauto < (float)0.) {	/* INPUT Y AXIS SCALE FACTORS */
	ym = f[7];			/* MIN Y (OTHERWISE RETURNED) */
	yx = f[8];			/* MAX Y */
    }
    jxuse = abs(f[9]);			/* USE X LINES WITH Y LINES,0=NO,1=YES */
    jconn = abs(f[10]);			/* CONNECT POINTS WITH LINES,0=YES,1=NO */
    jsym = abs(f[11]);			/* PLOT SYMBOL EVERY JSYM PT,0=NO SYMS */
    if (f[12] > (float)0.) {
	symsiz = f[12];			/* SYMBOL SIZE */
    }
    jsymst = abs(f[13]);		/* STARTING PLOT SYMBOL NUMBER */
    jebar = f[14];

/* 		|JEBAR|  ERROR BAR (CLINE IS LINE CONNECT 2ND/3RD REL. ERR) */
/* 		-------  --------------------------------------------------- */
/* 		  1	  CLINE */
/* 		  2	  CLINE+HORIZONTAL BARS WIDTH=EBAR */
/* 		  3	  CLINE+VERTICAL BARS WIDTH=EBAR */
/* 		  4	  DOUBLE CLINE+HORIZONTAL BARS WIDTH=EBAR */
/* 		  5	  DOUBLE CLINE+VERTICAL BARS WIDTH=EBAR */
/* 		  6	  VERTICAL RECTANGLE WIDTH=EBAR */
/* 		  7       RECTANGLE DEFINED BY 2ND/3RD REL ERROR */

/* 		NOTE: IF JBAR < 0 AN X (SIZE EBAR) IS USED TO MARK 1ST LINE */

    kebar = abs(jebar);			/* TYPE OF ERROR BAR,0=NOT USED */
    nbar = 1;
    if (jebar != 0) {
	nbar = 3;
    }
    if (f[16] > (float)0.) {
	ebar = f[16];
    }
/* 					  1ST LINE DEFINES CENTER */
/* 					  2ND IS LOWER REL. ERROR */
/* 					  3RD IS UPPER REL. ERROR */
/* ERROR BAR SIZE */
    jvline = f[17];			/* VERTICAL LINE TO ZVAL,0=NO,1=YES */
    /*    zval = f[18]; */			/* ZERO REFERENCE VALUE */
    jxlgax = f[19];			/* X AXIS, LINEAR=0/LOG=1/NONE=-1 */
    jylgax = f[20];			/* Y AXIS, LINEAR=0/LOG=1/NONE=-1 */
    if (f[21] > (float)0.) {
	xlen = f[21];			/* X AXIS LENGTH */
    }
    if (f[22] > (float)0.) {
	ylen = f[22];			/* Y AXIS LENGTH */
    }
    if (f[23] > (float)0.) {
	xtick = f[23];			/* X AXIS TICK PATTERN */
    }
    if (f[24] > (float)0.) {
	ytick = f[24];			/* Y AXIS TICK PATTERN */
    }
    jxtitle = abs(f[25]);		/* X AXIS TITLE SIDE,0=CW,1=CCW */
    if (jxtitle == 0) {
	jxtitle = -1;
    } else {
	jxtitle = 1;
    }
    jytitle = abs(f[26]);		/* Y AXIS TITLE SIDE,0=CCW,1=CW */
    if (jytitle == 0) {
	jytitle = 1;
    } else {
	jytitle = -1;
    }
    jxexpsc = abs(f[27]);	/* X AXIS ENABLE AUTO EXPONENT,0=YES,1=NO */
    jyexpsc = abs(f[28]);	/* Y AXIS ENABLE AUTO EXPONENT,0=YES,1=NO */
    jxticks = abs(f[29]);	/* X AXIS TICKS TITLE SIDE,0=YES,1=NO */
    jyticks = abs(f[30]);	/* Y AXIS TICKS TITLE SIDE,0=YES,1=NO */
    jxnums = abs(f[31]);	/* X AXIS NUMS PARA AXIS, 0=YES,1=NO */
    jynums = abs(f[32]);	/* Y AXIS NUMS PARA AXIS, 0=YES,1=NO */
    jxnum = abs(f[33]);		/* X AXIS NUMS SHOWN, 0=YES,1=NO */
    jynum = abs(f[34]);		/* Y AXIS NUMS SHOWN, 0=YES,1=NO */
    jxlog = abs(f[35]);		/* TAKE LOG OF X VALUES, 0=NO,1=YES */
    jylog = abs(f[36]);		/* TAKE LOG OF Y VALUES, 0=NO,1=YES */
    jxrax = f[37];	/* ADD AXIS OPPOSITE, 0=YES,-1=W/L,1=NO LABELS */
    jyrax = f[38];	/* ADD AXIS OPPOSITE, 0=YES,-1=W/L,1=NO LABELS */
    if (f[39] > (float)0.) {
	xcs = f[39];		/* X AXIS TITLE SIZE */
    }
    if (f[40] > (float)0.) {
	ycs = f[40];		/* Y AXIS TITLE SIZE */
    }
    if (f[41] > (float)0.) {
	tcs = f[41];		/* OVERALL TITLE SIZE */
    }
    jgrid = f[42];		/* GRID OPTION, 0=NONE,1=SOLID,2=DOTTED */
    jlegnd = f[43];		/* ADD LEGEND, 0=NONE,1=AUTO,-1=USER */
    xleg = xlen + (float).3;	/* DEFAULT LEGEND LOCATION */
    yleg = (float).5;
    if (jlegnd < 0) {
	xleg = f[44];		/* X LEGEND LOCATION */
    }
    if (jlegnd < 0) {
	yleg = f[45];		/* Y LEGEND LOCATION */
    }
    jlegsy = f[46];		/* USE SYMBOL ON LEGEND,0=NO,1=YES */
    jlegli = f[47];		/* USE LINETYPE ON LEGEND,0=NO,1=YES */
    if (f[48] > (float)0.) {
	csleg = f[48];		/* LEGEND CHARACTER SIZE */
    }
    if (f[49] > (float)0.) {
	glen = f[49];		/* LEGEND LINE LENGTH */
    }
    jtcntr = f[50];		/* CENTER TITLE,0=YES,-1=LEFT,1=RIGHT */
    jszref = f[51];		/* SHOW ZERO REFERENCE,0=NO,1=YES */
    jline = f[52];		/* USE LINE TYPES,0=NO,1=YES */
    jcol = f[53];
/* 	F(54)=FIRST COLOR */
/* 	F(55)=FIRST LINETYPE */
/* 	F(56)=SECOND COLOR */
/* 	F(57)=SECOND LINETYPE */
/* 	... */
/* USE COLORS,0=NO,1=YES */

    icoff = 54;
    iloff = 55;

/* 	COMPUTE SCALING */

    if (jxauto >= 0) {					/* AUTO SCALE X */
	x1 = dabs(xm);
	x2 = x1;
	i__1 = np;
	for (i = 1; i <= i__1; ++i) {
	    k = 1;
	    if (jxuse != 0) {
		k = nl;
	    }
	    i__2 = k;
	    i__3 = nbar;
	    for (j = 1; i__3 < 0 ? j >= i__2 : j <= i__2; j += i__3) {
		r__1 = xm, r__2 = x[i + j * x_dim1];
		xm = dmin(r__1,r__2);
		r__2 = x1, r__3 = (r__1 = x[i + j * x_dim1], dabs(r__1));
		x1 = dmin(r__2,r__3);
		r__1 = xx, r__2 = x[i + j * x_dim1];
		xx = dmax(r__1,r__2);
		r__2 = xx, r__3 = (r__1 = x[i + j * x_dim1], dabs(r__1));
		x2 = dmax(r__2,r__3);
		if (jebar != 0 && jxuse != 0) {
		    r__1 = xm, r__2 = x[i + j * x_dim1] + x[i + 1 + j * 
			    x_dim1];
		    xm = dmin(r__1,r__2);
		    r__2 = x1, r__3 = (r__1 = x[i + j * x_dim1] + x[i + 1 + j 
			    * x_dim1], dabs(r__1));
		    x1 = dmin(r__2,r__3);
		    r__1 = xx, r__2 = x[i + j * x_dim1] + x[i + 1 + j * 
			    x_dim1];
		    xx = dmax(r__1,r__2);
		    r__2 = x2, r__3 = (r__1 = x[i + j * x_dim1] + x[i + 1 + j 
			    * x_dim1], dabs(r__1));
		    x2 = dmax(r__2,r__3);
		    r__1 = xm, r__2 = x[i + j * x_dim1] + x[i + 2 + j * 
			    x_dim1];
		    xm = dmin(r__1,r__2);
		    r__2 = x1, r__3 = (r__1 = x[i + j * x_dim1] + x[i + 1 + j 
			    * x_dim1], dabs(r__1));
		    x1 = dmin(r__2,r__3);
		    r__1 = xx, r__2 = x[i + j * x_dim1] + x[i + 2 + j * 
			    x_dim1];
		    xx = dmax(r__1,r__2);
		    r__2 = x2, r__3 = (r__1 = x[i + j * x_dim1] + x[i + 1 + j 
			    * x_dim1], dabs(r__1));
		    x2 = dmax(r__2,r__3);
		}
/* L5: */
	    }
	}
	if (jxlog != 0) {
	    r__1 = x1 + (float)1e-34;
	    xm = r_lg10(&r__1);
	    r__1 = x2 + (float)1e-34;
	    xx = r_lg10(&r__1);
	}
	if (jxauto > 0 && jxlgax == 0) {	/* SMOOTH SCALING */
	    smo[0] = xm;
	    smo[1] = xx;
	    scale_(smo, &xlen, &c__2, &c__1, &c__1, &xm, &dx);
	    xx = xm + xlen * dx;
	}
	if (jxlgax != 0) {			/* LOG AXIS SCALING */
	    if (xm <= (float)0. && xm != (real) ((integer) xm)) {
		xm += (float)-1.;
	    }
	    xm = (real) ((integer) xm);
	    if (xx > (float)0. && xx != (real) ((integer) xx)) {
		xx += (float)1.;
	    }
	    xx = (real) ((integer) xx);
	}
	if (xx == xm) {
	    xx = xm + (float)1.;
	}
/* 	RETURN SCALE FACTORS USED */
	f[4] = xm;
	f[5] = xx;
    }
    if (jyauto >= 0) {					/* AUTO SCALE Y */
	y1 = abs(ym);
	y2 = y1;
	i__3 = np;
	for (i = 1; i <= i__3; ++i) {
	    i__2 = nl;
	    i__1 = nbar;
	    for (j = 1; i__1 < 0 ? j >= i__2 : j <= i__2; j += i__1) {
		r__1 = ym, r__2 = y[i + j * y_dim1];
		ym = dmin(r__1,r__2);
		r__2 = y1, r__3 = (r__1 = y[i + j * y_dim1], dabs(r__1));
		y1 = dmin(r__2,r__3);
		r__1 = yx, r__2 = y[i + j * y_dim1];
		yx = dmax(r__1,r__2);
		r__2 = yx, r__3 = (r__1 = y[i + j * y_dim1], dabs(r__1));
		y2 = dmax(r__2,r__3);
		if (jebar != 0) {
		    r__1 = ym, r__2 = y[i + j * y_dim1] + y[i + 1 + j * 
			    y_dim1];
		    ym = dmin(r__1,r__2);
		    r__2 = y1, r__3 = (r__1 = y[i + j * y_dim1] + y[i + 1 + j 
			    * y_dim1], dabs(r__1));
		    y1 = dmin(r__2,r__3);
		    r__1 = yx, r__2 = y[i + j * y_dim1] + y[i + 1 + j * 
			    y_dim1];
		    yx = dmax(r__1,r__2);
		    r__2 = y2, r__3 = (r__1 = y[i + j * y_dim1] + y[i + 1 + j 
			    * y_dim1], dabs(r__1));
		    y2 = dmax(r__2,r__3);
		    r__1 = ym, r__2 = y[i + j * y_dim1] + y[i + 2 + j * 
			    y_dim1];
		    ym = dmin(r__1,r__2);
		    r__2 = y1, r__3 = (r__1 = y[i + j * y_dim1] + y[i + 1 + j 
			    * y_dim1], dabs(r__1));
		    y1 = dmin(r__2,r__3);
		    r__1 = yx, r__2 = y[i + j * y_dim1] + y[i + 2 + j * 
			    y_dim1];
		    yx = dmax(r__1,r__2);
		    r__2 = y2, r__3 = (r__1 = y[i + j * y_dim1] + y[i + 1 + j 
			    * y_dim1], dabs(r__1));
		    y2 = dmax(r__2,r__3);
		}
/* L6: */
	    }
	}
	if (jylog != 0) {
	    r__1 = y1 + (float)1e-34;
	    ym = r_lg10(&r__1);
	    r__1 = y2 + (float)1e-34;
	    yx = r_lg10(&r__1);
	}
	if (jyauto > 0 && jylgax == 0) {	/* SMOOTH SCALING */
	    smo[0] = ym;
	    smo[1] = yx;
	    scale_(smo, &ylen, &c__2, &c__1, &c__1, &ym, &dy);
	    yx = ym + ylen * dy;
	}
	if (jylgax != 0) {			/* LOG AXIS SCALING */
	    if (ym <= (float)0. && ym != (real) ((integer) ym)) {
		ym += (float)-1.;
	    }
	    ym = (real) ((integer) ym);
	    if (yx > (float)0. && yx != (real) ((integer) yx)) {
		yx += (float)1.;
	    }
	    yx = (real) ((integer) yx);
	}
	if (yx == ym) {			/* 	RETURN SCALE FACTORS USED */
	    yx = ym + (float)1.;
	}
	f[7] = ym;
	f[8] = yx;
    }
    dx = (xx - xm) / xlen;
    dy = (yx - ym) / ylen;

/* 	PRODUCE PLOT X AXIS */

    if (jcol != 0) {			/* INITIALIZE COLOR AXIS ARRAY */
	for (i = 1; i <= 4; ++i) {
	    ic[i - 1] = (r__1 = f[(i << 1) + icoff - 2], dabs(r__1));
	    if (ic[i - 1] == 0) {
		ic[i - 1] = 1;
	    }
/* L10: */
	}
    }
    if (jline != 0) {
	i__1 = (integer) f[iloff];
	newpen_(&i__1);
    }

    if (jxexpsc != 0) {
	xcs = -(doublereal)xcs;
    }
    if (jxlgax == 0) {				/* LINEAR X AXIS */
	x1 = xlen;
	if (jxticks != 0) {
	    x1 = -(doublereal)xlen;
	}
	na = 1000;
	if (jxnum != 0) {
	    na += 100;
	}
	if (jcol != 0) {
	    na += 100000;
	}
	if (jxnums == 0) {
	    na += -1000;
	}
	if (nc[1] > 0) {			/* USE INPUT X AXIS TITLE */
	    na = (na + nc[1]) * jxtitle;
	    axis3_(&c_b16, &c_b16, c[0], &na, &x1, &c_b16, &xm, &xx, &
		    xtick, &xcs, &fx, ic);
	} else {				/* NO X AXIS TITLE */
	    na = (na + 1) * jxtitle;
	    axis3_(&c_b16, &c_b16, " ", &na, &x1, &c_b16, &xm, &xx, &xtick, &
		    xcs, &fx, ic);
	}
	if (jxrax != 0) {
	    na = 1000;
	    if (jxrax > 0) {
		na += 100;
	    }
	    if (jcol != 0) {
		na += 100000;
	    }
	    if (jxnums == 0) {
		na += -1000;
	    }
	    if (nc[1] > 0) {			/* USE INPUT X AXIS TITLE */
		na = -(na + nc[1]) * jxtitle;
		axis3_(&c_b16, &ylen, c[0], &na, &x1, &c_b16, &xm, &xx, &
			xtick, &xcs, &fx, ic);
	    } else {				/* NO X AXIS TITLE */
		na = (na + 1) * jxtitle;
		axis3_(&c_b16, &ylen, " ", &na, &x1, &c_b16, &xm, &xx, &xtick,
			 &xcs, &fx, ic);
	    }
	}
    } else if (jxlgax == 1) {			/* LOG X AXIS */
	x1 = xlen;
	if (jxticks != 0) {
	    x1 = -(doublereal)xlen;
	}
	na = 1000;
	if (jxnum != 0) {
	    na += 100;
	}
	if (jcol != 0) {
	    na += 10000;
	}
	if (jxnums == 0) {
	    na += -1000;
	}
	if (nc[1] > 0) {			/* USE INPUT X AXIS TITLE */
	    na = (na + nc[1]) * jxtitle;
	    lgaxs_(&c_b16, &c_b16, c[0], &na, &x1, &c_b16, &xm, &dx, ic);
	} else {				/* NO X AXIS TITLE */
	    na = (na + 1) * jxtitle;
	    lgaxs_(&c_b16, &c_b16, " ", &na, &x1, &c_b16, &xm, &dx, ic);
	}
	if (jxrax != 0) {
	    na = 1000;
	    if (jxrax > 0) {
		na += 100;
	    }
	    if (jcol != 0) {
		na += 10000;
	    }
	    if (jxnums == 0) {
		na += -1000;
	    }
	    if (nc[1] > 0) {	/* USE INPUT X AXIS TITLE */
		na = -(na + nc[1]) * jxtitle;
		lgaxs_(&c_b16, &ylen, c[0], &na, &x1, &c_b16, &xm, &dx, 
			ic);
	    } else {		/* NO X AXIS TITLE */
		na = -(na + 1) * jxtitle;
		lgaxs_(&c_b16, &ylen, " ", &na, &x1, &c_b16, &xm, &dx, ic);
	    }
	}
    }

/* 	PRODUCE PLOT Y AXIS */

    if (jcol != 0) {		/* INITIALIZE COLOR AXIS ARRAY */
	for (i = 1; i <= 4; ++i) {
	    ic[i - 1] = (r__1 = f[(i << 1) + icoff + 6], dabs(r__1));
	    if (ic[i - 1] == 0) {
		ic[i - 1] = 1;
	    }
/* L20: */
	}
    }
    if (jline != 0) {
	i__1 = (integer) f[iloff + 2];
	newpen_(&i__1);
    }

    if (jyexpsc != 0) {
	ycs = -(doublereal)ycs;
    }
    if (jylgax == 0) {				/* LINEAR Y AXIS */
	x1 = ylen;
	if (jyticks != 0) {
	    x1 = -(doublereal)ylen;
	}
	na = 1000;
	if (jynum != 0) {
	    na += 100;
	}
	if (jcol != 0) {
	    na += 100000;
	}
	if (jynums == 0) {
	    na += -1000;
	}
	if (nc[2] > 0) {			/* USE INPUT Y AXIS TITLE */
	    na = (na + nc[2]) * jytitle;
	    axis3_(&c_b16, &c_b16, c[1], &na, &x1, &c_b43, &ym, &
		    yx, &ytick, &ycs, &fy, ic);
	} else {				/* NO Y AXIS TITLE */
	    na = (na + 1) * jytitle;
	    axis3_(&c_b16, &c_b16, " ", &na, &x1, &c_b43, &ym, &yx, &ytick, &
		    ycs, &fy, ic);
	}
	if (jyrax != 0) {
	    na = 1000;
	    if (jyrax > 0) {
		na += 100;
	    }
	    if (jcol != 0) {
		na += 100000;
	    }
	    if (jynums == 0) {
		na += -1000;
	    }
	    if (nc[2] > 0) {		/* USE INPUT Y AXIS TITLE */
		na = -(na + nc[2]) * jytitle;
		axis3_(&xlen, &c_b16, c[1], &na, &x1, &c_b43, &ym,
			 &yx, &ytick, &ycs, &fy, ic);
	    } else {			/* NO Y AXIS TITLE */
		na = (na + 1) * jytitle;
		axis3_(&xlen, &c_b16, " ", &na, &x1, &c_b43, &ym, &yx, &ytick,
			 &ycs, &fy, ic);
	    }
	}
    } else if (jylgax == 1) {		/* LOG Y AXIS */
	x1 = ylen;
	if (jyticks != 0) {
	    x1 = -(doublereal)ylen;
	}
	na = 1000;
	if (jynum != 0) {
	    na += 100;
	}
	if (jcol != 0) {
	    na += 10000;
	}
	if (jynums == 0) {
	    na += -1000;
	}
	if (nc[2] > 0) {		/* USE INPUT Y AXIS TITLE */
	    na = (na + nc[2]) * jytitle;
	    lgaxs_(&c_b16, &c_b16, c[1], &na, &x1, &c_b43, &xy, &dy, ic);
	} else {			/* NO X AXIS TITLE */
	    na = (na + 1) * jytitle;
	    lgaxs_(&c_b16, &c_b16, " ", &na, &x1, &c_b43, &ym, &dy, ic);
	}
	if (jyrax != 0) {
	    na = 1000;
	    if (jyrax > 0) {
		na += 100;
	    }
	    if (jcol != 0) {
		na += 10000;
	    }
	    if (jynums == 0) {
		na += -1000;
	    }
	    if (nc[2] > 0) {		/* USE INPUT Y AXIS TITLE */
		na = -(na + nc[2]) * jytitle;
		lgaxs_(&xlen, &c_b16, c[1], &na, &x1, &c_b43, &ym, &dy, ic);
	    } else {			/* NO Y AXIS TITLE */
		na = -(na + 1) * jytitle;
		lgaxs_(&xlen, &c_b16, " ", &na, &x1, &c_b43, &ym, &dy, ic);
	    }
	}
    }

/* 	PLOT GRID */

    if (jgrid != 0) {
	if (jcol != 0) {
	    icc = (r__1 = f[icoff + 22], (integer) dabs(r__1));
	    if (icc < 1) {
		icc = 1;
	    }
	    r__1 = (real) icc;
	    plot_(&r__1, &c_b16, &c__0);
	}
	ng = jgrid - 1;
	i = (integer) xtick - 1;
	if (i < 1) {
	    i = 1;
	}
	x1 = xlen / (real) i;
	if (jxlgax > 0) {
	    i = 1 - (integer) (xlen * dx - xm + (float).001);
	    x1 = -(doublereal)xlen / (real) i;
	}
	j = (integer) ytick - 1;
	if (j < 1) {
	    j = 1;
	}
	y1 = ylen / (real) j;
	if (jylgax > 0) {
	    j = 1 - (integer) (ylen * dy - ym + (float).001);
	    y1 = -(doublereal)ylen / (real) j;
	}
	lgrid_(&c_b16, &c_b16, &x1, &y1, &i, &j, &ng);
    }

/* 	ADD TITLE */

    if (nc[3] > 0) {
	if (jline != 0) {
	    i__1 = (integer) f[iloff + 4];
	    newpen_(&i__1);
	}
	if (jcol != 0) {
	    icc = (r__1 = f[icoff + 16], (integer) dabs(r__1));
	    if (icc < 1) {
		icc = 1;
	    }
	    r__1 = (real) icc;
	    plot_(&r__1, &c_b16, &c__0);
	}
	icc = 0;
	x1 = xlen * (float).5;
	y1 = ylen + (float).1 + tcs * (float).2;
	if (jtcntr < 0) {
	    icc = -1;
	    x1 = (float)0.;
	    y1 -= tcs * (float).2;
	}
	if (jtcntr > 0) {
	    icc = 1;
	    x1 = xlen;
	    y1 -= tcs * (float).2;
	}
	if (jxrax < 0) {
	    y1 += xcs * (float)2.5;
	}
	symbol_(&x1, &y1, &tcs, c[2], &c_b16, &nc[3], &icc);
    }

/* PREPARE FOR PLOTTING */

    dx = (float)1.;
    dy = (float)1.;
    if (xx - xm != (float)0.) {
	dx = xlen / (xx - xm);
    }
    if (yx - ym != (float)0.) {
	dy = ylen / (yx - ym);
    }
    zref = (zref - ym) * dy;
    if (jszref != 0) {			/* SHOW ZERO REFERENCE LINE */
	if (jline != 0) {
	    i__1 = (integer) f[iloff + 8];
	    newpen_(&i__1);
	}
	if (jcol != 0) {
	    icc = (r__1 = f[icoff + 20], (integer) dabs(r__1));
	    if (icc < 1) {
		icc = 1;
	    }
	    r__1 = (real) icc;
	    plot_(&r__1, &c_b16, &c__0);
	}
	plot_(&c_b16, &zref, &c__3);
	plot_(&xlen, &zref, &c__2);
    }

/* PLOT THE ACTUAL DATA */

    i__1 = nl;
    i__2 = nbar;
    for (i = 1; i__2 < 0 ? i >= i__1 : i <= i__1; i += i__2) {
	if (jline != 0) {			/* LINE TYPE */
	    i__3 = (integer) f[2 * (i - 1) + iloff + 12];
	    newpen_(&i__3);
	}
	if (jcol != 0) {			/* COLOR */
	    icc = (r__1 = f[icoff + 24 + 2 * (i - 1) ], (integer) dabs(r__1));
	    if (icc < 1) {
		icc = 1;
	    }
	    r__1 = (real) icc;
	    plot_(&r__1, &c_b16, &c__0);
	}
	ksym = (i + jsymst - 1) % 17;		/* PLOT SYMBOL NUMBER */

/* 	IF WE NEED CONNECTING LINES MAKE A CONNECT PASS */

	ipen = 3;
	if (jconn == 0) {
	    i__3 = np;
	    for (j = 1; j <= i__3; ++j) {
		if (jxuse != 0) {
		    x1 = x[j + i * x_dim1];
		} else {
		    x1 = x[j + x_dim1];
		}
		if (jxlog != 0) {
		    r__1 = dabs(x1) + (float)1e-34;
		    x1 = r_lg10(&r__1);
		}
		x1 = (x1 - xm) * dx;
		y1 = y[j + i * y_dim1];
		if (jylog != 0) {
		    r__1 = dabs(y1) + (float)1e-34;
		    y1 = r_lg10(&r__1);
		}
		y1 = (y1 - ym) * dy;
		plot_(&x1, &y1, &ipen);
		ipen = 2;
/* L50: */
	    }
	}

/* 	ANOTHER PASS FOR SYMBOLS, ETC. */

	if (jconn != 0 && jebar == 0 && jvline == 0 && jsym == 0) {
	    goto L100;
	}
	isym = 0;
	i__3 = np;
	for (j = 1; j <= i__3; ++j) {
	    if (jxuse != 0) {
		x1 = x[j + i * x_dim1];
	    } else {
		x1 = x[j + x_dim1];
	    }
	    if (jxlog != 0) {
		r__1 = dabs(x1) + (float)1e-34;
		x1 = r_lg10(&r__1);
	    }
	    x1 = (x1 - xm) * dx;
	    y1 = y[j + i * y_dim1];
	    if (jylog != 0) {
		r__1 = dabs(y1) + (float)1e-34;
		y1 = r_lg10(&r__1);
	    }
	    y1 = (y1 - ym) * dy;
	    if (jsym != 0) {			/* SYMBOLS */
		if (isym % jsym == 0) {
		    ch__1[0] = ksym;
		    symbol_(&x1, &y1, &symsiz, ch__1, &c_b16, &c__1, &c_n1);
		}
	    }
	    if (jvline != 0) {			/* VERTICAL LINE */
		plot_(&x1, &y1, &c__3);
		plot_(&x1, &zref, &c__2);
	    }
	    if (jebar != 0) {			/* ERROR BAR */
		if (jline != 0) {
		    i__4 = (integer) f[iloff + 10];
		    newpen_(&i__4);
		}
		if (jxuse != 0) {
		    x2 = x[j + (i + 1) * x_dim1] + x[j + i * x_dim1];
		    x3 = x[j + (i + 2) * x_dim1] + x[j + i * x_dim1];
		    if (jxlog != 0) {
			r__1 = dabs(x2) + (float)1e-34;
			x2 = r_lg10(&r__1);
			r__1 = dabs(x3) + (float)1e-34;
			x3 = r_lg10(&r__1);
		    }
		    x2 = (x2 - xm) * dx;
		    x3 = (x3 - xm) * dx;
		} else {
		    x2 = x1;
		    x3 = x1;
		}
		y2 = y[j + (i + 1) * y_dim1] + y[j + i * y_dim1];
		y3 = y[j + (i + 2) * y_dim1] + y[j + i * y_dim1];
		if (jylog != 0) {
		    r__1 = dabs(y2) + (float)1e-34;
		    y2 = r_lg10(&r__1);
		    r__1 = dabs(y3) + (float)1e-34;
		    y3 = r_lg10(&r__1);
		}
		y2 = (y2 - ym) * dy;
		y3 = (y3 - ym) * dy;
		if (kebar == 2 || kebar == 5) {	/* ERROR BAR TOP */
		    r__1 = y2 - ebar;
		    plot_(&x2, &r__1, &c__3);
		    r__1 = y2 + ebar;
		    plot_(&x2, &r__1, &c__2);
		} else if (kebar == 3 || kebar == 4) {
		    r__1 = x2 - ebar;
		    plot_(&r__1, &y2, &c__3);
		    r__1 = x2 + ebar;
		    plot_(&r__1, &y2, &c__2);
		}
		if (kebar < 4) {		/* CONNECT LINE */
		    plot_(&x2, &y2, &c__3);
		    plot_(&x3, &y3, &c__2);
		} else if (kebar == 4) {	/* DOUBLE CONN V LINE */
		    r__1 = x2 - ebar * (float).5;
		    plot_(&r__1, &y2, &c__3);
		    r__1 = x3 - ebar * (float).5;
		    plot_(&r__1, &y3, &c__2);
		    r__1 = x3 + ebar * (float).5;
		    plot_(&r__1, &y3, &c__3);
		    r__1 = x2 + ebar * (float).5;
		    plot_(&r__1, &y2, &c__2);
		} else if (kebar == 5) {	/* DOUBLE CONN HLINE */
		    r__1 = y2 - ebar * (float).5;
		    plot_(&x2, &r__1, &c__3);
		    r__1 = y3 - ebar * (float).5;
		    plot_(&x3, &r__1, &c__2);
		    r__1 = y3 + ebar * (float).5;
		    plot_(&x3, &r__1, &c__3);
		    r__1 = y2 + ebar * (float).5;
		    plot_(&x2, &r__1, &c__2);
		} else if (kebar == 6) {	/* VERTICAL RECT */
		    r__1 = x1 - ebar;
		    r__2 = x1 + ebar;
		    rect_(&r__1, &y2, &r__2, &y3);
		} else if (kebar == 7) {	/* RECT */
		    rect_(&x2, &y2, &x3, &y3);
		}
		if (jebar < 0) {		/* X MARK */
		    r__1 = x1 - ebar;
		    r__2 = y1 - ebar;
		    plot_(&r__1, &r__2, &c__3);
		    r__1 = x1 + ebar;
		    r__2 = y1 + ebar;
		    plot_(&r__1, &r__2, &c__2);
		    r__1 = x1 - ebar;
		    r__2 = y1 + ebar;
		    plot_(&r__1, &r__2, &c__3);
		    r__1 = x1 + ebar;
		    r__2 = y1 - ebar;
		    plot_(&r__1, &r__2, &c__2);
		}
		if (kebar == 2 || kebar == 5) {	/* BAR BOTTOM */
		    r__1 = y3 - ebar;
		    plot_(&x3, &r__1, &c__3);
		    r__1 = y3 + ebar;
		    plot_(&x3, &r__1, &c__2);
		} else if (kebar == 3 || kebar == 4) {
		    r__1 = x3 - ebar;
		    plot_(&r__1, &y3, &c__3);
		    r__1 = x3 + ebar;
		    plot_(&r__1, &y3, &c__2);
		}
	    }
	    if (jsym == 0 && jconn == 0 && jebar == 0 && jvline == 0) {
		plot_(&x1, &y1, &c__3);		/* DOTS ONLY */
		plot_(&x1, &y1, &c__2);
	    }
	    ++isym;
/* L60: */
	}
L100:
	;
    }

/* 	ADD LEGEND */

    if (jlegnd != 0) {
	i__2 = nl;
	for (i = 1; i <= i__2; ++i) {
	    x1 = xleg + csleg * (float)1.5;
	    y1 = yleg + (i - 1) * csleg * (float)1.5 + csleg * (float).5;
	    if (jcol != 0) {
		icc = (r__1 = f[icoff + 24 + 2 * (i - 1) ], (integer) dabs(r__1));
		if (icc < 1) {
		    icc = 1;
		}
		r__1 = (real) icc;
		plot_(&r__1, &c_b16, &c__0);
	    }
	    if (jlegli != 0) {
		if (jline != 0) {
		    i__1 = (integer) f[2 * (i - 1) + iloff + 12];
		    newpen_(&i__1);
		}
		plot_(&x1, &y1, &c__3);
		r__1 = x1 + glen;
		plot_(&r__1, &y1, &c__2);
		x1 += glen * (float).5;
	    }
	    if (jlegsy != 0) {
		icc = i - 1 + jsymst;
		ch__1[0] = icc;
		symbol_(&x1, &y1, &symsiz, ch__1, &c_b16, &c__1, &c_n1);
	    }
	    if (jlegli != 0) {
		x1 += glen * (float).5;
	    }
	    x1 += csleg * (float).7;
	    y1 -= csleg * (float).5;
	    if (nc[i + 3] > 0) {
		if (jline != 0) {
		    i__1 = (integer) f[iloff + 6];
		    newpen_(&i__1);
		}
		if (jcol != 0) {
		    icc = (r__1 = f[icoff + 18], (integer) dabs(r__1));
		    if (icc < 1) {
			icc = 1;
		    }
		    r__1 = (real) icc;
		    plot_(&r__1, &c_b16, &c__0);
		}
		symbol_(&x1, &y1, &csleg, c[i+3], &c_b16, &nc[i + 3], &c_n1);
	    }
/* L200: */
	}
    }

/* 	FINISH UP */

    plot_(&c_b16, &c_b16, &c__3);		/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);				/* CLEAR TERMINAL */
	plotnd_();				/* CLOSE PLOT OUTPUT */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);				/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;
} /* lsplot_ */

