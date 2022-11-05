
/* *** LAST REVISED ON  1-FEB-1994 11:14:04.61 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.UTILS]REPLOT.C */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my.h"

/* Table of constant values */
static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static real c_b6 = (float)0.;
static real c_b8 = (float)1.;

FILE *input_file;

int main(argc,argv)
int argc; char **argv;
{
    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int frame_(),cterm_(),rterm_(),plotnd_(),replot_();

    /* Local variables */
    static char name[80];
    integer pone = 1, none = -1;

/* 	CREATED: DGL JAN 1995 */

/* 	THIS PROGRAM PERMITS REPLOTTING OF A PRINTER GRAPHICS FILE */
/* 	PRODUCED BY THE LONGLIB GRAPHICS LIBRARY TO A SCREEN DEVICE. */
/* 	THE USER IS PROMPTED TO DETERMINE WHICH SCREEN DEVICE TO USE. */

/* 	ANY NEWPAGE COMMANDS IN PRINTER FILE WILL BE PROCESSED AS */
/* 	A CTERM(2) COMMAND FOR THE SCREEN DEVICE. */
/* 	OF COURSE, SINCE THE PRINTER FILE DOES NOT MAINTAIN A COPY OF */
/* 	WHAT DATA WENT TO THE SCREENS, ANY CTERMS USED IN THE ORIGINAL */
/* 	PROGRAM GENERATING THE FILE WILL NOT BE REPEATED BY THIS PROGRAM. */

    if (*++argv) {
       strcpy(name,*argv);
    } else {
       strcpy(name,"3.dat");
    };

/* 	OPEN LONGLIB WITHOUT METAFILE */
/* 	PROMPT FOR SCREEN TYPE */

    frame_(&c_n3, &c__0, &c_b6, &c_b6, &c_b8);

/* 	REPLOT META FILE TO SCREEN */
    cterm_(&pone);
    printf("Opening file '%s'\n",name);
    cterm_(&none);
    replot_(name);

/* 	TERMINATE PLOTTING */

    plot_(&c_b6, &c_b6, &c__3);
    cterm_(&c__2);
    rterm_(&c__2);
    plotnd_();
    return 0;
}


int replot_(name)
char *name;
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int reget_(), cterm_(), rterm_();
    extern /* Subroutine */ int rmpix_();
    extern /* Subroutine */ int rammap_(), tekmap_(), newpen_(), terscl_();
    extern integer irmchan_();
    extern /* Subroutine */ int newpage_();

    /* Local variables */
    static integer iold, jold;
    static real xold, yold;
    static real rjxt, rjyt;
    static integer i, ichan;
    static integer i1, i2, i3, m1, m2, m3;
    static real x1, y1;
    static integer id, mp, it;
    static real sx, sy;
    static integer ix1, iy1, iar[1310720];
    static real amx, amy;
    static integer inx, iny, num;
    static integer ixr, iyr, ixt;
    static integer iyt;
    static real rjx, rjy;

/* 	MAIN ROUTINE TO REPLOT A PRINTER GRAPHICS FILE TO A SCREEN */
/* 	DEVICE FOR THE LONGLIB GRAPHICS LIB. */

/* 	INITIALIZE */

    amx = (float)1.;
    amy = (float)1.;
    xold = (float)0.;
    yold = (float)0.;

/* 	OPEN INPUT FILE */

    mp = 999;

    input_file = fopen(name,"r");
    if (input_file == NULL) {
	printf("*** Error opening input file '%s' ***\n",name);
	return 0;
    }

/* 	TOP OF COMMAND READ LOOP */
L1000:
    reget_(&m1, &m2, &m3, &mp, &c__2);
    if (m3 == 11) {
	goto L110;
    }
    if (m1 == 0 || m2 == 0) {
	goto L110;
    }
    sx = (float)1. / (real) m1;
    sy = (float)1. / (real) m2;

/* 	TOP OF INNER LOOP */

L1:
    reget_(&m1, &m2, &m3, &mp, &c__2);
L2:
    y1 = m1 * sx;
    x1 = m2 * sy;

/* 	I3 IS THE COMMAND */

    i3 = m3;
    iold = 0;
    jold = 1;

/* 	CHECK FOR END OF FILE */

    if (m3 > 999) {
	goto L999;
    }

/* 	EXECUTE COMMAND */

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

/* 	PLOT COMAND */

L20:
    plot_(&x1, &y1, &i3);
    if (abs(i3) == 2 || abs(i3) == 3) {
	xold = x1;
	yold = y1;
    }
    goto L1;

/* 	FOR NEWPAGE WE WILL PROMPT FOR SCREEN CLEARS */

L100:
    newpage_();
    cterm_(&c__2);
    cterm_(&c_n1);
    rterm_(&c__2);
    rterm_(&c_n1);
    goto L1;
L999:
    if (i3 > 1999) {
	goto L1999;
    }
    switch ((int)(i3 - 999)) {
	case 1:  goto L1000;
	case 2:  goto L1001;
	case 3:  goto L1002;
	case 4:  goto L1003;
    }
/* L2000: */
    goto L1;

/* 	CHANGE LINE TYPE */

L1001:
    iold = m1;
    i3 = jold * 10 + iold + 1;
    newpen_(&i3);
    goto L1;

/* 	PEN COLOR */

L1002:
    if (m2 >= 0) {
	r__1 = (real) m2;
	plot_(&r__1, &c_b6, &c__0);
    }
    goto L1;

/* 	PEN WIDTH */

L1003:
    jold = m1;
    i3 = jold * 10 + iold + 1;
    newpen_(&i3);
    goto L1;

/* 	HANDLE IMAGE DATA */

L1999:

/* 	CHECK EACH OPTION */

    if (i3 == 2000) {
	amx = m1 * sx;
	amy = m2 * sy;
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

/* 	READ IMAGE DATA INTO AN ARRAY */

	if (num % 2 == 1) {
	    ++num;
	}
	num /= 2;

/* 	READ IN MAP DATA IN Y-MAJOR ORDER, I.E., (0,0) (1,0) (2,0)... */

	i__1 = num;
	for (i = 1; i <= i__1; ++i) {
	    i1 = (i - 1 << 1) + 1;
	    reget_(&m1, &m2, &m3, &mp, &c__2);
	    if (m3 != 2002) {
		goto L2;
	    }
	    if (i1 < 1310720) {
		i2 = (i1 - 1) / iny + 1 + (i1 - 1) % iny * inx;
		iar[i2 - 1] = m1;
		/* iy = i1 % iny; */
		i2 = i1 / iny + 1 + i1 % iny * inx;
		iar[i2 - 1] = m2;
	    }
/* L2002: */
	}

/* 	DISPLAY IMAGE ARRAY */

/* C		CALL METMAP(IAR,INX,INY,INX,INY,XOLD,YOLD,AMX+XOLD,AMY+YOLD) */

/* 	TEKTRONICS TERMINAL */

	terscl_(&c__1, &it, &xold, &yold, &ixt, &iyt);
	if (it > 0) {		/* IF PROPER TEK TERMINAL */
	    r__1 = amx + xold;
	    r__2 = amy + yold;
	    terscl_(&c__1, &it, &r__1, &r__2, &ix1, &iy1);
	    rjxt = (real) (ix1 - ixt) / (real) inx;
	    rjyt = (real) (iy1 - iyt) / (real) iny;
	    tekmap_(iar, &inx, &iny, &inx, &iny, &ixt, &iyt, &rjxt, &rjyt);
	}

/* 	RAMTEK */

	ichan = irmchan_(&id);
	if (ichan > 0) {
	    rmpix_(&xold, &yold, &ixr, &iyr);
	    r__1 = amx + xold;
	    r__2 = amy + yold;
	    rmpix_(&r__1, &r__2, &ix1, &iy1);
	    rjx = (real) (ix1 - ixr) / (real) inx;
	    rjy = (real) (iy1 - iyr) / (real) iny;
	    rammap_(iar, &inx, &iny, &inx, &iny, &ixr, &iyr, &rjx, &rjy);
	}

    }
    goto L1;

L110:
    fclose(input_file);
    return 0;
} /* replot_ */


int reget_(m1, m2, m3, mp, ilu)
integer *m1, *m2, *m3, *mp, *ilu;
{
    /* Local variables */
    static shortint m[128];

/* 	READ DATA FROM LONGLIB META-FILE PRINTER DATA FILE */

    *mp += 3;
    if (*mp > 128) {
	if (fread(&m[0],sizeof(shortint), 128, input_file) == 0) {
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
