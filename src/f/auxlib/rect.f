C
	SUBROUTINE RECT(X0,Y0,X1,Y1)
C
C	ROUTINE TO PLOT A RECTANGLE
C	CREATED BY D. LONG JULY, 1983	AT JPL
C
C	X0,Y0	(R) LOWER LEFT HAND CORNER
C	X1,Y1	(R) UPPER RIGHT HAND CORNER
C
C	NOTE: PEN ENDS UP DOWN AT LOWER-LEFT HAND CORNER
C
	CALL PLOT(X0,Y0,3)
	CALL PLOT(X1,Y0,2)
	CALL PLOT(X1,Y1,2)
	CALL PLOT(X0,Y1,2)
	CALL PLOT(X0,Y0,2)
	RETURN
	END
