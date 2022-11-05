C
C *** LAST REVISED ON  8-DEC-1993 08:01:28.38
C *** SOURCE FILE: [LONGD.TEMP]WORLDMAP.FOR
C
	SUBROUTINE WORLDMAP(XFORM,ALATMIN,ALATMAX,
     $      ALONMIN,ALONMAX,IPFLAG,ILU)
	EXTERNAL XFORM
C
C	WRITTEN BY D. LONG NOV. 1992
C
C	DRAWS A LAND-EDGE MAP USING DATA FROM VECTOR LAND MAP FILE
C	USES USER SUPPLIED TRANSFORMATION
C
C	XFORM	*	USER SUPPLIED SUBROUTINE TO PERFORM TRANSFORMATION
C	ALATMIN, ALATMAX REAL	MIN, MAX LATTITUDE TO ATTEMPT TO PLOT
C	ALONMIN, ALONMAX REAL	MIN, MAX LONGITUDE TO PLOT
C	IPFLAG	INT	LONGITUDE OPTION FLAG FOR ALONMAX, ALONMIN
C			= 0 IGNORE MIN, MAX LONGITUDE
C			= 1 USE +/- 180
C			= 2 USE 0 TO 360
C	ILU	INT	FORTRAN UNIT NUMBER TO USE FOR DATA FILE READING
C
	REAL DATIN(10)
        INCLUDE 'files.inc'
C
C	OPEN DATA FILE
C
	OPEN(UNIT=ILU,FILE=EARTH,
     $		FORM='FORMATTED',
     $		STATUS='OLD')
C     $          ,READONLY)
C	IPT=3
C
C	READ THE DATA
C
   10	READ(ILU,1005,END=999) DATIN
 1005	FORMAT(10F8.0)
C
C	CHECK THE STORED DATA COMMAND
C
	DO 20 I=1,10,2
		IF (IFIX(DATIN(I)).EQ.0.AND.
     $ 		    IFIX(DATIN(I+1)).EQ.0) GOTO 20
		IF (DATIN(I+1).EQ.888.8) THEN		! END OF SEGMENT
			IPT=3
			CALL XFORM(ALON,ALAT,IPT)
			GOTO 20
		ENDIF
		IF (ABS(DATIN(I)).GT.180.5.OR.		! BAD POINT
     $		    ABS(DATIN(I+1)).GT.91.0) THEN	! BAD POINT
			IPT=3
			GOTO 20
		ENDIF
		ALON=MOD(DATIN(I)+360.0,360.0)
		ALAT=DATIN(I+1)
		IF (IPFLAG.NE.0.0) THEN
			IF (IPFLAG.EQ.1) THEN
				IF (ALON.GT.180.0) ALON=ALON-360.0
			ENDIF
			IF (ALAT.GT.ALATMIN.AND.ALAT.LT.ALATMAX.AND.
     $			    ALON.GT.ALONMIN.AND.ALON.LT.ALONMAX) THEN
				CALL XFORM(ALON,ALAT,IPT)
				IPT=2
			ELSE
			   IF (IPT.EQ.2) CALL XFORM(ALON,ALAT,IPT)
			   IPT=3
			ENDIF
		ELSE
			CALL XFORM(ALON,ALAT,IPT)
			IPT=2
		ENDIF
   20	CONTINUE
	GOTO 10
  999	CONTINUE
	CLOSE(ILU)
	CALL PLOT(0.,0.,5)	! DUMP PLOT BUFFER
C
	RETURN
	END