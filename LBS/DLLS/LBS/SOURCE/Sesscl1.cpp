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
// Module: SESSCL1.CPP 
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//				Tricia Souto Santos
//				Alessandro Araujo Jatoba'
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
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
#ifndef	_GRPLIST_H_
#include	<grplist.h>
#endif
#ifndef	_MBASELST_H_
#include	<MBaseLst.h>
#endif
extern "C" {
#include	<personcl.h>
}
extern "C" {
#ifndef _CRYPT_H_
	#include <crypt.h>
#endif	// _CRYPT_H_
}

#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif

#include <sys/stat.h>

extern	char	_szDefUDBName[ MAXPATH ];

#ifdef	_DEBUG_CRIT_SECT_
int				_iLastSessCritSectUsed = -1;
int				_iLastSessArray[ 5000 ];

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
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )
#endif

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;


// funcao de timer para ficar checando o arquivo de licencas
// periodicamente (util apenas para copia REDE)
void CALLBACK	LicTimerProc( HWND, UINT, UINT, DWORD );
UINT					_uLicTimerId = 0;
time_t					_tLicFileCreateTime;

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

LBSC_SessionList	*_clSessList;			// lista das sessoes abertas (logins feitos)
LBSC_LogList		*_clLoginList;			// lista contendo estruturas TNetInfo de todos
											// os logins efetuados. usada para controle
											// de licencas de clientes.
LBSC_LicList		*_clLicList;			// lista para controle de licencas e usuarios
											// logados. Usada apenas para o LBS tipo REDE.
LBSC_MaintBasesList	*_pclMaintBaseList;		// lista para armazenar bases que estao reservadas para manutencao
											// a regiao critica para essa lista eh CRITSECT3

extern void *LBS_Realloc( void *pvOrigBuf, int iOldSize, int iNewSize );

int	LBSC_Session::iNumLic = 0;						// numero de licencas usadas (do servidor)
int	LBSC_Session::iUserCacheSize = 0;				// numero de usuarios na cache local
TUserCacheInfo *LBSC_Session::pUserCache = NULL;	// cache de usuarios local
LBSC_BaseList	*LBSC_Session::pLRUBases=NULL;		// LRU de bases
LBSC_ControlFile *LBSC_Session::pControlFile = NULL;	// arquivo de controle



EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo New
	Instancia um objeto LBSC_Session para o usuário.

	Parameters:
		- o parametro deste metodo indica o nome do servidor onde a sessao
		  deve ser criada. So' e' util a nivel de RPC. Nao eh usado aqui.

	Return:
		- um objeto LBSC_Session.

	Comments:
		-

***/
LBSC_Session*
LBSC_Session::New( const char * )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::New") );
	LBSC_Session	*pS = new LBSC_Session;
	return( pS );
}

/***
	PUBLIC
	Metodo Delete
	Destroi um objeto LBSC_Session.

	Parameters:
		ps: apontador para objeto LBSC_Session.

	Return:
		- um objeto LBSC_Session.

	Comments:
		- Resolver problema da DLL.

***/
void
LBSC_Session::Delete( LBSC_Session *pS )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pS ){
		delete pS;
	}
}


/***
	PUBLIC
	Metodo LBSC_Session
	Construtor 2 da classe LBSC_Session

	Parameters:

	Return:

	Comments:

***/

LBSC_Session::LBSC_Session():
	C_LeaveCritSect<C_GlobalSessCritSect>( _pcGlobalSessCritSect ),
	lbscblBaseList(),
	cdOpenSessionDate(),
	ctOpenSessionTime()
{
	// Colocando o log no LBS !!!!
	PRINTLOG( _clLBSLog, ("LBSC_Session::LBSC_Session") );

	Init();

	if( ::GetTypeInt() == PE_REDE ){
		// estamos em uma copia rede. entao vamos acionar o mecanismo
		// de timer para ficar verificando o arquivo de licencas.
		C_SessCritSect	cCS3( this, CRITSECT3 );
		if( _uLicTimerId == 0 ){
			TIMERPROC	lpfnLockTimerProc;

			lpfnLockTimerProc = (TIMERPROC) MakeProcInstance( (TIMERPROC) LicTimerProc, _hInstance );
			_uLicTimerId = SetTimer( NULL, 1, 1 * (60*1000), lpfnLockTimerProc );
		}
	}
}


/***
	PUBLIC
	Metodo ~LBSC_Session
	Destrutor da classe LBSC_Session

	Parameters:

	Return:

	Comments:

***/

LBSC_Session::~LBSC_Session()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::~LBSC_Session") );
	if( IsLogged() ){
		// usuario ainda esta' logado.
		Logout();
	}

	C_SessCritSect	cCS1( this, CRITSECT1 );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( plbscuUser ){
		delete plbscuUser;
	}
	if( plbsctTicket ){
		delete plbsctTicket;
	}

	if( ::GetTypeInt() == PE_REDE ){
		// estamos em uma copia rede. entao vamos matar o timer
		// do arquivo de licencas.
		if( _clSessList->NumElem() == 0 ){
			if( KillTimer( NULL, _uLicTimerId ) ){
				_uLicTimerId = 0;
			}
		}
	}
	// nao podemos tentar sair da lista se ela ja' estiver processando seu
	// destrutor. Isso provocaria um crash, pois o destrutor da lista tentaria
	// deletar esta sessao e o destrutor desta sessao tentaria sair da lista,
	// atraves do Logout
	if( !_clSessList->bIsDying ){
		if( _clSessList->Find( this, CMPSESSIONPOINTER, TRUE ) != NULL ){
			// achamos o elemento na lista.
			// nao podemos chamar o metodo Del() da lista porque isso
			// provocaria uma chamada ao destrutor do elemento corrente, que
			// eh este metodo aqui!! Stack Overflow na certa!
			// Portanto, vamos primeiro limpar o elemento corrente da lista
			// e depois chamar o Del().
			_clSessList->Refresh( (LBSC_Session*) NULL );
			_clSessList->Del();
		}
	}
}


/***
	PRIVATE
	Metodo Init
	Inicializa os atributos do objeto

	Parameters:

	Return:

	Comments:

***/
void
LBSC_Session::Init()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Init") );

	plbscuUser = NULL;
	plbsctTicket = NULL;
	dwUserBaseId = 0;

	bSLogin = FALSE;
	bIsLogged = FALSE;
	bIsMono = FALSE;
	iSecurityFlags = 0x00000000;

	pLoginInfo = NULL;

	strAppName = "?";
	lAppId = 0;
	ulLastAccess = 0;
}

BOOL						
LBSC_Session::BaseObjOk( LBSC_Base *pObj )
{
	// Verifica se a base estah aberta
	C_SessCritSect	cCS0( this, CRITSECT0 );
	lbscblBaseList.First();
	if( lbscblBaseList.Find( pObj, CMPBASEPOINTER ) == NULL ){
		// A base passada nao consta na lista de bases desta sessao
		return FALSE;
	}
	return TRUE;
}

/***
	PUBLIC
	Metodo Login
	Faz o login de um usuario em um servidor

	Parameters:
		- szUserName
		- szUserPassword
		- tmaServer

	Return:
		- um ticket de acesso se conseguir fazer o login;
		  NULL em caso de erro.

	Comments:
		- A aplicacao NAO deve deletar o ticker retornado.

***/
const LBSC_Ticket*
LBSC_Session::Login( TNetInfo &tniPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Login") );

	FullSTR			strUserBaseNameAux;
	GroupSTR		strGroupNameAux;
	UserSTR			strUserNameAux;
	PswdSTR			strUserPasswordAux;
	BOOL			bIncSrvLic = FALSE;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	if( tniPar.strUserName == (char*) "" ){
		NRETURN( LBSE_BADARG );
	}

	// Verifica se o usuario ja estah logado
	if( bIsLogged == TRUE ){
		NRETURN( LBSE_USERLOGGED );
	}

	// converter os nomes para maiusculo
	strupr( (char*) tniPar.strUserName );
	strupr( (char*) tniPar.strPasswd );
	strupr( (char*) tniPar.strUDBName );
	strupr( (char*) tniPar.strServer );
	strupr( (char*) tniPar.strClient );

	// regiao critica que vai ser usada por outros métodos mais adiante (para evitar deadlocks) 
	C_SessCritSect	cCS0( this, CRITSECT0 );

	// regiao critica para tratar do ticket
	C_SessCritSect	cCS1( this, CRITSECT1 );

	// regiao critica para tratar o strUDBLogged, bIsLogged, bIsMono
	C_SessCritSect	cCS2( this, CRITSECT2 );

	// para realizarmos o login, precisamos travar a lista de sessoes para evitar
	// inconsistencias. Entrando na regiao critica 3 garantimos acesso exclusivo
	// aa lista de sessoes.
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// para realizarmos o login, podemos ter que atualizar a a senha do sujeito
	// pra corrigir o bug da senha do modulo cliente/servidor
	// pra isso teremos que entrar na regiao da cache de usuarios
	C_SessCritSect	cCS7( this, CRITSECT7 );

	// vamos verificar a expiracao do servidor (time-bomb)
	switch( CheckForRun() ){
	case PE_DATA:							// Estourou data
		NRETURN( LBSE_SERVEREXPIRED );

	case PE_INSTALA:						// Produto nao personalisado
	case PE_OK:								// Ok! Pode executar.
		break;

	}

	// protecao contra leak
	if( pLoginInfo ){
		delete pLoginInfo;
		pLoginInfo = NULL;
	}

	strUserNameAux = tniPar.strUserName;
	strUserPasswordAux = tniPar.strPasswd;
	strUserBaseNameAux = (tniPar.strUDBName != (char*) "") ? tniPar.strUDBName : _szDefUDBName;

	strUserNameAux.Upper();
	strUserPasswordAux.Upper();
	strUserBaseNameAux.Upper();

	// seguranca
	if( plbsctTicket ){
		// Da~!
		delete plbsctTicket;
	}
	plbsctTicket = NULL;

	// Monta o ticket
	plbsctTicket = new LBSC_Ticket( (char*) tniPar.strServer, (char*) tniPar.strClient, (char*) strUserBaseNameAux,
					strUserNameAux, strUserPasswordAux );

	if( !plbsctTicket ){
		NRETURN( LBSE_NOMEMORY );
	}

	// vamos verificar o numero de licencas do servidor.
	LBSC_LicControl		cLicControl( &_tLicFileCreateTime );
	
	int	iRet = LBS_OK;
	BOOL bNeedLicenseControl = !bSLogin;
	
	if( !bSLogin && (iSecurityFlags & BS_LICENSE) ){
		// pode ser que o cara
		// nao precise contar licenca
		// vamos liberar licenca se o cara for administrador
		// na UDB default

		// abrir a UDB
		LBSC_Base bUserBase( plbsctTicket, (char *)strUserBaseNameAux, 
				this, FALSE, FALSE );

		if( !bUserBase.BaseObjOk() ){
			iRet = LBSE_ERROR;
			// tentar reprocessar ou converter a udb
			LBSC_Session	*pSession = LBSC_Session::New();
			if( pSession ){
				TNetInfo	tni( "$", "$", NULL, NULL, NULL, NULL, 10, FALSE );
				const	LBSC_Ticket	*pTicket = pSession->SLogin( tni );

				if( pTicket ){
					if( bUserBase.LastError() == LBSE_OLDBASEVERSION ){
						// precisamos converter a UDB para a versao atual
						iRet = ConvertBase( pTicket, (char *)strUserBaseNameAux, "" );
					} else {
						// reprocesar a UDB
						iRet = bUserBase.LastError();
					}
					pSession->Logout();
				}
				LBSC_Session::Delete( pSession );
			}
			if( iRet == LBS_OK ){
				// tentar abrir novamente a udb
				LBSC_Base bUserBaseAux( plbsctTicket, (char *)strUserBaseNameAux, 
						this, FALSE, FALSE );

				if( bUserBaseAux.BaseObjOk() ){
					// obter o tipo do usuario
					if ( GetUserType( &bUserBaseAux, (char *)strUserNameAux ) == MASTER_USER ) {
						bNeedLicenseControl = FALSE;	// ta liberado!
					}
				}
			}
		} else {
			// obter o tipo do usuario
			if ( GetUserType( &bUserBase, (char *)strUserNameAux ) == MASTER_USER ) {
				bNeedLicenseControl = FALSE;	// ta liberado!
			}
		}
	}

	if( bNeedLicenseControl ) {
		iSecurityFlags = 0;	// sem liberacao de seguranca 
		iRet = cLicControl.IncLicense( &iNumLic, &tniPar, this );
		if( iRet != LBS_OK ){
			delete plbsctTicket;
			plbsctTicket = NULL;
			NRETURN( iRet );
		}
	}

	// se chegamos ateh aqui, temos pelo menos uma licenca de login.
	// podemos prosseguir com o processo.

	// vamos ver se ha' alguem logado em modo monousuario. se a resposta for
	// positiva, entao nao podemos realizar este login.
	if( _clSessList->Find( NULL, CMPSESSIONISLOGGED, TRUE ) != NULL ){
		// existe pelo menos uma sessao com usuario logado.
		// Vamos ver se a sessao encontrada esta' logada em modo mono.
		// basta encontrar uma sessao na lista, pois se ela estiver em
		// modo mono, nao havera' outras e se ela nao estiver em modo mono,
		// nenhuma estara'.
		if( _clSessList->Current()->bIsMono ){
			// a sessao encontrada esta' em modo mono.
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;
			NRETURN( LBSE_MONOMODE );
		}
	}

	if( tniPar.bMono ){

		// o cara quer fazer um login em modo monousuario.
		// antes de mais nada, vamos checar se o cara eh MASTER_USER.
		bIsLogged = TRUE;
		long lType = GetUserType( plbsctTicket, (char*) strUserBaseNameAux, (char*) strUserNameAux );
		bIsLogged = FALSE;
		if( lType != MASTER_USER ){
			// o cara nao eh MASTER_USER e portanto nao pode se logar
			// em modo monousuario.
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;
			NRETURN( LBSE_INVALIDUSERTYPE );
		}
		// vamos verificar se ha' alguem logado (em qualquer modo)
		if( _clSessList->Find( NULL, CMPSESSIONISLOGGED, TRUE ) != NULL ){
			// existe pelo menos uma sessao com usuario logado.
			// nao podemos fazer login em modo monousuario.
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;
			NRETURN( LBSE_THEREAREUSERS );
		}
		// nao ha' usuarios logados neste servidor. garantimos que nenhum
		// outro vai se logar enquanto estamos processando porque
		// a regiao critica 3 esta' bloqueada.
		cLicControl.SetMono( TRUE );
	}

	LBSC_GroupList	*plbscglGroupList = new LBSC_GroupList;
	if( !plbscglGroupList ){
		cLicControl.UndoProcess();
		NRETURN( LBSE_NOMEMORY );
	}

	if( bSLogin == FALSE ){
		DescSTR		strUserDescrAux;
		long		lTypeAux = NOP_USER;

		// nao pode abrir readonly pois pode ter que atualizar informacoes do usuario
		// ja no login (bug das senhas do cliente/servidor)
		BOOL		bOpenReadOnly = FALSE;

		// Abrir a UDB
		LBSC_Base	*lbscbUserBase = NewBaseHandler( plbsctTicket, (char*) strUserBaseNameAux, this, FALSE, bOpenReadOnly, FALSE );
		if( !lbscbUserBase ){
			cLicControl.UndoProcess();
			delete plbscglGroupList;
			delete plbsctTicket;
			plbsctTicket = NULL;
			NRETURN( LBSE_NOMEMORY );
		}
		if( lbscbUserBase->BaseObjOk() == FALSE ){ // Nao conseguiu abrir a base de usuarios
			iRet = lbscbUserBase->LastError();
			if( iRet == LBS_OK ){
				// tentar abrir novamente a udb
				delete lbscbUserBase;
				lbscbUserBase = NewBaseHandler( plbsctTicket, (char*) strUserBaseNameAux, this, FALSE, bOpenReadOnly, FALSE  );
				if( !lbscbUserBase || !lbscbUserBase->BaseObjOk() ){
					iRet = LBSE_ERROR;
				}
			}
			if( iRet != LBS_OK ){
				cLicControl.UndoProcess();
				delete plbsctTicket;
				plbsctTicket = NULL;

				delete plbscglGroupList;
				if( lbscbUserBase ){
					delete lbscbUserBase;
				}
				PRINTLOG( _clLBSLog, ("LBSC_Session::Login::LBSE_UBNOTOK") );
				INITLOG( _clLBSLog );
				NRETURN( LBSE_UBNOTOK );
			}
		}

		if( lbscbUserBase->GetBaseType() != USER_BASE ){
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;

			delete plbscglGroupList;
			delete lbscbUserBase;
			NRETURN( LBSE_INVALIDUSERBASE );
		}
		int iAux = FindUser( lbscbUserBase, strUserNameAux, strUserPasswordAux );

		if ( iAux == LBSE_INVALIDPASSWORD && NeedUptadeUserPassword( lbscbUserBase, strUserNameAux, strUserPasswordAux) ) {

			// vamos corrigir a senha armazenada por conta do bug da senha do cliente/servidor
			char szPwd[PASSWORDSIZE + 1];
			lbscbUserBase->GetFieldRepetition( USERBASEUSERPASSWORD, 0, szPwd );
			lbscbUserBase->PutFieldRepetitionByIndex( USERBASEUSERPASSWORD, strUserPasswordAux, 0 );
			lbscbUserBase->PutFieldRepetitionByIndex( USERBASEUSERUPDATEDATE, C_Date(), 0 );	// data de hoje
			lbscbUserBase->PutFieldRepetitionByIndex( USERBASELOGINATTEMPTS, (long)0, 0 );		// limpando o numero de tentativas invalidas de login
			lbscbUserBase->PutFieldRepetitionByIndex( USERBASEPASSWORDCHANGEDATE, C_Date(), 0 );// data de hoje

			iAux = lbscbUserBase->LockRecord( plbsctTicket );

			if( iAux != LBS_OK ){
				cLicControl.UndoProcess();
				delete plbsctTicket;
				plbsctTicket = NULL;

				delete plbscglGroupList;
				delete lbscbUserBase;
				NRETURN( iAux );
			}
			lbscbUserBase->UpdateRecord( plbsctTicket );
			lbscbUserBase->ReleaseRecord( plbsctTicket );
			// corrigir esse usuario em todas as UDBs em que ele aparece com essa senha
			ChangeUserCachePwd( strUserNameAux, szPwd, NULL, strUserPasswordAux );
			SetError( LBS_OK );
		} else {
			SetError( iAux );
		}

		int iAux2 = VerifyLoginAttempts( lbscbUserBase, strUserNameAux );

		if ( iAux2 != LBS_OK ) {
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;

			delete plbscglGroupList;
			delete lbscbUserBase;
			NRETURN( iAux2 );
		}

		if( iAux != LBS_OK ){
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;

			delete plbscglGroupList;
			delete lbscbUserBase;
			NRETURN( iAux );
		}

		if( PasswordExpired(lbscbUserBase, strUserNameAux) ){
			cLicControl.UndoProcess();
			delete plbsctTicket;
			plbsctTicket = NULL;

			delete plbscglGroupList;
			delete lbscbUserBase;
			NRETURN( LBSE_PASSWORDEXPIRED );
		}

		strUDBLogged = strUserBaseNameAux;

			int iNumberOfGroups = lbscbUserBase->GetNumberOfRepetition( USERBASEGROUPLIST );

			// $$$ Monta a lista de grupos
			for( int i = 0; i < iNumberOfGroups; i++ ){
				lbscbUserBase->GetFieldRepetition( USERBASEGROUPLIST, i,
					(char*) strGroupNameAux );
				LBSC_Group *plbscgGroup = new LBSC_Group( strGroupNameAux, "" );
					// $$$ Falta definir o segundo parametro
				if( !plbscgGroup ){
					cLicControl.UndoProcess();
					delete plbsctTicket;
					plbsctTicket = NULL;

					delete plbscglGroupList;
					delete lbscbUserBase;
					NRETURN( LBSE_NOMEMORY );
				}
				plbscglGroupList->Add( plbscgGroup, AFTER );
			}

			lbscbUserBase->GetFieldRepetition( USERBASEUSERDESCRIPTION, 0, (char*)strUserDescrAux );
			lbscbUserBase->GetFieldRepetition( USERBASEUSERTYPE, 0, &lTypeAux );
			dwUserBaseId = lbscbUserBase->GetBaseId();

		// Alimenta objeto Usr
		if( plbscuUser ){
			delete plbscuUser;
		}
		plbscuUser = new LBSC_User( strUserNameAux, strUserPasswordAux,
						strUserDescrAux, plbscglGroupList,
						this, (TUserType) lTypeAux  );
		ReturnBaseHandler( lbscbUserBase );
	} else {
		if ( plbsctTicket ) {
			delete plbsctTicket;
		}
		plbsctTicket = new LBSC_Ticket;
		if( !plbsctTicket ){
			cLicControl.UndoProcess();
			delete plbscglGroupList;
			NRETURN( LBSE_NOMEMORY );
		}

		// Alimenta objeto Usr
		if( plbscuUser ){
			delete plbscuUser;
		}
		plbscuUser = new LBSC_User( strUserNameAux, strUserPasswordAux,
						"$$$", plbscglGroupList, this,
						MASTER_USER );
		strUDBLogged = strUserBaseNameAux;
	}

	bIsLogged = TRUE;
	bIsMono = tniPar.bMono;

	// entra na lista global de objetos LBSC_Session.
	_clSessList->Add( this, TAIL );

	SetError( LBS_OK );
	return( (const LBSC_Ticket*) plbsctTicket );
}

/***
	PRIVATE
	Metodo SLogin
	Faz o login de um usuario em um servidor, sem verificar a
	existencia/integridade dos dados passados como parametros.

	Parameters:
		- szUserName
		- szUserPassword
		- tmaServer

	Return:
		- LBS_OK se conseguir fazer o login ou erro.

	Comments:
		- Este metodo assume que os dados estao corretos e nao
		  verifica nenhuma BU.
		- A aplicacao NAO deve deletar o ticker retornado.
***/
const LBSC_Ticket*
LBSC_Session::SLogin( TNetInfo &tniPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::SLogin") );
	C_SessCritSect	cCS2( this, CRITSECT2 );
	bSLogin = TRUE;

	return( Login( tniPar ) );
}



/***
	PUBLIC
	Metodo Logout
	Faz o logout de um usuario em um servidor

	Parameters:

	Return:
		- LBS_OK se conseguir fazer o logout ou erro.

	Comments:

***/
int
LBSC_Session::Logout()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Logout") );

	UserSTR			strUserLogged = "";

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		// protecao contra leak
		if( pLoginInfo ){
			delete pLoginInfo;
			pLoginInfo = NULL;
		}
		ERETURN( LBSE_USERNOTLOGGED );
	}

	C_SessCritSect	cCS0( this, CRITSECT0 );
	C_SessCritSect	cCS1( this, CRITSECT1 );
	C_SessCritSect	cCS2( this, CRITSECT2 );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// controle de licencas
	LBSC_LicControl		cLicControl( &_tLicFileCreateTime );
	
	int	iRet = LBS_OK;
	if( !(iSecurityFlags & BS_LICENSE) ){
		iRet = cLicControl.DecLicense( &iNumLic, bIsMono, this );
		if( iRet != LBS_OK ){
			ERETURN( iRet );
		}
	} else {
		// nao checar licencas e resetar o flag
		iSecurityFlags &= !BS_LICENSE;
	}

	if( pLoginInfo ){
		delete pLoginInfo;
		pLoginInfo = NULL;
	}


	// fechar todas as bases que por acaso tenham ficado abertas
	lbscblBaseList.DelAll();

	// Deletar o objeto Usr
	if( plbscuUser ){
		strUserLogged = (char*) plbscuUser->GetUserName();
		strUserLogged.Upper();
		delete plbscuUser;
	}
	plbscuUser = NULL;

	bIsLogged = FALSE;
	bIsMono = FALSE;
	if( plbsctTicket ){
		delete plbsctTicket;
	}
	plbsctTicket = NULL;

	// nao podemos tentar sair da lista se ela ja' estiver processando seu
	// destrutor. Isso provocaria um crash, pois o destrutor da lista tentaria
	// deletar esta sessao e o destrutor desta sessao tentaria sair da lista,
	// atraves do Logout
	if( !_clSessList->bIsDying ){
		if( _clSessList->Find( this, CMPSESSIONPOINTER, TRUE ) != NULL ){
			// achamos o elemento na lista.
			// nao podemos chamar o metodo Del() da lista porque isso
			// provocaria uma chamada ao destrutor do elemento corrente, que
			// eh este metodo aqui!! Stack Overflow na certa!
			// Portanto, vamos primeiro limpar o elemento corrente da lista
			// e depois chamar o Del().
			_clSessList->Refresh( (LBSC_Session*) NULL );
			_clSessList->Del();
		}
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo GetFirstSession
	Obtem o primeiro elemento da lista de sessoes _clSessList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
LBSC_Session *
LBSC_Session::GetFirstSession()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetFirstSession") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	LBSC_Session	*pRet = _clSessList->First();

	return( pRet );
}


/***
	PRIVATE
	Metodo GetNextSession
	Obtem o proximo elemento da lista de sessoes _clSessList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
LBSC_Session *
LBSC_Session::GetNextSession()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetNextSession") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	LBSC_Session	*pRet = _clSessList->Next();

	return( pRet );
}


/***
	PRIVATE
	Metodo GetPreviousSession
	Obtem o elemento anterior da lista de sessoes _clSessList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
LBSC_Session *
LBSC_Session::GetPreviousSession()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetPreviousSession") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	LBSC_Session	*pRet = _clSessList->Previous();

	return( pRet );
}

/***
	PRIVATE
	Metodo GetLastSession
	Obtem o ultimo elemento da lista de sessoes _clSessList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
LBSC_Session *
LBSC_Session::GetLastSession()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetLastSession") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	LBSC_Session	*pRet = _clSessList->Last();

	return( pRet );
}

/***
	PUBLIC
	Metodo GetUsersInfo
	Obtem informacoes importantes para a aplicacao de gerencia de rede
	sobre todos os usuarios logados no momento.

	Parameters:
		- pTicketPar	-> ticket de seguranca.

	Return:
		- apontador para uma lista de informacoes do tipo
		  LBSC_AppUserInfoList ou NULL em caso de erro.

	Comments:
		- apenas o dono da DEFUDB pode usar este metodo.

***/
LBSC_AppUserInfoList *
LBSC_Session::GetUsersInfo( const LBSC_Ticket *pTicketPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUsersInfo") );
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	// verificar se o cara logado eh administrador na UDB default
	int iType = GetUserType( pTicketPar, NULL, NULL);
	if ( iType != MASTER_USER ) {
		NRETURN( LBSE_NOPERMISSION );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicketPar ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	// protege a lista de sessoes
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( !_clSessList->First() ){
		// deu alguma merda.
		NRETURN( LBSE_ERROR );
	}

	// instanciar um elemento LBSC_AppUserInfoList para perencher e retornar
	LBSC_AppUserInfoList	*pRetList = new LBSC_AppUserInfoList;
	if( !pRetList ){
		NRETURN( LBSE_NOMEMORY );
	}
	do{
		TAppUserNetInfo	tUserInfo;
		LBSC_Session	*pSessionObj = _clSessList->Current();

		if( pSessionObj ){
			tUserInfo.strUserName = pSessionObj->plbscuUser ? (char*) pSessionObj->plbscuUser->GetUserName() : (char*) "";
			char *szClient = pSessionObj->plbsctTicket->GetClientName();

			TAppUserNetInfo	*pUser = NULL;
			TAppNetInfo		*pApp = NULL;
			BOOL			bNewUser = FALSE;

			// procurar na lista pRetList para ver se ja' existe um usuario com mesmo nome
			// de szUserName
			if( pRetList->Find( &tUserInfo, CMPUSERNAME ) ){
				pUser = pRetList->Current();

				// procurar na lista de aplicacoes do usuario pela aplicacao relativa a essa sessao
				TAppNetInfo tAppInfo;
				tAppInfo.strAppName = pSessionObj->GetAppName();
				tAppInfo.strMachineName = szClient;
				tAppInfo.lAppId = pSessionObj->lAppId;
				
				pApp = pUser->pclAppInfo->Find(&tAppInfo);
				if ( !pApp ) {
					pApp = new TAppNetInfo;
					if ( !pApp ) {
						delete pRetList;
						delete szClient;
						NRETURN( LBSE_NOMEMORY );
					}
					pApp->strAppName = pSessionObj->GetAppName();
					pApp->strMachineName = szClient;
					pApp->lAppId = pSessionObj->lAppId;
					pUser->pclAppInfo->Add( pApp, TAIL );
				}
			} else {
				// alocar um nodo para a lista pRetList
				pUser = new TAppUserNetInfo;
				if( !pUser ){
					// nao deu.
					delete pRetList;
					delete szClient;
					NRETURN( LBSE_NOMEMORY );
				}

				// adicionar pUser em pRetList
				pRetList->Add( pUser, TAIL );

				bNewUser = TRUE;

				// preencher o nome do usuario
				pUser->strUserName = tUserInfo.strUserName;

				// alocar um nodo para a lista clAppInfo, de pUser
				pApp = new TAppNetInfo;
				if( !pApp ){
					// deu merda.
					delete pRetList;
					delete szClient;
					NRETURN( LBSE_NOMEMORY );
				}
				pApp->strAppName = pSessionObj->GetAppName();
				pApp->strMachineName = szClient;
				pApp->lAppId = pSessionObj->lAppId;

				pUser->pclAppInfo->Add( pApp, TAIL );
			}

			delete szClient;
			szClient = NULL;

			// preencher pclSessionInfo de pApp
			TAppSessionNetInfo		*pSess = new TAppSessionNetInfo;

			pSess->SetSessionPt( pSessionObj );
			pApp->pclSessionInfo->Add( pSess, TAIL );
			if ( pApp->tEntryAccess < pSessionObj->ulLastAccess ) {
				pApp->tEntryAccess = pSessionObj->ulLastAccess;
			}

			// preencher pclBaseInfo de pApp.
			// protege a lista de bases da sessao
			C_SessCritSect	cCS3( this, CRITSECT3 );
			if( pSessionObj->lbscblBaseList.First() ){
				do {
					TAppBaseNetInfo		*pBase = new TAppBaseNetInfo;
					if( !pBase ){
						// deu pau.
						delete pRetList;
						NRETURN( LBSE_NOMEMORY );
					}
					LBSC_Base	*pBaseAux = pSessionObj->lbscblBaseList.Current();
					
					// prevencao
					if( !pBaseAux ){
						// deu pau.
						delete pRetList;
						NRETURN( LBSE_NOMEMORY );
					}
					pBase->lBaseId = (long) pBaseAux;
					pBaseAux->GetBaseLongName( (char*) pBase->strBaseLongName );
					pBaseAux->GetBaseName( (char*) pBase->strBaseAliasName );
					pBase->lCurrRecord = pBaseAux->CurrRecNum( pSessionObj->plbsctTicket );
					pBase->bRecLocked = ((pBaseAux->CurrRecStatus( pSessionObj->plbsctTicket ) & REC_LOCKED)) ? TRUE : FALSE;

					// adioncar pBase na lista de bases de pSess
					pSess->pclBaseInfo->Add( pBase, TAIL );

				} while( pSessionObj->lbscblBaseList.Next() );
			}
		}
	} while( _clSessList->Next() );
	SetError( LBS_OK );
	return( pRetList );
}


/***
	Funcao LicTimerProc
	Funcao para tratamento de timer do controle de licencas

	Parameters:
		- hWnd : handle da janela que gerou o timer ( neste caso e sempre NULL )
		- uMsg : mensagem do windows ( neste caso sempre igual a WM_TIMER )
		- uTimerId : identificador do timer
		- dwTime : hora corrente do sistema

	Return:
		- LBS_OK em caso de sucesso ou erro.

	Comments:

***/
void CALLBACK
LicTimerProc( HWND hWnd, UINT uMsg, UINT uTimerId, DWORD dwTime )
{
	// a finalidade desta funcao eh checar se a data de criacao
	// do arquivo de licencas (existente apenas em copia REDE)
	// mudou. Se isso aconteceu, eh porque alguem deletou o arquivo
	// na porrada e tentou sacanear conosco. Entao, vamos invalidar o
	// arquivo para que novos logins nao sejam efetuados.

	// observe que este esquema nao eh o unico que tenta evitar
	// sacanagens por parte do usuario. isso aqui eh apenas um
	// complemento do esquema. o principal ponto de checagem
	// do arquivo de licencas eh o metodo Logout, da classe LBSC_Session.


	if( _tLicFileCreateTime == 0 ){
		// ainda nao temos condicoes de testar, pois a
		// variavel que determina a data de criacao do arquivo
		// que temos guardada ainda nao foi devidamente inicializada.
		// (ninguem fez login ainda neste LBS)
		return;
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		return;
	}
	// vamos abrir o arquivo de licencas

	char			szDirBase[ FULLNAMESIZE ];
	char			szAux[ FILENAMESIZE ];
	char			szLicFile[ FULLNAMESIZE ];
	C_RecordFile	cLicFile( LICFILE_MAGICNUMBER );

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		return;
	}

	// testar o numero magico do arquivo de licencas
	sprintf( szLicFile, "%s\\%s", szDirBase, LICFILENAME );
	{
		C_File	cfAux( szLicFile, "r", SH_DENYNO );

		if( cfAux.IsOpen() ){
			// ler o primeiro byte, que eh o numero magico.
			BYTE	bMag;

			if( cfAux.Seek( 0, SEEK_SET ) == OK ){
				if( cfAux.Read( &bMag, sizeof( bMag ) ) == OK ){
					if( bMag != LICFILE_MAGICNUMBER ){
						// numero magico invalido.
						return;
					}
				}
			}
		}
	}
	// tentar NUMTRYLIC vezes abrir o arquivo
	for( int i = 0; i < NUMTRYLIC; i++){
		if( cLicFile.Open( szLicFile, sizeof( TLicInfoFixHead ), sizeof( TLicInfoFix ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
//			"HEADKEY", "RECKEY", "r", SH_DENYNO ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cLicFile.IsOpen() ){
		// nao consegui abrir o arquivo de licencas
		return;
	}

	if( cLicFile.R_FileSize() <= 0 ){
		// acabamos de criar o arquivo. mas esta funcao nao deveria fazer isso!
		// se aconteceu aqui, eh porque alguem detonou o arquivo de licencas
		// e isto significa que...

		// alguem detonou o arquivo de licencas. vamos detonar
		// todo mundo. NINGUEM MAIS CONSEGUIRA' USAR O LIGHT!!!
		// HA! HA! HA! HA! HA! 
		TLicInfoFixHead	tHead( FALSE, FALSE, 0, 0 );
		cLicFile.R_WriteHead( &tHead );
		cLicFile.Close();
		return;
	}

	// conseguimos abrir o arquivo, entao podemos trabalhar em paz,
	// pois ninguem mais podera' abri-lo enquanto estivermos usando.
	TLicInfoFixHead	tHead;
	if( cLicFile.R_ReadHead( &tHead ) != 0 ){
		// deu pau.
		return;
	}
	if( tHead.tTime != _tLicFileCreateTime ){
		// fudeu! alguem detonou o arquivo enquanto estavamos logado.
		// vamos ligar o "bit fatal", para que ninguem mais possa usar
		// o sistema. REPETINDO: NINGUEM MAIS PODERA' USAR O SISTEMA
		// ENQUANTO ELE NAO FOR TOTALMENTE RESETADO!!!
		// HA! HA! HA! HA! HA! HA! HA! ...
		tHead.bCanUse = FALSE;
		tHead.tTime = 0;
		cLicFile.R_WriteHead( &tHead );
	}

	// testar se a licenca usada por este LBS esta' invalida

	// ler os registros do grupo 1
	char *szMachineName = LBSC_Session::WhatServers();
	if( !szMachineName ){
		return;
	}
	cLicFile.R_Seek( 0 );
	for( i = 0; i < tHead.lNumRec; i++ ){
		TLicInfoFix	tInfo;
		if( cLicFile.R_Read( &tInfo ) != OK ){
			// deu pau
			delete szMachineName;
			return;
		}
		int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
		if( stricmp( (char*) tInfo.tLicSerial.strSerialSvc, ::GetSerialNumber() ) == 0 ){
			// achamos um registro com o numero de serie deste LBS.
			BOOL	bMod = FALSE;

			// procurar maquina (registros do grupo 2)
			for( int j = 0; j < iNumUsers; j++ ){
				cLicFile.R_SeekNext();
				if( cLicFile.R_Read( &tInfo ) != OK ){
					// deu pau
					delete szMachineName;
					return;
				}
				if( stricmp( (char*) tInfo.tLicClient.strClient, szMachineName ) == 0 ){
					// achamos a maquina
					if( tInfo.tLicClient.iCount < 0 ){
						// achamos uma licenca invalida.
						// vamos setar a variavel que indica aos outros metodos que
						// as aplicacoes devem sair do ar e retornar para que o LBS
						// revalide a licenca.
						_bInvalidLicence = TRUE;
						delete szMachineName;
						return;
					}
				}
			}
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
}


int CompareCacheInfo ( const void *elem1, const void *elem2 ) 
{
	if ( !elem1 || !elem2 ) {
		return -1;
	}

	int iRet = stricmp( ((TUserCacheInfo *)elem1)->szName, ((TUserCacheInfo *)elem2)->szName );
	if ( iRet != 0 ) {
		return iRet;
	}

	if ( stricmp( ((TUserCacheInfo *)elem1)->szPwd, "") != 0 ) {
		iRet = stricmp( ((TUserCacheInfo *)elem1)->szPwd, ((TUserCacheInfo *)elem2)->szPwd );
		if ( iRet != 0 ) {
			return iRet;
		}
	}

	if ( (((TUserCacheInfo *)elem1)->tUDBInfo.szUDB) == "" || (((TUserCacheInfo *)elem2)->tUDBInfo.szUDB) == "" ) {
		// nao ta interessado em comparar por UDB
		return 0;
	}
	return stricmp( ((TUserCacheInfo *)elem1)->tUDBInfo.szUDB, ((TUserCacheInfo *)elem2)->tUDBInfo.szUDB );
}


typedef struct _tUDBs {
public:
	LBSC_Base *pBase;
	CL_StringN<FULLNAMESIZE>	szUDBName;

	_tUDBs()
	{
		pBase = NULL;
		szUDBName = "";
	}
	~_tUDBs()
	{
		if ( pBase ) {
			delete pBase;
			pBase = NULL;
		}
		szUDBName = "";
	}
} TUDBs;


void
LBSC_Session::SaveUserCache()
{
	// PEND
}

void
LBSC_Session::ClearAll()
{
	if ( pUserCache ) {
		delete [] pUserCache;
		pUserCache = NULL;
	}
	if ( pControlFile ) {
		delete pControlFile;
		pControlFile = NULL;
	}
	if ( pLRUBases ) {
		delete pLRUBases;
		pLRUBases = NULL;
	}
}

void
LBSC_Session::LoadUserCacheFromBases()
{
	if ( !ControlFileOK() ) {
		return;
	}
	if ( !LBSC_ServerConfig::UserCacheEnabled() ) {
		return;
	}

	LBSC_ServerBasesList *pBasesList = WhatBasesOnServer( 1, "" );

	if ( !pBasesList || pBasesList->NumElem() == 0 ) {
		return;
	}

	// obtem os nomes das udbs
	int iNumUDBs = 0;
	TServerBases *ptsbServerBases = pBasesList->First();
	while ( ptsbServerBases ) {
		if ( ptsbServerBases->GetBaseType() == USER_BASE ) {
			iNumUDBs++;
		}
		ptsbServerBases = pBasesList->Next();
	}

	if ( iNumUDBs == 0 ) {
		delete pBasesList;
		return;
	}

	TUDBs *pUDBs = new TUDBs[iNumUDBs];
	if ( !pUDBs ) {
		delete pBasesList;
		return;
	}

	// abre as udbs

	LBSC_Session lsSess;
	TNetInfo			tni( "$", "$", NULL, NULL, NULL, NULL );
	const	LBSC_Ticket	*ptTicket = lsSess.SLogin( tni );
	if ( !ptTicket ) {
		delete pBasesList;
		delete [] pUDBs;
		return;
	}
	int iUDBsIndex = 0;
	int iNumUsers = 0;
	ptsbServerBases = pBasesList->First();
	while ( ptsbServerBases ) {
		if ( ptsbServerBases->GetBaseType() == USER_BASE ) {
			// abrir a base de usuarios
			LBSC_Base *pbUserBase = new LBSC_Base( ptTicket, ptsbServerBases->GetBaseName(), &lsSess );
			if ( !pbUserBase ) {	// lascou..
				delete pBasesList;
				delete [] pUDBs;
				return;
			}
			if( pbUserBase->LastError() == LBSE_OLDBASEVERSION ){
				// precisamos converter a UDB; 
				delete pbUserBase;
				lsSess.ConvertBase( ptTicket, ptsbServerBases->GetBaseName(), "" );
				// tentar abrir novamente a UDB
				pbUserBase = new LBSC_Base( ptTicket, ptsbServerBases->GetBaseName(), &lsSess );
				if ( !pbUserBase ) {	// lascou..
					delete pBasesList;
					delete [] pUDBs;
					return;
				}
			}
			if( pbUserBase->BaseObjOk() && pbUserBase->GetNumActiveRecords( ptTicket ) > 0 ){
				pbUserBase->FirstRecord( ptTicket );
				pUDBs[iUDBsIndex].pBase = pbUserBase;
				pUDBs[iUDBsIndex].szUDBName = ptsbServerBases->GetBaseName();
				iNumUsers += pbUserBase->GetNumActiveRecords( ptTicket );
				iUDBsIndex++;
			}
			else {
				delete pbUserBase;
			}
		}
		ptsbServerBases = pBasesList->Next();
	}
	delete pBasesList;

	if ( iNumUsers == 0 ) {
		delete [] pUDBs;
		return;
	}

	// agora vamos mexer na cache...
	// nao vamos entrar em regiao critica pq neste ponto nao deve 
	// haver nenhum outro thread executando. Se entrarmos, pode haver risco de 
	// deadlock 

	iUserCacheSize = iNumUsers;		
	pUserCache = new TUserCacheInfo[iUserCacheSize];
	if ( !pUserCache ) {
		delete [] pUDBs;
		return;
	}

	int j=0;
	for ( int i=0; i<iNumUDBs; i++ ) {
		// abrir a base de usuarios
		if( pUDBs[i].pBase ) { 
			do {
				LBSC_Field	*pf = (*(pUDBs[i].pBase))[ USERBASEUSERNAME ];
				LBSC_Data	*pd = pf ? (*pf)[ 0 ] : NULL;
				pUserCache[ j ].szName = pd ? (char*) (*pd) : (char*) "";

				pf = (*(pUDBs[i].pBase))[ USERBASEUSERPASSWORD ];
				pd = pf ? (*pf)[ 0 ] : NULL;
				pUserCache[ j ].szPwd = pd ? (char*) (*pd) : (char*) "";

				pUserCache[ j ].tUDBInfo.szUDB = pUDBs[i].szUDBName;

				pf = (*(pUDBs[i].pBase))[ USERBASEUSERTYPE ];
				pd = pf ? (*pf)[ 0 ] : NULL;
				pUserCache[ j ].tUDBInfo.iType = pd ? (long) (*pd) : NOP_USER;

				// se a senha ainda nao tiver sido alterada, esse cara eh um usuario de antes da correcao do bug das senhas
				pf = (*(pUDBs[i].pBase))[ USERBASEPASSWORDCHANGEDATE ];
				if ( pf && pf->GetNumberOfRepetition() > 0 ) {
					pUserCache[ j ].tUDBInfo.bOldUser = FALSE;
				} else {
					pUserCache[ j ].tUDBInfo.bOldUser = TRUE;
				}

				j++;
				
			} while( pUDBs[i].pBase->NextRecord( ptTicket ) == LBS_OK );
		}
	}

	delete [] pUDBs;
	qsort( pUserCache, iUserCacheSize, sizeof(TUserCacheInfo), CompareCacheInfo );
}

BOOL
LBSC_Session::LoadUserCacheFromFile()
{
	// PEND
	return FALSE;
}

void
LBSC_Session::LoadUserCache()
{
	if ( !LoadUserCacheFromFile() ) {
		LoadUserCacheFromBases();
	}
}

void
LBSC_Session::ChangeUserCachePwd( const char *szName, const char *szPwd, 
								const char *szUDB, const char *szNewPwd )
{
	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 
	if ( !szName || !szPwd || !pUserCache || iUserCacheSize <= 0 ) {
		return; 
	}

	int iPos = FindUserInCache( szName, szPwd, szUDB );
	if ( iPos < 0 ) {	
		return; 
	}

	if ( szUDB ) {	// mudar apenas nessa UDB
		pUserCache[iPos].szPwd = szNewPwd;
	} else {
		// mudar em todas as UDBs em que ele aparece
		for ( int i = iPos; i < iUserCacheSize;  i++) {
			if ( stricmp( pUserCache[i].szName, szName ) == 0 && 
					stricmp( pUserCache[i].szPwd, szPwd ) == 0 ) {
				pUserCache[i].szPwd = szNewPwd;
				pUserCache[i].tUDBInfo.bOldUser = FALSE;
			} else {
				// acabou
				break;
			}
		}
	}

	qsort( pUserCache, iUserCacheSize, sizeof(TUserCacheInfo), CompareCacheInfo );
}

void
LBSC_Session::ChangeUserCacheType( const char *szName, const char *szPwd, 
								const char *szUDB, int iNewType )
{
	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 
	if ( !szName || !szPwd || !szUDB || !pUserCache || iUserCacheSize <= 0 ) {
		return; 
	}

	TUserCacheInfo tciFind;
	tciFind.szName = szName;
	tciFind.szPwd = szPwd;
	tciFind.tUDBInfo.szUDB = (char *)szUDB;
	TUserCacheInfo *ptciFound = (TUserCacheInfo *)bsearch( 
				(const void *)&tciFind, 
				(const void *)pUserCache, 
				iUserCacheSize, 
				sizeof(TUserCacheInfo), 
				CompareCacheInfo );

	if ( !ptciFound || ptciFound->tUDBInfo.szUDB == "" ) {
		return; 
	}
	ptciFound->tUDBInfo.iType = iNewType;
}

void
LBSC_Session::DelUDBFromCache( const char *szUDB )
{
	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 
	if ( !szUDB || !pUserCache || iUserCacheSize <= 0 ) {
		return; 
	}
	if ( iUserCacheSize > 1 ) {
		int iUser = 0;
		//contar o numero de usuarios que irao sair da cache
		for ( int i=0; i < iUserCacheSize; i++ ) {
			if ( pUserCache[i].tUDBInfo.szUDB == szUDB ){
				iUser++;
			}
		}
		//Alocar espaco para a nova cache
		TUserCacheInfo *pNewUserCache = new TUserCacheInfo[ iUserCacheSize - iUser ];

		//Copiar para a nova cache os usuarios que nao sao da UDB a ser deletada
		int j;
		for ( j = 0, i=0; i < iUserCacheSize ; i++ ) {
			if ( pUserCache[i].tUDBInfo.szUDB != szUDB ){
				pNewUserCache[ j ] = pUserCache[i];
				j++;
			}
		}
		//Decrementar o contador da cache
		iUserCacheSize -= iUser; 

		//destruir a cache atual 
		delete [] pUserCache;	
		pUserCache = pNewUserCache;
		qsort( pUserCache, iUserCacheSize, sizeof(TUserCacheInfo), CompareCacheInfo );
	} else {
		//Zerar a cache se nao sobrou mais nenhum usuario nela.
		delete pUserCache;	
		iUserCacheSize--;
		pUserCache = NULL;
	}
}


void
LBSC_Session::AddUserToCache( const char *szNewName, const char *szNewPwd, 
								const char *szNewUDB, int iNewType )
{
	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 
	if ( !szNewName || !szNewPwd || !szNewUDB || !pUserCache || iUserCacheSize <= 0 ) {
		return; 
	}

	TUserCacheInfo *pNewUserCache = new TUserCacheInfo[iUserCacheSize + 1];
	if ( !pNewUserCache ) {
		return; 
	}

	for ( int i=0; i<iUserCacheSize; i++ ) {
		pNewUserCache[i] = pUserCache[i]; 
	}
	pNewUserCache[iUserCacheSize].szName = szNewName;
	pNewUserCache[iUserCacheSize].szPwd = szNewPwd;
	pNewUserCache[iUserCacheSize].tUDBInfo.szUDB = szNewUDB;
	pNewUserCache[iUserCacheSize].tUDBInfo.iType = iNewType;

	// vamos destruir a cache atual 
	delete [] pUserCache;	

	iUserCacheSize++;
	pUserCache = pNewUserCache;
	qsort( pUserCache, iUserCacheSize, sizeof(TUserCacheInfo), CompareCacheInfo );
}

void
LBSC_Session::DelUserFromCache( const char *szOldName, const char *szOldPwd, 
								const char *szOldUDB )
{
	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 
	if ( !szOldName || !szOldPwd || !szOldUDB || !pUserCache || iUserCacheSize <= 0 ) {
		return; 
	}

	TUserCacheInfo tciFind;
	tciFind.szName = szOldName;
	tciFind.szPwd = szOldPwd;
	tciFind.tUDBInfo.szUDB = (char *)szOldUDB;
	TUserCacheInfo *ptciFound = (TUserCacheInfo *)bsearch( 
				(const void *)&tciFind, 
				(const void *)pUserCache, 
				iUserCacheSize, 
				sizeof(TUserCacheInfo), 
				CompareCacheInfo );

	if ( !ptciFound || ptciFound->tUDBInfo.szUDB == "" ) {
		return; 
	}


	int iPos = ptciFound - pUserCache;

	if ( iUserCacheSize > 1 ) {
		TUserCacheInfo *pNewUserCache = new TUserCacheInfo[iUserCacheSize - 1];
		if ( !pNewUserCache ) {
			return; 
		}

		for ( int i=0; i<iPos; i++ ) {
			pNewUserCache[i] = pUserCache[i]; 
		}
		i++;
		for ( ; i<iUserCacheSize; i++ ) {
			pNewUserCache[i-1] = pUserCache[i]; 
		}

		// vamos destruir a cache atual 
		delete [] pUserCache;	

		iUserCacheSize--;
		pUserCache = pNewUserCache;
		qsort( pUserCache, iUserCacheSize, sizeof(TUserCacheInfo), CompareCacheInfo );
	} else {
		delete pUserCache;	
		iUserCacheSize--;
		pUserCache = NULL;
	}
}


int
LBSC_Session::FindUserInCache( const char *szUserName, const char *szPassword, const char *szUDB )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::FindUserInCache") );

	C_SessCritSect	cCS7( NULL, CRITSECT7 ); 

	if ( !szUserName ) {
		return( LBSE_BADARG ); 
	}
	if ( !pUserCache || iUserCacheSize <= 0 ) {
		LoadUserCache();
		if( !pUserCache || iUserCacheSize <= 0 ){
			return( LBSE_BADARG ); 
		}
	}

	TUserCacheInfo tciFind;
	tciFind.szName = szUserName;
	tciFind.szPwd = szPassword;
	tciFind.tUDBInfo.szUDB = szUDB;
	TUserCacheInfo *ptciFound = (TUserCacheInfo *)bsearch( 
				(const void *)&tciFind, 
				(const void *)pUserCache, 
				iUserCacheSize, 
				sizeof(TUserCacheInfo), 
				CompareCacheInfo );

	if ( !ptciFound || ptciFound->tUDBInfo.szUDB == "" ) {
		return( LBSE_BADARG ); 
	}

	// vamos achar o primeiro da lista
	int iPos = ptciFound - pUserCache - 1;
	if ( !szPassword && szUDB ) {
		// nao precisa procurar mais, ja achamos o cara
		return iPos+1;
	}
	while ( iPos >= 0 && stricmp( pUserCache[iPos].szName, szUserName ) == 0 ) {
		if ( szPassword && stricmp( pUserCache[iPos].szPwd, szPassword ) != 0 ) {
			break;
		}
		iPos--;
	}
	return iPos+1;
}

char *
LBSC_Session::WhatUDBsForUser( const char *szUserName, const char *szPassword, const char * )
{
	if ( !szUserName || !szPassword ) {
		NRETURN( LBSE_BADARG );  
	}

	char *szRet = NULL;
	int iRet = LBS_OK;

	// temos que entrar nas regioes em que o login entra pra evitar deadlocks
	C_SessCritSect	cCS0( this, CRITSECT0 );
	C_SessCritSect	cCS1( this, CRITSECT1 );
	C_SessCritSect	cCS2( this, CRITSECT2 );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// e agora entrar na regiao critica da cache de usuarios
	C_SessCritSect	cCS7( this, CRITSECT7 );

	// primeiro verificar se o cara realmente existe
	int iFirstUsr = FindUserInCache( szUserName, "", NULL );
	if ( iFirstUsr < 0 ) {	// nao achou
		NRETURN( LBSE_USERNOTFOUND );  
	}

	if ( LBSC_ServerConfig::MaxInvalidLoginAttempts() > 0 || LBSC_ServerConfig::PasswordExpireInterval() > 0 ) {
		// se a verificacoes de seguranca estao ligadas
		// devemos checar se eh pra bloquear o sujeito ou negar o login

		// pra isso basta tentar um login nas udbs em que ele esta cadastrado
		for ( int i = iFirstUsr; i < iUserCacheSize && 
						stricmp( pUserCache[i].szName, szUserName ) == 0; i++) {

			if ( pUserCache[i].tUDBInfo.szUDB != "" ) {

				TNetInfo	tni( (char *)szUserName, (char *)szPassword, pUserCache[i].tUDBInfo.szUDB, NULL, NULL, NULL );
				const	LBSC_Ticket	*pTicket = Login( tni );
				switch( LastError() ) {
				case LBSE_USERBLOCKED:
					iRet = LBSE_USERBLOCKED;
					break;
				case LBSE_USERBLOCKING:
					if ( iRet != LBSE_USERBLOCKED ) {
						iRet = LBSE_USERBLOCKING;
					}
					break;
				case LBSE_PASSWORDEXPIRED:
					if ( iRet != LBSE_USERBLOCKED && iRet != LBSE_USERBLOCKING ) {
						iRet = LBSE_PASSWORDEXPIRED;
					}
					break;
				}
				if ( pTicket ) {
					Logout();
				} 
			}
		}

		if ( iRet == LBSE_USERBLOCKING || iRet == LBSE_USERBLOCKED ) {
			NRETURN( iRet );  
		}
	}

	char szCryptPwd[FULLNAMESIZE + 1];
	int iPos = FindUserInCache( szUserName, szPassword, NULL );
	if ( iPos < 0 ) {	// nao achou, vamos ver se esse eh um cara afetado pelo bug das senhas no cliente/servidor
		strncpy( szCryptPwd, szPassword, PASSWORDSIZE );
		szCryptPwd[PASSWORDSIZE] = '\0';

		// o bug era tentar criptografar um string como string 
		// e nao como uma tira de bytes
		Criptografa(szCryptPwd, szCryptPwd + strlen(szCryptPwd) );
		Decriptografa(szCryptPwd, szCryptPwd + strlen(szCryptPwd) );

		iPos = FindUserInCache( szUserName, szCryptPwd, NULL );
		if ( iPos < 0 || !(pUserCache[iPos].tUDBInfo.bOldUser) ) {	
			// agora nao tem jeito; esse cara nao existe mesmo...
			NRETURN( LBSE_USERNOTFOUND );  
		}
		szPassword = szCryptPwd;
	}

	int iOrigSize = 1;
	szRet = Strdup( "" );
	if ( !szRet ) {
		NRETURN( LBSE_NOMEMORY );  
	}
	for ( int i = iPos; i < iUserCacheSize;  i++) {
		if ( stricmp( pUserCache[i].szName, szUserName ) == 0 && 
				stricmp( pUserCache[i].szPwd, szPassword ) == 0 ) {
			if ( pUserCache[i].tUDBInfo.szUDB != "" ) {
				int iNewSize = strlen(pUserCache[i].tUDBInfo.szUDB) + 1;
				szRet = (char *)LBS_Realloc( szRet, iOrigSize, iOrigSize + iNewSize );
				if ( !szRet ) {
					NRETURN( LBSE_NOMEMORY );  
				}
				strcat( szRet, pUserCache[i].tUDBInfo.szUDB );
				strcat( szRet, " ");
				iOrigSize += iNewSize;
			}
		}
		else {
			// acabou
			break;
		}
	}
	SetError( iRet );
	return szRet;
}

/***
	PUBLIC
	Metodo GetUDBTimeInfo
	Obtem informacoes sobre datas/horas de criacao/modificacao/acesso
	do arquivo LB1 da UDB desta sessao.

	Parameters:
		- psInfo	-> ponteiro para uma estrutura stat

	Return:
		- LBS_OK em caso de sucesso;
		  LBSE_ERROR caso ocorra algum erro.

	Comments:
		- 

***/
int
LBSC_Session::GetUDBTimeInfo( struct stat *psInfo )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetUDBTimeInfo") );

	// Obter o nome do arquivo LB4 da UDB
	char szDirBases[ FILENAMESIZE ];
	char szFullBasePath[ FILENAMESIZE ];
	LBSC_Base::GetDirBase( szDirBases );
	sprintf( szFullBasePath, "%s\\%s\\%s%s", (char*) szDirBases, (char*) strUDBLogged, (char*) strUDBLogged, REPETITIONFILEEXT );
	strupr( (char*) szFullBasePath );

	int	iStat = stat( szFullBasePath, psInfo );
	int	iRet = LBSE_ERROR;
	if( iStat == 0 ) {
		iRet = LBS_OK;
	}

	ERETURN( iRet );
}


void						
LBSC_Session::GetClientName( char *szClient )
{
	if ( !szClient || !plbsctTicket ) {
		return;
	}
	char *szAux = plbsctTicket->GetClientName();
	strcpy( szClient, szAux ? szAux : "?" );
	if( szAux ){
		delete szAux;
	}
}

//
//	Verifica se excedeu o numero de tentativas incorretas de login e 
//	atualiza esse contador para o usuario
//
int				
LBSC_Session::VerifyLoginAttempts( LBSC_Base *pUserBase, char *szUser )
{
	int iLastError = LastError();

	if ( LBSC_ServerConfig::MaxInvalidLoginAttempts() <= 0 || pUserBase->GetBaseType() != USER_BASE ) {
		// nao ha o que verificar
		ERETURN (LBS_OK);
	}

	char szName[USERNAMESIZE + 1];

	if ( pUserBase->GetFieldRepetition( USERBASEUSERNAME, 0, szName ) != LBS_OK ) {
		ERETURN (LBS_OK);
	}

	if ( stricmp( szName, szUser ) != 0 ) {
		ERETURN (LBS_OK);
	}

	long lCurLoginAttempts=0;
	if ( pUserBase->GetNumberOfRepetition( USERBASELOGINATTEMPTS ) <= 0 || 
			pUserBase->GetFieldRepetition( USERBASELOGINATTEMPTS, 0, &lCurLoginAttempts ) != LBS_OK ) {
		lCurLoginAttempts = 0;
	}

	if ( iLastError == LBSE_INVALIDPASSWORD ) {
		lCurLoginAttempts++;
	} 

	if ( iLastError == LBS_OK && lCurLoginAttempts == 0 ) {
		// tudo certo
		ERETURN (LBS_OK);
	}

	int iRet = LBS_OK;

	if ( lCurLoginAttempts >= LBSC_ServerConfig::MaxInvalidLoginAttempts() ) {
		// bloquear o usuario
		iRet = LBSE_USERBLOCKED;
	} else if ( iLastError == LBSE_INVALIDPASSWORD ) {
		// o cara esta em processo de bloqueio; ainda tem chance de nao ser bloqueado
		iRet = LBSE_USERBLOCKING;
	} else if ( iLastError == LBS_OK ) {
		// vamos limpar o cara; acertou a senha antes de ser bloqueado...
		lCurLoginAttempts = 0;
	} 

	// agora vamos atualizar o contador de tentativas incorretas
	if ( pUserBase->LockRecord( plbsctTicket, TRUE ) == LBS_OK ) {
		pUserBase->PutFieldRepetitionByIndex( USERBASELOGINATTEMPTS, lCurLoginAttempts, 0 );
		pUserBase->UpdateRecord( plbsctTicket );
		pUserBase->ReleaseRecord( plbsctTicket );
	}

	ERETURN (iRet);
}


//
//	Verifica se excedeu o numero de tentativas incorretas de login e 
//	atualiza esse contador para o usuario
//
BOOL				
LBSC_Session::PasswordExpired( LBSC_Base *pUserBase, char *szUser )
{
	if ( LBSC_ServerConfig::PasswordExpireInterval() <= 0 || pUserBase->GetBaseType() != USER_BASE ) {
		return FALSE;
	}

	char szName[USERNAMESIZE + 1];

	if ( pUserBase->GetFieldRepetition( USERBASEUSERNAME, 0, szName ) != LBS_OK ) {
		return FALSE;
	}

	if ( stricmp( szName, szUser ) != 0 ) {
		return FALSE;
	}

	C_Date cdCurChangeDate;
	if ( pUserBase->GetNumberOfRepetition( USERBASEPASSWORDCHANGEDATE ) <= 0 || 
			pUserBase->GetFieldRepetition( USERBASEPASSWORDCHANGEDATE, 0, &cdCurChangeDate ) != LBS_OK ||
			cdCurChangeDate.Hash() == 0 ) {
		// criar a data pra esse usuario; pra efeito de expiracao de senha,
		// vai contar a partir do dia atual
		if ( pUserBase->LockRecord( plbsctTicket, TRUE ) == LBS_OK ) {
			pUserBase->PutFieldRepetitionByIndex( USERBASEPASSWORDCHANGEDATE, C_Date(), 0 );	// data de hoje
			pUserBase->UpdateRecord( plbsctTicket );
			pUserBase->ReleaseRecord( plbsctTicket );
		}

		return FALSE;
	}

	C_Date cdToday;
	if ( (cdToday - cdCurChangeDate) > LBSC_ServerConfig::PasswordExpireInterval() ) {
		return TRUE;
	}

	return FALSE;
}


//
//	Verifica se eh necessario alterar a senha do usuario por conta do bug 
//	das senhas no cliente/servidor
//
BOOL				
LBSC_Session::NeedUptadeUserPassword( LBSC_Base *pUserBase, char *szUser, char *szCheckPassword )
{
	if ( pUserBase->GetBaseType() != USER_BASE ) {
		return FALSE;
	}
	char szName[USERNAMESIZE + 1];
	szName[0] = '\0';
	char szPwd[PASSWORDSIZE + 1];
	szPwd[0] = '\0';

	pUserBase->GetFieldRepetition( USERBASEUSERNAME, 0, szName );
	pUserBase->GetFieldRepetition( USERBASEUSERPASSWORD, 0, szPwd );

	if ( stricmp( szName, szUser ) != 0 ) {
		return FALSE;
	}

	if ( pUserBase->GetNumberOfRepetition( USERBASEPASSWORDCHANGEDATE ) > 0 ) {
		// ja corrigiu, se tivesse que ter corrigido
		return FALSE;
	}

	if ( stricmp( szPwd, szCheckPassword ) == 0 ) {
		// se ja esta ok, pra que mudar?
		return FALSE;
	}

	char szCrypt[PASSWORDSIZE + 1];
	strncpy( szCrypt, szCheckPassword, PASSWORDSIZE );
	szCrypt[PASSWORDSIZE] = '\0';

	// o bug era tentar criptografar um string como string 
	// e nao como uma tira de bytes
	Criptografa(szCrypt, szCrypt + strlen(szCrypt) );
	Decriptografa(szCrypt, szCrypt + strlen(szCrypt) );

	if ( stricmp( szPwd, szCrypt ) != 0 ) {
		// a senha que o cara passou eh outra mesmo
		return FALSE;
	}
	// a senha depois da criptografia esta ok; devemos corrigir esse cara na UDB
	return TRUE;
}

LBSC_Base *
LBSC_Session::NewBaseHandler( const LBSC_Ticket *lbscTicket, const char *szFullBaseName,
			const char *szBaseLongNamePar,
			const char *szBasePassword,
			LBSC_Session *plbscsSession, BOOL bExclusive,
			BOOL bReadOnly, BOOL bMaintenance, BOOL bCheckVersion )
{
	C_SessCritSect	cCS10( NULL, CRITSECT10 );	// para proteger a LRU de bases
	LBSC_Base *pBase = GetBaseHandler( szFullBaseName, plbscsSession );
	if ( !pBase ) {
		pBase = new LBSC_Base( lbscTicket, szFullBaseName, szBaseLongNamePar, szBasePassword,
				plbscsSession, bExclusive, bReadOnly, bMaintenance, bCheckVersion );
	}
	return pBase;
}


LBSC_Base *
LBSC_Session::NewBaseHandler( const LBSC_Ticket *lbscTicket, const char *szFullBaseName, 
			LBSC_Session *plbscsSession, BOOL bExclusive, BOOL bReadOnly, BOOL bMaintenance )
{
	C_SessCritSect	cCS10( NULL, CRITSECT10 );	// para proteger a LRU de bases
	LBSC_Base *pBase = GetBaseHandler( szFullBaseName, plbscsSession );
	if ( !pBase ) {
		pBase = new LBSC_Base ( lbscTicket, szFullBaseName, plbscsSession, bExclusive, 
			bReadOnly, bMaintenance );
	}
	return pBase;
}


void LBSC_Session::ReturnBaseHandler( LBSC_Base *pBase )
{
	C_SessCritSect	cCS10( NULL, CRITSECT10 );	// para proteger a LRU de bases

	delete pBase;
/***	LRU de bases desabilitada por enquanto
	if ( !pLRUBases || strchr( pBase->szBaseLongName, '\\' ) ) {
		delete pBase;
		return;
	}
	pLRUBases->Add( pBase, TAIL );
***/
}	

LBSC_Base *LBSC_Session::GetBaseHandler( const char *szBaseName, LBSC_Session *pSession )
{
	C_SessCritSect	cCS10( NULL, CRITSECT10 );	// para proteger a LRU de bases

	return NULL;

/***	LRU de bases desabilitada por enquanto

	if ( strchr( szBaseName, '\\' ) ) {
		return NULL;
	}
	if ( !pLRUBases ) {
		pLRUBases = new LBSC_BaseList;
		// criamos a lista agora, nem precisa procurar que nao vai achar
		return NULL;
	}
	LBSC_Base lbFindBase;
	lbFindBase.szBaseName = szBaseName;

	LBSC_Base *pFound = pLRUBases->Find( &lbFindBase, CMPBASENAME );

	if ( !pFound ) {
		return NULL;
	}
	pLRUBases->Refresh(NULL);
	pLRUBases->Del();

	// limpar atributos...
	pFound->SetError(0);

	/***
	bHeaderLocked = FALSE;
	bSelfReorganize = FALSE;
	bFullAccess = FALSE;
	bIsExclusive = FALSE;
	bIsReadOnly = FALSE;
	bBaseUpdated = FALSE;
	bACLChanged = FALSE;
	plbscisIndexSystem = NULL;
	plbscsOwnerSession = NULL;
	iLockTimeOut = LOCKTIMEOUT;
	iLockTimeSleep = LOCKTIMESLEEP;
	bBaseObjOk = TRUE;
	uTimerId = 0;
	lLockPos = -1;
	bPrivateCreation = FALSE;
	bStruct = TRUE;
	bSelfDelete = FALSE;
	pvUserData = NULL;
	lUserDataSize = 0L;
	lbscrCurrRecord.Clear();
	pltcMaskList = new LTC_TERMLIST;
	pltcPhone = new LTC_PHONE;
	pltcSynonym = new LTC_SYNONYM;
	iNavigationState = 0;
	iNavigationIndex = 0;
	uiNavigationField = 0;
	szNavigationKey = NULL;
	iSearchType = EQUAL_KEY;
	szStdArray = NULL;
	pcOLList = NULL;
	pOcListOfCurrKey = NULL;
	iIndexTree = 0;
	bStopIndex = FALSE;
	bSecureSort = TRUE;
	bAppendingRec = FALSE;
	bIsBasePasswdCorrect = FALSE;
	bFastRec = FALSE;
	strLogFieldAliasName = "";
	szExcludeModulesFromLog = "";
	szFieldsForUpdateLog = "";
	iOperationLogMask = 0;
	pFound->iNavigationState = 0;
	pFound->iNavigationIndex = 0;
	pFound->uiNavigationField = 0;
	if( pFound->pvUserData ){
		delete pFound->pvUserData;
		pFound->pvUserData = NULL;
	}
	if( pFound->pOcListOfCurrKey ){
		delete pFound->pOcListOfCurrKey;
		pFound->pOcListOfCurrKey = NULL;
	}
	if( pFound->szNavigationKey ){
		delete pFound->szNavigationKey;
		pFound->szNavigationKey = NULL;
	}
	pFound->iSearchType = EQUAL_KEY;
	pFound->iIndexTree = 0;
	pFound->plbscsOwnerSession = pSession;
	for ( int i=1; i<pFound->pcOLList->NumElem(); i++ ) {
		pFound->UnloadOcList( pSession->plbsctTicket, i );
	}
	pFound->EnableOcList( pSession->plbsctTicket, 0 );
	if ( pFound->LB1.tcrHead.bBaseType == USER_BASE ) {
		// se for udb tem forcar a recriacao das acls, mas tudo bem que eh em memoria
		// tem bug aqui nesse caso
	}

	// falta tratar bases em mmodo exclusivo

	return pFound;
***/
}


BOOL LBSC_Session::ControlFileOK()
{
	if ( pControlFile ) {
		return TRUE;
	}

	pControlFile = new LBSC_ControlFile;
	if ( !pControlFile ) {
		return FALSE;
	}
	if ( !pControlFile->Init() ) {
		delete pControlFile;
		pControlFile = NULL;
		return FALSE;
	}

	return TRUE;
}
