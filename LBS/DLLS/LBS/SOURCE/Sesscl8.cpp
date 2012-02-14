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
// Module: SESSCL8.CPP
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



EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo CloseBase
	Fecha uma base de dados

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- plbscbBase

	Return:
		LBS_OK se conseguir fechar ou erro.

	Comments:

***/
int
LBSC_Session::CloseBase( const LBSC_Ticket *plbscTicketPar, LBSC_Base *plbscbBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::CloseBase") );
	// $$$ Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// $$$ Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	C_SessCritSect	cCS0( this, CRITSECT0 );
	lbscblBaseList.First();
	if( lbscblBaseList.Find( plbscbBase, CMPBASEPOINTER ) != NULL ){
		lbscblBaseList.Refresh( NULL );
		ReturnBaseHandler( plbscbBase );
		lbscblBaseList.Del();
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_BASENOTFOUND );
}


#ifdef __BORLANDC__
#pragma warn -par
#endif
/***
	PUBLIC
	Metodo DeleteBase
	Apaga fisicamente uma base de dados

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- szFullBaseName

	Return:
		LBS_OK se conseguir deletar ou erro.

	Comments:
		- Uma base so pode ser deletada se nao estiver aberta por ninguem
		  e se o usuario logado for seu dono.
		- Este metodo nao pede confirmacao.

***/
int
LBSC_Session::DeleteBase( const LBSC_Ticket *plbscTicketPar, char *szFullBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DeleteBase") );
#ifdef LBS_DEBUG
	Printf( "Estou em DeleteBase" );
#endif // LBS_DEBUG
	char		szAux[ FILENAMESIZE ];
	char		szFullAux[ FULLNAMESIZE ];

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

	strupr( szFullBaseName );
	LBSC_Base	*plbscbBase = new LBSC_Base( szFullBaseName );
	if( plbscbBase == NULL ){
		// deu pau
		ERETURN( LBSE_NOMEMORY );
	}

	if( lbscblBaseList.Find( plbscbBase, CMPBASENAME ) != NULL ){
		delete plbscbBase;
		ERETURN( LBSE_BASEOPEN );
	}
	delete plbscbBase;

	// verifica se a base existe.
	char	szDrive[ MAXDRIVE ];
	char	szDir[ MAXDIR ];
	char	szName[ MAXFILE ];
	char	szExt[ MAXEXT ];
	fnsplit( szFullBaseName, szDrive, szDir, szName, szExt );
	LBSC_Base::GetDirBase( szAux );
	sprintf( (char*) szFullAux, "%s\\%s\\%s%s", szAux, szFullBaseName, szName, CONTROLFILEEXT );
	strupr( szFullAux );

	if( !C_LB1::Exist( szFullAux ) ){
		// o cara deu um nome de base que nao existe!
		ERETURN( LBSE_BASENOTFOUND );
	}

	// Abrir a base em modo exclusivo
	// (se falhar eh porque ha alguem usando a base e nao posso deleta-la)
	// forcando a nao verificacao de versao...
	plbscbBase = new LBSC_Base( plbscTicketPar, szFullBaseName, szFullBaseName, 
			"$$$", this, TRUE, FALSE, FALSE, FALSE );
	if( plbscbBase == NULL ){
		// deu pau
		ERETURN( LBSE_NOMEMORY );
	}
	int	iRet = plbscbBase->LastError();
	if( plbscbBase->BaseObjOk() == FALSE ){
		// nao consegui abrir a base
		delete plbscbBase;
		ERETURN( iRet );
	}

	// Consegui abrir a base em modo exclusivo e, portanto, posso deleta-la.

	// TESTAR SE O USR EH O DONO DA BASE
	if( stricmp( (char*) plbscuUser->GetUserName(), (char*) plbscbBase->LB1.tcrHead.szOwnerName ) == 0 || 
		bSLogin ){
		// Pegar o nome da UDB para uso posterior
		char *szUDBName = plbscbBase->GetUserBase();

		// Deletar fisicamente a base
		plbscbBase->Delete();
		delete plbscbBase;

		C_SessCritSect	cCS4( this, CRITSECT4 );

		// remover a base dos campos USERBASEACCESSBASES
		// e USERBASEACCESSTYPES da BU, para todos
		// os usuarios.
		DelBaseOfUDB( szFullBaseName, szUDBName, NULL );
		if( szUDBName ){
			delete szUDBName;
		}
		if( !pControlFile->Del( szFullBaseName ) ){
			ERETURN( LBSE_ERROR );
		}
		// NULL no 3o parametro indica TODOS OS USUARIOS
		ERETURN( LBS_OK );
	}
	// usuario nao eh o dono da base. fechar a base.
	if( plbscbBase ){
		delete plbscbBase;
	}
	ERETURN( LBSE_USERNOTOWNERBASE );
}
#ifdef __BORLANDC__
#pragma warn +par
#endif

/***
	PUBLIC
	Metodo Export
	Exporta uma lista de bases

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- plbscbnlExportBaseList	-> lista das bases que serao exportadas
		- szImportPsw			-> senha para importacao das bases
		- szFullExportFileName		-> nome completo do arquivao que vai ser gerado
		- bChangeOwnerName		-> indica se o nome do dono das bases deve mudar

	Return:
		- LBS_OK se conseguir exportar todas as bases ou erro.

	Comments:
		-

***/
int
LBSC_Session::Export( const LBSC_Ticket *plbscTicketPar, LBSC_ExportBaseList *plbscbnlExportBaseList,
			char *szImportPsw, char *szFullExportFileName, BOOL bChangeOwnerName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Export") );
	LBSC_BaseList	*plbscblBaseList;
	LBSC_Base	*plbscbBase;
	long		lPos;
	int		iBaseNumber;
	int		iRet;

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// Verifica a validade da lista de bases para exportacao
	if( plbscbnlExportBaseList == NULL ){
		ERETURN( LBSE_ERROR );
	}
	// Verifica a validade do nome do arquivo de exportacao
	if( ( szFullExportFileName == NULL ) || ( szFullExportFileName[0] == '\0' ) ){
		ERETURN( LBSE_ERROR );
	}
	// Verifica a validade da password de exportacao
	if( ( szImportPsw == NULL ) || ( szImportPsw[0] == '\0' ) ){
		ERETURN( LBSE_ERROR );
	}
	strupr( szImportPsw );
	strupr( szFullExportFileName );
	plbscblBaseList = new LBSC_BaseList;

	plbscbnlExportBaseList->First();
	do{
		// Tentar abrir em modo exclusivo
		plbscbBase = new LBSC_Base( plbsctTicket, (char *) plbscbnlExportBaseList->Current()->GetBaseName(),
			 (char *) plbscbnlExportBaseList->Current()->GetBaseLongName(),
			 (char *) plbscbnlExportBaseList->Current()->GetBasePassword(),
			 this, TRUE, FALSE, TRUE );
		if( plbscbBase == NULL ){
			delete plbscblBaseList;
			ERETURN ( LBSE_ERROR );
		}

		iRet = plbscbBase->BaseObjOk();
		if( !iRet ){
			// Nao conseguiu abrir a base
			delete plbscblBaseList;
			delete plbscbBase;
			ERETURN ( LBSE_ERROR );
		}
		if( !plbscbBase->IsExportable() ){
			// Base nao pode ser exportada
			delete plbscblBaseList;
			delete plbscbBase;
			ERETURN ( LBSE_NOTEXPORTABLEBASE );
		}

		// Checar se o usr eh o dono da base
		if( stricmp( plbscuUser->GetUserName(), plbscbBase->GetConstOwnerName() ) != 0 ){
			delete plbscblBaseList;
			delete plbscbBase;
			ERETURN ( LBSE_ERROR );
		}

		plbscblBaseList->Add( plbscbBase, AFTER );
	} while ( plbscbnlExportBaseList->Next() != NULL );

	// Abrir arquivo de exportacao
	C_File		cfExportFile( szFullExportFileName, "wb" );

	if( cfExportFile.IsOpen() == FALSE ){
		delete plbscblBaseList;
		ERETURN ( LBSE_ERROR );
	}

	// Gravar o cabecalho do arquivo de exportacao
	if( WriteImpExpFileHeader( &cfExportFile, 
				    szImportPsw, 
				    bChangeOwnerName, 
				    plbscbnlExportBaseList->NumElem() ) != LBS_OK ){
		delete plbscblBaseList;
		ERETURN ( LBSE_ERROR );
	}

	// Exportar as bases
	plbscblBaseList->First();
	plbscbnlExportBaseList->First();
	iBaseNumber = 0;	// Para posicionar no inicio
	long lPos1; // para depuracao
	do{
		// Gravar o endereco inicial da base no cabecalho
		lPos = cfExportFile.CurPos();			// Guardar o endereco inicial da base
		cfExportFile.Seek( sizeof( TImpExpFileHeader ) + ( iBaseNumber * sizeof( long ) ), SEEK_SET ); // Posicionar arquivo
		lPos1 = cfExportFile.CurPos();
		if( cfExportFile.Write( &lPos, sizeof( long ) ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		iBaseNumber++;
		cfExportFile.Seek( lPos, SEEK_SET );	// Reposicionar arquivo
		lPos1 = cfExportFile.CurPos();
		// Exportar a base
		if( plbscblBaseList->Current()->Export( plbscTicketPar, &cfExportFile,
		    plbscbnlExportBaseList->Current()->IsExportable() ) != LBS_OK ){
		    	// nao conseguimos exportar a base.
			// temos que abortar o proccesso.
			delete plbscblBaseList;
			ERETURN ( LBSE_ERROR );
		}
		CloseBase( plbscTicketPar, plbscblBaseList->Current() );
		plbscbnlExportBaseList->Next();
	}while( plbscblBaseList->Next() != NULL );

	// Deletar a lista de bases temporaria
	delete plbscblBaseList;

	ERETURN( LBS_OK );
}

/***
	PRIVATE
	Metodo WriteImpExpFileHeader
	Grava o cabecalho do arquivo de importacao

	Parameters:
		- plbscsnlSerialNumberList
		- szImportPsw
		- bChangeOwnerName
		- pcfExportFile

	Return:
		LBS_OK se conseguir gravar ou erro.

	Comments:

***/
int
LBSC_Session::WriteImpExpFileHeader( C_File *pcfExportFile, char *szImportPsw,
				     BOOL bChangeOwnerBase, int iNumberOfBases )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::WriteImpExpFileHeader") );
	TImpExpFileHeader	tiefhHeader;

	tiefhHeader.strImportPsw = szImportPsw;
	tiefhHeader.bChangeOwnerBase = bChangeOwnerBase;
	tiefhHeader.iNumberOfBases = iNumberOfBases;
	if( pcfExportFile->Write( &tiefhHeader, sizeof( tiefhHeader ) ) != OK ){
		ERETURN( LBSE_ERROR );
	}

	// Guardar espaco para o endereco inicial de cada base dentro do arquivao
	long lAux = 0;
	for( int x = 1; x <= iNumberOfBases; x++ ){
		if( pcfExportFile->Write( &lAux, sizeof( long ) ) != OK ){
			ERETURN( LBSE_ERROR );
		}
	}
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo Import
	Importa bases a partir de um arquivo no formato pre-definido de importacao

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- szNewOwnerName
		- szNewBasePassword
		- szImportPsw
		- szFullImportFileName
		- szUserBase

	Return:
		LBS_OK se conseguir importar todas as bases ou erro.

	Comments:

***/
int
LBSC_Session::Import( const LBSC_Ticket *plbscTicketPar, char *szNewOwnerName, char *szNewBasePassword,
			char *szNewMaintenanceBasePassword,
			char *szImportPsw, char *szFullImportFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Import") );
	int			iBasesNumber;
	long			lNextPos;
	TImpExpFileHeader	tiefhHeader;

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	// Abrir arquivo de importacao
	C_File	cfImportFile( szFullImportFileName, "rb" );
	if( cfImportFile.IsOpen() == FALSE ){
		ERETURN( LBSE_ERROR );
	}

	// Ler o cabecalho do arquivo de importacao
	if( cfImportFile.Read( &tiefhHeader, sizeof( TImpExpFileHeader ) ) != OK ){
		ERETURN( LBSE_ERROR );
	}

	// Checar password do arquivo de importacao
	tiefhHeader.strImportPsw.Upper();
	strupr( szImportPsw );
	if( tiefhHeader.strImportPsw != szImportPsw ){
		ERETURN( LBSE_INVALIDPASSWORD );
	}

	// Checar se DEVE mudar o dono da base
	if( tiefhHeader.bChangeOwnerBase &&
	    (!szNewOwnerName || !szNewBasePassword || !szNewMaintenanceBasePassword )){
		// a exportacao indicou que nome+passwd do dono
		// deveriam ser trocados, mas a importacao
		// nao recebeu nome+passwd do novo dono.
		ERETURN( LBSE_BADARG );
	}

	// Ler numero de bases a ser importadas
	iBasesNumber = tiefhHeader.iNumberOfBases;

	// Importar as bases uma a uma
	cfImportFile.Seek( sizeof( TImpExpFileHeader ), SEEK_SET );
	cfImportFile.Read( &lNextPos, sizeof( long ) );
	cfImportFile.Seek( lNextPos, SEEK_SET );

	while( iBasesNumber ){
		if( ImportBase( plbscTicketPar, &cfImportFile, tiefhHeader.bChangeOwnerBase, 
				szNewOwnerName, szNewBasePassword, 
				szNewMaintenanceBasePassword )  != LBS_OK ){
			// Deu erro na importacao. Pegar posicao da proxima base
			if( iBasesNumber - 1 ){
				cfImportFile.Seek( sizeof( TImpExpFileHeader ) +
						   ( ( tiefhHeader.iNumberOfBases - iBasesNumber )
						    * sizeof( long ) ), SEEK_SET );
				cfImportFile.Read( &lNextPos, sizeof( long ) );
				cfImportFile.Seek( lNextPos, SEEK_SET );
			}
		}
		iBasesNumber --;
	}
	ERETURN( LBS_OK );
}
