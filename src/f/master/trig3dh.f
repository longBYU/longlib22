C
C *** LAST REVISED ON  4-JAN-1994 10:28:42.41
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]TRIG3DH.FOR
C
	SUBROUTINE TRIG3DH(X,Y,Z,N,PSI,PHI,THETA,
     $		DV,XH,YH,ZH,IFLAG,IAXIS,
     $		XT,NXT,TX,TSX,PGX,FSX,
     $		YT,NYT,TY,TSY,PGY,FSY,
     $		ZT,NZT,TZ,TSZ,PGZ,FSZ,
     $		XAST,XAEN,YAST,YAEN,ZAST,ZAEN,ICOL)
C
C	CREATED BY D. LONG     FEB, 1986	AT JPL
C
C	ROUTINE TO PLOT DATA SPECIFIED AS (X,Y,Z) TRIPLES AS 3-D SURFACE
C	BY TRIANGULATING AND PLOTTING WITH HIDDEN LINE REMOVAL
C	USING THE INIT3DH ROUTINES.
C
C	X,Y,Z	 (R) ARRAYS CONTAINING DATA POINTS
C	N	 (I) NUMBER OF DATA POINTS
C	PSI,PHI,THETA (R) ANGLES (IN DEGREES) OF INIT3DH
C	DV	 (R) PERSPECTIVE FACTOR OF INIT3DH (9999=NO PERSPECTIVE)
C		    DV < 0 DO NOT INITIALIZE INIT3DH
C	XH,YH,ZH (R) LENGTH OF EACH AXIS (INCHES)
C	IFLAG	(I) PLOT FLAG
C		>1000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER
C		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT)
C		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT
C		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED)
C 	(ONE'S DIGIT) = 2 USE RAM TEK COLOR CONTROL ARRAY
C		      = 1 DO NOT USE RAM TEK COLOR ARRAY
C	(TEN'S DIGIT) = 0 NO HIDDEN LINE REMOVAL FOR AXIS
C		      = 1 HIDDEN LINE REMOVAL OF AXIS
C		      = 2 NO HIDDEN LINES AT ALL (SKETCH USED)
C		      = 3 NO HIDDEN LINES AT ALL (SKETCH NOT USED)
C 	(HUNDRED'S)   = 0 ASK WHICH SCREEN DEVICE TO USE
C		      <>0 SCREEN DEVICE CODE NUMBER
C 	IAXIS	(I) AXIS OPTION FLAG
C			< 0 DO NOT PLOT AXES
C 	(ONE'S DIGIT)	= 1 PLOT Z AXIS USING COMPUTED SCALE
C			= 2 PLOT Z AXIS USING COMPUTED, SMOOTHED SCALE
C			= 3 PLOT Z AXIS USING INPUT SCALE--VARIABLES ACCESSED
C			= 4 PLOT Z AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED
C 	(TEN'S DIGIT)	= 1 PLOT Y AXIS USING COMPUTED SCALE
C			= 2 PLOT Y AXIS USING COMPUTED, SMOOTHED SCALE
C			= 3 PLOT Y AXIS USING INPUT SCALE--VARIABLES ACCESSED
C			= 4 PLOT Y AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED
C 	(HUNDRED'S)	= 1 PLOT X AXIS USING COMPUTED SCALE
C			= 2 PLOT X AXIS USING COMPUTED, SMOOTHED SCALE
C			= 3 PLOT X AXIS USING INPUT SCALE--VARIABLES ACCESSED
C			= 4 PLOT X AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED
C 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES
C 	NXT,NYT,NZT	(I) LENGTH OF AXIS TITLES
C			     IF ZERO THEN AXIS NOT PLOTTED
C FOLLOWING ONLY ACCESSED IF IAXIS > 0
C	TX,TY,TZ	(R) NUMBER OF TICK MARKS (SEE AXIS3DH)
C	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS
C			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER)
C	PGX,PGY,PGZ	(R) ROTATION OF TEXT AND TICKS AROUND AXIS (DEG)
C	FSX,FSY,FSZ	(R) NUMBER FORMAT OF AXISES (SEE AXIS3DH)
C 	XAST,YAST,ZAST	(R) AXIS START VALUES
C 	XAEN,YAEN,ZAEN	(R) AXIS END VALUES
C	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2
C				ICOL(1) AXIS COLOR
C				ICOL(2) SURFACE COLOR
C			    NOTE: WHEN BOTH AXIS AND SURFACE USE SKETCH
C			    BOTH ARE PLOTTED USING SURFACE COLOR
C
	DIMENSION X(1),Y(1),Z(1),PAS(2),ICOL(2)
	LOGICAL REPEAT,HIDDEN
	SAVE REPEAT
	CHARACTER XT,YT,ZT
C
	DIMENSION XX(4),YY(4),ZZ(4)
	DIMENSION ITT(2000,3),IP(1000),IB(1000)
C
	PARAMETER (IWRKSZE=100000)
	COMMON /GO/ISIZE,WORK(IWRKSZE)
	SAVE /GO/
	DATA NZZ/2000/,NW/1000/
	DATA REPEAT/.FALSE./
C
	IF (ISIZE.LT.IWRKSZE) ISIZE=IWRKSZE	! INCREASE WORKSPACE IF NEEDED
C
	IF (N.GT.NW) THEN
		CALL CTERM(1)
		WRITE (*,3010)
3010		FORMAT(' *** WARNING: INSUFFICIENT WORKING SPACE')
		CALL CTERM(-1)
	ENDIF
C
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND	!CLOSE PLOTTER
		REPEAT=.FALSE.
		RETURN
	ENDIF
C
	XLEN=ABS(XH)
	YLEN=ABS(YH)
	ZLEN=ABS(ZH)
	IZAXIS=MOD(IABS(IAXIS),10)
	IYAXIS=MOD(IABS(IAXIS),100)/10
	IXAXIS=MOD(IABS(IAXIS),1000)/100
	IF (IXAXIS.GT.2) THEN
		XMAX=XAEN
		XMIN=XAST
	ELSE
		XMAX=X(1)
		XMIN=X(1)
		DO 16 I=1,N
			XMAX=AMAX1(XMAX,X(I))
			XMIN=AMIN1(XMIN,X(I))
16		CONTINUE
	ENDIF
	IF (IXAXIS.EQ.2.OR.IXAXIS.EQ.4) THEN
		PAS(1)=XMAX
		PAS(2)=XMIN
		CALL SCALE(PAS,XLEN,2,1,1,XMIN,DAA)
		XMAX=YLEN*DAA+XMIN
	ENDIF
C
	IF (IYAXIS.GT.2) THEN
		YMAX=YAEN
		YMIN=YAST
	ELSE
		YMAX=Y(1)
		YMIN=Y(1)
		DO 17 I=1,N
			YMAX=AMAX1(YMAX,Y(I))
			YMIN=AMIN1(YMIN,Y(I))
17		CONTINUE
	ENDIF
	IF (IYAXIS.EQ.2.OR.IYAXIS.EQ.4) THEN
		PAS(1)=YMAX
		PAS(2)=YMIN
		CALL SCALE(PAS,YLEN,2,1,1,YMIN,DAA)
		YMAX=YLEN*DAA+YMIN
	ENDIF
C
	IF (IZAXIS.GT.2) THEN
		ZMAX=ZAEN
		ZMIN=ZAST
	ELSE
		ZMAX=Z(1)
		ZMIN=Z(1)
		DO 18 I=1,N
			ZMAX=AMAX1(ZMAX,Z(I))
			ZMIN=AMIN1(ZMIN,Z(I))
18		CONTINUE
	ENDIF
	IF (IZAXIS.EQ.2.OR.IZAXIS.EQ.4) THEN
		PAS(1)=ZMAX
		PAS(2)=ZMIN
		CALL SCALE(PAS,ZLEN,2,1,1,ZMIN,DAA)
		ZMAX=ZLEN*DAA+ZMIN
	ENDIF
C
C	INTIALIZE PLOT PACKAGE
C
	JF=IABS(IFLAG)
	IF (.NOT.REPEAT.AND.JF.LT.10000) THEN
		ILU=MOD(JF,10000)/100
		CALL FRAME(3,ILU,1.5,0.65,1.)		!INTIALIZE
	ELSE
		CALL CTERM(-1)				!PUT TERMINAL IN PLOT MODE
	ENDIF
C
	HIDDEN=.TRUE.
	IOPT=MOD(JF,100)/10
	IF (IOPT.EQ.3) THEN
		IOPT=0
		HIDDEN=.FALSE.
	ENDIF
	JF=MOD(JF,10)
C
C	INITIALIZE 3DH PACKAGE
C
      	MNE=3			! MAX NUMBER OF EDGES
      	MNH=0			! NO HOLES
	ICORE=(25+5*MNE+4*MNH)*N*N  ! dimension some space
	IF (IAXIS.NE.0) ICORE=ICORE+10000	! ESTIMATED AXISES SPACE
	IF (ICORE.GT.ISIZE) THEN
		CALL CTERM(1)
		WRITE (*,3011)
3011		FORMAT('*** WARNING: COMMON BLOCK /GO/ MAY BE TOO SMALL')
		CALL CTERM(-1)
	ENDIF
	SF=1.0			! SCALE FACTOR
	IF (IOPT.EQ.2) SF=-1.0	! NO HIDDEN LINE REMOVAL
	IF (DV.GT.0.) CALL INIT3DH(0.,0.,0.,PSI,PHI,THETA,SF,DV,MNE,MNH)
C
	IF (IAXIS.NE.0) THEN		!PLOT AXIS LABELS
		IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(1)),0.,0) !RAM TEK COLOR
		IF (NXT.GT.0) THEN 	!PLOT X AXIS
			CALL AXIS3DH(0.,0.,0.,0.,0.,PGX,XT,
     $				NXT,XLEN,XMIN,XMAX,
     $				TX,TSX,FSX,IOPT)
		ENDIF
		IF (NYT.GT.0) THEN 	!PLOT Y AXIS
			CALL AXIS3DH(0.,0.,0.,0.,90.,PGY,YT,
     $				NYT,YLEN,YMIN,YMAX,
     $				TY,TSY,FSY,IOPT)
		ENDIF
		IF (NZT.GT.0) THEN 	!PLOT Z AXIS
			CALL AXIS3DH(0.,0.,0.,90.,0.,PGZ,ZT,
     $				NZT,-ZLEN,ZMIN,ZMAX,
     $				TZ,TSZ,FSZ,IOPT)
		ENDIF
	ENDIF
	IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(2)),0.,0) !RAM TEK COLOR
C
C	BEGIN SURFACE PLOTTING
C
	DX=1.0
	DY=1.0
	DZ=1.0
	IF (XMAX-XMIN.NE.0.0) DX=XLEN/(XMAX-XMIN)
	IF (YMAX-YMIN.NE.0.0) DY=YLEN/(YMAX-YMIN)
	IF (ZMAX-ZMIN.NE.0.0) DZ=ZLEN/(ZMAX-ZMIN)
C
	CALL TRIANGC(X,Y,-N,ITT,NZZ,M,IP,IB,NW,L,NZZ,IE,IBE,ITE)
	DO 50 I=1,M
		DO 15 J=1,3
			K1=ITT(I,J)
			XX(J)=(X(K1)-XMIN)*DX
			YY(J)=(Y(K1)-YMIN)*DY
			ZZ(J)=(Z(K1)-ZMIN)*DY
15		CONTINUE
		XX(4)=XX(1)
		YY(4)=YY(1)
		ZZ(4)=ZZ(1)
		NC=4
		IERR=0
		IF (I.EQ.M) IERR=1
		IF (HIDDEN) THEN
			CALL SKETCH(XX,YY,ZZ,NC,IERR)
		ELSE
			IERR=3
			DO 25 JF=1,NC
			  CALL PLT3DH(XX(JF),YY(JF),ZZ(JF),IERR)
			  IERR=2
25			CONTINUE
		ENDIF
		IF (IERR.LT.0) THEN
			CALL CTERM(1)
			WRITE(*,3012) IERR
3012			FORMAT(' *** WARNING: SKETCH ERROR HAS OCCURED',I5)
			CALL CTERM(-1)
		ENDIF
 50	CONTINUE
	IF (.NOT.HIDDEN) CALL PLT3DH(XX(JF),YY(JF),ZZ(JF),3)	!PEN UP
C
C	FINISH ROUTINE
C
	CALL PLOT(0.,0.,3)			!PEN UP
	IF (IFLAG.GT.0) THEN
		CALL CTERM(2)			!CLEAR TERMINAL
		CALL PLOTND			!CLOSE PLOT OUTPUT
		REPEAT=.FALSE.
	ENDIF
	IF (IFLAG.LT.0) THEN
		REPEAT=.TRUE.
		CALL CTERM(1)			!PUT TERMINAL IN TEXT MODE
	ENDIF
	RETURN
	END
