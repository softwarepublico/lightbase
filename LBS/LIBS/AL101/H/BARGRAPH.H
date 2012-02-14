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


#ifndef _BARGRAPH_H
#define _BARGRAPH_H

#include "arclib.h"

#if defined( __cplusplus )

/*
 * class ALBarGraph : public ALMonitor
 *
 * DESCRIPTION
 *
 *  This is a utility class.  The constructor opens a file for input,
 *  and keeps track of whether it was already open or not.  The destructor
 *  will automatically close the file if it was closed when the
 *  ctor was invoked.
 *
 * DATA MEMBERS
 *
 *  miCurrentOffset   : The current offset of the bargraph, in screen
 *                      units.  Usually the bar itself is 20 characters
 *                      long, in which case this value will be somewhere
 *                      between 0 and 19.
 *
 *  miBarLength       : The length of the bar, defined when the 
 *                      constructor is called.  This is a const member,
 *                      which means we can leave it public.
 *
 *  mrStream          : Reference to an output stream.  This is the
 *                      stream where the bargraph gets drawn.
 *                    
 * MEMBER FUNCTIONS
 *
 *  ALBarGraph()        : The constructor.
 *  ~ALBarGraph()       : Virtual destructor.
 *  Progress()          : The progress routine, where the bargraph
 *                        gets updated.
 *  ArchiveOperation()  : The routine that gets called when files
 *                        are opened, closed, etc.
 *
 * REVISION HISTORY
 *
 *  May 26, 1994  1.0A  : First release
 *
 */

class AL_CLASS_TYPE ALBarGraph : public ALMonitor {
/*
 * Constructors, destructors, and friend classes
 */
     public :
          AL_PROTO ALBarGraph( ALMonitorType monitor_type,
                               ostream AL_DLL_FAR& stream = cout,
                               int bar_length = 25 );
          virtual AL_PROTO ~ALBarGraph();
#if defined( AL_USING_DLL ) || defined( AL_BUILDING_DLL )
        void AL_DLL_FAR * AL_PROTO operator new( size_t size );
#endif
/*
 * The copy constructor and assignment operator do not exist.
 */
     protected :
          AL_PROTO ALBarGraph( const ALBarGraph AL_DLL_FAR & );
          ALBarGraph AL_DLL_FAR & AL_PROTO operator=( const ALBarGraph AL_DLL_FAR & );
/*
 * Member functions
 */
     protected :
          virtual void AL_PROTO Progress( long object_so_far,
                                          ALStorage AL_DLL_FAR & object );
          virtual void AL_PROTO
          ArchiveOperation( ALArchiveOperation operation,
                            ALArchiveBase AL_DLL_FAR *archive,
                            ALEntry AL_DLL_FAR *job );
/*
 * Data Members
 */
     protected :
          int miCurrentOffset;
          const int miBarLength;
          ostream AL_DLL_FAR & mrStream;
     public :
          AL_CLASS_TAG( _ALBarGraphTag );
};

#endif /* #if defined( __cplusplus ) */

#endif /* #ifdef _BARGRAP_H          */
