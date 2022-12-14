C
C *** LAST REVISED ON  8-DEC-1993 07:03:25.89
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]MLIB.FOR
C
	SUBROUTINE VAX3D(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,YT,NYT,ZT,NZT,ZASTART,ZAEND,
     $		AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG  MAR., 1984	AT JPL
C
C	SIMPLIFIES CALLING VAX3DX ROUTINE AXISES
C
	DIMENSION A(INX,INZ),ICOL(*),IC(4)
	CHARACTER*(*) XT,YT,ZT
	IAX=MOD(IAXIS,10)
	IF (IAXIS.LT.0) THEN
		AMN=AMININ
		AMX=AMAXIN
	ENDIF
	IF (MOD(IFLAG,10).EQ.2) THEN
		CALL VAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $			YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $			ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $			AMN,AMX,ICOL)
	ELSE
		CALL VAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAX,
     $			XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $			YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $			ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $			AMN,AMX,IC)
	ENDIF
	RETURN
	END
C
C
	SUBROUTINE VAX3DX(A,INX,INZ,NX,NZ,ALPHA,BETA,XH,YH,ZH,IFLAG,IAXIS,
     $		XT,NXT,XASTART,XAEND,NMX,NNX,MLX,TSX,NDX,SMX,
     $		YT,NYT,NMY,NNY,MLY,TSY,NDY,SMY,
     $		ZT,NZT,ZASTART,ZAEND,NMZ,NNZ,MLZ,TSZ,NDZ,SMZ,
     $		AMININ,AMAXIN,ICOL)
C
C	CREATED BY D. LONG     APR, 1984	AT JPL
C	REVISED BY D. LONG     MAY, 1986
C	+REDUCED REDUNDANT PEN MOTIONS AND CORRECTED SOME MINOR BUGS
C
C	ROUTINE TO PLOT DATA IN 3-D OVERLAY FORM
C
C	COORDINATE SYSTEM IS:		Y  Z
C				NAMES:	|/
C					 \X
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
C			= 0 DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED
C			< 0 PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C			> 0 PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED
C 	(ONE'S DIGIT)	= 1 PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED
C			= 2 PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED
C	(TEN'S DIGIT)	= 0 DEFAULT AXIS PARAMETERS
C			= 1 SPECIALIZED AXIS2 PARAMETERS
C 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES
C 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES
C			     IF ZERO THEN THAT AXIS NOT PLOTTED
C 	XASTART,ZASTART	REAL AXIS START VALUES
C 	XAEND,ZAEND	REAL AXIS END VALUES
C FOLLOWING ONLY ACCESSED IF TEN'S DIGIT OF IFLAG=1
C	NMX,NMY,NMZ	INT NUMBER OF MINOR TICKS BETWEEN MAJOR TICKS
C	NNX,NNY,NNZ	INT HIGHLIGHT LENGTH OF NNX-TH MINOR TICK ON AXIS
C	MLX,MLY,MLZ	INT NUMBER OF MAJOR TICK MARKS ON AXIS
C	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS
C			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER)
C 	NDX,NDY,NDZ	INT NUMBER OF DIGITS TO RIGHT OF DECIMAL POINT
C 	SMX,SMY,SMZ	REAL MAJOR TICK LENGTH
C 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0)
C	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MAG(IFLAG)=2)
C			  ICOL(1) AXIS LINE COLOR
C			  ICOL(2) AXIS NUMBERS COLOR
C			  ICOL(3) AXIS TITLE COLOR
C			  ICOL(4) AXIS EXPONENT COLOR
C			  ICOL(5) PLOT COLOR
C
	DIMENSION A(INX,INZ),AS(2),ICOL(*),IC(4)
	PARAMETER (MAXSIZE=2048)
	DIMENSION H(MAXSIZE,2),P(MAXSIZE,2)
	CHARACTER*(*) XT,YT,ZT
	LOGICAL FLAG,HHIGH,REPEAT
	COMMON /LOCATE/ XSCALE,YSCALE,ZSCALE,AMIN,ALPH,BET
	SAVE /LOCATE/,REPEAT
	DATA TPI/3.141592654/,REPEAT/.FALSE./,IP/0/
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
	IF(ALPHA.LT.0..OR.ALPHA.GT.88..OR.BETA.LT.1..OR.BETA.GT.90.)THEN
		WRITE(*,3000)
3000		FORMAT(' *** VAX3DX INPUT ANGLE ERROR ***')
		RETURN
	ENDIF
	IF (AMAX.EQ.AMIN) THEN
		WRITE(*,3001)
3001		FORMAT(' *** VAX3DX SCALE ERROR *** MAX=MIN')
		AMAX=AMIN+1.
	ENDIF
C
	XLEN=ABS(XH)
	XSCALE=XLEN/FLOAT(NX-1)
	ZLEN=ABS(ZH)
	ZSCALE=ZLEN/FLOAT(NZ-1)
	YLEN=ABS(YH)
	IF (MOD(IABS(IAXIS),10).EQ.2) THEN	! SMOOTH SCALE FACTORS
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
			IC(1)=ICOL(2)
			IC(2)=ICOL(3)
			IC(3)=ICOL(4)
			IC(4)=ICOL(5)
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
	IF (JF.EQ.2) CALL PLOT(FLOAT(ICOL(5)),0.,0) !PEN COLOR
C
C	PLOT FRONT PLATE
C
	IPEN=3
	DO 14 I=1,NX
		IF (I.GT.MAXSIZE) GOTO 999
		CALL VXPT3D(H(I,1),H(I,2),A(I,1),I,1,NX) !INTIALIZE HISTORY
		CALL PLOT(H(I,1),H(I,2),IPEN)		 !PLOT SIDE LINE
		IPEN=2
14	CONTINUE
	IHOLD=NX
	IF (BETA.EQ.90.) GOTO 5
	IF (JFF.EQ.1) GOTO 71			! DON'T PLOT SIDE PLATES
	CALL VXPT3D(XP,YP,AMIN,NX,1,NX)
	CALL PLOT(XP,YP,2)
	DO 19 I=1,NX-1				!ADD SIDE LINES
		CALL PLOT(H(I,1),H(I,2),3)
		CALL VXPT3D(XP,YP,AMIN,I,1,NX)
		CALL PLOT(XP,YP,2)
		CALL VXPT3D(XP,YP,AMIN,I+1,1,NX)
		CALL PLOT(XP,YP,2)
19	CONTINUE
C
C	PLOT SIDE PLATE
C
71	CALL PLOT(H(NX,1),H(NX,2),3)
	DO 23 I=1,NZ				!PLOT RIGHT SIDE CURVE
		IF (NX+I.GT.MAXSIZE) GOTO 999
		CALL VXPT3D(XP,YP,A(NX,I),NX,I,NX)
		H(NX+I,1)=XP
		H(NX+I,2)=YP
		CALL PLOT(XP,YP,2)
23	CONTINUE
	CALL VXPT3D(XP,YP,AMIN,NX,1,NX)
	CALL PLOT(XP,YP,3)
	IHOLD=NX+NZ				!NUMBER OF H VALUES
	IF (JFF.EQ.1) GOTO 5			!DON'T PLOT SIDE PLATES
	DO 24 I=2,NZ				!ADD SIDE LINES
		CALL VXPT3D(XP2,YP2,AMIN,NX,I,NX)
		CALL PLOT(XP2,YP2,2)
		CALL VXPT3D(XP,YP,A(NX,I),NX,I,NX)
		CALL PLOT(XP,YP,2)
		CALL PLOT(XP,YP2,3)
24	CONTINUE
C
C	BEGIN MAIN LOOP
C
   5	DO 500 IZ=2,NZ				!OVER Z DIMENSION TOWARD REAR
		IPCT=1
		IDCT=1
		IHCT=1
C
C	DETERMINE START POINT LOCATION
C
		CALL VXPT3D(XP1,YP1,A(IDCT,IZ),1,IZ,NX)	!LEFT MOST DATA POINT
C
		IF (XP1.LT.H(1,1)) THEN 	!DATA TO LEFT OF HISTORY ARRAY
C			IF (IPCT.GT.MAXSIZE) GOTO 999
C			P(IPCT,1)=XP1
C			P(IPCT,2)=YP1
C			IPCT=IPCT+1
			CALL PLOT(XP1,YP1,3)
			DO 6 I=1,NX		!(VERY RARE)
				CALL VXPT3D(XP1,YP1,A(I,IZ),I,IZ,NX)
				IF (XP1.GT.H(1,1)) THEN
					IDCT=I-1
					CALL VXPT3D(DX1,DY1,A(IDCT,IZ),
     $						IDCT,IZ,NX)
					HHIGH=.FALSE.
					HX1=H(1,1)
					HY1=H(1,2)
					HX2=H(2,1)
					HY2=H(2,2)
					IDCT=IDCT+1
					IHCT=IHCT+2
					CALL VXPT3D(DX2,DY2,A(IDCT,IZ),
     $						IDCT,IZ,NX)
					IDCT=IDCT+1
					GOTO 100
				ENDIF
				IF (IPCT.GT.MAXSIZE) GOTO 999
				P(IPCT,1)=XP1
				P(IPCT,2)=YP1
				IPCT=IPCT+1
				CALL PLOT(XP1,YP1,2)
6			CONTINUE
		ENDIF
C
		IDCT=2
		CALL VXPT3D(DX1,DY1,A(1,IZ-1),1,IZ-1,NX)
		CALL VXPT3D(DX2,DY2,A(1,IZ),1,IZ,NX)
CC		CALL PLOT(H(1,1),H(1,2),3)
		X0=H(1,1)
		Y0=H(1,2)
		IP=3
		IF (IPCT.GT.MAXSIZE) GOTO 999
		P(IPCT,1)=H(1,1)
		P(IPCT,2)=H(1,2)
		IPCT=IPCT+1
		DO 7 I=2,IHOLD
			IF (H(I,1).GT.DX1) GOTO 8
				IF (IPCT.GT.MAXSIZE) GOTO 999
				P(IPCT,1)=H(I,1)
				P(IPCT,2)=H(I,2)
				IPCT=IPCT+1
CC				CALL PLOT(H(I,1),H(I,2),2)
				X0=H(I,1)
				Y0=H(I,2)
7		CONTINUE
8		IHCT=I-1
		HX1=H(IHCT,1)
		HY1=H(IHCT,2)
		HX2=H(IHCT+1,1)
		HY2=H(IHCT+1,2)
		IHCT=IHCT+2
		HHIGH=.TRUE.
		IF (HX1.EQ.HX2) THEN
			IF (IHCT.EQ.IHOLD) GOTO 100
			IHCT=IHCT+1
			GOTO 8
		ENDIF
		AMH=(HY2-HY1)/(HX2-HX1)
		BH=HY1-HX1*AMH
		YP=AMH*DX1+BH
		IF (YP.LE.DY1) HHIGH=.FALSE.
		IF (HY1.EQ.DY1.AND.HX1.EQ.DX1) THEN
			HHIGH=.TRUE.
			YP=AMH*DX2+BH
			IF (YP.LT.DY2) HHIGH=.FALSE.
		ENDIF
C
C	TOP OF INNER LOOP
C
100		CONTINUE
			CALL INTERSECT(FLAG,X,Y,HX1,HY1,HX2,HY2,DX1,DY1
     $				,DX2,DY2,HHIGH)
			IF (FLAG) THEN		!SEGMENTS INTERSECT
				HX1=X		!DRAW SEGMENT WITH
				HY1=Y		!HIGHEST START POINT
				DX1=X		!TO THE INTERSECTION
				DY1=Y
				IF (IPCT.GT.MAXSIZE) GOTO 999
				P(IPCT,1)=X
				P(IPCT,2)=Y
				IPCT=IPCT+1
				IF (IP.EQ.2) CALL PLOT(X,Y,2)
				X0=X
				Y0=Y
				GOTO 100
			ENDIF
C
			IF (HX2.LE.DX2) THEN	!CHECKED ALL H SEGS OVER D SEGS
				IF (HHIGH) THEN !DRAW HIGHEST SEGMENT
					IF (IPCT.GT.MAXSIZE) GOTO 999
					P(IPCT,1)=HX2
					P(IPCT,2)=HY2
					IPCT=IPCT+1
					IF (IP.EQ.3) CALL PLOT(X0,Y0,3)
					CALL PLOT(HX2,HY2,2)
					X0=HX2
					Y0=HY2
					IP=2
				ENDIF
				HX1=HX2
				HY1=HY2
				HX2=H(IHCT,1)
				HY2=H(IHCT,2)
				IHCT=IHCT+1
				IF (IHCT.GT.IHOLD+1) THEN
 34					CONTINUE
					IF (IDCT.LE.NX+1) THEN
						CALL VXPT3D(X,Y,A(IDCT-1,
     $						  IZ),IDCT-1,IZ,NX)
						IF(IPCT.GT.MAXSIZE)GOTO 999
						P(IPCT,1)=X
						P(IPCT,2)=Y
						IPCT=IPCT+1
					IF (IP.EQ.3) CALL PLOT(X0,Y0,3)
						IP=2
						CALL PLOT(X,Y,2)
						IDCT=IDCT+1
						GOTO 34
					ENDIF
					GOTO 200	!DONE WITH H'S
				ENDIF
				IF (HX1.EQ.DX2) THEN
					DX1=DX2 	!NEXT DATA POINT
					DY1=DY2
					X0=DX1
					Y0=DY1
CC					IF (.NOT.HHIGH)CALL PLOT(DX1,DY1,2)
					CALL VXPT3D(DX2,DY2,A(IDCT,IZ),
     $						IDCT,IZ,NX)
					IDCT=IDCT+1
					IF (IDCT.GT.NX+2) GOTO 235!DONE WITH DATA
					IF (IDCT.GT.NX+1) THEN
						DX2=DX1
						DY2=AMIN
					ENDIF
					HHIGH=.TRUE.
					IF (DY1.GT.HY1) HHIGH=.FALSE.
				ENDIF
				GOTO 100
			ELSE
				IF (.NOT.HHIGH) THEN	!PLOT DATA THAT IS HIGHEST
					IF (IPCT.GT.MAXSIZE) GOTO 999
					P(IPCT,1)=DX2
					P(IPCT,2)=DY2
					IPCT=IPCT+1
					IF (IP.EQ.3) CALL PLOT(X0,Y0,3)
					CALL PLOT(DX2,DY2,2)
					IP=2
					X0=DX2
					Y0=DY2
				ENDIF
				DX1=DX2 	!NEXT DATA POINT
				DY1=DY2
				CALL VXPT3D(DX2,DY2,A(IDCT,IZ),IDCT,IZ,NX)
				IDCT=IDCT+1
				IF (IDCT.GT.NX+2) GOTO 235!DONE WITH DATA
				IF (IDCT.GT.NX+1) THEN
					DX2=DX1
					DY2=AMIN
				ENDIF
			ENDIF
C
C	DONE WITH INNER LOOP
C
			GOTO 100
235	CONTINUE				!FINISH H CURVE WHEN OUT OF DATA
	IHCT=IHCT-1
236	CONTINUE
	IF (IHCT.GT.IHOLD) GOTO 200
		X=H(IHCT,1)
		Y=H(IHCT,2)
		IHCT=IHCT+1
		IF (IPCT.GT.MAXSIZE) GOTO 999
		P(IPCT,1)=X
		P(IPCT,2)=Y
		IPCT=IPCT+1
CC		CALL PLOT(X,Y,2)
		IDCT=IDCT+1
	GOTO 236
C
200		IHOLD=IPCT-1			!STORE NEW HISTORY
		DO 201 I=1,IPCT
			H(I,1)=P(I,1)
			H(I,2)=P(I,2)
201		CONTINUE
C
C	END MAIN LOOP
C
500	CONTINUE
C
520	CALL PLOT(0.,0.,3)			!PEN UP
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
999	CALL CTERM(1)
	WRITE(*,3002)
3002	FORMAT(' *** VAX3DX INTERNAL MEMORY OVERFLOW ERROR ***')
	GOTO 520
	END
