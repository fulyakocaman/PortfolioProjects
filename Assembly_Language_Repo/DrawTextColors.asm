; Lab 6 Problem 1: Displays the same string in four different colors, using a loop. 
; Call the SetTextColor procedure from the book's link library. 
;  Any colors may be chosen, but you may find it easiest to change the foreground color. 

include Irvine32.inc

.data
mystring byte "This sentence will be displayed in four different colors.",0

.code
main proc

	mov  eax, red + (lightBlue * 16)	; red characters (foreground) on a blue background 
	mov  ecx,4				; loop repeats 4 times

L1:	
	call	SetTextColor			; calling the SetTextColor procedure
	mov	edx,OFFSET mystring		; passing the offset of the string in EDX 
	call	WriteString			; writing the string to the console window
	call	Crlf					; writing the end-of-line sequence to the console window
	add	eax,3				; adding 3 as a color constant to foreground color to change colors every time loop repeats
	loop	L1

	exit
main endp
end main