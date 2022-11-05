
/* *** LAST REVISED ON 24-DEC-1993 06:58:16.82 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]ARROW.C */

#include "my.h"

/* Table of constant values */

static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int arrow_(x, y, alen, ang, apt, aptan)
real *x, *y, *alen, *ang, *apt, *aptan;
{
    /* Initialized data */

    static real api = (float).0174532;

    /* Builtin functions */
    double cos(), sin();

    /* External functions */
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static real x0, y0, x1, y1;

/* 	CREATED BY D. LONG, DEC. 1983 AT JPL */
/* 	PLOTS AN ARROW WITH CHOICE OF HEADS */

/* 	X,Y	(R)	LOCATION OF TAIL (INCHES) */
/* 	ALEN	(R)	LENGTH OF ARROW (INCHES) */
/* 	ANG	(R)	ANGLE FROM HORIZONTAL (DEGREES) */
/* 	APT	(R)	LENGTH OF ARROW POINT (INCHES) */
/* 			> 0   -->  (NORMAL ARROW) */
/* 			< 0   -I> (DELTA HEAD ARROW) */
/* 	APTAN	(R)	ANGLE OF ARROW POINT FROM LINE (DEGREES) */

/* PI/180 */
    if (*alen == (float)0.) {
	return 0;
    }
    x0 = *x + *alen * cos(api * *ang);
    y0 = *y + *alen * sin(api * *ang);
    plot_(x, y, &c__3);
    plot_(&x0, &y0, &c__2);
    x1 = x0 + dabs(*apt) * cos(api * ((float)180. - *aptan + *ang));
    y1 = y0 + dabs(*apt) * sin(api * ((float)180. - *aptan + *ang));
    plot_(&x1, &y1, &c__2);
    if (*apt > (float)0.) {
	plot_(&x0, &y0, &c__2);
    }
    x1 = x0 + dabs(*apt) * cos(api * (*aptan + *ang - (float)180.));
    y1 = y0 + dabs(*apt) * sin(api * (*aptan + *ang - (float)180.));
    plot_(&x1, &y1, &c__2);
    if (*apt < (float)0.) {
	plot_(&x0, &y0, &c__2);
    }
    plot_(x, y, &c__3);
    return 0;
} /* arrow_ */
