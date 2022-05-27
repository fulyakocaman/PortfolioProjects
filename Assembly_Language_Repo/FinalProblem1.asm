; Final Project #1
; Write assembly programs with the following I/O
; ----------------------7-11 Convenient Store ----------------------
; Drinks
; Soda(S)…………………………………………….…$2
; Water (W)…………………………………………….$1
; Sandwiches
; 10 inches……………………………………………..$3
; 12 inches……………………………………………..$5

INCLUDE Irvine32.inc

.data
counter dword ?
soda byte 'S'
ten dword 10
drinks dword ?	
sandwiches dword ?

greetings byte "----------------------7-11 Convenient Store ----------------------",0dh, 0ah, 0dh, 0ah,
		     "Drinks",0dh, 0ah,
		     "  Soda(S)-------------------------------------------------------$2",0dh, 0ah,
		     "  Water(W)------------------------------------------------------$1",0dh, 0ah,0dh, 0ah,
		     "Sandwiches",0dh, 0ah, 
		     "  10 inches-----------------------------------------------------$3",0dh, 0ah,
		     "  12 inches-----------------------------------------------------$5",0
string1 byte "Enter the number of customers:  ",0
string2 byte "  How many drinks?  ",0
string3 byte "     What kind of drink(S=Soda, W=Water)?  ",0
string4 byte "  How many Sandwiches?  ",0
string5 byte "     What size of sandwich (10/12 inches)?  ",0
string6 byte "          Your total bill = $",0

.code
main PROC

	mov  edx,OFFSET greetings	
	call WriteString		; writes the greetings on the console window
	call Crlf				; moves the cursor to the next line
	call Crlf	
	
	mov  edx,OFFSET string1	
	call WriteString		; asks for the number of customers on the console window
	call ReadDec			; reads the number of customers in EAX
	mov counter,eax		; stores in the counter variable	

  .WHILE counter > 0		; repeat until the counter > 0
  dec counter				; decrease counter by 1 for each loop
	mov  edx,OFFSET string2	
	call WriteString		; asks for the number of drinks on the console window
	call ReadDec			; reads the number of drinks
	mov  drinks,eax		 ; stores in the drinks variable	
	
	mov  edx,OFFSET string3	
	call WriteString		; asks for kind of drink(S=Soda, W=Water) on the console window
	call ReadChar			; reads the character in AL

	.IF al == soda
		mov ebx,2
	.ELSE 
		mov ebx,1
	.ENDIF

	mov eax,drinks
	mul ebx
	mov  drinks,eax		; the cost of the drinks
	call Crlf

	mov  edx,OFFSET string4	
	call WriteString		; asks for the number of sandwiches on the console window
	call ReadDec			; reads the number of sandwiches	
	mov  sandwiches,eax	; stores in the sandwiches variable

	mov  edx,OFFSET string5	
	call WriteString		; asks for the size of sandwich (10/12 inches) 
	call ReadDec			; reads the character in AL
	.IF eax == ten
		mov ebx,3
	.ELSE 
		mov ebx,5
	.ENDIF

	mov eax,sandwiches
	mul ebx
	mov  sandwiches,eax		; the cost of the sandwiches

	add  eax,drinks		;  adds the cost of sandwiches and drinks and stores in EAX

	mov  edx,OFFSET string6	
	call WriteString		; writes the total bill on the console window
	call WriteDec			; writes the sum value already passed in EAX 
	call Crlf				; moves the cursor to the next line
	call Crlf	
  .ENDW 					; end of while loop

	exit
main ENDP
END main
