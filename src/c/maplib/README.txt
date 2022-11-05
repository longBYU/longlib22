This directory contains the maplib routines.  These routines use
two files: earth and landsea. The earth file contains a low resolution
list of the boarders of the land and sea while landsea is a bit map
land/sea flag.  Before compiling these routines, modify the "mapfiles.h"
file to specify the location of these files.  The f/maplib/ subdirectory
convert/ contains two programs which can be used to create and ascii
version of the landsea file and convert the ascii version to native mode.
These are useful in porting the binary landsea file.
