;Lab 5 Problem 3: Write a program with a loop and indirect addressing that copies a string from source to target, reversing the character order in the process.

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
source  BYTE  "This is the source string",0
target  BYTE  SIZEOF source DUP('#')

.code
main PROC

	mov  esi,OFFSET target - 2    ; Point ESI to the last character in the source string
	mov  edi,OFFSET target		; Point EDI to the  beginning of the target string
	mov  ecx,SIZEOF source - 1	; loop counter, will repeat 25 because could not copy the null terminator byte from the end of the string to the begining of the string
	
L1:	
	mov  al,[esi]				; get a character from source
	mov  [edi],al				; store it in the target
	dec  esi					; move down to next character by decreasing the index of last element 
	inc  edi					; move up to next character by increasing the index of first element 
	loop L1					

	mov	BYTE PTR [edi],0		; Now, adding a null byte to the  beginning of target string 

	; To see whether characters are stores in the target correctly. Checked upto the second word "source"
	mov  edi,OFFSET target	

	mov al,[edi]			;AL = 'g'
	mov al,[edi+1]			;AL = 'n'
	mov al,[edi+2]			;AL = 'i'
	mov al,[edi+3]			;AL = 'r'
	mov al,[edi+4]			;AL = 't'
	mov al,[edi+5]			;AL = 's'
	mov al,[edi+6]			;AL = ''
	mov al,[edi+7]			;AL = 'e'

	Invoke ExitProcess,0
main ENDP
END main