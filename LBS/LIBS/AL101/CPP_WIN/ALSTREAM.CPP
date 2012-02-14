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

#define STRICT
#include <windows.h>
#include "alstream.h"

//
// _ALControlStream::sync()
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  Always 0, I think this means success.
//
// DESCRIPTION
//
//  sync() gets called at various times by the base class.  I think
//  it gets called when the streambuf is being destroyed.  I am
//  pretty sure it also gets called when you perform a seek() type
//  of operation, or a flush(), or switch from output to input.
//
//  This function writes everything in the "put buffer" out to the
//  edit control, leaving an empty buffer.  A few pointers have to
//  get cleaned up after that.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

#if !defined( AL_BUILDING_DLL )

_ALControlStream::sync()
{
    int i = out_waiting();
    if ( i != 0 && pbase() != 0 ) {
        pbase()[ i ] = '\0';
        SendMessage( hWindow,
                     EM_REPLACESEL,
                     0,
                     (LPARAM) ( (LPSTR) pbase() ) );
    }
    setp( 0, 0 );
    return 0;
}

//
// _ALControlStream::_ALControlStream( HWND hwnd, int dlg_control )
//
// ARGUMENTS:
//
//  hwnd        : The dialog box containing the multiline edit control
//
//  dlg_control : The ID for the multiline edit control.  Note that if
//                we use -1 for this parameter, the hwnd parameter refers
//                to the window handle of a standalone edit control,
//                not the dialog box.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This is the constructor for my streambuf-derived class.  It has
//  to initialize the one data member for the derived class, which is
//  the window handle for the multiline edit control.  I then calls the
//  setp() and setg() member functions, which sets up the put and
//  get pointers for the buffer.  I don't know everything about what
//  setp() and setg() do, but it looks like this is the place to call them.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

_ALControlStream::_ALControlStream( HWND hwnd,
                                    int dlg_control )
{
    if ( dlg_control == -1 )
        hWindow = hwnd;
    else
        hWindow = GetDlgItem( hwnd, (short int) dlg_control );
    setp( 0, 0 );
    setg( 0, 0, 0 );
}

//
// _ALControlStream::~_ALControlStream()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This guy doesn't have to do anything, streambuf::~streambuf()
//  will be implicitly called, and he does all the work.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

_ALControlStream::~_ALControlStream()
{
}
        
//
// int _ALControlStream::overflow( int ch )
//
//
// ARGUMENTS:
//
//  ch  : A character to be written out to the stream.
//
// RETURNS
//
//  EOF on error, otherwise 0.
//
// DESCRIPTION
//
//  overflow() is the function in streambuf that you have to provide in
//  order to implement a new class that does something useful.  This function
//  is called to output the entire batch of characters in the put buffer
//  out to the edit control, at least when the put buffer is full.  I
//  don't entirely understand it, but it seems to work.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

int _ALControlStream::overflow( int ch )
{
    if ( !base() ) {
        if ( allocate() == EOF )
            return EOF;
        setg( 0, 0, 0 );
    } else {
        if ( out_waiting() ) {
            if ( sync() == EOF )
                return EOF;
        }
    }
    int bl = blen();
    setp( base(), base() + bl - 2 );
    if ( pptr() < epptr() ) {
        *pptr() = (char) ch;
        pbump( 1 );
    } else {
        *pptr() = (char ) ch;
        pbump( 1 );
        *pptr() = '\0';
        pbump( 1 );
        SendMessage( hWindow,
                     EM_REPLACESEL,
                     0,
                     (LPARAM) ( (LPSTR) pbase() ) );
    }
    return 0;
}

//
// int _ALControlStream::underflow()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  Always EOF.
//
// DESCRIPTION
//
//  This function is called to get more characters from a physical device
//  of some sort.  Since our multiline edit control is being used for
//  output only, this function always returns an error.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

int _ALControlStream::underflow()
{
    return EOF;
}

//
// ALEditControlStream::ALEditControlStream( HWND handle, 
//                                           int control /* = -1 */ )
//
// ARGUMENTS:
//
//  handle    :  The handle of a dialog box, if the control parameter is
//               being used to pass the ID of a multiline edit control.
//               If the multiline edit control is not part of a dialog
//               box, you should pass the handle of the edit control in
//               this parameter.
//
//  control   :  The ID of a control, if this function is setting up
//               a control in a dialog box.  If not, a -1 should be
//               passed here.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This ostream object doesn't have to do much, since it depends on the
//  _ALControlStream class derived from streambuf to do all the work
//  it really needs.  The constructor only has to construct that streambuf
//  type object, using our single data member.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

ALEditControlStream::ALEditControlStream( HWND handle, 
                                          int control /* = -1 */ )
    : mpControlStream( handle, control ) , ios( &mpControlStream )
{
}

//
// ALEditControlStream::~ALEditControlStream()
//
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  The destructor calls the synch() function first, which will dump
//  any characters that were just sitting in the buffer.  It then calls
//  delbuf(), but only if we are using Microsoft.  I'm not sure about
//  that part, it is kind of mysterious, so I don't know if we need
//  to call it or not.  I hope we get more and better iostream docs
//  one of these days...
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

ALEditControlStream::~ALEditControlStream()
{
    mpControlStream.sync();
#ifdef AL_MICROSOFT
    delbuf();
#endif
}

//
// ostream& gfendl( ostream& s )
//
//
// ARGUMENTS:
//
//  s   :  A reference to an ostream object.
//
// RETURNS
//
//  A reference to the same object.
//
// DESCRIPTION
//
//  Normally, when we are going to write an end of line to a stream,
//  we just send a "\n".  But that doesn't work in the edit box, so
//  I have this special operator to send the CR/LF pair.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

ostream& gfendl( ostream& s )
{
    return s << '\r' << '\n' << flush;
}

#endif //#if !defined( AL_BUILDING_DLL )
