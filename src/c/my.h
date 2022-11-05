
#include <stdio.h>
#include <stdlib.h>

/* set sizes -- may need to be adjusted for different compilers/machines */
typedef int integer;         /* 4 byte integer */
typedef int logical;         /* 4 byte integer */
typedef short int shortint;  /* 2 byte integer */
typedef long int longint;    /* 8 byte integer (sometimes long long) */
typedef float real;          /* 4 byte float */
typedef double doublereal;   /* 8 byte float */

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))
#define dabs(x) (doublereal)abs(x)
#define dmin(a,b) ((a) <= (b) ? (a) : (b))
#define dmax(a,b) ((a) >= (b) ? (a) : (b))

#define TRUE_ (1)
#define FALSE_ (0)

