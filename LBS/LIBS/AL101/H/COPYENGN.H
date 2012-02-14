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


#ifndef _COPYENG_H
#define _COPYENG_H

#include "arclib.h"

#if defined( __cplusplus )

#include "cmpengn.h"
#include "stor.h"

/*
 * class ALOpenInputFile 
 *
 * DESCRIPTION
 *
 * ALCopyEngine is a full fledged compression engine.  It just
 * copies files from input to output, instead of doing something
 * exciting like making them smaller.  Its principal virtue is that it
 * is very fast.  If you are packing a bunch of files into an archive,
 * and don't particularly need to compress them, you can use an instance of
 * ALCopyEngine and get your work done quickly.
 *
 * DATA MEMBERS
 *
 *   None.
 *
 * MEMBER FUNCTIONS
 *
 *  ALCopyEngine()      : The one and only constructor.
 *  ~ALCopyEngine()     : The virtual destructor.
 *  operator new()      : Memory allocation operator, only used when the
 *                        library is in a DLL.
 *  Compress()          : The virtual compression function.
 *  Decompress()        : The virtual decompression function.
 *
 * REVISION HISTORY
 *
 *  May 26, 1994  1.0A  : First release
 *
 */

class AL_CLASS_TYPE ALCopyEngine : public ALCompressionEngine {
/*
 * Constructors, destructors, declarations, friends
 */
    public :
        AL_PROTO ALCopyEngine();
        virtual AL_PROTO ~ALCopyEngine();
#if defined( AL_USING_DLL ) || defined( AL_BUILDING_DLL )
        void AL_DLL_FAR * AL_PROTO operator new( size_t size );
#endif
/*
 * The copy constructor and assignment operator do not exist.  I define
 * them here to prevent the compiler from creating default versions.
 */
    protected :
        AL_PROTO ALCopyEngine( ALCopyEngine AL_DLL_FAR & );
        ALCopyEngine AL_DLL_FAR & AL_PROTO operator=( ALCopyEngine AL_DLL_FAR & rhs );
/*
 * Member functions
 */
    public :
        virtual int AL_PROTO Compress( ALStorage AL_DLL_FAR &input,
                                       ALStorage AL_DLL_FAR &output );
        virtual int AL_PROTO Decompress( ALStorage AL_DLL_FAR &input,
                                         ALStorage AL_DLL_FAR &output,
                                         long compressed_length = -1 );
/*
 * Data members
 */
    public :
        AL_CLASS_TAG( _ALCompressedObjectTag );
};

#endif /* #if defined( __cplusplus ) */

#endif /* #ifndef _COPYENG_H         */
