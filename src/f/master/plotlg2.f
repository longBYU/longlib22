C
C *** LAST REVISED ON  8-DEC-1993 07:03:25.89
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]MLIB.FOR
C
	SUBROUTINE PLOTLG2(X,Y,NN,NP,IFLAG,NSYM,XAXL,YAXL,XTITL,NXT,
     1		YTITL,NYT,TITLE,NT,XMIN,XMAX,YMIN,YMAX,ICOL,ILINE)
C
C	CREATED BY D. LONG       OCT, 1983	AT JPL
C	REVISED BY D. LONG     FEB, 1986 -- ADDED LINE TYPE ARRAY
C
C	ROUTINE TO PLOT SEVERAL LINES OF DATA IN LOG/LINEAR COMBINATION
C
C	X	REAL X VALUE ARRAY
C	Y	REAL Y DATA ARRAY DIMENSION Y(NP,NN)
C	NN	INT  # NUMBER OF ARRAYS
C	NP	INT  # OF POINTS IN ARRAY
C	IFLAG	INT
C	  (MAG) >10000 REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER
C		< 0  REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT)
C		= 0  CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT
C		> 0  SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED)
C	  (ONE'S DIGIT) = 1 X LINEAR, Y LOGRITHMIC (BASE 10)
C	  (ONE'S DIGIT) = 2 X LOGRITHMIC,Y LINEAR
C	  (ONE'S DIGIT) = 3 X LOGRITHMIC,Y LOGRITHMIC
C	  (ONE'S DIGIT) = 4 X LINEAR, Y LINEAR
C	  (TEN'S DIGIT) = 0 NO AXIS OR GRID 
C	  (TEN'S DIGIT) = 1 PLOT BOX WITH AXIS TICKS
C	  (TEN'S DIGIT) = 2 PLOT SOLID GRID
C	  (TEN'S DIGIT) = 3 PLOT TICKED GRID W/O BOX
C	  (TEN'S DIGIT) = 4 PLOT TICKED GRID WITH BOX
C	  (TEN'S DIGIT) = 5 PLOT BOX WITH AXIS TICKS AND TICKED GRID
C	  (TEN'S DIGIT) = 6 PLOT W/O BOX OR GRID BUT USE AXISES
C	  (TEN'S DIGIT) = 7 PLOT SOLID LOGRITHMIC GRID
C	  (TEN'S DIGIT) = 8 PLOT DOTTED LOGRITHMIC GRID
C	  (TEN'S DIGIT) = 9 PLOT TICKED LOGRITHMIC GRID
C     (HUNDRED'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE
C		      <>0 SCREEN DEVICE CODE NUMBER
C	NSYM	INT   NUMBER OF POINTS BETWEEN SYMBOLS
C		      < 0  SYMBOLS ONLY, NO LINE
C		      = 0  NO SYMBOLS, LINE ONLY
C		      > 0 NUMBER OF POINTS BETWEEN SYMBOLS
C	XAXL	REAL  X AXIS LENGTH IN INCHES
C		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED
C		> 0  USE AUTO SCALING--AXIS PLOTTED
C	YAXL	REAL  Y AXIS LENGTH IN INCHES
C		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED
C		> 0  USE AUTO SCALING--AXIS PLOTTED
C
C NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ONLY ACCESSED IF XAXL OR YAXL < 0
C
C	XTITL	CHAR  X AXIS TITLE
C	NXT	INT   NUMBER OF CHARACTERS IN X AXIS TITLE STRING
C		< 0  TICKS ON INSIDE OF AXIS
C		= 0  NO AXIS
C		> 0  TICKS ON TITLE SIDE OF AXIS
C	YTITL	CHAR  Y AXIS TITLE
C	NYT	INT   NUMBER OF CHARACTERS IN Y AXIS TITLE STRING
C		< 0  TICKS ON INSIDE OF AXIS
C		= 0  NO AXIS
C		> 0  TICKS ON TITLE SIDE OF AXIS
C	TITLE	CHAR  PLOT TITLE
C	NT	INT   NUMBER OF CHARACTERS IN PLOT TITLE
C		= 0  NO TITLE
C		< 0  USE PEN COLOR ARRAY
C			IF IABS(NT)/100)>1 USE LINE TYPE ARRAY
C		      (REQUIRES XMIN,XMAX,YMIN,YMAX BE PRESENT)
C	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS
C	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS
C	YMIN	REAL  MINIMUM VALUE OF Y ARRAY
C	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY
C	ICOL	INT   ARRAY OF PEN COLORS DIMENSIONED ICOL(5+NN)
C			ICOL(1) = GRID COLOR
C			ICOL(2) = AXIS LINE COLOR
C			ICOL(3) = AXIS NUMBERS COLOR
C			ICOL(4) = AXIS TITLE COLOR
C			ICOL(5) = AXIS EXPONENT COLOR
C			ICOL(6) = TITLE COLOR (COLOR UPON RETURN)
C			ICOL(7) = LINE COLOR 1
C			ICOL(8) = LINE COLOR 2
C			   .	     .	     3
C	ILINE	INT  LINE TYPE ARRAY FOR LINES DIMENSIONED ILINE(NN)
C
	CHARACTER*(*) XTITL,YTITL,TITLE
	REAL Y(NP,NN),X(NP),PY(2)
	LOGICAL REPEAT
	INTEGER PL,ICOL(*),IC(4),ILINE(*)
	COMMON /CPLOTLG2/XM,DX,YM,DY
	SAVE /CPLOTLG2/,REPEAT
	DATA REPEAT/.FALSE./
C
	PL=3					!PRINTER DATA FILE= FOR003.DAT
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND !CLOSE PLOT PACKAGE
		REPEAT=.FALSE.
		RETURN
	ENDIF
	JF=IABS(IFLAG)
	IF (.NOT.REPEAT.AND.JF.LT.10000) THEN
		ILU=-(JF/100)			!SCREEN DEVICE, CLEAR SCREEN
		CALL FRAME(PL,ILU,1.2,1.2,1.)	!INTIALIZE PLOT PACKAGE
	ELSE
		CALL CTERM(-1)			!RESTORE PLOT MODE
C		CALL NEWPAGE			!NEW PAGE
		JF=MOD(JF,100)
	ENDIF
	JF=MOD(JF,100)
	IF=JF
	IF (IF.GT.10) IF=MOD(IF,10)
	JF=JF-IF
	NX=int(ABS(ANINT(XAXL)))			!GRID SIZES
	NY=int(ABS(ANINT(YAXL)))
	IF (XAXL.GT.0.0) THEN				!INPUT SCALING
	    XM=X(1)
	    DX=X(1)
	    DO 5 I=2,NP
		XM=MAX(X(I),XM)
		DX=MIN(X(I),DX)
 5	    CONTINUE
	    PY(1)=XM
	    PY(2)=DX
	    IF (IF.EQ.2.OR.IF.EQ.3) THEN
		CALL SCALG(PY,ABS(XAXL),2,1,1,XM,DX)	!SMOOTH SCALE FACTORS
		IK=-1
		GDX=1./DX
		NX=int(DX*ABS(XAXL))
		INX=-1
	    ELSE
		CALL SCALE(PY,ABS(XAXL),2,1,1,XM,DX)	!SMOOTH SCALE FACTORS
		IK=0
		GDX=1.
		INX=1
	    ENDIF
	ELSE
	    IF (IF.EQ.2.OR.IF.EQ.3) THEN
		XM=(ABS(XMIN)+1.E-25)
		IF (XM.NE.AINT(XM)) XM=AINT(XM)-1.
		DX=AINT(ALOG10(ABS(XMAX)+1.E-25))+1.
		DX=(DX-XM)/ABS(XAXL)
		GDX=1./DX
		IK=-1
		NX=int(DX*ABS(XAXL))
		INX=-1
	    ELSE
		XM=XMIN
		DX=(XMAX-XMIN)/ABS(XAXL)
		GDX=1.
		IK=0
		INX=1
	    ENDIF
	ENDIF
	IF (YAXL.GT.0.0) THEN				!INPUT SCALING
	    YM=Y(1,1)
	    DY=Y(1,1)
	    DO 6 IN=1,NN
		DO 6 I=1,NP
		    YM=MAX(Y(I,IN),YM)
		    DY=MIN(Y(I,IN),DY)
6		CONTINUE
	    PY(1)=YM
	    PY(2)=DY
	    IF (IF.EQ.1.OR.IF.EQ.3) THEN
		CALL SCALG(PY,ABS(YAXL),2,1,1,YM,DY)	!SMOOTH SCALE FACTORS
		IK=-1+IK
		GDY=1./DY
		NY=int(DY*ABS(YAXL))
		INY=-1
	    ELSE
		CALL SCALE(PY,ABS(YAXL),2,1,1,YM,DY)	!SMOOTH SCALE FACTORS
		IK=1+IK
		GDY=1.
		INY=1
	    ENDIF
	ELSE
	    IF (IF.EQ.1.OR.IF.EQ.3) THEN
		YM=ALOG10(ABS(YMIN)+1.E-25)
		IF (YM.NE.AINT(YM)) YM=AINT(YM)-1.
		DY=AINT(ALOG10(ABS(YMAX)+1.E-25))+1.
		DY=(DY-YM)/ABS(YAXL)
		GDY=1./DY
		NY=int(DY*ABS(YAXL))
		IK=-1+IK
		INY=-1
	    ELSE
		YM=YMIN
		DY=(YMAX-YMIN)/ABS(YAXL)
		IK=1+IK
		GDY=1.
		INY=1
	    ENDIF
	ENDIF
	IF (JF.EQ.0) GOTO 77		!NO AXIS OR GRID
	IF (JF.EQ.60) GOTO 76		!NO GRID
	IF (JF.GT.60) THEN		!LOGRITHMIC GRID
		II=0
		IF (JF.EQ.70) II=1
		IF (JF.EQ.80) II=2
		CALL LGRID(0.,0.,GDX,GDY,INX*NX,INY*NY,II)
		GOTO 76
	ENDIF
	IF (JF.GE.20) THEN		!CARTESIAN GRID
		IF (JF.GE.30) NX=-NX
		IF (JF.GE.40) NY=-NY
		IF (NT.LT.0) CALL PLOT(FLOAT(ICOL(1)),0.,0) !PEN COLOR
		CALL GRID(0.,0.,GDX,GDY,NX,NY)		!PRODUCE GRID
		IF (JF.EQ.50) JF=10
	ENDIF
76	NADD=0
	IF (NT.LT.0) THEN
		NADD=100000		!PEN COLOR
		IC(1)=ICOL(2)
		IC(2)=ICOL(3)
		IC(3)=ICOL(4)
		IC(4)=ICOL(5)
	ENDIF
	IX=IABS(NXT)
	XL=ABS(XAXL)*SIGN(1.,FLOAT(NXT))		!AXIS LENGTH WITH TICK INFOR
	IF (NXT.NE.0) THEN
		IF (IF.EQ.2.OR.IF.EQ.3) THEN
		CALL LGAXS(0.,0.,XTITL,-IX-NADD,XL,0.,XM,DX,IC) !X-AXIS
		IF (JF.EQ.10) CALL LGAXS(0.,ABS(YAXL),XTITL,IX+100+NADD,
     $			XL,0.,XM,DX,IC) !X-AXIS
		ELSE
		CALL AXIS(0.,0.,XTITL,-IX-NADD,XL,0.,XM,DX,N1,N2,IC)  !X-AXIS
		IF (JF.EQ.10) CALL AXIS(0.,ABS(YAXL),XTITL,IX+100+NADD,
     $			XL,0.,XM,DX,N1,N2,IC)  !X-AXIS
		ENDIF
	ENDIF
	IY=IABS(NYT)+1000
	YL=ABS(YAXL)*SIGN(1.,FLOAT(NYT))
	IF (NYT.NE.0) THEN
		IF (IF.EQ.1.OR.IF.EQ.3) THEN
		CALL LGAXS(0.,0.,YTITL,IY+NADD,YL,90.,YM,DY,IC) !Y-AXIS
		IF (JF.EQ.10) CALL LGAXS(ABS(XAXL),0.,YTITL,-IY-100-NADD,
     $			YL,90.,YM,DY,IC) !Y-AXIS
		ELSE
		CALL AXIS(0.,0.,YTITL,IY+NADD,YL,90.,YM,DY,N1,N2,IC)  !Y-AXIS
		IF (JF.EQ.10) CALL AXIS(ABS(XAXL),0.,YTITL,-IY-100-NADD,
     $			YL,90.,YM,DY,N1,N2,IC)	!Y-AXIS
		ENDIF
	ENDIF
77	IF (IK.EQ.1) THEN
	    DO 78 IN=1,NN
		IF (NT.LT.0) CALL PLOT(FLOAT(ICOL(6+IN)),0.,0)  !PEN COLOR
		IF (IABS(NT)/100.GT.0) CALL NEWPEN(ILINE(IN))	!LINE TYPE
		CALL LINE(X,Y(1,IN),NP,1,NSYM,IN-1,1,1,XM,DX,YM,DY) !PLOT DATA
78	    CONTINUE
	ELSE
	    IF (IK.EQ.-1) IK=1				    !CORRECT FLAG
	    IF (IK.EQ.0) IK=-1
	    DO 79 IN=1,NN
	    IF (NT.LT.0) CALL PLOT(FLOAT(ICOL(6+IN)),0.,0)!PEN COLOR
	    IF (IABS(NT)/100.GT.0) CALL NEWPEN(ILINE(IN)) !LINE TYPE
	    CALL LGLIN(X,Y(1,IN),NP,1,NSYM,IN-1,IK,1,1,XM,DX,YM,DY)!PLOT DATA
79	    CONTINUE
	ENDIF
	IF (IABS(NT)/100.GT.0) CALL NEWPEN(1)		!RESET LINE TYPE
	CS=.21						!TITLE CHARACTER SIZE
	IF (NT.LT.0) CALL PLOT(FLOAT(ICOL(6)),0.,0)	!PEN COLOR
	IF (NT.NE.0.AND.JF.NE.0) THEN			!PLOT TITLE
		XP=0.0
		YP=0.0
		CALL SYMBOL(XP,YP,CS,TITLE,
     $			0.,MOD(IABS(NT),100),-3)	!TITLE LENGTH
		XP=ABS(XAXL/2.)-XP/2.
		IF (XP.LT.0.) XP=0.
		CALL SYMBOL(XP,ABS(YAXL)+.15,CS,TITLE,
     $			0.,MOD(IABS(NT),100),-1)	!PLOT TITLE
	ENDIF
	CALL PLOT(0.,0.,3)
	IF (IFLAG.GT.0) THEN
		CALL CTERM(2)				!ASK IF CLEAR SCREN
		CALL PLOTND				!CLOSE PLOT PACKAGE
		REPEAT=.FALSE.
	ENDIF
	IF (IFLAG.LT.0) THEN
		REPEAT=.TRUE.
		CALL CTERM(1)				!RETURN TO TEXT MODE
	ENDIF
	RETURN
	END
