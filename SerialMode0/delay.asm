	PUBLIC	_DELAY
	DE	SEGMENT CODE
	RSEG	DE
_DELAY:	MOV	R0, #60
	MOV	R1, #250
DEL2:	DJNZ	R0, DEL2
DEL3:	DJNZ	R1, DEL3
	DJNZ	R7, _DELAY
	RET
	END