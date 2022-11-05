	PROGRAM REFTEST
C *** LAST REVISED ON 22-JUN-1990 09:22:24.85
C *** SOURCE FILE: [DL.GRAPHICS.LONGLIB77]REFTEST.FOR
C
C	PROGRAM TO TEST THE RAMTEK EMULATION FILE ROUTINES IN
C	LONGLIB.  INTEGER*2 IS USED IN THE TRANSFER OF IMAGE MODE
C	DATA TO RAMTEK
C
C	WRITTEN BY: DGL AUG, 1987
C
	DIMENSION X(10),Y(10)
	INTEGER*2 M(400)
C
	WRITE (*,1100)
1100	FORMAT(' RAMTEK EMULATION FILE TEST PROGRAM')
C
C	FIRST INITIALIZE LONGLIB WITH NO METAFILE AND RAMTEK OUTPUT
C
	CALL FRAME(-3,-2,1.,1.,1.)
C
C	INITIALLY WE WILL PRODUCE SOME SIMPLE LINE GRAPHICS EXAMPLES
C	THEN SHOW SOME IMAGE MODE EXAMPLES
C
	CALL SYMBOL(5.1,4.85,0.2,'REFTEST',0.0,7,-1)
	CALL SYMBOL(5.1,4.45,0.2,'Program',0.0,7,-1)
	CALL SYMBOL(5.1,4.0, 0.2,'Output',0.0,6,-1)
C
C	ENCLOSE TITLE IN BOX WITH FAT SOLID LINE
C
	CALL NEWPEN(20)
	CALL PLOT(200.0,0.0,0)
	CALL RECT(5.1,3.45,7.3,5.35)
C
C	MAKE A VERY LARGE CIRCLE
C
	CALL NEWPEN(-1)
	CALL CIRCLE(4.7,3.7,0.0,360.0,5.,5.0,0.0)
C
C	SHOW SOME MORE TEXT EXAMPLES IN DIFFERENT COLORS
C
	CALL PLOT(130.0,0.0,0)
	CALL SYMBOL(1.5,3.3,0.25,'SYMBOL Text ',45.0,11,-1)
	CALL PLOT(240.0,0.0,0)
	CALL SYMS(1.5,3.75,0.3,'SYMS Font 0 ',45.0,12,-1)
	CALL PLOT(50.0,0.0,0)
	CALL SYMS(-0.3,1.0,0.2,'|4SYMS Font 4 Text',90.0,18,-1)
C
C	SHOW AXES FOR SCALE AND ORIGIN LOCATION
C
	CALL AXIS3(-1.,0.,'X DIRECTION',11,13.,0.,-1.,12.,14.0104,
     $		-0.2,1002.,IC)
	CALL AXIS3(0.,-1.,'Y DIRECTION',-1011,13.,90.,-1.,12.,
     $		14.0104,-0.2,1002.,IC)
C
C	IDENTIFY LOCAL RELATIVE ORIGIN WITH LABEL AND ARROW
C
	CALL SYMBOL(0.5,0.5,.18,'RELATIVE ORIGIN (1,1)',0.,21,-1)
	CALL ARROW(0.45,0.5,0.6,-135.,0.12,45.0)
C
C	DRAW FULL CIRCLE WITH WIDE DOTTED LINE AND COLOR 225
C
	CALL NEWPEN(21)
	CALL PLOT(225.0,0.0,0)
	CALL CIRCLE(3.2,2.9,0.0,360.0,1.25,1.25,0.0)
C
C	DRAW SOME MORE STUFF SUCH AS A SPIRAL, TRIANGLE, AND A HEXAGON
C	WITH A UNIT WIDTH LINE TYPES
C
	CALL NEWPEN(-1)
	CALL PLOT(180.0,0.0,0)
	CALL CIRCLE(3.2,2.9,0.0,1600.0,0.2,1.0,0.0)
	CALL NEWPEN(3)
	CALL PLOT(3.2,3.7,3)
	CALL PLOT(2.5,2.4,2)
	CALL PLOT(3.95,2.4,2)
	CALL PLOT(3.2,3.7,2)
	CALL NEWPEN(2)
	CALL PLOT(90.0,0.0,0)
	CALL PLOT(2.05,2.35,3)
	CALL PLOT(2.05,3.45,2)
	CALL PLOT(3.2,4.15,2)
	CALL PLOT(4.35,3.45,2)
	CALL PLOT(4.35,2.35,2)
	CALL PLOT(3.2,1.65,2)
	CALL PLOT(2.05,2.35,2)
C
C	MAKE AN ARBITRARY REGION AND FILL IT IN USING SHADE, WE WILL
C	LABEL EXAMPLE USING NORMAL SOLID LINE TYPE AND COLOR 30 BUT SHADE
C	WITH COLOR 150
C
	CALL PLOT(30.,0.,0)
	CALL NEWPEN(0)
	CALL SYMBOL(6.2,2.9,.2,'SHADE EXAMPLE',0.,13,-1)
	X(1)=6.
	Y(1)=2.
	X(2)=7.2
	Y(2)=2.7
	X(3)=8.
	Y(3)=1.6
	X(4)=7.5
	Y(4)=0.5
	X(5)=6.2
	Y(5)=1.
	X(6)=6.5
	Y(6)=1.8
	X(7)=5.5
	Y(7)=1.
	X(8)=5.9
	Y(8)=2.
	CALL PLOT(100.0,0.0,0)
	CALL SHADE(X,Y,8,1,3,0.15,-30.,XX,1,0.,1.,0.,1.)
C
C	PLOT A FEW SIMPLE FORMS OF VARIOUS COLORS AND LINE TYPES
C
	CALL RECT(1.,1.,9.,9.)
	CALL NEWPEN(21)
	CALL PLOT(128.,0.,0)
	CALL RECT(2.,2.,8.,8.)
	CALL NEWPEN(302)
	CALL PLOT(195.,0.,0)
	CALL RECT(3.,3.,7.,7.)
	CALL NEWPEN(0)
	CALL PLOT(70.,0.,0)
	CALL CIRCLE(5.,5.,0.,360.0,1.5,1.5,0.)
	CALL PLOT(255.,0.,0)
	CALL SYMBOL(0.5,1.5,0.25,'REF Routine Test',0.,16,-1)
	CALL PLOT(0.,0.,3)
C
C	IN THE REMAINDER OF THIS PROGRAM WE WILL USE THE IMAGE MODE
C	OF THE SIMULATED RAMTEK. WE WILL PRODUCE SIMPLE TEST IMAGES.
C	FIRST MAKE A SIMPLE GREY SCALE.  FIRST GET CHANNEL NUMBER.
C
	ICHAN=IRMCHAN(IDEV)
	WRITE(*,1000) ICHAN,IDEV
1000	FORMAT(' RAMTEK CHANNEL NUMBER, DEVICE: ',I6,I6)
C
C	SET UP OUTPUT IMAGE WINDOW
C
	CALL RMWIND(ICHAN,500,500,900,900,IERR)
C
C	MAKE SMALL GREY SCALE
C
	DO 5 IX=1,400
		M(IX)=IX/2
5	CONTINUE
C
C	DUPLICATE GREY SCALE VERTICIALLY
C
	DO 10 IY=500,700
		CALL RMSTART(ICHAN,500,IY,IERR)
		CALL RMWRITEWORD(ICHAN,M,400,IERR)
10	CONTINUE
C
C	NOW MAKE A SOLID FILL WITH COLOR 255 (THE DEFAULT)
C
	CALL RMWIND(ICHAN,200,200,300,300,IERR)
	DO 15 IX=1,200
		M(IX)=255
15	CONTINUE
C
C	FILL REGION TWO LINES AT TIME
C
	DO 20 IY=200,300,2
		CALL RMSTART(ICHAN,200,IY,IERR)
		CALL RMWRITEWORD(ICHAN,M,200,IERR)
20	CONTINUE
C
C	NOW FINISH UP BY CALLING PLOTND
C
	WRITE(*,1200)
1200	FORMAT(' REF PLOTTING COMPLETE, OUTPUT TO FILE')
	CALL RTERM(2)
	CALL PLOTND
	STOP
	END
