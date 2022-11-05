C
C
	SUBROUTINE HLT3D(A,MD,ND,M,N,W1,L,W2,NN,ALT,AZ,XLEN,XOFF,
     $		YLEN,YOFF,ZFAC,ZOFF,IER)
	SAVE
C
C	ROUTINE TO PLOT COLUMNS IN 3D WITH HIDDEN LINE REMOVAL USING NXTVU
C	WRITTEN 8/17/87 BY D.LONG, JPL
C
C	A	(R): MD BY ND ARRAY CONTAINING Z VALUES TO BE PLOTTED
C	MD,ND	(I): DIMENSIONS OF A
C	M,N	(I): SIZE OF DATA IN A ARRAY  M,N > 1
C	W1	(R): WORKING ARRAY OF DIMENSIONED W1(L)
C		      (NOT USED--INCLUDED FOR COMPATIBILITY WITH PLT3D)
C	L	(I): DIMENSION OF W1 ARRAY
C	W2	(R): WORKING ARRAY OF DIMENSIONED W2(NN)
C	NN	(I): DIMENSION OF W2 ARRAY
C	ALT,AZ	(R): VIEWING ALTITUDE, AZIMUTH IN DEGREES
C	XLEN	(R): LENGTH OF UNPROJECTED X AXIS IN INCHES
C			> 0 SURFACE ABOVE PLANE SHOWN
C			< 0 SURFACE BELOW PLANE SHOWN
C	XOFF	(R): ORIGIN OF PLOT
C	YLEN	(R): LENGTH OF UNPROJECTED Y AXIS IN INCHES
C	YOFF	(R): ORIGIN OF PLOT
C	ZFAC	(R): Z COORDINATE SCALE FACTOR (Zplotted=ZFAC*A(I,J)+ZOFF)
C	ZOFF	(R): Z AXIS OFFSET VALUE
C	IER	(I): RETURNED ERROR CODE
C			0: NO ERROR
C			1: WORKING STORAGE W2 INTERNAL SPACE EXCEEDED
C			2: L LESS THAN 2*MIN(M,N)
C
	DIMENSION A(MD,ND),W2(NN)
	DIMENSION D(12)
C
	COMMON /PLT3B/A1,A2,A3,B1,B2,B3,B4
cc	SAVE /PLT3B/
	DATA DTR/0.0174532925/
C
	IX(I)=(I-1)*2+1
	IY(I)=I*2
C
	TAZ=AZ*DTR
	TALT=ALT*DTR
	SAZ=SIN(TAZ)
	CAZ=COS(TAZ)
	SAL=SIN(TALT)
	CAL=COS(TALT)
	XSC=ABS(XLEN)/FLOAT(N-1)
	ID=1
	IF (XLEN.LT.0.0) ID=-1
	YSC=YLEN/FLOAT(M-1)
	A1=CAZ*XSC
	A2=-SAZ*YSC
	A3=XOFF-0.5*(A1*FLOAT(N+1)+A2*FLOAT(M+1))
	B1=SAZ*SAL*XSC
	B2=CAZ*SAL*YSC
	B3=ZFAC*CAL
	B4=B3*ZOFF+YOFF-0.5*(B1*FLOAT(N+1)+B2*FLOAT(M+1))
	IAZ=1
	IF (A1.LE.0.0) IAZ=IAZ+1
	IF (A2.LE.0.0) IAZ=IAZ+2
	GOTO (10,20,10,20), IAZ
10	IFIRST=1
	ISTEP=1
	ILAST=M
	GOTO 30
20	IFIRST=M
	ISTEP=-1
	ILAST=1
30	GOTO (50,50,40,40),IAZ
40	JFIRST=1
	JSTEP=1
	JLAST=N
	GOTO 60
50	JFIRST=N
	JSTEP=-1
	JLAST=1
60	IC=ID
C
C	PLOT ZOFF PLANE LINE
C
	LL=3
	XX=FLOAT(JFIRST)
	YY=FLOAT(ILAST+ISTEP)+0.001
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*ZOFF+B4
	XX=FLOAT(JFIRST)
	YY=FLOAT(IFIRST)
	D(IX(2))=A1*XX+A2*YY+A3
	D(IY(2))=B1*XX+B2*YY+B3*ZOFF+B4
	XX=FLOAT(JLAST+JSTEP)+0.001
	YY=FLOAT(IFIRST)
	D(IX(3))=A1*XX+A2*YY+A3
	D(IY(3))=B1*XX+B2*YY+B3*ZOFF+B4
	CALL NXTVU(IC,D,LL,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IC=2*ID
C
	IBEG=IFIRST
	JBEG=JFIRST
70	CONTINUE
C
C	BOTTOM FRONT EDGE
C
	I=IBEG+ISTEP
	J=JBEG
490	CONTINUE
	LL=1
	XX=FLOAT(J)
	YY=FLOAT(I)
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*ZOFF+B4
	I=I-ISTEP
	LL=LL+1
	YY=FLOAT(I)
	D(IX(2))=A1*XX+A2*YY+A3
	D(IY(2))=B1*XX+B2*YY+B3*ZOFF+B4
	IF (J.EQ.JLAST) GOTO 400
	J=J+JSTEP
	LL=LL+1
	XX=FLOAT(J)
	D(IX(3))=A1*XX+A2*YY+A3
	D(IY(3))=B1*XX+B2*YY+B3*ZOFF+B4
400	CALL NXTVU(IC,D,LL,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IF (I.EQ.IFIRST.OR.J-JSTEP.EQ.JLAST) GOTO 480
	GOTO 490
C
C	PLOT FRONT CENTER LINES
C
480	I=IBEG
	J=JBEG
75	CONTINUE
	XX=FLOAT(J)
	YY=FLOAT(I)
	ZV=ZOFF
	IF (I.NE.IFIRST.AND.J.NE.JFIRST) THEN
		ZV=AMIN1(A(I-ISTEP,J-JSTEP),A(I-ISTEP,J))
		ZV=AMIN1(ZV,A(I,J-JSTEP))+ZOFF
	ENDIF
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*ZV+B4
	D(IX(2))=D(IX(1))
	D(IY(2))=B1*XX+B2*YY+B3*(A(I,J)+ZOFF)+B4
	CALL NXTVU(IC,D,2,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IC=2*ID
	IF (I.EQ.IFIRST.OR.J.EQ.JLAST) GOTO 80
	I=I-ISTEP
	J=J+JSTEP
	GOTO 75
C
C	FRONT SIDES
C
80	I=IBEG+ISTEP
	J=JBEG
175	CONTINUE
	LL=2
	XX=FLOAT(J)
	YY=FLOAT(I)
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*ZOFF+B4
	D(IX(2))=D(IX(1))
	D(IY(2))=D(IY(1))+B3*A(I-ISTEP,J)
	IF (I.EQ.IFIRST) GOTO 275
	I=I-ISTEP
	LL=LL+1
	YY=FLOAT(I)
	D(IX(3))=A1*XX+A2*YY+A3
	D(IY(3))=B1*XX+B2*YY+B3*(A(I,J)+ZOFF)+B4
	J=J+JSTEP
	LL=LL+2
	XX=FLOAT(J)
	D(IX(4))=A1*XX+A2*YY+A3
	D(IY(4))=B1*XX+B2*YY+B3*(A(I,J-JSTEP)+ZOFF)+B4
	D(IX(5))=D(IX(4))
	D(IY(5))=D(IY(4))-B3*A(I,J-JSTEP)
275	CALL NXTVU(IC,D,LL,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IF (I.EQ.IFIRST.OR.J-JSTEP.EQ.JLAST) GOTO 260
	GOTO 175
C
C	BACK TOP
C
260	I=IBEG+ISTEP
	J=JBEG
290	CONTINUE
	LL=1
	XX=FLOAT(J)
	YY=FLOAT(I)
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*(A(I-ISTEP,J)+ZOFF)+B4
	J=J+JSTEP
	LL=LL+1
	XX=FLOAT(J)
	D(IX(2))=A1*XX+A2*YY+A3
	D(IY(2))=B1*XX+B2*YY+B3*(A(I-ISTEP,J-JSTEP)+ZOFF)+B4
	IF (I.EQ.IFIRST) GOTO 300
	I=I-ISTEP
	LL=LL+1
	YY=FLOAT(I)
	D(IX(3))=A1*XX+A2*YY+A3
	D(IY(3))=B1*XX+B2*YY+B3*(A(I,J-JSTEP)+ZOFF)+B4
300	CALL NXTVU(IC,D,LL,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IF (I.EQ.IFIRST.OR.J-JSTEP.EQ.JLAST) GOTO 560
	GOTO 290
C
C	BACK BOTTOM
C
560	I=IBEG+ISTEP
	J=JBEG
590	CONTINUE
	IF (A(I-ISTEP,J).LT.ZOFF) THEN
C
C	FOR COLUMNS BELOW OFFSET PLANE, SHOW BACK CORNER
C
		LL=2
		XX=FLOAT(J+JSTEP)
		YY=FLOAT(I)
		D(IX(1))=A1*XX+A2*YY+A3
		D(IY(1))=B1*XX+B2*YY+B3*(A(I-ISTEP,J)+ZOFF)+B4
		D(IX(2))=A1*XX+A2*YY+A3
		D(IY(2))=B1*XX+B2*YY+B3*ZOFF+B4
		CALL NXTVU(IC,D,LL,W2,NN,IER)
		IF (IER.NE.0) RETURN
	ENDIF
	LL=1
	XX=FLOAT(J)
	YY=FLOAT(I)
	D(IX(1))=A1*XX+A2*YY+A3
	D(IY(1))=B1*XX+B2*YY+B3*ZOFF+B4
	J=J+JSTEP
	LL=LL+1
	XX=FLOAT(J)
	D(IX(2))=A1*XX+A2*YY+A3
	D(IY(2))=B1*XX+B2*YY+B3*ZOFF+B4
	IF (I.EQ.IFIRST) GOTO 550
	I=I-ISTEP
	LL=LL+1
	YY=FLOAT(I)
	D(IX(3))=A1*XX+A2*YY+A3
	D(IY(3))=B1*XX+B2*YY+B3*ZOFF+B4
550	CALL NXTVU(IC,D,LL,W2,NN,IER)
	IF (IER.NE.0) RETURN
	IF (I.EQ.IFIRST.OR.J-JSTEP.EQ.JLAST) GOTO 380
	GOTO 590
C
C	FINISHED ONE LAYER
C
380	CONTINUE
	IF (IBEG.NE.ILAST) THEN
		IBEG=IBEG+ISTEP
		GOTO 70
	ENDIF
	JBEG=JBEG+JSTEP
	IF (JBEG.EQ.JLAST) RETURN	
	GOTO 70
	END