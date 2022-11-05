	PROGRAM LL2AI
C *** LAST REVISED ON  7-JAN-1995 14:06:20.65
C *** SOURCE FILE: [LONGD.GRAPHICS]LL2AI.FOR
C
C	CREATED: DGL SEPT. 1994
C
C	THIS PROGRAM CONVERTS THE LONGLIB GENERATED POSTSCRIPT INTO
C	ADOBE ILLUSTRATOR-COMPATIBLE POSTSCRIPT
C
	CHARACTER*80 NAME,IFILE,DISK
	CHARACTER*250 LINE,L2
	LOGICAL CONTAINS
C
	FIIX=1.0
	FIIY=1.0
	IIX=1
	IIY=1
	IMCNT=47
C
	WRITE (*,*) 'Adobe Illustrator Postscript Converter'
	WRITE (*,1)
1	FORMAT(' Enter LONGLIB postscript file: ',$)
	READ (*,10) NAME
10	FORMAT(A80)
	IF (NAME.EQ.' ') NAME='OUT.LIS'
C
C	OPEN INPUT FILE OF LONGLIB POSTSCRIPT
C
	OPEN(UNIT=2,FILE=NAME,FORM='FORMATTED',STATUS='OLD',
     $		ERR=99,READONLY)
C
C	READ INPUT FILE HEADER
C
900	READ(2,200,END=950) LINE
	IF (LINE(1:14).EQ.'0 setlinewidth'.OR.
     $	    LINE(2:15).EQ.'0 setlinewidth'.OR.
     $	    LINE(3:16).EQ.'0 setlinewidth') GOTO 960
	IF (LINE(1:14).EQ.'1 setlinewidth'.OR.
     $	    LINE(2:15).EQ.'1 setlinewidth'.OR.
     $	    LINE(3:16).EQ.'1 setlinewidth') GOTO 960
	GOTO 900
950	WRITE (*,*) '*** ERROR READING INPUT FILE HEADER ***'
	STOP
960	CONTINUE
C
	ICNT=INDEX(NAME,'.')
	IF (ICNT.NE.0) NAME=NAME(1:ICNT)
	NAME=NAME(1:LENGTH(NAME))//'AIPS'
	WRITE (*,*) 'Output file: "',NAME(1:LENGTH(NAME)),'"'
C
C	OPEN OUTPUT FILE
C
	OPEN(UNIT=1,FILE=NAME,FORM='FORMATTED',STATUS='NEW')
C
C	SEND INITIALIZATION CODES TO OUTPUT FILE
C
	OPEN(UNIT=3,FILE='/mers1/users/long/LL93/ADIPS.HEADER',FORM='FORMATTED',
     $		STATUS='OLD',READONLY,ERR=310)
910	READ (3,200,END=300) LINE
200	FORMAT(A)
	WRITE(1,200) LINE(1:LENGTH(LINE))
	GOTO 910
300	CONTINUE
	CLOSE(3)
C	WRITE (*,*) 'Adobe Illustrator header copied'
C
C	TOP OF READ LOOP
C
1000	CONTINUE
C
C	READ LINE FROM INPUT FILE
C
	READ (2,200,END=3000) LINE
C
	IF (LINE(1:1).EQ.'%'.OR.LINE(2:2).EQ.'%') THEN	! SKIP
	ELSE IF (CONTAINS(LINE,'translate')) THEN	! image info
		L2=' '
		ICNT=INDEX(LINE,'translate')
		IF (ICNT.NE.0) L2=LINE(ICNT+9:LENGTH(LINE))
		IF (LINE(2:6).EQ.'gsave') LINE=LINE(8:LENGTH(LINE))
		IF (LINE(1:5).EQ.'gsave') LINE=LINE(7:LENGTH(LINE))
		CALL TWOVALUE(LINE,IIX,IIY)
		CALL TWOFVALUE(L2,FIIX,FIIY)
	ELSE IF (CONTAINS(LINE,'.')) THEN		! SKIP
	ELSE IF (CONTAINS(LINE,'setlinewidth')) THEN
		CALL ONEVALUE(LINE,I)
		WRITE(1,404) I
404		FORMAT(I1,' w')
	ELSE IF (CONTAINS(LINE,'s')) THEN
		CALL TWOVALUE(LINE,IX,IY)
		X=IX*4*0.072
		Y=IY*4*0.072
		WRITE (1,601) X,Y
601		FORMAT(F7.3,X,F7.3,' l'/'S')
	ELSE IF (LINE(1:1).EQ.'n'.OR.LINE(2:2).EQ.'n') THEN
		CALL TWOVALUE(LINE(3:50),IX,IY)
		X=IX*4*0.072
		Y=IY*4*0.072
		WRITE(1,600) X,Y
600		FORMAT(F7.3,X,F7.3,' m')
	ELSE IF (CONTAINS(LINE,'l')) THEN
		CALL TWOVALUE(LINE,IX,IY)
		X=IX*4*0.072
		Y=IY*4*0.072
		WRITE (1,603) X,Y
603		FORMAT(F7.3,X,F7.3,' l')
	ELSE IF (CONTAINS(LINE,'d')) THEN
		WRITE (1,403) LINE(1:LENGTH(LINE))
403		FORMAT(A)
C403		FORMAT(A13,'0 d')
	ELSE IF (CONTAINS(LINE,'{<')) THEN		! image
		IMCNT=IMCNT+1
		DISK='DataPak/RadioAmazon'
		IFILE=NAME
		ICNT=INDEX(IFILE,'.')
		IF (ICNT.NE.0) IFILE=IFILE(1:ICNT-1)
		IFILE=IFILE(1:LENGTH(IFILE))//'IMG'//CHAR(IMCNT)//'.EPS'
		CALL TWOVALUE(LINE(1:20),IX,IY)
		WRITE (*,4301) IX,IY,
     $			DISK(1:LENGTH(DISK)),
     $			IFILE(1:LENGTH(IFILE))
4301		FORMAT(/' Grayscale Image Found: (',I,' x',I,')'/
     $		' Stored in file: "',A,'":"',A,'"')
C
		WRITE (1,4500) NINT(IIX*0.25),NINT(IIY*0.25),
     $			NINT(FIIX*0.25),NINT(FIIY*0.25),
     $			DISK(1:LENGTH(DISK)),
     $			IFILE(1:LENGTH(IFILE)),
     $			DISK(1:LENGTH(DISK)),
     $			IFILE(1:LENGTH(IFILE))
4500		FORMAT('[1 0 0 1 ',I5,X,I5,'] 0 0 ',I5,X,I5/
     $			'(',A,':',A,')`'/
     $			'%%IncludeFile:',A,':',A/'~')
C
C	WRITE IMAGE FILE
C
		OPEN(UNIT=4,FILE=IFILE,STATUS='NEW',FORM='FORMATTED')
		WRITE(4,4000) IFILE,IX,IY,IX,IY,IX,IY
4000		FORMAT('%!PS-Adobe-3.0 EPSF-3.0'/
     1	'%%Creator: Photoshop Version 2.0'/
     2	'%%Title: ',A25/
     3	'%%CreationDate: 9/26/94 7:43 AM'/
     4	'%%BoundingBox: 0 0 ',I,X,I/
     5	'%%SuppressDotGainCompensation'/
     6	'%%DocumentProcessColors: Black'/
     7	'%%EndComments'/
     8	'%ImageData: ',I,X,I,' 8 1 0 ',I,' 2 "beginimage"'/
     9	I,' dict begin')
		WRITE(4,4001)
4001		FORMAT('/_image systemdict /image get def'/
     1	'/_setgray systemdict /setgray get def'/
     2	'/_currentgray systemdict /currentgray get def'/
     3	'/_settransfer systemdict /settransfer get def'/
     4	'/_currenttransfer systemdict /currenttransfer get def'/
     5	'/blank 0 _currenttransfer exec'/
     6	'1 _currenttransfer exec eq def'/
     7	'/negative blank'/
     8	'{0 _currenttransfer exec 0.5 lt}'/
     9	'{0 _currenttransfer exec 1 _currenttransfer exec gt}')
		WRITE(4,4002)
4002		FORMAT('ifelse def'/
     1	'/inverted? negative def'/
     2	'/level2 systemdict /languagelevel known'/
     3	'{languagelevel 2 ge} {false} ifelse def'/
     4	'gsave'/
     5	'0 setgray')
		WRITE(4,4010) IY,IX
4010		FORMAT('/rows ',I,' def'/'/cols ',I,' def'/
     1	'72 65536 mul 4718592 div dup cols mul exch rows mul scale'/
     2	'/picstr1 85 string def'/
     3	'/readdata {currentfile exch readhexstring pop} def'/
     4	'/image2 level2 {/image load def} {{begin'/
     5	'Width Height BitsPerComponent ImageMatrix'/
     6	'/DataSource load image end} def} ifelse'/
     7	'/beginimage {'/
     8	'image2'/
     9	'} def')
		WRITE(4,4011)
4011		FORMAT('12 dict begin'/
     1	'/ImageType 1 def'/
     2	'/Width cols def'/
     3	'/Height rows def')
		WRITE(4,4020)
4020		FORMAT('/ImageMatrix [cols 0 0 rows neg 0 rows] def'/
     1	'/BitsPerComponent 8 def'/
     2	'/Decode [0 1] def'/
     3	'/DataSource {picstr1 readdata} def'/
     4	'currentdict end'/
     5	'level2 {'/
     6	'/DeviceGray'/
     7	'setcolorspace} if'/
     8	'beginimage')
C
		DO 4700 WHILE (.TRUE.)
			READ(2,200,END=4950) LINE
			IF (CONTAINS(LINE(1:4),'>}')) GOTO 4800
			IF (LINE(1:1).EQ.' ') THEN
				WRITE(4,200) LINE(2:LENGTH(LINE))
			ELSE
				WRITE(4,200) LINE(1:LENGTH(LINE))
			ENDIF
4700		CONTINUE
C
4800		WRITE(4,4200)
4200		FORMAT('grestore end')
		CLOSE(4)
C
		IF (.FALSE.) THEN
4950			WRITE(*,4300)
4300			FORMAT('***END OF FILE REACHED DURING IMAGE READ ***')
			GOTO 4800
		ENDIF		
	ENDIF
	GOTO 1000
C
C	CLOSE INPUT FILE
C
3000	CONTINUE
110	CLOSE(2)
C
C	WRITE TRAILER
C
	OPEN(UNIT=3,FILE='/mers1/users/long/LL93/ADIPS.TRAILER',FORM='FORMATTED',
     $		STATUS='OLD',READONLY,ERR=510)
410	READ (3,200,END=500) LINE
	WRITE(1,200) LINE(1:LENGTH(LINE))
	GOTO 410
500	CONTINUE
	CLOSE(3)
	CLOSE(1)
 99	STOP
C
C	CLOSE OUTPUT FILE
C
310	CONTINUE
510	CONTINUE
	WRITE (*,*) '*** ERROR READ ADOBE ILLUSTRATOR HEADER OR TRAILER ***'
	STOP
	END
C
C
	LOGICAL FUNCTION CONTAINS(LINE,SUB)
C
C	FIND THE LOCATION OF THE SUBSTRING "SUB" IN THE STRING "LINE"
C	STARTING FROM THE FIRST CHARACTER IN "LINE"
C
	CHARACTER*(*) SUB,LINE
	NLEN=LEN(LINE)
	MLEN=LEN(SUB)
	CONTAINS=.FALSE.
	DO I=1,NLEN
		DO J=1,MLEN
			IF (LINE(I+J-1:I+J-1).NE.SUB(J:J)) GOTO 10
		END DO
		CONTAINS=.TRUE.
		RETURN
10		CONTINUE
	END DO
	RETURN
	END
C
C
	SUBROUTINE TWOVALUE(LINE,IX,IY)
	CHARACTER*(*) LINE
	N=LEN(LINE)
10	IF (LINE.EQ.' ') GOTO 20
	IF (LINE(1:1).EQ.' ') THEN	! REMOVE ANY LEADING SPACES
		LINE=LINE(2:N)
		GOTO 10
	ENDIF
20	CONTINUE
	DO I=1,N
		IF (LINE(I:I).EQ.' ') THEN
			M=I-1
			GOTO 30
		ENDIF
	END DO
	M=N
30	CONTINUE
	READ(LINE(1:M),'(I)') IX
	LINE=LINE(M+2:N)
C
	IF (LINE.EQ.' ') GOTO 40
35	IF (LINE(1:1).EQ.' ') THEN	! REMOVE ANY LEADING SPACES
		LINE=LINE(2:N)
		GOTO 35
	ENDIF
C
	DO I=1,N
		IF (LINE(I:I).EQ.' ') THEN
			M=I-1
			GOTO 40
		ENDIF
	END DO
	M=N
40	CONTINUE
	READ(LINE(1:M),'(I)') IY
	RETURN
	END
C
C
	SUBROUTINE TWOFVALUE(LINE,X,Y)
	CHARACTER*(*) LINE
	N=LEN(LINE)
10	IF (LINE.EQ.' ') GOTO 20
	IF (LINE(1:1).EQ.' ') THEN	! REMOVE ANY LEADING SPACES
		LINE=LINE(2:N)
		GOTO 10
	ENDIF
20	CONTINUE
	DO I=1,N
		IF (LINE(I:I).EQ.' ') THEN
			M=I-1
			GOTO 30
		ENDIF
	END DO
	M=N
30	CONTINUE
	READ(LINE(1:M),'(F)') X
	LINE=LINE(M+2:N)
C
	DO I=1,N
		IF (LINE(I:I).EQ.' ') THEN
			M=I-1
			GOTO 40
		ENDIF
	END DO
	M=N
40	CONTINUE
	READ(LINE(1:M),'(F)') Y
	RETURN
	END
C
C
	SUBROUTINE ONEVALUE(LINE,IX)
	CHARACTER*(*) LINE
	N=LEN(LINE)
10	IF (LINE.EQ.' ') GOTO 20
	IF (LINE(1:1).EQ.' ') THEN	! REMOV ANY LEADING SPACES
		LINE=LINE(2:N)
		GOTO 10
	ENDIF
20	CONTINUE
	DO I=1,N
		IF (LINE(I:I).EQ.' ') THEN
			M=I-1
			GOTO 30
		ENDIF
	END DO
	M=N
30	CONTINUE
	READ(LINE(1:M),'(I)') IX
	RETURN
	END
C
C
	INTEGER FUNCTION LENGTH(LINE)
	CHARACTER*(*) LINE
	N=LEN(LINE)
	DO I=N,1,-1
		IF (LINE(I:I).NE.' '.AND.LINE(I:I).NE.CHAR(0)) THEN
			LENGTH=I
			GOTO 10
		ENDIF
	END DO
	LENGTH=N
10	RETURN
	END
