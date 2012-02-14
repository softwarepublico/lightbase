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


#ifndef _FILESTOR_H
#define _FILESTOR_H

#include "arclib.h"

#if defined( __cplusplus )

#include "stor.h"

/*
 * class ALFile : public ALStorage
 *
 * DESCRIPTION
 *
 * This is the class declaration for ALFile.  This is the fundamental disk
 * storage class used in Archive Library.  It is derived directly from
 * ALStorage, so it has to implement versions of the five or six
 * critical virtual functions, mostly relating to opening files, closing
 * them, loading and flushing buffers.
 *
 * DATA MEMBERS
 *
 *  miHandle  :  The handle of the file when opened.  This is the value
 *               returned by the function call to open().
 *
 * MEMBER FUNCTIONS
 *
 *  ALFile()        : The constructor.
 *  ~ALFile()       : The virtual destructor.
 *  operator new()  : The memory allocation operator, only used when the
 *                    library is inside a DLL.
 *  MakeTempName()  : Private function used to generate temporary names.
 *  Open()          : Virtual function to open the file.
 *  Create()        : Virtual function to create the file.
 *  Close()         : Virtual fn to close the file.
 *  LoadBuffer()    : Virtual fn to load the I/O buffer from a specific address.
 *  FlushBuffer()   : Virtual fn to flush the I/O buffer.
 *  Seek()          : Virtual fn to seek to seek to a new position in the file.
 *  Rename()        : Rename the underlying file.
 *  UnRename()      : Undo the rename process.
 *  Delete()        : Delete the disk file (not destroy!)
 *  RenameToBackup(): Rename the current file to a backup name.
 *
 * REVISION HISTORY
 *
 *  May 26, 1994  1.0A   : First release
 *
 *  August 10, 1994 1.0B : Changed a default parameter to account for
 *                         mixed case file names under UNIX and NT.
 */

class AL_CLASS_TYPE ALFile : public ALStorage {
/*
 * Constructors, destructors, assignment operator, friends, declarations
 */
    public :
        AL_PROTO ALFile( const char AL_DLL_FAR *file_name = "",
                         int buffer_size = 4096,
#if defined( AL_UNIX ) || defined( AL_WIN32S )
                         ALCase name_case = AL_MIXED );
#else
                         ALCase name_case = AL_LOWER );
#endif
        virtual AL_PROTO ~ALFile();
#if defined( AL_USING_DLL ) || defined( AL_BUILDING_DLL )
        void AL_DLL_FAR * AL_PROTO operator new( size_t size );
#endif
/*
 * As usual, I don't want the compiler to generate a default copy constructor,
 * or an assignment operator here.  I force it to back off by declaring them
 * here.  They do not exist!
 */
    protected :
        AL_PROTO ALFile( ALFile AL_DLL_FAR & );
        ALFile AL_DLL_FAR & AL_PROTO operator=( const ALFile AL_DLL_FAR & );

/*
 * Member functions, grouped by category.
 *
 *
 * Protected member manipulation, used inside library, not for public use.
 */
    protected :
        virtual void AL_PROTO MakeTempName( int i );
/*
 * The file I/O access public interface
 */
    public :
        virtual int AL_PROTO Open();
        virtual int AL_PROTO Create();
        virtual int AL_PROTO Close();
        virtual int AL_PROTO LoadBuffer( long address );
        virtual int AL_PROTO FlushBuffer();
        virtual int AL_PROTO Seek( long address );

/*
 * File name and underlying object manipulation public interface
 */
    public :
        virtual int AL_PROTO Rename( const char AL_DLL_FAR *new_name = 0,
                                     int delete_on_clash = 1 );
        virtual int AL_PROTO UnRename( int delete_on_clash = 1 );
        virtual int AL_PROTO Delete();
        virtual int AL_PROTO RenameToBackup( int delete_on_clash = 1 );
/*
 * Data members
 */
    protected :
        int miHandle;
    public :
        AL_CLASS_TAG( _ALFileTag );
};

#endif /* #if defined( __cplusplus ) */

#endif /* #ifdef _FILESTOR_H         */
