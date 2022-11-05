
#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__0 = 0;
static real c_b3 = (float)4.;
static real c_b4 = (float)3.;
static real c_b6 = (float)-1.;
static real c_b8 = (float).2;
static real c_b10 = (float)0.;
static integer c__7 = 7;
static integer c_n1 = -1;
static real c_b16 = (float)14.;
static real c_b17 = (float)13.;
static real c_b18 = (float)12.;
static real c_b23 = (float)15.;
static real c_b24 = (float)1.;
static integer c__1 = 1;
static integer c__2 = 2;
static real c_b34 = (float).1;
static real c_b56 = (float).23;
static integer c__6 = 6;
static real c_b106 = (float)90.;
static real c_b124 = (float)180.;
static real c_b131 = (float)-90.;
static real c_b147 = (float).5;
static real c_b150 = (float)30.;
static real c_b153 = (float)3.14159;
static real c_b158 = (float)40.;
static real c_b187 = (float)3.0302;
static real c_b188 = (float).15;
static real c_b189 = (float)1002.;
static real c_b199 = (float)3.03;
static real c_b211 = (float)3.04;


int main()
{

    /* Local variables */
    static real amin, amax;
    extern /* Subroutine */ int plot_(), num3d_(), sym3d_();
    static real x, y;
    extern /* Subroutine */ int frame_(), cterm_(), init3d_(), axis3d_(), 
	    plot3d_(), plotnd_(), symbol_(), where3d_(), newpage_();

/*       EXAMPLE SHOWING THE USE OF THE 3D PLOTTING PACKAGE IN LONGLIB */

/*      OPEN PLOT PACKAGE WITH SCREEN PROMPT AND A HISTORY FILE*/

    frame_(&c__3, &c__0, &c_b3, &c_b4, &c_b4);
    symbol_(&c_b6, &c_b6, &c_b8, "EXAMP3D", &c_b10, &c__7, &c_n1, 7L);
    plot_(&c_b10, &c_b10, &c__3);

/*       INITIALIZE THE 3D (NO HIDDEN LINE REMOVAL) PACKAGE */

    init3d_(&c_b16, &c_b17, &c_b18, &c_b10, &c_b10, &c_b10, &c_b10, &c_b23, &
	    c_b24, &c__1);

/*       PLOT SOME AXIS LINES AS EXAMPLES */

    plot3d_(&c_b10, &c_b10, &c_b10, &c__3);
    plot3d_(&c_b24, &c_b10, &c_b10, &c__2);

/*       USE 2-D LABELING ON END OF AXIS */

/*       FIRST GET SCREEN COORDINATES AND ADD 2-D LABEL THEN */
/*       PUT ON 3D LABEL */

    where3d_(&x, &y);
    symbol_(&x, &y, &c_b34, "X", &c_b10, &c__1, &c_n1, 1L);
    sym3d_(&c_b24, &c_b10, &c_b10, &c_b10, &c_b10, &c_b10, &c_b8, "X", &c__1, 
	    1L);

    plot3d_(&c_b10, &c_b10, &c_b10, &c__3);
    plot3d_(&c_b10, &c_b24, &c_b10, &c__2);
    where3d_(&x, &y);
    symbol_(&x, &y, &c_b56, "Y", &c_b10, &c__1, &c_n1, 1L);
    sym3d_(&c_b10, &c_b24, &c_b10, &c_b10, &c_b10, &c_b10, &c_b8, "Y", &c__1, 
	    1L);

    plot3d_(&c_b10, &c_b10, &c_b10, &c__3);
    plot3d_(&c_b10, &c_b10, &c_b24, &c__2);
    where3d_(&x, &y);
    symbol_(&x, &y, &c_b56, "Z", &c_b10, &c__1, &c_n1, 1L);
    sym3d_(&c_b10, &c_b10, &c_b24, &c_b10, &c_b10, &c_b10, &c_b8, "Z", &c__1, 
	    1L);

/*       ADD FANCY LABELS */

    sym3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b10, &c_b10, &c_b8, "x axis", &
	    c__6, 6L);
    sym3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b10, &c_b106, &c_b8, "x2 axis", 
	    &c__7, 7L);
    sym3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b106, &c_b10, &c_b8, "y axis", &
	    c__6, 6L);
    sym3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b106, &c_b124, &c_b8, "y2 axis",
	     &c__7, 7L);
    sym3d_(&c_b10, &c_b10, &c_b10, &c_b131, &c_b10, &c_b10, &c_b8, "z axis", &
	    c__6, 6L);
    sym3d_(&c_b10, &c_b10, &c_b10, &c_b131, &c_b10, &c_b106, &c_b8, "z2 axis",
	     &c__7, 7L);

/*       ADD SOME RANDOM PI'S TO SHOW OFF NUM3D ROUTINE */

    num3d_(&c_b10, &c_b147, &c_b10, &c_b10, &c_b150, &c_b106, &c_b8, &c_b153, 
	    &c_b10);
    num3d_(&c_b147, &c_b10, &c_b147, &c_b158, &c_b10, &c_b10, &c_b8, &c_b153, 
	    &c_b10);
    num3d_(&c_b147, &c_b147, &c_b147, &c_b158, &c_b158, &c_b158, &c_b8, &
	    c_b153, &c_b10);

/*       ASK FOR A SCREEN CLEAR THEN RESTORE TERMINAL PLOT MODE */

    plot_(&c_b10, &c_b10, &c__3);
    newpage_();
    cterm_(&c__2);
    cterm_(&c_n1);

/*       NOW PLOT REAL AXIS */

    amin = (float)0.;
    amax = (float)3.;
    axis3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b10, &c_b10, "X AXIS", &c__6, &
	    c_b4, &amin, &amax, &c_b187, &c_b188, &c_b189, 6L);
    axis3d_(&c_b10, &c_b10, &c_b10, &c_b10, &c_b106, &c_b10, "Y AXIS", &c__6, 
	    &c_b4, &amin, &amax, &c_b199, &c_b188, &c_b189, 6L);
    axis3d_(&c_b10, &c_b10, &c_b10, &c_b131, &c_b10, &c_b10, "Z AXIS", &c__6, 
	    &c_b4, &amin, &amax, &c_b211, &c_b188, &c_b189, 6L);

/*       CLOSE PLOT PACKAGE AND ASK FOR SCREEN CLEAR */

    plot_(&c_b10, &c_b10, &c__3);
    cterm_(&c__2);
    plotnd_();
}

