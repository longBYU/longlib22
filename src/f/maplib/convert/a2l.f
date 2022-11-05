C
C *** LAST REVISED ON 28-OCT-1994 08:03:45.98
C *** SOURCE FILE: [LONGD.GRAPHICS]L2.FOR
C
 	INTEGER*4 ALLSAM(481)
	SAVE
cc	INCLUDE 'files.inc'
c	character*80 earth, landsea
c	data earth/'longloc:earth.dat'/
c	data landsea/'longloc:lndsea1.dat'/
C
	open(unit=2,file='F.DAT',form='formatted',status='old')
C
	OPEN(UNIT=1,FILE='L.DAT',form='unformatted',recl=1924,
     &	 ACCESS='DIRECT',STATUS='NEW')

C
	do irec=1,648
		read (2,*) irec1,(allsam(j),j=1,481)
                write (*,*) irec,irec1
		write(1,REC=IREC,ERR=99) ALLSAM
	end do
	stop
C
99	WRITE(*,45)
45	FORMAT(' *** ERROR writing L.DAT FILE ***')
	stop
	END
