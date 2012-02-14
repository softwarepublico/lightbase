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
#include <iomanip.h>

#include "bargraph.h"

#ifndef AL_UNIX
#define FOREGROUND '\xb1'
#define BACKGROUND '\xb0'
#else
#define BACKGROUND 'o'
#define FOREGROUND '.'
#endif

//
// void * ALBarGraph::operator new( size_t size )
//
// ARGUMENTS:
//
//  size  :  The number of bytes needed to create a new ALBarGraph
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
void AL_DLL_FAR * AL_PROTO ALBarGraph::operator new( size_t size )
{
    return ::new char[ size ];
}
#endif

//
// ALBarGraph::ALBarGraph( ALMonitorType monitor_type,
//                         ostream& stream,
//                         int bar_length = 25 )
//
// ARGUMENTS:
//
//  monitor_type  : AL_MONITOR_OBJECTS or AL_MONITOR_JOBS
//
//  stream        : The stream where the little graph is going to be
//                  printed.
//
//  bar_length    : The length of the bar.  
//
// RETURNS
//
//  Nothing, constructor.
//
// DESCRIPTION
//
//  This constructor initializes things, but it doesn't have any real
//  work to do.  It initializes the three local data members for
//  the object, and initializes ALMonitor with its data member, and
//  that's that.  We don't actually draw the graph yet, that happens
//  later when on of the Archive operations takes place.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//
//   January 9, 1995  1.01A : Modified the stream parameter to be a far ref,
//                            so you can use an ALBarGraph from inside a
//                            DOS DLL.
//
AL_PROTO ALBarGraph::ALBarGraph( ALMonitorType monitor_type,
                                 ostream AL_DLL_FAR& stream,
                                 int bar_length /* =25 */ )
     : ALMonitor( monitor_type ),
        mrStream( stream ),
        miBarLength( bar_length )
{
     miCurrentOffset = 0;
}

//
//  ALBarGraph::~ALBarGraph()
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
//  The destructor does nothing.  If it ever has to do anything serious, 
//  this is where it will happen.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//

AL_PROTO ALBarGraph::~ALBarGraph()
{
     AL_ASSERT( GoodTag(), "~ALBarGraph: attempt to delete invalid object" );
}

//
// void ALBarGraph::Progress( long object_tell,
//                            ALStorage& object )
//
// ARGUMENTS:
//
//  object_tell  : The current offset within the object being munged.
//                 Since this function is always called from inside
//                 ALStorage::Yield(), it knows.
//
// object        : The object being compressed, extracted, copied, or
//                 whatever.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This function gets called a lot while an object is being processed.
//  All we do in here is update the position on the bargraph.  Note
//  that we can't go backwards!
//
//  You might notice here that we don't check on whether we are monitoring
//  Objects or Jobs, we just go with the value found in miRatio.  There
//  is a simple reason for that.  At the start of the function, we call
//  ALMonitor::Progress().  The base class function checks to see which
//  mode we are in, and calculates the miRatio value according to whatever
//  mode we are in.
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//
//  July 8, 1994  1.0B  : Changed the default characters under UNIX to
//                        normal ASCII, not IBMPC non-printables.
//
//   January 9, 1995  1.01A : Modified the object parameter to be a far ref,
//                            so you can use an ALBarGraph from inside a
//                            DOS DLL.
//

void AL_PROTO ALBarGraph::Progress( long object_tell,
                                    ALStorage AL_DLL_FAR & object )
{
     ALMonitor::Progress( object_tell, object );
     if ( miRatio >= 0 ) {
          int new_offset = ( miBarLength * miRatio ) / 100;
          while ( miCurrentOffset < new_offset ) {
                mrStream << FOREGROUND;
                miCurrentOffset++;
          }
     }
     mrStream << flush;
}

//
// void ALBarGraph::ArchiveOperation( ALArchiveOperation operation,
//                                    ALArchiveBase AL_DLL_FAR *archive,
//                                    ALEntry AL_DLL_FAR *job )
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
//  The ALBarGraph class behaves a little differently, depending on
//  whether it is monitoring objects or the entire job.  When it is
//  monitoring individual objects, it will print out the name of
//  each object as it progresses, and will redraw the bargraph as
//  each new object is opened.  In monitor job mode, the bargraph
//  starts at 0 when the entire operation is started, and completes
//  when the whole thing is done.  The individual objects being compressed
//  don't cause anything exciting to happens as they are opened
//  and closed.
//
// REVISION HISTORY
//
//   May 22, 1994  1.0A  : First release
//
//  July 8, 1994  1.0B  : Changed the default characters under UNIX to
//                        normal ASCII, not IBMPC non-printables.
//
//   January 9, 1995  1.01A : Modified the archive and job parameters to be
//                            far pointers so you can use an ALBarGraph from
//                            inside a DOS DLL.
//

void AL_PROTO ALBarGraph::ArchiveOperation( ALArchiveOperation operation,
                                            ALArchiveBase AL_DLL_FAR *archive,
                                            ALEntry AL_DLL_FAR *job )
{
    int i;
//
// Note that I am using character 0xb0 to draw the graph originally,
// and 0xb1 to redraw it indicating progress.  Maybe it would be
// better to make these data members so people could change their
// values...
//
    switch ( operation ) {
        case AL_ARCHIVE_OPEN :
            if ( miMonitorType == AL_MONITOR_JOB ) {
                mrStream << archive->GetStorageObject()->mName.GetSafeName()
                         << " ";
                for ( i = 0 ; i < miBarLength ; i++ )
                    mrStream << BACKGROUND;
                for ( i = 0 ; i < miBarLength ; i++ )
                    mrStream << '\b';
            }
                break;

        case AL_ARCHIVE_CLOSE :
            if ( miMonitorType == AL_MONITOR_JOB ) {
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << ' ';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                mrStream << "\n";
                miCurrentOffset = 0;
            }
                break;
        case AL_EXTRACTION_OPEN :
        case AL_COPY_OPEN :
        case AL_INSERTION_OPEN :
            if ( miMonitorType == AL_MONITOR_OBJECTS ) {
                mrStream << job->mpStorageObject->mName.GetSafeName() << " ";
                for ( i = 0 ; i < miBarLength ; i++ )
                    mrStream << BACKGROUND;
                for ( i = 0 ; i < miBarLength ; i++ )
                    mrStream << '\b';
            }
            break;
        case AL_EXTRACTION_CLOSE :
        case AL_COPY_CLOSE :
            if ( miMonitorType == AL_MONITOR_OBJECTS ) {
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << ' ';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                mrStream << "\n";
                miCurrentOffset = 0;
            }
            break;
        case AL_INSERTION_CLOSE :
                if ( miMonitorType == AL_MONITOR_OBJECTS ) {
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << ' ';
                for ( i = 0 ; i < miCurrentOffset ; i++ )
                    mrStream << '\b';
                mrStream << job->CompressionRatio() << "%\n";
                miCurrentOffset = 0;
            }
            break;
//
// I decided the aesthetics were better without these messages.  I am
// leaving them here to look at in case we want to try them again
// some day.
//
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
