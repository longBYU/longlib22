This directory tree contains the LONGLIB graphics documentation.
The documentation was orignally written in RUNOFF but has been
converted to postscript.  Process the file longlib.tex twice
with pdflatex to produce longlib.pdf. 

The gzipped tar archive file longlib.html.tar.gz contains web pages created
from an old version of the .tex file.  To use, gunzip and untar the archive
into a directory and point the browser to longlib.html in that directory.

The LONGLIB library is a set of subroutines originally written in
DEC VAX/VMS FORTRAN that has been updated to support other fortran dialects
including gfortran. The code has been translated into archaic but workable C.
The package is designed to create line graphics, but has some support for
pixel images. The package supports three classes of graphics devices:
(1) terminals that support graphics such as Xterm and Tektronics,
(2) printers and hardcopy devices via an intermediate meta files, and
(3) pixel-based displays such as an X window or a standalone monitor (RamTek).

A general set of graphics commands provides information simultaneously to
one or more of these output classes. The line graphics commands are based
on moving a virtual pen on the surface, e.g., a "pen up" move to a position
on a virtual sheet of paper, then a "pen down" move to a series of other
positions that draws a line, followed by a "pen up" or "new pen" to change
the color/width/line-type of the pen. The positions are specified in user
units which are converted to scalled output positions for the particular
output class.  For terminals, escaped text strings are sent to switch the
display to graphics mode and then draw lines, followed by a switch back to
terminal text mode. For printers, the commands recorded in a "meta" file
which is later processed by a meta converter to generate an output file for
the particular hardcopy device desired, e.g., postcript. A "replot" program
plots the contents of the meta file to a terminal or pixel-based display.
For pixel-based displays, the pen movements are either sent directly to
the display drawing code (e.g., the X windows interface) or converted to
pixel address in an array that are set to the specified color. The array
can output to a file or display on a display (e.g., X-windows or an archaic
display monitor originally termed a "Ramtek" display in the code).

High level routines that provide pen movement comments are provided that
draw character and number strings, as well as provide finished plots with
axes in 2 or 3 dimensions.  See the examples illustrated in the figures/
directory.

The archaic nature of the code and its operation are acknowledged, but it
has a number of unique advantages. It self-contained and requires no other
libraries, other than optionally linking to X windows. It includes routines
that can draw directly into pixel arrays. This include characters. The code
is free and pieces from the library can be adapted for other uses.

Copyright info:  Longlib was originally written by an employee of a US
government contractor and is in the public domain.
