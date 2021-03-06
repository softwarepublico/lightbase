/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o t�tulo
"LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef	_DYNFILE_
#define	_DYNFILE_

//	Programmer:	Alessandro Ara�jo Jatob�

#include	<filecl.h>
#include	<lbstypes.h>
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

class _LIFILECLASS C_DynFileHead{
	public:
		BOOL 		bMagicNumber;
		TFreeSpace	tfFirstSpace;
};

class _LIFILECLASS C_DynamicFile : public C_File{
private:
		long D_MinSlotSize();

public:
		C_DynFileHead	cdfhHead;
		char			*szKey;

		C_DynamicFile( char *, BYTE, char *, const char * = NULL, int = SH_DENYNONE );
		C_DynamicFile( BYTE );
		~C_DynamicFile();
		int Open( char *, BYTE, char *, const char * = NULL, int = SH_DENYNONE );
		long D_WriteOnFreeSpace( void *szBuffer, long lLen );
		long D_GetFreeSpace( long lLen );
		long D_FreeSpace( long lGap, long lSize );
		int  WriteHead();
		int  ReadHead();
		int  LockHead( BOOL = FALSE );
		int  ReleaseHead();

};

#endif

