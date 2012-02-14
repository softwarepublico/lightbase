        DOSSEG
        .MODEL SMALL
        .STACK 100h
        .DATA
Message DB      13,10
        DB      'This program requires Microsoft Windows.'
        DB      13,10
        DB      'Thank you for choosing Greenleaf.'
        DB      13,10,'$'

        .CODE
        mov     ax,@Data
        mov     ds,ax
        mov     ah,9
        mov     dx,offset Message
        int     21h
        mov     ah,4ch
        int     21h
        END
