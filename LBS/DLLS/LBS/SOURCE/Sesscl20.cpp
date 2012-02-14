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
// Module: SESSCL20.CPP
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

// nome da defudb
extern	char	_szDefUDBName[ MAXPATH ];

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo SetServerParam
	Seta parametros de rede. Usado apenas a nivel de stubs de rede
	e implementado de forma "dummy" aqui para manter a mesma API.

	Parameters:
		- pTicket
		- iProtocolo
		- iTimeout

	Return:
		- sempre LBS_OK (aqui no LBS).

	Comments:
		- 
***/
int
LBSC_Session::SetServerParam( const LBSC_Ticket * /*pTicket*/, int /*iProtocolo*/, int /*iTimeout*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::SetServerParam") );
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo GetReinstallPath
	Obtem o diretorio onde se encontram os binarios para uma reinstalacao
	automatica do cliente. Usado apenas pelos stubs de rede
	e implementado de forma "dummy" aqui para manter a mesma API.

	Parameters:

	Return:
		- sempre NULL (aqui no LBS).

	Comments:
		- 
***/
const char *
LBSC_Session::GetReinstallPath()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetReinstallPath") );
	return( NULL );
}



/***
	STATIC PUBLIC
	Metodo GetServerParam
	Obtem parametros de rede. Usado apenas a nivel de stubs de rede
	e implementado de forma "dummy" aqui para manter a mesma API.

	Parameters:
		- szServer
		- piProtocolo
		- piTimeout

	Return:
		- 

	Comments:
		- 
***/
void 
LBSC_Session::GetServerParam( char * /*szServer*/, int * /*piProtocolo*/ , int * /*piTimeout*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetServerParam") );
	return;
}


/***
	STATIC PUBLIC
	Metodo SetClientParam
	Seta parametros de rede para cliente. Usado apenas a nivel de 
	stubs de rede e implementado de forma "dummy" aqui para 
	manter a mesma API.

	Parameters:
		- iProtocolo
		- iTimeout
		- szServersNames

	Return:
		- sempre LBS_OK (aqui no LBS).

	Comments:
		- 
***/
int
LBSC_Session::SetClientParam( int /*iProtocolo*/, int /*iTimeout*/, 
				int /*iPorta*/, int /*iPorta32s*/, 
							  char ** /*szServersNames*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::SetClientParam") );
	return( LBS_OK );
}

/***
	STATIC PUBLIC
	Metodo GetClientParam
	Obtem parametros de rede para cliente. Usado apenas a nivel de 
	stubs de rede e implementado de forma "dummy" aqui para 
	manter a mesma API.

	Parameters:
		- piProtocolo
		- piTimeout
		- szServersNames

	Return:
		- 

	Comments:
		- 
***/
void
LBSC_Session::GetClientParam( int * /*piProtocolo*/, int * /*piTimeout*/, 
				int * /*iPorta*/, int * /*iPorta32s*/, 
					char *** /*szServersNames*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetClientParam") );
	return;
}


/***
	PUBLIC
	Metodo UnLockRecord
	Destrava um registro de uma base especifica.

	Parameters:
		- pTicketPar	-> ticket de seguranca.
		- lBaseId		-> identificador da base

	Return:
		- LBS_OK ou erro.

	Comments:
		- 

***/
int
LBSC_Session::UnLockRecord( const LBSC_Ticket *pTicketPar, long lBaseId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::UnLockRecord") );
	// o lBaseId na verdade eh o ponteiro da base, a nivel LBS.
	// basta fazermos o cast para LBSC_Base* e tudo vai dar certo.
	LBSC_Base *pBase = (LBSC_Base *) lBaseId;

	if( !pTicketPar || !pBase ){
		ERETURN( LBSE_BADARG );
	}
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !pBase->plbscsOwnerSession ){
		ERETURN( LBSE_ERROR );
	}
	int iRet = pBase->ReleaseRecord( pBase->plbscsOwnerSession->plbsctTicket );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo KillSessions
	Detona todas as sessoes abertas por uma aplicacao. So' eh' implementado
	a nivel dos stubs de rede. Aqui este metodo eh "dummy".

	Parameters:
		- 

	Return:
		- LBS_OK ou erro.

	Comments:
		- 
***/
int
LBSC_Session::KillSessions( const LBSC_Ticket *, char *, char *, long, long )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::KillSessions") );
	return( LBS_OK );
}

/***
	PUBLIC
	Metodo KillServer
	Detona o servidor. So' eh' implementado
	a nivel dos stubs de rede. Aqui este metodo eh "dummy".

	Parameters:
		- 

	Return:
		- LBS_OK ou erro.

	Comments:
		- 
***/
int
LBSC_Session::KillServer( const LBSC_Ticket *, char * )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::KillServer") );
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo IsUDBOwner
	Verifica se o cara que esta' logado eh o dono de uma dada UDB.

	Parameters:
		- pTicketPar	-> ticket de seguranca
		- szUDB			-> nome da UDB. Se for NULL, indica a UDB default.

	Return:
		- LBS_OK ou erro.

	Comments:
		- 
***/
BOOL
LBSC_Session::IsUDBOwner( const LBSC_Ticket *pTicketPar, char *szUDB )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IsUDBOwner") );
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		SetError( LBSE_USERNOTLOGGED );
		return( FALSE );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicketPar ) != 0 ){
		SetError( LBSE_TICKETNOTOK );
		return( FALSE );
	}

	const char	*szOwnerName = NULL;

	// vamos abrir a UDB
	{
		LBSC_Base	bUDB( pTicketPar, szUDB ? szUDB : _szDefUDBName, this );
		if( bUDB.BaseObjOk() == FALSE ){ // Nao consegui abrir a UDB
			SetError( LBSE_INVALIDUSERBASE );
			return( FALSE );
		}

		// agora vamos obter o nome do dono da UDB
		szOwnerName = bUDB.GetConstOwnerName();
		if( !szOwnerName ){
			// deu pau.
			SetError( LBSE_ERROR );
			return( FALSE );
		}
	}

	// comparar o nome obtido com o nome do usuario que esta'
	// logado.
	char *szLoggedUser = (char*) plbscuUser->GetUserName();

	if( stricmp( szLoggedUser, szOwnerName ) == 0 ){
		// ok. o usuario logado eh o dono da UDB.
		SetError( LBS_OK );
		return( TRUE );
	}
	// o cara nao eh o dono da UDB
	SetError( LBS_OK );
	return( FALSE );
}

