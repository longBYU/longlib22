	SUBROUTINE RMTEXT(ICHAN,ICOL,IX,IY,ISS,TEXT,ILEN,IERR)
	character*(*) TEXT	! PREVIOUSLY "BYTE"
	CALL RMTEXT_(ICHAN,ICOL,IX,IY,ISS,TEXT,ILEN,IERR)
	RETURN
	END
