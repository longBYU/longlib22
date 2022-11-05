
/* *** LAST REVISED ON  9-DEC-1993 22:57:03.31 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.EXAMPLES]IMAGMAP.FOR */

#include "my.h"

/* Table of constant values */
static integer c_n101 = -101;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__5 = 5;
static integer c__101 = 101;
static real c_b3 = (float)1.;
static real c_b7 = (float)0.;
static real c_b37 = (float).12;
static real c_b38 = (float)6.2;
static real c_b50 = (float)90.;


int main()
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double cos();
    integer i_nint();
    double r_nint();

    /* External functions */
    extern /* Subroutine */ int rect_(), plot_();
    extern /* Subroutine */ int axis3_();
    extern /* Subroutine */ int frame_(), cterm_();
    extern /* Subroutine */ int rterm_(), rmpix_();
    extern /* Subroutine */ int rammap_(), tekmap_(), terscl_(), plotnd_();
    extern /* Subroutine */ int metmap2_();
    extern integer irmchan_();

    /* Local variables */
    static real rjxt, rjyt;
    static integer i, j, n, ichan;
    static real stval[40000];
    static real xsize, ysize, af;
    static integer id, it;
    static integer istval[40000], ix1, iy1;
    static integer ixr, iyr, ixt, iyt;
    static real rjx, rjy;
    static integer nsx, nsy, ixt1, iyt1;

/* 	OPEN PLOT PACKAGE */

    frame_(&c__0, &c__0, &c_b3, &c_b3, &c_b3);

/* 	SET SIZE AND SCALE FACTORS */

    nsx = 100;
    nsy = 100;
    xsize = (float)4.;
    ysize = (float)4.;

/* 	FILL ARRAY */

    i__1 = nsx;
    for (i = 1; i <= i__1; ++i) {
	i__2 = nsy;
	for (j = 1; j <= i__2; ++j) {
	    n = i + (j - 1) * nsx;
	    stval[n - 1] = cos(i * (float)6. / (real) nsx) * cos(j * (float)
		    5. / (real) nsy) + (float)1.;
	}
    }

/* 	DISPLAY IMAGE MAP TO TEKTRONICS TERMINAL */

    terscl_(&c__1, &it, &c_b7, &c_b7, &ixt, &iyt);
    terscl_(&c__1, &it, &xsize, &ysize, &ixt1, &iyt1);
    if (it > 0) {
/* IF PROPER TEK TERMINAL */
	rjxt = (real) (ixt1 - ixt) / (real) nsx;
	rjyt = (real) (iyt1 - iyt) / (real) nsy;

/* 	SCALE TO THE RANGE -15 TO 0 */

	i__1 = nsx * nsy;
	for (i = 1; i <= i__1; ++i) {
	    r__1 = stval[i - 1] * (float)7.5;
	    istval[i - 1] = -i_nint(&r__1);
	}
	cterm_(&c_n1);
	tekmap_(istval, &nsx, &nsy, &nsx, &nsy, &ixt, &iyt, &rjxt, &rjyt);
    }

/* 	DISPLAY IMAGE MAP TO RAMTEK DEVICE */

    rmpix_(&c_b7, &c_b7, &ixr, &iyr);
    rmpix_(&xsize, &ysize, &ix1, &iy1);
    i__1 = ix1 - ixr;
    rjx = (real) abs(i__1) / (real) nsx;
    rjy = (real) (iy1 - iyr) / (real) nsy;

/* 	SCALE TO (0..255) */

    i__1 = nsx * nsy;
    for (i = 1; i <= i__1; ++i) {
	r__1 = stval[i - 1] * 127;
	istval[i - 1] = i_nint(&r__1);
    }

/* 	PLOT TO RAMTEK ONLY IF RAMTEK IS OPEN */

    ichan = irmchan_(&id);
    if (ichan > 0) {
	rammap_(istval, &nsx, &nsy, &nsx, &nsy, &ixr, &iyr, &rjx, &rjy);
    }

/* 	SEND IMAGE MAP TO META FILE */

/* 	CALL METMAP(ISTVAL,NSX,NSY,NSX,NSY,0.,0.,XSIZE,YSIZE) */
    metmap2_(istval, &nsx, &nsy, &c__1, &c__1, &nsx, &nsy, &c_b7, &c_b7, &
	    xsize, &ysize);
    /*    plot_(&c_b17, &c_b17, &c_n3);
    metmap2_(istval, &nsx, &nsy, &c__50, &c__50, &c__100, &c__100, &c_b7, &
	    c_b7, &xsize, &ysize);
    */
/* 	NOW AXES PLOT TO ALL DEVICES */

    plot_(&c_b3, &c_b7, &c__0);

/* SET PLOT COLOR */
    rect_(&c_b7, &c_b7, &xsize, &ysize);
    af = r_nint(&xsize) + (float)1.0101;
    axis3_(&c_b7, &c_b7, "X", &c_n1, &xsize, &c_b7, &c_b7, &xsize, &af, &
	    c_b37, &c_b38, 1L);
    axis3_(&c_b7, &ysize, "X", &c__101, &xsize, &c_b7, &c_b7, &xsize, &af, &
	    c_b37, &c_b38, 1L);
    af = r_nint(&ysize) + (float)1.0101;
    axis3_(&c_b7, &c_b7, "Y", &c__1, &ysize, &c_b50, &c_b7, &ysize, &af, &
	    c_b37, &c_b38, 1L);
    axis3_(&xsize, &c_b7, "Y", &c_n101, &ysize, &c_b50, &c_b7, &ysize, &af, &
	    c_b37, &c_b38, 1L);
    plot_(&c_b7, &c_b7, &c__5);

/* 	CLEAR SCREENS AND CLOSE PACKAGES */

    cterm_(&c__2);
    rterm_(&c__2);
    plotnd_();

}

