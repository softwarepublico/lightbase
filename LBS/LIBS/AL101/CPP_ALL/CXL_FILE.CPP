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

//
// extern "C" hALStorage newALFile( char *file_name )
//
// ARGUMENTS:
//
//  file_name  :  The name of the file to construct.
//
// RETURNS
//
//  A handle for (pointer to) a newly constructed ALFile object.  It is
//  possible to get a 0 back if the file could not be constructed for
//  some reason.
//
// DESCRIPTION
//
//  This is the C and VB translation function that provides access to
//  ALFile::ALFile().  It calls the constructor, then casts the result
//  to a type C will be happy with and returns it.
//
// REVISION HISTORY
//
//   May 24, 1994  1.0A  : First release
//

extern "C" hALStorage AL_FUNCTION newALFile( char AL_DLL_FAR *file_name )
{
    return (hALStorage) new ALFile( file_name );
}


