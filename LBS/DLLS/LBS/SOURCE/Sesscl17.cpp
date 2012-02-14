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
// Module: SESSCL17.CPP
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
#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif
#ifndef	_DEFFUNCS_H_
#include	<deffuncs.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
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
	STATIC PRIVATE
	Metodo InsertBasesInControlFile
	Grava informacoes no arquivo de controle do LBS a partir da arvore de bases existentes.

	Parameters:
		- cfBasesFile	-> arquivo de controle, ja' aberto
		- szSourceDir	-> diretorio a partir de onde o metodo ira' trabalhar.

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- este metodo checa a arvore de diretorios a partir do dir_base
		  recursivamente aa procura de bases LBS
***/
int
LBSC_Session::InsertBasesInControlFile( C_RecordFile &cfBasesFile, char *szSourceDir )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::InsertBasesInControlFile") );
	if( !szSourceDir || !cfBasesFile.IsOpen() ){
		return( LBSE_BADARG );
	}
	// vamos procurar as bases no diretorio
	char		szPath [ 5 * MAXPATH ];
	WIN32_FIND_DATA	Win32FDDir;
	sprintf( szPath, "%s\\*", szSourceDir );
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FDDir );

	if( Newdir == INVALID_HANDLE_VALUE ){ // Nenhum arquivo encontrado!
		return( LBSE_ERROR );
	}
	do{
		char		szSourceName[ 5 * MAXPATH ];
		char		szFullBaseName[ 5 * MAXPATH ];

		// sessao auxiliar para poder chamar metodos nao estaticos
		LBSC_Session	csSessionAux;

		if( strcmp( Win32FDDir.cFileName, "." ) == 0 ||
		    strcmp( Win32FDDir.cFileName, ".." ) == 0 ){
		    	continue;
		}
		if( Win32FDDir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
			// o arquivo encontrado eh um diretorio.
			// vamos ver se esse diretorio representa uma base
			char	szDrive[ MAXDRIVE ];
			char	szDir[ MAXDIR ];
			char	szName[ MAXFILE ];
			char	szExt[ MAXEXT ];
			char	szBaseDir[ FILENAMESIZE ];

			LBSC_Base::GetDirBase( szBaseDir );
			fnsplit( szSourceDir, szDrive, szDir, szName, szExt );

			strupr( szBaseDir );
			strupr( szSourceDir );

			if( strcmp( szBaseDir, szSourceDir ) != 0 && strlen( szName ) > 0 ){
				sprintf( szFullBaseName, "%s\\%s", szName, Win32FDDir.cFileName );
			} else {
				strcpy( szFullBaseName, Win32FDDir.cFileName );
			}

			long lSize = csSessionAux.GetPrivateSlotSize( szFullBaseName );
			if( lSize < 0 ){
				// deu pau. provavelmente esse arquivo nao eh uma base LBS.
				// vamos para adiante.
				continue;
			}
			char	*szSlot = new char[ lSize + 1 ];
			if( !szSlot ){
				// deu pau. vamos adiante.
				continue;
			}
			memset( szSlot, 0, lSize + 1 );
			if( csSessionAux.GetPrivateSlotInfo( szFullBaseName, szSlot ) != LBS_OK ){
				// deu pau. vamos adiante.
				delete szSlot;
				continue;
			}
			if( strcmp( szSlot, "LBSBASE" ) != 0 ){
				// nao eh uma base LBS. vamos adiante.
				delete szSlot;
				continue;
			}
			delete szSlot;

			// vamos inserir o nome no arquivo de controle.
			TBasesFile	tbfAux;
			tbfAux.szBaseName = szFullBaseName;
			strupr( (char*) tbfAux.szBaseName );
			tbfAux.szBaseLongName = (char*) tbfAux.szBaseName;
			char	*szAux = csSessionAux.GetUDBName( szFullBaseName );
			tbfAux.szUserBaseName = szAux;
			strupr( (char*) tbfAux.szUserBaseName );
			if( szAux ){
				delete szAux;
			}
			tbfAux.bRecDeleted = FALSE;
			tbfAux.bBaseType = csSessionAux.GetBaseType( szFullBaseName );
			cfBasesFile.R_Append( &tbfAux );

			// agora vamos entrar no diretorio para procurarmos outras bases.
			sprintf( szSourceName, "%s\\%s", szSourceDir, Win32FDDir.cFileName );
			InsertBasesInControlFile( cfBasesFile, szSourceName );
		}
		// vamos para o proximo
	} while( FindNextFile( Newdir, &Win32FDDir ) );
	FindClose( Newdir );
	return( LBS_OK );
}



/***
	PRIVATE
	Metodo RenameDirFiles
	Renomeia arquivos para que fiquem com nomes iguais ao de um diretorio

	Parameters:
		- szDirName	-> nome do diretorio (indica o nome da base)

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- Este metodo NAO eh recursivo.
		- Os arquivo renomeados permanecerao com suas extensoes originais; apenas
		  os nomes serao alterados.

***/
int
LBSC_Session::RenameDirFiles( char *szDirName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::RenameDirFiles") );
	char			szPath [ MAXPATH ];		// caminho completo
	char			szDirect [ MAXPATH ];	// ultimo nome do diretorio
	char			szDrive[ MAXDRIVE ];	// drive
	char			szDir[ MAXDIR ];		// diretorio sem o ultimo nome
	char			szNewName[ MAXFILE ];	// novo nome do arquivo, depois de renomeado
	char			szExt[ MAXEXT ];		// extensao do arquivo
	WIN32_FIND_DATA	Win32FD;				// estrutura usada para pesquisar arquivos

	// extrair o ultimo nome do diretorio
	fnsplit( szDirName, szDrive, szDir, szDirect, szExt );

	// construir um nome completo de diretorio para tornar possivel
	// a pesquisa nos diretorios
	sprintf( szPath, "%s\\*", szDirName );

	// pega o primeiro nome de arquivo do diretorio szDirName
	// (o nome obtido pode ser um arquivo, um diretorio ou "." ou ".."
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FD );

	if( Newdir != INVALID_HANDLE_VALUE ){ // Existe
		do{

			if( stricmp( Win32FD.cFileName, "." ) == 0 ||
			    stricmp( Win32FD.cFileName, ".." ) == 0 ||
				Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ||
				stricmp( Win32FD.cFileName, STOPWORDFILENAME ) == 0 ||	// stopword
				stricmp( Win32FD.cFileName, IDXCONTEXTFILE ) == 0 ) {	// contexto de indexacao total
				// NAO DEVEMOS RENOMEAR
				continue;
			}
			// pegamos um arquivo. vamos verificar seu nome
			char *szAux = strchr(Win32FD.cFileName, '.');
			if ( szAux ) {
				strcpy( szExt, ".");
				strcat( szExt, szAux+1);
			} else {
				strcpy( szExt, "");
			}
			strupr( szExt );

			sprintf( szPath,"%s\\%s", szDirName, Win32FD.cFileName );
			sprintf( szNewName, "%s\\%s%s", szDirName, (char*) szDirect, szExt );
			if( stricmp( szPath, szNewName ) == 0 ){
				// os nomes sao iguais. entao, pra que renomear?
				continue;
			}
			// bom, vamos renomear o danado do arquivo encontrado:
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


/***
	static PUBLIC
	Metodo GetDefUserBaseName
	Obtem o nome da default user base

	Parameters:
		- szServerName	-> nome do servidor. dummy aqui no LBS,
						   pois so' interessa aos stubs c/s

	Return:
		- o nome da default user base ou NULL para indicar erro

	Comments:
		- a aplicacao DEVE deletar a string retornada (este metodo retorna
		  uma copia)

***/
char *
LBSC_Session::GetDefUserBaseName( char * /*szServerName*/)
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetDefUserBaseName") );
	return( Strdup( _szDefUDBName ) );
}



/***
	Metodo ClearBase
	Limpa todos os registros da base

	Parameters:
		- pTicket	-> ticket de seguranca
		- szBaseName	-> nome da base

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- Este metodo elimina fisicamente todos os registros. Eh diferente
		  de usar o DeleteRecord para todos os registros ou o DeleteOcList
		  para a lista fisica.

***/
int
LBSC_Session::ClearBase( const LBSC_Ticket *pTicket, char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ClearBase") );
	LBSC_Base	*plbscbBase;

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	strupr( szBaseName );
	plbscbBase = new LBSC_Base( szBaseName );
	if( plbscbBase == NULL ){
		// deu pau
		ERETURN( LBSE_NOMEMORY );
	}

	// verifica se a base esta' aberta
	if( lbscblBaseList.Find( plbscbBase, CMPBASENAME ) != NULL ){
		// a base esta' aberta
		delete plbscbBase;
		ERETURN( LBSE_BASEOPEN );
	}
	delete plbscbBase;

	// Abrir a base em modo exclusivo
	// (se falhar eh porque ha alguem usando a base e nao posso deleta-la)
	plbscbBase = new LBSC_Base( pTicket, szBaseName, this, TRUE, FALSE );
	if( plbscbBase == NULL ){
		// deu pau
		ERETURN( LBSE_NOMEMORY );
	}
	if( plbscbBase->BaseObjOk() == FALSE ){
		// nao consegui abrir a base
		delete plbscbBase;
		ERETURN( LBSE_ERROR );
	}

	// inserir a base na lista de bases, porque o ReprocBase precisa disso.
	C_SessCritSect	cCS0( this, CRITSECT0 );
	lbscblBaseList.Add( plbscbBase, AFTER );

	// Consegui abrir a base em modo exclusivo e, portanto, posso usa-la sem problemas.
	// agora eh so' chamar o metodo de reprocessamento de base, sem copiar os registros,
	// como eh feito pelo ReorganizeBase.
	int iRet = ReprocBase( pTicket, plbscbBase, FALSE );

	// retirar a base da lista de bases.
	// podemos deletar o elemento corrente da lista com seguranca, pois
	// estamos em regiao critica.
	lbscblBaseList.Del();

	// fecha a base
	delete plbscbBase;

	// retorna o resultado do ReprocBase
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo ChangeUDB
	Troca a UDB de uma base

	Parameters:
		- plbscTicketPar -> ticket de seguranca
		- szBaseName	 -> o nome fisico da base
		- szBasePassword -> senha da base (para bases privadas)
		- szUserName	 -> nome do usuario que eh dono da base (para bases privadas)
		- szUDBName	 -> nome da nova UDB (se for NULL, sera' assumida a DEFUDB)

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo pode ser usado para bases publicas (szBasePassword e szUserName
		  podem ser NULL ou "") e para bases privadas (desde que o usuario szUserName
		  seja o dono da base e szBasePassword seja a senha de uso da base)

***/
int
LBSC_Session::ChangeUDB( const LBSC_Ticket *plbscTicketPar, char *szBaseName, char *szBasePassword, char *szUserName, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ChangeUDB") );
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
	// verifica os parametros
	if( !szBaseName || strcmp( szBaseName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	char	szDirBase[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char	szFullName[ PATHNAMESIZE + FILENAMESIZE + 10 ];

	C_SessCritSect	cCS4( this, CRITSECT4 );

	const TBasesFile	*ptbfAux = pControlFile->Get( szBaseName );
	if ( !ptbfAux ) {
		ERETURN( LBSE_BASENOTFOUND );
	}

	// pegar o nome do diretorio base (dir_base)
	LBSC_Base::GetDirBase( szDirBase );

	// montar o nome do diretorio completo, para acessar os arquivos da base
	char	szDrive[ MAXDRIVE ];
	char	szDir[ MAXDIR ];
	char	szName[ MAXFILE ];
	char	szExt[ MAXEXT ];
	fnsplit( szBaseName, szDrive, szDir, szName, szExt );
	sprintf( (char*) szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, CONTROLFILEEXT );
	strupr( szFullName );

	// abre LB1 para verificar o tipo da base e a sua senha e o nome do usuario, se
	// for necessario
	if( !C_LB1::Exist( szFullName ) ){
		// o cara deu um nome de base que nao existe!
		ERETURN( LBSE_BASENOTFOUND );
	}
	C_LB1	cfLB1;
	if( cfLB1.Open( szFullName, NULL ) != OK ){
		// nao consegui abrir cfLB1
		ERETURN( LBSE_FILEERROR );
	}
	// checa o tipo da base
	if( cfLB1.tcrHead.bBaseType != BASE_PUBLIC && cfLB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ){
		// temos que comparar o nome do usuario e a senha da base
		if( !szBasePassword || !szUserName || 
		    strcmp( szBasePassword, "" ) == 0 ||
		    strcmp( szUserName, "" ) == 0 ){
		    	cfLB1.Close();
		    	ERETURN( LBSE_BADARG );
		}
		if( stricmp( (char*) cfLB1.tcrHead.szBasePassword, szBasePassword ) != 0 ){
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
	char	szUserBaseName[ FILENAMESIZE ];
	BYTE	bBaseType = cfLB1.tcrHead.bBaseType;
	BOOL	bEncrypt = cfLB1.tcrHead.bIsEncrypt;
	strcpy( szUserBaseName, bBaseType == USER_BASE ? "" : szUDBName ? szUDBName : _szDefUDBName );
	strupr( szUserBaseName );
	if( strcmp( szUserBaseName, "" ) == 0 && cfLB1.tcrHead.bBaseType != USER_BASE ){
		// nome invalido para UDB
		cfLB1.Close();
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// vamos abrir a UDB para obter seu numero de identificacao (numero de link)
	LBSC_Base	*pUDB = new LBSC_Base( plbscTicketPar, szUserBaseName, this );
	if( !pUDB ){
		cfLB1.Close();
		NRETURN( LBSE_NOMEMORY );
	}
	if( pUDB->BaseObjOk() == FALSE ){ // Nao consegui abrir a UDB
		delete pUDB;
		cfLB1.Close();
		ERETURN( LBSE_INVALIDUSERBASE );
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

	// atualizar, na base szBaseName, o nome da UDB e o link
	cfLB1.tcrHead.szUserBase = szUserBaseName;
	cfLB1.tcrHead.dwUserBaseId = pUDB->LB1.tcrHead.dwBaseId;

	// grava o header de LB1 de szBaseName
	cfLB1.LB1_WriteHead();

	// atualiza a copia de seguranca do header de LB1
	cfBak.R_WriteHead( &cfLB1.tcrHead );
	cfBak.Close();

	// fecha LB1 de szBaseName
	cfLB1.Close();

	// fecha a UDB
	delete pUDB;
	pUDB = NULL;

	// agora vamos atualizar o arquivo de controle. 
	TBasesFile	tbfAux = (*(TBasesFile *)ptbfAux);
	tbfAux.szUserBaseName = szUserBaseName;
	if ( !pControlFile->Set( tbfAux ) ) {
		// deu pau
		ERETURN( LBSE_ERROR );
	}
	ERETURN( LBS_OK );
}

