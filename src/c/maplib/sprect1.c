
/* *** LAST REVISED ON 24-FEB-1994 01:37:11.95 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]SPRECT1.C */

#include "my.h"

/* Subroutine */ int sprect1_(v, t, p, r)
real *v, *t, *p, *r;
{
    /* Builtin functions */
    double cos(), sin();

/* 	CONVERT FROM SPHERICAL TO RECTANGULAR COORDINATES */
/* 	(LATTITUDE-LONGITUDE TYPE SPHERICAL COORDINATES) */

/* 	V	(R):	OUTPUT VECTOR (RECTANGULAR COOR.) V(3) */
/* 	T	(R):	THETA INPUT ANGLE (RADIANS) */
/* 	P	(R):	PHI INPUT ANGLE (CONE ANGLE) (RADIANS) */
/* 	R	(R):	RADIUS INPUT */

    /* Parameter adjustments */
    --v;

    /* Function Body */
    v[1] = *r * cos(*t) * sin(*p);
    v[2] = *r * sin(*t) * sin(*p);
    v[3] = *r * cos(*p);
    return 0;
} /* sprect1_ */

