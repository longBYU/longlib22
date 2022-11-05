C
C *** LAST REVISED ON  3-SEP-1994 07:18:17.95
C *** SOURCE FILE: [LONGLIB93.SOURCES.FORTRAN.NORAMLIB]NORAMLIB2.FOR
C
C *********************************************************************
C
C  CREATED BY D. LONG   NOV, 1983
C
C  THIS FILE CONTAINS DUMMY ROUTINES TO REPLACE THE RAMTEK
C  ROUTINES IN THE LONGLIB GRAPHICS LIBRARY. 
C
C  SOURCE CODE IN THIS FILE ARE COMPLETELY ANSI FORTRAN 77 COMPATIBLE
C  WITH THE EXCEPTION OF SUBROUTINE NAME LENGTHS.
C
C *********************************************************************
C
	INTEGER FUNCTION IRMCHAN(IDEV)
	IRMCHAN=-1
	RETURN
	END
C
	SUBROUTINE PLOTRM(X,Y,I)
	RETURN
	END
C
	SUBROUTINE RFACTOR(F)
	RETURN
	END
C
	SUBROUTINE RPLOTS(X,Y,Z)
	RETURN
	END
C
	SUBROUTINE RMPEN(I)
	RETURN
	END
C
	SUBROUTINE RTERM(I)
	RETURN
	END
C
	SUBROUTINE RMPIX(X,Y,IX0,IY0)
	RETURN
	END
C
	SUBROUTINE RMPIXB(X,Y,IX0,IY0)
	RETURN
	END
C
	SUBROUTINE RMSIZE(XLEN,YLEN,NXSIZE,NYSIZE)
	RETURN
	END
C
	SUBROUTINE RMSETSIZE(XLEN,YLEN,NXSIZE,NYSIZE)
	RETURN
	END
C
	SUBROUTINE RAMMAP(IA,MA,NA,M,N,IX,IY,IX1,IY1)
	DIMENSION IA(1)
	RETURN
	END
C
	SUBROUTINE RAMOPEN(ICHAN,IDEV,IDDEV,IERR)
	COMMON /RAMTEKIO/ IC
	SAVE /RAMTEKIO/
	WRITE (*,10) 
10	FORMAT(' *** RAMTEK NOT AVAILABLE ON THIS LIBRARY VERSION ***')
	IERR=-1
	IOTYPE=IDEV			! STORE RAMTEK TYPE
	ICHAN=-1
	IC=-1
	RETURN
	END
C
	SUBROUTINE RAMCLOSE(ICHAN)
	ENTRY REFDIS
	RETURN
	END
C
	SUBROUTINE RMRESET(ICHAN,IERR)
	RETURN
	END
C
C
	SUBROUTINE RAMOUT(ICHAN,M,N,IERR)
	BYTE M(1)
	RETURN
	END
C
	SUBROUTINE RMPLOT(ICHAN,N,M,ICOL,IERR)
	DIMENSION M(1)
	RETURN
	END
C
	SUBROUTINE RMTEXTURE(ICHAN,ITEXT,IWIDE,ISIZE,IERR)
	RETURN
	END
C
	SUBROUTINE RMCLEAR(ICHAN,IERR)
	RETURN
	END
C
	SUBROUTINE RAMOUTIN(ICHAN,CMD,NC,BUF,NB,IERR)
	BYTE CMD(1),BUF(1)
	RETURN
	END
C
	SUBROUTINE RMREADCURSOR(ICHAN,IDEV,IX,IY,ITRK,IVIS,IENT,IERR)
	RETURN
	END
C
	SUBROUTINE RMREADCURSOR2(USER,ICHAN,IPNTS,JCOPT,IHIGH,
     *		IX1,IY1,IX2,IY2,IC)
	EXTERNAL USER
	DIMENSION IPNTS(1)
	RETURN
	END
C
	SUBROUTINE RMREADCOL(ICHAN,IS,N,IERR)
	INTEGER*4 IS(1)
	RETURN
	END
C
	SUBROUTINE RMWRITECOL(ICHAN,IS,N,IERR)
	INTEGER IS(1)
	RETURN
	END
C
	SUBROUTINE RMREADBYTE(ICHAN,IS,N,IERR)
	BYTE IS(1)
	RETURN
	END
C
	SUBROUTINE RMREADWORD(ICHAN,IS,N,IERR)
	INTEGER*2 IS(1)
	RETURN
	END
C
	SUBROUTINE RMWRITEBYTE(ICHAN,IS,N,IERR)
	BYTE IS(1)
	RETURN
	END
C
	SUBROUTINE RMWRITEWORD(ICHAN,IS,N,IERR)
	BYTE IS(1)
	RETURN
	END
C
	SUBROUTINE RMSTART(ICHAN,IX,IY,IERR)
	RETURN
	END
C
	SUBROUTINE RMWIND(ICHAN,IX,IY,IXM,IYM,IERR)
	RETURN
	END
C
	SUBROUTINE RMDIR(ICHAN,ISEQ,IERR)
	RETURN
	END
C
	SUBROUTINE RMZOOM(ICHAN,IFACT,IERR)
	RETURN
	END
C
	SUBROUTINE RMPAN(ICHAN,LEFTX,TOPY,IERR)
	RETURN
	END
C
	SUBROUTINE RMSETCUR(ICHAN,ICUR,IX,IY,IBL,IVI,IERR)
	RETURN
	END
C
	SUBROUTINE RMTEXT(ICHAN,ICOL,IX,IY,IS,TEXT,ILEN,IERR)
	BYTE TEXT(1)
	RETURN
	END
C
	SUBROUTINE RMFNTSIZE(ICHAN,HD,VD,HS,VS,IERR)
	INTEGER HD,VD,HS,VS
	RETURN
	END
C
C	NEW ROUTINES
C
	SUBROUTINE RMPAUSE(ICHAN,IWAIT)
	RETURN
	END
C
	SUBROUTINE RMINFO(ICHAN,IOPEN,IX,IY,NCOL,LCOL,XW,YW,ISIZE)
	INTEGER XW(2),YW(2)
	RETURN
	END
C
	SUBROUTINE RMWRCOLIND(ICHAN,IRED,IGREEN,IBLUE,INDEX,IERR)
	RETURN
	END
C
	SUBROUTINE RMRDCOLIND(ICHAN,IRED,IGREEN,IBLUE,INDEX,IERR)
	RETURN
	END
C
	SUBROUTINE RMWR4(ICHAN,IS,N,IERR)
	INTEGER*4 IS(1)
	RETURN
	END
C
	SUBROUTINE RMRW4(ICHAN,IS,N,IERR)
	INTEGER*4 IS(1)
	RETURN
	END
C
	SUBROUTINE RMSPIX(ICHAN,IX,IY,IVAL,IRDWR,IERR)
	RETURN
	END
C
	SUBROUTINE RMSTCOL(ICHAN,ITAB,NCOL,IERR)
	RETURN
	END
C
	SUBROUTINE RMMODE(ICHAN,IWIN,IPIX,ISWAP,IERR)
	LOGICAL IWIN,IPIX,ISWAP
	RETURN
	END
C
	SUBROUTINE RMPOINT(ICHAN,IX,IY,ICOL,IERR)
	RETURN
	END
