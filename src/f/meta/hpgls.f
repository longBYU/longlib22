	PROGRAM HPGLS
C *** LAST REVISED ON 26-AUG-1987 10:48:23.83
C *** SOURCE FILE: [DL.GRAPHICS.LONGLIB]HPGLS.FOR
C
C	CREATED:  DGL AUG 1987
C
C	THIS PROGRAM CONVERTS THE LONGLIB PRINTER HISTORY META FILE
C	INTO AN HPGL COMPATIBLE PLOT FILE.  THIS VERSION USES AN
C	INTERMEDIATE PEN MOTION FILE TO MINIMIZE PEN MOTIONS AND
C	CHANGES.  WHEN A NEWPAGE IS ENCOUNTERED IN THE INPUT METAFILE
C	OR WHEN A NEW STRIP IS GENERATED, THE OUTPUT FILE IS CLOSED
C	AND A NEW OUTPUT FILE OPENED.  THUS, EACH PAGE OR PLOT OF
C	OUTPUT IS IN A DIFFERENT FILE.  NOTE: NO ATTEMPT TO MINIMIZE
C	THE OUTPUT FILE LENGTH BY COMMAND COMPRESSION HAS BEEN MADE.
C
C	THIS PROGRAM IS FORTRAN 77 COMPATIBLE WITH THE EXCEPTIONS:
C		1. TABS (^I) ARE USED TO INDENT LINES.
C		2. A VAX DEPENDENT ROUTINE IS USED TO GET COMMAND LINE.
C		3. INTEGER*2 USED IN REGET ROUTINE.  THIS CAN BE CHANGED
C		   TO INTEGER IF THIS IS ALSO DONE IN LONGLIB PRINTER
C		   HISTORY ROUTINES LIBRARY.
C
	CHARACTER*80 NAME
C
C	MACHINE DEPENDENT METHOD OF GETING THE FILE NAME FROM THE
C	RUN COMMAND LINE
C
	IERR=LIB$GET_FOREIGN(NAME,,IFLAG)
C
C	IF FILE NAME WAS NOT PRESENT ON ARGUMENT LINE THEN USE DEFAULT FILE NAME
C
	IF (NAME.EQ.' ') NAME='FOR003.DAT'
C
C	OPTION FLAGS
C	 ISTRIP = 1	ENABLES STRIPPING
C	 ISTRIP = 0	DISABLES STRIPPING
C	 IPRINT = 0	PROGRAM RUNS QUIETLY
C	 IPRINT = 1	PROGRAM PRINTS STATUS LINES
C
	ISTRIP=1
	IPRINT=0
C
C	OPEN INPUT LONGLIB PRINTER HISTORY META FILE
C
	OPEN(UNIT=2,FILE=NAME,FORM='UNFORMATTED',STATUS='OLD',
     $		READONLY,ERR=299)
C
C	OPEN TEMPORARY WORKING FILE
C
	OPEN(UNIT=1,FILE='HPGL.TMP',FORM='UNFORMATTED',
     $		STATUS='SCRATCH',ERR=199,ACCESS='SEQUENTIAL')
C
C	OPEN OUTPUT FILE AND SEND INITIALIZATION CODES
C
	CALL NEWFILE(3)
C
C	CONVERT LONGLIB META FILE INTO HPGL FILE
C
	CALL RASCAN(1,2,3,ISTRIP,IPRINT)
C
C	CLOSE FILES AND TERMINATE PROGRAM
C
	CLOSE(1)
	CLOSE(2)
	GOTO 999
C
C	FILE OPEN ERRORS
C
199	WRITE(*,198)
198	FORMAT(' *** COULD NOT OPEN TEMPORARY FILE ***')
	GOTO 999
299	WRITE(*,298)
298	FORMAT(' *** COULD NOT OPEN INPUT FILE ***')
999	STOP
	END
C
C
	SUBROUTINE NEWFILE(LU)
C
C	OPEN NEW OUTPUT FILE
C
	OPEN(UNIT=LU,FILE='OUT.LIS',FORM='FORMATTED',
     $		STATUS='NEW',ERR=399)
C
C	SEND INITIALIZATION CODES TO PLOTTER
C
	CALL PRINIT(LU)
	RETURN
C
C	FILE OPEN ERROR
C
399	WRITE(*,398)
398	FORMAT(' *** COULD NOT OPEN NEW OUTPUT FILE ***')
	RETURN
	END
C
	SUBROUTINE PRINIT(LU)
C
C	SEND OUTPUT DEVICE INITIALIZATION CODES INTO OUTPUT FILE
C
C	WRITE (LU,2) 27		! VT100/VT220 PRINTER PORT ENABLE
C2	FORMAT(X,A1,'[?5i')
C
	WRITE (LU,1)
1	FORMAT(' IN;SP1;PU;LT-1;')
	RETURN
	END
C
	SUBROUTINE PRCLOS(LU)
C
C	SEND CLOSING CODES TO OUTPUT FILE
C
	WRITE (LU,1)
1	FORMAT(' PU;SP0;')
C
C	WRITE (LU,2) 27		! VT100/VT220 PRINTER PORT DISABLE
C2	FORMAT(X,A1,'[?4i')
	RETURN
	END
C
	SUBROUTINE ENPAGE(LU)
C
C	FINSH CURRENT PAGE
C
	DATA IPAGE/0/
C
C	OUTPUT PAGE COUNTER
C
	IPAGE=IPAGE+1
	WRITE (*,1) IPAGE
1	FORMAT(' *** NEW OUTPUT PLOT PAGE NUMBER ',I3)
	CALL PRCLOS(LU)
	CLOSE(LU)
	RETURN
	END
C
C
	SUBROUTINE RASCAN(LUT,LUI,LUO,ISTRIP,IPRINT)
C
C	INPUT:
C
C	LUT	(I)	OPEN TEMPORARY FILE LOGICAL UNIT NUMBER
C	LUI	(I)	INPUT FILE LOGICAL UNIT NUMBER
C	LUO	(I)	OUTPUT FILE LOGICAL UNIT NUMBER
C	ISTRIP	(I)	STRIPPING CONTROL FLAG
C			  NO STRIPPING=0
C			  AUTO STRIPPING=1
C	IPRINT	(I)	PRINT STATUS CONTROL FLAG
C			  NO PRINT=0
C			  SHOW STATUS=1
C
C	READ INPUT FILE, DECODE COMMANDS, REMOVE REDUNDANT COMMANDS,
C	ELIMINATE ORIGIN CHANGE COMMANDS, AND COPY TO TEMPORARY PEN
C	MOTION FILE.
C
C	LONGLIB META FILE COMMANDS
C
C	IC	COMMAND
C
C	2	PEN DOWN MOVE
C	3	PEN UP MOVE
C	-2	PEN DOWN MOVE WITH NEW ORIGIN
C	-3	PEN UP MOVE WITH NEW ORIGIN
C	9	PEN ERASE MOVE
C	-9	PEN ERASE WITH NEW ORIGIN
C	10	NEW PAGE
C	11	END OF FILE
C	999	END OF FILE
C	1000	SET RESOLUTION
C	1001	SET LINE TYPE
C	1002	SET PEN COLOR
C	1003	SET LINE WIDTH
C	(ELSE)	INVALID
C
C	FIRST COMMAND IN FILE SHOULD SET RESOLUTION
C	SECOND AND THIRD COMMANDS SHOULD SET LINE TYPE AND WIDTH
C
	INTEGER ICOM(13),ITRN(14),ICOLS(16)
	DATA ICOM/2,3,-3,1001,1002,1003,10,-2,9,-9,11,999,1000/
	DATA ITRN/2,3, 3,   6,   5,  10, 8, 2,4, 4, 9,  9,   7,1/
	INTEGER M(128)
	LOGICAL BLANK,PENUP,LAST,PENCOL,PENTYP,FILE
C
	COMMON /RAST/XSWIDE,YSWIDE,XRES,YRES,XLIM,YLIM,IXOFF,IYOFF,MAXSTR
C
C	SET OUTPUT DEVICE DEPENDENT PARAMETERS
C
	CALL SETPAR
C
C	SET MISC PARAMETERS
C
C	SX	DEFAULT X RESOLUTION OF METAFILE (INCH/DOT)
C	SY	DEFAULT Y RESOLUTION OF METAFILE (INCH/DOT)
C	IFIRST	FIRST OUTPUT PAGE FLAG
C	FILE	OPEN OUTPUT FILE FLAG
C
	SX=500.
	SY=500.
	IFIRST=0
	FILE=.TRUE.
C
C	INITIALIZE LAST LINE/COLOR 
C
	LSC=1
	LWIDE=1
	LLINE=0
	LCOL=1
	PENCOL=.TRUE.
	PENTYP=.TRUE.
C
C	INITIALIZE PAGE COUNTER
C
	NPAGE=1
	ICC=0
C
	IF (IPRINT.NE.0) WRITE(*,3000)
3000	FORMAT(' BEGIN HPGL CONVERSION')
C
C	INITIALIZE FILE BUFFERS
C
	MP=999
	NPCNT=1
C
C	INITIALIZE PAGE STRIP COUNTERS
C
12	CONTINUE
	IF (IPRINT.NE.0) WRITE(*,3010) NPAGE
3010	FORMAT(' BEGIN FIRST STRIP OF INPUT PAGE',I6)
	NXSTRIP=1
	NYSTRIP=1
	XMAX=0.
	YMAX=0.
	NCOL=0
C
C	NOTE THAT ORIGIN IS NOT PRESERVED OVER INPUT PAGE CHANGE
C
	XORG=0.
	YORG=0.
C
C	CHECK FOR COMPLETION OF TASK
C
	IF (ICC.EQ.11.OR.ICC.EQ.999) GOTO 110
C
C	START NEW STRIP
C
112	CONTINUE
C
C	INITIALIZE BLANK PAGE FLAG
C
	BLANK=.TRUE.
C
C	INITIALIZE LAST X,Y COMMANDS (LX,LY) ARE QUANTIZED VERSIONS
C
	PX=0.
	PY=0.
	LX=0
	LY=0
C
C	PENUP FLAG INDICATES POSITION OF PEN WHILE LAST FLAG INDICATES
C	WHETHER WE HAVE OUTPUT LAST COORDINATE
C
	PENUP=.TRUE.
	LAST=.FALSE.
C
C	READ EACH COMMAND IN HISTORY FILE
C
13	CALL REGET(M1,M2,ICC,MP,LUI,M)
C
C	CHECK FOR END OF FILE
C
	IF (ICC.EQ.11.OR.ICC.EQ.999) GOTO 10
C
C	DETERMINE COMMAND CODE
C
	DO 210 IC=1,13
		IF (ICOM(IC).EQ.ICC) GOTO 215
210	CONTINUE
	IC=14
215	CONTINUE
C
C	DECODE COMMAND AND EXECUTE
C
	GOTO (23,23,23,1001,1002,1003,10,23,23,23,10,10,1000) IC
	GOTO 13
C
C	HANDLE A PEN MOTION COMMAND
C
23	CONTINUE
C
C	CONVERT INPUT INTEGERS INTO REAL LOCATION VALUES
C
	Y1=M1*SY+YORG
	X1=M2*SX+XORG
C
C	DETERMINE MAXIMUM AND MINIMUM VALUES USED FOR X AND Y TO DETERMINE
C	HOW MUCH STRIPING IS NEEDED
C
	XMAX=AMAX1(XMAX,X1)
	YMAX=AMAX1(YMAX,Y1)
C
C	RESET ORIGIN
C
	IF (ICC.LT.0) THEN
		XORG=X1
		YORG=Y1
	ENDIF
C
C	CLIP LINE TO CURRENTLY VISIBLE STRIP
C
	X2=X1-(NXSTRIP-1)*XSWIDE
	Y2=Y1-(NYSTRIP-1)*YSWIDE
C
C	FOR PEN UP MOVES WE NEED ONLY STORE THE POINT
C
	IF (ITRN(IC).EQ.3) THEN
		PX=X2
		PY=Y2
		LX=-99
		LY=-99
		PENUP=.TRUE.
		LAST=.FALSE.
		GOTO 13
	ENDIF
C
C	GET CLIP FLAGS
C
	CALL CLIPS(IVT,XV1,YV1,XV2,YV2,X2,Y2,PX,PY,0.,0.,XLIM,YLIM)
C
C	CHECK FOR ENTIRELY INVISIBLE LINE
C
	IF (IVT.NE.0) THEN
		PX=X2
		PY=Y2
		LX=-99
		LY=-99
		PENUP=.TRUE.
		LAST=.FALSE.
		GOTO 13
	ENDIF
C
C	LINE IS AT LEAST PARTLY VISIBLE, SEND TO INTERMEDIATE PEN MOTION FILE
C	FIRST SEND LINE TYPE AND WIDTH IF NEEDED
C
	IF (FILE) THEN
		CALL NEWFILE(LUO)
		FILE=.FALSE.
	ENDIF
	IF (PENTYP) THEN
		CALL PENOUT(LLINE,LSC,6,NPCNT,LUT)
		PENTYP=.FALSE.
	ENDIF
	IF (PENCOL) THEN
		DO 450 IJ=1,NCOL
			IF (LCOL.EQ.ICOLS(IJ)) GOTO 460
450		CONTINUE
		NCOL=NCOL+1
		ICOLS(NCOL)=LCOL
460		CALL PENOUT(LWIDE,LCOL,5,NPCNT,LUT)
		PENCOL=.FALSE.
	ENDIF
C
C	SEND FIRST COORDINATE
C
	IX=IFIX(XV2*XRES+0.4999)+IXOFF
	IY=IFIX(YV2*YRES+0.4999)+IYOFF
	IF (.NOT.LAST.OR.IX.NE.LX.OR.IY.NE.LY) THEN
		CALL PENOUT(IX,IY,3,NPCNT,LUT)
		LAST=.TRUE.
		PENUP=.TRUE.
	ENDIF
	LX=IX
	LY=IY
	IX=IFIX(XV1*XRES+0.4999)+IXOFF
	IY=IFIX(YV1*YRES+0.4999)+IYOFF
	PX=X2
	PY=Y2
C
C	SEND SECOND COORDINATE IF NEEDED
C
	IF (PENUP.OR.IX.NE.LX.OR.IY.NE.LY) THEN
		CALL PENOUT(IX,IY,ITRN(IC),NPCNT,LUT)
	ENDIF
	PENUP=.FALSE.
	LX=IX
	LY=IY
C
C	IF VISIBLE PEN DOWN MOTION OCCURS THEN FLAG PAGE AS NOT BLANK
C
	IF (ITRN(IC).EQ.2) BLANK=.FALSE.
	GOTO 13
C
C	HANDLE NEW PAGE COMMANDS
C
10	CONTINUE
C
C	WRITE LAST RECORD TO TEMPORARY FILE
C
	CALL PENOUT(NXSTRIP,NYSTRIP,8,NPCNT,LUT)
C
C	REWIND TEMPORARY FILE
C
	REWIND(LUT)
C
C	OUTPUT CURRENT STRIP IF NOT BLANK
C
	IF (.NOT.BLANK) THEN
		IF (IPRINT.NE.0) WRITE(*,3020) NXSTRIP,NYSTRIP
3020		FORMAT(' OUTPUT STRIP ',I6,',',I6)
		CALL MAKEP(LUT,LUO,ICOLS,NCOL)
		IF (.NOT.FILE) CALL ENPAGE(LUO)
		REWIND(LUT)
		IFIRST=1
		FILE=.TRUE.
	ELSE
		IF (IPRINT.NE.0) WRITE(*,3030) NXSTRIP,NYSTRIP
3030		FORMAT(' BLANK STRIP ',I6,',',I6)
	ENDIF
C
C	COMPUTE NUMBER OF STRIPS NEEDED
C
	NXM=XMAX/XSWIDE+1
	NYM=YMAX/YSWIDE+1
C
C	IS STRIPPING ENABLED?  IF NOT INCREMENT PAGE AND CONTINUE
C
	IF (ISTRIP.NE.1) THEN
		IF (IPRINT.NE.0) WRITE(*,3045) NXSTRIP*NYSTRIP,NPAGE
3045		FORMAT(' STRIPPING DISABLED. ',I6,' STRIPS REQUIRED',
     $			' FOR INPUT PAGE',I6)
		NPAGE=NPAGE+1
		GOTO 12
	ENDIF
C
C	HAVE WE DONE ALL THE STRIPS THAT ARE REQUIRED?
C	IF NOT THEN REWIND INPUT FILE AND REPROCESS
C	OTHERWISE INCREMENT PAGE COUNTER AND PROCESS NEXT CASE
C
	IF (NXSTRIP.GE.NXM.AND.NYSTRIP.GE.NYM) THEN
		NPAGE=NPAGE+1
		GOTO 12
	ENDIF
C
C	NEW STRIP NUMBER
C
	IF (NXSTRIP.LT.NXM) THEN
		NXSTRIP=NXSTRIP+1
	ELSE
		NXSTRIP=1
		NYSTRIP=NYSTRIP+1
	ENDIF
C
C	WRITE WARNING IF NUMBER OF STRIPS EXCEEDS MAXIMUM
C
	IF (NXSTRIP*NYSTRIP.GT.MAXSTR.AND.NXSTRIP.EQ.1
     $		.AND.NYSTRIP.EQ.1) WRITE(*,3055) NXSTRIP*NYSTRIP,NPAGE
3055	FORMAT(' *** WARNING ',I6,' STRIPS REQUIRED FOR INPUT PAGE',I6)
C
	IF (IPRINT.NE.0) WRITE(*,3050) NXSTRIP,NYSTRIP,NXM,NYM
3050	FORMAT(' REREAD INPUT STRIP',I6,',',I6,'  OF ',I6,',',I6)
C
C REWIND INPUT FILE AND FIND CORRECT PAGE LOCATION
C
	REWIND(LUI)
	MP=999
C
C	FIND CORRECT LOCATION IN FILE
C
	IPGE=1
40	CONTINUE
C
C	IS THE CURRENT PAGE THE SAME AS THE PAGE POINTER IN THE FILE?
C	IF SO START NEW STRIP
C
	IF (IPGE.EQ.NPAGE) GOTO 112
45	CALL REGET(M1,M2,ICC,MP,LUI,M)
C
C	CHECK FOR END OF FILE -- IF WE HAVE REACHED IT WE ARE IN TROUBLE
C	SO EXIT WITH ERROR
C
	IF (ICC.EQ.11.OR.ICC.EQ.999) GOTO 199
C
C	COUNT UP NEW PAGE COMMANDS, SKIP THE REST
C
	IF (ICC.NE.10) GOTO 45
	IPGE=IPGE+1
	GOTO 40
C
C	SET RESOLUTION
C
1000	CONTINUE
C
C	CHECK FOR INPUT ERROR -- IF THERE IS, EXIT
C
	IF (M1.EQ.0.OR.M2.EQ.0) GOTO 110
	SX=1./FLOAT(M1)
	SY=1./FLOAT(M2)
	GOTO 13
C
C	CHANGE LINE TYPE COMMAND
C
1001	CONTINUE
C
C	M1 = LINE TYPE PATTERN MASK
C	M2 = LINE TYPE SCALE FACTOR
C
	IF (M1.NE.LLINE.OR.LSC.NE.M2) PENTYP=.TRUE.
	LLINE=M1
	LSC=M2
	GOTO 13
C
C	CHANGE COLOR COMMAND
C
1002	CONTINUE
C
C	M2 IS THE COLOR INDEX
C
	IF (M2.NE.LCOL) PENCOL=.TRUE.
	LCOL=M2
	GOTO 13
C
C	NEW PEN WIDTH
C
1003	CONTINUE
C
C	M1 IS THE PEN WIDTH
C
	IF (M1.LT.0) M1=0
	IF (M1.NE.LWIDE.AND.M1.NE.0) THEN
		LWIDE=M1
	ENDIF
	GOTO 13
C
C	ALL FINISHED WITH EVERYTHING
C
110	CONTINUE
	RETURN
C
199	CONTINUE
	WRITE(*,198)
198	FORMAT(' *** ERROR IN INPUT FILE REACHED END OF FILE EARLY ***')
	RETURN
	END
C
C
	SUBROUTINE CLIPS(IFLAG,XV1,YV1,XV2,YV2,X1,Y1,X2,Y2,XM,YM,XX,YX)
C
C	CLIPS THE LINE FROM X1,Y1 TO X2,Y2 TO THE RECTANCLE XM,YM XX,YX
C	CLIPPED LINE IS XV1,YV1 (CLIPPED X1,Y1) AND  XV2,YV2 (CLIPPED X2,Y2)
C
C	RETURNS IFLAG=-1 FOR ERROR, IFLAG<>0 FOR NOT VISIBLE, AND IFLAG=0
C	FOR AT LEAST PARTLY VISIBLE LINE
C
	XV1=X1
	YV1=Y1
	IV1=IPCLIP(XV1,YV1,XM,YM,XX,YX)
	XV2=X2
	YV2=Y2
	IV2=IPCLIP(XV2,YV2,XM,YM,XX,YX)
C
C	RETURN IF COMPLETELY VISIBLE OR INVISIBLE
C
	IFLAG=IOR(IV1,IV2)
	IF  (IFLAG.EQ.0) RETURN
	IFLAG=IAND(IV1,IV2)
	IF (IFLAG.NE.0) RETURN
C
C	OTHERWISE CLIP PARTIALLY VISIBLE LINE
C
	IC1=ICLIPS(IV1,XV1,YV1,X2,Y2,XM,YM,XX,YX)
	IC2=ICLIPS(IV2,XV2,YV2,X1,Y1,XM,YM,XX,YX)
	RETURN
	END
C
C
	INTEGER FUNCTION ICLIPS(IV,XV,YV,X2,Y2,XM,YM,XX,YX)
C
C	CLIPS LEFT SIDE LINE FROM XV,YV TO X2,V2 IN BOX XM,YM,XX,YX
C
C	CLIP LEFT EDGE
C
	IF (IAND(IV,1).NE.0) THEN
		YV=YV+(Y2-YV)*(XM-XV)/(X2-XV)
		XV=XM
		IV=IPCLIP(XV,YV,XM,YM,XX,YX)
	ENDIF
C
C	CLIP RIGHT EDGE
C
	IF (IAND(IV,2).NE.0) THEN
		YV=YV+(Y2-YV)*(XX-XV)/(X2-XV)
		XV=XX
		IV=IPCLIP(XV,YV,XM,YM,XX,YX)
	ENDIF
C
C	CLIP BOTTOM EDGE
C
	IF (IAND(IV,4).NE.0) THEN
		XV=XV+(X2-XV)*(YM-YV)/(Y2-YV)
		YV=YM
		IV=IPCLIP(XV,YV,XM,YM,XX,YX)
	ENDIF
C
C	CLIP TOP EDGE
C
	IF (IAND(IV,8).NE.0) THEN
		XV=XV+(X2-XV)*(YX-YV)/(Y2-YV)
		YV=YX
		IV=IPCLIP(XV,YV,XM,YM,XX,YX)
	ENDIF
	ICLIPS=IV
	RETURN
	END
C
C
	SUBROUTINE REGET(M1,M2,M3,MP,ILU,M)
C
C	READ DATA FROM LONGLIB PRINTER HISTORY META FILE
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
	SUBROUTINE PENOUT(M1,M2,M3,MP,ILU)
C
C	WRITE DATA TO TEMPORARY FILE
C	
	INTEGER*2 M(128)
	M(MP)=M1
	M(MP+1)=M2
	M(MP+2)=M3
	MP=MP+3
	IF (MP.GE.126.OR.M3.EQ.8) THEN
		WRITE (ILU,ERR=99) M
		MP=1
	ENDIF
	RETURN
99	WRITE(*,10)
10	FORMAT(' *** ERROR WRITING TEMPORARY FILE ***')
	CALL EXIT
	END
C
C
	INTEGER FUNCTION IPCLIP(X,Y,XM,YM,XX,YX)
C
C	FORTRAN-77 VERSION:   DGL JULY, 1987
C	CHECKS TO SEE IF POINT XY IS IN RECTANGLE (XM,YM)-(XX,YX)
C	OR ON THE BOUNDRY -- RETURNS ZERO OR A CODE INDICATING POSITION
C
	INTEGER CD
	CD=0
	IF (X.LT.XM) THEN
		CD=1
	ELSE
		IF (X.GT.XX) CD=2
	ENDIF
	IF (Y.LT.YM) THEN
		CD=CD+4
	ELSE
		IF (Y.GT.YX) CD=CD+8
	ENDIF
	IPCLIP=CD
	RETURN
	END
C
C
	SUBROUTINE SETPAR
C
C	SET OUTPUT DEVICE DEPENDENT PARAMETERS
C
	COMMON /RAST/XSWIDE,YSWIDE,XRES,YRES,XLIM,YLIM,
     $		IXOFF,IYOFF,MAXSTR
C
C	XSWIDE	LENGTH OF STRIP IN X DIRECTION (INCH) (XSWIDE<=XLIM)
C	YSWIDE	LENGTH OF STRIP IN X DIRECTION (INCH) (YSWIDE<=YLIM)
C	XRES	OUTPUT DEVICE RESOLUTION IN X DIRECTION (DOT/INCH)
C	YRES	OUTPUT DEVICE RESOLUTION IN Y DIRECTION (DOT/INCH)
C	XLIM	LIMIT OF MOTION IN X DIRECTION (INCH)
C	YLIM	LIMIT OF MOTION IN Y DIRECTION (INCH)
C	IXOFF	X OFFSET (DOTS)
C	IYOFF	Y OFFSET (DOTS)
C	MAXSTR	MAXIMUM NUMBER OF STRIPS BEFORE WARNING
C
C	INITIALIZE DEVICE COMMON BLOCK
C
	XSWIDE=10.85
	YSWIDE=8.35
	XLIM=11.0
	YLIM=8.5
	XRES=1020.4
	YRES=1020.4
	IXOFF=0
	IYOFF=0
	MAXSTR=6
C
	RETURN
	END
C
C
	SUBROUTINE MAKEP(LUT,LUO,ICOLS,NCOL)
C
C	READ PEN MOTION FILE AND CONVERT TO HPGL COMPATIBLE CODES
C
	INTEGER ICOLS(NCOL)
	INTEGER M(128)
C
C	LINE TYPE TRANSLATION ARRAY
C
	INTEGER ILT(7)
	DATA ILT/-1,1,4,2,3,6,5/,NTYPE/7/
	LOGICAL PENUP,PENCOL
C
C	MAKE A PASS THROUGH FILE FOR EACH COLOR
C
	IPCOL=1
C
500	CONTINUE
C
C	SET SOLID LINE TYPE WITH PEN UP
C
	WRITE(LUO,300) 
300	FORMAT(' PU;LT-1;')
C
	LWIDE=1
	LTYPE=0
	PENUP=.TRUE.
	PENCOL=.TRUE.
	ICCOL=ICOLS(IPCOL)
	LX=0
	LY=0
	MP=999
C
C	READ EACH COMMAND IN HISTORY FILE
C
10	CALL REGET(M1,M2,IC,MP,LUT,M)
C
C	DECODE COMMAND AND EXECUTE
C
	GOTO (10,20,30,40,50,60,10,80,80,55,10) IC
	GOTO 80
C
C	PEN DOWN MOVE
C
20	CONTINUE
C
C	DRAW PEN DOWN TO (M1,M2) IF COLOR IS CURRENT COLOR
C
	IF (LCOL.NE.ICCOL) GOTO 10
	IF (PENCOL) THEN
C
C	GET PEN OF DESIRED COLOR
C
		WRITE(LUO,320) ICCOL+1
320		FORMAT(' PU;SP',I2,';')
		PENCOL=.FALSE.
		PENUP=.TRUE.
	END IF
	IF (PENUP) WRITE(LUO,440)
	PENUP=.FALSE.
440	FORMAT(' PD;')
	WRITE (LUO,450) M1,M2
450	FORMAT(' PA',I6,',',I6,';')
C
	GOTO 10
C
C	PEN UP MOVE
C
30	CONTINUE
	IF (LCOL.NE.ICCOL) GOTO 10
	PENUP=.TRUE.
	WRITE(LUO,460) M1,M2
460	FORMAT(' PU;PA',I6,',',I6,';')
	GOTO 10
C
C	ERASE PEN MOVE	
C
40	CONTINUE
	GOTO 10
C
C	CHANGE PEN COLOR
C
50	CONTINUE
	LCOL=M2
	GOTO 10
C
C	CHANGE PEN WIDTH
C
55	CONTINUE
C
C	RESTRICT RANGE OF PERMISSIBLE LINE WIDTHS
C
	LWIDE=M1
	GOTO 10
C
C	CHANGE LINE TYPE AND SCALE
C
60	CONTINUE
	LTYPE=IABS(M1)+1
	IF (LTYPE.LT.1) LTYPE=1
	IF (LTYPE.GT.NTYPE) LTYPE=MOD(LTYPE,NTYPE)
	LTYPE=ILT(LTYPE)
	WRITE(LUO,3500) LTYPE
3500	FORMAT(' LT',I2,',1.2;')
	GOTO 10
C
C	END OF FILE REACHED
C
80	CONTINUE
C
C	DONE WITH ALL PASSES?
C
	IF (IPCOL.LT.NCOL) THEN
C
C	IF NOT, INCREMENT COLOR COUNTER, REWIND TEMP FILE AND PROCESS AGAIN
C
		IPCOL=IPCOL+1
		REWIND(LUT)
		GOTO 500
	ENDIF
C
C	FINISHED WITH THIS PAGE
C
	RETURN
	END
