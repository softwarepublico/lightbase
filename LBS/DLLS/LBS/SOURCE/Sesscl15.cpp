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
// Module: SESSCL15.CPP
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

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif
extern "C" {
#include	<personcl.h>
}

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo UpdateUserPhone
	Atualiza o telefone de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szNewPhone	-> novo endereco do usuario

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
LBSC_Session::UpdateUserPhone( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewPhone )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UpdateUserPhone") );

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
	if( !szNewPhone || !szUserName || !szUDBName ){
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
	bUserBase.PutFieldRepetitionByIndex( USERBASEUSERPHONE, szNewPhone, 0 );
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
	Metodo GetUserDescription
	Obtem a descricao de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario

	Return:
		- a descricao do usuario em caso de sucesso ou NULL.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para consultar
		  os dados.
		- Este metodo retorna uma copia da informacao obtida. A aplicacao
		  DEVE deleta-la depois do uso.

***/
char *
LBSC_Session::GetUserDescription( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserDescription") );

	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( !szUserName || !szUDBName ){
		NRETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		NRETURN( LBSE_INVALIDUSERBASE );
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		NRETURN( iRet );
	}
	LBSC_Field	*pf = bUserBase[ USERBASEUSERDESCRIPTION ];
	if( !pf ){
		NRETURN( LBSE_BADUSERBASE );
	}
	LBSC_Data	*pd = (*pf)[ 0 ];
	char *szAux = pd ? (char*) (*pd) : NULL;
	char *szDescrip = szAux ? Strdup( szAux ) : NULL;
	SetError( LBS_OK );
	return( szDescrip );
}


/***
	PUBLIC
	Metodo GetUserAddress
	Obtem o endereco de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario

	Return:
		- o endereco do usuario em caso de sucesso ou NULL.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para consultar
		  os dados.
		- Este metodo retorna uma copia da informacao obtida. A aplicacao
		  DEVE deleta-la depois do uso.

***/
char *
LBSC_Session::GetUserAddress( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserAddress") );

	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( !szUserName || !szUDBName ){
		NRETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		NRETURN( LBSE_INVALIDUSERBASE );
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		NRETURN( iRet );
	}
	LBSC_Field	*pf = bUserBase[ USERBASEUSERADDRESS ];
	if( !pf ){
		NRETURN( LBSE_BADUSERBASE );
	}
	LBSC_Data	*pd = (*pf)[ 0 ];
	char *szAux = pd ? (char*) (*pd) : NULL;
	char *szAddress = szAux ? Strdup( szAux ) : NULL;
	SetError( LBS_OK );
	return( szAddress );
}


/***
	PUBLIC
	Metodo GetUserPhone
	Obtem o telefone de um usuario, em uma UDB.

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario

	Return:
		- o telefone do usuario em caso de sucesso ou NULL.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para consultar
		  os dados.
		- Este metodo retorna uma copia da informacao obtida. A aplicacao
		  DEVE deleta-la depois do uso.

***/
char *
LBSC_Session::GetUserPhone( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserPhone") );

	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( !szUserName || !szUDBName ){
		NRETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		NRETURN( LBSE_INVALIDUSERBASE );
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( &bUserBase, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		NRETURN( iRet );
	}
	LBSC_Field	*pf = bUserBase[ USERBASEUSERPHONE ];
	if( !pf ){
		NRETURN( LBSE_BADUSERBASE );
	}
	LBSC_Data	*pd = (*pf)[ 0 ];
	char *szAux = pd ? (char*) (*pd) : NULL;
	char *szPhone = szAux ? Strdup( szAux ) : NULL;
	SetError( LBS_OK );
	return( szPhone );
}



/***
	PUBLIC
	Metodo AddGroupToUser
	Adiciona grupos a um usuario em uma UDB

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szGroups	-> string contendo os novos grupos
				   separados por um espaco em branco.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- Somente o dono da UDB e os super-usuarios podem usar este metodo.

***/
int
LBSC_Session::AddGroupToUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szGroups )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::AddGroupToUser") );

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szGroups || !szUserName || !szUDBName ){
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

	LBSC_Field	*pf = bUserBase[ USERBASEGROUPLIST ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	C_StrTok	cStrTok;
	char		*szToken = cStrTok.StrTok( szGroups, " " );
	while( szToken ){
		(*pf) << strupr( szToken );
		szToken = cStrTok.StrTok( NULL, " " );
	}
	pf = bUserBase[ USERBASEUSERUPDATEDATE ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	(*pf) = C_Date();	// data de hoje
	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DelGroupFromUser
	Deleta grupos de um usuario em uma UDB

	Parameters:
		- pTicket	-> ticket de seguranca
		- szUDBName	-> nome da UDB
		- szUserName	-> nome do usuario
		- szGroups	-> string contendo os grupos
				   separados por um espaco em branco.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados.
		- Somente o dono da UDB e os super-usuarios podem usar este metodo.

***/
int
LBSC_Session::DelGroupFromUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szGroups )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DelGroupFromUser") );

	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szGroups || !szUserName || !szUDBName ){
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

	C_StrTok	cStrTok;
	char		*szToken = cStrTok.StrTok( szGroups, " " );
	while( szToken ){
		int iRep = bUserBase.GetFieldRepetitionByVal( USERBASEGROUPLIST, strupr( szToken ), TRUE );
		if( iRep >= 0 ){
			bUserBase.DelFieldRepetition( USERBASEGROUPLIST, iRep );
		}
		szToken = cStrTok.StrTok( NULL, " " );
	}
	LBSC_Field	*pf = bUserBase[ USERBASEUSERUPDATEDATE ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	(*pf) = C_Date();	// data de hoje
	if( bUserBase.LockRecord( pTicket ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	bUserBase.UpdateRecord( pTicket );
	bUserBase.ReleaseRecord( pTicket );
	ERETURN( LBS_OK );
}
