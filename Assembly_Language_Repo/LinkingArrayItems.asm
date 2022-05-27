; Lab 6 Problem 2: Write a program that traverses the links and locates the characters 
;in their correct sequence.  For each character you locate, copy it to a new array.

INCLUDE Irvine32.inc

.data
start dword 1
chars byte 'H','A','C','E','B','D','F','G'
links dword 0,4,5,6,2,3,7,0
myarray byte LENGTHOF links DUP(0)  ; the output array expecting A,B,C,D,E,F,G,H. 

.code
main proc
	mov esi,0					 ; points to the first element of myarray
	mov edi,start				 ; starting index in the list
	mov ecx,LENGTHOF links		 ; loop counter, will repeat as many characters as in the array
L1:
	mov al,chars[edi]			 ; getting a character into AL
	mov myarray[esi],al			 ; copying the element in AL into the output array 
	call WriteChar				 ; writing a single character on the console window
	call	Crlf
	add	esi,TYPE myarray		 ; the pointer moves up the next element in myarray.
	mov  edi,links[edi*TYPE links] ; finding next index in the list and storing it in EDI
	loop L1

	exit
main endp
end main
