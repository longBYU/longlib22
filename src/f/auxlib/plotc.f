C
C *** LAST REVISED ON  4-JAN-1994 10:33:13.59
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.AUXLIB]PLOTC.FOR
C
	SUBROUTINE PLOTC(XA,YA,IA)
C
C	WRITTEN:   	DGL AUG 1990
C
C	SECONDARY CLIPPING SUPPORT ROUTINE
C	CALLS PLOT WITH CLIPPED AND SCALED RESULTS
C
C XA	X COORDINATE
C YA	Y COORDINATE
C IA	PEN CONTROL
C	+8   ENABLE PLOTC OPERATION (COMMANDS INTERPRETTED)
C	+7   SET UPPER RIGHT CORNER OF PLOTC VIEW PORT
C	+1   SET PLOTC RELATIVE ROTATION ANGLE TO XA (DEG)
C	     AND PLOTC SCALE FACTOR TO YA (0 IS EQUIVALENT TO 1)
C	-1   SET PLOTC ORIGIN TO (XA,YA)
C	-7   SET LOWER LEFT CORNER OF PLOTC VIEW PORT
C	+8   DISABLE PLOTC OPERATION (PASS THRU MODE)
C
C	ALL OTHER VALUES OF IA ARE PASSED DIRECTLY TO PLOT ALONG WITH XA AND YA
C	
C	DEFAULT:
C		PLOTC OPERATION DISABLED
C		LOWER LEFT VIEWPORT CORNER: (0,0)
C		UPPER RIGHT VIEWPORT CORNER: (8.5,11)
C		ROTATION ANGLE: 0.0 DEG
C		SCALE FACTOR: 1.0
C
	LOGICAL ENABLE
	REAL OX,OY,SF,PX,PY,CANG,SANG,VP(4)
	SAVE OX,OY,SF,PX,PY,CANG,SANG,VP,ENABLE
	INTEGER IC0(6)
C
C	INITIAL DEFAULT VALUES
C
	DATA OX,OY,SF,PX,PY,CANG,SANG/0.,0.,1.,0.,0.,1.,0./
	DATA VP,ENABLE/0.,0.,8.5,11.,.FALSE./
C
	DATA NC0/6/,IC0/8,7,1,-1,-7,-8/
C
C	DEFINE ROTATION, SCALING FUNCTIONS
C
	XFOR(X,Y,OX,OY,SF,CANG,SANG)=((X-OX)*CANG-(Y-OY)*SANG)*SF
	YFOR(X,Y,OX,OY,SF,CANG,SANG)=((X-OX)*SANG+(Y-OY)*CANG)*SF
	XBAC(X,Y,OX,OY,SF,CANG,SANG)= X/SF*CANG+Y/SF*SANG+OX
	YBAC(X,Y,OX,OY,SF,CANG,SANG)=-X/SF*SANG+Y/SF*CANG+OY
C
	I0=IABS(IA)
C
C	DECODE COMMAND
C
	IF (ENABLE) THEN
		IF (I0.EQ.2.OR.I0.EQ.3.OR.I0.EQ.9) THEN
			IF (SF.LE.0.0) SF=1.0
			IF (ABS(CANG*CANG+SANG*SANG-1.0).GT.0.001) THEN
				CANG=1.0
				SANG=0.0
			ENDIF
			AV1=XFOR(XA,YA,OX,OY,SF,CANG,SANG)
			AV2=YFOR(XA,YA,OX,OY,SF,CANG,SANG)
			GOTO 500
		ENDIF
		DO 30 I1=1,NC0
			IF (IA.EQ.IC0(I1)) GOTO 40
30		CONTINUE
	ELSE
		IF (I0.EQ.8) GOTO 100
		IF (I0.EQ.2.OR.I0.EQ.3) THEN
			PX=XA
			PY=YA
		ENDIF
	ENDIF
	CALL PLOT(XA,YA,IA)
	RETURN
C
40	CONTINUE
	GOTO (100,200,300,400,200,100),I1
C
100	CONTINUE		! SET ENABLE FLAG
	ENABLE=.TRUE.
	IF (IA.LT.0) ENABLE=.FALSE.
	RETURN
C
200	CONTINUE		! SET PLOTC VIEWPORT
	IF (IA.GT.0) THEN
		VP(3)=XA
		VP(4)=YA
	ELSE
		VP(1)=XA
		VP(2)=YA
	ENDIF
	RETURN
C
300	CONTINUE		! SET PLOTC ANGLE AND SCALE FACTOR
	CANG=COS(XA*0.0174532)
	SANG=SIN(XA*0.0174532)
	IF (SF.LE.0.0) SF=1.0
	IF (YA.NE.0.0) SF=SF*YA
	IF (SF.LE.0.0) SF=1.0
	RETURN
C
400	CONTINUE		! SET PLOTC ORIGIN
	OX=XA
	OY=YA
	RETURN
C
C	DRAW AND/OR CLIP LINE SEGMENT
C
500	CONTINUE
	XM=VP(1)
	YM=VP(2)
	XX=VP(3)
	YX=VP(4)
	IVTA=IPCLIP(AV1,AV2,XM,YM,XX,YX)
	IVTB=IPCLIP(PX,PY,XM,YM,XX,YX)
	IF (IOR(IVTA,IVTB).EQ.0) THEN		! LINE ENTIRELY VISIBLE	
		PX=AV1
		PY=AV2
		CALL PLOT(XA,YA,IA)
		RETURN
	ENDIF
	IF (IAND(IVTA,IVTB).NE.0) THEN		! LINE ENTIRELY INVISIBLE
		PX=AV1
		PY=AV2
		IF (IA.LT.0) CALL PLOT(XA,YA,-3)
		RETURN
	ENDIF
	IF (IVTB.NE.0) THEN			! OLD POINT IS OUTSIDE WINDOW
		XV2=PX
		YV2=PY
		CALL CLPIT(IVTB,XV2,YV2,AV1,AV2,XM,YM,XX,YX)
		IF (IVTB.NE.0) THEN		! VECTOR DOES NOT INTERSECT
			PX=AV1			! WINDOW
			PY=AV2
			IF (IA.LT.0) CALL PLOT(XA,YA,-3)
			RETURN
		ENDIF
		X1=XBAC(XV2,YV2,OX,OY,SF,CANG,SANG)
		Y1=YBAC(XV2,YV2,OX,OY,SF,CANG,SANG)
		CALL PLOT(X1,Y1,3)
	ENDIF
	XV=AV1
	YV=AV2
	IF (IVTA.NE.0) CALL CLPIT(IVTA,XV,YV,PX,PY,XM,YM,XX,YX)
	PX=AV1
	PY=AV2
	IF (IVTA.NE.0) THEN			! NEW POINT IS OUTSIDE WINDOW
		IF (IA.LT.0) CALL PLOT(XA,YA,-3)
		RETURN
	ENDIF
	X1=XBAC(XV,YV,OX,OY,SF,CANG,SANG)
	Y1=YBAC(XV,YV,OX,OY,SF,CANG,SANG)
	CALL PLOT(X1,Y1,I0)
	IF (IA.LT.0) CALL PLOT(XA,YA,-3)
	RETURN
	END
