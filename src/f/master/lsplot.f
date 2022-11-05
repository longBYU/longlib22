C
C *** LAST REVISED ON 20-JAN-1994 17:13:12.80
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.MASTER]LSPLOT.FOR
C
	SUBROUTINE LSPLOT(X,Y,NDP,NDL,IFLAG,F,C,NC)
C
C	ROUTINE FOR PLOTTING LINES
C
C	WRITTEN:  DGL SEPT. 1987
C
	DIMENSION X(NDP,NDL),Y(NDP,NDL),F(*),NC(*)
	CHARACTER*(*) C(*)
C
C	X	(R) X INPUT ARRAY DIMENSIONED X(NDP,NDL)
C		    NOTE: DEPENDING ON OPTIONS SELECTED, X
C		    ACTUALLY MAY BE DIMENSIONED X(NDP)
C	Y	(R) Y INPUT ARRAY DIMENSIONED Y(NDP,NDL)
C	NDP	(I) NUMBER OF POINTS PER LINE DIMENSION
C	NDL	(I) NUMBER OF LINES DIMENSION
C	IFLAG	(R) PLOTTING FLAG
C		    < 0 DON'T CLOSE PLOT PACKAGE
C		    = 0 CLOSE PLOT PACKAGE WITHOUT PLOTTING
C		    > 0 CLOSE PLOT PACKAGE
C		MAG > 10000 INIT PLOT PACKAGE
C	(HUNDRED'S) = SCREEN GRAPHICS DEVICE (SEE FRAME)
C	F	(R) OPTIONS ARRAY (DESCRIBED BELOW)
C	C	(R) TITLES ARRAY
C		     C(1) X AXIS TITLE
C		     C(2) Y AXIS TITLE
C		     C(3) CHART TITLE
C		     C(4) LEGEND TEXT FOR LINE 1 (IF LEGEND ENABLED)
C		     C(5) LEGEND TEXT FOR LINE 2 (IF LEGEND ENABLED)
C		     ...   ...
C	NC	(I) NUMBER OF CHARACTERS IN TITLE ARRAY
C		    NC(1) NUMBER OF CHARACTERS IN C(1)
C		    NC(2) NUMBER OF CHARACTERS IN C(2)
C		    ...    ...
C		    ETC.  NOTE: IF NC(I) IS ZERO C(I) IS NOT PLOTTED
C
C	THE ELEMENTS OF F ARE INTERPRETTED ACCORDING THE THE FOLLOWING:
C	DEFAULT VALUES ARE SHOWN IN SQUARE BRACKETS
C
C   INDEX OF F	VALUE    ACTION
C  ____________ _____   ___________________
C	1      0<.<=NDP NUMBER OF POINTS PLOTTED [NDP]
C 	2      0<.<=NDL NUMBER OF LINES PLOTTED [NL]
C	3	-1/0/1	X AUTO SCALING: 0=AUTO,SMOOTH; 1=AUTO,NOSMOOTH; -1=USER
C	4	XMIN    USER SUPPLIED SCALE VALUE (USED IF F(3)<0)
C	5	XMAX    USER SUPPLIED SCALE VALUE (USED IF F(3)<0)
C	6	-1/0/1	Y AUTO SCALING: 0=AUTO,SMOOTH; 1=AUTO,NOSMOOTH; -1=USER
C	7	YMIN    USER SUPPLIED SCALE VALUE (USED IF F(6)<0)
C	8	YMAX    USER SUPPLIED SCALE VALUE (USED IF F(6)<0)
C	9	0/1	USE X VALUES WITH Y VALUES: 0=ONLY FIRST LINE OF
C			X DATA USED FOR ALL Y LINES; 1=LINES OF X/Y USED
C	10	0/1	CONNECT PLOTTED POINTS: 0=YES; 1=NO
C	11	>=0	SYMBOL PLOTTED EVERY ()TH POINT: 0=NO SYMBOLS
C	12	>=0	SYMBOL SIZE [0.1]: 0=USE DEFAULT
C	13	>=0	SYMBOL NUMBER FOR FIRST DATA LINE
C	14     -8<.<8	SHOW ERROR BARS: 0=NO ERROR BARS
C			WHEN NON-ZERO, CHANGES INTERPRETATION OF LINES
C			POINTS EVERY THIRD LINE ARE PLOTTED.  RELATIVE
C			ERROR (UPPER,LOWER) ARE THE FOLLOWING TWO LINES.
C			PLOTTED RELATIVE ERROR COMPUTED AS SUM OF FIRST
C			LINE PLUS SECOND/THIRD.
C		  <0    AN X IS MADE AT THE CENTER POINT
C
C		ABS(.)  TYPE OF ERROR BAR
C		------  ---------------------------------------------------
C		  1	LINE CONNECTING 2ND/3RD RELATIVE ERRORS
C		  2	1+HORIZONTAL BARS OF WIDTH EBAR AT 2ND/3RD REL ERR
C		  3	1+VERTICAL BARS OF WIDTH EBAR AT 2ND/3RD REL ERR
C		  4	2 LINES SPACED EBAR/2+HORIZONTAL BARS WIDTH=EBAR
C		  5	2 LINES SPACED EBAR/2+VERTICAL BARS WIDTH=EBAR
C		  6	VERTICAL RECTANGLE FROM 2ND/3RD WITH WIDTH=EBAR
C		  7     RECTANGLE WITH CORNER AT 2ND/3RD REL ERROR
C
C	16	>=0	ERROR BAR SIZE [0.1]: 0=DEFAULT USED
C	17	0/1	VERTICAL DRAWN LINE FROM POINT TO REFERENCE VALUE:
C			0=NO; 1=YES
C	18		REFERENCE VALUE
C	19	-1/0/1	X AXIS TYPE: 0=LINEAR; 1=LOG AXIS, -1=NO AXIS
C	20	-1/0/1	Y AXIS TYPE: 0=LINEAR; 1=LOG AXIS, -1=NO AXIS
C	21	>=0	X AXIS LENGTH [7.0]: 0=DEFAULT USED
C	22	>=0	Y AXIS LENGTH [5.0]: 0=DEFAULT USED
C	23	>=0	X AXIS TICK PATTERN (SEE AXIS3) [7.00]: 0=DEFAULT
C	24	>=0	Y AXIS TICK PATTERN (SEE AXIS3) [5.00]: 0=DEFAULT
C	25	0/1	X AXIS TITLE SIDE OF AXIS: 0=BELOW; 1=ABOVE
C	26	0/1	Y AXIS TITLE SIDE OF AXIS: 0=LEFT; 1=RIGHT
C	27	0/1	X AXIS AUTO EXPONENT ENABLE: 0=ENABLE; 1=DISABLE
C	28	0/1	Y AXIS AUTO EXPONENT ENABLE: 0=ENABLE; 1=DISABLE
C	29	0/1	X AXIS TICK SIDE: 0=BELOW; 1=ABOVE
C	30	0/1	Y AXIS TICK SIDE: 0=LEFT; 1=RIGHT
C	31	0/1	X AXIS NUMBERS ORIENTATION: 0=HORIZONTAL; 1=VERTICAL
C	32	0/1	Y AXIS NUMBERS ORIENTATION: 0=VERTICAL; 0=HORIZONTAL
C	33	0/1	X AXIS NUMBERS/TITLE SHWON: 0=SHOWN; 1=NOT SHOWN
C	34	0/1	Y AXIS NUMBERS/TITLE SHWON: 0=SHOWN; 1=NOT SHOWN
C	35	0/1	TAKE LOG10(ABS(X VALUES)+1.E-34): 0=NO; 1=YES
C	36	0/1	TAKE LOG10(ABS(Y VALUES)+1.E-34): 0=NO; 1=YES
C	37	-1/0/1	ADD MIRROR X AXIS: 0=NO; 1=WITH LABELS; -1:W/O LABELS
C	38	-1/0/1	ADD MIRROR Y AXIS: 0=NO; 1=WITH LABELS; -1:W/O LABELS
C	39	>=0	X AXIS LABEL SIZE [0.15]: 0=USE DEFAULT
C	40	>=0	Y AXIS LABEL SIZE [0.15]: 0=USE DEFAULT
C	41	>=0	TOP TITLE CHARACTER SIZE [0.18]: 0=USE DEFAULT
C	42	0/1/2/3	GRID OPTION: 0=NO GRID; 1=SOLID; 2=DOTTED; 3=TICKED
C	43	-1/0/1	LINE/SYMBOL LEGEND: 0=NO LEGEND; 1=AUTO PLACE; -1=USER
C	44	X	USER SPECIFIED LOWER-LEFT CORNER OF LEGEND
C	45	Y	USER SPECIFIED LOWER-LEFT CORNER OF LEGEND
C	46	0/1	SHOW PLOT SYMBOL WITH LEGEND: 0=NO; 1=YES
C	47	0/1	SHOW LINE SEGMENT ON LEGEND: 0=NO; 1=YES
C	48	>=0	LEGEND CHARACTER HEIGHT [0.12]: 0=USE DEFAULT
C	49	>=0	LEGEND SEGMENT LENGTH [0.5]: 0=USE DEFAULT
C	50	-1/0/1	TOP TITLE JUSTIFY: 0=CENTER; -1:LEFT; 1:RIGHT
C	51	0/1	PLOT HORIZONTAL REFERENCE LINE: 0=NO; 1=YES
C	52	0/1	USE LINE TYPE ARRAY VALUES: 0=NO; 1=YES
C	53	0/1	USE COLOR ARRAY VALUES: 0=NO; 1=YES
C	54	>=0	COLOR INDEX 1: 0=COLOR 1 USED
C	55	>=0	LINETYPE INDEX 1
C	56	>=0	COLOR INDEX 2: 0=COLOR 1 USED
C	57	>=0	LINETYPE INDEX 2
C	...		... ETC ...
C
C	INDEX		COLOR USAGE	LINETYPE USAGE
C	-------		------------    --------------
C	  1	        X AXIS		X AXIS
C	  2	      X AXIS NUMBERS	Y AXIS
C	  3	      X AXIS TITLE	TITLE
C	  4	      X AXIS EXPONENT	LEGEND TITLES
C	  5		Y AXIS		ZERO REF LINETYPE
C	  6	      Y AXIS NUMBERS	ERROR BAR LINETYPES
C	  7	      Y AXIS TITLE	LINE 1 LINETYPE
C	  8	      Y AXIS EXPONENT     ETC.
C	  9	        TITLE		  ...
C	 10		LEGEND TITLES	  ...
C	 11		ZERO REF LINE	  ...
C	 12		GRID COLOR	  ...
C	 13		LINE 1 COLOR	  ...
C	...		... ETC. ...      ...
C
	DIMENSION IC(4),SMO(2)
	LOGICAL REPEAT
	SAVE REPEAT
	DATA REPEAT/.FALSE./
C
C	INTIALIZE ROUTINE AND PLOT PACKAGE IF REQUIRED
C
	IF (IFLAG.EQ.0) THEN
		IF (REPEAT) CALL PLOTND		!CLOSE PLOTTER
		REPEAT=.FALSE.
		RETURN
	ENDIF
C
C	INTIALIZE PLOT PACKAGE
C
	JF=IABS(IFLAG)
	IF (.NOT.REPEAT.AND.JF.LT.10000) THEN
		JF=JF/100			!GRAPHICS DEVICE CODE
		CALL FRAME(3,JF,1.5,1.0,1.)	!INTIALIZE
	ELSE
		CALL CTERM(-1)			!PUT TERMINAL IN PLOT MODE
	ENDIF
C
C	ESTABLISH DEFAULTS
C
	NP=NDP				! NUMBER OF POINTS/LINE
	NL=NDL				! NUMBER OF LINES
	XM=X(1,1)			! MIN X VALUE
	XX=XM				! MAX X VALUE
	YM=Y(1,1)			! MIN Y VALUE
	YX=YM				! MAX Y VALUE
	FX=5.01				! X AXIS NUMBER FORMAT
	FY=5.01				! Y AXIS NUMBER FORMAT
	XLEN=7.0			! X AXIS LENGTH
	YLEN=5.0			! Y AXIS LENGTH
	XTICK=7.0			! X AXIS TICK PATTERN
	YTICK=6.0			! Y AXIS TICK PATTERN
	XCS=0.15			! X AXIS TITLE SIZE
	YCS=0.15			! Y AXIS TITLE SIZE
	TCS=0.18			! OVERALL TITLE SIZE
	EBAR=0.1			! ERROR BAR SIZE
	SYMSIZ=0.1			! SYMBOL SIZE
	CSLEG=0.12			! LEGEND CHARACTER SIZE
	GLEN=0.5			! LEGEND LINE LENGTH
	XLEG=XLEN+0.3			! DEFAULT LEGEND LOCATION
	YLEG=0.5
C
C	READ OPTIONS ARRAY 
C
	IF (F(1).GT.0.0) NP=int(F(1))	! NUMBER OF POINT/LINE
	IF (NP.GT.NDP) NP=NDP
	IF (F(2).GT.0.0) NL=int(F(2))	! NUMBER OF LINES
	IF (NL.GT.NDL) NL=NDL
	JXAUTO=int(F(3))		! AUTO SCALE X, 0=YES/SMOOTH,-1=NO/USER
C					  1=YES/NO SMOOTH
	IF (JXAUTO.LT.0.0) THEN		! INPUT X AXIS SCALE FACTORS
		XM=F(4)			! MIN X (OTHERWISE RETURNED)
		XX=F(5)			! MAX X
	ENDIF
	JYAUTO=int(F(6))		! AUTO SCALE Y, 0=YES/SMOOTH,-1=NO/USER
C					  1=YES/NO SMOOTH
	IF (JYAUTO.LT.0.0) THEN		! INPUT Y AXIS SCALE FACTORS
		YM=F(7)			! MIN Y (OTHERWISE RETURNED)
		YX=F(8)			! MAX Y
	ENDIF
	JXUSE=int(ABS(F(9)))		! USE X LINES WITH Y LINES,0=NO,1=YES
	JCONN=int(ABS(F(10)))		! CONNECT POINTS WITH LINES,0=YES,1=NO
	JSYM=int(ABS(F(11)))		! PLOT SYMBOL EVERY JSYM PT,0=NO SYMS
	IF (F(12).GT.0.0) SYMSIZ=F(12)	! SYMBOL SIZE
	JSYMST=int(ABS(F(13)))		! STARTING PLOT SYMBOL NUMBER
	JEBAR=int(F(14))		! TYPE OF ERROR BAR,0=NOT USED
C
C		|JEBAR|  ERROR BAR (CLINE IS LINE CONNECT 2ND/3RD REL. ERR)
C		-------  ---------------------------------------------------
C		  1	  CLINE
C		  2	  CLINE+HORIZONTAL BARS WIDTH=EBAR
C		  3	  CLINE+VERTICAL BARS WIDTH=EBAR
C		  4	  DOUBLE CLINE+HORIZONTAL BARS WIDTH=EBAR
C		  5	  DOUBLE CLINE+VERTICAL BARS WIDTH=EBAR
C		  6	  VERTICAL RECTANGLE WIDTH=EBAR
C		  7       RECTANGLE DEFINED BY 2ND/3RD REL ERROR
C
C		NOTE: IF JBAR < 0 AN X (SIZE EBAR) IS USED TO MARK 1ST LINE
C
	KEBAR=IABS(JEBAR)
	NBAR=1
	IF (JEBAR.NE.0) NBAR=3
	IF (F(16).GT.0.0) EBAR=F(16)	! ERROR BAR SIZE
C					  1ST LINE DEFINES CENTER
C					  2ND IS LOWER REL. ERROR
C					  3RD IS UPPER REL. ERROR
	JVLINE=int(F(17))		! VERTICAL LINE TO ZVAL,0=NO,1=YES
	ZVAL=int(F(18))			! ZERO REFERENCE VALUE
	JXLGAX=int(F(19))		! X AXIS, LINEAR=0/LOG=1/NONE=-1
	JYLGAX=int(F(20))		! Y AXIS, LINEAR=0/LOG=1/NONE=-1
	IF (F(21).GT.0.0) XLEN=F(21)	! X AXIS LENGTH
	IF (F(22).GT.0.0) YLEN=F(22)	! Y AXIS LENGTH
	IF (F(23).GT.0.0) XTICK=F(23)	! X AXIS TICK PATTERN
	IF (F(24).GT.0.0) YTICK=F(24)	! Y AXIS TICK PATTERN
	JXTITLE=int(ABS(F(25)))		! X AXIS TITLE SIDE,0=CW,1=CCW
	IF (JXTITLE.EQ.0) THEN
		JXTITLE=-1
	ELSE
		JXTITLE=1
	ENDIF
	JYTITLE=int(ABS(F(26)))		! Y AXIS TITLE SIDE,0=CCW,1=CW
	IF (JYTITLE.EQ.0) THEN
		JYTITLE=1
	ELSE
		JYTITLE=-1
	ENDIF
	JXEXPSC=int(ABS(F(27)))		! X AXIS ENABLE AUTO EXPONENT,0=YES,1=NO
	JYEXPSC=int(ABS(F(28)))		! Y AXIS ENABLE AUTO EXPONENT,0=YES,1=NO
	JXTICKS=int(ABS(F(29)))		! X AXIS TICKS TITLE SIDE,0=YES,1=NO
	JYTICKS=int(ABS(F(30)))		! Y AXIS TICKS TITLE SIDE,0=YES,1=NO
	JXNUMS=int(ABS(F(31)))		! X AXIS NUMS PARA AXIS, 0=YES,1=NO
	JYNUMS=int(ABS(F(32)))		! Y AXIS NUMS PARA AXIS, 0=YES,1=NO
	JXNUM=int(ABS(F(33)))		! X AXIS NUMS SHOWN, 0=YES,1=NO
	JYNUM=int(ABS(F(34)))		! Y AXIS NUMS SHOWN, 0=YES,1=NO
	JXLOG=int(ABS(F(35)))		! TAKE LOG OF X VALUES, 0=NO,1=YES
	JYLOG=int(ABS(F(36)))		! TAKE LOG OF Y VALUES, 0=NO,1=YES
	JXRAX=int(F(37)	)	! ADD AXIS OPPOSITE, 0=YES,-1=W/L,1=NO LABELS
	JYRAX=int(F(38)	)	! ADD AXIS OPPOSITE, 0=YES,-1=W/L,1=NO LABELS
	IF (F(39).GT.0.0) XCS=F(39)	! X AXIS TITLE SIZE
	IF (F(40).GT.0.0) YCS=F(40)	! Y AXIS TITLE SIZE
	IF (F(41).GT.0.0) TCS=F(41)	! OVERALL TITLE SIZE
	JGRID=int(F(42))		! GRID OPTION, 0=NONE,1=SOLID,2=DOTTED
	JLEGND=int(F(43))		! ADD LEGEND, 0=NONE,1=AUTO,-1=USER
	XLEG=XLEN+0.3			! DEFAULT LEGEND LOCATION
	YLEG=0.5
	IF (JLEGND.LT.0) XLEG=F(44)	! X LEGEND LOCATION
	IF (JLEGND.LT.0) YLEG=F(45)	! Y LEGEND LOCATION
	JLEGSY=int(F(46))		! USE SYMBOL ON LEGEND,0=NO,1=YES
	JLEGLI=int(F(47))		! USE LINETYPE ON LEGEND,0=NO,1=YES
	IF (F(48).GT.0.0) CSLEG=F(48)	! LEGEND CHARACTER SIZE
	IF (F(49).GT.0.0) GLEN=F(49)	! LEGEND LINE LENGTH
	JTCNTR=int(F(50))		! CENTER TITLE,0=YES,-1=LEFT,1=RIGHT
	JSZREF=int(F(51))		! SHOW ZERO REFERENCE,0=NO,1=YES
C
	JLINE=int(F(52))		! USE LINE TYPES,0=NO,1=YES
	JCOL=int(F(53))			! USE COLORS,0=NO,1=YES
C
C	F(54)=FIRST COLOR
C	F(55)=FIRST LINETYPE
C	F(56)=SECOND COLOR
C	F(57)=SECOND LINETYPE
C	...
C
	ICOFF=54
	ILOFF=55
C
C	COMPUTE SCALING
C
	IF (JXAUTO.GE.0) THEN		! AUTO SCALE X
		X1=ABS(XM)
		X2=X1
		DO 5 I=1,NP
			K=1
			IF (JXUSE.NE.0) K=NL
			DO 5 J=1,K,NBAR
				XM=MIN(XM,X(I,J))
				X1=MIN(X1,ABS(X(I,J)))
				XX=MAX(XX,X(I,J))
				X2=MAX(XX,ABS(X(I,J)))
				IF (JEBAR.NE.0.AND.JXUSE.NE.0) THEN
				    XM=MIN(XM,X(I,J)+X(I+1,J))
				    X1=MIN(X1,ABS(X(I,J)+X(I+1,J)))
				    XX=MAX(XX,X(I,J)+X(I+1,J))
				    X2=MAX(X2,ABS(X(I,J)+X(I+1,J)))
				    XM=MIN(XM,X(I,J)+X(I+2,J))
				    X1=MIN(X1,ABS(X(I,J)+X(I+1,J)))
				    XX=MAX(XX,X(I,J)+X(I+2,J))
				    X2=MAX(X2,ABS(X(I,J)+X(I+1,J)))
				ENDIF
 5		CONTINUE
		IF (JXLOG.NE.0) THEN
			XM=ALOG10(X1+1.E-34)
			XX=ALOG10(X2+1.E-34)
		ENDIF
		IF (JXAUTO.GT.0.AND.JXLGAX.EQ.0) THEN	! SMOOTH SCALING
			SMO(1)=XM
			SMO(2)=XX
			CALL SCALE(SMO,XLEN,2,1,1,XM,DX)
			XX=XM+XLEN*DX
		ENDIF
		IF (JXLGAX.NE.0) THEN			! LOG AXIS SCALING
			IF (XM.LE.0.AND.XM.NE.INT(XM)) XM=XM-1.0
			XM=INT(XM)
			IF (XX.GT.0.AND.XX.NE.INT(XX)) XX=XX+1.0
			XX=INT(XX)
		ENDIF
		IF (XX.EQ.XM) XX=XM+1.0
C	RETURN SCALE FACTORS USED
		F(4)=XM
		F(5)=XX
	ENDIF
	IF (JYAUTO.GE.0) THEN		! AUTO SCALE Y
		Y1=ABS(YM)
		Y2=Y1
		DO 6 I=1,NP
			DO 6 J=1,NL,NBAR
				YM=MIN(YM,Y(I,J))
				Y1=MIN(Y1,ABS(Y(I,J)))
				YX=MAX(YX,Y(I,J))
				Y2=MAX(YX,ABS(Y(I,J)))
				IF (JEBAR.NE.0) THEN
				    YM=MIN(YM,Y(I,J)+Y(I+1,J))
				    Y1=MIN(Y1,ABS(Y(I,J)+Y(I+1,J)))
				    YX=MAX(YX,Y(I,J)+Y(I+1,J))
				    Y2=MAX(Y2,ABS(Y(I,J)+Y(I+1,J)))
				    YM=MIN(YM,Y(I,J)+Y(I+2,J))
				    Y1=MIN(Y1,ABS(Y(I,J)+Y(I+1,J)))
				    YX=MAX(YX,Y(I,J)+Y(I+2,J))
				    Y2=MAX(Y2,ABS(Y(I,J)+Y(I+1,J)))
				ENDIF
 6		CONTINUE
		IF (JYLOG.NE.0) THEN
			YM=ALOG10(Y1+1.E-34)
			YX=ALOG10(Y2+1.E-34)
		ENDIF
		IF (JYAUTO.GT.0.AND.JYLGAX.EQ.0) THEN	! SMOOTH SCALING
			SMO(1)=YM
			SMO(2)=YX
			CALL SCALE(SMO,YLEN,2,1,1,YM,DY)
			YX=YM+YLEN*DY
		ENDIF
		IF (JYLGAX.NE.0) THEN			! LOG AXIS SCALING
			IF (YM.LE.0.AND.YM.NE.INT(YM)) YM=YM-1.0
			YM=INT(YM)
			IF (YX.GT.0.AND.YX.NE.INT(YX)) YX=YX+1.0
			YX=INT(YX)
		ENDIF
		IF (YX.EQ.YM) YX=YM+1.0
C	RETURN SCALE FACTORS USED
		F(7)=YM
		F(8)=YX
	ENDIF
	DX=(XX-XM)/XLEN
	DY=(YX-YM)/YLEN
C
C	PRODUCE PLOT X AXIS
C
	IF (JCOL.NE.0) THEN		! INITIALIZE COLOR AXIS ARRAY
		DO 10 I=1,4
			IC(I)=int(ABS(F(2*I+ICOFF-2)))
			IF (IC(I).EQ.0) IC(I)=1
10		CONTINUE
	ENDIF
	IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF)))
C
	IF (JXEXPSC.NE.0) XCS=-XCS
	IF (JXLGAX.EQ.0) THEN		! LINEAR X AXIS
		X1=XLEN
		IF (JXTICKS.NE.0) X1=-XLEN
		NA=1000
		IF (JXNUM.NE.0) NA=NA+100
		IF (JCOL.NE.0) NA=NA+100000
		IF (JXNUMS.EQ.0) NA=NA-1000
		IF (NC(1).GT.0) THEN	! USE INPUT X AXIS TITLE
			NA=(NA+NC(1))*JXTITLE
			CALL AXIS3(0.,0.,C(1),NA,X1,
     $				0.0,XM,XX,XTICK,XCS,FX,IC)
		ELSE			! NO X AXIS TITLE
			NA=(NA+1)*JXTITLE
			CALL AXIS3(0.,0.,' ',NA,X1,
     $				0.0,XM,XX,XTICK,XCS,FX,IC)
		ENDIF
		IF (JXRAX.NE.0) THEN
		    NA=1000
		    IF (JXRAX.GT.0) NA=NA+100
		    IF (JCOL.NE.0) NA=NA+100000
		    IF (JXNUMS.EQ.0) NA=NA-1000
		    IF (NC(1).GT.0) THEN! USE INPUT X AXIS TITLE
			NA=-(NA+NC(1))*JXTITLE
			CALL AXIS3(0.,YLEN,C(1),NA,X1,
     $				0.0,XM,XX,XTICK,XCS,FX,IC)
		ELSE			! NO X AXIS TITLE
			NA=(NA+1)*JXTITLE
			CALL AXIS3(0.,YLEN,' ',NA,X1,
     $				0.0,XM,XX,XTICK,XCS,FX,IC)
		    ENDIF
		ENDIF
	ELSE IF (JXLGAX.EQ.1) THEN	! LOG X AXIS
		X1=XLEN
		IF (JXTICKS.NE.0) X1=-XLEN
		NA=1000
		IF (JXNUM.NE.0) NA=NA+100
		IF (JCOL.NE.0) NA=NA+10000
		IF (JXNUMS.EQ.0) NA=NA-1000
		IF (NC(1).GT.0) THEN	! USE INPUT X AXIS TITLE
			NA=(NA+NC(1))*JXTITLE
			CALL LGAXS(0.,0.,C(1),NA,X1,
     $				0.0,XM,DX,IC)
		ELSE			! NO X AXIS TITLE
			NA=(NA+1)*JXTITLE
			CALL LGAXS(0.,0.,' ',NA,X1,
     $				0.0,XM,DX,IC)
		ENDIF
		IF (JXRAX.NE.0) THEN
		    NA=1000
		    IF (JXRAX.GT.0) NA=NA+100
		    IF (JCOL.NE.0) NA=NA+10000
		    IF (JXNUMS.EQ.0) NA=NA-1000
		    IF (NC(1).GT.0) THEN! USE INPUT X AXIS TITLE
			NA=-(NA+NC(1))*JXTITLE
			CALL LGAXS(0.,YLEN,C(1),NA,X1,
     $				0.0,XM,DX,IC)
		    ELSE		! NO X AXIS TITLE
			NA=-(NA+1)*JXTITLE
			CALL LGAXS(0.,YLEN,' ',NA,X1,
     $				0.0,XM,DX,IC)
		    ENDIF
		ENDIF
	ENDIF
C
C	PRODUCE PLOT Y AXIS
C
	IF (JCOL.NE.0) THEN		! INITIALIZE COLOR AXIS ARRAY
		DO 20 I=1,4
			IC(I)=int(ABS(F(2*I+ICOFF+6)))
			IF (IC(I).EQ.0) IC(I)=1
20		CONTINUE
	ENDIF
	IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF+2)))
C
	IF (JYEXPSC.NE.0) YCS=-YCS
	IF (JYLGAX.EQ.0) THEN		! LINEAR Y AXIS
		X1=YLEN
		IF (JYTICKS.NE.0) X1=-YLEN
		NA=1000
		IF (JYNUM.NE.0) NA=NA+100
		IF (JCOL.NE.0) NA=NA+100000
		IF (JYNUMS.EQ.0) NA=NA-1000
		IF (NC(2).GT.0) THEN	! USE INPUT Y AXIS TITLE
			NA=(NA+NC(2))*JYTITLE
			CALL AXIS3(0.,0.,C(2),NA,X1,
     $				90.0,YM,YX,YTICK,YCS,FY,IC)
		ELSE			! NO Y AXIS TITLE
			NA=(NA+1)*JYTITLE
			CALL AXIS3(0.,0.,' ',NA,X1,
     $				90.0,YM,YX,YTICK,YCS,FY,IC)
		ENDIF
		IF (JYRAX.NE.0) THEN
		    NA=1000
		    IF (JYRAX.GT.0) NA=NA+100
		    IF (JCOL.NE.0) NA=NA+100000
		    IF (JYNUMS.EQ.0) NA=NA-1000
		    IF (NC(2).GT.0) THEN! USE INPUT Y AXIS TITLE
			NA=-(NA+NC(2))*JYTITLE
			CALL AXIS3(XLEN,0.,C(2),NA,X1,
     $				90.0,YM,YX,YTICK,YCS,FY,IC)
		ELSE			! NO Y AXIS TITLE
			NA=(NA+1)*JYTITLE
			CALL AXIS3(XLEN,0.,' ',NA,X1,
     $				90.0,YM,YX,YTICK,YCS,FY,IC)
		    ENDIF
		ENDIF
	ELSE IF (JYLGAX.EQ.1) THEN	! LOG Y AXIS
		X1=YLEN
		IF (JYTICKS.NE.0) X1=-YLEN
		NA=1000
		IF (JYNUM.NE.0) NA=NA+100
		IF (JCOL.NE.0) NA=NA+10000
		IF (JYNUMS.EQ.0) NA=NA-1000
		IF (NC(2).GT.0) THEN	! USE INPUT Y AXIS TITLE
			NA=(NA+NC(2))*JYTITLE
			CALL LGAXS(0.,0.,C(2),NA,X1,
     $				90.0,XY,DY,IC)
		ELSE			! NO X AXIS TITLE
			NA=(NA+1)*JYTITLE
			CALL LGAXS(0.,0.,' ',NA,X1,
     $				90.0,YM,DY,IC)
		ENDIF
		IF (JYRAX.NE.0) THEN
		    NA=1000
		    IF (JYRAX.GT.0) NA=NA+100
		    IF (JCOL.NE.0) NA=NA+10000
		    IF (JYNUMS.EQ.0) NA=NA-1000
		    IF (NC(2).GT.0) THEN! USE INPUT Y AXIS TITLE
			NA=-(NA+NC(2))*JYTITLE
			CALL LGAXS(XLEN,0.,C(2),NA,X1,
     $				90.0,YM,DY,IC)
		    ELSE		! NO Y AXIS TITLE
			NA=-(NA+1)*JYTITLE
			CALL LGAXS(XLEN,0.,' ',NA,X1,
     $				90.0,YM,DY,IC)
		    ENDIF
		ENDIF
	ENDIF
C
C	PLOT GRID
C
	IF (JGRID.NE.0) THEN
		IF (JCOL.NE.0) THEN
		    ICC=INT(ABS(F(ICOFF+22)))
		    IF (ICC.LT.1) ICC=1
		    CALL PLOT(FLOAT(ICC),0.,0)
		ENDIF
		NG=JGRID-1
		I=INT(XTICK)-1
		IF (I.LT.1) I=1
		X1=XLEN/FLOAT(I)
		IF (JXLGAX.GT.0) THEN
			I=1-INT(XLEN*DX-XM+0.001)
			X1=-XLEN/FLOAT(I)
		ENDIF
		J=INT(YTICK)-1
		IF (J.LT.1) J=1
		Y1=YLEN/FLOAT(J)
		IF (JYLGAX.GT.0) THEN
			J=1-INT(YLEN*DY-YM+0.001)
			Y1=-YLEN/FLOAT(J)
		ENDIF
		CALL LGRID(0.,0.,X1,Y1,I,J,NG)
	ENDIF
C
C	ADD TITLE
C
	IF (NC(3).GT.0) THEN
		IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF+4)))
		IF (JCOL.NE.0) THEN
			ICC=INT(ABS(F(ICOFF+16)))
			IF (ICC.LT.1) ICC=1
			CALL PLOT(FLOAT(ICC),0.,0)
		ENDIF
		ICC=0
		X1=0.5*XLEN
		Y1=YLEN+0.1+TCS*0.2
		IF (JTCNTR.LT.0) THEN
			ICC=-1
			X1=0.0
			Y1=Y1-TCS*0.2
		ENDIF
		IF (JTCNTR.GT.0) THEN
			ICC=1
			X1=XLEN
			Y1=Y1-TCS*0.2
		ENDIF
		IF (JXRAX.LT.0) Y1=Y1+2.5*XCS
		CALL SYMBOL(X1,Y1,TCS,C(3),
     $			0.0,NC(3),ICC)
	ENDIF
C
C	PLOT DATA IN DESIRED FORM
C
	zref=0.0
	DX=1.0
	DY=1.0
	IF (XX-XM.NE.0.0) DX=XLEN/(XX-XM)
	IF (YX-YM.NE.0.0) DY=YLEN/(YX-YM)
	ZREF=(ZREF-YM)*DY
	IF (JSZREF.NE.0) THEN	! SHOW ZERO REFERENCE LINE
		IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF+8)))
		IF (JCOL.NE.0) THEN
			ICC=INT(ABS(F(ICOFF+20)))
			IF (ICC.LT.1) ICC=1
			CALL PLOT(FLOAT(ICC),0.,0)
		ENDIF
		CALL PLOT(0.0,ZREF,3)
		CALL PLOT(XLEN,ZREF,2)
	ENDIF
C
	DO 100 I=1,NL,NBAR
		IF (JLINE.NE.0) CALL NEWPEN(INT(F(2*(I-1)+ILOFF+12)))
		IF (JCOL.NE.0) THEN
			ICC=INT(ABS(F(ICOFF+24+2*(I-1))))
			IF (ICC.LT.1) ICC=1
			CALL PLOT(FLOAT(ICC),0.,0)
		ENDIF
		KSYM=MOD(I+JSYMST-1,17)
C
C	IF WE NEED CONNECTING LINES MAKE A CONNECT PASS
C
		IPEN=3
		IF (JCONN.EQ.0) THEN
		    DO 50 J=1,NP
			IF (JXUSE.NE.0) THEN
				X1=X(J,I)
			ELSE
				X1=X(J,1)
			ENDIF
			IF (JXLOG.NE.0) X1=ALOG10(ABS(X1)+1.E-34)
			X1=(X1-XM)*DX
			Y1=Y(J,I)
			IF (JYLOG.NE.0) Y1=ALOG10(ABS(Y1)+1.E-34)
			Y1=(Y1-YM)*DY
			CALL PLOT(X1,Y1,IPEN)
			IPEN=2
 50		    CONTINUE
		ENDIF
C
C	ANOTHER PASS FOR SYMBOLS, ETC.
C
		IF (JCONN.NE.0.AND.JEBAR.EQ.0.AND.JVLINE.EQ.0
     $			.AND.JSYM.EQ.0) GOTO 100
		ISYM=0
		DO 60 J=1,NP
			IF (JXUSE.NE.0) THEN
				X1=X(J,I)
			ELSE
				X1=X(J,1)
			ENDIF
			IF (JXLOG.NE.0) X1=ALOG10(ABS(X1)+1.E-34)
			X1=(X1-XM)*DX
			Y1=Y(J,I)
			IF (JYLOG.NE.0) Y1=ALOG10(ABS(Y1)+1.E-34)
			Y1=(Y1-YM)*DY
			IF (JSYM.NE.0) THEN		! SYMBOLS
			  IF (MOD(ISYM,JSYM).EQ.0) CALL
     $			     SYMBOL(X1,Y1,SYMSIZ,CHAR(KSYM),0.,-1,-1)
			ENDIF
			IF (JVLINE.NE.0) THEN		! VERTICAL LINE
				CALL PLOT(X1,Y1,3)
				CALL PLOT(X1,ZREF,2)
			ENDIF
			IF (JEBAR.NE.0) THEN		! ERROR BAR
			    IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF+10)))
			    IF (JXUSE.NE.0) THEN
				X2=X(J,I+1)+X(J,I)
				X3=X(J,I+2)+X(J,I)
			        IF (JXLOG.NE.0) THEN
				    X2=ALOG10(ABS(X2)+1.E-34)
				    X3=ALOG10(ABS(X3)+1.E-34)
				ENDIF
				X2=(X2-XM)*DX
				X3=(X3-XM)*DX
			    ELSE
				X2=X1
				X3=X1
			    ENDIF
			    Y2=Y(J,I+1)+Y(J,I)
			    Y3=Y(J,I+2)+Y(J,I)
			    IF (JYLOG.NE.0) THEN
				Y2=ALOG10(ABS(Y2)+1.E-34)
				Y3=ALOG10(ABS(Y3)+1.E-34)
			    ENDIF
			    Y2=(Y2-YM)*DY
			    Y3=(Y3-YM)*DY
			    IF (KEBAR.EQ.2.OR.KEBAR.EQ.5) THEN	! ERROR BAR TOP
				CALL PLOT(X2,Y2-EBAR,3)
				CALL PLOT(X2,Y2+EBAR,2)
			    ELSE IF (KEBAR.EQ.3.OR.KEBAR.EQ.4) THEN
				CALL PLOT(X2-EBAR,Y2,3)
				CALL PLOT(X2+EBAR,Y2,2)
			    ENDIF
			    IF (KEBAR.LT.4) THEN	! CONNECT LINE
				CALL PLOT(X2,Y2,3)
				CALL PLOT(X3,Y3,2)
			    ELSE IF (KEBAR.EQ.4) THEN	! DOUBLE CONN V LINE
				CALL PLOT(X2-EBAR*0.5,Y2,3)
				CALL PLOT(X3-EBAR*0.5,Y3,2)
				CALL PLOT(X3+EBAR*0.5,Y3,3)
				CALL PLOT(X2+EBAR*0.5,Y2,2)
			    ELSE IF (KEBAR.EQ.5) THEN	! DOUBLE CONN HLINE
				CALL PLOT(X2,Y2-EBAR*0.5,3)
				CALL PLOT(X3,Y3-EBAR*0.5,2)
				CALL PLOT(X3,Y3+EBAR*0.5,3)
				CALL PLOT(X2,Y2+EBAR*0.5,2)
			    ELSE IF (KEBAR.EQ.6) THEN	! VERTICAL RECT
				CALL RECT(X1-EBAR,Y2,X1+EBAR,Y3)
			    ELSE IF (KEBAR.EQ.7) THEN	! RECT
				CALL RECT(X2,Y2,X3,Y3)
			    ENDIF
			    IF (JEBAR.LT.0) THEN	! X MARK
				CALL PLOT(X1-EBAR,Y1-EBAR,3)
				CALL PLOT(X1+EBAR,Y1+EBAR,2)
				CALL PLOT(X1-EBAR,Y1+EBAR,3)
				CALL PLOT(X1+EBAR,Y1-EBAR,2)
			    ENDIF
			    IF (KEBAR.EQ.2.OR.KEBAR.EQ.5) THEN	! BAR BOTTOM
				CALL PLOT(X3,Y3-EBAR,3)
				CALL PLOT(X3,Y3+EBAR,2)
			    ELSE IF (KEBAR.EQ.3.OR.KEBAR.EQ.4) THEN
				CALL PLOT(X3-EBAR,Y3,3)
				CALL PLOT(X3+EBAR,Y3,2)
			    ENDIF
			ENDIF
			IF (JSYM.EQ.0.AND.JCONN.EQ.0.AND.
     $			    JEBAR.EQ.0.AND.JVLINE.EQ.0) THEN
				CALL PLOT(X1,Y1,3)	! DOTS ONLY
				CALL PLOT(X1,Y1,2)
			ENDIF
			ISYM=ISYM+1
 60		    CONTINUE
100	CONTINUE
C
C	ADD LEGEND
C
	IF (JLEGND.NE.0) THEN
		DO 200 I=1,NL
			X1=XLEG+CSLEG*1.5
			Y1=YLEG+(I-1)*CSLEG*1.5+CSLEG*0.5
			IF (JCOL.NE.0) THEN
			    ICC=INT(ABS(F(ICOFF+24+2*(I-1))))
			    IF (ICC.LT.1) ICC=1
			    CALL PLOT(FLOAT(ICC),0.,0)
			ENDIF
			IF (JLEGLI.NE.0) THEN
		    	    IF (JLINE.NE.0)
     $				CALL NEWPEN(INT(F(2*(I-1)+ILOFF+12)))
			    CALL PLOT(X1,Y1,3)
			    CALL PLOT(X1+GLEN,Y1,2)
			    X1=X1+GLEN*0.5
			ENDIF
			IF (JLEGSY.NE.0) THEN
			    ICC=I-1+JSYMST
			    CALL SYMBOL(X1,Y1,SYMSIZ,
     $					CHAR(ICC),0.,-1,-1)
			ENDIF
			IF (JLEGLI.NE.0) X1=X1+GLEN*0.5
			X1=X1+CSLEG*0.7
			Y1=Y1-CSLEG*0.5
			IF (NC(I+3).GT.0) THEN
			    IF (JLINE.NE.0) CALL NEWPEN(INT(F(ILOFF+6)))
			    IF (JCOL.NE.0) THEN
				ICC=INT(ABS(F(ICOFF+18)))
				IF (ICC.LT.1) ICC=1
				CALL PLOT(FLOAT(ICC),0.,0)
			    ENDIF
			    CALL SYMBOL(X1,Y1,CSLEG,
     $				C(I+3),0.,NC(I+3),-1)
			ENDIF
200		CONTINUE
	ENDIF
C
C	FINISH UP
C
	CALL PLOT(0.,0.,3)			!PEN UP
	IF (IFLAG.GT.0) THEN
		CALL CTERM(2)			!CLEAR TERMINAL
		CALL PLOTND			!CLOSE PLOT OUTPUT
		REPEAT=.FALSE.
	ENDIF
	IF (IFLAG.LT.0) THEN
		REPEAT=.TRUE.
		CALL CTERM(1)			!PUT TERMINAL IN TEXT MODE
	ENDIF
	RETURN
	END
