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
// Module: SESSCL12.CPP
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

// nome da defudb
extern	char	_szDefUDBName[ MAXPATH ];

// extensoes de uma base LBS
extern	char	_szPrivateExtensions[];

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo TicketIsOk
	Verifica a validade do ticket de seguranca.

	Parameters:
		- plbscTicketPar	-> ticket de seguranca

	Return:
		- LBS_OK em caso de sucesso

	Comments:

***/
int
LBSC_Session::TicketIsOk( const LBSC_Ticket *plbscTicketPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::TicketIsOk 1 plbscTicketPar %p", plbscTicketPar) );
	if( !plbscTicketPar ){
		ERETURN( LBSE_BADARG );
	}
	if( !plbsctTicket ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	int iRet = memcmp( plbsctTicket, plbscTicketPar, sizeof( LBSC_Ticket ) );
	if( iRet == 0 ){
		SetError( LBS_OK );
	} else {
		SetError( LBSE_TICKETNOTOK );
	}
	return( iRet );
}




/***
	PUBLIC
	Metodo WhatUDBLogged
	O nome da UDB logada.

	Parameters:

	Return:
		- O nome da UDB.

***/
char *
LBSC_Session::WhatUDBLogged()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatUDBLogged") );
	SetError( LBS_OK );
	return( Strdup( (char*) strUDBLogged ) );
}




/***
	PUBLIC
	Metodo WhatUDB
	O nome da UDB associada a uma base.

	Parameters:
		- szDataBaseName: nome da base( inclusive path );
		- tmaServer: endereço do servidor. Se não for passado é assumido o servidor default ( configurado na instalação ).

	Return:
		- O nome da UDB.

	Comments:

***/
char *
LBSC_Session::WhatUDB( char *szDataBaseName, const char *tmaServer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WhatUDB") );
	char			szAux[ FILENAMESIZE ];

	// $$$ Ir para o servidor tmaServer

	if ( !ControlFileOK() ) {
		NRETURN( LBSE_CONTROLFILENOTOK );
	}

	C_SessCritSect	cCS4( this, CRITSECT4 );

	const TBasesFile *ptbfAux = pControlFile->Get( szDataBaseName );
	if ( !ptbfAux ) {
		// nao achamos a base
		NRETURN( LBSE_DIRNOTFOUND );
	}
	SetError( LBS_OK );
	return( Strdup( ((TBasesFile *)ptbfAux)->szUserBaseName ) );
}

/***
	PUBLIC
	Metodo CreateUDB
	Cria uma BU.

	Parameters:
		- pctTicket: ticket de seguranca;
		- szBaseName: nome da base;
		- szPassword: senha de uso;
		- szMaintPassword: senha de manutencao.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Apos a criacao da UDB, o usuario correntemente logado (que sera'
		  o dono) sera' adicionado.
		- Nao use este metodo para criar a UDB default. Para isso, use o
		  metodo CreateDefaultUserBase.

***/
int
LBSC_Session::CreateUDB( const LBSC_Ticket *pctTicket, char *szBaseName, char *szPassword, char *szMaintPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CreateUDB") );
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pctTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	int	iRet;
	TField	MyStruct [ 14 ];

	MyStruct [  0 ].Set( USERBASEUSERNAME, "User name", "PF1", ALPHA_FIELD, USERNAMESIZE, WORDTREE | UNIQUETREE | ENTIRETREE );
	MyStruct [  1 ].Set( USERBASEUSERPASSWORD, "User password", "PF2", ALPHA_FIELD, PASSWORDSIZE, 0 );
	MyStruct [  2 ].Set( USERBASEUSERTYPE, "User type", "PF3", VALUE_FIELD, 0, VALUETREE );
	MyStruct [  3 ].Set( USERBASEUSERDESCRIPTION, "User description", "PF4", ALPHA_FIELD, DESCRIPTIONSIZE, WORDTREE );
	MyStruct [  4 ].Set( USERBASEUSERADDRESS, "User address", "PF5", ALPHA_FIELD, ADDRESSSIZE, WORDTREE );
	MyStruct [  5 ].Set( USERBASEUSERPHONE, "User phone", "PF6", ALPHA_FIELD, PHONESIZE, WORDTREE );
	MyStruct [  6 ].Set( USERBASEGROUPLIST, "User groups", "PF7", ALPHA_FIELD, GROUPNAMESIZE, WORDTREE );
	MyStruct [  7 ].Set( USERBASEUSERCREATEDATE, "User creation date", "PF8", DATE_FIELD, 0, DATETREE );
	MyStruct [  8 ].Set( USERBASEUSERUPDATEDATE, "User update date", "PF9", DATE_FIELD, 0, DATETREE );
	MyStruct [  9 ].Set( USERBASEACCESSBASES, "Bases that the user can access", "PF10", ALPHA_FIELD, FULLNAMESIZE, WORDTREE );
	MyStruct [ 10 ].Set( USERBASEACCESSTYPES, "Type of the base", "PF11", VALUE_FIELD, 0, VALUETREE );
	MyStruct [ 11 ].Set( USERBASELOGINATTEMPTS, "Number of invalid login attempts", "PF12", VALUE_FIELD, 0, VALUETREE );
	MyStruct [ 12 ].Set( USERBASEPASSWORDCHANGEDATE, "Last password change date", "PF13", DATE_FIELD, 0, DATETREE );

	iRet = CreateBase( pctTicket, szBaseName ? szBaseName : _szDefUDBName, 
			   szBaseName ? "User DataBase" : "Default UserBase",
			   szPassword ? szPassword : "", szMaintPassword ? szMaintPassword : "", 
			   USER_BASE, TRUE, NULL, MyStruct, 5 /*slots*/, 5 /*contadores*/ );
	// os slots e os contadores sao de reserva, para o futuro.

	if( iRet == LBS_OK && plbscuUser ){
		TUDBRecord	tUDBRecord[ 2 ];
		tUDBRecord[ 0 ].Set( (char*) plbscuUser->GetUserName(), (char*) plbscuUser->lbscpPassword.GetConstPassword(), MASTER_USER, "User Data Base Owner", "", "", "UDB" );
		iRet = AddUser( pctTicket, szBaseName, tUDBRecord );
	}
	return( iRet );
}


/***
	static PUBLIC
	Metodo CreateDefaultUserBase
	Cria a UDB default.

	Parameters:
		- szServerName: nome do servidor. Nao eh importante para o LBS; apenas
				para os stubs de rede.
		- szPassword: senha de uso da UDB;
		- szMaintPassword: senha de manutencao da UDB.
		- szUserName: nome do usuario que sera' o dono da UDB
		- szUserPassword: senha do usuario szUserName.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- o arquivo de controle do LBS sera' destruido
		- Apos a criacao da UDB, o usuario szUserName sera' cadastrado.

***/
int
LBSC_Session::CreateDefaultUserBase( char * /*szServerName*/, char *szPassword, char *szMaintPassword, char *szUserName, char *szUserPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CreateDefaultUserBase") );
	if( !szUserName ){
		SetLastError( (DWORD) (LBSE_BADARG | 0x20000000) );
		return( LBSE_BADARG );
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetLastError( (DWORD) (LBSE_INVALIDLIC | 0x20000000) );
		return( LBSE_INVALIDLIC );
	}

	// cria uma sessao
	LBSC_Session	*pSession = LBSC_Session::New();

	if( !pSession ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( LBSE_NOMEMORY );
	}

	// faz slogin
	TNetInfo	tni( szUserName, szUserPassword, NULL, NULL, NULL, NULL );
	const	LBSC_Ticket	*pTicket = pSession->SLogin( tni );

	if( !pTicket ){
		// deu pau
		LBSC_Session::Delete( pSession );
		SetLastError( (DWORD) (LBSE_ERROR | 0x20000000) );
		return( LBSE_ERROR );
	}

	// tentar deletar a UDB (se ela existir)
	int	iRet = pSession->DeleteBase( pTicket, _szDefUDBName );

	// deletar arquivo de controle do LBS
	// Acessar lbs.ini para pegar o arquivo de controle
	char		szFNameAux[ FULLNAMESIZE ];
	char		szFullAux[ FULLNAMESIZE ];
	char		szAux[ FILENAMESIZE ];
	if( GetFNameOnProfile( szFullAux, szAux ) != LBS_OK ){
		LBSC_Session::Delete( pSession );
		SetLastError( (DWORD) (LBSE_LBSINIERROR | 0x20000000) );
		return( LBSE_LBSINIERROR );
	}
	sprintf( szFNameAux, "%s\\%s", szFullAux, szAux );
	// deletar
	remove( szFNameAux );
	// reinicializar o arquivo de controle
	if ( !ControlFileOK() || !pControlFile->Init() ) {
		SetLastError( (DWORD) (LBSE_CONTROLFILENOTOK | 0x20000000) );
		return( LBSE_CONTROLFILENOTOK );
	}

	// criar a UDB
	iRet = pSession->CreateUDB( pTicket, _szDefUDBName, szPassword, szMaintPassword );

	// logout
	pSession->Logout();

	// deleta a sessao
	LBSC_Session::Delete( pSession );

	// retorna
	SetLastError( (DWORD) (iRet | 0x20000000) );
	return( iRet );

}


/***
	PUBLIC
	Metodo DeleteUDB
	Deleta uma UDB

	Parameters:
		- szBaseName: nome da UDB;
		- szPassword: senha de uso da UDB;
		- bForce: se FALSE (default), indica que o metodo verificara' se ha'
			  bases ligadas aa UDB (se houver pelo menos uma base ligada aa
			  UDB, o metodo falhara'); se TRUE, o metodo deleta a UDB
			  incondicionalmente.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- o usuario deve estar logado em modo monousario
		- se bForce for TRUE, as bases com link para a UDB serao liberadas do
		  arquivo de controle para possibilitar uma posterior incorporacao em
		  outra UDB.

***/
int
LBSC_Session::DeleteUDB( const LBSC_Ticket *pTicket, char *szBaseName, char *szPassword, BOOL bForce )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DeleteUDB") );
	// Verifica se o usuario estah logado em modo mono
//	if( !IsMono() && !bSLogin ){
	if( !bIsLogged && !bSLogin ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	// procurar bases com link na UDB
	C_SessCritSect	cCS4( this, CRITSECT4 );

	for ( int i=0; i<pControlFile->Size(); i++) {
		// procurar pelo menos uma base com link para a UDB a ser
		// deletada
		const TBasesFile	*ptbfAux = pControlFile->Get( i );
		if ( !ptbfAux ) {
			continue;
		}
		if( stricmp( ((TBasesFile *)ptbfAux)->szUserBaseName, szBaseName) == 0 ){
			// existe uma base com link para a UDB
			if( !bForce ){
				// nao podemos deletar a UDB
				ERETURN( LBSE_UDBWITHBASE );
			} else {
				// vamos liberar a base do arquivo de controle para
				// que seja possivel incorpora-la depois.
				LeaveBase( pTicket, ((TBasesFile *)ptbfAux)->szBaseName );
			}
		}
	}

	// deletar a UDB
	int	iRet;
	do{
		// ficar tentando ate' que consiga abrir a base em modo
		// exclusivo para poder deleta-la.
		iRet = DeleteBase( pTicket, szBaseName );
	} while( iRet == LBSE_CANTOPENEXCLUSIVE );

	if ( iRet == LBS_OK ) {
		DelUDBFromCache( szBaseName );
	}
	// retorna
	ERETURN( iRet );
}


/***
	static PUBLIC
	Metodo DeleteDefaultUserBase
	Deleta a UDB default de um servidor

	Parameters:
		- szServerName: nome do servidor. Nao eh importante para o LBS; apenas
				para os stubs de rede.
		- szPassword: senha de uso da UDB;
		- bForce: se FALSE (default), indica que o metodo verificara' se ha'
			  bases ligadas aa UDB (se houver pelo menos uma base ligada aa
			  UDB, o metodo falhara'); se TRUE, o metodo deleta a UDB
			  incondicionalmente.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- se bForce for TRUE, as bases com link para a UDB serao liberadas do
		  arquivo de controle para possibilitar uma posterior incorporacao em
		  outra UDB.

***/
int
LBSC_Session::DeleteDefaultUserBase( char *szServerName, char *szPassword, BOOL bForce )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DeleteDefaultUserBase") );
	// cria uma sessao
	LBSC_Session	*pSession = LBSC_Session::New();

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetLastError( (DWORD) (LBSE_INVALIDLIC | 0x20000000) );
		return( LBSE_INVALIDLIC );
	}

	if( !pSession ){
		SetLastError( (DWORD) (LBSE_NOMEMORY | 0x20000000) );
		return( LBSE_NOMEMORY );
	}

	// faz slogin
	TNetInfo	tni( "$" /*USERNAME*/, "$" /*USERPASSWD*/, NULL, NULL, NULL, NULL, 10, TRUE );
	const	LBSC_Ticket	*pTicket = pSession->SLogin( tni );

	if( !pTicket ){
		// deu pau
		LBSC_Session::Delete( pSession );
		SetLastError( (DWORD) (LBSE_ERROR | 0x20000000) );
		return( LBSE_ERROR );
	}

	// chama DeleteUDB passando o nome da UDBDEFAULT
	int iRet = pSession->DeleteUDB( pTicket, _szDefUDBName, szPassword, bForce );

	// logout
	pSession->Logout();

	// deleta a sessao
	LBSC_Session::Delete( pSession );

	SetLastError( (DWORD) (iRet | 0x20000000) );
	return( iRet );
}


/***
	PRIVATE
	Metodo RenameToOrigFiles
	Renomeia arquivos de base temporaria para os da base original.

	Parameters:
		- szDirName
		- szBaseName

	Return:
		- LBS_OK caso exista a base original e obtenha sucesso.

	Comments:
		- Usado para recriar bases.

***/
int
LBSC_Session::RenameToOrigFiles( char *szDirName, char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::RenameToOrigFiles") );
	char		szPath[ MAXPATH ];
	char		*szFileName = strrchr( szBaseName, '\\' );

	if( szFileName ){
		szFileName++;
	} else {
		szFileName = szBaseName;
	}

	WIN32_FIND_DATA	Win32FD;
	sprintf( szPath, "%s\\*", szDirName );
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FD );

	if( Newdir != INVALID_HANDLE_VALUE ){ // Existe
		do{
			char	szExt[ MAXEXT ];
			char	szNewName[ MAXPATH ];

			if( stricmp( Win32FD.cFileName, "." ) == 0 ||
			    stricmp( Win32FD.cFileName, ".." ) == 0 ||
				Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ||
				stricmp( Win32FD.cFileName, STOPWORDFILENAME ) == 0 ||	// stopword
				stricmp( Win32FD.cFileName, IDXCONTEXTFILE ) == 0 ) {	// contexto de indexacao total
				// NAO DEVEMOS RENOMEAR
				continue;
			}
			char *szAux = strchr(Win32FD.cFileName, '.');
			if ( szAux ) {
				strcpy( szExt, ".");
				strcat( szExt, szAux+1);
			} else {
				strcpy( szExt, "");
			}

			strupr( szExt );
			sprintf( szPath,"%s\\%s", szDirName, Win32FD.cFileName );
			sprintf( szNewName, "%s\\%s%s", szDirName, (char*) szFileName, szExt );
			if( stricmp( szPath, szNewName ) == 0 ){
				// os nomes sao iguais. entao, pra que renomear?
				continue;
			}
			if( !MoveFile( szPath, szNewName ) ){
				FindClose( Newdir );
				ERETURN( LBSE_ERROR );
			}
		} while( FindNextFile( Newdir, &Win32FD ) );
		FindClose( Newdir );
		ERETURN( LBS_OK );
	}
	FindClose( Newdir );
	ERETURN( LBSE_ERROR );
}
