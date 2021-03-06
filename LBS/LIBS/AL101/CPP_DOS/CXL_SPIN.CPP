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
// extern "C" hALMonitor newALSpinner( enum ALMonitorType monitor_type )
//
// ARGUMENTS:
//
//  monitor_type  : AL_MONITOR_OBJECTS or AL_MONITOR_JOB.
//
// RETURNS
//
//   A C handle to a newly constructed ALSpinner object.
//
// DESCRIPTION
//
//  This routine provides the translation to C for the ALSpinner
//  constructor.  It creates the new object, then returns a pointer
//  to it to the calling program, cast to the handle type.
//
//  Note that we don't give the caller the option of defining
//  the stream that is going to get the spinner.  Sorry, it is
//  hardcoded to cout.  Most Run Time Libraries seem to be happy
//  to tie cout to stdout, so this stuff works okay with C.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A    : First release
//
//   January 9, 1995 1.01A : This function wasn't exported in previous
//                           releases of the library.  That meant that
//                           if you were trying to use DOS DLLs, you
//                           couldn't use this type of monitor.
//

extern "C"
hALMonitor AL_FUNCTION newALSpinner( enum ALMonitorType monitor_type )
{
    ALSpinner *monitor;
    monitor = new ALSpinner( monitor_type, cout );
    return (hALMonitor) monitor;
}

