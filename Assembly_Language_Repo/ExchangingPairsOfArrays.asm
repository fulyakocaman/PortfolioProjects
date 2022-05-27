; Lab 4 Problem 2:  Exchange every pair of values in an array with an even number of elements using a loop and indexed addressing 

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
array WORD 1,2,3,4,5,6,7,8

.code
main PROC
	; the index register initialized to zero before accessing the first array element
	mov	esi,0					; beginning of array
	mov	ecx,LENGTHOF array / 2		; need the loop to repeat half of total size

L1:	; the loop exchanges every pair of values in an array
	
	mov  ax,array[esi]
	xchg ax,array[esi+2]
	mov	array[esi],ax
	
	add	esi,TYPE array*2			; pointer moves to the next pair of values in an array 
	loop	L1
mov esi,OFFSET array   ; To see whether elements in the array are exchanged
mov ax,[esi]					;EAX = 2
mov ax,[esi+2]					;EAX = 1
mov ax,[esi+4]					;EAX = 4
mov ax,[esi+6]					;EAX = 3
mov ax,[esi+8]					;EAX = 6
mov ax,[esi+10]				;EAX = 5
mov ax,[esi+12]				;EAX = 8
mov ax,[esi+14]				;EAX = 7


	invoke	ExitProcess,0
main endp
end main