; Lab 4 Problem 3: Calculates the sum of all the gaps between successive array elements using a loop and indexed addressing

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
arrayD dword  0,2,5,9,10

.code
main proc
	mov esi,0				; beginning of array
	mov ecx,LENGTHOF arrayD	; initialize loop counter with the number of elements in the array 
	sub ecx,1				; repeating the loop as the number of gaps that is one less than the number of elements in the array 
	mov ebx,0				; accumulate the sum, initilized to 0

L1:
	mov  eax,arrayD[esi+4]	; get the second number
	sub  eax,arrayD[esi]		; subtract the first number from the second number
	add  ebx,eax			; add the difference to the sum
	add  esi,TYPE arrayD	; point to the next integer
	loop L1				; repeat until ECX = 0

	invoke ExitProcess,0
main endp
end main