
/* *** LAST REVISED ON 30-JAN-1994 03:54:50.84 */
/* *** SOURCE FILE: [LONGD]CXEXAMPLE.C */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "my.h"

#define MAXSIZE 7000
/* Table of constant values */
static integer c__0 = 0;
static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c_n2 = -2;
static integer c__3 = 3;
static integer c_n3 = -3;
static integer c__5 = 5;
static integer c__9 = 9;
static integer c__25 = 25;
static integer c__101 = 101;
static integer c_n101 = -101;
static real c_b7 = (float).33;
static real c_b8 = (float).78;
static real c_b9 = (float)1.;
static real c_b20 = (float).58;
static real c_b24 = (float)0.;
static real c_b25 = (float).5;
static real c_b101 = (float)-.12;
static real c_b102 = (float)1003.;
static real c_b113 = (float)90.;
static real c_b123 = (float)-.75;
static real c_b126 = (float).25;
static real c_b133 = (float)-.18;
static real c_b134 = (float).29;
static real c_b135 = (float).12;
static real c_b153 = (float)-.15;
static real c_b154 = (float)-.25;
static real c_b155 = (float).2;
static real c_b161 = (float)-.65;
static real c_b164 = (float).75;
static real c_b194 = (float)6.;
static real c_b255 = (float)250.;

int main()
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double sin();
    double r_nint();

    /* External Functions */
    extern /* Subroutine */ int rmwriteword_();
    extern /* Subroutine */ int rambox_();
    extern /* Subroutine */ int rect_();
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int axis3_();
    extern /* Subroutine */ int rmreadcursor_();
    extern /* Subroutine */ int frame_();
    extern /* Subroutine */ int cterm_(), rmdir_();
    extern /* Subroutine */ int rterm_(), rmpix_();
    extern /* Subroutine */ int rammap2_(),rmmode_(),number_(),plotnd_(),rmpixb_();
    extern /* Subroutine */ int rmwind_(), symbol_(), colortable_(), rmsize_();
    extern /* Subroutine */ int rplots_();
    extern /* Subroutine */ int editcolortable_();
    extern /* Subroutine */ int rmpause_(), rmstcol_(), rmstart_();
    extern integer irmchan_();

    /* Local variables */
    static real clen;
    static integer ncol, ival;
    static integer ient;
    static real argx, argy;
    static integer ierr;
    static real smin, xlen, smax;
    static integer illx, illy;
    static real ylen;
    static integer idrx;
    static real xval;
    static integer itrk, iurx, iury;
    static integer i, j, n, ichan;
    static real s;
    static real z;
    static integer ramid[4], index;
    static integer nxoff, nyoff;
    static real stval[70000];
    static real xsize, ysize, y1, af;
    static integer id;
    static real ds;
    static integer ix, iy, nx, ny;
    static shortint istval[MAXSIZE];
    static logical custom;
    static integer nn1, nn2, ix1, iy1;
    static real del, xhh, yhh,  xll;
    static real yll;
    static integer ixr, iyr;
    static real rjx, rjy;
    static integer nsx, nsy, nxspace, nyspace;
    static integer ixr1, iyr1;

    printf("Ramtek X Windows Demo Program\n");
    custom = 1;

/* 	CREATE A FLOATING POINT IMAGE */

    nsx = 256;
    nsy = 256;
    i__1 = nsx;
    for (i = 1; i <= i__1; ++i) {
	argx = ((i - 1) << 1) * (float)3.141592654 / (real) nsx;
	i__2 = nsy;
	for (j = 1; j <= i__2; ++j) {
	    index = i + (j - 1) * nsx;
	    argy = ((j - 1) << 1) * (float)3.141592654 / (real) nsy;
	    stval[index - 1] = sin(argx) * sin(argy);
	}
    }

/* 	SET MAX AND MIN PLOTTING VALUES */

    smin = (float)-1.;
    smax = (float)1.;

/* 	OPEN PLOT PACKAGE */

    if (! custom) {		/* 	CREATE STANDARD RAMTEK WINDOW SIZE */

	frame_(&c_n3, &c_n1, &c_b7, &c_b8, &c_b9);
    } else {			/* 	CREATE CUSTOM SIZED WINDOW */

	ramid[0] = 101;		/* RAMTEK DEVICE/WINDOW (101=CUSTOM) */
	ramid[1] = nsx + 50;	/* CUSTOM RAMTEK X DIMENSION IN PIXELS */
	ramid[2] = nsy + 120;	/* CUSTOM RAMTEK Y DIMENSION IN PIXELS */
	ramid[3] = 11;		/* WINDOW XWIDTH IN INCHES */
	printf("Creating Custom Ramtek Window: %d %d %d\n",ramid[1],ramid[2],ramid[3]);

/*	INITIALIZE RAMTEK DEVICE (BY DEFAULT, META AND TERMINAL PACKAGES ARE OFF)*/
	rplots_(ramid, &c_b7, &c_b20, &c_b9);
	printf("RAMTEK initialized\n");
    }
    cterm_(&c__1);

    ichan = irmchan_(&id);  /* 	GET CHANNEL AND/OR WINDOW NUMBER */
    if (ichan <= 0) {			       /* RAMTEK NOT OPENED */
	plotnd_();
	exit(-1);
    }

/* put small grey scale bar to test color map */
    for (i = 0; i < 255; i++) {
       j = i+1;
       rambox_(&ichan, &i, &c__9, &j, &c__25, &i);
    }

    rmstcol_(&ichan, &c__1, &ncol, &ierr);     /* STORE STANDARD COLOR TABLE */
    plot_(&c_b24, &c_b25, &c_n3);	       /* MOVE ORIGIN */

    rmsize_(&xsize, &ysize, &nx, &ny);	       /* GET SIZE OF DISPLAY IN INCHES AND PIXELS */
    printf("SIZE IN INCHES: %f %f\n",xsize,ysize);
    printf("MAX PIXEL:      %d %d\n",nx,ny);

    plot_(&c_b255, &c_b255, &c__0);
    rect_(&c_b9, &c_b9, &c_b194, &c_b194);

/* 	GET PIXEL TO INCH TRANSFORMATION INFO */
    rmpix_(&c_b24, &c_b24, &ixr, &iyr);
    printf("ORIGIN PIXEL:   %d %d\n",ixr,iyr);
    rmpix_(&c_b9, &c_b9, &ixr1, &iyr1);
    printf("UNIT POINT:     %d %d\n",ixr1,iyr1);
    ixr += (ixr1 - ixr > 0 ? 1 : -1);
    iyr += (iyr1 - iyr > 0 ? 1 : -1);
    nxspace = nx - ixr;
    if (ixr1 - ixr < 0) {
	nxspace = ixr;
    }
    nyspace = ny - iyr;
    if (iyr1 - iyr < 0) {
	nyspace = iyr;
    }
    printf("SIZE IN PIXELS:    %d %d\n",nxspace,nyspace);
    if (nxspace < nsx || nyspace < nsy) {
	printf("*** CAN NOT DISPLAY FULL IMAGE ***\n");
	nsx = nxspace;
	nsy = nyspace;
    }
    nxoff = ixr + (ixr1 - ixr > 0 ? nsx : - nsx);
    nyoff = iyr + (iyr1 - iyr > 0 ? nsy : - nsy);
    rmpixb_(&xsize, &ysize, &nxoff, &nyoff);
    nxoff -= (ixr1 - ixr >= 0 ? 1 : -1);
    nyoff -= (iyr1 - iyr >= 0 ? 1 : -1);
    iurx = nxoff;
    iury = iyr;
    illx = ixr;
    illy = nyoff;
    printf("LOWER-LEFT:     %d %d\n",illx,illy);
    printf("UPPER-RIGHT:    %d %d\n",iurx,iury);

    ds = smax - smin;
    if (ds == (float)0.) {
	ds = (float)1.;
    }
    ds = (float)1. / ds;

/* 	LOAD OUTPUT ARRAY WITH COLOR INDEXES */

    i__2 = nsy - 1;
    for (nn1 = 0; nn1 <= i__2; ++nn1) {
	i__1 = nsx - 1;
	for (nn2 = 0; nn2 <= i__1; ++nn2) {
	    index = nn1 * nsx + nn2 + 1;
	    z = stval[index - 1];
	    del = (z - smin) * ds;
	    if (del > (float)128.5) {
		del = (float)128.5;
	    }
	    if (del < (float)-128.5) {
		del = (float)-128.5;
	    }
	    r__1 = del * (ncol - 2);
	    ival = r_nint(&r__1) + 2;
	    if (ival > ncol - 2) {
		ival = ncol - 2;
	    }
	    if (ival < 1) {
		ival = 1;
	    }
	    istval[index - 1] = ival;
	}
    }

    printf("Begin Plotting\n");

/* 	DRAW IMAGE BOUNDARY */

    plot_(&c_b255, &c_b24, &c__0);
    rect_(&c_b24, &c_b24, &xsize, &ysize);
    plot_(&c_b24, &c_b24, &c__5);

/* 	NOW DISPLAY ARRAY USING RMWRITEWORD */

    rmwind_(&ichan, &illx, &illy, &iurx, &iury);
    rmdir_(&ichan, &c__2, &ierr);
    rmstart_(&ichan, &illx, &illy);
    i__2 = nsx * nsy;
    rmwriteword_(&ichan, istval, &i__2, &ierr);

/* 	ADD AXES */

    af = (real) (nsx / 32) + (float)1.01;
    xll = (float)0.;
    xhh = (real) nsx;
    xlen = xsize;
    axis3_(&c_b24, &c_b24, "X", &c_n1, &xlen, &c_b24, &xll, &xhh, &af, &
	    c_b101, &c_b102);
    axis3_(&c_b24, &ysize, "X", &c__101, &xlen, &c_b24, &xll, &xhh, &af, &
	    c_b101, &c_b102);

    af = (real) (nsy / 32) + (float)1.01;
    yll = (float)0.;
    yhh = (real) nsy;
    ylen = ysize;
    axis3_(&c_b24, &c_b24, "Y", &c__1, &ylen, &c_b113, &yll, &yhh, &af, &
	    c_b101, &c_b102);
    axis3_(&xsize, &c_b24, "Y", &c_n101, &ylen, &c_b113, &yll, &yhh, &af, &
	    c_b101, &c_b102);

/* 	GENERATE AND DISPLAY COLOR (GREYSCALE) BAR USING RAMMAP */

    i__2 = min(MAXSIZE,ncol - 1);
    for (i = 2; i <= i__2; ++i) {
	istval[i - 2] = i - 2;
    }
    clen = (float)3.;
    plot_(&c_b25, &c_b123, &c_n3);
    rmpix_(&c_b24, &c_b126, &ixr, &iyr);
    rmpix_(&clen, &c_b24, &ix1, &iy1);
    rjx = (i__2 = ix1 - ixr, (real) abs(i__2)) / (real) (i__2 - 2);
    rjy = (real) (iy1 - iyr);
    i__2 = min(MAXSIZE-2,ncol - 2);
    i__1 = min(MAXSIZE-2,ncol - 2);
    rammap2_(istval, &i__2, &c__1, &i__1, &c__1, &ixr, &iyr, &rjx, &rjy);
    plot_(&c_b9, &c_b9, &c__0);    
    idrx = rjx * (ncol - 2);
    i__2 = ixr + idrx;
    rmpixb_(&clen, &y1, &i__2, &iy1);
    rect_(&c_b24, &c_b24, &clen, &c_b126);

/* 	LABEL END OF BAR */
    
    number_(&c_b133, &c_b134, &c_b135, &smin, &c_b24, &c_b102, &c_n1);
    r__1 = clen - (float).18;
    number_(&r__1, &c_b134, &c_b135, &smax, &c_b24, &c_b102, &c_n1);
    del = smax - smin;
    n = 2;

/* 	LABEL INTERIOR POINTS OF BAR */

    i__2 = n - 1;
    for (i = 1; i <= i__2; ++i) {
	s = i * del / (real) n;
	xval = s * (float)3. / (smax - smin);
	plot_(&xval, &c_b24, &c__3);
	plot_(&xval, &c_b126, &c__2);
	r__1 = xval - (float).18;
	r__2 = s + smin;
	number_(&r__1, &c_b134, &c_b135, &r__2, &c_b24, &c_b102, &c_n1);
    }

/* 	ADD OTHER INFORMATION */

    symbol_(&c_b153, &c_b154, &c_b155, "BYU", &c_b24, &c__3, &c_n1);
    plot_(&c_b24, &c_b161, &c_n3);
    plot_(&c_b154, &c_b164, &c_n3);

    printf("Enter press return to continue\n");
    getc(stdin);

/* 	EVENT LOOP FOR OPTIONS */

    if (ichan != 99999) {		/* don't do this for REF library */
L4:
	printf("Type any key in focused window to exit program\n");
	printf("  Press right button to change color table\n"); 
	printf("  Press center button to edit color table\n");
	printf("  Press left button to focus and get position value\n");
L414:
	rmreadcursor_(&ichan, &c__0, &ix, &iy, &itrk, &c__0, &ient, &ierr);
	printf("got cursor event %d\n",ient);
	if (ient == 3) {		/* RIGHT BUTTON */
	    rmpause_(&ichan, &c__0);
	    printf("New Color Table:\n");
	    colortable_(&ichan, &ncol);
	    rmpause_(&ichan, &c__0);
	    goto L4;
	} else if (ient == 2) {		/* CENTER BUTTON */
	    rmpause_(&ichan, &c__0);
	    printf("Edit Color Table:\n");
	    editcolortable_(&ichan, &ncol);
	    rmpause_(&ichan, &c__0);
	    goto L4;
	} else if (ient == 1) {		/* LEFT (FOCUS) BUTTON */
	    if (ix - illx >= 0 && iury - iy >= 0 && ix - illx < nsx && iury - 
		    iy <= nsy) {
		i = (iury - iy) * nsx + (ix - illx) + 1;
		i__2 = ix - illx;
		i__1 = iury - iy;
		r__1 = istval[i - 1] / (real) ncol * (smax - smin) + smin;
		printf("Pix: (%4d,%4d) %3d Value:%f\n",i__2,i__1,istval[i-1],r__1);
	    }
	    goto L414;
	}
    } else {
	rmpause_(&ichan, &c__1);
	rterm_(&c_n2);
    }
    printf("end program\n");
    plotnd_();
} 

#include <stdio.h>

#define SCALE 7

/* Subroutine */ int colortable_(ichan, ncol)
integer *ichan, *ncol;
{
    integer i__1, i__2;
    integer ierr;
    char *p, cname[80];
    integer ired, iblue, igreen;
    FILE *cfile;
    extern /* Subroutine */ int rmwrcolind_();

    if (*ichan <= 0)
	return 0;

    printf("Color table file: (BLANK=NONE) ");
    p = fgets(cname,80,stdin);
    if (p != 0) {
       printf(" Reading from file: '%s'\n",cname);

       if (*ichan != 99999) {
	  if (*ncol > 256)
	     *ncol = 255;
	  cfile = fopen(cname,"r");
	  if (cfile == NULL) {
	     printf("Can't open input file\n");
	     goto L20;
	  }
	  fscanf(cfile,"%d",&i__1);
	  printf("File table entries: %d %d\n",i__1,*ncol);
	  if (i__1 > *ncol)
	     i__1 = *ncol;
	  for (i__2 = 0; i__2 < i__1; i__2++) {
	     fscanf(cfile,"%d %d %d",&ired, &igreen, &iblue);
	     printf("%d %d %d %d\n",i__2,ired,igreen,iblue);
	     ired   <<= SCALE;
	     if (ired < 0) ired = 0;
	     if (ired > 128*255) ired = 128*255;
	     igreen <<= SCALE;
	     if (igreen < 0) igreen = 0;
	     if (igreen > 128*255) igreen = 128*255;
	     iblue  <<= SCALE;
	     if (iblue < 0) iblue = 0;
	     if (iblue > 128*255) iblue = 128*255;
	     if (i__2 < *ncol - 4)
		rmwrcolind_(ichan, &ired, &igreen, &iblue, &i__2, &ierr);
	  }
	  fclose(cfile);
       }
    }
  L20:
    return 0;
} /* colortable_ */


/* Subroutine */ int editcolortable_(ichan, ncol)
integer *ichan, *ncol;
{
    extern integer ireadval1_();
    extern /* Subroutine */ int rmrdcolind_(), rmwrcolind_(), rmpause_();

    integer i__1, i__2, i__3;
    static integer index, ierr, iend;
    static integer i;
    static char cname[80];
    static int ired, iblue, igreen;

    FILE *cfile;

    if (*ichan <= 0)    /* no ramtek open */
	return 0;
    if (*ichan == 99999) /* ramtek = reflib */
	return 0;

    printf("Edit Color Table.  Max Num Colors=%d\n",*ncol);
    index = 0;
L10:
    rmpause_(ichan, &c__0);
    i__1 = index + 1;
    printf("Color Table Index Number: (-1=Save, 0=Exit) ");
    index = ireadval1_(i__1, &iend);
    if (index == -1) {
       printf("Enter output file name: ");
       scanf("%s",cname);
       cfile=fopen(cname,"w+t");
       if (cfile == NULL) {
	  printf("Can't Open file '%s'\n",cname);
	  goto L10;
       }
       i__1 = *ncol;
       fprintf(cfile,"%d\n",i__1);
       for (i = 1; i <= i__1; ++i) {
	  rmrdcolind_(ichan, &ired, &igreen, &iblue, &i, &ierr);
	  ired   <<= SCALE;
	  igreen <<= SCALE;
	  iblue  <<= SCALE;
	  fprintf(cfile,"%d %d %d\n",ired,igreen,iblue);
	}
	fclose(cfile);
	rmpause_(ichan, &c__0);
    }

    if (index <= 0)
	return 0;

    index = min(index,*ncol);

    rmrdcolind_(ichan, &ired, &igreen, &iblue, &index, &ierr);
    ired   >>= SCALE;
    igreen >>= SCALE;
    iblue  >>= SCALE;
    printf("Index->%4d  R:%3d  G:%3d  B:%3d\n",index,ired,igreen,iblue);

    rmpause_(ichan, &c__0);
    printf(" New Red   "); 
    i__3 = ireadval1_(ired, &iend);
    i__1 = *ncol;
    i__2 = max(i__3,0);
    ired = min(i__1,i__2);
    rmpause_(ichan, &c__0);

    printf(" New Green "); 
    i__3 = ireadval1_(igreen, &iend);
    i__1 = *ncol;
    i__2 = max(i__3,0);
    igreen = min(i__1,i__2);
    rmpause_(ichan, &c__0);

    printf(" New Blue  ");
    i__3 = ireadval1_(iblue, &iend);
    i__1 = *ncol;
    i__2 = max(i__3,0);
    iblue = min(i__1,i__2);
    rmpause_(ichan, &c__0);

    printf("Index->%4d  R:%3d  G:%3d  B:%3d\n",index,ired,igreen,iblue);
    ired   <<= SCALE;
    igreen <<= SCALE;
    iblue  <<= SCALE;
    rmwrcolind_(ichan, &ired, &igreen, &iblue, &index, &ierr);

    rmrdcolind_(ichan, &ired, &igreen, &iblue, &index, &ierr);
    ired   >>= SCALE;
    igreen >>= SCALE;
    iblue  >>= SCALE;
    printf("Index->%4d  R:%3d  G:%3d  B:%3d\n",index,ired,igreen,iblue);

    goto L10;

} /* editcolortable_ */


integer ireadval1_(integer val, integer *end)
{
   char *p, s[80];
   integer i;
      
   *end = 0;
   printf("[%d] ",val);
   p = fgets(s,80,stdin);

   if (*p != 0) {
      if (isdigit(s[0]) || s[0] == '.' || s[0] == '-')
	 i = atoi(s);
      else
	 i = val;
   } else {
      i = val;
   }
   return(i);
}
