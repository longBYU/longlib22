#
# Makefile for flonglibX and flonglib_noX
# written by D. Long at BYU 02 Nov 2022
#
LIBS = libflonglibX.a libflonglibnoX.a
EXES = utils/replot examples/plottests examples/symbols examples/linetype examples/examp3d examples/reftest examples/symtest examples/world meta/longepsf2

XINCLUDE = /usr/include/X11
XLIB = /usr/lib/X11

# compile flags
FF = gfortran -m64 -ff2c -frecord-marker=4 -ffixed-line-length-255 -O3 -Wall -Wno-tabs -Wno-unused-dummy-argument
CC = gcc -m64 -O2 -Wall -Wno-missing-braces -Wno-parentheses

# fortran compile flags used for other fortran compilers
# (gfortran) gfortran -m64 -ff2c -frecord-marker=4 -ffixed-line-length-255 -O3 -Wall -Wno-tabs -Wno-unused-dummy-argument
# (g77) g77 -fvxt -fugly-assumed -fugly-logint -fno-automatic -fno-underscoring
# (Laferty) lf95 --wide --ml cdecl --sav
# (pathscale) pathf95 -m64 -extend-source -static-data
# (SGI_ f77 -static -extend_source
# (SP) f77 -qxflag=oldtab -qfixed=120 -qsave -qflag=I:L
# (sun) f77 -cg92 -w -e -Nl99 -O4 -libmil -ext_names=plain -lnsl
# (HP) fort77 +es +E4 -K l
# (intel) ifort -m64 -extend-source -save -O3

# location of include
CFLAGS = -I.
CXFLAGS = -I. -I../c -I$(XINCLUDE)
# location of longlibX library
LDFLAGS = -llonglibnoX
XLDFLAGS = -L. -lflonglibX -lX11 -lm

.PHONY: all clean

all install: $(LIBS) $(EXES)

# instructions for examples (compiled with longlibX)
utils/replot : utils/replot.f libflonglibX.a
	$(FF) utils/replot.f -o utils/replot $(XLDFLAGS)

meta/longepsf2 : meta/longepsf2.f libflonglibnoX.a
	$(FF) meta/longepsf2.f -o meta/longepsf2 $(XLDFLAGS)

examples/plottests : examples/plottests.f libflonglibX.a
	$(FF) examples/plottests.f -o examples/plottests $(XLDFLAGS)

examples/symbols : examples/symbols.f libflonglibX.a
	$(FF) examples/symbols.f -o examples/symbols $(XLDFLAGS) 

examples/linetype : examples/linetype.f libflonglibX.a
	$(FF) examples/linetype.f -o examples/linetype $(XLDFLAGS) 

examples/examp3d : examples/examp3d.f libflonglibX.a
	$(FF) examples/examp3d.f -o examples/examp3d $(XLDFLAGS) 

examples/reftest : examples/reftest.f libflonglibX.a
	$(FF) examples/reftest.f -o examples/reftest $(XLDFLAGS) 

examples/symtest : examples/symtest.f libflonglibX.a
	$(FF) examples/symtest.f -o examples/symtest $(XLDFLAGS) 

examples/world : examples/world.f libflonglibX.a
	$(FF) examples/world.f -o examples/world $(XLDFLAGS) 

# instructions for flonglibnoX
libflonglibnoX.a : maplib/files.inc
	rm -f *.o
	$(FF) longlib/ll_nr.f -c
	$(FF) longlib/ll_ru.f -c
	$(FF) longlib/icterm.f -c
	$(FF) longlib/rterm.f -c
	$(FF) auxlib/*.f -c
	$(FF) master/*.f -c
	$(FF) 3dlib/*.f -c
	$(FF) -Imaplib maplib/*.f -c
	$(FF) color/*.f -c
	$(FF) ff/*.f -c
	$(FF) noramlib/*.f -c
	ar cr libflonglibnoX.a *.o
	rm *.o

# instructions for flonglibX
libflonglibX.a : maplib/files.inc
	rm -f *.o
	$(FF) longlib/ll_nr.f -c
	$(FF) longlib/ll_ru.f -c
	$(FF) longlib/icterm.f -c
	$(FF) longlib/rterm.f -c
	$(FF) auxlib/*.f -c
	$(FF) master/*.f -c
	$(FF) 3dlib/*.f -c
	$(FF) -Imaplib maplib/*.f -c
	$(FF) color/*.f -c
	$(FF) ff/*.f -c
	$(CC) $(CXFLAGS) ../c/newx/newramxlib.c -c
	$(CC) $(CXFLAGS) ../c/newx/extra.c -c
	$(CC) $(CXFLAGS) ../c/longlib/utilf.c -c
	ar cr libflonglibX.a *.o
	rm *.o

clean :
	rm -f libflonglibX.a libflonglibnoX.a *.o $(EXES)


