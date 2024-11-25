.586
.MODEL flat, stdcall
includelib kernel32.lib
includelib user32.lib

ExitProcess PROTO :DWORD
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD

.STACK 4096

.CONST

.DATA
fNumb db 5
sNumb db 3

str1 db "Результат сложения  ", 0
str2 db "Сложение", 0

.CODE

main PROC

    mov al, fNumb            
    add al, sNumb            
    add al, 30h              
    mov str1+19, al           

    invoke MessageBoxA, 0, offset str1, offset str2, 0 

    push 0                    
    call ExitProcess          

main ENDP
end main
