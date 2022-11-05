Data files for the LONGLIB3 graphics subroutine library. 

The files are:

adips.header & ADIPS.HEADER :    text header for meta->adobe illustrator
                                 postcript converters f/meta/illus.f and lla2i.f
adips.trailer & ADIPS.TRAILER :  text trailer for meta->adobe illustrator
earth.dat & EARTH.DAT :          text coastline data
llearth000.dat & llearth.dat :   text coastline data (lon [0..360])
llearth180.dat :                 text coastline data (lon [-180..180])
lndsea1.dat & LNDSEA1.DAT:       bitmap land/ocean map used by f/maplib/lndsea.f
README.txt :                     this file

More information about the binary lndsea1.dat file is available in the
README.txt in src/f/maplib/convert/

Notes:
 - source of original coastline and landmap data unknown.
 - file names in lower case and upper case are identical and provided
   to ensure capitibilty across platforms.
