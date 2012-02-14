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

#include <string.h>

#include "_openf.h"

//
// int ALStorage::Compare( ALStorage & test )
//
// ARGUMENTS:
//
//  test  :  The storage object that will be compared to this.
//
// RETURNS
//
//  AL_SUCCESS if the two files match.  AL_COMPARE_ERROR if the files
//  don't match.  An error code < AL_SUCCESS is possible if some other 
//  error takes place during the process.
//
// DESCRIPTION
//
//  This function provides a convenient way to test this object 
//  against another.  Note that if the comparison fails, the status
//  code of this object will be set to an error state.  You will need
//  to clear that error if you intend to use this object again.
//
// REVISION HISTORY
//
//   May 26, 1994  1.0A  : First release
//

int AL_PROTO ALStorage::Compare( ALStorage AL_DLL_FAR & test )
{
    ALOpenInputFile in1( test );
    ALOpenInputFile in2( *this );

    if ( test.mStatus < 0 )
       return mStatus = test.mStatus;
    if ( GetSize() != test.GetSize() ) 
        return mStatus.SetError( AL_COMPARE_ERROR, 
                                 "Comparison failed.  "
                                 "File %s and %s are two different sizes.",
                                 mName.GetSafeName(),
                                 test.mName.GetSafeName() );
    long position = 0;
    for ( ; ; ) {
        int c = ReadChar();
        if ( c < 0 )
            break;
        if ( c != test.ReadChar() ) 
            return mStatus.SetError( AL_COMPARE_ERROR,
                                     "File %s and %s differed at position %ld",
                                     mName.GetSafeName(),
                                     test.mName.GetSafeName(),
                                     position );
         position++;
    }
    return mStatus;    
}

