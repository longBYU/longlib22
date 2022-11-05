C
C *** LAST REVISED ON  4-JAN-1994 10:34:06.79
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.AUXLIB]SYMBOL.FOR
C
C ***********************************************************************
C
C	THIS ROUTINE IS FORTRAN-77 COMPATIBLE WITH THE FOLLOWING
C	EXCEPTIONS:
C		1. INTEGER*2 ARRAYS ARE USED TO SAVE SPACE.  THEY MAY
C		   BE REPLACED WITH INTEGER.
C
C	MACHINE DEPENDENT NOTES:
C		1. THE FUNCTION IBITS(I,J,K) RETURNS THE VALUE OF THE BITS
C		   IN I STARTING AT J FOR K BITS.
C
C ***********************************************************************
C
	SUBROUTINE SYMBOL(X,Y,S,T,A,NN,IS)
C
C	ROUTINE TO PLOT CHARACTERS AND SYMBOLS
C
C	WRITTEN BY:	D. LONG  JAN 1991   BYU
C
C	X,Y   (R): string position
C	           If x>998 or y>998 then plotting of the string is continued
C		   from the last SYMBOL call
C	S     (R): height of the string to be printed
C	T     (C): character variable containing the ascii text to be plotted
C	A     (R): angle at which the string is to be plotted
C		   counter-clockwise from x axis
C	N     (I): number of characters to use from T
C		   note: plotting will terminate if an ASCII zero is
C		   encountered at any other position than the first character.
C                  If N<0, a plot(x,y,2) will be executed prior to plotting
C		   the first character and ABS(N) characters will be plotted.
C		   For N<2, the plot pen is left at the 1st character origin
C		   point; otherwise it is at the end of the last plotted
C		   vector in the last plotted character.
C	IS    (I): centering option flag
C			= -3 end coordinates of string (if it were to  be
C                            plotted will be returned in x,y where the input 
C			     (x,y) are the lower left corner of string.  This
C			     permits computation of the plotted length.
C			     However, no plotting is done and the last position
C                            variables are not changed.
C			= -2 end coordinates of string are returned in x,y.
C			     Inital (x,y) to be lower left corner of plotted
C                            string.  String is plotted.
C			= -1 (x,y) to be lower left corner of plotted string
C                            (x and y not altered)  String is plotted.
C			= 0  (x,y) to be center of plotted string
C                            (x and y not altered)  String is plotted.
C                       = 1  (x,y) to be lower right corner of plotted string
C                            (x and y not altered)  String is plotted.
C
C SYMBOL plots an ASCII string in a CHARACTER array.  Each character (or string
C of characters) can be imagined as a square box with the origin at the lower
C left corner.  The routine determines the initial position of the lower
C left of the first character than plots each character relative to this
C position.  As each character is plotted the "current position" is moved
C to the right (along the string baseline) a fixed amount S.  When the
C string centering option is selected, the length of the plotted string is 
C determined and, based on the character height, the lower left corner is
C computed from the input (x,y) position.  The special plot symbols (ASCII 
C 0-31) are always centered about the current position.
C
C **********************************************************************
C
	CHARACTER*(*) T
	LOGICAL LENGTH
	SAVE OLDX,OLDY
C
      INTEGER*2 IFNT(  968),IPNT( 176)
      INTEGER*2 IF001( 88),IF002( 88),IF003( 88),
     $ IF004( 88),IF005( 88),IF006( 88),IF007( 88),
     $ IF008( 88),IF009( 88),IF010( 88),IF011( 88)
      INTEGER*2 IPT001( 88),IPT002( 88)
C
      EQUIVALENCE (IFNT(    1),IF001(1)),(IFNT(   89),IF002(1)),
     $ (IFNT(  177),IF003(1)),(IFNT(  265),IF004(1)),
     $ (IFNT(  353),IF005(1)),(IFNT(  441),IF006(1)),
     $ (IFNT(  529),IF007(1)),(IFNT(  617),IF008(1)),
     $ (IFNT(  705),IF009(1)),(IFNT(  793),IF010(1)),
     $ (IFNT(  881),IF011(1))
      EQUIVALENCE (IPNT(    1),IPT001(1)),(IPNT(   89),IPT002(1))
      DATA IF001/  6186,  6826,  6806,  5526,  5546,  6186,  2080,
     $   6176, 10282, 10538, 10916, 10908, 10518, 10006,  9628,  9636,
     $   5930,  2090,  6176,  6186,  6747,  5595,  2090,  6186,  6816,
     $   6166,  5536,  6186,  2080,  6176,  6688,  5672,  5656,  2592,
     $   6501,  6491,  5851,  5861, 14693,  5546, 14053,  5526, 14043,
     $   6806, 14683,  6176,  2730,  6166, 14378,  5536,  2720,  5721,
     $  14823,  5735,  2521,  5536, 15008,  6166, 14378,  5721, 14823,
     $   6617,  1639,  5735,  6176, 14358,  6176,  2535,  6166,  6186,
     $   6816,  5536,  2090,  5526,  6826,  5546,  2710, 13844,  5672,
     $   6696,  5656, 14872,  5920,  2336, 13612,  5672,  6680,  6696/
      DATA IF002/  1560,  6176, 14872,  6696,  6176,  1568,  5672,
     $   6696,  5656,  6680,  1576,  6176,  6680,  6696,  5656,  5672,
     $   2080,  6176,  6186,  6747,  5595, 14378,  6757,  6166,  5605,
     $   2661, 15124,  6696,  5672,  6680, 13848,  6432,  1824,  6696,
     $   6680,  5672,  5656, 14888,  6180,  2075,  5656,  6696,  5672,
     $   6680, 13848,  6432,  1824,  5536,  6186,  6816,  6166,  5536,
     $  15008,  6186,  2070,  5656,  5672,  6696,  6680,  5656, 14888,
     $   5672,  2584,  6176,  5928,  6440,  6176,  6688,  6424,  6176,
     $   5912,  5664,  2080, 10204, 10077, 10015, 10017, 10083, 10212,
     $  10340, 10467, 10529, 10527, 10461, 10332, 14300,  5983,  5985/
      DATA IF003/ 14177,  6046, 14242,  6109, 14307,  6173, 14371,
     $   6237, 14435,  6302, 14498,  6367,  2273,  5916,  5924,  6436,
     $   6428, 14108,  5981, 14179,  6045, 14243,  6109, 14307,  6173,
     $  14371,  6237, 14435,  6301, 14499,  6365,  2275,  6170,  5859,
     $   6499, 14362,  5986,  6173, 14562,  6176,  6114,  6176,  2146,
     $  10273, 10208, 10271, 10336,  2081, 10204, 10077, 10015, 10017,
     $  10083, 10212, 10340, 10467, 10529, 10527, 10461, 10332,  2012,
     $  10133,  9942,  9752,  9627,  9566,  9570,  9637,  9768,  9962,
     $  10155, 10411, 10602, 10792, 10917, 10978, 10974, 10907, 10776,
     $  10582, 10389,  1941, 10122,  9803,  9549,  9359,  9170,  9045/
      DATA IF004/  8921,  8862,  8866,  8935,  9067,  9198,  9393,
     $   9587,  9845, 10166, 10422, 10741, 10995, 11185, 11374, 11499,
     $  11623, 11682, 11678, 11609, 11477, 11346, 11151, 10957, 10699,
     $  10378,  1930,  6186,  5527,  6743,  2090,  1931,  9163,  9355,
     $   9359,  9167, 13259,  5138,  5088,  5280,  1042,  5081, 13280,
     $   5472,  1369,  5067, 13280,  5472, 13643,  4825, 13913,  5714,
     $    722,  4815,  9551,  9810,  9557,  9173,  4825,  5084, 13916,
     $   5280,  1163,  4815, 13916,  9180,  8924,  8928,  9184, 13276,
     $   9803,  9547,  9551,  9807,  1611,  9810,  9355,  9163,  8911,
     $   8914,  9561,  9564,  9376,  9180,  9173,  1611,  9177,  9372/
      DATA IF005/  1184,  9568,  9177,  9170,  1355,  9184,  9561,
     $   9554,   971,  5263, 13468,  5721, 13010,  4825,  1618,  5263,
     $  13468,  4821,  1621,  8905,  9165,   975,  4821,  1621,  5068,
     $    971,  4811,  1632,  8911,  8924,  9184,  9568,  5724,  9807,
     $   9547,  5067,  4815,  1628,  5067, 13643,  5259,  5280,   988,
     $   8924,  9184,  9568,  9820,  9817,  4815,  4811,  1611,  4832,
     $   9824,  5724,  9365,  9557,  9810,  9807,  9547,  9163,   719,
     $   5451,  5472,  4821,  4818,  1618,  8911,  9163,  9547,  9807,
     $   9813,  5465,  4825,  4832,  1632,  8917,  9557,  9810,  9807,
     $   9547,  9163,  8911,  8921,  9376,  1632,  4832,  5728,  9820/
      DATA IF006/  9170,   971,  9163,  9547,  9807,  9810,  9557,
     $   9173,  8921,  8924,  9184,  9568,  9820,  9817, 13653,  9173,
     $   8914,  8911,   971,  8907,  9355,  9810,  9820,  9568,  9184,
     $   8924,  8921,  9173,  1621,  5068, 13259,  5073,   978, 13003,
     $   9163,  9359, 13458,  5272,  1177,  5451,  4821,  1376,  4818,
     $  13906,  5721,   729, 13003,  5067,  5717,   992,  5260, 13451,
     $   9362,  9817,  9820,  9568,  9184,   732,  9547,  9163,  8911,
     $   8924,  9184,  9568,  9820,  9810,  9362,  9365,  1628,  4811,
     $   8921,  5280,  5721, 13899,  4818,  1618,  4811,  4832,  9568,
     $   9820,  5721,  5461, 13013,  9557,  9810,  5711,  5451,   715/
      DATA IF007/  9820,  9568,  9184,  8924,  8911,  9163,  9547,
     $   1615,  4811,  9547,  9807,  5724,  5472, 13024,  5088,   971,
     $   4811,  4832, 13920,  5461, 13013,  4811,  1611,  4811,  4832,
     $  13920,  5269,   725,  9820,  9568,  9184,  8924,  8911,  9163,
     $   5707,  5714,  1362,  4811, 13024,  4821, 13909,  5728,  1611,
     $   5067, 13643,  5259, 13472,  5088,  1376,  8911,  9163,  5451,
     $   5711,  1632,  4811, 13024,  5728,  4821,  1611,  4832,  4811,
     $   1611,  4811,  4832,  5269,  5728,  1611,  4811, 13024,  4828,
     $  13903,  5728,  1611,  8911,  9163,  9547,  9807,  9820,  9568,
     $   9184,  8924,   719,  4811,  4832,  9568,  9820,  5721,  5461/
      DATA IF008/   725,  8911,  9163,  9547,  9807,  9820,  9568,
     $   9184,  8924, 13007,  5266,  1611,  4811,  4832,  9568,  9820,
     $   5721,  5461, 13013,  5269,  1611,  8911,  9163,  9547,  9807,
     $   9810,  9557,  9173,  8921,  8924,  9184,  9568,  1628,  4832,
     $  13920,  5280,  1163,  4832,  8911,  9163,  5451,  5711,  1632,
     $   4832,  5259,  1632,  4832,  5067,  5269,  5451,  1632,  4811,
     $   4815,  5724, 13920,  4832,  4828,  5711,  1611,  4832,  4828,
     $   5269, 13451,  5728,  5724,  1173,  4832,  5728,  5724,  4815,
     $   4811,  1611,  5280,  4832,  4811,  1163,  5707,   736,  4811,
     $   5259,  5280,   736,  4821,  5276, 13909,  5276,  1167,  5263/
      DATA IF009/  4821, 13468,  4821,  1621,  4832,  1365,  8911,
     $   8917,  9177,  9369,  9810,  9355,  9163, 13007,  5721,  1611,
     $   4811, 13024,  8914,  9369,  9561,  9813,  9807,  9547,  9355,
     $    722,  5721,  9177,  8917,  4815,  5067,  1611,  5728, 13899,
     $   9810,  9369,  9177,  8917,  8911,  9163,  9355,  1618,  4818,
     $   9810,  9813,  9561,  9177,  8917,  8911,  9163,  1355,  5259,
     $   5276, 13664,  5077,  1365,  9156,  5444,  5704, 13913,  9810,
     $   9369,  9177,  8917,  8911,  9163,  9355,  1618,  4811, 13024,
     $   8921,  5465,  5717,  1611,  5067, 13643,  5259,  5269, 13269,
     $   5275,  1180,  5061,  5253,  5449, 13657,  5471,  1376,  4811/
      DATA IF010/ 13024,  5724, 13007,  5269,  1611,  5067, 13643,
     $   5259,  5280,   992,  4811, 13017,  8917,  5081,  5269, 13451,
     $   9365,  5465,  5717,  1611,  4811, 13017,  8917,  9177,  5465,
     $   5717,  1611,  8911,  8917,  9177,  9561,  9813,  9807,  9547,
     $   9163,   719,  4804, 13017,  8914,  9369,  9561,  9813,  9807,
     $   9547,  9355,   722,  5700, 13913,  9810,  9369,  9177,  8917,
     $   8911,  9163,  9355,  1618,  4811, 13017,  8914,  5273,  1625,
     $   8907,  9547,  9807,  9554,  9170,  8917,  9177,  1625,  5081,
     $  13657,  5280,  5263,  1355,  4825,  8911,  9163,  9547, 13903,
     $   5721,  1611,  4825,  5259,  1625,  4825,  5067,  5266,  5451/
      DATA IF011/  1625,  4811, 13913,  4825,  1611,  9156,  5444,
     $   5704, 13913,  4825,  8911,  9163,  1611,  4825,  5721,  4811,
     $   1611,  5259,  5007,  5075,  4885,  5080,  5020,  1184,  5259,
     $  13458,  5273,  1184,  5067,  5327,  5267,  5461,  5272,  5340,
     $    992,  4819,  5079,  5459,  1623,   131,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0/
      DATA IPT001/     1,     8,    19,    24,    30,    35,    48,
     $     52,    56,    64,    69,    74,    78,    85,    90,    95,
     $    100,   106,   115,   122,   129,   136,   144,   152,   162,
     $    190,   209,   220,   225,   238,   259,   292,   296,   297,
     $    306,   310,   318,   328,   340,   351,   354,   358,   362,
     $    368,   372,   375,   377,   379,   381,   391,   396,   404,
     $    414,   419,   428,   438,   443,   460,   470,   474,   480,
     $    483,   487,   491,   499,   510,   517,   529,   537,   545,
     $    552,   557,   566,   572,   578,   583,   588,   591,   596,
     $    602,   611,   618,   629,   638,   650,   654,   660,   663/
      DATA IPT002/   668,   676,   683,   689,   693,   695,   699,
     $    704,   709,   711,   721,   731,   737,   747,   756,   761,
     $    773,   779,   786,   792,   798,   803,   813,   820,   829,
     $    839,   849,   854,   862,   867,   874,   877,   882,   886,
     $    894,   898,   905,   909,   916,   920,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0,
     $      0,     0,     0,     0,     0,     0,     0,     0,     0/
C
C **********************************************************************
C
	N=NN				! NUMBER OF CHARACTERS
	AA=A				! PLOTTING ANGLE
	SI=SIN(AA*0.0174532)
	CO=COS(AA*0.0174532)
	LENGTH=.TRUE.			! PLOT (TRUE) OR LENGTH ONLY
	AL=0.0				! PLOTTED LENGTH
	ISS=IS				! CENTERING FLAG
	IF (ISS.EQ.-3) LENGTH=.FALSE.
	IF (ISS.GT.-1) LENGTH=.FALSE.
	OX=OLDX				! SAVE CURRENT POSITION
	OY=OLDY
1100	CONTINUE			! TOP OF LENGTH COMPUTATION
	AL=0.0				! LENGTH OF PLOTTED STRING ACCUMULATOR
	X1=X				! LOWER LEFT CORNER
	Y1=Y
	IF (ISS.EQ.0) THEN		! CENTERED
		X1=X-AL/2.*CO+S/2.*SI
		Y1=Y-S/2.*CO-AL/2.*SI
	ENDIF
	IF (ISS.EQ.1) THEN		! LOWER RIGHT CORNER
		X1=X-AL*CO
		Y1=Y-AL*SI
	ENDIF
	IF (X.GT.998.0.OR.Y.GT.998.0) THEN
		IF (X.LT.998.0) OLDX=OLDX+X1
		IF (Y.LT.998.0) OLDY=OLDY+Y1
	ELSE
		OLDX=X1
		OLDY=Y1
	ENDIF
	X0=OLDX
	Y0=OLDY
	IF (LENGTH.AND.N.LT.0) CALL PLOT(OLDX,OLDY,2)	! PLOT TO START
	SS=S/21.		! SCALE FACTOR
	I=0			! CHARACTER COUNTER
50	I=I+1
	IF (I.GT.IABS(N)) GOTO 1000		! END OF STRING COUNT
		ICC=ICHAR(T(I:I))		! GET ITH ASCII CHARACTER
		IF (ICC.GT.127) GOTO 50		! CODE TO LARGE
		IF (ICC.EQ.0.AND.I.GT.1) GOTO 1000	! END OF STRING REACHED
		IXOFF=11			! OFFSET
		IYOFF=11
		IF (ICC.LT.32) THEN		! DIFFERENT SYMBOL OFFSET
			IXOFF=32
			IYOFF=32
		ENDIF
		IL=IPNT(ICC+1)			! STARTING INDEX
		IW=21				! CHARACTER WIDTH
		IF (IL.EQ.0) GOTO 90		! NO PLOTING INFO
		IPENLAST=3
70		CONTINUE
		IY=IBITS(IFNT(IL),0,6)
		IX=IBITS(IFNT(IL),6,6)
		IPEN=IBITS(IFNT(IL),12,2)
		IP=IPENLAST
		IPENLAST=IPEN
		XX=SS*(IX-IXOFF)
cc		Y1=SS*(IY-IYOFF+ISUB)
		Y1=SS*(IY-IYOFF)
		X1=XX*CO-Y1*SI+OLDX
		Y1=XX*SI+Y1*CO+OLDY
		IF (IP.EQ.0) IP=2
		IF (IP.EQ.1) IP=2
		IF (LENGTH) CALL PLOT(X1,Y1,IP)
		IL=IL+1
		IF (IPEN.NE.0) GOTO 70
90		XX=SS*IW			! END OF CHARACTER
		AL=AL+SS*IW
		OLDX=XX*CO+OLDX
		OLDY=XX*SI+OLDY
	GOTO 50
1000	IF (.NOT.LENGTH) THEN	! FINISHED LENGTH-ONLY PASS
		LENGTH=.TRUE.
		IF (ISS.EQ.-3) THEN	! RETURN END POSITION
			X=OLDX
			Y=OLDY
		ENDIF
		OLDX=OX		! RESTORE OLD POSITION
		OLDY=OY
		IF (ISS.EQ.0.OR.ISS.EQ.1) GOTO 1100
	ELSE
		IF (N.LE.1) CALL PLOT(X0,Y0,3)	! LEAVE PEN AT START
		IF (ISS.EQ.-2) THEN	! RETURN END POSITION
			X=OLDX
			Y=OLDY
		ENDIF
	ENDIF
	RETURN
	END
