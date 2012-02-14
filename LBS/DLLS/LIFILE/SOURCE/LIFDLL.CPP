/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

//
// Module: LIFDLL.CPP
// Description:
//
//	Main LIFILE module
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 13/06/96
//

#ifndef __WINDOWS_H     /* prevent multiple includes */
#include	<windows.h>
#endif
#ifndef	_CLOG_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include	<lifregcrit.h>


// para personalizacao
extern "C" {
#include	<personcl.h>
}

#define	MAXNUMFILE32SSTR		"MAXNUMFILE32S"	// numero maximo de arquivos para Win32s
#define	MAXNUMFILE32S			-1
#define	CLOSESTDFILESSTR		"CLOSESTDFILES"	// indica se os stdfiles devem ser fechados
#define	LIFILEINIFILE			"LBFILE.INI"	// .ini de lifile
#define	LIFILECONFIGSECTION		"CONFIG"


// objeto log global apenas para manter o arquivo aberto 
// enquanto este modulo estiver no ar
extern	C_Log	*_pcGlobalLog;

// numero maximo de arquivos abertos simultaneamente
extern	int	_iMaxOpenFiles;

// variavel usada para indicacao de plataforma operacional
extern	int	_bIs32s;

// arquivo de reserva, para garantir um descritor que sera' usado em casos emergenciais
extern	C_File	*_xFile;

// lista de locks dos arquivos
extern	LockList	*_LockTable[ NUMLIST ];

// variavel que determina o nome do _xFile
static	char	_szTempName[ MAXPATH ];

// variavel usada para a janela de log
static	HWND	_hLogWnd = NULL;

// handle do evento de controle de wait de lock
extern	HANDLE	_hWaitLockEvent;

// variavel de controle de regioes criticas
C_GlobalFileCritSect	*_pcGlobalFileCritSect = NULL;
C_GlobalLogCritSect		*_pcGlobalLogCritSect = NULL;


void	Printf(char *, ... );
BOOL	Init();

void	GetAppFullPath( char *Path, int Size );


// esta variavel eh usada para saber quantos processos estao
// usando esta DLL.
static	int	_iNumberOfProc = 0;

/***
	DllEntryPoint Function
	Handles the DLL entry end exit

	Parameters:
		- hInstDLL	-> handle of DLL module
		- fdwReason	-> why function was called
		- lpvReserved	-> reserved; must be NULL

	Return:
		-

	Comments:
		-

***/
BOOL WINAPI
DllMain( HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	switch( fdwReason ){
	case DLL_PROCESS_ATTACH:	// A DLL ESTAH SENDO CARREGADA POR ALGUM PROCESSO
		if( _iNumberOfProc == 0 ) {
			if( !Init() ){
				return( FALSE );
			}
		}
		_iNumberOfProc++;
		return( TRUE );			// ESTE VALOR EH USADO PELO WINDOWS

	case DLL_THREAD_ATTACH:		// O PROCESSO CORRENTE ESTAH CRIANDO UM THREAD
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	case DLL_THREAD_DETACH:		// UM THREAD ESTAH TERMINANDO
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	case DLL_PROCESS_DETACH:	// A DLL ESTAH SENDO LIBERADA POR ALGUM PROCESSO
		--_iNumberOfProc;
		if( _iNumberOfProc == 0 ){
			FinishLifile();
		}
#ifdef _NEW_DBG_LIGHT_
		GeraLog();
#endif
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	}
	return( FALSE );
}


/***
***/
BOOL
Init()
{
	if( !_hWaitLockEvent ){
		_hWaitLockEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
		if( !_hWaitLockEvent ){
			return( FALSE );
		}
	}
	_pcGlobalFileCritSect = new C_GlobalFileCritSect;
	if( !_pcGlobalFileCritSect ){
		return( FALSE );
	}
	_pcGlobalLogCritSect = new C_GlobalLogCritSect;
	if( !_pcGlobalLogCritSect ){
		delete _pcGlobalFileCritSect;
		_pcGlobalFileCritSect = NULL;
		return( FALSE );
	}

	for( int i = 0; i < NUMLIST; i++ ){
		_LockTable[ i ] = new LockList;
		if( !_LockTable[ i ] ){
			// fudeu
			delete _pcGlobalFileCritSect;
			_pcGlobalFileCritSect = NULL;
			delete _pcGlobalLogCritSect;
			_pcGlobalLogCritSect = NULL;
			return( FALSE );
		}
	}
	_iMaxOpenFiles = C_File::CalcMaxOpenFiles();
	_bIs32s = FALSE;	//C_File::Is32s();

	char	szTempPath[ MAXPATH ];

	if( (GetTempPath( MAXPATH, szTempPath ) <= 0) ||
		(GetTempFileName( szTempPath, "LB", 0, _szTempName ) <= 0) ){
		strcmp( _szTempName, "c:\\x.dat" );
	}
	_xFile = new C_File( _szTempName );
	if( !_xFile ){
		// fudeu!
		delete _pcGlobalFileCritSect;
		_pcGlobalFileCritSect = NULL;
		delete _pcGlobalLogCritSect;
		_pcGlobalLogCritSect = NULL;
		return( FALSE );
	}
	if( !_xFile->IsOpen() ){
		// nao conseguimos abrir o arquivo.
		// vamos detonar o objeto para que o C_File nao
		// se engane, pensando que pode usar o _xFile.
		delete _xFile;
		_xFile = NULL;
	}

	_pcGlobalLog = new C_Log( "INTERNAL_LIFILE" );
	if( !_pcGlobalLog ){
		// fudeu!
		delete _xFile;
		_xFile = NULL;
		delete _pcGlobalFileCritSect;
		_pcGlobalFileCritSect = NULL;
		delete _pcGlobalLogCritSect;
		_pcGlobalLogCritSect = NULL;
		return( FALSE );
	}

	char	szFullIniName[ MAXPATH ];

	GetAppFullPath( szFullIniName, MAXPATH );

	strcat( szFullIniName, LIFILEINIFILE );

	// obtem o numero maximo de arquivos que podem ser abertos em 32s
	int iMaxNumFiles32s = GetPrivateProfileInt( LIFILECONFIGSECTION,
						MAXNUMFILE32SSTR,
						MAXNUMFILE32S,
						szFullIniName );
	if( iMaxNumFiles32s != MAXNUMFILE32S ){
		// seta o numero em C_File
		C_File::SetNumFiles32s( iMaxNumFiles32s );
	}
	// verifica se os arquivos stdin, stdout e stderr devem ser fechados
	// para liverar mais handles de arquivo.
	int iCloseStdFiles = GetPrivateProfileInt( LIFILECONFIGSECTION,
						CLOSESTDFILESSTR,
						0,
						szFullIniName );
	if( iCloseStdFiles ){
		// informa para C_File se os descritores devem ser liberados
		C_File::CloseStdFiles();
	}
	return( TRUE );
}


/***
***/
BOOL
FinishLifile()
{
	if( _pcGlobalLog ){
		delete _pcGlobalLog;
		_pcGlobalLog = NULL;
	}
	if( _xFile ){
		delete _xFile;
		_xFile = NULL;
		// remove o arquivo
		remove( _szTempName );
	}
	for( int i = 0; i < NUMLIST; i++ ){
		if( _LockTable[ i ] ){
			delete _LockTable[ i ];
			_LockTable[ i ] = NULL;
		}
	}
	if( _pcGlobalFileCritSect ){
		delete _pcGlobalFileCritSect;
		_pcGlobalFileCritSect = NULL;
	}
	if( _pcGlobalLogCritSect ){
		delete _pcGlobalLogCritSect;
		_pcGlobalLogCritSect = NULL;
	}
	if( _hWaitLockEvent ){
		CloseHandle( _hWaitLockEvent );
		_hWaitLockEvent = NULL;
	}
	return( TRUE );
}


void GetAppFullPath( char *Path, int Size )
{
   // Se inicia com aspas, ...
   if ( *GetCommandLine() == '\"' )
      // ... pega a linha a partir do segundo caracter
      strncpy( Path, GetCommandLine() + 1, Size );
   else
      // ... senão, pega a linha completa
      strncpy( Path, GetCommandLine(), Size );
   Path[Size-1] = '\0';

   // Retira o nome do arquivo
   for ( int i = strlen(Path)-1; i >= 0; i-- ) {
      if ( Path[i] == '\\' || Path[i] == '/' ) {
         Path[i+1] = '\0';
         break;
      }
   }
   if ( i < 0 )
      Path[0] = '\0';
}

