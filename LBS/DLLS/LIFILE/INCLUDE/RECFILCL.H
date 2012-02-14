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

#ifndef	_RECFILCL_
#define	_RECFILCL_

#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

// Definicao para implementacao dos seguintes metodos da classe C_RcordFile:
// 		void TurnOnCriptoHead( void );
//		void TurnOffCriptoHead( void );
//		void TurnOnCriptoRec( void );
//		void TurnOffCriptoRec( void );
#define TURN_ON		"TurnOn"


class _LIFILECLASS C_RecordFile : public C_File{
	protected:
		long	lHeadSize;
		long	lRecSize;
		long	lCurPos;
		long	lFileSize;
		char	*szHeadKey;
		char	*szRecKey;
		int		iHeadLocked;
		static long lNextAppendLocation;
	

	public:
		/*
		Inicio Cod: Katyusco
		Objetivo: bMagicNumber passa a ser public para que
		outras classes possam settar tal atributo.
		*/
		BYTE	bMagicNumber;
		/*
		Fim Cod: Katyusco
		*/


		/* Construtor */
		C_RecordFile( char *, BYTE, long, long, char *, char *,
			const char * = NULL, int = SH_DENYNONE, BOOL = FALSE );
		C_RecordFile();
		C_RecordFile( BYTE );
		~C_RecordFile( void );
		/* Open */
		int Open( char *, BYTE, long, long, char *, char *,
			const char * = NULL, int = SH_DENYNONE, BOOL = FALSE );
		int Open( char *, long, long, char *, char *,
			const char * = NULL, int = SH_DENYNONE, BOOL = FALSE );
		/* Seeks */
		int R_Seek( long lPos );
		int R_SeekNext( void );
		int R_SeekPrevious( void );
		int operator [ ] ( int lPos );

		/* Reads & Writes */
		int R_Write( void *szBuffer );
		int R_Write( void *szBuffer, long lOffset, long lSize );
		int R_Write( long lPos, void *szBuffer );
		int R_Append( void *szBuffer );
		int R_Read( void *szBuffer );
		int R_Read( void *szBuffer, long lOffset, long lSize );
		int R_Read( long lPos, void *szBuffer );
		int R_WriteHead( void *szBuffer );
		int R_ReadHead( void *szBuffer );
		void TurnOnCriptoHead( void );
		void TurnOffCriptoHead( void );
		void TurnOnCriptoRec( void );
		void TurnOffCriptoRec( void );
		int	R_UndoLastAppend();

		/* Others */
		long R_FileSize( void );
		long R_CurPos( void );
		int R_Lock( BOOL = FALSE );
		int R_Lock( long, long, BOOL = FALSE );
		int R_Release( void );
		int R_Release( long , long );
		int R_LockHead( BOOL = FALSE );
		int R_ReleaseHead( void );
		void R_SetRecKey( char *szRecKey );
		void R_SetHeadKey( char *szHeadKey );

		int Search( void *pvBuffer, char (*fCmp) ( void *a, void *b ) );
};

#endif

