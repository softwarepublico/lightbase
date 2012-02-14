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
// Module: OCBASE.CPP
// Description:
//
//	LBSC_BASE public class methods file.
//	This file implements some methods for "Occurrence" handle.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 14/06/95
//


#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif

#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#include	<lt.h>		// $$$ GREEN
#if !defined(__STAT_H) && !defined _INC_STAT
#include	<sys\stat.h>
#endif
#include	<baseinstance.h>
#ifndef	_OLSORT_H_
#include	<olsort.h>
#endif
#include	<strdup.h>

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

// tamanho maximo das informacoes de restricao de campo;
// ver metodo GetAclRestrictExpr
// "GROUPxxxxx = dddddddd ORxx "

#define MAX_RESTR_FIELDINFO		256

/***
	PUBLIC
	Metodo Locate
        Localiza uma chave qualquer dentro de um indice especificado e
        se posiciona sobre o registro que possui a chave encontrada

	Parameters:
		- lbscTicket : o ticket de seguranca
		- uiFieldId : o identificador do campo
		- iIndex : o indice ao qual o campo esta ligado
		- szKey : chave a ser pesquisada
                - iType  : o tipo de busca que deve ser feito na chave.
                           pode ser: EQUAL_KEY, GREATER_KEY, LESS_KEY,
                           GREATEQUAL_KEY, LESSEQUAL_KEY
                           (apenas uma dessas macros).

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo so' pode ser usado se a LO corrente for
                  a LO fisica

***/
int
LBSC_Base::Locate( const LBSC_Ticket *lbscTicket, UINT uiFieldId, int iIndex, char *szKey, int iType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Locate") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( pcOLList->GetCurrentIndex() != 0 ){
		// $$$ A LO Corrente nao eh a fisica
		ERETURN( LBSE_INVALIDOCLIST );
	}
	if( iIndex & 0x00008000 ){
		// indice de ENTIRETREE antigo. vamos converter para
		// o bit novo
		iIndex &= (~0x00008000);
		iIndex |= ENTIRETREE;
	}
	// apenas 1 indice deve ser indicado
	switch( iIndex ){
	case WORDTREE:
	case BACKTREE:
	case VALUETREE:
	case DATETREE:
	case TIMETREE:
	case SOUNDTREE:
	case UNIQUETREE:
	case ENTIRETREE:
		break;

	default:
		ERETURN( LBSE_INVALIDINDEXTYPE );
	}
	// guardar alguns valores em variaveis temporarias
	char	*szTmp = szNavigationKey;
	int		iTypeTmp = iSearchType;
	int		iTmpIndex = iNavigationIndex;
	UINT	uiTmpId = uiNavigationField;

	iSearchType = iType;
	iNavigationIndex = iIndex;
	uiNavigationField = uiFieldId;
	szNavigationKey = Strdup( szKey );
	PreStandardize( szNavigationKey, szStdArray ? szStdArray : DEFAULTSTANDARDIZERARRAY );

	// vamos tentar o posicionamento sobre a chave especificada
	SetError( LBS_OK );
	int iRet = GetKey( DEFINEDKEY );

	// se deu pau, retornar
	if( iRet != LBS_OK && iSearchType != ASTERISK_KEY ){
		// reestabelecer os valores originais das variaveis
		iSearchType = iTypeTmp;
		iNavigationIndex = iTmpIndex;
		uiNavigationField = uiTmpId;
		if( szNavigationKey ){
			delete szNavigationKey;
		}
		szNavigationKey = szTmp;
		return( iRet );
	}

	// posicionar-se sobre o primeiro registro que possua a chave
	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	pOcListOfCurrKey = GetListOfCurrentKey();
	long lNewPos = -1;
	iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, FIRSTOC );
	int iKeySize = strlen(szNavigationKey);

	while ( iRet != LBS_OK && iSearchType == ASTERISK_KEY && iKeySize > 0 ) {
		if( pOcListOfCurrKey ){
			delete pOcListOfCurrKey;
			pOcListOfCurrKey = NULL;
		}

		szNavigationKey[iKeySize-1] = '\0';

		SetError( LBS_OK );
		iRet = GetKey( DEFINEDKEY );
		if ( iRet == LBS_OK ) {

			pOcListOfCurrKey = GetListOfCurrentKey();

			iRet = GetRecPosByKey( CURRKEY, &lNewPos, LASTOC );
			if( iRet != LBS_OK ){
				iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, NEXTOC );
			}
		}

		iKeySize = strlen(szNavigationKey);
	}

	if( iRet != LBS_OK ){
		if( pOcListOfCurrKey ){
			delete pOcListOfCurrKey;
			pOcListOfCurrKey = NULL;
		}
		// reestabelecer os valores originais das variaveis
		iSearchType = iTypeTmp;
		iNavigationIndex = iTmpIndex;
		uiNavigationField = uiTmpId;
		if( szNavigationKey ){
			delete szNavigationKey;
		}
		szNavigationKey = szTmp;
		if ( iType == ASTERISK_KEY ) {
			FirstRecord( lbscTicket );
		}
		ERETURN( LBSE_EMPTYINDEX );
	}

	do{
		iRet = GotoRec( lbscTicket, lNewPos );
		if( iRet == LBSE_EXCLUDEDREC || iRet == LBSE_NOPERMISSION ){
			// vamos procurar outro registro
			iRet = GetRecPosByKey( DEFINEDKEY, &lNewPos, NEXTOC );
		} else {
			break;
		}
	} while( TRUE );

	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	// reestabelecer os valores originais das variaveis
	iSearchType = iTypeTmp;
	iNavigationIndex = iTmpIndex;
	uiNavigationField = uiTmpId;
	if( szNavigationKey ){
		delete szNavigationKey;
	}
	szNavigationKey = szTmp;
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo SetNavigationByIndex
        Seta uma maneira de navegar nos registros por uma sequencia indexada.


	Parameters:
		- lbscTicket : o ticket de seguranca
		- bNavState : o status da navegacao
		- uiFieldId : o identificador do campo
		- iIndex : o indice ao qual o campo esta ligado
                - iType  : o tipo de busca que deve ser feito na chave.
                           pode ser: EQUAL_KEY, GREATER_KEY, LESS_KEY,
                           GREATEQUAL_KEY, LESSEQUAL_KEY
                           (apenas uma dessas macros).

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo so' pode ser usado se a LO corrente for
                  a LO fisica

***/
int
LBSC_Base::SetNavigationByIndex( const LBSC_Ticket *lbscTicket, BOOL bNavState, UINT uiFieldId, int iIndex, int iType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetNavigationByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( pcOLList->GetCurrentIndex() != 0 ){
		// $$$ A LO Corrente nao eh a fisica
		ERETURN( LBSE_INVALIDOCLIST );
	}
	if( iNavigationState == NAVIGATIONBYKEY ){
		// Ja' estamos utilizando a navegacao por keys.
		// A aplicacao deve desativar essa navegacao antes
		// de chamar este metodo.
		ERETURN( LBSE_USINGNAVKEY );
	}
	if( iIndex & 0x00008000 ){
		// indice de ENTIRETREE antigo. vamos converter para
		// o bit novo
		iIndex &= (~0x00008000);
		iIndex |= ENTIRETREE;
	}
	// apenas 1 indice deve ser indicado
	switch( iIndex ){
	case WORDTREE:
	case BACKTREE:
	case VALUETREE:
	case DATETREE:
	case TIMETREE:
	case SOUNDTREE:
	case UNIQUETREE:
	case ENTIRETREE:
		break;

	default:
		if( bNavState ){
			iNavigationState = 0;
			ERETURN( LBSE_INVALIDINDEXTYPE );
                }
	}
	iNavigationState = bNavState ? NAVIGATIONBYINDEX : 0;
	iNavigationIndex = iIndex;
	iSearchType = iType;
	if( szStdArray ){
		delete szStdArray;
		szStdArray = NULL;
	}
	if( iNavigationState ){
		szStdArray = GetStandardizer();
	}
	uiNavigationField = bNavState ? uiFieldId : 0;
	if( iNavigationState ){
		// vamos ver se ha' pelo menos uma chave no indice especificado
		SetError( LBS_OK );
		int iRet = GetKey( FIRSTKEY );
		if( iRet != LBS_OK ){
			return( iRet );
		}
		return( FirstFRecord( lbscTicket ) );
	}
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo SetNavigationByKey
	Seta uma nova maneira de navegar entre os registros por uma chave.


	Parameters:
		- lbscTicket : o ticket de seguranca
		- bNavState : o status de navegacao
		- uifieldId : o identificador do campo
		- iIndex : o indice ao qual o campo esta ligado
		- szNavKey : a chave pela qual se deve caminhar
                - iType  : o tipo de busca que deve ser feito na chave.
                           pode ser: EQUAL_KEY, GREATER_KEY, LESS_KEY,
                           GREATEQUAL_KEY, LESSEQUAL_KEY
                           (apenas uma dessas macros).


	Return:
		LBS_OK em caso de sucesso.

	Comments:
		- Este metodo so' pode ser usado se a LO corrente for
		  a LO fisica

***/
int
LBSC_Base::SetNavigationByKey( const LBSC_Ticket *lbscTicket, BOOL bNavState, UINT uiFieldId, int iIndex, char *szNavKey, int iType )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetNavigationByKey 7 this %p lbscTicket %p bNavState %d uiFieldId %d iIndex %d szNavKey %s iType %d", this, lbscTicket, bNavState, uiFieldId, iIndex, szNavKey, iType) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( pcOLList->GetCurrentIndex() != 0 ){
		// $$$ A LO Corrente nao eh a fisica
		ERETURN( LBSE_INVALIDOCLIST );
	}
	if( iNavigationState == NAVIGATIONBYINDEX ){
		// Ja' estamos navegando pelo indice. A aplicacao
		// deve desativar o caminhamento pelo indice.
		ERETURN( LBSE_USINGNAVINDEX );
	}

	if( iIndex & 0x00008000 ){
		// indice de ENTIRETREE antigo. vamos converter para
		// o bit novo
		iIndex &= (~0x00008000);
		iIndex |= ENTIRETREE;
	}
	// apenas 1 indice deve ser indicado
	switch( iIndex ){
	case WORDTREE:
	case BACKTREE:
	case VALUETREE:
	case DATETREE:
	case TIMETREE:
	case SOUNDTREE:
	case UNIQUETREE:
	case ENTIRETREE:
		break;

	default:
			if( bNavState ){
				iNavigationState = 0;
				ERETURN( LBSE_INVALIDINDEXTYPE );
			}
	}
	iNavigationState = bNavState ? NAVIGATIONBYKEY : 0;
	if( szNavigationKey ){
		delete szNavigationKey;
		szNavigationKey = NULL;
	}
	iNavigationIndex = iIndex;
	uiNavigationField = bNavState ? uiFieldId : 0;
	iSearchType = iType;
	if( iNavigationState ){
		szNavigationKey = Strdup( szNavKey );
		// vamos ver se ha' pelo menos uma chave no indice especificado
		SetError( LBS_OK );
		int iRet = GetKey( DEFINEDKEY );
		if( iRet != LBS_OK ){
			return( iRet );
		}
		if( pOcListOfCurrKey ){
			delete pOcListOfCurrKey;
		}
		pOcListOfCurrKey = GetListOfCurrentKey();
		return( FirstFRecord( lbscTicket ) );
	}
	if( pOcListOfCurrKey ){
		delete pOcListOfCurrKey;
		pOcListOfCurrKey = NULL;
	}
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo SaveOcList
	Grava uma lista de ocorrencias em disco

	Parameters:
		- lbscTicket -> ticket de acesso
		- iHandle -> handle da LO que deve ser gravada
		- szName -> nome fisico do arquivo a ser gravado
		 (sem extensao e sem path)

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- o nome do arquivo eh composto pelo nome indicado + ".OL"
		- este metodo salva qualquer LO, seja a resultante ou uma
		  intermediaria, incluindo a expressao que a gerou.

***/
int
LBSC_Base::SaveOcList( const LBSC_Ticket *lbscTicket, int iHandle, char *szName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SaveOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Expr	*pExpr;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !szName ){
		ERETURN( LBSE_BADARG );
	}
	if( iHandle < 0 || iHandle >= pcOLList->NumElem() ){
		ERETURN( LBSE_BADARG );
	}

	// guarda o handle de LO corrente
	int	iCurrHandle = pcOLList->GetCurrentIndex();

	// posiciona-se na LO desejada
	if( !((*pcOLList)[ iHandle ]) ){
		// da~
		(*pcOLList)[ iCurrHandle ];
		ERETURN( LBSE_ERROR );
	}

	if( FISIC_OC_LIST ){
		// A LO corrente eh a fisica. Entao vamos gerar um arquivo
		// com 0 bytes.
		ERETURN( LBSE_ERROR );
	} else {
		if( ( pExpr = pcOLList->Current() ) == NULL ){
			// Da~!
			(*pcOLList)[ iCurrHandle ];
			ERETURN( LBSE_NOOCLIST );
		}
		LTC_EXPR LTExpr;
		pExpr->pOccList->CreateFullLTList( LTExpr.LT_GetResultList() );
		if( LTExpr.LT_SaveExpr( szName, plbscisIndexSystem ) != OK ){	// GREEN
			(*pcOLList)[ iCurrHandle ];
			ERETURN( LBSE_ERROR );
		}
		// fazer flush do sistema de indices
		FlushIndexSystem();

	}
	(*pcOLList)[ iCurrHandle ];
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo LoadOcList
	Recupera uma lista de ocorrencias do disco

	Parameters:
		- lbscTicket -> ticket de acesso
		- szName -> nome fisico do arquivo a ser lido
		 (sem extensao e sem path)

	Return:
		- o handle da LO gerada ou um valor negativo em caso de erro.

	Comments:
		- o nome do arquivo eh composto pelo nome indicado + ".OL"
		- este metodo le^ uma LO com a respectiva expressao.
		- o handle 0 (retornado) indica que a LO e' a fisica.
		- a LO lida e' automaticamente habilitada e se torna
		  a corrente.
		- se a LO a ser lida estiver "velha" em relacao ao sistema
		  de indices, ela sera' regerada.
		- se o retorno for LBSE_EMPTYLIST, significa que a LO foi
		  regerada, resultou em uma lista vazia, e o arquivo em disco
		  foi removido. Portanto, remova-a de OL_Names.

***/
int
LBSC_Base::LoadOcList( const LBSC_Ticket *lbscTicket, char *szName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LoadOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Expr	*pExpr;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !szName ){
		ERETURN( LBSE_BADARG );
	}

	pExpr = new LBSC_Expr;
	if( !pExpr ){
		ERETURN( LBSE_NOMEMORY );
	}

	LTC_EXPR LTExpr;

	{
		// Guardar a expressao de restricao da LO
		char *szExpr = NULL;
		if( GetAclRestrictExpr( &szExpr ) != LBS_OK ){
			delete pExpr;
			ERETURN( LBSE_RESTRICT );
		}

		if ( szExpr ) {
			LTExpr.LT_AppendRestriction( szExpr );
			delete szExpr;
		}
	}

	if( LTExpr.LT_LoadExpr( szName, plbscisIndexSystem ) != OK ){	// GREEN
		delete pExpr;
		ERETURN( LBSE_ERROR );
	}

	// Ir para a primeira ocorrencia da lista.
	// (o metodo que carrega a LO do disco (GREEN) deixa a lista na ultima posicao)

	if( LTExpr.LT_GetResultList() ){
		LTExpr.LT_GetResultList()->LT_GetFirstOccurrence();
	}

	// gera a LO no formato registro/lista de ocorrencias (para navegacao corretamente)
	int iRet = CreateLbsOccList( pExpr, &LTExpr );
	if ( iRet != LBS_OK ) {
		delete pExpr;
		ERETURN( iRet );
	}

	pExpr->szExpr = Strdup( LTExpr.LT_GetExpression() );

	// Adicionar a nova LO na lista
	if( pcOLList->Add( pExpr, TAIL ) != OK ){
		delete pExpr;
		ERETURN( LBSE_NOMEMORY );
	}

	// Habilita a LO
	if( EnableOcList( lbscTicket, pcOLList->GetCurrentIndex() ) != LBS_OK ){
		ERETURN( LBSE_ENABLE );
	}

	SetError( LBS_OK );
	// o indice do elemento corrente e' o handle da lista lida.
	return( pcOLList->GetCurrentIndex() );
}


/***
	PUBLIC
	Metodo EnableOcList
	Habilita uma LO atraves de seu handle.


	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle : o handle da LO a ser habilitada

	Return:
		- LBS_OK em caso de sucesso

        Comments:
		- O numero 0 indica a LO fisica.

***/
int
LBSC_Base::EnableOcList( const LBSC_Ticket *lbscTicket, int iHandle )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::EnableOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	int iHandleBack = pcOLList->GetCurrentIndex();
	if( (*pcOLList)[ iHandle ] == NULL ){
		// Indice nao existente na lista
		(*pcOLList)[ iHandleBack ];
		ERETURN( LBSE_INVALIDOCLIST );
	}

	if( iHandle != 0 ){
		// Posicionar-se no registro fisico referente aa
		// posicao corrente da LO que foi habilitada.
		LBSC_OcList	*pOcList = GetCurrentOcList();
		if( !pOcList ){
			return( LastError() );
		}
		if( !pOcList->GetCurrentOccurrence() ){
			ERETURN( LBSE_EMPTYLIST );
		}

		int iRet = FirstRecord( lbscTicket );
		if(  iRet != LBS_OK && iRet != LBSE_LASTRECORD ){
			return( LastError() );
		}
	}
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo UnloadOcList
	Retira (descarrega) uma LO da lista de LO's atraves de seu handle.

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle : o handle da LO a ser descarregada

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- Nao e' possivel descarregar a LO fisica (numero 0) nem a LO
		  que estiver ativa. Este metodo nao deleta a LO do disco;
		  simplesmente a deleta	da lista em memoria.

***/
int
LBSC_Base::UnloadOcList( const LBSC_Ticket *lbscTicket, int iHandle )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UnloadOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( iHandle == 0 ){
		// A LO passada como parametro e' a fisica.
		ERETURN( LBSE_DELFISICOL );
	}
	if( pcOLList->GetCurrentIndex() == iHandle ){
		// A LO passada como parametro e' a corrente.
		ERETURN( LBSE_DELCURROL );
	}
	int iHandleBack = pcOLList->GetCurrentIndex();
	if( (*pcOLList)[ iHandle ] == NULL ){
		// Indice nao existente na lista
		(*pcOLList)[ iHandleBack ];
		ERETURN( LBSE_INVALIDOCLIST );
	}
	pcOLList->DeleteCurrObj();	// deleta somente o objeto, mas deixa o nodo.
	// volta para a ocorrencia que estava ativa
	(*pcOLList)[ iHandleBack ];
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo DeleteOcList
	Deleta fisicamente uma LO atraves de seu nome de arquivo.

	Parameters:
		- lbscTicket : o ticket de seguranca
		- szName -> nome fisico do arquivo a ser gravado
		 (sem extensao e sem path)


	Return:
		- LBS_OK em caso de sucesso


	Comments:
		- Observe que este metodo simplesmente deleta o arquivo que
		  representa a LO, nao fazendo qualquer alteracao na lista
		  de LO's em memoria.

***/

int
LBSC_Base::DeleteOcList( const LBSC_Ticket *lbscTicket, char *szName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DeleteOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DeleteOcRecords
	Deleta da base todos os registros que fazem parte da LO
	correntemente ativa

	Parameters:
		- lbscTicket : o ticket de seguranca

	Return:
		- LBS_OK em caso de sucesso


	Comments:
		- Este metodo deleta da base todos os registros que
		  fazem parte da LO corrente,
		- depois se posiciona LO fisica e
		  faz um UnloadOcList na LO que era a corrente.
		- da proxima vez que a LO em questao for ser lida do disco,
		  ela sera' regerada, pois estara' desatualizada.
		- se a LO corrente for a fisica, todos os registros da base
		  serao deletados

***/
int
LBSC_Base::DeleteOcRecords( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DeleteOcRecords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	// posicionar-se no primeiro registro
	int iRet = FirstRecord( lbscTicket );
	// deletar os registros
	BOOL bAll = TRUE;
	LBSC_OcList	*plbscolOrigOccList = GetCurrentOcList();

	while( iRet == LBS_OK || iRet == LBSE_NOPERMISSION ) {
		if( iRet == LBS_OK ){
			if( LockRecord( lbscTicket ) == LBS_OK ){
				DeleteRecord( lbscTicket );
				if ( plbscolOrigOccList ) {	// nao eh lo fisica
					iRet = ( plbscolOrigOccList->GetCurrentOccurrence() ? LBS_OK : LBSE_NORECORD);
				} else {
					iRet = ( (GetNumActiveRecords( lbscTicket ) > 0) ? LBS_OK : LBSE_NORECORD);
				}
			} else {
				bAll = FALSE;
				iRet = NextRecord( lbscTicket );
			}
		} else {
			bAll = FALSE;
			iRet = NextRecord( lbscTicket );
		}
	}
	// guarda o handle de LO corrente
	int	iCurrHandle = pcOLList->GetCurrentIndex();

	// vai para a LO fisica
	(*pcOLList)[ 0 ];

	// deleta da memoria a LO em questao
	UnloadOcList( lbscTicket, iCurrHandle );
	ERETURN( bAll ? LBS_OK : LBSW_FAILURE );
}


/***
	PUBLIC
***
int
LBSC_Base::GotoFirstOcList( LBSC_Ticket *lbscTicket )
{
	return( GotoNthOcList( lbscTicket, FIRSTEXPR ) );
}

/***
	PUBLIC
***
int
LBSC_Base::GotoNextOcList( LBSC_Ticket *lbscTicket )
{
	return( GotoNthOcList( lbscTicket, NEXTEXPR ) );
}

/***
	PUBLIC
***
int
LBSC_Base::GotoPreviousOcList( LBSC_Ticket *lbscTicket )
{
	return( GotoNthOcList( lbscTicket, PREVIOUSEXPR ) );
}

/***
	PUBLIC
***
int
LBSC_Base::GotoLastOcList( LBSC_Ticket *lbscTicket )
{
	return( GotoNthOcList( lbscTicket, LASTEXPR ) );
}

/***
	PUBLIC
***
inta
LBSC_Base::GotoResultOcList( LBSC_Ticket *lbscTicket )
{
	return( GotoNthOcList( lbscTicket, RESULTEXPR ) );
}

/***
	PUBLIC
	Metodo GetCurrentExpression
	Obtem uma copia da expressao.

	Parameters:
		- lbscTicket : o ticket de seguranca

	Return:
		- a copia da expressao


	Comments:
		- A aplicacao DEVE deleta-la quando nao for usar mais.

***/
char *
LBSC_Base::GetCurrentExpression( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrentExpression") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Expr	*pExpr;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	pExpr = pcOLList->Current();
	if( !pExpr || !pExpr->szExpr ){
		NRETURN( LBSE_NOMEMORY );
	}
	SetError( LBS_OK );
	return( Strdup( pExpr->szExpr ) );
}

/***
	PUBLIC
	Metodo GetOcListExpression
	Obtem uma copia da expressao de uma determinada OL.

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle : o handle da LO a ser descarregada

	Return:
		- a copia da expressao

	 
	Comments:
		- A aplicacao DEVE deleta-la quando nao for usar mais.

***/
char *
LBSC_Base::GetOcListExpression( const LBSC_Ticket *lbscTicket, int iHandle )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetOcListExpression") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( iHandle == 0 ){
		// A LO passada como parametro e' a fisica.
		NRETURN( LBSE_INVALIDOCLIST );
	}
	int iHandleBack = pcOLList->GetCurrentIndex();
	if( (*pcOLList)[ iHandle ] == NULL ){
		// Indice nao existente na lista
		(*pcOLList)[ iHandleBack ];
		NRETURN( LBSE_INVALIDOCLIST );
	}
	char	*szExpr = GetCurrentExpression( lbscTicket );
	// Volta para a posicao que estava na lista
	(*pcOLList)[ iHandleBack ];
	return( szExpr );
}

/***
	PUBLIC
	Metodo GetOLRecNumber
	Obtem o numero do registro corrente da LO.

	Parameters:
		- lbscTicket : o ticket de seguranca


	Return:
		- o numero de registro pesquisado


	Comments:
        	-

***/
long
LBSC_Base::GetOLRecNumber( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetOLRecNumber") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	long	lNumRec = 0;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( FISIC_OC_LIST ){
		// a LO corrente eh a fisica
		return( CurrRecNum( lbscTicket ) );
	}

	LBSC_OcList	*pOcList = GetCurrentOcList();
	if( !pOcList ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( pOcList->CurPos() >= 0 ){
		SetError( LBS_OK );
		return pOcList->CurPos();
	}
	ERETURN( LBSE_ERROR );
}


/***
	PUBLIC
	Metodo SortOcList
	Ordena uma lista de ocorrencias

	Parameters:
		- lbscTicket	-> ticket de acesso
		- iHandle	-> handle da LO que deve ser ordenada
		- szExpr	-> expressao para formacao da chave de ordenacao.
		- bCopy		-> indica se a ordenacao devera' gerar uma copia da
				   LO original (TRUE) ou nao (FALSE, default)

	Return:
		- se nao for solicitada uma copia da LO, o retorno eh
		  LBS_OK em caso de sucesso ou um erro; se o resultado da ordenacao
		  for uma copia da LO, o retorno eh o handle da LO gerada ou um valor
		  negativo, indicando erro.

	Comments:
		- este metodo ordena qualquer LO, seja a fisica ou nao.
		- para ordenar a LO fisica sem gerar uma copia, eh necessario 
		  abrir a base em modo exclusivo.
		- a ordenacao da LO fisica sem gerar copia deixa o sistema de indices 
		  da base "doidao" (o LBS o invalida apos a ordenacao). Eh (fortemente) 
		  aconselhavel reindexar a base toda apos a ordenacao.

***/
int
LBSC_Base::SortOcList( const LBSC_Ticket *lbscTicket, int iHandle, char *szExpr, BOOL bCopy )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SortOcList") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( iHandle < 0 || iHandle >= pcOLList->NumElem() ){
		ERETURN( LBSE_BADARG );
	}

	if( iHandle == 0 && !bCopy ){
		// LO fisica sem pedido de geracao de copia. 
		// devemos verificar se a base esta' aberta em modo
		// exclusivo.
		if( !bIsExclusive ){
			// a base nao esta' aberta em modo exclusivo
			ERETURN( LBSE_BASENOTEXCLUSIVE );
		}
	}
	if( iHandle == 0 && bIsReadOnly ){
		// LO fisica com base read-only? Nananinanao!!
		ERETURN( LBSE_BASEREADONLY );
	}

	if( iNavigationState ){
		// vamos desabilitar qualquer navegacao
		// que esteja setada (por indice ou por chave)
		switch( iNavigationState ){
		case NAVIGATIONBYKEY:
			SetNavigationByKey( lbscTicket, FALSE );
			break;

		case NAVIGATIONBYINDEX:
			SetNavigationByIndex( lbscTicket, FALSE );
			break;

		}
	}

	int	iRet = LBS_OK;
	// guarda o handle de LO corrente
	int	iCurrHandle = pcOLList->GetCurrentIndex();

	// posiciona-se na LO desejada
	if( ! ((*pcOLList)[ iHandle ]) ){
		// da~
		(*pcOLList)[ iCurrHandle ];
		ERETURN( LBSE_ERROR );
	}

	LBSC_OcList *pOcList = GetCurrentOcList();

	if( LastError() != LBS_OK ){
		// deu pau
		(*pcOLList)[ iCurrHandle ];
		ERETURN( LastError() );
	}

	// instancia um objeto LBSC_OLSort
	LBSC_OLSort	sOLSort( szExpr, pOcList, this, lbscTicket, bSecureSort, bCopy );

	if( sOLSort.LastError() != LBS_OK ){
		// deu pau no construtor do objeto Sort
		(*pcOLList)[ iCurrHandle ];
		ERETURN( sOLSort.LastError() );
	}


	LBSC_OcList *pSortList = NULL;
	// agora vamos fazer a ordenacao.
	pSortList = sOLSort.StartSort();

	// vamos 

	// voltar para a LO que estava ativa no inicio deste metodo
	(*pcOLList)[ iCurrHandle ];

	if( !pSortList ){
		// deu pau na ordenacao.
		ERETURN( LBSE_SORTERROR );
	}
	if( bCopy ){
		// nao importa se a LO ordenada foi a fisica ou nao, pois
		// a LO resultante foi uma copia da original.
		// vamos adicionar a nova LO ao LBS e criar um Id para ela.
		// a partir de entao, essa LO eh uma LO qualquer, que pode ser
		// habilitada, gravada, etc.

		// cria uma LO vazia, com expressao igual aa expressao de
		// ordenacao que foi passada para este metodo.
		if( !plbscisIndexSystem ){
			ERETURN( LBSE_INVALIDINDEXSYSTEM );
		}

		LBSC_Expr *pExpr = new LBSC_Expr;
		LBSC_Expr *pOrigExpr = pcOLList->Current();

		if( !pExpr || !pOrigExpr ){
			ERETURN( LBSE_NOMEMORY );
		}

		pExpr->szExpr = pOrigExpr->szExpr ? Strdup( pOrigExpr->szExpr ) : NULL ;
		pExpr->pOccList = pSortList;

		// guarda o handle da LO corrente
		int	iCurrHandle = pcOLList->GetCurrentIndex();

		// adiciona a LO na lista de LO's e automaticamente
		// cria um handle para ela.
		pcOLList->Add( pExpr, TAIL );
		pcOLList->Last();

		// nao eh necessario filtrar a LO, pois so' existem ocorrencias
		// validas (as ocorrencias foram geradas a partir de registros
		// fisicos que foram acessados pelo usuario, o que significa que
		// ele podera' ve-las)

		// retornar o handle da LO resultante da ordenacao
		SetError( LBS_OK );
		FirstRecord( lbscTicket );
		return( pcOLList->GetCurrentIndex() );

	} else {

		if( pSortList != (LBSC_OcList *) FISIC_OL_OK ){
			// A ordenacao nao foi na LO fisica. 
			// Entao devemos substituir a LO antiga por pSortList, que
			// eh a LO ja' ordenada.
			iRet = ChangeOcList( pSortList );
		} else {
			// A ordenacao foi na LO fisica. Vamos detonar o sistema
			// de indices para que a aplicacao nao tente acessa-lo
			// antes de gera-lo novamente.
			if( plbscisIndexSystem ){
				// invalida os indices na cache
				if ( pBaseInstance ) {
					pBaseInstance->InvalidateIndexes();
				}
				plbscisIndexSystem->LT_ClearIndexSystem();
				if ( pBaseInstance ) {
					pBaseInstance->Indexes = plbscisIndexSystem->LT_GetIndexes();
				}
			}
		}
	}
	FirstRecord( lbscTicket );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo EnableSecureSort
	Habilita/desabilita o modo de seguranca na ordenacao da LO fisica.
	Quando o modo de seguranca esta' habilitado, o algoritmo de ordenacao
	da LO fisica gera informacoes uteis para recuperacao de algum registro que
	tenha se perdido em uma queda do sistema durante a ordenacao; a ordenacao
	fica mais lenta.

	Parameters:
		- bStatus	-> novo status de seguranca da ordenacao

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- 

***/
int
LBSC_Base::EnableSecureSort( BOOL bStatus )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::EnableSecureSort") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	bSecureSort = bStatus;
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo SecureSortStatus
	Retorna o status de seguranca da ordenacao da LO fisica.

	Parameters:
		- 

	Return:
		- TRUE ou FALSE

	Comments:
		- 

***/
BOOL
LBSC_Base::SecureSortStatus()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SecureSortStatus") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( bSecureSort );
}


/***
	PUBLIC
	Metodo GetNumOLRecords
	Obtem o numero de registros da LO corrente
	(nao eh o numero de ocorrencias)

	Parameters:
		- lbscTicket.
		- iHandle	-> handle da LO

	Return:
		- O numero de registros ou um valor negativo indicando erro.

	Comments:
		-

***/
long
LBSC_Base::GetNumOLRecords( const LBSC_Ticket *lbscTicket, int iHandle )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumOLRecords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( iHandle < -1 || iHandle >= pcOLList->NumElem() ){
		ERETURN( LBSE_BADARG );
	}

	// guarda o handle de LO corrente
	int	iCurrHandle = pcOLList->GetCurrentIndex();

	if( iHandle > -1 ){
		// posiciona-se na LO desejada
		if( ! ((*pcOLList)[ iHandle ]) ){
			// da~
			(*pcOLList)[ iCurrHandle ];
			ERETURN( LBSE_ERROR );
		}
	} else {
		iHandle = iCurrHandle;
	}

	if( FISIC_OC_LIST ){
		// a LO corrente eh a fisica
		long lRet = GetNumActiveRecords( lbscTicket );
		(*pcOLList)[ iCurrHandle ];
		return( lRet );
	}
	// vamos retornar o numero de registros da LO ativa
	LBSC_Expr	*pExpr = pcOLList->Current();
	if( !pExpr || !pExpr->pOccList ){
		(*pcOLList)[ iCurrHandle ];
		ERETURN( LBSE_NOMEMORY );
	}
	// volta para a LO que estava antes
	(*pcOLList)[ iCurrHandle ];

	SetError( LBS_OK );
	return( pExpr->pOccList->Size() );
}


/************************************************************************/
/*************			PRIVATE			*****************/
/************************************************************************/


/***
	PRIVATE
	ChangeOcList
	Troca a LO corrente por uma nova e deleta a corrente
	(tudo em memoria)
***/
int
LBSC_Base::ChangeOcList( LBSC_OcList *pNewList )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ChangeOcList") );

	if( !pNewList ){
		ERETURN( LBSE_BADARG );
	}

	// testar se a nova LO possui pelo menos um elemento
	LTC_OCCURRENCE	*pOc = pNewList->GetFirstOccurrence();
	if( !pOc ){
		ERETURN( LBSE_BADARG );
	}

	if( FISIC_OC_LIST ){
		// Lista fisica: retornar NULL, sem erro.
		ERETURN( LBS_OK );
	}

	// pegar a LO corrente
	LBSC_Expr	*pExpr = pcOLList->Current();
	if( !pExpr ){
		NRETURN( LBSE_NOMEMORY );
	}
	LBSC_OcList *pOcList = pExpr->pOccList;
	if( !pOcList ){
		NRETURN( LBSE_NOMEMORY );
	}

	// deletar a LO original
	delete pOcList;

	// mudar para a nova
	pExpr->pOccList = pNewList;

	ERETURN( LBS_OK );
}

/***
	PRIVATE
***/
LBSC_OcList *
LBSC_Base::GetCurrentOcList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrentOcList") );

	LBSC_Expr	*pExpr;

	if( FISIC_OC_LIST ){
		// Lista fisica: retornar NULL, sem erro.
		NRETURN( LBS_OK );
	}

	pExpr = pcOLList->Current();
	if( !pExpr ){
		NRETURN( LBSE_NOMEMORY );
	}
	LBSC_OcList *pOcList = pExpr->pOccList;
	if( !pOcList ){
		NRETURN( LBSE_NOMEMORY );
	}
	SetError( LBS_OK );
	return( pOcList );
}



/***
	PRIVATE
***
int
LBSC_Base::GotoNthOcList( LBSC_Ticket *lbscTicket, int iPos )
{
	LBSC_ExprList	*pExprList;
	LTC_EXPR	*pExpr;

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	if( FISIC_OC_LIST ){
		ERETURN( LBSE_INFISICOCLIST );
	}

	pExprList = pcOLList->Current();
	if( !pExprList ){
		ERETURN( LBSE_NOMEMORY );
	}

	switch( iPos ){
	case FIRSTEXPR:
		pExpr = pExprList->LT_GetFirstExpr();
		break;

	case NEXTEXPR:
		pExpr = pExprList->LT_GetNextExpr();
		break;

	case LASTEXPR:
		pExpr = pExprList->LT_GetLastExpr();
		break;

	case PREVIOUSEXPR:
		pExpr = pExprList->LT_GetPreviousExpr();
		break;

	case RESULTEXPR:
		pExpr = pExprList->LT_GetResultExpr();
		break;

	default:
		// programacao defensiva
		ERETURN( LBSE_BADARG );
	}
	if( !pExpr ){
		ERETURN( LBSE_NOMEMORY );
	}
	ERETURN( LBS_OK );
}

/***
	PRIVATE
***/
int
LBSC_Base::GetAclRestrictExpr( char **pszExpr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetAclRestrictExpr") );

	UINT		uiId;
	int			iPerm;

	if ( !pszExpr )  {
		ERETURN( LBSE_BADARG );
	}

	// $$$ O codigo abaixo eh responsavel pela restricao da lista de ocor-
	// $$$ rencias a partir das ACLs. As restricoes feitas aqui sao
	// $$$ somente a nivel de campo. As possiveis restricoes a nivel
	// $$$ de registro somente serao feitas no momento da leitura de
	// $$$ cada registro, ja que nao podemos sair testando todos os
	// $$$ registros da LO para verificar permissoes (questao de per-
	// $$$ formance)

	char	*pszSymbol = GLT_Session->LT_GetSymbol( "GROUP" );
	char	*pszSymbolOp = GLT_Session->LT_GetSymbol( "OR" );

	int iNumFields = lbscrCurrRecord.GetNumberOfFields();
	if ( !iNumFields ) {
		ERETURN( LBS_OK );
	}

	int		iExprCurSize = iNumFields * MAX_RESTR_FIELDINFO;
	char	*szExpr = new char[ iExprCurSize ];

	if ( !szExpr ) {
		ERETURN( LBSE_NOMEMORY );
	}

	szExpr[ 0 ] = '\0';

	BOOL	bMustRestrict = FALSE;
	int		iExprSize = 0;
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field *pField = lbscrCurrRecord[ i ];

		if ( pField ) {
			uiId = pField->GetId();
		} else {
			uiId = 0;
		}
		iPerm = bIsBasePasswdCorrect ? ACL_ADM : GetACLPerm( (char*) plbscsOwnerSession->GetUserName(), (long) uiId, NULL, USERFIELD );
		if( (iPerm > 0) && (iPerm & ACL_READ) ){
			char	szAux[ MAX_RESTR_FIELDINFO ];

			sprintf( szAux, " %s = %d ", pszSymbol, (int) uiId );
			iExprSize += strlen( szAux ) + strlen(pszSymbolOp);
			if( iExprSize >= iExprCurSize ){
				szExpr = (char*) LBS_Realloc( szExpr, iExprCurSize, iExprSize );
				if( !szExpr ){
					// deu merda
					ERETURN( LBSE_NOMEMORY );
				}
				iExprCurSize = (2*iExprCurSize) + iExprSize;
			}
			if ( szExpr[0] == '\0' ) {	// primeira vez
				strcpy( szExpr, szAux );
			}
			else {
				strcat( szExpr, pszSymbolOp );
				strcat( szExpr, szAux );
			}
		}
		else {
			bMustRestrict = TRUE;
		}
	}

	if( bMustRestrict && szExpr[ 0 ] ){
		*pszExpr = szExpr;
	}
	else {
		delete szExpr;
		*pszExpr = NULL;
	}

	ERETURN( LBS_OK );
}


/***
	PRIVATE
***/
int
LBSC_Base::GetKey( int iPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetKey") );

	int		iRet;
	if( LastError() != LBS_OK ){
		// Campo nao existe ou o usuario nao tem
		// permissao para acessa-lo
		return( LastError() );
	}
	char *szBuffer = new char [ DEFAULT_MAXKEYSIZE + 1 ];
	if( !szBuffer ){
		ERETURN( LBSE_NOMEMORY );
	}
	memset( szBuffer, 0, DEFAULT_MAXKEYSIZE + 1 );
	if( iPos == DEFINEDKEY ){
		if( !szNavigationKey || ( szNavigationKey[ 0 ] == '\0' ) ){
			// DEFINEDKEY nao deve ser usado quando szNavigationKey
			// estiver vazio
			delete szBuffer;
			ERETURN( LBSE_BADARG );
		}
	}
	LBSC_IndexSystem	*pIndexSystem;
	if( !plbscisIndexSystem ){
		// O sistema de indices nao esta' aberto
		delete szBuffer;
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	pIndexSystem = plbscisIndexSystem;

	switch( iPos ){
	case FIRSTKEY:
		if( !szNavigationKey || ( szNavigationKey[ 0 ] == '\0' ) ){
			// vai para o inicio do indice como um todo
			iRet = pIndexSystem->LT_GetFirstKey( iNavigationIndex, (char*) szBuffer );
		} else {
			// vai para o inicio do indice so da chave especificada
			iRet = pIndexSystem->LT_GetFirstKey( iNavigationIndex, (char*) szBuffer, TRUE );
		}
		break;

	case LASTKEY:
		iRet = pIndexSystem->LT_GetLastKey( iNavigationIndex, (char*) szBuffer );
		break;

	case NEXTKEY:
		iRet = pIndexSystem->LT_GetNextKey( iNavigationIndex, (char*) szBuffer );
		break;

	case PREVIOUSKEY:
		iRet = pIndexSystem->LT_GetPreviousKey( iNavigationIndex, (char*) szBuffer );
		break;

	case DEFINEDKEY:
		{
			char	*szAux = new char [ DEFAULT_MAXKEYSIZE + 1 ];
			if( !szAux ){
				delete szBuffer;
				ERETURN( LBSE_NOMEMORY );
			}
			// nao posso usar szNavigationKey por causa do tamanho.
			// A GREEN exige que as string usadas nesse metodo tenham
			// iMaxKeySize+1 caracteres e que todos os caracteres
			// nao usados estejam zerados.
			memset( szAux, 0, DEFAULT_MAXKEYSIZE + 1 );
			strncpy( szAux, szNavigationKey, DEFAULT_MAXKEYSIZE );
			// normalizar szAux
			PreStandardize( szAux, szStdArray ? szStdArray : DEFAULTSTANDARDIZERARRAY );
			iRet = pIndexSystem->LT_GetKey( iNavigationIndex, (char*) szAux, (char*) szBuffer, iSearchType );
			delete szAux;
		}
		break;

	default:
		// programacao defensiva
		delete szBuffer;
		ERETURN( LBSE_BADARG );
	}

	delete szBuffer;
	if( iRet != LBS_OK ){
		if( iRet == 1 ){
			ERETURN( LBSE_EMPTYINDEX );
		}
		iRet = pIndexSystem->GetError();
		ERETURN( iRet );
	}
	ERETURN( LBS_OK );
}



/***
	PRIVATE
***/
int
LBSC_Base::GetRecPosByKey( int iKey, long *plNewPos, int iPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetRecPosByKey") );

	LTC_OCCURRENCE	*pltcOcAux = NULL;

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if ( iSearchType == ASTERISK_KEY ) {
		if( !pOcListOfCurrKey ){
			// Da~!!
			ERETURN( LBSE_ERROR );
		}
		pltcOcAux = GetOc( pOcListOfCurrKey, iPos );
		if( iKey == CURRKEY ){
			if( pltcOcAux ){
				(*plNewPos) = pltcOcAux->LT_GetSet();
				ERETURN( LBS_OK );
			}
			if ( iPos == FIRSTOC || iPos == PREVIOUSOC ) {
				ERETURN( LBSE_FIRSTOCCURRENCE );
			} 
			ERETURN( LBSE_LASTOCCURRENCE );
		}

		while( !pltcOcAux ) {
			SetError( LBS_OK );
			int iRet = LBS_OK;
			switch( iPos ) {
			case FIRSTOC:
			case NEXTOC:
				iRet = GetKey( NEXTKEY );
				break;
			case PREVIOUSOC:
			case LASTOC:
				iRet = GetKey( PREVIOUSKEY );
				break;
			}
			if( iRet != LBS_OK ){
				// nao existe mais chave
				return( iRet );
			}
			delete pOcListOfCurrKey;
			pOcListOfCurrKey = GetListOfCurrentKey();
			if( !pOcListOfCurrKey ){
				ERETURN( LBSE_ERROR );
			}
			pltcOcAux = GetOc( pOcListOfCurrKey, iPos == LASTOC || iPos == PREVIOUSOC ? LASTOC : FIRSTOC );
		}

		if( !pltcOcAux ){
			ERETURN( LBSE_EMPTYINDEX );
		}

		(*plNewPos) = pltcOcAux->LT_GetSet();
		ERETURN( LBS_OK );
	}

	if( iKey != DEFINEDKEY && iKey != CURRKEY ){
		SetError( LBS_OK );
		int iRet = GetKey( iKey );
		if( iRet != LBS_OK ){
			return( iRet );
		}
		if( pOcListOfCurrKey ){
			delete pOcListOfCurrKey;
		}
		pOcListOfCurrKey = GetListOfCurrentKey();
		if( !pOcListOfCurrKey ){
			ERETURN( LBSE_ERROR );
		}
		switch( iKey ){
		case FIRSTKEY:
		case NEXTKEY:
			pltcOcAux = GetOc( pOcListOfCurrKey, FIRSTOC );
			break;

		case LASTKEY:
		case PREVIOUSKEY:
			pltcOcAux = GetOc( pOcListOfCurrKey, LASTOC );
			break;

		default:
			// programacao defensiva
			ERETURN( LBSE_BADARG );
		}
		while( !pltcOcAux ){
			// vamos tentar mais
			SetError( LBS_OK );
			delete pOcListOfCurrKey;
			pOcListOfCurrKey = NULL;
			switch( iKey ){
			case FIRSTKEY:
			case NEXTKEY:
				SetError( LBS_OK );
				iRet = GetKey( NEXTKEY );
				break;

			case LASTKEY:
			case PREVIOUSKEY:
				SetError( LBS_OK );
				iRet = GetKey( PREVIOUSKEY );
				break;

			default:
				// programacao defensiva
				ERETURN( LBSE_BADARG );
			}
			if( iRet != LBS_OK ){
				return( iRet );
			}
			if( pOcListOfCurrKey ){
				delete pOcListOfCurrKey;
			}
			pOcListOfCurrKey = GetListOfCurrentKey();
			if( !pOcListOfCurrKey ){
				ERETURN( LBSE_ERROR );
			}
			switch( iKey ){
			case FIRSTKEY:
			case NEXTKEY:
				pltcOcAux = GetOc( pOcListOfCurrKey, FIRSTOC );
				break;

			case LASTKEY:
			case PREVIOUSKEY:
				pltcOcAux = GetOc( pOcListOfCurrKey, LASTOC );
				break;

			default:
				// programacao defensiva
				ERETURN( LBSE_BADARG );
			}
		}
	} else {
		if( !pOcListOfCurrKey ){
			// Da~!!
			ERETURN( LBSE_ERROR );
		}
		switch( iPos ){
		case FIRSTOC:
			pltcOcAux = GetOc( pOcListOfCurrKey, FIRSTOC );
			break;

		case NEXTOC:
			if( iKey == CURRKEY ){
				pltcOcAux = GetOc( pOcListOfCurrKey, NEXTOC );
				if( pltcOcAux ){
					(*plNewPos) = pltcOcAux->LT_GetSet();
					ERETURN( LBS_OK );
				}
				ERETURN( LBSE_LASTOCCURRENCE );
			}
			pltcOcAux = GetOc( pOcListOfCurrKey, NEXTOC );
			while( !pltcOcAux && ( iSearchType != EQUAL_KEY ) ){
				// acabou a LO. Vamos pegar outra chave no
				// SI e gerar outra LO
				SetError( LBS_OK );
				int iRet = GetKey( NEXTKEY );
				if( iRet != LBS_OK ){
					// nao existe mais chave
					return( iRet );
				}
				delete pOcListOfCurrKey;
				pOcListOfCurrKey = GetListOfCurrentKey();
				if( !pOcListOfCurrKey ){
					ERETURN( LBSE_ERROR );
				}
				pltcOcAux = GetOc( pOcListOfCurrKey, FIRSTOC );
			}
			break;

		case PREVIOUSOC:
			if( iKey == CURRKEY ){
				pltcOcAux = GetOc( pOcListOfCurrKey, PREVIOUSOC );
				if( pltcOcAux ){
					(*plNewPos) = pltcOcAux->LT_GetSet();
					ERETURN( LBS_OK );
				}
				ERETURN( LBSE_FIRSTOCCURRENCE );
			}
			pltcOcAux = GetOc( pOcListOfCurrKey, PREVIOUSOC );
			while( !pltcOcAux && ( iSearchType != EQUAL_KEY ) ){
				// acabou a LO. Vamos pegar outra chave no
				// SI e gerar outra LO
				SetError( LBS_OK );
				int iRet = GetKey( PREVIOUSKEY );
				if( iRet != LBS_OK ){
					// nao existe mais chave
					return( iRet );
				}
				delete pOcListOfCurrKey;
				pOcListOfCurrKey = GetListOfCurrentKey();
				if( !pOcListOfCurrKey ){
					ERETURN( LBSE_ERROR );
				}
				pltcOcAux = GetOc( pOcListOfCurrKey, LASTOC );
			}
			break;

		case LASTOC:
			pltcOcAux = GetOc( pOcListOfCurrKey, LASTOC );
			break;

		default:
			// programacao defensiva
			ERETURN( LBSE_BADARG );
		}
	}
	if( !pltcOcAux ){
		ERETURN( LBSE_NOMEMORY );
	}
	(*plNewPos) = pltcOcAux->LT_GetSet();
	// nao devemos deletar pltcOcAux
	ERETURN( LBS_OK );
}

/***
	PRIVATE
***/
LTC_OCCURRENCELIST *
LBSC_Base::GetListOfCurrentKey()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetListOfCurrentKey") );

	LTC_OCCURRENCELIST *pOL;
	
	if( !plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	pOL = plbscisIndexSystem->LT_GetListOfCurrentKey( iNavigationIndex );
	SetError( LBS_OK );
	return( pOL );
}



/***
	PRIVATE
	Retorna uma ocorrencia da lista pOL.
	A ocorrencia serah procurada de acordo com iPos.
	Se for determinado um campo especifico atraves do atributo
	uiNavigationField (da classe Base), a ocorrencia retornada
	conterah o atributo 'campo' igual a uiNavigationField.
	Caso contrario, qualquer ocorrencia (de acordo com iPos)
	eh retornada.
***/
LTC_OCCURRENCE	*
LBSC_Base::GetOc( LTC_OCCURRENCELIST *pOL, int iPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetOc") );

	LTC_OCCURRENCE	*pltcOcAux = NULL;

	switch( iPos ){
	case FIRSTOC:
		pltcOcAux = pOL->LT_GetFirstOccurrence();
		break;

	case NEXTOC:
		pltcOcAux = pOL->LT_GetNextOccurrence();
		break;

	case PREVIOUSOC:
		pltcOcAux = pOL->LT_GetPreviousOccurrence();
		break;

	case LASTOC:
		pltcOcAux = pOL->LT_GetLastOccurrence();
		break;

	case CURROC:
		pltcOcAux = pOL->LT_GetCurrentOccurrence();
		break;

	}
	if( uiNavigationField > 0 && iPos != CURROC ){
		// o usuario escolheu um campo especifico.
		// vamos procurar uma ocorrencia que tenha o campo
		// requerido
		while( pltcOcAux ){
			if( uiNavigationField == pltcOcAux->LT_GetGroup() ){
				// estamos na ocorrencia desejada
				break;
			}
			switch( iPos ){
			case FIRSTOC:
			case NEXTOC:
				pltcOcAux = pOL->LT_GetNextOccurrence();
				break;

			default:
				pltcOcAux = pOL->LT_GetPreviousOccurrence();
				break;
			}
		}
	}
	if( !pltcOcAux ){
		// nao encontramos nenhuma ocorrencia.
		NRETURN( LBSE_ERROR );
	}
	SetError( LBS_OK );
	return( pltcOcAux );
}


BOOL LBSC_Base::ValidOccurrence( LTC_OCCURRENCE *pOcc, LTC_OCCURRENCELIST *pOccList ) 
{
	if ( !pOccList->bFalseOL ) {
		return TRUE;
	}
	return (VerifyRecordStatus( pOcc->LT_GetSet() ) == LBS_OK);
}

/***
	PRIVATE
	Metodo CreateLbsOccList
	Gera a LO no formato registro/lista de ocorrencias (para navegacao corretamente)

	Parameters:
		- pExpr	-> apontador para uma lista de LO+expressao

	Return:
		- LBS_OK em caso de sucesso ou um erro

	Comments:
		- 

***/
int
LBSC_Base::CreateLbsOccList( LBSC_Expr *pExpr, LTC_EXPR *pLTExpr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CountOLRecs") );

	if( !pExpr || !pLTExpr ){
		ERETURN( LBSE_BADARG );
	}

	LTC_OCCURRENCELIST	*pOcList = pLTExpr->LT_GetResultList();

	if( !pOcList ){
		// erro doidao
		ERETURN( LBSE_ERROR );
	}

	if ( pExpr->pOccList ) {
		delete pExpr->pOccList;
		pExpr->pOccList = NULL;
	}

	LBSC_OcList *pNewList = new LBSC_OcList;
	if ( !pNewList ) {
		ERETURN( LBSE_NOMEMORY );
	}
	// vamos inicializar a lista com o maximo possivel; depois diminuimos se for o caso
	if ( !pNewList->Init( pOcList->LT_GetNumberOfOccurrence() ) ) {
		delete pNewList;
		ERETURN( LBSE_NOMEMORY );
	}

	LTC_OCCURRENCE *pltcCurrOc = pOcList->LT_GetFirstOccurrence();	// GREEN
	if( !pltcCurrOc ){
		// lista vazia
		pExpr->pOccList = pNewList;
		ERETURN( LBSE_EMPTYLIST );
	}
	long	lRecFromNum = (long) pltcCurrOc->LT_GetSet();;

	while( pltcCurrOc && !OperationCanceled() ){
		long	lRecToNum = (long) pltcCurrOc->LT_GetSet();
		if ( ValidOccurrence( pltcCurrOc, pOcList ) ) {
			if( lRecToNum != lRecFromNum ){	// mudou de registro
				lRecFromNum = lRecToNum;
				if ( pNewList->GetCurrentOccurrence() ) {	
					pNewList->Next();
				}
			}

			if ( !pNewList->Add( pltcCurrOc ) ) {
				delete pNewList;
				ERETURN( LBSE_NOMEMORY );
			}
		}
		pOcList->LT_DelOccurrence();
		pltcCurrOc = pOcList->LT_GetCurrentOccurrence();
	}

	long lNewSize = pNewList->CurPos() + 1;

	pNewList->First();
	if ( !pNewList->GetCurrentOccurrence() ) {
		// lista vazia
		pExpr->pOccList = pNewList;
		ERETURN( LBSE_EMPTYLIST );
	}
	// vamos reajustar o tamanho da LO para o numero de itens ate o momento
	if ( !pNewList->Shrink( lNewSize ) ) {
		delete pNewList;
		ERETURN( LBSE_NOMEMORY );
	}
	pExpr->pOccList = pNewList;
	ERETURN( LBS_OK );
}

/***
	PRIVATE
	Metodo ClearMaxRepetitionStatus
	Troca para o valor da ultima repeticao do campo a indicacao de MAXREPETITION de uma ocorrencia qualquer

	Parameters:
		- pltcCurrOc -> apontador para a ocorrencia

	Return:
		- TRUE se trocou; FALSE caso contrario

	Comments:
		- 

***/
BOOL
LBSC_Base::ClearMaxRepetitionStatus( LBSC_Occurrence &lbscOc )
{
	LBSC_Field *pcfField = lbscrCurrRecord ( lbscOc.GetField() );
	if ( !pcfField ) {
		return FALSE;
	}

	if ( pcfField && lbscOc.GetRepetition() == MAXREPETITION ) {
		(lbscOc.pltcOc)->SetSubGroup( pcfField->GetNumberOfRepetition() - 1 );
		return TRUE;
	}

	return FALSE;
}


