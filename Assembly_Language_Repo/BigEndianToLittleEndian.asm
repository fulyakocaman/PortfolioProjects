; Lab 4 Problem 1: Copy the value from bigEndian to littleEndian, reversing the order of the bytes

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
bigEndian byte 12h,34h,56h,78h
littleEndian dword ?

.code
main proc
	mov  ah,byte ptr [bigEndian]				; AH = 12h
	mov  al,byte ptr [bigEndian+1]			; AL = 34h
	mov  word ptr [littleEndian+2],ax			; AX = 1234h assigned to the most significant word
	mov  ah,byte ptr [bigEndian+2]			; AH = 56h
	mov  al,byte ptr [bigEndian+3]			; AL = 78h	
	mov  word ptr [littleEndian],ax			; AX = 5678h assigned to the least significant word
	mov eax,dword ptr littleEndian			; EAX = 12345678h  littleEndian form od a double word


	invoke ExitProcess,0
main endp
end main