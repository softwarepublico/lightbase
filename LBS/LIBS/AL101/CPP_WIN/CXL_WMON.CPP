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

#include "alcxl.h"
#include "winmon.h"

//
// extern "C" hALMonitor newALWindowsMessage(
//                               enum ALMonitorType monitor_type,
//                               HWND progress_text_window,
//                               enum ALWindowsMessageType message_type,
//                               HWND progress_number_window,
//                               UINT windows_message )
//
// ARGUMENTS:
//
//  monitor_type           :  One of AL_MONITOR_OBJECTS or AL_MONITOR_JOB.
//
//  progress_text_window   :  The monitor periodically sends text messages
//                            to a window.  This is it.
//
//  message_type           :  One of AL_SEND_BYTE_COUNT or AL_SEND_RATIO.
//
//  progress_number_window :  This is the window that gets the number
//                            either as text or as a parameter.
//
//  windows_message        :  If this is non-zero, it means the number is
//                            sent as both the lparam and wparam of a
//                            windows message.
//
// RETURNS
//
//  An ALMonitor handle.
//
// DESCRIPTION
//
//  This is a wrapper function that provides C and VB programmers with
//  access to the ALWindowsMessage monitor object constructor.  For
//  lots of details on message monitor see WINMON.CPP.  Since this
//  is a wrapper function it pretty much just passes things along 
//  without doing any real work itself.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//
extern "C" hALMonitor AL_FUNCTION newALWindowsMessage(
                               enum ALMonitorType monitor_type,
                               HWND progress_text_window,
                               enum ALWindowsMessageType message_type,
                               HWND progress_number_window,
                               UINT windows_message )
{
    ALWindowsMessage *monitor;
    monitor = new ALWindowsMessage( monitor_type,
                                    progress_text_window,
                                    message_type,
                                    progress_number_window,
                                    windows_message );
    return (hALMonitor) monitor;
}

