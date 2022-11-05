C
C
	SUBROUTINE SHADE(A,B,N,I,L,D,T,W,MA,AM,DA,BM,DB)
C
C	SHADES AN AREA DEFINED BY THE A AND B ARRAYS
C
C A    (R) ARRAY CONTAINING ABSCISSA VALUES
C B    (R) ARRAY CONTAINING ORDINATE VALUES
C N    (I) NUMBER OF POINTS IN ARRAY
C I    (I)INCREMENT BETWEEN POINTS IN ARRAY
C L    (I) SHADE FORMAT CONTROL
C		-3 CLEAR AREA AND OUTLINE
C		-2 CLEAR AREA
C		-1 CLEAR OUTLINE
C		 0 NO ACTION
C		+1 SHADE OUTLINE
C		+2 SHADE AREA
C		+3 SHADE AREA AND OUTLINE
C D    (D) DISTANCE BETWEEN SHADING LINES
C T    (D) ANGLE OF SHADING LINES
C W    (D) WORKING ARRAY DIMENSIONED AT LEAST (3*N)
C MA   (I) TYPE OF SHADING (LINE TYPE) IF MA > 0
C AM   (R) MINIMUM VALUE FOR A ARRAY
C DA   (R) SCALE FACTOR FOR A ARRAY
C BM   (R) MINIMUM VALUE FOR B ARRAY
C DB   (R) SCALE FACTOR FOR B ARRAY
C
	INTEGER KP(2)
	REAL A(1),B(1),W(3,1)
C
C	EQUIVALENCES ARE FOR CONVENIENCE ONLY
C
	EQUIVALENCE (KP(1),KD),(KP(2),KU)
	DATA KP/2,3/
C
	ROT(X,Y)=X*CT+Y*ST
	SCL(Q,R,S)=(Q-R)/S
C
	IF (N.LE.2) GOTO 110
	IF (I.LE.0) GOTO 110
	AO=AM
	AI=DA
	BO=BM
	BI=DB
	IF (AI.LE.0.0) AI=1.0
	IF (BI.LE.0.0) BI=1.0
	LT=IABS(L)
	KD=2
	IF (L.LT.0) KD=9
	IF (LT.LE.1) GOTO 90
	DT=D
	IF (DT.LE.0.0) DT=0.005
	TH=T-(AINT(T/360.0))*360.0
	IF (TH.LT.0.0) TH=TH+360.0
	TH=TH*0.0174532
	ST=SIN(TH)
	CT=COS(TH)
	YS=ROT(SCL(B(1),BO,BI),-SCL(A(1),AO,AI))
	YL=YS
	I1=1
	DO 20 I0=1,N
		TX0=SCL(A(I1),AO,AI)
		TY0=SCL(B(I1),BO,BI)
		W(1,I0)=ROT(TX0,TY0)
		TY1=ROT(TY0,-TX0)
		W(2,I0)=TY1
		YS=AMIN1(YS,TY1)
		YL=AMAX1(YL,TY1)
		I1=I1+I
20	CONTINUE
	YC=YS+0.5*DT
	IF (MA.GE.0) CALL NEWPEN(MA)
30	IF (YC.GT.YL) GOTO 90
	I1=0
	DO 60 I0=1,N
		I2=I0+1
		IF(I2.GT.N)I2=1
		YT0=W(2,I0)
		YT1=W(2,I2)
		W1=AMIN1(YT0,YT1)
		IF(YC.LT.W1)GOTO 60
		W2=AMAX1(YT0,YT1)
		IF (YC.GE.W2) GOTO 60
		XT0=W(1,I0)
		XT1=W(1,I2)
		X1=XT0-(YT0-YC)*(XT1-XT0)/(YT1-YT0)
		I1=I1+1
		I2=I1
40		IF (I2.EQ.1) GOTO 50
		I3=I2-1
		IF (W(3,I3).GE.X1) GOTO 50
		W(3,I2)=W(3,I3)
		I2=I3
		GOTO 40
50		W(3,I2)=X1
60	CONTINUE
	IF (I1.LE.0) GOTO 80
	I2=1
	DO 70 I0=1,I1
		XT0=W(3,I0)
		XT=ROT(XT0,-YC)
		YT=ROT(YC,XT0)
		I2=3-I2
		KC=KP(I2)
		CALL PLOT(XT,YT,KC)
70	CONTINUE
80	YC=YC+DT
	GOTO 30
90	IF (2*(LT/2).EQ.LT) GOTO 110
	CALL PLOT(SCL(A(1),AO,AI),SCL(B(1),BO,BI),KU)
	I1=1
	DO 100 I0=2,N
		I1=I1+I
		CALL PLOT(SCL(A(I1),AO,AI),SCL(B(I1),BO,BI),KD)
100	CONTINUE
	CALL PLOT(SCL(A(1),AO,AI),SCL(B(1),BO,BI),KD)
C
C	RESET PEN TYPE
C
110	IF (MA.GT.0) CALL NEWPEN(1)
	RETURN
	END
