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
// Module: SESSCL7.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif

#include	<process.h>

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#include <deffuncs.h>
#ifndef	_MBASELST_H_
#include	<MBaseLst.h>
#endif
extern "C" {
#include	<personcl.h>
}

////////////////////////////////////////////////
// para resolver feedback entre base e session
typedef	struct	_sThreadPar
{
	LBSC_Session	*pSession;
	LBSC_Base		*pBase;
} TThreadPar;
////////////////////////////////////////////////

#ifdef	_DEBUG_CRIT_SECT_

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

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

// nome da defudb
extern	char	_szDefUDBName[ MAXPATH ];

// controle de bases reservadas para manutencao
extern LBSC_MaintBasesList	*_pclMaintBaseList;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo CreateBase
	Cria uma base de dados.

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- szBaseName
		- szBasePassword
		- szMaintenancePassword
		- bBaseType
		- bIsCrypto
		- szUserBaseName
		- ptfField
		- iSlotNum
		- iCountNum
		- iMaxKeySize

	Return:
		LBS_OK se conseguir criar a base ou erro.

	Comments:
		- Se o endereco do servidor nao for passado, o LBS verifica se a
		  maquina em questao e servidora; se for, ela sera a servidora
		  dessa nova base; senao, o LBS faz um broadcast perguntando quem
		  sao os servidores e assume como servidor para a base a ser criada
		  o primeiro que responder;
		- A base fica pronta para uso.
		- Retorna erro se existir outra base com mesmo nome no servidor.
		- A base criada nao fica aberta.

***/
int
LBSC_Session::CreateBase( const LBSC_Ticket *plbscTicketPar, char *szBaseName, 
			char *szBaseLongName, 
			char *szBasePassword, char* szMaintenancePassword,
			BYTE bBaseType, BOOL bIsCrypto,
			char *szUserBaseName, TField *ptfField, int iSlotNum,
			int iCountNum, int iMaxKeySize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CreateBase") );
	char			szFullAux[ FULLNAMESIZE ];
	char			szAux[ FILENAMESIZE ];
	char			szUDBName[ FULLNAMESIZE ];
	BOOL			bUserBaseFound = FALSE;
	long			lBFilePos = -1;
	DWORD			dwUserBaseId = 0;
	char			*szMsg = NULL;				// para internacionalizacao de mensagens

#ifdef LBS_DEBUG
	Printf( "Estou em CreateBase." );
#endif // LBS_DEBUG

	C_SessCritSect	cCS4( this, CRITSECT4 );

	// entrar em uma regiao critica que bloqueie todo o processo
	// de criacao de base.
	C_SessCritSect	cCS5( this, CRITSECT5 );

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( 5 );	// 5 pontos fixos

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INITCREATE" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// incrementar o numero de slots, pois o LBS precisa de UM (o primeiro)
	iSlotNum++;

	if( szBaseName == NULL ){
		ERETURN( LBSE_ERROR );
	}
	strupr( szBaseName );

	if( strncmp( szBaseName, "\\", 1 ) == 0 ){
		// o nome da base comeca com '\\'
		ERETURN( LBSE_INVALIDNAME );
	}

	if( szBasePassword == NULL ){
		ERETURN( LBSE_ERROR );
	}
	strupr( szBasePassword );

	// se a aplicacao nao passou szUserBaseName ou passou vazia,
	// assumimos que ela quer usar a UDB default
	if( !szUserBaseName || ( szUserBaseName[ 0 ] == '\0' ) ){
		strcpy( szUDBName, _szDefUDBName );
	} else {
		strcpy( szUDBName, szUserBaseName );
	}
	strupr( szUDBName );

	// Acessar lbs.ini para pegar o arquivo de bases
	if( GetFNameOnProfile( szFullAux, szAux ) != LBS_OK ){
		ERETURN( LBSE_LBSINIERROR );
	}

	// criar o diretorio das bases, se ele nao existir
	MakeDir( szFullAux );

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CREATSEARCH" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if ( ptbfAux ){
		ERETURN( LBSE_DUPLICATEBASE );
	}
	if( bBaseType != USER_BASE && pControlFile->Get( szUDBName ) ){	// se bBaseType == USER_BASE, estamos criando uma BU
		bUserBaseFound = TRUE;
	}
	if( bBaseType != USER_BASE ){
		if( ! ( bUserBaseFound ) ){
			ERETURN( LBSE_USERBASENOTFOUND );
		}
		// Vamos abrir a BU para pegar o Id dela
		LBSC_Base	lbscbUserBase( plbsctTicket, szUDBName, this, FALSE );

		if( !lbscbUserBase.BaseObjOk() ){
			// Deu pau na abertura da BU
			ERETURN( LBSE_ERROR );
		}
		dwUserBaseId = lbscbUserBase.GetBaseId();

		// verificar se o usuario logado tem permissao para criar base
		// (o tipo NOP_USER indica que ele nao pode criar base)
		// lembrar que a UDB passada como parametro neste metodo
		// pode nao ser a UDB na qual o cara esta' logado.

		long lType = GetUserType( &lbscbUserBase, (char*) plbscuUser->GetUserName() );
		if( lType < 0 || lType == NOP_USER ){
			// deu pau ou o usuario nao tem permissao
			ERETURN( LBSE_INVALIDUSERTYPE );
		}
	}


	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CREATBASE" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Instanciar um novo objeto base
#ifdef LBS_DEBUG
	Printf( "CreateBase: Vou criar a base." );
#endif // LBS_DEBUG
	LBSC_Base lbscBase;
	int iRet = lbscBase.Create( plbsctTicket, szBaseName, szBasePassword, szMaintenancePassword,
			bBaseType, bIsCrypto, this,
			strcmp( szBaseName, _szDefUDBName ) == 0 ?
			NULL : szUDBName,
			ptfField, dwUserBaseId, iSlotNum, 
			iCountNum, iMaxKeySize );

	if( iRet!= LBS_OK ){
#ifdef LBS_DEBUG
		Printf( "CreateBase: Nao consegui criar a base." );
#endif // LBS_DEBUG
		ERETURN( iRet );
	}

#ifdef LBS_DEBUG
	Printf( "CreateBase: Criei a base." );
#endif // LBS_DEBUG

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deletar a base que foi criada.
		lbscBase.Delete();
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CADBASE" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Inserir a nova base no arquivo de bases
	TBasesFile	tbfAux;
	tbfAux.szBaseName = szBaseName;
	strupr( (char*) tbfAux.szBaseName );
	tbfAux.szBaseLongName = szBaseLongName;
	tbfAux.szUserBaseName = bBaseType == USER_BASE ? "" : szUDBName;
	strupr( (char*) tbfAux.szUserBaseName );
	tbfAux.bRecDeleted = FALSE;
	tbfAux.bBaseType = bBaseType;
	if ( !pControlFile->Insert( tbfAux ) ) {
		ERETURN( LBSE_ERROR );
	}

	// a base esta' criada. vamos adicionar informacoes do slot-0, que eh o slot
	// reservado para o proprio LBS.
	PutPrivateSlotInfo( szBaseName );

#ifdef LBS_DEBUG
	Printf( "CreateBase: Vou inserir a base nos campos especiais da UDB." );
#endif // LBS_DEBUG

	// inserir a nova base nos campos USERBASEACCESSBASES
	// e USERBASEACCESSTYPES da BU, no registro
	// correspondente ao usuario correntemente logado.
	PutBaseInUDB( szBaseName, bBaseType, (char*) szUDBName, (char*)plbscuUser->GetUserName() );

	/*******************************************************/
	// informacao de feedback
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPERATIONOK" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	ERETURN ( LBS_OK );
}


#ifdef __BORLANDC__
#pragma warn -par
#endif
/***
	PUBLIC
	Metodo OpenBase
	Abre uma base de dados ja existente para utilizacao.

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- szBaseName
		- szBasePassword
		- bExclusive
		- bReadOnly
		- bMaintenance
		- plbscReturnBase

	Return:
		Apontador para objeto LBSC_Base ou NULL

	Comments:
		- Se o usuario tentar abrir uma base que ja esta aberta em modo
		  exclusivo o metodo retorna NULL;
		- Se o usuario tentar abrir uma base em modo exclusivo e esta ja
		  estiver aberta o metodo tambem retorna NULL.

***/
int
LBSC_Session::OpenBase( const LBSC_Ticket *plbscTicketPar, char *szBaseName,
			char *szBasePassword, BOOL bExclusive, BOOL bReadOnly, 
			BOOL bMaintenance, LBSC_Base **plbscReturnBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::OpenBase") );
	LBSC_Base		*plbscbBase;
	int				iRet;
	char			*szMsg = NULL;				// para internacionalizacao de mensagens


	(*plbscReturnBase) = NULL;

	// regiao critica para a lista de bases reservadas
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( _pclMaintBaseList ){
		// verificar se a base esta' reservada para manutencao
		const char		*szUserLogged = GetUserName();
		LBSC_MaintBase	cMaintBaseAux( szBaseName, szUserLogged, NULL );

		if( _pclMaintBaseList->Find( &cMaintBaseAux, 0, TRUE ) ){
			// a base esta' reservada. vamos ver se eh para mim que ela
			// esta' reservada...
			if( !szUserLogged ){
				ERETURN( LBSE_BASERESERVED );
			}
			LBSC_MaintBase	*pMaintBase = _pclMaintBaseList->Current();

			if( pMaintBase && (stricmp( pMaintBase->strUserName, szUserLogged ) == 0) ){
				// eh pra mim mesmo. entao, deixa rolar...
			} else {
				// a base esta' reservada, mas nao eh pra mim. nao posso abrir a base.
				ERETURN( LBSE_BASERESERVED );
			}
		}
	}

	// regiao critica para o arquivo de controle
	C_SessCritSect	cCS4( this, CRITSECT4 );

	// entrar em uma regiao critica que bloqueie todo o processo
	// de abertura de base.
	C_SessCritSect	cCS5( this, CRITSECT5 );

	// $$$ Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	char	szFullAux[ FULLNAMESIZE ];
	char	szAux[ FILENAMESIZE ];
	// Acessar lbs.ini para pegar o arquivo de bases
	if( GetFNameOnProfile( szFullAux, szAux ) != LBS_OK ){
		ERETURN( LBSE_LBSINIERROR );
	}

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( 4 );	// 4 pontos fixos

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}

	/*******************************************************/

	// Abrir o arquivo de bases para verificar se a base existe.
	TBasesFile	tbfAux;
	BOOL		bFound = FALSE;

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if( !ptbfAux ){
		ERETURN( LBSE_BASENOTFOUND );
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}

	/*******************************************************/

	// Instanciar um objeto base
	plbscbBase = NewBaseHandler( plbsctTicket, szBaseName, (const char*) (char*) tbfAux.szBaseLongName, szBasePassword, this, bExclusive,
				    bReadOnly, bMaintenance );
	if( plbscbBase == NULL ){
		ERETURN( LBSE_NOMEMORY );
	}
	iRet = plbscbBase->LastError();
	if( ( plbscbBase->BaseObjOk() == FALSE ) && ( plbscbBase->BaseStruct() == TRUE ) ){	// $$$ Nao conseguiu abrir a base
		delete plbscbBase;
		(*plbscReturnBase) = NULL;
		ERETURN( iRet );
	}


	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// fechar a base, que ja' estava aberta.
		(*plbscReturnBase) = NULL;
		delete plbscbBase;
		ERETURN( LBSW_OPCANCEL );
	}

	/*******************************************************/

	if( plbscbBase->GetBaseType() != USER_BASE ){
		// Instanciar um objeto base de usuarios
		char		*szUserBaseNameAux = plbscbBase->GetUserBase();
		if( dwUserBaseId != plbscbBase->GetUserBaseId() ){
			(*plbscReturnBase) = NULL;
			delete plbscbBase;
			delete szUserBaseNameAux;
			ERETURN( LBSE_INVALIDUSERBASE );
		}
		// Procurar usuario
		((LBSC_Ticket *) plbscTicketPar)->Descriptografa();
		char	*szAux1 = (char*) (((LBSC_Ticket*) plbscTicketPar)->strUserName);
		char	*szAux2 = (char*) (((LBSC_Ticket*) plbscTicketPar)->strUserPassword);

		iRet = FindUser( szUserBaseNameAux, (const char*) szAux1,
				 (const char*) szAux2 );
		delete szUserBaseNameAux;

		((LBSC_Ticket *) plbscTicketPar)->Criptografa();
	} else {
		// setar as ACLS da UDB na porrada
		iRet = SetUDBACLs( plbscbBase );
	}
	if( iRet == LBS_OK ){
		// Inserir a base na lista de bases
		// (nao precisamos entrar em regiao critica porque
		// a lista ja' faz isso sozinha)
		lbscblBaseList.Add( plbscbBase, AFTER );

		// Retornar a base aberta
		(*plbscReturnBase) = plbscbBase;
		if( !plbscbBase->IndexSystemOk() ){
			if( plbscbBase->GetBaseVersion() < OCCTREE_MAGICNUMBER ){
				iRet = LBSW_OPENBUTNEEDREPROC;
			} else {
				iRet = LBSW_OPENNOIS;
			}
		}
	} else {
		(*plbscReturnBase) = NULL;
		delete plbscbBase;
	}
	ERETURN( iRet );
}
#ifdef __BORLANDC__
#pragma warn +par
#endif


/**********************************************************
// Function name	: LBSC_Session::NeedReprocOnConvert
// Description	    : 
// Return type		: BOOL 
// Argument         :  const LBSC_Ticket *pTicket
// Argument         : char *szBaseName
// Argument         : char *szBasePassword
**********************************************************/
BOOL LBSC_Session::NeedReprocOnConvert( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword )
{
	// VLAD: PEND 
	return( TRUE );
}


void TryUndoRenameV3Files( char *szBaseDir, char *szBaseName, BYTE bLB1MagicNum ) 
{
	if( bLB1MagicNum < PAGEFILE_MAGICNUMBER ){
		char	szAux[ FILENAMESIZE ];

		// detona o recem criado LB2
		sprintf( szAux, "%s\\%s%s", szBaseDir, szBaseName, SLOTFILEEXT );
		remove ( szAux );

		// vamos voltar o lb1 e lb4 para o estado original

		char	szAux1[ FILENAMESIZE ];
		char	szAux2[ FILENAMESIZE ];

		// lb1
		sprintf( szAux1, "%s\\%s%s", szBaseDir, szBaseName, CONTROLFILEEXT );
		sprintf( szAux2, "%s\\%s%s.bak", szBaseDir, szBaseName, CONTROLFILEEXT );
		remove( szAux1 );
		rename( szAux2, szAux1 );

		// lb4
		sprintf( szAux1, "%s\\%s%s", szBaseDir, szBaseName, REPETITIONFILEEXT );
		sprintf( szAux2, "%s\\%s%s.bak", szBaseDir, szBaseName, REPETITIONFILEEXT );
		remove( szAux1 );
		rename( szAux2, szAux1 );
	}
}

/**********************************************************
// Function name	: LBSC_Session::ConvertBase
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *pTicket
// Argument         : char *szBaseName
// Argument         : char *szBasePassword
**********************************************************/
int LBSC_Session::ConvertBase( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword )
{
	int		iRet;
	char	*szMsg;
	char	szTmpBasePath[ MAXPATH ];
	char	szBasesDir[ FULLNAMESIZE ];
	char	szBaseDir[ MAXPATH ];

	PRINTLOG( _clLBSLog, ("LBSC_Session::ConvertBase") );

	if( !szBaseName ){
		ERETURN( LBSE_BADARG );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( 4 );	// 4 pontos fixos para iniciar o processo... 

	// primeiro, reservar a base para manutencao, para que todo
	// o processo de conversao seja feito sem problemas

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INITCONV" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// regiao critica para a lista de bases reservadas
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// regiao critica para o arquivo de controle
	C_SessCritSect	cCS4( this, CRITSECT4 );

	char	szAux[ FILENAMESIZE ];

	// Acessar lbs.ini para pegar o arquivo de bases
	if( GetFNameOnProfile( szBasesDir, szAux ) != LBS_OK ){
		ERETURN( LBSE_LBSINIERROR );
	}
	sprintf( szBaseDir, "%s\\%s", szBasesDir, szBaseName );

	// Abrir o arquivo de bases para verificar se a base existe.
	TBasesFile	tbfAux;
	BOOL		bFound = FALSE;

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CREATSEARCH" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if( !ptbfAux ){
		ERETURN( LBSE_BASENOTFOUND );
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		char	szFullMsg[ 200 ];
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPENBASE" );
		if ( szMsg ) {
			sprintf( szFullMsg, "%s: %s", (char*)szBaseName, szMsg );
			IncStep( szFullMsg );
			delete szMsg;
		}
		else {
			IncStep( "" );
		}
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	char		szDrive[ MAXDRIVE ];
	char		szDir[ MAXDIR ];
	char		szExt[ MAXEXT ];
	char		szBaseNameAux[ MAXPATH ];
	fnsplit( szBaseName, szDrive, szDir, szBaseNameAux, szExt );
	// verifica as versoes das bases
	sprintf( szAux, "%s\\%s%s", (char*) szBaseDir, szBaseNameAux, CONTROLFILEEXT );
	if( !C_LB1::Exist( szAux ) ){
		ERETURN( LBSE_BASENOTFOUND );
	}
	C_LB1	lb1Aux;
	if( lb1Aux.Open( szAux, NULL, NULL, SH_DENYRW ) != OK ){
		ERETURN( LBSE_CANTOPENFILE );
	}
	TControlRecHead	LB1Head;
	BYTE bLB1MagicNum = 0;
	if ( lb1Aux.R_ReadHead( &LB1Head ) != OK ) {
		ERETURN( LBSE_CANTOPENFILE );
	}
	if ( lb1Aux.Seek( 0, SEEK_SET ) != OK ) {
		ERETURN( LBSE_CANTOPENFILE );
	}
	if ( lb1Aux.Read( &bLB1MagicNum, sizeof( bLB1MagicNum ) ) != OK ) {
		ERETURN( LBSE_CANTOPENFILE );
	}
	lb1Aux.Close();
	
	// agora vamos fazer alguns testes simples ...
	BOOL bVersaoBaseOK = (bLB1MagicNum == CURRENT_MAGICNUMBER);
	BOOL bVersaoUDBOK = TRUE;
	
	if ( LB1Head.bBaseType == USER_BASE ) {
		C_LB3	lb3Aux;
		sprintf( szAux, "%s\\%s%s", (char*) szBaseDir, (char*) szBaseNameAux, STRUCTFILEEXT );
		if( lb3Aux.Open( szAux, NULL, NULL, SH_DENYRW, lb1Aux.tcrHead.iSlotNum, lb1Aux.tcrHead.iCountNum ) != OK ){
			ERETURN( LBSE_CANTOPENFILE );
		}
		BYTE bLB3MagicNum = 0;
		if ( lb3Aux.Seek( 0, SEEK_SET ) != OK ) {
			ERETURN( LBSE_CANTOPENFILE );
		}
		if ( lb3Aux.Read( &bLB3MagicNum, sizeof( bLB1MagicNum ) ) != OK ) {
			ERETURN( LBSE_CANTOPENFILE );
		}
		bVersaoUDBOK = (bLB3MagicNum == CURRENT_UDBMAGICNUMBER);
	}

	if ( bVersaoBaseOK && bVersaoUDBOK ) {
		// nao precisamos converter
		
		/*******************************************************/
		// finalizar informacao de feedback
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPERATIONOK" );
			SetOpInfo( szMsg, 100.0 );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/

		ERETURN( LBS_OK );
	}

	if( bLB1MagicNum < CRYPTO_MAGICNUMBER ){
		// nao da' para converter por aqui. Essa conversao eh escrota
		// e precisa ser feita pelo ConvBase. A aplicacao deve usar o
		// ConvBase e nao o lbs.

		ERETURN( LBSE_OLDBASEVERSION );
	}

	if( bLB1MagicNum < OCCTREE_MAGICNUMBER ){
		// nao da' para converter por aqui. Tem que usar outra versao do lightbase

		ERETURN( LBSE_CONVERTWITHLB_V3 );
	}

	// tirar uma copia da base, para restaurar em caso de erro ou de o 
	// usuario cancelar a operacao de conversao

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_COPINGFILES" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	{
		// Procura um diretorio para trabalhar
		for( int iDirNum = 0 ; iDirNum < 9000;iDirNum++ ){
			sprintf( szTmpBasePath, "%s\\%d", szBasesDir, iDirNum );
			if( mkdir( szTmpBasePath ) == 0 ){
				strcat( szTmpBasePath, "\\" );
				strcat( szTmpBasePath, szBaseName );
				MakeDir( szTmpBasePath );
				break;
			}
		}
		if( iDirNum >= 9000 ){
			ERETURN( LBSE_ERROR );
		}

		// copiar os arquivos da base para o diretorio auxiliar
		if( CopyDir( szBaseDir, szTmpBasePath, TRUE ) != LBS_OK ){
			// nao conseguimos copiar os arquivos. vamos abandonar a
			// conversao, por seguranca

			// detona o que eventualmente ja foi copiado
			char *szBasePtr = strstr( szTmpBasePath, szBaseName);
			if ( szBasePtr ) {
				*szBasePtr = '\0';
				LBSC_Base::RemoveDir( szTmpBasePath, TRUE );
			}

			ERETURN( LBSE_FILEERROR );
		}

		// pronto. a base esta' copiada no diretorio szTmpBasePath
	}

	if( bLB1MagicNum < PAGEFILE_MAGICNUMBER ){
		// vamos renomear o lb1 e lb4 pra forcar a criacao no esquema novo

		// e renomear o gowords.lb pra servir de arquivo de configuração

		char	szAux1[ FILENAMESIZE ];
		char	szAux2[ FILENAMESIZE ];
		sprintf( szAux1, "%s\\%s%s", (char*) szBaseDir, (char*) szBaseNameAux, CONTROLFILEEXT );
		sprintf( szAux2, "%s\\%s%s.bak", (char*) szBaseDir, (char*) szBaseNameAux, CONTROLFILEEXT );
		rename( szAux1, szAux2 );

		// agora vamos recriar o lb1 com o header quase igual como estava (lembrar que a base esta vazia)
		C_LB1	lb1Aux;
		if( lb1Aux.Open( szAux1, NULL, NULL, SH_DENYRW ) != OK ){
			ERETURN( LBSE_CANTOPENFILE );
		}
		lb1Aux.bMagicNumber = bLB1MagicNum;
		lb1Aux.Seek( 0, SEEK_SET );
		lb1Aux.Write( &bLB1MagicNum, sizeof( bLB1MagicNum ) );

		LB1Head.lFirstRecActivePos = LB1Head.lLastRecPos = LB1Head.lLastRecActivePos = -1;
		LB1Head.lDeletedRecNum = 0;
		LB1Head.lNumRecords = 0;
		lb1Aux.R_WriteHead( &LB1Head );;

		// renomear lb4
		sprintf( szAux1, "%s\\%s%s", (char*) szBaseDir, (char*) szBaseNameAux, REPETITIONFILEEXT );
		sprintf( szAux2, "%s\\%s%s.bak", (char*) szBaseDir, (char*) szBaseNameAux, REPETITIONFILEEXT );
		rename( szAux1, szAux2 );

		// renomear gowords.lb
		sprintf( szAux1, "%s\\%s", (char*) szBaseDir, GOWORDSFILE );
		sprintf( szAux2, "%s\\%s%s", (char*) szBaseDir, (char*) szBaseNameAux, CONFFILEEXT );
		rename( szAux1, szAux2 );

		// setar informacoes do log de uso (extrair do lbs.ini e colocar no novo arquivo .conf)
		char szLogFieldAliasName[FIELDNAMESIZE+1];	
		char szExcludeModulesFromLog[FULLNAMESIZE+1];
		char szFieldsForUpdateLog[FULLNAMESIZE+1];	
		char szOperationLogMask[FULLNAMESIZE+1];	
		GetPrivateProfileString( szBaseNameAux, LOGUSE_FIELD_KEY, "", szLogFieldAliasName, FIELDNAMESIZE, LBSINIFILE );
		GetPrivateProfileString( szBaseNameAux, LOGUSE_EXCLUDE_MODULES_KEY, "", szExcludeModulesFromLog, FULLNAMESIZE, LBSINIFILE );
		GetPrivateProfileString( szBaseNameAux, LOGUSE_FIELDSFORUPDATELOG_KEY, "", szFieldsForUpdateLog, FULLNAMESIZE, LBSINIFILE );
		GetPrivateProfileString( szBaseNameAux, LOGUSE_OPERATIONS_KEY, "", szOperationLogMask, FULLNAMESIZE, LBSINIFILE );

		WritePrivateProfileString( LOGUSE_SECTION, LOGUSE_FIELD_KEY, szLogFieldAliasName, szAux2 );
		WritePrivateProfileString( LOGUSE_SECTION, LOGUSE_EXCLUDE_MODULES_KEY, szExcludeModulesFromLog, szAux2 );
		WritePrivateProfileString( LOGUSE_SECTION, LOGUSE_FIELDSFORUPDATELOG_KEY, szFieldsForUpdateLog, szAux2 );
		WritePrivateProfileString( LOGUSE_SECTION, LOGUSE_OPERATIONS_KEY, szOperationLogMask, szAux2 );
	}

	// abrir a base em modo exclusivo agora
	LBSC_Base *pBase = new LBSC_Base( pTicket, szBaseName, (const char*) (char*) tbfAux.szBaseLongName, szBasePassword, this, TRUE, FALSE, FALSE, FALSE );
	//////////////////////
	TThreadPar	tThreadPar;
	HANDLE		hThreadHandle = NULL;
	unsigned	uThreadId;

	tThreadPar.pSession = this;
	tThreadPar.pBase = pBase;
	BOOL	bReindex = FALSE;
	BOOL	bOnLineIndex = TRUE;

	if( !pBase ){
		iRet = LBSE_NOMEMORY;
		goto final;
	}
	iRet = pBase->LastError();
	if( !pBase->BaseObjOk() || !pBase->BaseStruct() ){	// Nao conseguiu abrir a base
		goto final;
	}

	if( bLB1MagicNum < PAGEFILE_MAGICNUMBER ){

		// vamos forcar a recriacao do sistema de indices
		pBase->RemoveIndexSystem();
		if ( !pBase->CreateIndexSystem() ) {
			iRet = pBase->LastError();
			if ( iRet != LBSE_TOOMANYOPENFILES ) {
				iRet = LBSE_NOMEMORY;
			}
			goto final;
		}

		// desligar a indexacao on-line da base para evitar
		// reconstrucoes dos indices varias vezes. No final
		// fazemos uma reindexacao total para deixar os indices ok.
		bOnLineIndex = pBase->OnLineIndexStatus();

		pBase->EnableOnLineIndex( FALSE );

		bReindex = TRUE;
	}

	ResetFeedbackInfo();

	// o feedback aqui eh feito dentro do metodo ConvertBaseTo
	iRet = ConvertBaseTo( pTicket, pBase, CURRENT_MAGICNUMBER );

	if( iRet == LBS_OK ){
		// atualizar a versao da base
		pBase->LB1.bMagicNumber = CURRENT_MAGICNUMBER;
		pBase->LB1.Seek( 0, SEEK_SET );
		pBase->LB1.Write( &pBase->LB1.bMagicNumber, sizeof( pBase->LB1.bMagicNumber ) );

		if( bReindex ){
			// reconstruir os indices da base

			if( !C_File::Is32s() ){
				// criar thread para obter feedback da classe LBSC_Base e repassar para LBSC_Session
				hThreadHandle = (HANDLE)_beginthreadex( NULL, 0, (unsigned (__stdcall *)(LPVOID)) ThreadFunc, &tThreadPar, 0, &uThreadId );
			}
			// sleep so' para dormir e o outro thread comecar.
			Sleep( 1 );

			pBase->EnableOnLineIndex( TRUE );
			iRet = pBase->IndexAll( pTicket, FALSE );
			while( iRet == LBSW_INDEXSTOPED ){
				iRet = pBase->IndexAll( pTicket, TRUE );
			}
			if( iRet == LBSE_NORECORD ){
				// nao ha' registros para indexar, mas isso
				// nao deve ser considerado erro.
				iRet = LBS_OK;
			}
			// restaurar o status de indexacao on-line
			pBase->EnableOnLineIndex( bOnLineIndex );
		}
		if ( !bVersaoUDBOK ) {
			iRet = ConvertUDBTo( pTicket, pBase, CURRENT_UDBMAGICNUMBER );
		}
	}

	if( hThreadHandle ){
		// cancelar a operacao para o thread morrer
		// (isso nao significa que o usuario cancelou)
		this->CancelOperation();
		WaitForSingleObject( hThreadHandle, INFINITE );
		CloseHandle( hThreadHandle );
		hThreadHandle = NULL;
	}

final:
	// fechar a base
	if ( pBase ) {
		pBase->InvalidateCache();
		delete pBase;
	}
	pBase = NULL;

	if( iRet != LBS_OK ){
		// deu pau ou o usuario cancelou a conversao.
		// vamos restaurar os arquivos da base, a partir da 
		// copia que fizemos antes
		TryUndoRenameV3Files( szBaseDir, szBaseNameAux, bLB1MagicNum );
		CopyDir( szTmpBasePath, szBaseDir, TRUE );
	}

	// a copia da base nao eh destruida por seguranca. se der alguma merda
	// pelo menos temos uma copia da base original

	if( iRet == LBS_OK ){
		/*******************************************************/
		// finalizar informacao de feedback
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPERATIONOK" );
			SetOpInfo( szMsg, 100.0 );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/
	}

	ERETURN( iRet );
}
	

/**********************************************************
// Function name	: LBSC_Session::ConvertBaseTo
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *pTicket
// Argument         : LBSC_Base *pBase
// Argument         : int iVersionTo
**********************************************************/
int LBSC_Session::ConvertBaseTo( const LBSC_Ticket *pTicket, LBSC_Base *pBase, int iVersionTo )
{
	int	iRet = LBS_OK;

	if( pBase->GetBaseVersion() >= iVersionTo ){
		// a versao da base ja' eh a versao desejada
		ERETURN( LBS_OK );
	}

	if ( pBase->GetBaseVersion() < SOUNDEX_MAGICNUMBER ){
		// essas conversoes requerem alteracao no minkeysize e uma reindexacao total. 
		int iCurMinKeySize = pBase->GetMinkeysize();
		pBase->SetMinkeysize( iCurMinKeySize + 1 );
	}

	if ( pBase->GetBaseVersion() < PAGEFILE_MAGICNUMBER ){

		// atualizar slots e regravar todos os registros

		// vamos reabrir os arquivos lb1 e lb4 antigos
		char szAux[ FILENAMESIZE ];
		char szBasePath[ FILENAMESIZE ];
		pBase->GetFullBaseName( szBasePath );
		
		sprintf( szAux, "%s\\%s%s.bak", (char*) pBase->szBasePath, (char*) pBase->szBaseName, CONTROLFILEEXT );
		C_LB1_V3	lb1V3;
 		if( lb1V3.Open( szAux, NULL, NULL, SH_DENYRW ) != OK ){
			ERETURN( LBSE_CANTOPENFILE );
		}
		if( lb1V3.tcrHead.bIsEncrypt ){
			lb1V3.R_SetRecKey( LBDEFKEY );
		}
		C_LB4	lb4Aux;
		sprintf( szAux, "%s\\%s%s.bak", (char*) pBase->szBasePath, (char*) pBase->szBaseName, REPETITIONFILEEXT );
		if( lb4Aux.Open( szAux, lb1V3.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, NULL, SH_DENYRW ) != OK ){
			ERETURN( LBSE_CANTOPENFILE );
		}

		// copia os slots de base
		for( int i=1; i <= pBase->LB1.tcrHead.iSlotNum; i++ ){
			if( pBase->GetSlotSize_V3( i, lb4Aux ) > 0 ){
				char	*szBuffer = new char [ pBase->GetSlotSize_V3( i, lb4Aux ) + 1 ];
				if( szBuffer ){
					if( pBase->GetSlot_V3( i, szBuffer, lb4Aux ) == LBS_OK ){
						pBase->PutSlot( i, szBuffer, pBase->GetSlotSize_V3( i, lb4Aux ) );
					}
					delete szBuffer;
				}
			}
		}

		// copia os slots de campo
		for( i=0; i < pBase->GetNumberOfFields(); i++ ){
			LBSC_Field	*pf = (*pBase)[ i ];
			if( pf && pBase->GetFieldSlotSize_V3( pf->GetId(), lb4Aux ) > 0 ){
				char	*szBuffer = new char [ pBase->GetFieldSlotSize_V3( pf->GetId(), lb4Aux ) + 1 ];
				if( szBuffer ){
					if( pBase->GetFieldSlot_V3( pf->GetId(), szBuffer, lb4Aux ) == LBS_OK ){
						pBase->PutFieldSlot( pf->GetId(), szBuffer, pBase->GetFieldSlotSize_V3( pf->GetId(), lb4Aux ) );
					}
					delete szBuffer;
				}
			}
		}
		pBase->FillFieldsFromSlotInfo();
		pBase->lbscrCurrRecord.SortFieldLists();

		// copia os registros de fato... 
		pBase->EnableFastRecord( TRUE );
		lb1V3.R_Seek( 0 );
		long lSize = lb1V3.R_FileSize();
		ResetFeedbackInfo();
		SetNumSteps( lSize );	// info de feedback: reprocessamento da base
		for ( i=0; i<lSize; i++ ) {
			if ( OperationCanceled() ) {
				// operacao foi cancelada a pedido do usuario.
				pBase->EnableFastRecord( FALSE );
				ERETURN( LBSW_OPCANCEL );
			}
			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				char	szFullMsg[ 200 ];
				char	*szMsg = NULL;

				szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCRECORDS" );
				sprintf( szFullMsg, "%s: %s %d/%d", (char*)pBase->szBaseName, szMsg, i+1, lSize );
				IncStep( szFullMsg );
				delete szMsg;
			} else {
				IncStep( "" );
			}
			if ( pBase->ReadRecord_V3( lb1V3, lb4Aux ) == LBS_OK ) {
				pBase->AppendRecord( pTicket );
			}
			lb1V3.R_SeekNext();
		}
		pBase->EnableFastRecord( FALSE );
		iRet = LBS_OK;

		// detonando os antigos arquivos lb1 e lb4
		lb1V3.Close();
		lb4Aux.Close();
		remove ( lb1V3.GetFileName() );
		remove ( lb4Aux.GetFileName() );

		// detonando o antigo arquivo de "standardizacao"; agora esse conteudo fica em memoria
		sprintf( szAux, "%s\\%s%s", (char*) pBase->szBasePath, (char*) pBase->szBaseName, STDFILEEXT );
		remove( szAux );
	}
	ERETURN( iRet );
}

/**********************************************************
// Function name	: LBSC_Session::ConvertUDBTo
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *pTicket
// Argument         : LBSC_Base *pBase
// Argument         : int iVersionTo
**********************************************************/
int LBSC_Session::ConvertUDBTo( const LBSC_Ticket *pTicket, LBSC_Base *pBase, int iVersionTo )
{
	int	iRet = LBS_OK;

	if( pBase->LB1.tcrHead.bBaseType != USER_BASE || 
				pBase->GetUDBVersion() >= iVersionTo ){
		// nao eh UDB ou a versao da base ja' eh a versao desejada
		ERETURN( LBS_OK );
	}
	pBase->SetFullAccessMode( TRUE );

	switch( iVersionTo ){
	case SEMARROBA_UDBMAGICNUMBER:
		// mudando os nomes de campos
		if ( pBase->ModifyFieldName( OLDUSERBASEACCESSTYPES, "", USERBASEACCESSTYPES ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEACCESSBASES, "", USERBASEACCESSBASES ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERUPDATEDATE, "", USERBASEUSERUPDATEDATE ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERCREATEDATE, "", USERBASEUSERCREATEDATE ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEGROUPLIST, "", USERBASEGROUPLIST ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERPHONE, "", USERBASEUSERPHONE ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERADDRESS, "", USERBASEUSERADDRESS ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERDESCRIPTION, "", USERBASEUSERDESCRIPTION ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERTYPE, "", USERBASEUSERTYPE ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERPASSWORD, "", USERBASEUSERPASSWORD ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->ModifyFieldName( OLDUSERBASEUSERNAME, "", USERBASEUSERNAME ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		break;

	case SECURITYFIELDS_UDBMAGICNUMBER:
		// converter para a versao imediatamente anterior
		iRet = ConvertUDBTo( pTicket, pBase, SEMARROBA_UDBMAGICNUMBER );
		if ( iRet != LBS_OK ) {
			break;
		}
		// criar os campos necessarios para as verificacoes de seguranca
		if ( pBase->AddField( pTicket, USERBASELOGINATTEMPTS, "Number of invalid login attempts", "PF12", VALUE_FIELD, 0, VALUETREE, 0 ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		if ( pBase->AddField( pTicket, USERBASEPASSWORDCHANGEDATE, "Last password change date", "PF13", DATE_FIELD, 0, DATETREE, 0 ) != LBS_OK ) {
			iRet = LBSE_ERROR;
			break;
		}
		break;

	default:
		iRet = LBSE_BADARG;
	}

	if( iRet == LBS_OK ){
		char	*szMsg;

		// atualizar a versao da UDB
		pBase->LB3.bMagicNumber = iVersionTo;
		pBase->LB3.Seek( 0, SEEK_SET );
		pBase->LB3.Write( &pBase->LB3.bMagicNumber, sizeof( pBase->LB3.bMagicNumber ) );

		/*******************************************************/
		// informacao de feedback
		if( OperationCanceled() ){
			// operacao foi cancelada a pedido do usuario.
			ERETURN( LBSW_OPCANCEL );
		}
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CONVERTINGBASE" );
			IncStep( szMsg );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/
	}

	ERETURN( iRet );
}


int LBSC_Session::SetUDBACLs( LBSC_Base *pBase )
{
	if ( pBase->LB1.tcrHead.bBaseType != USER_BASE ) {
		ERETURN( LBS_OK );
	}

	// limpar tudo primeiro...
	pBase->ClearAllAcls();

	LBSC_ACL		*plbscaACL=NULL;
	LBSC_Perm		*plbscpPerm=NULL;

	// tem status de administrador se ja for um, ou se for o dono da udb
	BOOL bAdmUser = ( plbscuUser->GetUserType() == MASTER_USER || 
			pBase->LB1.tcrHead.szOwnerName == plbscuUser->GetUserName() );
	// setar ACLS de base
	plbscaACL = new LBSC_ACL;
	if( !plbscaACL ){
		ERETURN( LBSE_NOMEMORY );
	}
	plbscaACL->szName = (char*) plbscuUser->GetUserName();
	pBase->lbscaBaseUserAcl.Add( plbscaACL, AFTER );
	plbscpPerm = new LBSC_Perm;
	if( !plbscpPerm ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( plbscpPerm ){
		plbscpPerm->lId = (long) ID_BASE;
		plbscpPerm->bPermission = ACL_READ;
		pBase->lbscaBaseUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
	}

	// setar ACLS de formularios
	plbscaACL = new LBSC_ACL;
	if( !plbscaACL ){
		ERETURN( LBSE_NOMEMORY );
	}
	plbscaACL->szName = (char*) plbscuUser->GetUserName();
	pBase->lbscaFormUserAcl.Add( plbscaACL, AFTER );
	plbscpPerm = new LBSC_Perm;
	if( !plbscpPerm ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( plbscpPerm ){
		plbscpPerm->lId = (long) ID_BASE;
		plbscpPerm->bPermission = bAdmUser ? ACL_ADM : ACL_READ;
		pBase->lbscaFormUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
	}

	// setar ACLS de relatorios
	plbscaACL = new LBSC_ACL;
	if( !plbscaACL ){
		ERETURN( LBSE_NOMEMORY );
	}
	plbscaACL->szName = (char*) plbscuUser->GetUserName();
	pBase->lbscaReportUserAcl.Add( plbscaACL, AFTER );
	plbscpPerm = new LBSC_Perm;
	if( !plbscpPerm ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( plbscpPerm ){
		plbscpPerm->lId = (long) ID_BASE;
		plbscpPerm->bPermission = bAdmUser ? ACL_ADM : ACL_READ;
		pBase->lbscaReportUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
	}

	// setar ACLS de campos
	plbscaACL = new LBSC_ACL;
	if( !plbscaACL ){
		ERETURN( LBSE_NOMEMORY );
	}
	plbscaACL->szName = (char*) plbscuUser->GetUserName();
	pBase->lbscaFieldUserAcl.Add( plbscaACL, AFTER );
	// alimenta a lista de ACL's por campo
	int	iNumFields = pBase->GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = pBase->lbscrCurrRecord[ i ];
		if( pf ){
			plbscpPerm = new LBSC_Perm;

			if( !plbscpPerm ){
				ERETURN( LBSE_NOMEMORY );
			}
			plbscpPerm->lId = (long) (pf->GetId());

			if ( stricmp( pf->GetAliasName(), USERBASEUSERNAME ) == 0 || 
				stricmp( pf->GetAliasName(), USERBASEUSERCREATEDATE ) == 0 || 
				stricmp( pf->GetAliasName(), USERBASEUSERTYPE ) == 0 ) {

				plbscpPerm->bPermission = ACL_READ;

			} else if ( stricmp( pf->GetAliasName(), USERBASEACCESSBASES ) == 0 || 
				stricmp( pf->GetAliasName(), USERBASEACCESSTYPES ) == 0 ||
				stricmp( pf->GetAliasName(), USERBASEUSERPASSWORD ) == 0 ) {

				plbscpPerm->bPermission = ACL_NONE;

			} else {

				plbscpPerm->bPermission = bAdmUser ? ACL_ADM : ACL_READ;

			}
			pBase->lbscaFieldUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
		}
	}

	ERETURN( LBS_OK );
}

