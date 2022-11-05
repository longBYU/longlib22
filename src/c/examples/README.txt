C programs to demonstrate longlib (originally translated from fortran
originals)

examp3d.c	The 3-d package
imagmap.c	Very simplistic image program
linetype.c	Demonstrates the various line types available
plottests.c	Demonstrate MASTER routines with multiple pages
reftest.c       Demonstrate image processing through ramtek to X
symbols.c	Plots only simple symbols
world.c		Plots a globe in 3-d with coast outline
cxexample.c	X windows application example - link with X11 library


Note: to create example .jpg or .png files in ../../doc/figures/
 1. run plottests using Y when prompted for meta file (use N for when
    prompted for screen device. The program should produce a file
    named 3.dat in the local directory
    > plottests
    Create Longlib Meta File? (Y/N) [N] Y
    Longlib Screen Graphics Device? [?=Help] N

 2. run meta/poscript using default values when prompted. This should
    produce a postscript file name out.lis
    > ../meta/postscript 3.dat
    
 3. Use the linux system utility convert to create .jpg or .png files
    (ignore RGB color space warning) produces files out-0.jpg to out-4.jpg
    or out-0.png to out-4.png  Note that the .png files have transparent
    backgrounds where as the .jpg files have a white background
    > convert out.lis out.jpg    
    > convert out.lis out.png

 4. rename out-* files to avoid them being overwritten in next step
    > mv out-0.jpg plottests0.jpg
    > mv out-1.jpg plottests1.jpg	
    > mv out-2.jpg plottests2.jpg	
    > mv out-3.jpg plottests3.jpg
    > mv out-4.jpg plottests4.jpg
    > mv out-0.png plottests0.png
    > mv out-1.png plottests1.png	
    > mv out-2.png plottests2.png	
    > mv out-3.png plottests3.png
    > mv out-4.png plottests4.png

 5. Repeat steps 1-4 for symbols and linetype
    > symbols
    Longlib Screen Graphics Device? [?=Help] N  
    > ../meta/postscript 3.dat
    > convert out.lis out.jpg    
    > convert out.lis out.png
    > mv out-0.jpg symbols0.jpg
    > mv out-1.jpg symbols1.jpg	
    > mv out-0.png symbols0.png
    > mv out-1.png symbols1.png	

    > linetype
    Longlib Screen Graphics Device? [?=Help] N  
    > ../meta/postscript 3.dat
    > convert out.lis out.jpg    
    > convert out.lis out.png
    > mv out-0.jpg linetype0.jpg
    > mv out-1.jpg linetype1.jpg	
    > mv out-0.png linetype0.png
    > mv out-1.png linetype1.png

6. Clean up by removing 3.dat and out.lis
    > rm 3.dat out.lis
    
7. Optionally copy figures to documentation area
   > cp *.jpg *.png ../../doc/figures/
