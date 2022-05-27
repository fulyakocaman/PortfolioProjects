; Final Project #2
; College Registration: Using the College Registration example from Section 6.7.3 as a starting point, do 
; the following:
; • Recode the logic using CMP and conditional jump instructions (instead of the .IF and .ELSEIF directives).
; • Perform range checking on the credits value; it cannot be less than 1 or greater than 30. If an
; invalid entry is discovered, display an appropriate error message.
; • Prompt the user for the grade average and credits values.
; • Display a message that shows the outcome of the evaluation, such as “The student can register”
; or “The student cannot register”.
; (The Irvine32 library is required for this solution program.

INCLUDE Irvine32.inc

.data
TRUE  = 1
FALSE = 0
gradeAverage  DWORD ?
credits       DWORD ?
OkToRegister  DWORD ?

string1 BYTE "Enter your grade average ranging from 0 to 400, including 400: ",0
string2 BYTE "Enter the number of credits you want to take: ",0
string3 BYTE "The student can register",0
string4 BYTE "The student cannot register",0
errormsg BYTE "Error: Credits cannot be less than 1 or greater than 30!",0

.code
main PROC
	
	mov	edx,OFFSET string1	
	call	WriteString		; prompts the user for the grade average 
	call	ReadDec			; reads the grade average
	mov	gradeAverage,eax	; stores in the gradeAverage variable
	call	Crlf				; moves the cursor to the next line

	mov	edx,OFFSET string2 
	call	WriteString		; prompts the user for the credits values
	call	ReadDec			; reads the number of credits
	mov	credits,eax		; stores in the credits variable
	call	Crlf				; moves the cursor to the next line


	mov	OkToRegister,FALSE	; sets to False according to question

	; performs range checking on the credits value
	cmp	credits,1				
	jb	Error				; jump to Error if credits < 1
	cmp	credits,30			
	ja	Error				; jump to Error if credits > 30
	jmp	L1					; if credits check, jump to register check

Error:	
	mov	edx,OFFSET errormsg
	call	WriteString			; displays the error message on the console window
	call	Crlf					; moves the cursor to the next line
	jmp L5					; exit the IF statement

; performs register check 
;.IF gradeAverage > 350
L1:	
	cmp gradeAverage,350		
	ja	L4					; jumps if above > 350
	jmp	L2					; if not, jump to L2

;.ELSEIF (gradeAverage > 250) && (credits <= 16)
L2:	
	cmp gradeAverage,250		
	jna	L3					; jump if not above  > 250
	cmp	credits,16			
	jnbe	L3					; and jump if not <= 16
	jmp L4					; jump to L4 if (gradeAverage > 250) && (credits <= 16) is true

;.ELSEIF (credits <= 12)
L3:	
	cmp credits,12				
	jbe	L4					; jump if credits <= 12
	jmp L5					; if not, jump to L5 to exit the IF statement

L4:	
	mov	OkToRegister,TRUE		; assigns true to register
	mov   edx,offset string3		
	call  WriteString			; displays can register message
	call Crlf					; moves the cursor to the next line

L5:
	; handles cannot register message
	cmp   OkToRegister,FALSE
	je   cannotRegister			; jump to cannotRegister if OkToRegister = False
	jmp   quit				; exit the IF statement

cannotRegister:
	mov   edx,offset string4		
	call  WriteString			; displays cannot register message
	call Crlf					; moves the cursor to the next line

quit:						

	exit
main ENDP
END main
