C
C *** LAST REVISED ON  8-DEC-1993 07:03:25.89
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]MLIB.FOR
C
	SUBROUTINE MESH3D(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,
     $		IFLAG,IAXIS,XT,NXT,XASTART,XAEND,YT,NYT,
     $		ZT,NZT,ZASTART,ZAEND,AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG  JAN 1986	AT JPL
C
C	SIMPLIFIES CALLING MESH3DX ROUTINE AXISES
C
	DIMENSION A(INX,INZ),ICOL(*),IC(5)
	CHARACTER*(*) XT,YT,ZT
	IAX=MOD(IAXIS,10)
	IF (IAXIS.LT.0) THEN
		AMN=AMININ
		AMX=AMAXIN
	ENDIF
	IF (MOD(IFLAG,10).EQ.2) THEN
		CALL MESH3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $			YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $			ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $			AMN,AMX,ICOL)
	ELSE
		CALL MESH3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $			YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $			ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $			AMN,AMX,IC)
	ENDIF
	RETURN
	END
C
C
	SUBROUTINE MESH3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,
     $		IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $		YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $		ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $		AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG     JAN 1986
C
C	ROUTINE TO PLOT DATA IN 3-D OVERLAY FORM
C	COORDINATE SYSTEM IS:		Z Y		Y  Z
C			DOCUMENTED:	|/	NAMES:	|/
C					 \ X		 \X
C
C	A	REAL ARRAY A(INX,INZ) CONTAINING VERTICAL HEIGHT DATA
C	INX,INZ INTEGERS DIMENSION OF A ARRAY
C	NX,NZ	INTEGERS INDICATING SIZE OF A ARRAY TO PLOT
C	ALPHA	REAL ANGLE (IN DEGREES) OF X AXIS (NX) FROM HORIZONTAL
C	BETA	REAL ANGLE (IN DEGREES) OF Z AXIS (NZ) FROM HORIZONTAL
C	XH,YH,ZH REAL LENGTH OF EACH AXIS
C	IFLAG	INTEGER
C		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER
C		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT
C		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT
C		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED)
C 	(ONE'S DIGIT) = 2 USE PEN COLOR CONTROL ARRAY
C		      = 1 DO NOT USE PEN COLOR ARRAY
C	(TEN'S DIGIT) = 0 PLOT SIDE PLATES
C		      = 1 DO NOT PLOT SIDE PLATES
C 	(HUNDREDS'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE
C		           <>0 SCREEN DEVICE CODE NUMBER
C 	IAXIS	INTEGER AXIS OPTION FLAG
C			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED
C			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED
C			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED
C	(TEN'S DIGIT)	= 0	DEFAULT AXIS PARAMETERS
C			= 1	SPECIALIZED AXIS2 PARAMETERS
C 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES
C 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES
C			     IF ZERO THEN THAT AXIS NOT PLOTTED
C 	XASTART,ZASTART	REAL AXIS START VALUES
C 	XAEND,ZAEND	REAL AXIS END VALUES
C ONLY ACCESSED IF TEN'S DIGIT OF IFLAG=1
C	NMX,NMY,NMZ	INT NUMBER OF MINOR TICKS BETWEEN MAJOR TICKS
C	NNX,NNY,NNZ	INT HIGHLIGHT LENGTH OF NNX-TH MINOR TICK ON AXIS
C	MLX,MLY,MLZ	INT NUMBER OF MAJOR TICK MARKS ON AXIS
C	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS
C			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER)
C 	NDX,NDY,NDZ	INT NUMBER OF DIGITS TO RIGHT OF DECIMAL POINT
C 	SMX,SMY,SMZ	REAL MAJOR TICK LENGTH
C 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0)
C	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MAG(IFLAG)=2)
C				ICOL(1) AXIS LINE COLOR
C				ICOL(2) AXIS NUMBERS COLOR
C				ICOL(3) AXIS TITLE COLOR
C				ICOL(4) AXIS TITLE COLOR
C				ICOL(5) PLOT COLOR
C
	DIMENSION A(INX,INZ),AS(2),ICOL(5),IC(4)
	CHARACTER*(*) XT,YT,ZT
	LOGICAL REPEAT
	COMMON /LOCATE/ XSCALE,YSCALE,ZSCALE,AMIN,ALPH,BET
	SAVE /LOCATE/,REPEAT
	DATA TPI/3.141592654/,REPEAT/.FALSE./
C
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND	!CLOSE PLOTTER
		REPEAT=.FALSE.
		RETURN
	ENDIF
	ALPH=ALPHA*TPI/180.		!X-AXIS INCLINATION 0-80 DEGS
	BET=BETA*TPI/180.		!Z-AXIS ANGLE 5-80 DEGS
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
	IF (ALPHA.LT.0..OR.ALPHA.GT.88..OR.BETA.LT.1..OR.BETA.GT.90.)THEN
		WRITE(*,3000)
3000		FORMAT(' *** MESH3DX INPUT ANGLE ERROR ***')
		RETURN
	ENDIF
	IF (AMAX.EQ.AMIN) THEN
		WRITE(*,3001)
3001		FORMAT(' *** MESH3DX ERROR *** MAX=MIN')
		AMAX=AMIN+1.
	ENDIF
C
	XLEN=ABS(XH)
	XSCALE=XLEN/FLOAT(NX-1)
	ZLEN=ABS(ZH)
	ZSCALE=ZLEN/FLOAT(NZ-1)
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
		ILU=JF/100
		CALL FRAME(3,ILU,1.5,0.65,1.)		!INTIALIZE
	ELSE
		CALL CTERM(-1)				!PUT TERMINAL PLOT MODE
	ENDIF
C
	IAF=IABS(IAXIS)/10
	JFF=MOD(JF,100)/100
	JF=MOD(JF,10)
	IF (IAXIS.NE.0) THEN		!PLOT AXIS LABELS
		NADD=0
		IF (JF.EQ.2) THEN
			IC(1)=ICOL(1)
			IC(2)=ICOL(2)
			IC(3)=ICOL(3)
			IC(4)=ICOL(4)
			NADD=100000	!PEN COLOR
		ENDIF
		CALL VXPT3D(XP,YP,AMIN,1,1,NX)
		DY=(AMAX-AMIN)/YLEN
		IF (NYT.GT.0) THEN 	!PLOT Y AXIS
			IF (IAF.EQ.1) THEN
				CALL AXIS2(XP,YP,YT,NYT+11000+NADD,
     $				YLEN,90.,AMIN,DY,NMY,NNY,-IABS(MLY),
     $				TSY,NDY,SMY,IC)
			ELSE
				CALL AXIS(XP,YP,YT,NYT+1000+NADD,
     $					YLEN,90.,AMIN,DY,N1,N2,IC)
			ENDIF
		ENDIF
		CALL VXPT3D(XP1,YP1,AMIN,NX,1,NX)
		DX=(XAEND-XASTART)/XLEN
		ANG=ATAN2(YP1-YP,XP1-XP)*180./TPI
		IF (NXT.GT.0) THEN
			IF (IAF.EQ.1) THEN
				CALL AXIS2(XP,YP,XT,-NXT-NADD-10000,XLEN,ANG,
     $				XASTART,DX,NMX,NNX,-IABS(MLX),TSX,NDX,SMX,IC)
			ELSE
				CALL AXIS(XP,YP,XT,-NXT-NADD,XLEN,ANG,
     $					XASTART,DX,N1,N2,IC)
			ENDIF
		ENDIF
		DZ=(ZAEND-ZASTART)/ZLEN
		IF (NZT.GT.0) THEN
			IF (IAF.EQ.1) THEN
				CALL AXIS2(XP1,YP1,ZT,-NZT-NADD-10000
     $				,ZLEN,BETA,ZASTART,DZ,NMZ,NNZ,
     $				-IABS(MLZ),TSZ,NDZ,SMZ,IC)
			ELSE
				CALL AXIS(XP1,YP1,ZT,-NZT-NADD,
     $				ZLEN,BETA,ZASTART,DZ,N1,N2,IC)
			ENDIF
		ENDIF
	ENDIF
	IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(5)),0.,0) !COLOR
C
C	PLOT FRONT PLATE
C
	IPEN=3
	DO 14 I=1,NX
		CALL VXPT3D(XP1,YP1,A(I,1),I,1,NX)
		CALL PLOT(XP1,YP1,IPEN)		 !PLOT SIDE LINE
		IPEN=2
14	CONTINUE
	IHOLD=NX
	IF (BETA.EQ.90.) GOTO 5
	IF (JFF.EQ.1) GOTO 71			! DON'T PLOT SIDE PLATES
	CALL VXPT3D(XP,YP,AMIN,NX,1,NX)
	CALL PLOT(XP,YP,2)
	DO 19 I=1,NX-1				!ADD SIDE LINES
		CALL VXPT3D(XP1,YP1,A(I,1),I,1,NX)
		CALL PLOT(XP1,YP1,3)
		CALL VXPT3D(XP,YP,AMIN,I,1,NX)
		CALL PLOT(XP,YP,2)
		CALL VXPT3D(XP,YP,AMIN,I+1,1,NX)
		CALL PLOT(XP,YP,2)
19	CONTINUE
C
C	PLOT SIDE PLATE
C
71	CALL VXPT3D(XP1,YP1,A(NX,1),NX,1,NX)
	CALL PLOT(XP1,YP1,3)
	DO 23 I=1,NZ				!PLOT RIGHT SIDE CURVE
		CALL VXPT3D(XP,YP,A(NX,I),NX,I,NX)
		CALL PLOT(XP,YP,2)
23	CONTINUE
	CALL VXPT3D(XP,YP,AMIN,NX,1,NX)
	CALL PLOT(XP,YP,3)
	IHOLD=NX+NZ				!NUMBER OF H VALUES
	IF (JFF.EQ.1) GOTO 5			! DON'T PLOT SIDE PLATES
	DO 24 I=2,NZ				!ADD SIDE LINES
		CALL VXPT3D(XP2,YP2,AMIN,NX,I,NX)
		CALL PLOT(XP2,YP2,2)
		CALL VXPT3D(XP,YP,A(NX,I),NX,I,NX)
		CALL PLOT(XP,YP,2)
		CALL PLOT(XP,YP2,3)
24	CONTINUE
C
C	PLOT MESH
C
   5	DO 500 IZ=2,NZ
		IP=3
		DO 500 IX=1,NX
			CALL VXPT3D(XP1,YP1,A(IX,IZ),IX,IZ,NX)
			CALL PLOT(XP1,YP1,IP)
			IP=2
500	CONTINUE
	DO 600 IX=1,NX-1
		IP=3
		DO 600 IZ=1,NZ
			CALL VXPT3D(XP1,YP1,A(IX,IZ),IX,IZ,NX)
			CALL PLOT(XP1,YP1,IP)
			IP=2
600	CONTINUE
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
