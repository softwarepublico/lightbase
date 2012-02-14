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

//
// Module: FILECL.H
// Description:
//	C_File Class definition file.
//
// Programmer:	Marcos Sebastian Alsina
//
// Last Uptade: 05/01/96 -> Adriano Sergio
//

#ifndef	_FILECL_
#define	_FILECL_

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#if !defined( __STDIO_H ) && !defined _INC_STDIO
#include	<stdio.h>
#endif
#if !defined __IO_H && !defined _INC_IO
#include	<io.h>
#endif
#if !defined( __SHARE_H ) && !defined _INC_SHARE
#include	<share.h>
#endif


#ifdef _NEW_DBG_
extern void GeraLIFILELog();
#include	<stddef.h>
extern void *operator new( size_t, char *, int );
#define	new	new(__FILE__, __LINE__)
#endif



#define	E_NOTOPEN	-100
#define	E_BUFFNULL	-101
#define	E_WRITE		-102
#define	E_READ		-103
#define	E_SEEK		-104
#define	E_CLOSE		-105
#define MAXCRIPTOKEY	15
#ifndef	OK
#define	OK		0
#endif

#include	<DeviceCl.h>
#include	<Locklst.h>

#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

#define	NUMLIST		13
#define	CRITSECT0	0


class _LIFILECLASS C_File : public Device
{

private:

	// atributos estaticos privados
	// atributos privados


	// MMF
	int					iPageSize;		// granularidade de alocacao
	HANDLE				hMMF;			// handle MMF
	LPVOID				pHeadView;		// ponteiro para o header do arquivo, ja' mapeado
	LPVOID				pWinView;		// ponteiro para uma janela de dados, ja' mapeada
	int					iWinNum;		// numero da janela corrente (comeca em 0)
	int					iSeekWin;		// seek corrente dentro da janela atual (comeca em 0)
	int					iMMFWinSize;	// tamanho de uma janela (a ser multiplicado por iPageSize)
	
	HANDLE				hFile;
	int					iFile;
	DWORD				dwAccess;
	char				szKey [ MAXCRIPTOKEY ];
	char				cCriptoOn;
	DWORD				dwLastUse;
	BOOL				bReOpen;
	char				szFileName[ 256 ];
	char				szMode[ 10 ];
	int					iShFlag;
	long				lCurPos;
	long				lNumLocks;
	int					iLine;
	BOOL				bRealLock;
	SECURITY_ATTRIBUTES	saSecurity;

	// metodos privados
	int			ListIn();
	int			ListOut();
	int			CloseSomeFile();
	int			ReOpen();
	BOOL		IsLocked( LockStruct *, BOOL = FALSE );
	LockStruct 	*GetLock( LockStruct * );
	int			DelLock( LockStruct * );
	int			AddLock( LockStruct *, BOOL = FALSE );
	int			Hash();

	void		CreateViewOfFile();
	void		CreateViewOfHead();
	void		SeekMMFWin( long );
	int			GrowFile( long  );
	int			RealLock( LockStruct *, BOOL = FALSE );
	int			RealRelease( LockStruct * );

protected:
	int			PseudoClose();

public:
	// atributos publicos
	int					iHeadSize;		// tamanho em bytes do header
	int					iHeadInit;		// posicao inicial do header

	// metodos publicos
			C_File();
			C_File( const char *, const char * = NULL, int = SH_DENYNONE, BOOL = FALSE );
			~C_File();
	BOOL		IsOpen();
	long		CurPos();
	long		FileSize();
	int		Open( const char *, const char * = NULL, int = SH_DENYNONE, BOOL = FALSE );
	int		Close();
	int			ReadBuffer( void FAR *, size_t );
	size_t		Read( void FAR *, size_t, size_t );
	size_t		Write( void FAR *, size_t, size_t );
	size_t		ReadLine( char FAR *, size_t );
	size_t		WriteLine( char FAR * );
	int			Read( void FAR *buffer, size_t size );
	int			Write( void FAR *buffer, size_t size );
	int			Seek( long, int );
	int			Rewind();
	size_t		Append( void *pvBuf, size_t tsSize, size_t tsNumItens );
	int			GetHandle();
	int			Lock( long, BOOL = FALSE );
	int			Release( long );
	void		TurnOnCripto( char *szKey );
	void		TurnOffCripto( void );
	BOOL		IsCriptoOn();
	int			Flush();
	int			PseudoCloseAllFiles();
	int			ReOpenAllFiles();
	BOOL		TryUse();
	time_t		GetCreateTime();
	const char	*GetFileName();
	int			GetFileStatInfo( struct stat * );


	// metodos virtuais publicos
	virtual	void Encrypt( void *, char *, size_t );
	virtual	void Decrypt( void *, char *, size_t );

	// metodos estaticos publicos
	static	BOOL	Exist( const char* );
	static	int		CalcMaxOpenFiles();
	static	int		SetNumFiles32s( int );
	static	int		CloseStdFiles();
	static	BOOL	Is32s();
	static	BOOL	Get32sVar();
	static	void	SetRealLock( BOOL );
};

class	C_FileCritSect
{
	int		iLastSectUsed;
	C_File	 *pObj;

public:
	C_FileCritSect( C_File *pObjPar, int iNumCritSect );
	~C_FileCritSect();
	void EnterCriticalSection();
	void LeaveCriticalSection();
};


#endif	// _FILECL_

