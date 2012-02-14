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


#include "arclib.h"
#pragma hdrstop

#include "al.h"
#include "alcxl.h"

// C TRANSLATION FUNCTION
//
// extern "C" char * StripFileName( char *filename )
//
// VB TRANSLATION FUNCTION
//
// extern "C" long StripFileNameVB( char *filename )
//
// ARGUMENTS:
//
//  filename  :  An ordinary VB or C string that contains a file name.
//
// RETURNS
//
//  Either a C or VB string type, containing just the path.  Note that
//  the C version of the function copies over your existing string,
//  whereas the VB version creates a new VB string.
//
// DESCRIPTION
//
//  This function takes a file name, and strips off any filename and
//  extension, leaving the drive and path name.  These functions are
//  very handy when it comes to wild card expansion, which is why
//  they are in ArchiveLib.
//
//  If you want to see how the C++ member functions perform these
//  amazing feats, see OBJNAME.CPP.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A  : First release
//
//   August 10, 1994 1.0B : Combined a bunch of #ifdefs into a single test
//                          against AL_VB

//
// The C translation function.
//
extern "C" char AL_DLL_FAR * AL_FUNCTION
StripFileName( char AL_DLL_FAR *filename )
{
    ALName temp = filename;
    temp.StripFileName();
    strcpy( filename, temp );
    return filename;
}

#if defined( AL_VB )

//
// The VB translation function.
//
extern "C" long AL_FUNCTION StripFileNameVB( char AL_DLL_FAR *filename )
{
    ALName temp = filename;
    char _far *p = temp.StripFileName();
    return ALCreateVBString( p, (unsigned short int) _fstrlen( p ) );
}

#endif

// C TRANSLATION FUNCTION
//
// extern "C" char * StripPath( char *filename )
//
// VB TRANSLATION FUNCTION
//
// extern "C" long StripPathVB( char *filename )
//
// ARGUMENTS:
//
//  filename  :  An ordinary VB or C string that contains a file name.
//
// RETURNS
//
//  Either a C or VB string type, with the drive and path stripped,
//  leaving just a filename and extension.  Note that
//  the C version of the function copies over your existing string,
//  whereas the VB version creates a new VB string.
//
// DESCRIPTION
//
//  This function takes a file name, and strips off any path and drive
//  information, leaving the file and extension.  These functions are
//  very handy when it comes to wild card expansion, which is why
//  they are in ArchiveLib.
//
//  If you want to see how the C++ member functions perform these
//  amazing feats, see OBJNAME.CPP.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A   : First release
//
//   August 10, 1994 1.0B : Combined a bunch of #ifdefs into a single test
//                          against AL_VB

//
// The C translation function.
//
extern "C" char AL_DLL_FAR * AL_FUNCTION
StripPath( char AL_DLL_FAR *filename )
{
    ALName temp = filename;
    temp.StripPath();
    strcpy( filename, temp );
    return filename;
}

#if defined( AL_VB )
//
// The VB translation function
//
extern "C" long AL_FUNCTION StripPathVB( char AL_DLL_FAR *filename )
{
    ALName temp = filename;
    char _far *p = temp.StripPath();
    return ALCreateVBString( p, (unsigned short int) _fstrlen( p ) );
}
#endif


