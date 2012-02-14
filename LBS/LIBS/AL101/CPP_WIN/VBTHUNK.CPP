/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include "arclib.h"
#pragma hdrstop


//
// extern "C" long ALCreateVBString( char *string, unsigned short int l )
//
// ARGUMENTS:
//
//  string  : A standard C string that is going to be returned to
//            a Visual Basic calling routine.
//
//  l       : The length of the string.  Admittedly, it would be
//            pretty easy to figure that out here, but this routine
//            is replacing an assembly routine that didn't know
//            how to do it.
//
// RETURNS
//
//  A Visual Basic string thingy.  I'm not even sure what it is, a pointer,
//  a handle, and index or what.  VB knows.
//
// DESCRIPTION
//
//  If you poke around inside Microsoft's VB CDK, you will see that the
//  actual code to create a VB string can be replaced by a function
//  that does this:
//
//       mov  bx,50
//       jmp  dword ptr ss:[20]
//
//  Originally, ArchiveLib created VB strings using an assembly language
//  routine that looked just like this.  However, I didn't want everyone
//  to have to pay the price of having an assembler just to support two
//  lines of code.
//
//  Replacing this with in line assembly looked doable.  The big problem
//  is that the VB routine located at ss:[20] expects the stack to
//  be in just the right configuration when you call it, and that isn't
//  always easy to accomplish in the middle of a C routine.  What makes
//  it really difficult is that the VB guy is going to return by way of
//  a far return.
//
//  Writing the assembly code to accomplish this wasn't so bad.  Using
//  Microsoft's inline assembly it was fairly easy to make it happen. 
//  Unfortunately, Borland's assembler couldn't handle calls to local
//  labels, and Symantec's couldn't handle calls or jumps to local labels.
//  In both cases, you could work around this by inserting the correct
//  bytes.
//
//  This was nothing compared to Watcom.  They don't even support in
//  line assembly.  When I asked them about this, one of their developers
//  got real snotty and pointed out that the C++ spec only requires that 
//  the asm statements pass through the compiler without generating
//  any errors, they don't actually have to do anything.  That attitude
//  might explain Watcom's current position in the C++ market.
//
//  Anyway, to make Watcom work you have to create this strange pragma,
//  which I did, out of the goodness of my heart.  It would have been
// more satisfying to just not support them.
//
//  
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

//
// Note that we only create this code for Win16 DLLs, nobody else
// supports VB.  Some day I suppose the Win32s DLL will, but we
// haven't seen the specs on that yet.
//

#if defined( AL_VB )

//
// If watcom, we do it this way, everyone else is different.
//
#if defined( AL_WATCOM )

long call_vb( unsigned short int, unsigned short int, unsigned short int );
#pragma aux call_vb =  \
    0x0cc \        
    "push ax"                           \
    "push bx"                           \
    "push cx"                           \
    "mov bx,50h"                        \
    "push cs"                           \
    0x0e8 0x02 0x00                     \
    0x0eb 0x05                          \
    0x36 0x0ff 0x2e 0x20 0x00           \
    parm [ax] [bx] [cx]                 \
    modify [ax bx cx dx si di]

extern "C" long _far _pascal ALCreateVBString( char *string, unsigned short int l )
{
    long result =
            call_vb( (unsigned short int) (((long) string ) >> 16 ),
                    (unsigned short int) (((long) string) & 0xffff),
                    l );
    return result;
}

#else // #if defined( AL_WATCOM )

//
// I think this here just to make some error messages go away.
//
#if defined( AL_MICROSOFT )
#pragma optimize( "", off )
#endif

extern "C" long _far _pascal ALCreateVBString( const char _far *string, unsigned short int l )
{
    unsigned short int string_seg = (unsigned short int) (((long) string ) >> 16 );
    unsigned short int string_off = (unsigned short int) (((long) string) & 0xffff);
    unsigned short int result_seg;
    unsigned short int result_off;
//
// The VB routine we jump to is going to return to me with a far call,
// so after setting the arguments up on the stack, I do a push CS before
// a local call.  At that point the stack is set up perfectly, and I
// can jump to the VB guy.
//
    _asm {
         push  string_seg;
         push  string_off;
         push  l;
         mov   bx, 0x50;
         push  cs      //This makes my near call look like a far call
//
//  What you see next is three different ways of making the same
//  four lines of ASM code work.
//
#if defined( AL_SYMANTEC )
         db 0e8H
         db 02H
         db 00H
         db 0ebh
         db 05H
         db 36H
         db 0ffH
         db 2eH
         db 20H
         db 00H
#elif defined( AL_BORLAND )
         db 0x0e8, 0x02, 0x00;
         db 0xeb, 0x05;
         jmp dword ptr ss:[0x20];
#else
         call  do_vb
         jmp done
do_vb:   jmp dword ptr ss:[0x20];
done:
#endif
         mov result_seg, dx;
         mov result_off, ax;
    }
    return ( (long) result_seg << 16 ) + result_off;
}

#endif // #if defined( AL_WATCOM )

#endif // #if defined( AL_VB )
