C
C *** LAST REVISED ON  4-JAN-1994 10:18:35.39
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]HIST3D.FOR
C
	SUBROUTINE HIST3D(A,INX,INY,NX,NY,PSI,PHI,THETA,
     $		DV,ZMIN,XH,YH,ZH,IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,TX,TSX,PGX,FSX,
     $		YT,NYT,YASTART,YAEND,TY,TSY,PGY,FSY,
     $		ZT,NZT,TZ,TSZ,PGZ,FSZ,AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG     FEB, 1986	AT JPL
C
C	ROUTINE TO PLOT DATA IN 3-D COLUMN FORM WITH HIDDEN LINE REMOVAL
C	USING THE INIT3DH ROUTINES.
C
C	A	(R) ARRAY A(INX,INY) CONTAINING Z AXIS DATA
C	INX,INY (I) DIMENSION OF A ARRAY
C	NX,NY	(I) INDICATING SIZE OF A ARRAY TO PLOT
C	PSI,PHI,THETA (R) ANGLES (IN DEGREES) OF INIT3DH
C	DV	(R) PERSPECTIVE FACTOR OF INIT3DH (9999 = NO PERSPECTIVE)
C		    DV < 0 DO NOT INITIALIZE INIT3DH
C	ZMIN	(R) REFERENCE PLANE VALUE FOR Z AXIS
C	XH,YH,ZH (R) LENGTH OF EACH AXIS (INCHES)
C	IFLAG	(I) PLOT FLAG
C		>1000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER
C		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT
C		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT
C		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED)
C 	(ONE'S DIGIT) = 2 USE RAM TEK COLOR CONTROL ARRAY
C		      = 1 DO NOT USE RAM TEK COLOR ARRAY
C	(TEN'S DIGIT) = 0 NO HIDDEN LINE REMOVAL FOR AXIS
C		      = 1 HIDDEN LINE REMOVAL OF AXIS
C		      = 2 NO HIDDEN LINES (SKETCH STILL USED)
C		      = 3 NO HIDDEN LINES (SKETCH NOT USED)
C 	(HUNDRED'S)   = 0 ASK WHICH SCREEN DEVICE TO USE
C		      <>0 SCREEN DEVICE CODE NUMBER
C 	IAXIS	(I) AXIS OPTION FLAG
C			= 0 DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED
C			< 0 PLOT AXIS, USE INPUT Z AXIS SCALE
C			> 0 PLOT AXIS, USE COMPUTED Z AXIS SCALE
C 	(ONE'S DIGIT)	= 1 PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED
C			= 2 PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED
C 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES
C 	NXT,NYT,NZT	(I) LENGTH OF AXIS TITLES
C			     IF ZERO THEN THAT AXIS NOT PLOTTED
C 	XASTART,YASTART	(R) AXIS START VALUES
C 	XAEND,YAEND	(R) AXIS END VALUES
C FOLLOWING ONLY ACCESSED IF IAXIS<>0
C	TX,TY,TZ	(R) NUMBER OF TICK MARKS (SEE AXIS3DH)
C	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS
C			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER)
C	PGX,PGY,PGZ	(R) ROTATION OF TEXT AND TICKS AROUND AXIS (DEG)
C	FSX,FSY,FSZ	(R) NUMBER FORMAT OF AXISES (SEE AXIS3DH)
C 	AMININ,AMAXIN 	(R) ZAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0)
C	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2)
C				ICOL(1) : AXIS COLOR
C				ICOL(2) : COLUMNS
C			    NOTE: IF SKETCH IS USED FOR BOTH AXIS AND COLUMNS
C			    THEN ENTIRE PLOT IS IN COLUMN COLOR
C
	DIMENSION A(INX,INY),PAS(2),ICOL(2)
	LOGICAL REPEAT,HIDDEN
	SAVE REPEAT
	CHARACTER*(*) XT,YT,ZT
C
	PARAMETER (IWRKSZE=100000)
	COMMON /GO/ISIZE,WORK(IWRKSZE)
	SAVE /GO/
	DATA REPEAT/.FALSE./
C
C	INSURE THAT WE HAVE AT LEAST A MINIMUM SIZE WORKSPACE
C
	IF (ISIZE.LT.IWRKSZE) ISIZE=IWRKSZE	! INCREASE WORKSPACE IF NEEDED
C
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND	!CLOSE PLOTTER
		REPEAT=.FALSE.
		RETURN
	ENDIF
C
C	DETERMINE MAX/MIN Z VALUES
C
	IF (IAXIS.LT.0) THEN
		AMAX=AMAXIN
		AMIN=AMININ
	ELSE
		AMAX=ZMIN
		AMIN=ZMIN
		DO 16 IY=1,NY			!DETERMINE MAX,MIN ARRAY VALUES
			DO 16 IX=1,NX
				AMAX=AMAX1(AMAX,A(IX,IY))
				AMIN=AMIN1(AMIN,A(IX,IY))
16		CONTINUE
	ENDIF
C
C	SMOOTH Z VALUES IF DESIRED
C
	XLEN=ABS(XH)
	YLEN=ABS(YH)
	ZLEN=ABS(ZH)
	IF (MOD(IABS(IAXIS),10).EQ.2) THEN
		PAS(1)=AMAX
		PAS(2)=AMIN
		CALL SCALE(PAS,ZLEN,2,1,1,AMIN,DAA)
		AMAX=ZLEN*DAA+AMIN
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
	IOPT=MOD(JF,10000)/10
	IF (IOPT.EQ.3) THEN
		IOPT=0
		HIDDEN=.FALSE.
	ENDIF
	JF=MOD(JF,10)
C
C	INITIALIZE 3DH PACKAGE
C
      	MNE=4			! MAX NUMBER OF EDGES
      	MNH=0			! NO HOLES
	ICORE=(25+5*MNE+4*MNH)*NX*NY*6
	IF (IAXIS.NE.0) ICORE=ICORE+10000	! ESTIMATED AXISES SPACE
	IF (ICORE.GT.ISIZE) THEN
		CALL CTERM(1)
		WRITE(*,3030)
3030		FORMAT(' *** WARNING: COMMON BLOCK /GO/ MAY BE TOO SMALL')
		CALL CTERM(-1)
	ENDIF
	SF=1.0			! SCALE FACTOR
	IF (IOPT.EQ.2) SF=-1.0	! NO HIDDEN LINE REMOVAL FOR SKETCH
	IF (DV.GT.0.) CALL INIT3DH(0.,0.,0.,PSI,PHI,THETA,SF,DV,MNE,MNH)
C
C	PLOT AXES IF DESIRED
C
	IF (IAXIS.NE.0) THEN		!PLOT AXIS LABELS
		IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(1)),0.,0) !RAM TEK COLOR
		IF (NXT.GT.0) THEN 	!PLOT X AXIS
			CALL AXIS3DH(0.,0.,0.,0.,0.,PGX,XT,
     $				NXT,XLEN,XASTART,XAEND,
     $				TX,TSX,FSX,IOPT)
		ENDIF
		IF (NYT.GT.0) THEN 	!PLOT Y AXIS
			CALL AXIS3DH(0.,0.,0.,0.,90.,PGY,YT,
     $				NYT,YLEN,YASTART,YAEND,
     $				TY,TSY,FSY,IOPT)
		ENDIF
		IF (NZT.GT.0) THEN 	!PLOT Z AXIS
			CALL AXIS3DH(0.,0.,0.,90.,0.,PGZ,ZT,
     $				NZT,-ZLEN,AMIN,AMAX,
     $				TZ,TSZ,FSZ,IOPT)
		ENDIF
	ENDIF
	IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(2)),0.,0) !RAM TEK COLOR
C
C	BEGIN SURFACE PLOTTING
C
	XXX=NX
	DX=XLEN/IABS(NX+1)
	DY=YLEN/IABS(NY+1)
	DZ=1.0
	IF (AMAX-AMIN.NE.0.0) DZ=ZLEN/(AMAX-AMIN)
	NC=5
	Z1=ZMIN
	IERR=0
C
	DO 50 IY=1,IABS(NY)		! FOR EACH Y CELL
		Y1=(IY-1)*DY
		Y2=IY*DY
		DO 50 IX=1,IABS(NX)	! FOR EACH X CELL
			X1=(IX-1)*DX
			X2=IX*DX
			Z2=(A(IX,IY)-AMIN)*DZ
			IERR=0
			IF (IX.EQ.IABS(NX).AND.IY.EQ.IABS(NY)) IERR=1
			IF(Z1.NE.Z2)CALL CUBE(X1,X2,Y1,Y2,Z1,Z2,IERR,HIDDEN)
			IF (IERR.LT.0) THEN
			 CALL CTERM(1)
			 WRITE(*,3031) IERR
3031		FORMAT(' *** WARNING: SKETCH ERROR HAS OCCURED',I3)
			 CALL CTERM(-1)
			ENDIF
 50	CONTINUE
C
C	FINISH ROUTINE
C
	IF (.NOT.HIDDEN) CALL PLT3DH(X1,Y1,Z1,3)	!PEN UP
	CALL PLOT(0.,0.,3)			!PEN UP
	IF (IFLAG.GT.0) THEN
		CALL CTERM(2)			!CLEAR TERMINAL
		CALL PLOTND			!CLOSE PLOT OUTPUT
		REPEAT=.FALSE.
	ENDIF
	IF (IFLAG.LT.0) THEN
		REPEAT=.TRUE.
		CALL CTERM(1)			!PUT TERMINAL TEXT MODE
	ENDIF
	RETURN
	END
C
	SUBROUTINE CUBE(X1,X2,Y1,Y2,Z1,Z2,IERR,HIDE)
	LOGICAL HIDE
C
C	PLOTS A 3D SOLID 'CUBE' USING SKETCH OR PLOT3DH
C
C	X1,Y1,Z1 (R) ONE CORNER OF CUBE
C	X2,Y2,Z2 (R) OPOSITE CORNER OF CUBE
C	IERR	 (I) OPTION/ERR FLAG FOR LAST CALL TO SKETCH
C	HIDE	 (L) IF TRUE USE SKETCH ELSE USE PLT3DH
C
	DIMENSION XX(5),YY(5),ZZ(5)
C
	IER=0
	NC=5
C
	XX(1)=X1
	XX(2)=X2
	XX(3)=X2
	XX(4)=X1
	XX(5)=X1
	YY(1)=Y1
	YY(2)=Y1
	YY(3)=Y2
	YY(4)=Y2
	YY(5)=Y1
	ZZ(1)=Z1
	ZZ(2)=Z1
	ZZ(3)=Z1
	ZZ(4)=Z1
	ZZ(5)=Z1
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IER)	! BOTTOM
	ELSE
		IP=3
		DO 1 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
1		CONTINUE
	ENDIF
	IF (IER.LT.0) GOTO 10
	XX(1)=X1
	XX(2)=X2
	XX(3)=X2
	XX(4)=X1
	XX(5)=X1
	YY(1)=Y1
	YY(2)=Y1
	YY(3)=Y2
	YY(4)=Y2
	YY(5)=Y1
	ZZ(1)=Z2
	ZZ(2)=Z2
	ZZ(3)=Z2
	ZZ(4)=Z2
	ZZ(5)=Z2
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IER)	! TOP
	ELSE
		IP=3
		DO 2 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
2		CONTINUE
	ENDIF
	IF (IER.LT.0) GOTO 10
	XX(1)=X1
	XX(2)=X1
	XX(3)=X1
	XX(4)=X1
	XX(5)=X1
	YY(1)=Y1
	YY(2)=Y1
	YY(3)=Y2
	YY(4)=Y2
	YY(5)=Y1
	ZZ(1)=Z1
	ZZ(2)=Z2
	ZZ(3)=Z2
	ZZ(4)=Z1
	ZZ(5)=Z1
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IER)	! LEFT SIDE
	ELSE
		IP=3
		DO 3 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
3		CONTINUE
	ENDIF
	IF (IER.LT.0) GOTO 10
	XX(1)=X2
	XX(2)=X2
	XX(3)=X2
	XX(4)=X2
	XX(5)=X2
	YY(1)=Y1
	YY(2)=Y1
	YY(3)=Y2
	YY(4)=Y2
	YY(5)=Y1
	ZZ(1)=Z1
	ZZ(2)=Z2
	ZZ(3)=Z2
	ZZ(4)=Z1
	ZZ(5)=Z1
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IER)	! RIGHT SIDE
	ELSE
		IP=3
		DO 4 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
4		CONTINUE
	ENDIF
	IF (IER.LT.0) GOTO 10
	XX(1)=X1
	XX(2)=X2
	XX(3)=X2
	XX(4)=X1
	XX(5)=X1
	YY(1)=Y1
	YY(2)=Y1
	YY(3)=Y1
	YY(4)=Y1
	YY(5)=Y1
	ZZ(1)=Z1	
	ZZ(2)=Z1
	ZZ(3)=Z2
	ZZ(4)=Z2
	ZZ(5)=Z1
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IER)	! FRONT
	ELSE
		IP=3
		DO 5 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
5		CONTINUE
	ENDIF
	IF (IER.LT.0) GOTO 10
	XX(1)=X1
	XX(2)=X2
	XX(3)=X2
	XX(4)=X1
	XX(5)=X1
	YY(1)=Y2
	YY(2)=Y2
	YY(3)=Y2
	YY(4)=Y2
	YY(5)=Y2
	ZZ(1)=Z1
	ZZ(2)=Z1
	ZZ(3)=Z2
	ZZ(4)=Z2
	ZZ(5)=Z1
	IF (HIDE) THEN
		CALL SKETCH(XX,YY,ZZ,NC,IERR)	! BACK
	ELSE
		IP=3
		DO 6 I=1,5
			CALL PLT3DH(XX(I),YY(I),ZZ(I),IP)
			IP=2
6		CONTINUE
	ENDIF
10	IERR=IER
	RETURN
	END
