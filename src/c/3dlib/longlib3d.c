
/* *** LAST REVISED ON  7-FEB-1994 07:20:28.05 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C]LONGLIB3D.C */

#include "my.h"

/* Common Block Declarations */

struct {
    integer last[4];
    real v0[4], vorg[4], rot[16]	/* was [4][4] */, ds, view[16]	/* 
	    was [4][4] */, temp1[16]	/* was [4][4] */, sf;
    integer i3d;
} cplot3d_;

#define cplot3d_1 cplot3d_

struct {
    real xs2, ys2, xs1, ys1;
} last3d_;

#define last3d_1 last3d_

/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__5 = 5;
static integer c__8 = 8;
static real c_b38 = (float)1.;
static real c_b65 = (float)1e3;
static real c_b104 = (float)0.;
static doublereal c_b171 = 10.;

/****************************************************************************/

/* 	LONGLIB3D LIBRARY ROUTINES FOR 3-D PLOTTING WITHOUT HIDDEN */
/* 	LINE REMOVAL. */

/* 	MACHINE DEPDENDENT NOTES: */
/* 		1. IOR AND IAND DUE BIT-WISE OR AND AND FUNCTIONS. */

/****************************************************************************/


/* Subroutine */ int init3d_(x, y, z, xa, ya, za, theta, dds, ssf, ii3d)
real *x, *y, *z, *xa, *ya, *za, *theta, *dds, *ssf;
integer *ii3d;
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt();

    /* Local variables */
    static real d;
    static integer i, j;
    extern /* Subroutine */ int rotem_();
    static real vv;
    extern /* Subroutine */ int matmul4_();

/* 	CREATED: DGL 1-AUG-1984 */

/* 	INITIALIZE 3D PLOTTING ROUTINE */

/* 	X,Y,Z	 (R):	VIEWING POINT */
/* 	XA,YA,ZA (R):	ORIGIN POINT (LOOKING AT FROM VIEWING POINT) */
/* 	THETA	 (R):	ROTATION ABOUT AXIS DEFINED BY (X,Y,Z), (XA,YA,ZA) (DEG) 
*/
/* 	DDS	 (R):	PERSPECTIVE SCALE */
/* 	SSF	 (R):	RELATIVE SCALE FACTOR */
/* 	II3D	 (I):	PLOTTING ON FLAG (-1 = OFF) */


    cplot3d_1.i3d = cplot3d_1.i3d;
    cplot3d_1.sf = (float)1.;
    if (*ssf > (float)0.) {
	cplot3d_1.sf = *ssf;
    }
    cplot3d_1.ds = *dds;
    if (*dds < (float)0.) {
	cplot3d_1.ds = (float)2.;
    }
    for (i = 1; i <= 4; ++i) {
	for (j = 1; j <= 4; ++j) {
	    cplot3d_1.rot[i + (j << 2) - 5] = (float)0.;
	    cplot3d_1.temp1[i + (j << 2) - 5] = (float)0.;
/* L10: */
	    cplot3d_1.view[i + (j << 2) - 5] = (float)0.;
	}
	cplot3d_1.rot[i + (i << 2) - 5] = (float)1.;
	cplot3d_1.temp1[i + (i << 2) - 5] = (float)1.;
	cplot3d_1.view[i + (i << 2) - 5] = (float)1.;
	cplot3d_1.vorg[i - 1] = (float)0.;
/* L20: */
    }
    cplot3d_1.view[3] = -(doublereal)(*x); /* SHIFT ORIGIN TO VIEW POINT */
    cplot3d_1.view[7] = -(doublereal)(*y);
    cplot3d_1.view[11] = -(doublereal)(*z);

    r__1 = *x - *xa;
    r__2 = *y - *ya;
    r__3 = *z - *za;
    d = sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
    r__1 = *y - *ya;
    r__2 = *x - *xa;
    vv = sqrt(r__1 * r__1 + r__2 * r__2);
    cplot3d_1.temp1[5] = (float)0.;
    cplot3d_1.temp1[10] = (float)0.;
    cplot3d_1.temp1[6] = (float)1.;
    cplot3d_1.temp1[9] = (float)-1.;
    cplot3d_1.temp1[0] = (float)-1.;
    matmul4_(cplot3d_1.view, cplot3d_1.view, cplot3d_1.temp1);
/* REVERSE Z COORIDINATE */
    if (vv != (float)0.) {
	cplot3d_1.temp1[0] = (*y - *ya) / vv;
	cplot3d_1.temp1[5] = (float)1.;
	cplot3d_1.temp1[10] = cplot3d_1.temp1[0];
	cplot3d_1.temp1[9] = (float)0.;
	cplot3d_1.temp1[6] = (float)0.;
	cplot3d_1.temp1[2] = -(doublereal)(*x - *xa) / vv;
	cplot3d_1.temp1[8] = -(doublereal)cplot3d_1.temp1[2];
	matmul4_(cplot3d_1.view, cplot3d_1.view, cplot3d_1.temp1);
/* ROTATE ABOUT Y AXIS */
    }
    if (d != (float)0.) {
	cplot3d_1.temp1[2] = (float)0.;
	cplot3d_1.temp1[8] = (float)0.;
	cplot3d_1.temp1[0] = (float)1.;
	cplot3d_1.temp1[5] = vv / d;
	cplot3d_1.temp1[9] = -(doublereal)(*z - *za) / d;
	cplot3d_1.temp1[6] = -(doublereal)cplot3d_1.temp1[9];
	cplot3d_1.temp1[10] = cplot3d_1.temp1[5];
	matmul4_(cplot3d_1.view, cplot3d_1.view, cplot3d_1.temp1);
/* ROTATE ABOUT X AXIS */
    }
    if (*theta != (float)0.) {
	rotem_(&c__3, theta, cplot3d_1.temp1);
	matmul4_(cplot3d_1.view, cplot3d_1.view, cplot3d_1.temp1);
    }
    for (i = 1; i <= 4; ++i) {
	for (j = 1; j <= 4; ++j) {
	    cplot3d_1.temp1[i + (j << 2) - 5] = (float)0.;
/* L40: */
	}
	cplot3d_1.temp1[i + (i << 2) - 5] = (float)1.;
/* L50: */
    }
    if (cplot3d_1.ds > (float)0.) {
	cplot3d_1.temp1[0] = cplot3d_1.ds;
	cplot3d_1.temp1[5] = cplot3d_1.ds;
	matmul4_(cplot3d_1.view, cplot3d_1.view, cplot3d_1.temp1);
/* xN  CLIPPING WINDOW */
    }
    return 0;
} /* init3d_ */


integer ipclp3_(v1, v2)
real *v1, *v2;
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    static integer b;
    static real t, x, y, z;
    static integer b1, b2;
    extern integer clip3d_();
    static integer ipc;

/* 	CLIPS A 3D LINE FROM V1 TO V2 TO A VIEWING PYRAMID */

/* 	RETURN CODE:	-1	INVISIBLE LINE */
/* 			 0	FULLY VISIBLE LINE */
/* 			 1	CLIPPED FIRST POINT OFF */
/* 			 2	CLIPPED SECOND POINT OFF */
/* 			 3	CLIPPED BOTH ENDS OFF */

    /* Parameter adjustments */
    --v2;
    --v1;

    /* Function Body */
    b1 = clip3d_(&v1[1], &v1[2], &v1[3]);
    b2 = clip3d_(&v2[1], &v2[2], &v2[3]);
    ipc = 0;
L100:
    if ((b1 || b2) != 0) {
	if ((b1 && b2) != 0) {/* INVISIBLE LINE */
	    ipc = -1;
	    goto L1000;
	}
	b = b1;
	if (b == 0) {
	    b = b2;
	}
	if ((b && c__1) != 0) {/* CLIP LEFT */
	    t = (v1[3] + v1[1]) / (v1[1] - v2[1] - (v2[3] - v1[3]));
	    z = t * (v2[3] - v1[3]) + v1[3];
	    x = -(doublereal)z;
	    y = t * (v2[2] - v1[2]) + v1[2];
	}
	if ((b && c__2) != 0) {/* CLIP RIGHT */
	    t = (v1[3] - v1[1]) / (v2[1] - v1[1] - (v2[3] - v1[3]));
	    z = t * (v2[3] - v1[3]) + v1[3];
	    x = z;
	    y = t * (v2[2] - v1[2]) + v1[2];
	}
	if ((b && c__4) != 0) {/* CLIP BOTTOM */
	    t = (v1[3] + v1[2]) / (v1[2] - v2[2] - (v2[3] - v1[3]));
	    z = t * (v2[3] - v1[3]) + v1[3];
	    x = t * (v2[1] - v1[1]) + v1[1];
	    y = -(doublereal)z;
	}
	if ((b && c__8) != 0) { /* CLIP TOP */
	    t = (v1[3] - v1[2]) / (v2[2] - v1[2] - (v2[3] - v1[3]));
	    z = t * (v2[3] - v1[3]) + v1[3];
	    x = t * (v2[1] - v1[1]) + v1[1];
	    y = z;
	}
	if (b == b1) {
	    ++ipc;
	    v1[1] = x;
	    v1[2] = y;
	    v1[3] = z;
	    b1 = clip3d_(&x, &y, &z);
	} else {
	    ipc += 2;
	    v2[1] = x;
	    v2[2] = y;
	    v2[3] = z;
	    b2 = clip3d_(&x, &y, &z);
	}
	goto L100;
    }
L1000:
    ret_val = ipc;
    return ret_val;
} /* ipclp3_ */



integer clip3d_(x, y, z)
real *x, *y, *z;
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    static integer c;

/* 	CREATED: DGL 1-AUG-1984 */

/* 	RETURNS A CODE INDICATING THE LOCATION OF THE POINT (X,Y,Z) */
/* 	IN VIEWING PYRAMID */

/* 		1001 | 1000 | 1010 */
/* 		------------------ */
/* 		0001 | 0000 | 0010 */
/* 		------------------ */
/* 		0101 | 0100 | 0100 */

    c = 0;
    if (*x < -(doublereal)(*z)) {
	c = 1;
    } else {
	if (*x > *z) {
	    c = 2;
	}
    }
    if (*y < -(doublereal)(*z)) {
	c = (c || c__4);
    } else {
	if (*y > *z) {
	    c = (c || c__8);
	}
    }
    ret_val = c;
    return ret_val;
} /* clip3d_ */



/* Subroutine */ int plot3d_(x, y, z, id)
real *x, *y, *z;
integer *id;
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    extern /* Subroutine */ int plot_(), vcpy_();
    static integer iflag;
    extern /* Subroutine */ int rotem_();
    static real v1[4], v2[4], v3[4];
    extern /* Subroutine */ int draw3d_();
    extern integer ipclp3_();
    extern /* Subroutine */ int matmul4_(), mtv4_();


/* 	CREATED: DGL 1-AUG-1984 */

/* 	PLOTS A 3D LINE WITH PERSPECTIVE */

/* 	X,Y,Z	(R):	POINT LOCATION */
/* 	ID	(I):	PLOT COMMAND */
/* 			 0 = CHANGE COLOR (X), AND ANGLE (Y) OF PLOT PACKAGE */
/* 			 1 = CHANGE RELATIVE ROTATION MATRIX */
/* 			-1 = CHANGE RELATIVE SCALE FACTOR BY X */
/* 			-2 = PLOT TO X,Y,Z PEN DOWN NEW ORG */
/* 			 2 = PLOT TO X,Y,Z PEN DOWN */
/* 			-3 = MOVE TO X,Y,Z PEN UP NEW ORG */
/* 			 3 = MOVE TO X,Y,Z PEN UP */
/* 			-9 = ERASE TO X,Y,Z PEN DOWN NEW ORG */
/* 			 9 = ERASE TO X,Y,Z PEN DOWN */


    v1[0] = *x;
    v1[1] = *y;
    v1[2] = *z;
    v1[3] = (float)1.;
    mtv4_(v1, cplot3d_1.rot, v1); /* ROTATE AROUND LOCAL ORIGIN */
    v2[0] = (v1[0] - cplot3d_1.vorg[0]) * cplot3d_1.sf; /* SHIFT ORIGIN TO WORLD COORINDATES */
    v2[1] = (v1[1] - cplot3d_1.vorg[1]) * cplot3d_1.sf;
    v2[2] = (v1[2] - cplot3d_1.vorg[2]) * cplot3d_1.sf;
    v2[3] = (float)1.;
    mtv4_(v1, cplot3d_1.view, v2); /* ROTATE AROUND WORLD ORIGIN */
/* xVN */
    if (cplot3d_1.ds == (float)0. || v1[2] == (float)0.) {
	vcpy_(cplot3d_1.last, v1);
    } else {
	cplot3d_1.last[0] = v1[0] / v1[2];
	cplot3d_1.last[1] = v1[1] / v1[2];
	cplot3d_1.last[2] = (float)1. / v1[2];
	cplot3d_1.last[3] = v1[3];
    }
    if (abs(*id) > 9) {
	return 0;
    }
    switch ((int)(abs(*id) + 1)) {
	case 1:  goto L5;
	case 2:  goto L10;
	case 3:  goto L20;
	case 4:  goto L30;
	case 5:  goto L40;
	case 6:  goto L40;
	case 7:  goto L40;
	case 8:  goto L40;
	case 9:  goto L40;
	case 10:  goto L20;
    }
L5:
/* ID = 0 */
    plot_(x, y, &c__0);
/* CHANGE COLOR */
    if (*z > (float)0.) {
	cplot3d_1.ds *= *z;
    }
    return 0;
L10:
/* ID = 1 */
    if (*id > 0) {
/* CHANGE ROTATION MATRIX */
	rotem_(&c__1, x, cplot3d_1.temp1);
	matmul4_(cplot3d_1.rot, cplot3d_1.rot, cplot3d_1.temp1);
	rotem_(&c__2, y, cplot3d_1.temp1);
	matmul4_(cplot3d_1.rot, cplot3d_1.rot, cplot3d_1.temp1);
	rotem_(&c__3, z, cplot3d_1.temp1);
	matmul4_(cplot3d_1.rot, cplot3d_1.rot, cplot3d_1.temp1);
    } else {
/* CHANGE SCALE FACTOR */
	cplot3d_1.sf = *x * cplot3d_1.sf;
	if (cplot3d_1.sf <= (float)0.) {
	    cplot3d_1.sf = (float)1.;
	}
    }
L20:
/* ID = 2,9 */
    if (*id < 0) {
	vcpy_(cplot3d_1.vorg, v2);
    }
    vcpy_(v2, cplot3d_1.v0);
    vcpy_(v3, v1);
    if (cplot3d_1.i3d != -1) {
	iflag = ipclp3_(v2, v3);
/* 3D PERSPECTIVE CLIPPING */
	if (iflag != -1) {
	    i__1 = abs(*id);
	    draw3d_(v2, v3, &i__1, &cplot3d_1.ds, &iflag);
	}
    }
    vcpy_(cplot3d_1.v0, v1);
    return 0;
L30:
/* ID = 3 */
    if (*id < 0) {
	vcpy_(cplot3d_1.vorg, v2);
    }
    vcpy_(cplot3d_1.v0, v1);
L40:
    return 0;
} /* plot3d_ */



/* Subroutine */ int draw3d_(v1, v2, id, ds, iflag)
real *v1, *v2;
integer *id;
real *ds;
integer *iflag;
{
    extern /* Subroutine */ int plot_();


/* 	CREATED: DGL 1-AUG-1984 */

/* 	PLOT A LINE FROM V1 TO V2 WITH PERSPECTIVE */

/* 	V1,V2	(R):	LINE DEFINED BETWEEN TWO SCREEN COORDINATE POINTS */
/* 	ID	(I):	PLOT CODE (2,9) */
/* 	DS	(R):	PERSPECTIVE SCALE FACTOR (DS=0 NO PERSPECTIVE) */
/* 	IFLAG	(I):	CLIP CODE */

    /* Parameter adjustments */
    --v2;
    --v1;

    /* Function Body */
    if (*ds != (float)0.) {
/* PERSPECTIVE */
	if (v1[3] == (float)0. || v2[3] == (float)0.) {
	    return 0;
/* LINE THROUGH Ze PLANE */
	} else {
	    last3d_1.xs1 = v1[1] / v1[3];
	    last3d_1.ys1 = v1[2] / v1[3];
	    plot_(&last3d_1.xs1, &last3d_1.ys1, &c__3);
	    last3d_1.xs2 = v2[1] / v2[3];
	    last3d_1.ys2 = v2[2] / v2[3];
	    plot_(&last3d_1.xs2, &last3d_1.ys2, id);
/* 			CALL PLOT(XS2,YS2,3) */
	}
    } else {
/* NO PERSPECTIVE */
	last3d_1.xs1 = v1[1];
	last3d_1.ys1 = v1[2];
	plot_(&last3d_1.xs1, &last3d_1.ys1, &c__3);
	last3d_1.xs2 = v2[1];
	last3d_1.ys2 = v2[2];
	plot_(&last3d_1.xs2, &last3d_1.ys2, id);
/* 		CALL PLOT(XS2,YS2,3) */
    }
    return 0;
} /* draw3d_ */



/* Subroutine */ int where3d_(x, y)
real *x, *y;
{

/* 	CREATED: DGL 1-AUG-1984 */

/* 	RETURNS THE X,Y SCREEN LOCATIONS OF THE LAST CALL TO */
/* 	DRAW3D (FROM PLOT3D) */

    *x = last3d_1.xs2;
    *y = last3d_1.ys2;
    return 0;
} /* where3d_ */



/* Subroutine */ int vcpy_(v1, v2)
real *v1, *v2;
{
    static integer i;


/* 	CREATED: DGL 1-AUG-1984 */

/* 	COPIES A FOUR ELEMENT VECTOR FROM V2 TO V1 */

    /* Parameter adjustments */
    --v2;
    --v1;

    /* Function Body */
    for (i = 1; i <= 4; ++i) {
	v1[i] = v2[i];
/* L10: */
    }
    return 0;
} /* vcpy_ */



/* Subroutine */ int mtv4_(v2, r, v1)
real *v2, *r, *v1;
{
    static integer i, k;
    static real v3[4];


/* 	CREATED: DGL 1-AUG-1984 */

/* 	MULTIPLIES VECTOR V1 TIMES MATRIX R AND STORES RESULT INTO V2 */
/* 	V2 CAN BE V1 (CAN BE DONE IN PLACE) V2 = V1*R */

    /* Parameter adjustments */
    --v1;
    r -= 5;
    --v2;

    /* Function Body */
    for (k = 1; k <= 4; ++k) {
	v3[k - 1] = (float)0.;
	for (i = 1; i <= 4; ++i) {
	    v3[k - 1] += v1[i] * r[i + (k << 2)];
/* L10: */
	}
/* L20: */
    }
    for (i = 1; i <= 4; ++i) {
	v2[i] = v3[i - 1];
/* L30: */
    }
    return 0;
} /* mtv4_ */



/* Subroutine */ int rotem_(irot, ang, r)
integer *irot;
real *ang, *r;
{
    /* Builtin functions */
    double r_sign(), cos(), sin();

    /* Local variables */
    static real c;
    static integer i, j;
    static real s, x;


/* 	CREATED: DGL 1-AUG-1984 */

/* 	CREATES 3 AXIS ROTATION MATRIX */

/* 	R	RESULT MATRIX R(4,4) */
/* 	IROT	AXIS OF ROTATION */
/* 		= 1  X AXIS */
/* 		= 2  Y AXIS */
/* 		= 3  Z AXIS */
/* 	ANG	ANGLE OF ROTATION IN DEGREES */

    /* Parameter adjustments */
    r -= 5;

    /* Function Body */
    x = *ang * (float)3.141592654 / (float)180.;
    if (*ang == (float)0.) {
	c = (float)1.;
	s = (float)0.;
    } else if (dabs(*ang) == (float)90.) {
	c = (float)0.;
	s = r_sign(&c_b38, ang) * (float)1.;
    } else {
	c = cos(x);
	s = sin(x);
    }
    for (i = 1; i <= 4; ++i) {
	for (j = 1; j <= 4; ++j) {
	    r[i + (j << 2)] = (float)0.;
/* L20: */
	}
/* L10: */
    }
    if (*irot != 1) {
	goto L200;
    }
    r[10] = c;
    r[11] = -(doublereal)s;
    r[14] = s;
    r[15] = c;
    r[5] = (float)1.;
    r[20] = (float)1.;
    return 0;
L200:
    if (*irot != 2) {
	goto L300;
    }
    r[5] = c;
    r[7] = s;
    r[13] = -(doublereal)s;
    r[15] = c;
    r[10] = (float)1.;
    r[20] = (float)1.;
    return 0;
L300:
    r[5] = c;
    r[6] = -(doublereal)s;
    r[9] = s;
    r[10] = c;
    r[15] = (float)1.;
    r[20] = (float)1.;
    return 0;
} /* rotem_ */



/* Subroutine */ int matmul4_(r, a, b)
real *r, *a, *b;
{
    static integer i, j, k;
    static real v[4];


/* 	CREATED: DGL 1-AUG-1984 */

/* 	THIS SUBROUTINE MULTIPLIES TWO 4X4 MATRICES A X B = R */
/* 	A CAN BE C (IN PLACE) */

/* 	R	RESULT MATRIX DIMENSIONED R(4,4) */
/* 	A	INPUT MATRIX DIMENSIONED A(4,4) */
/* 	B	INPUT MATRIX DIMENSIONED B(4,4) */

    /* Parameter adjustments */
    b -= 5;
    a -= 5;
    r -= 5;

    /* Function Body */
    for (j = 1; j <= 4; ++j) {
	for (k = 1; k <= 4; ++k) {
	    v[k - 1] = (float)0.;
	    for (i = 1; i <= 4; ++i) {
		v[k - 1] += a[j + (i << 2)] * b[i + (k << 2)];
/* L5: */
	    }
/* L10: */
	}
	for (k = 1; k <= 4; ++k) {
	    r[j + (k << 2)] = v[k - 1];
/* L15: */
	}
/* L20: */
    }
    return 0;
} /* matmul4_ */



/* Subroutine */ int sym3d_(xa, ya, za, pa, pb, pg, hi, asc, nc)
real *xa, *ya, *za, *pa, *pb, *pg, *hi;
char *asc;
integer *nc;
{
    /* Initialized data */

    static struct {
	shortint e_1[128];
	} equiv_15 = { 0, 8, 20, 26, 31, 36, 43, 50, 55, 62, 68, 82, 91, 98, 
		101, 104, 111, 118, 125, 125, 125, 125, 125, 125, 125, 125, 
		125, 125, 125, 125, 125, 125, 125, 126, 136, 141, 150, 161, 
		174, 186, 190, 195, 200, 207, 212, 215, 218, 221, 223, 234, 
		240, 249, 260, 266, 276, 287, 293, 311, 321, 326, 332, 336, 
		341, 345, 354, 366, 373, 385, 394, 402, 409, 414, 424, 430, 
		437, 443, 448, 452, 457, 463, 473, 480, 492, 501, 514, 519, 
		526, 530, 536, 544, 552, 559, 564, 567, 571, 577, 583, 586, 
		597, 607, 614, 625, 635, 641, 654, 660, 668, 675, 681, 687, 
		697, 704, 714, 724, 735, 740, 748, 754, 762, 766, 772, 776, 
		785, 790, 798, 803, 811, 816 };

    static struct {
	shortint e_1[416];
	} equiv_67 = { 10842, 2088, 11276, -9686, 10842, 8233, 2320, 5131, 
		11044, -9686, 10842, 3080, -9686, 2666, 7256, 18650, 26668, 
		-9716, 10842, 2584, 10780, 23258, 10776, 6684, -9718, 11336, 
		3112, 26842, 2092, 22796, -9701, 10330, 6764, -9718, 11354, 
		8547, 24872, 2065, 4945, 21260, -9693, 11336, 3176, 10826, 
		7256, 23258, 11304, 3080, -9702, 10826, 22746, -9700, 7256, 
		11368, 3144, 24794, 20516, 18708, -9685, 10842, 9057, 4945, 
		-14630, 577, 2314, 20993, 12849, -14830, 12641, 9075, 16838, 
		29489, 24579, 21540, -14832, 2888, 6932, 8217, 11305, 626, 
		18630, 26924, 12328, 10545, 836, 3083, -14844, 596, 2049, 
		8976, 12843, 6441, -14844, 10849, -14798, 8563, 785, 29126, 
		4899, -14847, 10826, 4196, 5216, 19142, 22570, -14820, 4361, 
		22726, -14820, 321, 13510, 18630, 12584, 11315, 780, 2049, 
		-14804, 833, 12866, -14807, 12648, 11315, 2084, 1024, 28870, 
		11316, 6938, 3092, 259, -14840, 13123, 4120, -14828, 328, 
		3075, 8988, 12320, -14796, 7000, 3092, 259, 8200, 13362, 
		28870, 11316, 273, 16838, 3075, 6932, 8217, 12584, 11315, 
		6948, 4185, 264, 710, 11284, 12595, 8232, 7193, 16838, 20737, 
		-14831, 2625, 25106, -14814, 6211, -14797, 5200, 8292, 16838, 
		12572, 17094, 20994, 11300, 12595, -14808, 323, 10248, 13105, 
		5164, 6674, -14804, 12832, 1060, 5200, 12486, 11315, 6948, 
		23320, 3092, 3, 27846, 12595, 2088, 769, -14836, 3075, 13100, 
		28976, -14847, 13360, 6235, 1088, 12486, 23092, -14824, 13164,
		 10289, 264, 5124, -14829, 22576, 29724, -14844, 833, 12866, 
		13169, 18630, 769, 13324, 12486, 6260, -14844, 16432, -14844, 
		6704, 1076, 12486, 3176, 1140, 18630, 769, 11276, 12595, 2088,
		 12486, 11315, 6948, -14824, 328, 3075, 13100, 10289, 21000, 
		-14844, 13104, 9260, 6171, 1114, 18630, 769, 5132, 6427, 
		10272, 13105, -14804, 13424, 626, 28870, 264, 3075, -14796, 
		624, -14796, 368, 794, -14796, 11272, 28724, 3112, -14844, 
		10352, 538, 11380, -14822, 13424, 2092, 1024, 29382, 48, 
		-15358, 12356, 710, 12338, 22724, 7210, 2666, 19142, 10776, 
		7256, 28870, -14821, 6216, 8737, 532, 2049, 1124, 12486, 8784,
		 7203, 780, 4098, 25798, 6177, 264, -14844, 1140, 8788, 6177, 
		264, 5122, 20678, 7188, 8483, 2072, 769, 17094, 13098, 7001, 
		16838, 3075, 25652, 12594, 6184, 4625, -14812, 24624, 7203, 
		-14844, 833, 6722, 27161, -14806, 577, 8971, 13171, 12486, 
		2156, 1114, 16838, 16899, 12594, 8390, 8536, 538, 9050, 1052, 
		8390, 8536, 7203, -14844, 6216, 8993, 3100, 259, -14840, 
		24624, 13106, 7212, 4627, -14816, 13380, 12900, 10289, 4376, 
		9234, 8390, 8784, -14812, 3075, 4371, 8472, -14812, 9057, 
		2674, -14845, 2144, 769, 25612, -14844, 608, -14812, 352, 786,
		 -14812, 24612, -14844, 833, 13324, 6256, 5137, 24774, 36, 
		-14844, 2370, 6161, 10529, -15054, 4674, 12898, 16838, 4618, 
		8731, 12586, 20677, 6937, -14812, 13360, 4, 28724, -14844, 0, 
		0, 0, 0 };


    /* System generated locals */
    real r__1, r__2, r__3;

    /* Local variables */
#define syn9 ((shortint *)&equiv_15 + 8)
#define stc41 ((shortint *)&equiv_67 + 40)
#define stc33 ((shortint *)&equiv_67 + 32)
#define stc25 ((shortint *)&equiv_67 + 24)
#define stc17 ((shortint *)&equiv_67 + 16)
#define stc81 ((shortint *)&equiv_67 + 80)
#define stc73 ((shortint *)&equiv_67 + 72)
#define stc65 ((shortint *)&equiv_67 + 64)
    static real temp[16]	/* was [4][4] */;
#define stc49 ((shortint *)&equiv_67 + 48)
#define stc57 ((shortint *)&equiv_67 + 56)
#define stc97 ((shortint *)&equiv_67 + 96)
#define stc89 ((shortint *)&equiv_67 + 88)
#define syn41 ((shortint *)&equiv_15 + 40)
#define syn33 ((shortint *)&equiv_15 + 32)
#define syn25 ((shortint *)&equiv_15 + 24)
#define syn17 ((shortint *)&equiv_15 + 16)
#define syn81 ((shortint *)&equiv_15 + 80)
#define syn73 ((shortint *)&equiv_15 + 72)
#define syn65 ((shortint *)&equiv_15 + 64)
#define syn57 ((shortint *)&equiv_15 + 56)
#define syn49 ((shortint *)&equiv_15 + 48)
#define syn97 ((shortint *)&equiv_15 + 96)
#define syn89 ((shortint *)&equiv_15 + 88)
#define stc201 ((shortint *)&equiv_67 + 200)
#define stc121 ((shortint *)&equiv_67 + 120)
#define stc113 ((shortint *)&equiv_67 + 112)
#define stc105 ((shortint *)&equiv_67 + 104)
#define stc241 ((shortint *)&equiv_67 + 240)
#define stc161 ((shortint *)&equiv_67 + 160)
#define stc153 ((shortint *)&equiv_67 + 152)
#define stc145 ((shortint *)&equiv_67 + 144)
#define stc137 ((shortint *)&equiv_67 + 136)
#define stc129 ((shortint *)&equiv_67 + 128)
#define stc193 ((shortint *)&equiv_67 + 192)
#define stc185 ((shortint *)&equiv_67 + 184)
#define stc177 ((shortint *)&equiv_67 + 176)
#define stc169 ((shortint *)&equiv_67 + 168)
#define stc209 ((shortint *)&equiv_67 + 208)
#define stc217 ((shortint *)&equiv_67 + 216)
#define stc225 ((shortint *)&equiv_67 + 224)
#define syn121 ((shortint *)&equiv_15 + 120)
#define syn113 ((shortint *)&equiv_15 + 112)
#define syn105 ((shortint *)&equiv_15 + 104)
#define stc233 ((shortint *)&equiv_67 + 232)
#define stc249 ((shortint *)&equiv_67 + 248)
#define stc257 ((shortint *)&equiv_67 + 256)
#define stc265 ((shortint *)&equiv_67 + 264)
#define stc273 ((shortint *)&equiv_67 + 272)
#define stc281 ((shortint *)&equiv_67 + 280)
#define stc289 ((shortint *)&equiv_67 + 288)
#define stc297 ((shortint *)&equiv_67 + 296)
#define stc305 ((shortint *)&equiv_67 + 304)
#define stc313 ((shortint *)&equiv_67 + 312)
#define stc321 ((shortint *)&equiv_67 + 320)
#define stc329 ((shortint *)&equiv_67 + 328)
#define stc337 ((shortint *)&equiv_67 + 336)
#define stc345 ((shortint *)&equiv_67 + 344)
#define stc353 ((shortint *)&equiv_67 + 352)
#define stc361 ((shortint *)&equiv_67 + 360)
#define stc369 ((shortint *)&equiv_67 + 368)
#define stc377 ((shortint *)&equiv_67 + 376)
#define stc385 ((shortint *)&equiv_67 + 384)
#define stc393 ((shortint *)&equiv_67 + 392)
#define stc401 ((shortint *)&equiv_67 + 400)
    static real v[4];
#define stc409 ((shortint *)&equiv_67 + 408)
    static real x, y, z, h;
    extern integer ibits_();
    extern /* Subroutine */ int rotem_();
    static integer i0, i1, i2, i3, i4;
    static real x1, y1;
    extern /* Subroutine */ int plot3d_();
    static integer ij, ip, iv, ix, iy, nc0;
    static real xa1, ya1, za1, xw1, yw1, xw2, yw2;
    extern /* Subroutine */ int matmul4_();
    static integer jch;
#define stb ((shortint *)&equiv_67)
    static real rot[16]	/* was [4][4] */;
#define sym ((shortint *)&equiv_15)
#define stc1 ((shortint *)&equiv_67)
#define stc9 ((shortint *)&equiv_67 + 8)
#define syn1 ((shortint *)&equiv_15)
    extern /* Subroutine */ int mtv4_();


/* 	CREATED: DGL 1-OCT-1984 */

/* 	PLOTS SYMBOLS IN 3-D USING PLOT3D */

/* 	XA,YA,ZA COORDINATES OF STRING LOWER-LEFT CORNER */
/* 		  (999.,999.,999.) CONTINUE FROM LAST POINT */
/* 	PA,PB	SPECIFIES THE PROJECTED ANGLES (IN DEGS) RELATIVE TO THE */
/* 		 X-Y PLANE AND THE X-Z PLANE OF THE LINE ALONG THE */
/* 		 BASE OF THE PLOTTED NUMBER SEQUENCE */
/* 	PG	SPECIFIES THE ROTATION OF THE PLOTTED SYMBOLS AROUND */
/* 		THE LINE SPECIFIED BY PA,PB */
/* 	HI	HEIGHT OF THE PLOTTED CHARACTERS */
/* 	ASC	CHARACTER VARIABLE CONTAINING CHARACTERS TO BE PLOTTED */
/* 	NC	NUMBER OF CHARACTERS TO BE PLOTTED */



    xa1 = *xa;
    ya1 = *ya;
    za1 = *za;
    if (*xa == (float)999. || *ya == (float)999. || *za == (float)999.) {
/* CONTINUE STRING OUTPUT */
	xa1 = x;
	ya1 = y;
	za1 = z;
    } else {

/* 	SET UP 3-D CONVERSION MATRIXES */

	rotem_(&c__1, pg, rot);
	rotem_(&c__3, pb, temp);
	matmul4_(rot, rot, temp);
	rotem_(&c__2, pa, temp);
	matmul4_(rot, rot, temp);
    }
    x = xa1;
    y = ya1;
    z = za1;

    h = *hi / (float)7.;
    if (*nc != -2) {
	goto L4;
    }
    ip = 2;
    plot3d_(&xa1, &ya1, &z, &ip);
L4:
    ip = 3;
    plot3d_(&x, &y, &z, &ip);
    if (*nc < 0) {
	goto L10;
    } else if (*nc == 0) {
	goto L20;
    } else {
	goto L30;
    }
L10:
    nc0 = 0;

    jch = *asc;
    goto L50;
L20:
    return 0;
L30:
    nc0 = *nc;
    i0 = 0;
L40:
    --nc0;
    if (nc0 < 0) {
	goto L20;
    }
    ++i0;
    jch = asc[i0 - 1];
L50:
    if (jch < 0 || jch >= 128) {
	jch = 32;
    }
    i3 = sym[jch];
    if (jch >= 32) {
	goto L55;
    }
/* 	CENTERED PLOTTING SYMBOLS */
    ip = 3;
    i1 = 0;
    v[0] = -(doublereal)h * (float)2.;
    v[1] = -(doublereal)h * (float)3.;
    v[2] = (float)0.;
    mtv4_(v, rot, v);
    x = v[0] + x;
    y = v[1] + y;
    z = v[2] + z;
    xw1 = (float)0.;
    yw1 = (float)0.;
    xw2 = (float)0.;
    yw2 = (float)0.;
    goto L110;
L55:
    if (jch != 112) {
	goto L60;
    }
    xw2 = (float)0.;
    yw2 = -(doublereal)h * (float)2.;
    v[0] = xw2;
    v[1] = yw2;
    v[2] = (float)0.;
    mtv4_(v, rot, v);
    r__1 = v[0] + x;
    r__2 = v[1] + y;
    r__3 = v[2] + z;
    plot3d_(&r__1, &r__2, &r__3, &c__3);
L60:
    ip = 2;
    ++i3;
    i4 = (i3 - 1) / 2 + 1;
    iv = stb[i4 - 1];
    ij = (i3 - 1) % 2 << 3;
    i1 = ibits_(&iv, &ij, &c__8);
    i2 = i1 % 64;
    if (i1 >= 64) {
	ip = 3;
    }
    iy = i2 / 8;
    ix = i2 - (iy << 3);
    x1 = (real) ix;
    y1 = (real) iy;
    xw1 = h * x1;
    yw1 = h * y1;
    xw2 = xw1;
    yw2 = yw1;
    if ((jch == 103 || jch == 112 || jch == 113 || jch == 121) && i1 < 192) {
	xw2 = xw2;
	yw2 -= h * (float)2.;
    }
L110:
    v[0] = xw2;
    v[1] = yw2;
    v[2] = (float)0.;
    mtv4_(v, rot, v);
    r__1 = v[0] + x;
    r__2 = v[1] + y;
    r__3 = v[2] + z;
    plot3d_(&r__1, &r__2, &r__3, &ip);
    if (i1 < 192) {
	goto L60;
    }
    v[0] = xw1;
    v[1] = yw1;
    v[2] = (float)0.;
    mtv4_(v, rot, v);
    x = v[0] + x;
    y = v[1] + y;
    z = v[2] + z;
    goto L40;
} /* sym3d_ */

#undef syn1
#undef stc9
#undef stc1
#undef sym
#undef stb
#undef stc409
#undef stc401
#undef stc393
#undef stc385
#undef stc377
#undef stc369
#undef stc361
#undef stc353
#undef stc345
#undef stc337
#undef stc329
#undef stc321
#undef stc313
#undef stc305
#undef stc297
#undef stc289
#undef stc281
#undef stc273
#undef stc265
#undef stc257
#undef stc249
#undef stc233
#undef syn105
#undef syn113
#undef syn121
#undef stc225
#undef stc217
#undef stc209
#undef stc169
#undef stc177
#undef stc185
#undef stc193
#undef stc129
#undef stc137
#undef stc145
#undef stc153
#undef stc161
#undef stc241
#undef stc105
#undef stc113
#undef stc121
#undef stc201
#undef syn89
#undef syn97
#undef syn49
#undef syn57
#undef syn65
#undef syn73
#undef syn81
#undef syn17
#undef syn25
#undef syn33
#undef syn41
#undef stc89
#undef stc97
#undef stc57
#undef stc49
#undef stc65
#undef stc73
#undef stc81
#undef stc17
#undef stc25
#undef stc33
#undef stc41
#undef syn9


/* Subroutine */ int num3d_(xa, ya, za, pa, pb, pg, hght, z, f0)
real *xa, *ya, *za, *pa, *pb, *pg, *hght, *z, *f0;
{
    /* System generated locals */
    integer i__2;
    real r__1;
    char ch__1[26];

    /* Builtin functions */
    double r_mod(), r_lg10();

    /* Local variables */
    extern /* Subroutine */ int sym3d_();
    static char b[18];
    static real f;
    static integer i;
    static real fa;
    static real hg;
    static integer nd, nn;
    static real xt, yt, zt, alg;
    static integer iff;
    static real pat, pbt, pgt;


/* 	CREATED: DGL 1-OCT-1984 */

/* 	PLOTS A FLOATING POINT NUMBER IN 3-D USING SYM3D */

/* 	XA,YA,ZA COORDINATES OF STRING LOWER-LEFT CORNER */
/* 		  (999.,999.,999.) CONTINUE FROM LAST POINT */
/* 	PA,PB	SPECIFIES THE PROJECTED ANGLES (IN DEGS) RELATIVE TO THE */
/* 		 X-Y PLANE AND THE X-Z PLANE OF THE LINE ALONG THE */
/* 		 BASE OF THE PLOTTED NUMBER SEQUENCE */
/* 	PG	SPECIFIES THE ROTATION OF THE PLOTTED SYMBOLS AROUND */
/* 		THE LINE SPECIFIED BY PA,PB */
/* 	HGHT	HEIGHT OF THE PLOTTED NUMBER */
/* 	Z	FLOATING POINT NUMBER TO BE PLOTTED */
/* 	F0	PLOTTING FORMAT (Fn.j) */
/* 		  n = TOTAL NUMBER OF SPACES TO USE (INCLUDING SIGN AND D.P.) */
/* 			[MAX 18 CHARACTERS WIDE] */
/* 		  j = DIGITS TO RIGHT OF DECIMAL POINT (TWO DIGITS EXPECTED) */
/* 			(F4.2 SHOULD BE WRITTEN F4.02) */
/* 		  IF F0 < 0 USE EXPONENTIAL NOTATION (I.E., En,j) */
/* 		  F0 = 1 PLOT IN FLOATING POINT FREE FORMAT */
/* 		  F0 = 0 PLOT INTEGER PORTION WITH NO D.P. (FREE FORMAT) */
/* 		  F0 =-1 PLOT IN EXPONENTIAL FREE FORMAT */
/* 			 NOTE: FREE FORMATS HAVE LEADING SPACES SUPPRESSED */
/* 		  F0 > 1000 PLOT INTEGER PORTION IN FIXED FORMAT WITH */
/* 			n DIGITS AND WITHOUT D.P. */
/* 		  IF n=0 THEN PLOT INTEGER PORTION, DECIMAL POINT, AND */
/* 			 j DIGITS TO RIGHT OF DECIMAL POINT */
/* 		  WHEN Z OVERFLOWS THIS FORMAT, SPACE IS FILLED WITH ASTERICKS */

    xt = *xa;
    yt = *ya;
    zt = *za;
    pat = *pa;
    pbt = *pb;
    pgt = *pg;
    iff = 0;
    hg = *hght;
    if (hg == (float)0.) {
	hg = (float).15;
    }
    nd = 0;
    nn = 0;
    fa = *f0;
    if (dabs(fa) > (float)1022.) {
	fa = (float)0.;
    }
    if (fa == (float)0.) {
	goto L10;
    }
/* INTEGER FORMAT */
    if (fa > (float)999.) {
/* PLOT FORMATTED INTEGER */
	nn = r_mod(&fa, &c_b65);
	fa = (float)0.;
    } else {
/* PLOT FLOAT OR EXPON NUMBER */
	f = dabs(fa) * (float)1.000002;
	nn = f;
	f = (f - nn) * (float)100.;
	nd = f;
    }
L10:
    if (nd > 17) {
	nd /= 10;
    }
/* CORRECT SIMPLE INPUT ERRORS */
    if (nn == 0) {
/* DIGITS TO LEFT OF DECIMAL POINT */
	nn = nd + 2;
	if (*z == (float)0. && fa == (float)0.) {
	    nn = 1;
	}
	if (*z != (float)0.) {
	    r__1 = dabs(*z);
	    alg = r_lg10(&r__1);
	    if (alg < (float)0.) {
		alg = (float)0.;
	    }
	    nn = nd + 2 + alg;
	    if (fa == (float)0.) {
		nn = alg + 1;
	    }
	}
	if (*z < (float)0.) {
	    ++nn;
	}
	if (fa < (float)0.) {
	    nn += 4;
	}
    }
    if (nd > nn) {
	goto L90;
    }
/* FORMAT ERROR */
    if (nn > 18) {			/* MAX CHARACTERS */
	nn = 18;
    }
    if (fa == 0.f) {			/* INTEGER */
	i = *z;
	if (nn / 10 > 0) {
	    i__2 = sprintf(ch__1, "%%%2dd", nn);
	} else {
	    i__2 = sprintf(ch__1, "%%%1dd", nn);
	}
/*	if (i__2 != 0) {
	    goto L90;
	} */
	i__2 = sprintf(b, ch__1, i);
/*	if (i__2 != 0) {
	    goto L90;
	} */
    } else {				/* FLOATING POINT OR EXPONENTIAL */
	if (nn > 1) {
	    if (nd/10 > 0) {
		i__2 = sprintf(ch__1, "%%%2d.%2df", nn,nd);
	    } else {
		if (nn/10 > 0) {
			i__2 = sprintf(ch__1, "%%%2d.%1df", nn,nd);
		} else {
			i__2 = sprintf(ch__1, "%%%1d.%1df", nn,nd);
		}
	    }
	} else {
	    i__2 = sprintf(ch__1, "%%f");
	}
/*	if (i__2 != 0) {
	    goto L90;
	} */
	i__2 = sprintf(b, ch__1, *z);
/*	if (i__2 != 0) {
	    goto L90;
	} */
	if (iff == 1) {			/* REMOVE LEADING SPACES */
	    for (i = 1; i <= 18; ++i) {
		if (*b == ' ') {
		    for (i__2 = i; i__2 < 18; ++i__2)
			b[i__2] = b[i__2+1];
		}
	    }
	    b[17] = 0;
	}
    }
L50:
    sym3d_(&xt, &yt, &zt, &pat, &pbt, &pgt, &hg, b, &nn);
/* L60: */
    return 0;
L90:
    for (i = 1; i <= 18; ++i) {
	b[i - 1] = '*';
	if (i == nn - nd) {
	    b[i - 1] = '.';
	}
/* L95: */
    }
    goto L50;
} /* num3d_ */



/* Subroutine */ int axis3d_(x0, y0, z0, pa, pb, pg, t, n0, s0, b0, c0, d0, 
	e0, f0)
real *x0, *y0, *z0, *pa, *pb, *pg;
char *t;
integer *n0;
real *s0, *b0, *c0, *d0, *e0, *f0;
{
    /* Initialized data */

    static real space = (float).08;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2, r__3;
    doublereal d__1;

    /* Builtin functions */
    double r_mod(), r_lg10(), r_int(), pow_dd();

    /* Local variables */
    static real temp[16]	/* was [4][4] */;
    extern /* Subroutine */ int num3d_(), sym3d_();
    static integer i, j, k;
    static real v[4], e1;
    extern /* Subroutine */ int rotem_();
    static real c1;
    static integer n1;
    static real x1, y1, y2, x2, x3;
    extern /* Subroutine */ int plot3d_();
    static real fa, cs;
    static integer nc;
    static real x01, y01, z01;
    static integer nd, ng;
    static real tl, xj, xn, xs, tl1, paa, pba;
    extern /* Subroutine */ int matmul4_();
    static real pga;
    extern doublereal xvmul3d_();
    static real hor, dnx, dny;
    static integer njt, nnt;
    static real dty, dtx, rot[16]	/* was [4][4] */;
    static integer nst;


/* 	CREATED: DGL 1-OCT-1984 */

/* 	X0	X COORDINATE OF START OF AXIS */
/* 	Y0	Y COORDINATE OF START OF AXIS */
/* 	Z0	Z COORDINATE OF START OF AXIS */
/* 	T	CHARACTER STRING TO DESCRIBE AXIS */
/* 	PA	ANGLE FROM X-Y PLANE (DEG) */
/* 	PB	ANGLE FROM X-Z PLANE (DEG) */
/* 	PG	ANGLE OF ROTATION AROUND PA,PB RAY (DEG) */
/* 	N0	NUMBER OF CHARACTERS IN STRING */
/* 		- ON CLOCKWISE SIDE OF AXIS (NORMAL FOR X) */
/* 		+ ON COUNTER CLOCKWISE SIDE OF AXIS (NORMAL FOR Y) */
/* 		HUNDREDS DIGIT	= 1 NO LABELING OF AXIS--TICKS AND LINE ONLY */
/* 	S0	LENGTH OF AXIS IN INCHES */
/* 		< 0	TICKS PLACED ON OPPOSITE SIDE OF AXIS LABEL */
/* 		= 0	NO ACTION (NOP) */
/* 		> 0	NORMAL */
/* 	B0	MINIMUM VALUE ON TICK AXIS */
/* 	C0	MAXIMUM VALUE ON TICK AXIS */
/* 	D0	INT(D0) = NUMBER OF MAJOR AXIS TICKS */
/*		INT((INT(D0)-D0)*100) = NUMBER OF MINOR AXIS TICKS BETWEEN MAJOR TICKS
*/
/* 		INT(MOD((INT(D0)-D0)*10000,100) = NUMBER OF SUB MINOR AXIS TICKS */
/* 			BETWEEN MINOR TICKS */
/* 	E0	CHARACTER SIZE OF TITLE AND NUMBER (IF E0=0 DEFAULTS TO .15) */
/* 			< 0 THEN DO NOT AUTO SCALE BY (x10 TO POWER) */
/* 	F0	NUMBER SPECIFICATION (FORMAT FX.Y) (2 DIGITS FOR Y, MAX(X)=18) */

/* MIN SPACING BETWEEN ITEMS */

    tl = (float).1;
/* TICK LENGTH */
    x01 = *x0;
    y01 = *y0;
    z01 = *z0;
    paa = *pa;
    pba = *pb;
    pga = *pg;
    e1 = *e0;
/* CHARACTER SIZE */
    cs = dabs(e1);
    if (cs == (float)0.) {
	cs = (float).15;
    }
    if (*s0 == (float)0.) {
	goto L1000;
    }
/* ZERO LENGTH AXIS */
    x1 = *d0 * (float)1.000002;
    njt = dabs(x1);
/* NUMBER OF MAJOR TICKS */
    nnt = (dabs(x1) - njt) * (float)100.;
/* NUMBER OF MINOR TICKS */
    nst = ((dabs(x1) - njt) * (float)100. - nnt) * (float)100.;
/* NUMBER OF SUB-MINOR TICKS */
    if (njt < 2) {
	njt = 2;
    }
    xj = dabs(*s0) / (njt - 1);
/* INCREMENT BETWEEN MAJOR TICKS */
    xn = xj;
    if (nnt != 0) {
	xn /= nnt + 1;
    }
/* INCREMENT BETWEEN MINOR TICKS */
    xs = xn / (nst + 1);
/* INCREMENT BETWEEN SUB-MINOR TICKS */
    n1 = *n0;
    hor = (float)0.;
    if (abs(n1) >= 1000) {
	hor = (float)90.;
    }
/* DEFAULT ROTATION ANGLE */
    nc = abs(n1) % 100;
/* NUMBER OF CHARACTERS IN TITLE */
    fa = *f0;
/* FORMAT NUMBER */
    r__1 = dabs(fa);
    nd = r_mod(&r__1, &c_b65);
/* NUMBER OF DIGITS */
    r__1 = dabs(fa);
    ng = (r_mod(&r__1, &c_b65) - nd) * (float)100.;
/* NUMBER OF DIGITS RIGHT OF D.P. */
    if (ng > 17) {
	ng /= 10;
    }
/* CORRECT SIMPLE ERRORS */
    if (nd == 0) {
	nd = ng;
    }
    if (dabs(fa) > (float)1e3) {
	ng = -1;
    }
/* FORMATTED INTEGER */
    tl1 = tl;
    if (*s0 < (float)0.) {
	tl1 = -(doublereal)tl;
    }
/* REVERSE SIDE OF TICKS */
    if (*s0 < (float)0.) {
	tl = (float)0.;
    }
/* REVERSE SIDE OF TICKS */
    if (abs(n1) >= 1000) {
	goto L10;
    }
    dnx = -nd * cs / (float)2.;
/* NUMBER LABEL DISTANCE FROM AXIS */
    dny = -(doublereal)tl - space - cs;
/* NUMBER LABEL DISTANCE FROM AXIS */
    dty = dny - cs - space;
/* TITLE DISTANCE FROM AXIS */
    goto L20;
L10:
/* HORIZONTAL NUMBERS ON VERTICAL AXIS */
    dnx = -(doublereal)cs / (float)2.;
/* NUMBER LABEL DISTANCE FROM AXIS */
    dny = -(doublereal)tl - space;
/* NUMBER LABEL DISTANCE FROM AXIS */
    dty = dny - nd * cs - space;
/* TITLE DISTANCE FROM AXIS */
L20:
    dtx = (dabs(*s0) - nc * cs) / (float)2.;
/* TITLE DISTANCE FROM AXIS */
    if (n1 < 0) {
	goto L30;
    }
/* CLOCKWISE TITLES */
    dny = -(doublereal)dny - cs;
/* COUNTER-CLOCKWISE TITLES */
    dty = -(doublereal)dty - cs;
    tl1 = -(doublereal)tl1;
/* CHANGE SIDES OF TICKS */
    if (abs(n1) < 1000) {
	goto L30;
    }
    dny += cs * nd;
    dty = dny + space;
L30:

/* 	SET UP 3-D CONVERSION MATRIXES */

    rotem_(&c__1, &pga, rot);
    rotem_(&c__3, &pba, temp);
    matmul4_(rot, rot, temp);
    rotem_(&c__2, &paa, temp);
    matmul4_(rot, rot, temp);

    x1 = (float)0.;
/* FIRST MAJOR TICK */
    y1 = (float)0.;
    y2 = -(doublereal)tl1;
    r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
    r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
    r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
    plot3d_(&r__1, &r__2, &r__3, &c__3);
    r__1 = xvmul3d_(&c__1, &x1, &y2, &c_b104, v, rot) + x01;
    r__2 = xvmul3d_(&c__2, &x1, &y2, &c_b104, v, rot) + y01;
    r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
    plot3d_(&r__1, &r__2, &r__3, &c__2);
    i__1 = njt - 1;
    for (i = 1; i <= i__1; ++i) {
/* MAJOR TICKS */
	r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
	r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
	r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
	plot3d_(&r__1, &r__2, &r__3, &c__3);
	x1 = xj * i;
	y2 = -(doublereal)tl1;
	r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
	r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
	r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
	plot3d_(&r__1, &r__2, &r__3, &c__2);
	r__1 = xvmul3d_(&c__1, &x1, &y2, &c_b104, v, rot) + x01;
	r__2 = xvmul3d_(&c__2, &x1, &y2, &c_b104, v, rot) + y01;
	r__3 = xvmul3d_(&c__3, &x1, &y2, &c_b104, v, rot) + z01;
	plot3d_(&r__1, &r__2, &r__3, &c__2);
	i__2 = nnt + 1;
	for (j = 1; j <= i__2; ++j) {
/* MINOR TICKS */
	    y2 = -(doublereal)tl1 * (float).7;
	    x2 = x1 + xn * j - xj;
	    r__1 = xvmul3d_(&c__1, &x2, &y1, &c_b104, v, rot) + x01;
	    r__2 = xvmul3d_(&c__2, &x2, &y1, &c_b104, v, rot) + y01;
	    r__3 = xvmul3d_(&c__3, &x2, &y1, &c_b104, v, rot) + z01;
	    plot3d_(&r__1, &r__2, &r__3, &c__3);
	    r__1 = xvmul3d_(&c__1, &x2, &y2, &c_b104, v, rot) + x01;
	    r__2 = xvmul3d_(&c__2, &x2, &y2, &c_b104, v, rot) + y01;
	    r__3 = xvmul3d_(&c__3, &x2, &y2, &c_b104, v, rot) + z01;
	    plot3d_(&r__1, &r__2, &r__3, &c__2);
	    y2 = -(doublereal)tl1 * (float).4;
	    i__3 = nst;
	    for (k = 1; k <= i__3; ++k) {
/* SUB MINOR TICKS */
		x3 = x2 + xs * k - xn;
		r__1 = xvmul3d_(&c__1, &x3, &y1, &c_b104, v, rot) + x01;
		r__2 = xvmul3d_(&c__2, &x3, &y1, &c_b104, v, rot) + y01;
		r__3 = xvmul3d_(&c__3, &x3, &y1, &c_b104, v, rot) + z01;
		plot3d_(&r__1, &r__2, &r__3, &c__3);
		r__1 = xvmul3d_(&c__1, &x3, &y2, &c_b104, v, rot) + x01;
		r__2 = xvmul3d_(&c__2, &x3, &y2, &c_b104, v, rot) + y01;
		r__3 = xvmul3d_(&c__3, &x3, &y2, &c_b104, v, rot) + z01;
		plot3d_(&r__1, &r__2, &r__3, &c__2);
/* L120: */
	    }
/* L110: */
	}
/* L100: */
    }
    if (abs(n1) % 1000 / 100 != 0) {
	goto L1000;
    }
/* NO LABELING */
    xs = (float)0.;
/* EXPONENT */
    if (e1 < (float)0.) {
	goto L140;
    }
/* NO AUTO SCALING */
    x1 = (float)0.;
    y1 = (float)0.;
    i = nd - ng - 2;
    if (*b0 < (float)0. || *c0 < (float)0.) {
	--i;
    }
    if (*b0 != (float)0.) {
	r__1 = dabs(*b0);
	x1 = r_lg10(&r__1);
    }
    if (x1 < (float)0. && x1 != r_int(&x1)) {
	x1 += (float)-1.;
    }
    x1 = r_int(&x1);
    if (*c0 != (float)0.) {
	r__1 = dabs(*c0);
	y1 = r_lg10(&r__1);
    }
    if (y1 < (float)0. && y1 != r_int(&y1)) {
	y1 += (float)-1.;
    }
    y1 = r_int(&y1);
    x2 = dmin(x1,y1);
    x3 = dmax(x1,y1);
    if (x2 < (float)0. && (real) ng <= -(doublereal)x2) {
	xs = -ng + 1 - x2;
    }
    if ((real) i < x3 + xs) {
	xs = i - x3 - xs;
    }
L140:
    y1 = dny;
    y2 = (*c0 - *b0) / (njt - 1);
    e1 = xs;
/* EXPONENT VALUE */
    i__1 = njt;
    for (i = 1; i <= i__1; ++i) {
/* LABEL MAJOR TICKS */
	x1 = (i - 1) * xj + dnx;
	d__1 = (doublereal) e1;
	c1 = (y2 * (i - 1) + *b0) * pow_dd(&c_b171, &d__1);
	r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
	r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
	r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
	num3d_(&r__1, &r__2, &r__3, &paa, &pba, &pga, &cs, &c1, &fa, &hor);
/* L150: */
    }
    if (e1 != (float)0.) {
	dtx -= cs * (float)3.;
    }
/* ADD EXPONENT SPACE */
    x1 = dtx;
    y1 = dty;
    if (nc != 0) {
	r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
	r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
	r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
	sym3d_(&r__1, &r__2, &r__3, &paa, &pba, &pga, &cs, t, &nc);
    }
    if (e1 == (float)0.) {
	goto L1000;
    }
/* NO EXPONENT */
    x1 += nc * cs;
    r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
    r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
    r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
    sym3d_(&r__1, &r__2, &r__3, &paa, &pba, &pga, &cs, "(X10)", &c__5);
    x1 += cs * (float)4.5;
    y1 += cs / (float)2.;
    cs /= (float)2.;
    r__1 = xvmul3d_(&c__1, &x1, &y1, &c_b104, v, rot) + x01;
    r__2 = xvmul3d_(&c__2, &x1, &y1, &c_b104, v, rot) + y01;
    r__3 = xvmul3d_(&c__3, &x1, &y1, &c_b104, v, rot) + z01;
    num3d_(&r__1, &r__2, &r__3, &paa, &pba, &pga, &cs, &e1, &c_b104);
L1000:
    return 0;
} /* axis3d_ */


doublereal xvmul3d_(i, x, y, z, v, r)
integer *i;
real *x, *y, *z, *v, *r;
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern /* Subroutine */ int mtv4_();
/* 	CREATED: DGL 1-AUG-1984 */
/* 	RETURNS ONE ELEMENT OF A 3 ELEMENT VECTOR TRANSFORMATION */

    /* Parameter adjustments */
    --r;
    --v;

    /* Function Body */
    v[1] = *x;
    v[2] = *y;
    v[3] = *z;
    v[4] = (float)0.;
    mtv4_(&v[1], &r[1], &v[1]);
    ret_val = v[1];
    if (*i == 2) {
	ret_val = v[2];
    }
    if (*i == 3) {
	ret_val = v[3];
    }
    return ret_val;
} /* xvmul3d_ */
