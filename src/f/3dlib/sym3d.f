C
C
      SUBROUTINE SYM3D(XA,YA,ZA,PA,PB,PG,HI,ASC,NC)
C
C	CREATED: DGL 1-OCT-1984
C	
C	PLOTS SYMBOLS IN 3-D USING PLOT3D
C
C	XA,YA,ZA COORDINATES OF STRING LOWER-LEFT CORNER
C		  (999.,999.,999.) CONTINUE FROM LAST POINT
C	PA,PB	SPECIFIES THE PROJECTED ANGLES (IN DEGS) RELATIVE TO THE
C		 X-Y PLANE AND THE X-Z PLANE OF THE LINE ALONG THE
C		 BASE OF THE PLOTTED NUMBER SEQUENCE
C	PG	SPECIFIES THE ROTATION OF THE PLOTTED SYMBOLS AROUND
C		THE LINE SPECIFIED BY PA,PB
C	HI	HEIGHT OF THE PLOTTED CHARACTERS
C	ASC	CHARACTER VARIABLE CONTAINING CHARACTERS TO BE PLOTTED
C	NC	NUMBER OF CHARACTERS TO BE PLOTTED
C
      DIMENSION ROT(4,4),TEMP(4,4),V(4)
C     
      CHARACTER*(*) ASC
      INTEGER*2 SYM(128),STB(416)
      INTEGER*2 SYN  1(8)
      INTEGER*2 SYN  9(8)
      INTEGER*2 SYN 17(8)
      INTEGER*2 SYN 25(8)
      INTEGER*2 SYN 33(8)
      INTEGER*2 SYN 41(8)
      INTEGER*2 SYN 49(8)
      INTEGER*2 SYN 57(8)
      INTEGER*2 SYN 65(8)
      INTEGER*2 SYN 73(8)
      INTEGER*2 SYN 81(8)
      INTEGER*2 SYN 89(8)
      INTEGER*2 SYN 97(8)
      INTEGER*2 SYN105(8)
      INTEGER*2 SYN113(8)
      INTEGER*2 SYN121(8)
      INTEGER*2 STC  1(8)
      INTEGER*2 STC  9(8)
      INTEGER*2 STC 17(8)
      INTEGER*2 STC 25(8)
      INTEGER*2 STC 33(8)
      INTEGER*2 STC 41(8)
      INTEGER*2 STC 49(8)
      INTEGER*2 STC 57(8)
      INTEGER*2 STC 65(8)
      INTEGER*2 STC 73(8)
      INTEGER*2 STC 81(8)
      INTEGER*2 STC 89(8)
      INTEGER*2 STC 97(8)
      INTEGER*2 STC105(8)
      INTEGER*2 STC113(8)
      INTEGER*2 STC121(8)
      INTEGER*2 STC129(8)
      INTEGER*2 STC137(8)
      INTEGER*2 STC145(8)
      INTEGER*2 STC153(8)
      INTEGER*2 STC161(8)
      INTEGER*2 STC169(8)
      INTEGER*2 STC177(8)
      INTEGER*2 STC185(8)
      INTEGER*2 STC193(8)
      INTEGER*2 STC201(8)
      INTEGER*2 STC209(8)
      INTEGER*2 STC217(8)
      INTEGER*2 STC225(8)
      INTEGER*2 STC233(8)
      INTEGER*2 STC241(8)
      INTEGER*2 STC249(8)
      INTEGER*2 STC257(8)
      INTEGER*2 STC265(8)
      INTEGER*2 STC273(8)
      INTEGER*2 STC281(8)
      INTEGER*2 STC289(8)
      INTEGER*2 STC297(8)
      INTEGER*2 STC305(8)
      INTEGER*2 STC313(8)
      INTEGER*2 STC321(8)
      INTEGER*2 STC329(8)
      INTEGER*2 STC337(8)
      INTEGER*2 STC345(8)
      INTEGER*2 STC353(8)
      INTEGER*2 STC361(8)
      INTEGER*2 STC369(8)
      INTEGER*2 STC377(8)
      INTEGER*2 STC385(8)
      INTEGER*2 STC393(8)
      INTEGER*2 STC401(8)
      INTEGER*2 STC409(8)
      EQUIVALENCE (SYM(  1),SYN  1(1))
      EQUIVALENCE (SYM(  9),SYN  9(1))
      EQUIVALENCE (SYM( 17),SYN 17(1))
      EQUIVALENCE (SYM( 25),SYN 25(1))
      EQUIVALENCE (SYM( 33),SYN 33(1))
      EQUIVALENCE (SYM( 41),SYN 41(1))
      EQUIVALENCE (SYM( 49),SYN 49(1))
      EQUIVALENCE (SYM( 57),SYN 57(1))
      EQUIVALENCE (SYM( 65),SYN 65(1))
      EQUIVALENCE (SYM( 73),SYN 73(1))
      EQUIVALENCE (SYM( 81),SYN 81(1))
      EQUIVALENCE (SYM( 89),SYN 89(1))
      EQUIVALENCE (SYM( 97),SYN 97(1))
      EQUIVALENCE (SYM(105),SYN105(1))
      EQUIVALENCE (SYM(113),SYN113(1))
      EQUIVALENCE (SYM(121),SYN121(1))
      EQUIVALENCE (STB(  1),STC  1(1))
      EQUIVALENCE (STB(  9),STC  9(1))
      EQUIVALENCE (STB( 17),STC 17(1))
      EQUIVALENCE (STB( 25),STC 25(1))
      EQUIVALENCE (STB( 33),STC 33(1))
      EQUIVALENCE (STB( 41),STC 41(1))
      EQUIVALENCE (STB( 49),STC 49(1))
      EQUIVALENCE (STB( 57),STC 57(1))
      EQUIVALENCE (STB( 65),STC 65(1))
      EQUIVALENCE (STB( 73),STC 73(1))
      EQUIVALENCE (STB( 81),STC 81(1))
      EQUIVALENCE (STB( 89),STC 89(1))
      EQUIVALENCE (STB( 97),STC 97(1))
      EQUIVALENCE (STB(105),STC105(1))
      EQUIVALENCE (STB(113),STC113(1))
      EQUIVALENCE (STB(121),STC121(1))
      EQUIVALENCE (STB(129),STC129(1))
      EQUIVALENCE (STB(137),STC137(1))
      EQUIVALENCE (STB(145),STC145(1))
      EQUIVALENCE (STB(153),STC153(1))
      EQUIVALENCE (STB(161),STC161(1))
      EQUIVALENCE (STB(169),STC169(1))
      EQUIVALENCE (STB(177),STC177(1))
      EQUIVALENCE (STB(185),STC185(1))
      EQUIVALENCE (STB(193),STC193(1))
      EQUIVALENCE (STB(201),STC201(1))
      EQUIVALENCE (STB(209),STC209(1))
      EQUIVALENCE (STB(217),STC217(1))
      EQUIVALENCE (STB(225),STC225(1))
      EQUIVALENCE (STB(233),STC233(1))
      EQUIVALENCE (STB(241),STC241(1))
      EQUIVALENCE (STB(249),STC249(1))
      EQUIVALENCE (STB(257),STC257(1))
      EQUIVALENCE (STB(265),STC265(1))
      EQUIVALENCE (STB(273),STC273(1))
      EQUIVALENCE (STB(281),STC281(1))
      EQUIVALENCE (STB(289),STC289(1))
      EQUIVALENCE (STB(297),STC297(1))
      EQUIVALENCE (STB(305),STC305(1))
      EQUIVALENCE (STB(313),STC313(1))
      EQUIVALENCE (STB(321),STC321(1))
      EQUIVALENCE (STB(329),STC329(1))
      EQUIVALENCE (STB(337),STC337(1))
      EQUIVALENCE (STB(345),STC345(1))
      EQUIVALENCE (STB(353),STC353(1))
      EQUIVALENCE (STB(361),STC361(1))
      EQUIVALENCE (STB(369),STC369(1))
      EQUIVALENCE (STB(377),STC377(1))
      EQUIVALENCE (STB(385),STC385(1))
      EQUIVALENCE (STB(393),STC393(1))
      EQUIVALENCE (STB(401),STC401(1))
      EQUIVALENCE (STB(409),STC409(1))
      real X,Y,Z ! note these are set on first call, may used for later calls
      data X,Y,Z/0.,0.,0./
      DATA SYN	1/     0,     8,    20,    26
     1,    31,	  36,	 43,	50/
      DATA SYN	9/    55,    62,    68,    82
     1,    91,	  98,	101,   104/
      DATA SYN 17/   111,   118,   125,   125
     1,   125,	 125,	125,   125/
      DATA SYN 25/   125,   125,   125,   125
     1,   125,	 125,	125,   125/
      DATA SYN 33/   125,   126,   136,   141
     1,   150,	 161,	174,   186/
      DATA SYN 41/   190,   195,   200,   207
     1,   212,	 215,	218,   221/
      DATA SYN 49/   223,   234,   240,   249
     1,   260,	 266,	276,   287/
      DATA SYN 57/   293,   311,   321,   326
     1,   332,	 336,	341,   345/
      DATA SYN 65/   354,   366,   373,   385
     1,   394,	 402,	409,   414/
      DATA SYN 73/   424,   430,   437,   443
     1,   448,	 452,	457,   463/
      DATA SYN 81/   473,   480,   492,   501
     1,   514,	 519,	526,   530/
      DATA SYN 89/   536,   544,   552,   559
     1,   564,	 567,	571,   577/
      DATA SYN 97/   583,   586,   597,   607
     1,   614,	 625,	635,   641/
      DATA SYN105/   654,   660,   668,   675
     1,   681,	 687,	697,   704/
      DATA SYN113/   714,   724,   735,   740
     1,   748,	 754,	762,   766/
      DATA SYN121/   772,   776,   785,   790
     1,   798,	 803,	811,   816/
      DATA STC	1/ 10842,  2088, 11276, -9686
     1, 10842,	8233,  2320,  5131/
      DATA STC	9/ 11044, -9686, 10842,  3080
     1, -9686,	2666,  7256, 18650/
      DATA STC 17/ 26668, -9716, 10842,  2584
     1, 10780, 23258, 10776,  6684/
      DATA STC 25/ -9718, 11336,  3112, 26842
     1,  2092, 22796, -9701, 10330/
      DATA STC 33/  6764, -9718, 11354,  8547
     1, 24872,	2065,  4945, 21260/
      DATA STC 41/ -9693, 11336,  3176, 10826
     1,  7256, 23258, 11304,  3080/
      DATA STC 49/ -9702, 10826, 22746, -9700
     1,  7256, 11368,  3144, 24794/
      DATA STC 57/ 20516, 18708, -9685, 10842
     1,  9057,	4945,-14630,   577/
      DATA STC 65/  2314, 20993, 12849,-14830
     1, 12641,	9075, 16838, 29489/
      DATA STC 73/ 24579, 21540,-14832,  2888
     1,  6932,	8217, 11305,   626/
      DATA STC 81/ 18630, 26924, 12328, 10545
     1,   836,	3083,-14844,   596/
      DATA STC 89/  2049,  8976, 12843,  6441
     1,-14844, 10849,-14798,  8563/
      DATA STC 97/   785, 29126,  4899,-14847
     1, 10826,	4196,  5216, 19142/
      DATA STC105/ 22570,-14820,  4361, 22726
     1,-14820,	 321, 13510, 18630/
      DATA STC113/ 12584, 11315,   780,  2049
     1,-14804,	 833, 12866,-14807/
      DATA STC121/ 12648, 11315,  2084,  1024
     1, 28870, 11316,  6938,  3092/
      DATA STC129/   259,-14840, 13123,  4120
     1,-14828,	 328,  3075,  8988/
      DATA STC137/ 12320,-14796,  7000,  3092
     1,   259,	8200, 13362, 28870/
      DATA STC145/ 11316,   273, 16838,  3075
     1,  6932,	8217, 12584, 11315/
      DATA STC153/  6948,  4185,   264,   710
     1, 11284, 12595,  8232,  7193/
      DATA STC161/ 16838, 20737,-14831,  2625
     1, 25106,-14814,  6211,-14797/
      DATA STC169/  5200,  8292, 16838, 12572
     1, 17094, 20994, 11300, 12595/
      DATA STC177/-14808,   323, 10248, 13105
     1,  5164,	6674,-14804, 12832/
      DATA STC185/  1060,  5200, 12486, 11315
     1,  6948, 23320,  3092,	 3/
      DATA STC193/ 27846, 12595,  2088,   769
     1,-14836,	3075, 13100, 28976/
      DATA STC201/-14847, 13360,  6235,  1088
     1, 12486, 23092,-14824, 13164/
      DATA STC209/ 10289,   264,  5124,-14829
     1, 22576, 29724,-14844,   833/
      DATA STC217/ 12866, 13169, 18630,   769
     1, 13324, 12486,  6260,-14844/
      DATA STC225/ 16432,-14844,  6704,  1076
     1, 12486,	3176,  1140, 18630/
      DATA STC233/   769, 11276, 12595,  2088
     1, 12486, 11315,  6948,-14824/
      DATA STC241/   328,  3075, 13100, 10289
     1, 21000,-14844, 13104,  9260/
      DATA STC249/  6171,  1114, 18630,   769
     1,  5132,	6427, 10272, 13105/
      DATA STC257/-14804, 13424,   626, 28870
     1,   264,	3075,-14796,   624/
      DATA STC265/-14796,   368,   794,-14796
     1, 11272, 28724,  3112,-14844/
      DATA STC273/ 10352,   538, 11380,-14822
     1, 13424,	2092,  1024, 29382/
      DATA STC281/    48,-15358, 12356,   710
     1, 12338, 22724,  7210,  2666/
      DATA STC289/ 19142, 10776,  7256, 28870
     1,-14821,	6216,  8737,   532/
      DATA STC297/  2049,  1124, 12486,  8784
     1,  7203,	 780,  4098, 25798/
      DATA STC305/  6177,   264,-14844,  1140
     1,  8788,	6177,	264,  5122/
      DATA STC313/ 20678,  7188,  8483,  2072
     1,   769, 17094, 13098,  7001/
      DATA STC321/ 16838,  3075, 25652, 12594
     1,  6184,	4625,-14812, 24624/
      DATA STC329/  7203,-14844,   833,  6722
     1, 27161,-14806,	577,  8971/
      DATA STC337/ 13171, 12486,  2156,  1114
     1, 16838, 16899, 12594,  8390/
      DATA STC345/  8536,   538,  9050,  1052
     1,  8390,	8536,  7203,-14844/
      DATA STC353/  6216,  8993,  3100,   259
     1,-14840, 24624, 13106,  7212/
      DATA STC361/  4627,-14816, 13380, 12900
     1, 10289,	4376,  9234,  8390/
      DATA STC369/  8784,-14812,  3075,  4371
     1,  8472,-14812,  9057,  2674/
      DATA STC377/-14845,  2144,   769, 25612
     1,-14844,	 608,-14812,   352/
      DATA STC385/   786,-14812, 24612,-14844
     1,   833, 13324,  6256,  5137/
      DATA STC393/ 24774,    36,-14844,  2370
     1,  6161, 10529,-15054,  4674/
      DATA STC401/ 12898, 16838,  4618,  8731
     1, 12586, 20677,  6937,-14812/
      DATA STC409/ 13360,     4, 28724,-14844
     1,     0,	   0,	  0,	 0/
C
	XA1=XA
	YA1=YA
	ZA1=ZA
	IF (XA.EQ.999..OR.YA.EQ.999..OR.ZA.EQ.999.) THEN !CONTINUE STRING OUTPUT
		XA1=X
		YA1=Y
		ZA1=Z
	ELSE
C
C	SET UP 3-D CONVERSION MATRIXES
C
		CALL ROTEM(1,PG,ROT)
		CALL ROTEM(3,PB,TEMP)
		CALL MATMUL4(ROT,ROT,TEMP)
		CALL ROTEM(2,PA,TEMP)
		CALL MATMUL4(ROT,ROT,TEMP)
	ENDIF
	X=XA1
	Y=YA1
	Z=ZA1
C
	H=HI/7.0
	IF (NC.NE.-2) GOTO 4
	IP=2
	CALL PLOT3D(XA1,YA1,Z,IP)
4	IP=3
	CALL PLOT3D(X,Y,Z,IP)
	IF (NC) 10,20,30
10	NC0=0
C
	JCH=ICHAR(ASC(1:1))
	GOTO 50
20	RETURN
30	NC0=NC
	I0=0
40	NC0=NC0-1
	IF (NC0.LT.0) GOTO 20
	I0=1+I0
	JCH=ICHAR(ASC(I0:I0))
50	IF (JCH.LT.0.OR.JCH.GE.128) JCH=32
	I3=SYM(1+JCH)
	IF (JCH.GE.32) GOTO 55
C	CENTERED PLOTTING SYMBOLS
	IP=3
	I1=0
	V(1)=-H*2.
	V(2)=-H*3.
	V(3)=0.
	CALL MTV4(V,ROT,V)
	X=V(1)+X
	Y=V(2)+Y
	Z=V(3)+Z
	XW1=0.
	YW1=0.
	XW2=0.
	YW2=0.
	GOTO 110
55	IF (JCH.NE.112) GOTO 60
	XW2=0.
	YW2=-H*2.
	V(1)=XW2
	V(2)=YW2
	V(3)=0.0
	CALL MTV4(V,ROT,V)
	CALL PLOT3D(V(1)+X,V(2)+Y,V(3)+Z,3)
60	IP=2
	I3=1+I3
	I4=(I3-1)/2+1
	IV=STB(I4)
	IJ=MOD(I3-1,2)*8
	I1=IBITS(IV,IJ,8)
	I2=MOD(I1,64)
	IF (I1.GE.64) IP=3
	IY=I2/8
	IX=I2-8*IY
	X1=IX
	Y1=IY
	XW1=H*X1
	YW1=H*Y1
	XW2=XW1
	YW2=YW1
	IF ((JCH.EQ.103.OR.JCH.EQ.112.OR.JCH.EQ.113.OR.
     $		JCH.EQ.121).AND.(I1.LT.192)) THEN
		XW2=XW2
		YW2=YW2-H*2.
	ENDIF
110	CONTINUE
	V(1)=XW2
	V(2)=YW2
	V(3)=0.0
	CALL MTV4(V,ROT,V)
	CALL PLOT3D(V(1)+X,V(2)+Y,V(3)+Z,IP)
	IF (I1.LT.192) GOTO 60
	V(1)=XW1
	V(2)=YW1
	V(3)=0.0
	CALL MTV4(V,ROT,V)
	X=V(1)+X
	Y=V(2)+Y
	Z=V(3)+Z
	GOTO 40
	END