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

#ifndef	_OLDRECFILCL_H_
#define	_OLDRECFILCL_H_

#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

class _LIFILECLASS C_OldRecordFile : public C_File{
	private:
		long	lHeadSize;
		long	lRecSize;
		long	lCurPos;
		long	lFileSize;
		char	*szHeadKey;
		char	*szRecKey;

	protected:
		int	iHeadLocked;
		static long lNextAppendLocation;

	public:
		/* Construtor */
		C_OldRecordFile( char* szFileNamePar, long lHeadSize, long lRecSize,
			char *szHeadKey, char *szRecKey,
			const char *szMode = NULL, int iShFlag = SH_DENYNONE );
		C_OldRecordFile();
		~C_OldRecordFile( void );
		/* Open */
		int Open( char* szFileNamePar, long lHeadSize, long lRecSize,
			char *szHeadKey, char *szRecKey,
			const char *szMode = NULL, int iShFlag = SH_DENYNONE );
		/* Seeks */
		int R_Seek( long lPos );
		int R_SeekNext( void );
		int R_SeekPrevious( void );
		int operator [ ] ( int lPos );

		/* Reads & Writes */
		int R_Write( void *szBuffer );
		int R_Write( long lPos, void *szBuffer );
		int R_Append( void *szBuffer );
		int R_Read( void *szBuffer );
		int R_Read( long lPos, void *szBuffer );
		int R_WriteHead( void *szBuffer );
		int R_ReadHead( void *szBuffer );
		int	R_UndoLastAppend();

		/* Others */
		long R_FileSize( void );
		long R_CurPos( void );
		int R_Lock( void );
		int R_Release( void );
		int R_LockHead( void );
		int R_ReleaseHead( void );
		void R_SetRecKey( char *szRecKey );
		void R_SetHeadKey( char *szHeadKey );

		int Search( void *pvBuffer, char (*fCmp) ( void *a, void *b ) );
};

#endif	// _OLDRECFILCL_H_



