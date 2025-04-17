

section .data 

    NULL    equ 0
    fmt_int     db "%ld", 10, 0;
    fmt_newnode db "New node created with value: %ld", 10, 0
    fmt_print   db "List contents: ", 0
    fmt_empty   db "List is empty", 10, 0 
    fmt_del     db "Deleted Node with value: %ld", 10, 0
    fmt_notfound db "Value %ld not found in list", 10, 0

section .bss 
        head    resq    1 

section .text 
    global main 
    extern printf 
    extern malloc 
    extern free 

init_list:

    mov     qword [head], NULL 
    ret 

create_node:
    push    rdi

    mov     rdi, 16 
    call    malloc 
    
    ;rax holds pointer
    ;test rax, if malloc fail 
    test    rax, rax 
    jz      create_node_error 

    pop rdx 

    ;initialize 
    mov     [rax], rdx
    mov     [rax+8], NULL
    
    ;printf confirmation message 
    push    rax
    mov     rdi, fmt_newnode
    mov     rsi, rdx 
    xor     eax, eax 
    call    printf
    pop     rax

    ret 

create_node_error:

    pop     rdi 
    xor     rax,


insert_begining:

    push    rbx
    call    create_node
    mov     rbx, rax 
    
    mov     rcx, [head]     ;rcx = head 
    mov     [rbx+8], rcx    ;node->next = head 
    mov     [head], rbx     ;head = node 

    pop     rbx     
    ret 

insert_end:

    push    rbx
    push    r12 

    ;create new node

    call create_node
    mov     rbx, rax

    ;check if list is empty 
    mov     rcx, [head]
    test    rcx, rcx 
    jz      insert_empty 

    ;find last node 
    mov     r12 , rcx 

find_last:

    mov     rcx, [r12+8]; 
    test    rcx, rcx
    jz      found_last 
    mov     r12, rcx 
    jmp     find_last

found_last:
    mov     [r12+8], rbx 
    jmp inser_end_done 

insert_empty:

    mov     [head], rbx 

inser_end_done:
    pop     r12 
    pop     rbx
    ret


