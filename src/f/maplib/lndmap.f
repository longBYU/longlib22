C
C *** LAST REVISED ON  8-FEB-1994 00:04:22.30
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MAPLIB]LNDMAP.FOR
C
	SUBROUTINE LNDMAP(MAPPLT,SLONG)
C
C	WRITTEN BY D. LONG JUNE 1990  JPL
C
C	DRAWS A LAND-EDGE MAP USING DATA FROM VECTOR LAND MAP FILE
C	USING USER SUPPLIED PROJECTION ROUTINE MAPPLT
C
C	SLONG	REAL	LEFT-MOST LONGITUDE (-180 TO +180)
C
C	MAPPLT SHOULD BE A SUBROUTINE WITH THE CALL FORMAT
C
C	 SUBROUTINE MAPPLT(LONG,LAT,IP)
C 	WHERE
C	 LONG (R) IS THE SHIFTED LONGITUDE IN DEG (0 TO 360)
C		  WHERE ZERO CORRESPONDS TO SLONG ON THE GLOBE
C	 LAT  (R) IS THE LATTITUDE IN DEG (-90 TO 90)
C	 IP   (I) IS THE "PEN" CONTROL FLAG
C                 = 3: MOVE TO (LONG,LAT) WITH PEN UP
C                 = 2: DRAW TO (LONG,LAT) WITH PEN DOWN
C
C	AN EXAMPLE IMPLEMENTATION OF MAPPLT WHICH USES A LINEAR
C	PROJECT IS:
C
C	SUBROUTINE MAPPLT(ALONG,ALAT,IP)
C	DATA XLONG/0.02/	! LONG. SCALE FACTOR (INCHES/DEG LONG)
C	DATA YLAT/0.02/		! LAT. SCALE FACTOR (INCHES/DEG LAT)
C	X1=ALONG*XLONG
C	Y1=(ALAT+90.)*YLAT
C	CALL PLOT(X1,Y1,IP)
C	RETURN
C	END
C
C	USES FORTRAN FILE UNIT NUMBER 2.
C
C	NOTE: SINCE MAP DATA HAS ITS ORIGIN FROM -180 TO 180, TO MAKE
C	MAP START FROM ANOTHER LONGITUDE, THE DATA MUST BE CLIPPED AND
C	COPIED.
C
	EXTERNAL MAPPLT
	REAL DATIN(10)
	LOGICAL LAST,PENUP
	INCLUDE 'files.inc'
C
C	OPEN INPUT DATA FILE
C
	OPEN(UNIT=2,FILE=EARTH,FORM='FORMATTED',STATUS='OLD')
C     $		,READONLY)
	IPT=3
	LAST=.FALSE.
	X=360.0
C
C	READ MAP DATA RECORD
C
   10	READ(2,1005,END=999) DATIN
 1005	FORMAT(10F8.0)
C
C	CHECK THE STORED DATA COMMAND
C
	DO 20 I=1,10,2
		IF (IFIX(DATIN(I)).EQ.0.AND.
     $ 		    IFIX(DATIN(I+1)).EQ.0) GOTO 20
		IF (DATIN(I+1).EQ.888.8) THEN
C
C	 END OF LINE SEGMENT
C
			IPT=3
			CALL MAPPLT(X,Y,IPT)
			PENUP=.TRUE.
			LAST=.FALSE.
			X=360.0
			GO TO 20
		ENDIF
		IF (ABS(DATIN(I)).GT.180.5.OR.
     $		    ABS(DATIN(I+1)).GT.91.) THEN
C	BAD POINT IN DATA FILE
			IPT=3
			CALL MAPPLT(X,Y,IPT)
			PENUP=.TRUE.
			LAST=.FALSE.
			X=360.0
			GO TO 20
		ENDIF
		PENUP=.FALSE.
		IF (DATIN(I).LT.SLONG) THEN
C
C	LEFT OF DESIRED LONGITUDE
C
			IF (LAST) THEN
C
C	CLIP INTERSECTION LINE
C
			    	X1=DATIN(I)+360.-SLONG
				Y1=DATIN(I+1)
				Y2=Y1-(Y-Y1)*X1/(X-X1)
				CALL MAPPLT(X,Y2,IPT)
				CALL MAPPLT(X1,Y2,3)
				CALL MAPPLT(X1,Y1,2)
				X=X1
				Y=Y1
			ELSE
				X=DATIN(I)+360.-SLONG
				Y=DATIN(I+1)
				CALL MAPPLT(X,Y,IPT)
			ENDIF
			IPT=2
			LAST=.FALSE.
		ELSE
C
C	RIGHT OF DESIRED LONGITUDE
C
			IF (LAST) THEN
				X=DATIN(I)-SLONG
				Y=DATIN(I+1)
				CALL MAPPLT(X,Y,IPT)
			ELSE
C
C	CLIP INTERSECTION LINE
C
				X1=DATIN(I)-SLONG
				Y1=DATIN(I+1)
				Y2=Y-(Y1-Y)*X/(X1-X)
				CALL MAPPLT(X,Y2,IPT)
				CALL MAPPLT(X1,Y2,3)
				IPT=3
				IF (PENUP) IPT=3
				CALL MAPPLT(X1,Y1,IPT)
				X=X1
				Y=Y1
			ENDIF
			IPT=2
			LAST=.TRUE.
		ENDIF
   20	CONTINUE
	GO TO 10
  999	CONTINUE
	CLOSE(2)
	RETURN
	END
