
/* *** LAST REVISED ON  7-JAN-1994 13:13:47.04 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]VAX3D.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xscale, yscale, zscale, amin, alph, bet;
} locate_;

#define locate_1 locate_

/* Table of constant values */

static integer c__2 = 2;
static integer c__1 = 1;
static integer c__3 = 3;
static real c_b12 = (float)1.5;
static real c_b13 = (float).65;
static real c_b14 = (float)1.;
static integer c_n1 = -1;
static real c_b18 = (float)90.;
static real c_b21 = (float)0.;
static integer c__0 = 0;

/* Subroutine */ int vax3d_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, xt, nxt, xastart, xaend, yt, nyt, zt, nzt, zastart, 
	zaend, aminin, amaxin, icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
char *xt;
integer *nxt;
real *xastart, *xaend;
char *yt;
integer *nyt;
char *zt;
integer *nzt;
real *zastart, *zaend, *aminin, *amaxin;
integer *icol;
{
    /* System generated locals */
    integer a_dim1, a_offset;

    /* Local variables */
    static integer ic;
    extern /* Subroutine */ int vax3dx_();
    static real amn;
    static integer iax;
    static real amx;
    static integer ndx, ndy, ndz, mlx, nmx, nnx, nmy, nny, mly;
    static real smx, smy;
    static integer nmz, nnz;
    static real tsx, tsy;
    static integer mlz;
    static real tsz, smz;


/* 	CREATED BY D. LONG  MAR., 1984	AT JPL */

/* 	SIMPLIFIES CALLING VAX3DX ROUTINE AXISES */

    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    iax = *iaxis % 10;
    if (*iaxis < 0) {
	amn = *aminin;
	amx = *amaxin;
    }
    if (*iflag % 10 == 2) {
	vax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &nmx, &nnx, &mlx, &tsx, 
		&ndx, &smx, yt, nyt, &nmy, &nny, &mly, &tsy, &ndy, &smy, zt, 
		nzt, zastart, zaend, &nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn,
		 &amx, &icol[1]);
    } else {
	vax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &nmx, &nnx, &mlx, &tsx, 
		&ndx, &smx, yt, nyt, &nmy, &nny, &mly, &tsy, &ndy, &smy, zt, 
		nzt, zastart, zaend, &nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn,
		 &amx, &ic);
    }
    return 0;
} /* vax3d_ */



/* Subroutine */ int vax3dx_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, xt, nxt, xastart, xaend, nmx, nnx, mlx, tsx, ndx, smx, 
	yt, nyt, nmy, nny, mly, tsy, ndy, smy, zt, nzt, zastart, zaend, nmz, 
	nnz, mlz, tsz, ndz, smz, aminin, amaxin, icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
char *xt;
integer *nxt;
real *xastart, *xaend;
integer *nmx, *nnx, *mlx;
real *tsx;
integer *ndx;
real *smx;
char *yt;
integer *nyt, *nmy, *nny, *mly;
real *tsy;
integer *ndy;
real *smy;
char *zt;
integer *nzt;
real *zastart, *zaend;
integer *nmz, *nnz, *mlz;
real *tsz;
integer *ndz;
real *smz, *aminin, *amaxin;
integer *icol;
{
    /* Initialized data */

    static real tpi = (float)3.141592654;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double atan2();

    /* Local variables */
    static integer nadd;
    static logical flag_;
    static integer idct;
    static real amax;
    static integer ihct, ipen, ipct;
    extern /* Subroutine */ int axis_();
    static real xlen, ylen, zlen;
    extern /* Subroutine */ int plot_(), axis2_();
    static real h[4096]	/* was [2048][2] */;
    static integer i;
    static real p[4096]	/* was [2048][2] */;
    static logical hhigh;
    extern /* Subroutine */ int scale_();
    static real x;
    extern /* Subroutine */ int frame_();
    static real y;
    static integer ihold;
    extern /* Subroutine */ int cterm_();
    static integer n1, n2;
    static real x0, y0;
    extern /* Subroutine */ int intersect_();
    static real bh;
    static integer ic[4], jf;
    static real as[2];
    extern /* Subroutine */ int vxpt3d_();
    static integer ip;
    static real dx, dy, dz;
    static integer iz, ix;
    static real xp, yp;
    extern /* Subroutine */ int plotnd_();
    static real dx1, dy1, dx2, dy2, hx1, hy1, hx2, hy2, xp1, yp1, xp2, yp2, 
	    daa;
    static integer iaf, jff;
    static real ang, amh;
    static integer ilu;

/* 	CREATED BY D. LONG     APR, 1984	AT JPL */
/* 	REVISED BY D. LONG     MAY, 1986 */
/* 	+REDUCED REDUNDANT PEN MOTIONS AND CORRECTED SOME MINOR BUGS */

/* 	ROUTINE TO PLOT DATA IN 3-D OVERLAY FORM */

/* 	COORDINATE SYSTEM IS:		Y  Z */
/* 				NAMES:	|/ */
/* 					 \X */

/* 	A	REAL ARRAY A(INX,INZ) CONTAINING VERTICAL HEIGHT DATA */
/* 	INX,INZ INTEGERS DIMENSION OF A ARRAY */
/* 	NX,NZ	INTEGERS INDICATING SIZE OF A ARRAY TO PLOT */
/* 	ALPHA	REAL ANGLE (IN DEGREES) OF X AXIS (NX) FROM HORIZONTAL */
/* 	BETA	REAL ANGLE (IN DEGREES) OF Z AXIS (NZ) FROM HORIZONTAL */
/* 	XH,YH,ZH REAL LENGTH OF EACH AXIS */
/* 	IFLAG	INTEGER */
/* 		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT) = 2 USE PEN COLOR CONTROL ARRAY */
/* 		      = 1 DO NOT USE PEN COLOR ARRAY */
/* 	(TEN'S DIGIT) = 0 PLOT SIDE PLATES */
/* 		      = 1 DO NOT PLOT SIDE PLATES */
/* 	(HUNDREDS'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		           <>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	INTEGER AXIS OPTION FLAG */
/* 			= 0 DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0 PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED 
*/
/*			> 0 PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSE
D*/
/* 	(ONE'S DIGIT)	= 1 PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2 PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 0 DEFAULT AXIS PARAMETERS */
/* 			= 1 SPECIALIZED AXIS2 PARAMETERS */
/* 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,ZASTART	REAL AXIS START VALUES */
/* 	XAEND,ZAEND	REAL AXIS END VALUES */
/* FOLLOWING ONLY ACCESSED IF TEN'S DIGIT OF IFLAG=1 */
/* 	NMX,NMY,NMZ	INT NUMBER OF MINOR TICKS BETWEEN MAJOR TICKS */
/* 	NNX,NNY,NNZ	INT HIGHLIGHT LENGTH OF NNX-TH MINOR TICK ON AXIS */
/* 	MLX,MLY,MLZ	INT NUMBER OF MAJOR TICK MARKS ON AXIS */
/* 	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	NDX,NDY,NDZ	INT NUMBER OF DIGITS TO RIGHT OF DECIMAL POINT */
/* 	SMX,SMY,SMZ	REAL MAJOR TICK LENGTH */
/* 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) 
*/
/* 	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MAG(IFLAG)=2) */
/* 			  ICOL(1) AXIS LINE COLOR */
/* 			  ICOL(2) AXIS NUMBERS COLOR */
/* 			  ICOL(3) AXIS TITLE COLOR */
/* 			  ICOL(4) AXIS EXPONENT COLOR */
/* 			  ICOL(5) PLOT COLOR */

    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }
    locate_1.alph = *alpha * tpi / (float)180.;
/* X-AXIS INCLINATION 0-80 DEGS */
    locate_1.bet = *beta * tpi / (float)180.;

/* Z-AXIS ANGLE 5-80 DEGS */
    if (*iaxis < 0) {
	amax = *amaxin;
	locate_1.amin = *aminin;
    } else {
	amax = a[a_dim1 + 1];
	locate_1.amin = a[a_dim1 + 1];
	i__1 = *nz;
	for (iz = 1; iz <= i__1; ++iz) {
/* DETERMINE MAX,MIN ARRAY VALUES */
	    i__2 = *nx;
	    for (ix = 1; ix <= i__2; ++ix) {
/* Computing MAX */
		r__1 = amax, r__2 = a[ix + iz * a_dim1];
		amax = dmax(r__1,r__2);
/* Computing MIN */
		r__1 = locate_1.amin, r__2 = a[ix + iz * a_dim1];
		locate_1.amin = dmin(r__1,r__2);
/* L16: */
	    }
	}
    }
    if (*alpha < (float)0. || *alpha > (float)88. || *beta < (float)1. || *
	    beta > (float)90.) {
	printf("\n*** VAX3DX ANGLE SPECIFICATION ERROR ***\n");
	return 0;
    }
    if (amax == locate_1.amin) {
	printf("\n*** VAX3DX SCALE ERROR ***\n");
	amax = locate_1.amin + (float)1.;
    }

    xlen = dabs(*xh);
    locate_1.xscale = xlen / (real) (*nx - 1);
    zlen = dabs(*zh);
    locate_1.zscale = zlen / (real) (*nz - 1);
    ylen = dabs(*yh);
    if (abs(*iaxis) % 10 == 2) {
/* SMOOTH SCALE FACTORS */
	as[0] = amax;
	as[1] = locate_1.amin;
	scale_(as, &ylen, &c__2, &c__1, &c__1, &locate_1.amin, &daa);
	amax = ylen * daa + locate_1.amin;
    }
    locate_1.yscale = (float)1.;
    if (amax - locate_1.amin != (float)0.) {
	locate_1.yscale = ylen / (amax - locate_1.amin);
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf / 100;
	frame_(&c__3, &ilu, &c_b12, &c_b13, &c_b14);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL PLOT MODE */
    }

    iaf = abs(*iaxis) / 10;
    jff = jf % 100 / 100;
    jf %= 10;
    if (*iaxis != 0) {
/* PLOT AXIS LABELS */
	nadd = 0;
	if (jf == 2) {
	    ic[0] = icol[2];
	    ic[1] = icol[3];
	    ic[2] = icol[4];
	    ic[3] = icol[5];
	    nadd = 100000;
/* PEN COLOR */
	}
	vxpt3d_(&xp, &yp, &locate_1.amin, &c__1, &c__1, nx);
	dy = (amax - locate_1.amin) / ylen;
	if (*nyt > 0) {
/* PLOT Y AXIS */
	    if (iaf == 1) {
		i__2 = *nyt + 11000 + nadd;
		i__1 = -abs(*mly);
		axis2_(&xp, &yp, yt, &i__2, &ylen, &c_b18, &locate_1.amin, &
			dy, nmy, nny, &i__1, tsy, ndy, smy, ic);
	    } else {
		i__2 = *nyt + 1000 + nadd;
		axis_(&xp, &yp, yt, &i__2, &ylen, &c_b18, &locate_1.amin, &dy,
			 &n1, &n2, ic);
	    }
	}
	vxpt3d_(&xp1, &yp1, &locate_1.amin, nx, &c__1, nx);
	dx = (*xaend - *xastart) / xlen;
	ang = atan2(yp1 - yp, xp1 - xp) * (float)180. / tpi;
	if (*nxt > 0) {
	    if (iaf == 1) {
		i__2 = -(*nxt) - nadd - 10000;
		i__1 = -abs(*mlx);
		axis2_(&xp, &yp, xt, &i__2, &xlen, &ang, xastart, &dx, nmx, 
			nnx, &i__1, tsx, ndx, smx, ic);
	    } else {
		i__2 = -(*nxt) - nadd;
		axis_(&xp, &yp, xt, &i__2, &xlen, &ang, xastart, &dx, &n1, &
			n2, ic);
	    }
	}
	dz = (*zaend - *zastart) / zlen;
	if (*nzt > 0) {
	    if (iaf == 1) {
		i__2 = -(*nzt) - nadd - 10000;
		i__1 = -abs(*mlz);
		axis2_(&xp1, &yp1, zt, &i__2, &zlen, beta, zastart, &dz, nmz, 
			nnz, &i__1, tsz, ndz, smz, ic);
	    } else {
		i__2 = -(*nzt) - nadd;
		axis_(&xp1, &yp1, zt, &i__2, &zlen, beta, zastart, &dz, &n1, &
			n2, ic);
	    }
	}
    }
    if (jf == 2) {
	r__1 = (real) icol[5];
	plot_(&r__1, &c_b21, &c__0);
    }

/* 	PLOT FRONT PLATE */

/* PEN COLOR */
    ipen = 3;
    i__2 = *nx;
    for (i = 1; i <= i__2; ++i) {
	if (i > 2048) {
	    goto L999;
	}
	vxpt3d_(&h[i - 1], &h[i + 2047], &a[i + a_dim1], &i, &c__1, nx);
/* INTIALIZE HISTORY */
	plot_(&h[i - 1], &h[i + 2047], &ipen);
/* PLOT SIDE LINE */
	ipen = 2;
/* L14: */
    }
    ihold = *nx;
    if (*beta == (float)90.) {
	goto L5;
    }
    if (jff == 1) {
	goto L71;
    }
/* DON'T PLOT SIDE PLATES */
    vxpt3d_(&xp, &yp, &locate_1.amin, nx, &c__1, nx);
    plot_(&xp, &yp, &c__2);
    i__2 = *nx - 1;
    for (i = 1; i <= i__2; ++i) {
/* ADD SIDE LINES */
	plot_(&h[i - 1], &h[i + 2047], &c__3);
	vxpt3d_(&xp, &yp, &locate_1.amin, &i, &c__1, nx);
	plot_(&xp, &yp, &c__2);
	i__1 = i + 1;
	vxpt3d_(&xp, &yp, &locate_1.amin, &i__1, &c__1, nx);
	plot_(&xp, &yp, &c__2);
/* L19: */
    }

/* 	PLOT SIDE PLATE */

L71:
    plot_(&h[*nx - 1], &h[*nx + 2047], &c__3);
    i__2 = *nz;
    for (i = 1; i <= i__2; ++i) {
/* PLOT RIGHT SIDE CURVE */
	if (*nx + i > 2048) {
	    goto L999;
	}
	vxpt3d_(&xp, &yp, &a[*nx + i * a_dim1], nx, &i, nx);
	h[*nx + i - 1] = xp;
	h[*nx + i + 2047] = yp;
	plot_(&xp, &yp, &c__2);
/* L23: */
    }
    vxpt3d_(&xp, &yp, &locate_1.amin, nx, &c__1, nx);
    plot_(&xp, &yp, &c__3);
    ihold = *nx + *nz;
/* NUMBER OF H VALUES */
    if (jff == 1) {
	goto L5;
    }
/* DON'T PLOT SIDE PLATES */
    i__2 = *nz;
    for (i = 2; i <= i__2; ++i) {
/* ADD SIDE LINES */
	vxpt3d_(&xp2, &yp2, &locate_1.amin, nx, &i, nx);
	plot_(&xp2, &yp2, &c__2);
	vxpt3d_(&xp, &yp, &a[*nx + i * a_dim1], nx, &i, nx);
	plot_(&xp, &yp, &c__2);
	plot_(&xp, &yp2, &c__3);
/* L24: */
    }

/* 	BEGIN MAIN LOOP */

L5:
    i__2 = *nz;
    for (iz = 2; iz <= i__2; ++iz) {
/* OVER Z DIMENSION TOWARD REAR */
	ipct = 1;
	idct = 1;
	ihct = 1;

/* 	DETERMINE START POINT LOCATION */

	vxpt3d_(&xp1, &yp1, &a[idct + iz * a_dim1], &c__1, &iz, nx);

/* LEFT MOST DATA POINT */
	if (xp1 < h[0]) {
/* 			IF (IPCT.GT.MAXSIZE) GOTO 999 */
/* 			P(IPCT,1)=XP1 */
/* 			P(IPCT,2)=YP1 */
/* 			IPCT=IPCT+1 */
/* DATA TO LEFT OF HISTORY ARRAY */
	    plot_(&xp1, &yp1, &c__3);
	    i__1 = *nx;
	    for (i = 1; i <= i__1; ++i) {
/* (VERY RARE) */
		vxpt3d_(&xp1, &yp1, &a[i + iz * a_dim1], &i, &iz, nx);
		if (xp1 > h[0]) {
		    idct = i - 1;
		    vxpt3d_(&dx1, &dy1, &a[idct + iz * a_dim1], &idct, &iz, 
			    nx);
		    hhigh = FALSE_;
		    hx1 = h[0];
		    hy1 = h[2048];
		    hx2 = h[1];
		    hy2 = h[2049];
		    ++idct;
		    ihct += 2;
		    vxpt3d_(&dx2, &dy2, &a[idct + iz * a_dim1], &idct, &iz, 
			    nx);
		    ++idct;
		    goto L100;
		}
		if (ipct > 2048) {
		    goto L999;
		}
		p[ipct - 1] = xp1;
		p[ipct + 2047] = yp1;
		++ipct;
		plot_(&xp1, &yp1, &c__2);
/* L6: */
	    }
	}

	idct = 2;
	i__1 = iz - 1;
	vxpt3d_(&dx1, &dy1, &a[(iz - 1) * a_dim1 + 1], &c__1, &i__1, nx);
	vxpt3d_(&dx2, &dy2, &a[iz * a_dim1 + 1], &c__1, &iz, nx);
/* C		CALL PLOT(H(1,1),H(1,2),3) */
	x0 = h[0];
	y0 = h[2048];
	ip = 3;
	if (ipct > 2048) {
	    goto L999;
	}
	p[ipct - 1] = h[0];
	p[ipct + 2047] = h[2048];
	++ipct;
	i__1 = ihold;
	for (i = 2; i <= i__1; ++i) {
	    if (h[i - 1] > dx1) {
		goto L8;
	    }
	    if (ipct > 2048) {
		goto L999;
	    }
	    p[ipct - 1] = h[i - 1];
	    p[ipct + 2047] = h[i + 2047];
	    ++ipct;
/* C				CALL PLOT(H(I,1),H(I,2),2) */
	    x0 = h[i - 1];
	    y0 = h[i + 2047];
/* L7: */
	}
L8:
	ihct = i - 1;
	hx1 = h[ihct - 1];
	hy1 = h[ihct + 2047];
	hx2 = h[ihct];
	hy2 = h[ihct + 2048];
	ihct += 2;
	hhigh = TRUE_;
	if (hx1 == hx2) {
	    if (ihct == ihold) {
		goto L100;
	    }
	    ++ihct;
	    goto L8;
	}
	amh = (hy2 - hy1) / (hx2 - hx1);
	bh = hy1 - hx1 * amh;
	yp = amh * dx1 + bh;
	if (yp <= dy1) {
	    hhigh = FALSE_;
	}
	if (hy1 == dy1 && hx1 == dx1) {
	    hhigh = TRUE_;
	    yp = amh * dx2 + bh;
	    if (yp < dy2) {
		hhigh = FALSE_;
	    }
	}

/* 	TOP OF INNER LOOP */

L100:
	intersect_(&flag_, &x, &y, &hx1, &hy1, &hx2, &hy2, &dx1, &dy1, &dx2, &
		dy2, &hhigh);
	if (flag_) {
/* SEGMENTS INTERSECT */
	    hx1 = x;
/* DRAW SEGMENT WITH */
	    hy1 = y;
/* HIGHEST START POINT */
	    dx1 = x;
/* TO THE INTERSECTION */
	    dy1 = y;
	    if (ipct > 2048) {
		goto L999;
	    }
	    p[ipct - 1] = x;
	    p[ipct + 2047] = y;
	    ++ipct;
	    if (ip == 2) {
		plot_(&x, &y, &c__2);
	    }
	    x0 = x;
	    y0 = y;
	    goto L100;
	}

	if (hx2 <= dx2) {
/* CHECKED ALL H SEGS OVER D SEGS */
	    if (hhigh) {
/* DRAW HIGHEST SEGMENT */
		if (ipct > 2048) {
		    goto L999;
		}
		p[ipct - 1] = hx2;
		p[ipct + 2047] = hy2;
		++ipct;
		if (ip == 3) {
		    plot_(&x0, &y0, &c__3);
		}
		plot_(&hx2, &hy2, &c__2);
		x0 = hx2;
		y0 = hy2;
		ip = 2;
	    }
	    hx1 = hx2;
	    hy1 = hy2;
	    hx2 = h[ihct - 1];
	    hy2 = h[ihct + 2047];
	    ++ihct;
	    if (ihct > ihold + 1) {
L34:
		if (idct <= *nx + 1) {
		    i__1 = idct - 1;
		    vxpt3d_(&x, &y, &a[idct - 1 + iz * a_dim1], &i__1, &iz, 
			    nx);
		    if (ipct > 2048) {
			goto L999;
		    }
		    p[ipct - 1] = x;
		    p[ipct + 2047] = y;
		    ++ipct;
		    if (ip == 3) {
			plot_(&x0, &y0, &c__3);
		    }
		    ip = 2;
		    plot_(&x, &y, &c__2);
		    ++idct;
		    goto L34;
		}
		goto L200;
/* DONE WITH H'S */
	    }
	    if (hx1 == dx2) {
		dx1 = dx2;
/* NEXT DATA POINT */
		dy1 = dy2;
		x0 = dx1;
		y0 = dy1;
/* C					IF (.NOT.HHIGH)CALL PLOT(DX1,DY1,2) */
		vxpt3d_(&dx2, &dy2, &a[idct + iz * a_dim1], &idct, &iz, nx);
		++idct;
		if (idct > *nx + 2) {
		    goto L235;
		}
/* DONE WITH DATA */
		if (idct > *nx + 1) {
		    dx2 = dx1;
		    dy2 = locate_1.amin;
		}
		hhigh = TRUE_;
		if (dy1 > hy1) {
		    hhigh = FALSE_;
		}
	    }
	    goto L100;
	} else {
	    if (! hhigh) {
/* PLOT DATA THAT IS HIGHEST */
		if (ipct > 2048) {
		    goto L999;
		}
		p[ipct - 1] = dx2;
		p[ipct + 2047] = dy2;
		++ipct;
		if (ip == 3) {
		    plot_(&x0, &y0, &c__3);
		}
		plot_(&dx2, &dy2, &c__2);
		ip = 2;
		x0 = dx2;
		y0 = dy2;
	    }
	    dx1 = dx2;
/* NEXT DATA POINT */
	    dy1 = dy2;
	    vxpt3d_(&dx2, &dy2, &a[idct + iz * a_dim1], &idct, &iz, nx);
	    ++idct;
	    if (idct > *nx + 2) {
		goto L235;
	    }
/* DONE WITH DATA */
	    if (idct > *nx + 1) {
		dx2 = dx1;
		dy2 = locate_1.amin;
	    }
	}

/* 	DONE WITH INNER LOOP */

	goto L100;

L200:
	ihold = ipct - 1;
/* STORE NEW HISTORY */
	i__1 = ipct;
	for (i = 1; i <= i__1; ++i) {
	    h[i - 1] = p[i - 1];
	    h[i + 2047] = p[i + 2047];
/* L201: */
	}

/* 	END MAIN LOOP */

/* L500: */
    }

L520:
    plot_(&c_b21, &c_b21, &c__3);
/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);
/* CLEAR TERMINAL */
	plotnd_();
/* CLOSE PLOT OUTPUT */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);
/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;
L235:
/* FINISH H CURVE WHEN OUT OF DATA */
    --ihct;
L236:
    if (ihct > ihold) {
	goto L200;
    }
    x = h[ihct - 1];
    y = h[ihct + 2047];
    ++ihct;
    if (ipct > 2048) {
	goto L999;
    }
    p[ipct - 1] = x;
    p[ipct + 2047] = y;
    ++ipct;
/* C		CALL PLOT(X,Y,2) */
    ++idct;
    goto L236;
L999:
    cterm_(&c__1);
    printf("\n*** VAX3DX INTERNAL STORAGE EXHAUSTED ***\n");
    goto L520;
} /* vax3dx_ */

