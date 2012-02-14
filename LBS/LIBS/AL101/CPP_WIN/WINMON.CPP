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

#include "grenengn.h"
#include "winmon.h"
#include "wildcard.h"

//
// void * ALWindowsMessage::operator new( size_t size )
//
// ARGUMENTS:
//
//  size  :  The amount of storage that needs to be allocated for
//           this object.
//
// RETURNS
//
//  A pointer to the storage.
//
// DESCRIPTION
//
//  When using the DLL version of ArchiveLib, it is a good idea to
//  allocate the storage for objects from inside the DLL, since they
//  will be freed inside the DLL.  If we don't have the new operator
//  for a class, its storage will be allocated from the EXE before
//  the constructor code is called.  Then, when it is time to free
//  the storage, the delete operator will be called inside the DLL.
//  Not good, right?
//
//  By providing our own version of operator new inside this class, we
//  ensure that all memory allocation for the class will be done from
//  inside the DLL, not the EXE calling the DLL.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

#if defined( AL_BUILDING_DLL )
void AL_DLL_FAR * AL_PROTO ALWindowsMessage::operator new( size_t size )
{
    return ::new char[ size ];
}
#endif

//
// ALWindowsMessage::ALWindowsMessage(  ALMonitorType monitor_type,
//                                      HWND progress_text_window,
//                                      ALWindowsMessageType message_type,
//                                      HWND progress_number_window,
//                                      UINT windows_message = 0 )
//
// ARGUMENTS:
//
//  monitor_type           : AL_MONITOR_OBJECTS or AL_MONITOR_JOBS
// 
//  progress_text_window   : The handle of the window that is going to
//                           receive text messages during the archiving
//                           process.
//
//  message_type           : AL_SEND_RATIO or AL_SEND_BYTE_COUNT
//
//  progress_number_window : The window that is going to receive the
//                           number, which will either be the byte
//                           count or the percent complete ratio.
//
//  windows_message        : The message that will be sent to the 
//                           progress number window.  When the message
//                           is sent, the number is sent in LPARAM
//                           and WPARAM, so take your pick.  If this
//                           number is set to 0, the message is instead
//                           sent as test using the set text call.
//
// RETURNS
//
//  None, its a constructor.
//
// DESCRIPTION
//
//  This constructor has an easy job.  It accepts five parameters. 
//  Four of them just get copied into data members, the fifth gets
//  passed up to the constructor for the base class.
//
//  This type of monitor is used in Windows programs.  Our examples
//  make use of it frequently.  It sends text messages to edit or static
//  text controls, and sends numbers to either text controls or custom
//  controls.  We use it to dink with our ALGauge control.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

AL_PROTO 
ALWindowsMessage::ALWindowsMessage( ALMonitorType monitor_type,
                                    HWND progress_text_window,
                                    ALWindowsMessageType message_type,
                                    HWND progress_number_window,
                                    UINT windows_message /* = 0 */ )
    : ALMonitor( monitor_type )
{
    mhMessageWindowHandle = progress_text_window;
    mhNumberWindowHandle = progress_number_window;
    miMessage = windows_message;
    mMessageType = message_type;
}

//
// void ALWindowsMessage::Progress( long object_tell,
//                                  ALStorage &object )
//
// ARGUMENTS:
//
//  object_tell   :  The current offset in the storage object.
//
//  object        :  The ALStorage object currently being processed,
//                   whether for insertion, extraction, or whatever.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  While an archiving operation is in progress, this monitor function
//  will get called sometimes.  It gets called by the Yield() function
//  inside the ALStorage object.  The Yield function figures out what
//  the current offset is inside the storage object, and passes that
//  as a parameter.
//
//  Taking that all into account, this routine has to figure out what
//  sort of message to send to the window that is getting the progress
//  update.  Basically, there are two options we have to consider.  First,
//  we have to figure out whether we are sending the byte count or
//  the ratio (the percent of the job/object that we have done.)  Second,
//  we have to see if there is a windows message or not.  If there is
//  a windows message, we send the number with SendMessage().  Otherwise
//  we format it into ASCII text and send it using SetWindowText().
//  SetWindowText() works good for edit controls and the like.
//
//  In case you are wondering, we don't have to take into account whether
//  we are monitoring individual objects or an entire job.  That is because
//  that is figured out in the Progress() function in the base class,
//  which we call at the start of this function.  It calculates the correct
//  values of mlByteCount and miRatio based on which type of monitoring
//  we are doing, then leaves it up to us here to figure out how and where
//  to send the data.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

void AL_PROTO ALWindowsMessage::Progress( long object_tell,
                                          ALStorage AL_DLL_FAR & object )
{
    char buf[ 18 ];

//
//  This guy figures out what the current byte count and ratio are
//
    ALMonitor::Progress( object_tell, object );
    if ( mhNumberWindowHandle == 0 )
        return;

    switch ( mMessageType ) {
        case AL_SEND_BYTE_COUNT :
//
// Send the byte count using either SendMessage() or SetWindowText()
//
            if ( miMessage == 0 ) {
                wsprintf( buf, "%ld", mlByteCount );
                SetWindowText( mhNumberWindowHandle, buf );
            } else
                SendMessage( mhNumberWindowHandle,
                             (short int) miMessage,
                             0,
                             mlByteCount );
            break;
        case AL_SEND_RATIO :
//
// Send the progress ratio using SendMessage() or SetWindowText()
//
            if ( miMessage == 0 ) {
                wsprintf( buf, "%d%%", miRatio );
                SetWindowText( mhNumberWindowHandle, buf );
            } else
                SendMessage( mhNumberWindowHandle,
                             (short int) miMessage,
                             (short int) miRatio,
                             miRatio );
        default :
            break;
    }
}

//
// void ALWindowsMessage::ArchiveOperation( ALArchiveOperation operation,
//                                          ALArchiveBase *archive,
//                                          ALEntry *job )
//
// ARGUMENTS:
//
//  operation : One of the values from the enumerated type ALArchiveOperation.
//              It is simply a list of possible operations that the archive
//              operation might take, such as opening a file, closing a
//              file, etc.
//
//  archive   : A pointer to the archive object currently being worked on.
//
//  job       : A pointer to an ALEntry object that defines the ALStorage
//              object presently being worked on.
//
// RETURNS
//
//  Not a thing.
//
// DESCRIPTION
//
//  During the course of an Archiving operation, the functions in
//  ALArchiveBase will get the urge to spit out a message.  They do
//  so by calling this member function.  All of the messages should
//  be self-explanatory.
//
//  It would make a lot of sense to move the message formatting up into
//  the base class so I didn't have to duplicate this effort in every
//  derived class.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

#ifdef AL_FLAT_MODEL
  #define CHAR_PTR char *
#else
  #define CHAR_PTR char _far *
#endif

void AL_PROTO
ALWindowsMessage::ArchiveOperation( ALArchiveOperation operation,
                                    ALArchiveBase AL_DLL_FAR *archive,
                                    ALEntry AL_DLL_FAR *job )
{
    if ( mhMessageWindowHandle == 0 )
        return;
    char buf[ 81 ];

    switch ( operation ) {
        case AL_ARCHIVE_OPEN :
            wsprintf( buf, "Opening %s", (CHAR_PTR) archive->GetStorageObject()->mName.GetSafeName() );
            break;
        case AL_ARCHIVE_CLOSE :
            wsprintf( buf, "Closing %s", (CHAR_PTR) archive->GetStorageObject()->mName.GetSafeName() );
            break;
        case AL_EXTRACTION_OPEN :
            wsprintf( buf, "Extracting %s", (CHAR_PTR) job->mpStorageObject->mName.GetSafeName() );
            break;
        case AL_INSERTION_OPEN :
            wsprintf( buf, "Inserting %s", (CHAR_PTR) job->mpStorageObject->mName.GetSafeName() );
            break;
        case AL_COPY_OPEN :
            wsprintf( buf, "Copying %s", (CHAR_PTR) job->mpStorageObject->mName.GetSafeName() );
            break;
        case AL_EXTRACTION_CLOSE :
        case AL_INSERTION_CLOSE :
        case AL_COPY_CLOSE :
        case AL_END_DIRECTORY_WRITE :
        case AL_END_DIRECTORY_READ :
            strcpy( buf, "Done" );
            break;
        case AL_START_DIRECTORY_WRITE :
            strcpy( buf, "Writing directory" );
            break;
        case AL_START_DIRECTORY_READ :
            strcpy( buf, "Reading directory" );
            break;
    }
    SetWindowText( mhMessageWindowHandle, buf );
}

//
// ALWindowsMessage::~ALWindowsMessage()
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
//  This destructor doesn't do anything.  I guess it is just sort of a 
//  place holder in case anything exciting comes along.  Of course, it
//  does run a check to make sure it is the right sort of object.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

AL_PROTO ALWindowsMessage::~ALWindowsMessage()
{
    AL_ASSERT( GoodTag(), "~ALWindowsMessage: attempt to delete invalid object" );
}
