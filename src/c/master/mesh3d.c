
/* *** LAST REVISED ON 21-JAN-1994 15:14:15.19 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]MESH3D.C */

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


/* Subroutine */ int mesh3d_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
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
    extern /* Subroutine */ int mesh3dx_();
    static real amn;
    static integer iax;
    static real amx;
    static integer ndx, ndy, ndz, mlx, nmx, nnx, nmy, nny, mly;
    static real smx, smy;
    static integer nmz, nnz;
    static real tsx, tsy;
    static integer mlz;
    static real tsz, smz;


/* 	CREATED BY D. LONG  JAN 1986	AT JPL */

/* 	SIMPLIFIES CALLING MESH3DX ROUTINE AXISES */

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
	mesh3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &nmx, &nnx, &mlx, &tsx, 
		&ndx, &smx, yt, nyt, &nmy, &nny, &mly, &tsy, &ndy, &smy, zt, 
		nzt, zastart, zaend, &nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn,
		 &amx, &icol[1]);
    } else {
	mesh3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &nmx, &nnx, &mlx, &tsx, 
		&ndx, &smx, yt, nyt, &nmy, &nny, &mly, &tsy, &ndy, &smy, zt, 
		nzt, zastart, zaend, &nmz, &nnz, &mlz, &tsz, &ndz, &smz, &amn,
		 &amx, &ic);
    }
    return 0;
} /* mesh3d_ */



/* Subroutine */ int mesh3dx_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
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
    static real amax;
    static integer ipen;
    extern /* Subroutine */ int axis_();
    static real xlen, ylen, zlen;
    extern /* Subroutine */ int plot_(), axis2_();
    static integer i;
    extern /* Subroutine */ int scale_(), frame_();
    extern /* Subroutine */ int cterm_();
    static integer n1, n2, ic[4], jf;
    static real as[2];
    extern /* Subroutine */ int vxpt3d_();
    static integer ip;
    static real dx, dy, dz;
    static integer iz, ix;
    static real xp, yp;
    extern /* Subroutine */ int plotnd_();
    static real xp1, yp1, xp2, yp2, daa;
    static integer iaf, jff;
    static real ang;
    static integer ilu;

/* 	CREATED BY D. LONG     JAN 1986 */

/* 	ROUTINE TO PLOT DATA IN 3-D OVERLAY FORM */
/* 	COORDINATE SYSTEM IS:		Z Y		Y  Z */
/* 			DOCUMENTED:	|/	NAMES:	|/ */
/* 					 \ X		 \X */

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
/* 			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED 
*/
/*			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSE
D*/
/* 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 0	DEFAULT AXIS PARAMETERS */
/* 			= 1	SPECIALIZED AXIS2 PARAMETERS */
/* 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,ZASTART	REAL AXIS START VALUES */
/* 	XAEND,ZAEND	REAL AXIS END VALUES */
/* ONLY ACCESSED IF TEN'S DIGIT OF IFLAG=1 */
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
/* 				ICOL(1) AXIS LINE COLOR */
/* 				ICOL(2) AXIS NUMBERS COLOR */
/* 				ICOL(3) AXIS TITLE COLOR */
/* 				ICOL(4) AXIS TITLE COLOR */
/* 				ICOL(5) PLOT COLOR */

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
    	printf("\n *** MESH3DX INPUT ANGLE ERROR ***\n");
	return 0;
    }
    if (amax == locate_1.amin) {
	printf("\n *** MESH3DX INITIALIZATION ERROR ***\n");
	amax = locate_1.amin + (float)1.;
    }

    xlen = dabs(*xh);
    locate_1.xscale = xlen / (real) (*nx - 1);
    zlen = dabs(*zh);
    locate_1.zscale = zlen / (real) (*nz - 1);
    ylen = dabs(*yh);
    if (abs(*iaxis) % 10 == 2) {
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
	    ic[0] = icol[1];
	    ic[1] = icol[2];
	    ic[2] = icol[3];
	    ic[3] = icol[4];
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

/* COLOR */
    ipen = 3;
    i__2 = *nx;
    for (i = 1; i <= i__2; ++i) {
	vxpt3d_(&xp1, &yp1, &a[i + a_dim1], &i, &c__1, nx);
	plot_(&xp1, &yp1, &ipen);
/* PLOT SIDE LINE */
	ipen = 2;
/* L14: */
    }
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
	vxpt3d_(&xp1, &yp1, &a[i + a_dim1], &i, &c__1, nx);
	plot_(&xp1, &yp1, &c__3);
	vxpt3d_(&xp, &yp, &locate_1.amin, &i, &c__1, nx);
	plot_(&xp, &yp, &c__2);
	i__1 = i + 1;
	vxpt3d_(&xp, &yp, &locate_1.amin, &i__1, &c__1, nx);
	plot_(&xp, &yp, &c__2);
/* L19: */
    }

/* 	PLOT SIDE PLATE */

L71:
    vxpt3d_(&xp1, &yp1, &a[*nx + a_dim1], nx, &c__1, nx);
    plot_(&xp1, &yp1, &c__3);
    i__2 = *nz;
    for (i = 1; i <= i__2; ++i) {
/* PLOT RIGHT SIDE CURVE */
	vxpt3d_(&xp, &yp, &a[*nx + i * a_dim1], nx, &i, nx);
	plot_(&xp, &yp, &c__2);
/* L23: */
    }
    vxpt3d_(&xp, &yp, &locate_1.amin, nx, &c__1, nx);
    plot_(&xp, &yp, &c__3);
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

/* 	PLOT MESH */

L5:
    i__2 = *nz;
    for (iz = 2; iz <= i__2; ++iz) {
	ip = 3;
	i__1 = *nx;
	for (ix = 1; ix <= i__1; ++ix) {
	    vxpt3d_(&xp1, &yp1, &a[ix + iz * a_dim1], &ix, &iz, nx);
	    plot_(&xp1, &yp1, &ip);
	    ip = 2;
/* L500: */
	}
    }
    i__1 = *nx - 1;
    for (ix = 1; ix <= i__1; ++ix) {
	ip = 3;
	i__2 = *nz;
	for (iz = 1; iz <= i__2; ++iz) {
	    vxpt3d_(&xp1, &yp1, &a[ix + iz * a_dim1], &ix, &iz, nx);
	    plot_(&xp1, &yp1, &ip);
	    ip = 2;
/* L600: */
	}
    }

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
} /* mesh3dx_ */

