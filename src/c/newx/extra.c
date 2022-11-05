#include <stdio.h>

#include "my.h"

int nb = 1024;  /* This variable is used by the ramxlib routines */

/* Common Block Declarations */

struct {
    integer ichan, imr[128];
    real rre[2], rox, roy, rsf;
    integer nimr;
    real rang;
    integer mm, ipw, ipsc, icol;
    real rvp[4];
    integer irid;
    real rlim[2];
    integer irxlim, irylim, iddev;
} rmtek_;        /*This structure is used by the ramxlib routines*/

#define rmtek_1 rmtek_

/*
int getch() 
{
        int c, d;
        c = getchar();
        d = c;
        while (d != -1 && d != 10) {
                d = getchar();
        }
        if (d == -1) c = -1;
        if (c == 10) c = 32;
        return c;
}
*/


