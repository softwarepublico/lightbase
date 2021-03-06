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



