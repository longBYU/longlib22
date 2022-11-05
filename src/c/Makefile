#
# Makefile for longlibX and longlib_noX
# written by D. Long at BYU 02 Nov 2022
#
LIBS = liblonglibX.a liblonglibnoX.a
EXES = examples/cxexample examples/plottests examples/symbols examples/linetype  examples/reftest examples/imagmap utils/creplot meta/postscript

XINCLUDE = /usr/include/X11
XLIB = /usr/lib/X11

# compile flags
CC = gcc -m64 -O2 -Wall -Wno-missing-braces -Wno-parentheses
CCN = gcc -m64 -Wall -Wno-missing-braces -Wno-parentheses

# location of include
CFLAGS = -I.
XCFLAGS = -I. -I$(XINCLUDE)
# location of longlibX library
LDFLAGS = -llonglibnoX
XLDFLAGS = -L. -llonglibX -lX11 -lm

.PHONY: all clean

all install: $(LIBS) $(EXES)

# instructions for examples (compiled with longlibX)
examples/cxexample : examples/cxexample.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/cxexample.c -o examples/cxexample $(XLDFLAGS) 

examples/linetype : examples/linetype.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/linetype.c -o examples/linetype $(XLDFLAGS) 

examples/plottests : examples/plottests.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/plottests.c -o examples/plottests $(XLDFLAGS)

examples/symbols : examples/symbols.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/symbols.c -o examples/symbols $(XLDFLAGS) 

examples/imagmap : examples/imagmap.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/imagmap.c -o examples/imagmap $(XLDFLAGS) 

examples/reftest : examples/reftest.c my.h liblonglibX.a
	$(CC) $(CFLAGS) examples/reftest.c -o examples/reftest $(XLDFLAGS) 

utils/creplot : utils/creplot.c my.h liblonglibX.a
	$(CC) $(CFLAGS) utils/creplot.c -o utils/creplot $(XLDFLAGS) 

meta/postscript : meta/postscript.c
	$(CC) $(CFLAGS) meta/postscript.c -o meta/postscript $(XLDFLAGS) 


# instructions for longlibnoX
liblonglibnoX.a : longlib/ll_nr.o longlib/ll_r.o longlib/util.o auxlib/arrow.o auxlib/axis.o auxlib/axis2.o auxlib/axis3.o auxlib/circle.o auxlib/cshade.o auxlib/dashl.o auxlib/ellipse.o auxlib/grid.o auxlib/hlt3d.o auxlib/lgaxs.o auxlib/lglin.o auxlib/lgrid.o auxlib/line.o auxlib/line2.o auxlib/lineoutf.o auxlib/number.o auxlib/nxtvu.o auxlib/plrax.o auxlib/plrln.o auxlib/plt3d.o auxlib/pltarc.o auxlib/rect.o auxlib/scale.o auxlib/scalg.o auxlib/shade.o auxlib/symbol.o auxlib/syms.o master/barchr.o master/cncelplt.o master/cndraw.o master/cnt3d.o master/cntln.o master/cntrplt.o master/cvax3d.o master/cvax3dx.o master/glplot.o master/hist3d.o master/interpc.o master/intersect.o master/lcntr.o master/lsplot.o master/mesh3d.o master/mvax3d.o master/phist.o master/pichrt.o master/plotlg2.o master/plotlg.o master/plotlgx.o master/plotsc2.o master/plotsc.o master/scatpl.o	master/seispl.o master/splots.o master/t3dh.o master/trig3dh.o master/vax3d.o master/vxpt3d.o 3dlib/longlib3d.o maplib/bitmap.o maplib/drawmap.o maplib/earthmap.o maplib/landmap.o maplib/polarmap.o maplib/sprect1.o maplib/worldmap.o
	ar cr liblonglibnoX.a longlib/ll_nr.o longlib/ll_ru.o longlib/util.o auxlib/arrow.o auxlib/axis.o auxlib/axis2.o auxlib/axis3.o auxlib/circle.o auxlib/cshade.o auxlib/dashl.o auxlib/ellipse.o auxlib/grid.o auxlib/hlt3d.o auxlib/lgaxs.o auxlib/lglin.o auxlib/lgrid.o auxlib/line.o auxlib/line2.o auxlib/lineoutf.o auxlib/number.o auxlib/nxtvu.o auxlib/plrax.o auxlib/plrln.o auxlib/plt3d.o auxlib/pltarc.o auxlib/rect.o auxlib/scale.o auxlib/scalg.o auxlib/shade.o auxlib/symbol.o auxlib/syms.o master/barchr.o master/cncelplt.o master/cndraw.o master/cnt3d.o master/cntln.o master/cntrplt.o master/cvax3d.o master/cvax3dx.o master/glplot.o master/hist3d.o master/interpc.o master/intersect.o master/lcntr.o master/lsplot.o master/mesh3d.o master/mvax3d.o master/phist.o master/pichrt.o master/plotlg2.o master/plotlg.o master/plotlgx.o master/plotsc2.o master/plotsc.o master/scatpl.o master/seispl.o master/splots.o master/t3dh.o master/trig3dh.o master/vax3d.o master/vxpt3d.o 3dlib/longlib3d.o maplib/bitmap.o maplib/drawmap.o maplib/earthmap.o maplib/landmap.o maplib/polarmap.o maplib/sprect1.o maplib/worldmap.o

# instructions for longlibX
liblonglibX.a : longlib/ll_nr.o longlib/ll_ru.o longlib/util.o newx/ramxlib.o newx/rterm.o auxlib/arrow.o auxlib/axis.o auxlib/axis2.o auxlib/axis3.o auxlib/circle.o auxlib/cshade.o auxlib/dashl.o auxlib/ellipse.o auxlib/grid.o auxlib/hlt3d.o auxlib/lgaxs.o auxlib/lglin.o auxlib/lgrid.o auxlib/line.o auxlib/line2.o auxlib/lineoutf.o auxlib/number.o auxlib/nxtvu.o auxlib/plrax.o auxlib/plrln.o auxlib/plt3d.o auxlib/pltarc.o auxlib/rect.o auxlib/scale.o auxlib/scalg.o auxlib/shade.o auxlib/symbol.o auxlib/syms.o master/barchr.o master/cncelplt.o master/cndraw.o master/cnt3d.o master/cntln.o master/cntrplt.o master/cvax3d.o master/cvax3dx.o master/glplot.o master/hist3d.o master/interpc.o master/intersect.o master/lcntr.o master/lsplot.o master/mesh3d.o master/mvax3d.o master/phist.o master/pichrt.o master/plotlg2.o master/plotlg.o master/plotlgx.o master/plotsc2.o master/plotsc.o master/scatpl.o master/seispl.o master/splots.o master/t3dh.o master/trig3dh.o master/vax3d.o master/vxpt3d.o 3dlib/longlib3d.o maplib/bitmap.o maplib/drawmap.o maplib/earthmap.o maplib/landmap.o maplib/polarmap.o maplib/sprect1.o maplib/worldmap.o
	ar cr liblonglibX.a longlib/ll_nr.o longlib/ll_ru.o longlib/util.o newx/ramxlib.o newx/rterm.o auxlib/arrow.o auxlib/axis.o auxlib/axis2.o auxlib/axis3.o auxlib/circle.o auxlib/cshade.o auxlib/dashl.o auxlib/ellipse.o auxlib/grid.o auxlib/hlt3d.o auxlib/lgaxs.o auxlib/lglin.o auxlib/lgrid.o auxlib/line.o auxlib/line2.o auxlib/lineoutf.o auxlib/number.o auxlib/nxtvu.o auxlib/plrax.o auxlib/plrln.o auxlib/plt3d.o auxlib/pltarc.o auxlib/rect.o auxlib/scale.o auxlib/scalg.o auxlib/shade.o auxlib/symbol.o auxlib/syms.o master/barchr.o master/cncelplt.o master/cndraw.o master/cnt3d.o master/cntln.o master/cntrplt.o master/cvax3d.o master/cvax3dx.o master/glplot.o master/hist3d.o master/interpc.o master/intersect.o master/lcntr.o master/lsplot.o master/mesh3d.o master/mvax3d.o master/phist.o master/pichrt.o master/plotlg2.o master/plotlg.o master/plotlgx.o master/plotsc2.o master/plotsc.o master/scatpl.o	master/seispl.o master/splots.o master/t3dh.o master/trig3dh.o master/vax3d.o master/vxpt3d.o 3dlib/longlib3d.o maplib/bitmap.o maplib/drawmap.o maplib/earthmap.o maplib/landmap.o maplib/polarmap.o maplib/sprect1.o maplib/worldmap.o


# instructions for key routines
longlib/ll_nr.o : longlib/ll_nr.c
	$(CC) $(CFLAGS) -Ilonglib longlib/ll_nr.c -c -o longlib/ll_nr.o

longlib/ll_r.o : longlib/ll_r.c
	$(CC) $(CFLAGS) -Ilonglib longlib/ll_r.c -c -o longlib/ll_r.o

longlib/ll_ru.o : longlib/ll_ru.c
	$(CC) $(CFLAGS) -Ilonglib longlib/ll_ru.c -c -o longlib/ll_ru.o

longlib/util.o : longlib/util.c
	$(CC) $(CFLAGS) -Ilonglib longlib/util.c -c -o longlib/util.o 

newx/ramxlib.o : newx/newramxlib.c
	$(CC) $(XCFLAGS) -c newx/newramxlib.c -o newx/ramxlib.o 

newx/rterm.o : newx/rterm.c
	$(CC) $(XCFLAGS) -c newx/rterm.c -o newx/rterm.o

# instructions for each sublibrary

# instructions for auxlib
auxlib/arrow.o : auxlib/arrow.c my.h
	$(CC) $(CFLAGS) -Iauxlib auxlib/arrow.c -c -o auxlib/arrow.o	  
auxlib/axis.o : auxlib/axis.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/axis.c -c -o auxlib/axis.o	  
auxlib/axis2.o : auxlib/axis2.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/axis2.c -c -o auxlib/axis2.o	  
auxlib/axis3.o : auxlib/axis3.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/axis3.c -c -o auxlib/axis3.o	  
auxlib/circle.o : auxlib/circle.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/circle.c -c -o auxlib/circle.o	  
auxlib/cshade.o : auxlib/cshade.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/cshade.c -c -o auxlib/cshade.o	  
auxlib/dashl.o : auxlib/dashl.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/dashl.c -c -o auxlib/dashl.o	  
auxlib/ellipse.o : auxlib/ellipse.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/ellipse.c -c -o auxlib/ellipse.o  
auxlib/grid.o : auxlib/grid.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/grid.c -c -o auxlib/grid.o	  
auxlib/hlt3d.o : auxlib/hlt3d.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/hlt3d.c -c -o auxlib/hlt3d.o	  
auxlib/lgaxs.o : auxlib/lgaxs.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/lgaxs.c -c -o auxlib/lgaxs.o	  
auxlib/lglin.o : auxlib/lglin.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/lglin.c -c -o auxlib/lglin.o	  
auxlib/lgrid.o : auxlib/lgrid.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/lgrid.c -c -o auxlib/lgrid.o	  
auxlib/line.o : auxlib/line.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/line.c -c -o auxlib/line.o	  
auxlib/line2.o : auxlib/line2.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/line2.c -c -o auxlib/line2.o	  
auxlib/lineoutf.o : auxlib/lineoutf.c my.h                         
	$(CC) $(CFLAGS) -Iauxlib auxlib/lineoutf.c -c -o auxlib/lineoutf.o
auxlib/number.o : auxlib/number.c my.h                         
	$(CC) $(CFLAGS) -Iauxlib auxlib/number.c -c -o auxlib/number.o
auxlib/nxtvu.o : auxlib/nxtvu.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/nxtvu.c -c -o auxlib/nxtvu.o	  
auxlib/plrax.o : auxlib/plrax.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/plrax.c -c -o auxlib/plrax.o	  
auxlib/plrln.o : auxlib/plrln.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/plrln.c -c -o auxlib/plrln.o	  
auxlib/plt3d.o : auxlib/plt3d.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/plt3d.c -c -o auxlib/plt3d.o	  
auxlib/pltarc.o : auxlib/pltarc.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/pltarc.c -c -o auxlib/pltarc.o	  
auxlib/rect.o : auxlib/rect.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/rect.c -c -o auxlib/rect.o	  
auxlib/scale.o : auxlib/scale.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/scale.c -c -o auxlib/scale.o	  
auxlib/scalg.o : auxlib/scalg.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/scalg.c -c -o auxlib/scalg.o	  
auxlib/shade.o : auxlib/shade.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/shade.c -c -o auxlib/shade.o	  
auxlib/symbol.o : auxlib/symbol.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/symbol.c -c -o auxlib/symbol.o	  
auxlib/syms.o : auxlib/syms.c my.h	                          
	$(CC) $(CFLAGS) -Iauxlib auxlib/syms.c -c -o auxlib/syms.o

# instructions for 3dlib
3dlib/longlib3d.o : 3dlib/longlib3d.c my.h
	$(CC) $(CFLAGS) -I3dlib 3dlib/longlib3d.c -c -o 3dlib/longlib3d.o

# instructions for master
master/barchr.o : master/barchr.c my.h	                          
	$(CC) $(CFLAGS) -Imaster master/barchr.c -c -o master/barchr.o        
master/cncelplt.o : master/cncelplt.c my.h                           
	$(CC) $(CFLAGS) -Imaster master/cncelplt.c -c -o master/cncelplt.o  
master/cndraw.o : master/cndraw.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/cndraw.c -c -o master/cndraw.o	    
master/cnt3d.o : master/cnt3d.c my.h                                 
	$(CC) $(CFLAGS) -Imaster master/cnt3d.c -c -o master/cnt3d.o	    
master/cntln.o : master/cntln.c my.h                                 
	$(CC) $(CFLAGS) -Imaster master/cntln.c -c -o master/cntln.o	    
master/cntrplt.o : master/cntrplt.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/cntrplt.c -c -o master/cntrplt.o    
master/cvax3d.o : master/cvax3d.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/cvax3d.c -c -o master/cvax3d.o	    
master/cvax3dx.o : master/cvax3dx.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/cvax3dx.c -c -o master/cvax3dx.o    
master/glplot.o : master/glplot.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/glplot.c -c -o master/glplot.o	    
master/hist3d.o : master/hist3d.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/hist3d.c -c -o master/hist3d.o	    
master/interpc.o : master/interpc.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/interpc.c -c -o master/interpc.o    
master/intersect.o : master/intersect.c my.h      		    
	$(CC) $(CFLAGS) -Imaster master/intersect.c -c -o master/intersect.o
master/lcntr.o : master/lcntr.c my.h                                 
	$(CC) $(CFLAGS) -Imaster master/lcntr.c -c -o master/lcntr.o	    
master/lsplot.o : master/lsplot.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/lsplot.c -c -o master/lsplot.o	    
master/mesh3d.o : master/mesh3d.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/mesh3d.c -c -o master/mesh3d.o	    
master/mvax3d.o : master/mvax3d.c my.h                               
	$(CCN) $(CFLAGS) -Imaster master/mvax3d.c -c -o master/mvax3d.o	    
master/phist.o : master/phist.c my.h                                 
	$(CC) $(CFLAGS) -Imaster master/phist.c -c -o master/phist.o	    
master/pichrt.o : master/pichrt.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/pichrt.c -c -o master/pichrt.o	    
master/plotlg2.o : master/plotlg2.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/plotlg2.c -c -o master/plotlg2.o    
master/plotlg.o : master/plotlg.c my.h                               
	$(CC) $(CFLAGS) -O -Imaster master/plotlg.c -c -o master/plotlg.o	    
master/plotlgx.o : master/plotlgx.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/plotlgx.c -c -o master/plotlgx.o    
master/plotsc2.o : master/plotsc2.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/plotsc2.c -c -o master/plotsc2.o    
master/plotsc.o : master/plotsc.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/plotsc.c -c -o master/plotsc.o	    
master/scatpl.o : master/scatpl.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/scatpl.c -c -o master/scatpl.o	    
master/seispl.o : master/seispl.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/seispl.c -c -o master/seispl.o	    
master/splots.o : master/splots.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/splots.c -c -o master/splots.o	    
master/t3dh.o : master/t3dh.c my.h      	                            
	$(CC) $(CFLAGS) -Imaster master/t3dh.c -c -o master/t3dh.o	    
master/trig3dh.o : master/trig3dh.c my.h                             
	$(CC) $(CFLAGS) -Imaster master/trig3dh.c -c -o master/trig3dh.o    
master/vax3d.o : master/vax3d.c my.h                                 
	$(CC) $(CFLAGS) -Imaster master/vax3d.c -c -o master/vax3d.o	    
master/vxpt3d.o : master/vxpt3d.c my.h                               
	$(CC) $(CFLAGS) -Imaster master/vxpt3d.c -c -o master/vxpt3d.o

# instructions for maplib
# note: maplib/mapfiles.h needs to be edited to specify location of files
maplib/bitmap.o : maplib/bitmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/bitmap.c -c -o maplib/bitmap.o

maplib/drawmap.o : maplib/drawmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/drawmap.c -c -o maplib/drawmap.o

maplib/earthmap.o : maplib/earthmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/earthmap.c -c -o maplib/earthmap.o

maplib/landmap.o : maplib/landmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/landmap.c -c -o maplib/landmap.o

maplib/polarmap.o : maplib/polarmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/polarmap.c -c -o maplib/polarmap.o

maplib/sprect1.o : maplib/sprect1.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/sprect1.c -c -o maplib/sprect1.o

maplib/worldmap.o : maplib/worldmap.c my.h maplib/mapfiles.h
	$(CC) $(CFLAGS) -Imaplib maplib/worldmap.c -c -o maplib/worldmap.o

clean :
	rm -f liblonglibX.a liblonglibnoX.a */*.o $(EXES)


