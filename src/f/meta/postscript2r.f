	PROGRAM POSTSCRIPT2R
C *** LAST REVISED ON 10-FEB-1994 13:58:40.15
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.META]POSTSCRIPT1.FOR
C
C	CREATED: DGL 4-APR-1985
C	MODIFIED: DGL 28-JAN-1991
C	+ ADDED IMAGE CAPABILITY AND CHANGED SCALING
C	MODIFIED: DGL 16-SEPT-1992
C	+ ADDED MACROS TO REDUCE FILE SIZE
C       MODIFIED: DGL 29-DEC-1995
C       + UNIX COMMAND LINE ARGUMENT, SINGLE PAGE ONLY OUTPUT ONLY, OUTPUT FILE
C       MODIFIED: DGL 7-AUG-96
C       + DO NOT ROTATE/TRANSLATE IMAGE (OUTPUT AS PORTRAIT MODE)
C
C	THIS PROGRAM CONVERTS THE LONGLIB METAFILE
C	PRODUCED BY THE LONGLIB GRAPHICS LIBRARY 
C	TO THE POSTSCRIPT LANGUAGE.
C
C	USES INTEGER*2 IN REGET (MAY BE CHANGED TO INTEGER IF DONE
C	IN THE MAIN LONGLIB FILE)
C
	CHARACTER*80 NAME,line
        logical single,portrait
C
        narg=iargc()   ! number of command line arguments
C
C	DEFAULT NAME
C
	NAME='ftn03'	! DEFAULT FILE NAME
        single=.true.
        portrait=.false.
        line='out.lis'
        if (narg.ge.1) then
           call getarg(1,name)
           if (name(1:1).eq.'?') then
              type *
              type *,'Command line options:'
              type *,' 1st arg: file name (default ftn03)'
              type *,' 3rd arg: Landscape (L) or Portrait (P) [Def=L]'
              type *,' 2nd arg: forced single page N=multipage Y=single page',
     $               ' [Def=Y]'
              type *,' 4th arg: output file name (default out.lis)'
              stop
           endif
           type *,'Longlib Postcript Converter (Version 2r)'
           type *,'Input file: ',name
           if (narg.ge.2) then
              call getarg(2,line)
              if (line(1:1).eq.'P'.or.line(1:1).eq.'p') portrait=.true.
           endif
           if (portrait) type *,'Portrait mode'
           if (narg.ge.3) then
              call getarg(3,line)
              if (line(1:1).eq.'N'.or.line(1:1).eq.'n') single=.false.
           endif
           if (single) type *,'Single page output (forced)'
           if (.not.single) type *,'Multiple page output enabled'
           line='out.lis'
           if (narg.ge.4) then
              call getarg(4,line)
           endif
           type *,'Output file:',line
	endif
C
C     CALL WORKING ROUTINE
C
	CALL LPLOT(NAME,single,line,portrait)
C
	STOP
	END
C
	SUBROUTINE LPLOT(NAME,single,output,portrait)
C
C	MAIN ROUTINE TO CONVERT PRINTER GRAPHICS FILE TO POSTSCRIPT
C
C	NAME	(CHARACTER)	FILE NAME
C
	CHARACTER*(*) NAME,output
        logical single,portrait
C
C	DEFINITIONS FOR LINE TYPES
C
	CHARACTER*13 LINETYPE(10)
	DATA LINETYPE(1)/'[]'/,LINETYPE(2)/'[2]'/,LINETYPE(3)/'[4 4]'/
	DATA LINETYPE(4)/'[4 7]'/,LINETYPE(5)/'[2 2]'/
	DATA LINETYPE(6)/'[2 2 2 2 4]'/,LINETYPE(7)/'[6 2 3 2 4]'/
	DATA LINETYPE(8)/'[1 1]'/,LINETYPE(9)/'[1 1 4 4]'/
	DATA LINETYPE(10)/'[1 1 2 2 3 3]'/
C
	INTEGER PENUP
C
C	INITIALIZE VARIABLES
C
	LW=-1		! LINE WIDTH (INVALID TO FORCE NEW WIDTH)
	LT=-1		! LINE TYPE (INVALID TO FORCE NEW TYPE)
	LC=-1		! LINE COLOR (INVALID TO FORCE NEW TYPE)
C
	AMX=288.0
	AMY=288.0
	MP=999
	IXOLD=0
	IYOLD=0
C
C	PENUP IS PEN CONTROL FLAG (0=NO SEGMENT, 2=PEN UP, 3=PEN DOWN)
C
	PENUP=0
	JPCNT=0
C
C	OPEN INPUT FILE PRODUCED BY LONGLIB GRAPHICS LIBRARY
C
	OPEN(UNIT=2,FILE=NAME,FORM='UNFORMATTED',STATUS='OLD')
C     $		ERR=99,READONLY)
C
C	OPEN OUTPUT FILE
C
	OPEN(UNIT=1,FILE=output,FORM='FORMATTED',STATUS='NEW')
C
C	SEND INITIALIZATION CODES TO OUTPUT FILE
C
 	WRITE (1,200)
200	FORMAT('%!PS-Adobe-2.0',
     $	/'%Title: PostScript for LongLib',
     $	/'%Creator: D. Long VAX VMS (POSTSCRIPT)',
     $	/'%Creation Date: Mon Aug 27, 1990',
     $	/'%Pages: (atend) 1',
     $	/'%EndComments',
     $	/' % Function definitions to reduce filesize',
     $	/' /g { grestore showpage } bind def',
     $	/' /l { lineto } bind def',
     $	/' /m { moveto } bind def',
     $	/' /s { moveto closepath stroke } bind def',
     $	/' /n { newpath } bind def',
     $	/' /i { image grestore } bind def',
     $	/' /d { setdash } bind def',
     $	/'%Page:1 1')
 	WRITE (1,300)
300	FORMAT(	X,'1 setlinejoin',	! LINE JOIN TYPE
     $		X,'0 setlinecap',	! LINE END CAP
     $		X,'[] 0 setdash',	! SOLID LINE
     $		X,'0 setlinewidth',	! SINGLE LINE WIDTH
     $		X,'0 setgray',/		! BLACK LINE
     $		X,'0.25 0.25 scale'	! SCALE TO 288 DOTS/INCH
     $		X,'gsave')
	jps = 1
C
C	TOP OF LONGLIB META-FILE READ LOOP
C
1000	CONTINUE
C
C	READ INITIAL COMMAND CODE AND PARAMETERS FROM LONGLIB META-FILE
C
	CALL REGET(M1,M2,M3,MP,2)
C
C	CHECK END OF FILE
C
	IF (M3.EQ.11) GOTO 110
	SX=M1
	SY=M2
	IF (M1.EQ.0.OR.M2.EQ.0) GOTO 110
  1	CONTINUE
C
C	READ COMMAND CODE AND PARAMETERS FROM LONGLIB META-FILE
C
	CALL REGET(M1,M2,M3,MP,2)
C
C	COORDINATE TRANSFORM
C
  2	Y1=M1/SX
	X1=M2/SY
	I3=M3
	IOLD=-1
C
C	CHECK END OF FILE
C
	IF (M3.GT.999) GOTO 999
C
C	EXECUTE META-FILE COMMAND
C
	GOTO (10,20,20,10,10,10,10,10,20,100,110) I3
10	GOTO 1
C
C	INTERPRET COMMAND
C
20	CONTINUE
C
C	"CALL PLOT(X1,Y1,I3)"
C
C	CONVERT TO INTEGER 0.25/72'S INCH
C
        IF (PORTRAIT) THEN
           IX=INT(X1*288+0.5)+5 ! 0.25 * 72th's of an inch portrait
           IY=INT(Y1*288+0.5)
           IF (IX.LT.0) IX=0
           IF (IY.LT.0) IY=0
        ELSE
           IX=INT(Y1*288+0.5)+5 ! 0.25 * 72th's of an inch landscape
           IY=3120-INT(X1*288+0.5)
           IF (IY.LT.0) IY=0
        ENDIF
C
	IF (I3.EQ.3) THEN
C
C	PEN UP MOVE
C
		IF (PENUP.EQ.2) THEN
			KX=IDIGITS(IXOLD)
			KY=IDIGITS(IYOLD)
			WRITE (1,601) IXOLD,IYOLD
cc601			FORMAT(X,I<KX>,X,I<KY>,' moveto closepath stroke')
601			FORMAT(X,I<KX>,X,I<KY>,' s')
		ENDIF
		PENUP=3
		JPCNT=0
	ELSE
C
C	PEN DOWN MOVE
C 				! PEN DOWN MOVE
		IF (PENUP.EQ.3) THEN
			KX=IDIGITS(IXOLD)
			KY=IDIGITS(IYOLD)
			WRITE (1,600) IXOLD,IYOLD
cc600			FORMAT(X,'newpath ',I<KX>,X,I<KY>,' moveto')
600			FORMAT(X,'n ',I<KX>,X,I<KY>,' m')
			JPCNT=0
		ENDIF
		PENUP=2
		KX=IDIGITS(IX)
		KY=IDIGITS(IY)
C
C	OUTPUT LINE CONTINUATION.  IF # POINTS EXCEEDS 256, OUTPUT
C	ALSO, DON'T OUTPUT REDUNDANT POINTS
C
		IF (JPCNT.GT.256) THEN
			WRITE (1,601) IX,IY
			WRITE (1,600) IX,IY
			JPCNT=0
		ELSE
			IF (JPCNT.EQ.0.OR.(IX.NE.IXOLD.OR.IY.NE.IYOLD)) THEN
				WRITE (1,603) IX,IY
cc603				FORMAT(X,I<KX>,X,I<KY>,X,'lineto')
603				FORMAT(X,I<KX>,X,I<KY>,X,'l')
				JPCNT=JPCNT+1
			ENDIF
		ENDIF
	ENDIF
	IXOLD=IX
	IYOLD=IY
	GOTO 1
C
100	CONTINUE
C
C	"CALL NEWPAGE"
C
        if (single) goto 110
	IF (PENUP.EQ.2) THEN
		KX=IDIGITS(IXOLD)
		KY=IDIGITS(IYOLD)
		WRITE (1,601) IXOLD,IYOLD
		PENUP=0
		JPCNT=0
	ENDIF
	JPS = JPS+1
	WRITE (1,402) JPS,JPS
cc402	FORMAT(X,'grestore showpage',
402	FORMAT(X,'g',
     $	/'%Page: ',I2,1X,I2/
     $		X,'0.25 0.25 scale'	! SCALE TO 288 DOTS/INCH
     $		X,'gsave')
	WRITE (1,403) LINETYPE(LT+1)
	WRITE (1,404) LW-1
	GOTO 1
C
C	SPECIAL COMMANDS
C
999	CONTINUE
	JPCNT=0
	IF (I3.GT.1999) GOTO 1999
	GOTO (1000,1001,1002,1003) I3-999
998	GOTO 1
C
C	NEW PEN/LINE TYPE
C
1001	CONTINUE
	IF (M1.LT.0) M1=0
	IF (M1.GT.9) M1=MOD(M1,10)
	IF (M1.NE.LT) THEN
		IF (PENUP.EQ.2) THEN
			KX=IDIGITS(IXOLD)
			KY=IDIGITS(IYOLD)
			WRITE (1,601) IXOLD,IYOLD
			PENUP=0
		ENDIF
		WRITE (1,403) LINETYPE(M1+1)
		LT=M1
	ENDIF
cc403	FORMAT(X,A13,' 0 setdash')
403	FORMAT(X,A13,' 0 d')
	GOTO 1
C
C	LINE COLOR
C
1002	CONTINUE
c	LW=M1
C
C	INCLUDE PEN COLOR AS GRAY SCALE (0-16) BLACK=16, WHITE=0
C
	IF (M2.NE.LC) THEN
C
C	"CALL PLOT(FLOAT(M2),0.,0)"
C
C		WRITE (1,407) FLOAT(M2-1)/16.
C 407		FORMAT(X,F4.2,' setgray')
	ENDIF
	LC=M2
	GOTO 1
C
C	LINEWIDTH
C
1003	CONTINUE
C
C	"CALL NEWPEN(I3)"
C
	IF (M1.LE.0) M1=1
C
C	NOTE: THE LINEWIDTH IS GRAPHICS DEVICE DEPENDENT AND MAY VARY
C	DEPENDING ON LINE ORIENTATION
C
	IF (M1.NE.LW) THEN
		IF (PENUP.EQ.2) THEN
			KX=IDIGITS(IXOLD)
			KY=IDIGITS(IYOLD)
			WRITE (1,601) IXOLD,IYOLD
			PENUP=0
		ENDIF
C
C	NEW LINE WIDTH
C
		WRITE (1,404) M1-1
404		FORMAT(X,I2,' setlinewidth')
		LW=M1
	ENDIF
	GOTO 1
C
C	IMAGE MODE
C
1999	CONTINUE
C
C	CHECK EACH OPTION
C
	IF (I3.EQ.2000) THEN
		Y1=M1/SX
		X1=M2/SY
		AMX=X1*288
		AMY=Y1*288
	ENDIF
	IF (I3.EQ.2001) THEN
		INX=M1
		IF (INX.LT.1) INX=1
		INY=M2
		IF (INY.LT.1) INY=1
		NUM=INX*INY
                IF (PORTRAIT) THEN
		 WRITE (1,2019) IXOLD,IYOLD,AMY,AMX,INY,INX,INX,INY
 2019            FORMAT(' gsave ',I4,X,I4,' translate ',
     $                F10.4,X,F10.4,' scale '/
     $                X,I4,X,I4,' 8 [0 ',I4,X,I4,' 0 0 0] {<')
                ELSE
		 IY=IYOLD-NINT(AMY)
		 WRITE (1,2020) IXOLD,IY,AMX,AMY,INY,INX,INY,-INX,INX
2020		 FORMAT(' gsave ',I4,X,I4,' translate ',
     $                F10.4,X,F10.4,' scale '/
     $                X,I4,X,I4,' 8 [',I4,' 0 0 ',I4,' 0 ',I4,'] {<')
                ENDIF
C
C	READ IMAGE DATA AND CONVERT TO HEXIDECIMAL
C		
		IF (MOD(NUM,2).EQ.1) NUM=NUM+1
		NUM=NUM/2
		IC=0
		DO 2002 I=1,NUM
			CALL REGET(M1,M2,M3,MP,2)
			IF (M3.NE.2002) GOTO 2
			CALL HEXIT(M1,M2,IC)
2002		CONTINUE
		IF (IC.GT.0) CALL HEXIT(M1,M2,-IC)
		WRITE (1,2030)
cc2030		FORMAT(' >} image grestore')
2030		FORMAT(' >} i')
	ENDIF
	GOTO 1
C
C	CLOSE INPUT FILE
C
110	CLOSE(2)
C
	IF (PENUP.EQ.2) THEN
		KX=IDIGITS(IXOLD)
		KY=IDIGITS(IYOLD)
		WRITE (1,601) IXOLD,IYOLD
		PENUP=0
	ENDIF
C
	WRITE (1,410)jps
cc410	FORMAT(X,'grestore showpage',
410	FORMAT(X,'g',
     $	/'%Trailer',
     $	/'%Pages: ',I2,1X,'1',
     $	/)
C
C	CLOSE OUTPUT FILE
C
	CLOSE(1)
 99	RETURN
	END
C
	SUBROUTINE REGET(M1,M2,M3,MP,ILU)
C
C	READ DATA FROM LONGLIB META-FILE PRINTER DATA FILE
C	
	INTEGER*2 M(128)
	MP=MP+3
	IF (MP.GT.128) THEN
		READ (ILU,ERR=99) M
		MP=3
	ENDIF
	M3=M(MP)
	M2=M(MP-1)
	M1=M(MP-2)
	IF (M3.EQ.999) GOTO 99
	RETURN
99	M3=11
	RETURN
	END
C
C
	INTEGER FUNCTION IDIGITS(I)
	N=1
	IF (I.GT.9) N=N+1
	IF (I.GT.99) N=N+1
	IF (I.GT.999) N=N+1
	IF (I.GT.9999) N=N+1
	IDIGITS=N
	RETURN
	END
C
C
	SUBROUTINE HEXIT(I,J,IC)
	INTEGER C(38)
	IF (IC.EQ.0) ICNT=1
	IF (IC.LT.0) THEN		! DUMP OUTPUT BUFFER
		IF (ICNT.GT.1) WRITE (1,10) (C(I),I=1,ICNT-1)
		ICNT=1
		GOTO 100
	ENDIF
	IC=1
	C(ICNT)=I
	IF (C(ICNT).LT.0) C(ICNT)=0
	IF (C(ICNT).GT.255) C(ICNT)=255
	ICNT=ICNT+1
	C(ICNT)=J
	IF (C(ICNT).LT.0) C(ICNT)=0
	IF (C(ICNT).GT.255) C(ICNT)=255
	ICNT=ICNT+1
	IF (ICNT.GE.38) THEN
		WRITE (1,10) (C(I),I=1,38)
		ICNT=1
	ENDIF
10	FORMAT(X,38Z2.2)
100	RETURN
	END
