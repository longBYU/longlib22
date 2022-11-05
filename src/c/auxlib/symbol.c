
/* *** LAST REVISED ON 26-DEC-1993 02:05:47.97 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]SYMBOL.C */

#include "my.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__6 = 6;
static integer c__12 = 12;

/* *********************************************************************** */
/* 	MACHINE DEPENDENT NOTES: */
/* 		1. THE FUNCTION IBITS_(I,J,K) RETURNS THE VALUE OF THE BITS */
/* 		   IN I STARTING AT J FOR K BITS. */
/* *********************************************************************** */

/* Subroutine */ int symbol_(x, y, s, t, a, nn, is)
real *x, *y, *s;
char *t;
real *a;
integer *nn, *is;
{
    /* Initialized data */

    static struct {
	shortint e_1[968];
	} equiv_1 = { 6186, 6826, 6806, 5526, 5546, 6186, 2080, 6176, 10282, 
		10538, 10916, 10908, 10518, 10006, 9628, 9636, 5930, 2090, 
		6176, 6186, 6747, 5595, 2090, 6186, 6816, 6166, 5536, 6186, 
		2080, 6176, 6688, 5672, 5656, 2592, 6501, 6491, 5851, 5861, 
		14693, 5546, 14053, 5526, 14043, 6806, 14683, 6176, 2730, 
		6166, 14378, 5536, 2720, 5721, 14823, 5735, 2521, 5536, 15008,
		 6166, 14378, 5721, 14823, 6617, 1639, 5735, 6176, 14358, 
		6176, 2535, 6166, 6186, 6816, 5536, 2090, 5526, 6826, 5546, 
		2710, 13844, 5672, 6696, 5656, 14872, 5920, 2336, 13612, 5672,
		 6680, 6696, 1560, 6176, 14872, 6696, 6176, 1568, 5672, 6696, 
		5656, 6680, 1576, 6176, 6680, 6696, 5656, 5672, 2080, 6176, 
		6186, 6747, 5595, 14378, 6757, 6166, 5605, 2661, 15124, 6696, 
		5672, 6680, 13848, 6432, 1824, 6696, 6680, 5672, 5656, 14888, 
		6180, 2075, 5656, 6696, 5672, 6680, 13848, 6432, 1824, 5536, 
		6186, 6816, 6166, 5536, 15008, 6186, 2070, 5656, 5672, 6696, 
		6680, 5656, 14888, 5672, 2584, 6176, 5928, 6440, 6176, 6688, 
		6424, 6176, 5912, 5664, 2080, 10204, 10077, 10015, 10017, 
		10083, 10212, 10340, 10467, 10529, 10527, 10461, 10332, 14300,
		5983, 5985, 14177, 6046, 14242, 6109, 14307, 6173, 14371, 
		6237, 14435, 6302, 14498, 6367, 2273, 5916, 5924, 6436, 6428, 
		14108, 5981, 14179, 6045, 14243, 6109, 14307, 6173, 14371, 
		6237, 14435, 6301, 14499, 6365, 2275, 6170, 5859, 6499, 14362,
		5986, 6173, 14562, 6176, 6114, 6176, 2146, 10273, 10208, 
		10271, 10336, 2081, 10204, 10077, 10015, 10017, 10083, 10212, 
		10340, 10467, 10529, 10527, 10461, 10332, 2012, 10133, 9942, 
		9752, 9627, 9566, 9570, 9637, 9768, 9962, 10155, 10411, 10602,
		10792, 10917, 10978, 10974, 10907, 10776, 10582, 10389, 1941,
		10122, 9803, 9549, 9359, 9170, 9045, 8921, 8862, 8866, 8935, 
		9067, 9198, 9393, 9587, 9845, 10166, 10422, 10741, 10995, 
		11185, 11374, 11499, 11623, 11682, 11678, 11609, 11477, 11346,
		11151, 10957, 10699, 10378, 1930, 6186, 5527, 6743, 2090, 
		1931, 9163, 9355, 9359, 9167, 13259, 5138, 5088, 5280, 1042, 
		5081, 13280, 5472, 1369, 5067, 13280, 5472, 13643, 4825, 
		13913, 5714, 722, 4815, 9551, 9810, 9557, 9173, 4825, 5084, 
		13916, 5280, 1163, 4815, 13916, 9180, 8924, 8928, 9184, 13276,
		9803, 9547, 9551, 9807, 1611, 9810, 9355, 9163, 8911, 8914, 
		9561, 9564, 9376, 9180, 9173, 1611, 9177, 9372, 1184, 9568, 
		9177, 9170, 1355, 9184, 9561, 9554, 971, 5263, 13468, 5721, 
		13010, 4825, 1618, 5263, 13468, 4821, 1621, 8905, 9165, 975, 
		4821, 1621, 5068, 971, 4811, 1632, 8911, 8924, 9184, 9568, 
		5724, 9807, 9547, 5067, 4815, 1628, 5067, 13643, 5259, 5280, 
		988, 8924, 9184, 9568, 9820, 9817, 4815, 4811, 1611, 4832, 
		9824, 5724, 9365, 9557, 9810, 9807, 9547, 9163, 719, 5451, 
		5472, 4821, 4818, 1618, 8911, 9163, 9547, 9807, 9813, 5465, 
		4825, 4832, 1632, 8917, 9557, 9810, 9807, 9547, 9163, 8911, 
		8921, 9376, 1632, 4832, 5728, 9820, 9170, 971, 9163, 9547, 
		9807, 9810, 9557, 9173, 8921, 8924, 9184, 9568, 9820, 9817, 
		13653, 9173, 8914, 8911, 971, 8907, 9355, 9810, 9820, 9568, 
		9184, 8924, 8921, 9173, 1621, 5068, 13259, 5073, 978, 13003, 
		9163, 9359, 13458, 5272, 1177, 5451, 4821, 1376, 4818, 13906, 
		5721, 729, 13003, 5067, 5717, 992, 5260, 13451, 9362, 9817, 
		9820, 9568, 9184, 732, 9547, 9163, 8911, 8924, 9184, 9568, 
		9820, 9810, 9362, 9365, 1628, 4811, 8921, 5280, 5721, 13899, 
		4818, 1618, 4811, 4832, 9568, 9820, 5721, 5461, 13013, 9557, 
		9810, 5711, 5451, 715, 9820, 9568, 9184, 8924, 8911, 9163, 
		9547, 1615, 4811, 9547, 9807, 5724, 5472, 13024, 5088, 971, 
		4811, 4832, 13920, 5461, 13013, 4811, 1611, 4811, 4832, 13920,
		5269, 725, 9820, 9568, 9184, 8924, 8911, 9163, 5707, 5714, 
		1362, 4811, 13024, 4821, 13909, 5728, 1611, 5067, 13643, 5259,
		13472, 5088, 1376, 8911, 9163, 5451, 5711, 1632, 4811, 13024,
		5728, 4821, 1611, 4832, 4811, 1611, 4811, 4832, 5269, 5728, 
		1611, 4811, 13024, 4828, 13903, 5728, 1611, 8911, 9163, 9547, 
		9807, 9820, 9568, 9184, 8924, 719, 4811, 4832, 9568, 9820, 
		5721, 5461, 725, 8911, 9163, 9547, 9807, 9820, 9568, 9184, 
		8924, 13007, 5266, 1611, 4811, 4832, 9568, 9820, 5721, 5461, 
		13013, 5269, 1611, 8911, 9163, 9547, 9807, 9810, 9557, 9173, 
		8921, 8924, 9184, 9568, 1628, 4832, 13920, 5280, 1163, 4832, 
		8911, 9163, 5451, 5711, 1632, 4832, 5259, 1632, 4832, 5067, 
		5269, 5451, 1632, 4811, 4815, 5724, 13920, 4832, 4828, 5711, 
		1611, 4832, 4828, 5269, 13451, 5728, 5724, 1173, 4832, 5728, 
		5724, 4815, 4811, 1611, 5280, 4832, 4811, 1163, 5707, 736, 
		4811, 5259, 5280, 736, 4821, 5276, 13909, 5276, 1167, 5263, 
		4821, 13468, 4821, 1621, 4832, 1365, 8911, 8917, 9177, 9369, 
		9810, 9355, 9163, 13007, 5721, 1611, 4811, 13024, 8914, 9369, 
		9561, 9813, 9807, 9547, 9355, 722, 5721, 9177, 8917, 4815, 
		5067, 1611, 5728, 13899, 9810, 9369, 9177, 8917, 8911, 9163, 
		9355, 1618, 4818, 9810, 9813, 9561, 9177, 8917, 8911, 9163, 
		1355, 5259, 5276, 13664, 5077, 1365, 9156, 5444, 5704, 13913, 
		9810, 9369, 9177, 8917, 8911, 9163, 9355, 1618, 4811, 13024, 
		8921, 5465, 5717, 1611, 5067, 13643, 5259, 5269, 13269, 5275, 
		1180, 5061, 5253, 5449, 13657, 5471, 1376, 4811, 13024, 5724, 
		13007, 5269, 1611, 5067, 13643, 5259, 5280, 992, 4811, 13017, 
		8917, 5081, 5269, 13451, 9365, 5465, 5717, 1611, 4811, 13017, 
		8917, 9177, 5465, 5717, 1611, 8911, 8917, 9177, 9561, 9813, 
		9807, 9547, 9163, 719, 4804, 13017, 8914, 9369, 9561, 9813, 
		9807, 9547, 9355, 722, 5700, 13913, 9810, 9369, 9177, 8917, 
		8911, 9163, 9355, 1618, 4811, 13017, 8914, 5273, 1625, 8907, 
		9547, 9807, 9554, 9170, 8917, 9177, 1625, 5081, 13657, 5280, 
		5263, 1355, 4825, 8911, 9163, 9547, 13903, 5721, 1611, 4825, 
		5259, 1625, 4825, 5067, 5266, 5451, 1625, 4811, 13913, 4825, 
		1611, 9156, 5444, 5704, 13913, 4825, 8911, 9163, 1611, 4825, 
		5721, 4811, 1611, 5259, 5007, 5075, 4885, 5080, 5020, 1184, 
		5259, 13458, 5273, 1184, 5067, 5327, 5267, 5461, 5272, 5340, 
		992, 4819, 5079, 5459, 1623, 131, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static struct {
	shortint e_1[176];
	} equiv_2 = { 1, 8, 19, 24, 30, 35, 48, 52, 56, 64, 69, 74, 78, 85, 
		90, 95, 100, 106, 115, 122, 129, 136, 144, 152, 162, 190, 209,
		220, 225, 238, 259, 292, 296, 297, 306, 310, 318, 328, 340, 
		351, 354, 358, 362, 368, 372, 375, 377, 379, 381, 391, 396, 
		404, 414, 419, 428, 438, 443, 460, 470, 474, 480, 483, 487, 
		491, 499, 510, 517, 529, 537, 545, 552, 557, 566, 572, 578, 
		583, 588, 591, 596, 602, 611, 618, 629, 638, 650, 654, 660, 
		663, 668, 676, 683, 689, 693, 695, 699, 704, 709, 711, 721, 
		731, 737, 747, 756, 761, 773, 779, 786, 792, 798, 803, 813, 
		820, 829, 839, 849, 854, 862, 867, 874, 877, 882, 886, 894, 
		898, 905, 909, 916, 920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    /* Builtin functions */
    double sin(), cos();

    /* External functions */
    extern integer ibits_();
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static integer ipen;
#define ifnt ((shortint *)&equiv_1)
#define ipnt ((shortint *)&equiv_2)
    static real oldx, oldy;
    static integer ipenlast;
    static integer i, n;
    static integer ixoff, iyoff;
    static real x0, x1, y1, y0, aa, al, co;
    static integer il, ip;
    static real si;
    static integer iw, ix, iy;
    static real ss, ox, oy, xx;
    static logical length;
    static integer icc, iss;

/* 	ROUTINE TO PLOT CHARACTERS AND SYMBOLS */

/* 	WRITTEN BY:	D. LONG  JAN 1991   BYU */

/* 	X,Y   (R): string position */
/* 	           If x>998 or y>998 then plotting of the string is continued */
/* 		   from the last SYMBOL call */
/* 	S     (R): height of the string to be printed */
/* 	T     (C): character variable containing the ascii text to be plotted */
/* 	A     (R): angle at which the string is to be plotted */
/* 		   counter-clockwise from x axis */
/* 	N     (I): number of characters to use from T */
/* 		   note: plotting will terminate if an ASCII zero is */
/* 		   encountered at any other position than the first character. */
/*                 If N<0, a plot(x,y,2) will be executed prior to plotting*/
/* 		   the first character and ABS(N) characters will be plotted. */
/* 		   For N<2, the plot pen is left at the 1st character origin */
/* 		   point; otherwise it is at the end of the last plotted */
/* 		   vector in the last plotted character. */
/* 	IS    (I): centering option flag */
/* 			= -3 end coordinates of string (if it were to  be */
/*                           plotted will be returned in x,y where the input*/
/* 			     (x,y) are the lower left corner of string.  This */
/* 			     permits computation of the plotted length. */
/* 			     However, no plotting is done and the last position */
/*                            variables are not changed. */
/* 			= -2 end coordinates of string are returned in x,y. */
/* 			     Inital (x,y) to be lower left corner of plotted */
/*                            string.  String is plotted. */
/* 			= -1 (x,y) to be lower left corner of plotted string */
/*                            (x and y not altered)  String is plotted. */

/* 			= 0  (x,y) to be center of plotted string */
/*                            (x and y not altered)  String is plotted. */

/*                      = 1  (x,y) to be lower right corner of plotted string*/
/*                            (x and y not altered)  String is plotted. */

/*SYMBOL plots an ASCII string in a CHARACTER array.  Each character (or string*/
/*of characters) can be imagined as a square box with the origin at the lower*/
/* left corner.  The routine determines the initial position of the lower */
/* left of the first character than plots each character relative to this */
/* position.  As each character is plotted the "current position" is moved */
/* to the right (along the string baseline) a fixed amount S.  When the */
/*string centering option is selected, the length of the plotted string is*/
/* determined and, based on the character height, the lower left corner is */
/*computed from the input (x,y) position.  The special plot symbols (ASCII */
/* 0-31) are always centered about the current position. */

/* ********************************************************************** */

    n = *nn;					/* NUMBER OF CHARACTERS */
    aa = *a;					/* PLOTTING ANGLE */
    si = sin(aa * (float).0174532);
    co = cos(aa * (float).0174532);
    length = TRUE_;				/* PLOT (TRUE) OR LENGTH ONLY */
    al = (float)0.;				/* PLOTTED LENGTH */
    iss = *is;					/* CENTERING FLAG */
    if (iss == -3)
	length = FALSE_;
    if (iss > -1)
	length = FALSE_;
    ox = oldx;					/* SAVE CURRENT POSITION */
    oy = oldy;
L1100:			/* TOP OF LENGTH COMPUTATION */
    al = (float)0.;		/* LENGTH OF PLOTTED STRING ACCUMULATOR */
    x1 = *x;					/* LOWER LEFT CORNER */
    y1 = *y;
    if (iss == 0) {				/* CENTERED */
	x1 = *x - al / (float)2. * co + *s / (float)2. * si;
	y1 = *y - *s / (float)2. * co - al / (float)2. * si;
    }
    if (iss == 1) {				/* LOWER RIGHT CORNER */
	x1 = *x - al * co;
	y1 = *y - al * si;
    }
    if (*x > (float)998. || *y > (float)998.) {
	if (*x < (float)998.)
	    oldx += x1;
	if (*y < (float)998.)
	    oldy += y1;
    } else {
	oldx = x1;
	oldy = y1;
    }
    x0 = oldx;
    y0 = oldy;
    if (length && n < 0)		/* PLOT TO START */
	plot_(&oldx, &oldy, &c__2);
    ss = *s / (float)21.;		/* SCALE FACTOR */
    i = 0;				/* CHARACTER COUNTER */
L50:
    ++i;
    if (i > abs(n))			/* END OF STRING COUNT */
	goto L1000;
    icc = t[i - 1];			/* GET ITH ASCII CHARACTER */
    if (icc > 127)			/* CODE TOO LARGE */
	goto L50;
    if (icc == 0 && i > 1) 		/* END OF STRING REACHED */
	goto L1000;
    ixoff = 11;				/* OFFSET */
    iyoff = 11;
    if (icc < 32) {			/* DIFFERENT SYMBOL OFFSET */
	ixoff = 32;
	iyoff = 32;
    }
    il = ipnt[icc];			/* STARTING INDEX */
    iw = 21;				/* CHARACTER WIDTH */
    if (il == 0) {			/* NO PLOTING INFO */
	goto L90;
    }
    ipenlast = 3;
L70:
    iy = ibits_(&ifnt[il - 1], &c__0, &c__6);
    ix = ibits_(&ifnt[il - 1], &c__6, &c__6);
    ipen = ibits_(&ifnt[il - 1], &c__12, &c__2);
    ip = ipenlast;
    ipenlast = ipen;
    xx = ss * (ix - ixoff);
    y1 = ss * (iy - iyoff);
    x1 = xx * co - y1 * si + oldx;
    y1 = xx * si + y1 * co + oldy;
    if (ip == 0)
	ip = 2;
    if (ip == 1)
	ip = 2;
    if (length)
	plot_(&x1, &y1, &ip);
    ++il;
    if (ipen != 0)
	goto L70;
L90:
    xx = ss * iw;				/* END OF CHARACTER */
    al += ss * iw;
    oldx = xx * co + oldx;
    oldy = xx * si + oldy;
/* L100: */
    goto L50;
L1000:
    if (! length) {				/* FINISHED LENGTH-ONLY PASS */
	length = TRUE_;
	if (iss == -3) {			/* RETURN END POSITION */
	    *x = oldx;
	    *y = oldy;
	}
	oldx = ox;				/* RESTORE OLD POSITION */
	oldy = oy;
/* L1003: */
	if (iss == 0 || iss == 1)
	    goto L1100;

    } else {
	if (n <= 1) {				/* LEAVE PEN AT START */
	    plot_(&x0, &y0, &c__3);
	}
	if (iss == -2) {			/* RETURN END POSITION */
	    *x = oldx;
	    *y = oldy;
	}
    }
    return 0;
} /* symbol_ */

#undef ipnt
#undef ifnt







