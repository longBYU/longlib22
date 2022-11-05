
/* *** LAST REVISED ON 23-DEC-1993 06:13:44.04 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CVAX3D.C */

#include "my.h"

/* Subroutine */ int cvax3d_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, clow, nlev, cval, nch, nmin, iline, ipls, xt, nxt, 
	xastart, xaend, yt, nyt, zt, nzt, zastart, zaend, aminin, amaxin, 
	icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
real *clow;
integer *nlev;
real *cval;
integer *nch, *nmin, *iline, *ipls;
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
    static real tx, ty, tz;
    extern /* Subroutine */ int cvax3dx_();
    static real amn;
    static integer iax;
    static real fdx, fdy, fdz, amx, tsx, tsy, tsz;


/* 	CREATED BY D. LONG  AUG 1987	AT JPL */

/* 	SIMPLIFIES CALLING CVAX3DX ROUTINE */

    /* Parameter adjustments */
    --icol;
    --ipls;
    --iline;
    --cval;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    iax = *iaxis % 100;
    if (*iaxis < 0) {
	amn = *aminin;
	amx = *amaxin;
    }
    if (abs(*iflag) % 10 == 2) {
	cvax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, clow, nlev, &cval[1], nch, nmin, &iline[1], &
		ipls[1], xt, nxt, xastart, xaend, &tx, &tsx, &fdx, yt, nyt, &
		ty, &tsy, &fdy, zt, nzt, zastart, zaend, &tz, &tsz, &fdz, &
		amn, &amx, &icol[1]);
    } else {
	cvax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, clow, nlev, &cval[1], nch, nmin, &iline[1], &
		ipls[1], xt, nxt, xastart, xaend, &tx, &tsx, &fdx, yt, nyt, &
		ty, &tsy, &fdy, zt, nzt, zastart, zaend, &tz, &tsz, &fdz, &
		amn, &amx, &ic);
    }
    return 0;
} /* cvax3d_ */

