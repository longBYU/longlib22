
/*  X Routines for the Longlib graphics library

    4/13/92  translated from original DECW FORTRAN by Tom Nelson
    This is the C version of the ramxlib.for X-Windows driver for Longlib

    1/17/94  revised by D. Long
    6/18/94  revised by D. Long + changed events and added rmreadcursor2
    10/13/94  revised by D. Long + improve event handling and changed rambox call
    1/1/02  revised by D. Long + support for additional visuals, some code cleaning
    9/9/21  revised by D. Long + clean code to remove warnings

    
    Note:  These routines make use of the external variable 'nb' and the
           external structure 'rmtek_' (defined in ll_nr.c) and so in order
           to link this library it is necessary for the program using these
           routines to allocate storage for these external variables.
    ***************************************************************/

/* #define DEBUG */ /* debug outputs if defined */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>

#include "my.h"

#define MAXWIND 5  /*This allows channel numbers 0-4, but channel number 0 
                     is not used.*/

extern struct {
  int ichan, imr[128];
  float rre[2], rox, roy, rsf;
  int nimr;
  float rang;
  int mm, ipw, ipsc, icol;
  float rvp[4];
  int irid;
  float rlim[2];
  int irxlim, irylim, iddev;
} rmtek_;

#define rmtek_1 rmtek_

/*Input and output structure for Ramout*/
struct evnt
{
  int ix, iy;   /*Returned pixel coordinates of keypress or buttonpress*/
  int key,      /*Code for key pressed (0 if not keyboard)*/
      button;   /*Code for button pressed (0 if not button)*/
};

  
  
/*The following are the structures used by the ramxlib functions*/

Display *dpy[MAXWIND];				/*display id*/
Screen *screen[MAXWIND];			/*screen id*/
Window window[MAXWIND];				/*window id*/
unsigned long attr_mask[MAXWIND];		/*attributes mask*/
long int eventmask[MAXWIND];			/*event mask*/
GC gc[MAXWIND];					/*gc id*/
Font font[MAXWIND];				/*font id*/
int window_x[MAXWIND],window_y[MAXWIND];	/*window origin*/
unsigned int ixwide[MAXWIND],iywide[MAXWIND];	/*window size*/
int depth[MAXWIND];				/*number of planes*/
long int ncolors[MAXWIND];			/*number of colors*/
long int func[MAXWIND], status[MAXWIND];	/*synchronous behavior*/
Pixmap pix[MAXWIND];				/*pixmap to store copy of window*/
Colormap colmap[MAXWIND];			/*color map*/
Cursor cursor1[MAXWIND],cursor2[MAXWIND];	/*cursors*/
unsigned long lastcol[MAXWIND];			/*last color index*/
int numpat[MAXWIND];				/*number entries in linpat*/
int ixopen[MAXWIND];	
int xl[2][MAXWIND],yl[2][MAXWIND],lx[MAXWIND],ly[MAXWIND];
long int imsize[MAXWIND];
unsigned int linwid[MAXWIND],imseq[MAXWIND];
char linpat[MAXWIND][16];			/*dot-dash line pattern*/

Visual *visual[MAXWIND];
XSetWindowAttributes xswda[MAXWIND];     
XGCValues xgcvl[MAXWIND];
XSizeHints xszhn[MAXWIND];
XEvent event[MAXWIND];
XColor color[MAXWIND];
XImage *image[MAXWIND]; 
XButtonEvent xbutton[MAXWIND];
XKeyEvent xkey[MAXWIND];

/* begin routine code */

int ramopen_(int *icha, int *idev, int *iddev, int *ierr)
/*Open and initialize a Ramtek X window */
{  
  int i, ichan, maxsizex, maxsizey;
  unsigned long pmasks[16];
  unsigned long returnpix[16];
  char title[16] = "LongLib Window";
  /*  char font_name[85] = "-adobe-new century schoolbook-medium-r-normal--14-140-75-75-p-82-hp-roman8"; */

  XVisualInfo vTemplate;
  XVisualInfo *visualList;
  int visualsMatched;

  ichan = *icha;

/*initialize ixopen*/
/*  for(i = 0; i <= MAXWIND; i++)
     ixopen[i] = 0;
*/  /* assume that compiler has dones this for us! */

/*Create and display window*/
  
  if(ichan <= 0)
     return -1; 
  if(ichan > MAXWIND)  {
     printf("*** XLongLib Error:  Window number %d too large!\n\r",ichan);
     //ichan=1;
     //*icha=1;
     //return -1;
     }
  if(ixopen[ichan] != 0)  {
     printf("*** XLongLib Error:  Attempt to open existing window!\n\r");
     return -1;
     }
     
  /*Initialize display ID and screen ID*/
  if((dpy[ichan] = XOpenDisplay(NULL)) == 0)  {
     printf("*** XLongLib Error:  X Display can not be opened!\n\r");
     return -1;
     }
  ixopen[ichan] = 1;
  screen[ichan] = XDefaultScreenOfDisplay(dpy[ichan]);

  /*get visual*/
  visualList = XGetVisualInfo (dpy[ichan], 0, &vTemplate, &visualsMatched);
  if (visualsMatched == 0) {
    printf("*** No matching visuals in X interface\n");
    (void) exit(-1);
  }
  XFree(visualList);

#ifdef DEBUG
  printf("X interface: visuals matched=%d\n",visualsMatched);
  printf("X interrace: screen depth %d  screen number %d\n",visualList[0].depth,visualList[0].screen);
#endif

  /*create the graphics output window*/
  
  maxsizex = XWidthOfScreen(screen[ichan]);
  maxsizey = XHeightOfScreen(screen[ichan]);
  
  /*Set window size*/
  
  ixwide[ichan] = 1280;     /*Default X array dimension */
  iywide[ichan] = 1024;     /*Default Y array dimension */
  
  window_x[ichan] = 50;
  window_y[ichan] = 50;
  
  switch(*idev)  {  
  case 2:                   /*512x512 array*/
     ixwide[ichan] = 512;
     iywide[ichan] = 512;
     break;
  case 3:                   /*Custom size array*/
     ixwide[ichan] = max(10, (*iddev)-1);
     iywide[ichan] = *ierr;
     break;
  case 4:		    /*Custom size and location*/
     ixwide[ichan] = max(10, (*iddev)-1);
     iywide[ichan] = *ierr;
     window_x[ichan] = max(1, min(*(iddev+1),maxsizex));
     window_y[ichan] = max(1, min(*(iddev+2),maxsizey));
     break;
  case 5:		    /*Maximum size array*/
     ixwide[ichan] = maxsizex-40;
     iywide[ichan] = maxsizey-50;
     window_x[ichan] = 20;
     window_y[ichan] = 40;
     *(iddev+1) = ixwide[ichan];	/*Return Ramtek size*/
     *(iddev+2) = iywide[ichan];
     break;
  default:
     break;
  }
   
  *iddev = 0;			/*Return Ramtek device number*/
  
  /*Initialize line types*/ 
  
  linpat[ichan][1]= 1;		/*Line bit pattern solid*/
  numpat[ichan] = 1;
  linwid[ichan] = 1;		/*Line width*/
  lastcol[ichan] = -1;		/*Color index*/
  
  /*Initialize image mode*/
  
  imsize[ichan] = 0;		/*Image size*/
  lx[ichan] = 0;		/*Image mode start x*/
  ly[ichan] = 0;		/*Image mode start y*/
  xl[0][ichan] = 0;		/*left default window*/
  yl[0][ichan] = 0;		/*upper default window*/
  xl[1][ichan] = ixwide[ichan]; /*right default window*/
  yl[1][ichan] = iywide[ichan] -1;   /*lower default window*/  
  imseq[ichan] = 0;		/*pix sequence:  left to right, top to bottom*/

  
  depth[ichan] = XDefaultDepthOfScreen(screen[ichan]);
  visual[ichan] = XDefaultVisualOfScreen(screen[ichan]);
  colmap[ichan] = XCopyColormapAndFree(dpy[ichan], XDefaultColormapOfScreen(screen[ichan]));
  
  attr_mask[ichan] = CWEventMask | CWBackPixel;
  xswda[ichan].event_mask = ExposureMask | KeyPressMask | ButtonReleaseMask | 
     PointerMotionHintMask | ButtonMotionMask | ButtonPressMask;
  xswda[ichan].background_pixel = XBlackPixelOfScreen(screen[ichan]);
  eventmask[ichan] = ExposureMask | KeyPressMask | ButtonReleaseMask |
     PointerMotionHintMask | ButtonMotionMask | ButtonPressMask;

#ifdef DEBUG
  printf("Create window channel=%d\n",ichan);
#endif

  window[ichan] = XCreateWindow(dpy[ichan], XRootWindowOfScreen(screen[ichan]), window_x[ichan], window_y[ichan], ixwide[ichan], iywide[ichan], 0, depth[ichan], InputOutput, visual[ichan], attr_mask[ichan], &xswda[ichan]);

#ifdef DEBUG
  XFlush(dpy[ichan]);  
  printf("X window created\n");
#endif

  /*Create pixmap which is a duplicate of what is displayed on screen.
    This pixmap is used to update window when expose event occurs*/ 
  pix[ichan] = XCreatePixmap(dpy[ichan], window[ichan], ixwide[ichan], iywide[ichan], depth[ichan]);

  /*Install private color map appropriate for visual*/
  XSetWindowColormap(dpy[ichan], window[ichan], colmap[ichan]);
  XInstallColormap(dpy[ichan], colmap[ichan]);

  lastcol[ichan] = 1;
  
  ncolors[ichan] = (long int) pow(2.0, depth[ichan]) - 1;
  
  /*Create a default color map for small visuals*/

  if (ncolors[ichan] < 1025) {

    for(i = 1; i <= ncolors[ichan] - 1; i++)  {
      color[ichan].pixel = i - 1;

      XQueryColor(dpy[ichan], XDefaultColormapOfScreen(screen[ichan]), &color[ichan]);

      /*If color is previously defined (from system default), use it
       	otherwise use appropriate gray level */
     
      if(color[ichan].red==0 && color[ichan].blue==0 && color[ichan].green==0 && i > 1)  {
        color[ichan].red   = cos((double) (i-1)) * 255 * 256;
        color[ichan].green = sin((double) (i-1)) * 255 * 256;
        color[ichan].blue  = sin((double) (i*i)) * 255 * 256;
        color[ichan].flags = 7; /*DoRed | DoGreen | DoBlue; */
      }
      XAllocColorCells(dpy[ichan], colmap[ichan], 0, pmasks, 0, returnpix, 1);
      color[ichan].pixel = returnpix[0];
      XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]);
    }
  }
  
  /*Create graphics context*/
  xgcvl[ichan].foreground = ncolors[ichan];
  xgcvl[ichan].background = 1; 
  xgcvl[ichan].line_width = 0;
    
  gc[ichan] = XCreateGC(dpy[ichan], window[ichan], GCForeground | GCBackground, &xgcvl[ichan]);

  /*Load the font for text writing*/
  /*  
      font[ichan] = XLoadFont(dpy[ichan], font_name);
      XSetFont(dpy[ichan], gc[ichan], font[ichan]);
  */

  /*Load up cursors*/
  cursor1[ichan] = XCreateFontCursor(dpy[ichan], XC_crosshair);
  cursor2[ichan] = XCreateFontCursor(dpy[ichan], XC_cross);
    
  /*Define the size and name of the graphics window for the window manager*/
  xszhn[ichan].x = 362;
  xszhn[ichan].y = 282;
  xszhn[ichan].width = ixwide[ichan];
  xszhn[ichan].height = iywide[ichan];
  xszhn[ichan].flags = PPosition | PSize;
  
  XSetNormalHints(dpy[ichan], window[ichan], &xszhn[ichan]);
  
  XStoreName(dpy[ichan], window[ichan], title);
  
  /*Map the window*/
  XMapWindow(dpy[ichan], window[ichan]);
  
  /*Get next event.  This should be an expose on our newly created window*/

  XNextEvent(dpy[ichan], &event[ichan]);
  if(event[ichan].type == Expose)   /*Clear window and pixmap*/
    XCopyArea(dpy[ichan], window[ichan], pix[ichan], gc[ichan], 1, 1, ixwide[ichan], iywide[ichan], 1, 1);
  else
    printf("*** Error:  First XLongLib window exposure channel=%d ***",ichan);
  
  /*Now should be ready to plot*/

  *ierr = 0;
  XFlush(dpy[ichan]);

  return 0;
  }


int ramclose_(int *icha)   /*Terminate Ramtek X Window plotting (destroy window)*/
{
  int ichan = *icha;  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
     
  ixopen[ichan] = 0;
  XUnmapWindow(dpy[ichan], window[ichan]);
  XDestroyWindow(dpy[ichan], window[ichan]);
  XCloseDisplay(dpy[ichan]);

  imsize[ichan] = -1;
  ichan = -1;
  return ichan;
}   
       

int ramout_(int ichan, int ic, struct evnt *evnts);

#define MAXPNTS 65
int rmplot_(int *icha, int *m, int p[2*MAXPNTS], int *ico, int *ier)
/*
  Plot a line of connected points
  
  ichan = the channel number
  n = the number of points (n<=64)
  p = the array of points (array of x,y coordinates)
  icol = plotting color (0-255)
  The returned value is the error code.
  */
{      
  int npnts, i;
  struct evnt event1;
  int ichan = *icha, n = *m, icol = *ico, ierr = *ier;
  XPoint ip[MAXPNTS];
  
  if(ichan <= 0 || ixopen[ichan] < 1)
     return 0;
  
 /*Check for expose events first*/
  
  if (ierr <= 0) ramout_(ichan, 0, &event1);
  
  /*Check for for xor/copy command */
  
  if (icol < 0) {
    if (icol == -1)
      XSetFunction(dpy[ichan],gc[ichan],GXcopy);
    else if (icol == -2)
      XSetFunction(dpy[ichan],gc[ichan],GXxor);
    return 0;
  }

  if (n < 0) return 0;
  npnts = min(max(n, 1), 64);  /*64 is the maximum number of points*/
  for(i = 0; i < MAXPNTS; i++)  {
    ip[i].x = p[2*i];
    ip[i].y = p[2*i + 1];
  }

  if (ncolors[ichan] > 1024 && icol < 256) {  /* to more simply handle larger visuals */
    if (icol < 25) icol=icol+125;
    icol = icol + icol * 256 + icol * 256 *256;
  }
  
  if(icol != lastcol[ichan])  {
#ifdef DEBUG
    printf("Color change: from %d to %d\n",lastcol[ichan],icol);
#endif
    lastcol[ichan] = icol;
    XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
  }

  if(npnts == 1)  {  
    XDrawPoint(dpy[ichan], pix[ichan], gc[ichan], ip[0].x, ip[0].y);
    XDrawPoint(dpy[ichan], window[ichan], gc[ichan], ip[0].x, ip[0].y);
  } else  {
    XDrawLines(dpy[ichan], pix[ichan], gc[ichan], ip, n, CoordModeOrigin);
    XDrawLines(dpy[ichan], window[ichan], gc[ichan], ip, n, CoordModeOrigin);
  }
  XFlush(dpy[ichan]);
  return 0;
}


int ramout_(int ichan, int ic, struct evnt *evnts)
/*Central event loop
  
  if ic = 0, ramout will check for and process any pending events
  if ic = 1, ramout will raise window and wait for keypress or button press
             inside of window.  Pixel coordinates of event are returned in
             evnt.ix and evnt.iy.
             evnt.key = code for pressed key (0 if not keyboard)
             evnt.button = code for pressed button (0 if not button)
  if ic = 2, ramout will raise window forward and then act as in ic = 0.
  */
{  
    
  int i;
  int flag2 = 1;
   
  if (ichan <= 0)
     return 0;
  if (ixopen[ichan] < 1)
     return 0;
  switch(ic)  {
   case 1:         /*ic = 1, raise window and wait for keypress or button press*/
   /*XSync(dpy[ichan], 1);
     XUndefineCursor((dpy[ichan], window[ichan], cursor1[ichan]);
     XDefineCursor(dpy[ichan], window[ichan], cursor2[ichan]);*/

     XDefineCursor(dpy[ichan], window[ichan], cursor2[ichan]);
     XRaiseWindow(dpy[ichan], window[ichan]);

   /*Await kepress or button event in graphics window*/
   /*While waiting, process expose events on all windows*/
   /*Ignore all other events in all other windows*/
     goto top5;
  case 2:	/*ic=2 raise window, just check for outstanding events */
     XRaiseWindow(dpy[ichan], window[ichan]);
     break;
  }
  XFlush(dpy[ichan]);

/* check for outstanding events if not event loop */
  
top5:
    for (i = 1; i < MAXWIND; i++)  { 
     if (i != ichan || flag2 == 1) {
       if (ixopen[i] == 1) {
top6:
         if (XCheckWindowEvent(dpy[i], window[i], eventmask[i], &event[i]) != 0)  {
           if (event[i].type == Expose)  {
            if (event[i].xexpose.count == 0)  {
             XCopyArea(dpy[i], pix[i], window[i], gc[i], 1, 1, ixwide[i], iywide[i], 1, 1);          
            } else {
              goto top6;
            } 		/*end of expose if */
           } 		/*end of event type if */
         } 		/*end of an event has occured if */
       } 		/*end of if (ixopen[i]) channel open*/    
      }			/*end of for each channel loop*/
     }
     if (ic != 1) return 0;

/* event looop */

/*     XUndefineCursor(dpy[ichan], window[ichan]); */
/*   XDefineCursor(dpy[ichan], window[ichan], cursor1[ichan]);*/

top10:
    for (i = 1; i <= MAXWIND; i++)  { 
       if (ixopen[i] == 1) {
top16:
         if (XCheckWindowEvent(dpy[i], window[i], eventmask[i], &event[i]) != 0)  {
           if (event[i].type == Expose)  {
            if (event[i].xexpose.count == 0)  {
             XCopyArea(dpy[i], pix[i], window[i], gc[i], 1, 1, ixwide[i], iywide[i], 1, 1);          
            } else {
              goto top16;
            } 		/*end of expose count if */
           } 		/*end of expose if */
/* all button and mouse events which occur in windows other than the
   desired one (ichan) are treated as raise window events */
	   if (i != ichan)
	     XRaiseWindow(dpy[i], window[i]);
	   else {
            if (event[ichan].type==ButtonRelease || event[ichan].type==KeyPress) {
	      if (event[ichan].type==ButtonRelease)  {
	           evnts->key = 0;
	           evnts->button = event[ichan].xbutton.button;
	           evnts->ix = event[ichan].xkey.x;
	           evnts->iy = event[ichan].xkey.y;
              } else  {
	           evnts->button = 0;
	           evnts->key = event[ichan].xkey.keycode;
	           evnts->ix = event[ichan].xbutton.x;
	           evnts->iy = event[ichan].xbutton.y;
              }
              XUndefineCursor(dpy[ichan], window[ichan]);
	      if (ic == 1) return 0;
            } 		/*end of event type if */
           } 		/*end of correct channel if */
         } 		/*end of an event has occured if */
       } 		/*end of if (ixopen[i]) channel open*/    
    }			/*end of for each channel loop*/
    goto top10;
}


int rmreadcursor2_(int *user(), int *icha, int ipnts[], int *jcopt, int *ihigh, 
                   int *ix1, int *iy1, int *ix2, int *iy2, int *icc)
{  /* Call event loop routine to return button press or key press w/rubberbanding */
/* fancy Rubberband event loop routine
  
  int user	external user supplied routine used when jcopt < 0.  Called when
		mouse button first depressed (icode=1) and periodically thereafter as mouse
		is moved (icode=2).  Call format for routine is: 
			"int user(int *ichan, int *iwx, int *iwy, int *icode, int *ikeys)
		(iwx,iwy) give the pixel location for mouse.  ichan contains window id number.
		ikeys is the button/key code.

  int ipnts	arrsy of (x,y) values for rubber banding
		first two elements are used for return values when
		abs(jcopt)=3 or 6 then ipnts(1)=x event location, ipnts(2)=y location

  int jcopt	fancy cursor option.  keypress or button release
		will end wait.
		 < 0 call user routine
		 > 0 do not call user routine
		abs(jcopt)=1 cursor tracking only
			  =2 rubber-band line from (ipnts(1),ipnts(2)) to
			     cursor position.
			  =3 same as 2 but from location of button depress
			  =4 rubber-band line from (ipnts(1),ipnts(2)) to
			     cursor location to (ipnts(5),ipnts(6))
			  =5 rubber-band box from corner at (ipnts(1),ipnts(2))
			     to cursor location
			  =6 same as 5 but start corner is location of button
			     depress

  int ihigh	color table index to use for rubber-band line

  int ic	control code
		  if ic = 0, check for and process any pending events
		  if ic = 1, raise window and wait for keypress or button press
		             inside of window.  Pixel coordinates of button release or
			     key press event are returned in (ix1,iy1).
		             ix2 = code for pressed key (0 if not keyboard)
		             iy2 = code for pressed button (0 if not button)
		  if ic = 2, raise window forward and then act as in ic = 0.
  */
    
  int ichan = *icha;
  int ic = *icc;

  int i;
  int ione = 1, izero = 0;
  int prev = 0;
  int down = 0;
  int npnts = 0;
  XPoint pnts[5];
  int icopt= (*jcopt > 0 ? *jcopt : - *jcopt);
  int irx, iry, iwx, iwy;
  Window iroot, ichild;
  unsigned int kbs;
  int iwx_org = 0, iwy_org = 0;

  switch(icopt) {
   case 2:
    npnts = 2;
    break;
   case 3:
    npnts = 2;
    break;
   case 4:
    npnts = 3;
    break;
   case 5:
    npnts = 5;
    break;
   case 6:
    npnts = 5;
    break;
   default:
    break;
  }
   
  if (ichan <= 0)
     return 0;
  if (ixopen[ichan] < 1)
     return 0;

  if (ic == 1) { /* ic = 1, raise window and wait for keypress or button press */
   /*XSync(dpy[ichan], 1);
     XUndefineCursor((dpy[ichan], window[ichan], cursor1[ichan]);
     XDefineCursor(dpy[ichan], window[ichan], cursor2[ichan]);*/

     XDefineCursor(dpy[ichan], window[ichan], cursor2[ichan]);
     XRaiseWindow(dpy[ichan], window[ichan]);

     if (icopt == 7 || icopt == 8 || icopt == 9) {
	if (XQueryPointer(dpy[ichan], window[ichan], &iroot, &ichild, &irx, &iry,
	  &iwx, &iwy, &kbs)  == 1) {
		switch(icopt) {
		  case 7:
		    npnts = 2;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    break;
		  case 8:
		    npnts = 3;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    pnts[2].x = ipnts[4];
		    pnts[2].y = ipnts[5];
		    break;
		  case 9:
		    npnts = 5;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = ipnts[0];
		    pnts[1].y = iwy;
		    pnts[2].x = iwx;
		    pnts[2].y = iwy;
		    pnts[3].x = iwx;
		    pnts[3].y = ipnts[1];
		    pnts[4].x = ipnts[0];
		    pnts[4].y = ipnts[1];
		    break;
		}
		XSetFunction(dpy[ichan], gc[ichan], GXxor);
		XSetForeground(dpy[ichan], gc[ichan], *ihigh);
		XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
		prev = 1;
		XSetFunction(dpy[ichan], gc[ichan], GXcopy);
		XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
	}
     }
     goto top5;
  }
  if (ic == 2) /* ic=2 raise window, just check for outstanding events */
     XRaiseWindow(dpy[ichan], window[ichan]);
  XFlush(dpy[ichan]);

/* check for outstanding events if not event loop */
  
top5:
    for (i = 1; i <= MAXWIND; i++)  { 
     if (i != ichan) {
       if (ixopen[i] == 1) {
top6:
         if (XCheckWindowEvent(dpy[i], window[i], eventmask[i], &event[i]) != 0)  {
           if (event[i].type == Expose)  {
            if (event[i].xexpose.count == 0)  {
             XCopyArea(dpy[i], pix[i], window[i], gc[i], 1, 1, ixwide[i], iywide[i], 1, 1);          
            } else {
              goto top6;
            } 		/*end of expose if */
           } 		/*end of event type if */
         } 		/*end of an event has occured if */
       } 		/*end of if (ixopen[i]) channel open*/    
      }			/*end of for each channel loop*/
     }
     if (ic != 1) return 0;

/* event looop */

top10:
    for (i = 1; i <= MAXWIND; i++)  { 
       if (ixopen[i] == 1) {
top16:
         if (XCheckWindowEvent(dpy[i], window[i], eventmask[i], &event[i]) != 0)  {
           if (event[i].type == Expose)  {
            if (event[i].xexpose.count == 0)  {
             XCopyArea(dpy[i], pix[i], window[i], gc[i], 1, 1, ixwide[i], iywide[i], 1, 1);          
            } else {
              goto top16;
            } 		/*end of expose count if */
           } 		/*end of expose if */
/* all button and mouse events which occur in windows other than the
   desired one (ichan) are treated as raise window events */
	   if (i != ichan)
	     XRaiseWindow(dpy[ichan], window[ichan]);
	   else {
       if (event[ichan].type == MotionNotify) {
	if (icopt > 1 || *jcopt == -1) {
	  if (XQueryPointer(dpy[ichan], window[ichan], &iroot, &ichild, &irx, &iry,
	       &iwx, &iwy, &kbs)  == 1) {
		if (*jcopt < 0) user(icha, &iwx, &iwy, &ione, &kbs);

		if (prev == 1) {
		  XSetFunction(dpy[ichan], gc[ichan], GXxor);
		  XSetForeground(dpy[ichan], gc[ichan], *ihigh);
		  XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
		}

		switch(icopt) {
		  case 2:
		  case 3:
		  case 7:
		    npnts = 2;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    if (down == 1 && icopt == 3) {
			    pnts[0].x = iwx_org;
			    pnts[0].y = iwy_org;
		    }
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    break;
		  case 4:
		  case 8:
		    npnts = 3;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    pnts[2].x = ipnts[4];
		    pnts[2].y = ipnts[5];
		    break;
		  case 5:
		  case 6:
		  case 9:
		    npnts = 5;
		    if (down == 1 && icopt == 6) {
			    pnts[0].x = iwx_org;
			    pnts[0].y = iwy_org;
			    pnts[1].x = iwx_org;
			    pnts[1].y = iwy;
			    pnts[2].x = iwx;
			    pnts[2].y = iwy;
			    pnts[3].x = iwx;
			    pnts[3].y = iwy_org;
			    pnts[4].x = iwx_org;
			    pnts[4].y = iwy_org;
		    } else {
			    pnts[0].x = ipnts[0];
			    pnts[0].y = ipnts[1];
			    pnts[1].x = ipnts[0];
			    pnts[1].y = iwy;
			    pnts[2].x = iwx;
			    pnts[2].y = iwy;
			    pnts[3].x = iwx;
			    pnts[3].y = ipnts[1];
			    pnts[4].x = ipnts[0];
			    pnts[4].y = ipnts[1];
		    }
		    break;
		}
		if (npnts > 0) {
		  if (prev == 0) {
		    XSetFunction(dpy[ichan], gc[ichan], GXxor);
		    XSetForeground(dpy[ichan], gc[ichan], *ihigh);
		  }
		  XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
		  prev = 1;
		  XSetFunction(dpy[ichan], gc[ichan], GXcopy);
		  XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
		}
	     }
	 }
       } else if (event[ichan].type == ButtonPress) {
	  
	  if (XQueryPointer(dpy[ichan], window[ichan], &iroot, &ichild, &irx, &iry,
	       &iwx, &iwy, &kbs)  == 1) {
		iwx_org = iwx;
		iwy_org = iwy;
		down = 1;
		if (prev == 1) {
		  XSetFunction(dpy[ichan], gc[ichan], GXxor);
		  XSetForeground(dpy[ichan], gc[ichan], *ihigh);
		  XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
		}
		
		switch(icopt) {
		  case 7:
		    npnts = 2;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    break;
		  case 8:
		    npnts = 3;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = iwx;
		    pnts[1].y = iwy;
		    pnts[2].x = ipnts[4];
		    pnts[2].y = ipnts[5];
		    break;
		  case 9:
		    npnts = 5;
		    pnts[0].x = ipnts[0];
		    pnts[0].y = ipnts[1];
		    pnts[1].x = ipnts[0];
		    pnts[1].y = iwy;
		    pnts[2].x = iwx;
		    pnts[2].y = iwy;
		    pnts[3].x = iwx;
		    pnts[3].y = ipnts[1];
		    pnts[4].x = ipnts[0];
		    pnts[4].y = ipnts[1];
		    break;
		}
		switch(icopt) {
		  case 7:
		  case 8:
		  case 9:
			prev = 1;
			if (prev == 0) {
			    XSetFunction(dpy[ichan], gc[ichan], GXxor);
			    XSetForeground(dpy[ichan], gc[ichan], *ihigh);
			}
			XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
		}
	        if (*jcopt < 0) user(icha, &iwx, &iwy, &izero, &kbs);
	   }
	  
	} else if (event[ichan].type == ButtonRelease || event[ichan].type == KeyPress) {
	  if (event[ichan].type == ButtonRelease)  {
	           *ix2 = 0;
	           *iy2 = event[ichan].xbutton.button;
	           *ix1 = event[ichan].xkey.x;
	           *iy1 = event[ichan].xkey.y;
          } else  {
	           *ix2 = event[ichan].xkey.keycode;
	           *iy2 = 0;
	           *ix1 = event[ichan].xbutton.x;
	           *iy1 = event[ichan].xbutton.y;
          }
          XUndefineCursor(dpy[ichan], window[ichan]);
	  if (ic == 1) goto top99;
            } 		/*end of event type if */
           } 		/*end of channel number if */
         } 		/*end of an event has occured if */
       } 		/*end of if (ixopen[i]) channel open*/    
    }			/*end of for each channel loop*/
    goto top10;

top99:
   if (prev == 1) {
	XSetFunction(dpy[ichan], gc[ichan], GXxor);
        XSetForeground(dpy[ichan], gc[ichan], *ihigh);
	XDrawLines(dpy[ichan], window[ichan], gc[ichan], pnts, npnts, CoordModeOrigin);
	XSetFunction(dpy[ichan], gc[ichan], GXcopy);
	XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
   }
   if (icopt == 3 || icopt == 6) {
	ipnts[0] = iwx_org;
	ipnts[1] = iwy_org;
   }
   return 0;
}


int rmtexture_(int *icha, int *itex1, int *iwid, int *isiz, int *ierr)
/*Change plot line texture and scaling
  
  inputs:  ichan    Channel number
           itext1   Line type (0-15)
           iwide    Line width
           isize    Pixel scaling  (ignored)
           
           */
{    
  struct evnt event1;
  int itext;
  int ichan = *icha;
  int itext1 = *itex1;
  int iwide = *iwid;
  
  if(ichan<=0 || ixopen[ichan] < 1)
     return 0;
     
  ramout_(ichan, 0, &event1);
  itext = itext1 % 14;
  numpat[ichan] = 1;
  linpat[ichan][1] = 1;
  switch (itext) {
  case 1:
     numpat[ichan] = 2;
     linpat[ichan][0] = 1;
     linpat[ichan][1] = 1;
     break;
  case 2:
     numpat[ichan] = 2;
     linpat[ichan][0] = 2;
     linpat[ichan][1] = 2;
     break;
  case 3:
     numpat[ichan] = 2;
     linpat[ichan][0] = 3;
     linpat[ichan][1] = 3;
     break;
  case 4:
     numpat[ichan] = 2;
     linpat[ichan][0] = 2;
     linpat[ichan][1] = 1;
     break;
  case 5:
     numpat[ichan] = 2;
     linpat[ichan][0] = 4;
     linpat[ichan][1] = 1;
     break;
  case 6:
     numpat[ichan] = 2;
     linpat[ichan][0] = 5;
     linpat[ichan][1] = 2;
     break;
  case 7:
     numpat[ichan] = 3;
     linpat[ichan][0] = 1;
     linpat[ichan][1] = 3;
     linpat[ichan][2] = 2;
     break;
  case 8:
     numpat[ichan] = 3;
     linpat[ichan][0] = 2;
     linpat[ichan][1] = 4;
     linpat[ichan][2] = 1;
     break;
  case 9:
     numpat[ichan] = 3;
     linpat[ichan][0] = 1;
     linpat[ichan][1] = 2;
     linpat[ichan][2] = 1;
     break;
  case 10:
     numpat[ichan] = 3;
     linpat[ichan][0] = 5;
     linpat[ichan][1] = 1;
     linpat[ichan][2] = 2;
     break;
  case 13:
     numpat[ichan] = 3;
     linpat[ichan][0] = 5;
     linpat[ichan][1] = 3;
     linpat[ichan][2] = 1;
     break;
  }
  
  linwid[ichan] = max(iwide - 1, 0);
  if(numpat[ichan]==1)		/*Solid line*/
    XSetLineAttributes(dpy[ichan], gc[ichan], linwid[ichan], LineSolid, 
		       CapButt, JoinMiter);
  else {			/* dashed line */
    XSetDashes(dpy[ichan], gc[ichan], 0, &linpat[ichan][0], numpat[ichan]);
    XSetLineAttributes(dpy[ichan], gc[ichan], linwid[ichan], LineOnOffDash,
		       CapButt, JoinMiter);
  }
  XFlush(dpy[ichan]);
  
  return 0;
}

int rmclear_(int *icha, int *ierr)
/*Clear RamTek screen*/
{      
  struct evnt event1;
  int ichan = *icha;
  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  
  ramout_(ichan, 0, &event1);
  XClearWindow(dpy[ichan], window[ichan]);
/*XCopyArea(dpy[ichan], window[ichan], pix[ichan], gc[ichan], 1, 1, ixwide[ichan], iywide[ichan], 1, 1);*/
  XSetForeground(dpy[ichan], gc[ichan], 0);
  XFillRectangle(dpy[ichan], pix[ichan], gc[ichan], 1, 1, ixwide[ichan], iywide[ichan]);
  XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
  XFlush(dpy[ichan]);
  return 0;
}

int ramoutin_(int ichan, char *a, short int *b, long int *c, int numwords, 
		int mode)
/*    Read/Write data from Ramtek in image mode   
   Inputs:
      ichan    channel number
      p        pointer to an array of either 1, 2, or 4 byte words
      numwords number of words to be written or read
      mode     mode of operation
                 0 = read bytes (char)
                 1 = read 2 byte (short int)  words
                 2 = write bytes (char)
                 3 = write 2 byte (short int) words
                 4 = read 4 byte (long int) words
                 5 = write 4 byte (long int) words
        */
{    
  int lx1, ly1;
  unsigned int width, height;
  int data;
  int planemask = 65535;
  
  int ix = 1, iy = 0, jx = 0, jy = 1,i,flag;
  
  if(numwords <= 0)
     return 0;
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  if(imsize[ichan] <= 0)  {
     printf("*** XLongLib Image Mode Error:  No Image Window");
     return 0;
     }
  if (mode < 0 || mode > 5) {
     printf("*** XLongLib Error:  Improper array type for ramoutin_ ***");
     return 0;
  }
  
  width = xl[1][ichan] - xl[0][ichan] + 1;
  height = yl[1][ichan] - yl[0][ichan] + 1;
  
  /*Read image from display pixmap*/

  image[ichan] = XGetImage(dpy[ichan], pix[ichan], xl[0][ichan], yl[0][ichan],
			   width, height, planemask, ZPixmap);
  
  ix = 1;  iy = 0;  jx = 0;  jy = 1;
  switch(imseq[ichan])  {    /*Set scanning sequence*/
  case 1:    /*r-l, t-b*/
     ix = -1;
     break;
  case 2:    /*l-r, b-t*/
  default:
     jy = -1;
     break;
  case 3:    /*r-l, b-t*/
     ix = -1;   jy = -1;
     break;
  case 4:    /*t-b, l-r*/
     ix = 0;     iy = 1;     jx = 1;     jy = 0;
     break;
  case 5:    /*b-t, l-r*/
     ix = 0;     iy = -1;     jx = 1;     jy = 0;
     break;
  case 6:    /*t-b, r-l*/
     ix = 0;     iy = 1;     jx = -1;     jy = 0;
     break;
  case 7:    /*b-t, r-l*/
     ix = 0;     iy = -1;     jx = -1;     jy = 0;
     break;
  }
  for(i = 0; i <= numwords; i++)  {
     lx1 = lx[ichan] - xl[0][ichan];
     ly1 = ly[ichan] - yl[0][ichan];
     switch(mode)  {
        case 0:       /*Read bytes*/ 
           data = XGetPixel(image[ichan], lx1, ly1);
           a[i] = data;  /*least significant byte*/
           break;
        case 1:       /*Read 2 byte words*/
           data = XGetPixel(image[ichan], lx1, ly1);
           b[i] = data;   /*least significant 2 bytes*/
           break;
        case 2:       /*Write bytes*/
           data = a[i];
           XPutPixel(image[ichan], lx1, ly1, data);
           break;
        case 3:       /*Write 2 byte words*/
           data = b[i];
           XPutPixel(image[ichan], lx1, ly1, data);
           break;
        case 4:       /*Read 4 byte words*/
           c[i] = XGetPixel(image[ichan], lx1, ly1);
           break;
        case 5:       /*Write 4 byte words*/
           XPutPixel(image[ichan], lx1, ly1, c[i]);
           break;
     } 
     lx[ichan] = lx[ichan] + ix;
     ly[ichan] = ly[ichan] + iy;
     do  {
      flag = 0;
      if(lx[ichan] < xl[0][ichan])  {
        lx[ichan] = xl[1][ichan];
        ly[ichan] = ly[ichan] + jy;
        }
      if(lx[ichan] > xl[1][ichan])  {
        lx[ichan] = xl[0][ichan];
        ly[ichan] = ly[ichan] +jy;
        }
      if(ly[ichan] < yl[0][ichan])  {
        ly[ichan] = yl[1][ichan];
        lx[ichan] = lx[ichan] + jx;
        flag = 1;
        }
      if(ly[ichan] > yl[1][ichan])  {
        ly[ichan] = yl[0][ichan];
        lx[ichan] = lx[ichan] + jx;
        flag = 1;
        }
     } while(flag==1);
   }
     
   /*Write image to display*/
     XPutImage(dpy[ichan], window[ichan], gc[ichan], image[ichan], 0, 0, 
	xl[0][ichan], yl[0][ichan], xl[1][ichan]-xl[0][ichan]+1, 
	yl[1][ichan]-yl[0][ichan]+1);
     XPutImage(dpy[ichan], pix[ichan], gc[ichan], image[ichan], 0, 0, 
	xl[0][ichan], yl[0][ichan], xl[1][ichan]-xl[0][ichan]+1, 
	yl[1][ichan]-yl[0][ichan]+1);
     XFlush(dpy[ichan]);
     
   return 0;
}

 
int rmreadcursor_(int *icha, int *idev, int *ix, int *iy, int *itrk, int *ivis, int *ient, int *ierr)
/*Call event loop routine to return button press or key press*/
{
  int ichan = *icha;
  struct evnt evnt1;
  ramout_(ichan, 1, &evnt1);
  *ix = evnt1.ix;
  *iy = evnt1.iy;
  *itrk = evnt1.key;
  *ient = evnt1.button;
  return 0;
}


int rmreadcol_(int *icha, int *itab, int *m, int *ierr)
/*Read color table from screen device
  Inputs
    ichan    channel number
    n        number of colors
  Output
    itab     table of colors     
*/
{
  int i, ichan = *icha, n = *m;
  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  if(n <= 0)
     return -1;
  
  ncolors[ichan] = pow(2,depth[ichan]) - 1;
  n = min(ncolors[ichan],n);

  if (ncolors[ichan] > 1024) return 0;
  
  for(i = 0; i < n; i += 3)  {
     color[ichan].pixel = i;
     XQueryColor(dpy[ichan], colmap[ichan], &color[ichan]);
     itab[i] = color[ichan].red;
     itab[i+1] = color[ichan].green;
     itab[i+2] = color[ichan].blue;
     }
  XFlush(dpy[ichan]);
  
  return 0;
}
  
  
int rmwritecol_(int *icha, int *itab, int *m, int *ierr)
/*Write color table to screen*/
{
  int i, ichan = *icha, n = *m;
  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  if(n <= 0)
     return -1;
  
  ncolors[ichan] = pow(2,depth[ichan]) - 1;
  n = min(ncolors[ichan],n);

  if (ncolors[ichan] > 1024) return 0;
  
  for(i = 0; i < n; i +=3)  {
     color[ichan].pixel = i;
     color[ichan].red   = itab[i];
     color[ichan].green = itab[i+1];
     color[ichan].blue  = itab[i+2];
     XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]);
     }
  XFlush(dpy[ichan]);
  
  return 0;
}
     

int rmreadbyte_(int *icha, char *is, int *m, int *ierr)
/*Read data byte from Ramtek image mode
  Inputs
     ichan
     n       number of bytes to be read
  output
     is      array of bytes
  */
{
  int ichan = *icha, n = *m;
  short int i2; long int i4;
  
  ramoutin_(ichan, is, &i2, &i4, n, 0);
  return 0;
}


int rmreadword_(int *icha, short int *is, int *m, int *ierr)
/*Read 2 byte word from Ramtek image mode
  Inputs
    ichan
    n       number of words to be read
  Output
    is      array of 2 byte words
    */
{
  char c;
  long int i4;
  int ichan = *icha, n = *m;
  
  ramoutin_(ichan, &c, is, &i4, n, 1);
  return 0;
}


int rmwritebyte_(int *icha, char *is, int *m, int *ierr)
/*Write byte data to Ramtek in image mode
  Inputs
    ichan
    is     array image data (bytes)
    n      number of bytes to write
 */ 
{
  short int i2; long int i4;
  int ichan = *icha, n = *m;
  ramoutin_(ichan, is, &i2, &i4, n, 2);
  return 0;
}


int rmwriteword_(int *icha, short int *is, int *m, int *ierr)
/*Write 2 byte words to Ramtek in image mode
  Inputs
    ichan
    is      array of word image data
    n       number of words to write
*/
{
  char c;
  long int i4;
  int ichan = *icha, n = *m;
  ramoutin_(ichan, &c, is, &i4, n, 3);
  return 0;
}


int rmstart_(int *icha, int *x, int *y, int *ierr)
/*Set start of image write (cop) location to (ix,iy)*/
{    
  int ichan = *icha, ix = *x, iy = *y;
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  
  lx[ichan] = ix;
  ly[ichan] = iy;
  if(lx[ichan] < xl[0][ichan])
     lx[ichan] = xl[0][ichan];
  if(lx[ichan] > xl[1][ichan])
     lx[ichan] = xl[1][ichan];
  if(ly[ichan] < yl[0][ichan])
     ly[ichan] = yl[0][ichan];
  if(ly[ichan] > yl[1][ichan])
     ly[ichan] = yl[1][ichan];    
  
  return 0;
}

#define MAXIM 10000
int rmwind_(int *icha, int *x, int *y, int *xm, int *ym, char *storage)
/*Set image mode window on Ramtek
  Inputs
     ichan
     ix, iy    upper-left corner
     ixm,iym   lower right corner
     storage   external image storage area (used if # of pixels > 10,000--ignored otherwise)
  Note:  Minimum window size allowed is 2x2 pixels
  */
{
  char store[MAXIM];
  int nbitpad = 16;
  int ichan = *icha, ix = *x, iy = *y, ixm = *xm, iym = *ym;
  extern long int nb;
  
  if(ichan <= 0)
     return -1;
  if(ixopen[ichan] < 1)
     return -1;
/*if(imsize[ichan] > 0)
     XDestroyImage(image[ichan]);*/
  xl[0][ichan] = ix;
  if(xl[0][ichan] < 0)
     xl[0][ichan] = 0;
  if(xl[0][ichan] > ixwide[ichan])
     xl[0][ichan] = ixwide[ichan];
  yl[0][ichan] = iy;
  if(yl[0][ichan] < 0)
     yl[0][ichan] = 0;
  if(yl[0][ichan] > iywide[ichan])
     yl[0][ichan] = iywide[ichan];
  xl[1][ichan] = ixm;
  if(xl[1][ichan] < 0)
     xl[1][ichan] = 0;
  if(xl[1][ichan] > ixwide[ichan])
     xl[1][ichan] = ixwide[ichan];
  yl[1][ichan] = iym;
  if(yl[1][ichan] < 0)
     yl[1][ichan] = 0;
  if(yl[1][ichan] > iywide[ichan])
     yl[1][ichan] = iywide[ichan];
  if(xl[1][ichan] <= xl[0][ichan])
     xl[1][ichan] = xl[0][ichan] + 1;
  if(yl[1][ichan] <= yl[0][ichan])
     yl[1][ichan] = yl[0][ichan] + 1;
  imsize[ichan] = (xl[1][ichan] - xl[0][ichan] +1) * (yl[1][ichan] - yl[0][ichan] + 1);  
  if(depth[ichan] > 8)
     nbitpad = 32;
      
  if(imsize[ichan] > MAXIM)     /*Use external storage for image*/
     image[ichan] = XCreateImage(dpy[ichan], visual[ichan], depth[ichan], 
				 ZPixmap, 0, storage, xl[1][ichan] - xl[0][ichan]+1, 
				 yl[1][ichan] - yl[0][ichan]+1, nbitpad, nb);
  else                          /*Use internal storage form image (store)*/
     image[ichan] = XCreateImage(dpy[ichan], visual[ichan], depth[ichan], 
				 ZPixmap, 0, store, xl[1][ichan] - xl[0][ichan]+1, 
				 yl[1][ichan] - yl[0][ichan]+1, nbitpad, nb);
  
  lx[ichan] = xl[0][ichan];
  ly[ichan] = yl[0][ichan];
  
  return 0;
}


int rmdir_(int *icha, int *seq, int *ierr)
/*Set scan sequence for image writing on Ramtek
  Inputs:
  ichan    channel number
  iseq     scan code
           pix-to-pix      line-to-line
     0		L-R		T-B
     1		R-L		T-B
     2		L-R		B-T
     3		R-L		B-T
     4		T-B		L-R
     5		B-T		L-R
     6		T-B		R-L
     7		B-T		R-L
  Output
  status error returned (-1 = error)
  */
{    
  int ichan = *icha, iseq = *seq;
  if(ichan <= 0)
    return 0;
  if(ixopen[ichan] < 1)
    return 0;
  if(iseq >= 0 && iseq < 8)  {
    imseq[ichan] = iseq;
    return 0;
  } else
    return -1;
}


int rmzoom_(int *ichan, int *ifact, int *ierr)
{
   return 0;
}


int rmpan_(int *ichan, int *leftx, int *topy, int *ierr)
{
   return 0;
}


int rmsetcur_(int *ichan, int *icur, int *ix, int *iy, int *ibl, int *ivi, int *ierr)
{
   return 0;
}


int rmtext_(int *icha, int *col, int *x, int *y, int *iss, char *text, int *length, int *ierr)
/*Print text to Ramtek screen
  Inputs
  ichan   channel number
  icol    text color (if negative, xor with abs(icol) is used)
  ix,iy   text coordinates
  iss     size (not used)
  text    text string
  ilen    number of characters to print
  */
{
  int len;
  int ichan = *icha, ix = *x, iy = *y, ilen = *length;
  int icol = *col;
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;

 /*Check for for xor */
  if (icol < 0) XSetFunction(dpy[ichan],gc[ichan],GXxor);

  if(icol != lastcol[ichan])  {
    lastcol[ichan] = abs(icol);
    XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
  }

  len = min(strlen(text), max(ilen, 1));
  XDrawString(dpy[ichan], pix[ichan], gc[ichan], ix, iy, text, len);
  XDrawString(dpy[ichan], window[ichan], gc[ichan], ix, iy, text, len);

  if (icol < 0) XSetFunction(dpy[ichan],gc[ichan],GXcopy);
  XFlush(dpy[ichan]);
  
  return 0;
}


int rmfntsize_(int *ichan, int *hd, int *vd, int *vs, int *ierr)
{
  return 0;
}


int rmreset_(int *ichan, int *ierr)
{
  return 0;
}


int rambox_(int *chan, int *x1, int *y1, int *x2, int *y2, int *col)
/*Fills in a box on the Ramtek
  Inputs:
  (ix1,iy1)  lower left corner (in pixels)
  (ix2,iy2)  upper right corner (in pixels)
  jcol       color index
  
  */
{
  int ix, ixx, iy, iyy, c, d;
  struct evnt event1;
  int ix1 = *x1, iy1 = *y1, ix2 = *x2, iy2 = *y2, jcol = *col;
  int rmichan = *chan;

  if (rmichan <=0)
     return 0;
  if(max(ix1,ix2) < 1 || min(ix1,ix2) > ixwide[rmichan])
     return 0;
  if(max(iy1,iy2) < 1 || min(iy1,iy2) > iywide[rmichan])
     return 0;
   
  ix = max(1, min(ix1,ix2));
  ixx = min(ixwide[rmichan], max(ix1,ix2)) - ix;
  iy = max(1, min(iy1,iy2));
  c = max(iy1,iy2);
  d = min(iywide[rmichan], c);
  iyy = d - iy;
  
  if(lastcol[rmichan] != jcol) {
    lastcol[rmichan] = jcol;
    XSetForeground(dpy[rmichan], gc[rmichan], lastcol[rmichan]);
  }
  
  XFillRectangle(dpy[rmichan], window[rmichan], gc[rmichan], ix, iy, ixx, iyy);
  XFillRectangle(dpy[rmichan], pix[rmichan], gc[rmichan], ix, iy, ixx, iyy);

  ramout_(rmichan, 0, &event1);
  return 0;
} 


int rmpause_(int *ichan, int *iwait)
/*iwait = 0  checks for event in Ramtek window and processes it if present
  iwait = 1  waits for event in Ramtek window and then processes it
  */
{
  struct evnt evnt1; 
  ramout_(*ichan, *iwait, &evnt1);
  return 0;
}

int rminfo_(int *icha, int *iopen, int *ix, int *iy, int *ncol, int *lcol, int *xw, int *yw, int *isize)
/*Get info on Ramtek device*/
{
  int ichan = *icha;
  *iopen = -1;
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  
  *iopen = ixopen[ichan];
  *ix = ixwide[ichan];
  *iy = iywide[ichan];
  *ncol = ncolors[ichan];
  *lcol = lastcol[ichan];
  xw[0] = xl[0][ichan];
  xw[1] = xl[1][ichan];
  yw[0] = yl[0][ichan];
  yw[1] = yl[1][ichan];
  *isize = imsize[ichan];
 /* *iseq = imseq[ichan];*/
  
  return 0;
}


int rmwrcolind_(int *icha, long *ire, long *igree, long *iblu, long *inde, int *ierr)
/*Write single color table index to Ramtek device*/
{
  int ichan = *icha;
  long ired = *ire, igreen = *igree, iblue = *iblu, index = *inde;
  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  if(index < 0)
     return -1;
  ncolors[ichan] = pow(2,depth[ichan]) - 1;

  if(index > ncolors[ichan] || ncolors[ichan] > 1024)
     return -1;
  color[ichan].pixel = index;
  color[ichan].red = (short) ired;
  color[ichan].green = (short) igreen;
  color[ichan].blue = (short) iblue;
  color[ichan].flags = DoRed | DoGreen | DoBlue;
  
  XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]);
  XFlush(dpy[ichan]);
  
  return 0;
}

int rmrdcolind_(int *icha, long *ired, long *igreen, long *iblue, long *index, int *ierr)
/*Read single color table index value from screen device */
{    
  int ichan = *icha;
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  if(*index < 0)
     return -1;
  ncolors[ichan] = pow(2,depth[ichan]) - 1;
  if(*index > ncolors[ichan])
     return -1;

  color[ichan].pixel = *index;
  XQueryColor(dpy[ichan], colmap[ichan], &color[ichan]);
  *ired   = color[ichan].red;
  *igreen = color[ichan].green;
  *iblue  = color[ichan].blue;
  
  return 0;
}
  

int rmwr4_(int *ichan, long int *is, int *n, int *ierr)
/*Write 4 byte integer words to Ramtek in image mode
  Inputs:
  ichan
  is     pointer to an array of data
  n      number of words to write
  */
{
  char c; short int i2;
  ramoutin_(*ichan, &c, &i2, is, *n, 5);
  return 0;
}


int rmrd4_(int *ichan, long int *is, int *n, int *ierr)
/*Read 4 byte integer words to Ramtek in image mode
  Inputs
  ichan
  is     pointer to a storage arrea (an array of data)
  n      number of words to read
  */
{
  char c; short int i2;
  ramoutin_(*ichan, &c, &i2, is, *n, 5);
  return 0;
}


long int rmspix_(int *icha, int *x, int *y, long int *val, int *rdwr, int *ierr)
/*Read/write a single pixel on Ramtek  (very inefficient)
  Inputs
    ichan
    ix,iy   pixel coordinates
    irdwr   = 0  Read pixel value
            = 1  Write pixel value
  Output
    on irdwr = 0, rmspix_ returns the value read
    */
{    
  int nbitpad;
  int ichan = *icha, ix = *x, iy = *y, irdwr = *rdwr;
  long int ival = *val;
  extern long int nb;
  char store[MAXIM];   /*MAXIM defined above to be 11000*/
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
/*if(imsize[ichan] > 0)
     XDestroyImage(image[ichan]);*/
  xl[0][ichan] = ix;
  if(xl[0][ichan] < 0)
     xl[0][ichan] = 0;
  if(xl[0][ichan] > ixwide[ichan])
     xl[0][ichan] = ixwide[ichan];
  yl[0][ichan] = iy;
  if(yl[0][ichan] < 0)
     yl[0][ichan] = 0;
  if(yl[0][ichan] > iywide[ichan])
     yl[0][ichan] = iywide[ichan];
  nbitpad = 16;
  if(depth[ichan] > 8)
     nbitpad = 32;
  imsize[ichan] = 1;
  image[ichan] = XCreateImage(dpy[ichan], visual[ichan], depth[ichan], ZPixmap, 0, store, 1, 1, nbitpad, nb);
  lx[ichan] = xl[0][ichan];
  ly[ichan] = yl[0][ichan];
  if(irdwr == 1)
     XPutPixel(image[ichan], lx[ichan], ly[ichan], ival);
  else
     ival = XGetPixel(image[ichan], lx[ichan], ly[ichan]);
  
  return ival;
}


int rmstcol_(int *icha, int *tab, int *ncol, int *ierr)
/*Writes a standard color table to Ramtek device
  Inputs
    ichan
    itab   = 0  Nothing done
           = 1  Gray
           = 2  Startup
           = 3  Pseudo color
  Output
    The number of colors is returned
  */
{
  int ichan = *icha, itab = *tab, i;
  int m1 = 3, m2 = 3, m3 = 2;
  unsigned short int col, col2;
  int iwait = 0;
  struct evnt event1;
  
  if(ichan <= 0)
     return 0;
  if(ixopen[ichan] < 1)
     return 0;
  *ncol = ncolors[ichan];
  if(itab == 0)
     return 0;
  
  if(depth[ichan] == 6)  {
     m1 = 2;
     m2 = 2;
     }
  
  ramout_(ichan,iwait,&event1);
  if (ncolors[ichan] > 1024) return -1;
  
  for (i = 0; i < ncolors[ichan] - 1; i++)  {
    color[ichan].pixel = i;
    if (itab == 1)  {    /*gray*/
	col = (unsigned short int) (((float) i /(float) ncolors[ichan])*255*256);
	color[ichan].red   = col;
	color[ichan].green = col;
	color[ichan].blue  = col;
	color[ichan].flags = DoRed | DoGreen | DoBlue;
	XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]);
     } else if (itab == 2)  {   /*startup colors*/
	color[ichan].red   = (unsigned short int) (cos((double) i)  *255*256);
	color[ichan].green = (unsigned short int) (sin((double) i)  *255*256);
	color[ichan].blue  = (unsigned short int) (sin((double) i*i)*255*256);
	color[ichan].flags = DoRed | DoGreen | DoBlue;
	XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]);
     } else if (itab == 3)  {  /*Psuedo-color*/
	col2 = (unsigned short int) (((float) i/(float) ncolors[ichan])*255*256);
	col = (unsigned short int) (((i % (1<<m1)) * (1<<(depth[ichan]-m1)) ) * 256);
	if(col <= ncolors[ichan])
          color[ichan].red = col;
	else
          color[ichan].red = col2;
	col = (unsigned short int) ((((i / (1<<m1)) % (1<<m2) ) * (1<<(depth[ichan]-m2)))* 256);
	if (col <= ncolors[ichan])
          color[ichan].green = col;
	else
	  color[ichan].green = col2;
	col = (unsigned short int) (((i / (1<<(m1+m2))) * (1<<(depth[ichan]-m3)))* 256);
	if (col <= ncolors[ichan])
          color[ichan].blue = col;
	else
          color[ichan].blue = col2;     
	color[ichan].flags = DoRed | DoGreen | DoBlue;
	XStoreColor(dpy[ichan], colmap[ichan], &color[ichan]); 
     }
  }

  XFlush(dpy[ichan]);

  return 0;
}

int rmmode_(int *icha, int *iwind, int *ipix, int *iswap, int *ierr)
{
  return 0;
}

int rmpoint_(int *icha, int *x, int *y, int *ico, int *ier)
/*
  Plot a single point
  
  ichan = the channel number
  x,y = pixel location of point
  ico = plotting color
         if icol < 0 point is xor'd
  The returned value is the error code.
  */
{  
  int ichan = *icha, icol = *ico;
  short xp = *x, yp = *y;
  
/*  printf("rmpoint: %d %d %d %d %d\n",ichan,xp,yp,icol,*ier); */
  if(ichan <= 0 || ixopen[ichan] < 1)
     return 0;

  /*Check for for xor/copy command */
  
  if (icol < 0) {
    if (icol == -1)
      XSetFunction(dpy[ichan],gc[ichan],GXcopy);
    else if (icol == -2)
      XSetFunction(dpy[ichan],gc[ichan],GXxor);
  }

  if (icol < 0) XSetFunction(dpy[ichan],gc[ichan],GXxor);

  if (ncolors[ichan] > 1024 && icol < 256)  /* to more simply handle larger visuals */
    icol = icol + icol * 256 + icol * 256 *256;

  if(icol != lastcol[ichan])  {
    lastcol[ichan] = abs(icol);
    XSetForeground(dpy[ichan], gc[ichan], lastcol[ichan]);
  }
  
  XDrawPoint(dpy[ichan], pix[ichan], gc[ichan], xp, yp);
  XDrawPoint(dpy[ichan], window[ichan], gc[ichan], xp, yp);

  if (icol < 0) XSetFunction(dpy[ichan],gc[ichan],GXcopy);

  XFlush(dpy[ichan]);
  return 0;
}


