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
// Module: SESSCL11.CPP
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
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef _INC_PROCESS
#include	<process.h>
#endif
#ifndef _SLOT_
#include	<slot.h>
#endif
#include	<time.h>
#include	<baseinstance.h>

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

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

// nome da defudb
extern	char	_szDefUDBName[ MAXPATH ];

// para acesso ao manipulador de bases
extern BaseInstanceManager	_BasesManager;

////////////////////////////////////////////////
// para resolver feedback entre base e session
typedef	struct	_sThreadPar
{
	LBSC_Session	*pSession;
	LBSC_Base		*pBase;
} TThreadPar;
////////////////////////////////////////////////

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo ReorganizeUDB
	Reorganiza os arquivos de uma udb

	Parameters:
		- plbscTicketPar	-> ticket de seguranca
		- szUDBName			-> nome da UDB

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- 
***/
int
LBSC_Session::ReorganizeUDB( const LBSC_Ticket *plbscTicketPar, char *szUDBName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReorganizeUDB") );

	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( plbscTicketPar ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	// abre a UDB
	LBSC_Base	*lbscbUserBase = new LBSC_Base( plbscTicketPar, szUDBName, szUDBName, 
			"$$$", this, TRUE, FALSE, FALSE, FALSE );

	if( !lbscbUserBase ){
		ERETURN( LBSE_NOMEMORY );
	}
	int	iRet = lbscbUserBase->LastError();
	if( !lbscbUserBase->BaseObjOk() ){	// Nao conseguiu abrir a base
		delete lbscbUserBase;
		ERETURN( iRet );
	}
	// repassar a bola para o ReorganizeUDB privado
	iRet = ReorganizeUDB( plbscTicketPar, lbscbUserBase );

	// fechar a base
	delete lbscbUserBase;

	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo ReorganizeDefaultUserBase
	Reorganiza os arquivos de uma udb default

	Parameters:
		- plbscTicketPar	-> ticket de seguranca
		- szUDBName			-> nome da UDB

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- O usuario deve estar logado em modo monousuario
***/
int
LBSC_Session::ReorganizeDefaultUserBase( const LBSC_Ticket *plbscTicketPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReorganizeDefaultUserBase") );
	// chama o ReorganizeUDB, passando o nome da UDB default
	return( ReorganizeUDB( plbscTicketPar, _szDefUDBName ) );
}


/***
	PRIVATE
	Metodo ReprocBase
	Reprocessa uma base

	Parameters:
		- plbscTicketPar	-> ticket de seguranca
		- plbscBase		-> ponteiro para uma base ja aberta
		- bCopyRec		-> indica se os registros da base devem
					   ser copiados para a base resultante ou nao.
					   O default eh TRUE (copiar).

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- A base a ser reorganizada deve estar aberta em modo exclusivo
		  e nao deve estar em modo ReadOnly
		- Esta operacao pode ser demorada

***/
int
LBSC_Session::ReprocBase( const LBSC_Ticket *plbscTicketPar, LBSC_Base *plbscBase, BOOL bCopyRec )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReprocBase") );
	char			szTmpBasePath[ MAXPATH ];
	char			szBasePath[ MAXPATH ];
	char			szBaseName[ MAXPATH ];
	char			szBaseLongName[ MAXPATH ];
	char			szNewBaseName[ MAXPATH ];
	char			szBaseDir[ MAXPATH ];
	char			szCntrlFile[ MAXPATH ];
	char			*szMsg = NULL;				// para internacionalizacao de mensagens
	TControlRecHead	tchrControl;
	BOOL			bMaintenance;				// a base original esta' aberta para manutencao?
	BOOL			bOnLine;					// a base original esta' com indexacao on-line?

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

	// Verifica se a base estah aberta
	{
		C_SessCritSect	cCS0( this, CRITSECT0 );
		lbscblBaseList.First();
		if( lbscblBaseList.Find( plbscBase, CMPBASEPOINTER ) == NULL ){
			// A base passada nao consta na lista de bases desta sessao
			ERETURN( LBSE_BASENOTOPEN );
		}
	}

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( 14 + plbscBase->GetNumRecords( plbscTicketPar ) );	// 14 pontos fixos mais o loop dos registros

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INITREPROC" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Verifica se a base estah aberta em modo exclusivo
	if( plbscBase->IsExclusive() == FALSE ){
		ERETURN( LBSE_BASENOTEXCLUSIVE );
	}

	// Verifica se a base estah aberta em modo ReadOnly
	if( plbscBase->IsReadOnly() == TRUE ){
		ERETURN( LBSE_BASEREADONLY );
	}

	// verificar se a LO corrente eh a fisica
	// (isso so' eh importante se os registros da
	// base original forem copiados para a nova base)
	if( bCopyRec && (!plbscBase->pcOLList || !(plbscBase->pcOLList->GetCurrentIndex() == 0)) ){
		// este metodo deve copiar os registros para
		// a nova base, mas a LO corrente nao eh a fisica
		ERETURN( LBSE_INVALIDOCLIST );
	}

	// guarda o estado FullAccess da base (se esta' em modo manutencao ou nao)
	bMaintenance = plbscBase->IsFullAccess();

	// guarda o estado da indexacao on-line
	bOnLine = plbscBase->OnLineIndexStatus();

	// seta o estado de FullAccess para FALSE na base para poder enxergar os
	// dados.
	plbscBase->SetFullAccessMode( FALSE );

	// seta a indexacao para off-line para acelerar o processo de reprocessamento
	plbscBase->EnableOnLineIndex( FALSE );

	// obtem o alias, o nome longo e o path da base original
	plbscBase->GetBaseName( szBaseName );
	plbscBase->GetBaseLongName( szBaseLongName );
	plbscBase->GetFullBaseName( szBasePath );

	// Acessar lbs.ini para pegar o arquivo de controle
	if( GetFNameOnProfile( szBaseDir, szCntrlFile ) != LBS_OK ){
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		ERETURN( LBSE_LBSINIERROR );
	}

	// Procura um diretorio para trabalhar
	for( int iDirNum = 0 ; iDirNum < 9000;iDirNum++ ){
		sprintf( szTmpBasePath, "%s\\%d", szBaseDir, iDirNum );
		if( mkdir( szTmpBasePath ) == 0 ){
			if( rmdir( szTmpBasePath ) == 0 ){
				break;
			}
			plbscBase->SetFullAccessMode( bMaintenance );
			plbscBase->EnableOnLineIndex( bOnLine );
			ERETURN( LBSE_ERROR );
		}
	}
	if( iDirNum >= 9000 ){
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		ERETURN( LBSE_ERROR );
	}
	sprintf( szNewBaseName, "%d", iDirNum );

	// vamos alterar o nome do usuario logado para que fique igual ao nome do
	// dono da base. Assim, passamos por cima de todos os problemas de permissao
	// que eventualmente existirao daqui pra frente.
	char	*szOrigUser = (char*) plbscuUser->GetUserName();	// szOrigUser nao precisa ser deletado
	const char	*szOwnerAux = plbscBase->GetConstOwnerName();  // szOwnerAux nao precisa ser deletado
	plbscuUser->SetUserName( szOwnerAux );

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_CREATBASE" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Gera a lista de campos para a base nova
	TField	*tf = plbscBase->GetFields( plbscTicketPar );
	if( !tf ){
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSE_NOMEMORY );
	}


	// O array de TField retornado pelo metodo GetFields
	// contem varias estruturas TField com todas as informacoes
	// sobre os campos, menos as passwords. Portanto, vamos
	// preencher as passwords agora.
	int	iNumFields = plbscBase->GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pcfFieldAux = (*plbscBase)[ i ];
		if( !pcfFieldAux ){
			delete tf;
			plbscBase->SetFullAccessMode( bMaintenance );
			plbscBase->EnableOnLineIndex( bOnLine );
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		tf[ i ].szPasswordName = (char*) pcfFieldAux->GetPassword();
	}

	// Cria a base nova
	// (usei um apontador para objeto porque tenho que destrui-lo
	// antes do final deste metodo. Se tivesse usado um objeto
	// direto, o destrutor seria chamado apenas no final do escopo
	// deste metodo e isso eh indesejavel)
	LBSC_Base	*pbNewBase = new LBSC_Base;

	if( !pbNewBase ){
		delete tf;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSE_NOMEMORY );
	}

	if( pbNewBase->Create( plbsctTicket, szNewBaseName, (char*) plbscBase->GetPassword(),
			(char*) plbscBase->LB1.tcrHead.szMaintenancePassword,
			plbscBase->GetBaseType(), plbscBase->IsEncrypt(), this,
			(char*) plbscBase->LB1.tcrHead.szUserBase, tf,
			plbscBase->GetUserBaseId(), plbscBase->LB1.tcrHead.iSlotNum,
			plbscBase->LB1.tcrHead.iCountNum ) != LBS_OK ){
		delete tf;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSE_ERROR );
	}
	delete tf;

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_COPOLDFILES" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	InvalidateCacheInSubDirs( szBasePath );
	// copia os subdiretorios da base original para a nova base (essa que foi criada agora)
	// a funcao abaixo tambem copia os arquivos "*.LB" da base original para a nova.
	// esses arquivos nao sao gerados no createbase.
	if( CopyDir( szBasePath, szTmpBasePath ) != LBS_OK ){
		// deu pau. pode ter sido problema com travamento
		// de arquivo. vamos dar um tempo e tentar novamente.
		Sleep( 1000 );
		if( CopyDir( szBasePath, szTmpBasePath ) != LBS_OK ){
			// deu pau
			// deleta a nova base
			pbNewBase->Delete();
			delete pbNewBase;
			pbNewBase = NULL;
			plbscBase->SetFullAccessMode( bMaintenance );
			plbscBase->EnableOnLineIndex( bOnLine );
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			ERETURN( LBSE_ERROR );
		}
	}


	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPENTMPBASE" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Abre a base temporaria
	pbNewBase->Open( plbsctTicket, szNewBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
			TRUE, FALSE, FALSE );

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCHEADER" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Atualiza cabecalho da nova base para que fique igual ao da
	// base original
	plbscBase->LB1.R_ReadHead( &tchrControl );
	tchrControl.lDeletedRecNum = 0L;
	tchrControl.lNumRecords = 0L;
	tchrControl.bBaseIndexed = FALSE;
	tchrControl.ulLastModifyDate = C_Date().Hash();
	tchrControl.szLastModifyUserName = (char*) GetUserName();
	tchrControl.szOwnerName = (char*) GetUserName();
	tchrControl.lLastRecPos = -1L;
	tchrControl.lFirstRecActivePos = -1L;
	tchrControl.lLastRecActivePos = -1L;
	tchrControl.uiLastFieldId = plbscBase->LB1.tcrHead.uiLastFieldId;
	tchrControl.iMaxKeySize = pbNewBase->LB1.tcrHead.iMaxKeySize;
	pbNewBase->LB1.R_WriteHead( &tchrControl );

	// atualiza em memoria o header da nova base.
	pbNewBase->LB1.R_ReadHead();

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCFIELDS" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// reorganiza os identificadores de campo da base nova, para que fiquem
	// iguais aos da base original.
	for( i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = (*plbscBase)[ i ];
		if( !pf ){
			// deleta a nova base
			pbNewBase->Delete();
			delete pbNewBase;
			pbNewBase = NULL;
			plbscBase->SetFullAccessMode( bMaintenance );
			plbscBase->EnableOnLineIndex( bOnLine );
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		pbNewBase->ModifyFieldId( (char*) pf->GetAliasName(), pf->GetId() );
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCBASESLOTS" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// copia os slots de base
	for( i = 1; i <= plbscBase->LB1.tcrHead.iSlotNum; i++ ){
		if( plbscBase->GetSlotSize( i ) > 0 ){
			char	*szBuffer = new char [ plbscBase->GetSlotSize( i ) + 1 ];
			if( szBuffer ){
				if( plbscBase->GetSlot( i, szBuffer ) == LBS_OK ){
					pbNewBase->PutSlot( i, szBuffer, plbscBase->GetSlotSize( i ) );
				}
				delete szBuffer;
			}
		}
	}

	if( ConvertGroupInfo( plbscBase, pbNewBase ) != LBS_OK ){
		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCFIELDSLOTS" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// copia os slots de campo
	for( i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = (*plbscBase)[ i ];
		if( !pf ){
			// deleta a nova base
			pbNewBase->Delete();
			delete pbNewBase;
			pbNewBase = NULL;
			plbscBase->SetFullAccessMode( bMaintenance );
			plbscBase->EnableOnLineIndex( bOnLine );
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( plbscBase->GetFieldSlotSize( pf->GetId() ) > 0 ){
			char	*szBuffer = new char [ plbscBase->GetFieldSlotSize( pf->GetId() ) + 1 ];
			if( szBuffer ){
				if( plbscBase->GetFieldSlot( pf->GetId(), szBuffer ) == LBS_OK ){
					pbNewBase->PutFieldSlot( pf->GetId(), szBuffer, plbscBase->GetFieldSlotSize( pf->GetId() ) );
				}
				delete szBuffer;
			}
		}
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCCOUNTERS" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// copia os contadores
	for( i = 0; i < plbscBase->LB1.tcrHead.iCountNum; i++ ){
		pbNewBase->LockCount( i );
		pbNewBase->PutCount( i, plbscBase->GetCount( i ) );
		pbNewBase->ReleaseCount( i );
	}

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		pbNewBase->Delete();
		delete pbNewBase;
		pbNewBase = NULL;
		plbscBase->SetFullAccessMode( bMaintenance );
		plbscBase->EnableOnLineIndex( bOnLine );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCACLS" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// copia as ACLs
	pbNewBase->lbscaBaseUserAcl = plbscBase->lbscaBaseUserAcl;
	pbNewBase->lbscaBaseGroupAcl = plbscBase->lbscaBaseGroupAcl;
	pbNewBase->lbscaFieldUserAcl = plbscBase->lbscaFieldUserAcl;
	pbNewBase->lbscaFieldGroupAcl = plbscBase->lbscaFieldGroupAcl;
	pbNewBase->lbscaRecordUserAcl = plbscBase->lbscaRecordUserAcl;
	pbNewBase->lbscaRecordGroupAcl = plbscBase->lbscaRecordGroupAcl;
	pbNewBase->lbscaFormUserAcl = plbscBase->lbscaFormUserAcl;
	pbNewBase->lbscaFormGroupAcl = plbscBase->lbscaFormGroupAcl;
	pbNewBase->lbscaReportUserAcl = plbscBase->lbscaReportUserAcl;
	pbNewBase->lbscaReportGroupAcl = plbscBase->lbscaReportGroupAcl;
	pbNewBase->bACLChanged = TRUE;
	
	char szLogFileName[ MAXPATH ];
	sprintf( szLogFileName, "%s\\%s", szBasePath, "reproc.log" );
	FILE *pfile = fopen( szLogFileName, "a+");
	if ( pfile ){
		time_t ltime;
		char *cabecalho;
		char linha[MAXPATH];
		if( _pcInter ){
			cabecalho = _pcInter->GetGenMsgsAppVar( "LBSMSG_RECORDDAMAGEDHEADER" );
		}
		time(&ltime);
		sprintf(linha, "\t\t%s %s - %s\n\n", cabecalho, szBaseName, ctime( &ltime ));
		fputs(linha, pfile);
		fflush(pfile);
		delete cabecalho;
	}

	BOOL bRecOk = TRUE;
	if( bCopyRec ){
		// Copia todos os registro da base original para a nova base.
		long	lRecNumAux = 0l;
		long	lCurRecNum = 0l;
		int		iRet = LBS_OK;
		BOOL	bContinue = TRUE;
		long	lRecTotAux = plbscBase->GetNumRecords( plbscTicketPar );
		char	*err_msg1 = NULL;
		char	*err_msg2 = NULL;
		pbNewBase->EnableFastRecord( TRUE );
		iRet = plbscBase->FirstFRecord( plbsctTicket );
		if( iRet != LBS_OK && iRet != LBSE_NORECORD ){
			bRecOk = FALSE;
		}
		if( _pcInter ){
			err_msg1 = _pcInter->GetGenMsgsAppVar( "LBSMSG_RECORDDAMAGED1" );
			err_msg2 = _pcInter->GetGenMsgsAppVar( "LBSMSG_RECORDDAMAGED2" );
		}
		pbNewBase->FillFieldsFromSlotInfo();
		pbNewBase->lbscrCurrRecord.SortFieldLists();
		do{
			/*******************************************************/
			// informacao de feedback
			if( OperationCanceled() ){
				// operacao foi cancelada a pedido do usuario.

				// deleta a nova base
				pbNewBase->Delete();
				delete pbNewBase;
				pbNewBase = NULL;
				plbscBase->SetFullAccessMode( bMaintenance );
				plbscBase->EnableOnLineIndex( bOnLine );
				// restaura o nome do usuario logado
				if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
					plbscuUser->SetUserName( (const char*) szOrigUser );
				}
				if ( err_msg1 ){
					delete err_msg1;
				}
				if ( err_msg2 ){
					delete err_msg2;
				}
				if ( pfile ){
					fclose( pfile );
					pfile = NULL;
				}

				ERETURN( LBSW_OPCANCEL );
			}
			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				char	szFullMsg[ 200 ];

				szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCRECORDS" );
				sprintf( szFullMsg, "%s %d/%d", szMsg, lRecNumAux++, lRecTotAux );
				IncStep( szFullMsg );
				delete szMsg;
			} else {
				IncStep( "" );
			}
			/*******************************************************/

			switch ( iRet ) {
			case LBS_OK:
				// tudo ok...
				pbNewBase->lbscrCurrRecord = plbscBase->lbscrCurrRecord;
				pbNewBase->AppendRecord( plbsctTicket );
				lCurRecNum = plbscBase->CurrRecNum( plbsctTicket ) + 1;
				iRet = plbscBase->NextFRecord( plbsctTicket );
				break;
			case LBSE_LASTRECORD:
			case LBSE_NORECORD:
				// acabou...
				bContinue = FALSE;
				break;
			default:
				bRecOk = FALSE;
				// vamos achar o proximo registro que esteja ok...
				do {
					lCurRecNum++;
					// grava uma linha de log dizendo que o lCurRecNum ta fudido
					// deixa baseado em 1 ao inves de 0 como eh o normal do LBS
					if ( pfile && iRet != LBSE_EXCLUDEDREC ){
						char linha[MAXPATH];
						sprintf(linha, "%s %d %s\n", err_msg1, lCurRecNum, err_msg2);
						fputs(linha, pfile);
						fflush(pfile);
					}
					iRet = plbscBase->NthFRecord( plbsctTicket, lCurRecNum );
					if ( iRet == LBSE_INVALIDRECPOSITION ){
						bContinue = FALSE;
						break;
					}
				} while( iRet != LBS_OK );
			}
		} while( bContinue );
		if ( err_msg1 ){
			delete err_msg1;
		}
		if ( err_msg2 ){
			delete err_msg2;
		}
		pbNewBase->EnableFastRecord( FALSE );
	}

	/// fechando o arquivo de log.
	if ( pfile ){
		fclose( pfile );
		pfile = NULL;
	}

	// grava o header de lb1 da base nova
	pbNewBase->LB1.R_WriteHead();

	// Fecha as duas bases para manipular os arquivos
	pbNewBase->InvalidateCache();
	delete pbNewBase;
	pbNewBase = NULL;

	plbscBase->SetFullAccessMode( bMaintenance );
	plbscBase->EnableOnLineIndex( bOnLine );
	plbscBase->Close();
	plbscBase->InvalidateCache();

	/*******************************************************/
	// informacao de feedback
	if( OperationCanceled() ){
		// operacao foi cancelada a pedido do usuario.

		// deleta a nova base
		DeleteBase( plbsctTicket, szNewBaseName );
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		// Reabre a base original, com os arquivos velhos
		plbscBase->Open( plbsctTicket, szBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
				TRUE, FALSE, bMaintenance );
		plbscBase->FirstRecord( plbsctTicket );
		ERETURN( LBSW_OPCANCEL );
	}
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_TRANSFFILES" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// transfere os arquivos originais para um diretorio temporario
	char	szTmpNewBasePath[ MAXPATH ];

	for( iDirNum = 0 ; iDirNum < 9001;iDirNum++ ){
		sprintf( szTmpNewBasePath, "%s\\%d", szBaseDir, iDirNum );
		if( mkdir( szTmpNewBasePath ) == 0 ){
			if( rmdir( szTmpNewBasePath ) == 0 ){
				break;
			}
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			// Reabre a base original, com os arquivos velhos
			plbscBase->Open( plbsctTicket, szBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
					TRUE, FALSE, bMaintenance );
			plbscBase->FirstRecord( plbsctTicket );
			ERETURN( LBSE_ERROR );
		}
	}
	if( iDirNum >= 9001 ){
		// restaura o nome do usuario logado
		if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
			plbscuUser->SetUserName( (const char*) szOrigUser );
		}
		// Reabre a base original, com os arquivos velhos
		plbscBase->Open( plbsctTicket, szBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
				TRUE, FALSE, bMaintenance );
		plbscBase->FirstRecord( plbsctTicket );
		ERETURN( LBSE_ERROR );
	}

	chdir( "\\" );
	// move original para trabalho2:
	if( rename( szBasePath, szTmpNewBasePath ) != 0 ){
		// deu pau. pode ter sido problema com travamento
		// de arquivo. vamos dar um tempo e tentar novamente.
		Sleep( 1000 );
		if( rename( szBasePath, szTmpNewBasePath ) != 0 ){
			DWORD dw = GetLastError();	// para depuracao
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			// Reabre a base original, com os arquivos velhos
			plbscBase->Open( plbsctTicket, szBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
					TRUE, FALSE, bMaintenance );
			plbscBase->FirstRecord( plbsctTicket );
			// Remove o diretorio que ficou criado e nao foi usado
			plbscBase->RemoveDir( szTmpBasePath, TRUE );
			ERETURN( LBSE_ERROR );
		}
	}

	chdir( "\\" );
	// move trabalho1 para original:
	if( rename( szTmpBasePath, szBasePath ) != 0 ){
		// deu pau. pode ter sido problema com travamento
		// de arquivo. vamos dar um tempo e tentar novamente.
		Sleep( 1000 );
		if( rename( szTmpBasePath, szBasePath ) != 0 ){
			if( rename( szTmpNewBasePath, szBasePath  ) != 0 ){
				// deu pau. pode ter sido problema com travamento
				// de arquivo. vamos dar um tempo e tentar novamente.
				Sleep( 1000 );
				if( rename( szTmpNewBasePath, szBasePath  ) != 0 ){
					ERETURN( LBSE_FATAL );
				}
			}
			// restaura o nome do usuario logado
			if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
				plbscuUser->SetUserName( (const char*) szOrigUser );
			}
			// Reabre a base original, com os arquivos velhos
			plbscBase->Open( plbsctTicket, szBasePath, szBaseLongName, (char*) plbscBase->GetPassword(), this,
					TRUE, FALSE, bMaintenance );
			plbscBase->FirstRecord( plbsctTicket );
			ERETURN( LBSE_ERROR );
		}
	}


	/*******************************************************/
	// informacao de feedback
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_RENAMFILES" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	if( RenameToOrigFiles( szBasePath, szBaseName ) != LBS_OK ){
		// deu pau. pode ter sido problema com travamento
		// de arquivo. vamos dar um tempo e tentar novamente.
		Sleep( 1000 );
		if( RenameToOrigFiles( szBasePath, szBaseName ) != LBS_OK ){
			ERETURN( LBSE_FATAL );
		}
	}

	// restaura o nome do usuario logado
	if( strcmp( szOrigUser, (char*) plbscuUser->GetUserName() ) != 0 ){
		plbscuUser->SetUserName( (const char*) szOrigUser );
	}
	/*******************************************************/
	// informacao de feedback
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCFINISH" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	// Reabre a base original, que ja possui os novos arquivos
	plbscBase->Open( plbsctTicket, szBaseName, szBaseLongName, (char*) plbscBase->GetPassword(), this,
			TRUE, FALSE, bMaintenance );

	// seta o estado original da indexacao on-line; se for UDB, temos que forcar para on-line
	if ( plbscBase->LB1.tcrHead.bBaseType != USER_BASE ) {
		plbscBase->EnableOnLineIndex( bOnLine );
	} else {
		plbscBase->EnableOnLineIndex( TRUE );
	}

	// NAO PRECISAMOS REMOVER O SEGUNDO DIRETORIO DE TRABALHO
//	plbscBase->RemoveDir( szTmpNewBasePath, TRUE );


	int iRet = LBS_OK;
	if( bCopyRec ){
		// realiza uma indexacao total da base.
		TThreadPar	tThreadPar;
		HANDLE		hThreadHandle = NULL;
		unsigned	uThreadId;

		tThreadPar.pSession = this;
		tThreadPar.pBase = plbscBase;

		if( !C_File::Is32s() ){
			// criar thread para obter feedback do processo de
			// indexacao e repassar para a aplicacao.
			hThreadHandle = (HANDLE)_beginthreadex( NULL, 0, (unsigned (__stdcall *)(LPVOID)) ThreadFunc, &tThreadPar, 0, &uThreadId );
		}
		// sleep so' para dormir e o outro thread comecar.
		Sleep( 1 );
		iRet = plbscBase->IndexAll( plbscTicketPar, FALSE );
		while( iRet == LBSW_INDEXSTOPED ){
			iRet = plbscBase->IndexAll( plbscTicketPar, TRUE );
		}
		if( iRet == LBSE_NORECORD ){
			// nao ha' registros para indexar, mas isso
			// nao deve ser considerado erro.
			iRet = LBS_OK;
		}
		if( hThreadHandle ){
			// cancelar a operacao para o thread morrer
			// (isso nao significa que o usuario cancelou)
			this->CancelOperation();
			WaitForSingleObject( hThreadHandle, INFINITE );
			CloseHandle( hThreadHandle );
			hThreadHandle = NULL;
		}
	}

	/*******************************************************/
	// informacao de feedback
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_OPERATIONOK" );
		IncStep( szMsg );
		delete szMsg;
	} else {
		IncStep( "" );
	}
	/*******************************************************/

	if ( iRet == LBS_OK && !bRecOk ) {
		ERETURN( LBSW_DAMAGEDBUTREPROC );
	}

	ERETURN( iRet );
}


DWORD
ThreadFunc( LPVOID pParam )
{
	TThreadPar	*pThreadPar = (TThreadPar*) pParam;
	char		szMsg[ 512 ];
	float		fPercent;

	if( pThreadPar && pThreadPar->pSession && pThreadPar->pBase ){
		do{
			Sleep( 1000 );
			if( !pThreadPar->pSession->OperationCanceled() ){
				pThreadPar->pBase->GetOpInfo( szMsg, &fPercent );
				pThreadPar->pSession->SetOpInfo( szMsg, fPercent );
			} else {
				break;
			}
		} while( fPercent < 100 );
	}
	return( 0 );
}

void
LBSC_Session::InvalidateCacheInSubDirs( char *szDirName )
{
	char		szPath[ MAXPATH ];

	WIN32_FIND_DATA	Win32FD;
	sprintf( szPath, "%s\\*", szDirName );
	HANDLE	Newdir = FindFirstFile( szPath, &Win32FD );

	if( Newdir == INVALID_HANDLE_VALUE ){ // Nao Existe
		return;
	}

	do{
		char	szFullName[ MAXPATH ];

		if( stricmp( Win32FD.cFileName, "." ) == 0 ||
				stricmp( Win32FD.cFileName, ".." ) == 0 ||
				!(Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {	
			// nada a fazer...
			continue;
		}

		sprintf( szFullName, "%s\\%s", szDirName, Win32FD.cFileName );

		// achamos um diretorio... eh uma candidato a base; logo, candidato a ter a cache removida
		BaseInstance *pBaseInstance = _BasesManager.Search( szFullName );	
		if ( pBaseInstance ) {
			pBaseInstance->InvalidateAll();
		}

		// vamos fazer o mesmo trabalho recursivamente
		InvalidateCacheInSubDirs( szFullName );

	} while( FindNextFile( Newdir, &Win32FD ) );
	FindClose( Newdir );
}


/**********************************************************
// Function name	: LBSC_Session::ConvertGroupInfo
// Description	    : 
// Return type		: int 
// Argument         :  LBSC_Base *pOrigBase
// Argument         : LBSC_Base *pNewBase
**********************************************************/
int LBSC_Session::ConvertGroupInfo( LBSC_Base *pOrigBase, LBSC_Base *pNewBase )
{
	if( !pOrigBase ){
		return( LBSE_BADARG );
	}
	int		iNumFields = pOrigBase->GetNumberOfFields();
	int		iNumSlots = pOrigBase->GetNumberOfSlots();
	if( (iNumFields > 0) && (pOrigBase->GetBaseVersion() < SORTGROUP_MAGICNUMBER) && (iNumSlots >= SLOTGROUP) ){
		// converte informacao de grupo nos slots, caso a base que esta'
		// sendo reprocessada seja de uma versao anterior a SORTGROUP_MAGICNUMBER
		// *e* tenha pelo menos o slot SLOTGROUP

		if ( pOrigBase->GetSlotSize( SLOTGROUP ) < 0 ){
			return LBSE_ERROR;
		}

		SlotBaseManager	sBaseInfoOrig( SLOTGROUP, pOrigBase );
		SlotBaseManager	sBaseInfoNew( SLOTGROUP, pNewBase ? pNewBase : pOrigBase );

		if( pNewBase ){
			sBaseInfoNew.ClearSlotInfo();
		}


		// alocar um vetor de inteiros para guardarmos os numeros
		// dos grupos tratados para evitar tratar o mesmo grupo mais
		// de uma vez. Se a alocacao falhar, entao vamos continuar o
		// algoritmo, mas os grupos que forem encontrados mais de uma
		// vez serao tratados mais de uma vez. Estamos considerando
		// que o maximo de grupos que pode existir em uma base
		// eh igual ao numero de campos (teriamos um grupo para cada
		// campo).
		int		*piGroupTreated = new int [ iNumFields ];
		int		iLastArrayEntry = -1;

		if( piGroupTreated ){
			for( int j = 0; j < iNumFields; j++ ){
				piGroupTreated[ j ] = -1;
			}
		}
		for( int i = 0; i < iNumFields; i++ ){
			LBSC_Field	*pf = (*pOrigBase)[ i ];
			if( !pf ){
				// fudeu
				return( LBSE_ERROR );
			}
			int j = iNumFields;
			if( piGroupTreated ){
				// procurar o pf->iGroup no vetor piGroupTreated. Se for encontrado eh
				// porque o referido grupo ja' foi convertido.
				for( j = 0; j <= iLastArrayEntry; j++ ){
					if( piGroupTreated[ j ] == pf->iGroup ){
						break;
					}
				}
			}
			if( j > iLastArrayEntry ){
				// grupo ainda nao foi convertido

				// ler no formato velho...
				SLOTSTRUCT	*pSlotOrig = sBaseInfoOrig.GetObjectInfo( pf->iGroup );

				if( pSlotOrig ){
					CB_Grupos		cbGroup;

					cbGroup.sGrupo = (char*) pSlotOrig->SlotInformation;
					cbGroup.iGrupo = pf->iGroup;
					cbGroup.iSort = pOrigBase->GetGroupSortField( pf->iGroup );

					// ... e gravar com formato novo.
					C_Buffer		cbBuf( CB_Grupos::GetMaxSize() );

					cbBuf.Rewind();
					cbGroup.Serialize( cbBuf );
					int iSize = cbBuf.MyBufLen();
					sBaseInfoNew.DeleteObject ( cbGroup.iGrupo );
					sBaseInfoNew.AddObjectInfo( cbGroup.iGrupo, iSize, (void *) cbBuf.MyBuffer() );

					if( iLastArrayEntry < (iNumFields-1) ){
						piGroupTreated[ ++iLastArrayEntry ] = cbGroup.iGrupo;
					}
				}
			}
		}
		if( iLastArrayEntry > -1 ){
			sBaseInfoNew.Store();
		}

		if( piGroupTreated ){
			delete [] piGroupTreated;
		}
	}
	return( LBS_OK );
}


