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

#ifndef	_OLDDYNFILE_
#define	_OLDDYNFILE_

//	Programmer:	Alessandro Ara�jo Jatob�

#include	<filecl.h>
#include	<lbstypes.h>
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

class C_OldDynFileHead{
	public:
		int 		iMagicNumber;
		TFreeSpace	tfFirstSpace;
};

class _LIFILECLASS C_OldDynamicFile : public C_File{
	public:
		C_OldDynFileHead	cdfhHead;

		C_OldDynamicFile( char *szFileName, int iMagNum, char *szKey,
			const char *szMode = NULL, int iShFlag = SH_DENYNONE );
		C_OldDynamicFile();
		int Open( char *szFileName, int iMagNum, char *szKey,
			const char *szMode = NULL, int iShFlag = SH_DENYNONE );
		long D_WriteOnFreeSpace( void *szBuffer, long lLen );
		long D_GetFreeSpace( long lLen );
		long D_FreeSpace( long lGap, long lSize );
		int  WriteHead();
		int  ReadHead();
		int  LockHead();
		int  ReleaseHead();

};

#endif

