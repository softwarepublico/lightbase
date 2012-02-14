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
// Module: SESSCL2.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//				Alessandro Araujo Jatoba'
//
// Last update: 20/01/96
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



/***
	PUBLIC
	Metodo GetUserName
	Obtem o nome do usuario que esta' logado

	Parameters:
		-

	Return:
		- O nome do usuario.

	Comments:
		- Este metodo NAO retorna uma copia do buffer interno.

***/
const char *
LBSC_Session::GetUserName()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserName") );
	// $$$ Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		NRETURN( LBSE_USERNOTLOGGED );
	}

	SetError( LBS_OK );
	return( plbscuUser->GetUserName() );
}


/***
	PUBLIC
	Metodo IsLogged
	Verifica se o usuario esta logado

	Parameters:

	Return:
		O status.

	Comments:

***/
BOOL
LBSC_Session::IsLogged()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IsLogged") );
	SetError( LBS_OK );
	return( bIsLogged );
}


/***
	PUBLIC
	Metodo IsMono
	Verifica se o usuario esta logado em modo mono-usuario

	Parameters:

	Return:
		O status.

	Comments:

***/
BOOL
LBSC_Session::IsMono()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IsMono") );
	SetError( LBS_OK );
	return( bIsMono );
}


/***
	PRIVATE
	Metodo FindUser
	Procura um usuario e sua password em uma BU.

	Parameters:
		- plbscbUserBase	-> apontador para a BU, que ja deve estar
					   aberta. ao final, deixa a base posicionada no usuario encontrado
		- szUserName		-> nome do usuario a ser procurado
		- szUserPassword	-> senha do usuario

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- 

***/
int
LBSC_Session::FindUser( LBSC_Base *plbscbUserBase, const char *szUserName, const char *szUserPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::FindUser") );
	UserSTR		strUserNameAux;
	PswdSTR		strPasswdAux;

	if( !plbscbUserBase || !szUserName || !szUserPassword ){
		ERETURN( LBSE_BADARG );
	}
	// procurar  usuario
	strUserNameAux = szUserName;
	strUserNameAux.Upper();

	LBSC_Field	*pf = (*plbscbUserBase)[ USERBASEUSERNAME ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	if( plbscbUserBase->Locate( plbsctTicket, pf->GetId(), ENTIRETREE, (char*) strUserNameAux ) != LBS_OK ){
		// o usuario na existe
		ERETURN( LBSE_USERNOTFOUND );
	}
	// Checar a password
	strPasswdAux = szUserPassword;
	strPasswdAux.Upper();

	pf = (*plbscbUserBase)[ USERBASEUSERPASSWORD ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	LBSC_Data	*pcData = (*pf)[ 0 ];
	if( pcData ){
		// so' comparar a password do cara, se ela existir na UDB.
		// o cara pode ter sido cadastrado sem senha, caso este em
		// que nao eh necessario verifica-la.
		if( stricmp( (char *) (*pcData), (char *) strPasswdAux ) != 0 ){
			// a password nao bateu
			ERETURN( LBSE_INVALIDPASSWORD );
		}
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}


/***
	PRIVATE
	Metodo FindUser
	Procura um usuario e sua password em uma BU.

	Parameters:
		- szUserBase		-> nome da BU
		- szUserName		-> nome do usuario a ser procurado
		- szUserPassword	-> senha do usuario

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- 

***/
int
LBSC_Session::FindUser( const char *szUserBase, const char *szUserName, const char *szUserPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::FindUser") );
	UserSTR		strUserNameAux;
	PswdSTR		strPasswdAux;

	if( !szUserBase || !szUserName || !szUserPassword ){
		ERETURN( LBSE_BADARG );
	}
	// procurar  usuario
	strUserNameAux = szUserName;
	strUserNameAux.Upper();

	if ( FindUserInCache( strUserNameAux, "", NULL ) < 0 ) {
		// o usuario na existe
		ERETURN( LBSE_USERNOTFOUND );
	}
	// Checar a password
	strPasswdAux = szUserPassword;
	strPasswdAux.Upper();

	if ( FindUserInCache( strUserNameAux, strPasswdAux, szUserBase ) < 0 ) {
			// a password nao bateu
		ERETURN( LBSE_INVALIDPASSWORD );
	}
	ERETURN( LBS_OK );
}


/***********************/
int
RemoveFile( char *szMask, ... )
{
	char 	szBuffer [ MAXPATH ];
	va_list argptr;
	int 	cnt;

	va_start( argptr, szMask );
	cnt = vsprintf( szBuffer, szMask, argptr );
	va_end( argptr );

	remove( szBuffer );

	return( cnt );
}

/***********************/
int
RenameFile( char *szMask, ... )
{
	char 	szBuffer [ 2 * MAXPATH + 1 ];
	va_list argptr;
	int 	cnt;

	va_start( argptr, szMask );
	cnt = vsprintf( szBuffer, szMask, argptr );
	va_end( argptr );

	char *p = strchr( szBuffer, ' ' );
	p [ 0 ] = '\0';
	p++;

	rename( szBuffer, p );

	return( cnt );
}

/***
	PUBLIC
	Metodo ReorganizeBase
	Reorganiza os arquivos de uma base

	Parameters:
		- plbscTicketPar	-> ticket de seguranca
		- plbscBase		-> ponteiro para uma base ja aberta

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- A base a ser reorganizada deve estar aberta em modo exclusivo
		  e nao deve estar em modo ReadOnly
		- Esta operacao pode ser demorada
		- Algoritmo:
			1.  testa condicoes de uso (read-only, manutencao, permissoes, etc.)
			2.  monta um diretorio de trabalho1
			3.  modifica o nome do usuario logado para que fique igual ao
			    nome do dono da base. isso serve para evitar problemas de
			    permissao nas operacoes seguintes
			4.  cria uma base auxiliar em trabalho1
			5.  copia todos os subdiretorios da base original para o diretorio
			    trabalho1
			6.  copia algumas informacoes do header da base original 
			    para o da base trabalho1
			7.  copia os slots de base e de campos da base original para
			    a base trabalho1
			8.  copia os contadores
			9.  copia todos os registros validos
			10. fecha as duas bases (a original e a trabalho1)
			11. cria um diretorio temporario trabalho2
			12. copia os arquivos da base original para trabalho2
			    (inclusive os subdiretorios que por acaso existirem,
			     que nao sao da conta do LBS)
			13. copia os arquivos de trabalho1 para o diretorio original
			14. remove trabalho2

***/
int
LBSC_Session::ReorganizeBase( const LBSC_Ticket *plbscTicketPar, LBSC_Base *plbscBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReorganizeBase") );
	// simplesmente repassa a bola para o metodo ReprocBase
	int iRet = ReprocBase( plbscTicketPar, plbscBase );
	ERETURN( iRet );
}


