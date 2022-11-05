C
C *** LAST REVISED ON 20-AUG-1987 16:47:03.07
C *** SOURCE FILE: [DL.GRAPHICS.LONGLIB]REFTERM.FOR
C
	PROGRAM REFTERM
C
C	THIS PROGRAM PLOTS A RAMTEK EMULATION FILE INTO THE LONGLIB
C	PLOT PACKAGE
C	WRITTEN: NOV 1986   DGL
C
C	THIS PROGRAM USING THE VAX FORTRAN "BYTE" VARIABLE TYPE
C
	BYTE B(1280)
	INTEGER PEN
	CHARACTER*70 FNAME
C
C	PROMPT USER FOR FILE INPUT
C
35	WRITE(*,15)
15	FORMAT('$Enter Ramtek Emulation File Name: ')
	READ(*,20) FNAME
20	FORMAT(A70)
	WRITE(*,25)
25	FORMAT(' Note: Select only one output graphics device')
C
C	OPEN GRAPHICS PACKAGE
C
	CALL FRAME(0,0,0.,0.,1.)
C
C	OUTPUT RAMTEK EMULATION ARRAY TO SELECTED DEVICE
C	OPEN REF FILE ASSUMING LARGE RAMTEK
C
	IXWIDE=1280
	IYWIDE=1024
	OPEN(UNIT=2,FILE=FNAME,ACCESS='DIRECT',STATUS='UNKNOWN',
     $	 RECL=IXWIDE,FORM='FORMATTED',ERR=199)
C
C	DETERMINE WHICH GRAPHICS DEVICE IS OPEN
C
65	IXW=IXWIDE
	IF (IXWIDE.EQ.512) IXW=512
C
C	CHECK TERMINAL, RAMTEK, AND METAFILE
C
	CALL WHEREVT(XS,YS,XS,YS,RX,RY,ILU,IY,IX,IX,IY)
	RX=RX*4
	RY=RY*4
	IF (ILU.LE.0) THEN
		CALL WHERERM(XS,YS,XS,YS,RX,RY,IY,IX,IX,ILU)
		IF (ILU.LE.0) THEN
		 CALL WHEREPR(XS,YS,XS,YS,XS,YS,RX,RY,ILU,IY,IX,IX)
		 RX=RX*5./3.
		 RY=RY*5./3.
		 IDEV=2
		ELSE
		 ICHAN=IRMCHAN(IDDEV)
		 IDEV=1
		ENDIF
	ELSE
		IDEV=0
	ENDIF
C
C	SEE IF ANY DEVICE IS IN USE, EXIT IF NOT
C
	IF (ILU.LE.0) CALL EXIT
C
C	READ EACH LINE OF IMAGE AND PLOT IT OUT
C
	LPEN=-3
	DO 250 IY1=1,IYWIDE
		IY=IYWIDE-IY1
		IF (IXW.EQ.512) THEN
			READ(2'IY1,260,ERR=97) (B(II),II=1,512)
260			FORMAT(512A1)
		ELSE
			READ(2'IY1,261,ERR=97) B
261			FORMAT(1280A1)
		ENDIF
		IF (IDEV.NE.1) THEN
C
C	OUTPUT DIRECTLY TO RAMTEK USING IMAGE MODE WRITE
C
			CALL RMSTART(ICHAN,IY1,0,IERR)
			CALL RMWRITEBYTE(ICHAN,B,IXW,IERR)
		ELSE
C
C	CONVERT PIXEL ROW INTO SCAN LINES FOR METAFILE AND TERMINAL
C
		    PEN=-1
		    DO 305 IX=0,IXWIDE
			II=B(IX+1).AND.255
			IF (IX.EQ.IXWIDE) II=-2
			IF (II.NE.PEN) THEN
				IF (PEN.NE.-1.AND.PEN.NE.0) THEN
					XS=(IX0+0.5)*RX
					XS1=(IX-0.5)*RX
					YS=(IY+0.5)*RX
					IF (LPEN.NE.PEN)
     $					  CALL PLOT(FLOAT(PEN),0.,0)
					CALL PLOT(XS,YS,3)
					CALL PLOT(XS1,YS,2)
				ENDIF
				LPEN=PEN
				PEN=II
				IX0=IX
			ENDIF
305		    CONTINUE
		ENDIF
250	CONTINUE
C
350	CALL PLOT(0.,0.,3)
	CALL CTERM(2)
	CALL PLOTND
C
	STOP
C
199	CONTINUE
C
C	IF WE GET TO HERE WE GOT AN ERROR OPENING REF FILE
C	MAY BE IT WAS A 512 SIZE FILE, TRY AGAIN
C
	IXWIDE=512
	IYWIDE=512
	OPEN(UNIT=2,FILE=FNAME,ACCESS='DIRECT',STATUS='UNKNOWN',
     $	 RECL=IXWIDE,FORM='FORMATTED',ERR=99)
	GOTO 65
C
99	WRITE(*,98)
98	FORMAT(' *** ERROR OPENING RAMTEK EMULATION FILE ***')
	GOTO 35
C
97	WRITE(*,96) IY1
96	FORMAT(' *** ERROR READING RAMTEK EMULATION FILE ***',I5)
	GOTO 350
	END
