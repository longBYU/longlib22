/* illus.f -- translated by f2c (version of 2 February 1991  11:28:34).
   You must link the resulting object file with the libraries:
	-lF77 -lI77 -lm -lc   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__128 = 128;

/* Main program */ MAIN__()
{
    /* Builtin functions */
    integer s_cmp();
    /* Subroutine */ int s_copy(), s_stop();

    /* Local variables */
    static char name[80];
    static integer ierr, iflag;
    extern /* Subroutine */ int lplot_();
    extern integer libget_foreign__();

/* *** LAST REVISED ON 20-APR-1993 15:14:33.25 */
/* *** SOURCE FILE: [LONGD.GRAPHICS]ILLUS.FOR */

/* 	CREATED: DGL 4-APR-1985 */
/* 	MODIFIED: DGL 28-JAN-1991 */
/* 	+ ADDED IMAGE CAPABILITY AND CHANGED SCALING */
/* 	MODIFIED: DGL 20-APR-1993 */
/* 	+ SET UP FOR ADOBE ILLUSTRATOR INPUT */

/* 	THIS PROGRAM CONVERTS THE LONGLIB METAFILE */
/* 	PRODUCED BY THE LONGLIB GRAPHICS LIBRARY */
/* 	TO THE POSTSCRIPT LANGUAGE. */

/* 	USES INTEGER*2 IN REGET (MAY BE CHANGED TO INTEGER IF DONE */
/* 	IN THE MAIN LONGLIB FILE) */


/* 	VAX DEPENDENT ROUTINE TO GET COMMAND LINE FILE NAME */
/* 	(CAN BE COMMENTED OUT) */

    ierr = libget_foreign__(name, &c__0, &iflag, 80L);

/* 	DEFAULT NAME */

    if (s_cmp(name, " ", 80L, 1L) == 0) {
	s_copy(name, "for003.dat", 80L, 10L);
/* DEFAULT FILE NAME */
    }
    lplot_(name, 80L);
    s_stop("", 0L);
} /* MAIN__ */


/* Subroutine */ int lplot_(name, name_len)
char *name;
ftnlen name_len;
{
    /* Initialized data */

    static char linetype[13*10+1] = "[]           [2]          [4 4]        \
[4 7]        [2 2]        [2 2 2 2 4]  [6 2 3 2 4]  [1 1]        [1 1 4 4]  \
  [1 1 2 2 3 3]";

    /* Format strings */
    static char fmt_200[] = "(a)";
    static char fmt_601[] = "(f<kx+2>.1,x,f<ky+2>.1,\002 l\002/\002S\002)";
    static char fmt_600[] = "(f<kx+2>.1,x,f<ky+2>.1,\002 m\002)";
    static char fmt_602[] = "(f<kx+2>.1,x,f<ky+2>.1,\002 l\002/\002S\002)";
    static char fmt_603[] = "(f<kx+2>.1,x,f<ky+2>.1,\002 l\002)";
    static char fmt_402[] = "(\002%% newpage \002,i2,x,i2)";
    static char fmt_403[] = "(a13,\0020 d\002)";
    static char fmt_404[] = "(i1,\002 w\002)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(), s_wsle(), do_lio(), e_wsle(), s_rsfe(), do_fio(), 
	    e_rsfe(), s_wsfe(), e_wsfe(), f_clos(), i_nint();

    /* Local variables */
    static char line[80];
    static integer iold, i;
    extern /* Subroutine */ int reget_();
    static integer jpcnt;
    static real ixold, iyold;
    extern /* Subroutine */ int hexit_();
    static integer penup, i3, m1, m2, m3;
    static real x1, y1;
    static integer ic, lc, mp, lt;
    static real ix, iy;
    static integer lw, kx, ky;
    static real sx, sy, amx, amy;
    static integer jps, inx, iny, num;
    extern integer idigits_();

    /* Fortran I/O blocks */
    static cilist io___15 = { 0, 6, 0, 0, 0 };
    static cilist io___16 = { 0, 3, 1, fmt_200, 0 };
    static cilist io___18 = { 0, 1, 0, fmt_200, 0 };
    static cilist io___33 = { 0, 1, 0, fmt_601, 0 };
    static cilist io___34 = { 0, 1, 0, fmt_600, 0 };
    static cilist io___35 = { 0, 1, 0, fmt_602, 0 };
    static cilist io___36 = { 0, 1, 0, fmt_600, 0 };
    static cilist io___37 = { 0, 1, 0, fmt_603, 0 };
    static cilist io___38 = { 0, 1, 0, fmt_603, 0 };
    static cilist io___39 = { 0, 1, 0, fmt_402, 0 };
    static cilist io___40 = { 0, 1, 0, fmt_601, 0 };
    static cilist io___41 = { 0, 1, 0, fmt_403, 0 };
    static cilist io___42 = { 0, 1, 0, fmt_601, 0 };
    static cilist io___43 = { 0, 1, 0, fmt_404, 0 };
    static cilist io___49 = { 0, 1, 0, fmt_601, 0 };
    static cilist io___50 = { 0, 3, 1, fmt_200, 0 };
    static cilist io___51 = { 0, 1, 0, fmt_200, 0 };



/* 	MAIN ROUTINE TO CONVERT PRINTER GRAPHICS FILE TO POSTSCRIPT */

/* 	NAME	(CHARACTER)	FILE NAME */


/* 	DEFINITIONS FOR LINE TYPES */




/* 	INITIALIZE VARIABLES */

    lw = -1;
/* LINE WIDTH (INVALID TO FORCE NEW WIDTH) */
    lt = -1;
/* LINE TYPE (INVALID TO FORCE NEW TYPE) */
    lc = -1;

/* LINE COLOR (INVALID TO FORCE NEW TYPE) */
    amx = (float)288.;
    amy = (float)288.;
    mp = 999;
    ixold = (float)0.;
    iyold = (float)0.;

/* 	PENUP IS PEN CONTROL FLAG (0=NO SEGMENT, 2=PEN UP, 3=PEN DOWN) */

    penup = 0;
    jpcnt = 0;

/* 	OPEN INPUT FILE PRODUCED BY LONGLIB GRAPHICS LIBRARY */

    o__1.oerr = 0;
    o__1.ounit = 2;
    o__1.ofnmlen = name_len;
    o__1.ofnm = name;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
/*     $		ERR=99,READONLY) */

/* 	OPEN OUTPUT FILE */

    o__1.oerr = 0;
    o__1.ounit = 1;
    o__1.ofnmlen = 7;
    o__1.ofnm = "out.lis";
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);

/* 	SEND INITIALIZATION CODES TO OUTPUT FILE */

    s_wsle(&io___15);
    do_lio(&c__9, &c__1, "ADOBE ILLUSTRATOR POSTSCRIPT CONVERTER", 38L);
    e_wsle();
    o__1.oerr = 1;
    o__1.ounit = 3;
    o__1.ofnmlen = 12;
    o__1.ofnm = "ADIPS.HEADER";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L310;
    }
L910:
    i__1 = s_rsfe(&io___16);
    if (i__1 != 0) {
	goto L300;
    }
    i__1 = do_fio(&c__1, line, 80L);
    if (i__1 != 0) {
	goto L300;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L300;
    }
    s_wsfe(&io___18);
    do_fio(&c__1, line, 80L);
    e_wsfe();
    goto L910;
L300:
    cl__1.cerr = 0;
    cl__1.cunit = 3;
    cl__1.csta = 0;
    f_clos(&cl__1);
L310:
    jps = 1;

/* 	TOP OF LONGLIB META-FILE READ LOOP */

L1000:

/* 	READ INITIAL COMMAND CODE AND PARAMETERS FROM LONGLIB META-FILE */

    reget_(&m1, &m2, &m3, &mp, &c__2);

/* 	CHECK END OF FILE */

    if (m3 == 11) {
	goto L110;
    }
    sx = (real) m1;
    sy = (real) m2;
    if (m1 == 0 || m2 == 0) {
	goto L110;
    }
L1:

/* 	READ COMMAND CODE AND PARAMETERS FROM LONGLIB META-FILE */

    reget_(&m1, &m2, &m3, &mp, &c__2);

/* 	COORDINATE TRANSFORM */

L2:
    y1 = m1 / sx;
    x1 = m2 / sy;
    i3 = m3;
    iold = -1;

/* 	CHECK END OF FILE */

    if (m3 > 999) {
	goto L999;
    }

/* 	EXECUTE META-FILE COMMAND */

    switch ((int)i3) {
	case 1:  goto L10;
	case 2:  goto L20;
	case 3:  goto L20;
	case 4:  goto L10;
	case 5:  goto L10;
	case 6:  goto L10;
	case 7:  goto L10;
	case 8:  goto L10;
	case 9:  goto L20;
	case 10:  goto L100;
	case 11:  goto L110;
    }
L10:
    goto L1;

/* 	INTERPRET COMMAND */

L20:

/* 	"CALL PLOT(X1,Y1,I3)" */

/* 	CONVERT TO INTEGER 0.25/72'S INCH */

/* C	IX=INT(Y1*72+0.5)+5 */
/* C	IY=780-INT(X1*72+0.5) */
/* C	IX=INT(Y1*288+0.5)+5 */
/* C	IY=3120-INT(X1*288+0.5) */
    ix = y1 * (float)72.;
    iy = (float)780. - x1 * (float)72.;
    if (iy < (float)0.) {
	iy = (float)0.;
    }
    if (i3 == 3) {

/* 	PEN UP MOVE */

	if (penup == 2) {
	    i__1 = (integer) (ixold + (float).9999);
	    kx = idigits_(&i__1);
	    i__1 = (integer) (iyold + (float).9999);
	    ky = idigits_(&i__1);
	    s_wsfe(&io___33);
	    do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	    e_wsfe();
	}
	penup = 3;
	jpcnt = 0;
    } else {

/* 	PEN DOWN MOVE */
/* 				! PEN DOWN MOVE */
	if (penup == 3) {
	    i__1 = (integer) (ix + (float).9999);
	    kx = idigits_(&i__1);
	    i__1 = (integer) (iy + (float).9999);
	    ky = idigits_(&i__1);
	    s_wsfe(&io___34);
	    do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	    e_wsfe();
/* L602: */
	    jpcnt = 0;
	}
	penup = 2;
	i__1 = (integer) (ix + (float).9999);
	kx = idigits_(&i__1);
	i__1 = (integer) (iy + (float).9999);
	ky = idigits_(&i__1);

/* 	OUTPUT LINE CONTINUATION.  IF # POINTS EXCEEDS 256, OUTPUT */
/* 	ALSO, DON'T OUTPUT REDUNDANT POINTS */

	if (jpcnt > 256) {
	    s_wsfe(&io___35);
	    do_fio(&c__1, (char *)&ix, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iy, (ftnlen)sizeof(real));
	    e_wsfe();
	    s_wsfe(&io___36);
	    do_fio(&c__1, (char *)&ix, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iy, (ftnlen)sizeof(real));
	    e_wsfe();
	    jpcnt = 0;
	} else {
	    if (jpcnt == 0 || (ix != ixold || iy != iyold)) {
		s_wsfe(&io___37);
		do_fio(&c__1, (char *)&ix, (ftnlen)sizeof(real));
		do_fio(&c__1, (char *)&iy, (ftnlen)sizeof(real));
		e_wsfe();
		++jpcnt;
	    }
	}
    }
    ixold = ix;
    iyold = iy;
    goto L1;

L100:

/* 	"CALL NEWPAGE" */

    if (penup == 2) {
	i__1 = (integer) (ixold + (float).9999);
	kx = idigits_(&i__1);
	i__1 = (integer) (iyold + (float).9999);
	ky = idigits_(&i__1);
	s_wsfe(&io___38);
	do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	e_wsfe();
	penup = 0;
	jpcnt = 0;
    }
    ++jps;
    s_wsfe(&io___39);
    do_fio(&c__1, (char *)&jps, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&jps, (ftnlen)sizeof(integer));
    e_wsfe();
/* 402	FORMAT(X,'grestore showpage', */
/*     $	/'%%Page: ',I2,1X,I2/ */
/*     $		X,'0.25 0.25 scale'	! SCALE TO 288 DOTS/INCH */
/*     $		X,'gsave') */
/* c	WRITE (1,403) LINETYPE(LT+1) */
/* c	WRITE (1,404) LW-1 */
    goto L1;

/* 	SPECIAL COMMANDS */

L999:
    jpcnt = 0;
    if (i3 > 1999) {
	goto L1999;
    }
    switch ((int)(i3 - 999)) {
	case 1:  goto L1000;
	case 2:  goto L1001;
	case 3:  goto L1002;
	case 4:  goto L1003;
    }
/* L998: */
    goto L1;

/* 	NEW PEN/LINE TYPE */

L1001:
    if (m1 < 0) {
	m1 = 0;
    }
    if (m1 > 9) {
	m1 %= 10;
    }
    if (m1 != lt) {
	if (penup == 2) {
	    i__1 = (integer) (ixold + (float).9999);
	    kx = idigits_(&i__1);
	    i__1 = (integer) (iyold + (float).9999);
	    ky = idigits_(&i__1);
	    s_wsfe(&io___40);
	    do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	    e_wsfe();
	    penup = 0;
	}
	s_wsfe(&io___41);
	do_fio(&c__1, linetype + m1 * 13, 13L);
	e_wsfe();
	lt = m1;
    }
    goto L1;

/* 	LINE COLOR */

L1002:
/* 	LW=M1 */

/* 	INCLUDE PEN COLOR AS GRAY SCALE (0-16) BLACK=16, WHITE=0 */

    if (m2 != lc) {

/* 	"CALL PLOT(FLOAT(M2),0.,0)" */

/* 		WRITE (1,407) FLOAT(M2-1)/16. */
/* 407		FORMAT(X,F4.2,' setgray') */
    }
    lc = m2;
    goto L1;

/* 	LINEWIDTH */

L1003:

/* 	"CALL NEWPEN(I3)" */

    if (m1 <= 0) {
	m1 = 1;
    }

/* 	NOTE: THE LINEWIDTH IS GRAPHICS DEVICE DEPENDENT AND MAY VARY */
/* 	DEPENDING ON LINE ORIENTATION */

    if (m1 != lw) {
	if (penup == 2) {
	    i__1 = (integer) (ixold + (float).9999);
	    kx = idigits_(&i__1);
	    i__1 = (integer) (iyold + (float).9999);
	    ky = idigits_(&i__1);
	    s_wsfe(&io___42);
	    do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	    e_wsfe();
	    penup = 0;
	}

/* 	NEW LINE WIDTH */

	s_wsfe(&io___43);
	do_fio(&c__1, (char *)&m1, (ftnlen)sizeof(integer));
	e_wsfe();
	lw = m1;
    }
    goto L1;

/* 	IMAGE MODE */

L1999:

/* 	CHECK EACH OPTION */

    if (i3 == 2000) {
	y1 = m1 / sx;
	x1 = m2 / sy;
	amx = x1 * 288;
	amy = y1 * 288;
    }
    if (i3 == 2001) {
	inx = m1;
	if (inx < 1) {
	    inx = 1;
	}
	iny = m2;
	if (iny < 1) {
	    iny = 1;
	}
	num = inx * iny;
	iy = iyold - i_nint(&amy);
/* c		WRITE (1,2020) IXOLD,IY,AMX,AMY,INY,INX,INY,-INX,INX */
/* L2020: */

/* 	READ IMAGE DATA AND CONVERT TO HEXIDECIMAL */

	if (num % 2 == 1) {
	    ++num;
	}
	num /= 2;
	ic = 0;
	i__1 = num;
	for (i = 1; i <= i__1; ++i) {
	    reget_(&m1, &m2, &m3, &mp, &c__2);
	    if (m3 != 2002) {
		goto L2;
	    }
	    hexit_(&m1, &m2, &ic);
/* L2002: */
	}
	if (ic > 0) {
	    i__1 = -ic;
	    hexit_(&m1, &m2, &i__1);
	}
/* c		WRITE (1,2030) */
/* L2030: */
    }
    goto L1;

/* 	CLOSE INPUT FILE */

L110:
    cl__1.cerr = 0;
    cl__1.cunit = 2;
    cl__1.csta = 0;
    f_clos(&cl__1);

    if (penup == 2) {
	i__1 = (integer) (ixold + (float).9999);
	kx = idigits_(&i__1);
	i__1 = (integer) (iyold + (float).9999);
	ky = idigits_(&i__1);
	s_wsfe(&io___49);
	do_fio(&c__1, (char *)&ixold, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&iyold, (ftnlen)sizeof(real));
	e_wsfe();
	penup = 0;
    }

/* 	WRITE (1,410)jps */
/* 410	FORMAT(X,'grestore showpage', */
/*     $	/'%%Trailer', */
/*     $	/'%%Pages: ',I2,1X,'1', */
/*     $	/) */

    o__1.oerr = 1;
    o__1.ounit = 3;
    o__1.ofnmlen = 13;
    o__1.ofnm = "ADIPS.TRAILER";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L510;
    }
L410:
    i__1 = s_rsfe(&io___50);
    if (i__1 != 0) {
	goto L500;
    }
    i__1 = do_fio(&c__1, line, 80L);
    if (i__1 != 0) {
	goto L500;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L500;
    }
    s_wsfe(&io___51);
    do_fio(&c__1, line, 80L);
    e_wsfe();
    goto L410;
L500:
    cl__1.cerr = 0;
    cl__1.cunit = 3;
    cl__1.csta = 0;
    f_clos(&cl__1);

/* 	CLOSE OUTPUT FILE */

L510:
    cl__1.cerr = 0;
    cl__1.cunit = 1;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* L99: */
    return 0;
} /* lplot_ */


/* Subroutine */ int reget_(m1, m2, m3, mp, ilu)
integer *m1, *m2, *m3, *mp, *ilu;
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_rsue(), do_uio(), e_rsue();

    /* Local variables */
    static shortint m[128];

    /* Fortran I/O blocks */
    static cilist io___52 = { 1, 0, 0, 0, 0 };



/* 	READ DATA FROM LONGLIB META-FILE PRINTER DATA FILE */

    *mp += 3;
    if (*mp > 128) {
	io___52.ciunit = *ilu;
	i__1 = s_rsue(&io___52);
	if (i__1 != 0) {
	    goto L99;
	}
	i__1 = do_uio(&c__128, (char *)&m[0], (ftnlen)sizeof(shortint));
	if (i__1 != 0) {
	    goto L99;
	}
	i__1 = e_rsue();
	if (i__1 != 0) {
	    goto L99;
	}
	*mp = 3;
    }
    *m3 = m[*mp - 1];
    *m2 = m[*mp - 2];
    *m1 = m[*mp - 3];
    if (*m3 == 999) {
	goto L99;
    }
    return 0;
L99:
    *m3 = 11;
    return 0;
} /* reget_ */



integer idigits_(i)
integer *i;
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    static integer n;

    n = 1;
    if (*i > 9) {
	++n;
    }
    if (*i > 99) {
	++n;
    }
    if (*i > 999) {
	++n;
    }
    if (*i > 9999) {
	++n;
    }
    ret_val = n;
    return ret_val;
} /* idigits_ */



/* Subroutine */ int hexit_(i, j, ic)
integer *i, *j, *ic;
{
    /* Format strings */
    static char fmt_10[] = "(x,38z2.2)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe();

    /* Local variables */
    static integer icnt, c[38];

    /* Fortran I/O blocks */
    static cilist io___56 = { 0, 1, 0, fmt_10, 0 };
    static cilist io___58 = { 0, 1, 0, fmt_10, 0 };


    if (*ic == 0) {
	icnt = 1;
    }
    if (*ic < 0) {
/* DUMP OUTPUT BUFFER */
	if (icnt > 1) {
	    s_wsfe(&io___56);
	    i__1 = icnt - 1;
	    for (*i = 1; *i <= i__1; ++(*i)) {
		do_fio(&c__1, (char *)&c[*i - 1], (ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}
	icnt = 1;
	goto L100;
    }
    *ic = 1;
    c[icnt - 1] = *i;
    if (c[icnt - 1] < 0) {
	c[icnt - 1] = 0;
    }
    if (c[icnt - 1] > 255) {
	c[icnt - 1] = 255;
    }
    ++icnt;
    c[icnt - 1] = *j;
    if (c[icnt - 1] < 0) {
	c[icnt - 1] = 0;
    }
    if (c[icnt - 1] > 255) {
	c[icnt - 1] = 255;
    }
    ++icnt;
    if (icnt >= 38) {
	s_wsfe(&io___58);
	for (*i = 1; *i <= 38; ++(*i)) {
	    do_fio(&c__1, (char *)&c[*i - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
	icnt = 1;
    }
L100:
    return 0;
} /* hexit_ */

/* Main program alias */ int illus_ () { MAIN__ (); }
