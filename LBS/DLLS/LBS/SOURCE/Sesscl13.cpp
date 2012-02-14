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
// Module: SESSCL13.H
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
extern "C" {
#include	<personcl.h>
}

#define LBW_PARSER_ONEKBYTE			1024

EXTLOG( _clLBSLog );	// objeto para geracao de log

char* 
LBSC_Session::getAppDrive( char *szDrive )
{
	char szPath[ LBW_PARSER_ONEKBYTE ];
	if( szPath ){
		HMODULE  hMod = GetModuleHandle( NULL ); 
		if( hMod ) {			
			*szPath = '\0';
			GetModuleFileName( hMod, szPath, LBW_PARSER_ONEKBYTE );
			if( *szPath ) {
				char * aux;
				_splitpath( szPath, szDrive, NULL, NULL, NULL );
				return szDrive;
			}
		}
	}
	return NULL;
}

/***
	PRIVATE
	Metodo GetFNameOnProfile
	Obtem informacoes do LBS.INI.

	Parameters:
		- szFullAux
		- szAux

	Return:
		- LBS_OK caso obtenha sucesso.

	Comments:

***/
int
LBSC_Session::GetFNameOnProfile( char *szFullAux, char *szAux )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetFNameOnProfile") );
	strncpy( szFullAux, LBSC_ServerConfig::DirBase(), FULLNAMESIZE-1 );
	strncpy( szAux, LBSC_ServerConfig::BasesFileName(), FILENAMESIZE-1 );

	// testa se o caminho tem o drive!!!
	char szDrive[ _MAX_DRIVE ];
	_splitpath ( szFullAux, szDrive, NULL, NULL, NULL );
	if ( (szFullAux[0] != '\\' || szFullAux[1] != '\\') && strlen( szDrive ) == 0 ){
		// tenta descobrir o drive somente se estiver relativo ao drive onde estamos rodando
		getAppDrive( szDrive );
		char * szAux = strdup ( szFullAux );
		if ( szAux ){
			sprintf( szFullAux, "%s%s", szDrive, szAux );
			free ( szAux );
		}
	}
	if( ( strcmp( LBSINIDEFMSG, szFullAux ) == 0 ) ||
	    ( strcmp( LBSINIDEFMSG, szAux ) == 0 ) ){
		// $$$ deu pau (nao achei a string em LBS.INI)
		SetLastError( (DWORD) (LBSE_LBSINIERROR | 0x20000000) );
		return( LBSE_LBSINIERROR );
	}
	SetLastError( LBS_OK | 0x20000000 );
	return( LBS_OK );
}

/***
	PRIVATE
	PutBaseInUDB
	Insere um nome de base em um registro de uma BU. O registro
	corresponde ao nome de um usuario.

	Parameters:
		- szBaseName	 -> nome da base a ser inserida
		- bBaseType	 -> tipo da base a ser inserida
		- szUserBaseName -> nome da BU
		- szUserName	 -> nome do usuario

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:

***/
int
LBSC_Session::PutBaseInUDB( char *szBaseName, BYTE bBaseType, char *szUserBaseName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::PutBaseInUDB") );
	if( !szBaseName || !szUserBaseName || !szUserName ){
		ERETURN( LBSE_BADARG );
	}
	if( szBaseName[ 0 ] == '\0' || szUserBaseName[ 0 ] == '\0' ){
		ERETURN( LBSE_BADARG );
	}
	strupr( szBaseName );
	strupr( szUserBaseName );
	strupr( szUserName );

	// abrir a BU
#ifdef LBS_DEBUG
	Printf( "PutBaseInUDB: Vou abrir a UDB." );
#endif // LBS_DEBUG
	LBSC_Base	lbscbUserBase( plbsctTicket, szUserBaseName, this, FALSE, FALSE );
	if( lbscbUserBase.BaseObjOk() == FALSE ){	// $$$ Nao conseguiu abrir a BU
#ifdef LBS_DEBUG
		Printf( "PutBaseInUDB: Nao consegui abrir a UDB." );
#endif // LBS_DEBUG
		ERETURN( LBSE_UBNOTOK );
	}
#ifdef LBS_DEBUG
	Printf( "PutBaseInUDB: UDB aberta com sucesso." );
#endif // LBS_DEBUG
	if( lbscbUserBase.GetBaseType() != USER_BASE ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// procura o usuario szUserName
	// (nao importa a password, so importa se ele estah ou nao cadastrado)
	int iRet = FindUser( &lbscbUserBase, szUserName, "$$$" );
	if( ( iRet != LBS_OK ) && ( iRet != LBSE_INVALIDPASSWORD ) ){
		// $$$ O usuario NAO estah cadastrado para a base
#ifdef LBS_DEBUG
		Printf( "PutBaseInUDB: Usuario nao cadastrado." );
#endif // LBS_DEBUG
		ERETURN( LBSE_USERNOTFOUND );
	}
	if( lbscbUserBase.GetFieldRepetitionByVal( USERBASEACCESSBASES, szBaseName ) >= 0 ){
		// a base szBaseName ja' esta' cadastrada na
		// UDB szUserBaseName, para o usuario szUserName
#ifdef LBS_DEBUG
		Printf( "PutBaseInUDB: A base ja existe nesta UDB." );
#endif // LBS_DEBUG
		ERETURN( LBS_OK );
	}
	iRet = lbscbUserBase.PutFieldRepetition( USERBASEACCESSBASES, szBaseName );
	if( iRet == LBS_OK ){
		iRet = lbscbUserBase.PutFieldRepetition( USERBASEACCESSTYPES, (long) bBaseType );
		if( iRet == LBS_OK ){
			if( (iRet = lbscbUserBase.LockRecord( plbsctTicket )) == LBS_OK ){
				iRet = lbscbUserBase.UpdateRecord( plbsctTicket );
				lbscbUserBase.ReleaseRecord( plbsctTicket );
			}
		}
	}
#ifdef LBS_DEBUG
	Printf( "PutBaseInUDB: Vou retornar %d.", iRet );
#endif // LBS_DEBUG
	ERETURN( iRet );
}



/***
	PRIVATE
	DelBaseOfUDB
	Remove um nome de base em um registro (ou de todos)
	de uma BU. O registro corresponde ao nome de um usuario.

	Parameters:
		- szBaseName	 -> nome da base a ser inserida
		- szUserBaseName -> nome da BU
		- szUserName	 -> nome do usuario. Pode ser NULL para
				    indicar TODOS OS USUARIOS.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:

***/
int
LBSC_Session::DelBaseOfUDB( char *szBaseName, char *szUserBaseName, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DelBaseOfUDB") );
	if( !szBaseName || !szUserBaseName ){
		ERETURN( LBSE_BADARG );
	}
//	if( szBaseName[ 0 ] == '\0' || szUserBaseName[ 0 ] == '\0' ){
	if( ( strcmp( szBaseName, "" ) == 0 ) || ( strcmp( szUserBaseName, "" ) == 0 ) ){
		ERETURN( LBSE_BADARG );
	}
	strupr( szBaseName );
	strupr( szUserBaseName );
	if( szUserName ){
		strupr( szUserName );
	}

	// abrir a BU
	LBSC_Base	lbscbUserBase( plbsctTicket, szUserBaseName, this, FALSE, FALSE );
	if( lbscbUserBase.BaseObjOk() == FALSE ){	// $$$ Nao conseguiu abrir a BU
		ERETURN( LBSE_UBNOTOK );
	}
	if( lbscbUserBase.GetBaseType() != USER_BASE ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	int iRet = LBS_OK;
	if( szUserName ){
		// procura o usuario szUserName
		// (nao importa a password, so importa se ele estah ou nao cadastrado)
		iRet = FindUser( &lbscbUserBase, szUserName, "$$$" );
		if( ( iRet != LBS_OK ) && ( iRet != LBSE_INVALIDPASSWORD ) ){
			// $$$ O usuario NAO estah cadastrado para a base
			ERETURN( LBSE_USERNOTFOUND );
		}
		int iPos = lbscbUserBase.GetFieldRepetitionByVal( USERBASEACCESSBASES, szBaseName );
		if( iPos < 0 ){
			// a base szBaseName NAO esta' cadastrada na
			// UDB szUserBaseName, para o usuario szUserName
			ERETURN( LBSE_BASENOTFOUND );
		}
		int iRet = lbscbUserBase.DelFieldRepetition( USERBASEACCESSBASES, iPos );
		if( iRet == LBS_OK ){
			lbscbUserBase.DelFieldRepetition( USERBASEACCESSTYPES, iPos );
			if( (iRet = lbscbUserBase.LockRecord( plbsctTicket )) == LBS_OK ){
				iRet = lbscbUserBase.UpdateRecord( plbsctTicket );
				lbscbUserBase.ReleaseRecord( plbsctTicket );
			}
		}
	} else {
		// para todos os usuarios
		if( lbscbUserBase.FirstFRecord( plbsctTicket ) != LBS_OK ){
			// erro
			ERETURN( LBSE_ERROR );
		}
		do{
			int iPos = lbscbUserBase.GetFieldRepetitionByVal( USERBASEACCESSBASES, szBaseName );
			if( iPos >= 0 ){
				iRet = lbscbUserBase.DelFieldRepetition( USERBASEACCESSBASES, iPos );
				if( iRet == LBS_OK ){
					lbscbUserBase.DelFieldRepetition( USERBASEACCESSTYPES, iPos );
					if( (iRet = lbscbUserBase.LockRecord( plbsctTicket )) == LBS_OK ){
						iRet = lbscbUserBase.UpdateRecord( plbsctTicket );
						lbscbUserBase.ReleaseRecord( plbsctTicket );
					}
				}
			}
		} while( lbscbUserBase.NextFRecord( plbsctTicket ) == LBS_OK );
	}
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo GetGroups
	Obtem a lista de grupos da UDB logada. Se o parâmetro szUserName
	for NULL, o metodo lista todos os grupos de todos os usuários;
	caso contrario, lista apenas os grupos do usuário szUserName.

	Parameters:
        	- plbscTicketPar -> apontador para o ticket;
		- szUserName	 -> nome do usuario. Pode ser NULL para
				    indicar TODOS OS USUARIOS.
		- bMem		 -> so' e' util quando szUserName indica o
				    nome do usuario que esta' logado. Quando
				    for FALSE (valor default), indica que os nomes de 
				    grupos do usuario serao buscados na UDB onde o usuario
				    esta' logado, o que significa uma busca em disco;
				    se for TRUE, os dados serao
				    obtidos em memoria, na estrutura de dados do
				    usuario que eh montada no momento do login. Isso
				    eh mais rapido, mas ha' o risco de obtencao de
				    dados inconsistentes, pois algum outro processo pode
				    ter alterado a lista de grupos do usuario na UDB
				    e a estrutura de dados em memoria fica inconsistente.

	Return:
		- NULL em caso de erro. Uma string contendo os grupos separados
		  por espacos em branco se correr tudo bem.

	Comments:
		- O valor retornado DEVE ser deletado pela aplicacao.

***/
char *
LBSC_Session::GetGroups( const LBSC_Ticket *plbscTicketPar, char *szUserName, BOOL bMem )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetGroups") );
	int	iRet;
	char	*szReturn;

	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	if( bMem ){
		// devemos consultar os dados em memoria
		if( stricmp( szUserName, plbscuUser->GetUserName() ) != 0 ){
			// o usuario indicado nao eh o que esta' logado.
			NRETURN( LBSE_BADARG );
		}
		if( !plbscuUser->plbscglGroupList ){
			// por algum motivo estranho, a lista de grupos do cara logado
			// nao esta' montada.
			NRETURN( LBSE_NOMEMORY );
		}
		LBSC_Group *pGrp = plbscuUser->FirstGroup();
		if( !pGrp ){
			// nao ha' grupos na lista
			SetError( LBS_OK );
			return( Strdup( "" ) );
		}
		char	*szReturn = (char*) LBS_Realloc( NULL, 0, strlen( (char*) pGrp->strUserName ) + 2 );
		if( !szReturn ){
			// deu pau
			NRETURN( LBSE_NOMEMORY );
		}
		szReturn[ 0 ] = '\0';
		while( pGrp ){
			strcat( szReturn, (char*) pGrp->strUserName );
			strcat( szReturn, " " );
			pGrp = plbscuUser->NextGroup();
			if( pGrp ){
				szReturn = (char*) LBS_Realloc( szReturn, strlen( szReturn ), strlen( szReturn ) + strlen( (char*) pGrp->strUserName ) + 2 );
			}
			if( !szReturn ){
				// deu pau
				NRETURN( LBSE_NOMEMORY );
			}
		}
		// retirar o ultimo espaco em branco
		szReturn[ strlen( szReturn ) - 1 ] = '\0';
		SetError( LBS_OK );
		return( szReturn );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( plbscTicketPar, (char *)strUDBLogged, this );
	if( !bUserBase.BaseObjOk() ){
		NRETURN( LBSE_ERROR );
	}
	if( szUserName ){
		// vamos pegar os grupos do usuario szUserName
		iRet = bUserBase.Locate( plbscTicketPar, 1, ENTIRETREE, strupr( szUserName ) );
		if( iRet != LBS_OK ){
			NRETURN( LBSE_ERROR );
		}
		LBSC_Field	*pf = bUserBase[ USERBASEGROUPLIST ];
		// obter tamanhos das strings para alocar
		if( pf ){
			int	iSize = 0;
			int	iNumRep = pf->GetNumberOfRepetition();
			for( int i = 0; i < iNumRep; i++ ){
				LBSC_Data	*pd = (*pf)[ i ];

				if( !pd ){
					NRETURN( LBSE_REPETITIONNOTFOUND );
				}
				iSize += (pd->GetSize()+1); // +1 para o espaco em branco
			}
			// aloca o buffer
			szReturn = new char[ iSize + 1 ]; // +1 por garantia
			if( !szReturn ){
				NRETURN( LBSE_NOMEMORY );
			}
			memset( szReturn, 0, iSize + 1 );
			// construir a string de retorno
			for( i = 0; i < pf->GetNumberOfRepetition(); i++ ){
				// evitar repeticao de chaves na string de retorno
				LBSC_Data	*pd = (*pf)[ i ];
				if( pd ){
					if( !strstr( szReturn, (char*) (*pd) ) ){
						strcat( szReturn, (char*) (*pd) );
						strcat( szReturn, " " );
					}
				}
			}
			szReturn[ strlen( szReturn ) - 1 ] = '\0';
			SetError( LBS_OK );
			return( szReturn );
		} else {
			NRETURN( LBSE_BADUSERBASE );
		}
	}

	// como e' dificil saber o tamanho exato que devemos alocar para
	// o buffer de retorno, vamos alocar um tamanho qualquer e, quando
	// for necessario, realocaremos seu espaco a fim de aumenta-lo.
	int	iAllocNum = 0;	// quantas vezes aloquei szReturn
	szReturn = new char[ (++iAllocNum * (DEFAULT_MAXKEYSIZE + 2)) ];
	if( !szReturn ){
		NRETURN( LBSE_NOMEMORY );
	}
	memset( szReturn, 0, DEFAULT_MAXKEYSIZE + 2 );
	// szBuffer pode ser alocado com um tamanho fixo
	char	*szBuffer = new char [ DEFAULT_MAXKEYSIZE + 1 ];
	if( !szBuffer ){
		delete szReturn;
		NRETURN( LBSE_NOMEMORY );
	}
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
		// nome de grupo
		if( CheckFieldInCurrentKey( USERBASEGROUPLIST, bUserBase ) ){
			// evitar repeticao de chaves na string de retorno
			if( !strstr( szReturn, szBuffer ) ){
				if( (strlen( szBuffer ) + strlen( szReturn ) + 1) > (size_t)
				    (iAllocNum * (DEFAULT_MAXKEYSIZE+2)) ){
					// precisamos realocar szReturn
					char	*szAux = (char*) LBS_Realloc( (void*) szReturn, (iAllocNum * (DEFAULT_MAXKEYSIZE + 2)), (++iAllocNum * (DEFAULT_MAXKEYSIZE + 2)) );

					if( !szAux ){
						// infelizmente, nao pudemos aumentar
						// a string. Vamos retornar o que temos
						// ateh o momento.
						delete szBuffer;
						SetError( LBSE_NOMEMORY );
						return( szReturn );
					}
					szReturn = szAux;
				}
				strcat( szReturn, szBuffer );
				strcat( szReturn, " " );
			}
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
	STATIC PUBLIC
	Metodo GetGroups
	Obtem a lista de grupos de uma determinada UDB. Se o parâmetro szUserName
	for NULL, o metodo lista todos os grupos de todos os usuários;
	caso contrario, lista apenas os grupos do usuário szUserName.

	Parameters:
		- szUserName -> nome do usuario. Pode ser NULL para
				    indicar TODOS OS USUARIOS.
		- szUDBName	 -> nome da UDB
		- szServerName -> nome do servidor

	Return:
		- NULL em caso de erro. Uma string contendo os grupos separados
		  por espacos em branco se correr tudo bem.

	Comments:
		- O valor retornado DEVE ser deletado pela aplicacao.

***/
char *
LBSC_Session::GetGroups( const char *szUserName, const char *szUDBName, const char * /*szServerName*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetGroups") );
	char	*szReturn = NULL;
	int		iRet = LBSE_NOMEMORY;

	// fazer um login para chamar o outro GetGroups

	LBSC_Session	*pSession = LBSC_Session::New();

	if( pSession ){
		// para o SLogin nao interessa o nome do usuario
		TNetInfo			tni( "$", "$", NULL, NULL, NULL, NULL );
		const	LBSC_Ticket	*pTicket = pSession->SLogin( tni );

		if( pTicket ){
			szReturn = pSession->GetGroups( pTicket, (char*) szUserName );
			iRet = pSession->LastError();
			pSession->Logout();
		} else {
			iRet = pSession->LastError();
		}
		LBSC_Session::Delete( pSession );
	}
	SetLastError( (DWORD) (iRet | 0x20000000) );
	return( szReturn );
}

/***
	PRIVATE
***/
BOOL
LBSC_Session::CheckFieldInCurrentKey( char *szFieldName, LBSC_Base &bUserBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CheckFieldInCurrentKey") );
	LTC_OCCURRENCELIST	*pOcListOfCurrKey;
	UINT		uiAux = bUserBase.uiNavigationField;
	LTC_OCCURRENCE	*pltcOcAux;

	if( !bUserBase.plbscisIndexSystem ){
		SetError( LBSE_INVALIDINDEXSYSTEM );
		return( FALSE );
	}

	int iTmpIndex = bUserBase.iNavigationIndex;
	bUserBase.iNavigationIndex = WORDTREE;
	pOcListOfCurrKey = bUserBase.GetListOfCurrentKey();
	bUserBase.iNavigationIndex = iTmpIndex;

	if( !pOcListOfCurrKey ){
		return( FALSE );
	}
	LBSC_Field	*pf = bUserBase[ szFieldName ];
	if( !pf ){
		SetError( LBSE_FIELDNOTFOUND );
		return( FALSE );
	}
	bUserBase.uiNavigationField = pf->GetId();
	pltcOcAux = bUserBase.GetOc( pOcListOfCurrKey, FIRSTOC );
	bUserBase.uiNavigationField = uiAux;
	delete pOcListOfCurrKey; // A GREEN diz que devemos deletar pOcListOfCurrKey
	if( pltcOcAux ){
		// nao devemos deletar pltcOcAux
		return( TRUE );
	}
	return( FALSE );
}

