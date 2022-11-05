This directory and its subdirectories contain the fortran language
version of LONGLIB.  The appropriate makelib*.com script should be
used to create a library archive.  Makelib*.com scripts are shown
for various fortran compilers and operating systems.  Sample compile
scripts are shown in examples/link.plottests*   Other example programs 
are also given in the examples/ subdirectory.  The meta file converter 
programs source code are contained in meta/.  The replot program is 
contained in utils/.  Note that the fortran and c meta files are NOT 
compatible.

The decw/ subdirectory includes a old vax fortran interface to X windows.
For other systems, the c code interface in the c/newx/ subdirectory
should be used.  Depending on the default compiler (whether it
appends a underscore to a file name) the files in the ff/ or fc/ directory
can be used.  These are simply interfaces from fortran to c when
a underscore is used.


Copyright info:  Longlib was written by an employee of a US government
contractor and is in the public domain.

