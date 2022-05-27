; Lab 4 Problem 4: Copy all the elements from an unsigned Word (16bit) array into an unsigned doubleword (32-bit) array using a loop

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
arrayW word 1000h,2000h,3000h,4000h
arrayD dword LENGTHOF arrayW	DUP(?)

.code
main proc
	mov esi,0				 ; beginning of array
	mov ecx,LENGTHOF arrayW	 ; initialize loop counter with the number of elements in the arrayW 
	mov edi,0				 ; new double array, initialized to 0

L1:
	movzx  eax,arrayW[esi]	; using movzx in order to copy smaller arrayW to arrayD and extending 16 bits to 32 bits with zeros
	mov  arrayD[edi],eax	; moving the element in the arrayW to the arrayD
	add  esi,TYPE arrayW	; point to the next number in the arrayW
	add  edi,TYPE arrayD	; point to the next number in the arrayD
	loop L1				; repeat until ECX = 0

	; To see whether the elements are copied correctly into the arrayD
	mov edi,OFFSET arrayD 
	mov ebx,[edi]				;EBX = 00001000h
	mov ebx,[edi+4]			;EBX = 00002000h
	mov ebx,[edi+8]			;EBX = 00003000h
	mov ebx,[edi+12]			;EBX = 00004000h



	invoke ExitProcess,0
main endp
end main