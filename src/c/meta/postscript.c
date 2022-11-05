
/* *** LAST REVISED ON  1-FEB-1994 11:25:01.27 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.META]POSTSCRIPT.C */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../my.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c__2 = 2;
static integer c__1 = 1;
static integer c__128 = 128;

FILE *input_file, *output_file;

int main(argc,argv)
int argc; char **argv;
{
    /* Local variables */
    static char name[80];
    static integer ierr, iflag;
    extern int lplot_();

/* 	CREATED: DGL 6 JAN 1994 */

/* 	THIS PROGRAM CONVERTS THE LONGLIB METAFILE */
/* 	PRODUCED BY THE LONGLIB GRAPHICS LIBRARY */
/* 	TO THE POSTSCRIPT LANGUAGE. */

    if (*++argv) {
	strcpy(name,*argv);
    } else {
	strcpy(name,"3.dat");
    };
    lplot_(name);
}


int lplot_(name)	/* MAIN ROUTINE TO CONVERT PRINTER GRAPHICS FILE TO POSTSCRIPT */
char *name;
{
/* 	DEFINITIONS FOR LINE TYPES */
    static char linetype[13*10+1] = "[]           [2]          [4 4]        \
[4 7]        [2 2]        [2 2 2 2 4]  [6 2 3 2 4]  [1 1]        [1 1 4 4]  \
  [1 1 2 2 3 3]";

    integer i__1;

    /* Local variables */
    static integer iold, i;
    extern int reget_();
    static integer jpcnt, ixold, iyold;
    extern int hexit_();
    static integer penup, i3, m1, m2, m3;
    static real x1, y1;
    static integer ic, lc, mp, lt, ix, iy, lw, kx, ky;
    static real sx, sy, amx, amy;
    static integer jps, inx, iny, num;
    extern integer idigits_();

    float temp;
    char str[128];

/* 	INITIALIZE VARIABLES */
    lw = -1;		/* LINE WIDTH (INVALID TO FORCE NEW WIDTH) */
    lt = -1;		/* LINE TYPE (INVALID TO FORCE NEW TYPE) */
    lc = -1;		/* LINE COLOR (INVALID TO FORCE NEW TYPE) */
    amx = (float)288.;
    amy = (float)288.;
    mp = 999;
    ixold = 0;
    iyold = 0;

/* PENUP IS PEN CONTROL FLAG (0=NO SEGMENT, 2=PEN UP, 3=PEN DOWN) */
    penup = 0;
    jpcnt = 0;

/* OPEN INPUT FILE PRODUCED BY LONGLIB GRAPHICS LIBRARY */
    input_file = fopen(name,"r");
    if (input_file == NULL) {
	printf("*** Error opening input file '%s' ***\n",name);
	return 0;
    }

/* OPEN OUTPUT FILE */
    output_file = fopen("out.lis","w");
    if (output_file == NULL) {
	printf("*** Error opening output file 'out.lis' ***\n");
	return 0;
    }

/* SEND INITIALIZATION CODES TO OUTPUT FILE */
    fprintf(output_file,"%%!PS-Adobe-2.0\n");
    fprintf(output_file,"%%Title: PostScript for C LongLib\n");
    fprintf(output_file,"%%Creator: D. Long VAX VMS C (POSTSCRIPT)\n");
    fprintf(output_file,"%%Creation Date: Mon Aug 27, 1990\n");
    fprintf(output_file,"%%Pages: (atend) 1\n");
    fprintf(output_file,"%%EndComments\n");
    fprintf(output_file,"%% Function definitions to reduce filesize\n");
    fprintf(output_file,"/g { grestore showpage } bind def\n");
    fprintf(output_file,"/l { lineto } bind def\n");
    fprintf(output_file,"/m { moveto } bind def\n");
    fprintf(output_file,"/s { moveto closepath stroke } bind def\n");
    fprintf(output_file,"/n { newpath } bind def\n");
    fprintf(output_file,"/i { image grestore } bind def\n");
    fprintf(output_file,"/d { setdash } bind def\n");
    fprintf(output_file,"%%Page:1 1\n");

    fprintf(output_file,"1 setlinejoin\n");	/* LINE JOIN TYPE */
    fprintf(output_file,"0 setlinecap\n");	/* LINE END CAP */
    fprintf(output_file,"[] 0 setdash\n");	/* SOLID LINE */
    fprintf(output_file,"0 setlinewidth\n");	/* SINGLE LINE WIDTH */
    fprintf(output_file,"0 setgray\n");		/* BLACK LINE */
    fprintf(output_file,"0.25 0.25 scale\n");	/* SCALE TO 288 DOTS/INCH */
    fprintf(output_file,"gsave\n");

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
L20:	/* 	"CALL PLOT(X1,Y1,I3)" */

/* 	CONVERT TO INTEGER 0.25/72'S INCH */

    ix = (integer) (y1 * 288 + (float).5) + 5;
    iy = 3120 - (integer) (x1 * 288 + (float).5);
    if (iy < 0)
	iy = 0;

    if (i3 == 3) {		/* 	PEN UP MOVE */

	if (penup == 2) {
	    kx = idigits_(&ixold);
	    ky = idigits_(&iyold);
	    sprintf(str,"%%%dd %%%dd s\n",kx,ky);
	    fprintf(output_file,str,ixold,iyold);
	}
	penup = 3;
	jpcnt = 0;
    } else {			/* 	PEN DOWN MOVE */
	if (penup == 3) {
	    kx = idigits_(&ixold);
	    ky = idigits_(&iyold);
	    sprintf(str,"n %%%dd %%%dd m\n",kx,ky);
	    fprintf(output_file,str,ixold,iyold);
	    jpcnt = 0;
	}
	penup = 2;
	kx = idigits_(&ix);
	ky = idigits_(&iy);

/* 	OUTPUT LINE CONTINUATION.  IF # POINTS EXCEEDS 256, OUTPUT */
/* 	ALSO, DON'T OUTPUT REDUNDANT POINTS */

	if (jpcnt > 256) {
	    sprintf(str,"%%%dd %%%dd s\n",kx,ky);
	    fprintf(output_file,str,ix,iy);
	    sprintf(str,"n %%%dd %%%dd m\n",kx,ky);
	    fprintf(output_file,str,ix,iy);
	    jpcnt = 0;
	} else {
	    if (jpcnt == 0 || (ix != ixold || iy != iyold)) {
		sprintf(str,"%%%dd %%%dd l\n",kx,ky);
		fprintf(output_file,str,ix,iy);
		++jpcnt;
	    }
	}
    }
    ixold = ix;
    iyold = iy;
    goto L1;

L100:			/* 	"CALL NEWPAGE" */

    if (penup == 2) {
	kx = idigits_(&ixold);
	ky = idigits_(&iyold);
	sprintf(str,"n %%%dd %%%dd m\n",kx,ky);
	fprintf(output_file,str,ixold,iyold);
	penup = 0;
	jpcnt = 0;
    }
    ++jps;
    fprintf(output_file,"g\n");
    fprintf(output_file,"%%Page:  %2d %2d\n",jps,jps);
    fprintf(output_file,"0.25 0.25 scale\n");
    fprintf(output_file,"gsave\n");

    strncpy(str,linetype + lt * 13, 13);
    fprintf(output_file,"%s 0 d\n",str);

    i__1 = lw - 1;
    fprintf(output_file,"%2d setlinewidth\n",i__1);
    goto L1;


L999:				/* 	SPECIAL COMMANDS */
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
	    kx = idigits_(&ixold);
	    ky = idigits_(&iyold);
	    sprintf(str,"n %%%dd %%%dd s\n",kx,ky);
	    fprintf(output_file,str,ixold,iyold);
	    penup = 0;
	}

	strncpy(str,linetype + m1 * 13, 13);
	fprintf(output_file,"%s 0 d\n",str);
	lt = m1;
    }
    goto L1;

/* 	LINE COLOR */
L1002:				/* 	"CALL PLOT(FLOAT(M2),0.,0)" */
/* 	INCLUDE PEN COLOR AS GRAY SCALE (0-16) BLACK=16, WHITE=0 */

    if (m2 != lc) {		
	temp = ((float) m2 - 1.0) / 16.0;
/*	fprintf(output_file,"%f setgray\n",temp); */
    }
    lc = m2;
    goto L1;

/* 	LINEWIDTH */
L1003:				/* 	"CALL NEWPEN(I3)" */
    if (m1 <= 0) {
	m1 = 1;
    }

/* 	NOTE: THE LINEWIDTH IS GRAPHICS DEVICE DEPENDENT AND MAY VARY */
/* 	DEPENDING ON LINE ORIENTATION */

    if (m1 != lw) {
	if (penup == 2) {
	    kx = idigits_(&ixold);
	    ky = idigits_(&iyold);
	    sprintf(str,"n %%%dd %%%dd s\n",kx,ky);
	    fprintf(output_file,str,ixold,iyold);
	    penup = 0;
	}

/* 	NEW LINE WIDTH */
	i__1 = m1 - 1;
	fprintf(output_file,"%2d setlinewidth\n",i__1);
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
	/* iy = iyold - i_nint(&amy); */
	iy = iyold - (int) amy;
	i__1 = -inx;
	fprintf(output_file,"gsave %4d %4d translate %f %f scale %4d %4d 8 [%4d 0 0 %4d 0 %4d] {<",ixold,iy,amx,amy,iny,inx,iny,i__1,inx);

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
	}
	if (ic > 0) {
	    i__1 = -ic;
	    hexit_(&m1, &m2, &i__1);
	}
	fprintf(output_file," >} i\n");
    }
    goto L1;

/* 	CLOSE INPUT FILE */

L110:
    fclose(input_file);

    if (penup == 2) {
	kx = idigits_(&ixold);
	ky = idigits_(&iyold);
	sprintf(str,"n %%%dd %%%dd s\n",kx,ky);
	fprintf(output_file,str,ixold,iyold);
	penup = 0;
    }

    fprintf(output_file," g\n");
    fprintf(output_file,"%%Trailer\n");
    fprintf(output_file,"%%Pages %2d 1\n",jps);

/* 	CLOSE OUTPUT FILE */

    fclose(output_file);
/* L99: */
    return 0;
} /* lplot_ */


int reget_(m1, m2, m3, mp, ilu)
integer *m1, *m2, *m3, *mp, *ilu;
{
    /* System generated locals */
    integer i__1;

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
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer icnt, c[38];

    if (*ic == 0) {
	icnt = 1;
    }
    if (*ic < 0) {			/* DUMP OUTPUT BUFFER */
	if (icnt > 1) {
	    i__1 = icnt - 1;
	    for (*i = 1; *i <= i__1; ++(*i)) {
		fprintf(output_file,"%2X", &c[*i - 1]);
	    }
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
	for (*i = 1; *i <= 38; ++(*i)) {
		fprintf(output_file,"%2X", &c[*i - 1]);
	}
	icnt = 1;
    }
L100:
    return 0;
} /* hexit_ */

integer i_nint(r) real *r;
{
	integer ret_val = *r;
	if (ret_val - *r > 0.5) ret_val--;
	if (*r - ret_val > 0.5) ret_val++;
	return ret_val;
}
