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
// Module: BASECL.CPP
// Description:
//
//	LBSC_BASE private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Alessandro A. Jatoba'
//
// Last update: 22/01/96
//

#ifndef __BORLANDC__
#pragma warning(disable:4355)
#endif
#include	<stdlib.h>

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined __ERRNO_H && !defined _INC_ERRNO
#include	<errno.h>
#endif
#if !defined __STDARG_H && !defined _INC_STDARG
#include	<stdarg.h>
#endif
#if !defined __CTYPE_H && !defined _INC_CTYPE
#include	<ctype.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined __DIRECT_H && !defined _INC_DIRECT
#include	<direct.h>
#endif
#if !defined __DIRENT_H && !defined _INC_DIRECT
#include	DIRENT_H
#endif
#if !defined( __SHARE_H ) && !defined _INC_SHARE
#include	<share.h>
#endif
#include <math.h>
#ifndef _LB3LIST_H_
#include	<lb3list.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_BASETIMERSLIST_H_
#include	<btimerl.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif
#ifndef	_CKEYSTRUCT_H_
#include	<keystruc.h>
#endif

// $$$ API LIGHT-TEXT
#ifndef         _SESSION
#include	<lt.h>
#endif
#ifndef         _EXPRLIST
#include	<exprlist.h>
#endif

#ifndef	_DEFMACRO_H_		// usado apenas quando compilando no MSVC20
#include	<defmacro.h>
#endif
#ifndef	_DEFFUNCS_H_
#include	<deffuncs.h>
#endif

#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif

extern "C" {
#include	<personcl.h>
}

#ifndef _SLOT_
#include <slot.h>
#endif
#ifndef __LBWDEFS_H_
#include <lbwdefs.h>
#endif
#ifndef	_LBSLCKCL_H_
#include	<lbslckcl.h>
#endif
#include <baseinstance.h>

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

// para acesso ao manipulador de bases
extern BaseInstanceManager	_BasesManager;

// IMPORTANTE:
// O objeto GLT_Session eh definido automaticamente pela API Light Text e eh
// usado para inicializar algumas coisas assim que este codigo entra no ar.
// Tambem eh usado para manipular sistemas de indices.
// O arquivo lt.h o declara.


// Prototypes
int		FRemoveFile( char *, ... );
int		FRenameFile( char *, ... );
void CALLBACK	LockTimerProc( HWND, UINT, UINT, DWORD );

// Global variables
extern	HINSTANCE			_hInstance;
extern	char				_szDefUDBName[ MAXPATH ];


#ifdef	_DEBUG_CRIT_SECT_

int				_iLastBaseCritSectUsed = -1;
int				_iLastBaseArray[ 5000 ];

#define	cCS0( x, y )					cCS0( (x), (y), __FILE__, __LINE__ )
#define	cCS1( x, y )					cCS1( (x), (y), __FILE__, __LINE__ )
#define	cCS2( x, y )					cCS2( (x), (y), __FILE__, __LINE__ )
#define	cCS3( x, y )					cCS3( (x), (y), __FILE__, __LINE__ )
#define	cCS4( x, y )					cCS4( (x), (y), __FILE__, __LINE__ )
#define	cCS5( x, y )					cCS5( (x), (y), __FILE__, __LINE__ )
#define	cCS6( x, y )					cCS6( (x), (y), __FILE__, __LINE__ )
#define	cCS7( x, y )					cCS7( (x), (y), __FILE__, __LINE__ )
#define	cCS8( x, y )					cCS8( (x), (y), __FILE__, __LINE__ )
#define	cCS9( x, y )					cCS9( (x), (y), __FILE__, __LINE__ )
#define	cCS10( x, y )					cCS10( (x), (y), __FILE__, __LINE__ )
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

#ifdef __BORLANDC__
#pragma warn -par
#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	Metodo LBSC_Base
	Construtor 2 da classe LBSC_Base

	Parameters:
		- szFullBaseName : path + nome_da_base
		- szBasePassword
		- plbscsSession
		- bExclusive : modo exclusivoou nao
		- bReadOnly : operacoes permitidas na base
		- bMaintenance : modo manutencao ou nao
		- bCheckVersion : checar versao de LB1 ou nao. Default = TRUE.
	Return:

	Comments:

***/

LBSC_Base::LBSC_Base( const LBSC_Ticket *lbscTicket, const char *szFullBaseName,
			const char *szBaseLongNamePar,
			const char *szBasePassword,
			LBSC_Session *plbscsSession, BOOL bExclusive,
			BOOL bReadOnly, BOOL bMaintenance, BOOL bCheckVersion ):
	C_LeaveCritSect<C_GlobalBaseCritSect>( _pcGlobalBaseCritSect ),
	lbscrCurrRecord( this ),
	lbscpParser( this ),
	epEntParser( this )
{
	bBaseObjOk = TRUE;
	Init();
	int iRet = Open( lbscTicket, (char*)szFullBaseName, (char*) szBaseLongNamePar, (char*)szBasePassword, 
			plbscsSession, bExclusive, bReadOnly, bMaintenance, bCheckVersion );
	if( iRet == LBSE_BADUSERBASE ){
		// deu pau na abertura da UDB e nao foi possivel
		// reindexa-la. Vamos tentar novamente.
		iRet = Open( lbscTicket, (char*)szFullBaseName, (char*) szBaseLongNamePar, (char*)szBasePassword, 
				plbscsSession, TRUE, FALSE, FALSE, bCheckVersion );
		if( iRet == LBS_OK ){
			Close();
			iRet = Open( lbscTicket, (char*)szFullBaseName, (char*) szBaseLongNamePar, (char*)szBasePassword, 
				plbscsSession, bExclusive, bReadOnly, bMaintenance, bCheckVersion );
		} else {
			iRet = LBSE_BADUSERBASE;
		}
	}
	if( iRet != LBS_OK && iRet != LBSW_OPENNOIS && iRet != LBSW_OPENBUTNEEDREPROC ){
		bBaseObjOk = FALSE;
	}
}


/***
	Metodo LBSC_Base
	Construtor 3 da classe LBSC_Base

	Parameters:
		- szFullBaseName : path + nome_da_base
		- plbscsSession
		- bMagic : Numero mágico inicial da base

	Return:

	Comments:

***/

LBSC_Base::LBSC_Base( const LBSC_Ticket *lbscTicket, const char *szFullBaseName, LBSC_Session *plbscsSession, BOOL bExclusive, BOOL bReadOnly, BOOL bMaintenance ):
	C_LeaveCritSect<C_GlobalBaseCritSect>( _pcGlobalBaseCritSect ),
	lbscrCurrRecord( this ),
	lbscpParser( this ),
	epEntParser( this )
{
	Init();
	bPrivateCreation = TRUE;
	bBaseObjOk = TRUE;
	int iRet = Open( lbscTicket, (char *) szFullBaseName, (char *) szFullBaseName, "$$$", plbscsSession, bExclusive, bReadOnly, bMaintenance );
	if( iRet == LBSE_BADUSERBASE ){
		// deu pau na abertura da UDB e nao foi possivel
		// reindexa-la. Vamos tentar novamente.
		iRet = Open( lbscTicket, (char *) szFullBaseName, (char *) szFullBaseName, "$$$", plbscsSession, TRUE, FALSE, FALSE );
		if( iRet == LBS_OK ){
			Close();
			iRet = Open( lbscTicket, (char *) szFullBaseName, (char *) szFullBaseName, "$$$", plbscsSession, bExclusive, bReadOnly, bMaintenance );
		} else {
			iRet = LBSE_BADUSERBASE;
		}
	}
	if( iRet != LBS_OK && iRet != LBSW_OPENNOIS && iRet != LBSW_OPENBUTNEEDREPROC ){
		bBaseObjOk = FALSE;
	}
}


/***
	Metodo LBSC_Base
	Construtor 4 da classe LBSC_Base

	Parameters:
		- szFullBaseName : path + nome_da_base
		- bMagic : Numero mágico inicial da base

	Return:

	Comments:

***/

LBSC_Base::LBSC_Base( const char *szFullBaseName ):
	C_LeaveCritSect<C_GlobalBaseCritSect>( _pcGlobalBaseCritSect ),
	lbscrCurrRecord( this ),
	lbscpParser( this ),
	epEntParser( this )
{
	char		szDrive[ MAXDRIVE ];
	char		szDir[ MAXDIR ];
	char		szExt[ MAXEXT ];
	memset( szExt, 0, MAXEXT );

	Init();
	szBasePath = szFullBaseName;
	szBasePath.Upper();
	fnsplit( szBasePath, szDrive, szDir, szBaseName, szExt );
	bPrivateCreation = TRUE;
	bBaseObjOk = FALSE;
}


/***
	Metodo Open
	Abre a base

	Parameters:
		-
	Return:
		- LBS_OK ou erro
	Comments:
		- Este metodo eh PRIVADO
***/
int
LBSC_Base::Open( const LBSC_Ticket *lbscTicket, char *szFullBaseName, 
				char *szBaseLongNamePar, char *szBasePassword,
		        LBSC_Session *plbscsSession, BOOL bExclusive,
		        BOOL bReadOnly, BOOL bMaintenance, BOOL bCheckVersion )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Open") );

	char		szDrive[ MAXDRIVE ];
	char		szDir[ MAXDIR ];
	char		szExt[ MAXEXT ];
	char		szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char		*szBackSlash = NULL;
	BOOL		bIndexFailed = FALSE;

	LB1.bMagicNumber = 0;
	LB3.bMagicNumber = 0;

	// reajusta as variaveis bMaintenance e bReadOnly, dependendo do
	// login em LBSC_Session (mono-usuario ou nao)
	if( plbscsSession && plbscsSession->bIsMono ){
		bMaintenance = TRUE;
		bReadOnly = TRUE;
	}
	szBasePath = szFullBaseName;
	szBaseLongName = szBaseLongNamePar;
	plbscsOwnerSession = plbscsSession;
	bIsExclusive = bExclusive ? bExclusive : bMaintenance;
	if ( ::GetTypeInt() == PE_MONO && !LBSC_ServerConfig::ReadOnlyFileSystem() ){	// abrir em modo exclusivo sempre se for copia mono
		bIsExclusive = TRUE;
	}
	bIsReadOnly = bReadOnly;

	if( !szFullBaseName ){
		ERETURN( LBSE_INVALIDNAME );
	}
	strupr( szFullBaseName );
	if( szBasePassword ){
		strupr( szBasePassword );
	}

	// Splits the base name
	fnsplit( szFullBaseName, szDrive, szDir, szBaseName, szExt );
	if( szDrive[ 0 ] != '\0' ){
		ERETURN( LBSE_INVALIDNAME );
	}

	// pegar o nome do diretorio base (dir_base)
	GetDirBase( szAux );
	strupr( szAux );
	strupr( szFullBaseName );

	sprintf( (char*) szBasePath, "%s\\%s", szAux, szFullBaseName );
	strupr( (char*) szBasePath );

	char	*szBaseDir = strstr( (char*) szBasePath, szAux );
	if( szBaseDir ){
		szCompleteBaseName = szBaseDir + strlen( szAux ) + 1;
	} else {
		szCompleteBaseName = szBaseName;
	}

	// verificar se o diretorio da base existe
	if( chdir( (char*) szBasePath ) != 0 ){
		// diretorio nao existe.
		ERETURN( LBSE_BASENOTFOUND );
	}


	// Abrir os arquivos...
	if( szDrive[0] ){
		if( _chdrive( toupper( (int) szDrive[0] ) - FIRSTDRIVELETTER + 1 ) != 0 ){
			ERETURN( LBSE_DRIVENOTFOUND );
		}
	}
	if( OpenAllFiles( bCheckVersion ) != LBS_OK ){
		ERETURN( LastError() );
	}

	// verifica se eh necessario usar compressao ou nao na gravacao dos dados

	bUsingCompress = LBSC_ServerConfig::UsingCompress();

	// Carrega o registro de cabecalho para
	{
		LB1.R_ReadHead();
		LB1.tcrHead.szUserBase.Upper();
		LB1.tcrHead.szOwnerName.Upper();
		LB1.tcrHead.szLastModifyUserName.Upper();
		LB1.tcrHead.szMaintenancePassword.Upper();
		LB1.tcrHead.szBasePassword.Upper();
	}

	// Carregando as ACLs
	if ( LB1.tcrHead.bBaseType == USER_BASE ) {
		ClearAllAcls();
	} else {
		LoadAllAcls( GetBaseVersion() );
	}

	// vamos logo verificar se a password informada esta' correta.
	// se estiver, ja' libera o cara para passar por cima das ACLs, sem
	// burocracia
	if( LB1.tcrHead.szBasePassword == (char*) "" ||
		LB1.tcrHead.szBasePassword != (char*) szBasePassword ){
		// a password da base eh vazia (o que significa que "apenas" as ACLs podem
		// validar o cara) ou a que o cara informou esta' errada
		bIsBasePasswdCorrect = FALSE;
	} else {
		bIsBasePasswdCorrect = TRUE;
	}
	if( !bCheckVersion && LB1.tcrHead.bBaseType == USER_BASE ){
		// se eu nao estou verificando versao de base *e* a base
		// que estou abrindo eh uma UDB, entao vamos deixar a senha
		// de lado. Isso eh util para podermos converter UDBs com versoes
		// antigas sem presisar saber a senha. Ate' poderiamos descobrir a 
		// senha, mas precisariamos que o usuario indicasse (ai' nao poderiamos
		// fazer conversoes automaticas de UDBs) ou criar um codigo novo para
		// abrir o header de LB1 e extrair a senha.
		bIsBasePasswdCorrect = TRUE;
		bPrivateCreation = TRUE;
	}

	// Verifying if the loaded password is correct
	if( !bPrivateCreation && ( plbscsSession && !plbscsSession->bIsMono) ){
		// vamos verificar as possibilidades de permissao para o cara:

		// o cara quer abrir a base para manutencao?
		if( bMaintenance || bIsExclusive ){
			// se chegamos aqui eh porque os arquivos foram abertos em modo
			// exclusivo, pois no inicio deste metodo, forcamos a barra para
			// isso, tendo em vista a flag bMaintenance == TRUE;

			BOOL bUdbAdmUser = ( GetBaseType() == USER_BASE &&
						( plbscsSession->plbscuUser->GetUserType() == MASTER_USER || 
						LB1.tcrHead.szOwnerName == plbscsSession->plbscuUser->GetUserName()) );
			// vamos checar as ACLs
			// (na verificacao de ACL checamos se o usuario eh o dono da base)
			if( !bUdbAdmUser && VerifyPermission( plbscsSession->GetUserName(), (long) ID_ASTERISK, 
					USERFIELD, ACL_ADM ) != LBS_OK ){
				// a password passada bate com a de manutencao?
				if( LB1.tcrHead.szMaintenancePassword == (char*) "" ){
					// apenas o dono pode abrir a base.
					// permissao negada.
					CloseAllFiles();
					ERETURN( LBSE_ONLYBASEOWNER );
				}

				if( LB1.tcrHead.szMaintenancePassword != (char*) szBasePassword ){
					// senha errada.
					// permissao negada.
					CloseAllFiles();
					ERETURN( LBSE_INVALIDPASSWORD );
				}
			}
			bFullAccess = bMaintenance ? TRUE : FALSE;

			// Monta a lista de campos
			if( GetBaseFieldList() == LBSE_NOSTRUCT ){
				bStruct = FALSE;
				// nao fecha os arquivos
				PRINTLOG( _clLBSLog, ("LBSC_Base::Open::GetBaseFieldList") );
				INITLOG( _clLBSLog );
				ERETURN( LBSE_ERROR );
			}
		} else {
			// antes de mais nada, devemos nos lembrar que o cara
			// nao possui FullAccess para a base, pois ele nao esta'
			// tentando abri-la para manutencao.

			bFullAccess = FALSE;

			// Monta a lista de campos (isso deve ser feito aqui, pois
			// a verificacao de ACLs requer que a lista de campos ja' exista)
			if( GetBaseFieldList() == LBSE_NOSTRUCT ){
				bStruct = FALSE;
				// nao fecha os arquivos
				PRINTLOG( _clLBSLog, ("LBSC_Base::Open::GetBaseFieldList") );
				INITLOG( _clLBSLog );
				ERETURN( LBSE_ERROR );
			}

			// a base eh privada?
			if( LB1.tcrHead.bBaseType != BASE_PUBLIC && LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ){
				// a base eh privada.
				// vamos checar as ACLs
				// (na verificacao de ACL, checamos se o usuario eh o dono dela)
				if( VerifyPermission( plbscsSession->GetUserName(), (long) ID_ASTERISK, 
						USERFIELD, ACL_ASTERISK ) != LBS_OK ){
					// Ate' aqui, nenhuma permissao.
					// a password passada bate com a da base?
					// antes de checar a password, vamos ver se a password
					// da base eh vazia ( "" ). Se for, significa que nao eh
					// possivel acessa-la via password; o cara tem que ter permissao
					// de ACL.
					if( LB1.tcrHead.szBasePassword == (char*) "" ){
						// senha vazia. o cara tem que ser o dono da base.
						CloseAllFiles();
						ERETURN( LBSE_NOPERMISSION );
					}
					if( LB1.tcrHead.szBasePassword != (char*) szBasePassword ){
						// nao tem jeito.
						// a base eh privada, mas o cara
						// nao informou a password, 
						// nem eh o dono da base, nem consta nas ACLs.
						CloseAllFiles();
						ERETURN( LBSE_INVALIDPASSWORD );

					}
				}
				// ok. podemos prosseguir.
				// a base eh privada, mas o usuario informou a
				// password correta.
			}
			// ok. a base eh publica. podemos prosseguir sem checar
			// ACLs ou password.
		}
	} else {
		// Monta a lista de campos
		if( GetBaseFieldList() == LBSE_NOSTRUCT ){
			bStruct = FALSE;
			// nao fecha os arquivos
			PRINTLOG( _clLBSLog, ("LBSC_Base::Open::GetBaseFieldList") );
			INITLOG( _clLBSLog );
			ERETURN( LBSE_ERROR );
		}
	}

	// Filling the current record with information got from LB1 file
	if( LB1.tcrHead.lNumRecords > 0 ){
		LB1.R_Seek( LB1.tcrHead.lFirstRecActivePos );
		ReadRecord( lbscTicket );
	} else {
		lbscrCurrRecord.Clear();
		lbscrCurrRecord.SetIsUndefined( TRUE );
	}

	// se der pau na abertura do sistema de indices, deveremos retornar um 
	// warning para a aplicacao indicando que ela deve reprocessar os
	// indices.
	if ( !OpenIndexSystem() ){
		bIndexFailed = TRUE;
	}

	// setar o tamanho minimo de uma chave para ser indexada
	// Seta o tempo de espera para nova tentativa de lock de registro
	{
		this->iLockTimeSleep = LBSC_ServerConfig::LockTimeSleep();

		// Seta o time-out de lock de registro
		this->iLockTimeOut = LBSC_ServerConfig::LockTimeOut();
	}

	// cria a LO fisica na lista de LO's. A LO fisica e' a de numero
	// 0 (zero) na lista de LO's.
	if( pcOLList ){
		delete pcOLList;
	}
	pcOLList = new LBSC_OLList;
	if( pcOLList ){
		LBSC_Expr	*pExpr = new LBSC_Expr;
		pcOLList->Add( pExpr, TAIL );
	}

	if( bIndexFailed ){
		// podemos regerar o sistema de indices automaticamente,
		// desde que a base que estamos tentando abrir seja
		// uma UDB.
		// Senao, deixamos a cargo da aplicacao a reconstrucao do
		// sistema de indices.
		if( LB1.tcrHead.bBaseType == USER_BASE ){
			// reindexacao total
			int iRet = IndexAll( lbscTicket );
			if( iRet != LBS_OK ){
				// deu pau
				Close();
				ERETURN( LBSE_BADUSERBASE );
			}
			bIndexFailed = FALSE;
		} else {
			if ( LastError() == LBSE_TOOMANYOPENFILES ) {
				ERETURN( LBSE_TOOMANYOPENFILES );
			}
			// vamos apenas destruir o sistema de indices da base
			RemoveIndexSystem();
		}
	}

	if( LB1.tcrHead.bBaseType != USER_BASE ){
		// temos que adicionar o nome da base na lista de bases
		// abertas em disco (apenas se este LBS for REDE)
		if( ::GetTypeInt() == PE_REDE ){
			AddBaseInfoFile( szBaseName );
		}
	}
	if( bIndexFailed ){
		// a abertura do sistema de indices falhou.
		if( GetBaseVersion() < OCCTREE_MAGICNUMBER ){
			// base precisa de reprocessamento para poder ser aberta
			ERETURN( LBSW_OPENBUTNEEDREPROC );
		}
		// base precisa ser reindexada.
		ERETURN( LBSW_OPENNOIS );
	}

	LOGUSE( OPEN_BASE, 1);
	ERETURN( LBS_OK );
}



/***
	Metodo Close
	Fecha a base

	Parameters:

	Return:

	Comments:

***/
int
LBSC_Base::Close()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Close") );

	LOGUSE( CLOSE_BASE, 1 );

	if( !LB1.IsOpen() ){
		// LB1 estah fechado
		CloseAllFiles();	// Para seguranca
		ERETURN( LBS_OK );
	}
	// Gravar as ACL's
	if( bACLChanged && !bIsReadOnly ){
		// gracas aa regiao critica nao vai haver problema na hora de salvar/ler acls
		SaveAllAcls( GetBaseVersion() );
	}

	{
		// a regiao critica abaixo protege toda a operacao de atualizacao de registro
		CLBAutoRegCrit	AutoRegCritDataFile( pBaseInstance ? &(pBaseInstance->DataFileCritSect) : NULL );

		// criar objeto para fazer lock e gravar o header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( bBaseUpdated && !bIsReadOnly ){
			{
				if( cLB1_LockHead.IsLocked() ){
					LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
					LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
					// agora grava o header...
					LB1.LB1_WriteHead();
				}
			}

			Flush( (const LBSC_Ticket*) plbscsOwnerSession->plbsctTicket );
		}
		// Nao eh necessario gravar as StopWords pois estas sao setadas
		// via arquivo, portanto  o arquivo esta sempre atualizado
	}

	// Fechar os arquivos
	CloseAllFiles();

	if( LB1.tcrHead.bBaseType != USER_BASE ){
		// temos que retirar o nome da base na lista de bases
		// abertas em disco (apenas se este LBS for REDE)
		if( ::GetTypeInt() == PE_REDE ){
			DelBaseInfoFile( szBaseName );
		}
	}

	if( plbscsOwnerSession != NULL ){
		plbscsOwnerSession = NULL;	// NAO PODE DELETAR
	}
	if( pvUserData ){
		delete pvUserData;
	}

	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	if( szNavigationKey ){
		delete szNavigationKey;
		szNavigationKey = NULL;
	}
	// Fechar sistema de indices
	if( plbscisIndexSystem ){
		delete plbscisIndexSystem;
		plbscisIndexSystem = NULL;
	}

	ERETURN( LBS_OK );
}


/***
	Metodo Create
	Cria uma base no disco

	Parameters:
		- szFullBaseName : path + nome_da_base
		- szBasePassword
		- bBaseType
		- bEncrypt
		- plbscsSession
		- szUserBaseName : nome da BU a ser associada a base a ser
				   criada. Se omitido assume-se a BU default.
		- dwUserBaseIdPar : identificador da BU a ser associada a base.

	Return:
		LBS_OK se conseguir criar a base ou erro.

	Comments:
		- A base criada nao esta pronta para uso.
		- O metodo retorna NULL se ja existir uma base com mesmo nome
		  no servidor.

***/
int
LBSC_Base::Create( const LBSC_Ticket *plbsctTicket, char *szFullBaseName,
		   char *szBasePassword, char *szMaintenancePassword,
		   BYTE bBaseType, BOOL bEncrypt,
		   LBSC_Session *plbscsSession, char *szUserBaseName = NULL,
		   TField *ptfField, DWORD dwUserBaseIdPar, int iSlotNum,
		   int iCountNum, int iMaxKeySizePar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Create") );

#ifdef __BORLANDC__	
	int			ifnResult;
#endif
	char			szDrive[ MAXDRIVE ];
	char			szDir[ MAXDIR ];
	char			szExt[ MAXEXT ];
	char			szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char			*szBackSlash = NULL;
	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( iSlotNum + iCountNum );

	bIsExclusive = TRUE;
	plbscsOwnerSession = plbscsSession;
	szBasePath = szFullBaseName;
	LB1.tcrHead.uiLastFieldId = 0;
	LB1.tcrHead.iSlotNum = iSlotNum;
	LB1.tcrHead.iCountNum = iCountNum;
	LB1.tcrHead.dwBaseId = GetTickCount();
	LB1.tcrHead.dwUserBaseId = dwUserBaseIdPar;
	LB1.tcrHead.szOwnerName = plbscsOwnerSession->GetUserName();
	LB1.tcrHead.szLastModifyUserName = LB1.tcrHead.szOwnerName;
	LB1.tcrHead.lFirstRecActivePos = LB1.tcrHead.lLastRecPos = LB1.tcrHead.lLastRecActivePos = -1;
	LB1.tcrHead.bBaseType = bBaseType;
	LB1.tcrHead.bIsEncrypt = bEncrypt;
	LB1.tcrHead.szBasePassword = szBasePassword;
	LB1.tcrHead.szMaintenancePassword = szMaintenancePassword;
	LB1.tcrHead.ulCreateDate = C_Date().Hash();
	LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
	LB1.tcrHead.szUserBase = "";

	// Setar o numero magico para o mais recente
	LB1.bMagicNumber = CURRENT_MAGICNUMBER;
	// convencionamos usar o numero magico do LB3 para armazenar a versao da UDB; se nao for udb, recebe a mesma versao da base
	LB3.bMagicNumber = (bBaseType == USER_BASE ? CURRENT_UDBMAGICNUMBER : CURRENT_MAGICNUMBER);

	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( bBaseObjOk == FALSE ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_OBJNOTOK );
	}

	// nao devemos permitir criacao de bases sem campos.
	if( !ptfField || ptfField[ 0 ].IsZero() ){
		// a base tem que ter pelo menos um campo
		ERETURN( LBSE_NOFIELD );
	}

	// Splits the base name
	fnsplit( szFullBaseName, szDrive, szDir, szBaseName,szExt );
	if( szDrive[ 0 ] != '\0' ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_INVALIDNAME );
	}

	// pegar o nome do diretorio base (dir_base)
	GetDirBase( szAux );
	strupr( szAux );
	strupr( szFullBaseName );
	sprintf( (char*) szBasePath, "%s\\%s", szAux, szFullBaseName );
	strupr( szBasePath );

	char	*szBaseDir = strstr( (char*) szBasePath, szAux );
	if( szBaseDir ){
		szCompleteBaseName = szBaseDir + strlen( szAux ) + 1;
	} else {
		szCompleteBaseName = szBaseName;
	}

	// seta o tamanho maximo de uma
	// chave para o sistema de indices (apenas se o iMaxKeySize nao foi
	// informado ou foi informado com valor zero)
	LB1.tcrHead.iMaxKeySize = iMaxKeySizePar > 0 ? iMaxKeySizePar : DEFAULT_MAXKEYSIZE;

	// Inicio codigo Katyusco
	// agora vou pegar o tamanho da parte inteira de um dado numerico
	LB1.tcrHead.iIntPart = INTEGER_PART;
	
	// idem para a parte decimal
	LB1.tcrHead.iDecPart = DECIMAL_PART;
	// Fim codigo Katyusco

		// $$$ Preencher alguns atributos do objeto base
	if( LB1.tcrHead.bBaseType != USER_BASE ){
		if( szUserBaseName && ( szUserBaseName[ 0 ] != '\0' ) ){
			LB1.tcrHead.szUserBase = szUserBaseName;
		} else {
			LB1.tcrHead.szUserBase = _szDefUDBName;
		}
	}

	// Vamos criar os arquivos...
	if( mkdir( (char*) szBasePath ) == 0 ){
		if( szDrive[0] ){
			if( _chdrive( toupper( (int) szDrive[0] ) - FIRSTDRIVELETTER + 1 ) != 0 ){
				TStructHeadRec::Free( ptsrStructRecHead );
				ERETURN( LBSE_DRIVENOTFOUND );
			}
		}
		if( OpenAllFiles() != LBS_OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
	} else {
		TStructHeadRec::Free( ptsrStructRecHead );
		int iErr = errno;
		ERETURN( LBSE_DSKERROR );
	}

	// Criar o Sistema de Indices
	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) szBaseName );
	RemoveIndexSystem();
	if( !CreateIndexSystem() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		if ( LastError() == LBSE_TOOMANYOPENFILES ) {
			ERETURN( LBSE_TOOMANYOPENFILES );
		}
		ERETURN( LBSE_NOMEMORY );
	}
	// Fechar sistema de indices
	delete plbscisIndexSystem;
	plbscisIndexSystem = NULL;

	lbscrCurrRecord.DelAllFields();
	bFullAccess = TRUE;
	// cria a lista de campos da nova base
	int iNumFields = 0;
	while( !(ptfField [ iNumFields ].IsZero()) ){
		if( AddField( plbsctTicket, ptfField [ iNumFields ].szFieldAliasName,
			ptfField [ iNumFields ].szFieldDescription,
			ptfField [ iNumFields ].szPasswordName,
			ptfField [ iNumFields ].tftFieldType,
			ptfField [ iNumFields ].lFieldSize,
			ptfField [ iNumFields ].tiaIndexAttrib,
			ptfField [ iNumFields ].uiFieldAttrib ) != OK ){
			break;
		}
		iNumFields++;
	}
	lbscrCurrRecord.SortFieldLists();

	// nao eh necessario entar em regiao critica global porque a base esta sendo criada
	// agora, logo nao tem acesso concorrente ainda
	if( LB1.LB1_WriteHead() != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	
	// Tratamento de ACL
	GenerateOwnerACL();

	// seta o dono da base
	if( SetOwnerBase() != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bFullAccess = 0;


	// gerar o arquivo default de go-words
	char	*szGWAux = NULL;
	char	szMsg[ 512 ];

	sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	C_File	cGWFile( szAux, "wt" );

	for( int i = 0; i < GWTABSIZE; i++ ){
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			sprintf( szMsg, "LBSGW_%d", i );
			szGWAux = _pcInter->GetGenMsgsAppVar( szMsg );
		} else {
			szGWAux = NULL;
		}
		if( szGWAux ){
			sprintf( szMsg, "%s", szGWAux );
			delete szGWAux;
		} else {
			strcpy( szMsg, _LBS_GoWordsMsg[ i ] );
		}
		cGWFile.WriteLine( szMsg );
	}

	// Criar o arquivo de ACLs para o dono da base
	if( SaveAllAcls( GetBaseVersion() ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}

	// Criar o registro de cabecalho em LB1
	// nao eh necessario entar em regiao critica global porque a base esta sendo criada
	// agora, logo nao tem acesso concorrente ainda
	if( LB1.LB1_WriteHead() != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}

	// Criar o registro de cabecalho em LB3
	ptsrStructRecHead->iNumberOfFields = iNumFields;
	if( LB3.R_WriteHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	TStructHeadRec::Free( ptsrStructRecHead );

	// nao eh necessario entar em regiao critica global porque a base esta sendo criada
	// agora, logo nao tem acesso concorrente ainda
	if( LB1.LB1_WriteHead() != OK ){
		ERETURN( LBSE_ERROR );
	}

	if ( LB1.tcrHead.bBaseType == USER_BASE ) {
		// vamos setar os slots de cada campo pra uso via LBW (caso ja nao existam)
		AddDefaultUDBSlots();
	}

	CloseAllFiles();
	ERETURN( LBS_OK );
}

/***
	Metodo Delete
	Deleta uma base do disco

	Parameters:

	Return:
		LBS_OK se conseguir deletar a base ou erro.

	Comments:
		- O metodo simplesmente liga uma flag; a base somente serah
		  destruida quando o destrutor for chamado.

***/
int
LBSC_Base::Delete()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Delete") );

	bSelfDelete = TRUE;
	ERETURN( LBS_OK );
}



/***
	Metodo RenameFile
	Renomeia um arquivo

	Parameters:
		- pcfNewFile
		- pcfOldFile
		- szNewExt
		- szOldExt

	Return:
		LBS_OK se conseguir renomear ou erro.

	Comments:

***/
int
LBSC_Base::RenameFile( C_File *pcfNewFile, C_File *pcfOldFile, char *szNewExt,
			char *szOldExt )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::RenameFile") );

	char			szFileTerminalName[ FILENAMESIZE ];
	char			szAux[ FILENAMESIZE ];

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( pcfOldFile != NULL ){
		delete pcfOldFile;
	}
	if( pcfNewFile != NULL ){
		delete pcfNewFile;
		pcfNewFile = NULL;
	}

	sprintf( szFileTerminalName, "%s%s", (char*)szBaseName, szOldExt );
	remove( szFileTerminalName );

	sprintf( szAux, "%s%s", (char*)szBaseName, szNewExt );
	rename( szAux, szFileTerminalName );
	sprintf( szFileTerminalName, "%s%s", (char*)szBaseName, szOldExt );

	pcfOldFile = new C_File( szFileTerminalName );

	ERETURN( LBS_OK );
}


/***
	Metodo OpenAllFiles
	Abre todos os arquivos de uma base

	Parameters:
		- bCheckVersion ->	default = TRUE. Indica se a versao de LB1 deve
							ser verificada. Versoes que precisam de conversao
							sao checadas e, em caso de necessidade de conversao,
							o metodo falha na abertura de LB1. Se o valor desse
							parametro for FALSE, entao essa verificacao nao
							eh feita e o arquivo LB1 eh aberto mesmo que precise
							de conversao.

	Return:
		LBS_OK se conseguir abrir ou erro.

	Comments:

***/
int
LBSC_Base::OpenAllFiles( BOOL bCheckVersion )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OpenAllFiles") );

	char	szAux[ FILENAMESIZE ];
	char	*szMode = NULL;
	int		iShFlag;
	int		iNumberOfSlots;
	int		iNumberOfCounters;

	// vamos verificar se temos permissao de gravacao no diretorio das bases
	if ( LBSC_ServerConfig::ReadOnlyFileSystem() ){
		bIsReadOnly = TRUE;
	}
	
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( bIsReadOnly == TRUE ){
		szMode = "rb";
	} else {
		szMode = NULL;
	}
	if( bIsExclusive == TRUE ){
		iShFlag = SH_DENYRW;
	} else {
		iShFlag = SH_DENYNO;
	}
	int iRet = LBS_OK;

	sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONTROLFILEEXT );
	BOOL bExist = C_LB1::Exist( szAux );
	if( !bExist ){
		iNumberOfSlots = LB1.tcrHead.iSlotNum;
		iNumberOfCounters = LB1.tcrHead.iCountNum;
	} else {
		// verificar a versao da base (na verdade, do arquivo LB1)
		int iVer = LBSC_Base::GetBaseVersion( szAux );
		if( bCheckVersion ){
			if ( iVer < CURRENT_MAGICNUMBER && iVer >= BEFORECRYPTO_MAGICNUMBER ){
				// versao velha; precisa de conversao.
				ERETURN( LBSE_OLDBASEVERSION );
			}
			if ( iVer != CURRENT_MAGICNUMBER ){
				// erro na abertura do arquivo. nao podemos dizer nada sobre a versao.
				ERETURN( (bIsExclusive ? LBSE_CANTOPENEXCLUSIVE : (bIsReadOnly ? LBSE_CANTOPENRDONLY : LBSE_CANTOPENFILE)) );
			}
		} else {
			if ( iVer == BEFORECRYPTO_MAGICNUMBER ){
				// versao muito velha; precisa de conversao de qualquer jeito.
				ERETURN( LBSE_OLDBASEVERSION );
			}
			if ( iVer > CURRENT_MAGICNUMBER || iVer < BEFORECRYPTO_MAGICNUMBER ){
				// erro na abertura do arquivo. nao podemos dizer nada sobre a versao.
				ERETURN( (bIsExclusive ? LBSE_CANTOPENEXCLUSIVE : (bIsReadOnly ? LBSE_CANTOPENRDONLY : LBSE_CANTOPENFILE)) );
			}
		}
	}

	// LB1
	if( LB1.Open( szAux, LB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, szMode, iShFlag ) == OK ){
		// Verifica se a base estah criptografada. Se estiver,
		// chama o metodo para LB1 que liga a criptografia
		// e seta LB1.tcrHead.bIsEncrypt para que os outros arquivos
		// ja sejam abertos com criptografia.
		if( LB1.R_FileSize() > 0 || bExist ){
			// ler o numero magico
			LB1.Seek( 0, SEEK_SET );
			LB1.Read( &LB1.bMagicNumber, sizeof( LB1.bMagicNumber ) );

			// atualizar atributos do objeto
			iNumberOfSlots = LB1.tcrHead.iSlotNum;
			iNumberOfCounters = LB1.tcrHead.iCountNum;
			if( LB1.tcrHead.bIsEncrypt ){
				LB1.R_SetRecKey( LBDEFKEY );
			}
			// recuperar o registro perdido na ordenacao da base (LO fisica)
			// (somente se houve erro durante a ultima ordenacao)
			sprintf( szAux, "%s\\SECURE.LB", (char*) szBasePath );
			if( C_File::Exist( szAux ) ){
				// deu pau na ultima ordenacao da LO fisica
				if( bIsReadOnly ){
					// o usuario pediu para abrir a base em
					// modo read-only, mas a base esta' danificada.
					// eh necessario abri-la para gravacao para que
					// o arquivo LB1 seja recuperado.
					LB1.Close();
					ERETURN( LBSE_BADBASENOTRDONLY );
				}

				C_File	cfSecure( szAux, "r", SH_DENYRW, TRUE );
				if( cfSecure.IsOpen() ){
					long		lPos;
					TControlRec	tAux;
					if( cfSecure.Read( &lPos, sizeof( long ) ) == OK ){
						if( cfSecure.Read( &tAux, sizeof( TControlRec ) ) == OK ){
							if( LB1.R_Seek( lPos ) == OK ){
								LB1.R_Write( &tAux );
							}
						}
					}
					cfSecure.Close();
				}
			}

			// checar a consistencia do header de LB1
			if( CheckLB1Header() != LBS_OK && !bIsExclusive ){
				// o header esta' fudido
				LB1.Close();
				PRINTLOG( _clLBSLog, ("LBSC_Base::OpenAllFiles::LBSE_INCONSISTBASE ") );
				INITLOG( _clLBSLog );
				ERETURN( LBSE_INCONSISTBASE );
			}
		}
		// LB3
		sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char*)szBaseName, STRUCTFILEEXT );
		if( LB3.Open( szAux, LB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, szMode, iShFlag, iNumberOfSlots, iNumberOfCounters ) == OK ){
			if( LB3.R_FileSize() > 0 || bExist ){
				// ler o numero magico
				LB3.Seek( 0, SEEK_SET );
				LB3.Read( &LB3.bMagicNumber, sizeof( LB3.bMagicNumber ) );
			}

			// verificar a versao da UDB
			if ( bCheckVersion && LB1.tcrHead.bBaseType == USER_BASE && GetUDBVersion() < CURRENT_UDBMAGICNUMBER ) {
				LB1.Close();
				LB3.Close();
				ERETURN( LBSE_OLDBASEVERSION );
			}

			// LB4

			BOOL bNewInstance = FALSE;
			// o lb4 deve ser sempre aberto em modo read/write, exceto se estivermos num sistema de arquivos read/only
			pBaseInstance = _BasesManager.Search( szBasePath );	
			if ( !pBaseInstance ) {
				bNewInstance = TRUE;
				pBaseInstance = new BaseInstance(szBasePath, szBaseName, LBSC_ServerConfig::ReadOnlyFileSystem() );
			}
			if ( pBaseInstance ) {
				if ( pBaseInstance->OpenDataFile() ) {
					// LB2
					sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char*)szBaseName, SLOTFILEEXT );
					if( cfSlotsFile.Open( szAux, LB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, szMode, iShFlag ) == OK ){
						if ( bNewInstance ) {
							_BasesManager.Add(pBaseInstance);
						}
						ERETURN( LBS_OK );
					}
				}
				if ( errno == EMFILE ) {
					iRet = LBSE_TOOMANYOPENFILES;
				}
				LB1.Close();
				LB3.Close();
				if ( bNewInstance ) {
					// houve algum erro e nao incluiu na cache... detonar!
					delete pBaseInstance;
					pBaseInstance = NULL;
				}
			}
			PRINTLOG( _clLBSLog, ("LBSC_Base::OpenAllFiles::LB4ERR") );
			INITLOG( _clLBSLog );
		} else {
			PRINTLOG( _clLBSLog, ("LBSC_Base::OpenAllFiles::LB3ERR") );
			INITLOG( _clLBSLog );
		}
	} else {
		PRINTLOG( _clLBSLog, ("LBSC_Base::OpenAllFiles::LB1ERR") );
		INITLOG( _clLBSLog );
	}
	CloseAllFiles();
	if ( iRet != LBS_OK ) {
		ERETURN( iRet );
	}
	ERETURN( (bIsExclusive ? LBSE_CANTOPENEXCLUSIVE : (bIsReadOnly ? LBSE_CANTOPENRDONLY : LBSE_CANTOPENFILE)) );
}



/***
	Metodo CloseAllFiles
	Fecha todos os arquivos de uma base

	Parameters:

	Return:
		LBS_OK se conseguir fechar ou erro.

	Comments:

***/
int
LBSC_Base::CloseAllFiles()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CloseAllFiles") );

	// terminar o eventual timer de lock
	KillLockTimer();

	LB1.Close();
	LB3.Close();
	cfSlotsFile.Close();

	ERETURN( LBS_OK );
}


/***
	Metodo RemoveDir
	Deleta os arquivos dentro de um diretório e depois remove
	o proprio. Este metodo age recursivamente no caso do Visual C++.
	Para o Borland, a recursividade ainda nao foi implementada.

	Parameters:
		- szDirName	-> Diretorio que contem os arquivos
		- bDestroyDir	-> Flag indicando se o diretorio tambem
				   deve ser destruido.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:

***/
int
LBSC_Base::RemoveDir( char *szDirName, BOOL bDestroyDir )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::RemoveDir") );

	char		szPath [ PATHNAMESIZE ];
	WIN32_FIND_DATA	Win32FD;
	sprintf( szPath, "%s\\*", szDirName );
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FD );

	if( Newdir != INVALID_HANDLE_VALUE ){ // Existe
		do{
			if( ( strcmp( Win32FD.cFileName, "." ) != 0 ) && 
			    ( strcmp( Win32FD.cFileName, ".." ) != 0 ) ){
				sprintf( szPath,"%s\\%s", szDirName, Win32FD.cFileName );
			    	if( Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
					// eh um diretorio. vamos deleta-lo recursivamente
					if( RemoveDir( szPath, TRUE ) != LBS_OK ){
						return( LBSE_ERROR );
					}
				} else {
					// eh um arquivo simples.
					if( remove( szPath ) == -1 ){
						return( LBSE_ERROR );
					}
				}
			}
		} while( FindNextFile( Newdir, &Win32FD ) );
		FindClose( Newdir );
	} else {
		return( LBSE_ERROR );
	}
	if( bDestroyDir ){
		if( chdir( "\\" ) == -1 ){
			return( LBSE_ERROR );
		}
		if( rmdir( szDirName ) != 0 ){
			return( LBSE_ERROR );
		}
	}
	return( LBS_OK );
}


/***********************/
int
FRemoveFile( char *szMask, ... )
{
	char 	szBuffer [ MAXPATH ];
	va_list argptr;
	int 	cnt;

	va_start( argptr, szMask );
	cnt = vsprintf( szBuffer, szMask, argptr );
	va_end( argptr );

	remove( szBuffer );

	return( cnt );
}

/***********************/
int
FRenameFile( char *szMask, ... )
{
	char 	szBuffer [ 2 * MAXPATH + 1 ];
	va_list argptr;
	int 	cnt;

	va_start( argptr, szMask );
	cnt = vsprintf( szBuffer, szMask, argptr );
	va_end( argptr );

	char *p = strchr( szBuffer, ' ' );
	p [ 0 ] = '\0';
	p++;

	if( rename( szBuffer, p ) != 0 ){
		return( -1 );
	}
	return( cnt );
}


/***
	Metodo DelFieldOnFile
	Deleta um campo do arquivo de estruturas (LB3)

	Parameters:
		- szField	-> nome do campo a ser deletado

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Base::DelFieldOnFile( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelFieldOnFile") );

	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	TStructRec	tsrRec;

	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( !LB3.IsOpen() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.uiFieldId == uiFieldId ){
				// invalida a cache de campos dessa base
				pBaseInstance->InvalidateBaseStruct();

				// deletar o slot do campo que esta' sendo detonado
				PutFieldSlot( uiFieldId, NULL, 0 );
				LB3.R_Seek( i );
				tsrRec.uiFieldAttrib |= DELETED_FIELD;
				if( LB3.R_Write( &tsrRec ) != OK ){
					TStructHeadRec::Free( ptsrStructRecHead );
					ERETURN( LBSE_ERROR );
				}
				--(ptsrStructRecHead->iNumberOfFields);
				if( LB3.R_WriteHead( ptsrStructRecHead ) != OK ){
					TStructHeadRec::Free( ptsrStructRecHead );
					ERETURN( LBSE_FATAL );
				}
				TStructHeadRec::Free( ptsrStructRecHead );

				ERETURN( LBS_OK );
			}
		}
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( LBSE_FIELDNOTFOUND );
}



/***
	Metodo AppendLastFieldOnFile
	Adiciona o ultimo campo da FieldList no arquivo de estruturas (LB3)

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Base::AppendLastFieldOnFile()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AppendLastFieldOnFile") );

	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	TStructRec	tsrRec;

	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( !LB3.IsOpen() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_BASENOTOPEN );
	}
	int iRet = LBSE_ERROR;
	if( LB3.R_ReadHead( ptsrStructRecHead ) == OK ){
		LBSC_Field *pcfField = lbscrCurrRecord [ lbscrCurrRecord.GetNumberOfFields() - 1 ];

		if( !pcfField ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		tsrRec.szFieldAliasName = (char*) pcfField->GetAliasName();
		tsrRec.szFieldDescription = (char*) pcfField->GetDescription();
		tsrRec.szFieldPassword = (char*) pcfField->GetPassword();
		tsrRec.bFieldType = pcfField->GetType();
		tsrRec.lFieldSize = pcfField->GetSize();
		tsrRec.uiFieldId = pcfField->GetId();
		tsrRec.tiaIndexAttrib = pcfField->GetIndexAttrib();
		tsrRec.lLinkListPointer = 0L;	// POR ENQUANTO. DEPOIS DEVEREMOS APONTAR PARA
						// A RESPECIVA LISTA DE LINKS NO ARQ. DE LINKS
		tsrRec.uiFieldAttrib = (pcfField->uiFieldAttrib & ~DELETED_FIELD);

		// invalida a cache de campos dessa base
		pBaseInstance->InvalidateBaseStruct();

		if( LB3.R_Append( &tsrRec ) == OK ){
			LB3.Flush();
			++(ptsrStructRecHead->iNumberOfFields);
			iRet = LB3.R_WriteHead( ptsrStructRecHead ) != OK ?
				LBSE_FATAL : LBS_OK;
		} else {
		}
	} else {
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( iRet );
}



/***
	PRIVATE
	Metodo UpdateStatus
	Atualiza o estado do registro em LB1 a partir do estado
	do registro em memoria

	Parameters:

	Return:
		LBS_OK ou erro.

	Comments:

***/
int
LBSC_Base::UpdateStatus( const LBSC_Ticket *lbscTicket, BOOL bIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateStatus") );

	TControlRec	tcrControlRec;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_ERROR );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_ERROR );
	}

	// a regiao critica abaixo protege toda a operacao de atualizacao de registro
	CLBAutoRegCrit	AutoRegCritDataFile( pBaseInstance ? &(pBaseInstance->DataFileCritSect) : NULL );

	if( LB1.R_Read( &tcrControlRec ) == OK ){
//		if( bIndex ){
//			tcrControlRec.bRecStatus |= REC_EXCLUDED;
//		} else {
//			tcrControlRec.bRecStatus &= ~REC_EXCLUDED;
//		}
		tcrControlRec.bRecStatus = lbscrCurrRecord.bStatus;
		tcrControlRec.bRecStatus &= ~REC_LOCKED;
		if( LB1.R_Write( &tcrControlRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		ERETURN( LBS_OK );
	}

	ERETURN( LBSE_ERROR );
}


/***
	PRIVATE
	OpenLogFile
	Abre o arquivo de Log da indexacao off-line do LBS
***/
int
LBSC_Base::OpenLogFile( C_IDXOFF &cfIdxOff )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OpenLogFile") );

	char		szAux[ FULLNAMESIZE ];

	sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char *)szBaseName, LOGFILE1EXT );
	if( cfIdxOff.OpenIndex( szAux ) != OK ){
//		if( cfIdxOff.CreateIndex( szAux ) != OK ){
//			return( LBSE_ERROR );
//		}
//		if( cfIdxOff.OpenIndex( szAux ) != OK ){
			return( LBSE_ERROR );
//		}
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo WriteRecordInLogFile
	Grava o registro atualizado no arquivo de log para posterior indexacao

	Parameters:

	Return:
		- LBS_OK ou erro

	Comments:

***/
int
LBSC_Base::WriteRecordInLogFile( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::WriteRecordInLogFile") );

	char		szAux[ FULLNAMESIZE ];
	long		lN;
	BOOL		bOpen = cfLB5.IsOpen();

	lN = CurrRecNum( lbscTicket );

	if( !bOpen ){
		// Abrir LB5
		sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char *)szBaseName, LOGFILE1EXT );
		if( cfLB5.OpenIndex( szAux ) != OK ){
			if( cfLB5.CreateIndex( szAux ) != OK ){
				return( LBSE_ERROR );
			}
			if( cfLB5.OpenIndex( szAux ) != OK ){
				return( LBSE_ERROR );
			}
		}
	}

	// Adicionar registro em LB5
	cfLB5.AddBitValue( lN );

	if( !bOpen ){
		cfLB5.CloseIndex();
	}

	ERETURN( LBS_OK );
}


/***
	Metodo MakeLockFileName
	Monta o nome do arquivo de lock correspondente ao registro corrente.
	
	Parameters:
		- szName -> string ja' alocada que recebera' o nome resultante
		- bLock -> indica se o nome sera' montado a partir do registro
			   correntemente travado (TRUE, default) ou a partir
			   do registro corrente, travado ou nao (FALSE)

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo usa sempre o registro correntemente travado 
		  para montar o nome do arquivo.

***/
int
LBSC_Base::MakeLockFileName( char *szName, BOOL bLock )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::MakeLockFileName") );

	if( !szName ){
		// erro
		return( LBSE_BADARG );
	}
	if( bLock ){
		if( lLockPos <= -1 ){
			// nao ha' registro travado
			szName[ 0 ] = '\0';
			return( LBSE_RECORDNOTLOCKED );
		}
		sprintf( szName, "%s\\%08x%s", (char *) szBasePath, lLockPos, LOCKFILEEXT );
	} else {
		sprintf( szName, "%s\\%08x%s", (char *) szBasePath, LB1.R_CurPos(), LOCKFILEEXT );
	}
	return( LBS_OK );
}


/***
	Metodo ExistLockFile
	Verifica a existencia de um arquivo de lock para o registro corrente
	
	Parameters:
		- bLock - indica se o arquivo a ser checado deve ser montado
			  com o nome igual ao do registro correntemente travado
			  (TRUE, default) ou se com o nome igual ao do registro
			  corrente, travado ou nao (FALSE)

	Return:
		- TRUE ou FALSE

	Comments:
		- Este metodo usa sempre o registro corrente para montar o nome
		  do arquivo.

***/
BOOL
LBSC_Base::ExistLockFile( BOOL bLock )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ExistLockFile") );

	char	szTmp[ FILENAMESIZE ];

	MakeLockFileName( szTmp, bLock );

	return( C_File::Exist( szTmp ) );
}


/***
	Metodo WriteOnLockFile
	Grava um registro de informacao de lock no arquivo de lock correspondente
	ao registro corrente.
	
	Parameters:
		- ptli - endereco de uma estrutura TLockInfo contendo as informacoes
			que devem ser gravadas.
		- bLock - indica se o nome do arquivo de lock deve ser montado usando-se
			  o registro correntemente travado (TRUE, default) ou o registro
			  corrente, travado ou nao (FALSE).

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- Este metodo usa sempre o registro correntemente travado 
		  para montar o nome do arquivo.

***/
int
LBSC_Base::WriteOnLockFile( TLockInfo *ptli, BOOL bLock )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::WriteOnLockFile") );

	char	szTmp[ FILENAMESIZE ];

	MakeLockFileName( szTmp, bLock );
	C_File	cfLock( szTmp );
	cfLock.Seek( 0, SEEK_SET );
	cfLock.Write( ptli, sizeof( *ptli ) );
	return( LBS_OK );
}


/***
	Metodo ReadFromLockFile
	Le um registro de informacao de lock do arquivo de lock correspondente
	ao registro corrente.
	
	Parameters:
		- ptli - endereco de uma estrutura TLockInfo
		- bLock - indica se o nome do arquivo de lock deve ser montado usando-se
			  o registro correntemente travado (TRUE, default) ou o registro
			  corrente, travado ou nao (FALSE).

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- Este metodo usa sempre o registro correntemente travado 
		  para montar o nome do arquivo.

***/
int
LBSC_Base::ReadFromLockFile( TLockInfo *ptli, BOOL bLock )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ReadFromLockFile") );

	char	szTmp[ FILENAMESIZE ];

	MakeLockFileName( szTmp, bLock );
	C_File	cfLock( szTmp );
	cfLock.Seek( 0, SEEK_SET );
	cfLock.Read( ptli, sizeof( *ptli ) );
	return( LBS_OK );
}


/***
	Metodo OpenIndexSystem
	Abre os arquivos do sistema de indices da base, setando tudo o que for preciso (stopwords, maxkeysize, etc.)

	Return:
		- LBS_OK  em caso de sucesso; valor negativo em caso de erro.

	Comments:
		-

***/
BOOL
LBSC_Base::OpenIndexSystem()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OpenIndexSystem") );
	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	if ( !pBaseInstance ) {
		return FALSE;
	}

	// vamos pegar o tamanho minimo de uma chave para ser indexada

	int iMinKeySize = 0;

	if ( !(pBaseInstance->BaseStructLoaded()) ) {
		char	szGowordsFileName[ MAXPATH ];
		sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
		iMinKeySize = GetPrivateProfileInt( GWMAINSECTION, GWMINKEYSIZE, 0, szGowordsFileName );
		pBaseInstance->MinKeySize = iMinKeySize;
	} else {
		iMinKeySize = pBaseInstance->MinKeySize;
	}

	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) szBaseName );
	// Primeiro fechar sistema de indices
	if ( plbscisIndexSystem ) {
		delete plbscisIndexSystem;
	}
	plbscisIndexSystem = new LTC_INDEXSYSTEM;
	if ( plbscisIndexSystem ) {
		// o sistema de indices deve sempre ser aberto em modo full, 
		// exceto se o sistema de arquivos nao permitir (bases em CD, rede sem permissao de gravacao, etc.)
		if( plbscisIndexSystem->LT_OpenIndexSystem( szAux, iMinKeySize, LBSC_ServerConfig::ReadOnlyFileSystem(), pBaseInstance->Indexes ) == ERR ){
			if ( errno == EMFILE ) {
				SetError( LBSE_TOOMANYOPENFILES );
			}
			delete plbscisIndexSystem;
			plbscisIndexSystem = NULL;
			return FALSE;
		}

		if ( !pBaseInstance->Indexes ) {
			pBaseInstance->Indexes = plbscisIndexSystem->LT_GetIndexes();
		}
	}
	SetStopWord();

	// carrega o conjunto de caracteres de normalizacao
	char	*szCurArray = SetStandardizer( DEFAULTSTANDARDIZERARRAY );
	if( szCurArray ){
		delete szCurArray;
	}
	return TRUE;
}


/***
	Metodo CreateIndexSystem
	Cria os arquivos do sistema de indices da base, setando tudo o que for preciso (stopwords, maxkeysize, etc.)

	Return:
		- LBS_OK  em caso de sucesso; valor negativo em caso de erro.

	Comments:
		-

***/
BOOL
LBSC_Base::CreateIndexSystem()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CreateIndexSystem") );
	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	// vamos pegar o tamanho minimo de uma chave para ser indexada
	char	szGowordsFileName[ MAXPATH ];
	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	int iMinKeySize = GetPrivateProfileInt( GWMAINSECTION, GWMINKEYSIZE, 0, szGowordsFileName );
	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) szBaseName );
	// Primeiro fechar sistema de indices
	if ( plbscisIndexSystem ) {
		delete plbscisIndexSystem;
	}
	// invalida os indices na cache
	if ( pBaseInstance ) {
		pBaseInstance->InvalidateIndexes();
	}
	plbscisIndexSystem = new LTC_INDEXSYSTEM;
	if ( plbscisIndexSystem ) {
		if( plbscisIndexSystem->LT_CreateIndexSystem( szAux, iMinKeySize ) == ERR ){
			if ( errno == EMFILE ) {
				SetError( LBSE_TOOMANYOPENFILES );
			}
			delete plbscisIndexSystem;
			plbscisIndexSystem = NULL;
			return FALSE;
		}
		if ( pBaseInstance ) {
			pBaseInstance->Indexes = plbscisIndexSystem->LT_GetIndexes();
		}
	}
	SetStopWord();

	char	*szCurArray = SetStandardizer( DEFAULTSTANDARDIZERARRAY );
	if( szCurArray ){
		delete szCurArray;
	}
	return TRUE;
}


/***
	Metodo RemoveIndexSystem
	Deleta os arquivos do sistema de indices da base

	Return:
		- LBS_OK  em caso de sucesso; valor negativo em caso de erro.

	Comments:
		-

***/
int
LBSC_Base::RemoveIndexSystem()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::RemoveIndexSystem") );

	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) szBaseName );
	// Fechar sistema de indices para depois remove-lo.
	if ( plbscisIndexSystem ) {
		delete plbscisIndexSystem;
	}
	plbscisIndexSystem = NULL;
	// invalida os indices na cache
	if ( pBaseInstance ) {
		pBaseInstance->InvalidateIndexes();
	}
	int iRet = LTC_INDEXSYSTEM::LT_RemoveIndexSystem( szAux ); 

	// vamos agora deletar todos arquivos do sistema de indices antigo (que usavam a CTREE)
	strcat( szAux, ".lt*" );
	WIN32_FIND_DATA		Win32FD;		// estrutura usada para pesquisar arquivos
	HANDLE		NewFile = FindFirstFile( szAux, &Win32FD );

	if( NewFile != INVALID_HANDLE_VALUE ){ // Existe
		do{
			// pegamos um arquivo. vamos verificar seu nome
			if( strcmp( Win32FD.cFileName, "." ) == 0 ||
			    strcmp( Win32FD.cFileName, ".." ) == 0 ){
				// ISSO NAO INTERESSA
				continue;
			}
			if( Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
				// o arquivo encontrado eh um diretorio.
				// Tambem nao interessa.
				continue;
			}

			// agora vamos montar o nome do arquivo 
			sprintf( szAux, "%s\\%s", (char*) szBasePath, Win32FD.cFileName );
			remove( szAux );
		} while( FindNextFile( NewFile, &Win32FD ) );
		FindClose( NewFile );
	}
	return( iRet );
}



/***
	PRIVATE
	Metodo CheckLB1Header
	Verifica (e corrige) a integridade do header de LB1.

	Parameters:
		-

	Return:
		- LBS_OK se nao houver erro ou se conseguir consertar os erros
		  existentes; valor negativo em caso de insucesso.

	Comments:
		-

***/
int
LBSC_Base::CheckLB1Header()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header") );

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_NOTOPEN );
	}
	if( LB1.R_ReadHead() != OK ){
		ERETURN( LBSE_ERROR );
	}
	// checar e corrigir eventuais problemas
	if( LB1.tcrHead.iSlotNum < 0 ||
	    LB1.tcrHead.iCountNum < 0 || 
	    LB1.tcrHead.iMaxKeySize < 0 ||
	    LB1.tcrHead.iIntPart < 0 ||
	    LB1.tcrHead.iDecPart < 0 ||
	    LB1.tcrHead.lDeletedRecNumReorg < 0 ||
	    LB1.tcrHead.ulLastModifyDate < 0L ||
	    LB1.tcrHead.ulLastModifyDate < 0L ||
	    LB1.tcrHead.uiLastFieldId <= 0 ||
	    (LB1.tcrHead.bIsEncrypt != 0 && LB1.tcrHead.bIsEncrypt != 1) ||
	    (LB1.tcrHead.bReExport != 0 && LB1.tcrHead.bReExport != 1) ||
	    (LB1.tcrHead.bBaseIndexed != 0 && LB1.tcrHead.bBaseIndexed != 1) ||
	    (LB1.tcrHead.bOnLineIndex != 0 && LB1.tcrHead.bOnLineIndex != 1) ||
	    LB1.tcrHead.bBaseType < 0 ||
	    LB1.tcrHead.dwBaseId < 0 ||
	    LB1.tcrHead.dwUserBaseId < 0 ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::GenHeaderErr") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar o numero de registros
	if( LB1.tcrHead.lNumRecords < 0 ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lNumRecords::neg") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar o numero de registros deletados em relacao ao numero de registros existentes
	if( LB1.tcrHead.lDeletedRecNum < 0 ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lDeletedRecNum::neg") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar a posicao do ultimo registro
	if( LB1.tcrHead.lLastRecActivePos < -1 ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lLastRecActivePosLB1::neg") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar a posicao do ultimo registro
	if( LB1.tcrHead.lFirstRecActivePos < -1 ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lLastFirstActivePos::neg") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar a posicao do ultimo registro em relacao aa do primeiro
	if( LB1.tcrHead.lLastRecActivePos < LB1.tcrHead.lFirstRecActivePos ){
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lLastRecActivePosLB1::lFirstRecActivePos") );
		INITLOG( _clLBSLog );
		ERETURN( LBSE_ERROR );
	}
	// testar o numero de registros em funcao da posicao do ultimo registro
	if( LB1.tcrHead.lLastRecActivePos < (LB1.tcrHead.lNumRecords - 1) ){
		ERETURN( LBSE_ERROR );
		PRINTLOG( _clLBSLog, ("LBSC_Base::CheckLB1Header::lLastRecActivePosLB1::lNumRecords") );
		INITLOG( _clLBSLog );
	}

	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo Flush
	Descarrega em disco os headers e os dados dos principais arquivos da base.

	Parameters:
		- lbscTicket -> ticket de seguranca

	Return:
		- TRUE em caso de sucesso; FALSE caso contrario.

	Comments:
		-

***/
BOOL
LBSC_Base::Flush( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Flush") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		SetError( LBSE_TICKETNOTOK );
		return( FALSE );
	}

	if( LB1.IsOpen() ){
		LB1.Flush();
	}
	if( LB3.IsOpen() ){
		LB3.Flush();
	}
	if ( pBaseInstance && pBaseInstance->DataFileLoaded() ) {
		// a regiao critica abaixo protege a manipulacao do LB4
		CLBAutoRegCrit	AutoRegCrit( &(pBaseInstance->DataFileCritSect) );
		CPageFile *pDataFile = pBaseInstance->GetDataFile();
		if( pDataFile->IsOpen() ){
			pDataFile->Flush();
		}
	}

	SetError( LBS_OK );
	return( TRUE );
}


/***
	PUBLIC
	Metodo Recover
	Recupera dados perdidos de uma base

	Parameters:
		- plbscTicketPar	-> ticket de seguranca

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- A base deve estar aberta em modo manutencao.
		- O usuario logado deve ser o dono da base ou um super-usuario
		- Este metodo simplesmente tenta recuperar registros, para que a
		  quantidade de registros existentes fique igual aa quantidade indicada
		  no header de LB1.
		- Este metodo pode ser expandido para fazer mais correcoes na base,
		  conforme for necessario.

***/
int
LBSC_Base::Recover( const LBSC_Ticket *plbscTicketPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Recover") );

	// Verifica a validade do ticket de seguranca
	if( plbscsOwnerSession->TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	if( !bFullAccess ){
		// a base nao esta' aberta para manutencao
		ERETURN( LBSE_NOTFULLACCESS );
	}

	// seta o estado de FullAccess para FALSE na base para poder enxergar os
	// dados.
	SetFullAccessMode( FALSE );

	if( LB1.R_FileSize() == 0 ){
		// se o tamanho do arquivo eh zero, entao nao temos nenhum registro para
		// recuperar.
		LB1.tcrHead.lNumRecords = 0l;
		LB1.LB1_WriteHead();
		// seta o estado de FullAccess para TRUE novamente
		SetFullAccessMode( TRUE );
		ERETURN( LBS_OK );
	}

	// vamos ler os registros de LB1, checar o flag de delecao e, se for o caso,
	// tentar carrega-lo para ter certeza de que ele esta' integro.
	long	lNumRecords = LB1.tcrHead.lNumRecords;

	if( LB1.R_Seek( 0L ) != OK ){
		// nao conseguimos nos posicionar no primeiro registro. ERRO.
		// seta o estado de FullAccess para TRUE novamente
		SetFullAccessMode( TRUE );
		ERETURN( LBS_OK );
	}
	long lFirstPos = -1L;
	while( lNumRecords > 0 ){
		TControlRec	tcr;
		if( LB1.R_Read( &tcr ) != OK ){
			// erro de leitura.
			break;
		}
		if( ! (tcr.bRecStatus | REC_EXCLUDED) ){
			// registro NAO esta' excluido.
			// vamos tentar fazer um ReadRecord
			if( ReadRecord( plbscTicketPar ) == LBS_OK ){
				// conseguimos. este registro NAO esta' com problemas.
				--lNumRecords;
				if( lFirstPos != -1L ){
					lFirstPos = LB1.R_CurPos();
				}
			}
		}
		if( LB1.R_SeekNext() != OK ){
			// deu pau
			break;
		}
	}
	// seta o estado de FullAccess para TRUE novamente
	SetFullAccessMode( TRUE );

	if( lNumRecords == 0 ){
		LB1.tcrHead.lFirstRecActivePos = lFirstPos;
		LB1.tcrHead.lLastRecActivePos = LB1.R_CurPos();
		LB1.tcrHead.lLastRecPos = LB1.R_FileSize() - 1L;
		if( LB1.LB1_WriteHead() != LBS_OK ){
			ERETURN( LBSE_ERROR );
		}
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}


/***
	static PRIVATE
	Metodo GetBaseVersion
	Obtem a versao de uma base (a versao eh o numero magico)

	Parameters:
		- szAux	-> nome do arquivo LB1 (com path)

	Return:
		- o numero da versao

	Comments:
		- 

***/
int
LBSC_Base::GetBaseVersion( char *szAux )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseVersion") );

	C_File	cFile;
	
	if( cFile.Open( szAux, "r" ) != OK ){
		if( errno == EACCES ){
			// o arquivo esta' em uso por outro processo/thread
			return( LBSE_NOPERMISSION );
		}
		// nao consegui abrir o arquivo
		return( LBSE_FILEERROR );
	}

	if( cFile.Seek( 0, SEEK_SET ) == OK ){
		BYTE	bFirstByte;
		if( cFile.Read( &bFirstByte, sizeof( bFirstByte ) ) == OK ){
			if( bFirstByte >= BEFORECRYPTO_MAGICNUMBER && bFirstByte <= CURRENT_MAGICNUMBER){
				return( bFirstByte );
			}
		}
	}
	return( LBSE_FILEERROR );
}


/***
	PUBLIC
	Metodo GetBaseTimeInfo
	Obtem informacoes sobre datas/horas de criacao/modificacao/acesso
	do arquivo LB1 da base.

	Parameters:
		- psInfo	-> ponteiro para uma estrutura stat

	Return:
		- LBS_OK em caso de sucesso;
		  LBSE_ERROR caso ocorra algum erro.

	Comments:
		- 

***/
int
LBSC_Base::GetBaseTimeInfo( struct stat *psInfo )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseTimeInfo") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char*)szBaseName, REPETITIONFILEEXT );

	int	iStat = stat( szAux, psInfo );
	if( iStat == 0 ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}

/***
	STATIC PUBLIC
	Metodo GetDirBase
        Obtem o nome do diretorio base do lbs (dir_base)

        Parameters:
        	- szBuffer -> buffer para receber o valor de retorno
                	      (deve estar alocado e ter tamanho suficiente
                               para tal)

        Return:
        	- None

        Comments:
        	- Por enquanto, vamos obter tal informacao no arquivo
                  LBS.INI. Futuramente deveremos mudar isso para
                  obter a informacao de algum lugar que seja setado
                  no momento da instalacao do LBS e nao possa ser
                  alterado por um usuario.
***/
void
LBSC_Base::GetDirBase( char *szBuffer, const char *szUDB, const char *szServer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetDirBase") );

	if( szBuffer ){
		strncpy( szBuffer, LBSC_ServerConfig::DirBase(), FULLNAMESIZE-1 );
		if ( strlen( szBuffer ) > 0){
			char szDrive[ _MAX_DRIVE ];
			_splitpath ( szBuffer, szDrive, NULL, NULL, NULL );
			if ( (szBuffer[0] != '\\' || szBuffer[1] != '\\') && strlen( szDrive ) == 0 ){
				// tenta descobrir o drive somente se estiver relativo ao drive onde estamos rodando
				LBSC_Session::getAppDrive( szDrive );
				char * szAux = strdup ( szBuffer );
				if ( szAux ){
					sprintf( szBuffer, "%s%s", szDrive, szAux );
					free ( szAux );
				}
			}
		}
	}
}


/**********************************************************
// Function name	: LBSC_Base::GetBaseVersion
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::GetBaseVersion()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !LB1.IsOpen() ){
		// a base esta' fechada.
		ERETURN( LBSE_BASENOTOPEN );
	}

	SetError( LBS_OK );

	return( LB1.bMagicNumber );
}


/**********************************************************
// Function name	: LBSC_Base::GetUDBVersion
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::GetUDBVersion()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !LB3.IsOpen() ){
		// a base esta' fechada.
		ERETURN( LBSE_BASENOTOPEN );
	}

	SetError( LBS_OK );

	// convencionamos usar o numero magico do LB3 para armazenar a versao da UDB

	return( LB3.bMagicNumber );
}


void LBSC_Base::AddDefaultUDBSlots()
{
	if ( LB1.tcrHead.bBaseType != USER_BASE ) {
		return;
	}

	if ( GetSlotSize( SLOTDESCRIPTION ) <= 0 ){
		// slot da descricao da base
		SlotBaseManager	sBaseInfo( SLOTDESCRIPTION, this );

		sBaseInfo.ClearSlotInfo();
		sBaseInfo.AddObjectInfo( BASEDESCRIPTION, strlen(plbscsOwnerSession->strUDBLogged)+1, (void *) (LPCSTR) plbscsOwnerSession->strUDBLogged );
		sBaseInfo.Store();
	}

	if ( GetSlotSize( SLOTGROUP ) <= 0 ) {
		// slot dos grupos de campos multivalorados
		SlotBaseManager	sBaseInfo( SLOTGROUP, this );
		char			szGroup[] = "BaseAccess";

		C_Buffer		cbBuf( CB_Grupos::GetMaxSize() );
		CB_Grupos		cbGroup;

		cbGroup.sGrupo = (char*) szGroup;
		cbGroup.iGrupo = 2; // grupo com a lista de acesso às bases
		cbGroup.iSort = -1;	// sem ordenacao no grupo
		cbBuf.Rewind();
		cbGroup.Serialize( cbBuf );
		int iSize = cbBuf.MyBufLen();

		sBaseInfo.ClearSlotInfo();
		sBaseInfo.AddObjectInfo( cbGroup.iGrupo, iSize, (void *) cbBuf.MyBuffer() );
		sBaseInfo.Store();
	}

	// slots de campos
	AddDefaultUDBFieldSlots( USERBASEUSERNAME, 0, FALSE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEUSERPASSWORD, 0, FALSE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEUSERTYPE, 0, FALSE, LBWF_NUMBER );
	AddDefaultUDBFieldSlots( USERBASEUSERDESCRIPTION, 0, FALSE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEUSERADDRESS, 0, FALSE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEUSERPHONE, 0, FALSE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEUSERCREATEDATE, 0, FALSE, LBWF_DATE );
	AddDefaultUDBFieldSlots( USERBASEUSERUPDATEDATE, 0, FALSE, LBWF_DATE );
	AddDefaultUDBFieldSlots( USERBASEGROUPLIST, 1, TRUE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEACCESSBASES, 2, TRUE, LBWF_ALPHA );
	AddDefaultUDBFieldSlots( USERBASEACCESSTYPES, 2, TRUE, LBWF_NUMBER );
	AddDefaultUDBFieldSlots( USERBASEPASSWORDCHANGEDATE, 0, FALSE, LBWF_DATE );
	AddDefaultUDBFieldSlots( USERBASELOGINATTEMPTS, 0, FALSE, LBWF_NUMBER );
}
	
void LBSC_Base::AddDefaultUDBFieldSlots( const char *szField, int iGroup, BOOL bMultiVal, int iLBWType )
{
	if ( LB1.tcrHead.bBaseType != USER_BASE ) {
		return;
	}

	LBSC_Field *pf = (*this)[ (char *)szField ];
	if ( !pf || GetFieldSlotSize( pf->GetId() ) > 0 ) { // nao precisa setar o slot 
		return;
	}
 	SlotFieldManager sSlotInfo( pf->GetId(), this );

	int iShowPos = pf->GetId() - 1;	// pro lbw o showpos eh baseado em 0

	sSlotInfo.ClearSlotInfo();

	// indica o grupo do campo
	sSlotInfo.AddObjectInfo( FSI_GROUP, sizeof( iGroup ), (void*) &iGroup );

	// indica se o campo eh multivalorado
	sSlotInfo.AddObjectInfo( FSI_MULTIVAL, sizeof( bMultiVal ), (void*) &bMultiVal );

	// tipo do campo LBW
	sSlotInfo.AddObjectInfo( FSI_LBWTYPE, sizeof( iLBWType ), (void*) &iLBWType );

	// posicao visual (tela) onde o campo sera' apresentado 
	sSlotInfo.AddObjectInfo( SHOWPOSITION, sizeof( iShowPos ), (void*) &iShowPos );

	if ( pf->GetType() == DATE_FIELD ) {
		// setar mascara de data 
		char szMask[] = "dd/mm/yyyy";
		sSlotInfo.AddObjectInfo( FSI_MASK, strlen( szMask ) + 1, (void*) szMask );
	}

	sSlotInfo.Store();
}
