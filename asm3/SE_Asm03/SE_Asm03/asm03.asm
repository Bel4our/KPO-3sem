.586
.model flat, stdcall

includelib kernel32.lib
includelib user32.lib

ExitProcess PROTO : DWORD			
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD

.stack 4096

.const

.data

str1 BYTE "Семёнов Даниил Вячеславович 2 курс 8 группа",0
str2 BYTE "true",0
str3 BYTE "false",0

myBytes BYTE 10h, 20h, 30h, 40h
myWords WORD 8Ah, 3Bh, 5Fh, 99h
myDoubles DWORD 1, 2, 3, 4, 5, 6
myPointer DWORD myDoubles

mass DWORD 1, 2, 3, 4, 0, 6, 7

.code

main PROC

mov ESI, 0
mov EAX, myDoubles[ESI + 4]
mov EDX, [myDoubles + ESI]



mov EAX, 0
mov ECX, 7
CYCLE:
	add eax, mass[ESI]
	add ESI, 4

	loop CYCLE


mov ECX, 7
mov ESI, 0

CHECKZERO:
	cmp mass[ESI],0 
	je HAVEZERO
	add ESI, 4

	loop CHECKZERO

	mov EBX, 1
	jmp HAVENTZERO


HAVEZERO:
mov EBX, 0
	INVOKE MessageBoxA, 0, OFFSET str2, OFFSET str1, 1
	jmp ENDPROGRAM

HAVENTZERO:
	INVOKE MessageBoxA, 0, OFFSET str3, OFFSET str1, 1
	jmp ENDPROGRAM

ENDPROGRAM:
    push 0
    call ExitProcess

main ENDP
end main

