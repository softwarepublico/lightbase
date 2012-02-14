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

#include "al.h"
#include "alcxl.h"

//
// extern "C" hALMonitor newALBarGraph( enum ALMonitorType monitor_type 
//
// ARGUMENTS:
//
//  monitor_type : AL_MONITOR_OBJECTS or AL_MONITOR_JOB.
//
// RETURNS
//
//  A C handle to the newly constructed monitor object.
//
// DESCRIPTION
//
//  This is the C translation layer that is used to invoke the
//  ALBarGraph destructor.  Note that I didn't offer the C caller
//  the options of changing the stream or the bargraph length.  If
//  further customization is needed, it would be really, really, easy
//  to add a new function to do so.
//
//  Also, this guy writes to cout, which doesn't really exist in C.
//  So we are going to have to depend on the synchronization of
//  cout and stdout in the Run Time Library, otherwise this whole
//  thing will look pretty goofy.
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
hALMonitor AL_FUNCTION newALBarGraph( enum ALMonitorType monitor_type )
{
    ALBarGraph *monitor;
    monitor = new ALBarGraph( monitor_type, cout );
    return (hALMonitor) monitor;
}

