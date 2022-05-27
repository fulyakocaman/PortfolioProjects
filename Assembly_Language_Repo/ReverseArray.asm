; Lab 5 Problem 2: Use a loop with INDEXED ADDRESSING to reverse the elements of an integer array in place

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
array DWORD 1000h, 2000h, 3000h, 4000h, 5000h, 6000h
; becomes 6000h,5000h,4000h,3000h,2000h,1000h

.code
main PROC
	
	mov	esi,0						; first pointer points to the first element of array
	mov	edi,SIZEOF array - TYPE array		; second pointer points to the last element of array, to get the index of the last element we need to use sizeof (lengthof x size) minus the size since the index of the last element would be like n-1. This would make the program as flexible as possible if the array size should be changed in the future 
	mov	ecx,LENGTHOF array / 2			; loop counter, will repeat (N / 2) times since we are exchanging the corresponding elements from both ends
	
L1:
	; exchange array[esi] with array[edi], using indexed addressing.
	
	mov  eax,array[esi]		;copying the first element into EAX
	xchg eax,array[edi]		;exchanging the EAX with the corresponding end element
	mov	array[esi],eax		;copying the value in EAX to the first array position
	
	add	esi,TYPE array			; first pointer moves up forward to the next index. Used TYPE instead of just 4 because it would make the program as flexible as possible if the array type should be changed in the future 
	sub	edi,TYPE array			; second pointer moves down backwards to the next index. Used TYPE instead of just 4 because it would make the program as flexible as possible if the array type should be changed in the future 
	loop	L1
	
	; To see whether elements in the array are exchanged
	mov	 esi,OFFSET array

	mov eax,[esi]				;EAX = 6000h
	mov eax,[esi+4]			;EAX = 5000h
	mov eax,[esi+8]			;EAX = 4000h
	mov eax,[esi+12]			;EAX = 3000h
	mov eax,[esi+16]			;EAX = 2000h
	mov eax,[esi+20]			;EAX = 1000h

	invoke	ExitProcess,0
main endp
end main