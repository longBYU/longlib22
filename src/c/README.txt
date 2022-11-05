This directory and its subdirectories contain the c language version
of LONGLIB.  The Makefile can be used to create library archive. Two
versions are made. One with ramtek X11 interface and the other with
"dummy" ramtek routines that do nothing.  Compiling the code with the
reflib/reflib.c uses a pixel array.

Example programs are in examples/ subdirectory.  The meta file converter
programs source code is contained in meta/.  The "creplot" program is
contained in utils/.  It replots the meta file to a terminal or
ramtek display Note that the fortran and c meta files are NOT compatible.

Note that the c code in the newx/ subdirectory is also used by the
fortran version of the library for interfacing to X windows
on unix or linux machine.

Copyright info:  Longlib was written by an employee of a US government
contractor and is in the public domain.
