/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o 
t�tulo "LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef _ALSTREAM_H
#define _ALSTREAM_H

#define STRICT
#include <windows.h>
#include "arclib.h"

#if defined( __cplusplus )

/* Won't work in a DLL! */

#if !defined( AL_BUILDING_DLL )

#include <iostream.h>

/*
 * class _ALControlStream 
 *
 * DESCRIPTION
 *
 *  This is a class derived from streambuf.  We attach this to an
 *  ALEditControlStream, and it will write to the edit control
 *  specified in the constructor.
 *
 * DATA MEMBERS
 *
 *  hWindow   : The handle of the edit control.
 *
 * MEMBER FUNCTIONS
 *
 *  _ALControlStream()  : The constructor, called by the ALEditControlStream
 *                        constructor.
 *
 *  ~_ALControlStream() : The virtual destructor.
 *
 *  overflow()          : Called by the base class when the buffer is about
 *                        to overflow.  This is our cue to send bytes out
 *                        to the edit control.
 *
 *  underflow()         : Called by the base class when the more data is
 *                        needed by the buffer for reading. We don't
 *                        supply any data, this is a stub.
 *
 *  sync()              : Base class calls this when it feels like flushing
 *                        the buffers.
 *
 * REVISION HISTORY
 *
 *  May 26, 1994  1.0A  : First release
 *
 */

class _ALControlStream : public streambuf {
/*
 * Constructors, destructors, friend declarations
 */
    friend class ALEditControlStream;

    public :
        _ALControlStream( HWND hwnd, int control );
        virtual ~_ALControlStream();
/*
 * The copy constructor and assignment operator are not supported.  I
 * declare them here because I don't want the compiler to generate
 * default versions for me.
 */
    protected :
        operator=( _ALControlStream& );
        _ALControlStream( _ALControlStream& );
/*
 * Member functions and overloaded operators
 */
    protected :
        virtual int overflow( int );
        virtual int underflow();
        virtual int sync();
/*
 * Data members
 */
    protected :
        HWND hWindow;
};

/*
 * class ALEditControlStream 
 *
 * DESCRIPTION
 *
 *  This is the demo class that actually performs output to the 
 *  edit control.  It doesn't really have to do anything other than 
 *  create itself and then create the streambuf derivative, because
 *  the streambuf does al the work.
 *
 * DATA MEMBERS
 *
 *  mpControlStream  :  A pointer to the streambuf object we create,
 *                      because without him I am nothing.
 *
 * MEMBER FUNCTIONS
 *
 *  ALEditControlStream()   : The constructor.
 *  ~ALEditControlStream()  : The destructor.
 *  
 *
 * REVISION HISTORY
 *
 *  May 26, 1994  1.0A  : First release
 *
 */

class ALEditControlStream : public ostream
{
/*
 * Constructors, destructors, and friends
 */
    public :
        ALEditControlStream( HWND handle, int control_id = -1 );
        ~ALEditControlStream();
/*
 * The copy constructor and assignment operator are not supported.  I
 * declare them here because I don't want the compiler to generate
 * default versions for me.
 */
    protected :
        operator=( ALEditControlStream& );
        ALEditControlStream( ALEditControlStream& );
/*
 * Data members
 */
        _ALControlStream mpControlStream;
};

/*
 * The gfendl manipulator is used to send an eol and flush the buffer
 * when writing to an ALEditControlStream.  It serves the same purpose
 * as an endl written to a normal stream.  The difference is that an
 * eol on a regular stream has a "/n/r" pair, and this guy doesn't.
 */
ostream& gfendl( ostream &s );

#endif /* #if !defined( AL_BUILDING_DLL ) */

#endif /* #if defined( __cplusplus )      */

#endif /* #ifdef _ALSTREAM_H */
