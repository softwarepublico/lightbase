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
// extern "C" long ALMonitorSetObjectSize( hALMonitor this_object,
//                                         long size )
//
// ARGUMENTS:
//
//  this_object   : The monitor whose object size member needs to be set.
//
//  size          : The new value to be assigned to mlObjectSize.
//
// RETURNS
//
//  The long size value.
//
// DESCRIPTION
//
//  This C/VB translation function provides access to the C++ data member
//  ALMonitor::mlObjectSize.  Why would you want to change this
//  data member?  Normally this data member is set up by the member functions
//  of ALArchiveBase before performing an operation.  If you are trying
//  to use a monitor to provide feedback on an operation of your own,
//  such as a file copy, you would  have to set the data member up
//  using this function.
//
//  This function first tests its handle argument for correct type (when in
//  debug mode), then casts and modifies the data member.
//
//  This function is like all of the other translation routines in that
//  it is fairly uninformative.  To get the real scoop on monitor objects,
//  look at MONITOR.CPP and ARCHIVEB.CPP.
//
// REVISION HISTORY
//
//   May 24, 1994  1.0A  : First release
//

extern "C" long AL_FUNCTION ALMonitorSetObjectSize( hALMonitor this_object,
                                                     long size )
{
    AL_ASSERT_OBJECT( this_object, ALMonitor, "ALMonitorSetObjectSize" );
    return ( (ALMonitor *) this_object )->mlObjectSize = size;
}

//
// extern "C" long ALMonitorSetObjectStart( hALMonitor this_object,
//                                          long offset )
//
// ARGUMENTS:
//
//  this_object   : The monitor whose object start member needs to be set.
//
//  offset        : The new value to be assigned to mlObjectStart.
//
// RETURNS
//
//  The long offset value.
//
// DESCRIPTION
//
//  This C/VB translation function provides access to the C++ data member
//  ALMonitor::mlObjectStart.  Why would you want to change this
//  data member?  Normally this data member is set up by the member functions
//  of ALArchiveBase before performing an operation.  If you are trying
//  to use a monitor to provide feedback on an operation of your own,
//  such as a file copy, you would  have to set the data member up
//  using this function.
//
//  This function first tests its handle argument for correct type (when in
//  debug mode), then casts and modifies the data member.
//
//  This function is like all of the other translation routines in that
//  it is fairly uninformative.  To get the real scoop on monitor objects,
//  look at MONITOR.CPP and ARCHIVEB.CPP.
//
// REVISION HISTORY
//
//   May 24, 1994  1.0A  : First release
//

extern "C" long AL_FUNCTION ALMonitorSetObjectStart( hALMonitor this_object,
                                                     long offset )
{
    AL_ASSERT_OBJECT( this_object, ALMonitor, "ALMonitorSetObjectStart" );
    return ( (ALMonitor *) this_object )->mlObjectStart = offset;
}

//
// extern "C" long ALMonitorSetJobSize( hALMonitor this_object,
//                                      long size )
//
// ARGUMENTS:
//
//  this_object   : The monitor whose job size member needs to be set.
//
//  size          : The new value to be assigned to mlJobSize.
//
// RETURNS
//
//  The long size value.
//
// DESCRIPTION
//
//  This C/VB translation function provides access to the C++ data member
//  ALMonitor::mlJobSize.  Why would you want to change this
//  data member?  Normally this data member is set up by the member functions
//  of ALArchiveBase before performing an operation.  If you are trying
//  to use a monitor to provide feedback on an operation of your own,
//  such as a batch file copy, you would  have to set the data member up
//  using this function.
//
//  This function first tests its handle argument for correct type (when in
//  debug mode), then casts and modifies the data member.
//
//  This function is like all of the other translation routines in that
//  it is fairly uninformative.  To get the real scoop on monitor objects,
//  look at MONITOR.CPP and ARCHIVEB.CPP.
//
// REVISION HISTORY
//
//   May 24, 1994  1.0A  : First release
//

extern "C" long AL_FUNCTION ALMonitorSetJobSize( hALMonitor this_object,
                                                 long size )
{
    AL_ASSERT_OBJECT( this_object, ALMonitor, "ALMonitorSetJobSize" );
    return ( (ALMonitor *) this_object )->mlJobSize = size;
}

//
// extern "C" long ALMonitorSetJobSoFar( hALMonitor this_object,
//                                       long job_so_far )
//
// ARGUMENTS:
//
//  this_object   : The monitor whose "job so far" member needs to be set.
//
//  job_so_far    : The new value to be assigned to mlJobSoFar.   
//
// RETURNS
//
//  The new value of mlJobSoFar.
//
// DESCRIPTION
//
//  This C/VB translation function provides access to the C++ data member
//  ALMonitor::mlJobSoFar.  Why would you want to change this
//  data member?  Normally this data member is set up by the member functions
//  of ALArchiveBase before performing an operation.  If you are trying
//  to use a monitor to provide feedback on an operation of your own,
//  such as a batch file copy, you would  have to set the data member up
//  using this function.
//
//  This function first tests its handle argument for correct type (when in
//  debug mode), then casts and modifies the data member.
//
//  This function is like all of the other translation routines in that
//  it is fairly uninformative.  To get the real scoop on monitor objects,
//  look at MONITOR.CPP and ARCHIVEB.CPP.
//
// REVISION HISTORY
//
//   May 24, 1994  1.0A  : First release
//

extern "C" long AL_FUNCTION ALMonitorSetJobSoFar( hALMonitor this_object,
                                                   long job_so_far )
{
    AL_ASSERT_OBJECT( this_object, ALMonitor, "ALMonitorSetJobSoFar" );
    return ( (ALMonitor *) this_object )->mlJobSoFar = job_so_far;
}

//
// extern "C" void deleteALMonitor( hALMonitor this_object )
//
// ARGUMENTS:
//
//  this_object  : The monitor object to be destroyed.  This will usually
//                 be an object from a derived class, not the base class.
//                 The dtor is virtual, so we always call the base
//                 class destructor using this function.
//
// RETURNS
//
//  No returns, this is a destructor.
//
// DESCRIPTION
//
//  This is the C/VB wrapper function that calls the destructor for an
//  ALMonitor object.  This is a virtual destructor, so you won't find
//  equivalent functions defined for the base classes used with
//  ArchiveLib.
//
//  This function just checks its single argument for correct type, then
//  casts it and calls the destructor.
//
//  Like most of these wrapper functions, this is fairly unenlightening.
//  For more real dirt, try looking at the base class dtor in MONITOR.CPP,
//  or derived class dtors in BARGRAPH.CPP and WINMON.CPP.
//
// REVISION HISTORY
//
//   May 25, 1994  1.0A  : First release
//

extern "C" void AL_FUNCTION deleteALMonitor( hALMonitor this_object )
{
    AL_ASSERT_OBJECT( this_object, ALMonitor, "deleteALMonitor" );
    delete (ALMonitor *) this_object;
}

