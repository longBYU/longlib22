	PROGRAM SYMBOLS
C *** LAST REVISED ON 20-FEB-1995 18:43:14.56
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.EXAMPLES]SYMBOLS.FOR
C
C	A SIMPLE PROGRAM TO PLOT A SAMPLE OF EACH PLOTTING SYMBOL
C       FROM THE ROUTINES SYMBOL, SYMS, AND SYMSS
C
C       THIS VERSION OF SYMBOLS IS FOR COMPILERS THAT ESCAPE \
C
	CHARACTER*2 T
	CHARACTER*73 STRING
	DATA STRING/'\\2A\\0=\\7R\\6a\\^2\\[\\]\\_\\6n\\[\\]\\]\\]\\=\\U\\6n=1\\@\\]\\]\\O\\1K'/
C
	CALL FRAME(3,0,1.,1.,1.)	!INTIALIZE PLOT PACKAGE
	X1=.5
	Y=1.
C	
C	FIRST PLOT "SYMBOL" CHARACTER FONT
C
	CALL SYMBOL(0.,3.,.2,'SYMBOL Characters',90.,17,-1)
	DO 25 ISYM=0,23
		DO 26 J=0,6
			Y=FLOAT(J)*1.1
			K=J*23+ISYM
			IF (K.GT.134) GOTO 26
			CALL NUMBER(X1+.01,Y,.18,FLOAT(K),90.,0.0,-1)
			CALL SYMBOL(X1,Y+.65,.2,CHAR(K),90.,1,-1)
26		CONTINUE
		X1=X1+.24
25	CONTINUE
	CALL CTERM(2)
	CALL RTERM(2)
	CALL NEWPAGE
C
C	NOW PLOT "SYMS" CHARACTER FONTS
C
	CALL CTERM(-1)
	AL=SYMS(0.,2.5,.2,'SYMS Character Fonts',90.,20,-1)
	CALL PLOT(1.2,-.5,-3)
	CALL FACTOR(.8)
 84	DO 43 I=1,32
		X1=(I-1)*.25
		AL=SYMS(X1,0.,.20,CHAR(I-1),0.,1,-1)
		CALL NUMBER(X1,-0.5,.15,FLOAT(I-1),90.,0.0,-1)
43	CONTINUE
C
	AL=SYMS(-1.2,.5,.2,STRING,90.,99,-1)
	CALL SYMBOL(-1.2,1.5,.12,STRING,90.,60,-1)
	DO 100 I=1,9
	  T=CHAR(92)//CHAR(I+47)
	  CALL SYMBOL(-.35,0.3+(I-1)*.9,.15,'Font',90.,4,-1)
	  CALL SYMBOL(999.,999.,.15,CHAR(I+47),90.,1,-1)
	  AL=SYMS(0.,0.3+(I-1)*.9,.23,T,0.,2,-1)	! CHANGE FONT AND LOCATION
	  AL=SYMS(999.,999.,.23,'@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_',
     $		0.,33,-1)
	  AL=SYMS(0.,.6+(I-1)*.9,.23,T,0.,2,-1)	! CHANGE LOCATION
	  AL=SYMS(999.,999.,.23,'`abcdefghijklmnopqrstuvwxyz{|}~',
     $		0.,32,-1)
	  AL=SYMS(0.,.9+(I-1)*.9,.23,T,0.,2,-1)	! CHANGE LOCATION
	  AL=SYMS(999.,999.,.23,' !"#$%&''()*+,-./0123456789:;<=>?',
     $		0.,32,-1)
100	CONTINUE
	CALL PLOT(0.,0.,3)
	CALL NEWPAGE
	CALL CTERM(2)
	CALL RTERM(2)
C
C	NOW PLOT "SYMSS" CHARACTER FONTS
C
	CALL CTERM(-1)
	CALL SYMBOL(0.,3.,.2,'SYMSS Characters',90.,16,-1)
	DO 44 I=1,32
		X1=(I-1)*.25
		AL=SYMSS(X1,0.,.25,CHAR(I-1),0.,1,-1,.02,0,0,0,0,0)
		CALL NUMBER(X1,-.6,.18,FLOAT(I-1),90.,0.0,-1)
44	CONTINUE 
	AL=SYMSS(-1.3,.5,.2,STRING,0.,99,-1,.02,0,0,0,0,0)
	CALL SYMBOL(0.9,.5,.2,STRING,0.,60,-1)
	DO 110 I=1,9
	  T=CHAR(124)//CHAR(I+47)
	  CALL SYMBOL(-.35,I*.9,.15,'Font ',90.,5,-1)
	  CALL SYMBOL(999.,999.,.15,CHAR(I+47),90.,1,-1)
	  AL=SYMSS(0.,I*.9,.23,T,0.,2,-1,.02,0,0,0,0,0)! CHANGE FONT,LOCATION
	  AL=SYMSS(999.,999.,.23,'@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_',
     $		0.,32,-1,.02,0,0,0,0,0)
	  AL=SYMSS(0.,.3+I*.9,.23,T,0.,2,-1,.02,0,0,0,0,0)! LOCATION
	  AL=SYMSS(999.,999.,.23,'`abcdefghijklmnopqrstuvwxyz{||}~',
     $		0.,33,-1,.02,0,0,0,0,0)
	  AL=SYMSS(0.,.6+I*.9,.23,T,0.,2,-1,.02,0,0,0,0,0)! LOCATION
	  AL=SYMSS(999.,999.,.23,' !"#$%&''()*+,-./0123456789:;<=>?',
     $		0.,32,-1,.02,0,0,0,0,0)
110	CONTINUE
	CALL PLOT(0.,0.,3)
	CALL CTERM(2)
	CALL RTERM(2)
	CALL PLOTND
	STOP
 	END
