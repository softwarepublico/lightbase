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
// Module: SESSCL4.CPP
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
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif
#ifndef	_DEFFUNCS_H_
#include	<deffuncs.h>
#endif

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

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
	Metodo Duplicate
	Duplica uma sessao

	Parameters:

	Return:
		Apontador para um novo objeto LBSC_Session.

	Comments:

***/
LBSC_Session *
LBSC_Session::Duplicate()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Duplicate") );
	NRETURN( LBSW_NOTREADY );		// $$$ FALTA IMPLEMENTAR
}


/***
	PUBLIC
	Metodo Compare
	Compara dois objetos session

	Parameters:
		- pAux : apontador para o objeto session a ser comparado com o corrente
		- iType : CMPSESSIONPOINTER - compara o ponteiro do objeto
			  CMPSESSIONISLOGGED - compara o bIsLogged do objeto this com TRUE
			  			(nao usa o objeto pAux)

	Return:
		O resultado da comparacao. ( 0 <=> Objetos iguais )
					   ( != 0 <=> Objetos diferentes )

	Comments:

***/
int
LBSC_Session::Compare( LBSC_Session *pAux, int iType )
{
	switch( iType ){
	case CMPSESSIONISLOGGED:
		SetError( LBS_OK );
		return( this->bIsLogged ? 0 : 1 );
	case CMPSESSIONPOINTER:
		SetError( LBS_OK );
		return( this == pAux ? 0 : 1 );
	default:
		SetError( LBS_OK );
		return( 0 );
	}
}



/***
	PUBLIC
	Metodo LeaveBase
	Retira uma base do arquivo de controle, sem remove-la da arvore de
	diretorios.

	Parameters:
		- plbscTicketPar -> ticket de seguranca
		- szBaseName	 -> o nome fisico da base

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Para usar este metodo, o usuario logado deve ser um MASTER_USER
		  ou o dono da base.

***/
int
LBSC_Session::LeaveBase( const LBSC_Ticket *plbscTicketPar, char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::LeaveBase") );
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
	// verifica o nome da base
	if( !szBaseName || strcmp( szBaseName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	strupr( szBaseName );

	LBSC_Base	*pBase = new LBSC_Base( plbscTicketPar, szBaseName, szBaseName, 
			"$$$", this, TRUE, FALSE, FALSE, FALSE );
	if( !pBase ){
		NRETURN( LBSE_NOMEMORY );
	}
	int	iRet = pBase->LastError();
	if( pBase->BaseObjOk() == FALSE ){ // Nao conseguiu abrir a base
		delete pBase;
		ERETURN( iRet );
	}
	char	*szUDBName = pBase->GetUserBase();
	char	*szOwnerName = pBase->GetOwnerName();
	pBase->InvalidateCache();
	delete pBase;
	pBase = NULL;
	if( !szUDBName || !szOwnerName ){
		// erro doidao
		if( szUDBName ){
			delete szUDBName;
		}
		if( szOwnerName ){
			delete szOwnerName;
		}
		ERETURN( LBSE_BASENOTOPEN );
	}
	// verifica se o cara logado eh um master user:
	if( !bSLogin ){
		if( GetUserType( plbscTicketPar, szUDBName, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara nao eh MASTER_USER. verifica se o cara logado eh o dono da base
			if( stricmp( szOwnerName, (char*) plbscuUser->GetUserName() ) != 0 ){
				// o cara tambem nao eh o dono da base.
				delete szUDBName;
				delete szOwnerName;
				ERETURN( LBSE_NOPERMISSION );
			}
		}
	}
	delete szUDBName;
	delete szOwnerName;
	szUDBName = NULL;
	szOwnerName = NULL;

	// finalmente, vamos remover a base do arquivo de controle

	if ( !pControlFile->Del( szBaseName ) ) {
		// ih, lascou...
		ERETURN( LBSE_ERROR );
	}
	// se nao achamos a base, eh porque ela nao existe mais (talvez outro processo
	// a tenha removido antes deste). De toda forma, eh a situacao que o usuario
	// desejava.
	ERETURN( LBS_OK );
}




/***
	PUBLIC
	Metodo IncorporateBase
	Incorpora uma nova base ao LBS. A base sera' adicionada ao arquivo de controle
	e ligada a uma UDB.

	Parameters:
		- plbscTicketPar -> ticket de seguranca
		- szBaseName	 -> o nome fisico da base
		- szBasePassword -> senha da base (para bases privadas)
		- szUserName	 -> nome do usuario que eh dono da base (para bases privadas)
		- szUDBName	 -> nome da UDB aa qual a base szBaseName vai ser incorporada
				    (se nao for indicado ou for NULL, sera' assimida a UDB
				     atual da base - indicada em LB1)

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo pode ser usado para bases publicas (szBasePassword e szUserName
		  podem ser NULL ou "") e para bases privadas (desde que o usuario szUserName
		  seja o dono da base e szBasePassword seja a senha de uso da base)

***/
int
LBSC_Session::IncorporateBase( const LBSC_Ticket *plbscTicketPar, char *szBaseName, char *szBasePassword, char *szUserName, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::IncorporateBase") );
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
	// verifica os parametros
	if( !szBaseName || strcmp( szBaseName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}

	// montar o nome do diretorio completo, para acessar os arquivos da base
	char	szDirBase[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char	szFullName[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	char	szDrive[ MAXDRIVE ];
	char	szDir[ MAXDIR ];
	char	szName[ MAXFILE ];
	char	szExt[ MAXEXT ];

	// pegar o nome do diretorio base (dir_base)
	LBSC_Base::GetDirBase( szDirBase );

	fnsplit( szBaseName, szDrive, szDir, szName, szExt );
	sprintf( (char*) szFullName, "%s\\%s", szDirBase, szBaseName );
	strupr( szFullName );

	// verifica se a base existe (checar se o diretorio passado
	// existe)
	if( chdir( szFullName ) != 0 ){
		// o cara deu um nome de base que nao existe!
		ERETURN( LBSE_BASENOTFOUND );
	}

	chdir( "\\" );

	// renomeia os arquivos da base para que eles fiquem com o mesmo nome do diretorio.
	// (eh bom ter certeza de que o nome da base esta' coerente com o esquema de nomes
	// usado pelo LBS)
	if( RenameDirFiles( szFullName ) != LBS_OK ){
		// deu pau no rename.
		// temos que abortar o processo.
		ERETURN( LBSE_ERROR );
	}

	fnsplit( szBaseName, szDrive, szDir, szName, szExt );
	sprintf( (char*) szFullName, "%s\\%s\\%s%s", szDirBase, szBaseName, szName, CONTROLFILEEXT );
	strupr( szFullName );

	// verificar a versao da base (na verdade, do arquivo LB1)
	if( LBSC_Base::GetBaseVersion( (char*) szFullName ) < CRYPTO_MAGICNUMBER ){
		// versao 3.
		return( IncorporateBase3( plbscTicketPar, szBaseName, szBasePassword, szUserName, szUDBName ) );
	}
	// versao 4.
	return( IncorporateBase4( plbscTicketPar, szBaseName, szBasePassword, szUserName, szUDBName ) );
}



/***
	PRIVATE
	Metodo CopyDir
	Copia todos os subdiretorios (recursivamente) de um dado diretorio para outro
	ja' existente.

	Parameters:
		- szSourceDir	-> diretorio de origem
		- szDestDir	-> diretorio de destino

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- 

***/
int
LBSC_Session::CopyDir( char *szSourceDir, char *szDestDir, BOOL bOnlyFiles )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CopyDir") );
	char		szPath [ MAXPATH ];
#ifdef __BORLANDC__
		$$$ NAO IMPLEMENTADO PARA O BORLAND $$$
#else
	WIN32_FIND_DATA	Win32FDDir;
	sprintf( szPath, "%s\\*", szSourceDir );
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FDDir );

	if( Newdir != INVALID_HANDLE_VALUE ){ // Existe
		do{
			char	szDrive[ MAXDRIVE ];
			char	szDir[ MAXDIR ];
			char	szName[ MAXFILE ];
			char	szExt[ MAXEXT ];
			char	szDestName[ 5 * MAXPATH ];
			char	szSourceName[ 5 * MAXPATH ];

			fnsplit( Win32FDDir.cFileName, szDrive, szDir, szName, szExt );
			if( strcmp( Win32FDDir.cFileName, "." ) == 0 ||
			    strcmp( Win32FDDir.cFileName, ".." ) == 0 ){
			    	continue;
			}

			BOOL bEhDir = (Win32FDDir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

			if( strcmp( strupr( szExt ), ".LB" ) == 0 || strcmp( strupr( szExt ), CONFFILEEXT ) == 0 ||
				strcmp( strupr( szExt ), ".OL" ) == 0  || (!bEhDir && bOnlyFiles) ){
				// vamos copiar este arquivo tambem.
				sprintf( szSourceName,"%s\\%s", szSourceDir, Win32FDDir.cFileName );

				if ( strcmp( strupr( szExt ), CONFFILEEXT ) == 0 ) {
					for ( int i = strlen(szDestDir)-1; i >= 0; i-- ) {
						if ( szDestDir[i] == '\\' ) {
							i += 1;
							break;
						}
					}
					sprintf( szDestName, "%s\\%s%s", szDestDir, szDestDir+i, CONFFILEEXT );
				} else {
					sprintf( szDestName, "%s\\%s", szDestDir, Win32FDDir.cFileName );
				}
				if ( !CopyFile( szSourceName, szDestName, FALSE ) ) {
					// deu pau 
					FindClose( Newdir );
					ERETURN( LBSE_ERROR );
				}
			    continue;
			}
			if( bEhDir && !bOnlyFiles ){
				// o arquivo encontrado eh um diretorio.
				// vamos copia-lo.
				sprintf( szDestName, "%s\\%s", szDestDir, Win32FDDir.cFileName );
				if( mkdir( szDestName ) != 0 ){
					// deu pau
					FindClose( Newdir );
					ERETURN( LBSE_ERROR );
				}
				// criei o diretorio. agora vou copiar os arquivos dele.
				sprintf( szSourceName, "%s\\%s\\*", szSourceDir, Win32FDDir.cFileName );
				WIN32_FIND_DATA	Win32FDFile;
				HANDLE	NewFile = FindFirstFile( szSourceName, &Win32FDFile );
				if( NewFile == INVALID_HANDLE_VALUE ){
					// deu pau
					FindClose( Newdir );
					ERETURN( LBSE_ERROR );
				}
				// copiando arquivos...
				do{
					fnsplit( Win32FDFile.cFileName, szDrive, szDir, szName, szExt );
					if( Win32FDFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
						// NAO DEVO COPIAR
						continue;
					}
//					sprintf( szSourceName,"%s\\%s\\%s", szSourceDir, szName, Win32FDFile.cFileName );
//					sprintf( szDestName, "%s\\%s\\%s", szDestDir, szName, Win32FDFile.cFileName );
					sprintf( szSourceName,"%s\\%s\\%s", szSourceDir, Win32FDDir.cFileName, Win32FDFile.cFileName );
					sprintf( szDestName, "%s\\%s\\%s", szDestDir, Win32FDDir.cFileName, Win32FDFile.cFileName );
					if( !CopyFile( szSourceName, szDestName, FALSE ) ){
						// deu pau
						FindClose( NewFile );
						FindClose( Newdir );
						ERETURN( LBSE_ERROR );
					}
				} while( FindNextFile( NewFile, &Win32FDFile ) );
				FindClose( NewFile );
				// copiei todos os arquivos. agora vou entrar recursivamente:
				sprintf( szSourceName, "%s\\%s", szSourceDir, Win32FDDir.cFileName );
				sprintf( szDestName, "%s\\%s", szDestDir, Win32FDDir.cFileName );
				int iAux = CopyDir( szSourceName, szDestName );
				if ( iAux != LBS_OK ) {
					FindClose( Newdir );
					ERETURN( LBSE_ERROR );
				}
			}
		} while( FindNextFile( Newdir, &Win32FDDir ) );
		FindClose( Newdir );
		ERETURN( LBS_OK );
	}
#endif
	ERETURN( LBSE_ERROR );
}



/***
	STATIC PUBLIC
	Metodo RebuildControl
	Reconstroi o arquivo de controle do LBS a partir da arvore de bases existentes.

	Parameters:
		- szServer -> nome do servidor. So' eh usado nos stubs de rede. Para
				o LBS nao faz sentido.

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- este metodo checa a arvore de diretorios a partir do dir_base
		  recursivamente aa procura de bases LBS
***/
int
LBSC_Session::RebuildControl( char * /*szServer*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::RebuildControl") );
	char		szFullAux[ FULLNAMESIZE ];
	char		szAux[ FILENAMESIZE ];

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetLastError( (DWORD) (LBSE_INVALIDLIC | 0x20000000) );
		return( LBSE_INVALIDLIC );
	}

	// obtem o nome do arquivo de controle em LBS.INI
	if( GetFNameOnProfile( szFullAux, szAux ) != LBS_OK ){
		SetLastError( (DWORD) (LBSE_LBSINIERROR | 0x20000000) );
		return( LBSE_LBSINIERROR );
	}

	// (re)cria o arquivo de controle
	char		szFNameAux[ FULLNAMESIZE ];

	C_SessCritSect	cCS4( NULL, CRITSECT4 );

	sprintf( szFNameAux, "%s%s%s", szFullAux, "\\", szAux );
	C_RecordFile	cfBasesFile( szFNameAux, CRYPTO_MAGICNUMBER, 0, 
								 sizeof( TBasesFile ), "HEADKEY", 
								 "RECKEY", "w", SH_DENYRW, TRUE );
	if( !cfBasesFile.IsOpen() ){
		SetLastError( (DWORD) (LBSE_NOBASESFILE | 0x20000000) );
		return( LBSE_NOBASESFILE );
	}
	cfBasesFile.R_Seek( 0 );

	// insere as bases encontradas no arquivo de controle.
	// o metodo abaixo eh o responsavel pela leitura da arvore de diretorios
	// recursivamente.
	int iRet = LBSC_Session::InsertBasesInControlFile( cfBasesFile, szFullAux );

	cfBasesFile.Close();
	SetLastError( (DWORD) (iRet | 0x20000000) );
	return( iRet );
}
