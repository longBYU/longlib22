C
C
	SUBROUTINE VCPY(V1,V2)
C
C	CREATED: DGL 1-AUG-1984
C
C	COPIES A FOUR ELEMENT VECTOR FROM V2 TO V1
C
	DIMENSION V1(4),V2(4)
	DO 10 I=1,4
		V1(I)=V2(I)
10	CONTINUE
	RETURN	
	END
