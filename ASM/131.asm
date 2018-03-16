global _start

section .bss
text resb 100
buffer resb 100
buf resb 1
vika resb 1
section .data
probel db 10
prob db ' '
one db '1'
two db '2'
section .text
;////////////////////////////////////
    ; FUNCTION ONE
proc1:
    push ebp
    mov ebp,esp
    mov eax,dword[ebp+8]
begin:
     cmp byte[eax+esi],'.'
     je lowexit      
     cmp byte[eax+esi],'a'
     jb low
     cmp byte[eax+esi],'z'
     ja low
     sub byte[eax+esi],32
low: inc esi
       jmp begin
lowexit:
     mov eax,4
     mov ebx,1
     mov ecx,one
     mov edx,1
     int 80h
    pop ebp
ret
;////////////////////////////////////////////////////
      ; FUNCTION TWO
proc2:
    push ebp
    mov ebp,esp
   mov ebx,dword[ebp+8]
   mov eax,dword[ebp+12]
start_1:
     cmp byte[eax+esi],'.'
     je end_1     
     cmp byte[eax+esi],'0'
     jb met_1
     cmp byte[eax+esi],'9'
     ja met_1
      mov dl,byte[eax+esi]
     mov byte[ebx+ecx],dl
      mov byte[eax+esi],''
       inc ecx
met_1: inc esi
       jmp start_1
end_1:
     xor esi,esi
start_2:
     cmp byte[eax+esi],'.'
      je end_2
     cmp byte[eax+esi],''
       je met_2
      mov dl,byte[eax+esi]
     mov byte[ebx+ecx],dl
      inc ecx
met_2: inc esi
         jmp start_2
end_2:         
     mov byte[ebx+ecx],'.'

     xor esi,esi
start_3:  cmp byte[ebx+esi],'.'
          je end_3
        mov dl,byte[ebx+esi]
        mov byte[eax+esi],dl 
      inc esi
       jmp start_3
end_3:   
     mov eax,4
     mov ebx,1
     mov ecx,two
     mov edx,1
     int 80h
  pop ebp
ret
  




_start:
;///////////////////////////////////////////////////////////
           ; SCHITIVANIE

		xor 	esi, esi 	
read:
		mov 	eax, 3	
		mov 	ebx, 0 		
		mov 	ecx, text
		add     ecx, esi
		mov 	edx, 1	
		int 	80h
		cmp eax, 0
		jb error
		cmp byte[text + esi], '.'
		je prov
		inc esi
		jmp read
prov:
 cmp esi,0
 jne readok
 jmp clear_buffer		
;/////////////////////////////////////////////////////////////		
         ;PECHATAEM IZNOCHALNIY TEKST
readok: ; ESLI NET OSHIBOK V READ
  xor esi,esi
 print_1:
    cmp byte[text+esi],'.'
    je exit_1
    mov eax,4
    mov ebx,1
    mov ecx,text
    add ecx,esi
    mov edx,1
    int 80h
    inc esi
    jmp print_1
exit_1:
;/////////////////////////////////////////////////////////////
      ;PEREVOD STROKI
    mov eax,4
    mov ebx,1
    mov ecx,probel
    mov edx,1 
    int 80h   

                  xor eax,eax
                xor ebx,ebx
;/////////////////////////////////////////////////////////////////
     ;   NACHALO PROVERKI       
     dec esi; NOMER POSLEDNEGO SIMBOLA
     mov al,byte[text+esi] 
     mov byte[vika],al; PO ADRESU "VIKA" LEGIT POSLEDNIY SIMBOL
     cmp byte[vika],'A'
     jb TWO
     cmp byte[vika],'Z'
     ja TWO
     xor esi,esi
     xor eax,eax
     mov bl,byte[vika]
start:
     cmp byte[text+esi],'.'
     je ender
     cmp byte[text+esi],bl
     jne startend
     inc eax
startend: inc esi
          jmp start
ender:
      cmp eax,1
      jne TWO
;///////////////////////////////////////////////////////////
            ;PERVAYA FUNCTION
ONE:
   pushad ; KLADEM REGISTRI V STEK
   xor esi,esi 
   mov eax,text; 
   push eax ; KLADEM V STEK 1 PARAMETR
   call proc1 ; VISIVAEM 1 FUNCTION
   add esp,4
   popad ; DOSTAYOM REGISTRI IZ STEKA
     jmp print_2
;///////////////////////////////////////////////////////////
            ;VTORAYA FUNCTION
TWO: 
    pushad  ; KLADEM REGISTRI V STEK
    mov eax,text
    mov ebx,buffer
    xor esi,esi 
    xor ecx,ecx 
    push eax ; KLADEM 1 PARAMETR
    push ebx ; KLADEM 2 PARAMETR
    call proc2 ; VISIVAEM 2 FUNCTION
    add esp,8
    popad ; DOSTAYOM REGISTRI IZ STEKA
;///////////////////////////////////////////////////////////
            ;PECHATAEM 1 PROBEL I PEREVOD STROKI    
print_2: 	
       xor esi,esi
          mov eax,4
          mov ebx,1
          mov ecx,probel
          mov edx,1
          int 80h
        xor esi,esi
;//////////////////////////////////////////////////////////
            ;PECHATAEM TEXT
 print_3:
	cmp byte[text+esi],'.'
	je exit_3
		mov eax, 4		
		mov ebx, 1		
		mov ecx, text
		add ecx, esi
		mov edx, 1
		int 80h
		inc esi
		
		jmp print_3
exit_3:                
		
		;PECHATAEM PEREVOD STROKI
		mov eax, 4		
		mov ebx, 1		
		mov ecx, probel ; PEREVOD STROKI
		mov edx, 1		
		int 80h
		
		; OTCHISHAEM BUFFER
clear_buffer: 
		mov eax, 3
		mov ebx, 0
		mov ecx, buf
		mov edx, 1
		int 80h
		cmp byte[ecx], 10
		jne clear_buffer
		
		
		mov eax, 1
		mov ebx, 0
		int 80h

            ; ESLI BILA OSHIBKA
error:
		mov eax, 1
		mov ebx, 1
		int 80h
