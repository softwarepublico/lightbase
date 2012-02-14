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
// Module: PUBBASE2.CPP
// Description:
//
//	LBSC_BASE public class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Alessandro A. Jatoba'
//
// Last update: 19/01/96
//

#ifndef __BORLANDC__
#pragma warning(disable:4355)
#endif

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
#if !defined _INC_ERRNO
#include	<errno.h>
#endif
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
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef	_LBSLCKCL_H_
#include	<lbslckcl.h>
#endif
extern "C" {
#include	<personcl.h>
}


// $$$ API LIGHT-TEXT
#include	<lt.h>
#include	<exprlist.h>


#include <baseinstance.h>


// Prototypes
extern	void	Printf( char *, ... );

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

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
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo GetCurrentOccurrence
	Obtem a ocorrencia corrente da LO

	Parameters:

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- NAO altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetCurrentOccurrence( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrentOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar NULL
	if( !plbscolOcurrenceList ){
		NRETURN( LBSE_NOOCCURRENCE );
	}
	LTC_OCCURRENCE *pltcOcAux = plbscolOcurrenceList->GetCurrentOccurrence();	
	if( pltcOcAux ){

		lbscOcAux = *pltcOcAux;

		SetError( LBS_OK );
		ClearMaxRepetitionStatus( lbscOcAux );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}



/***
	PUBLIC
	Metodo GetFirstOccurrence
	Obtem a primeira ocorrencia da LO, para o numero de registro corrente

	Parameters:

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetFirstOccurrence( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFirstOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar uma ocorrencia que contem apenas o numero do
	// $$$ registro corrente
	if( !plbscolOcurrenceList ){
		if( FirstFRecord( lbscTicket ) != LBS_OK ){
			// $$$ Erro
			return( NULL );
		}
		SetError( LBS_OK );
		LTC_OCCURRENCE	ltAux(	(CHARTYPE*) "", CurrRecNum( lbscTicket ),
					0, 0, 0, 0, 0 );
		
		lbscOcAux = ltAux;

		SetError( LBS_OK );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	LTC_OCCURRENCE *pCurOcc = plbscolOcurrenceList->GetCurrentOccurrence();	
	LTC_OCCURRENCE *pFirstOcc = plbscolOcurrenceList->GetFirstOccurrence();
	if( pCurOcc && pFirstOcc ){
		lbscOcAux = *pFirstOcc;
		if( pCurOcc == pFirstOcc ){
			// Ja' estamos na primeira ocorrencia
			SetError( LBSE_FIRSTOCCURRENCE );
		} else {
			SetError( LBS_OK );
		}
		ClearMaxRepetitionStatus( lbscOcAux );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}



/***
	PUBLIC
	Metodo GetLastOccurrence
	Obtem a ultima ocorrencia da LO

	Parameters:

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetLastOccurrence( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetLastOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar uma ocorrencia que contem apenas o numero do
	// $$$ registro corrente
	if( !plbscolOcurrenceList ){
		if( LastFRecord( lbscTicket ) != LBS_OK ){
			// $$$ Erro
			return( NULL );
		}
		SetError( LBS_OK );
		LTC_OCCURRENCE	ltAux(	(CHARTYPE*) "", CurrRecNum( lbscTicket ),
					0, 0, 0, 0, 0 );
		lbscOcAux = ltAux;
		SetError( LBS_OK );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	LTC_OCCURRENCE *pCurOcc = plbscolOcurrenceList->GetCurrentOccurrence();	
	LTC_OCCURRENCE *pLastOcc = plbscolOcurrenceList->GetLastOccurrence();
	if( pCurOcc && pLastOcc ){
		lbscOcAux = *pLastOcc;
		if( pCurOcc == pLastOcc ){
			// Ja' estamos na ultima ocorrencia
			SetError( LBSE_LASTOCCURRENCE );
		} else {
			SetError( LBS_OK );
		}
		ClearMaxRepetitionStatus( lbscOcAux );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}



/***
	PUBLIC
	Metodo GetNextOccurrence
	Obtem a proxima ocorrencia da LO

	Parameters:

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetNextOccurrence( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNextOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar uma ocorrencia que contem apenas o numero do
	// $$$ registro corrente
	if( !plbscolOcurrenceList ){
		if( NextFRecord( lbscTicket ) != LBS_OK ){
			// $$$ Erro
			return( NULL );
		}
		SetError( LBS_OK );
		LTC_OCCURRENCE	ltAux(	(CHARTYPE*) "", CurrRecNum( lbscTicket ),
					0, 0, 0, 0, 0 );
		
		lbscOcAux = ltAux;

		SetError( LBS_OK );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	LTC_OCCURRENCE *pCurOcc = plbscolOcurrenceList->GetCurrentOccurrence();	
	LTC_OCCURRENCE *pNextOcc = plbscolOcurrenceList->GetNextOccurrence();
	if( pCurOcc ){
		if( !pNextOcc || pCurOcc == pNextOcc ){
			// Ja' estamos na ultima ocorrencia
			lbscOcAux = *pCurOcc;
			SetError( LBSE_LASTOCCURRENCE );
		} else {
			lbscOcAux = *pNextOcc;
			SetError( LBS_OK );
		}
		ClearMaxRepetitionStatus( lbscOcAux );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}



/***
	PUBLIC
	Metodo GetPreviousOccurrence
	Obtem a ocorrencia anterior da LO

	Parameters:

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetPreviousOccurrence( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetPreviousOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar uma ocorrencia que contem apenas o numero do
	// $$$ registro corrente
	if( !plbscolOcurrenceList ){
		if( PreviousFRecord( lbscTicket ) != LBS_OK ){
			// $$$ Erro
			return( NULL );
		}
		SetError( LBS_OK );
		LTC_OCCURRENCE	ltAux(	(CHARTYPE*) "", CurrRecNum( lbscTicket ),
					0, 0, 0, 0, 0 );
		
		lbscOcAux = ltAux;

		SetError( LBS_OK );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	LTC_OCCURRENCE *pCurOcc = plbscolOcurrenceList->GetCurrentOccurrence();	
	LTC_OCCURRENCE *pPreviousOcc = plbscolOcurrenceList->GetPreviousOccurrence();
	if( pCurOcc ){
		if( !pPreviousOcc || pCurOcc == pPreviousOcc ){
			// Ja' estamos na primeira ocorrencia
			lbscOcAux = *pCurOcc;
			SetError( LBSE_FIRSTOCCURRENCE );
		} else {
			lbscOcAux = *pPreviousOcc;
			SetError( LBS_OK );
		}
		ClearMaxRepetitionStatus( lbscOcAux );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}



/***
	PUBLIC
	Metodo GetNthOccurrence
	Obtem a n-esima ocorrencia da LO

	Parameters:
		- lPos -> posicao da lista da qual se deseja obter a ocorrencia

	Return:
		- Apontador para um objeto LBSC_Occurrence

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.
		- A aplicacao NAO deve deletar o objeto retornado por este metodo.

***/
const LBSC_Occurrence *
LBSC_Base::GetNthOccurrence( const LBSC_Ticket *lbscTicket, long lPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNthOccurrence") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// $$$ Se a lista de ocorrencias for NULL entao
	// $$$ devo retornar uma ocorrencia que contem apenas o numero do
	// $$$ registro corrente
	if( !plbscolOcurrenceList ){
		int iRet = GotoRec( lbscTicket, lPos );
		if( iRet != LBS_OK ){
			// $$$ Erro
			NRETURN( iRet );
		}
		SetError( LBS_OK );
		LTC_OCCURRENCE	ltAux(	(CHARTYPE*) "", CurrRecNum( lbscTicket ),
					0, 0, 0, 0, 0 );
		
		lbscOcAux = ltAux;

		SetError( LBS_OK );
		return( (LBSC_Occurrence *) &lbscOcAux );
	}

	if ( lPos >= plbscolOcurrenceList->GetNumberOfOccurrences() ) {
		NRETURN( LBSE_NOMEMORY );
	}

	// vamos para a n-esima ocorrencia dentro do registro corrente
	LTC_OCCURRENCE *pNthOcc = plbscolOcurrenceList->NthOccurrence( lPos );

	if( pNthOcc ){
		lbscOcAux = *pNthOcc;
		SetError( LBS_OK );
		ClearMaxRepetitionStatus( lbscOcAux );
		return( ( LBSC_Occurrence *) &lbscOcAux );
	}
	NRETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo IsEncrypt
	Obtem o estado de criptografia da base

	Parameters:
		-

	Return:
		- TRUE, caso a base esteja criptografada;
		  FALSE, caso contrario.

	Comments:
		- bIsEncrypt nunca muda. E' definido na criacao da base.

***/
BOOL
LBSC_Base::IsEncrypt()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( LB1.tcrHead.bIsEncrypt );
}


/***
	PUBLIC
	Metodo IsFullAccess
	Verifica se o usuario tem full access ou nao.

	Parameters:
		-

	Return:
		- TRUE, caso o usuario tenha aberto a base com
		  senha de manutencao; FALSE, caso contrario.

	Comments:
		-

***/
BOOL
LBSC_Base::IsFullAccess()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( bFullAccess );
}


/***
	PUBLIC
	Metodo GetUserBase
	Obtem o nome da base de usuarios associada aquela base

	Parameters:

	Return:
		- O nome da BU.

	Comments:
		- Este metodo retorna uma copia do buffer interno e
		  a aplicacao DEVE liberar o espaco alocado para a copia.

***/
char *
LBSC_Base::GetUserBase()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( ( bBaseObjOk == FALSE ) && ( bPrivateCreation == FALSE ) ){
		NRETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	return( Strdup( LB1.tcrHead.szUserBase ) );
}



/***
	PUBLIC
	Metodo GetOwnerName
	Obtem o nome do dono da base

	Parameters:

	Return:
		- O nome do dono da base.

	Comments:
		- Este metodo retorna uma copia do buffer interno e
		  a aplicacao DEVE liberar o espaco alocado para a copia.

***/
char *
LBSC_Base::GetOwnerName()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetOwnerName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( Strdup( (char*) LB1.tcrHead.szOwnerName ) );
}

/***
	PUBLIC
	Metodo GetFullBaseName
	Obtem o nome completo da base ( path + nome_da_base )

	Parameters:
		- szFullName

	Return:
		LBS_OK se conseguir montar o nome ou erro.

	Comments:

***/
int
LBSC_Base::GetFullBaseName( char *szFullName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFullBaseName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( strcpy( szFullName, (char*) szBasePath ) != NULL ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo GetBaseName
	Obtem o nome da base ( apenas o nome_da_base, sem o path )

	Parameters:
		- szName

	Return:
		- LBS_OK se conseguir montar o nome ou erro.

	Comments:

***/
int
LBSC_Base::GetBaseName( char *szName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( strcpy( szName, (char*) szCompleteBaseName ) != NULL ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}


/***
	PUBLIC
	Metodo GetBaseLongName
	Obtem o nome longo da base

	Parameters:
		- szName

	Return:
		- LBS_OK se conseguir montar o nome ou erro.

	Comments:
		- a string szName deve ter espaco suficiente para conter
		  o nome da base

***/
int
LBSC_Base::GetBaseLongName( char *szName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseLongName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( strcpy( szName, (char*) szBaseLongName ) != NULL ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo GetBaseType
	Obtem o tipo da base

	Parameters:
		-

	Return:
		- o tipo da base

	Comments:

***/
BYTE
LBSC_Base::GetBaseType()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseType") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( LB1.tcrHead.bBaseType );
}


/***
	PUBLIC
	Metodo ModifyBaseType
	Modifica o atributo tipo da base

	Parameters:
		- bNewBaseType

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:
		- o cara logado deve ser o dono da base.

***/
int
LBSC_Base::ModifyBaseType( BYTE bNewBaseType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyBaseType") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( ( bNewBaseType < BASE_PRIVATE ) || ( bNewBaseType > BASE_PUBLIC_REC_PRIVATE ) ){
		ERETURN( LBSE_BADARG );
	}
	// verifica se o cara logado eh o dono da base.
	if( !plbscsOwnerSession || 
		stricmp( plbscsOwnerSession->GetUserName(), (char*) LB1.tcrHead.szOwnerName ) != 0 ){
		// o cara nao eh o dono da base.
		ERETURN( LBSE_NOPERMISSION );
	}

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( cLB1_LockHead.LastError() != OK && cLB1_LockHead.LastError() != E_NEWHEAD ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}

		LB1.tcrHead.bBaseType = bNewBaseType;
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();
	}
	bBaseUpdated = TRUE;
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo ModifyBaseName
	Modifica o nome longo da base

	Parameters:
		- szNewBaseName

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:
		- este metodo atualiza o arquivo de controle do LBS com
		  a nova informacao.

***/
int
LBSC_Base::ModifyBaseName( char *szNewBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyBaseName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	C_SessCritSect	cCS4( plbscsOwnerSession, CRITSECT4 );

	if ( !plbscsOwnerSession->ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	const TBasesFile	*ptbfAux = plbscsOwnerSession->pControlFile->Get( szBaseName );
	if ( ptbfAux ) {
		// achamos a base
		TBasesFile	tbfAux = (*(TBasesFile *)ptbfAux);
		tbfAux.szBaseLongName = szNewBaseName;
		if ( plbscsOwnerSession->pControlFile->Set( tbfAux ) ) {
			ERETURN( LBS_OK );
		}
	}
	// deu merda
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo EnableOnLineIndex
	Ativa\desativa o modo de indexacao on-line de uma base

	Parameters:
		- bEnable

	Return:
		- LBS_OK.

	Comments:
		- 

***/
int
LBSC_Base::EnableOnLineIndex( BOOL bEnable )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::EnableOnLineIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( cLB1_LockHead.LastError() != OK && cLB1_LockHead.LastError() != E_NEWHEAD ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}
		LB1.tcrHead.bOnLineIndex = bEnable;
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();
	}

	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo UpdateIndex
	Indexa todos os registros que constarem no arquivo de log

	Parameters:
		- lbscTicket	-> ticket de seguranca

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Base::UpdateIndex( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	BOOL		bIsOpen = cfLB5.IsOpen();
	int			iRet = LBSE_NORECORD;
	BOOL		bErr = FALSE;
	char		*szMsg = NULL;				// para internacionalizacao de mensagens

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( bIsReadOnly ){
		ERETURN( LBSE_BASEREADONLY );
	}

	// nao permitir a reindexacao de bases anteriores ao 
	// numero magico OCCTREE_MAGICNUMBER
	if( GetBaseVersion() < OCCTREE_MAGICNUMBER ){
		ERETURN( LBSE_CANNOTINDEXOLDVERSION );
	}

	// verificar se ha' contexto de indexacao total a recuperar
	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) IDXCONTEXTFILE );

	if( C_File::Exist( szAux ) ){
		// o arquivo de contexto de indexacao existe. vamos 
		// disparar a indexacao total para fazer o que falta
		iRet = IndexAll( lbscTicket, TRUE );
		while( iRet == LBSW_INDEXSTOPED ){
			iRet = IndexAll( lbscTicket, TRUE );
		}
/*		if( iRet == LBSE_NORECORD ){
			// nao ha' registros para indexar, mas isso
			// nao deve ser considerado erro.
			iRet = LBS_OK;
		}

		iRet = ChangeIndex( lbscTicket, TOTAL_INDEX, TRUE, TRUE );
*/
		if( iRet != LBS_OK ){
			if( iRet == LBSE_LASTRECORD ){
				// esta eh a condicao natural de saida
				// da indexacao total.
				iRet = LBS_OK;
			} else {
				return( iRet );
			}
		}
	}

	if( !bIsOpen ){
		// Abrir LB5
		if( OpenLogFile( cfLB5 ) != LBS_OK ){
			// Nao conseguiu abrir LB5 (nao ha' registros para indexar)
			ERETURN( iRet );
		}
	}

	long		lRecTotAux = cfLB5.GetNumRecordsLogged();

	// resetar informacao de feedback
	ResetFeedbackInfo();
	SetNumSteps( 2 + lRecTotAux );	// 2 pontos fixos mais o loop dos registros

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

	// Pegar cada registro de LB5;
	// posicionar-se no registro correspondente ao encontrado em
	// LB5; reindexar o registro.
	int	iGrpBits;
	if( cfLB5.GetFirstGroupOfBits( &iGrpBits ) == OK ){
		int	iGroupNum = 0;
		do{
			int	iMask = 0x80000000;
			for( int iBit = 0; iBit < (sizeof( int )*8); iBit++ ){
				long	lNumRecord = (iBit+(iGroupNum*(sizeof( int )*8)));
				/*******************************************************/
				// informacao de feedback
				if( OperationCanceled() ){
					// operacao foi cancelada a pedido do usuario.
					bErr = TRUE;
					break;
				}
				if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
					char	szFullMsg[ 200 ];

					szMsg = _pcInter->GetGenMsgsAppVar( "LBSMSG_INDEXREC" );
					sprintf( szFullMsg, "%s %d/%d", szMsg, lNumRecord, lRecTotAux );
					IncStep( szFullMsg );
					delete szMsg;
				} else {
					IncStep( "" );
				}
				/*******************************************************/
				if( (iGrpBits & iMask) == 0 ){
					iMask = ((iMask >> 1) & ~iMask);
					continue;
				}
				
				iMask = ((iMask >> 1) & ~iMask);

				if( iMask == 0 ){
					iMask = 0x80000000;
				}

				if( GotoRec( lbscTicket, lNumRecord ) == LBS_OK ){
					// forcar a barra para que todos os campos sejam indexados
					int	iNumFields = GetNumberOfFields();
					for( int i = 0; i < iNumFields; i ++ ){
						LBSC_Field	*pf = lbscrCurrRecord[ i ];
						
						if( pf ){
							pf->UpdateFieldFlag( TRUE );
							pf->bMustFillOriginalDataList = TRUE;
							pf->FillOriginalDataList();
						}
					}
					iRet = Index( lbscTicket, PARTIAL_INDEX );
					if( iRet != LBS_OK ){
						bErr = TRUE;
					} else {
						// atualizar status do registro
						lbscrCurrRecord.bStatus &= ~REC_INLOGFILE;
						UpdateStatus( lbscTicket, 0 );
					}
				}
			}
			++iGroupNum;
		} while( cfLB5.GetNextGroupOfBits( &iGrpBits ) == OK );
	}
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

	// fechar o arquivo de log
	if( !bIsOpen ){
		cfLB5.CloseIndex();
	}

	// zerar o flag de atualizacao de todos os campos
	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i ++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];
		
		if( pf ){
			pf->UpdateFieldFlag( FALSE );
			pf->bMustFillOriginalDataList = TRUE;
			pf->lbscdlOriginalDataList.DelAll();
		}
	}
	if( !bErr ){
		// deletar o arquivo de log
		char		szAux[ FULLNAMESIZE ];
		sprintf( szAux, "%s\\%s%s", (char*) szBasePath, (char *)szBaseName, LOGFILE1EXT );
		remove( szAux );
	}
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo SetACLPerm
	Seta permissoes de ACL para um determinado registro
	ou campo.

	Parameters:
		- szName: nome do usuario/grupo;
		- lId: identificador do campo ou numero do registro;
		- szId: identificador do componente. Usado apenas para ACLs
				de componentes.
		- bMask: maskara de permissao;
			ACL_NONE, ACL_READ, ACL_WRITE, ACL_APPEND,
			ACL_DEL, ACL_ADM, ACL_RD_WR, ACL_WR_APP,
			ACL_RW_APP
		- iList: identificador da lista de ACL.
			USERBASE
			GROUPBASE
			USERFIELD
			GROUPFIELD
			USERRECORD
			GROUPRECORD
			USERFORM
			GORUPFORM
			USERREPORT
			GROUPREPORT

	Return:
		- LBS_OK.

	Comments:

***/
int
LBSC_Base::SetACLPerm( char *szName, long lId, char *szId, BYTE bMask, int iList )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetACLPerm") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szName ){
		ERETURN( LBSE_BADARG );
	}

	LBSC_ACLList	*plbscalACLList;
	LBSC_ACL		*plbscaACL;
	LBSC_Perm		*plbscpPerm;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// se a base for publica, nao podemos setar ACLs
	if( LB1.tcrHead.bBaseType == BASE_PUBLIC || LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ){
		// a nao ser para ACLs de componentes, por causa da conversao
		// automatica que o LBS faz (eh necessario setar ACLs de componentes)
		if( !ISCOMPONENTLIST( iList ) ){
			ERETURN( LBSE_ERROR );
		}
	}
	if( strcmp( szName, NAME_ASTERISK ) == 0 ){
		ERETURN( LBSE_BADARG );
	}

	// Verifica se o cara que estah logado eh o dono do
	// registro corrente (somente se este metodo for
	// chamado para setar ACL de registro)
	if( (iList == USERRECORD) || (iList == GROUPRECORD) ){
		if( stricmp( (char*) lbscrCurrRecord.GetOwnerName(),
			    (char*) plbscsOwnerSession->GetUserName() ) != 0 ){
			ERETURN( LBSE_NOPERMISSION );
		}
	} else {
		// vamos checar se o cara pode alterar ACLs
		// (na verificacao de ACL checamos se o usuario eh o dono da base)
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ID_ASTERISK, 
				USERFIELD, ACL_ADM ) != LBS_OK ){
			// a password passada bate com a de manutencao?
			if( LB1.tcrHead.szMaintenancePassword == (char*) "" ){
				// apenas o dono pode abrir a base.
				// permissao negada.
				ERETURN( LBSE_NOPERMISSION );
			}

			if ( !bFullAccess ) {	// a ultima chance...
				// permissao negada.
				ERETURN( LBSE_NOPERMISSION );
			}
		}
	}

	switch( iList ){
	case USERBASE:
		plbscalACLList = &lbscaBaseUserAcl;
		break;
	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		break;
	case USERFIELD:
		plbscalACLList = &lbscaFieldUserAcl;
		break;
	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		break;
	case USERRECORD:
		plbscalACLList = &lbscaRecordUserAcl;
		break;
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		break;
	case USERFORM:
		plbscalACLList = &lbscaFormUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case USERREPORT:
		plbscalACLList = &lbscaReportUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	default:
		ERETURN( LBSE_BADARG );
	}

	if( lId == ID_ASTERISK ){
		// so' vale para campo e componentes
		if( (iList != USERFIELD) && (iList != GROUPFIELD) ){
			ERETURN( LBSE_BADARG );
		}
		// setar ACL para todos os campos
		int	iNumFields = GetNumberOfFields();
		for( int i = 0; i < iNumFields; i++ ){
			// pegamos o Id do campo diretamente da lista de campos
			// para nao corrermos o risco de sermos barrados pelas
			// proprias ACLs.
			LBSC_Field	*pf = lbscrCurrRecord[ i ];
			
			if( !pf ){
				ERETURN( LBSE_FIELDNOTFOUND );
			}
			UINT	uiFieldIdAux = pf->GetId();
			switch( plbscalACLList->ACLFind( szName, uiFieldIdAux ) ){
			case LBS_OK:
				plbscalACLList->Current()->lbscplPermList.Current()->bPermission = bMask;
				break;

			case LBSE_NAMENOTFOUND:
				plbscaACL = new LBSC_ACL;
				plbscaACL->szName = strupr( szName );
				plbscalACLList->Add( plbscaACL, AFTER );
				/* no break here*/
			case LBSE_IDNOTFOUND:
				plbscpPerm = new LBSC_Perm;
				plbscpPerm->lId = uiFieldIdAux;
				plbscpPerm->bPermission = bMask;
				plbscalACLList->Current()->lbscplPermList.Add( plbscpPerm, AFTER );
				break;
			default:
				ERETURN( LBSE_ERROR );
			}
		}
	} else {
		if( iList == USERBASE || iList == GROUPBASE ){
			// ajusta o lId para o caso de estarmos trabalhando
			// com ACLs de BASE.
			lId = ID_BASE;
		}
		int iRet = ISCOMPONENTLIST( iList ) ? plbscalACLList->ACLFind( szName, szId ) : plbscalACLList->ACLFind( szName, lId );
		switch( iRet ){
		case LBS_OK:
			plbscalACLList->Current()->lbscplPermList.Current()->bPermission = bMask;
			break;

		case LBSE_NAMENOTFOUND:
			plbscaACL = new LBSC_ACL;
			plbscaACL->szName = szName;
			plbscalACLList->Add( plbscaACL, AFTER );
			/* no break here*/
		case LBSE_IDNOTFOUND:
			plbscpPerm = new LBSC_Perm;
			plbscpPerm->lId = lId;
			plbscpPerm->szId = szId;
			plbscpPerm->bPermission = bMask;
			plbscalACLList->Current()->lbscplPermList.Add( plbscpPerm, AFTER );
			break;
		default:
			ERETURN( LBSE_ERROR );
		}
	}
	if( bMask != ACL_NONE ){
		// inserir esta base nos campos USERBASEACCESSBASES
		// e USERBASEACCESSTYPES da UDB, no registro
		// correspondente ao usuario que esta' ganhando
		// permissao de ACL (apenas se o iList determinar um usuario).
		// DUVIDA (deveriamos fazer isso tambem para o caso de iList determinar
		// um grupo? A dificuldade de se fazer isso e': procurar na UDB todos os
		// registros que possuam o grupo especificado por szName e, para cada um
		// deles, chamar o metodo abaixo).
		if( iList == USERFIELD || iList == USERRECORD || iList == USERBASE ){
			plbscsOwnerSession->PutBaseInUDB( (char*) szBaseName, LB1.tcrHead.bBaseType, (char*) LB1.tcrHead.szUserBase, szName );
		}
	}
	bACLChanged = TRUE;
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DelACLPerm
	Deleta permissoes de ACL
	ou campo.

	Parameters:
		- szName: nome do usuario/grupo;
		- lId: identificador do campo ou numero do registro;
		- szId: identificador do componente. Usado apenas para ACLs
				de componentes.
		- iList: identificador da lista de ACL.
			USERBASE
			GROUPBASE
			USERFIELD
			GROUPFIELD
			USERRECORD
			GROUPRECORD
			USERFORM
			GORUPFORM
			USERREPORT
			GROUPREPORT

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Base::DelACLPerm( char *szName, long lId, char *szId, int iList )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelACLPerm") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_ACLList	*plbscalACLList;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica se o cara que estah logado eh o dono do
	// registro corrente (somente se este metodo for
	// chamado para setar ACL de registro)
	if( (iList == USERRECORD) || (iList == GROUPRECORD) ){
		if( stricmp( (char*) lbscrCurrRecord.GetOwnerName(),
			    (char*) plbscsOwnerSession->GetUserName() ) != 0 ){
			ERETURN( LBSE_NOPERMISSION );
		}
	} else {
		// vamos checar se o cara pode alterar ACLs
		// (na verificacao de ACL checamos se o usuario eh o dono da base)
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ID_ASTERISK, 
				USERFIELD, ACL_ADM ) != LBS_OK ){
			// a password passada bate com a de manutencao?
			if( LB1.tcrHead.szMaintenancePassword == (char*) "" ){
				// apenas o dono pode abrir a base.
				// permissao negada.
				ERETURN( LBSE_NOPERMISSION );
			}

			if ( !bFullAccess ) {	// a ultima chance...
				// permissao negada.
				ERETURN( LBSE_NOPERMISSION );
			}
		}
	}

	switch( iList ){
	case USERBASE:
		plbscalACLList = &lbscaBaseUserAcl;
		break;
	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		break;
	case USERFIELD:
		plbscalACLList = &lbscaFieldUserAcl;
		break;
	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		break;
	case USERRECORD:
		plbscalACLList = &lbscaRecordUserAcl;
		break;
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		break;
	case USERFORM:
		plbscalACLList = &lbscaFormUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case USERREPORT:
		plbscalACLList = &lbscaReportUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	default:
		ERETURN( LBSE_BADARG );
	}

	if( lId == ID_ASTERISK ){
		// so' vale para campo e componentes
		if( (iList != USERFIELD) && (iList != GROUPFIELD) && (!ISCOMPONENTLIST( iList )) ){
			ERETURN( LBSE_BADARG );
		}

		do {
			int iRet = ISCOMPONENTLIST( iList ) ? plbscalACLList->ACLFind( szName, szId ) : plbscalACLList->ACLFind( szName, lId );
			switch( iRet ){
			case LBS_OK:
			case LBSE_IDNOTFOUND:
				// encontramos pelo menos o szName.
				// deletar!!!
				plbscalACLList->Current()->lbscplPermList.DelAll();
				// Nesse caso, devemos deletar tambem a entrada na UDB que possui
				// o nome desta base (nos campos USERBASEACCESSBASES e
				// USERBASEACCESSTYPES)
				// DUVIDA (deveriamos fazer isso tambem para o caso de iList determinar
				// um grupo? A dificuldade de se fazer isso e': procurar na UDB todos os
				// registros que possuam o grupo especificado por szName e, para cada um
				// deles, chamar o metodo abaixo).
				if( iList == USERFIELD || iList == USERRECORD || iList == USERBASE ){
					plbscsOwnerSession->DelBaseOfUDB( (char*) szBaseName, (char*) LB1.tcrHead.szUserBase, (char*) (plbscalACLList->Current()->szName) );
				}
				// vamos retirar tambem o no' que possui no nome do usuario/grupo.
				plbscalACLList->Del();
				break;

			case LBSE_NAMENOTFOUND:
				if( strcmp( szName, NAME_ASTERISK ) == 0 ){
					continue;
				}
				// szName nao encontrado
				ERETURN( LBSE_INVALIDNAME );
			default:
				ERETURN( LBSE_ERROR );
			}
		} while( ( strcmp( szName, NAME_ASTERISK ) == 0 ) && ( plbscalACLList->NumElem() != 0 ) );
	} else {
		if( iList == USERBASE || iList == GROUPBASE ){
			// ajusta o lId para o caso de estarmos trabalhando
			// com ACLs de BASE.
			lId = ID_BASE;
		}
		do {
			int iRet = ISCOMPONENTLIST( iList ) ? plbscalACLList->ACLFind( szName, szId ) : plbscalACLList->ACLFind( szName, lId );
			switch( iRet ){
			case LBS_OK:
				// deletar!!!
				plbscalACLList->Current()->lbscplPermList.Del();
				// se nao sobrou nenhum elemento de ACL para o usuario/grupo em questao,
				// vamos retirar tambem o no' que possui no nome do usuario/grupo.
				if( plbscalACLList->Current()->lbscplPermList.NumElem() == 0 ){
					// Nesse caso, devemos deletar tambem a entrada na UDB que possui
					// o nome desta base (nos campos USERBASEACCESSBASES e
					// USERBASEACCESSTYPES)
					// DUVIDA (deveriamos fazer isso tambem para o caso de iList determinar
					// um grupo? A dificuldade de se fazer isso e': procurar na UDB todos os
					// registros que possuam o grupo especificado por szName e, para cada um
					// deles, chamar o metodo abaixo).
					if( iList == USERFIELD || iList == USERRECORD || iList == USERBASE ){
						plbscsOwnerSession->DelBaseOfUDB( (char*) szBaseName, (char*) LB1.tcrHead.szUserBase, (char*) (plbscalACLList->Current()->szName) );
					}
					plbscalACLList->Del();
				}
				break;

			case LBSE_NAMENOTFOUND:
				if( strcmp( szName, NAME_ASTERISK ) == 0 ){
					continue;
				}
				ERETURN( LBSE_INVALIDNAME );

			case LBSE_IDNOTFOUND:
				if( strcmp( szName, NAME_ASTERISK ) == 0 ){
					continue;
				}
				ERETURN( LBSE_INVALIDID );

			default:
				ERETURN( LBSE_ERROR );
			}
		} while( ( strcmp( szName, NAME_ASTERISK ) == 0 ) && ( plbscalACLList->NumElem() != 0 ) );
	}
	bACLChanged = TRUE;
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetACLPerm
	Obtem a mascara de permissoes de ACL de um determinado
	registro ou campo.

	Parameters:
		- szName: nome do usuario/grupo;
		- lId: identificador do campo ou numero do registro;
		- szId: identificador do componente. Usado apenas para ACLs
				de componentes.
		- iList: identificador da lista de ACL.
			USERBASE
			GROUPBASE
			USERFIELD
			GROUPFIELD
			USERRECORD
			GROUPRECORD
			USERFORM
			GORUPFORM
			USERREPORT
			GROUPREPORT
		- bCheckAll: Indica se todas as permissoes possiveis devem
		  ou nao ser checadas. O default eh TRUE, o que indica que o
		  LBS verificara' as permissoes de base e de grupo, caso o
		  usuario queira verificar permissoes de campo. Se for passado
		  FALSE, o LBS verifica apenas o que o usuario pedir.

	Return:
		- a maskara de permissao;
			ACL_NONE, ACL_READ, ACL_WRITE, ACL_APPEND,
			ACL_DEL, ACL_ADM, ACL_RD_WR, ACL_WR_APP,
			ACL_RW_APP
		ou codigo de erro.

	Comments:
		- o metodo retorna inteiro por causa dos codigos
		  de erro. Deve-se fazer um cast para BYTE quando
		  for manipular o retorno como maskara. 

***/
int
LBSC_Base::GetACLPerm( char *szName, long lId, char *szId, int iList, BOOL bCheckAll )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetACLPerm") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_ACLList	*plbscalACLList;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		SetError( LBSE_INVALIDLIC );
		return( LBSE_UNDEFINEDACL );
	}

	if( LB1.tcrHead.bBaseType == BASE_PUBLIC ){
		// a base eh publica
		SetError( LBS_OK );
		return( ACL_ADM );
	}
	if( (LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE) &&
	    ( iList != USERRECORD ) && ( iList != GROUPRECORD ) ){
    	// a base eh publica com restricao de registro e
		// a ACL pedida nao eh de registro
		SetError( LBS_OK );
		return( ACL_ADM );
	}
	BOOL bAdmUser = ( plbscsOwnerSession->plbscuUser->GetUserType() == MASTER_USER || 
				LB1.tcrHead.szOwnerName == plbscsOwnerSession->plbscuUser->GetUserName());
	if ( bAdmUser && ISCOMPONENTLIST( iList ) && GetBaseType() == USER_BASE ) {
		// administradores podem tudo caso seja uma base de formularios ou relatorios de uma UDB
		SetError( LBS_OK );
		return( ACL_ADM );
	}

	// Verifica se o usuario eh o dono do
	// registro corrente (somente se este metodo for
	// chamado para verificar ACL de registro)
	if( (iList == USERRECORD) || (iList == GROUPRECORD) ){
		if( lbscrCurrRecord.GetOwnerName() && szName ){
			if( stricmp( (char*) lbscrCurrRecord.GetOwnerName(), szName ) == 0 ){
				SetError( LBS_OK );
				return( ACL_ADM );
			}
		}
	} else {
		// verifica se o usuario eh o dono
		// da base (somente se este metodo for chamado
		// para verificar ACL de campo ou de base ou de componente)
		if( LB1.tcrHead.szOwnerName == szName && 
				LB1.tcrHead.bBaseType != USER_BASE ){
			SetError( LBS_OK );
			return( ACL_ADM );
		}
//		// verifica se o cara que esta' logado informou a password da base corretamente
//		// no OpenBase
//		if( bIsBasePasswdCorrect ){
//			SetError( LBS_OK );
//			return( ACL_ADM );
//		}
	}

	switch( iList ){
	case USERBASE:
		plbscalACLList = &lbscaBaseUserAcl;
		break;
	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		break;
	case USERFIELD:
		plbscalACLList = &lbscaFieldUserAcl;
		break;
	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		break;
	case USERRECORD:
		plbscalACLList = &lbscaRecordUserAcl;
		break;
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		break;
	case USERFORM:
		plbscalACLList = &lbscaFormUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case USERREPORT:
		plbscalACLList = &lbscaReportUserAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		if( !szId ){
			ERETURN( LBSE_BADARG );
		}
		break;
	default:
		ERETURN( LBSE_BADARG );
	}

	int iRet = ISCOMPONENTLIST( iList ) ? plbscalACLList->ACLFind( szName, szId ) : plbscalACLList->ACLFind( szName, lId );
	if( iRet == LBS_OK ){
		SetError( LBS_OK );
		return( plbscalACLList->Current()->lbscplPermList.Current()->bPermission );
	}

	if( bCheckAll ){
		switch( iList ){
		case USERBASE:
			// nao achamos ACL de usuario, vamos verificar as ACLs de grupo, em busca
			// da melhor permissao possivel.
			if( lbscaBaseGroupAcl.NumElem() > 0 ){
				int iRet = ACLGroupFind( szName, NAME_ASTERISK, lId, szId, GROUPBASE, ACL_BEST );
				if( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ){
					SetError( LBS_OK );
					return( lbscaBaseGroupAcl.Current()->lbscplPermList.Current()->bPermission );
				}
			}
			break;

		case USERFIELD:
			// nao achamos ACL de usuario, vamos verificar as ACLs de grupo, em busca
			// da melhor permissao possivel.
			if( lbscaFieldGroupAcl.NumElem() > 0 ){
				int iRet = ACLGroupFind( szName, NAME_ASTERISK, lId, szId, GROUPFIELD, ACL_BEST );
				if( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ){
					SetError( LBS_OK );
					return( lbscaFieldGroupAcl.Current()->lbscplPermList.Current()->bPermission );
				}
			}
			break;

		case USERFORM:
			// nao achamos ACL de usuario, vamos verificar as ACLs de grupo, em busca
			// da melhor permissao possivel.
			if( lbscaFormGroupAcl.NumElem() > 0 ){
				int iRet = ACLGroupFind( szName, NAME_ASTERISK, lId, szId, GROUPFORM, ACL_BEST );
				if( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ){
					SetError( LBS_OK );
					return( lbscaFormGroupAcl.Current()->lbscplPermList.Current()->bPermission );
				}
			}
			break;

		case USERREPORT:
			// nao achamos ACL de usuario, vamos verificar as ACLs de grupo, em busca
			// da melhor permissao possivel.
			if( lbscaReportGroupAcl.NumElem() > 0 ){
				int iRet = ACLGroupFind( szName, NAME_ASTERISK, lId, szId, GROUPREPORT, ACL_BEST );
				if( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ){
					SetError( LBS_OK );
					return( lbscaReportGroupAcl.Current()->lbscplPermList.Current()->bPermission );
				}
			}
			break;

		default:
			break;
		}
	}
	// nao ha' ACL
	ERETURN( LBSE_UNDEFINEDACL );
}

/***
	PUBLIC
	Metodo GetACLListPermission
	Obtem a lista de permissoes de ACL de um usuario ou grupo.

	Parameters:
		- szName: nome do usuario/grupo;
		- iList: identificador da lista de ACL.
			USERBASE		
			GROUPBASE		
			USERFIELD		
			GROUPFIELD		
			USERRECORD		
			GROUPRECORD		
			USERFORM
			GORUPFORM
			USERREPORT
			GROUPREPORT

	Return:
		- a lista de permissoes ou NULL se ocorrer erro.

	Comments:
		- A aplicacao DEVE deletar o objeto retornado por este metodo.

***/
LBSC_PermList *
LBSC_Base::GetACLListPermission( char *szName, int iList )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetACLListPermission") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_ACLList	*plbscalACLList;
	LBSC_PermList	*plbscplPermList;

	switch( iList ){
	case USERBASE:
		plbscalACLList = &lbscaBaseUserAcl;
		break;
	case GROUPBASE:
		plbscalACLList = &lbscaBaseGroupAcl;
		break;
	case USERFIELD:
		plbscalACLList = &lbscaFieldUserAcl;
		break;
	case GROUPFIELD:
		plbscalACLList = &lbscaFieldGroupAcl;
		break;
	case USERRECORD:
		plbscalACLList = &lbscaRecordUserAcl;
		break;
	case GROUPRECORD:
		plbscalACLList = &lbscaRecordGroupAcl;
		break;
	case USERFORM:
		plbscalACLList = &lbscaFormUserAcl;
		break;
	case GROUPFORM:
		plbscalACLList = &lbscaFormGroupAcl;
		break;
	case USERREPORT:
		plbscalACLList = &lbscaReportUserAcl;
		break;
	case GROUPREPORT:
		plbscalACLList = &lbscaReportGroupAcl;
		break;
	default:
		NRETURN( LBSE_BADARG );
	}

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	if( plbscalACLList->ACLFind( szName, -1 ) == LBS_OK ){
		plbscplPermList = new LBSC_PermList;
		// duplica a lista
		(*plbscplPermList) = plbscalACLList->Current()->lbscplPermList;
		SetError( LBS_OK );
		return( plbscplPermList );
	}

	NRETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo IndexAll
	(Re)indexa todos os registros da base

	Parameters:
		- lbscTicket	-> ticket de acesso
		- bRestoreContext -> indica se a rotina deve restaurar um contexto
				anterior (TRUE) ou se deve inicializar a indexacao
				a partir do primeiro registro (FALSE, default).

	Return:
		- LBS_OK se conseguir indexar a base ou erro.

	Comments:
		- Esta operacao pode ser demorada

***/
int
LBSC_Base::IndexAll( const LBSC_Ticket *lbscTicket, BOOL bRestoreContext )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IndexAll") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// nao permitir a reindexacao de bases anteriores ao 
	// numero magico OCCTREE_MAGICNUMBER
	if( GetBaseVersion() < OCCTREE_MAGICNUMBER ){
		ERETURN( LBSE_CANNOTINDEXOLDVERSION );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bIsReadOnly ){
		ERETURN( LBSE_BASEREADONLY );
	}
	// guarda o estado de bFullAccess
	// se essa variavel estiver com valor TRUE, o metodo Index retornara' erro,
	// pois ele nao permite indexacao dos dados em modo de manutencao.
	BOOL bMaint = bFullAccess;
	bFullAccess = FALSE;

	int iRet = Index( lbscTicket, TOTAL_INDEX, bRestoreContext );
	
	bFullAccess = bMaint;
	return( iRet );
}


/***
	PUBLIC
	Metodo OnLineIndexStatus
	Verifica o status de indexacao.

	Parameters:

		
	Return:
		- LBS_OK se os status de indexacao esta online.

	Comments:

***/
BOOL
LBSC_Base::OnLineIndexStatus()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OnLineIndexStatus") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( LB1.tcrHead.bOnLineIndex );
}

/***
	PUBLIC
	Metodo GetNumOcorrences
	Captura o numero de ocorrencias da lista de LO's.

	Parameters:
		- lbscTicket.

	Return:
		- o numero de ocorrencias.

	Comments:
        
***/
long
LBSC_Base::GetNumOccurrences( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumOccurrences") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	if( !plbscolOcurrenceList ){
		LB1.R_ReadHead();
		SetError( LBS_OK );
		return( LB1.tcrHead.lNumRecords );
	}
	SetError( LBS_OK );
	return( plbscolOcurrenceList->GetTotalNumberOfOccurrences() );
}

/***
	PUBLIC
	Metodo AddGoWord
	Adiciona uma GoWord a um campo passado como parametro.

	Parameters:
		- uiId: o campo onde a GoWord sera adicionada;
		- szGoWord.

	Return:
		LBS_OK em caso de sucesso.

        Comments:
                	
	
***/
int
LBSC_Base::AddGoWord( UINT uiId, char *szGoWord )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddGoWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	LBSC_Field	*pf = (*this)( uiId );
	if( !pf ){
		return( LastError() );
	}
	if( pf->AddGoWord( szGoWord ) != 0 ){
		ERETURN( LBSE_ERROR );
	}
	SetGowords( pf->pltcgwGoWords );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DelGoWord
	Deleta uma GoWord de um campo passado como parametro.

	Parameters:
		- uiId: o campo de onde a GoWord será deletada;
		- szGoWord;

	Return:
		- LBS_OK em caso de sucesso.

	Comments:

***/
int
LBSC_Base::DelGoWord( UINT uiId, char *szGoWord )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelGoWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	LBSC_Field	*pf = (*this)( uiId );
	if( !pf ){
		return( LastError() );
	}
	if( pf->DelGoWord( szGoWord ) != 0 ){
		ERETURN( LBSE_ERROR );
	}
	SetGowords( pf->pltcgwGoWords );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo ModifyBaseOwnerName
	Modifica o atributo dono da base

	Parameters:
		- szOwnerName

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:
		- 

***/
int
LBSC_Base::ModifyBaseOwnerName( const LBSC_Ticket *plbscTicket, char *szOwnerNamePar, char *szCurrentPsw )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyBaseOwnerName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( plbscsOwnerSession->TicketIsOk( plbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( szOwnerNamePar == NULL ){
		ERETURN( LBSE_BADARG );
	}

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( cLB1_LockHead.LastError() != OK && cLB1_LockHead.LastError() != E_NEWHEAD ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}
		// checar a password corrente
		if( LB1.tcrHead.szBasePassword != szCurrentPsw ){
			ERETURN( LBSE_INVALIDPASSWORD );
		}
		LB1.tcrHead.szOwnerName = szOwnerNamePar;
		bBaseUpdated = TRUE;
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();
	}
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo BlockReExport
	Modifica o atributo de reexportacao da base

	Parameters:
		- plbscTicket

	Return:
		- LBS_OK em caso de sucesso.

	Comments:

***/
int
LBSC_Base::BlockReExport( const LBSC_Ticket *plbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::BlockReExport") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( plbscsOwnerSession->TicketIsOk( plbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( cLB1_LockHead.LastError() != OK && cLB1_LockHead.LastError() != E_NEWHEAD ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}
		LB1.tcrHead.bReExport = FALSE;
		bBaseUpdated = TRUE;
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();
	}
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo IsExportable
	Obtem o flag de re-exportacao da base

	Parameters:


	Return:
		- TRUE para indicar que a base pode ser exportada;
		  FALSE para indicar o contrario

	Comments:

***/
BOOL
LBSC_Base::IsExportable()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IsExportable") );

	SetError( LBS_OK );
	return( LB1.tcrHead.bReExport );
}


/***
	PUBLIC
	Metodo IsExclusive
	Informa se a base esta' aberta em modo exclusivo ou nao

	Parameters:


	Return:
		- TRUE para indicar que a base esta' em modo exclusivo;
		  FALSE para indicar o contrario

	Comments:

***/
BOOL
LBSC_Base::IsExclusive()
{
	SetError( LBS_OK );
	return( bIsExclusive );
}

/***
	PUBLIC
	Metodo IsReadOnly
	Informa se a base esta' aberta em modo read-only ou nao

	Parameters:


	Return:
		- TRUE para indicar que a base esta' em modo read-only;
		  FALSE para indicar o contrario

	Comments:

***/
BOOL
LBSC_Base::IsReadOnly()
{
	SetError( LBS_OK );
	return( bIsReadOnly );
}



/***
	PUBLIC
	Metodo GetNumberOfSlots
	Captura o numero de Slots numa base.

	Parameters:


	Return:
		- o numero de Slots pesquisado.

	Comments:


***/
int
LBSC_Base::GetNumberOfSlots()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	return( LB1.tcrHead.iSlotNum - 1 );	// menos um porque o zero eh privado
}


/***
	PUBLIC
	Metodo GetNumberOfCounters
	Captura o numero de contadores numa base.

	Parameters:


	Return:
		- o numero de contadores pesquisado.

	Comments:


***/
int
LBSC_Base::GetNumberOfCounters()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	return( LB1.tcrHead.iCountNum );
}


/***
	PUBLIC
	Metodo GetSlot
	Captura a informacao dentro da slot passada como parametro.

	Parameters:
		- iIndex: o numero da slot;
		- szBuffer: o endereco de retorno.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetSlot( int iIndex, void *szBuffer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetSlot") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// a regiao critica abaixo protege a operacao de atualizacao do LB2
	C_BaseCritSect	cCS13( this, CRITSECT13 );

	if( (iIndex < 1 && !bPrivateCreation) || iIndex > LB1.tcrHead.iSlotNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( ptsrStructRecHead->spSlot[ iIndex ].lPointer == 0 ){
		// nao ha' slot gravado ainda
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_EMPTYSLOT );
	}
	if( cfSlotsFile.Seek( ptsrStructRecHead->spSlot[ iIndex ].lPointer, SEEK_SET ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( cfSlotsFile.Read( szBuffer, ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetSlotSize
	Captura o tamanho do conteudo da slot.

	Parameters:
		- iIndex: o numero da slot

	Return:
		- o tamanho pesquisado.

	Comments:


***/
long
LBSC_Base::GetSlotSize( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetSlotSize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( (iIndex < 1 && !bPrivateCreation) || iIndex > LB1.tcrHead.iSlotNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( ptsrStructRecHead->spSlot[ iIndex ].lPointer <= 0 ){
		// nao ha' slot gravado ainda
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_EMPTYSLOT );
	}
	long lSize = ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize;
	// checa o arquivo LB4
	if( !cfSlotsFile.IsOpen() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_BASENOTOPEN );
	}
	long lfSize		= cfSlotsFile.FileSize();
	if ( lSize < 0 || 
			lSize > ( lfSize - ptsrStructRecHead->spSlot[ iIndex ].lPointer ) ){
		// O tamanho do slot deste campo está inválido (maior que o possível).
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}

	SetError( LBS_OK );
	TStructHeadRec::Free( ptsrStructRecHead );
	return lSize;
}

/***
	PUBLIC
	Metodo PutSlot
	Coloca a informacao passada como parametro na slot.

	Parameters:
		- iIndex: o numero da slot;
		- szBuffer: a informacao a ser gravada;
		- iLen: o tamanho da informacao.

	Return:
		- LBS_OK caso obtenha sucesso.

	Comments:
		- Se o parametro szBuffer for NULL, o slot sera' zerado.


***/
int
LBSC_Base::PutSlot( int iIndex, void *szBuffer, int iLen )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutSlot") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// a regiao critica abaixo protege a operacao de atualizacao do LB2
	C_BaseCritSect	cCS13( this, CRITSECT13 );

	if( (iIndex < 1 && !bPrivateCreation) || iIndex > LB1.tcrHead.iSlotNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.LB3_LockHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_HEADERROR );
	}
	if( ptsrStructRecHead->spSlot[ iIndex ].lPointer != 0 ){
		/*** para evitar maiores problemas e por nao ser uma operacao muito frequente
			estamos evitando fazer a delecao; se o ponteiro estiver invalido (e como
			nao temos como valida-lo como na leitura de um registro, eh melhor nao
			liberar esse espaco em LB4 
		if( LB4.D_FreeSpace( ptsrStructRecHead->spSlot[ iIndex ].lPointer,
			ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize ) < 0 ){
			TStructHeadRec::Free( ptsrStructRecHead );
			LB3.R_ReleaseHead();
			ERETURN( LBSE_ERROR );
		}
		***/
	}
	long lPointer=0;
	if( szBuffer ){
		lPointer = cfSlotsFile.D_GetFreeSpace( iLen +
				5 /* extra por via das duvidas... */ );
		if( lPointer <= 0 ){
			TStructHeadRec::Free( ptsrStructRecHead );
			LB3.R_ReleaseHead();
			ERETURN( LBSE_FATAL );
		}
		if( cfSlotsFile.Seek( lPointer, SEEK_SET ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			LB3.R_ReleaseHead();
			ERETURN( LBSE_FATAL );
		}
		if( cfSlotsFile.Write( szBuffer, iLen ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			LB3.R_ReleaseHead();
			ERETURN( LBSE_FATAL );
		}
	}
	ptsrStructRecHead->spSlot[ iIndex ].lPointer = szBuffer ? lPointer : 0;
	ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize = szBuffer ? iLen : 0;
	if( LB3.LB3_ReleaseHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		LB3.R_ReleaseHead();
		ERETURN( LBSE_FATAL );
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetFieldSlot
	Captura a slot do campo passado como parametro.

	Parameters:
		- uiId: o campo;
		- szBuffer: o endereco de retorno.

	Return:
		- LBS_OK em caso de sucesso.

	Comments:


***/
int
LBSC_Base::GetFieldSlot( UINT uiId, void *szBuffer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldSlot") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// checa se o campo existe em memoria
	// (checa diretamente na lista de campos para nao correr o risco de
	// ser barrado pelas ACLs)

	// pra evitar a carga de todos os dados do registro so porque estamos querendo obter a estrutura
	BOOL bAux = lbscrCurrRecord.bMustLoadData;
	lbscrCurrRecord.bMustLoadData = FALSE;
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	// reabilita a carga dos dados dos campos
	lbscrCurrRecord.bMustLoadData = bAux;
	if( !pf ){
		return( LBSE_FIELDNOTFOUND );
	}
	if ( pf->lSlotSize <= 0 || !pf->pvSlot ) {
		ERETURN( LBSE_EMPTYSLOT );
	}
	memcpy( szBuffer, pf->pvSlot, pf->lSlotSize );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetFieldSlotSize
	Captura o tamanho da slot do campo passado como parametro.

	Parameters:
		- uiId: o campo.

	Return:
		- o tamanho pesquisado.

	Comments:


***/
long
LBSC_Base::GetFieldSlotSize( UINT uiId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldSlotSize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// checa se o campo existe em memoria
	// (checa diretamente na lista de campos para nao correr o risco de
	// ser barrado pelas ACLs)

	// pra evitar a carga de todos os dados do registro so porque estamos querendo obter a estrutura
	BOOL bAux = lbscrCurrRecord.bMustLoadData;
	lbscrCurrRecord.bMustLoadData = FALSE;
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	// reabilita a carga dos dados dos campos
	lbscrCurrRecord.bMustLoadData = bAux;
	if( !pf ){
		return( LBSE_FIELDNOTFOUND );
	}
	SetError( LBS_OK );
	return( pf->lSlotSize );
}

/***
	PUBLIC
	Metodo PutFieldSlot
	Coloca uma informacao na slot do campo passado como parametro.

	Parameters:
		- uiId: o campo;
		- szBuffer: a informacao;
		- iLen: o tamanho da informacao;

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Se o parametro szBuffer for NULL, o slot sera' zerado.


***/
int
LBSC_Base::PutFieldSlot( UINT uiId, void *szBuffer, int iLen )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldSlot") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// a regiao critica abaixo protege a operacao de atualizacao do LB2
	C_BaseCritSect	cCS13( this, CRITSECT13 );

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	// checa se o campo existe em memoria
	// (checa diretamente na lista de campos para nao correr o risco de
	// ser barrado pelas ACLs)
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	if( !pf ){
		return( LBSE_FIELDNOTFOUND );
	}
	// checa o arquivo LB3
	if( !LB3.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	TStructRec	sRec;
	int	iNumF = LB3.R_FileSize();
	// procura em LB3 o campo com id = uiId
	for( int i = 0; i < iNumF; i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &sRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(sRec.uiFieldAttrib & DELETED_FIELD) && ( sRec.uiFieldId == uiId ) ){
			// achei o campo que estava procurando
			// tentar travar o campo para alterar o slot
			if( LB3.R_Lock() != OK ){
				ERETURN( LBSE_HEADERROR );
			}
			if( sRec.spSlot.lPointer != 0 ){
			/*** para evitar maiores problemas e por nao ser uma operacao muito frequente
				estamos evitando fazer a delecao; se o ponteiro estiver invalido (e como
				nao temos como valida-lo como na leitura de um registro, eh melhor nao
				liberar esse espaco em LB4 
				if( LB4.D_FreeSpace( sRec.spSlot.lPointer,
						sRec.spSlot.pElem.lSize ) < 0 ){
					LB3.R_Release();
					ERETURN( LBSE_ERROR );
				}
			***/
			}
			long lPointer=0;
			// invalida a cache de campos dessa base
			pBaseInstance->InvalidateBaseStruct();

			if( szBuffer ){
				lPointer = cfSlotsFile.D_GetFreeSpace( iLen +
						5 /* extra por via das duvidas... */ );
				if( lPointer <= 0 ){
					LB3.R_Release();
					ERETURN( LBSE_FATAL );
				}
				if( cfSlotsFile.Seek( lPointer, SEEK_SET ) != OK ){
					LB3.R_Release();
					ERETURN( LBSE_FATAL );
				}
				if( cfSlotsFile.Write( szBuffer, iLen ) != OK ){
					LB3.R_Release();
					ERETURN( LBSE_FATAL );
				}
				void *pvFieldSlot = new char[iLen];
				if ( pvFieldSlot ) {
					memcpy( pvFieldSlot, szBuffer, iLen );
					pf->SetSlot( iLen, pvFieldSlot );
				}
			} else {
				pf->SetSlot( 0, NULL );
			}
			sRec.spSlot.lPointer = szBuffer ? lPointer : 0;
			sRec.spSlot.pElem.lSize = szBuffer ? iLen : 0;
			if( LB3.R_Write( &sRec ) != OK ){
				LB3.R_Release();
				ERETURN( LBSE_FATAL );
			}
			LB3.R_Release();
			ERETURN( LBS_OK );
		}
	}
	ERETURN( LBSE_FIELDNOTFOUND );
}



/***
	PUBLIC
	Metodo GetCount
	Captura o valor corrente do contador passado como parametro

	Parameters:
		- iIndex: o numero do contador;

	Return:
		- o valor do contador indicado

	Comments:

***/
long
LBSC_Base::GetCount( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

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
		if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			ERETURN( LBSE_ERROR );
		}
		long lCount = ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount;
		TStructHeadRec::Free( ptsrStructRecHead );
		SetError( LBS_OK );
		return( lCount );
	}
	long	lAux;

	if( LB3.LoadCount( iIndex, lAux ) == OK ){
		SetError( LBS_OK );
		return( lAux );
	}
	ERETURN( LBSE_ERROR );
}


/***
	PUBLIC
	Metodo PutCount
	Coloca um valor em um determinado contador da base

	Parameters:
		- iIndex: o numero do contador;
		- lCount: o valor a ser armazenado;

	Return:
		- LBS_OK caso obtenha sucesso.

	Comments:
		- Este metodo so' pode ser utilizado quando a base estiver aberta
		  em modo exclusivo ou manutencao.

***/
int
LBSC_Base::PutCount( int iIndex, long lCount )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

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
		ptsrStructRecHead->spSlot[ LB1.tcrHead.iSlotNum + iIndex ].pElem.lCount = lCount;
		if( LB3.LB3_ReleaseHead( ptsrStructRecHead ) != OK ){
			TStructHeadRec::Free( ptsrStructRecHead );
			LB3.R_ReleaseHead();
			ERETURN( LBSE_FATAL );
		}
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBS_OK );
	}
	if( LB3.SaveCount( iIndex, lCount ) == OK ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_LOCKERROR );
}


/***
	PUBLIC
	Metodo IncCount
	Incrementa o valor de um determinado contador da base

	Parameters:
		- iIndex: o numero do contador;
		- lCount: o valor a ser incrementado (default = 1);

	Return:
		- LBS_OK caso obtenha sucesso.

	Comments:
		-

***/
int
LBSC_Base::IncCount( int iIndex, long lCount )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IncCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	C_BaseCritSect	cCS11( this, CRITSECT11 );
	
	PrivIncCount( iIndex, lCount );

	return( LastError() );
}



/***
	PUBLIC
	Metodo DecCount
	Decrementa o valor de um determinado contador da base

	Parameters:
		- iIndex: o numero do contador;
		- lCount: o valor a ser decrementado (default = 1);

	Return:
		- LBS_OK caso obtenha sucesso.

	Comments:
		-

***/
int
LBSC_Base::DecCount( int iIndex, long lCount )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DecCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	C_BaseCritSect	cCS11( this, CRITSECT11 );

	PrivDecCount( iIndex, lCount );

	return( LastError() );
}


/***
	PUBLIC
	Metodo GetNextCount
	Incrementa o valor de um contador e retorna o valor resultante

	Parameters:
		- iIndex: o numero do contador;

	Return:
		- o valor do contador indicado, depois do incremento

	Comments:
		- Como um valor negativo pode ser um valor valido, eh bom consultar
		  o LastError apos este metodo para ter certeza do sucesso.

***/
long
LBSC_Base::GetNextCount( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNextCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	C_BaseCritSect	cCS11( this, CRITSECT11 );

	long	lRet = PrivIncCount( iIndex );

	if( LastError() != LBS_OK ){
		return( LastError() );
	}
	return( lRet );
}




/***
	PUBLIC
	Metodo GetPreviousCount
	Decrementa o valor de um contador e retorna o valor resultante

	Parameters:
		- iIndex: o numero do contador;

	Return:
		- o valor do contador indicado, depois do decremento

	Comments:
		- Como um valor negativo pode ser um valor valido, eh bom consultar
		  o LastError apos este metodo para ter certeza do sucesso.

***/
long
LBSC_Base::GetPreviousCount( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetPreviousCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	C_BaseCritSect	cCS11( this, CRITSECT11 );

	long	lRet = PrivDecCount( iIndex );

	if( LastError() != LBS_OK ){
		return( LastError() );
	}
	return( lRet );
}


/***
	PUBLIC
	Metodo LockCount
	Trava um contador no arquivo LB3

	Parameters:
		- iIndex: o numero do contador;
		- bWait:  indica se a rotina deve esperar ate' conseguir o lock ou se deve
				  retornar caso nao consiga. Valor default = FALSE, indicando que
				  a rotina retorna imediatamente apos a tentativa de lock, 
				  independentemente de ter conseguido faze-lo ou nao.

	Return:
		- LBS_OK em caso de sucesso ou um codigo de erro.

	Comments:

***/
int
LBSC_Base::LockCount( int iIndex, BOOL bWait )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LockCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

//	C_BaseCritSect	cCS11( this, CRITSECT11 );	isso vai evitar deadlock; o lock ja da exclusao mutua

	if( iIndex < 0 || iIndex >= LB1.tcrHead.iCountNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	// vamos pegar o timeout de lock de contadores de lifile
	int iLockTmOut = LBSC_ServerConfig::CounterLockTimeOut(); 
	DWORD dwInicio = GetTickCount();

	while ( LB3.LockCount( iIndex, FALSE ) != OK ){
		if ( !bWait ) {
			ERETURN( LBSE_LOCKERROR );
		}

		Sleep( 1000 );
		DWORD dwFim = GetTickCount();
		if ( (dwFim - dwInicio) > iLockTmOut*1000 ) { // em milisegundos..
			ERETURN( LBSE_LOCKERROR );
		}
	}
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo ReleaseCount
	Destrava um contador no arquivo LB3

	Parameters:
		- iIndex: o numero do contador;

	Return:
		- LBS_OK em caso de sucesso ou um codigo de erro.

	Comments:

***/
int
LBSC_Base::ReleaseCount( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ReleaseCount") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

//	C_BaseCritSect	cCS11( this, CRITSECT11 ); 	isso vai evitar deadlock; o lock ja da exclusao mutua

	if( iIndex < 0 || iIndex >= LB1.tcrHead.iCountNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( LB3.ReleaseCount( iIndex ) == OK ){
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_LOCKERROR );
}

/***
	Metodo IndexSystemOk
	Retorna o estado do sistema de indices da base

	Parameters:
		-

	Return:
		- TRUE se o sistema de indices estiver aberto; FALSE caso contrario.

	Comments:
		-

***/
BOOL
LBSC_Base::IndexSystemOk()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( plbscisIndexSystem ? TRUE : FALSE );
}



/***
	PUBLIC
	Metodo GetFieldId
	Obtem o identificador de um campo atraves de seu aliasname

	Parameters:
		- szFielName - aliasname do campo

	Return:
		- identificador do campo em caso de sucesso ou um valor negativo
		  para indicar erro

	Comments:
		- em caso de erro, consulte LastError()

***/
int
LBSC_Base::GetFieldId( const char *szFieldName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldId") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szFieldName ){
		ERETURN( LBSE_BADARG );
	}
	LBSC_Field	*pf = (*this)[ (char*) szFieldName ];
	if( pf ){
		return( pf->GetId() );
	}
	return( LastError() );
}


/***
	PUBLIC
	Metodo ModifyMaxKeySize
	Modifica o tamanho maximo de uma chave no sistema de indices da base

	Parameters:
		- lbscTicket  -> ticket de seguranca
		- iNewKeySize -> novo tamanho da chave

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo so' pode ser chamado se a base estiver em modo
		  de manutencao.
		- Este metodo dispara automaticamente uma reindexacao total
		  da base.

***/
int
LBSC_Base::ModifyMaxKeySize( const LBSC_Ticket *lbscTicket, int iNewKeySize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyMaxKeySize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( iNewKeySize <= 0 ){
		ERETURN( LBSE_BADARG );
	}
	// altera o MaxKeySize do header de LB1
	int iOldKeySize = LB1.tcrHead.iMaxKeySize;
	LB1.tcrHead.iMaxKeySize = iNewKeySize;
	// grava o header de LB1
	if( LB1.LB1_WriteHead() != OK ){
		LB1.tcrHead.iMaxKeySize = iOldKeySize;
		ERETURN( LBSE_ERROR );
	}
	Flush( lbscTicket );
	// agora destroi o sistema de indices atual
	RemoveIndexSystem();
	// agora reindexa a base toda
	int iRet = IndexAll( lbscTicket );
	while( iRet == LBSW_INDEXSTOPED ){
		iRet = IndexAll( lbscTicket, TRUE );
	}
	ERETURN( iRet );
}





/***
	PUBLIC
	Metodo GetBaseInfo
	Obtem um conjunto de informacoes sobre uma base

	Parameters:
		- lbscTicket  -> ticket de seguranca

	Return:
		- ponteiro para uma estrutura TBaseInfo ou NULL em caso de erro

	Comments:
		- A estrutura retornada por este metodo DEVE ser deletada pela aplicacao.

***/
TBaseInfo *
LBSC_Base::GetBaseInfo( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetBaseInfo") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	// obter os usuarios que estao acessando a base
	int		iNumInst = 0;		// numero de instancias da mesma base
	char	*szUsers = NULL;	// string que contera' os nomes dos usuarios

	// a variavel abaixo indica se estamos trabalhando em uma copia rede.
	BOOL	bNetLBS = (::GetTypeInt() == PE_REDE) ? TRUE : FALSE;

	if( bNetLBS ){
		// estamos em uma copia REDE. Portando, o procedimento
		// para verificar os usuarios que estao acessando uma determinada
		// base eh um pouco diferente do normal.

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
			// nao consegui abrir o arquivo de licencas
			NRETURN( LBSE_BUSY );
		}
		if( cInfoFile.R_FileSize() <= 0 ){
			// o arquivo acabou de ser criado.
			szUsers = Strdup( plbscsOwnerSession->plbscuUser->GetUserName() );
			iNumInst = 1;
		} else {
			// fazer loop procurando todos os registros que tenham uma
			// base com o nome desta que esta' aberta.
			int	iNumElem = cInfoFile.R_FileSize();
			cInfoFile.R_Seek( 0 );
			for( int i = 0; i < iNumElem; i++ ){
				TBaseNetInfo	tbInfo;

				cInfoFile.R_Read( &tbInfo );
				if( stricmp( (char*) tbInfo.strBaseName, szBaseName ) == 0 &&
					!tbInfo.bDeleted ){
					// achamos um elemento cujo nome de base eh igual
					// aa base que estamos tratando
					iNumInst++;
					szUsers = (char*) LBS_Realloc( (void*) szUsers, (USERNAMESIZE+2) * (iNumInst-1), (USERNAMESIZE+2) * iNumInst );
					if( !szUsers ){
						// deu pau
						NRETURN( LBSE_NOMEMORY );
					}
					strcat( szUsers, (char*) tbInfo.strUserLogged );
					strcat( szUsers, " " );
				}
				cInfoFile.R_SeekNext();
			}
			if( !szUsers ){
				// alguma coisa saiu errada. vamos colocar pelo menos
				// o nome do usuario corrente.
				szUsers = Strdup( plbscsOwnerSession->plbscuUser->GetUserName() );
				iNumInst = 1;
			}
			// no final do escopo, o arquivo sera' fechado.
		}
	} else {
		// travar a lista de sessoes para evitar inconsistencias na navegacao
		C_SessCritSect	cCS3( plbscsOwnerSession, CRITSECT3 );
//		plbscsOwnerSession->LockSessList();
		LBSC_Session	*pCurrSess = plbscsOwnerSession->GetFirstSession();

		// varrer todas as sessoes do servidor
		while( pCurrSess ){
			// para cada sessao, verificar as bases abertas
			pCurrSess->lbscblBaseList.First();
			while( pCurrSess->lbscblBaseList.Find( this, CMPBASENAME, FALSE ) != NULL ){
				iNumInst++;
				szUsers = (char*) LBS_Realloc( (void*) szUsers, (USERNAMESIZE+2) * (iNumInst-1), (USERNAMESIZE+2) * iNumInst );
				if( !szUsers ){
					// deu pau
//					plbscsOwnerSession->ReleaseSessList();
					NRETURN( LBSE_NOMEMORY );
				}
				// pegar o nome do usuario que esta' logado na sessao dona da base encontrada
				LBSC_Base		*pBase = pCurrSess->lbscblBaseList.Current();
				LBSC_Session	*pSession = NULL;
				LBSC_User		*pUser = NULL;
				if( pBase ){
					pSession = pBase->plbscsOwnerSession;
					if( pSession ){
						pUser = pSession->plbscuUser;
					}
				}
				if( !pUser ){
					// erro doidao
					if( szUsers ){
						delete szUsers;
					}
//					plbscsOwnerSession->ReleaseSessList();
					NRETURN( LBSE_ERROR );
				}
				strcat( szUsers, pUser->GetUserName() );
				strcat( szUsers, " " );
				if( pCurrSess->lbscblBaseList.Next() == NULL ){
					// acabou a lista
					break;
				}
			}
			pCurrSess = plbscsOwnerSession->GetNextSession();
		}
		// destravar a lista de sessoes
//		plbscsOwnerSession->ReleaseSessList();
	}
	if( iNumInst == 0 ){
		// da~! como eh que nao tem nenhum usuario acessando esta base e estamos
		// rodando este codigo. deveria haver pelo menos um usuario!
		NRETURN( LBSE_ERROR );
	}
	// retira um eventual espaco que possa ter ficado no final da string
	if( szUsers[ strlen( szUsers )-1 ] == ' ' ){
		szUsers[ strlen( szUsers )-1 ] = '\0';
	}
	// agora temos que obter o nome do servidor desta base (this).
	// podemos usar o metodo WhatServers da sessao que eh dona desta base.
	// lembre-se que no WhatServers, cada servidor responde por si so'. Entao,
	// se ja' estamos no servidor, o metodo eh ideal para o que queremos.

	LB1.R_ReadHead();
	char	*szServerName = plbscsOwnerSession->WhatServers();
	char	*szUDB = LB1.tcrHead.bBaseType == USER_BASE ? szBaseName : (char*) LB1.tcrHead.szUserBase;
	TBaseInfo	*pInfo = new TBaseInfo( szUDB, 
						(char*) LB1.tcrHead.szOwnerName, 
						(char*) LB1.tcrHead.szLastModifyUserName,
						szUsers,
						szServerName ? szServerName : "",
						iNumInst,
		  				LB1.tcrHead.ulCreateDate, 
		  				LB1.tcrHead.ulLastModifyDate,
		  				LB1.tcrHead.bBaseType, 
		  				LB1.tcrHead.iSlotNum, 
		  				LB1.tcrHead.iCountNum, 
		  				LB1.tcrHead.iMaxKeySize, 
		  				LB1.tcrHead.iIntPart, 
		  				LB1.tcrHead.iDecPart, 
		  				LB1.tcrHead.bIsEncrypt, 
		  				LB1.tcrHead.bReExport );
	if( szUsers ){
		delete szUsers;
	}
	if( szServerName ){
		delete szServerName;
	}
	if( !pInfo ){
		NRETURN( LBSE_NOMEMORY );
	}
	SetError( LBS_OK );
	return( pInfo );
}


/***
	Metodo ClearBase
	Limpa todos os registros da base

	Parameters:
		- pTicket	-> ticket de seguranca

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- Este metodo elimina fisicamente todos os registros. Eh diferente
		  de usar o DeleteRecord para todos os registros ou o DeleteOcList
		  para a lista fisica.
		- A base deve estar aberta em modo exclusivo.

***/
int
LBSC_Base::ClearBase( const LBSC_Ticket *pTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearBase") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	// Verifica a validade do ticket de seguranca
	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	// verifica se a base esta' em modo exclusivo
	if( !bIsExclusive ){
		ERETURN( LBSE_BASENOTEXCLUSIVE );
	}

	// chama o metodo de reprocessamento de base (metodo de LBSC_Session), 
	// sem copiar os registros, como eh feito pelo ReorganizeBase.
	int iRet = plbscsOwnerSession->ReprocBase( pTicket, this, FALSE );

	// retorna o resultado do ReprocBase
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo GetOwnerSession
	Retorna o ponteiro para o objeto LBSC_Session que eh
	dono desta base
***/
LBSC_Session *
LBSC_Base::GetOwnerSession()
{
	SetError( LBS_OK );
	return( plbscsOwnerSession );
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
LBSC_Base::CancelOperation()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CancelOperation") );

	LBSC_OpInfo::CancelOperation();
	if ( plbscisIndexSystem ) {
		plbscisIndexSystem->CancelOperation();
	}
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
LBSC_Base::GetOpInfo( char *szActionPar, float *pfPercentPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetOpInfo") );

	LBSC_OpInfo::GetOpInfo( szActionPar, pfPercentPar );
}

