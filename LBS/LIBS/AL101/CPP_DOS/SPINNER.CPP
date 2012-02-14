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

#include <iostream.h>

#include "spinner.h"

//
// A single static member for the whole class.  At one time I thought
// this would be a good idea, I don't think so any more.  But it doesn't
// really matter unless you have multiple processes running multiple
// monitors.  Since this is MS-DOS only, that doesn't seem likely.
//
int ALSpinner::miSpinIndex;

//
// void * ALSpinner::operator new( size_t size )
//
// ARGUMENTS:
//
//  size  :  The number of bytes needed to create a new ALSpinner
//           object.
//
// RETURNS
//
//  A pointer to the newly allocated storage area, or 0 if no storage
//  was available.
//
// DESCRIPTION
//
//  When using a DLL, it is easy to get into a dangerous situation when
//  creating objects whose ctor and dtor are both in the DLL.  The problem
//  arises because when you create an object using new, the memory for
//  the object will be allocated from the EXE.  However, when you destroy
//  the object using delete, the memory is freed inside the DLL.  Since
//  the DLL doesn't really own that memory, bad things can happen.
//
//  By providing our own version of operator new inside this class, we
//  ensure that all memory allocation for the class will be done from
//  inside the DLL, not the EXE calling the DLL.
//
// REVISION HISTORY
//
//   January 6, 1995 1.01A  : First release
//

#if defined( AL_BUILDING_DLL )
void AL_DLL_FAR * AL_PROTO ALSpinner::operator new( size_t size )
{
    return ::new char[ size ];
}
#endif

//
// ALSpinner::ALSpinner( ALMonitorType monitor_type,
//                       ostream& stream = cout )
//
// ARGUMENTS:
//
//  monitor_type : AL_MONITOR_OBJECTS or AL_MONITOR_JOB
//
//  stream       : The stream where the propellor is going to be displayed.
//
// RETURNS
//
//  Nothing returned from a constructor.
//
// DESCRIPTION
//
//  The constructor for the ALSpinner object just has to initialize
//  a couple of data members.  The real action doesn't start until the
//  archive is opened.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A    : First release
//
//   January 9, 1995  1.01A : Modified the stream argument to be a
//                            far reference.  This lets me use this
//                            class even when it is inside a DLL.
//

AL_PROTO ALSpinner::ALSpinner( ALMonitorType monitor_type,
                               ostream AL_DLL_FAR & stream )
    : ALMonitor( monitor_type ),
      mrStream( stream )
{
}

//
// ALSpinner::~ALSpinner()
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  None.
//
// DESCRIPTION
//
//  The ALSpinner destructor  doesn't have to do anything.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A  : First release
//

AL_PROTO ALSpinner::~ALSpinner()
{
    AL_ASSERT( GoodTag(), "~ALSpinner: attempt to delete invalid object" );
}

//
// void ALSpinner::Progress( long object_tell,
//                           ALStorage& object )
//
// ARGUMENTS:
//
//  object_tell  : The current offset in the storage object being
//                 worked on.  We pass this to the base class so that
//                 it can calculate the ration, but that is really
//                 a waste of effort, since we don't use the results.
//                 It would be better to just ignore this object.
//
//  object       : A reference to the object being worked on.  Once again,
//                 we pass it to the base class, and never use them again.
//                 It would be better to ignore this.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This function is called from ALStorage::Yield() during the processing
//  of the object.  All we do is display a little propellor spinning
//  around and around.  It spins one tick each time it gets called, which
//  will normally be once every 4K bytes.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A  : First release
//
//   January 9, 1995  1.01A : Modified the object argument to be a
//                            far reference.  This lets me use this
//                            class even when it is inside a DLL.
//

void AL_PROTO ALSpinner::Progress( long object_tell,
                                   ALStorage AL_DLL_FAR & object )
{
    ALMonitor::Progress( object_tell, object );
    mrStream << "|/-\\"[ miSpinIndex++ & 3 ] << '\b' << flush;
}

//
// void ALSpinner::ArchiveOperation( ALArchiveOperation operation,
//                                   ALArchiveBase *archive,
//                                   ALEntry *job )
//
// ARGUMENTS:
//
//  operation   : One of the enumerated values of ALArchiveOperation,
//                used to indicate just what is happening here.
//
//  archive     : A pointer to the archive object.  You can use this
//                in monitor routines to get the name of the archive
//                or other exciting facts.
//
//  job         : A pointer to the ALEntry object.  This lets me know
//                which object is being compressed, expanded, or whatever.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This monitor routine is called by the Archive class from time to
//  time during key points in the archiving process.  We can then 
//  print diagnostic messages out to the user.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A  : First release
//
//   January 9, 1995  1.01A : Modified the archive and job arguments to be
//                            far pointers.  This lets me use this
//                            class even when it is inside a DLL.
//

void AL_PROTO ALSpinner::ArchiveOperation( ALArchiveOperation operation,
                                           ALArchiveBase AL_DLL_FAR *archive,
                                           ALEntry AL_DLL_FAR *job )
{
    switch ( operation ) {
        case AL_ARCHIVE_OPEN :
            if ( miMonitorType == AL_MONITOR_JOB )
                mrStream << archive->GetStorageObject()->mName.GetName() << " ";
            break;
        case AL_ARCHIVE_CLOSE :
            if ( miMonitorType == AL_MONITOR_JOB )
                mrStream << "\n";
            break;
        case AL_EXTRACTION_OPEN :
        case AL_COPY_OPEN :
        case AL_INSERTION_OPEN :
            if ( miMonitorType == AL_MONITOR_OBJECTS )
                mrStream << job->mpStorageObject->mName.GetSafeName() << " ";
            break;
        case AL_EXTRACTION_CLOSE :
        case AL_COPY_CLOSE :
            if ( miMonitorType == AL_MONITOR_OBJECTS )
                mrStream << "\n";
            break;
        case AL_INSERTION_CLOSE :
            if ( miMonitorType == AL_MONITOR_OBJECTS )
                mrStream << job->CompressionRatio() << "%\n";
            break;
        case AL_END_DIRECTORY_WRITE :
        case AL_END_DIRECTORY_READ :
//            cout << "Done\n";
            break;
        case AL_START_DIRECTORY_WRITE :
//            mrStream << "Writing directory\n";
            break;
        case AL_START_DIRECTORY_READ :
//            mrStream << "Reading directory\n";
            break;
    }
    mrStream << flush;
}
