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
// Module: SESSCL19.CPP
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
#ifndef	_LOGLIST_H_
#include	<loglist.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
extern "C" {
#include	<personcl.h>
}
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif

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

extern	LBSC_LogList		*_clLoginList;	// lista contendo estruturas TNetInfo de todos
											// os logins efetuados. usada para controle
											// de licencas de clientes.

// nome da defudb
extern	char				_szDefUDBName[ MAXPATH ];

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	static PUBLIC
	Metodo KillSession
	Deleta todas as sessoes que estiverem abertas para um
	determinado cliente, em uma UDB

	Parameters:
		- szServerName	-> nome do servidor (nao interessa ao
						   LBS; e' usado apenas pelos stubs
						   de rede)
		- szClientName	-> nome da maquina cliente
		- szUserName	-> nome do usuario que esta' tentando
						   deletar as sessoes
		- szUserPasswd	-> password do usuario szUserName
		- szUDBName		-> nome da UDB. se for NULL, indica a
						   UDB default

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo
		  indicando erro.

	Comments:
		- 

***/
int
LBSC_Session::KillSession( char * /*szServerName*/, char *szClientName, char *szUserName, char *szUserPasswd, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::KillSession") );
	// verificar os parametros
	if( !szClientName || !szUserName || !szUserPasswd ){
		SetLastError( (DWORD) (LBSE_BADARG | 0x20000000) );
		return( LBSE_BADARG );
	}
	// instanciar um objeto LBSC_Session para poder utilizar
	// os metodos e estruturas necessarias
	LBSC_Session	*pSession = LBSC_Session::New();

	if( !pSession ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( LBSE_NOMEMORY );
	}
	// para abrir a UDB e fazer o FindUser eh necessario gerar um
	// ticket, mas o ticket de pSession eh NULL, porque nao fizemos login. 
	// Entao, vamos gerar um ticket para possibilitar  a execucao deste metodo.
	pSession->plbsctTicket = new LBSC_Ticket;	// nao interessa o conteudo

	if( !pSession->plbsctTicket ){
		// nao poderemos prosseguir sem essa informacao.
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( LBSE_NOMEMORY );
	}


	// verificar a validade das informacoes szUserName e szUserPasswd.
	// agora vamos abrir a UDB:
	{
		LBSC_Base	cbUDB( pSession->plbsctTicket, szUDBName ? szUDBName : _szDefUDBName, pSession );
		if( !cbUDB.BaseObjOk() ){
			// nao foi possivel abrir a UDB
			if( pSession->plbsctTicket ){
				delete pSession->plbsctTicket;
			}
			SetLastError( (DWORD) (LBSE_ERROR | 0x20000000) );
			return( LBSE_ERROR );
		}

			// Verificar a existencia do usuario e a validade da password
			int iRet = pSession->FindUser( &cbUDB, szUserName, szUserPasswd );
			if( iRet != LBS_OK ){
				// usuario nao encontrado ou senha invalida
				if( pSession->plbsctTicket ){
					delete pSession->plbsctTicket;
				}
				SetLastError( (DWORD) (iRet | 0x20000000) );
				return( iRet );
			}

		long lType = USUAL_USER;

			LBSC_Field	*pf = cbUDB[ USERBASEUSERTYPE ];
			LBSC_Data	*pd = pf ? (*pf)[ 0 ] : NULL;

			if( !pd ){
				if( pSession->plbsctTicket ){
					delete pSession->plbsctTicket;
				}
				SetLastError( (DWORD) (LBSE_BADUSERBASE | 0x20000000) );
				return( LBSE_BADUSERBASE );
			}
			lType = (long) (*pd);

		if( lType != MASTER_USER ){
			// o cara nao eh MASTER_USER
			if( pSession->plbsctTicket ){
				delete pSession->plbsctTicket;
			}
			SetLastError( (DWORD) (LBSE_INVALIDUSERTYPE | 0x20000000) );
			return( LBSE_INVALIDUSERTYPE );
		}
		// fechar a UDB (o final de escopo definido pelo "}" abaixo faz isso)
	}

	// varrer a lista de logins procurando ocorrencias do
	// cliente szClientName
	TNetInfo	tniPar( szUserName, szUserPasswd, szUDBName ? szUDBName : _szDefUDBName, "$", szClientName, "$" );
	TLoginInfo	tLogInfo( tniPar, pSession );
	_clLoginList->First();
	while( _clLoginList->Find( &tLogInfo, CMPCLIENTNAME, FALSE ) ){
		// achamos um elemento na lista que contem uma sessao do cliente indicado
		TLoginInfo		*pInfoToKill = _clLoginList->Current();
		if( pInfoToKill ){
			LBSC_Session	*pSessionToKill = pInfoToKill->pOwnerSession;
			if( pSessionToKill ){
				LBSC_Session::Delete( pSessionToKill );
			}
		}
		if( !_clLoginList->Next() ){
			break;
		}
	}
	tLogInfo.pOwnerSession = NULL;

	// deletar a sessao que foi instanciada aqui, neste metodo
	if( pSession->plbsctTicket ){
		delete pSession->plbsctTicket;
		pSession->plbsctTicket = NULL;
	}

	LBSC_Session::Delete( pSession );
	SetLastError( (DWORD) (LBS_OK | 0x20000000) );
	return( LBS_OK );
}

/***
	static PUBLIC
	Metodo GetSessions
	Obtem todas as sessoes que estiverem abertas para um
	determinado cliente, em uma UDB

	Parameters:
		- szServerName	-> nome do servidor (nao interessa ao
						   LBS; e' usado apenas pelos stubs
						   de rede)
		- szClientName	-> nome da maquina cliente
		- szUserName	-> nome do usuario que esta' tentando
						   deletar as sessoes
		- szUserPasswd	-> password do usuario szUserName
		- szUDBName		-> nome da UDB. Se for NULL indica a
						   UDB default

	Return:
		- vetor de apontadores para LBSC_Session, com um ponteiro NULL no final ou
		  NULL em caso de erro.

	Comments:
		- 

***/
LBSC_Session **
LBSC_Session::GetSessions( char * /*szServerName*/, char *szClientName, char *szUserName, char *szUserPasswd, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetSessions") );
	// verificar os parametros
	if( !szClientName || !szUserName || !szUserPasswd ){
		SetLastError( (DWORD) (LBSE_BADARG | 0x20000000) );
		return( NULL );
	}
	// instanciar um objeto LBSC_Session para poder utilizar
	// os metodos e estruturas necessarias
	LBSC_Session	*pSession = LBSC_Session::New();

	if( !pSession ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( NULL );
	}
	// para abrir a UDB e fazer o FindUser eh necessario gerar um
	// ticket, mas o ticket de pSession eh NULL, porque nao fizemos login. 
	// Entao, vamos gerar um ticket para possibilitar  a execucao deste metodo.
	pSession->plbsctTicket = new LBSC_Ticket;	// nao interessa o conteudo

	if( !pSession->plbsctTicket ){
		// nao poderemos prosseguir sem essa informacao.
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( NULL );
	}


	// verificar a validade das informacoes szUserName e szUserPasswd.
	// agora vamos abrir a UDB:
	{
		LBSC_Base	cbUDB( pSession->plbsctTicket, szUDBName ? szUDBName : _szDefUDBName, pSession );
		if( !cbUDB.BaseObjOk() ){
			// nao foi possivel abrir a UDB
			if( pSession->plbsctTicket ){
				delete pSession->plbsctTicket;
			}
			SetLastError( (DWORD) (LBSE_ERROR | 0x20000000) );
			return( NULL );
		}

			// Verificar a existencia do usuario e a validade da password
			int iRet = pSession->FindUser( &cbUDB, szUserName, szUserPasswd );
			if( iRet != LBS_OK ){
				// usuario nao encontrado ou senha invalida
				if( pSession->plbsctTicket ){
					delete pSession->plbsctTicket;
				}
				SetLastError( (DWORD) (iRet | 0x20000000) );
				return( NULL );
			}

		long lType= USUAL_USER;

			LBSC_Field	*pf = cbUDB[ USERBASEUSERTYPE ];
			LBSC_Data	*pd = pf ? (*pf)[ 0 ] : NULL;

			if( !pd ){
				if( pSession->plbsctTicket ){
					delete pSession->plbsctTicket;
				}
				SetLastError( (DWORD) (LBSE_BADUSERBASE | 0x20000000) );
				return( NULL );
			}
			lType = (long) (*pd);

		if( lType != MASTER_USER ){
			// o cara nao eh MASTER_USER
			if( pSession->plbsctTicket ){
				delete pSession->plbsctTicket;
			}
			SetLastError( (DWORD) (LBSE_INVALIDUSERTYPE | 0x20000000) );
			return( NULL );
		}
		// fechar a UDB (o final de escopo definido pelo "}" abaixo faz isso)
	}

	// varrer a lista de logins procurando ocorrencias do
	// cliente szClientName
	TNetInfo	tniPar( szUserName, szUserPasswd, szUDBName ? szUDBName : _szDefUDBName, "$", szClientName, "$" );
	TLoginInfo	tLogInfo( tniPar, pSession );

	int	iCount = 0;
	_clLoginList->First();
	while( _clLoginList->Find( &tLogInfo, CMPCLIENTNAME, FALSE ) ){
		// achamos um elemento na lista que contem uma sessao do cliente indicado
		TLoginInfo		*pInfoToKill = _clLoginList->Current();
		if( pInfoToKill ){
			LBSC_Session	*pSessionToKill = pInfoToKill->pOwnerSession;
			if( pSessionToKill ){
				iCount++;
			}
		}
		if( !_clLoginList->Next() ){
			break;
		}
	}
	LBSC_Session	**pVet = NULL;
	if( iCount ){
		// ok. achamos iCount sessoes. vamos alocar o vetor com uma posicao a mais
		// para colocar o NULL no final.
		pVet = new LBSC_Session * [ iCount + 1 ];
		if( !pVet ){
			// fudeu
			SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
			return( NULL );
		}
		int		i = 0;
		_clLoginList->First();
		while( _clLoginList->Find( &tLogInfo, CMPCLIENTNAME, FALSE ) ){
			// achamos um elemento na lista que contem uma sessao do cliente indicado
			TLoginInfo		*pInfoToKill = _clLoginList->Current();
			if( pInfoToKill ){
				LBSC_Session	*pSessionToKill = pInfoToKill->pOwnerSession;
				if( pSessionToKill ){
					pVet[ i++ ] = pSessionToKill;
				}
			}
			if( !_clLoginList->Next() ){
				break;
			}
		}
		pVet[ i ] = NULL;
	} else {
		// nao ha' sessoes
		SetLastError( (DWORD) (LBSE_NOOCCURRENCE | 0x20000000) );
		return( NULL );
	}
	tLogInfo.pOwnerSession = NULL;

	// deletar a sessao que foi instanciada aqui, neste metodo
	if( pSession->plbsctTicket ){
		delete pSession->plbsctTicket;
		pSession->plbsctTicket = NULL;
	}

	LBSC_Session::Delete( pSession );
	SetLastError( (DWORD) (LBS_OK | 0x20000000) );
	return( pVet );
}

/***
	PUBLIC
	Metodo KillServer
	Mata o servidor LBS.

	Parameters:
		- szServerName	-> nome do servidor

	Return:
		- 

	Comments:
		- Este metodo so' esta' implementado no stub cliente
		  do LBS. Na DLL do LBS mono ele existe apenas para
		  que a API mono seja igual aa API do cliente.

***/
void
LBSC_Session::KillServer( char * /* szServerName */)
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::KillServer") );
	return;
}



/***
	STATIC PUBLIC
	Metodo GetBaseLongName
	Obtem o nome longo de uma base a partir de seu alias name

	Parameters:
		- szServerName		-> nome do servidor (nao importa aqui,
							   so' importa para os stubs de rede)
		- szUDBName			-> nome da UDB onde o nome da base deve
							   ser procurado. se for NULL, DEFUDB sera'
							   assumido.
		- szBaseAliasName	-> alias_name da base

	Return:
		- copia do nome longo da base. a aplicacao DEVE deletar ou
		  NULL em caso de erro.

	Comments:
		- eh bom lembrar que a aplicacao DEVE deletar o retorno 
		  deste metodo.
***/
char *
LBSC_Session::GetBaseLongName( char * /*szServerName*/, char *szUDBName, char *szBaseAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetBaseLongName") );

	if( !szBaseAliasName ){
		SetLastError( (DWORD) (LBSE_BADARG | 0x20000000) );
		return( NULL );
	}
	if ( !ControlFileOK() ) {
		SetLastError( (DWORD) (LBSE_CONTROLFILENOTOK | 0x20000000) );
		return( NULL );
	}

	C_SessCritSect	cCS4( NULL, CRITSECT4 );

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseAliasName );
	if ( ptbfAux ) {
		// achamos a base
		SetLastError( LBS_OK | 0x20000000 );
		return( Strdup( ((TBasesFile *)ptbfAux)->szBaseLongName ) );
	}
	SetLastError( (DWORD) (LBSE_ERROR | 0x20000000) );
	return( NULL );
}


