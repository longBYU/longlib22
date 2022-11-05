C
C *** LAST REVISED ON 28-OCT-1994 08:03:45.98
C *** SOURCE FILE: [LONGD.GRAPHICS]L2A.FOR
C
 	INTEGER*4 ALLSAM(481)
c	character*80 earth, landsea
c	data earth/'longloc:earth.dat'/
c	data landsea/'longloc:lndsea1.dat'/
C
	open(unit=2,file='F.DAT',form='formatted',status='new')
C
	OPEN(UNIT=1,FILE='L.DAT',form='unformatted',recl=1924,
     &	 ACCESS='DIRECT',STATUS='old')

C
	do irec=1,648
		read (1,REC=IREC,ERR=99) ALLSAM
		write (2,*) irec1,(allsam(j),j=1,481)
                type *,irec,irec1
	end do
	stop
C
99	WRITE(*,45)
45	FORMAT(' *** ERROR writing output FILE ***')
	stop
	END
