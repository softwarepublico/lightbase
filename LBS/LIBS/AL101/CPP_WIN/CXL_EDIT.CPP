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

#include <stdarg.h>
#include <stdio.h>

#include "al.h"
#include "alcxl.h"

//
// extern "C" void EditDisplay( HWND hDlg,
//                              int id,
//                              char AL_DLL_FAR *fmt,
//                              ... )
//
// ARGUMENTS:
//
//  hDlg   :  This is the handle of the dialog box containing the edit
//            control.  If the second parameter, id, is set to -1, it
//            means this parameter is the handle of the edit control.
//
//  id     :  The id of the multiline edit control in a dialog box.  If
//            set to -1, it means the edit control is not in a dialog box,
//            and the hDlg parameter is the handle of the edit control.
//
//  fmt    :  The format parameter to be used in wsprintf.
//
//  ...    :  Any additional arguments that are going to be used by
//            wvsprintf().
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This little function lets you use s printf() style command to print
//  data to a multiline edit control.  The internal buffer is only 128
//  bytes, so please be careful.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

extern "C" void AL_CFUNCTION EditDisplay( HWND hDlg,
                                          int id,
                                          char AL_DLL_FAR *fmt,
                                          ... )
{
    char buffer[ 128 ];
    HWND window;
    va_list args;

    va_start( args, fmt );
//
// Watcom does this differently than everyone else.  It isn't really
// part of the ANSI spec, so we can't complain.
//
#if !defined( AL_WATCOM ) 
    wvsprintf( buffer, fmt, args );
#else
    wvsprintf( buffer, fmt, *args );
#endif
    va_end( args );
    if ( id == -1 )
        window = hDlg;
    else
        window = GetDlgItem( hDlg, (short int) id );
    SendMessage( window,
                 EM_REPLACESEL,
                 0,
                 (LPARAM) ( (LPSTR) buffer ) );
}

