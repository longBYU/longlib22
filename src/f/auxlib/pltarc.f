C
C
	SUBROUTINE PLTARC(X1,Y1,X2,Y2,X3,Y3)
C
C	WRITTEN: DGL JUNE 1990
C
C	PLOTS AN ARC OF A CIRCLE WHICH PASSES THROUGH (X1,Y1)
C	(X2,Y2) AND (X3,Y3) IN SEQUENCE.  IN THE DEGENERATE CASES
C	WHERE POINTS ARE COINCIDENT OR COLINEAR, A STRAIGHT
C	LINE FROM (X1,Y1) TO (X3,Y3) IS PLOTTED.
C
C	INPUTS:
C	  X1,Y1,X2,Y2,X3,Y3: (R) INPUT POINTS
C
C	CHECK FOR COINCIDENT POINTS
	IF (X1.EQ.X2.AND.Y1.EQ.Y2) GOTO 10
	IF (X1.EQ.X3.AND.Y1.EQ.Y3) GOTO 10
	IF (X2.EQ.X3.AND.Y2.EQ.Y3) GOTO 10
C
	D=(X1-X2)*(Y1-Y3)-(X1-X3)*(Y1-Y2)
	IF (D.EQ.0.0) GOTO 10
	XX=X2*X2-X1*X1+Y2*Y2-Y1*Y1
	YY=X3*X3-X1*X1+Y3*Y3-Y1*Y1
	X0=0.5*((Y3-Y1)*XX+(Y1-Y2)*YY)/D
	Y0=0.5*((X1-X3)*XX+(X2-X1)*YY)/D
	R=SQRT((X1-X0)**2+(Y1-Y0)**2)
	A1=ATAN2D(Y1-Y0,X1-X0)
	A3=ATAN2D(Y3-Y0,X3-X0)
	CALL CIRCLE(X0,Y0,A1,A3,R,R,0.0)
  5	RETURN
 10	CALL PLOT(X1,Y1,3)
	CALL PLOT(X3,Y3,2)
	GOTO 5
	END
