; Final Project #4
; Convert C-code to Assembly 
; #inlcude <stdio.h>
; void main() 
; { int n, i, sum=0;
;	printf("]nEnter an integer number: ");
;	scanf("%d", &n);
;	for (i=1; i<n; i++)
;		sum=sum+i;
;	printf("\n Sum %d=%d", n, sum)'
;  }

INCLUDE Irvine32.inc

.data

i dword 1
n dword ?	
sum dword 0

string1 byte "Enter an integer number: ",0
string2 byte "Sum ",0
string3 byte " = ",0

.code
main PROC

	mov  edx,OFFSET string1	
	call WriteString		; printf("Enter an integer number:"); 
	call ReadDec			; scanf("%d", &n); reads the n and returns the number of n in EAX	
	call Crlf				; moves the cursor to the next line

  .WHILE i <= eax			; for (i = 1; i <=n; i++)
	inc i				; i++
	inc sum				; sum = sum +1; 
  .ENDW 	
	
	mov ebx,sum			; stores the sum in EBX

	mov  edx,OFFSET string2	
	call WriteString		; writes the left side of the equation from printf("\nSum %d = %d",n,sum);
	call WriteDec			; writes the n from EAX
	
	mov  edx,OFFSET string3	
	call WriteString		; writes the equal sign from printf("\nSum %d = %d",n,sum);
	mov eax,ebx			; stores the sum from EBX back to EAX
	call WriteDec			; writes the sum from EAX
	call Crlf				; moves the cursor to the next line
	
	exit
main ENDP
END main
