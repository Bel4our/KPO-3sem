.586								
.model flat, stdcall				
includelib kernel32.lib				

ExitProcess PROTO : DWORD			
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD
					
.stack 4096							
					
.const								


.data								

MB_OK EQU 0

STR1 DB "Ассемблер", 0				
STR2 DB "Моя первая программа", 0	
HW   DD ?							


.code								

main PROC							
START:
		INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK	
		
push -1									
call ExitProcess						


main ENDP								

end main								
		