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
// Module: LBSDLL.CPP
// Description:
//
//	Main LBS module
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 18/10/94
//

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef __WINDOWS_H     /* prevent multiple includes */
#include	<windows.h>
#endif
#include	<process.h>

// API LBS
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_LOGLIST_H_
#include	<loglist.h>
#endif
#ifndef	_LICLIST_H_
#include	<liclist.h>
#endif
#ifndef	_BASETIMERSLIST_H_
#include	<btimerl.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef _LISOCK_H_
#include <LIsock.h>
#endif	// _LISOCK_H_
#ifndef	_MBASELST_H_
#include	<MBaseLst.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif

#include <baseinstance.h>

extern "C" {
#include	<personcl.h>
}

#ifdef	_DEBUG_CRIT_SECT_
int		_iCritSectCount = 0;	// definindo a variavel de controle de regioes criticas
#endif

const char *GetMyAppPath();

#ifdef LBS_DEBUG

// numero maximo de linhas que cabem na janela de log
#define	MAXLOGLINES	500

// variavel usada para a janela de log
static	HWND	_hLogWnd = NULL;

void Printf(char *, ... );

#endif // LBS_DEBUG

// handle do MMF para copia rede
static	HANDLE	_hFile = NULL;

// nome da defudb
char	_szDefUDBName[ MAXPATH ];

// extensoes de arquivos que compoem uma base LBS
char	_szPrivateExtensions[] = ".LB1 .LB2 .LB3 .LB4 .LB5 .LB6 .LB7 .LCK .LB .OL .STD .LTC .LTI .LTD .LTT .LTL .LT .NET";

// nome do arquivo de log de uso de bases
char	_szLogFileName[ MAXPATH ] = "";

// tokens importantes para a geracao do log de uso de bases
char	_szBaseToken[ 64 ] = "";
char	_szAccToken[ 64 ] = "";
char	_szRecToken[ 64 ] = "";
char	_szFieldKeyToken[ 64 ] = "";
char	_szUserToken[ 64 ] = "";
char	_szClientToken[ 64 ] = "";
char	_szReadOperationToken[ 64 ] = "";
char	_szWriteOperationToken[ 64 ] = "";
char	_szAppendOperationToken[ 64 ] = "";
char	_szDeleteOperationToken[ 64 ] = "";
char	_szSearchOKOperationToken[ 64 ];
char	_szSearchErrorOperationToken[ 64 ];
char	_szOpenBaseOperationToken[ 64 ];
char	_szCloseBaseOperationToken[ 64 ];
int		_iFieldContentLen = 20;

BaseInstanceManager	_BasesManager;

DWORD	LockTimerProc( LPVOID );					// funcao do thread de verificacao de locks
void	ReleaseLocks( LBSC_BaseTimersList *pBaseTimersList );	// funcao q efetivamente remove locks pendentes

// API LIGHT-TEXT
#include	<lt.h>

// IMPORTANTE:
// O objeto GLT_Session eh definido automaticamente pela API Light Text e eh
// usado para inicializar algumas coisas assim que este codigo entra no ar.
// Tambem eh usado para manipular sistemas de indices.
// O arquivo lt.h o declara.

// esta variavel eh usada para saber quantos processos estao
// usando esta DLL.
static	int	_iNumberOfProc = 0;

// variaveis globais de outros modulos
extern	LBSC_SessionList	*_clSessList;		// lista das sessoes abertas
extern	LBSC_LogList		*_clLoginList;		// lista contendo estruturas TNetInfo de todos
												// os logins efetuados. usada para controle
												// de licencas.
extern	LBSC_LicList		*_clLicList;		// lista para controle de licencas e usuarios
												// logados. Usada apenas para o LBS tipo REDE.
extern LBSC_MaintBasesList	*_pclMaintBaseList;	// lista para controle das bases que estao
												// reservadas para manutencao.
static LBSC_BaseTimersList 	*_clBaseTimersList;	// lista com indicacoes dos locks feitos para liberacao em caso de timeout

static void	Detonate();
static int	StartMMF();
static int	RecoverLicence();


// para internacionalizar
AppParmsMngr				*_pcInter = NULL;

// as variaveis abaixo determinam os conjuntos de
// regioes criticas utilizadas pelo LBS
C_GlobalSessCritSect		*_pcGlobalSessCritSect = NULL;			// regioes criticas para LBSC_Session
C_GlobalBaseCritSect		*_pcGlobalBaseCritSect = NULL;			// regioes criticas para LBSC_Base
C_GlobalDataCritSect		*_pcGlobalDataCritSect = NULL;			// regioes criticas para LBSC_Data
C_GlobalFieldCritSect		*_pcGlobalFieldCritSect = NULL;			// regioes criticas para LBSC_Field

void BeginAllTlsUsage();
void AllocAllTls();
void AllocTls( DWORD dwTlsSlot );
unsigned long GetTlsVal( DWORD dwTlsSlot );
void SetTlsVal( DWORD dwTlsSlot, unsigned long ulMask );
void FreeAllTls();
void FreeTls( DWORD dwTlsSlot );
void EndAllTlsUsage();
void EndTlsUsage( DWORD dwTlsSlot );

// as variaveis abaixo determinam os conjuntos de
// regioes criticas utilizadas pelo LT
#include	<error.h>
#include	<filedata.h>
#include	<hashtab.h>
#include	<index.h>
#include	<indexsys.h>
#include	<listcl.h>
#include	<lockfile.h>
#include	<phone.h>
#include	<session.h>
#include	<synonym.h>
#include	<termlist.h>

// objeto para gerar log no LBS
USELOG( _clLBSLog, "LBS.DLL" );

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
		BeginAllTlsUsage();
		if( _iNumberOfProc == 0 ) {
#ifdef LBS_DEBUG
			if( GetPrivateProfileInt( LBSINILBSSECTION, "PRINTF", 0, LBSINIFILE ) ){
				_hLogWnd = CreateWindow( "LISTBOX", "LBS", WS_OVERLAPPED | WS_CAPTION | 
							WS_MINIMIZEBOX | 
							WS_VISIBLE | WS_VSCROLL,
							CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
							NULL, NULL, hInstDLL, NULL );
			}
#endif // LBS_DEBUG
			int iRet = StartLBS();
			if( iRet != LBS_OK ){
				return( FALSE );
			}
		}
		PRINTLOG( _clLBSLog, ("DLL_PROCESS_ATTACH") );
		return( TRUE );			// ESTE VALOR EH USADO PELO WINDOWS

	case DLL_THREAD_ATTACH:		// O PROCESSO CORRENTE ESTAH CRIANDO UM THREAD
		AllocAllTls();
		PRINTLOG( _clLBSLog, ("DLL_THREAD_ATTACH") );
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	case DLL_THREAD_DETACH:		// UM THREAD ESTAH TERMINANDO
		FreeAllTls();
		PRINTLOG( _clLBSLog, ("DLL_THREAD_DETACH") );
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	case DLL_PROCESS_DETACH:	// A DLL ESTAH SENDO LIBERADA POR ALGUM PROCESSO
		{
			EndAllTlsUsage();
			--_iNumberOfProc;
			if( _iNumberOfProc == 0 ){
	#ifdef LBS_DEBUG
				DestroyWindow( _hLogWnd );
	#endif // LBS_DEBUG
				EndLBS();
			}
		}
		PRINTLOG( _clLBSLog, ("DLL_PROCESS_DETACH") );
		return( TRUE );			// ESTE VALOR NAO EH USADO PELO WINDOWS

	}
	return( FALSE );
}

/***
***/
int
StartLBS()
{
	PRINTLOG( _clLBSLog, ("StartLBS") );

	if( _iNumberOfProc == 0 ){

		LBSC_ServerConfig::Init();

		// le^ o nome da defudb
		strncpy( _szDefUDBName, LBSC_ServerConfig::DefUdbName(), MAXPATH-1 );

		if( ( strcmp( "", _szDefUDBName ) == 0 ) ){
			// deu pau (nao achei a string em LBS.INI).
			// assumir "DEFUDB"
			strcpy( _szDefUDBName, DEFAULTUSERBASE );
		}
		strupr( _szDefUDBName );

		// instancia objetos globais do LBS
		_pcInter = new AppParmsMngr( "LBS", "LBS", (char *)GetMyAppPath() );
		if( !_pcInter ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}
		_clSessList = new LBSC_SessionList;
		if( !_clSessList ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}
		_clLoginList = new LBSC_LogList;
		if( !_clLoginList ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}
		_clLicList = new LBSC_LicList;
		if( !_clLicList ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}
		_pclMaintBaseList = new LBSC_MaintBasesList;
		if( !_pclMaintBaseList ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		_pcGlobalSessCritSect = new C_GlobalSessCritSect;
		if( !_pcGlobalSessCritSect ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		_pcGlobalBaseCritSect = new C_GlobalBaseCritSect;
		if( !_pcGlobalBaseCritSect ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		_pcGlobalDataCritSect = new C_GlobalDataCritSect;
		if( !_pcGlobalDataCritSect ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		_pcGlobalFieldCritSect = new C_GlobalFieldCritSect;
		if( !_pcGlobalFieldCritSect ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		_clBaseTimersList = new LBSC_BaseTimersList;
		if ( !_clBaseTimersList ) {
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}
		unsigned uThreadId = 0;
		// criar thread para verificacao de locks
		HANDLE hThread = (HANDLE)_beginthreadex( NULL, 
							0, 
							(unsigned (__stdcall *)(LPVOID)) LockTimerProc, 
							(LPVOID)NULL, 
							0, 
							&uThreadId );
		CloseHandle( hThread );
		
		// instancia objetos globais do LT
		if( InitLT() != 0 ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		GLT_Session = new LTC_SESSION;
		if( !GLT_Session ){
			// fudeu!
			Detonate();
			return( LBSE_ERROR );
		}

		LI_Sock::InicializaWinSockApi();

		// settando o nome do diretorio temporario na LT
		char szTempDir[MAXPATH + 1];
		GetPrivateProfileString( LBSINILBSSECTION, LBSINILIGHTTEMPDIR,
					 "", szTempDir, MAXPATH, LBSINIFILE );
		LTC_SESSION::LT_SetTempDirName(szTempDir);

		// personalizacao
		int	i = CheckForRun();
		switch( i ){
		case PE_INSTALA:	// Produto nao personalisado
			MessageBox( NULL, "Person error!", "ERROR", MB_OK );
			return( LBSE_SERVERNOTPERS );

		case PE_DATA:		// Estourou data
//			MessageBox( NULL, "Server expired!", "ERROR", MB_OK );
//			return( LBSE_SERVEREXPIRED );

		case PE_OK:		// Ok! Pode executar.
			break;

		}

		// verificar tipo de copia para habilitar
		// lock em SO em C_File e desabilitar o uso de
		// regiao critica
		if( ::GetTypeInt() == PE_REDE ){
			// estamos em uma copia rede
			C_File::SetRealLock( TRUE );
			_bLTCanUseCritSect = FALSE;

			// inicializar o MMF
			if( StartMMF() != LBS_OK ){
				Detonate();
				return( LBSE_ERROR );
			}
		}

		return( LBS_OK );
	}
	return( LBSE_ERROR );
}


/***
	Funcao LockTimerProc
	Funcao para tratamento dos "timers" de lock; deve ser executada via thread a parte

	Parameters:

	Return:
		LBS_OK em caso de sucesso ou erro.

	Comments:

***/
DWORD	LockTimerProc( LPVOID )
{
	PRINTLOG( _clLBSLog, ("::LockTimerProc_NoAr") );

	DWORD dwTimeout = LBSC_ServerConfig::LockTimeOut();

	if ( !_clBaseTimersList ) {
		// ops!!!
		return 0;
	}

	do {
		PRINTLOG( _clLBSLog, ("::LockTimerProc_Dormindo") );

		Sleep( dwTimeout );

		PRINTLOG( _clLBSLog, ("::LockTimerProc_Acordado") );

		DWORD dwNow = GetTickCount();
		LBSC_BaseTimersList clTimersToRelease;

		{
			// vamos procurar por locks expirados
			// entrar nas regiao critica da lista de timers
			C_BaseCritSect	cCSBase14( NULL, CRITSECT14, __FILE__, __LINE__  );

			TBaseTimers *pTimer = _clBaseTimersList->First();
			while ( pTimer ) {
				PRINTLOG( _clLBSLog, ("::LockTimerProc_Loop") );

				if ( dwNow > (pTimer->dwStartTime + pTimer->dwInterval) ) {
					PRINTLOG( _clLBSLog, ("::LockTimerProc_LockEspirado") );

					// esse lock espirou
					// vamos inclui-lo na lista de releases 

					clTimersToRelease.Add( pTimer, TAIL );
					_clBaseTimersList->Refresh( NULL );
					_clBaseTimersList->Del();
					pTimer = _clBaseTimersList->Current();
				} else {
					pTimer = _clBaseTimersList->Next();
				}
			}
		}

		ReleaseLocks( &clTimersToRelease );

	} while ( TRUE );

	return 0;
}

void	AddLockInfo( TBaseTimers *pNew )
{
	PRINTLOG( _clLBSLog, ("::AddLockInfo") );

	// entra na regiao critica da lista de timers
	C_BaseCritSect	cCS14( NULL, CRITSECT14 );

	if ( !_clBaseTimersList->Find( pNew ) ) {
		// so insere se ja nao existe
		_clBaseTimersList->Add( pNew, TAIL );
	}
}


void	DelLockInfo( TBaseTimers *pFind )
{
	PRINTLOG( _clLBSLog, ("::DelLockInfo") );

	// entra na regiao critica da lista de timers
	C_BaseCritSect	cCS14( NULL, CRITSECT14 );

	TBaseTimers *pFound = _clBaseTimersList->Find( pFind );
	if ( pFound ) {
		// detona o corrente
		_clBaseTimersList->Del();
	}
}

void ReleaseLocks( LBSC_BaseTimersList *pTimersToRelease ) 
{
	// vamos tentar remover os locks da lista; primieiro precisamos ter certeza de que os ponteiros de base 
	// sao validos dai termos que pesquisa-los nas listas de sessoes 
	// e dai termos que entrar nas regioes criticas de session
	C_SessCritSect	cCS0( NULL, CRITSECT0 );
	C_SessCritSect	cCS1( NULL, CRITSECT1 );
	C_SessCritSect	cCS2( NULL, CRITSECT2 );
	C_SessCritSect	cCS3( NULL, CRITSECT3 );

	TBaseTimers *pTimer = pTimersToRelease->First();
	while ( pTimer ) {
		if( _clSessList->bIsDying ){
			// servidor saindo do ar... mais nada a fazer
			return;
		}
		LBSC_Session *pSession = _clSessList->Find( pTimer->pSession, CMPSESSIONPOINTER, TRUE );
		if( pSession ){
			LBSC_Base *pBase = (pSession->lbscblBaseList).Find( pTimer->pBase, CMPBASEPOINTER, TRUE );
			if( pBase ){
				if ( pBase->lLockPos == pTimer->lLockPos ) {
					PRINTLOG( _clLBSLog, ("::LockTimerProc_ReleaseLock") );
					// achamos o dito cujo
					pBase->ReleaseRecord( pBase->plbscsOwnerSession->plbsctTicket );
				}
			}
		}
		pTimer = pTimersToRelease->Next();
	}
}

/***
***/
int
EndLBS()
{
	PRINTLOG( _clLBSLog, ("EndLBS") );

	// detona objetos globais do LBS
	Detonate();

	return( LBS_OK );
}

/***
	Realoca buffers que foram alocados inicialmente com new
	e nao com calloc ou malloc.

	Se houver algum erro, o retorno sera' NULL.
	Se o pvOrigBuf for NULL, esta funcao funcionara' como um new,
	retornando o ponteiro do buffer alocado.
***/
void *
LBS_Realloc( void *pvOrigBuf, int iOldSize, int iNewSize )
{
	void	*pvNewBuf = NULL;

	if( iNewSize <= 0 || iOldSize < 0 ){
		return( NULL );
	}
	pvNewBuf = (void*) new char[ iNewSize ];
	if( pvNewBuf ){
		memset( pvNewBuf, 0, iNewSize );
	}
	if( pvOrigBuf && pvNewBuf ){
		memcpy( pvNewBuf, pvOrigBuf, min( iOldSize, iNewSize ) );
		delete (char*) pvOrigBuf;
	}
	return( pvNewBuf );
}


/***
	Obtem o numero de versao (numero magico) do arquivo
	de controle do LBS.
***/
int
GetControlFileVersion( char *szFileName )
{
	// se o arquivo nao existir, entao retornar versao OK
	if( !C_File::Exist( szFileName ) ){
		return( CRYPTO_MAGICNUMBER );
	}

	C_File cfBasesFile( szFileName, "rb", SH_DENYRW, TRUE );
	if( !cfBasesFile.IsOpen() ){
		return( LBSE_NOTOPEN );
	}
	cfBasesFile.Seek( 0, SEEK_SET );

	BYTE	bMagicNum = 0;

	cfBasesFile.Read( &bMagicNum, sizeof( bMagicNum ) );

	return( (int) bMagicNum );
}

/***
***/
BOOL
VerifySerialNumber( char *szSerialNumber )
{
	return( LBS_OK );
}

void
Detonate()
{
	if( _clSessList ){
		delete _clSessList;
		_clSessList = NULL;
	}
	if( _clLoginList ){
		delete _clLoginList;
		_clLoginList = NULL;
	}
	if( _clLicList ){
		delete _clLicList;
		_clLicList = NULL;
	}
	if( _pclMaintBaseList ){
		delete _pclMaintBaseList;
		_pclMaintBaseList = NULL;
	}
	if( _pcGlobalSessCritSect ){
		delete _pcGlobalSessCritSect;
		_pcGlobalSessCritSect = NULL;
	}
	if( _pcGlobalBaseCritSect ){
		delete _pcGlobalBaseCritSect;
		_pcGlobalBaseCritSect = NULL;
	}
	if( _pcGlobalDataCritSect ){
		delete _pcGlobalDataCritSect;
		_pcGlobalDataCritSect = NULL;
	}
	if( _pcGlobalFieldCritSect ){
		delete _pcGlobalFieldCritSect;
		_pcGlobalFieldCritSect = NULL;
	}
	if( _pcInter ){
		delete _pcInter;
		_pcInter = NULL;
	}

	if ( _clBaseTimersList ) {
		delete _clBaseTimersList;
		_clBaseTimersList = NULL;
	}

	LBSC_Session::ClearAll();

	// arquivo MMF
	if( _hFile ){
		CloseHandle( _hFile );
		_hFile = NULL;
	}

	// detona objetos globais do LT
	if( GLT_Session ){
		delete GLT_Session;
		GLT_Session = NULL;
	}
	LI_Sock::LiberaWinSockApi();
	FinishLT();
}


/***
	NextTok
	Obtem o proximo nome de diretorio de uma string

	Parameters:
		- szStr	-> string da qual os nomes de diretorios serao extraidos.
			   se for NULL, o metodo assume a ultima string != NULL que
			   foi passada (como o strtok)
		- szSeparator -> string de separacao (deve conter apenas um caracter)
				 (funciona como o segundo parametro do strtok)

	Return:
		- nome do diretorio encontrado ou NULL se o fim da string foi atingido

	Comments:
		- 

***/
char *
NextTok( char *szStr, char *szSeparator )
{
	static	char	szConst[ 1024 ];	// guarda a string original
	static	char	szRet[ 1024 ];		// serve para retorno
	static	char	*szBuffer = szStr;	// serve para procurar o szSeparator
	static	int	iPos = 0;

	if( !szSeparator ){
		// resetar
		szBuffer = szStr;
		iPos = 0;
		return( NULL );
	}

	if( szStr ){
		strcpy( szConst, szStr );
		szBuffer = szStr;
	}
	if( szConst[ iPos ] == '\0' ){
		return( NULL );
	}
	do{
		strcpy( szRet, szConst );
		for( ; *szBuffer != *szSeparator && *szBuffer; szBuffer++, iPos++ );
		szRet[ iPos++ ] = '\0';
		szBuffer++;
	} while( *szRet == '\0' || strcmp( szRet, "\\" ) == 0 || szRet[ strlen( szRet ) -1 ] == ':' );
	return( szRet );
}

/***
	MakeDir
	Cria um diretorio

	Parameters:
		- szDirName	-> nome do diretorio a ser criado

	Return:
		- LBS_OK ou erro

	Comments:
		- o diretorio a ser criado pode conter varios niveis e este metodo
		  criara' todos os niveis, ate' o ultimo.
		- se o diretorio ja' existir, o metodo retornara' LBSE_DIREXIST

***/
int
MakeDir( char *szDirName )
{
	if( chdir( szDirName ) == 0 ){
		// ja' existe
		return( LBSE_DIREXIST );
	}

	C_StrTok	cStrTok;
	char *szDir = new char [strlen(szDirName) + 10];
	char *szAuxDir = new char [strlen(szDirName) + 10];
	if ( !szDir || !szAuxDir ) {
		return ( LBSE_NOMEMORY );
	}

	strcpy( szDir, "" );
	strcpy( szAuxDir, szDirName );
	char *szName = cStrTok.StrTok( szAuxDir, "\\" );
	while( szName ){
		strcat( szDir, szName );
		strcat( szDir, "\\" );
		mkdir( szDir );
		szName = cStrTok.StrTok( NULL, "\\" );
	}

	delete szDir;
	delete szAuxDir;
	return( LBS_OK );
}



/***
	StartMMF
	Inicializa estruturas MMF

	Parameters:
		- 

	Return:
		- LBS_OK ou erro

	Comments:
		- 

***/
int
StartMMF()
{
	int		iCount = 0;
	LPVOID	pBuf = NULL;

	_hFile = NULL;

	// tentar abrir o arquivo MMF
	for( int i = 0; i < 3; i++ ){
		SetLastError( 0 );
		_hFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, "LBSINST" );
		if( !_hFile ){
/*			if( GetLastError() != ERROR_FILE_NOT_FOUND ){
				if( _pcInter ){
					_pcInter->AppMsgBox( NULL, "LBSERR_128", "ERR_CAP", MB_OK );
				} else {
					MessageBox( NULL, "Não foi possível inicializar o LBS.", "ERRO", MB_OK );
				}
				return( LBSE_ERROR );
			}
*/			DWORD dw = GetLastError();
			_hFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof( int ), "LBSINST" );
			dw = GetLastError();
			if( _hFile ){
				iCount = 1;
				break;
			}
		} else {
			break;
		}
	}
	if( !_hFile ){
		MessageBox( NULL, "Não foi possível inicializar o LBS.", "ERRO", MB_OK );
		return( LBSE_ERROR );
	}
	pBuf = MapViewOfFile( _hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0 );
	if( !pBuf ){
		MessageBox( NULL, "Não foi possível inicializar o LBS.", "ERRO", MB_OK );
		CloseHandle( _hFile );
		return( LBSE_ERROR );
	}
	if( iCount <= 0 ){
		// ler o contador do arquivo
		memcpy( &iCount, pBuf, sizeof( int ) );
		iCount++;
	}
	// gravar o contador no arquivo
	memcpy( pBuf, &iCount, sizeof( int ) );
	if( !UnmapViewOfFile( pBuf ) ){
		MessageBox( NULL, "Não foi possível inicializar o LBS.", "ERRO", MB_OK );
		CloseHandle( _hFile );
		return( LBSE_ERROR );
	}
	if( iCount == 1 ){
		// primeira instancia do LBS
		if( RecoverLicence() != LBS_OK ){
			MessageBox( NULL, "Não foi possível inicializar o LBS.", "ERRO", MB_OK );
			return( LBSE_ERROR );
		}
	}
	return( LBS_OK );
}


/***
	RecoverLicence
	Reorganiza o arquivo de controle de licencas, para recuperar alguma licenca que
	tenha sido invalidada por outra aplicacao.

	Parameters:
		- 

	Return:
		- LBS_OK ou erro

	Comments:
		- 

***/
int
RecoverLicence()
{
	char			szDirBase[ FULLNAMESIZE ];
	char			szAux[ FILENAMESIZE ];
	char			szLicFile[ FULLNAMESIZE ];
	C_RecordFile	cLicFile( LICFILE_MAGICNUMBER );

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		return( LBSE_LBSINIERROR );
	}
	sprintf( szLicFile, "%s\\%s", szDirBase, LICFILENAME );

	// verificar se o arquivo existe
	if( !C_File::Exist( szLicFile ) ){
		// arquivo nao existe.
		return( LBS_OK );
	}

	// testar o numero magico do arquivo de licencas
	{
		C_File	cfAux( szLicFile, "r", SH_DENYNO );

		if( cfAux.IsOpen() ){
			// ler o primeiro byte, que eh o numero magico.
			BYTE	bMag;

			if( cfAux.Seek( 0, SEEK_SET ) == OK ){
				if( cfAux.Read( &bMag, sizeof( bMag ) ) == OK ){
					if( bMag != LICFILE_MAGICNUMBER ){
						// numero magico invalido.
						return( LBSE_BADLICFILE );
					}
				}
			}
		}
	}

	// tentar NUMTRYLIC vezes abrir o arquivo
	for( int i = 0; i < NUMTRYLIC; i++ ){
		if( cLicFile.Open( szLicFile, sizeof( TLicInfoFixHead ), sizeof( TLicInfoFix ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cLicFile.IsOpen() ){
		// nao consegui abrir o arquivo de licencas.
		return( LBSE_BUSY );
	}

	// ler os registros do grupo 1
	TLicInfoFixHead	tHead;
	char			*szMachineName = LBSC_Session::WhatServers();
	if( !szMachineName ){
		return( LBSE_NOMEMORY );
	}
	if( cLicFile.R_ReadHead( &tHead ) != 0 ){
		// deu pau.
		delete szMachineName;
		return( LBSE_BUSY );
	}
	cLicFile.R_Seek( 0 );
	for( i = 0; i < tHead.lNumRec; i++ ){
		TLicInfoFix	tInfo;
		if( cLicFile.R_Read( &tInfo ) != OK ){
			// deu pau
			delete szMachineName;
			return( LBSE_BUSY );
		}
		int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
		if( stricmp( (char*) tInfo.tLicSerial.strSerialSvc, ::GetSerialNumber() ) == 0 ){
			// achamos um registro com o numero de serie deste LBS.
//			BOOL	bMod = FALSE;

			long	lLicFilePos = cLicFile.R_CurPos();

			// procurar maquina (registros do grupo 2)
			for( int j = 0; j < iNumUsers; j++ ){
				cLicFile.R_SeekNext();
				if( cLicFile.R_Read( &tInfo ) != OK ){
					// deu pau
					delete szMachineName;
					return( LBSE_BUSY );
				}
				if( stricmp( (char*) tInfo.tLicClient.strClient, szMachineName ) == 0 ){
					// achamos a maquina
					if( tInfo.tLicClient.iCount < 0 ){
						// achamos uma licenca invalida.
						// vamos revalidar a dita cuja
						tInfo.tLicClient.iCount = 0;
						tInfo.tLicClient.strClient = "";
						tInfo.tLicClient.strUserName = "";
						if( cLicFile.R_Write( &tInfo ) != OK ){
							// deu pau
							delete szMachineName;
							return( LBSE_BUSY );
						}
//						bMod = TRUE;
					}
				}
			}
/*			if( bMod ){
				// atualizar o registro do grupo 1, fazendo o numero de licencas
				// utilizadas ser igual a 0
				long lAuxPos = cLicFile.R_CurPos();
				cLicFile.R_Seek( lLicFilePos );
				cLicFile.R_Read( &tInfo );
				tInfo.tLicSerial.iNumUsedLic = 0;
				cLicFile.R_Write( &tInfo );
				cLicFile.R_Seek( lAuxPos );
			} */
		} else {
			// pular os registros que contem marquina/usuario
			int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
			for( int j = 0; j < iNumUsers; j++ ){
				cLicFile.R_SeekNext();
			}
			// proximo registro com numero de serie
			cLicFile.R_SeekNext();
		}
	}
	delete szMachineName;
	cLicFile.Close();
	return( LBS_OK );
}


const char *
GetMyAppPath()
{
	static char szAppFileName[MAXPATH];

	if ( !GetAppIniPath( "LBS" ) ) {
		return NULL;
	}
	else {
		strcpy( szAppFileName, GetAppIniPath( "LBS" ));
	}
	char	*pAux = strrchr( szAppFileName, '\\' );
	if( pAux ){
		*(pAux) = '\0';
		return szAppFileName;
	}
	return NULL;
}

#ifdef LBS_DEBUG
void
Printf( char *szMsg, ... )
{
	if( GetPrivateProfileInt( LBSINILBSSECTION, "PRINTF", 0, LBSINIFILE ) ){
		char 	szBuffer [ 2048 ];
		va_list argptr;
		int 	cnt;

		va_start( argptr, szMsg );
		cnt = vsprintf( szBuffer, szMsg, argptr );
		va_end( argptr );

		if( _hLogWnd ){
			int	iIndex;

			iIndex = SendMessage( _hLogWnd, LB_ADDSTRING, 0, (LPARAM) (LPCTSTR) szBuffer );
			SendMessage( _hLogWnd, LB_SELECTSTRING, iIndex-1, (LPARAM) (LPCTSTR) szBuffer );
			if( iIndex >= MAXLOGLINES ){
				// deletar metade das linhas existentes
				for( int i = 0; i < (MAXLOGLINES/2); i++ ){
					SendMessage( _hLogWnd, LB_DELETESTRING, (WPARAM) 0, 0L );
				}
			}
			UpdateWindow( _hLogWnd );
		}
	}
}

#endif


