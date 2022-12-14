C
C
	SUBROUTINE DASHL(X,Y,N,K,J,L,IX,IY,XMIN,DX,YMIN,DY)
C
C	MODIFIED FROM LINE D.LONG 24-MAY-1983 AT JPL
C
C	X	(R) ARRAY OF UNSCALED ABCISSA VALUES
C	Y	(R) ARRAY OF UNSCALED ORDINATE VALUES
C	N	(I) NUMBER OF POINTS IN THE ARRAY
C	K	(I) REPEAT CYCLE OF A MIXED ARRAY (NORMALLY =1)
C	J	(I) >0, SYMBOL AND LINE SYMBOL PLOTTED EVERY JTH POINT
C		    =0, LINE ONLY
C		    <0, SYMBOL ONLY SYMBOL PLOTTED EVERY JTH POINT
C	L	(I) NUMBER OF SYMBOL ,SEE SYMBOL ROUTINE FOR LIST
C	IX,IY	(I) FIRST REVALENT VALUE IN X,Y ARRAY
C	XMIN,YMIN (R) MINIMUM VALUES IN ARRAY (DETERMINED BY SCALE)
C	DX,DY	(R) SCALED (SMOOTHED) INCREMENT (DETERMINED BY SCALE)
C
	REAL X(1),Y(1)
	LOGICAL PEN
	DATA DL/.3/,SL/.15/		! DASH AND SPACE LENGTH
	IF(N.LT.1)GOTO 110
	LA=L
	IF (LA.LT.0.OR.LA.GT.117) LA=100.
	I2=IX
	I2Y=IY
	I3=3
	IF(J.GE.0)I3=2
	IF (DX.NE.0.0) THEN
		X0=(X(I2)-XMIN)/DX
	ELSE
		X0=0.0
	ENDIF
	IF (DY.NE.0.0) THEN
		Y0=(Y(I2Y)-YMIN)/DY
	ELSE
		Y0=0.0
	ENDIF
	CALL PLOT(X0,Y0,3)
	I6=I3
	I4=I3
	I5=N-1
	D=0.0
	PEN=.TRUE.
	IF( J.NE.0) THEN
		IF (MOD((I2-1),J).EQ.0) CALL
     $			SYMBOL(X0,Y0,0.14,CHAR(LA),0.0,-1,-1)
	ENDIF
	IF (I5.LE.0) GOTO 110
100	IF (DX.NE.0.0) THEN
		X1=(X(I2)-XMIN)/DX
	ELSE
		X1=0.0
	ENDIF
	IF (DY.NE.0.0) THEN
		Y1=(Y(I2Y)-YMIN)/DY
	ELSE
		Y1=0.0
	ENDIF
	D0=((X1-X0)**2+(Y1-Y0)**2)**.5
	I4=3
	DC=SL
	IF (PEN) DC=DL
	IF (D+D0.LT.DC) THEN
		IF (PEN) I4=I3
		CALL PLOT(X1,Y1,I4)
		IF(J.NE.0)THEN
	IF (MOD((I2-1),J).EQ.0)CALL SYMBOL(X1,Y1,0.14,CHAR(LA),0.0,-1,-1)
		ENDIF
		D=D0+D
		X0=X1
		Y0=Y1
		GOTO 105
	ENDIF
	DD=DC-D
	D=0.0
	A=ATAN2(Y1-Y0,X1-X0)
	X0=X0+DD*COS(A)
	Y0=Y0+DD*SIN(A)
	IF (PEN) I4=I3
	CALL PLOT(X0,Y0,I4)
	PEN=.NOT.PEN
	GOTO 100
105	I2=I2+K
	I2Y=I2Y+K
	I5=I5-1
	IF(I5.GT.0)GOTO 100
110	RETURN
	END
