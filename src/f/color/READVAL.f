	REAL FUNCTION READVAL(DEF,IEND)
C
C	READS A REAL VALUE FROM THE SYS$INPUT IN A FREE FORMAT USING 
C	THE FORTRAN "READ".  INPUT VALUE OR EOF DEFAULT VALUE IS
C	RETURNED.  IF EOF IEND IS SET TO -1.  ON READ ERROR DEFAULT VALUE
C	RETURNED.
C
C	ROUTINE SKIPS LEADING SPACES, THEN USES ONLY NUMERIC CHARACTERS
C	I.E.  "-", ".", "0" THROUGH "9", "E", "e"
C
C	DEF	(R)	INPUT DEFAULT VALUE
C	IEND	(I)	END FLAG
C			  =  0 NORMAL
C			  = -1 EOF ENCOUNTERD
C
	CHARACTER*18 B, FM1
	CHARACTER*1 A
	LOGICAL NUMERIC
C
	IEND=0
	READVAL=DEF
	READ (*,10,END=120,ERR=111) B
 10	FORMAT(18A1)
	ILEN=-1
	IDECFLAG=0
	IEFLAG=0
	ISPACE=-1
	DO 20 I=1,18
		A=B(I:I)
		IF (A.NE.' '.AND.ISPACE.EQ.-1) ISPACE=I-1 ! COUNT LEADING SPACES
		IF (.NOT.NUMERIC(A).AND.ILEN.EQ.-1.AND.
     $			(A.NE.' '.OR.(A.EQ.' '.AND.ISPACE.NE.-1))) ILEN=I-1
		IF (ILEN.EQ.-1.AND.A.EQ.'.') IDECFLAG=I
		IF (ILEN.EQ.-1.AND.(A.EQ.'E'.OR.A.EQ.'e')) IEFLAG=I
20	CONTINUE
	IF (ILEN.LT.1) GOTO 110			! INVALID INPUT
	IF (IEFLAG.NE.0) GOTO 60
	IF (IDECFLAG.EQ.0) GOTO 40
	WRITE (FM1,430) ILEN,ILEN-IDECFLAG
 430	FORMAT('(G',I2.2,'.',I2.2,')')
	READ (B,FM1,ERR=110) XX                 ! FLOATING POINT
C	DECODE(18,30,B,ERR=110) XX		! FLOATING POINT
C30	FORMAT(G<ILEN>.<ILEN-IDECFLAG>)
	GOTO 100
C
40	CONTINUE				! INTEGER INPUT
	WRITE (FM1,450) ILEN
 450	FORMAT('(I',I2.2,')')
	READ(B,FM1,ERR=110) IX
C	DECODE(18,50,B,ERR=110) IX
C50	FORMAT(I<ILEN>)
	XX=IX
	GOTO 100
C
60	CONTINUE
	IF (IDECFLAG.EQ.0) IDECFLAG=IEFLAG
	WRITE (FM1,470) ILEN,IEFLAG-IDECFLAG,ILEN-IEFLAG
 470	FORMAT('(E',I2.2,'.',I2.2,'E',I2.2,')')
	READ (B,FM1,ERR=110) XX
C	DECODE(18,70,B,ERR=110) XX
C70	FORMAT(E<ILEN>.<IEFLAG-IDECFLAG>E<ILEN-IEFLAG>)
C
100	CONTINUE		! VALID INPUT
	READVAL=XX
	RETURN
110	CONTINUE		! DECODE ERROR
	RETURN
111	CONTINUE		! FILE READ ERROR
	RETURN
120	IEND=-1			! EOF
	RETURN
	END
