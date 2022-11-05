/* refterm.f -- translated by f2c (version of 2 February 1991  11:28:34).
   You must link the resulting object file with the libraries:
	-lF77 -lI77 -lm -lc   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static real c_b11 = (float)0.;
static real c_b13 = (float)1.;
static integer c__1280 = 1280;
static integer c__3 = 3;
static integer c__2 = 2;


/* *** LAST REVISED ON 20-AUG-1987 16:47:03.07 */
/* *** SOURCE FILE: [DL.GRAPHICS.LONGLIB]REFTERM.FOR */

/* Main program */ MAIN__()
{
    /* Format strings */
    static char fmt_15[] = "(\002$Enter Ramtek Emulation File Name: \002)";
    static char fmt_20[] = "(a70)";
    static char fmt_25[] = "(\002 Note: Select only one output graphics devi\
ce\002)";
    static char fmt_260[] = "(512a1)";
    static char fmt_261[] = "(1280a1)";
    static char fmt_98[] = "(\002 *** ERROR OPENING RAMTEK EMULATION FILE \
***\002)";
    static char fmt_96[] = "(\002 *** ERROR READING RAMTEK EMULATION FILE \
***\002,i5)";

    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    olist o__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), s_rsfe(), do_fio(), e_rsfe(), f_open();
    /* Subroutine */ int s_stop();

    /* Local variables */
    extern /* Subroutine */ int rmwritebyte_();
    static integer idev, lpen, ierr;
    extern /* Subroutine */ int exit_(), plot_();
    static shortint b[1280];
    static integer ichan;
    static char fname[70];
    extern /* Subroutine */ int frame_();
    static integer iddev;
    extern /* Subroutine */ int cterm_();
    static integer ii, ix, iy;
    static real rx, xs, ys, ry;
    static integer ixwide, iywide;
    extern /* Subroutine */ int plotnd_();
    static integer ix0, iy1;
    static real xs1;
    static integer pen, ilu;
    extern integer irmchan_();
    static integer ixw;
    extern /* Subroutine */ int whererm_(), wherepr_(), wherevt_(), rmstart_()
	    ;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_15, 0 };
    static cilist io___2 = { 0, 5, 0, fmt_20, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_25, 0 };
    static cilist io___20 = { 1, 2, 0, fmt_260, 0 };
    static cilist io___23 = { 1, 2, 0, fmt_261, 0 };
    static cilist io___28 = { 0, 6, 0, fmt_98, 0 };
    static cilist io___29 = { 0, 6, 0, fmt_96, 0 };



/* 	THIS PROGRAM PLOTS A RAMTEK EMULATION FILE INTO THE LONGLIB */
/* 	PLOT PACKAGE */
/* 	WRITTEN: NOV 1986   DGL */

/* 	THIS PROGRAM USING THE VAX FORTRAN "BYTE" VARIABLE TYPE */


/* 	PROMPT USER FOR FILE INPUT */

L35:
    s_wsfe(&io___1);
    e_wsfe();
    s_rsfe(&io___2);
    do_fio(&c__1, fname, 70L);
    e_rsfe();
    s_wsfe(&io___4);
    e_wsfe();

/* 	OPEN GRAPHICS PACKAGE */

    frame_(&c__0, &c__0, &c_b11, &c_b11, &c_b13);

/* 	OUTPUT RAMTEK EMULATION ARRAY TO SELECTED DEVICE */
/* 	OPEN REF FILE ASSUMING LARGE RAMTEK */

    ixwide = 1280;
    iywide = 1024;
    o__1.oerr = 1;
    o__1.ounit = 2;
    o__1.ofnmlen = 70;
    o__1.ofnm = fname;
    o__1.orl = ixwide;
    o__1.osta = "UNKNOWN";
    o__1.oacc = "DIRECT";
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L199;
    }

/* 	DETERMINE WHICH GRAPHICS DEVICE IS OPEN */

L65:
    ixw = ixwide;
    if (ixwide == 512) {
	ixw = 512;
    }

/* 	CHECK TERMINAL, RAMTEK, AND METAFILE */

    wherevt_(&xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &ix, &iy);
    rx *= 4;
    ry *= 4;
    if (ilu <= 0) {
	whererm_(&xs, &ys, &xs, &ys, &rx, &ry, &iy, &ix, &ix, &ilu);
	if (ilu <= 0) {
	    wherepr_(&xs, &ys, &xs, &ys, &xs, &ys, &rx, &ry, &ilu, &iy, &ix, &
		    ix);
	    rx = rx * (float)5. / (float)3.;
	    ry = ry * (float)5. / (float)3.;
	    idev = 2;
	} else {
	    ichan = irmchan_(&iddev);
	    idev = 1;
	}
    } else {
	idev = 0;
    }

/* 	SEE IF ANY DEVICE IS IN USE, EXIT IF NOT */

    if (ilu <= 0) {
	exit_();
    }

/* 	READ EACH LINE OF IMAGE AND PLOT IT OUT */

    lpen = -3;
    i__1 = iywide;
    for (iy1 = 1; iy1 <= i__1; ++iy1) {
	iy = iywide - iy1;
	if (ixw == 512) {
	    i__2 = s_rsfe(&io___20);
	    if (i__2 != 0) {
		goto L97;
	    }
	    for (ii = 1; ii <= 512; ++ii) {
		i__2 = do_fio(&c__1, (char *)&b[ii - 1], (ftnlen)sizeof(
			shortint));
		if (i__2 != 0) {
		    goto L97;
		}
	    }
	    i__2 = e_rsfe();
	    if (i__2 != 0) {
		goto L97;
	    }
	} else {
	    i__2 = s_rsfe(&io___23);
	    if (i__2 != 0) {
		goto L97;
	    }
	    i__2 = do_fio(&c__1280, (char *)&b[0], (ftnlen)sizeof(shortint));
	    if (i__2 != 0) {
		goto L97;
	    }
	    i__2 = e_rsfe();
	    if (i__2 != 0) {
		goto L97;
	    }
	}
	if (idev != 1) {

/* 	OUTPUT DIRECTLY TO RAMTEK USING IMAGE MODE WRITE */

	    rmstart_(&ichan, &iy1, &c__0, &ierr);
	    rmwritebyte_(&ichan, b, &ixw, &ierr);
	} else {

/* 	CONVERT PIXEL ROW INTO SCAN LINES FOR METAFILE AND TERMINAL */


	    pen = -1;
	    i__2 = ixwide;
	    for (ix = 0; ix <= i__2; ++ix) {
		ii = b[ix];
/* .AND.255 */
		if (ix == ixwide) {
		    ii = -2;
		}
		if (ii != pen) {
		    if (pen != -1 && pen != 0) {
			xs = (ix0 + (float).5) * rx;
			xs1 = (ix - (float).5) * rx;
			ys = (iy + (float).5) * rx;
			if (lpen != pen) {
			    r__1 = (real) pen;
			    plot_(&r__1, &c_b11, &c__0);
			}
			plot_(&xs, &ys, &c__3);
			plot_(&xs1, &ys, &c__2);
		    }
		    lpen = pen;
		    pen = ii;
		    ix0 = ix;
		}
/* L305: */
	    }
	}
/* L250: */
    }

L350:
    plot_(&c_b11, &c_b11, &c__3);
    cterm_(&c__2);
    plotnd_();

    s_stop("", 0L);

L199:

/* 	IF WE GET TO HERE WE GOT AN ERROR OPENING REF FILE */
/* 	MAY BE IT WAS A 512 SIZE FILE, TRY AGAIN */

    ixwide = 512;
    iywide = 512;
    o__1.oerr = 1;
    o__1.ounit = 2;
    o__1.ofnmlen = 70;
    o__1.ofnm = fname;
    o__1.orl = ixwide;
    o__1.osta = "UNKNOWN";
    o__1.oacc = "DIRECT";
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L99;
    }
    goto L65;

L99:
    s_wsfe(&io___28);
    e_wsfe();
    goto L35;

L97:
    s_wsfe(&io___29);
    do_fio(&c__1, (char *)&iy1, (ftnlen)sizeof(integer));
    e_wsfe();
    goto L350;
} /* MAIN__ */

/* Main program alias */ int refterm_ () { MAIN__ (); }
