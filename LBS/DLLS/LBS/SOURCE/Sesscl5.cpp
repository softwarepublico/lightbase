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
// Module: SESSCL5.CPP
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
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef	_GETNAME_H_
#include	<getname.h>
#endif
extern "C" {
#include	<personcl.h>
}


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


// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	static PUBLIC
	Metodo WhatServers
	Verifica quais sao os servidores disponiveis na rede

	Parameters:

	Return:
		Apontador para uma string contendo os enderecos das maquinas
		servidoras separados por um espaco em branco.

	Comments:
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo, retornando uma
		  copia do nome do servidor obtido atraves da funcao NetServerGetInfo ou
		  do LBS.INI ou "LOCALHOST".

***/
char *
LBSC_Session::WhatServers()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatServers") );
	char			szServerName[ SERVERNAMESIZE ];
	const	char	*szMachine = GetMachineName();

	if( szMachine ){
		strcpy( szServerName, szMachine );
	} else {
		// deu pau na funcao NetServerGetInfo.
		// vamos pegar o nome no LBS.INI. Se houver erro, o nome retornado
		// sera' "LOCALHOST"
		strncpy( szServerName, LBSC_ServerConfig::ServerName(), SERVERNAMESIZE-1 );
	}
	SetLastError( (DWORD) (LBS_OK | 0x20000000) );
	return( Strdup( szServerName ) );
}


/***
	PUBLIC
	Metodo WhatServersForUser
	Verifica quais sao os servidores disponiveis na rede para um determinado
	servidor.

	Parameters:
		- szUserName

	Return:
		Apontador para uma string contendo os enderecos das maquinas
		servidoras separados por um espaco em branco.

	Comments:
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo, retornando uma
		  copia do nome do servidor definido no LBS.INI ou "LOCALHOST".

***/
char *
LBSC_Session::WhatServersForUser( char * szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatServersForUser") );
	// ja' que responderemos por si' mesmo, vamos verificar todas as UDBs
	// para saber se o usuario szUserName possui algum acesso

	// vamos fazer o seguinte:
	//	. procurar, no arquivo de controle, todas as UDBs do servidor
	//	. para cada UDB encontrada, verificar se o usuario possui algum acesso
	//	. se for encontrado algum acesso, podemos encerrar as buscas e retornar OK
	//	. se terminarmos de procurar em todas as UDBs e nao encontrarmos nada,
	//	  retornamos NULL
	// fim

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	C_SessCritSect	cCS4( this, CRITSECT4 );

	// Procurar usuario (nao importa a password, 
	// so' importa se ele estah ou nao cadastrado)
	if( FindUserInCache( szUserName, NULL, "" ) >= 0 ){
		// encontramos o cadastro do cara em alguma UDB
		return( WhatServers() );
	}
	NRETURN( LBSE_USERNOTFOUND );
}



/***
	static PUBLIC
	Metodo WhatBases
	Verifica quais as bases disponiveis na rede.

	Parameters:
		- iFilterLevel -> um filtro indicando o que
					  nao deve ser retornado na lista.

	Return:
		Apontador para uma lista de quadruplas:
		[servidor, nome-da-base, tipo da base, nome da BU]
		indicando todas as bases disponiveis na rede.

	Comments:
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo.

***/
LBSC_AllBasesList *        // $$$ lista com: servidor + nome-da-base + nome-longo-da-base + tipo + BU
LBSC_Session::WhatBases( int iFilterLevel )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatBases") );
	LBSC_AllBasesList 	*plbscablAllBasesList;
	TAllBases		*palbAllBases;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetLastError( (DWORD) (LBSE_INVALIDLIC | 0x20000000) );
		return( NULL );
	}

	// Instanciar a lista
	plbscablAllBasesList = new LBSC_AllBasesList;
	if( !plbscablAllBasesList ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( NULL );
	}

	palbAllBases = new TAllBases;
	if( !palbAllBases ){
		delete plbscablAllBasesList;
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( NULL );
	}
	char	*szServer = WhatServers();
	palbAllBases->tmaServer = szServer;
	if( szServer ){
		delete szServer;
	}
	palbAllBases->plbscsblServerBasesList = WhatBasesOnServer( iFilterLevel, palbAllBases->tmaServer );
	if( !(palbAllBases->plbscsblServerBasesList) ){
		delete palbAllBases;
		palbAllBases = NULL;
	} else {
		plbscablAllBasesList->Add( palbAllBases, TAIL );
	}

	if( plbscablAllBasesList->NumElem() == 0 ){
		delete plbscablAllBasesList;
		plbscablAllBasesList = NULL;
	} else {
		plbscablAllBasesList->First();
	}
	SetLastError( LBS_OK | 0x20000000 );
	return( plbscablAllBasesList );
}


#ifdef __BORLANDC__
#pragma warn -par
#endif
/***
	static PUBLIC
	Metodo WhatBasesOnServer
	Verifica quais as bases disponiveis em um servidor.

	Parameters:
		- iFilterLevel -> um filtro indicando o que
					  nao deve ser retornado na lista.

		- tmaServer
		- szUDB			-> nome de uma UDB. Se for passado, o metodo retornara'
						   apenas as bases que estiverem vinculadas aa tal UDB; senao,
						   todas as bases de todas as UDBs serao retornadas.
		- szUser		-> nome do usuario. Se for passado, o metodo retornara' 
						   apenas as bases em cujas UDBs o usuario estiver cadastrado


	Return:
		Apontador para uma lista de triplas:
		[nome-da-base, nome longo da base, tipo da base, nome da BU]
		indicando todas as bases disponiveis no servidor.

	Comments:
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo.

***/
LBSC_ServerBasesList *
LBSC_Session::WhatBasesOnServer( int iFilterLevel, const char * /*tmaServer*/, char *szUDB, char *szUser )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatBasesOnServer") );
	char					szFullAux[ FULLNAMESIZE ];
	char					szAux[ FILENAMESIZE ];
	LBSC_ServerBasesList	*plbscsblServerBasesList;
	TServerBases			*ptsbServerBases;

	// O parametro tmaServer nao interessa para o LBS (so' interessa para o Stub Servidor)

	if ( !ControlFileOK() ) {
		SetLastError( (DWORD) (LBSE_CONTROLFILENOTOK | 0x20000000) );
		return( NULL );
	}
	int iUserType = NOP_USER;
	if ( szUser ) {
		int iPos = FindUserInCache( szUser, NULL, szUDB );
		if ( iPos >= 0 ) {
			iUserType = pUserCache[iPos].tUDBInfo.iType;
		}
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetLastError( (DWORD) (LBSE_INVALIDLIC | 0x20000000) );
		return( NULL );
	}

	plbscsblServerBasesList = new LBSC_ServerBasesList;
	if( !plbscsblServerBasesList ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( NULL );
	}

	C_SessCritSect	cCS4( NULL, CRITSECT4 );

	for ( int i=0; i<pControlFile->Size(); i++ ) {
		const TBasesFile *ptbfAux = pControlFile->Get( i );
		if( ptbfAux ){
			// filtrar
			if( iFilterLevel > 0 ){
				if( strchr( ((TBasesFile *)ptbfAux)->szBaseName, '\\' ) ){
					continue;
				}
			}

			if( !szUDB || (szUDB && (stricmp( szUDB, ((TBasesFile *)ptbfAux)->szUserBaseName ) == 0) && (ptbfAux->bBaseType != USER_BASE)) ){
				// Instanciar um no' da lista de bases do servidor
				ptsbServerBases = new TServerBases;
				if( !ptsbServerBases ){
					continue;
				}
				ptsbServerBases->SetBaseName( ((TBasesFile *)ptbfAux)->szBaseName );
				ptsbServerBases->SetBaseLongName( ((TBasesFile *)ptbfAux)->szBaseLongName );
				ptsbServerBases->SetBaseType( ((TBasesFile *)ptbfAux)->bBaseType );
				ptsbServerBases->SetUserBaseName( ((TBasesFile *)ptbfAux)->szUserBaseName );
				plbscsblServerBasesList->Add( ptsbServerBases, TAIL );
			}
		}
	}
	if ( szUDB && iUserType == MASTER_USER ) {	// incluir a UDB como base tambem...
		ptsbServerBases = new TServerBases;
		if( ptsbServerBases ){
			ptsbServerBases->SetBaseName( szUDB );
			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				char *szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_UDB" );
				ptsbServerBases->SetBaseLongName( szMsg );
				delete szMsg;
			} else {
				ptsbServerBases->SetBaseLongName( "UDB" );
			}
			ptsbServerBases->SetBaseType( USER_BASE );
			ptsbServerBases->SetUserBaseName( szUDB );
			plbscsblServerBasesList->Add( ptsbServerBases, TAIL );
		}
	}
	if( plbscsblServerBasesList->NumElem() == 0 ){
		delete plbscsblServerBasesList;
		plbscsblServerBasesList = NULL;
	} else {
		plbscsblServerBasesList->First();
	}
	SetLastError( LBS_OK | 0x20000000 );
	return( plbscsblServerBasesList );
}
#ifdef __BORLANDC__
#pragma warn +par
#endif

/***
	PUBLIC
	Metodo WhatBasesForUser
	Verifica quais as bases disponiveis na rede para um determinado usuario.

	Parameters:
		- iFilterLevel -> um filtro indicando o que
					  nao deve ser retornado na lista.

		- szUserName: se nao for informado assume-se o usuario que esta
				 logado.

	Return:
		- Apontador para uma lista de quadruplas:
		  [servidor, nome-da-base, nome longo da base, tipo da base, nome da BU]
		  indicando todas as bases disponiveis na rede para o usuario.

	Comments:
		- O usuario so pode usar este metodo para ele mesmo, a nao
		  ser que ele seja super usuario
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo.

***/
LBSC_AllBasesList *
LBSC_Session::WhatBasesForUser( int iFilterLevel, char *szUserName = NULL )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatBasesForUser") );
	LBSC_AllBasesList 	*plbscablAllBasesList;
	TAllBases		*palbAllBases;

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	// Checar se o usuario passado eh o mesmo que estah logado ou
	// se quem estah logado eh super usuario
	if( szUserName ){
		if( stricmp( szUserName, plbscuUser->GetUserName() ) != 0 ){
			if( plbscuUser->GetUserType() != MASTER_USER ){
				NRETURN( LBSE_USERNOTOWNERBASE );
			}
		}
	}

	// Instanciar a lista
	plbscablAllBasesList = new LBSC_AllBasesList;
	if( !plbscablAllBasesList ){
		NRETURN( LBSE_NOMEMORY );
	}
	palbAllBases = new TAllBases;	// Instanciar um no'
	if( !palbAllBases ){
		delete plbscablAllBasesList;
		NRETURN( LBSE_NOMEMORY );
	}
	char	*szServerName = WhatServers();
	palbAllBases->tmaServer = szServerName;
	if( szServerName ){
		delete szServerName;
	}
	palbAllBases->plbscsblServerBasesList = WhatBasesForUserOnServer( iFilterLevel, palbAllBases->tmaServer, szUserName );
	if( !(palbAllBases->plbscsblServerBasesList) ){
		delete palbAllBases;
		palbAllBases = NULL;
	} else {
		plbscablAllBasesList->Add( palbAllBases, TAIL );
	}
	if( plbscablAllBasesList->NumElem() == 0 ){
		delete plbscablAllBasesList;
		plbscablAllBasesList = NULL;
	} else {
		plbscablAllBasesList->First();
	}
	SetError( LBS_OK );
	return( plbscablAllBasesList );
}


/***
	PUBLIC
	Metodo WhatBasesForUserOnServer
	Verifica quais as bases disponiveis na rede para um determinado usuario
	em um determinado servidor.

	Parameters:
		- iFilterLevel -> um filtro indicando o que
					  nao deve ser retornado na lista.

		- szUserName: se nao for informado assume-se o usuario que esta
			      logado.
		- tmaServer

	Return:
		- Apontador para uma lista de triplas:
		  [nome-da-base, tipo da base, nome da BU]
		  indicando todas as bases disponiveis no servidor para o usuario.

	Comments:
		- O usuario so pode usar este metodo para ele mesmo, a nao
		  ser que ele seja super usuario
		- Este metodo devera' ser implementado no stub servidor de rede.
		- Aqui, o LBS responde apenas por si' mesmo.

***/
LBSC_ServerBasesList *
LBSC_Session::WhatBasesForUserOnServer( int iFilterLevel, const char * /*tmaServer*/, const char *szUserName = NULL )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatBasesForUserOnServer") );
	LBSC_ServerBasesList	*plbscsblServerBasesList;
	char					szUserNameAux[ USERNAMESIZE ];
	char					szFullAux[ FULLNAMESIZE ];
	char					szAux[ FILENAMESIZE ];
	char					szFNameAux[ FULLNAMESIZE ];
	TBasesFile				tbfAux;
	TServerBases			*ptsbServerBases;

	// O parametro tmaServer nao interessa para o LBS (so' interessa para o Stub Servidor)

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}
	if ( !ControlFileOK() ) {
		NRETURN( LBSE_CONTROLFILENOTOK );
	}

	// Verifica parametro
	if( szUserName == NULL ){
		strcpy( szUserNameAux, plbscuUser->GetUserName() );
	} else {
		strcpy( szUserNameAux, szUserName );
	}
	strupr( szUserNameAux );
	// $$$ Checar se o usuario passado eh o mesmo que estah logado ou
	// $$$ se quem estah logado eh super usuario
	if( stricmp( szUserNameAux, plbscuUser->GetUserName() ) != 0 ){
		if( plbscuUser->GetUserType() != MASTER_USER ){
			NRETURN( LBSE_USERNOTOWNERBASE );
		}
	}

	// o proximo loop faz o seguinte:
	// . varre o arquivo de controle
	// . para cada BU encontrada no arquivo de controle:
	//	. abre a BU
	//	. localiza o usuario dentro da BU
	//	. obtem todas as bases que o usuario tem acesso, atraves
	//	  do campo USERBASEACCESSBASES
	//	. preenche a lista
	//	. fecha a BU
	// . fim do loop

	C_SessCritSect	cCS4( this, CRITSECT4 );

	plbscsblServerBasesList = new LBSC_ServerBasesList;
	if( !plbscsblServerBasesList ){
		NRETURN( LBSE_NOMEMORY );
	}
	for ( int i=0; i<pControlFile->Size(); i++ ) {
		const TBasesFile *ptbfAux = pControlFile->Get( i );
		if( !ptbfAux ){
			continue;
		}
		if( ptbfAux->bBaseType != USER_BASE ){
			continue;
		}
		// abre a BU
		LBSC_Base	lbscbUserBase( plbsctTicket, ((TBasesFile *)ptbfAux)->szUserBaseName, this );
		if( !lbscbUserBase.BaseObjOk() ){
			// nao foi possivel abrir essa UDB
			continue;
		}

		// Procurar usuario (nao importa a password,
		// so' importa se ele estah ou nao cadastrado)
		int iRet = FindUser( &lbscbUserBase, szUserNameAux, "$$$" );
		if( ( iRet != LBS_OK ) && ( iRet != LBSE_INVALIDPASSWORD ) ){
			continue;
		}

		// obter todas as bases do campo USERBASEACCESSBASES do
		// registro corrente da BU e adicionar elementos na lista
		LBSC_Field	*pf = lbscbUserBase[ USERBASEACCESSBASES ];
		if( pf ){
			int iNumRep = pf->GetNumberOfRepetition();
			for( int i = 0; i < iNumRep; i++ ){
				LBSC_Field	*pf1 = lbscbUserBase[ USERBASEACCESSBASES ];
				LBSC_Field	*pf2 = lbscbUserBase[ USERBASEACCESSTYPES ];
				LBSC_Data	*pd1 = (*pf1)[ i ];
				LBSC_Data	*pd2 = (*pf2)[ i ];

				if( pf1 && pf2 && pd1 && pd2 ){
					// filtrar
					if( iFilterLevel > 0 ){
						if( strchr( ((TBasesFile *)ptbfAux)->szBaseName, '\\' ) ){
							continue;
						}
					}

					ptsbServerBases = new TServerBases;
					if( !ptsbServerBases ){
						// nao consegui alocar
						continue;
					}

					ptsbServerBases->SetBaseName( (char*) (*pd1) );
					ptsbServerBases->SetBaseLongName( ((TBasesFile *)ptbfAux)->szBaseLongName );
					ptsbServerBases->SetBaseType( (int) (long) (*pd2) );
					ptsbServerBases->SetUserBaseName( ((TBasesFile *)ptbfAux)->szUserBaseName );
					plbscsblServerBasesList->Add( ptsbServerBases, TAIL );
				}
			}
		}
	}
	if( plbscsblServerBasesList->NumElem() == 0 ){
		delete plbscsblServerBasesList;
		plbscsblServerBasesList = NULL;
	}
	SetError( LBS_OK );
	return( plbscsblServerBasesList );
}


