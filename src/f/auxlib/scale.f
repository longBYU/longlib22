C
C
	SUBROUTINE SCALE(X,S,N,K,IX,XMIN,DX)
C
C	CREATES SMOOTHED LINEAR SCALE FACTORS FROM INPUT DATA
C
C	X	(R) ARRAY OF DATA TO BE SCANNED FOR MAXIMUM AND MINIMUM
C		    VALUES. 
C	S	(R) LENGTH OVER WHICH THIS DATA IS TO BE PLOTTED.
C	N	(I) NUMBER OF DATA POINTS IN THE ARRAY X.
C	K	(I) REPEAT CYCLE OF MIXED ARRAY(NORMALLY 1).
C	IX	(I) FIRST RELEVANT DATA POINT IN X
C	XMIN	(R) SMOOTHED MINIMUM AFTER CALL
C	DX	(R) SMOOTHED INCREMENT AFTER CALL
C
C	TO USE SMOOTHED VALUES: XPLOTTED=(XVALUE-XM)/DX
C
	REAL X(1),Q(6)
	DATA Q/1.0,2.0,4.0,5.0,8.0,10.0/
	NP=N*K
	XMAX=X(1)
	XMIN=XMAX
	DO 100 I=IX,NP,K
		XI=X(I)
		XMAX=AMAX1(XMAX,XI)
		XMIN=AMIN1(XMIN,XI)
100	CONTINUE
	XMM=XMIN
	IF (S.LE.0.0) GOTO 160
	DX=(XMAX-XMIN)/S
	IF (DX.LE.0.0) GOTO 160
	SJ=0.0
	IF (DX.LT.1.0) SJ=-1.0
	IDX=int(ALOG10(DX)+SJ)
	DX=DX/(10.0**IDX)
	DO 110 I=1,6
		XI=Q(I)
		IF (XI.GE.DX) GOTO 120
110	CONTINUE
120	DX=XI*(10.0**IDX)
	SI=1.0
	SJ=0.0
	IF (XMIN) 130,170,140
130	SI=-1.0
	SJ=-0.99999
	XMIN=-XMIN
140	IDX=int(ALOG10(XMIN)+SJ)
	XMIN=XMIN/(10.0**IDX)
	XMIN=XMIN-SJ
	XMIN=IFIX(XMIN)*SI*(10.0**IDX)
	GOTO 170
160	DX=1.0
	XMIN=XMIN-0.5
170	CONTINUE
C
C	BEFORE EXIT, CHECK TO BE SURE THAT DATA IS CONTAINED WITHIN
C	THE LIMITS XMIN AND XMIN+DX*S.  IF NOT, RESET DX
C
	IF (XMM.LT.XMIN) XMIN=XMM
	IF (XMAX.GT.XMIN+DX*S) THEN
		IF (S.GT.0.0) DX=(XMAX-XMIN)/S
		IF (DX.LE.0.0) DX=1.0
	ENDIF
	RETURN
	END
