C
C *** LAST REVISED ON  8-DEC-1993 07:27:09.08
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]CNDRAW.FOR
C
	SUBROUTINE CNDRAW(X,Y,IL,IH,CVAL,NCH,CS,NMIN,ICL,ICOL,ILINE)
C
C	ROUTINE TO PLOT CONTOUR LINES AND LABELS
C
C	X,Y	(R)	LOCATION OF POINT (IN POINTS)
C	IL	(I)	OPERATION ID FLAG
C			= 1 CONTINUE CONTOUR
C			= 2 START CONTOUR AT BOUNDRY
C			= 3 START CONTOUR NOT AT BOUNDRY
C			= 4 FINISH CONTOUR AT BOUNDRY
C			= 5 FINISH CLOSED CONTOUR (NOT AT BOUNDRY)
C	IH	(I)	CONTOUR NUMBER
C			 IF IH > 0 THEN CONTOUR NUMBER IS LOOKED UP IN
C			 CVAL ARRAY.  IF IH < 0 THEN THE FIRST ELEMENT
C			 OF CVAL IS USED AND CONTOUR IS LABELED WITH IABS(IH)
C	CVAL	(R)	CONTOUR VALUE
C	NCH	(I)	CONTOUR LABELING OPTION
C			< 0 LABEL WITH CONTOUR VALUE (NCH IS NUMBER
C				OF DIGITS TO THE LEFT OF DECIMAL
C			= 0 NO LABELING OF CONTOURS
C			> 0 LABEL WITH LETTERS
C	CS	(R)	LABEL SIZE
C			< 0 PLT3D LOCATION SCALING USED WITH Z VALUE
C			    OF ZERO
C			> 0 NORMAL SCALING USED
C	NMIN	(I)	MINIMUM NUMBER OF SEGMENTS TO BE LABELED
C	ICL	(I)	COLOR AND LINE TYPE FLAG
C			= 0 NO COLOR OR LINE TYPE USED
C			= 1 COLOR USED ONLY
C			= 2 LINE TYPE USED ONLY
C			= 3 COLOR AND LINE TYPE USED
C	ICOL	(I)	LINE COLOR FOR EACH CONTOUR
C	ILINE	(I)	LINE TYPE FOR EACH CONTOUR
C
	DIMENSION ILINE(1),ICOL(1)
C
	COMMON /PLT3B/A1,A2,A3,B1,B2,B3,B4
	SAVE /PLT3B/
C
	IPEN=2
	IF (IL.EQ.2.OR.IL.EQ.3) THEN
		IHN=MAX(1,IH)
		IF (ICL.GT.1) CALL NEWPEN(ILINE(IHN))	! LINE TYPE
		IF (MOD(ICL,2).EQ.1) CALL PLOT(FLOAT(ICOL(IHN)),0.,0)! PEN COLOR
		IPEN=3
		NCNT=0
	ENDIF
	NCNT=NCNT+1
	X1=X
	Y1=Y
	IF (CS.LT.0.0) THEN
		X1=A1*(Y+1.0)+A2*(X+1.0)+A3
		Y1=B1*(Y+1.0)+B2*(X+1.0)+B4
	ENDIF
	CALL PLOT(X1,Y1,IPEN)
	IF (IL.LT.4) GOTO 30
	IF (NCH.EQ.0) GOTO 30
	IF (NCNT.LT.NMIN) GOTO 30
	IF (ICL.GT.1) CALL NEWPEN(1)			! RESET LINE TYPE
	IF (NCH.LT.0) GOTO 5
	IF (IABS(IH).LT.26) GOTO 10
5	CALL NUMBER(X1,Y1-0.05,ABS(CS),CVAL,0.,FLOAT(IABS(NCH))/100.,-1)
	GOTO 30
10	CALL SYMBOL(X1,Y1-0.05,ABS(CS),CHAR(64+IABS(IH)),0.,1,-1)
30	RETURN
	END