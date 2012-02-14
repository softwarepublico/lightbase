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
// Module: SESSCL21.CPP
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
#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif
#ifndef	_DEFFUNCS_H_
#include	<deffuncs.h>
#endif
extern "C" {
#include	<personcl.h>
}
#ifndef	_OLDTYPES_H_
#include "oldtypes.h"
#endif
#ifndef _OLDLB1_
#include "oldlb1cl.h"
#endif
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

EXTLOG( _clLBSLog );	// objeto para geracao de log

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

// controle de bases reservadas para manutencao
extern LBSC_MaintBasesList	*_pclMaintBaseList;


/***
	PRIVATE
	Metodo IncorporateBase3
	Incorpora uma nova base ao LBS. A base deve estar no formato 
	antigo (numero magico 3).

	Parameters:
		- 

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- 

***/
int
LBSC_Session::IncorporateBase3( const LBSC_Ticket *plbscTicketPar, char *szBaseName, char *szBasePassword, char *szUserName, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IncorporateBase3") );
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// verifica os parametros
	if( !szBaseName || strcmp( szBaseName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}
	char	szDirBase[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char	szFullName[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	// vamos checar se a base szBaseName ja' existe no arquivo de controle

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if ( ptbfAux ) {
		// ja' existe uma base com o nome indicado
		ERETURN( LBSE_DUPLICATEBASE );
	}

	// pegar o nome do diretorio base (dir_base)
	LBSC_Base::GetDirBase( szDirBase );

	// montar o nome do diretorio para renomear os arquivos
	sprintf( (char*) szFullName, "%s\\%s", szDirBase, szBaseName );
	strupr( szFullName );

	// verifica se a base existe.
//	if( !C_LB1::Exist( szFullName ) ){
	if( chdir( szFullName ) != 0 ){
		// o cara deu um nome de base que nao existe!
		ERETURN( LBSE_BASENOTFOUND );
	}

	// renomeia os arquivos da base para que eles fiquem com o mesmo nome do diretorio.
	// (eh bom ter certeza de que o nome da base esta' coerente com o esquema de nomes
	// usado pelo LBS)
	if( RenameDirFiles( szFullName ) != LBS_OK ){
		// deu pau no rename.
		// temos que abortar o processo.
		ERETURN( LBSE_ERROR );
	}

	// montar o nome do diretorio completo, para acessar os arquivos da base
	char	szUserBaseName[ FILENAMESIZE ];
	BYTE	bBaseType;
	BOOL	bEncrypt;
	char	szDrive[ MAXDRIVE ];
	char	szDir[ MAXDIR ];
	char	szName[ MAXFILE ];
	char	szExt[ MAXEXT ];
	fnsplit( szBaseName, szDrive, szDir, szName, szExt );
	sprintf( (char*) szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, CONTROLFILEEXT );
	strupr( szFullName );

	// abre LB1 para verificar o tipo da base e a sua senha e o nome do usuario, se
	// for necessario
	C_OldLB1	cfLB1;
	if( cfLB1.Open( szFullName, NULL ) != OK ){
		// nao consegui abrir cfLB1
		ERETURN( LBSE_FILEERROR );
	}
	// checa o tipo da base
	if( cfLB1.tcrHead.tcrHead.bBaseType != BASE_PUBLIC && cfLB1.tcrHead.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ){
		// temos que comparar o nome do usuario e a senha da base

		// vejamos o nome do usuario:
		if( !szUserName || strcmp( szUserName, "" ) == 0 ){
	    	cfLB1.Close();
	    	ERETURN( LBSE_PRIVUSERNAMEFAULT );
		}

		// ok.
		if( stricmp( (char*) cfLB1.tcrHead.tcrHead.szBasePassword, szBasePassword ? szBasePassword : "" ) != 0 ){
			// a password esta' errada
	    	cfLB1.Close();
	    	ERETURN( LBSE_INVALIDPASSWORD );
		}
		if( stricmp( (char*) cfLB1.tcrHead.tcrHead.szOwnerName, szUserName ) != 0 ){
			// o nome do usuario indicado nao eh igual ao nome do dono da base
	    	cfLB1.Close();
	    	ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// se chegamos aqui, eh porque a base eh publica ou o usuario indicou o nome do dono
	// e a password da base corretamente.
	// vamos obter o nome da UDB aa qual a base vai ser associada
	bBaseType = cfLB1.tcrHead.tcrHead.bBaseType;
	bEncrypt = cfLB1.tcrHead.tcrHead.bIsEncrypt;

	strcpy( szUserBaseName, bBaseType == USER_BASE ? "" : szUDBName ? szUDBName : (char*) cfLB1.tcrHead.tcrHead.szUserBase );
	strupr( szUserBaseName );
	if( strcmp( szUserBaseName, "" ) == 0 && cfLB1.tcrHead.tcrHead.bBaseType != USER_BASE ){
		// nome invalido para UDB
		cfLB1.Close();
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	LBSC_Base	*pUDB = NULL;
	if( bBaseType != USER_BASE ){
		// vamos abrir a UDB para obter seu numero de identificacao (numero de link)
		pUDB = new LBSC_Base( plbscTicketPar, szUserBaseName, this );
		if( !pUDB ){
			cfLB1.Close();
			NRETURN( LBSE_NOMEMORY );
		}
		if( pUDB->BaseObjOk() == FALSE ){ // Nao consegui abrir a UDB
			delete pUDB;
			cfLB1.Close();
			ERETURN( LBSE_INVALIDUSERBASE );
		}
	}

	// abrir o arquivo de backup do header de LB1
	sprintf( szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, LB1BAKEXT );
	C_OldLB1	cfBak( szFullName, bEncrypt ? LBDEFKEY : NULL, "wb+", SH_DENYNO );

	if( !cfBak.IsOpen() ){
		// nao deu para abrir o arquivo de backup
		ERETURN( LBSE_ERROR );
	}
	if( cfBak.Seek( 0, SEEK_SET ) != OK ){
		// deu pau
		ERETURN( LBSE_ERROR );
	}

	// atualizar, na base szBaseName, o nome da UDB e o seu link,
	// e o nome do novo dono da base, que vai ser o cara que
	// esta' logado.
	cfLB1.tcrHead.tcrHead.szUserBase = szUserBaseName;
	cfLB1.tcrHead.tcrHead.dwUserBaseId = (bBaseType == USER_BASE) ? 0 : pUDB->LB1.tcrHead.dwBaseId;
	if( plbscuUser ){
		cfLB1.tcrHead.tcrHead.szOwnerName = plbscuUser->GetUserName();
	}

	// grava o header de LB1 de szBaseName
	cfLB1.R_WriteHead();

	// atualiza a copia de seguranca do header de LB1
	cfBak.R_WriteHead( &cfLB1.tcrHead );
	cfBak.Close();

	// fecha LB1 de szBaseName
	cfLB1.Close();

	// fecha a UDB
	if( pUDB ){
		delete pUDB;
		pUDB = NULL;
	}

	TBasesFile	tbfAux;
	tbfAux.szBaseName = strupr( szBaseName );
	tbfAux.szBaseLongName = strupr( szBaseName );
	tbfAux.szUserBaseName = szUserBaseName;
	tbfAux.bRecDeleted = FALSE;
	tbfAux.bBaseType = bBaseType;
	if( !pControlFile->Insert( tbfAux ) ){
		ERETURN( LBSE_ERROR );
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo IncorporateBase4
	Incorpora uma nova base ao LBS. A base deve estar no formato 
	novo (numero magico 4).

	Parameters:
		- 

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- 

***/
int
LBSC_Session::IncorporateBase4( const LBSC_Ticket *plbscTicketPar, char *szBaseName, char *szBasePassword, char *szUserName, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IncorporateBase4") );
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// verifica os parametros
	if( !szBaseName || strcmp( szBaseName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}
	char	szDirBase[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char	szFullName[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	// vamos checar se a base szBaseName ja' existe no arquivo de controle

	C_SessCritSect	cCS4( this, CRITSECT4 );

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if ( ptbfAux ) {
		// ja' existe uma base com o nome indicado
		ERETURN( LBSE_DUPLICATEBASE );
	}

	// pegar o nome do diretorio base (dir_base)
	LBSC_Base::GetDirBase( szDirBase );

	// montar o nome do diretorio para renomear os arquivos
	sprintf( (char*) szFullName, "%s\\%s", szDirBase, szBaseName );
	strupr( szFullName );

	// verifica se a base existe.
//	if( !C_LB1::Exist( szFullName ) ){
	if( chdir( szFullName ) != 0 ){
		// o cara deu um nome de base que nao existe!
		ERETURN( LBSE_BASENOTFOUND );
	}

	// renomeia os arquivos da base para que eles fiquem com o mesmo nome do diretorio.
	// (eh bom ter certeza de que o nome da base esta' coerente com o esquema de nomes
	// usado pelo LBS)
	if( RenameDirFiles( szFullName ) != LBS_OK ){
		// deu pau no rename.
		// temos que abortar o processo.
		ERETURN( LBSE_ERROR );
	}

	// montar o nome do diretorio completo, para acessar os arquivos da base
	char	szUserBaseName[ FILENAMESIZE ];
	BYTE	bBaseType;
	BOOL	bEncrypt;
	char	szDrive[ MAXDRIVE ];
	char	szDir[ MAXDIR ];
	char	szName[ MAXFILE ];
	char	szExt[ MAXEXT ];
	fnsplit( szBaseName, szDrive, szDir, szName, szExt );
	sprintf( (char*) szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, CONTROLFILEEXT );
	strupr( szFullName );

	// abre LB1 para verificar o tipo da base e a sua senha e o nome do usuario, se
	// for necessario
	C_LB1	cfLB1;
	if( cfLB1.Open( szFullName, NULL ) != OK ){
		// nao consegui abrir cfLB1
		ERETURN( LBSE_FILEERROR );
	}
	// checa o tipo da base
	if( cfLB1.tcrHead.bBaseType != BASE_PUBLIC && cfLB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ){
		// temos que comparar o nome do usuario e a senha da base

		// vejamos o nome do usuario:
		if( !szUserName || strcmp( szUserName, "" ) == 0 ){
	    	cfLB1.Close();
	    	ERETURN( LBSE_PRIVUSERNAMEFAULT );
		}

		// ok.
		if( stricmp( (char*) cfLB1.tcrHead.szMaintenancePassword, szBasePassword ? szBasePassword : "" ) != 0 ){
			// a password esta' errada
	    	cfLB1.Close();
	    	ERETURN( LBSE_INVALIDPASSWORD );
		}
		if( stricmp( (char*) cfLB1.tcrHead.szOwnerName, szUserName ) != 0 ){
			// o nome do usuario indicado nao eh igual ao nome do dono da base
	    	cfLB1.Close();
	    	ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// se chegamos aqui, eh porque a base eh publica ou o usuario indicou o nome do dono
	// e a password da base corretamente.
	// vamos obter o nome da UDB aa qual a base vai ser associada
	bBaseType = cfLB1.tcrHead.bBaseType;
	bEncrypt = cfLB1.tcrHead.bIsEncrypt;

	strcpy( szUserBaseName, bBaseType == USER_BASE ? "" : szUDBName ? szUDBName : (char*) cfLB1.tcrHead.szUserBase );
	strupr( szUserBaseName );
	if( strcmp( szUserBaseName, "" ) == 0 && cfLB1.tcrHead.bBaseType != USER_BASE ){
		// nome invalido para UDB
		cfLB1.Close();
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	LBSC_Base	*pUDB = NULL;
	if( bBaseType != USER_BASE ){
		// vamos abrir a UDB para obter seu numero de identificacao (numero de link)
		pUDB = new LBSC_Base( plbscTicketPar, szUserBaseName, this );
		if( !pUDB ){
			cfLB1.Close();
			NRETURN( LBSE_NOMEMORY );
		}
		if( pUDB->BaseObjOk() == FALSE ){ // Nao consegui abrir a UDB
			delete pUDB;
			cfLB1.Close();
			ERETURN( LBSE_INVALIDUSERBASE );
		}
	}

	// abrir o arquivo de backup do header de LB1
	sprintf( szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, LB1BAKEXT );
	C_LB1	cfBak( szFullName, bEncrypt ? LBDEFKEY : NULL, "wb+", SH_DENYNO );

	if( !cfBak.IsOpen() ){
		// nao deu para abrir o arquivo de backup
		ERETURN( LBSE_ERROR );
	}
	if( cfBak.Seek( 0, SEEK_SET ) != OK ){
		// deu pau
		ERETURN( LBSE_ERROR );
	}

	// atualizar, na base szBaseName, o nome da UDB e o seu link,
	// e o nome do novo dono da base, que vai ser o cara que
	// esta' logado.
	cfLB1.tcrHead.szUserBase = szUserBaseName;
	cfLB1.tcrHead.dwUserBaseId = (bBaseType == USER_BASE) ? 0 : pUDB->LB1.tcrHead.dwBaseId;
	if( plbscuUser ){
		cfLB1.tcrHead.szOwnerName = plbscuUser->GetUserName();
	}

	// grava o header de LB1 de szBaseName
	cfLB1.LB1_WriteHead();

	// atualiza a copia de seguranca do header de LB1
	cfBak.R_WriteHead( &cfLB1.tcrHead );
	cfBak.Close();

	// fecha LB1 de szBaseName
	cfLB1.Close();

	// fecha a UDB
	if( pUDB ){
		delete pUDB;
		pUDB = NULL;
	}

	// agora vamos inserir a base no arquivo de controle. eh bom lembrar que
	// esse arquivo de controle ja' esta' aberto por este metodo e esta' travado.
	// portanto, nenhum outro processo o acessou durante o processamento deste metodo.
	TBasesFile	tbfAux;
	tbfAux.szBaseName = strupr( szBaseName );
	tbfAux.szBaseLongName = strupr( szBaseName );
	tbfAux.szUserBaseName = szUserBaseName;
	tbfAux.bRecDeleted = FALSE;
	tbfAux.bBaseType = bBaseType;
	if( !pControlFile->Insert( tbfAux ) ){
		ERETURN( LBSE_ERROR );
	}
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo CancelOperation
	Cancela a operacao corrente.

	Parameters:
		- 

	Return:
		- 

	Comments:
		- Este metodo existe na classe LBSC_OpInfo, mas foi
		  implementado aqui para manter compatibilidade com o
		  stub cliente do LBS.

***/
void
LBSC_Session::CancelOperation()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CancelOperation") );
	LBSC_OpInfo::CancelOperation();
}

/***
	PUBLIC
	Metodo GetOpInfo
	Obtem o status da operacao corrente (quanto ja foi
	executado, em %, e uma string contendo uma informacao
	dizendo o que esta' sendo feito no momento).

	Parameters:
		- szActionPar	-> buffer, alocado pela aplicacao,
						   onde sera' retornada a string que
						   informa o que esta' acontecendo no
						   momento
		- pfPercentPar	-> ponteiro parra um float, no qual
						   sera' armazenado um numero de 0 a 100,
						   indicando o percentual do processamento
						   da operacao corrente.

	Return:
		- 

	Comments:
		- Este metodo existe na classe LBSC_OpInfo, mas foi
		  implementado aqui para manter compatibilidade com o
		  stub cliente do LBS.

***/
void
LBSC_Session::GetOpInfo( char *szActionPar, float *pfPercentPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetOpInfo") );
	LBSC_OpInfo::GetOpInfo( szActionPar, pfPercentPar );
}

/***
	PUBLIC
	Metodo BreakSecurity
	Desliga momentaneamente algum tipo de checagem de seguranca.

	Parameters:
		- iFlags		-> conjunto de bits informando quais as
						   checagens de seguranca devem ser desativadas.

	Return:
		- 

	Comments:
		- Os possiveis bits de iFlags estao descritos no arquivo LBSDEFS.H.
		- Cada bit de iFlags age sobre determinadas operacoes do LBS. Essas
		  operacoes, quando executadas, *sempre* resetam os bits que estiverem
		  setados. Isto eh, para cada operacao que se deseja a nao checagem de
		  seguranca, este metodo deve ser chamado uma vez.

***/
void
LBSC_Session::BreakSecurity( int iFlags )
{
	iSecurityFlags = iFlags;
}


/***
	static PUBLIC
	Metodo StBreakSecurity
	Implementado apenas nos stubs client/server. Nao faz nada aqui no LBS.

	Parameters:
		- 

	Return:
		- 

	Comments:
		- 

***/
void
LBSC_Session::StBreakSecurity( int, const char * )
{
}



/***
	PRIVATE
	Metodo ReorganizeUDB
	Reorganiza os arquivos de uma udb

	Parameters:
		- plbscTicketPar	-> ticket de seguranca
		- plbscbUdb			-> ponteiro para uma base de usuarios, ja' aberta

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- 
***/
int
LBSC_Session::ReorganizeUDB( const LBSC_Ticket *plbscTicketPar, LBSC_Base *plbscbUdb )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReorganizeUDB (privado)") );

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	// verifica se o ponteiro realmente representa uma UDB
	if( !plbscbUdb || (plbscbUdb->LB1.tcrHead.bBaseType != USER_BASE) ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	
	// inserir a base na lista de bases, porque o ReprocBase precisa disso.
	C_SessCritSect	cCS0( this, CRITSECT0 );
	lbscblBaseList.Add( plbscbUdb, AFTER );

	// agora eh so' chamar o metodo de reprocessamento de base
	int	iRet = ReprocBase( plbscTicketPar, plbscbUdb, TRUE );

	// retirar a base da lista de bases.
	// podemos deletar o elemento corrente da lista com seguranca, pois
	// estamos em regiao critica.
	// lembrar que nao podemos chamar simplesmente o Del da lista,
	// porque se fizermos isso o ponteiro da base vai ser destruido.
	lbscblBaseList.Refresh( NULL );
	lbscblBaseList.Del();

	ERETURN( iRet );
}


/**********************************************************
// Function name	: LBSC_Session::ValidUser
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *plbscTicketPar
// Argument         : const char *szUserName
// Argument         : const char *szPassword
**********************************************************/
int LBSC_Session::ValidUser( const LBSC_Ticket *plbscTicketPar, const char *szUserName, const char *szPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ValidUser") );

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// Abrir a UDB
	LBSC_Base	*pUdb = new LBSC_Base( plbscTicketPar, (char*) strUDBLogged, this );
	if( !pUdb ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !pUdb->BaseObjOk() ){
		delete pUdb;
		ERETURN( LBSE_UBNOTOK );
	}
	int iRet = FindUser( pUdb, szUserName, szPassword );
	delete pUdb;
	ERETURN( iRet );	
}



/**********************************************************
// Function name	: LBSC_Session::SetAppInfo
// Description	    : 
// Return type		: void 
// Argument         :  long lAppIdPar
// Argument         : const char *szAppName
**********************************************************/
void LBSC_Session::SetAppInfo( long lAppIdPar, const char *szAppName )
{
	strAppName = szAppName;
	lAppId = lAppIdPar;
}

/**********************************************************
// Function name	: LBSC_Session::GetAppName
// Description	    : 
// Return type		: const char* 
**********************************************************/
const char* LBSC_Session::GetAppName()
{
	return( (const char*) (char*) strAppName );
}

/**********************************************************
// Function name	: LBSC_Session::SetLastAccess
// Description	    : 
// Return type		: void 
// Argument         :  unsigned long ulLastAccessPar
**********************************************************/
void LBSC_Session::SetLastAccess( unsigned long ulLastAccessPar )
{
	ulLastAccess = ulLastAccessPar;
}

/**********************************************************
// Function name	: LBSC_Session::GetLastAccess
// Description	    : 
// Return type		: unsigned long 
**********************************************************/
unsigned long LBSC_Session::GetLastAccess()
{
	return ulLastAccess;
}

/**********************************************************
// Function name	: LBSC_Session::SetBaseForMaintenance
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *pTicketPar
// Argument         : const char *szBaseName
// Argument         : const char *szUserName
// Argument         : const char *szWarningMsg
// Argument         : BOOL bSet
**********************************************************/
int LBSC_Session::SetBaseForMaintenance( const LBSC_Ticket *pTicketPar, const char *szBaseName, const char *szUserName, const char *szWarningMsg, BOOL bSet )
{
	// o parametro bSet indica se a base deve ser setada para manutencao (TRUE)
	// ou retirada da lista de bases reservadas (FALSE)


	if( !szBaseName || !szUserName ){
		ERETURN( LBSE_BADARG );
	}

	if( TicketIsOk( pTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_MaintBase	cMaintBaseAux( szBaseName, szUserName, szWarningMsg );

	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( !_pclMaintBaseList ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( _pclMaintBaseList->Find( &cMaintBaseAux, 0, TRUE ) ){
		// a base esta' reservada
		if( !bSet ){
			// vamos retirar a base da lista
			_pclMaintBaseList->Del();
			ERETURN( LBS_OK );
		}
		ERETURN( LBSE_BASEALREADYRESERVED );
	}
	if( !bSet ){
		// deveriamos tirar a base da lista mas ela nao
		// foi encontrada. Isso nao precisa ser um erro.
		ERETURN( LBS_OK );
	}

	// so' posso fazer isso se eu (usuario logado) for um administrador 
	// na UDB ou se for o dono da base que esta' sendo reservada.

	// verificar se o cara eh administrador na udb
	int iType = GetUserType( pTicketPar, strUDBLogged, NULL);
	if ( iType != MASTER_USER ) {
		// o cara nao eh administrador. entao vamos ver se ele eh o
		// dono da base em questao.

		// ********** isso eh mais delicado de se verificar, pois tenho que abrir a base
		// para ver o nome do dono e ela pode estar aberta em modo exclusivo
		// RESOLVER!!! ************************


		ERETURN( LBSE_NOPERMISSION );
	}

	// vamos adicionar um novo elemento na lista
	LBSC_MaintBase	*pcMaintBase = cMaintBaseAux.Duplicate();
	
	if( pcMaintBase ){
		if( _pclMaintBaseList->Add( pcMaintBase, TAIL ) == OK ){
			ERETURN( LBS_OK );
		}
		delete pcMaintBase;
	}
	ERETURN( LBSE_NOMEMORY );
}


/**********************************************************
// Function name	: LBSC_Session::GetDefaultWarningMsg
// Description	    : 
// Return type		: char* 
**********************************************************/
char* LBSC_Session::GetDefaultWarningMsg()
{
	// a aplicacao DEVE deletar o buffer retornado.
	
	char	*szRet = NULL;
	
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szRet = _pcInter->GetGenMsgsAppVar( "LBSMSG_DEF_MAINTBASE_WARNINGMSG" );
	}

	if( !szRet ){
		NRETURN( LBSE_NOMEMORY );
	}

	SetError( LBS_OK );
	return( szRet );
}

/**********************************************************
// Function name	: LBSC_Session::GetBaseWarningMsg
// Description	    : 
// Return type		: char* 
// Argument         : const char *szBaseName
**********************************************************/
char* LBSC_Session::GetBaseWarningMsg( const char *szBaseName )
{
	// a aplicacao DEVE deletar o buffer retornado.
	

	if( !szBaseName ){
		NRETURN( LBSE_BADARG );
	}

	// regiao critica para a lista de bases reservadas
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( _pclMaintBaseList ){
		// verificar se a base esta' reservada para manutencao
		LBSC_MaintBase	cMaintBaseAux( szBaseName, "", NULL );

		if( _pclMaintBaseList->Find( &cMaintBaseAux, 0, TRUE ) ){
			// a base esta' reservada.
			LBSC_MaintBase	*pMaintBase = _pclMaintBaseList->Current();
			char			*szRet;

			szRet = Strdup( (char*) pMaintBase->strWarningMsg );
			if( szRet ){
				SetError( LBS_OK );
				return( szRet );
			}
		} else {
			// a base nao esta' reservada
			NRETURN( LBSE_BASENOTRESERVED );
		}
	}
	NRETURN( LBSE_NOMEMORY );
}

/**********************************************************
// Function name	: LBSC_Session::GeMaintBaseUserName
// Description	    : 
// Return type		: char* 
// Argument         : const char *szBaseName
**********************************************************/
char* LBSC_Session::GeMaintBaseUserName( const char *szBaseName )
{
	// a aplicacao DEVE deletar o buffer retornado.
	

	if( !szBaseName ){
		NRETURN( LBSE_BADARG );
	}

	// regiao critica para a lista de bases reservadas
	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( _pclMaintBaseList ){
		// verificar se a base esta' reservada para manutencao
		LBSC_MaintBase	cMaintBaseAux( szBaseName, "", NULL );

		if( _pclMaintBaseList->Find( &cMaintBaseAux, 0, TRUE ) ){
			// a base esta' reservada.
			LBSC_MaintBase	*pMaintBase = _pclMaintBaseList->Current();
			char			*szRet;

			szRet = Strdup( (char*) pMaintBase->strUserName );
			if( szRet ){
				SetError( LBS_OK );
				return( szRet );
			}
		} else {
			// a base nao esta' reservada
			NRETURN( LBSE_BASENOTRESERVED );
		}
	}
	NRETURN( LBSE_NOMEMORY );
}


/**********************************************************
// Function name	: LBSC_Session::GetReservedMaintBases
// Description	    : 
// Return type		: LBSC_MaintBase* 
// Argument         : const LBSC_Ticket *pTicketPar
**********************************************************/
LBSC_MaintBase* LBSC_Session::GetReservedMaintBases( const LBSC_Ticket *pTicketPar )
{
	// retorna um array de LBSC_MaintBase contendo as bases que estao reservadas
	// para manutencao. O numero de elementos no array eh igual ao numero de bases
	// reservadas mais um. O ultimo elemento eh zerado (todos os atributos vazios) e
	// serve para indicar o final do array. Use o metodo IsZero da classe LBSC_MaintBase
	// para detectar o final do array.

	C_SessCritSect	cCS3( this, CRITSECT3 );

	if( TicketIsOk( pTicketPar ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	if( !_pclMaintBaseList ){
		NRETURN( LBSE_NOMEMORY );
	}
	int	iNumElem = _pclMaintBaseList->NumElem();

	if( iNumElem < 0 ){
		NRETURN( LBSE_ERROR );
	}

	LBSC_MaintBase	*pRet = new LBSC_MaintBase[ iNumElem + 1 ];	// +1 para o ultimo ser zerado.

	if( !pRet ){
		NRETURN( LBSE_NOMEMORY );
	}
	for( int i = 0; i < iNumElem; i++ ){
		LBSC_MaintBase	*pMaintBaseAux = (*_pclMaintBaseList)[ i ];

		if( pMaintBaseAux ){
			pRet[ i ].Set( (const char*) (char*) pMaintBaseAux->strBaseName, (const char*) (char*) pMaintBaseAux->strUserName, (const char*) (char*) pMaintBaseAux->strWarningMsg );
		}
	}
	SetError( LBS_OK );
	return( pRet );
}



/**********************************************************
// Function name	: LBSC_Session::Delete
// Description	    : 
// Return type		: void 
// Argument         : LBSC_MaintBase *pData
**********************************************************/
void LBSC_Session::Delete( LBSC_MaintBase *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete [] pData;
	}
}


/**********************************************************
// Function name	: LBSC_Session::GetInstalInfo
// Description	    : 
// Return type		: static TInstalInfo	 
// Argument         : 
**********************************************************/
TInstalInfo	LBSC_Session::GetInstalInfo( const char * /* szServer */ )
{
	TInstalInfo tiiInfo;

	tiiInfo.szSerialNum = LBSC_ServerConfig::Serial();

	tiiInfo.szOwnerName = LBSC_ServerConfig::Name();

	tiiInfo.szCompanyName = LBSC_ServerConfig::Company();

	return tiiInfo;
}


