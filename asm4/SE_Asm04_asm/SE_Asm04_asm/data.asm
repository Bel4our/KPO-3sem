.586
.model flat, stdcall
includelib kernel32.lib

ExitProcess PROTO :DWORD
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD

.STACK 4096

.DATA
MB_OK db 0
HW db ?
str1 db 356 dup(32), 0
str2 db 'Окно', 0
char0 db 'A', 0

number1 dd 246

char2 db 'B', 0

number3 dd 132523

char4 db 'C', 0

number5 dd 543521

.CODE
main PROC
mov esi, 0
mov al, char0
mov [str1 + esi], al
inc esi

push esi
mov eax, number1
call WriteNumber
pop esi
add esi, eax

mov al, char2
mov [str1 + esi], al
inc esi

push esi
mov eax, number3
call WriteNumber
pop esi
add esi, eax

mov al, char4
mov [str1 + esi], al
inc esi

push esi
mov eax, number5
call WriteNumber
pop esi
add esi, eax

mov byte ptr [str1 + esi], 0
Invoke MessageBoxA, 0, offset str1, offset str2, MB_OK
push 0
call ExitProcess
main ENDP
WriteNumber PROC
push edx
push ecx
push ebx
mov ecx, 10
lea edi, [esp - 16]
mov ebx, edi

reverse_digits:
xor edx, edx
div ecx
add dl, '0'
mov [edi], dl
inc edi
test eax, eax
jnz reverse_digits
mov eax, edi
sub eax, ebx
dec edi

write_digits:
mov dl, [edi]
mov [str1 + esi], dl
inc esi
dec edi
cmp edi, ebx
jge write_digits
pop ebx
pop ecx
pop edx
ret
WriteNumber ENDP
end main
