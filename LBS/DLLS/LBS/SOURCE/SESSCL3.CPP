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
// Module: SESSCL3.CPP
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
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
extern "C" {
#include	<personcl.h>
}

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo GetUsers
	Obtem a lista de todos os usuarios de uma UDB

	Parameters:
		- pTicket     -> ticket de seguranca
		- szUDBName   -> nome da UDB. Se for NULL, a UDB logada pela
						 sessao sera' utilizada.

	Return:
		- Uma string contendo os usuarios separados
		  por branco se correr tudo bem ou NULL em caso de erro.

	Comments:
		- A aplicacao DEVE deletar a string retornada quando nao
		  quiser mais usa-la.
		- Se a UDB nao possuir nenhum usuario cadastrado, o metodo
		  retornara' NULL, mas isso nao significa erro.
		- E' bom checar LastError para ter certeza da ocorrencia ou
		  nao de um erro.

***/
char *
LBSC_Session::GetUsers( const LBSC_Ticket *pTicket, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUsers") );
	int	iRet;
	char	*szReturn;

	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName ? szUDBName : (char*) strUDBLogged, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		NRETURN( LBSE_INVALIDUSERBASE );
	}
	if( bUserBase.GetNumActiveRecords( pTicket ) <= 0 ){
		// nao ha' usuarios. Retornar NULL, sem erro.
		SetError( LBS_OK );
		return( NULL );
	}
	int iSize = (bUserBase.GetNumActiveRecords( pTicket ) * (DEFAULT_MAXKEYSIZE+1)) + 1;
	szReturn = new char [ iSize ];
	if( !szReturn ){
		// erro
		NRETURN( LBSE_NOMEMORY );
	}
	char	*szBuffer = new char [ DEFAULT_MAXKEYSIZE + 1 ];
	if( !szBuffer ){
		delete szReturn;
		NRETURN( LBSE_NOMEMORY );
	}
	memset( szReturn, 0, iSize );
	memset( szBuffer, 0, DEFAULT_MAXKEYSIZE + 1 );

	if( !bUserBase.plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	iRet = bUserBase.plbscisIndexSystem->LT_GetFirstKey( WORDTREE, (char*) szBuffer );
	if( iRet != LBS_OK ){
		delete szReturn;
		delete szBuffer;
		NRETURN( LBSE_ERROR );
	}
	do{
		// so' devemos processar a chave corrente se ela for um
		// nome de usuario
		if( CheckFieldInCurrentKey( USERBASEUSERNAME, bUserBase ) ){
			strcat( szReturn, szBuffer );
			strcat( szReturn, " " );
			memset( szBuffer, 0, DEFAULT_MAXKEYSIZE + 1 );
		}
		iRet = bUserBase.plbscisIndexSystem->LT_GetNextKey( WORDTREE, (char*) szBuffer );
	} while( iRet == LBS_OK );
	delete szBuffer;
	SetError( LBS_OK );
	szReturn[ strlen( szReturn ) - 1 ] = '\0';
	return( szReturn );
}



/***
	PUBLIC 
	Metodo UpdateUserPassword
	Atualiza a password de um usuario, em uma UDB, sem precisar que ele esteja logado.

	Parameters:
		- szServer	-> servidor (necessario so pro stub)
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szOldPassword	-> password atual do usuario
		- szNewPassword	-> nova password do usuario

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Metodo estatico pra permitir a mudanca de senhas expiradas
		- Faz login na udb e chama o UpdateUserPassword de session

***/
int
LBSC_Session::UpdateUserPassword( char *szServer, char *szUDBName, char *szUserName, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserPassword2") );

	// tenta fazer um login pra validar o cara ou confirmar se a senha esta expirada
	TNetInfo	tni( szUserName, szOldPassword, szUDBName, NULL, NULL, NULL );
	const	LBSC_Ticket	*pTicket = Login( tni );
	int iRet = LastError();
	if( !pTicket && iRet != LBSE_PASSWORDEXPIRED ){
		// usuario invalido
		ERETURN( iRet );
	}
	if ( iRet == LBSE_PASSWORDEXPIRED ) {
		// vamos fazer um slogin
		pTicket = SLogin( tni );
	}
	iRet = LastError();
	if ( !pTicket ) {
		ERETURN( iRet );
	}

	// agora vai...
	iRet = UpdateUserPassword( pTicket, szUDBName, szUserName, szOldPassword, szNewPassword );
	Logout();
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo UpdateUserPassword
	Atualiza a password de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szOldPassword	-> password atual do usuario
		- szNewPassword	-> nova password do usuario

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- So' quem pode alterar a senha de um usuario sao: o proprio
		  usuario, o dono da UDB, ou um super-usuario.

***/
int
LBSC_Session::UpdateUserPassword( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserPassword") );

	BOOL	bMasterUser = FALSE;

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szNewPassword || !szUserName || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}
	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// o cara logado tem que ser o proprio usuario (neste caso,
	// informando a password antiga), o dono da UDB, ou um super-usuario
	if( bUserBase.LB1.tcrHead.szOwnerName == plbscuUser->GetUserName() ){
		bMasterUser = TRUE;
	} else {
		// o cara nao e' o dono da UDB
		// Vamos verificar se ele e' um super-usuario
		if( GetUserType( &bUserBase, (char*) plbscuUser->GetUserName() ) == MASTER_USER ){
			// o cara eh super usuario
			bMasterUser = TRUE;
		}
	}

	// procurar o usuario e sua password na UDB
	int iRet = FindUser( &bUserBase, szUserName, szOldPassword ? szOldPassword : "$" );
	if( iRet != LBS_OK ){
		if( iRet != LBSE_INVALIDPASSWORD ){
			ERETURN( iRet );
		}
		if( !bMasterUser ){
			// a password esta' errada e o cara NAO e' o dono da UDB nem
			// eh super-usuario
			ERETURN( iRet );
		}
		// a password esta' errada, mas o cara e' o dono da UDB ou eh super-usuario
	}
	char szPwd[PASSWORDSIZE + 1];
	bUserBase.GetFieldRepetition( USERBASEUSERPASSWORD, 0, szPwd );

	if ( InvalidPasswordFormat( szNewPassword ) ) {
		ERETURN( LBSE_INVALIDPASSWORDFORMAT );
	}

	if ( EqualsStoredPasswords( &bUserBase, szUserName, szNewPassword ) ) {
		ERETURN( LBSE_EQUALSSTOREDPASSWORDS );
	}

	if ( LBSC_ServerConfig::MaxStoredPasswords() > 0 ) {	
		// precisa guardar as senhas anteriores
		LBSC_Field *pf = bUserBase[ USERBASEUSERPASSWORD ];
		if ( pf ) {
			bUserBase.InsertBlankRepetition( pf->GetId(), 0 );
			if ( pf->GetNumberOfRepetition() > LBSC_ServerConfig::MaxStoredPasswords() ) {
				bUserBase.DelFieldRepetition( pf->GetId(), LBSC_ServerConfig::MaxStoredPasswords(), TRUE );
			}
		}

	}
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERPASSWORD, szNewPassword, 0 );
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERUPDATEDATE, C_Date(), 0 );	// data de hoje
	bUserBase.PutFieldRepetitionByIndex( USERBASELOGINATTEMPTS, (long)0, 0 );	// limpando o numero de tentativas invalidas de login
	bUserBase.PutFieldRepetitionByIndex( USERBASEPASSWORDCHANGEDATE, C_Date(), 0 );	// data de hoje

	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ChangeUserCachePwd( szUserName, szPwd, szUDBName, szNewPassword );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo UpdateUserType
	Atualiza o tipo de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- lNewType	-> novo tipo do usuario

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- So' quem pode fazer este tipo de alteracao sao o dono da UDB
		  e os super-usuarios (nem o proprio usuario podera' faze-la)

***/
int
LBSC_Session::UpdateUserType( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, long lNewType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserType") );

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( (lNewType < 0) || !szUserName || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// checar se o cara logado e' o dono da UDB
	if( bUserBase.LB1.tcrHead.szOwnerName != plbscuUser->GetUserName() ){
		// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
		if( GetUserType( &bUserBase, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara tambem nao eh super usuario
			ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		ERETURN( iRet );
	}
	char szPwd[PASSWORDSIZE + 1];
	bUserBase.GetFieldRepetition( USERBASEUSERPASSWORD, 0, szPwd );

	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERTYPE, lNewType, 0 );
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERUPDATEDATE, C_Date(), 0 );	// data de hoje

	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ChangeUserCacheType( szUserName, szPwd, szUDBName, lNewType );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetUserType
	Obtem o tipo de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario

	Return:
		- o tipo do usuario em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para consultar
		  os dados.

***/
long
LBSC_Session::GetUserType( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserType") );
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	BOOL bMustDelUDB = FALSE;
	BOOL bMustDelUser = FALSE;
	if ( !szUDBName ) {	// ta querendo a UDB default
		szUDBName = GetDefUserBaseName( NULL );
		bMustDelUDB = TRUE;
	}

	if( !szUserName ){	// podemos pegar o nome do usr no ticket
		LBSC_Ticket lbsctAuxTick = *((LBSC_Ticket *)pTicket);
		lbsctAuxTick.Descriptografa();
		szUserName = strdup((char *)lbsctAuxTick.strUserName);
		bMustDelUser = TRUE;
	}

	if ( stricmp( plbscuUser->GetUserName(), szUserName ) == 0 && 
			stricmp( strUDBLogged, szUDBName ) == 0 ) {
		// eh sobre o usuario logado...
		if ( bMustDelUDB ) {
			delete szUDBName;
			szUDBName = NULL;
		}
		if ( bMustDelUser ) {
			free (szUserName);
			szUserName = NULL;
		}
		return plbscuUser->GetUserType();
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );

	if ( bMustDelUDB ) {
		delete szUDBName;
		szUDBName = NULL;
	}

	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// obter o tipo do usuario
	return( GetUserType( &bUserBase, szUserName ) );
}


/***
	PUBLIC
	Metodo UpdateUserDescription
	Atualiza a descricao de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szNewDescrip	-> nova descricao do usuario

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- So' quem pode fazer este tipo de alteracao sao o dono da UDB
		  e os super-usuarios (nem o proprio usuario podera' faze-la)

***/
int
LBSC_Session::UpdateUserDescription( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewDescrip )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserDescription") );

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szNewDescrip || !szUserName || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// checar se o cara logado e' o dono da UDB
	if( bUserBase.LB1.tcrHead.szOwnerName != plbscuUser->GetUserName() ){
		// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
		if( GetUserType( &bUserBase, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara tambem nao eh super usuario
			ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		ERETURN( iRet );
	}
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERDESCRIPTION, szNewDescrip, 0 );
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERUPDATEDATE, C_Date(), 0 );	// data de hoje

	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo UpdateUserAddress
	Atualiza o endereco de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szNewAddr	-> novo endereco do usuario

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- So' quem pode fazer este tipo de alteracao sao o dono da UDB
		  e os super-usuarios (nem o proprio usuario podera' faze-la)

***/
int
LBSC_Session::UpdateUserAddress( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewAddr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserAddress") );

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szNewAddr || !szUserName || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// checar se o cara logado e' o dono da UDB
	if( bUserBase.LB1.tcrHead.szOwnerName != plbscuUser->GetUserName() ){
		// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
		if( GetUserType( &bUserBase, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara tambem nao eh super usuario
			ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		ERETURN( iRet );
	}
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERADDRESS, szNewAddr, 0 );
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERUPDATEDATE, C_Date(), 0 );	// data de hoje

	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ERETURN( LBS_OK );
}

//
//	Verifica se a nova senha eh valida de acordo com as validacaoes no servidor
//
BOOL				
LBSC_Session::InvalidPasswordFormat( char *szNewPassword )
{
	if ( LBSC_ServerConfig::MinUserPasswordSize() > 0) {
		if ( strlen(szNewPassword) < LBSC_ServerConfig::MinUserPasswordSize() ) {
			return TRUE;
		}
	}

	if ( !LBSC_ServerConfig::PasswordValidation() ) {
		return FALSE;
	}

	BOOL bTemAlfa = FALSE;
	BOOL bTemNum = FALSE;
	while ( *szNewPassword != '\0' ) {
		if ( isdigit(*szNewPassword) ) {
			bTemNum = TRUE;
		} else {
			bTemAlfa = TRUE;
		}
		++szNewPassword;
	}

	return !bTemAlfa || !bTemNum;
}


//
//	Verifica se a nova senha bate com as n senhas armazenadas
//
BOOL				
LBSC_Session::EqualsStoredPasswords( LBSC_Base *pUserBase, char *szUser, char *szNewPassword )
{
	if ( LBSC_ServerConfig::MaxStoredPasswords() <= 0 || pUserBase->GetBaseType() != USER_BASE ) {
		return FALSE;
	}

	char szName[USERNAMESIZE + 1];

	if ( pUserBase->GetFieldRepetition( USERBASEUSERNAME, 0, szName ) != LBS_OK ) {
		return FALSE;
	}

	if ( stricmp( szName, szUser ) != 0 ) {
		return FALSE;
	}

	for ( int i=0; i < pUserBase->GetNumberOfRepetition(USERBASEUSERPASSWORD) && 
				i < LBSC_ServerConfig::MaxStoredPasswords(); i++ ) {
		char szPwd[PASSWORDSIZE + 1];
		if ( pUserBase->GetFieldRepetition( USERBASEUSERPASSWORD, i, szPwd ) == LBS_OK ) {
			if ( stricmp(szNewPassword, szPwd) == 0 ) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

