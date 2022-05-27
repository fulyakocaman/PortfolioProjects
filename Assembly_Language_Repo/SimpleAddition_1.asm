; Lab 6 Problem 3: Write a program that clears the screen, locates the cursor near the middle  
; of the screen, prompts the user for two integers, adds the integers, and displays their sum.

INCLUDE Irvine32.inc

.data
integer1 sdword ?		; since the problem said to be an integer, chose SDWORD to describe it
integer2 sdword ?
string1 byte "Please enter the first integer:    ",0
string2 byte "Please enter the second integer:   ",0
string3 byte "The sum of the two integers is:   ",0

.code
main PROC

	call GetMaxXY			; Finding out current number of rows/columns

	mov  dl,10			; x-coordinate in DL of the first integer
	mov  dh,10			; y-coordinate in DH of the first integer
	call Gotoxy			; locates the cursor at 10x10
	mov  edx,OFFSET string1	; need to pass the string1's OFFSET in EDX for Writestring  proc
	call WriteString		; writes the string1 on the console window
	call ReadInt			; ReadInt used for signed integers and returns the value in EAX
	mov  integer1,eax		; store the value in EAX to the integer1 variable

	mov  dl,10			; x-coordinate in DL of the second integer
	mov  dh,12			; y-coordinate in DH of the second integer
	call Gotoxy			; locates the cursor at 10x12
	mov  edx,OFFSET string2	; need to pass the string2's OFFSET in EDX for Writestring  proc
	call WriteString		; writes the string2 on the console window
	call ReadInt			; ReadInt used for signed integers and returns the value in EAX

	add  eax,integer1		; Adds the integer1 to the integer2 stored in EAX

	mov  dl,10			; x-coordinate in DL of the third integer
	mov  dh,14			; y-coordinate in DH of the third integer
	call Gotoxy			; locates the cursor at 10x14
	mov  edx,OFFSET string3	; need to pass the string3's OFFSET in EDX for Writestring  proc
	call WriteString		; writes the string3 on the console window
	call WriteInt			; writes the sum integer already passed in EAX on the console window
	call Crlf				; moves the cursor to the next line
	
	exit
main ENDP
END main