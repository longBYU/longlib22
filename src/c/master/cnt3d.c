
/* *** LAST REVISED ON  7-JAN-1994 13:07:04.60 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CNT3D.C */

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
static real c_b22 = (float)0.;
static integer c__0 = 0;

/* Subroutine */ int cnt3d_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	nlevels, astart, aend, idir, iflag, iaxis, xt, nxt, xastart, xaend, 
	yt, nyt, zt, nzt, zastart, zaend, aminin, amaxin, icol, iline)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *nlevels;
real *astart, *aend;
integer *idir, *iflag, *iaxis;
char *xt;
integer *nxt;
real *xastart, *xaend;
char *yt;
integer *nyt;
char *zt;
integer *nzt;
real *zastart, *zaend, *aminin, *amaxin;
integer *icol, *iline;
{
    /* System generated locals */
    integer a_dim1, a_offset;

    /* Local variables */
    extern /* Subroutine */ int cnt3dx_();
    static integer ic;
    static real amn;
    static integer iax;
    static real amx;
    static integer ndx, ndy, ndz, mlx, nmx, nnx, nmy, nny, mly;
    static real smx, smy;
    static integer nmz, nnz;
    static real tsx, tsy;
    static integer mlz;
    static real tsz, smz;


/* 	CREATED BY D. LONG  JULY, 1985	AT JPL */
/* 	MODIFIED BY D. LONG   FEB, 1986 AT JPL + ADDED LINE TYPE ARRAY */

/* 	SIMPLIFIES CALLING CNT3DX ROUTINE AXISES */

    /* Parameter adjustments */
    --iline;
    --icol;
    --astart;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    iax = *iaxis % 10;
    if (*iaxis < 0) {
	amn = *aminin;
	amx = *amaxin;
    }
    if (abs(*iflag) % 10 == 1) {
	cnt3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		nlevels, &astart[1], aend, idir, iflag, &iax, xt, nxt, 
		xastart, xaend, &nmx, &nnx, &mlx, &tsx, &ndx, &smx, yt, nyt, &
		nmy, &nny, &mly, &tsy, &ndy, &smy, zt, nzt, zastart, zaend, &
		nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn, &amx, &icol[1], &ic);
    } else if (abs(*iflag) % 10 > 1) {
	cnt3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		nlevels, &astart[1], aend, idir, iflag, &iax, xt, nxt, 
		xastart, xaend, &nmx, &nnx, &mlx, &tsx, &ndx, &smx, yt, nyt, &
		nmy, &nny, &mly, &tsy, &ndy, &smy, zt, nzt, zastart, zaend, &
		nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn, &amx, &icol[1],
		&iline[1]);
    } else {
	cnt3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		nlevels, &astart[1], aend, idir, iflag, &iax, xt, nxt, 
		xastart, xaend, &nmx, &nnx, &mlx, &tsx, &ndx, &smx, yt, nyt, &
		nmy, &nny, &mly, &tsy, &ndy, &smy, zt, nzt, zastart, zaend, &
		nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn, &amx, &ic, &ic);
    }
    return 0;
} /* cnt3d_ */


/****************************************************************************/


/* Subroutine */ int cnt3dx_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	nlevels, astart, aend, idir, iflag, iaxis, xt, nxt, xastart, xaend, 
	nmx, nnx, mlx, tsx, ndx, smx, yt, nyt, nmy, nny, mly, tsy, ndy, smy, 
	zt, nzt, zastart, zaend, nmz, nnz, mlz, tsz, ndz, smz, aminin, amaxin,
	 icol, iline)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *nlevels;
real *astart, *aend;
integer *idir, *iflag, *iaxis;
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
integer *icol, *iline;
{
    /* Initialized data */

    static real tpi = (float)3.141592654;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    real r__1, r__2;

    /* Builtin functions */
    double atan2();

    /* Local variables */
    static integer nadd;
    static real amax;
    extern /* Subroutine */ int axis_();
    static real xlen, ylen, zlen;
    extern /* Subroutine */ int plot_(), axis2_(), scale_(), frame_(), cterm_(
	    );
    static integer n1, n2;
    static real x1, y1, y2, x2, da, ae;
    extern /* Subroutine */ int cncelplt3d_();
    static integer ic[4], jf;
    static real as;
    static integer il;
    extern /* Subroutine */ int vxpt3d_();
    static integer nl;
    static real dx, dy, dz;
    extern /* Subroutine */ int trcelplt3d_();
    static integer iz, ix, iy;
    static real xp, yp, tv;
    extern /* Subroutine */ int newpen_(), plotnd_();
    static integer ix2, iy2;
    static real xp1, yp1, daa;
    static integer iaf;
    static real ang, pas[2];
    static integer ilu, iyy, ixx;
    static real xxx;

/* 	CREATED BY D. LONG     JULY, 1985	AT JPL */
/* 	MODIFIED BY D. LONG   FEB, 1986 AT JPL + ADDED LINE TYPE ARRAY */

/* 	ROUTINE TO PLOT DATA IN 3-D CONTOUR FORM SIMILAR TO VAX3DX */
/* 	DOES NOT DO HIDDEN LINE REMOVAL */

/* 	COORDINATE SYSTEM IS:		Y  Z */
/* 				NAMES:	|/ */
/* 					 \X */

/* 	A	(R) ARRAY A(INX,INZ) CONTAINING VERTICAL HEIGHT DATA */
/* 	INX,INZ (I) DIMENSION OF A ARRAY */
/* 	NX,NZ	(I) INDICATING SIZE OF A ARRAY TO PLOT */
/* 	ALPHA	(R) ANGLE (IN DEGREES) OF X AXIS (NX) FROM HORIZONTAL */
/* 	BETA	(R) ANGLE (IN DEGREES) OF Z AXIS (NZ) FROM HORIZONTAL */
/* 	XH,YH,ZH(R) LENGTH OF EACH AXIS (INCHES) */
/* 	NLEVELS REAL NUMBER OF UNIFORMLY SPACED CONTOUR LEVELS BETWEEN */
/* 			 VALUES ASTART AND AEND.  Jth CONTOUR IS */
/* 			 (J-1)*(AEND-ASTART)/(NL-1)+ASTART */
/* 			IF NLEVELS < 0 THEN MIN(V) AND MAX(V) ARE USED */
/* 			 AS ASTART AND AEND VALUES */
/* 			IF NLEVELS = 0 THEN ASTART IS USED CONTOUR LIST */
/* 			 WITH INT(AEND) THE NUMBER OF CONTOURS */
/* 	ASTART  REAL STARTING VALUE OF CONTOUR PLOT LEVELS (NLEVELS<>0) */
/* 		     CONTOUR LIST (NLEVELS=0) DIMENSIONED ASTART(INT(AEND)) */
/* 	AEND    REAL ENDING VALUE OF CONTOUR PLOT LEVELS (NLEVELS<>0) */
/* 		     NUMBER OF CONTOURS IN ASTART (NLEVELS=0) */
/* 	IDIR	(I) CONTOUR EDGING FLAG */
/* 			< 0 EXTEND CONTOUR SURFACE TO EDGES LESS THAN CONTOUR LEVEL */
/* 			= 0 DO NOT EXTEND CONTOUR EDGES */
/* 			> 0 EXTEND CONTOUR SURFACE TO EDGES GREATER THAN CONTOUR */
/* 	IFLAG	(I) PLOT FLAG */
/* 		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT)	= 1 DO NOT USE PEN COLOR OR LINE TYPE ARRAY */
/* 			= 2 USE PEN COLOR CONTROL ARRAY BUT NOT LINE TYPE */
/* 			= 3 DO NOT USE PEN COLOR BUT DO USE LINE TYPE */
/* 			= 4 USE PEN COLOR AND LINE TYPE ARRAYS */
/* 	(HUNDREDS'S)	= 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		   	<>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	(I) AXIS OPTION FLAG */
/* 			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED 
*/
/*			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSE
D*/
/* 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 0	DEFAULT AXIS PARAMETERS */
/* 			= 1	SPECIALIZED AXIS2 PARAMETERS */
/* 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	(I)  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,ZASTART	(R) AXIS START VALUES */
/* 	XAEND,ZAEND	(R) AXIS END VALUES */
/* ACCESSED ONLY IF TEN'S DIGIT OF IFLAG=1 */
/* 	NMX,NMY,NMZ	(I) NUMBER OF MINOR TICKS BETWEEN MAJOR TICKS */
/* 	NNX,NNY,NNZ	(I) HIGHLIGHT LENGTH OF NNX-TH MINOR TICK ON AXIS */
/* 	MLX,MLY,MLZ	(I) NUMBER OF MAJOR TICK MARKS ON AXIS */
/* 	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	NDX,NDY,NDZ	(R) NUMBER OF DIGITS TO RIGHT OF DECIMAL POINT */
/* 	SMX,SMY,SMZ	(R) MAJOR TICK LENGTH */
/* 	AMININ,AMAXIN 	(R) YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) */

/* 	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF MOD(IFLAG,10)>1) */
/* 				ICOL(1) AXIS LINE COLOR */
/* 				ICOL(2) AXIS NUMBERS COLOR */
/* 				ICOL(3) AXIS TITLE COLOR */
/* 				ICOL(4) AXIS EXPONENT COLOR */
/* 				ICOL(5) CONTOUR LINE 1 */
/* 				ICOL(6) CONTOUR LINE 2 */
/* 				ICOL(7)   . . .      3 */
/* 				 ...      ...       ... */
/* 	ILINE		(I) LINE TYPE ARRAY FOR CONTOURS */
/* 				(ONLY ACCESSED IF MOD(IABS(IFLAG),10)>2) */

    /* Parameter adjustments */
    --iline;
    --icol;
    --astart;
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
	printf("\n *** CNT3DX INPUT ANGLE ERROR ***\n");
	return 0;
    }
    if (amax == locate_1.amin) {
	printf("\n *** CNT3DX SCALE ERROR ***\n");
	amax = locate_1.amin + (float)1.;
    }

    xlen = dabs(*xh);
    locate_1.xscale = xlen / (real) (*nx - 1);
    zlen = dabs(*zh);
    locate_1.zscale = zlen / (real) (*nz - 1);
    ylen = dabs(*yh);
    if (abs(*iaxis) % 10 == 2) {
	pas[0] = amax;
	pas[1] = locate_1.amin;
	scale_(pas, &ylen, &c__2, &c__1, &c__1, &locate_1.amin, &daa);
	amax = ylen * daa + locate_1.amin;
    }
    locate_1.yscale = (float)1.;
    if (amax - locate_1.amin != (float)0.) {
	locate_1.yscale = ylen / (amax - locate_1.amin);
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = -jf / 10;
	frame_(&c__3, &ilu, &c_b12, &c_b13, &c_b14);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL PLOT MODE */
    }

    iaf = abs(*iaxis) / 10;
    jf %= 10;
    if (*iaxis != 0) {
/* PLOT AXIS LABELS */
	nadd = 0;
	if (jf == 2 || jf == 4) {
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

/* 	BEGIN CONTOUR PLOTTING */

    xxx = (real) (*nx);
    ae = *aend;
    as = astart[1];
    nl = abs(*nlevels);
    if (nl == 0) {
	nl = (integer) (dabs(*aend) + (float).5);
    }
    if (*nlevels <= 0) {
	ae = amax;
	as = locate_1.amin;
    }
    da = (float)0.;
    if (nl > 1) {
	da = (ae - as) / (nl - 1);
    }

/* 	BEGIN CONTOURING */

    i__2 = nl;
    for (il = 1; il <= i__2; ++il) {
/* FOR EACH LEVEL */
	if (jf == 2 || jf == 4) {
	    r__1 = (real) icol[il + 6];
	    plot_(&r__1, &c_b22, &c__0);
	}
/* COLOR */
	if (jf > 2) {
	    newpen_(&iline[il]);
	}
/* LINE TYPE */
	tv = as + (real) (il - 1) * da;
/* Z VALUE FOR CONTOUR LEVEL */
	if (*nlevels == 0) {
	    tv = astart[il];
	}
	i__1 = abs(*nz) - 1;
	for (iy = 1; iy <= i__1; ++iy) {
/* FOR EACH Z CELL */
	    y1 = (real) (iy - 1);
	    y2 = (real) iy;
	    iyy = iy;
	    if (iy > 1) {
		--iyy;
	    }
	    iy2 = iy + 1;
	    if (iy2 < *nz) {
		++iy2;
	    }
	    i__3 = abs(*nx) - 1;
	    for (ix = 1; ix <= i__3; ++ix) {
/* FOR EACH X CELL */
		x1 = (real) (ix - 1);
		x2 = (real) ix;
		ixx = ix;
		if (ix > 1) {
		    --ixx;
		}
		ix2 = ix + 1;
		if (ix2 < *nx) {
		    ++ix2;
		}
		cncelplt3d_(&tv, &xxx, &x1, &y1, &x2, &y2, &tv, &a[ix + iy * 
			a_dim1], &a[ix + (iy + 1) * a_dim1], &a[ix + 1 + (iy 
			+ 1) * a_dim1], &a[ix + 1 + iy * a_dim1], &a[ixx + 
			iyy * a_dim1], &a[ixx + iy2 * a_dim1], &a[ix2 + iy2 * 
			a_dim1], &a[ix2 + iyy * a_dim1]);
/* L50: */
	    }

	    if (*idir == 0) {
		goto L60;
	    }

/* 	ADD Y CELL EDGES */

	    ix = 1;
	    x1 = (real) (ix - 1);
	    trcelplt3d_(idir, &x1, &y1, &x1, &y2, &a[ix + iy * a_dim1], &a[ix 
		    + (iy + 1) * a_dim1], &tv, &xxx);
	    ix = abs(*nx);
	    x1 = (real) (ix - 1);
	    trcelplt3d_(idir, &x1, &y1, &x1, &y2, &a[ix + iy * a_dim1], &a[ix 
		    + (iy + 1) * a_dim1], &tv, &xxx);
L60:
	    ;
	}

/* 	NOW ADD X EDGES, EACH SIDE SEPARATELY TO MINIMIZE PEN MOVEMENTS */


	if (*idir == 0) {
	    goto L100;
	}

	iy = 1;
	y1 = (real) (iy - 1);
	i__1 = abs(*nx) - 1;
	for (ix = 1; ix <= i__1; ++ix) {
/* FOR EACH X EDGE */
	    x1 = (real) (ix - 1);
	    x2 = (real) ix;
	    trcelplt3d_(idir, &x1, &y1, &x2, &y1, &a[ix + iy * a_dim1], &a[ix 
		    + 1 + iy * a_dim1], &tv, &xxx);
/* L70: */
	}

	iy = abs(*nz);
	y1 = (real) (iy - 1);
	i__1 = abs(*nx) - 1;
	for (ix = 1; ix <= i__1; ++ix) {
/* FOR EACH X EDGE */
	    x1 = (real) (ix - 1);
	    x2 = (real) ix;
	    trcelplt3d_(idir, &x1, &y1, &x2, &y1, &a[ix + iy * a_dim1], &a[ix 
		    + 1 + iy * a_dim1], &tv, &xxx);
/* L80: */
	}
L100:
	;
    }

/* 	FINISH PLOTTING ROUTINE */

    if (jf > 2) {
	newpen_(&c__1);
    }
/* RESTORE LINE TYPE */
    plot_(&c_b22, &c_b22, &c__3);
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
} /* cnt3dx_ */



/* Subroutine */ int rvxpt3d_(x, y, aval, xr, zr, xm)
real *x, *y, *aval, *xr, *zr, *xm;
{
    /* Builtin functions */
    double cos(), sin();


/* 	CREATED BY DAVID LONG    JULY, 1985	AT JPL */
/* 	SUBPROGRAM OF CNT3DX */

/* 	ROUTINE TO DETERMINE X,Y VALUE OF A POINT ON 3-D SURFACE */
/* 	FOR CNT3DCX */

    *x = locate_1.xscale * *xr * cos(locate_1.alph) + *zr * cos(locate_1.bet) 
	    * locate_1.zscale;
    *y = locate_1.yscale * (*aval - locate_1.amin) + (*xm - *xr) * sin(
	    locate_1.alph) * locate_1.xscale + *zr * sin(locate_1.bet) * 
	    locate_1.zscale;
    return 0;
} /* rvxpt3d_ */



/* Subroutine */ int cncelplt3d_(zp, xmax, x1, y1, x2, y2, tv, v1, v2, v3, v4,
	 v5, v6, v7, v8)
real *zp, *xmax, *x1, *y1, *x2, *y2, *tv, *v1, *v2, *v3, *v4, *v5, *v6, *v7, *
	v8;
{
    extern doublereal poly1int_();
    extern /* Subroutine */ int plot_();
    static real c, c1, c2;
    static integer if_;
    static real px, py, yi1, xi2, yi3, xi4;
    extern integer segcode_();
    extern /* Subroutine */ int rvxpt3d_();


/* 	CREATED BY D. LONG     JULY, 1985	AT JPL */
/* 	SUBPROGRAM OF CNT3DX */
/* 	COMPUTES AND PLOTS CELL SQUARE-SECTIONED CONTOURS IN 3D */

/* 	INTERSECTION CODE MAP: */
/* 			  (2) */
/* 			2.   3. */
/* 		    (1)	       (4) */
/* 			1.   4. */
/* 			  (8) */


    if_ = segcode_(y1, y2, v1, v2, tv, &yi1);
    if_ += segcode_(x1, x2, v2, v3, tv, &xi2) << 1;
    if_ += segcode_(y2, y1, v3, v4, tv, &yi3) << 2;
    if_ += segcode_(x2, x1, v4, v1, tv, &xi4) << 3;

    switch ((int)(if_ + 1)) {
	case 1:  goto L50;
	case 2:  goto L50;
	case 3:  goto L50;
	case 4:  goto L103;
	case 5:  goto L50;
	case 6:  goto L105;
	case 7:  goto L106;
	case 8:  goto L107;
	case 9:  goto L50;
	case 10:  goto L109;
	case 11:  goto L110;
	case 12:  goto L111;
	case 13:  goto L112;
	case 14:  goto L113;
	case 15:  goto L114;
	case 16:  goto L115;
    }
    goto L50;
L103:
    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, &xi2, y2, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L105:
    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, x2, &yi3, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L106:
    rvxpt3d_(&px, &py, zp, &xi2, y2, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, x2, &yi3, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L107:
    if (*v3 == *tv) {
	goto L103;
    }
    goto L106;
L109:
    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, &xi4, y1, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L110:
    rvxpt3d_(&px, &py, zp, &xi4, y1, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, &xi2, y2, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L111:
    if (*v1 == *tv) {
	goto L103;
    }
    goto L109;
L112:
    rvxpt3d_(&px, &py, zp, &xi4, y1, xmax);
    plot_(&px, &py, &c__3);
    rvxpt3d_(&px, &py, zp, x2, &yi3, xmax);
    plot_(&px, &py, &c__2);
    goto L50;
L113:
    if (*v1 == *tv) {
	goto L112;
    }
    goto L109;
L114:
    if (*v3 == *tv) {
	goto L112;
    }
    goto L106;
L115:
    if (*v1 == *tv) {
	goto L50;
    }
    c1 = poly1int_(v5, v1, v3, v7, &c_b12);
    c2 = poly1int_(v6, v2, v4, v8, &c_b12);
    c = (c1 + c2) / (float)2.;
    if (c > *tv) {
	if (*v1 > *tv) {
	    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
	    plot_(&px, &py, &c__3);
	    rvxpt3d_(&px, &py, zp, &xi2, y2, xmax);
	    plot_(&px, &py, &c__2);
	    goto L112;
	} else {
	    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
	    plot_(&px, &py, &c__3);
	    rvxpt3d_(&px, &py, zp, &xi4, y1, xmax);
	    plot_(&px, &py, &c__2);
	    goto L106;
	}
    } else {
	if (*v1 < *tv) {
	    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
	    plot_(&px, &py, &c__3);
	    rvxpt3d_(&px, &py, zp, &xi2, y2, xmax);
	    plot_(&px, &py, &c__2);
	    goto L112;
	} else {
	    rvxpt3d_(&px, &py, zp, x1, &yi1, xmax);
	    plot_(&px, &py, &c__3);
	    rvxpt3d_(&px, &py, zp, &xi4, y1, xmax);
	    plot_(&px, &py, &c__2);
	    goto L106;
	}
    }
L50:
    return 0;
} /* cncelplt3d_ */



/* Subroutine */ int trcelplt3d_(idir, x1, y1, x2, y2, v1, v2, tv, xmax)
integer *idir;
real *x1, *y1, *x2, *y2, *v1, *v2, *tv, *xmax;
{
    extern integer isegcode_();
    extern /* Subroutine */ int plot_();
    static integer if_;
    static real xi, yi, px, py;
    static logical if1, if2;
    extern /* Subroutine */ int rvxpt3d_();


/* 	CREATED BY D. LONG     JULY, 1985	AT JPL */
/* 	SUBPROGRAM OF CNT3DX */
/* 	COMPUTES AND PLOTS WHERE A LINE SEGMENT CROSSES A THRESHOLD */
/* 	VALUE. */

/* 	IDIR		(I)	DIRECTION:  < 0 LESS, > 0 GREATER */
/* 	X1,Y1,X2,Y2	(R)	START, END POINTS OF LINE SEGMENT */
/* 	V1,V2		(R)	VALUE OF FUNCTION AT START, END OF LINE */
/* 	TV		(R)	THRESHOLD VALUE */
/* 	XMAX		(R)	MAXIMUM X VALUE (USED FOR SCALING) */


    if1 = FALSE_;
    if2 = FALSE_;
    if (*idir < 0) {
	if (*v1 < *tv) {
	    if1 = TRUE_;
	}
	if (*v2 < *tv) {
	    if2 = TRUE_;
	}
    } else {
	if (*v1 > *tv) {
	    if1 = TRUE_;
	}
	if (*v2 > *tv) {
	    if2 = TRUE_;
	}
    }
    if (if1 && if2) {
	rvxpt3d_(&px, &py, tv, x1, y1, xmax);
	plot_(&px, &py, &c__3);
	rvxpt3d_(&px, &py, tv, x2, y2, xmax);
	plot_(&px, &py, &c__2);
	return 0;
    }
    if (if1 || if2) {
	if_ = isegcode_(x1, y1, x2, y2, v1, v2, tv, &xi, &yi);
	if (if_ != 0) {
	    if (if1) {
		rvxpt3d_(&px, &py, tv, x1, y1, xmax);
		plot_(&px, &py, &c__3);
		rvxpt3d_(&px, &py, tv, &xi, &yi, xmax);
		plot_(&px, &py, &c__2);
	    } else {
		rvxpt3d_(&px, &py, tv, x2, y2, xmax);
		plot_(&px, &py, &c__3);
		rvxpt3d_(&px, &py, tv, &xi, &yi, xmax);
		plot_(&px, &py, &c__2);
	    }
	}
    }
    return 0;
} /* trcelplt3d_ */



integer isegcode_(x1, y1, x2, y2, v1, v2, tv, xi, yi)
real *x1, *y1, *x2, *y2, *v1, *v2, *tv, *xi, *yi;
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    static real dv, xd;


/* 	CREATED BY D. LONG  JULY, 1985 */
/* 	SUBPROGRAM OF CNT3DX */

/* 	ROUTINE TO COMPUTE WHERE A LINE IN 2-SPACE CROSSES */
/* 	A THRESHOLD VALUE */

/* 	X1,Y1,X2,Y2	(R)	START, END POINTS OF LINE */
/* 	V1,V2		(R)	VALUE OF FUNCTION AT START, END POINTS OF LINE */
/* 	TV		(R)	THRESHOLD VALUE */
/* 	XI,YI		(R)	THRESHOLD POINT (RETURNED) */

/* 	ISEGCODE RETURNS: */
/* 				0 = NO INTERSECTION */
/* 				1 = INTERSECTION */

    ret_val = 0;
    if (*v1 <= *tv && *v2 >= *tv || *v1 >= *tv && *v2 <= *tv) {
	dv = *v2 - *v1;
	xd = (*x2 - *x1) / dv;
	if (xd == (float)0.) {
	    xd = (*y2 - *y1) / dv;
	    if (xd == (float)0.) {
		return ret_val;
	    }
	    *yi = (*tv - *v1) * xd + *y1;
	    *xi = *x1;
	} else {
	    *xi = (*tv - *v1) * xd + *x1;
	    *yi = (*y2 - *y1) * (*xi - *x1) / (*x2 - *x1) + *y1;
	}
	ret_val = 1;
    }
    return ret_val;
} /* isegcode_ */

