C
C *** LAST REVISED ON  4-JAN-1994 10:21:30.72
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]MVAX3D.FOR
C
	SUBROUTINE MVAX3D(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,
     $		IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,YT,NYT,ZT,NZT,ZASTART,ZAEND,
     $		AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG  AUG 1987	AT JPL
C
C	SIMPLIFIES CALLING MVAX3DX ROUTINE
C
	DIMENSION A(INX,INZ),ICOL(*),IC(4)
	CHARACTER*(*) XT,YT,ZT
	IAX=MOD(IAXIS,100)
	IF (IAXIS.LT.0) THEN
		AMN=AMININ
		AMX=AMAXIN
	ENDIF
	IF (MOD(IABS(IFLAG),10).EQ.2) THEN
		CALL MVAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,TX,TSX,FDX,
     $			YT,NYT,TY,TSY,FDY,
     $			ZT,NZT,ZASTART,ZAEND,TZ,TSZ,FDZ,
     $			AMN,AMX,ICOL)
	ELSE
		CALL MVAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,TX,TSX,FDX,
     $			YT,NYT,TY,TSY,FDY,
     $			ZT,NZT,ZASTART,ZAEND,TZ,TSZ,FDZ,
     $			AMN,AMX,IC)
	ENDIF
	RETURN
	END
C
C ********************************************************************
C
	SUBROUTINE MVAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,
     $		IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,TX,TSX,FDX,
     $		YT,NYT,TY,TSY,FDY,
     $		ZT,NZT,ZASTART,ZAEND,TZ,TSZ,FDZ,
     $		AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG     AUG 1987	AT JPL
C
C	ROUTINE TO PLOT DATA IN 3-D MESH OR HISTOGRAM COLUMN FORM
C	WITH HIDDEN LINE REMOVAL USING PLT3D OR HLT3D
C
C	COORDINATE SYSTEM HAS ORIGIN AT UPPER LEFT CORNER
C					Y
C			VARIABLE NAMES:	|	
C				      Z/ \X
C
C	A	REAL ARRAY A(INX,INZ) CONTAINING VERTICAL HEIGHT DATA
C	INX,INZ INTEGERS DIMENSION OF A ARRAY
C	NX,NZ	INTEGERS INDICATING SIZE OF A ARRAY TO PLOT
C	ALPHA	REAL ANGLE (IN DEGREES) OF X AXIS (NX) (ALTITUDE)
C	BETA	REAL ANGLE (IN DEGREES) OF Z AXIS (NZ) (AZIMUTH)
C	XH,YH,ZH REAL LENGTH OF EACH AXIS
C	IFLAG	INTEGER
C		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER
C		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT
C		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT
C		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED)
C 	(ONE'S DIGIT) = 2 USE PEN COLOR CONTROL ARRAY
C		      = 1 DO NOT USE PEN COLOR ARRAY
C	(TEN'S DIGIT) = 0 PLOT MESH WITH SIDE PLATES (LOWER SURFACE NOT SHOWN)
C		      = 1 MESH W/O SIDE PLATES (LOWER SIDE SURFACE SHOWN
C			  USING SOLID LINE)
C		      = 2 MESH W/O SIDE PLATES (LOWER SIDE SURFACE SHOWN
C			  USING DOTTED LINE)
C		      = 3 MESH W/O SIDE PLATES (LOWER SIDE SURFACE NOT SHOWN)
C		      = 4 HISTOGRAM COLUMNS (LOWER SIDE SURFACE SHOWN
C			  USING SOLID LINE)
C		      = 5 HISTOGRAM COLUMNS (LOWER SIDE SURFACE SHOWN
C			  USING DOTTED LINE)
C		      = 6 HISTOGRAM COLUMNS (LOWER SIDE SURFACE NOT SHOWN)
C 	(HUNDREDS'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE
C		           <>0 SCREEN DEVICE CODE NUMBER
C 	IAXIS	INTEGER AXIS OPTION FLAG
C			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED
C			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED
C			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED
C	(TEN'S DIGIT)	= 0	BACK PLANE PLOTTED
C			= 1	BACK PLANE NOT PLOTTED
C	(HUNDRED'S)	= 0	DEFAULT AXIS PARAMETERS
C			= 1	SPECIALIZED AXIS3 PARAMETERS
C 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES
C 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES
C			     IF ZERO THEN THAT AXIS NOT PLOTTED
C 	XASTART,ZASTART	REAL AXIS START VALUES
C 	XAEND,ZAEND	REAL AXIS END VALUES
C ONLY ACCESSED IF TEN'S DIGIT OF IAXIS=1
C	TX,TY,TZ	REAL TICK MARK PATTERN (SEE AXIS3)
C	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS
C			  IF <0 DO NOT AUTO-SCALE AXIS BY (x10^POWER)
C 	FDX,FDY,FDZ	REAL AXIS NUMBER LABEL FORMAT (SEE AXIS3)
C 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0)
C	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MOD(IFLAG,10)=2)
C				ICOL(1) AXIS LINE COLOR
C				ICOL(2) AXIS NUMERIC LABEL COLOR
C				ICOL(3) AXIS TITLE COLOR
C				ICOL(4) AXIS EXPONENT COLOR
C				ICOL(5) BACK PLANE COLOR (RETURN)
C				ICOL(6) TOP SURFACE COLOR
C				ICOL(7) BOTTOM SURFACE COLOR
C
	DIMENSION A(INX,INZ),AS(2),ICOL(*),IC(4)
	CHARACTER*(*) XT,YT,ZT
	LOGICAL REPEAT
	SAVE REPEAT
C
C	WORKING SPACE
C
	PARAMETER (NW2D0=6000)
	DIMENSION W2(NW2D0)
C
	COMMON /PLT3B/A1,A2,A3,B1,B2,B3,B4
	SAVE /PLT3B/
	DATA TPI/3.141592654/,REPEAT/.FALSE./
C
	XFORM(I,J,AV)=A1*J+A2*I+A3
	YFORM(I,J,AV)=B1*J+B2*I+B3*AV+B4
C
C	INTIALIZE ROUTINE AND PLOT PACKAGE IF ACCESSED
C
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND	!CLOSE PLOTTER
		REPEAT=.FALSE.
		RETURN
	ENDIF
C
	IF (IAXIS.LT.0) THEN
		AMAX=AMAXIN
		AMIN=AMININ
	ELSE
		AMAX=A(1,1)
		AMIN=A(1,1)
		DO 16IZ=1,NZ			!DETERMINE MAX,MIN ARRAY VALUES
			DO 16 IX=1,NX
				AMAX=AMAX1(AMAX,A(IX,IZ))
				AMIN=AMIN1(AMIN,A(IX,IZ))
16		CONTINUE
	ENDIF
	XLEN=ABS(XH)
	ZLEN=ABS(ZH)
	YLEN=ABS(YH)
	IF (MOD(IABS(IAXIS),10).EQ.2) THEN
		AS(1)=AMAX
		AS(2)=AMIN
		CALL SCALE(AS,YLEN,2,1,1,AMIN,DAA)
		AMAX=YLEN*DAA+AMIN
	ENDIF
	YSCALE=1.0
	IF (AMAX-AMIN.NE.0.0) YSCALE=YLEN/(AMAX-AMIN)
C
C	INTIALIZE PLOT PACKAGE
C
	JF=IABS(IFLAG)
	IF (.NOT.REPEAT.AND.JF.LT.10000) THEN
		ILU=JF/100				!GRAPHICS DEVICE CODE
		CALL FRAME(3,ILU,1.5,1.0,1.)		!INTIALIZE
	ELSE
		CALL CTERM(-1)				!PUT TERMINAL IN PLOT MODE
	ENDIF
C
	IAFF=IABS(IAXIS)/100				!AXIS TYPE
	IAF=MOD(IABS(IAXIS),100)/10			!BACK PANEL
	JFF=MOD(JF,100)/10				!SIDE PLATES/SUFACE
	JF=MOD(JF,10)					!COLORS
C
C	PLOT SURFACE WITH SIMPLE HIDDEN LINE REMOVAL
C
	XP=XLEN/2.*COSD(ALPHA)+2.0
	YP=-(XLEN/2.+YLEN/2.)*SIND(ALPHA)*SIND(BETA+180.)-YSCALE*AMIN
	NW1D=1
	NW2D=NW2D0-10
	IF (JFF.LT.4) THEN
		NW1D=4*MAX(NX,NZ)
		NW2D=NW2D0-NW1D-1
		IF (NW2D.LT.NW1D) GOTO 42
	ENDIF
	NW=NW2D+1
C
	IF (JFF.NE.0.AND.JFF.NE.3.AND.JFF.NE.6) THEN
C
C	IF WE DON'T PLOT SIDE PLATES THEN PLOT UNDERSIDE OF SURFACE
C
		IF (JFF.EQ.1.OR.JFF.EQ.4) CALL NEWPEN(2)
		IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(7)),0.,0)
		IF (JFF.LT.3) THEN
		 CALL PLT3D(A,INX,INZ,NX,NZ,W2(NW),NW1D,W2,NW2D,
     $		 ALPHA,180.+BETA,-XLEN,XP,ZLEN,YP,YSCALE,0.,IERR)
		ELSE
		 CALL HLT3D(A,INX,INZ,NX,NZ,W2,NW1D,W2,NW2D,
     $		 ALPHA,180.+BETA,-XLEN,XP,ZLEN,YP,YSCALE,0.,IERR)
		ENDIF
		IF (JFF.EQ.1.OR.JFF.EQ.4) CALL NEWPEN(1)
		IF (IERR.NE.0) GOTO 42
C
C	IF BACK PANEL IS DESIRED, PLOT LOWER SIDE OF BACK PANEL
C
	IF (IAXIS.NE.0) THEN
		DY=1./YSCALE
		IF (NYT.GT.0) THEN 	!PLOT Y AXIS
			IF (IAFF.EQ.1) THEN
			  N1=INT(TY)
			ELSE
			  N1=IFIX(YLEN+.5)+1
			ENDIF
			IF (IAF.EQ.0) THEN
		IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(5)),0.,0)
				 VAL2=(N1-1)*DY+AMIN
				 W2(  NW)=XFORM(1,NZ,VAL2)
				 W2(1+NW)=YFORM(1,NZ,VAL2)
				 W2(2+NW)=XFORM(1,1,VAL2)
				 W2(3+NW)=YFORM(1,1,VAL2)
				 W2(4+NW)=XFORM(NX,1,VAL2)
				 W2(5+NW)=YFORM(NX,1,VAL2)
			CALL NXTVU(-2,W2(NW),3,W2,NW2D,IERR)
				 IF (IERR.NE.0) GOTO 42
				DO 338 K=1,N1-1
				 VAL1=(N1-K-1)*DY+AMIN
				 W2(  NW)=XFORM(1,NZ,VAL2)
				 W2(1+NW)=YFORM(1,NZ,VAL2)
				 W2(2+NW)=XFORM(1,NZ,VAL1)
				 W2(3+NW)=YFORM(1,NZ,VAL1)
				 W2(4+NW)=XFORM(1,1,VAL1)
				 W2(5+NW)=YFORM(1,1,VAL1)
				 W2(6+NW)=XFORM(1,1,VAL2)
				 W2(7+NW)=YFORM(1,1,VAL2)
			CALL NXTVU(-2,W2(NW),4,W2,NW2D,IERR)
				 IF (IERR.NE.0) GOTO 42
				 W2(  NW)=XFORM(1,1,VAL1)
				 W2(1+NW)=YFORM(1,1,VAL1)
				 W2(2+NW)=XFORM(NX,1,VAL1)
				 W2(3+NW)=YFORM(NX,1,VAL1)
				 W2(4+NW)=XFORM(NX,1,VAL2)
				 W2(5+NW)=YFORM(NX,1,VAL2)
			CALL NXTVU(-2,W2(NW),3,W2,NW2D,IERR)
				 IF (IERR.NE.0) GOTO 42
338				CONTINUE
			ENDIF
		ENDIF
	ENDIF
C
	ENDIF
C
C	PLOT TOP SIDE OF SURFACE
C
	IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(6)),0.,0)
	IF (JFF.LT.4) THEN
	   CALL PLT3D(A,INX,INZ,NX,NZ,W2(NW),NW1D,W2,NW2D,ALPHA,
     $		180.+BETA,XLEN,XP,ZLEN,YP,YSCALE,0.,IERR)
	ELSE
	   CALL HLT3D(A,INX,INZ,NX,NZ,W2,NW1D,W2,NW2D,ALPHA,
     $		180.+BETA,XLEN,XP,ZLEN,YP,YSCALE,0.,IERR)
	ENDIF
C
	IF (IERR.EQ.0) GOTO 43
42	CALL CTERM(1)
	WRITE(*,1) IERR
1	FORMAT(' *** ERROR CALLING PLT3D/HLT3D IN MVAX3DX *** '/
     $	 ' *** INTERNAL WORK SPACE EXCEEDED ***',I2)
	RETURN
43	CONTINUE
C
C	ADD SIDE PLATES
C
	IF (JFF.NE.0) GOTO 71			! DON'T PLOT SIDE PLATES
	DO 4335 I=1,NX
		XP=XFORM(I,NZ,AMIN)
		YP=YFORM(I,NZ,AMIN)
		XP1=XFORM(I,NZ,A(I,NZ))
		YP1=YFORM(I,NZ,A(I,NZ))
		IF (MOD(I,2).EQ.0) THEN
			CALL PLOT(XP,YP,3)
			CALL PLOT(XP1,YP1,2)
		ELSE
			CALL PLOT(XP1,YP1,3)
			CALL PLOT(XP,YP,2)
		ENDIF
4335	CONTINUE
	DO 4336 J=2,NZ
		JJ=NZ-J+1
		XP=XFORM(NX,JJ,AMIN)
		YP=YFORM(NX,JJ,AMIN)
		XP1=XFORM(NX,JJ,A(NX,JJ))
		YP1=YFORM(NX,JJ,A(NX,JJ))
		IF (MOD(J,2).EQ.0) THEN
			CALL PLOT(XP,YP,3)
			CALL PLOT(XP1,YP1,2)
		ELSE
			CALL PLOT(XP1,YP1,3)
			CALL PLOT(XP,YP,2)
		ENDIF
4336	CONTINUE
C
C	DRAW BOTTOM LINE
C
	XP=XFORM(NX,1,AMIN)
	YP=YFORM(NX,1,AMIN)
	CALL PLOT(XP,YP,3)
	XP=XFORM(NX,NZ,AMIN)
	YP=YFORM(NX,NZ,AMIN)
	CALL PLOT(XP,YP,2)
	XP=XFORM(1,NZ,AMIN)
	YP=YFORM(1,NZ,AMIN)
	CALL PLOT(XP,YP,2)
C
C	PLOT AXIS LABELS
C
71	CONTINUE
	IF (IAXIS.NE.0) THEN		!PLOT AXIS LABELS
		NADD=0
		IF (JF.EQ.2) THEN
			NADD=100000
			IC(1)=ICOL(1)
			IC(2)=ICOL(2)
			IC(3)=ICOL(3)
			IC(4)=ICOL(4)
		ENDIF
		XP=XFORM(NX,NZ,AMIN)
		YP=YFORM(NX,NZ,AMIN)
		XP1=XFORM(1,NZ,AMIN)
		YP1=YFORM(1,NZ,AMIN)
		ANG=ATAN2(YP-YP1,XP-XP1)*180./TPI
		ZLEN1=SQRT((XP-XP1)**2+(YP-YP1)**2)
		IF (NXT.GT.0) THEN	! PLOT X AXIS
			IF (IAFF.EQ.1) THEN
			  CALL AXIS3(XP1,YP1,XT,-NADD-NXT,ZLEN1,
     $					ANG,XASTART,XAEND,TX,
     $					TSX,FDX,IC)
			ELSE
			  VAL1=INT(XLEN+.5)+1.
			  CALL AXIS3(XP1,YP1,XT,-NADD-NXT,ZLEN1,
     $					ANG,XASTART,XAEND,VAL1,
     $					0.15,4.01,IC)
			ENDIF
		ENDIF
		XP1=XFORM(NX,1,AMIN)
		YP1=YFORM(NX,1,AMIN)
		ANG=ATAN2(YP1-YP,XP1-XP)*180./TPI
		ZLEN1=SQRT((XP1-XP)**2+(YP1-YP)**2)
		IF (NZT.GT.0) THEN		! PLOT Z AXIS
			IF (IAFF.EQ.1) THEN
			  CALL AXIS3(XP,YP,ZT,-NADD-NZT,ZLEN1,
     $					ANG,ZAEND,ZASTART,TZ,
     $					TSZ,FDZ,IC)
			ELSE
			  VAL1=INT(ZLEN+.5)+1.
			  CALL AXIS3(XP,YP,ZT,-NADD-NZT,ZLEN1,
     $					ANG,ZAEND,ZASTART,VAL1,
     $					0.15,4.01,IC)
			ENDIF
C
C	PLOT Y AXISES
C
		ENDIF
		DY=1./YSCALE
		XP1=XFORM(NX,NZ,AMAX)
		YP1=YFORM(NX,NZ,AMAX)
		ZLEN1=SQRT((XP1-XP)**2+(YP1-YP)**2)
		IF (NYT.GT.0) THEN 	!PLOT Y AXIS
			XP=XFORM(1,NZ,AMIN)	! LEFT SIDE
			YP=YFORM(1,NZ,AMIN)
			XP1=XFORM(NX,1,AMIN)	! RIGHT SIDE
			YP1=YFORM(NX,1,AMIN)
			IF (IAFF.EQ.1) THEN
			  CALL AXIS3(XP,YP,YT,NADD+NYT,ZLEN1,
     $					90.,AMIN,AMAX,TY,
     $					TSY,FDY,IC)
			  CALL AXIS3(XP1,YP1,YT,-NADD-NYT,ZLEN1,
     $					90.,AMIN,AMAX,TY,
     $					TSY,FDY,IC)
			  N1=INT(TY)	! MAJOR AXIS TICKS
			ELSE
			  VAL1=INT(YLEN+.5)+1.
			  CALL AXIS3(XP,YP,YT,NADD+NYT,ZLEN1,
     $				90.,AMIN,AMAX,VAL1,0.15,4.01,IC)
			  CALL AXIS3(XP1,YP1,YT,-NADD-NYT,ZLEN1,
     $				90.,AMIN,AMAX,VAL1,0.15,4.01,IC)
			  N1=IFIX(YLEN+.5)+1
			ENDIF
C
C	PLOT BACK PANEL
C
			IF (IAF.EQ.0) THEN
		IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(5)),0.,0)
				DO 4338 K=1,N1
				 VAL1=(K-1)*DY+AMIN
				 W2(NW)=XFORM(1,NZ,AMIN)
				 W2(1+NW)=YFORM(1,NZ,AMIN)
				 W2(2+NW)=XFORM(1,NZ,VAL1)
				 W2(3+NW)=YFORM(1,NZ,VAL1)
				 W2(4+NW)=XFORM(1,1,VAL1)
				 W2(5+NW)=YFORM(1,1,VAL1)
				 W2(6+NW)=XFORM(1,1,AMIN)
				 W2(7+NW)=YFORM(1,1,AMIN)
			CALL NXTVU(2,W2(NW),4,W2,NW2D,IERR)
				 IF (IERR.NE.0) GOTO 42
				 W2(NW)=XFORM(1,1,VAL1)
				 W2(1+NW)=YFORM(1,1,VAL1)
				 W2(2+NW)=XFORM(NX,1,VAL1)
				 W2(3+NW)=YFORM(NX,1,VAL1)
				 W2(4+NW)=XFORM(NX,1,AMIN)
				 W2(5+NW)=YFORM(NX,1,AMIN)
			CALL NXTVU(2,W2(NW),3,W2,NW2D,IERR)
				 IF (IERR.NE.0) GOTO 42
4338				CONTINUE
			ENDIF
		ENDIF
	ENDIF
C
C	FINISH UP
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