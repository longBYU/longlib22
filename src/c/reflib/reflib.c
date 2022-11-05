
/* *** LAST REVISED ON  1-FEB-1994 07:50:02.67 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C]REFLIB.C */

#include <stdio.h>

#include "my.h"

/* Common Block Declarations */

struct {
    integer iotype, mt, nt, ist, ixwide, iywide, lx, ly;
    real xl[2], yl[2];
    integer is, ibnt;
    char a[1310721];
} ramtekio_;

#define ramtekio_1 ramtekio_

extern struct {
    integer ichan, imr[128];
    real rre[2], rox, roy, rsf;
    integer nimr;
    real rang;
    integer mm, ipw, ipsc, icol;
    real rvp[4];
    integer irid;
    real rlim[2];
    integer irxlim, irylim, iddev;
} rmtek_;

#define rmtek_1 rmtek_

FILE *col_file, *ref_file;

/* Table of constant values */
static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__5 = 5;
static real c_b49 = (float)0.;
static real c_b51 = (float)1.;
static integer c__9999 = 9999;

/**************************************************************************/
/* RAMTEK EMULATION FILE ROUTINES FOR THE LONGLIB GRAPHICS LIBRARY */
/* C LANGUAGE VERSION: DGL JAN 1993
/**************************************************************************/

/* Subroutine */ int ramopen_(ichan, idev, iddev, ierr)
integer *ichan, *idev, *iddev, *ierr;
{
/* 	OPEN/INIT RAMTEK EMULATION FILE CHANNEL */
/* 	INPUTS: */
/* 	IDEV	(I)	DEVICE TYPE */
/* 				1=1280x1024 */
/* 				2=512x512 */
/* 				3=IDDEVxIERR (CUSTOM SIZE) */
/* 				4=IDDEVxIERR (CUSTOM SIZE) */
/* 				5=1280x1024 */
/* 	IDDEV,IERR (I)	CUSTOM IMAGE SIZE DIMENSIONS (CHANGED ON OUTPUT) */
/* 			  IDDEV =< 1280 */
/* 			  IERR  =< 1024 */
/* 	OUTPUTS: */
/* 	ICHAN	(I)	RETURNED CHANNEL NUMBER (ALWAYS=1) */
/* 	IDDEV	(I)	RETURNED RAMTEK DEVICE NUMBER (ALWAYS=0) */
/* 	IERR	(I)	RETURNED ERROR CODE (0=NO ERROR) */

/* 	SET ARRAY SIZE */

    ramtekio_1.ixwide = 1279;	/* ARRAY X DIMENSION SIZE (DEFAULT VALUE) */
    ramtekio_1.iywide = 1024;	/* ARRAY Y DIMENSION SIZE (DEFAULT VALUE) */
    if (*idev == 2) {		/* 512X512 ARRAY */
	ramtekio_1.ixwide = 511;
	ramtekio_1.iywide = 512;
    } else if (*idev == 3 || *idev == 4) {	/* CUSTOM SIZE */
	ramtekio_1.ixwide = *iddev - 1;
	ramtekio_1.iywide = *ierr;
    }
    ramtekio_1.iotype = *idev;	/* STORE RAMTEK EMULATION FILE SIZE CODE */
    *iddev = 0;			/* RETURN RAMTEK DEVICE NUMBER */
    *ichan = 1;			/* "CHANNEL" NUMBER */
    *ierr = 0;			/* RETURN OK ERROR CODE */
    ramtekio_1.mt = -1;		/* LINE BIT PATTERN SOLID */
    ramtekio_1.nt = 1;		/* LINE WIDTH */
    ramtekio_1.ist = 1;		/* BIT PATTERN SCALE FACTOR */
    ramtekio_1.lx = 0;		/* IMAGE MODE START X */
    ramtekio_1.ly = 0;		/* IMAGE MODE START Y */
    ramtekio_1.xl[0] = (float)0.;	/* LEFT DEFAULT WINDOW */
    ramtekio_1.yl[0] = (float)0.;	/* UPPER DEFAULT WINDOW */
    ramtekio_1.xl[1] = (real) ramtekio_1.ixwide;/* RIGHT DEFAULT WINDOW */
    ramtekio_1.yl[1] = (real) (ramtekio_1.iywide - 1);/* LOWER DEFAULT WINDOW */
    ramtekio_1.is = 0;		/* PIX SEQ: L-R, T-B */
    return 0;
} /* ramopen_ */


/* Subroutine */ int ramclose_0_(n__, ichan, iargi, iopti, name, rsx, rsy)
int n__;
integer *ichan, *iargi, *iopti;
char *name;
real *rsx, *rsy;
{
    /* Initialized data */
    static integer ipass = 0;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1;

    /* External Routines */
    extern /* Subroutine */ int cterm_(), pplot_();
    extern /* Subroutine */ int pplots_();
    extern /* Subroutine */ int vplots_(), plotvt_();
    extern /* Subroutine */ int newpage_();
    extern /* Subroutine */ int wherepr_(), wherevt_();
    extern char getch();

    /* Local variables */
    static integer iarg, idev, lpen, iopt;
    static char b[1600];
    static char fname[70];
    static integer iwide;
    static char ib;
    static integer ii, iy, ix;
    static real rx, xs, ys, ry;
    static integer ix0;
    static real xs1;
    static integer iaa;
    static char dev;
    static integer pen, ilu;
    static integer ixw, iyx;

/* 	TERMINATE RAMTEK EMULATION FILE PLOTTING */
/* 	MAY HAVE THE SIDE EFFECT CLOSING THEN REOPENING PRINTER HISTORY FILE */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL NUMBER (IGNORED) */

/* MAXIMUM WIDTH=1600 */
    switch(n__) {
	case 1: goto L_refdis;	/* PROMPT USER FOR OUTPUT FOR THIS CALL */
	}

    if (ipass == 2) {	/* ALREADY COMPLETED A NON-INTERACTIVE PASS */
	return 0;
    }
    ipass = 1;			/* INTERACTIVE=1 */
L100:
    cterm_(&c__1);
    printf("REFLIB Plot-Buffer Ouput Device? (T,F,O,M,X) ");
    dev = getch();
    idev = dev;
    if (idev >= 96) {
	idev += -32;
    }
    if (idev == 32 || idev == 63) {
	printf("\nAvailable Ramtek Emulation Output Devices:\n");
	printf(" T : Screen Graphics Terminal\n");
	printf(" F : Ramtek Emulation File\n");
	printf(" O : Ramtek Emulation File Overlay\n");
	printf(" M : Longlib MetaFile Output\n");
	printf(" X : Exit\n\n");
	goto L100;
    }
    if (idev == 84) {			/* TERMINAL SCREEN */
	iarg = 1;
	wherevt_(&xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &ix, &iy);
	if (ilu < 0) {
	    printf("Enter NUMBER of Terminal Code: ");
	    i__1 = scanf("%d",&iopt);
	}
	iopt = 0;
    }
    if (idev == 70 || idev == 82) {	/* RAMTEK FILE */
	iarg = 2;
	iopt = 1;
	goto L35;
    }
    if (idev == 79) {			/* RAMTEK FILE (OVERLAY) */
	iarg = 2;
	iopt = 2;
        printf("Enter Ramtek Emulation File Name: ");
	i__1 = scanf("%s",fname);
	getch();
    }
    if (idev == 77 || idev == 80) {	/* PRINTER PACKAGE */
	iarg = 3;
    }
    if (idev == 88) {			/* EXIT */
	return 0;
    }
    goto L200;
L35:
    printf("Enter Ramtek Emulation File Name: ");
    i__1 = scanf("%s",fname);
    getch();
    goto L200;

/* 	ENTRY FOR NON-INTERACTIVE RAMTEK EMULATION FILE STUFF */

L_refdis:

/* 	IARGI	(I)	OUTPUT DEVICE CODE */
/* 			 -1 = GRAPHICS TERMINAL */
/* 				(IOPT=TERMINAL TYPE SEE WHEREVT) */
/* 				RSX, RSY USED FOR TERMINAL RESOLUTION */
/* 			 1 = GRAPHICS TERMINAL */
/* 				(IOPT=TERMINAL TYPE SEE FRAME) */
/* 				DEFAULT INTERNAL RESOLUTION USED */
/* 			 2 = RAMTEK EMULATION FILE */
/* 				(IOPT=1 IS ABSOLUTE WRITE) */
/* 				(IOPT=2 IS OVERLAY--WRITE ONLY NON-ZERO COLORS) */
/* 				(IOPT=3 IS ERASE) */
/* 			 -3 = METAFILE OUTPUT */
/* 				RSX, RSY USED FOR METAFILE RESOLUTION */
/* 			 3 = METAFILE OUTPUT */
/* 				DEFAULT INTERNAL RESOLUTION USED */
/* 	IOPTI	(I)	OPTION CODE (SEE ABOVE) */
/* 	NAME	(C)	FILE NAME FOR RAMTEK EMULATION FILE */
/* 	RSX,RSY (I)	DEVICE RESOLUTION (INCH/PIXEL) */

    iarg = *iargi;
    iopt = *iopti;
    strncpy(fname, name, 70);
    ipass = 2;			/* NON-INTERACTIVE=2 */
L200:

/* 	OUTPUT RAMTEK EMULATION ARRAY TO SELECTED DEVICE */

    if (iarg == 2) {			/* OUTPUT TO FILE */
	ixw = ramtekio_1.ixwide + 1;
	ref_file = fopen(fname,"w");
	if (ref_file == NULL) {
	    goto L99;
	}
	i__1 = ramtekio_1.ixwide;
	if (fwrite(&i__1, sizeof(integer), 1, ref_file) == 0) {
		goto L98;
	}
	i__1 = ramtekio_1.iywide;
	if (fwrite(&i__1, sizeof(integer), 1, ref_file) == 0) {
		goto L98;
	}
	for (iy = 0; iy < i__1; ++iy) {
	    iyx = iy * ixw;
	    if (iopt > 1) { /* overlay option not implemented */
/*		    i__3 = ixw;
		    for (ii = 1; ii <= i__3; ++ii) {
			if (fgetc(ref_file) == EOF) {
			    goto L97;
			}
		    }
		    if (fseek(ref_file, i__3 ,1) == EOF) {
			goto L97;
		    }
*/	    }
	    for (ix = 0; ix <= ixw; ++ix) {
		ib = ramtekio_1.a[ix + iyx];
		b[ix] = ib;
/*		if (ib !=0 && ib != -1)
			printf("%d at %d %d\n",ib,ix,iy);
		if (iopt == 1 || ib != 0 && iopt == 2 || ib == 0 && iopt == 3)
			 {
		    b[ix] = ib;
		}
*/ /* L245: */
	    }
/* 	write data */
	   fwrite(b, sizeof(char), ixw, ref_file);

/* L250: */
	}
	fclose(ref_file);
    }

    iaa = abs(iarg);
    if (iaa == 3 || iaa == 1) {
	if (iaa == 3) {		/* META FILE */
	    wherepr_(&xs, &ys, &xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &
		    ix);
	    if (ilu < 0) {	/* IF METAFILE CLOSED, OPEN IT */
		ilu = 3;
		pplots_(&ilu, &c_b49, &c_b49, &c_b51);
		wherepr_(&xs, &ys, &xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &
			ix, &ix);
	    } else {		/* ELSE ISSUE A NEWPAGE COMMAND */
		newpage_();
	    }

/* 	RESCALE RESOLUTION OF OUTPUT */
	    rx = rx * (float)5. / (float)3.;
	    ry = ry * (float)5. / (float)3.;
	    if (iarg < 0) {
		rx = *rsx;
		ry = *rsy;
	    }
	}
	if (iaa == 1) {
	    wherevt_(&xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &ix, &iy);
	    if (ilu < 0) {	/* IF TERMINAL OUTPUT CLOSED, OPEN IT */
		vplots_(&iopt, &c_b49, &c_b49, &c_b51);
		wherevt_(&xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &ix, &
			iy);
	    }
	    cterm_(&c_n1);

/* 	RESCALE RESOLUTION OF OUTPUT */

	    rx *= 4;
	    ry *= 4;
	    if (iarg < 0) {
		rx = *rsx;
		ry = *rsy;
	    }
	}

/* 	OUTPUT TO METAFILE AND/OR TERMINAL */

	lpen = -3;
	i__1 = ramtekio_1.iywide;
	for (iy = 1; iy <= i__1; ++iy) {
	    iyx = (ramtekio_1.iywide - iy) * (ramtekio_1.ixwide + 1);
	    pen = -1;
	    i__2 = ramtekio_1.ixwide;
	    for (ix = 0; ix <= i__2; ++ix) {
/* 				II=A(IX+IYX).AND.255 */
		ii = ramtekio_1.a[ix + iyx];
		if (ix == ramtekio_1.ixwide) {
		    ii = -2;
		}
		if (ii != pen || ix == iwide) {
		    if (pen != -1 && pen != 0) {
			xs = (ix0 + (float).5) * rx;
			xs1 = (ix - (float).5) * rx;
			ys = (iy + (float).5) * rx;
			if (iarg == 1) {
			    if (lpen != pen) {
				r__1 = (real) pen;
				plotvt_(&r__1, &c_b49, &c__0);
			    }
			    plotvt_(&xs, &ys, &c__3);
			    plotvt_(&xs1, &ys, &c__2);
			}
			if (iarg == 3) {
			    if (lpen != pen) {
				r__1 = (real) pen;
				pplot_(&r__1, &c_b49, &c__0);
			    }
			    pplot_(&xs, &ys, &c__3);
			    pplot_(&xs1, &ys, &c__2);
			}
			lpen = pen;
		    }
		    pen = ii;
		    ix0 = ix;
		}
/* L305: */
	    }
/* L300: */
	}
	if (iarg == 3) {	/* UP PEN FOR METAFILE */
	    pplot_(&c_b49, &c_b49, &c_n3);
	}
	if (iarg == 1) {	/* UP PEN FOR TERMINAL */
	    plotvt_(&c_b49, &c_b49, &c_n3);
	}
    }

    if (ipass == 1) {		/* MORE INTERACTIVE STUFF */
	goto L100;
    }
    return 0;
L99:
    printf("\n*** ERROR OPENING RAMTEK EMULATION FILE ***\n");
    goto L35;
L97:
    printf("\n*** ERROR READING RAMTEK EMULATION FILE ***\n");
    goto L35;
L98:
    printf("\n*** ERROR WRITING RAMTEK EMULATION FILE ***\n");
    goto L35;
} /* ramclose_ */

/* Subroutine */ int ramclose_(ichan)
integer *ichan;
{
    return ramclose_0_(0, ichan, (integer *)0, (integer *)0, (char *)0, (real 
	    *)0, (real *)0);
    }

/* Subroutine */ int refdis_(iargi, iopti, name, rsx, rsy)
integer *iargi, *iopti;
char *name;
real *rsx, *rsy;
{
    return ramclose_0_(1, (integer *)0, iargi, iopti, name, rsx, rsy);
    }


/* Subroutine */ int rmplot_(ichan, n, ip, jcol, ierr)
integer *ichan, *n, *ip, *jcol, *ierr;
{
    /* Initialized data */

    static integer mwp[7] = { 1,5,12,21,26,37,44 };
    static integer mwx[44] = { 0,-1,1,1,-1,-1,0,2,1,0,0,-1,0,-1,-1,-1,0,0,1,1,
	    1,1,1,0,0,-1,-1,-1,-1,-1,-1,0,0,1,1,1,1,1,1,1,0,0,-1,-1 };
    static integer mwy[44] = { 0,0,1,-1,-1,0,2,0,0,-1,-1,0,-1,0,0,1,1,1,1,0,0,
	    0,-1,-1,-1,-1,-1,0,0,1,1,1,1,1,1,0,0,0,-1,-1,-1,-1,-1,-1 };

    /* System generated locals */
    integer i__1, i__2;

    /* External Routines */
    extern /* Subroutine */ int ramout_();

    /* Local variables */
    static integer i, iw, lw;
    static integer ix1, iy1, ix2, iy2;

/* 	PLOT A LINE OF CONNECTED VECTORS */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	N	(I)	NUMBER OF VECTOR PAIRS */
/* 	IP	(I)	ARRAY OF X,Y LOCATIONS OF POINTS */
/* 	JCOL	(I)	PLOTTING COLOR (0-255) */
/* 	IERR	(I)	RETURNED IO ERROR FLAG */

    /* Parameter adjustments */
    --ip;

    /* Function Body */

    ramtekio_1.ibnt = 0;
    if (*n <= 0) {
	return 0;
    }

printf("rmplot %d %d\n",*jcol,rmtek_1.icol);
/*rmtek_1.icol = 253; */

/* 	CONVERT A STRING OF VECTORS INTO INDIVIDUAL VECTORS */

    if (*n == 1) {
	ix1 = ip[1];
	iy1 = ip[2];
	lw = mwp[ramtekio_1.nt - 1];
	i__1 = lw;
	for (iw = 1; iw <= i__1; ++iw) {
	    ix1 += mwx[iw - 1];
	    iy1 += mwy[iw - 1];
	    ix2 = ix1;
	    iy2 = iy1;
	    ramout_(&c__9999, &ix1, &iy1, &ix2, &iy2, jcol);
/* L10: */
	}
	goto L200;
    }
    i__1 = *n << 1;
    for (i = 3; i <= i__1; i += 2) {
	ix1 = ip[i - 2];
	iy1 = ip[i - 1];
	ix2 = ip[i];
	iy2 = ip[i + 1];
	lw = mwp[ramtekio_1.nt - 1];
	i__2 = lw;
	for (iw = 1; iw <= i__2; ++iw) {
	    ix1 += mwx[iw - 1];
	    iy1 += mwy[iw - 1];
	    ix2 += mwx[iw - 1];
	    iy2 += mwy[iw - 1];
	    ramout_(&c__9999, &ix1, &iy1, &ix2, &iy2, jcol);
/* L50: */
	}
/* L100: */
    }
L200:
    return 0;
} /* rmplot_ */


/* Subroutine */ int ramout_(ichan, ix1, iy1, ix2, iy2, ic)
integer *ichan, *ix1, *iy1, *ix2, *iy2, *ic;
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer isst, b[16], d, i, x, y;
    extern integer ibits_();
    static integer i1, i2, x1, y1, x2, y2, dx, dy, icc, dif, ibt;
    static logical inv;
    static integer ixw, iyy;

/* 	CONVERT A VECTOR PLOT INTO RASTER SCAN BYTE MAP */

/* 	NOTE: THIS RAMOUT IS NOT COMPATIBLE WITH THE */
/* 	REAL RAMTEK VERSION */

/* 	ICHAN	(I)	SHOULD BE 9999 */
/* 	IX1,IY1	(I)	START POINT OF LINE SEGMENT */
/* 	IX2,IY2	(I)	START POINT OF LINE SEGMENT */
/* 	IC	(I)	COLOR (0-255) */

/* 	CHECK TO SEE IF SOME ROUTINE OTHER THAN RMPLOT IS CALLING RAMOUT */

    if (*ichan < 9999) {
	*ix2 = -1;
	return 0;
    }

/* 	BIT MAP FOR LINE TYPE */

    for (i = 1; i <= 16; ++i) {
	i__1 = i - 1;
	b[i - 1] = ibits_(&ramtekio_1.mt, &i__1, &c__1);
/* L75: */
    }
    dx = *ix1 - *ix2;
    if (dx < 0) dx = -dx;
    dy = *iy1 - *iy2;
    if (dy < 0) dy = -dy;
    x1 = *ix1;
    x2 = *ix2;
    y1 = *iy1;
    y2 = *iy2;
    if (x1 < 0) 
	x1 = 0;
    if (x2 < 0) 
	x2 = 0;
    if (y1 < 0)
	y1 = 0;
    if (y2 < 0)
	y2 = 0;
    if (x1 > ramtekio_1.ixwide) {
	x1 = ramtekio_1.ixwide;
    }
    if (x2 > ramtekio_1.ixwide) {
	x2 = ramtekio_1.ixwide;
    }
    if (y1 >= ramtekio_1.iywide) {
	y1 = ramtekio_1.iywide - 1;
    }
    if (y2 >= ramtekio_1.iywide) {
	y2 = ramtekio_1.iywide - 1;
    }
    inv = 0;
    if (dx < dy) {
	x = x1;
	x1 = y1;
	y1 = x;
	x = x2;
	x2 = y2;
	y2 = x;
	x = dy;
	dy = dx;
	dx = x;
	inv = 1;
    }
    if (x2 < x1) {
	x = x1;
	x1 = x2;
	x2 = x;
	y = y1;
	y1 = y2;
	y2 = y;
    }
    dif = 1;
    if (y2 < y1)
	dif = -1;
    d = 2 * dy - dx;
    i1 = 2 * dy;
    i2 = 2 * (dy - dx);
    y = y1;
    iyy = 0;

/* CONVERT COLOR VALUE FROM INTEGER TO BYTE */

    icc = *ic;
    if (icc > 127) {
	icc = *ic - 256;
    }

    ixw = ramtekio_1.ixwide + 1;
    isst = ramtekio_1.ist << 4;
    i__1 = x2;
    printf("ramout %d %d  %d %d  %d %d  %d %d\n",*ix1,*iy1,*ix2,*iy2,dx,dy,icc,*ic);
    printf("%d %d %d %d %d %d\n",x1,y1,x2,y2,dif,inv);
    for (x = x1; x <= i__1; ++x) {
	++ramtekio_1.ibnt;
	ibt = (ramtekio_1.ibnt / ramtekio_1.ist) % 16 + 1;
	ramtekio_1.ibnt %= isst;
	if (inv == 1) {
/*	    if (b[ibt - 1] != 0) 
*/		ramtekio_1.a[(x + iyy) * ixw + y] = icc;
/*	    printf("y %d  x %d  %d\n",x,y,(x + iyy) * ixw + y);
*/	} else {
/*	    if (b[ibt - 1] != 0)
*/		ramtekio_1.a[x + (y + iyy) * ixw] = icc;
/*	    printf("x %d  y %d  %d\n",x,y,(y + iyy) * ixw + x);
*/	}
	if (d < 0) {
	    d += i1;
	} else {
	    d += i2;
	    y += dif;
	}
/* L10: */
    }
    return 0;
} /* ramout_ */


/* Subroutine */ int rmtexture_(ichan, itext, iwide, isize, ierr)
integer *ichan, *itext, *iwide, *isize, *ierr;
{
    /* Initialized data */

    static integer ilt[16] = { -1,21845,13311,16191,8191,13119,16359,255,
	    23485,13107,7295,15567,22015,3855,24383,23485 };
    static integer it;

/* 	CHANGE PLOT LINE TEXTURE AND SCALING */

/* 	INPUTS: */

/* 	ICHAN	(I)	CHANNEL */
/* 	ITEXT	(I)	LINE TYPE (0-15) */
/* 	IWIDE	(I)	LINE WIDTH (FOR RMPLOT) */
/* 	ISIZE	(I)	PIXEL SCALING */
/* 	IERR	(I)	STATUS ERROR */

    it = *itext + 1;
    if (it < 1) {
	it = 1;
    }
    if (it > 16) {
	it = it % 16 + 1;
    }
    ramtekio_1.mt = ilt[it - 1];
    ramtekio_1.nt = *iwide;
    if (ramtekio_1.nt < 1) {
	ramtekio_1.nt = 1;
    }
    if (ramtekio_1.nt > 7) {
	ramtekio_1.nt = 7;
    }
    ramtekio_1.ist = *isize;
    if (ramtekio_1.ist < 1) {
	ramtekio_1.ist = 1;
    }
    if (ramtekio_1.ist > 16) {
	ramtekio_1.ist = 16;
    }
    return 0;
} /* rmtexture_ */


/* Subroutine */ int rmclear_(ichan, ierr)
integer *ichan, *ierr;
{
    static integer i;

/* 	CLEAR RAMTEK SCREEN */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IERR	(I)	STATUS ERROR */

    for (i = 0; i <= 1310719; ++i) {
	ramtekio_1.a[i] = 0;
    }
    return 0;
} /* rmclear_ */


/* Subroutine */ int ramoutin_(ichan, cmd, nc, buf, nb, ird, buf4)
integer *ichan;
shortint *cmd;
integer *nc;
shortint *buf;
integer *nb, *ird, *buf4;
{
    /* System generated locals */
    integer i__1;
    static integer equiv_2[2];

    /* Local variables */
#define z ((shortint *)equiv_2)
    static integer index, ib;
#define ij ((shortint *)equiv_2)
    static integer ix, iy, jx, jy;
#define ij4 (equiv_2)
    static integer nbb;
#define iib ((shortint *)equiv_2)


/* 	READ/WRITE DATA FROM RAMTEK IN IMAGE MODE */

/* 	INPUTS: */

/* 	ICHAN	(I)	CHANNEL NUMBER (=9999) */
/* 	CMD	(B)	ARRAY OF BYTE DATA TO READ/WRITE */
/* 	NC	(I)	NUMBER OF BYTES */
/* 	BUF	(I*2)	ARRAY OF INTEGER*2 DATA TO READ/WRITE */
/* 	NB	(I)	NUMBER OF WORDS */
/* 	BUF4	(I*4)	ARRAY OF INTEGER*4 DATA TO READ/WRITE */
/* 	IRD	(I)	READ/WRITE CODE */
/* 			 0=READ BYTES */
/* 			 1=READ I*2 WORDS */
/* 			 2=WRITE BYTES */
/* 			 3=WRITE I*2 WORDS */
/* 			 4=READ I*4 WORDS */
/* 			 5=WRITE I*4 WORDS */

/* 	OUTPUTS: (DEPENDS ON IRD) */

/* 	BUF4	(I*4)	RETURNED DATA INTEGER*2 WORDS */
/* 	BUF	(I*2)	RETURNED DATA INTEGER*2 WORDS */
/* 	NB	(I)	NUMBER OF WORDS TO READ */
/* 	CMD	(B)	RETURNED DATA BYTES */
/* 	NC	(I)	NUMBER OF BYTESS TO READ */

    /* Parameter adjustments */
    --buf4;
    --buf;
    --cmd;

    /* Function Body */
    if (*ichan != 9999) {
	return 0;
    }
    if (*ird == 0 && *nc <= 0) {
	return 0;
    }
    if (*ird == 1 && *nb <= 0) {
	return 0;
    }
    if (*ird == 2 && *nc <= 0) {
	return 0;
    }
    if (*ird == 3 && *nb <= 0) {
	return 0;
    }
    if (*ird == 4 && *nb <= 0) {
	return 0;
    }
    if (*ird == 5 && *nb <= 0) {
	return 0;
    }

    ix = 1;
    iy = 0;
    jx = 0;
    jy = 1;
    switch ((int)(ramtekio_1.is + 1)) {
	case 1:  goto L10;
	case 2:  goto L11;
	case 3:  goto L12;
	case 4:  goto L13;
	case 5:  goto L14;
	case 6:  goto L15;
	case 7:  goto L16;
	case 8:  goto L17;
    }
L10:
    goto L20;			/* "NORMAL" L-R,T-B */
L11:
    ix = -1;			/* R-L, T-B */
    goto L20;
L12:
    jy = -1;			/* L-R, B-T */
    goto L20;
L13:
    ix = -1;			/* R-L, B-T */
    iy = -1;
    goto L20;
L14:
    ix = 0;			/* T-B, L-R */
    iy = 1;
    jx = 1;
    jy = 0;
    goto L20;
L15:
    ix = 0;			/* B-T, L-R */
    iy = -1;
    jx = 1;
    jy = 0;
    goto L20;
L16:
    ix = 0;			/* T-B, R-L */
    iy = 1;
    jx = -1;
    jy = 0;
    goto L20;
L17:
    ix = 0;			/* B-T, R-L */
    iy = -1;
    jx = -1;
    jy = 0;
    goto L20;

L20:
    nbb = *nc;
    if (*ird == 1 || *ird == 3) {
	nbb = *nb;
    }
    if (*ird == 4 || *ird == 5) {
	nbb = *nb;
    }
    i__1 = nbb;
    for (ib = 1; ib <= i__1; ++ib) {
	index = ramtekio_1.ly;
	index = ramtekio_1.lx + index * (ramtekio_1.ixwide + 1);
	switch ((int)(*ird + 1)) {
	    case 1:  goto L50;
	    case 2:  goto L51;
	    case 3:  goto L52;
	    case 4:  goto L53;
	    case 5:  goto L54;
	    case 6:  goto L55;
	}
	goto L60;
L50:
	cmd[ib] = ramtekio_1.a[index];
	goto L60;
L51:
	buf[ib] = ramtekio_1.a[index];
/* 		BUF(IB)=A(INDEX).AND.255	! BIT-WISE AND OF integer*2 VARIABLES */

/* BIT-WISE AND OF integer*2 VARIABLES */
	goto L60;
L52:
	ramtekio_1.a[index] = cmd[ib];
	goto L60;
L53:
	*ij = buf[ib];
/* PUT I*2 VALUE INTO integer*2 */
	ramtekio_1.a[index] = *iib;
	goto L60;
L54:
	*iib = ramtekio_1.a[index];
	z[1] = 0;
	z[2] = 0;
	z[3] = 0;
	buf4[ib] = *ij4;
	goto L60;
L55:
	*ij4 = buf4[ib];
	z[1] = 0;
	z[2] = 0;
	z[3] = 0;
	ramtekio_1.a[index] = *iib;
	goto L60;
L60:
	ramtekio_1.lx += ix;
	ramtekio_1.ly += iy;
L65:
	if ((real) ramtekio_1.lx < ramtekio_1.xl[0]) {
	    ramtekio_1.lx = ramtekio_1.xl[1];
	    ramtekio_1.ly += jy;
	}
	if ((real) ramtekio_1.lx > ramtekio_1.xl[1]) {
	    ramtekio_1.lx = ramtekio_1.xl[0];
	    ramtekio_1.ly += jy;
	}
	if ((real) ramtekio_1.ly < ramtekio_1.yl[0]) {
	    ramtekio_1.ly = ramtekio_1.yl[1];
	    ramtekio_1.lx += jx;
	    goto L65;
	}
	if ((real) ramtekio_1.ly > ramtekio_1.yl[1]) {
	    ramtekio_1.ly = ramtekio_1.yl[0];
	    ramtekio_1.lx += jx;
	    goto L65;
	}
/* L100: */
    }

    return 0;
} /* ramoutin_ */

#undef iib
#undef ij4
#undef ij
#undef z



/* Subroutine */ int rmreadcursor_(ichan, idev, ix, iy, itrk, ivis, ient, 
	ierr)
integer *ichan, *idev, *ix, *iy, *itrk, *ivis, *ient, *ierr;
{
    *ierr = -1;
    return 0;
} /* rmreadcursor_ */


/* Subroutine */ int rmreadcol_(ichan, is, n, ierr)
integer *ichan, *is, *n, *ierr;
{
    /* System generated locals */
    integer i__1, i__2;

    static integer i;
    static char fname[80];
    static integer iv;

/* 	READ COLOR TABLE FROM COLOR TABLE FILE */
/* 	USES FILE UNIT 2 */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    if (*ichan <= 0) {
	return 0;
    }
    *ierr = 0;
    printf("\nRMREADCOL--Enter Color Table File Name: ");
    scanf("%s",fname);
    col_file = fopen(fname,"r");
    if (col_file == 0) {
	goto L99;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
	if (fscanf(col_file,"%4d %10d",&iv, &is[i]) == EOF) {
	    goto L99;
	}
    }
L20:
    fclose(col_file);
    return 0;

L99:
    *ierr = -1;
    printf("\n *** ERROR READING COLOR TABLE FILE ***\n");
    goto L20;
} /* rmreadcol_ */


/* Subroutine */ int rmwritecol_(ichan, is, n, ierr)
integer *ichan, *is, *n, *ierr;
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i;
    static char fname[60];
    static integer iv;

/* 	WRITE COLOR TABLE TO COLOR TABLE FILE */
/* 	USES FILE UNIT 2 */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    if (*ichan <= 0) {
	return 0;
    }
    if (*ierr < 0) {
	return 0;
    }
    *ierr = 0;
    printf("\nRMWRITECOL--Enter Color Table File Name: ");
    scanf("%s",fname);
    col_file = fopen(fname,"w");
    if (col_file == 0) {
	goto L99;
    }
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
	if (fprintf(col_file,"%4d %10d",&iv, &is[i]) == EOF) {
	    goto L99;
	}
    }
L20:
    fclose(col_file);
    return 0;

L99:
    *ierr = -1;
    printf("\n*** RMWRITECOL:  ERROR WRITING COLOR TABLE ***\n");
    goto L20;
} /* rmwritecol_ */


/* Subroutine */ int rmreadbyte_(ichan, is, n, ierr)
integer *ichan;
shortint *is;
integer *n, *ierr;
{

    /* External Routines */
    extern /* Subroutine */ int ramoutin_();

/* 	READ DATA char FROM RAMTEK IMAGE MODE */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL (IGNORED) */
/* 	N	(I)	NUMBER OF BYTES TO READ OF IMAGE */

/* 	OUTPUTS: */
/* 	IS	(B)	ARRAY OF IMAGE DATA */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, &is[1], n, ierr, &c__0, &c__0, &c__0);
    return 0;
} /* rmreadbyte_ */


/* Subroutine */ int rmreadword_(ichan, is, n, ierr)
integer *ichan;
shortint *is;
integer *n, *ierr;
{

    /* External Routines */
    extern /* Subroutine */ int ramoutin_();

/* 	READ INTEGER*2 WORD FROM RAMTEK IMAGE MODE */

/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL (IGNORED) */
/* 	N	(I)	NUMBER OF WORDS TO READ */

/* 	OUTPUTS: */
/* 	IS	(I*2)	ARRAY OF IMAGE DATA */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, ierr, &c__0, &is[1], n, &c__1, &c__0);
    return 0;
} /* rmreadword_ */


/* Subroutine */ int rmwritebyte_(ichan, is, n, ierr)
integer *ichan;
shortint *is;
integer *n, *ierr;
{

    /* External Routines */
    extern /* Subroutine */ int ramoutin_();

    static integer ie;

/* 	WRITE BYTE DATA TO RAMTEK IN IMAGE MODE */

/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IS	(B)	ARRAY OF IMAGE DATA */
/* 	N	(I)	NUMBER OF bytes TO WRITE */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, &is[1], n, &ie, &c__0, &c__2, &c__0);
    return 0;
} /* rmwritebyte_ */


/* Subroutine */ int rmwriteword_(ichan, is, n, ierr)
integer *ichan;
shortint *is;
integer *n, *ierr;
{
    /* External Routines */
    extern /* Subroutine */ int ramoutin_();

/* 	WRITE INTEGER*2 WORDS TO RAMTEK IN IMAGE MODE */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IS	(I*2)	ARRAY OF IMAGE DATA */
/* 	N	(I)	NUMBER OF WORDS TO READ */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, ierr, &c__0, &is[1], n, &c__3, &c__0);
    return 0;
} /* rmwriteword_ */


/* Subroutine */ int rmstart_(ichan, ix, iy, ierr)
integer *ichan, *ix, *iy, *ierr;
{

/* 	SET START OF IMAGE WRITE (COP) LOCATION TO (IX,IY) */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IX,IY	(I)	PIXEL LOCATION */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR (IGNORED) */

    ramtekio_1.lx = *ix;
    if ((real) ramtekio_1.lx < ramtekio_1.xl[0]) {
	ramtekio_1.lx = ramtekio_1.xl[0];
    }
    if ((real) ramtekio_1.lx > ramtekio_1.xl[1]) {
	ramtekio_1.lx = ramtekio_1.xl[1];
    }
    ramtekio_1.ly = *iy;
    if ((real) ramtekio_1.ly < ramtekio_1.yl[0]) {
	ramtekio_1.ly = ramtekio_1.yl[0];
    }
    if ((real) ramtekio_1.ly > ramtekio_1.yl[1]) {
	ramtekio_1.ly = ramtekio_1.yl[1];
    }

    return 0;
} /* rmstart_ */


/* Subroutine */ int rmwind_(ichan, ix, iy, ixm, iym, ierr)
integer *ichan, *ix, *iy, *ixm, *iym, *ierr;
{

/* 	SET IMAGE MODE WINDOW ON RAMTEK */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IX,IY	(I)	UPPER-LEFT (MINIMUM) CORNER */
/* 	IXM,IYM	(I)	LOWER-RIGHT (MAXIMUM) CORNER */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR (IGNORED) */
/* 	NOTE: MINIMUM WINDOW SIZE ALLOWED IS 2X2 PIXELS */

    ramtekio_1.xl[0] = (real) (*ix);
    if (ramtekio_1.xl[0] < (float)0.) {
	ramtekio_1.xl[0] = (float)0.;
    }
    if (ramtekio_1.xl[0] > (real) ramtekio_1.ixwide) {
	ramtekio_1.xl[0] = (real) ramtekio_1.ixwide;
    }
    ramtekio_1.yl[0] = (real) (*iy);
    if (ramtekio_1.yl[0] < (float)0.) {
	ramtekio_1.yl[0] = (float)0.;
    }
    if (ramtekio_1.yl[0] > (real) ramtekio_1.iywide) {
	ramtekio_1.yl[0] = (real) ramtekio_1.iywide;
    }
    ramtekio_1.xl[1] = (real) (*ixm);
    if (ramtekio_1.xl[1] < (float)0.) {
	ramtekio_1.xl[1] = (float)0.;
    }
    if (ramtekio_1.xl[1] > (real) ramtekio_1.ixwide) {
	ramtekio_1.xl[1] = (real) ramtekio_1.ixwide;
    }
    ramtekio_1.yl[1] = (real) (*iym);
    if (ramtekio_1.yl[1] < (float)0.) {
	ramtekio_1.yl[1] = (float)0.;
    }
    if (ramtekio_1.yl[1] > (real) ramtekio_1.iywide) {
	ramtekio_1.yl[1] = (real) ramtekio_1.iywide;
    }
    if (ramtekio_1.xl[1] <= ramtekio_1.xl[0]) {
	ramtekio_1.xl[1] = ramtekio_1.xl[0] + 1;
    }
    if (ramtekio_1.yl[1] <= ramtekio_1.yl[0]) {
	ramtekio_1.yl[1] = ramtekio_1.yl[0] + 1;
    }
    ramtekio_1.lx = ramtekio_1.xl[0];
    ramtekio_1.ly = ramtekio_1.yl[0];

    return 0;
} /* rmwind_ */


/* Subroutine */ int rmdir_(ichan, iseq, ierr)
integer *ichan, *iseq, *ierr;
{

/* 	SET SCAN SEQUENCE FOR IMAGE WRITING ON RAMTEK */

/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	ISEQ	(I)	SCAN CODE */
/* 		    PIX-TO-PIX  LINE-TO-LINE */
/* 	ISEQ	0	L-R	   T-B */
/* 		1	R-L	   T-B */
/* 		2	L-R	   B-T */
/* 		3	R-L	   B-T */
/* 		4	T-B	   L-R */
/* 		5	B-T	   L-R */
/* 		6	T-B	   R-L */
/* 		7	B-T	   R-L */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR */

    if (*iseq >= 0 && *iseq < 8) {
	ramtekio_1.is = *iseq;
    } else {
	*ierr = -1;
    }

    return 0;
} /* rmdir_ */


/* Subroutine */ int rmzoom_()
{
    return 0;
} /* rmzoom_ */


/* Subroutine */ int rmpan_()
{
    return 0;
} /* rmpan_ */


/* Subroutine */ int rmsetcur_()
{
    return 0;
} /* rmsetcur_ */


/* Subroutine */ int rmtext_()
{
    return 0;
} /* rmtext_ */


/* Subroutine */ int rmfntsize_()
{
    return 0;
} /* rmfntsize_ */


/* Subroutine */ int rmreset_()
{
    return 0;
} /* rmreset_ */



/* Subroutine */ int rterm_(ix)
integer *ix;
{
    /* Local variables */
    static integer ians;
    extern /* Subroutine */ int ramclose_();
    extern char getch();
    static char ans;

/* 	REPLACEMENT FOR RTERM ROUTINE FOR THE REF PACKAGE */
/* 	WRITTEN: DGL 8/18/87 */

/* IX	CONTROL FLAG */
/* 	= 0 CLEAR RAMTEK SCREEN */
/* 	= 2 ASK IF RAMTEK SCREEN CLEAR */
/* 	=-2 CLEAR RAMTEK SCREEN */
/* 	=-4 CLEAR RAMTEK SCREEN */
/* 	= 3 CLOSE RAMTEK CHANNEL */
/* 	=-3 REOPEN CLOSED RAMTEK CHANNEL */

    if (rmtek_1.ichan == -99 && *ix == 2) {
	goto L80;
    }
    if (rmtek_1.ichan == -99 && *ix == -3) {
	goto L80;
    }
    if (rmtek_1.ichan <= 0) {
	return 0;
    }
    if (abs(*ix) > 4) {
	return 0;
    }
    switch ((int)(*ix + 5)) {
	case 1:  goto L10;
	case 2:  goto L15;
	case 3:  goto L10;
	case 4:  goto L15;
	case 5:  goto L10;
	case 6:  goto L15;
	case 7:  goto L20;
	case 8:  goto L30;
	case 9:  goto L15;
    }
L10:
/* CLEAR RAMTEK SCREEN */
    ramclose_(&rmtek_1.ichan);
L15:
    return 0;
L20:
    printf("\nCall REF Output Routine? (y/n) [y] ");
/* ASK IF SCREEN CLEAR */
    ans = getch();
    ians = ans;
    if (ians >= 96) {
	ians += -32;
    }
    if (ians == 89 || ians == 32) {
	goto L10;
    } else {
	if (ians == 81) {
	    goto L30;
	}
/* TEMP. CLOSE CHANNEL */
	if (ians == 83) {
	    rmtek_1.ichan = -99;
/* SKIP PLOT MODE */
	}
    }
    return 0;
L30:
/* TEMP. CLOSE CHANNEL */
    rmtek_1.ichan = -99;
    return 0;
L80:
    return 0;
} /* rterm_ */


/****************************************************************************/
/* 	NEW SUBROUTINES */
/****************************************************************************/


/* Subroutine */ int rmpause_(ichan, iwait)
integer *ichan, *iwait;
{
    return 0;
} /* rmpause_ */


/* Subroutine */ int rminfo_(ichan, iopen, ix, iy, ncol, lcol, xw, yw, isize)
integer *ichan, *iopen, *ix, *iy, *ncol, *lcol, *xw, *yw, *isize;
{
    static integer iseq;

/* 	GET INFO ON RAMTEK DEVICE */

    /* Parameter adjustments */
    --yw;
    --xw;

    /* Function Body */
    *iopen = -1;
    if (*ichan <= 0) {
	return 0;
    }
    *iopen = ramtekio_1.iotype;
    *ix = ramtekio_1.ixwide;
    *iy = ramtekio_1.iywide;
    *ncol = 256;
    *lcol = -1;
    xw[1] = ramtekio_1.xl[0];
    xw[2] = ramtekio_1.xl[1];
    yw[1] = ramtekio_1.yl[0];
    yw[2] = ramtekio_1.yl[1];
    *isize = (ramtekio_1.xl[1] - ramtekio_1.xl[0] + 1) * (ramtekio_1.yl[1] - 
	    ramtekio_1.yl[0] + 1);
    iseq = ramtekio_1.is;
    return 0;
} /* rminfo_ */


/* Subroutine */ int rmwrcolind_(ichan, ired, igreen, iblue, index, ierr)
integer *ichan, *ired, *igreen, *iblue, *index, *ierr;
{
    return 0;
} /* rmwrcolind_ */


/* Subroutine */ int rmrdcolind_(ichan, ired, igreen, iblue, index, ierr)
integer *ichan, *ired, *igreen, *iblue, *index, *ierr;
{
    return 0;
} /* rmrdcolind_ */


/* Subroutine */ int rmwr4_(ichan, is, n, ierr)
integer *ichan, *is, *n, *ierr;
{
    extern /* Subroutine */ int ramoutin_();


/* 	WRITE INTEGER*4 WORDS TO RAMTEK IN IMAGE MODE */
/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IS	(I)	ARRAY OF IMAGE DATA */
/* 	N	(I)	NUMBER OF WORDS TO READ */

/* 	OUTPUTS: */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, ierr, &c__0, &c__0, n, &c__5, &is[1]);
    return 0;
} /* rmwr4_ */



/* Subroutine */ int rmrw4_(ichan, is, n, ierr)
integer *ichan, *is, *n, *ierr;
{
    extern /* Subroutine */ int ramoutin_();

/* 	READ INTEGER*4 WORD FROM RAMTEK IMAGE MODE */

/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL (IGNORED) */
/* 	N	(I)	NUMBER OF WORDS TO READ */

/* 	OUTPUTS: */
/* 	IS	(I*4)	ARRAY OF IMAGE DATA */
/* 	IERR	(I)	STATUS ERROR */

    /* Parameter adjustments */
    --is;

    /* Function Body */
    ramoutin_(&c__9999, ierr, &c__0, &c__0, n, &c__4, &is[1]);
    return 0;
} /* rmrw4_ */



/* Subroutine */ int rmspix_(ichan, ix, iy, ival, irdwr, ierr)
integer *ichan, *ix, *iy, *ival, *irdwr, *ierr;
{
    /* System generated locals */
    static integer equiv_0[2];

    /* Local variables */
    static integer index;
#define ij (equiv_0)
#define iib ((shortint *)equiv_0)

/* 	READ/WRITE A SINGLE PIXEL ON RAMTEK */

/* 	INPUTS: */
/* 	ICHAN	(I)	CHANNEL */
/* 	IX,IY	(I)	LOCATION */
/* 	IVAL	(I)	VALUE (IN/OUT) */
/* 	IRDWR	(I)	=0 READS PIXEL VALUE */
/* 			=1 WRITE PIXEL VALUE */
/* 	IERR	(I)	NOT USED */

    if (*ichan != 9999) {
	return 0;
    }

    *ij = *ival;
    iib[1] = 0;
    iib[2] = 0;
    iib[3] = 0;
    index = *ix + *iy * (ramtekio_1.ixwide + 1);
    if (*irdwr == 1) {
	ramtekio_1.a[index] = iib[0];
    } else {
	iib[0] = ramtekio_1.a[index];
	*ival = *ij;
    }

    return 0;
} /* rmspix_ */

#undef iib
#undef ij


/* Subroutine */ int rmstcol_(ichan, itab, ncol, ierr)
integer *ichan, *itab, *ncol, *ierr;
{
    *ncol = 256;
    *ierr = -1;
    return 0;
} /* rmstcol_ */


/* Subroutine */ int rmmode_(ichan, l1, l2, l3, ierr)
integer *ichan, *l1, *l2, *l3, *ierr;
{
    return 0;
} /* rmmode_ */

/* Subroutine */ int rambox_(ix1, iy1, ix2, iy2, ic)
integer *ix1, *iy1, *ix2, *iy2, *ic;
{
    integer x1, x2, y1, y2, icc, ixw, x, y;

    x1 = ( *ix1 <= *ix2 ? *ix1 : *ix2);
    x2 = ( *ix1  > *ix2 ? *ix1 : *ix2);
    y1 = ( *iy1 <= *iy2 ? *iy1 : *iy2);
    y2 = ( *iy1  > *iy2 ? *iy1 : *iy2);
    if (x1 < 0) 
	x1 = 0;
    if (x2 < 0) 
	x2 = 0;
    if (y1 < 0)
	y1 = 0;
    if (y2 < 0)
	y2 = 0;
    if (x1 > ramtekio_1.ixwide)
	x1 = ramtekio_1.ixwide;
    if (x2 > ramtekio_1.ixwide)
	x2 = ramtekio_1.ixwide;
    if (y1 >= ramtekio_1.iywide) 
	y1 = ramtekio_1.iywide - 1;
    if (y2 >= ramtekio_1.iywide)
	y2 = ramtekio_1.iywide - 1;

/* CONVERT COLOR VALUE FROM INTEGER TO BYTE */

    icc = *ic;
    if (icc > 127)
	icc = *ic - 256;

    ixw = ramtekio_1.ixwide + 1;
    printf("rambox %d %d %d %d %d %d %d\n",*ic,icc,x1,y1,x2,y2,ixw);
    printf("%d %d %d %d  %d %d\n",*ix1,*iy1,*ix2,*iy2,ramtekio_1.ixwide, ramtekio_1.iywide);

    for (y = y1; y <= y2; ++y)
	for (x = x1; x <= x2; ++x)
		ramtekio_1.a[x + y * ixw] = icc;

    for (x = 1; x <= 100; ++x)
	ramtekio_1.a[x + 88 * ixw] = 2;

    for (y = 1; y <= 100; ++y)
	ramtekio_1.a[8 + y * ixw] = 2;
/*
    for (y = 1; y <= 100; ++y)
	ramtekio_1.a[y + y * ixw] = 2;
*/
    return 0;
} /* rambox_ */


/* Subroutine */ int rmwopt_0_(n__, iwind, ierr)
int n__;
integer *iwind, *ierr;
{
    switch(n__) {
	case 1: goto L_rmsave;
    }
 L_rmsave:
    return 0;
} /* rmwopt_ */

/* Subroutine */ int rmwopt_(iwind, ierr)
integer *iwind, *ierr;
{
    return rmwopt_0_(0, iwind, ierr);
}

/* Subroutine */ int rmsave_()
{
    return rmwopt_0_(1, (integer *)0, (integer *)0);
}
