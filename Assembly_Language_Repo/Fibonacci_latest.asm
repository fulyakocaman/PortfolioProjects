; Lab 5 Problem 1: Calculate the first seven Fibonacci number sequence.

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
array DWORD 7 DUP(0)
; 1, 1, 2, 3, 5, 8, 13
.code
main proc
	
	mov  ebx,1				; store the first Fibonacci number, Fib(1) = 1 given
	mov  array,ebx				; store the first Fibonacci number into the array 
	mov  edx,1				; store the second Fibonacci number, Fib(2) = 1 given
	mov  [array + 4],edx		; store the second Fibonacci number into the array
	mov  eax,1				; store 1 into eax to use in the loop for the second previous number for the Fibonacci sum

	mov  ecx,5				; loop counter, will repeat 5 times because the first two Fibonacci numbers are given as 1 
	mov  esi,4				; array index for a double word array starting with the third Fibonacci number
   
L1:
	mov	 edx,eax				; updating edx with eax to become Fib(n – 2), second previous number
	add	 edx,ebx				; edx now becomes Fib(n – 1) + Fib(n – 2), edx stores the Fibonacci numbers
	mov  [array + esi + 4],edx	; store the Fibonacci number, Fib(n) into the array starting with the third number
	mov	 eax,ebx				; updating eax with ebx so that eax will always be the second previous number
	mov	 ebx,edx				; updating ebx, becoming Fib(n – 1) so that ebx will always be the first previous number
	add	 esi,4				; moving up by 4 for the next double word index 
	Loop  L1

	; checking whether Fibonacci array stores numbers correctly
	mov	 edi,OFFSET array
	mov	 ebx,[edi]
	
	mov ebx,[edi]				
	mov ebx,[edi+4]			
	mov ebx,[edi+8]			
	mov ebx,[edi+12]				
	mov ebx,[edi+16]			
	mov ebx,[edi+20]			
	mov ebx,[edi+24]


	invoke	ExitProcess,0
main endp
end main