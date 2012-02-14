/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o título
"LICENCA.txt", junto com este programa, se não, escreva para a Fundação do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef	_DYNFILE_
#define	_DYNFILE_

//	Programmer:	Alessandro Araújo Jatobá

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

