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
// Module: BASECL.CPP
// Description:
//
//	LBSC_BASE private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//		Alessandro A. Jatoba'
//
// Last update: 14/06/95
//

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined __STDARG_H && !defined _INC_STDARG
#include	<stdarg.h>
#endif
#include <math.h>
#if !defined __CTYPE_H && !defined _INC_CTYPE
#include	<ctype.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined __DIRECT_H && !defined _INC_DIRECT
#include	<direct.h>
#endif
#if !defined __DIRENT_H && !defined _INC_DIRECT
#include	DIRENT_H
#endif
#if !defined( __SHARE_H ) && !defined _INC_SHARE
#include	<share.h>
#endif
#ifndef _LB3LIST_H_
#include	<lb3list.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_BASETIMERSLIST_H_
#include	<btimerl.h>
#endif
#ifndef	_LBSLCKCL_H_
#include	<lbslckcl.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif
extern "C" {
#include	<personcl.h>
}
#ifndef _HTML_HTMLTOTXT_H_
#include	<HTML_HtmlToTxt.h>
#endif
#ifndef _HTML_URL_H_
#include	<HTML_Url.h>
#endif
#ifndef _HTML_DEFS_H_
#include	<HTML_Defs.h>
#endif
#ifndef	_LBS_HTTP_H_
#include <LBS_Http.h>
#endif

// $$$ API LIGHT-TEXT
#ifndef         _SESSION
#include	<lt.h>
#endif
#ifndef         _EXPRLIST
#include	<exprlist.h>
#endif

#ifndef	_DEFMACRO_H_		// usado apenas quando compilando no MSVC20
#include	<defmacro.h>
#endif
#ifndef	_DEFFUNCS_H_
#include	<deffuncs.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef _SLOT_
#include <slot.h>
#endif
#include <baseinstance.h>
#include <LZO.h>
#include <malloc.h>
#include <olsort.h>

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

#define	K100	(100 * 1024)	// representa 100 Kbytes

#define MINBLOCKSIZE	1024

// IMPORTANTE:
// O objeto GLT_Session eh definido automaticamente pela API Light Text e eh
// usado para inicializar algumas coisas assim que este codigo entra no ar.
// Tambem eh usado para manipular sistemas de indices.
// O arquivo lt.h o declara.

// structs

extern	void	Printf( char *, ... );
int ContaBits( int );

// Global variables
extern	HINSTANCE		_hInstance;

// tratamento de log
// nome do arquivo de log de uso de bases
extern	char	_szLogFileName[ MAXPATH ];
// tamanho maximo de um arquivo de log de uso de bases
extern	char	_szBaseToken[ 64 ];
extern	char	_szAccToken[ 64 ];
extern	char	_szRecToken[ 64 ];
extern	char	_szFieldKeyToken[ 64 ];
extern	char	_szUserToken[ 64 ];
extern	char	_szClientToken[ 64 ];
extern	char	_szReadOperationToken[ 64 ];
extern	char	_szWriteOperationToken[ 64 ];
extern	char	_szAppendOperationToken[ 64 ];
extern	char	_szDeleteOperationToken[ 64 ];
extern	char	_szSearchOKOperationToken[ 64 ];
extern	char	_szSearchErrorOperationToken[ 64 ];
extern	char	_szOpenBaseOperationToken[ 64 ];
extern	char	_szCloseBaseOperationToken[ 64 ];
extern	int		_iFieldContentLen;

extern	void	AddLockInfo( TBaseTimers * );
extern	void	DelLockInfo( TBaseTimers * );
extern	int		CompareRecordHeaderFunc( const void *Key1, const void *Key2 );

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
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )


#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	Metodo Init
	Inicializa os atributos do objeto

	Parameters:

	Return:

	Comments:

***/
void
LBSC_Base::Init()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Init") );

	LB1.tcrHead.uiLastFieldId = 0;
	LB1.tcrHead.lDeletedRecNum = 0L;
	LB1.tcrHead.lDeletedRecNumReorg = NUMRECREORGANIZE;
	LB1.tcrHead.bBaseType = (BYTE) BASE_PUBLIC;
	LB1.tcrHead.bIsEncrypt = FALSE;
	LB1.tcrHead.bReExport = TRUE;
	LB1.tcrHead.bBaseIndexed = FALSE;
	LB1.tcrHead.lNumRecords = 0;
	LB1.tcrHead.lLastRecPos = -1L;
	LB1.tcrHead.lFirstRecActivePos = -1L;
	LB1.tcrHead.lLastRecActivePos = -1L;
	LB1.tcrHead.dwBaseId = 0;
	LB1.tcrHead.dwUserBaseId = 0;
	LB1.tcrHead.bOnLineIndex = TRUE;
	LB1.tcrHead.lLastRecActivePos = 0;
	LB1.tcrHead.iSlotNum = 0;
	LB1.tcrHead.iCountNum = 0;
	bHeaderLocked = FALSE;
	bSelfReorganize = FALSE;
	bFullAccess = FALSE;
	bIsExclusive = FALSE;
	bIsReadOnly = FALSE;
	bBaseUpdated = FALSE;
	bACLChanged = FALSE;
	plbscisIndexSystem = NULL;
	plbscsOwnerSession = NULL;
	pltctlStopWordList = NULL;
	iLockTimeOut = LOCKTIMEOUT;
	iLockTimeSleep = LOCKTIMESLEEP;
	bBaseObjOk = TRUE;
	uTimerId = 0;
	lLockPos = -1;
	bPrivateCreation = FALSE;
	bStruct = TRUE;
	bSelfDelete = FALSE;
	pvUserData = NULL;
	lUserDataSize = 0L;
	lbscrCurrRecord.Clear();
	pltcMaskList = new LTC_TERMLIST;
	pltcPhone = new LTC_PHONE;
	pltcSynonym = new LTC_SYNONYM;
	iNavigationState = 0;
	iNavigationIndex = 0;
	uiNavigationField = 0;
	szNavigationKey = NULL;
	iSearchType = EQUAL_KEY;
	szStdArray = NULL;
	pcOLList = NULL;
	pOcListOfCurrKey = NULL;
	iIndexTree = 0;
	bStopIndex = FALSE;
	bSecureSort = TRUE;
	bAppendingRec = FALSE;
	bIsBasePasswdCorrect = FALSE;
	bFastRec = FALSE;
	strLogFieldAliasName = "";
	szExcludeModulesFromLog = "";
	szFieldsForUpdateLog = "";
	iOperationLogMask = 0;
	pSortObj = NULL;
	pBaseInstance = NULL;
}


/***
	Metodo GenerateOwnerACL
	Gera as ACLs do dono da base na lista de ACLs de campo e de base

	Parameters:

	Return:
		- LBS_OK ou erro.

	Comments:

***/
int
LBSC_Base::GenerateOwnerACL()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GenerateOwnerACL") );

	LBSC_ACL		*plbscaACL;
	LBSC_Perm		*plbscpPerm;

	plbscaACL = new LBSC_ACL;
	if( !plbscaACL ){
		ERETURN( LBSE_NOMEMORY );
	}
	plbscaACL->szName = (char*) GetConstOwnerName();

	// ACLs de campo
	if( lbscaFieldUserAcl.Find( plbscaACL, 0 ) != NULL ){
		delete plbscaACL;
		lbscaFieldUserAcl.Current()->lbscplPermList.DelAll();
	} else {
		lbscaFieldUserAcl.Add( plbscaACL, AFTER );
	}
	// ACLs de base
	plbscaACL = new LBSC_ACL;
	if( plbscaACL ){
		plbscaACL->szName = (char*) GetConstOwnerName();
		if( lbscaBaseUserAcl.Find( plbscaACL, 0 ) != NULL ){
			delete plbscaACL;
			lbscaBaseUserAcl.Current()->lbscplPermList.DelAll();
		} else {
			lbscaBaseUserAcl.Add( plbscaACL, AFTER );
		}
	}
	// alimenta a lista de ACL's por campo
	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];
		if( pf ){
			plbscpPerm = new LBSC_Perm;
			if( plbscpPerm ){
				// pegamos o Id do campo diretamente da lista de campos
				// para nao corrermos o risco de sermos barrados pelas
				// proprias ACLs.
				plbscpPerm->lId = (long) (pf->GetId());
				plbscpPerm->bPermission = ACL_ADM;
				lbscaFieldUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
			}
		}
	}
	// agora setamos as permissoes nas ACLs da base
	plbscpPerm = new LBSC_Perm;
	if( plbscpPerm ){
		plbscpPerm->lId = (long) ID_BASE;
		plbscpPerm->bPermission = ACL_ADM;
		lbscaBaseUserAcl.Current()->lbscplPermList.Add( plbscpPerm, AFTER );
	}
	
	bBaseUpdated = TRUE;
	bACLChanged = TRUE;
	ERETURN( LBS_OK );
}


/***
	Metodo ClearAllFields
	Limpa todos os campos

	Parameters:
		-

	Return:
		-

	Comments:

***/
void
LBSC_Base::ClearAllFields()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearAllFields") );

	lbscrCurrRecord.Clear();
}


/******************************************************************************
				GET FIELD REPETITION
******************************************************************************/
/***
	Metodo GetFieldRepetition (string)
	Obtem uma string de um campo da base (NAO OBTEM UMA COPIA)

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- szReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- A string apontada por szReturn deve ter tamanho suficiente
		  para armazenar o valor de retorno.
		- o buffer retornado nao pode ser alterado.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, char **szReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
				USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*pf = lbscrCurrRecord( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData =  (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	if( pcData->GetType() != TEXT_FIELD && pcData->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_ERROR );
	}
	*szReturn = (char*) pcData->GetConstData();
	ERETURN( LBS_OK );
}



/***
	Metodo GetPassword
	Obtem a password da base

	Parameters:

	Return:
		A password da base para consulta.

	Comments:

***/
const char *
LBSC_Base::GetPassword()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetPassword") );

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	return( LB1.tcrHead.szBasePassword );
}

/***
	Metodo GetRecordPassword
	Obtem a password do registro corrente da base

	Parameters:

	Return:
		A password do registro corrente ou NULL.

	Comments:

***/
const char *
LBSC_Base::GetRecordPassword()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetRecordPassword") );

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	const char *szAux = lbscrCurrRecord.GetPassword();
	SetError( szAux ? LBS_OK : LBSE_ERROR );
	return( szAux );
}

/***
	Metodo GetFieldPassword
	Obtem a password de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo

	Return:
		- A password do campo ou erro.

	Comments:

***/
const char *
LBSC_Base::GetFieldPassword( char *szFieldAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldPassword") );

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	const char *szAux = lbscrCurrRecord.GetFieldPassword( szFieldAliasName );
	SetError( szAux ? LBS_OK : LBSE_ERROR );
	return( szAux );
}


/***
	Metodo GetFieldPassword
	Obtem a password de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo

	Return:
		- A password do campo ou erro.

	Comments:

***/
const char *
LBSC_Base::GetFieldPassword( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldPassword") );

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		const char *szAux = lbscrCurrRecord.GetFieldPassword( (char*) plbscfAux->GetAliasName() );
		SetError( szAux ? LBS_OK : LBSE_ERROR );
		return( szAux );
	}
	NRETURN( LBSE_FIELDNOTFOUND );
}


/***
	Metodo VerifyRecordStatus
	Acerta posicionamento de arquivo no caso de registros deletados

	Parameters:
		- lPos

	Return:

	Comments:

***/

int
LBSC_Base::VerifyRecordStatus( long lPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::VerifyRecordStatus") );

	TControlRec	tcrControlRec;

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( LB1.R_Seek( lPos ) != OK ){ 		// Posicionar no possivel ultimo
		ERETURN( LBSE_ERROR );
	}
	if( LB1.R_Read( &tcrControlRec ) != OK ){	// Ler o registro
		// se foi erro de lock, tentar novamente, sem ler
		// a data de criacao do registro, que eh a regiao de lock.
		if( LB1.R_Read( &tcrControlRec, sizeof( unsigned long ), 
					sizeof( tcrControlRec ) - sizeof( unsigned long ) ) != OK ){
			ERETURN( LBSE_ERROR );
		}
	}
	if( tcrControlRec.bRecStatus & REC_EXCLUDED ){   // Registro deletado
		ERETURN( LBSE_EXCLUDEDREC );
	}
	ERETURN( LBS_OK );
}

/***
	Metodo ChangeIndex
	Indexa ou desindexa todos ou um registro da base

	Parameters:
		- iType	     -> tipo de indexacao/desindexacao. Os possiveis
				valores estao listados no switch mais abaixo.
		- bIndex     -> indica se o(s) registro(s) sera(ao) indexado(s)
				(TRUE) ou desindexado(s) (FALSE).
		- bRestoreContext -> indica se a rotina deve restaurar um contexto
				anterior (TRUE) ou se deve inicializar a indexacao
				a partir do primeiro registro (FALSE, default).
				Este parametro so' tem validade para indexacao
				total.

	Return:
		- LBS_OK se conseguir indexar/desindexar a base ou erro.

	Comments:
		- Esta operacao pode ser demorada
		- No caso de indexacao/desindexacao total, todos os registros da base
		  serao indexados/desindexados, independentemente da LO corrente.
		  Isto eh, a base toda (fisicamente) serah percorrida.
		- Antes de iniciar qualquer indexacao/desindexacao, este metodo
		  recarrega a lista de stopwords, a partir do arquivo STOPWORD.LB.

***/
int
LBSC_Base::ChangeIndex( const LBSC_Ticket *lbscTicket, int iType, BOOL bIndex, BOOL bRestoreContext )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ChangeIndex") );

	int				i, j;
	int				iRet = LBS_OK;
	long			lAuxRecNum;
	BOOL			bAtLeastOneError = FALSE;
	static	BOOL	bTotalProcess = FALSE;
	static	BOOL	bVerifyLog = TRUE;
	int				iStop = 0;
	char			*szMsg = NULL;				// para internacionalizacao de mensagens
	long			lRecNumAux;
	long			lRecTotAux;
	int				iNumFields;

	if( iType == TOTAL_INDEX ){
		// resetar informacao de feedback
		ResetFeedbackInfo();
		SetNumSteps( 3 + GetNumRecords( lbscTicket ) );	// 3 pontos fixos mais o loop dos registros

		/*******************************************************/
		// informacao de feedback
		if( OperationCanceled() ){
			// operacao foi cancelada a pedido do usuario.
			ERETURN( LBSW_OPCANCEL );
		}
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INITINDEX" );
			IncStep( szMsg );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/

		// verificar se existe arquivo de log de indexacao off-line
		if( cfLB5.IsOpen() ){
			bVerifyLog = TRUE;
		} else {
			C_File		cfLB5Aux;
			char		szAux[ FULLNAMESIZE ];

			sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char *)szBaseName, LOGFILE1EXT );
			cfLB5Aux.Open( szAux, "r" );
			if( cfLB5Aux.IsOpen() && (cfLB5Aux.FileSize() > 0) ){
				bVerifyLog = TRUE;
			} else {
				bVerifyLog = FALSE;
			}
		}
	} else {
		if( !bTotalProcess ){
			bVerifyLog = TRUE;
		}
	}

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// se a base estiver aberta para manutencao, entao
	// nao permitiremos que o usuario manipule dados
	if( bFullAccess ){
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bIsReadOnly ){
		ERETURN( LBSE_BASEREADONLY );
	}
	if( lbscrCurrRecord.GetNumberOfFields() == 0 ){
		ERETURN( LBSE_NOFIELD );
	}

	switch( iType ){
	case TOTAL_INDEX:
		// Vamos primeiro destruir (zerar) o sistema de indices
		// atual. Depois, indexaremos todos os registros da base.

		/*******************************************************/
		// informacao de feedback
		if( OperationCanceled() ){
			// operacao foi cancelada a pedido do usuario.
			ERETURN( LBSW_OPCANCEL );
		}
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INITIS" );
			IncStep( szMsg );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/
		if( !plbscisIndexSystem || !bRestoreContext ){
			RemoveIndexSystem();
			if( !CreateIndexSystem() ){
				if ( LastError() == LBSE_TOOMANYOPENFILES ) {
					ERETURN( LBSE_TOOMANYOPENFILES );
				}
				ERETURN( LBSE_NOMEMORY );
			}
		}
		if( bRestoreContext ){
			iRet = LoadIndexStatus( lbscTicket );
			if( iRet != LBS_OK ){
				// nao conseguimos restaurar o contexto.
				// vamos voltar ao primeiro registro e
				// fazer tudo de novo.
				if( (iRet = FirstFRecord( lbscTicket )) != LBS_OK ){
					ERETURN( LBSE_NORECORD );
				}
			} else {
				if( CurrRecNum( lbscTicket ) > 0 ){
					iRet = NextFRecord( lbscTicket );
					if( iRet != LBS_OK ){
						// chegamos ao fim
						ERETURN( LBSE_LASTRECORD );
					}
				}
			}
		} else {
			if( (iRet = FirstFRecord( lbscTicket )) != LBS_OK ){
				ERETURN( LBSE_NORECORD );
			}
		}
		{
			bTotalProcess = TRUE;	// para que a indexacao parcial
									// saiba que estah sendo chamada a
									// partir da indexacao total

			// criar objeto para fazer lock do header de LB1. 
			// O destrutor faz o Release.
			LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

			if( !cLB1_LockHead.IsLocked() ){
				// nao consegui travar o header de LB1
				ERETURN( LBSE_HEADERROR );
			}
			// le^ o numero de parada para indexacao total.
			// este numero indica de quantos em quantos registros indexados
			// este metodo deve gravar um status e retornar para a aplcacao.
			// a aplicacao decide se quer continuar ou nao com a indexacao.
			// isso e' util para evitar que, numa indexacao longa, todo o
			// trabalho se perca por causa de uma queda.
			if( bStopIndex ){
				iStop = LBSC_ServerConfig::StopIndex();
			}

			// vamos varrer todos os registros
			lRecNumAux = CurrRecNum( lbscTicket );
			lRecTotAux = GetNumRecords( lbscTicket );

			if( bRestoreContext ){
				// atualizar o progress, em caso de indexacao incremental
				if( FirstFRecord( lbscTicket ) != LBS_OK ){
					ERETURN( LBSE_NORECORD );
				}
				long	lFirstRec = CurrRecNum( lbscTicket );
				if( NthFRecord( lbscTicket, lRecNumAux ) != OK ){
					ERETURN( LBSE_NORECORD );
				}
				for( long l = lFirstRec; l < lRecNumAux; l++ ){
					IncStep( "" );
				}
			}

			DWORD dwIni = 0;
			dwIni = GetTickCount();
			plbscisIndexSystem->LT_TurnOnAutoBuffer( LBSC_ServerConfig::MaxMemForIndex() );
			do{
				/*******************************************************/
				// informacao de feedback
				if( OperationCanceled() ){
					// operacao foi cancelada a pedido do usuario.
					iRet = LBSW_OPCANCEL;
					break;
				}
				if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
					char	szFullMsg[ 1000 ];

					szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INDEXREC" );
					sprintf( szFullMsg, "%s: %s %d/%d", (char *)szBaseName, szMsg, lRecNumAux++, lRecTotAux );
					IncStep( szFullMsg );
					delete szMsg;
				} else {
					IncStep( "" );
				}
				/*******************************************************/
				if( ( iRet = ChangeIndex( lbscTicket, PARTIAL_INDEX, bIndex ) ) != LBS_OK ){
					if( bIndex == TRUE ){
						// deu pau na indexacao de um registro,
						// entao devo desindexa-lo.
						bAtLeastOneError = TRUE;
						ChangeIndex( lbscTicket, PARTIAL_INDEX, FALSE );
					}
				}
				// se iStop for zero e' porque o cliente nao quer parar
				// a indexacao antes do fim.
				long	lRec = CurrRecNum( lbscTicket );
				if( iStop && (lRec != 0) && !(lRec % iStop) ){
					// baixar em disco tudo o que foi indexado ate' agora.
					/*******************************************************/
					// informacao de feedback
					if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
						szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_UPDATINGFILES" );
						IncStep( szMsg );
						delete szMsg;
					} else {
						IncStep( "" );
					}
					/*******************************************************/

					// devemos salvar o contexto da indexacao e retornar.
					// a aplicacao decide quando continuar.
					if( SaveIndexStatus( lbscTicket ) == LBS_OK ){
						iRet = LBSW_INDEXSTOPED;
						break;
					}
					// nao conseguimos salvar o contexto da indexacao.
					// entao vamos continuar e tentar na proxima.
				}

				iRet = NextFRecord( lbscTicket );
			} while( iRet == LBS_OK );
			FlushIndexSystem();
			plbscisIndexSystem->LT_TurnOffAutoBuffer();
			bTotalProcess = FALSE;
		}
		break;

	case PARTIAL_INDEX:	// Apenas para o registro corrente
		if( !plbscisIndexSystem ){
			ERETURN( LBSE_INVALIDINDEXSYSTEM );
		}
		if( !bIndex ){
			// $$$ Desligar flag de desindexacao em memoria
			lbscrCurrRecord.bStatus &= ~REC_INDEXED;
		}
		// Atualizar LB1
		UpdateStatus( lbscTicket, bIndex );

		// varre todos os campos
		iNumFields = GetNumberOfFields();
		for( j = 0; j < iNumFields; j++ ){
			LBSC_Field *pcfField = lbscrCurrRecord [ j ];

			if( !pcfField ){
				// por algum motivo, deu pau
				// (talvez permissao)
				continue;
			}

			if( !pcfField->bFlagUpdate && !bTotalProcess ){
				// nao ha' alteracoes de dado no campo
				// e nao estamos fazendo uma indexacao total.
				continue;	// vai pro proximo campo
			}

			lAuxRecNum = CurrRecNum( lbscTicket );
			if ( bIndex ) {
				pcfField->SetDataListTo( VALID_DATALIST );
			} else {
				pcfField->SetDataListTo( ORIGINAL_DATALIST );
			}

			int iNumRepet = pcfField->GetNumberOfRepetition(); 

			if( iNumRepet <= 0 ){
				if ( bIndex ) {
					//Indexar na arvore vazia a repetição 0
					//......//
					IndexEmptyLT( plbscisIndexSystem,
								  lAuxRecNum,
								  pcfField, 
								  0);
				} else {
					//Desindexar na arvore vazia a repetição 0
					//......//
					UnindexEmptyLT( plbscisIndexSystem,
								  lAuxRecNum,
								  pcfField, 
								  0);
				}

				pcfField->SetDataListTo( VALID_DATALIST );

				// nao ha' repeticoes
				// vai pro proximo campo
				continue;
			}
		
			// varre todas as repeticoes
			for( i = 0; i < iNumRepet; i++ ){
				iRet = LBS_OK;

				LBSC_Data	*pd = (*pcfField)[ i ];
				lAuxRecNum = CurrRecNum( lbscTicket );
				int	iIndexAttrib = (int) pcfField->GetIndexAttrib();
				BOOL bEmptyRep = TRUE;
				if ( pd && pd->GetConstData() && pd->GetStatus() != DATA_HOLE ) {
					long lRepSize = 0;
					if ( pcfField->GetType() == ALPHA_FIELD ) {
						lRepSize = strlen( (char*) pd->GetConstData() );
					} else {
						lRepSize = pd->GetSize();
					}
					bEmptyRep = lRepSize <= 0;
				}

				if( !bIndex ){ // desindexar
					if( bEmptyRep ) {
						// desindexar vazio
						iRet = UnindexEmptyLT( plbscisIndexSystem,
								  lAuxRecNum,
								  pcfField, 
								  i);
					} else {
						// desindexar repeticao
						iRet = UnindexLT( plbscisIndexSystem,
										  iIndexAttrib,
										  lAuxRecNum,
										  pcfField,
										  i,
										  (LTC_PARSER *) &lbscpParser );
					}
				} else {	// indexar
					if( bEmptyRep ){
						// indexar vazio
						iRet = IndexEmptyLT( plbscisIndexSystem,
									  lAuxRecNum,
									  pcfField, 
									  i);
					} else {
						// indexar repeticao
						iRet = IndexLT( plbscisIndexSystem,
								iIndexAttrib,
								lAuxRecNum,
								pcfField,
								i,
								(LTC_PARSER *) &lbscpParser );
					}
				}
			}
			pcfField->SetDataListTo( VALID_DATALIST );
		}
		break;

	default:
		ERETURN( LBSE_INVALIDINDEXTYPE );
	}

	if( iType == TOTAL_INDEX ){
		/*******************************************************/
		// informacao de feedback
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_FINISHINDEX" );
			IncStep( szMsg );
			delete szMsg;
		} else {
			IncStep( "" );
		}
		/*******************************************************/
	}

	if( !bAtLeastOneError ){
		// a regiao critica abaixo protege toda a operacao de atualizacao de registro
		CLBAutoRegCrit	AutoRegCritDataFile( pBaseInstance ? &(pBaseInstance->DataFileCritSect) : NULL );

		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		bBaseUpdated = TRUE;

		LB1.tcrHead.bBaseIndexed = TRUE;
		LB1.LB1_WriteHead();
	}

	if( bIndex && (iRet == LBS_OK) && (iType == PARTIAL_INDEX) ){
		// Ligar flag de indexacao em memoria
		lbscrCurrRecord.bStatus |= REC_INDEXED;
	}

	if( iType == PARTIAL_INDEX ){
		// Atualizar LB1
		UpdateStatus( lbscTicket, bIndex );

		if( bVerifyLog && bIndex ){
			// se o registro que acabamos de indexar estiver
			// no arquivo LB5 (esperando por uma indexacao),
			// devemos remove-lo. Isso serve para nao o indexarmos
			// novamente quando uma indexacao parcial (UpdateIndex)
			// for disparada.
			BOOL	bIsOpen = cfLB5.IsOpen();

			lAuxRecNum = CurrRecNum( lbscTicket );

			if( !bIsOpen ){
				// Abrir LB5
				if( OpenLogFile( cfLB5 ) == LBS_OK ){
					cfLB5.DelBitValue( lAuxRecNum );
					cfLB5.CloseIndex();
				}
			} else {
				cfLB5.DelBitValue( lAuxRecNum );
			}
		}
	}

	if( ((iRet == LBS_OK) || (iRet == LBSE_LASTRECORD)) && (iType == TOTAL_INDEX) ){
		// deletar o arquivo de contexto de indexacao
		char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
		sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) IDXCONTEXTFILE );
		remove( szAux );
	}
	if( (iRet == LBSW_OPCANCEL) && (iType == TOTAL_INDEX) ){
		// a operacao foi cancelada pelo usuario.
		// vamos deixar um contexto gravado para a proxima chamada a este metodo
		// continuar a indexacao a partir do ponto que parou.
		// se o usuario quiser comecar a indexacao do zero, tem que deletar
		// o arquivo "INDEX.CTX".

		PreviousFRecord( lbscTicket );
		SaveIndexStatus( lbscTicket );
	}

	ERETURN( iRet );
}




//.........//
/***
	Metodo IndexEmptyLT
	Faz indexacao de repetições vazias utilizando o metodo LT_IndexEmpty,
	da LT. 

	Parameters:
		- plbscisIndexSystem	-> ponteiro para o sistema de indices
		- lRecNum				-> numero do registro
		- uiFieldId				-> identificador do campo
		- iRep					-> numero da repeticao
		
	Return:
		- LBS_OK em caso de sucesso ou um valor negativo

	Comments:

***/

int
LBSC_Base::IndexEmptyLT( LBSC_IndexSystem *plbscisIndexSystem,
					long lRecNum,
					LBSC_Field *pField,
					int iRep )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IndexEmptyLT") );
	
	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	int	iRet = LBS_OK;

	if ( pField && pField->tiaIndexAttrib & EMPTYTREE ) {
		iRet = plbscisIndexSystem->LT_IndexEmpty(
						( unsigned long )  lRecNum,
						( unsigned short ) pField->uiFieldId,
						( unsigned short ) iRep);

		if ( iRet == LBS_OK && MustIndexLast( pField->uiFieldId, iRep ) ) {
			// indexar tambem a MAXREPETITION; 
			iRet = plbscisIndexSystem->LT_IndexEmpty(
						( unsigned long )  lRecNum,
						( unsigned short ) pField->uiFieldId,
						( unsigned short ) MAXREPETITION);
		}
	}
	
	iIndexTree = 0;
	ERETURN( iRet );
}



//..........//
/***
	Metodo UnindexEmptyLT
        Faz desindexacao utilizando o metodo LT_UnindexEmpty, da LT.

        Parameters:
			- plbscisIndexSystem	-> ponteiro para o sistema de indices
			- lRecNum		-> numero do registro
			- uiFieldId		-> identificador do campo
			- iRep			-> numero da repeticao
		
		Return:
        	- LBS_OK em caso de sucesso ou um valor negativo

        Comments:

***/
int
LBSC_Base::UnindexEmptyLT( LBSC_IndexSystem *plbscisIndexSystem,
					long lRecNum,
					LBSC_Field *pField,
					int iRep)
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UnindexEmptyLT") );

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	int	iRet = LBS_OK;
	
	if ( pField && pField->tiaIndexAttrib & EMPTYTREE ) {
		iRet = plbscisIndexSystem->LT_UnindexEmpty(
						( unsigned long )  lRecNum,
						( unsigned short ) pField->uiFieldId,
						( unsigned short ) iRep);

		if ( iRet == LBS_OK && MustUnIndexLast(pField->uiFieldId, iRep) ) {
			// tenta desindexar tambem a repeticao MAXREPETITION 
			iRet = plbscisIndexSystem->LT_UnindexEmpty(
						( unsigned long )  lRecNum,
						( unsigned short ) pField->uiFieldId,
						( unsigned short ) MAXREPETITION);
		}
	}
	
	iIndexTree = 0;
	ERETURN( iRet );
}




/***
	Metodo GetBaseFieldList
	Carrega a lista de campos de uma base para a memoria

	Parameters:

	Return:
		LBS_OK se conseguir carregar ou erro.

	Comments:

***/
int
LBSC_Base::GetBaseFieldList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseFieldList") );

	if ( !pBaseInstance ) {
		ERETURN( LBSE_NOSTRUCT );
	}

	// protegendo a manipulacao da lista de campos
	CLBAutoRegCrit	AutoRegCrit( &(pBaseInstance->FieldListCritSect) );

	if ( pBaseInstance->BaseStructLoaded() ) {		// estrutura ja foi carregada; vamos pegar da cache
		strLogFieldAliasName = pBaseInstance->strLogFieldAliasName;
		szExcludeModulesFromLog = pBaseInstance->szExcludeModulesFromLog;
		szFieldsForUpdateLog = pBaseInstance->szFieldsForUpdateLog;
		iOperationLogMask = pBaseInstance->iOperationLogMask;
		lbscrCurrRecord.lbscFieldList = pBaseInstance->lbscflFieldList;
		for ( int i=0; i<GetNumberOfFields(); i++ ) {
			LBSC_Field	*pf = lbscrCurrRecord[ i ];
			if ( !pf ) {	
				ERETURN( LBSE_NOSTRUCT );
			}
			pf->plbscbBase = this;
		}
		lbscrCurrRecord.SortFieldLists();
		ERETURN ( LBS_OK );
	}

	// vamos ler e guardar na cache...

	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	TStructRec	tsrStructRec;
	LBSC_Field	*plbscfField;

	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !LB3.IsOpen() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB3.R_FileSize() == 0 ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_NOSTRUCT );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_NOSTRUCT );
	}
	lbscrCurrRecord.DelAllFields();
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		if( LB3.R_Seek( i ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
		if( LB3.R_Read( &tsrStructRec ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
		if( tsrStructRec.uiFieldAttrib & DELETED_FIELD ){
			continue;
		}
		if( tsrStructRec.tiaIndexAttrib & 0x00008000 ){
			// este campo contem o antigo indice ENTIRETREE.
			// vamos converter para o novo indice (versao 3.3).
			// a conversao aqui eh feita apenas em memoria. quando
			// a base for reprocessada, o arquivo LB3 sera' corrigido.
			tsrStructRec.tiaIndexAttrib &= (~0x00008000);
			tsrStructRec.tiaIndexAttrib |= ENTIRETREE;
		}
		plbscfField = new LBSC_Field( tsrStructRec.szFieldAliasName,
						tsrStructRec.szFieldDescription,
						tsrStructRec.szFieldPassword,
						tsrStructRec.bFieldType,
						tsrStructRec.lFieldSize,
						tsrStructRec.uiFieldId,
						tsrStructRec.uiFieldAttrib,
						tsrStructRec.tiaIndexAttrib,
						this );
		if( !plbscfField ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_NOMEMORY );
		}

		// ler os slots do campo
		long lfSize		= cfSlotsFile.FileSize();
		if ( tsrStructRec.spSlot.pElem.lSize > 0 && 
				tsrStructRec.spSlot.pElem.lSize <= ( lfSize - tsrStructRec.spSlot.lPointer ) ){
			// so ler slots validos
			if( cfSlotsFile.Seek( tsrStructRec.spSlot.lPointer, SEEK_SET ) == OK ){
				void *pvBuffer = (void *)new char[tsrStructRec.spSlot.pElem.lSize];
				if ( pvBuffer ) {
					if( cfSlotsFile.Read( pvBuffer, tsrStructRec.spSlot.pElem.lSize ) == OK ){
						plbscfField->SetSlot(  tsrStructRec.spSlot.pElem.lSize, pvBuffer );
					}
				}
			}
		}

		if( lbscrCurrRecord.AddField( plbscfField, AFTER ) != OK ){
			delete plbscfField;
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
	}

	TStructHeadRec::Free( ptsrStructRecHead );

	// preenche as informacoes que veem de slots
	FillFieldsFromSlotInfo();

	// gowords
	FillGowords();

	// atributos do log de uso
	GetUsageLogParams();

	lbscrCurrRecord.SortFieldLists();

	if ( LB1.tcrHead.bBaseType == USER_BASE && GetUDBVersion() == CURRENT_UDBMAGICNUMBER && GetBaseVersion() == CURRENT_MAGICNUMBER ) {
		// vamos setar os slots de cada campo pra uso via LBW (caso ja nao existam)
		AddDefaultUDBSlots();
	}

	// guardar as informacoes na cache...
	pBaseInstance->lbscflFieldList = lbscrCurrRecord.lbscFieldList;
	pBaseInstance->strLogFieldAliasName = strLogFieldAliasName;
	pBaseInstance->szExcludeModulesFromLog = szExcludeModulesFromLog;
	pBaseInstance->szFieldsForUpdateLog = szFieldsForUpdateLog;
	pBaseInstance->iOperationLogMask = iOperationLogMask;

	ERETURN( LBS_OK );
}


void
LBSC_Base::GetUsageLogParams()
{
	if ( strcmp( LBSC_ServerConfig::LogFileDir(), "") == 0 ) {
		// nao gerar log
		return;
	}

	char	szConfFileName[ MAXPATH ];
	sprintf( szConfFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );

	GetPrivateProfileString( LOGUSE_SECTION, LOGUSE_FIELD_KEY, "", (char*) strLogFieldAliasName, FIELDNAMESIZE, szConfFileName );
	GetPrivateProfileString( LOGUSE_SECTION, LOGUSE_EXCLUDE_MODULES_KEY, "", (char*) szExcludeModulesFromLog, FULLNAMESIZE, szConfFileName );
	GetPrivateProfileString( LOGUSE_SECTION, LOGUSE_FIELDSFORUPDATELOG_KEY, "", (char*) szFieldsForUpdateLog, FULLNAMESIZE, szConfFileName );
	iOperationLogMask = GetPrivateProfileInt( LOGUSE_SECTION, LOGUSE_OPERATIONS_KEY, 0, szConfFileName );
}

void 
LBSC_Base::FillGowords()
{
	char	szGowordsFileName[ MAXPATH ];
	char	szGWFieldName[ MAXPATH ];
	int		iFieldNum = 0;

	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	// Carregar a lista de GoWords
	LBSC_Field	*pf = NULL;
	for ( int j=0; (pf = lbscrCurrRecord[ j ]) ; j++ ) {

		if ( !pf->GetAliasName() ) {
			continue;
		}

		strcpy( szGWFieldName, pf->GetAliasName() );

		// campo encontrado.
		// localizar a secao que contem as gowords do campo szGWFieldName
		char	szGWKey[ MAXPATH ];
		char	szGWs[ MAXPATH ];
		int		iGWNum = 0;
		
		sprintf( szGWKey, "%s%d", GWKEY, ++iGWNum );
		GetPrivateProfileString( szGWFieldName, szGWKey, "", szGWs, MAXPATH-1, szGowordsFileName );
		while( szGWs[0] ){
			// gowords encontradas para o campo szGWFieldName.
			// montar a lista interna de gowords para o campo.
			C_StrTok	cStrTok;
			char		*szGW = cStrTok.StrTok( szGWs, "," );

			while( szGW ){
				char	c;
				// tirar os espacos e tabs
				while( (*szGW == ' ') || (*szGW == '\t') ){
					++szGW;
				}
				c = szGW[ strlen( szGW ) - 1 ];
				while( (c == ' ') || (c == '\t') ){
					szGW[ strlen( szGW ) - 1 ] = '\0';
					c = szGW[ strlen( szGW ) - 1 ];
				}
				if( *szGW ){
					PreStandardize( szGW, DEFAULTSTANDARDIZERARRAY );
					pf->AddGoWord( szGW );
				}
				szGW = cStrTok.StrTok( NULL, "," );
			}

			// tentar ler outro grupo de gowords
			sprintf( szGWKey, "%s%d", GWKEY, ++iGWNum );
			GetPrivateProfileString( szGWFieldName, szGWKey, "", szGWs, MAXPATH-1, szGowordsFileName );
		}
	}
}


/***
	Metodo ResetLockElapsedTime
	Reinicializa a contagem do tempo de "lock"

	Parameters:

	Return:
		LBS_OK se conseguir reinicializar ou erro.

	Comments:

***/
int
LBSC_Base::ResetLockElapsedTime()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ResetLockElapsedTime") );

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	// terminar o eventual timer de lock 
	KillLockTimer();

	TBaseTimers	*pTimerInfo = new TBaseTimers;

	if ( pTimerInfo ) {
		pTimerInfo->pBase = this;
		pTimerInfo->pSession = plbscsOwnerSession;
		pTimerInfo->dwInterval = iLockTimeOut;
		pTimerInfo->dwStartTime = GetTickCount();
		pTimerInfo->lLockPos = lLockPos;

		AddLockInfo( pTimerInfo );
	}

	ERETURN( LBS_OK );
}


/***
	Metodo KillLockTimer
	Desabilita o timer de travamento de registro

	Parameters:

	Return:
		LBS_OK se conseguir desabilitar ou erro.

	Comments:

***/
int
LBSC_Base::KillLockTimer()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::KillLockTimer_Inicio") );

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	TBaseTimers	TimerInfo;

	TimerInfo.pBase = this;
	TimerInfo.pSession = plbscsOwnerSession;
	TimerInfo.lLockPos = lLockPos;

	DelLockInfo( &TimerInfo );

	ERETURN( LBS_OK );
}


/***
	Metodo Export
	Exporta uma base

	Parameters:
		- pcfExportFile : nome do arquivo de exportacao.

	Return:
		LBS_OK se conseguir exportar ou erro.

	Comments:

***/
int
LBSC_Base::Export( const LBSC_Ticket *lbscTicket, C_File *pcfExportFile, BOOL bReExportBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Export") );

	// algoritmo:
	// . gravar o nome da base
	// . gravar o flag de criptografia da base
	// . varrer o diretorio da base
	// . para cada arquivo:
	//	. incrementar o numero de arquivos encontrados
	//	. gravar todo o nome do arquivo no arquivao
	//	. gravar o tamanho do arquivo no arquivao
	//	. gravar todo o arquivo no arquivao
	// . no final, voltar ao ponto inicial do arquivao e gravar o numero de arquivos
	// . pronto!

	char			szPath [ MAXPATH ];	// caminho completo
	char			szDrive[ MAXDRIVE ];	// drive
	char			szDir[ MAXDIR ];	// diretorio sem o ultimo nome
	char			szFileName[ MAXFILE ];	// nome do arquivo
	char			szExt[ MAXEXT ];	// extensao do arquivo
	char			szAux[ FULLNAMESIZE ];	// string auxiliar
	WIN32_FIND_DATA		Win32FD;		// estrutura usada para pesquisar arquivos
	int			iNumFilesFound = 0;

	// vamos gravar o numero de arquivos encontrados no arquivao para
	// ja' reservamos espaco para essa informacao, que sera' usada mais
	// adiante.
	pcfExportFile->Write( &iNumFilesFound, sizeof( iNumFilesFound ) );

	// agora vamos gravar o nome da base no arquivao
	GetDirBase( szAux );
	char	*szBaseName = (strstr( (char*) szBasePath, szAux )) + strlen( szAux ) + 1;
	pcfExportFile->Write( szBaseName, FILENAMESIZE );

	// gravar o flag de criptografia
	pcfExportFile->Write( &(LB1.tcrHead.bIsEncrypt), sizeof( LB1.tcrHead.bIsEncrypt ) );

	// construir um nome completo de diretorio para tornar possivel
	// a pesquisa
	sprintf( szPath, "%s\\*", (char*) szBasePath );

	// pega o primeiro nome de arquivo do diretorio szPath
	// (o nome obtido pode ser um arquivo, um diretorio ou "." ou ".."
	HANDLE		Newdir = FindFirstFile( szPath, &Win32FD );

	if( Newdir != INVALID_HANDLE_VALUE ){ // Existe
		do{
			// pegamos um arquivo. vamos verificar seu nome
			fnsplit( Win32FD.cFileName, szDrive, szDir, szFileName, szExt );
			if( strcmp( Win32FD.cFileName, "." ) == 0 ||
			    strcmp( Win32FD.cFileName, ".." ) == 0 ){
				// ISSO NAO INTERESSA
				continue;
			}
			if( Win32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
				// o arquivo encontrado eh um diretorio.
				// Tambem nao interessa.
				continue;
			}
			// bom, vamos incrementar o numero de arquivos encontrados
			iNumFilesFound++;

			// agora vamos gravar o nome do arquivo no arquivao
			sprintf( szAux, "%s\\%s", (char*) szBasePath, szFileName );
			pcfExportFile->Write( szAux, FULLNAMESIZE );

			// agora vamos gravar o arquivo todo dentro do arquivao
			// vamos logo tentar ab
			C_File	cFile( szAux, "rb" );
			if( cFile.IsOpen() ){
				// fudeu!
				ERETURN( LBSE_ERROR );
			}

			// gravar o tamanho do arquivo
			long	lSize = cFile.FileSize();
			pcfExportFile->Write( &lSize, sizeof( lSize ) );

			// agora, gravar o proprio arquivo
			if( CopyFile( pcfExportFile, &cFile ) != LBS_OK ){
				// deu pau
				ERETURN( LBSE_ERROR );
			}
			// ok. vamos para o proximo.
			cFile.Close();

		} while( FindNextFile( Newdir, &Win32FD ) );
		FindClose( Newdir );
		ERETURN( LBS_OK );
	}
	FindClose( Newdir );
	ERETURN( LBSE_ERROR );
}

/***
	Metodo ExportLB3
	Exporta LB3 para o arquivo de xportacao

	Parameters:
		- pcfExportFile : nome do arquivo de exportacao

	Return:
		LBS_OK se conseguir exportar ou erro.

	Comments:

***/
int
LBSC_Base::ExportLB3( C_File *pcfExportFile )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ExportLB3") );

	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	TStructRec	tsrStructRec;

	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}

	// $$$ Le o cabecalho de LB3
	LB3.R_ReadHead( ptsrStructRecHead );

	// Grava o numero de slots no arquivo de exportacao
	if( pcfExportFile->Write( &LB1.tcrHead.iSlotNum, sizeof( LB1.tcrHead.iSlotNum ) ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_FILEERROR );
	}

	// Grava o numero de contadores no arquivo de exportacao
	if( pcfExportFile->Write( &LB1.tcrHead.iCountNum, sizeof( LB1.tcrHead.iCountNum ) ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_FILEERROR );
	}

	// $$$ Grava o cabecalho de LB3 no arq. de exportacao
	if( pcfExportFile->Write( ptsrStructRecHead, TStructHeadRec::SizeOf( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum ) ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_FILEERROR );
	}

	// $$$ Le os registros de LB3 e os grava no arq. de exportacao
	for( int i = 0; i < ptsrStructRecHead->iNumberOfFields; i++ ){
		LB3.R_Seek( i );
		LB3.R_Read( &tsrStructRec );
		pcfExportFile->Write( &tsrStructRec, sizeof( TStructRec ) );
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( LBS_OK );
}

/***
	Metodo ExportLB1
	Exporta LB1 para o arquivo de exportacao

	Parameters:
		- pcfExportFile : nome do arquivo de exportacao

	Return:
		LBS_OK se conseguir exportar ou erro.

	Comments:

***/
int
LBSC_Base::ExportLB1( const LBSC_Ticket *lbscTicket, C_File *pcfExportFile, BOOL bReExportBase )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ExportLB1") );

	TControlRecHeadExp	tcrheRecHead;
	TControlRecExp		tcreRec;
	int			iNumFields;
	int			iNumRep;
	int			iType;
	long			lSize;
	JulTy			jt;
	char			*szAux;

	// Monta e grava o cabecalho de LB1
	tcrheRecHead.lDeletedRecNumReorg = LB1.tcrHead.lDeletedRecNumReorg;
	tcrheRecHead.lNumRecords = LB1.tcrHead.lNumRecords;
	tcrheRecHead.bIsEncrypt = LB1.tcrHead.bIsEncrypt;
	tcrheRecHead.bReExport = LB1.tcrHead.bReExport;
	tcrheRecHead.bBaseIndexed = LB1.tcrHead.bBaseIndexed;
	tcrheRecHead.iSlotNum = LB1.tcrHead.iSlotNum;
	tcrheRecHead.iCountNum = LB1.tcrHead.iCountNum;
	tcrheRecHead.szOwnerName = LB1.tcrHead.szOwnerName;
	tcrheRecHead.szLastModifyUserName = LB1.tcrHead.szLastModifyUserName;
	tcrheRecHead.ulCreateDate = cdCreateDate.Hash();
	tcrheRecHead.ulLastModifyDate = cdLastModifyDate.Hash();
	tcrheRecHead.szBasePassword = LB1.tcrHead.szBasePassword;
	tcrheRecHead.bBaseType = LB1.tcrHead.bBaseType;
//	tcrheRecHead.iLockTimeOut = this->iLockTimeOut;
	tcrheRecHead.dwBaseId = LB1.tcrHead.dwBaseId;
	tcrheRecHead.bReExport = bReExportBase;
	tcrheRecHead.szMaintenancePassword = LB1.tcrHead.szMaintenancePassword;

	if( pcfExportFile->Write( &tcrheRecHead, sizeof( TControlRecHeadExp ) ) != OK ){
		ERETURN( LBSE_ERROR );
	}

	// Gravar arquivo de ACL's
	lbscaBaseUserAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaBaseGroupAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaFieldUserAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaFieldGroupAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaRecordUserAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaRecordGroupAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaFormUserAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaFormGroupAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaReportUserAcl.Save( pcfExportFile, GetBaseVersion() );
	lbscaReportGroupAcl.Save( pcfExportFile, GetBaseVersion() );

	// Le e grava os registros nao deletados de LB1
	iNumFields = GetNumberOfFields();
	FirstFRecord( lbscTicket );
	do{
		tcreRec.ulCreateDate = lbscrCurrRecord.GetCreateDate();
		tcreRec.ulModifyDate = lbscrCurrRecord.GetModifyDate();
		tcreRec.szLastModifyUserName = lbscrCurrRecord.GetLastModifyUserName();
		tcreRec.szOwnerName = (char*) lbscrCurrRecord.GetOwnerName();
		tcreRec.bRecStatus = lbscrCurrRecord.GetStatus();
		tcreRec.szPassword = lbscrCurrRecord.GetPassword();
		if( pcfExportFile->Write( &tcreRec, sizeof( TControlRecExp ) ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		for( int i = 0; i < iNumFields; i++ ){
			iType = (lbscrCurrRecord[ i ])->GetType();
			iNumRep = (lbscrCurrRecord[ i ])->GetNumberOfRepetition();
			if( pcfExportFile->Write( &iNumRep, sizeof( int ) ) != OK ){
				ERETURN( LBSE_ERROR );
			}
			for( int j = 0; j < iNumRep; j++ ){
				if( pcfExportFile->Write( &( lSize =
					( ( *this )[ i ][ j ] ).GetSize() ), sizeof( long ) ) != OK ){
					ERETURN( LBSE_ERROR );				
				}
				switch( iType ){
				case VALUE_FIELD:
					{
						long	l = (long) *((*(*this )[ i ])[ j ]);
						if( pcfExportFile->Write( &l, lSize ) != OK ){
							ERETURN( LBSE_ERROR );
						}
					}
					break;
				case DVALUE_FIELD:
					{
						double	d = (double) *((*(*this )[ i ])[ j ]);
						if( pcfExportFile->Write( &d, lSize ) != OK ){
							ERETURN( LBSE_ERROR );
						}
					}
					break;
				case ALPHA_FIELD:
				case TEXT_FIELD:
					szAux = new char[ lSize ];
					if( szAux ){
						strcpy( szAux, ((char*) (*((*(*this )[ i ])[ j ]))) );
						if( pcfExportFile->Write( szAux, lSize ) != OK ){
							ERETURN( LBSE_ERROR );
						}
						delete szAux;
					}
					break;
				case DATE_FIELD:
					jt = (JulTy) (*((*(*this )[ i ])[ j ]));
					if( pcfExportFile->Write( &jt, lSize ) != OK ){
						ERETURN( LBSE_ERROR );
					}
					break;
				case TIME_FIELD:
					jt = (JulTy)(*((*(*this )[ i ])[ j ]));
					if( pcfExportFile->Write( &jt, lSize ) != OK ){
						ERETURN( LBSE_ERROR );
					}
					break;
				case BINARY_FIELD:
					{
						LBSC_Binary	*b = (LBSC_Binary*) *(((*(lbscrCurrRecord[ i ]))[ j ]));
						if( pcfExportFile->Write( b, lSize ) != OK ){
							ERETURN( LBSE_ERROR );
						}
					}
					break;
				case REFERENCED_FIELD:
					{
						LBSC_Reference	*r = (LBSC_Reference*) *(((*(lbscrCurrRecord[ i ]))[ j ]));
						if( pcfExportFile->Write( r, lSize ) != OK ){
							ERETURN( LBSE_ERROR );
						}
					}
					break;
				}
			}
		}
	}while( NextFRecord( lbscTicket ) == LBS_OK );

	// Vai para o final do arquivo
	pcfExportFile->Seek( 0, SEEK_END );

	ERETURN( LBS_OK );
}

/***
	Metodo BaseStruct
	Obtem o status bStruct, que indica se o arquivo de estrutura (LB3) foi lido
	com sucesso ou nao.

	Parameters:

	Return:
		bStruct

	Comments:

***/
BOOL
LBSC_Base::BaseStruct()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::BaseStruct") );

	SetError( LBS_OK );
	return( bStruct );
}


#ifdef __BORLANDC__
#pragma warn +par
#endif

/***
	PRIVATE
	Metodo FirstFRecord
	Obtem o primeiro registro ativo de uma base, independente da LO

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::FirstFRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::FirstFRecord") );

	int	iRet;

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	// reler o header de LB1
	{
		if( LB1.R_ReadHead() != OK ){
			ERETURN( LBSE_HEADERROR );
		}
	}
	if( LB1.tcrHead.lNumRecords == 0 ){
		ERETURN( LBSE_NORECORD );
	}
	if( (iRet = VerifyRecordStatus( LB1.tcrHead.lFirstRecActivePos )) != LBS_OK ){
		ERETURN( iRet );
	}

	long lOldPos = LB1.R_CurPos();
	long lNewPos = LB1.tcrHead.lFirstRecActivePos;

	// Checar se o caminhamento por chave esta' ligado.
	// Se tiver, pegar a primeira chave, a partir dela pegar
	// uma LO, extrair a primeira ocorrencia e posicionar-se
	// sobre o registro adequado.
	switch( iNavigationState ){
	case NAVIGATIONBYINDEX:
		iRet = GetRecPosByKey( FIRSTKEY, &lNewPos );
		if( iRet != LBS_OK ){
			iRet = GetRecPosByKey( NEXTKEY, &lNewPos );
			if( iRet != LBS_OK ){
				ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_FIRSTRECORD : iRet );
			}
		}
		break;

	case NAVIGATIONBYKEY:
		iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, FIRSTOC );
		if( iRet != LBS_OK ){
			iRet = GetRecPosByKey( NEXTKEY, &lNewPos );
			if( iRet != LBS_OK ){
				ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_FIRSTRECORD : iRet );
			}
		}
		break;

	}
	// faz release no registro corrente
	ReleaseRecord( lbscTicket );

	if( (iRet = LB1.R_Seek( lNewPos )) != OK ){
		ERETURN( iRet );
	}

	if( (iRet = ReadRecord( lbscTicket )) != LBS_OK ){
		if( (iRet == LBSE_NOPERMISSION) || (iRet == LBSE_EXCLUDEDREC)){
			return( NextFRecord( lbscTicket ) );
		} else {
			if( iRet != LBSE_ZERORECORD ){
				LB1.R_Seek( lOldPos );
			}
		}
		ERETURN( iRet );
	}
	ERETURN( LBS_OK );
}



/***
	PRIVATE
	Metodo NextFRecord
	Obtem o proximo registro ativo da base, independente da LO

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::NextFRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::NextFRecord") );

	long	lFAux;

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB1.tcrHead.lNumRecords == 0 ){
		ERETURN( LBSE_NORECORD );
	}

	// faz release no registro corrente
	ReleaseRecord( lbscTicket );

	// Checar se o caminhamento por chave esta' ligado.
	// Se tiver, pegar a primeira chave, a partir dela pegar
	// uma LO, extrair a primeira ocorrencia e posicionar-se
	// sobre o registro adequado.
	int		iRet;
	long	lCurRecPos = LB1.R_CurPos();
	long	lNewPos = lCurRecPos;
	switch( iNavigationState ){
	case NAVIGATIONBYINDEX:
		do{
			iRet = GetRecPosByKey( CURRKEY, &lNewPos, NEXTOC );
			if( iRet != LBS_OK ){
				iRet = GetRecPosByKey( NEXTKEY, &lNewPos );
				if( iRet != LBS_OK ){
					ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_LASTRECORD : iRet );
				}
			}
			iRet = GotoRec( lbscTicket, lNewPos );
		} while( iRet == LBSE_EXCLUDEDREC || (lCurRecPos == lNewPos) );
		return( iRet );

	case NAVIGATIONBYKEY:
		do{
			iRet = GetRecPosByKey( CURRKEY, &lNewPos, NEXTOC );
			if( iRet != LBS_OK ){
				iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, NEXTOC );
				if( iRet != LBS_OK ){
					ERETURN( LBSE_LASTRECORD );
				}
			}
			iRet = GotoRec( lbscTicket, lNewPos );
		} while( iRet == LBSE_EXCLUDEDREC || (lCurRecPos == lNewPos) );
		return( iRet );
	}

	if( ( lFAux = LB1.R_CurPos() ) == LB1.tcrHead.lLastRecActivePos ){
		ERETURN( LBSE_LASTRECORD );
	}
	iRet = LBS_OK;
	do {
		if( (iRet = LB1.R_SeekNext()) != OK ){
			/* posso contar com isso */
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
		iRet = ReadRecord( lbscTicket );
		if( (iRet != LBS_OK) && (iRet != LBSE_EXCLUDEDREC) &&
		    (iRet != LBSE_NOPERMISSION) && (iRet != LBSE_ZERORECORD) &&
			(iRet != LBSE_RECORDLOCKED) ){
			/* posso contar com isso */
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
		if( (iRet == LBSE_NOPERMISSION) &&
		    ( LB1.R_CurPos() == LB1.tcrHead.lLastRecActivePos ) ){
		    // $$$ estou no ultimo registro e o usuario nao tem permissao
			/* posso contar com isso */
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
	} while( (iRet != LBS_OK) && (iRet != LBSE_ZERORECORD) );

	ERETURN( iRet );
}


/***
	PRIVATE
	Metodo PreviousFRecord
	Obtem o registro ativo anterior da base, independente da LO

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::PreviousFRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PreviousFRecord") );

	long	lFAux;

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB1.tcrHead.lNumRecords == 0 ){
		ERETURN( LBSE_NORECORD );
	}

	// faz release no registro corrente
	ReleaseRecord( lbscTicket );

	// Checar se o caminhamento por chave esta' ligado.
	// Se tiver, pegar a primeira chave, a partir dela pegar
	// uma LO, extrair a primeira ocorrencia e posicionar-se
	// sobre o registro adequado.
	int		iRet;
	long	lCurRecPos = LB1.R_CurPos();
	long	lNewPos = lCurRecPos;
	switch( iNavigationState ){
	case NAVIGATIONBYINDEX:
		do {
			iRet = GetRecPosByKey( CURRKEY, &lNewPos, PREVIOUSOC );
			if( iRet != LBS_OK ){
				iRet = GetRecPosByKey( PREVIOUSKEY, &lNewPos );
				if( iRet != LBS_OK ){
					ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_FIRSTRECORD : iRet );
				}
			}
			iRet = GotoRec( lbscTicket, lNewPos );
		} while( iRet == LBSE_EXCLUDEDREC || (lCurRecPos == lNewPos) );
		return( iRet );

	case NAVIGATIONBYKEY:
		do{
			iRet = GetRecPosByKey( CURRKEY, &lNewPos, PREVIOUSOC );
			if( iRet != LBS_OK ){
				iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, PREVIOUSOC );
				if( iRet != LBS_OK ){
					ERETURN( LBSE_FIRSTRECORD );
				}
			}
			iRet = GotoRec( lbscTicket, lNewPos );
		} while( iRet == LBSE_EXCLUDEDREC || (lCurRecPos == lNewPos) );
		return( iRet );
	}

	if( ( lFAux = LB1.R_CurPos() ) == LB1.tcrHead.lFirstRecActivePos ){
		ERETURN( LBSE_FIRSTRECORD );
	}

	iRet = LBS_OK;
	do {
		if( (iRet = LB1.R_SeekPrevious()) != OK ){
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
		iRet = ReadRecord( lbscTicket );
		if( (iRet != LBS_OK) && (iRet != LBSE_EXCLUDEDREC) &&
		    (iRet != LBSE_NOPERMISSION) && (iRet != LBSE_ZERORECORD) &&
			(iRet != LBSE_RECORDLOCKED) ){
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
		if( (iRet == LBSE_NOPERMISSION) &&
		    ( LB1.R_CurPos() == LB1.tcrHead.lFirstRecActivePos ) ){
		    // $$$ estou no primeiro registro e o usuario nao tem permissao
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			ERETURN( iRet );
		}
	} while( (iRet != LBS_OK) && (iRet != LBSE_ZERORECORD) );

	ERETURN( iRet );
}


/***
	PRIVATE
	Metodo LastFRecord
	Obtem o ultimo registro ativo da base, independente da LO

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::LastFRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LastFRecord") );

	int	iRet = LBS_OK;

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}

	// reler o header de LB1
	{
		if( LB1.R_ReadHead() != OK ){
			ERETURN( LBSE_HEADERROR );
		}
	}

	if( bBaseObjOk == TRUE ){
		if( LB1.tcrHead.lNumRecords == 0 ){
			ERETURN( LBSE_NORECORD );
		}
		if( VerifyRecordStatus( LB1.tcrHead.lLastRecActivePos ) == LBS_OK ){
			long lNewPos = LB1.tcrHead.lLastRecActivePos;

			// Checar se o caminhamento por chave esta' ligado.
			// Se tiver, pegar a primeira chave, a partir dela pegar
			// uma LO, extrair a primeira ocorrencia e posicionar-se
			// sobre o registro adequado.
			int iRet;
			switch( iNavigationState ){
			case NAVIGATIONBYINDEX:
				iRet = GetRecPosByKey( LASTKEY, &lNewPos );
				if( iRet != LBS_OK ){
					iRet = GetRecPosByKey( PREVIOUSKEY, &lNewPos, LASTOC );
					if( iRet != LBS_OK ){
						ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_LASTRECORD : iRet );
					}
				}
				break;

			case NAVIGATIONBYKEY:
				iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, LASTOC );
				if( iRet != LBS_OK ){
					iRet = GetRecPosByKey( PREVIOUSKEY, &lNewPos, LASTOC );
					if( iRet != LBS_OK ){
						ERETURN( iRet == LBSE_EMPTYINDEX ? LBSE_LASTRECORD : iRet );
					}
				}
				break;
			}

			// faz release no registro corrente
			ReleaseRecord( lbscTicket );

			if( LB1.R_Seek( lNewPos ) == OK ){
				if( (iRet = ReadRecord( lbscTicket )) == LBS_OK ){
					ERETURN( LBS_OK );
				}else{
					if( (iRet == LBSE_NOPERMISSION) || (iRet == LBSE_EXCLUDEDREC)){
						return( PreviousFRecord( lbscTicket ) );
					}
					ERETURN( iRet );
				}
			}
		}
	}
	ERETURN( LBSE_ERROR );
}


/***
	PRIVATE
	Metodo NthFRecord
	Obtem o n-esimo registro ativo da base, independente da LO

	Parameters:
		- lPos

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::NthFRecord( const LBSC_Ticket *lbscTicket, long lPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::NthFRecord") );

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( ( LB1.tcrHead.lNumRecords == 0 ) || ( lPos < 0 ) ){
		ERETURN( LBSE_NORECORD );
	}
	// faz release no registro corrente
	ReleaseRecord( lbscTicket );


	return( GotoRec( lbscTicket, lPos ) );
/*

	long lFAux = LB1.R_CurPos();
	if( FirstFRecord( lbscTicket ) != LBS_OK ){
		return( LastError() );
	}
	while( lPos > 0 ){
		if( NextFRecord( lbscTicket ) != LBS_OK ){
			LB1.R_Seek( lFAux );
			ReadRecord( lbscTicket );
			return( LastError() );
		}
		--lPos;
	}
	ERETURN( LBS_OK );
*/
}

/***
	PRIVATE
	Metodo Index
	Indexa todos os registros ou o registro corrente

	Parameters:
		- iType	     -> tipo de desindexacao. Os possiveis valores sao
				TOTAL_INDEX e PARTIAL_INDEX.
		- bRestoreContext -> indica se a rotina deve restaurar um contexto
				anterior (TRUE) ou se deve inicializar a indexacao
				a partir do primeiro registro (FALSE, default).
				Este parametro so' tem validade para indexacao
				total.

	Return:
		- LBS_OK se conseguir indexar a base ou erro.

	Comments:
		- Esta operacao pode ser demorada

***/
int
LBSC_Base::Index( const LBSC_Ticket *lbscTicket, int iType, BOOL bRestoreContext )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Index") );

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	int	iRet = ChangeIndex( lbscTicket, iType, TRUE, bRestoreContext );

	if( (iRet == LBSE_LASTRECORD || iRet == LBSE_NORECORD) && iType == TOTAL_INDEX ){
		// $$$ esta eh a condicao natural de saida
		// $$$ da indexacao total; entao tudo OK...
		iRet = LBS_OK;
	}

	ERETURN( iRet );
}



/***
	PRIVATE
	Metodo Unindex
	Desindexa todos os registros ou o registro corrente

	Parameters:
		- iType	     -> tipo de desindexacao. Os possiveis valores sao
				TOTAL_INDEX e PARTIAL_INDEX.

	Return:
		- LBS_OK se conseguir indexar a base ou erro.

	Comments:
		- Esta operacao pode ser demorada

***/
int
LBSC_Base::Unindex( const LBSC_Ticket *lbscTicket, int iType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Unindex") );

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	return ( ChangeIndex( lbscTicket, iType, FALSE ) );
}

/***
	PRIVATE
	Metodo GetCurrFieldType
	Obtem o tipo do campo corrente

	Parameters:

	Return:
		- o tipo do campo corrente

	Comments:

***/
int
LBSC_Base::GetCurrFieldType()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrFieldType") );

	SetError( LBS_OK );
	int iType = (lbscrCurrRecord.CurrentField())->GetType();
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionSize 1 %s %d", "FieldType", iType) );

	return iType;
}


/***
	PRIVATE
	Metodo GetCurrFieldId
	Obtem o identificador do campo corrente

	Parameters:

	Return:
		- o identificador do campo corrente

	Comments:

***/
UINT
LBSC_Base::GetCurrFieldId()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrFieldId") );

	SetError( LBS_OK );
	return( (lbscrCurrRecord.CurrentField())->GetId() );
}




/***
***/
BOOL
LBSC_Base::CheckFieldType( UINT uiId, TFieldType tftFieldType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CheckFieldType") );

/*	if( GetFieldObj( uiId ) == NULL ){
		SetError( LBSE_FIELDNOTFOUND );
		return( FALSE );
	}*/
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	if( !pf ){
		SetError( LBSE_FIELDNOTFOUND );
		return( FALSE );
	}
	if( pf->GetType() != tftFieldType ){
		SetError( LBSE_INVALIDFIELDTYPE );
		return( FALSE );
	}
	SetError( LBS_OK );
	return( TRUE );
}

/***
***/
int
LBSC_Base::SetOwnerBase()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetOwnerBase") );

	if( lbscrCurrRecord.GetNumberOfFields() == 0 ){
		// nao ha' campos na base
		ERETURN( LBS_OK );
	}

	for ( int i=0; i<lbscrCurrRecord.GetNumberOfFields(); i++ ) {
		LBSC_Field *pField = lbscrCurrRecord[i];
		if ( !pField ) {
			ERETURN( LBSE_ERROR );
		}
		pField->plbscbBase = this;
	}

	ERETURN( LBS_OK );
}


/***
***/
int
LBSC_Base::ACLFind( const char *szName, long lId, char *szId, int iList, BYTE bMask, BOOL bFirst )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ACLFind") );

	LBSC_ACLList	*plbscalACLList;

	if( !szName ){
		ERETURN( LBSE_BADARG );
	}
	switch( iList ){
	case USERBASE:
		plbscalACLList = &lbscaBaseUserAcl;
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;

	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;

	case USERFIELD:
		plbscalACLList = &lbscaFieldUserAcl;
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;

	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	
	case USERRECORD:
		plbscalACLList = &lbscaRecordUserAcl;
		if( ( LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ) &&
		    ( LB1.tcrHead.bBaseType != BASE_PRIVATE_REC_PRIVATE ) ){
		    	// a base nao possui restricao de registro
			ERETURN( LBS_OK );
		}
		break;
	
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		if( ( LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ) &&
		    ( LB1.tcrHead.bBaseType != BASE_PRIVATE_REC_PRIVATE ) ){
		    	// a base nao possui restricao de registro
			ERETURN( LBS_OK );
		}
		break;
	
	case USERFORM:
		plbscalACLList = &lbscaFormUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	
	case USERREPORT:
		plbscalACLList = &lbscaReportUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
		    	// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	default:
		ERETURN( LBSE_BADARG );
	}

	// Verifica se o cara que estah logado eh o dono do
	// registro corrente (somente se este metodo for
	// chamado para verificar ACL de registro)
	if( (iList == USERRECORD) || (iList == GROUPRECORD) ){
		if( lbscrCurrRecord.GetOwnerName() && plbscsOwnerSession->GetUserName() ){
			if( stricmp( (char*) lbscrCurrRecord.GetOwnerName(),
				    (char*)plbscsOwnerSession->GetUserName() ) == 0 ){
				ERETURN( LBS_OK );
			}
		}
	} else {
		// verifica se o cara que estah logado eh o dono
		// da base (somente se este metodo for chamado
		// para verificar ACL de campo ou de base ou componente)
		if( LB1.tcrHead.szOwnerName == plbscsOwnerSession->GetUserName() && 
				LB1.tcrHead.bBaseType != USER_BASE ){
			ERETURN( LBS_OK );
		}
//		// verifica se o cara que esta' logado informou a password da base corretamente
//		// no OpenBase
//		if( bIsBasePasswdCorrect ){
//			ERETURN( LBS_OK );
//		}
	}

	if( lId == ID_ASTERISK && ((iList == USERFIELD) || (iList == GROUPFIELD)) ){
		// verificar todos os campos ateh achar um que satisfaca
		int	iNumFields = GetNumberOfFields();
		for( int i = 0; i < iNumFields; i++ ){
			LBSC_Field	*pf = lbscrCurrRecord[ i ];
			if( !pf ){
				ERETURN( LBSE_FIELDNOTFOUND );
			}
			if( plbscalACLList->ACLFind( (char*) szName, pf->GetId() ) == LBS_OK ){
				int	iPerm = plbscalACLList->Current()->lbscplPermList.Current()->bPermission;
				if( ((iPerm & bMask) || ((bMask == ACL_ASTERISK) && iPerm != 0)) ){
					// pelo menos uma permissao foi encontrada
					ERETURN( LBS_OK );
				}
			}
		}
		// o cara nao tem nenhuma permissao para nenhum campo
		ERETURN( LBSE_UNDEFINEDACL );
	} else {
		// verificar em um campo/registro (pode ser especifico ou NAME_ASTERISK)
		int iRet = ISCOMPONENTLIST( iList ) ? plbscalACLList->ACLFind( (char*)szName, szId, bFirst ) : plbscalACLList->ACLFind( (char*)szName, lId, bFirst );
		if( iRet != LBS_OK ){
			ERETURN( LBSE_UNDEFINEDACL );
		}
	}
	int	iPerm = plbscalACLList->Current()->lbscplPermList.Current()->bPermission;

	// atencao: ACL_ASTERISK nao eh "todos os bits ligados"... 
	if( (!(iPerm & bMask) && ((bMask != ACL_ASTERISK) || iPerm == 0)) ){
		// devemos tentar outro cara da lista, se a permissao nao bate com o que queremos
		// e: ou nao pedimos ACL_ASTERISK, ou pedimos e a ACL achada foi nenhuma

		if( strcmp( szName, NAME_ASTERISK ) == 0 ){
			// temos que procurar mais.
			if( plbscalACLList->Next() ){
				return( this->ACLFind( szName, lId, szId, iList, bMask, FALSE ) );
			}
		}
		ERETURN( LBSE_NOPERMISSION );
	}
	if( iPerm != 15 && bMask == ACL_ADM ){
		ERETURN( LBSE_NOPERMISSION );
	}
	ERETURN( LBS_OK );
}


/***
	Procura um conjunto de permissoes de grupo de um usuario especificado
***/
int
LBSC_Base::ACLGroupFind( const char *szUserName, const char *szGroupName, long lId, char *szId, int iList, BYTE bMask )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ACLGroupFind") );

	if( !szUserName || !szGroupName ){
		ERETURN( LBSE_BADARG );
	}
	switch( iList ){
	case GROUPBASE:
	case GROUPFIELD:
	case GROUPFORM:
	case GROUPREPORT:
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC ) ||
		    ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ){
			// a base nao eh privada
			ERETURN( LBS_OK );
		}
		break;
	case GROUPRECORD:
		if( ( LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE ) &&
		    ( LB1.tcrHead.bBaseType != BASE_PRIVATE_REC_PRIVATE ) ){
		    	// a base nao possui restricao de registro
			ERETURN( LBS_OK );
		}
		break;
	default:
		// este metodo trabalha somente com grupos
		ERETURN( LBSE_BADARG );
	}

	if( ISCOMPONENTLIST( iList ) ){
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
	}
	if( strcmp( szGroupName, NAME_ASTERISK ) != 0 ){
		// so' temos um grupo. Neste caso, nao ha' diferenca entre este metodo
		// e o metoro ACLFind, pois o nome do usuario nao interessa.
		return( ACLFind( szGroupName, lId, szId, iList, (bMask == ACL_BEST) ? ACL_ADM : bMask ) );
	}

	// agora vamos analisar as ACLs de cada grupo do usuario

	LBSC_ACLList	*plbscalACLList;
	switch( iList ){
	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		break;
	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		break;
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		break;
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		break;
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		break;
	default:
		// este metodo trabalha somente com grupos
		ERETURN( LBSE_BADARG );
	}

	// vamos pegar os grupos do usuario szUserName
	char *szGrp = plbscsOwnerSession->GetGroups( plbscsOwnerSession->plbsctTicket, 
							(char*) szUserName, 
							!strcmp( szUserName, plbscsOwnerSession->GetUserName() ) );
	if( !szGrp ){
		// o cara nao possui nenhum grupo. Entao, nao possui permissao
		// definida.
		ERETURN( LBSE_UNDEFINEDACL );
	}

	// vamos tentar a permissao requerida para cada um dos grupos retornados em
	// szGrp:

	C_StrTok	cStrTok;
	char		*szToken = cStrTok.StrTok( szGrp, " " );

	if( plbscalACLList->NumElem() <= 0 ){ // nao temos elementos no grupo; nao deve ser possivel, mas ...
		ERETURN( LBSE_UNDEFINEDACL );
	}

	int iPerm = LBSE_UNDEFINEDACL;
	int	iIdxACL = 0;
	int	iIdxPerm = 0;
	while( szToken ){

		int iRet = ACLFind( szToken, lId, szId, iList, ((bMask == ACL_BEST) || (bMask == ACL_ASTERISK)) ? ACL_ADM : bMask );

		if ( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ) { // achamos alguma permissao valida

			// vamos ver se esta permissao eh melhor do que a que ja temos
			int	iPermAux = plbscalACLList->Current()->lbscplPermList.Current()->bPermission;
			int iNumBits = ContaBits(iPerm);
			int iNumBitsAux = ContaBits(iPermAux);

			if( (iPerm == LBSE_UNDEFINEDACL) || (iNumBitsAux > iNumBits) || 
					( (iNumBitsAux == iNumBits) && (iPermAux > iPerm) )) {  
				iPerm = iPermAux;
				iIdxACL = plbscalACLList->GetCurrentIndex();
				iIdxPerm = plbscalACLList->Current()->lbscplPermList.GetCurrentIndex();
			}
		}

		// vamos procurar em outro grupo
		szToken = cStrTok.StrTok( NULL, " " );
	}

	// chegamos aqui e estamos prontos para analisar a melhor permissao encontrada

	delete szGrp;

	if ( iPerm == LBSE_UNDEFINEDACL ) { // nao encontramos nada
		ERETURN( LBSE_UNDEFINEDACL );
	}

	// encontramos alguma coisa...

	if ( (bMask != ACL_BEST) && (bMask != ACL_ASTERISK) && ((iPerm & bMask) != bMask)) { 
		// pedimos uma ACL especifica e nao achamos 
		ERETURN( LBSE_UNDEFINEDACL );
	}

	// posicionar na posicao encontrada ...
	plbscalACLList->Nth( iIdxACL );
	plbscalACLList->Current()->lbscplPermList.Nth( iIdxPerm );

	if ( iPerm == ACL_NONE ) { // a melhor permissao encontrada eh nao poder nada...
		ERETURN( LBSE_NOPERMISSION );
	}

	ERETURN( LBS_OK );
}


/***
	PRIVATE
	CheckUniqueKey
	Checks if the some data in the current record matches with
	some unique-key inside the index system.

	Parameters:
		-

	Return:
		- LBS_OK if there isn't a key that matches or
		  LBS_DUPKEY if there is a key or
		  an error.

	Comments:
		-

***/
int
LBSC_Base::CheckUniqueKey()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CheckUniqueKey") );

	int	iRet = LBS_OK;
	int	iCurrKey = -1;

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	char szRetKey [ DEFAULT_MAXKEYSIZE + 1 ];

	memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );

	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];

		if( !pf || (LastError() ==  LBSE_FIELDNOTFOUND) ){
			ERETURN( LBSE_ERROR );
		}
		if( (pf->GetIndexAttrib() & UNIQUETREE) && (pf->bFlagUpdate) ){
			// campo eh chave unica e foi alterado.
			char szKey [ DEFAULT_MAXKEYSIZE + 1 ];
			int	iNumRep = pf->GetNumberOfRepetition();
			for( int j = 0; j < iNumRep; j++ ){
				LBSC_Data	*pd = (*pf)[ j ];

				if ( !pd || !pd->IsModified() ) { 
					continue;
				}

				memset( szKey, 0, DEFAULT_MAXKEYSIZE + 1 );

				if( pd ){
					switch( pf->GetType() ){
					case BYTE_FIELD:
						memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
						ltoa( (BYTE) (*pd), (char*) szKey, 10 );
						break;

					case SINT_FIELD:
						memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
						ltoa( (short int) (*pd), (char*) szKey, 10 );
						break;

					case VALUE_FIELD:
						memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
						ltoa( (long) (*pd), (char*) szKey, 10 );
						break;

					case DVALUE_FIELD:
						memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
						gcvt( (double) (*pd), DECPART, (char*) szKey );
						break;

					case FLOAT_FIELD:
						memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
						gcvt( (float) (*pd), DECPART, (char*) szKey );
						break;

					case REFERENCED_FIELD:
					case ALPHA_FIELD:
					case TEXT_FIELD:
						{
							char	szNormKey [ DEFAULT_MAXKEYSIZE + 1 ];
							
							memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
							memset( szKey, 0, DEFAULT_MAXKEYSIZE + 1 );
							memset( szNormKey, 0, DEFAULT_MAXKEYSIZE + 1 );

							if ( pf->GetType() == REFERENCED_FIELD ) {
								strncpy( szKey, (char*) (((LBSC_Reference*) (*pd))->szFileName), DEFAULT_MAXKEYSIZE );
							} else {
								strncpy( szKey, (char*) (*pd), DEFAULT_MAXKEYSIZE );
							}

							if( szNormKey ){
								// normaliza szKey
								strncpy( szNormKey, szKey, DEFAULT_MAXKEYSIZE );
								if( PreStandardize( szNormKey, DEFAULTSTANDARDIZERARRAY ) == 0 ){
									// deu certo a normalizacao. vamos fazer com que szKey 
									// assuma o termo normalizado.
									strcpy( szKey, szNormKey);
								}
							}

						}
						break;

					case DATE_FIELD:
						{
							memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
							C_Date	cd = JULIANDATE( (JulTy) (*pd) );
							sprintf( (char*) szKey, "%02d/%02d/%04d", cd.Month(), cd.DayOfMonth(), cd.Year() );
						}
						break;

					case TIME_FIELD:
						{
							memset( szRetKey, 0, DEFAULT_MAXKEYSIZE + 1 );
							C_Time	ct = SECONDTIME( (JulTy) (*pd) );
							sprintf( (char*) szKey, "%02d:%02d", ct.Hour(), ct.Minute() );
						}
						break;
					}
					// ini m@x
					if( plbscisIndexSystem->LT_GetKey( UNIQUETREE, (char*) szKey, (char*) szRetKey, EQUAL_KEY, (long) pf->uiFieldId ) ==  0 ){
						LTC_OCCURRENCELIST *pOL = plbscisIndexSystem->LT_GetListOfCurrentKey( UNIQUETREE );
						LTC_OCCURRENCE *pOc = pOL ? pOL->LT_GetFirstOccurrence() : NULL;
						if ( !bAppendingRec && pOc && pOc->LT_GetSet() == LB1.R_CurPos() ) {
							// a duplicacao ocorreu ao salvar o registro corrente; se o campo eh multivalorado, 
							// e nao ocorreu duplicacao em suas repeticoes, foi um erro devido ao novo esquema
							// de indexacao bufferizada (juntar tudo num buffer e desindexar; neste momento ainda nao foi
							// desindexado o conteudo em que houve erro, mas sera). Se este for o caso devemos desprezar
							// o erro de chave unica
							for ( int k=0; k<iNumRep ; k++ ) {
								if ( k == j ) {
									// essa repeticao nao deve ser testada; eh ela que estamos querendo comparar, ne?
									continue;
								}
								LBSC_Data	*pdTest = (*pf)[ k ];

								if ( !pdTest ) { 
									continue;
								}

								if ( pdTest->Compare(pd, CMPDATA) == 0 ) {
									// achou...
									break;
								}
							}

							if ( k >= iNumRep ) {
								// nao ha duplicatas; releve o erro...
								continue;
							}
						}

						iRet = LBSE_DUPKEY - LBSERROR_OFFSET - (int)pf->uiFieldId;
						j = pf->GetNumberOfRepetition();
						i = GetNumberOfFields();
					}
				}  
			}
		}
	}

	ERETURN( iRet );
}



/***
	PRIVATE
***/
int
LBSC_Base::GotoRec( const LBSC_Ticket *lbscTicket, long lPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GotoRec") );

	long	lOldPos = LB1.R_CurPos();

	if( LB1.R_Seek( lPos ) != LBS_OK ){
		ERETURN( LBSE_INVALIDRECPOSITION );
	}
	if( ReadRecord( lbscTicket ) != LBS_OK ){
		int	iErr = LastError();

		// podemos contar com isso
		if( LB1.R_Seek( lOldPos ) == LBS_OK ){
			if( ReadRecord( lbscTicket ) == LBS_OK ){
				ERETURN( iErr );
			}
		}
		ERETURN( LBSE_FATAL );
	}
	ERETURN( LBS_OK );
}



/***
	Metodo IndexLT
        Faz indexacao utilizando o metodo LT_IndexGroup, da GREEN. Este
        metodo chama o metodo da GREEN para cada um dos indices contidos
        no parametro iIndexAttrib, ao inves de chama-lo de uma so' vez
        para todos os indices.

        Parameters:
			- plbscisIndexSystem	-> ponteiro para o sistema de indices
			- iIndexAttrib	-> mascara com os indices que serao usados
			- lRecNum		-> numero do registro
			- uiFieldId		-> identificador do campo
			- iRep			-> numero da repeticao
			- pParser		-> ponteiro para o parser

        Return:
        	- LBS_OK em caso de sucesso ou um valor negativo

        Comments:

***/
int
LBSC_Base::IndexLT( LBSC_IndexSystem *plbscisIndexSystem,
					int iIndexAttrib,
					long lRecNum,
					LBSC_Field *pField,
					int iRep,
					LTC_PARSER *pParser )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IndexLT") );

	int iType = STOPWORD;

	if( pField->pltcgwGoWords && pField->pltcgwGoWords->LT_GetNbrOfTerm() != 0 ){
		// indexar com gowords.
		// setar gowords na LT
		SetGowords( pField->pltcgwGoWords );
		iType = GOWORD;
	}

	if( iIndexAttrib == 0 ){
		ERETURN( LBS_OK );
	}
	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	int	iRet = LBSE_INVALIDINDEXTYPE;

	iIndexAttrib &= (~EMPTYTREE);	// o indice vazio eh tratado aa parte
	iIndexTree = iIndexAttrib;
	if( (iIndexAttrib != UNIQUETREE) && 
		(iIndexAttrib != ENTIRETREE) && 
		(iIndexAttrib != (UNIQUETREE | ENTIRETREE)) ){
		iIndexTree = (iIndexAttrib & ~(UNIQUETREE | ENTIRETREE));

		// indexar desconsiderando as arvores UNIQUETREE e ENTIRETREE,
		// que devem ser tratadas separadamente (parsers diferentes...)

		iRet = plbscisIndexSystem->LT_IndexGroup(
					( int ) iIndexTree,
					( unsigned long )  lRecNum,
					( unsigned short ) pField->GetId(),
					( unsigned short ) iRep,
					( LTC_PARSER far* )pParser,
					iType );

		if ( iRet == LBS_OK && MustIndexLast( pField->GetId(), iRep ) ) {
			// indexar tambem a MAXREPETITION; 
			iRet = plbscisIndexSystem->LT_IndexGroup(
						( int ) iIndexTree,
						( unsigned long )  lRecNum,
						( unsigned short ) pField->GetId(),
						( unsigned short ) MAXREPETITION,
						( LTC_PARSER far* )pParser,
						iType );
		}
	}
	if( (iIndexAttrib & UNIQUETREE) || (iIndexAttrib & ENTIRETREE) ){
		iIndexTree = (iIndexAttrib & UNIQUETREE) ? UNIQUETREE | ( (iIndexAttrib & ENTIRETREE) ? ENTIRETREE : 0 ) : ENTIRETREE;

		// agora vamos indexar UNIQUETREE e/ou ENTIRETREE
		iRet = plbscisIndexSystem->LT_IndexGroup(
					( int ) iIndexTree,
					( unsigned long )  lRecNum,
					( unsigned short ) pField->GetId(),
					( unsigned short ) iRep,
					( LTC_PARSER far* )pParser,
					iType );

		if ( iRet == LBS_OK && MustIndexLast( pField->GetId(), iRep ) ) {
			// indexar tambem a MAXREPETITION; 
			iRet = plbscisIndexSystem->LT_IndexGroup(
						( int ) iIndexTree,
						( unsigned long )  lRecNum,
						( unsigned short ) pField->GetId(),
						( unsigned short ) MAXREPETITION,
						( LTC_PARSER far* )pParser,
						iType );
		}
		
	}
	iIndexTree = 0;
	ERETURN( iRet );
}

/***
	Metodo UnindexLT
        Faz desindexacao utilizando o metodo LT_UnindexGroup, da GREEN. Este
        metodo chama o metodo da GREEN para cada um dos indices contidos
        no parametro iIndexAttrib, ao inves de chama-lo de uma so' vez
        para todos os indices.

        Parameters:
			- plbscisIndexSystem	-> ponteiro para o sistema de indices
			- iIndexAttrib	-> mascara com os indices que serao usados
			- lRecNum		-> numero do registro
			- uiFieldId		-> identificador do campo
			- iRep			-> numero da repeticao
			- pParser		-> ponteiro para o parser

        Return:
        	- LBS_OK em caso de sucesso ou um valor negativo

        Comments:

***/
int
LBSC_Base::UnindexLT( LBSC_IndexSystem *plbscisIndexSystem,
					int iIndexAttrib,
					long lRecNum,
					LBSC_Field *pField,
					int iRep,
					LTC_PARSER *pParser )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UnindexLT") );

	int iType = STOPWORD;

	if( pField->pltcgwGoWords && pField->pltcgwGoWords->LT_GetNbrOfTerm() != 0 ){
		// desindexar com gowords.
		// setar gowords na LT
		SetGowords( pField->pltcgwGoWords );
		iType = GOWORD;
	}

	if( iIndexAttrib == 0 ){
		ERETURN( LBS_OK );
	}
	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	int	iRet = LBSE_INVALIDINDEXTYPE;
	
	iIndexAttrib &= (~EMPTYTREE);	// o indice vazio eh tratado aa parte
	iIndexTree = iIndexAttrib;
	((LBSC_Parser*)pParser)->bIndexing = FALSE;
	if( (iIndexAttrib != UNIQUETREE) && 
		(iIndexAttrib != ENTIRETREE) && 
		(iIndexAttrib != (UNIQUETREE | ENTIRETREE)) ){
		iIndexTree = (iIndexAttrib & ~(UNIQUETREE | ENTIRETREE));

		// desindexar desconsiderando as arvores UNIQUETREE e ENTIRETREE,
		// que devem ser tratadas separadamente
		iRet = plbscisIndexSystem->LT_UnindexGroup(
					( int ) iIndexTree,
					( unsigned long )  lRecNum,
					( unsigned short ) pField->GetId(),
					( unsigned short ) iRep,
					( LTC_PARSER far* )pParser,
					iType );

		if ( iRet == LBS_OK && MustUnIndexLast(pField->GetId(), iRep) ) {
			// tenta desindexar tambem a repeticao MAXREPETITION 
			iRet = plbscisIndexSystem->LT_UnindexGroup(
						( int ) iIndexTree,
						( unsigned long )  lRecNum,
						( unsigned short ) pField->GetId(),
						( unsigned short ) MAXREPETITION,
						( LTC_PARSER far* )pParser,
						iType );

		}
	}
	if( (iIndexAttrib & UNIQUETREE) || (iIndexAttrib & ENTIRETREE) ){
		iIndexTree = (iIndexAttrib & UNIQUETREE) ? UNIQUETREE | ( (iIndexAttrib & ENTIRETREE) ? ENTIRETREE : 0 ) : ENTIRETREE;
		// agora vamos desindexar UNIQUETREE e/ou ENTIRETREE
		iRet = plbscisIndexSystem->LT_UnindexGroup(
					( int ) iIndexTree,
					( unsigned long )  lRecNum,
					( unsigned short ) pField->GetId(),
					( unsigned short ) iRep,
					( LTC_PARSER far* )pParser,
					iType );

		if ( iRet == LBS_OK && MustUnIndexLast(pField->GetId(), iRep) ) {
			// tenta desindexar tambem a repeticao MAXREPETITION 
			iRet = plbscisIndexSystem->LT_UnindexGroup(
						( int ) iIndexTree,
						( unsigned long )  lRecNum,
						( unsigned short ) pField->GetId(),
						( unsigned short ) MAXREPETITION,
						( LTC_PARSER far* )pParser,
						iType );
		}
	}
	iIndexTree = 0;
	((LBSC_Parser*)pParser)->bIndexing = TRUE;
	ERETURN( iRet );
}


/***
	PRIVATE
	Metodo SetStopWord
	Seta o conjunto de StopWords do SI de uma base

	Parameters:
		-

	Return:
		- LBS_OK.

	Comments:
		- Este metodo eh usado sempre que o LBS vai fazer alguma operacao que
		  possa envolver StopWords (indexacao, por exemplo)
		- Este metodo le^ o arquivo STOPWORD.LB e seta a lista interna
		  de stop-words.

***/
int
LBSC_Base::SetStopWord()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetStopWord") );

	char			szAux[ FULLNAMESIZE ];
	LTC_TERMLIST	*ptAux = NULL;

	if( !plbscisIndexSystem || !pBaseInstance ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if ( pBaseInstance->BaseStructLoaded() ) {
		LTC_TERMVECT *pCurrVect = pBaseInstance->StopWordVect; 

		LTC_TERMVECT *pNewVect = pBaseInstance->StopWordVect->Duplicate();
		if ( !pNewVect ) {
			ERETURN( LBSE_NOMEMORY );
		}
		LTC_TERMVECT *pOrigVect = plbscisIndexSystem->LT_SetStopWord( pNewVect );
		if( pOrigVect ){
			delete pOrigVect;
		}
		ERETURN( LBS_OK );
	}

	sprintf( szAux,"%s\\%s", (char*) szBasePath, STOPWORDFILENAME );
	char	*szSWSet1 = NULL;
	char	*szSWSet2 = NULL;
	C_File 	cfStopWordFile( szAux, "rt" );
	if( !cfStopWordFile.IsOpen() ){
		// nao conseguimos abrir o arquivo. nao vamos setar stopwords
		LTC_TERMVECT *pVect = new LTC_TERMVECT(0);
		pBaseInstance->StopWordVect = pVect;
		ERETURN( LBS_OK );
	} else {
		int iSize = cfStopWordFile.FileSize();
		szSWSet1 = new char[iSize+1];
		if ( !szSWSet1 ) {
			ERETURN( LBSE_NOMEMORY );
		}
		if ( cfStopWordFile.Read( szSWSet1, iSize ) != OK ) {
			// deu erro na leitura das stopwords
			// nao vamos setar stopwords
			delete szSWSet1;
			ERETURN( LBS_OK );
		}
		szSWSet1[iSize] = '\0';
		szSWSet2 = Strdup(szSWSet1);
		if ( !szSWSet2 ) {
			delete szSWSet1;
			ERETURN( LBSE_NOMEMORY );
		}
	}

	// primeiro contar quantas tem
	C_StrTok	cStrTok;
	char		*szTok = cStrTok.StrTok( szSWSet1, " \r\t\n" );
	for ( int iStopCount=0; szTok; szTok = cStrTok.StrTok( NULL, " \r\t\n" ) ) {
		iStopCount++;
	}

	// agora criar as stopwords de fato
	LTC_TERMVECT *pVect = new LTC_TERMVECT(iStopCount);
	szTok = cStrTok.StrTok( szSWSet2, " \r\t\n" );
	for ( int i=0; szTok; szTok = cStrTok.StrTok( NULL, " \r\t\n" ), i++ ) {
		// normaliza o termo antes de mandar para a LT
		char *szTerm = Strdup(szTok);
		if ( szTerm ) {
			PreStandardize( szTerm, DEFAULTSTANDARDIZERARRAY );
		}
		pVect->SetTerm( szTerm, i );
	}
	pVect->Sort();

	delete szSWSet1;
	delete szSWSet2;
	LTC_TERMVECT *pOrigVect = plbscisIndexSystem->LT_SetStopWord( pVect );
	if( pOrigVect ){
		delete pOrigVect;
	}
	pBaseInstance->StopWordVect = pVect->Duplicate();
	ERETURN( LBS_OK );
}


void LBSC_Base::SetGowords( LTC_TERMLIST *pTermList )
{
	LTC_TERMVECT *pVect = new LTC_TERMVECT(pTermList->LT_GetNbrOfTerm());
	if ( !pVect ) {
		return;
	}
	pTermList->LT_GetFirstTerm();
	for ( int i=0; i<pTermList->LT_GetNbrOfTerm(); i++ ) {
		char *szTerm = Strdup(pTermList->LT_GetCurrentTerm());
		pVect->SetTerm( szTerm, i );
		pTermList->LT_GetNextTerm();
	}
	pVect->Sort();
	LTC_TERMVECT *pOldVect = plbscisIndexSystem->LT_SetGoWord( pVect );
	if ( pOldVect ) {
		// o LT_SetGoWord guarda a lista passada como parametro e retorna a que estava 
		// usando. Essa lista retornada deve ser deletada.
		delete pOldVect;
	}
}

/***
	PRIVATE
	Metodo VerifyPermission
	Verifica as permissoes de ACL para usuario e para todos os grupos do usuario.

	Parameters:
		- szName	-> nome do usuario
		- lId		-> id do campo ou numero do registro
		- iList		-> tipo de ACL a ser checada (USERFIELD ou USERRECORD)
		- bMask		-> permissao a ser checada

	Return:
		- LBS_OK para indicar que o usuario possui algum acesso;
		  LBSE_NOPERMISSION para indicar que nenhum acesso foi encontrado
		  nas ACLs.

	Comments:
		- Se a base aberta for uma UDB, entao este metodo retorna OK, pois
		  so' quem pode abrir uma UDB e' o proprio LBS e ele possui full
		  access.
		- Este metodo preve^ em seu algoritmo que iList eh USERFIELD ou
		  USERRECORD. Para outros valores, o funcionamento nao foi previsto.
		- Caso a permissao desejada nao seja encontrada nas ACLs de usuario,
		  as ACLs da base serao percorridas. Se ainda assim nao for encontrada
		  a permissao, as ACLs de todos os grupos pertencentes ao usuario 
		  serao verificadas. Se o erro persistir, as ACLs de grupo da base
		  serao verificadas. Se em nenhuma das tentativas a permissao for
		  encontrada, entao o metodo retornara' erro.

***/
int
LBSC_Base::VerifyPermission( const char *szName, long lId, int iList, BYTE bMask )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::VerifyPermission") );

	// se a base es questao for uma UDB, e nao setamos ainda as permissoes 
	// podemos retornar OK; neste caso quem abre e' o proprio LBS.
	if( LB1.tcrHead.bBaseType == USER_BASE && 
			lbscaBaseUserAcl.NumElem() == 0 &&
			lbscaFormUserAcl.NumElem() == 0 &&
			lbscaReportUserAcl.NumElem() == 0 &&
			lbscaFieldUserAcl.NumElem() == 0 ){
		ERETURN( LBS_OK );
	}

	// tambem devemos liberar se a base for publica.
	if( LB1.tcrHead.bBaseType == BASE_PUBLIC ){
		ERETURN( LBS_OK );
	}

	// ALGORITMO DESTE METODO
	// se a ACL a ser checada for USERRECORD e a base nao possuir restricao
	// a registros, entao checar somente as ACLs de base e retornar o resultado
	// encontrado
	// senao:
	// checar em USERFIELD/USERRECORD
	// 	se nao encontrou nada, checar em USERBASE
	// 		se nao encontrou nada, checar em GROUPFIELD/GROUPRECORD
	// 			se nao encontrou nada, checar em GROUPBASE
	// 				se nao encontrou nada, retornar erro
	// retornar ok

	// verifica se o cara que esta' logado informou a password da base corretamente
	// no OpenBase (se szName for o cara logado)
	if( stricmp( (char*) plbscsOwnerSession->GetUserName(), szName ) == 0 && bIsBasePasswdCorrect ){
		ERETURN( LBS_OK );
	}
	if( iList == USERRECORD ){
		if( (LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE) && (LB1.tcrHead.bBaseType != BASE_PRIVATE_REC_PRIVATE) ){
			// estamos tentando verificar permissoes de USERRECORD, mas a base
			// nao possui restricao de registro. Entao vamos converter a consulta em
			// USERFIELD, com ID_ASTERISK
			iList = USERFIELD;
			lId = ID_ASTERISK;
		}
	} else {
		if( iList == GROUPRECORD ){
			if( (LB1.tcrHead.bBaseType != BASE_PUBLIC_REC_PRIVATE) && (LB1.tcrHead.bBaseType != BASE_PRIVATE_REC_PRIVATE) ){
				// estamos tentando verificar permissoes de GROUPRECORD, mas a base
				// nao possui restricao de registro. Entao vamos converter a consulta em
				// GROUPFIELD, com ID_ASTERISK
				iList = GROUPFIELD;
				lId = ID_ASTERISK;
			}
		}
	}
	int	iPerm = LBSE_UNDEFINEDACL;
	if( (iList != USERRECORD) || 
		( (LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE) || 
		  (LB1.tcrHead.bBaseType == BASE_PRIVATE_REC_PRIVATE ) ) ){
		iPerm = ACLFind( szName, lId, NULL, iList, bMask );
	}

	// checar em USERFIELD/USERRECORD
	if( iPerm != LBS_OK && iPerm != LBSE_NOPERMISSION ){
		// checar em USERBASE
		iPerm = ACLFind( szName, ID_BASE, NULL, USERBASE, bMask );
		if( iPerm != LBS_OK && iPerm != LBSE_NOPERMISSION ){
			// checar as ACLs por grupo (todos os grupos do usuario logado)
			if( (iList != USERRECORD) || 
				( (LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE) || 
				  (LB1.tcrHead.bBaseType == BASE_PRIVATE_REC_PRIVATE ) ) ){
				switch( iList ) {
				case USERBASE:
					iList = GROUPBASE;
					break;

				case USERFIELD:
					iList = GROUPFIELD;
					break;

				case USERRECORD:
					iList = GROUPRECORD;
					break;

				case USERFORM:
					iList = GROUPFORM;
					break;

				case USERREPORT:
					iList = GROUPREPORT;
					break;
				}
				iPerm = ACLGroupFind( szName, NAME_ASTERISK, lId /*ID_ASTERISK*/, NULL,
				  iList, bMask );
			}
		}
	}
	ERETURN( iPerm );
}


/***
	PRIVATE
	Metodo SetFullAccessMode
	Seta o estado da flag bFullAccess

	Parameters:
		- bFlag -> novo estado de bFullAccess

	Return:
		- 

	Comments:
		-

***/
void
LBSC_Base::SetFullAccessMode( BOOL bFlag )
{
	bFullAccess = bFlag;
}


/***
	PRIVATE
	Metodo PreStandardize
	Realiza uma normalizacao em uma string.

	Parameters:
		- szBuffer	-> buffer a ser normalizado
		- szStdStr	-> string de normalizacao. o valor deault eh
				   PRESTANDARDIZEARRAY

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- A normalizacao eh feita dependendo da string de normalizacao passada
		  como segundo parametro.
		- A alteracao eh feita no proprio buffer passado como parametro.
		- Qualquer alteracao neste metodo deve ser refletida na copia dele
		  que foi feita para brilhar palavras nos controls de Alessandro.

***/
int
LBSC_Base::PreStandardize( char *szBuffer, char *szStdStr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PreStandardize") );

	if( !szBuffer ){
		ERETURN( LBSE_BADARG );
	}
	int iLen = strlen( szBuffer );
	for( int i = 0; i < iLen; i++ ){
		szBuffer[ i ] = szStdStr[ (unsigned char) szBuffer[ i ] ];
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo CopyFile
	Copia um C_File para outro

	Parameters:
		- pcfDest	-> arquivo destino
		- pcfSource	-> arquivo de origem

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- os dois arquivos devem estar abertos.
		- o arquivo destino deve estar na posicao (SEEK) desejada para a
		  copia; este metodo nao altera a posicao inicial dele
		- o arquivo de origem sofrera' seek para seu inicio antes da copia.

***/
int
LBSC_Base::CopyFile( C_File *pcfDest, C_File *pcfSource )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CopyFile") );

	if( !pcfDest || !pcfSource || !pcfDest->IsOpen() || !pcfSource->IsOpen() ){
		return( LBSE_ERROR );
	}
	pcfSource->Seek( 0, SEEK_SET );

	long	lInitPos = pcfDest->CurPos();
	char	szBuffer[ K100 ];

	// copiar de forma blocada
	while( pcfSource->Read( szBuffer, K100 ) == OK ){
		pcfDest->Write( szBuffer, K100 );
	}
	// copia caracter a caracter
	while( pcfSource->Read( szBuffer, 1 ) == OK ){
		pcfDest->Write( szBuffer, 1 );
	}
	if( pcfSource->CurPos() != pcfSource->FileSize() ){
		// deu pau
		pcfSource->Seek( 0, SEEK_SET );
		pcfDest->Seek( lInitPos, SEEK_SET );
		return( LBSE_ERROR );
	}
	return( LBS_OK );
}


/***
	PRIVATE
	Metodo DelBaseInfoFile
	Deleta um nome de base do arquivo de informacoes
	(usado apenas em copias REDE)

	Parameters:
		- strBaseName	-> nome da base

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Base::DelBaseInfoFile( BaseSTR &strBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelBaseInfoFile") );

	char			szDirBase[ FULLNAMESIZE ];
	char			szAux[ FILENAMESIZE ];
	char			szInfoFile[ FULLNAMESIZE ];
	C_RecordFile	cInfoFile( CRYPTO_MAGICNUMBER );

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		NRETURN( LBSE_LBSINIERROR );
	}

	// tentar NUMTRYLIC vezes abrir o arquivo
	sprintf( szInfoFile, "%s\\%s", szDirBase, INFOFILENAME );
	for( int i = 0; i < NUMTRYLIC; i++){
		if( cInfoFile.Open( szInfoFile, 0, sizeof( TBaseNetInfo ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cInfoFile.IsOpen() ){
		// nao consegui abrir o arquivo de informacoes
		NRETURN( LBSE_BUSY );
	}
	if( cInfoFile.R_FileSize() <= 0 ){
		ERETURN( LBSE_ERROR );
	} else {
		// fazer loop procurando um registro que tenha uma base
		// com o nome que queremos.
		int	iNumElem = cInfoFile.R_FileSize();
		cInfoFile.R_Seek( 0 );
		for( int i = 0; i < iNumElem; i++ ){
			TBaseNetInfo	tbInfo;

			cInfoFile.R_Read( &tbInfo );
			char *szUserName = (char*) plbscsOwnerSession->GetUserName();
			if( szUserName &&
				stricmp( (char*) tbInfo.strBaseName, (char*) strBaseName ) == 0 &&
				stricmp( (char*) tbInfo.strUserLogged, szUserName  ) == 0 &&
				tbInfo.bDeleted == FALSE ){
				// achamos.
				tbInfo.bDeleted = TRUE;
				cInfoFile.R_Write( &tbInfo );
				break;
			}
			cInfoFile.R_SeekNext();
		}
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo AddBaseInfoFile
	Adiciona um nome de base no arquivo de informacoes
	(usado apenas em copias REDE)

	Parameters:
		- strBaseName	-> nome da base

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Base::AddBaseInfoFile( BaseSTR &strBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddBaseInfoFile") );

	char			szDirBase[ FULLNAMESIZE ];
	char			szAux[ FILENAMESIZE ];
	char			szInfoFile[ FULLNAMESIZE ];
	C_RecordFile	cInfoFile( CRYPTO_MAGICNUMBER );

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		ERETURN( LBSE_LBSINIERROR );
	}

	// tentar NUMTRYLIC vezes abrir o arquivo
	sprintf( szInfoFile, "%s\\%s", szDirBase, INFOFILENAME );
	for( int i = 0; i < NUMTRYLIC; i++){
		if( cInfoFile.Open( szInfoFile, 0, sizeof( TBaseNetInfo ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cInfoFile.IsOpen() ){
		// nao consegui abrir o arquivo de licencas
		ERETURN( LBSE_BUSY );
	}
	if( cInfoFile.R_FileSize() <= 0 ){
		TBaseNetInfo	tbInfo( (char*) strBaseName, (char*) plbscsOwnerSession->GetUserName() );

		cInfoFile.R_Append( &tbInfo );

		ERETURN( LBS_OK );
	} else {
		// fazer loop procurando um registro deletado para reutiliza-lo.
		int	iNumElem = cInfoFile.R_FileSize();
		cInfoFile.R_Seek( 0 );
		for( int i = 0; i < iNumElem; i++ ){
			TBaseNetInfo	tbInfo;

			cInfoFile.R_Read( &tbInfo );
			if( tbInfo.bDeleted ){
				// achamos.
				tbInfo.Set( (char*) strBaseName, (char*) plbscsOwnerSession->GetUserName(), FALSE );
				cInfoFile.R_Write( &tbInfo );
				break;
			}
			cInfoFile.R_SeekNext();
		}
		if( i >= iNumElem ){
			// nao achamos elemento. vamos adicionar um.
			TBaseNetInfo	tbInfo( (char*) strBaseName, (char*) plbscsOwnerSession->GetUserName() );

			cInfoFile.R_Append( &tbInfo );
		}
	}
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo PrivNextRec
	Obtem o proximo registro da LO (o proximo registro, nao a proxima
	ocorrencia)

	Parameters:
		- lbscTicket
		- bDeleteCurrent-> indica o numero se deve-se deletar o registro corrente da LO
						   antes de iniciar o processo. O valor default eh FALSE 
		- bTryOther		-> indica se o processo deve tentra ir para o registro
						   anterior caso nao consiga nenhum proximo. O valor
						   default eh FALSE.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::PrivNextRec( const LBSC_Ticket *lbscTicket, BOOL bDeleteCurrent, BOOL bTryOther )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PrivNextRec") );

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// Se a lista de ocorrencias for NULL entao
	// devo retornar o proximo registro da base independente da LO
	if( !plbscolOcurrenceList ){
		return( NextFRecord( lbscTicket ) );
	}

	if( bDeleteCurrent ){
		// tenta retirar da LO corrente todos as ocorrencias que contenham referencias
		// ao registro com problema (que eh sempre o corrente)
		plbscolOcurrenceList->Del();
	} else {
		if ( !plbscolOcurrenceList->Next() ) {
			ERETURN( LBSE_LASTRECORD );
		}
	}

	LTC_OCCURRENCE *pltcOcAux = plbscolOcurrenceList->GetCurrentOccurrence();
	int iRet = LBSE_LASTRECORD;
	while( pltcOcAux ){
		long lRecToNum = (long) pltcOcAux->LT_GetSet();
		// faz release no registro corrente
		ReleaseRecord( lbscTicket );

		iRet = GotoRec( lbscTicket, lRecToNum );
		if( iRet != LBSE_EXCLUDEDREC && iRet != LBSE_FATAL ){
			ERETURN( iRet );
		}
		// seguinte: se aconteceu um erro fatal no 
		// GotoRec, eh porque tentamos posicionar sobre
		// um registro que nao existe, tentamos voltar
		// para o que estavamos, mas ele tambem nao
		// existe. vamos tentar ir para o proximo, ate'
		// chegarmos no final da lista.

		// retira da LO corrente todos as ocorrencias que contenham referencias
		// ao registro apontado pela ocorrencia corrente
		if ( plbscolOcurrenceList->CurPos() == (plbscolOcurrenceList->Size()-1) ) {
			// acabou...
			plbscolOcurrenceList->Del();
			break;
		}
		plbscolOcurrenceList->Del();
		pltcOcAux = plbscolOcurrenceList->GetCurrentOccurrence();
		if( !pltcOcAux ){
			ERETURN( LBSE_NORECORD );
		}
	}
	if( bTryOther ){
		return( PrivPrevRec( lbscTicket ) );
	}
	ERETURN( LBSE_LASTRECORD );
}



/***
	PRIVATE
	Metodo PrivPrevRec
	Obtem o registro anterior da LO (o registro anterior, nao a ocorrencia
	anterior)

	Parameters:
		- bDeleteCurrent-> indica o numero se deve-se deletar o registro corrente da LO
						   antes de iniciar o processo. O valor default eh FALSE 
		- bTryOther		-> indica se o processo deve tentra ir para o proximo
						   registro caso nao consiga nenhum previo. O valor
						   default eh FALSE.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::PrivPrevRec( const LBSC_Ticket *lbscTicket, BOOL bDeleteCurrent, BOOL bTryOther )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PrivPrevRec") );

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// Se a lista de ocorrencias for NULL entao
	// devo retornar o registro anterior da base independente da LO
	if( !plbscolOcurrenceList ){
		return( PreviousFRecord( lbscTicket ) );
	}

	LTC_OCCURRENCE *pltcOcAux;
	if( bDeleteCurrent ){
		// tenta retirar da LO corrente todos as ocorrencias que contenham referencias
		// ao registro com problema (que eh sempre o corrente)
		plbscolOcurrenceList->Del();
	} else {
		if ( !plbscolOcurrenceList->Previous() ) {
			ERETURN( LBSE_FIRSTRECORD );
		}
	}
	pltcOcAux = plbscolOcurrenceList->GetCurrentOccurrence();
	int iRet = LBSE_FIRSTRECORD;
	while( pltcOcAux ){
		long lRecToNum = (long) pltcOcAux->LT_GetSet();
		// faz release no registro corrente
		ReleaseRecord( lbscTicket );

		iRet = GotoRec( lbscTicket, lRecToNum );
		if( iRet != LBSE_EXCLUDEDREC && iRet != LBSE_FATAL ){
			ERETURN( iRet );
		}
		// seguinte: se aconteceu um erro fatal no 
		// GotoRec, eh porque tentamos posicionar sobre
		// um registro que nao existe, tentamos voltar
		// para o que estavamos, mas ele tambem nao
		// existe. vamos tentar ir para o proximo, ate'
		// chegarmos no final da lista.

		// retira da LO corrente todos as ocorrencias que contenham referencias
		// ao registro apontado pela ocorrencia corrente
		plbscolOcurrenceList->Del();
		if ( !plbscolOcurrenceList->Previous() ) {
			// acabou...
			break;
		}
		pltcOcAux = plbscolOcurrenceList->GetCurrentOccurrence();
		if( !pltcOcAux ){
			ERETURN( LBSE_NORECORD );
		}
	}
	if( bTryOther ){
		return( PrivNextRec( lbscTicket ) );
	}
	ERETURN( LBSE_FIRSTRECORD );
}


/***
	PRIVATE
	Metodo GetPhysMemory
	Retorna a quantidade de memoria *fisica* disponivel.

	Parameters:
		- 

	Return:
		- obvio 

	Comments:
		- 

***/
DWORD
LBSC_Base::GetPhysMemory()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetPhysMemory") );

	MEMORYSTATUS	ms;

	memset( &ms, 0, sizeof( ms ) );
	ms.dwLength = sizeof( MEMORYSTATUS );

	GlobalMemoryStatus( &ms );

	return( ms.dwAvailPhys );
}

/***
	PRIVATE
	Metodo GetConstOwnerName
	Obtem o nome do dono da base

	Parameters:

	Return:
		- O nome do dono da base.

	Comments:
		- Este metodo retorna o buffer interno e a aplicacao NAO 
		  deve deletar.

***/
const char *
LBSC_Base::GetConstOwnerName()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetConstOwnerName") );

	SetError( LBS_OK );
	return( (const char*) (char*) LB1.tcrHead.szOwnerName );
}

/***
	PRIVATE
	Metodo PrivIncCount
	Incrementa o valor de um determinado contador da base 
	e retorna o valor resultante

	Parameters:
		- iIndex: o numero do contador;
		- lCount: o valor a ser incrementado (default = 1);

	Return:
		- o valor resultante do incremento ou um erro 
		  (consulte LastError)

	Comments:
		-

***/
long
LBSC_Base::PrivIncCount( int iIndex, long lCount )
{
	C_BaseCritSect	cCS11( this, CRITSECT11 );
	if( iIndex < 0 || iIndex >= LB1.tcrHead.iCountNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB3.bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
		if( !ptsrStructRecHead ){
			ERETURN( LBSE_NOMEMORY );
		}
		if( LB3.LB3_LockHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_HEADERROR );
		}
		ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount += lCount;
		long	lRet = ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount;
		if( LB3.LB3_ReleaseHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_FATAL );
		}
		TStructHeadRec::Free( ptsrStructRecHead );
		SetError( LBS_OK );
		return( lRet );
	}
	long	lAux;

	if( LB3.IncCount( iIndex, lCount, lAux ) == OK ){
		SetError( LBS_OK );
		return( lAux );
	}
	ERETURN( LBSE_ERROR );
}



/***
	PRIVBASE
	Metodo PrivDecCount
	Decrementa o valor de um determinado contador da base
	e retorna o valor resultante da operacao

	Parameters:
		- iIndex: o numero do contador;
		- lCount: o valor a ser decrementado (default = 1);

	Return:
		- o valor resultante da operacao ou um codigo de erro
		  (consulte LastError )

	Comments:
		-

***/
long
LBSC_Base::PrivDecCount( int iIndex, long lCount )
{
	C_BaseCritSect	cCS11( this, CRITSECT11 );
	if( iIndex < 0 || iIndex >= LB1.tcrHead.iCountNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB3.bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
		if( !ptsrStructRecHead ){
			ERETURN( LBSE_NOMEMORY );
		}
		if( LB3.LB3_LockHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_HEADERROR );
		}
		ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount -= lCount;
		long	lRet = ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount;
		if( LB3.LB3_ReleaseHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_FATAL );
		}
		TStructHeadRec::Free( ptsrStructRecHead );
		SetError( LBS_OK );
		return( lRet );
	}
	long	lAux;

	if( LB3.DecCount( iIndex, lCount, lAux ) == OK ){
		SetError( LBS_OK );
		return( lAux );
	}
	ERETURN( LBSE_ERROR );
}


/**********************************************************
// Function name	: LBSC_Base::FillUrlBuffer
// Description	    : 
// Return type		: LBSC_Reference* 
// Argument         : LBSC_Reference *pRef
**********************************************************/
LBSC_Reference* LBSC_Base::FillUrlBuffer( LBSC_Reference *pRef )
{
	if( !pRef || (pRef->iFormat != LBSRT_URL) ){
		NRETURN( LBSE_BADARG );
	}

	// tratar campo com formato URL
	char			szFileName[ MAXPATH ];
	char			szAux[ MAXPATH ];
	char			szDrive[ MAXDRIVE ];
	char			szDir[ MAXDIR ];
	char			szExt[ MAXEXT ];
	char			*szBufferIn = NULL;
	char			*szTmp = NULL;
	C_File			cfRefFile;
	long			lSize = 0;
	LBSC_Reference	*pRefRet = NULL;
	LBSC_Http		cHttp;
	BOOL			bEhTexto = FALSE;
	BOOL			bEhHTML = FALSE;

	if ( pRef->szFileName && pRef->szBuffer && strlen(pRef->szBuffer) != 0 ) {
		// a repeticao  ja esta preenchida, vamos reutiliza-la
		pRefRet = LBSC_Reference::Alloc( strlen(pRef->szBuffer) );
		if( !pRefRet ){
			NRETURN( LBSE_NOMEMORY );
		}
		(*pRefRet) = (*pRef);
		return pRefRet;
	}

	_splitpath( pRef->szFileName, szDrive, szDir, szAux, szExt );
	strcat( szAux, szExt );

	szTmp = strstr( szDir, "://" );
	if( szTmp ){
		szTmp += 3;
	} else {
		szTmp = szDir;
	}

	// ler do LBS.INI o diretorio base para arquivos de referencia
	strncpy( szFileName, LBSC_ServerConfig::ReferenceDirBase(), MAXPATH-1 );

	if( szFileName[0] != '\0' ){
		char	szFileNameAux[ MAXPATH ];

		strcpy( szFileNameAux, szFileName );

		// montar nome do arquivo
		strcat( szFileName, "\\" );
		strcat( szFileName, szTmp );
		strcat( szFileName, szAux );

		if( cfRefFile.Open( szFileName, "rb" ) != OK ){
			// o arquivo nao esta' disponivel.
			// vamos tentar abri-lo no dirbase.
			strcat( szFileNameAux, "\\" );
			strcat( szFileNameAux, szAux );
			if( cfRefFile.Open( szFileNameAux, "rb" ) != OK ){
				// o arquivo nao esta' disponivel.
				NRETURN( LBSE_URLNOTFOUND );
			}
		}
		// beleza. o arquivo esta' aberto.
		// agora temos que filtrar o danado para
		// converte-lo em ascii e depois passar pelo parser
		lSize = cfRefFile.FileSize();
	} else {
		// nao existe dirbase.
		// vamos usar o chupador html
		int			iErr;

		iErr = cHttp.SetWinsockLoaded( TRUE );
		if( !iErr ){
			iErr = cHttp.SetURL( pRef->szFileName );
			if( !iErr ){
				iErr = cHttp.SetAction( HTTP_GET );
			}
		}

		if( iErr ){
			char *szHttpErr = cHttp.GetLastError();
			if ( szHttpErr ) {
				if ( strstr(szHttpErr, "403 ") ) {
					iErr = LBSE_HTTPACCESSFORBIDDEN;
				} else if ( strstr(szHttpErr, "404 ") ) {
					iErr = LBSE_HTTPURLNOTFOUND;
				} else if ( strstr(szHttpErr, "500 ") ) {
					iErr = LBSE_HTTPINTERNALERROR;
				} else if ( strstr(szHttpErr, "503 ") ) {
					iErr = LBSE_HTTPUNAVAILABLE;
				} else if ( strstr(szHttpErr, "504 ") ) {
					iErr = LBSE_HTTPTIMEOUT;
				}
			}
			SetError( iErr );
			SetErrorDesc( szHttpErr );
			return( NULL );
		}

		bEhTexto = strstr( cHttp.ContentType(), "text" ) != NULL ;
		bEhHTML = strstr( cHttp.ContentType(), "html" ) != NULL ;
		lSize = cHttp.lContentSize;
		szBufferIn = cHttp.szContent;
		if( lSize <= 0 ){	// nao trouxe a pagina legal
			SetError( LBSE_HTTPPROTOCOLERROR );
			SetErrorDesc( cHttp.GetLastError() );
			return( NULL );
		}
	}
	pRefRet = LBSC_Reference::Alloc( lSize );
	if( !pRefRet ){
		NRETURN( LBSE_NOMEMORY );
	}
	// copiar os atributos do pRef para o pRefRet
	pRefRet->iFormat = pRef->iFormat;
	memset( pRefRet->szFileName, 0, MAXPATH );
	strncpy( pRefRet->szFileName, pRef->szFileName, MAXPATH-1 );
	if( szFileName[0] != '\0' ){
		// alocar um buffer de entrada
		szBufferIn = new char [ lSize+1 ];
	}
	if( !szBufferIn ){
		// deu pau
		NRETURN( LBSE_NOMEMORY );
	}
	if( szFileName[0] != '\0' ){
		if( cfRefFile.Seek( 0, SEEK_SET ) != OK ||
			cfRefFile.Read( szBufferIn, lSize ) != OK ){
			// deu pau
			NRETURN( LBSE_ERROR );
		}
		cfRefFile.Close();
		szBufferIn[ lSize ] = '\0';
	}

	if( (szFileName[0] != '\0') ||	// a url veio do disco ou
			((szFileName[0] == '\0') && bEhHTML && bEhTexto) ){	// veio do chupador e eh texto html
		// converter o texto HTML para ascii
		HTML_Memory		cmIn( szBufferIn );
		HTML_Memory		cmOut( pRefRet->szBuffer );
		HTML_HtmlToTxt	chHtmlToTxt;

		chHtmlToTxt.Run( cmIn, cmOut );
		lSize = cmOut.Pos();
	} else {
		if( (szFileName[0] == '\0') && bEhTexto ){	// a url veio do chupador e eh texto
			strcpy( pRefRet->szBuffer, szBufferIn );
		} else {																// a url veio do chupador mas possui tipo desconhecido
			pRefRet->szBuffer[ 0 ] = '\0';
		}
	}
	if( szFileName[0] != '\0' ){
		delete szBufferIn;
		szBufferIn = NULL;
	} else {
		// se o szBufferIn for igual ao cHttp.szContent
		// nao eh necessario deletar, pois o destrutor de
		// cHttp o faz.
	}

	SetError( LBS_OK );
	return( pRefRet );
}


/**********************************************************
// Function name	: LBSC_Base::ConvertACLFile
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::ConvertACLFile()
{
	if( ClearAllAcls() == LBS_OK ){
		if( LoadAllAcls( OCCTREE_MAGICNUMBER ) == LBS_OK ){
			if( SaveAllAcls( CURRENT_MAGICNUMBER ) == LBS_OK ){
				ClearAllAcls();
				ERETURN( LBS_OK );
			}
			ERETURN( LBS_OK );
		}
	}
	ERETURN( LBSE_ERROR );
}


/**********************************************************
// Function name	: LBSC_Base::ClearAllAcls
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::ClearAllAcls()
{
	lbscaBaseUserAcl.DelAll();
	lbscaBaseGroupAcl.DelAll();
	lbscaFieldUserAcl.DelAll();
	lbscaFieldGroupAcl.DelAll();
	lbscaRecordUserAcl.DelAll();
	lbscaRecordGroupAcl.DelAll();
	lbscaFormUserAcl.DelAll();
	lbscaFormGroupAcl.DelAll();
	lbscaReportUserAcl.DelAll();
	lbscaReportGroupAcl.DelAll();

	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::SaveAllAcls
// Description	    : 
// Return type		: int 
// Argument         : BYTE bVersion
**********************************************************/
int LBSC_Base::SaveAllAcls( BYTE bVersion )
{
	C_File		cfACLFile;
	char szAux[ PATHNAMESIZE + FILENAMESIZE + sizeof( ACLFILEEXT ) ];

	sprintf( szAux, "%s\\%s%s", (char *)szBasePath, (char*) szBaseName, ACLFILEEXT );
	if( cfACLFile.Open( szAux, "wb" ) == OK ){
		if( bVersion >= COMPONENTPERM_MAGICNUMBER ){
			UINT	uiBaseId = LB1.tcrHead.dwBaseId;

			cfACLFile.Write( &uiBaseId, sizeof( UINT ) );
		}
		if ( pBaseInstance ) {		// limpar cache
			pBaseInstance->InvalidateACLs();
		}
		lbscaBaseUserAcl.Save( &cfACLFile, bVersion );
		lbscaBaseGroupAcl.Save( &cfACLFile, bVersion );
		lbscaFieldUserAcl.Save( &cfACLFile, bVersion );
		lbscaFieldGroupAcl.Save( &cfACLFile, bVersion );
		lbscaRecordUserAcl.Save( &cfACLFile, bVersion );
		lbscaRecordGroupAcl.Save( &cfACLFile, bVersion );
		if( bVersion >= COMPONENTPERM_MAGICNUMBER ){
			lbscaFormUserAcl.Save( &cfACLFile, bVersion );
			lbscaFormGroupAcl.Save( &cfACLFile, bVersion );
			lbscaReportUserAcl.Save( &cfACLFile, bVersion );
			lbscaReportGroupAcl.Save( &cfACLFile, bVersion );
		}
		cfACLFile.Close();
	}
	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::LoadAllAcls
// Description	    : 
// Return type		: int 
// Argument         : BYTE bVersion
**********************************************************/
int LBSC_Base::LoadAllAcls( BYTE bVersion )
{
	if ( bVersion <= 0 ) {
		ERETURN( LBSE_ERROR );
	}
	if ( pBaseInstance && pBaseInstance->ACLsLoaded() ) {		// estrutura ja foi carregada; vamos pegar da cache
		CLBAutoRegCrit	AutoRegCrit( &(pBaseInstance->AclListCritSect) );

		lbscaBaseUserAcl = pBaseInstance->ACLLists->lUserBase ;					// usa o operador = da lista
		lbscaBaseGroupAcl = pBaseInstance->ACLLists->lGroupBase;					// idem
		lbscaFieldUserAcl = pBaseInstance->ACLLists->lUserField;					// idem
		lbscaFieldGroupAcl = pBaseInstance->ACLLists->lGroupField;				// idem
		lbscaRecordUserAcl = pBaseInstance->ACLLists->lUserRecord;				// idem
		lbscaRecordGroupAcl = pBaseInstance->ACLLists->lGroupRecord;				// idem
		lbscaFormUserAcl = pBaseInstance->ACLLists->lUserForm;					// idem
		lbscaFormGroupAcl = pBaseInstance->ACLLists->lGroupForm;					// idem
		lbscaReportUserAcl = pBaseInstance->ACLLists->lUserReport;				// idem
		lbscaReportGroupAcl = pBaseInstance->ACLLists->lGroupReport;				// idem
		ERETURN( LBS_OK );
	}

	C_File		cfACLFile;
	char szAux[ PATHNAMESIZE + FILENAMESIZE + sizeof( ACLFILEEXT ) ];

	sprintf( szAux, "%s\\%s%s", (char *)szBasePath, (char*) szBaseName, ACLFILEEXT );
	if( cfACLFile.Open( szAux, "rb" ) == OK ){
		if( bVersion >= COMPONENTPERM_MAGICNUMBER ){
			UINT	uiBaseId;

			cfACLFile.Read( &uiBaseId, sizeof( UINT ) );

			if( uiBaseId != LB1.tcrHead.dwBaseId ){
				ERETURN( LBSE_ERROR );
			}
		}

		lbscaBaseUserAcl.Load( &cfACLFile, bVersion );
		lbscaBaseGroupAcl.Load( &cfACLFile, bVersion );
		lbscaFieldUserAcl.Load( &cfACLFile, bVersion );
		lbscaFieldGroupAcl.Load( &cfACLFile, bVersion );
		lbscaRecordUserAcl.Load( &cfACLFile, bVersion );
		lbscaRecordGroupAcl.Load( &cfACLFile, bVersion );
		if( bVersion >= COMPONENTPERM_MAGICNUMBER ){
			lbscaFormUserAcl.Load( &cfACLFile, bVersion );
			lbscaFormGroupAcl.Load( &cfACLFile, bVersion );
			lbscaReportUserAcl.Load( &cfACLFile, bVersion );
			lbscaReportGroupAcl.Load( &cfACLFile, bVersion );
		}
		cfACLFile.Close();
	}

	if ( pBaseInstance ) {		// atualizar cache
		CLBAutoRegCrit	AutoRegCrit( &(pBaseInstance->AclListCritSect) );

		pBaseInstance->ACLLists = new TACL_Lists;
		pBaseInstance->ACLLists->lUserBase = lbscaBaseUserAcl;					// usa o operador = da lista
		pBaseInstance->ACLLists->lGroupBase = lbscaBaseGroupAcl;					// idem
		pBaseInstance->ACLLists->lUserField = lbscaFieldUserAcl;					// idem
		pBaseInstance->ACLLists->lGroupField = lbscaFieldGroupAcl;				// idem
		pBaseInstance->ACLLists->lUserRecord = lbscaRecordUserAcl;				// idem
		pBaseInstance->ACLLists->lGroupRecord = lbscaRecordGroupAcl;				// idem
		pBaseInstance->ACLLists->lUserForm = lbscaFormUserAcl;					// idem
		pBaseInstance->ACLLists->lGroupForm = lbscaFormGroupAcl;					// idem
		pBaseInstance->ACLLists->lUserReport = lbscaReportUserAcl;				// idem
		pBaseInstance->ACLLists->lGroupReport = lbscaReportGroupAcl;				// idem
	}
	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::GenerateComponentAcls
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::GenerateComponentAcls()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GenerateComponentAcls") );

	C_StrTok	cStrTok;
	char		*szAllGroups;

	if( !plbscsOwnerSession || !plbscsOwnerSession->plbsctTicket ){
		ERETURN( LBSE_ERROR );
	}

	// obter todos os grupos da udb desta base.
	// para cada grupo encontrado, setar permissoes nos componentes
	// da seguinte forma: 
	//		permissoes genericas: ACL_APPEND | ACL_READ
	//		permissoes individuais: ACL_READ | ACL_WRITE
	// Ou seja, para cada grupo encontrado, adicionar um elemento
	// LBSC_ACL nas listas de componentes com o nome vazio ("") e
	// a permissao ACL_ADM.

	// obter os grupos da UDB
	szAllGroups = plbscsOwnerSession->GetGroups( plbscsOwnerSession->plbsctTicket, NULL );

	if( !szAllGroups ){
		ERETURN( LBSE_ERROR );
	}

	BOOL	bAccAux = bFullAccess;
	
	bFullAccess = TRUE;

	// gerar as ACLs
	char	*szGrp = cStrTok.StrTok( szAllGroups, " " );
	while( szGrp ){
		// O id do componente deve ser "" para indicar um componente especial
		SetACLPerm( szGrp, 0, "", ACL_ADM, GROUPFORM );
		SetACLPerm( szGrp, 0, "", ACL_ADM, GROUPREPORT );
		szGrp = cStrTok.StrTok( NULL, " " );
	}

	bFullAccess = bAccAux;

	// o retorno de GetGroups DEVE ser destruido.
	delete szAllGroups;

	bBaseUpdated = TRUE;
	
	ERETURN( LBS_OK );
}



/**********************************************************
// Function name	: LBSC_Base::FillFieldsFromSlotInfo
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::FillFieldsFromSlotInfo()
{
 	if( stricmp( (char*) szCompleteBaseName, (char*) szBaseName ) != 0 ){
		// bases auxiliares nao devem ser analisadas por este metodo
		ERETURN( LBSE_ERROR );
	}

	// para cada campo, pegar o numero do grupo
	// e setar o iGroup
	int	iNumFields = GetNumberOfFields();

	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = (*this)[i];
		SLOTSTRUCT	*pSlot = NULL;

		if( !pf ){
			ERETURN( LBSE_INVALIDFIELD );
		}


		if( GetFieldSlotSize( pf->uiFieldId ) > 0 ){
			// este campo possui slot.
			SlotFieldManager sSlotInfo( pf->uiFieldId, this );

			// obter numero do grupo ao qual o campo pertence
			pSlot = sSlotInfo.GetObjectInfo( FSI_GROUP );
			if( pSlot ){
				pf->iGroup = *((int*) pSlot->SlotInformation);
			} else {
				pf->iGroup = 0;
			}
		}
	}
	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::SortFields
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Base::SortFields()
{
	//////////////////////////////////////////////////
	// so' pode existir um campo ordenado por grupo //
	//////////////////////////////////////////////////

	int	iNumGroups = lbscrCurrRecord.lbscflGroupList.NumElem();

	for( int i = 0; i < iNumGroups; i++ ){
		LBSC_FieldGroup	*pfg = lbscrCurrRecord.lbscflGroupList[i];
		LBSC_Field	*pKeyField = NULL;

		// primeiro vamos achar o campo chave do multivalorado (se houver)
		int iNumFields = lbscrCurrRecord.GetNumberOfFieldsInGroup( pfg );
		for ( int j=0; j<iNumFields; j++ ) {
			LBSC_Field	*pf = lbscrCurrRecord.GetFieldInGroup( pfg, j );
			if( pf && (pf->GetAttrib() & (ASC_ORD_FIELD | DESC_ORD_FIELD)) && pf->bFlagUpdate ){
				// ordenar o campo
				if( pf->SortRepetition( MASTER_FIELD_SORT ) == LBS_OK ){
					pKeyField = pf;
					break;
				}
			}
		}
		if ( !pKeyField ) {
			// nada nesse grupo; procurar em outro
			continue;
		}
		// agora vamos ordenar as repeticoes dos campos nao chave 
		// baseados na ordenacao de pKeyField feita acima
		for ( j=0; j<iNumFields; j++ ) {
			LBSC_Field	*pf = lbscrCurrRecord.GetFieldInGroup( pfg, j );
			if( pf != pKeyField ){
				pf->SortRepetition( GROUP_FIELD_SORT, pKeyField );
			}
		}
	}

	ERETURN( LBS_OK );
}



/**********************************************************
// Function name	: LBSC_Base::PrintLogUse
// Description	    : 
// Return type		: int 
// Argument         :  LogType ltLogType
// Argument         : long lNumRec
**********************************************************/
int LBSC_Base::PrintLogUse( LogType ltLogType, long lNumRec, char *szExtras )
{
	if( !plbscsOwnerSession || !plbscsOwnerSession->bIsLogged ){
		return( LBSE_USERNOTLOGGED );
	}

	int iCurOperMask = (int)pow(2, ltLogType);
	if( !(iCurOperMask & iOperationLogMask) ) {
		// nao gerar log para esta base/operacao.
		return( LBS_OK );
	}


	C_Date	cdDate;				// data atual
	C_Time	ctTime;				// hora atual
	char	szAccType[ 100 ];
	char	szHeader[ 1000 ];
	char	szFieldKeyToken[ 64 ];
	char	szUserName[ 20 ];
	char	szClientType[ 50 ];
	char	szClientName[ 255 ];
	char	szFieldContent[ 256 ];
	char	szDate[ 256 ];
	char	szTime[ 256 ];
	char	szLine[ 2048 ];
	char	szLogFName[ MAXPATH ];
	char	*szAux;
	C_File	cfLogFile;

	// a regiao critica abaixo protege toda a operacao
	// de log
	C_BaseCritSect	cCS13( this, CRITSECT13 );

	memset( szFieldContent, 0, 256 );

	if ( szExcludeModulesFromLog != "" ) {
		char szAux[FULLNAMESIZE];
		strcpy( szAux, (char *)szExcludeModulesFromLog );
		C_StrTok	cStrTok;
		char *szTok = cStrTok.StrTok( szAux, " ," );
		while ( szTok ) {
			if ( stricmp(szTok, plbscsOwnerSession->GetAppName()) == 0 ){
				// nao gerar log para operacoes vindas desse modulo 
				return( LBS_OK );
			}
			szTok = cStrTok.StrTok( NULL, " ," );
		}
	}

	// obter o nome do arquivo de log
	GetLogFileName( szLogFName );

	if( !szLogFName[0] ){
		// nao podemos gerar log
		ERETURN( LBSE_ERROR );
	}

	switch( ltLogType ){
	case READ_RECORD:
		strcpy( szAccType, _szReadOperationToken );
		break;

	case UPDATE_RECORD:
		strcpy( szAccType, _szWriteOperationToken );
		break;

	case APPEND_RECORD:
		strcpy( szAccType, _szAppendOperationToken );
		break;

	case DELETE_RECORD:
		strcpy( szAccType, _szDeleteOperationToken );
		break;

	case SEARCH_OK:
		strcpy( szAccType, _szSearchOKOperationToken );
		break;

	case SEARCH_ERROR:
		strcpy( szAccType, _szSearchErrorOperationToken );
		break;

	case OPEN_BASE:
		strcpy( szAccType, _szOpenBaseOperationToken );
		break;

	case CLOSE_BASE:
		strcpy( szAccType, _szCloseBaseOperationToken );
		break;

	default:
		return( LBSE_BADARG );
	}

	if ( ltLogType == SEARCH_OK || ltLogType == SEARCH_ERROR ) {
		strncpy( szFieldContent, szExtras, 255 );
		strcpy( szFieldKeyToken, "" );
	} else {
		strcpy( szFieldKeyToken, _szFieldKeyToken );
		// verificar se o campo indicado faz sentido
		LBSC_Field	*pf = (*this)[ (char*) strLogFieldAliasName ];

		if( !pf ){
			// field nao existente.
			strcpy( szFieldContent, "" );
			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				char	*szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_UNKNOWNFIELD" );

				if( szTok ){
					strcpy( szFieldContent, szTok );
					delete szTok;
				}
			}
		} else {
			LBSC_Data	*pd = (*pf)[0];
			char *szData = NULL;

			if( pd && (szData = pd->ToString()) ){
				strncpy( szFieldContent, szData, 255 );
				delete szData;
			} else {
				strcpy( szFieldContent, "" );
				if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
					char	*szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_EMPTYFIELD" );

					if( szTok ){
						strcpy( szFieldContent, szTok );
						delete szTok;
					}
				}
			}
		}
	}

	strcpy( szUserName, plbscsOwnerSession->GetUserName() );
	strcpy( szClientType, plbscsOwnerSession->GetAppName() );
	szAux = plbscsOwnerSession->plbsctTicket->GetClientName();
	strcpy( szClientName, szAux ? szAux : "?" );
	if( szAux ){
		delete szAux;
		szAux = NULL;
	}

	// montar data e hora conforme mascara internacionalizada
	PRODLANGPARMS *pLangSectVars = NULL;
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		PRODLANGPARMS *pLangSectVars = _pcInter->GetProdLangParms();
	}
	cdDate.Get( szDate, (pLangSectVars && pLangSectVars->datemask) ? pLangSectVars->datemask : "dd/mm/yyyy" );
	ctTime.Get( szTime, (pLangSectVars && pLangSectVars->timemask) ? pLangSectVars->timemask : "hh:mm:ss" );

	sprintf( szHeader, "#LBLOG_%s", szAccType );
	sprintf( szLine, "%-25.25s# %s %s - %s: %-30.30s - %s: %06d - %s: %-20.20s - %s: %-30.30s (%-15.15s) - %s: %s",
					szHeader, 
					szDate,
					szTime,
					_szBaseToken, (char*) szBaseName, 
					_szRecToken, lNumRec, 
					_szUserToken, szUserName, 
					_szClientToken, szClientName, 
					szClientType,
					szFieldKeyToken, szFieldContent );

	// gravar uma linha no arquivo de log
	cfLogFile.Open( szLogFName, "ab", SH_DENYNO );
	if( !cfLogFile.IsOpen() ){
		return( LBSE_ERROR );
	}
	cfLogFile.WriteLine( szLine );

	if ( ltLogType == UPDATE_RECORD && szFieldsForUpdateLog != "" ) {	
		// tentar gerar log com os valores anteriores dos campos
		char szAux[FULLNAMESIZE];
		strcpy( szAux, (char *)szFieldsForUpdateLog );
		C_StrTok	cStrTok;
		char *szTok = cStrTok.StrTok( szAux, " ," );
		while ( szTok ) {

			// verificar se o campo indicado faz sentido
			LBSC_Field	*pf = (*this)[ szTok ];
			if( pf && pf->bFlagUpdate ){	// houve alteracao aqui
				LBSC_DataList *pDataList = &(pf->lbscdlDataList);
				LBSC_DataList *pOriginalDataList = &(pf->lbscdlOriginalDataList);
				BOOL bMaisMudancas = FALSE;
				int iFirst = -1;

				int iNumRepet = pDataList ? pDataList->NumElem() : 0;
				int iNumOrigRepet = pOriginalDataList ? pOriginalDataList->NumElem() : 0;
				for ( int i=0, j=0; i<iNumRepet && j<iNumOrigRepet; i++, j++ ) {
					LBSC_Data	*pd = (*pDataList)[ i ];
					LBSC_Data	*pdOrig = (*pOriginalDataList)[ j ];
					if ( !pd && !pdOrig ) {
						// sem mudancas
						continue;
					}
					if ( pd && pdOrig && pd->Compare( pdOrig, CMPDATA) == 0 ) {
						// sem mudancas
						continue;
					}
					// se chegou aqui eh porque houve diferencas
					if ( iFirst == -1 ) {
						iFirst = i;
					} else {
						bMaisMudancas = TRUE;
					}
				}

				if ( iFirst != -1 ) {
					sprintf( szHeader, "#LBLOG_%s", szAccType );
					sprintf( szLine, "%-25.25s# CAMPO:%s, REPETIÇÕES: DE %d PARA %d, PRIMEIRA ALTERAÇÃO: %d (%s) CONTEÚDO:",
								szHeader,
								szTok,
								iNumOrigRepet,
								iNumRepet, 
								iFirst+1, // tem que deixar baseado em 1
								bMaisMudancas ? "HÁ MAIS ALTERAÇÕES" : "ÚNICA ALTERAÇÃO" );
					cfLogFile.WriteLine( szLine );

					LBSC_Data	*pd = (*pDataList)[iFirst];
					char *szData = NULL;
					szData = pd->ToString();

					if( pd ){
						if ( szData ) {
							cfLogFile.WriteLine( szData );
							delete szData;
						} else {
							cfLogFile.WriteLine( "" );
						}
					}
				} else if ( i < iNumRepet ) {
					// inclusao de repeticoes
					sprintf( szHeader, "#LBLOG_%s_INSERT", szAccType );
					sprintf( szLine, "%-25.25s# CAMPO:%s, REPETIÇÕES: DE %d PARA %d",
								szHeader,
								szTok,
								iNumOrigRepet,
								iNumRepet );
					cfLogFile.WriteLine( szLine );
				} else if ( j < iNumOrigRepet ) {
					// delecao de repeticoes
					sprintf( szHeader, "#LBLOG_%s_DELETE", szAccType );
					sprintf( szLine, "%-25.25s# CAMPO:%s, REPETIÇÕES: DE %d PARA %d",
								szHeader,
								szTok,
								iNumOrigRepet,
								iNumRepet );
					cfLogFile.WriteLine( szLine );
				}
			}
			szTok = cStrTok.StrTok( NULL, " ," );
		}
	}
	cfLogFile.Close();
	return( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::PutGroupRepetition
// Description	    : 
// Return type		: int 
// Argument         :  LBSC_Field *pfField
// Argument         : int iIndex
**********************************************************/
int LBSC_Base::PutGroupRepetition( LBSC_Field *pfField, int iIndex )
{
	if( !pfField ){
		ERETURN( LBSE_ERROR );
	}

	if( pfField->GetGroup() <= 0 ){
		// este campo nao pertence a nenhum grupo
		ERETURN( LBS_OK );
	}

	switch( iIndex ){
	case -1:
		// posicao corrente da lista de repeticoes de pfField
		iIndex = pfField->lbscdlDataList.GetCurrentIndex();
		break;

	case TAIL_REPETITION:
		// final da lista de repeticoes de pfField
		iIndex = pfField->GetNumberOfRepetition() - 1;
		break;

	default:
		if( iIndex < 0 ){
			// iIndex invalido.
			ERETURN( LBSE_BADARG );
		}
	}

	LBSC_FieldGroup findGroup;
	findGroup.iGroup = pfField->GetGroup();
	LBSC_FieldGroup *pFieldGroup = lbscrCurrRecord.lbscflGroupList.Find( &findGroup, 0 );
	if ( !pFieldGroup ) {
		ERETURN( LBSE_ERROR );
	}

	int iNumFields = lbscrCurrRecord.GetNumberOfFieldsInGroup( pFieldGroup );
	for ( int i=0; i<iNumFields; i++ ) {
		LBSC_Field	*pf = lbscrCurrRecord.GetFieldInGroup( pFieldGroup, i );

		if( pf && (pf != pfField) ){
			// o fato de tentar acessar a repeticao iIndex
			// atraves do operador [] de field ja' cria uma
			// repeticao vazia se ela nao existir.

			// verificar se a repeticao existe.
			if( !((pf->lbscdlDataList)[iIndex]) ){
				// nao existe. cria.
				LBSC_Data	*pd = (*pf)[iIndex];

				// desabilita, para nao deixar informacao
				// que a aplicacao nao setou.
				if( pd ){
					pd->DisableData();
				}
				// setar como DATA_HOLE para possibilitar o tratamento
				// correto das permissoes nos PutFieldRepetition...
				pd->SetStatus( DATA_HOLE );
			}
		}
	}
	ERETURN( LBS_OK );
}

/**********************************************************
// Function name	: LBSC_Base::GetNumberOfGroupRepetition
// Description	    : 
// Return type		: int 
// Argument         :  LBSC_Field *pfField
**********************************************************/
int LBSC_Base::GetNumberOfGroupRepetition( int iGroup )
{
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	LBSC_FieldGroup findGroup;
	findGroup.iGroup = iGroup;
	LBSC_FieldGroup *pFieldGroup = lbscrCurrRecord.lbscflGroupList.Find( &findGroup, 0 );
	if ( !pFieldGroup ) {
		ERETURN( LBSE_ERROR );
	}

	int iNumFields = lbscrCurrRecord.GetNumberOfFieldsInGroup( pFieldGroup );
	int	iMaxRep = 0;
	for ( int i=0; i<iNumFields; i++ ) {
		LBSC_Field	*pf = lbscrCurrRecord.GetFieldInGroup( pFieldGroup, i );
		if ( pf && pf->GetNumberOfRepetition() > iMaxRep ) {
			iMaxRep = pf->GetNumberOfRepetition();
		}
	}
	return( iMaxRep );
}

/**********************************************************
// Function name	: LBSC_Base::ReprocRecords
// Description	    : 
// Return type		: int 
// Argument         :  const LBSC_Ticket *pTicket
// Argument         : BYTE bOldMagicNumber
// Argument         : BYTE bNewMagicNumber
**********************************************************/
int LBSC_Base::ReprocRecords( const LBSC_Ticket *pTicket, BYTE bOldMagicNumber, BYTE bNewMagicNumber )
{
	// reprocessa os registros da base, lendo-os com um numero
	// magico e gravando com outro.

	// o sistema de indices vai ficar invalido no final do processo.

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( GetNumRecords( pTicket ) );	// depende do número de registros da base... 

	BYTE	bMagicNumber = GetBaseVersion();

	// primeiramente, destruir o sistema de indices
	RemoveIndexSystem();

	// agora ler e regravar cada registro
	EnableFastRecord( TRUE );
	LB1.bMagicNumber = bOldMagicNumber;
	if( FirstFRecord( pTicket ) == LBS_OK ){
		long	lRecNumAux = 0l;
		long	lRecTotAux = GetNumRecords( pTicket );
		do{
			/*******************************************************/
			// informacao de feedback
			if( OperationCanceled() ){
				// operacao foi cancelada a pedido do usuario.

				ERETURN( LBSW_OPCANCEL );
			}
			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				char	szFullMsg[ 200 ];

				char *szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_REPROCRECORDS" );
				if ( szMsg ) {
					sprintf( szFullMsg, "%s: %s %d/%d", (char*)szBaseName, szMsg, lRecNumAux++, lRecTotAux );
					IncStep( szFullMsg );
					delete szMsg;
				}
				else {
					IncStep( "" );
				}
			} else {
				IncStep( "" );
			}
			/*******************************************************/

			LB1.bMagicNumber = bNewMagicNumber;
			// forcar a barra para que todos os campos sejam gravados
			int	iNumFields = GetNumberOfFields();
			for( int i = 0; i < iNumFields; i++ ){
				LBSC_Field	*pf = lbscrCurrRecord[ i ];

				if( pf ){
					pf->UpdateFieldFlag( TRUE );
					pf->bMustFillOriginalDataList = TRUE;
					pf->FillOriginalDataList();
				}
			}
			bAppendingRec = TRUE;
			UpdateRecord( pTicket );
			bAppendingRec = FALSE;
			LB1.bMagicNumber = bOldMagicNumber;
		} while( NextFRecord( pTicket ) == LBS_OK );
	}
	bAppendingRec = FALSE;
	LB1.bMagicNumber = bMagicNumber;
	EnableFastRecord( FALSE );

	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: PUBLIC LBSC_Base::MustIndexLast
// Description	    : Determina se eh necessario indexar a ultima repeticao com um flag especial
// Return type		: boolean
// Argument         : UINT uiFieldId, int iRep
**********************************************************/
BOOL
LBSC_Base::MustIndexLast( UINT uiFieldId, int iRep )
{
	LBSC_Field	*pcfField = lbscrCurrRecord( uiFieldId );
	if ( LB1.tcrHead.bBaseType != USER_BASE && 
				pcfField && 
				(pcfField->GetGroup() > 0) && 
				((pcfField->GetIndexAttrib() & UNIQUETREE) == 0) && 
				((iRep+1) >= pcfField->GetNumberOfRepetition()) ) {
		// nao pode ser campo de UDB, 
		// tem que ser multivalorado,
		// nao pode ter chave unica, e 
		// a repeticao a ser indexada tem que ser a ultima
		return TRUE;
	}
	return FALSE;
}


/**********************************************************
// Function name	: PUBLIC LBSC_Base::MustUnIndexLast
// Description	    : Determina se eh necessario tentar desindexar a ultima repeticao com um flag especial
// Return type		: boolean
// Argument         : UINT uiFieldId
**********************************************************/
BOOL
LBSC_Base::MustUnIndexLast( UINT uiFieldId, int iRep )
{
	LBSC_Field	*pcfField = lbscrCurrRecord( uiFieldId );
	if ( LB1.tcrHead.bBaseType != USER_BASE && 
				pcfField && 
				(pcfField->GetGroup() > 0) && 
				((pcfField->GetIndexAttrib() & UNIQUETREE) == 0) && 
				((iRep+1) >= pcfField->GetNumberOfRepetition()) ) {
		// nao pode ser campo de UDB, 
		// tem que ser multivalorado,
		// nao pode ter chave unica, e 
		// a repeticao a ser indexada tem que ser a ultima
		return TRUE;
	}
	return FALSE;
}


/**********************************************************
// Function name	: STATIC PUBLIC LBSC_Base::GetLogFileName
// Description	    : 
// Return type		: void 
// Argument         : char *szRet
**********************************************************/
void LBSC_Base::GetLogFileName( char *szRet )
{
	// regiao para proteger a operacao de log (mexendo em _szLogFileName)
	C_BaseCritSect	cCS13( NULL, CRITSECT13 );

	// definir o diretorio do arquivo de log
	char	szDir[ MAXPATH ];
	strncpy( szDir, LBSC_ServerConfig::LogFileDir(), MAXPATH-1 );

	if( szDir[0] == '\0'){	// nao tem log
		_szLogFileName[0] = '\0';
		strcpy( szRet, "" );
		return;
	}

	time_t now;
	time( &now );
	struct tm *tm_now = localtime( &now );

	int iYear = tm_now->tm_year+1900;
	int iMon = tm_now->tm_mon+1;
	int iDay = tm_now->tm_mday;
	char	szTodayLogFile[ MAXPATH ];
	// definir o nome do arquivo de log
	sprintf( szTodayLogFile, "LOGUSE-%04d-%02d-%02d.LOG", iYear, iMon, iDay );

	if( _szLogFileName[0] == '\0' ){
		// arquivo de log nao foi definido ainda...

		// definir os tokens de geracao de uma linha de log
		strcpy( _szBaseToken, "" );
		strcpy( _szAccToken, "" );
		strcpy( _szRecToken, "" );
		strcpy( _szFieldKeyToken, "" );
		strcpy( _szUserToken, "" );
		strcpy( _szClientToken, "" );
		strcpy( _szReadOperationToken, "LEITURA" );
		strcpy( _szWriteOperationToken, "ALTERAÇÃO" );
		strcpy( _szAppendOperationToken, "INCLUSÃO" );
		strcpy( _szDeleteOperationToken, "EXCLUSÃO" );
		strcpy( _szSearchOKOperationToken, "SUCESSO_PESQUISA" );
		strcpy( _szSearchErrorOperationToken, "ERRO_PESQUISA" );
		strcpy( _szOpenBaseOperationToken, "ABERTURA" );
		strcpy( _szCloseBaseOperationToken, "FECHAMENTO" );
		_iFieldContentLen = 20;
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			char	*szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_BASE" );
			if( szTok ){
				strcpy( _szBaseToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_ACCESS" );
			if( szTok ){
				strcpy( _szAccToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_RECORD" );
			if( szTok ){
				strcpy( _szRecToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_FIELDKEY" );
			if( szTok ){
				strcpy( _szFieldKeyToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_USER" );
			if( szTok ){
				strcpy( _szUserToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_CLIENT" );
			if( szTok ){
				strcpy( _szClientToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_READACCESS" );
			if( szTok ){
				strcpy( _szReadOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_WRITEACCESS" );
			if( szTok ){
				strcpy( _szWriteOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_APPENDACCESS" );
			if( szTok ){
				strcpy( _szAppendOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_DELETEACCESS" );
			if( szTok ){
				strcpy( _szDeleteOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_SEARCHOKACCESS" );
			if( szTok ){
				strcpy( _szSearchOKOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_SEARCHERRORACCESS" );
			if( szTok ){
				strcpy( _szSearchErrorOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_OPENBASEACCESS" );
			if( szTok ){
				strcpy( _szOpenBaseOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_CLOSEBASEACCESS" );
			if( szTok ){
				strcpy( _szCloseBaseOperationToken, szTok );
				delete szTok;
			}
			szTok = _pcInter->GetGenMsgsAppVar( "LBSLOG_FIELDKEYLEN" );
			if( szTok ){
				_iFieldContentLen = atoi( szTok );
				delete szTok;
			}
		}
		if ( LBSC_ServerConfig::MaxLogFiles() > 0 ) {
			// verificar se precisa apagar algum arquivo
			// para isso, vamos ver de todos eles qual o mais velho e se extrapolarmos o
			// numero maximo de arquivos, deletamos ele
			char		szPath[MAXPATH+1];
			sprintf( szPath, "%s\\LOGUSE-*", szDir );
			WIN32_FIND_DATA		Win32FD;		// estrutura usada para pesquisar arquivos
			HANDLE		NewFile = FindFirstFile( szPath, &Win32FD );
			BOOL		bOK = (NewFile != INVALID_HANDLE_VALUE);
			FILETIME	FileToDel_Date = Win32FD.ftCreationTime;
			char		FileToDel_Name[MAXPATH+1];

			if ( bOK ) {
				sprintf( FileToDel_Name, "%s\\%s", (char*) szDir, Win32FD.cFileName );
			} else {
				strcpy( FileToDel_Name, "" );
			}

			for ( int i=1; bOK; i++ ) {
				if ( CompareFileTime( &(Win32FD.ftCreationTime), &FileToDel_Date ) < 0 ) {
					// achamos um mais velho, guardar esse cara
					sprintf( FileToDel_Name, "%s\\%s", (char*) szDir, Win32FD.cFileName );
					FileToDel_Date = Win32FD.ftCreationTime;	// esse passa a ser o mais velho por enquanto
				}
				if ( stricmp(szTodayLogFile,Win32FD.cFileName) == 0 ) {
					i--;	// se o arquivo de hoje ja foi criado, desconta-lo do total
				}

				bOK = FindNextFile( NewFile, &Win32FD );		
			}
			FindClose( NewFile );

			if ( i > LBSC_ServerConfig::MaxLogFiles() ) {
				remove( FileToDel_Name );
			}
		}
	}

	sprintf( _szLogFileName, "%s\\%s", szDir, szTodayLogFile);
	strcpy( szRet, _szLogFileName );
}


//
//	Conta o numero de bits ligados de um numero qualquer
//
int
ContaBits( int iNum )
{
	int iTotal = 0;
	if ( iNum < 0 ) {
		return 0;
	}

	while ( iNum ) {
		unsigned uiMask = 0x1;

		if ( iNum & uiMask ) {
			iTotal++;
		}

		iNum >>= 1;
	}

	return iTotal;
}

/*	
	Gera o buffer com o registro;
	O buffer deve ter o seguinte formato:
		Header Geral (esse header nao deve ser compactado):
			1 byte para indicar se o buffer esta ou nao compactado
			4 bytes para indicar o tamanho maximo do buffer (independente de compactacao)
			4 bytes para indicar o tamanho total do buffer compactado (se for o caso)

		Informacoes do registro (opcional; apenas para uso pelo stub C/S)
			4 bytes para o numero do registro corrente

		Header do bloco de campos
			4 bytes para indicar a quantidade de campos

		Bloco de campos (loop para todos os campos da base)
			4 bytes para indicar o id do campo
			4 bytes para o numero de repeticoes 
			4 bytes para a posicao da primeira repeticao do campo dentro do buffer

		Bloco de repeticoes
			loop para todas as repeticoes de cada campo
				1 byte para indicar se possue conteudo nulo
				caso o conteudo nao seja nulo
					caso o campo possua tamanho variavel (ALPHA_FIELD, TEXT_FIELD, BINARY_FIELD, REFERENCED_FIELD)
						4 bytes para o tamanho do campo
					n bytes para o conteudo

		Este metodo tambem eh usado para gerar a cache do cliente; para isso deve fazer verificacao de acls, e guardar
		o erro, caso exista no numero de repeticoes do campo. Deve tambem manter a posicao na LO corrente; 

*/
BYTE *
LBSC_Base::GetRecordBuffer( C_Buffer **pBuf, long *plRecordSize, long *plSuggestedPageSize, BOOL bSendToClientStub )
{
	//////////////
	////////////// calculando o tamanho
	//////////////

	// Header Geral + Header do bloco de campos 
	long lHeaderSize = sizeof(BYTE) + 3*sizeof(long);
	if ( bSendToClientStub ) {
		// Informacoes para o stub C/S
		lHeaderSize += sizeof(long);
	}
	*plRecordSize = lHeaderSize;		

	// Bloco de campos 
	long lNumFields = lbscrCurrRecord.GetNumberOfFields();
	*plRecordSize += (lNumFields * sizeof(TRecordBufferHeader));			

	// Bloco de repeticoes
	for ( int i=0; i<lNumFields; i++ ){
		LBSC_Field *pField = lbscrCurrRecord[i];
		for ( int j=0; j<pField->GetNumberOfRepetition(); j++ ) {
			*plRecordSize += GetBufferSizeFromRepetition(pField, j);
		}
	}

	//////////////
	////////////// gerando o buffer de fato
	//////////////

	*pBuf = new C_Buffer( *plRecordSize );
	if ( !(*pBuf) ) {
		*plRecordSize = 0;
		return NULL;
	}
	TRecordBufferHeader	*pRecBufHeader = new TRecordBufferHeader[lNumFields];
	if ( !pRecBufHeader ) {
		delete *pBuf;
		*plRecordSize = 0;
		return NULL;
	}

	BYTE bCompressed = FALSE;

	BOOL bOK = TRUE;

	// Header Geral 
	bOK &= (*pBuf)->PutData( (void *)&bCompressed, sizeof(BYTE) ); // esta compactado? 
	bOK &= (*pBuf)->PutData( (void *)plRecordSize, sizeof(long) ); // tam. maximo do buffer  
	bOK &= (*pBuf)->PutData( (void *)plRecordSize, sizeof(long) ); // tam. efetivo do buffer  

	// Informacoes para o stub C/S
	if ( bSendToClientStub ) {
		long lRec = GetOLRecNumber( plbscsOwnerSession->plbsctTicket );
		bOK &= (*pBuf)->PutData( (void *)&lRec, sizeof(long) ); // Numero do reg corrente 
	}

	// Header do bloco de campos 
	bOK &= (*pBuf)->PutData( (void *)&lNumFields, sizeof(long) ); // num. de campos 

	if ( !bOK ) {
		delete pRecBufHeader;
		delete *pBuf;
		*plRecordSize = 0;
		return NULL;
	}

	// Vamos pular o bloco de campos... depois a gente preenche com os offsets corretos
	if ( !(*pBuf)->SetMyPos( (*pBuf)->MyPos() + (lNumFields * sizeof(TRecordBufferHeader)) ) ) {
		delete pRecBufHeader;
		delete *pBuf;
		*plRecordSize = 0;
		return NULL;
	}

	// Bloco de repeticoes
	for ( i=0; i<lNumFields; i++ ){
		LBSC_Field *pField = lbscrCurrRecord[i];
		pRecBufHeader[i].lId = pField->GetId();
		pRecBufHeader[i].lNumRep = pField->GetNumberOfRepetition();
		pRecBufHeader[i].lOffSet = (*pBuf)->MyPos();

		if ( bSendToClientStub ) {
			// Checar permissoes de ACL
			if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pField->GetId(), USERFIELD, ACL_READ ) != LBS_OK ){
				pRecBufHeader[i].lNumRep = LBSE_NOPERMISSION;
				continue;	// nao continuar a ler as repeticoes desse campo
			}
		}

		for ( int j=0; j<pRecBufHeader[i].lNumRep; j++ ) {
			if ( !FillBufferFromRepetition( (**pBuf), pField, j) ) {
				delete pRecBufHeader;
				delete *pBuf;
				*plRecordSize = 0;
				return NULL;
			}
		}
	}

	qsort( pRecBufHeader, lNumFields, sizeof(TRecordBufferHeader), CompareRecordHeaderFunc );
	// Copiando o bloco de campos (pula os headers)
	memcpy( (*pBuf)->MyBuffer() + lHeaderSize, pRecBufHeader, (lNumFields * sizeof(TRecordBufferHeader)) );
	delete pRecBufHeader;
	pRecBufHeader = NULL;

	(*pBuf)->Rewind();

	if ( !bSendToClientStub ) {
		// por enquanto nao vamos tentar comprimir o buffer se for pra mandar pro stub cliente
		if ( !TryCompressRecordBuffer( **pBuf, plRecordSize ) ) {
			delete *pBuf;
			*plRecordSize = 0;
			return NULL;
		}
	}

	*plSuggestedPageSize = ((*plRecordSize / MINBLOCKSIZE) + 1) * MINBLOCKSIZE;
	return (BYTE*)((*pBuf)->MyBuffer());
}


/**
	Calcula o tamanho de uma repeticao no buffer de acordo com formato definido no metodo GetRecordBuffer
**/
long 
LBSC_Base::GetBufferSizeFromRepetition(LBSC_Field *pField, int iRep)
{
	long lHeaderSize = sizeof(BYTE);	// eh nulo ?
	LBSC_Data *pd = pField->lbscdlDataList[iRep];

	if ( !pd || !(pd->IsEnabled()) || (pField->GetType() == ALPHA_FIELD && strlen((char*) pd->GetConstData()) == 0) ) {	// eh nulo ?
		return lHeaderSize;
	}

	long lRepSize = pd->GetSize();	// conteudo
	switch( pField->GetType() ) {
	case ALPHA_FIELD:
	case TEXT_FIELD:
	case BINARY_FIELD:
	case REFERENCED_FIELD:
		if ( pField->GetType() == ALPHA_FIELD ) {
			lRepSize = strlen((char*) pd->GetConstData()) + 1;	// conteudo
		}
		lRepSize += sizeof(long); // tamanho do conteudo
		break;
	default:
		break;
	}

	return lHeaderSize + lRepSize;
}

/**
	Copia a repeticao pro buffer de acordo com formato definido no metodo GetRecordBuffer
**/
BOOL 
LBSC_Base::FillBufferFromRepetition(C_Buffer &Buf, LBSC_Field *pField, int iRep)
{
	LBSC_Data *pd = pField->lbscdlDataList[iRep];
	BYTE bIsNull = (!pd || !(pd->IsEnabled()) || (pField->GetType() == ALPHA_FIELD && strlen((char*) pd->GetConstData()) == 0));	// eh nulo ?

	if ( !Buf.PutData( (void *)&bIsNull, sizeof(BYTE) ) ) {
		return FALSE;
	}

	if ( bIsNull ) {
		return TRUE;
	}

	long lRepSize = pd->GetSize();

	switch( pField->GetType() ) {
	case ALPHA_FIELD:
	case TEXT_FIELD:
	case BINARY_FIELD:
	case REFERENCED_FIELD:
		if ( pField->GetType() == ALPHA_FIELD ) {
			lRepSize = strlen((char*) pd->GetConstData()) + 1;	
		}
		if ( !Buf.PutData( (void *)&lRepSize, sizeof(long) ) ) {	// tamanho do buffer
			return FALSE;
		}
		break;
	default:
		break;
	}
	if ( !Buf.PutData( (void *)(pd->GetConstData()), lRepSize ) ) {	// conteudo
		return FALSE;
	}
	return TRUE;
}


BOOL LBSC_Base::TryCompressRecordBuffer( C_Buffer &Buf, long *plRecordSize )
{
	if ( *plRecordSize <= MINBLOCKSIZE ) {
		// nada a fazer
		return TRUE;
	}

	// Compacta usando a LZO

	long lMaxBufSize = *plRecordSize;
	// Calcula o tamanho do buffer no pior caso
	// tem q pular as informacoes do header do buffer
	unsigned int BufferUsageSize = *plRecordSize - lbscrCurrRecord.RecordHeaderBufferSize();

	unsigned int CompressBufferSize = LZO_MaximumCompressionSize(BufferUsageSize);
    BYTE *CompressBuffer = new BYTE[CompressBufferSize];
	
	// tem q pular as informacoes do header do buffer
	if ( !LZO_Compress((BYTE *) Buf.MyBuffer() + lbscrCurrRecord.RecordHeaderBufferSize(),BufferUsageSize,
							 CompressBuffer,&CompressBufferSize ) ) {
		delete (CompressBuffer);
		return FALSE;
	}

	if ( CompressBufferSize > (0.80 * (lMaxBufSize - lbscrCurrRecord.RecordHeaderBufferSize())) ) {	
		// so aceitaremos no maximo 80% do tamanho original, caso contrario eh melhor nao compactar
		delete (CompressBuffer);
		return TRUE;
	}

	// tem q pular as informacoes do header do buffer
	memcpy( Buf.MyBuffer() + lbscrCurrRecord.RecordHeaderBufferSize(), CompressBuffer, CompressBufferSize );
	delete (CompressBuffer);

	BYTE bCompressed = TRUE;
	*plRecordSize = CompressBufferSize + lbscrCurrRecord.RecordHeaderBufferSize();

	Buf.Rewind();
	Buf.PutData( (void *)&bCompressed, sizeof(BYTE) );
	Buf.PutData( (void *)&lMaxBufSize, sizeof(long) );
	Buf.PutData( (void *)plRecordSize, sizeof(long) );
	Buf.Rewind();
	return TRUE;
}

void LBSC_Base::InvalidateCache()
{
	Close();
	if ( pBaseInstance ) {
		pBaseInstance->InvalidateAll();
	}
}


int LBSC_Base::ReadRecordData()
{
	// a regiao critica abaixo protege toda a operacao de
	// leitura dos dados do registro
	CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );
	CPageFile *pDataFile = pBaseInstance->GetDataFile();

	TControlRec	tcrControlRec;

	lbscrCurrRecord.SetIsUndefined( TRUE );

	if( LB1.R_Read( &tcrControlRec ) != OK ){
		ERETURN( LBSE_NORECORD );
	}

	if( tcrControlRec.bRecStatus & REC_EXCLUDED ){
		ERETURN( LBSE_EXCLUDEDREC );
	}
	if( tcrControlRec.fContentPos == (FAU)0 ){
		ERETURN( LBSE_ZERORECORD );
	}

	if ( !pDataFile->CheckPage( tcrControlRec.fContentPos ) ) {
		ERETURN( LBSE_WRONGRECORD );
	}

	long lRecordSize = pDataFile->PageSize(tcrControlRec.fContentPos);
	if ( lRecordSize <= 0 ) {
		ERETURN( LBSE_WRONGRECORD );
	}

	C_Buffer Buf(lRecordSize);

	if ( !pDataFile->ReadPage( (BYTE *)(Buf.MyBuffer()), lRecordSize, tcrControlRec.fContentPos ) ) {
		ERETURN( LBSE_WRONGRECORD );
	}

	if ( !lbscrCurrRecord.SetRecordBuffer(Buf) ) {
		ERETURN( LBSE_WRONGRECORD );
	}

	lbscrCurrRecord.SetIsUndefined( FALSE );
	ERETURN( LBS_OK );
}


