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

#ifndef	_OLDDYNFILE_
#define	_OLDDYNFILE_

//	Programmer:	Alessandro Araújo Jatobá

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

