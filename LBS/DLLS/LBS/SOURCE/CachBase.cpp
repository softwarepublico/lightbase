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
// Module: CACHBASE.CPP
// Description:
//
//	LBSC_BASE cache methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 03/02/97
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
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif

#ifdef __BORLANDC__
#pragma warn -par
#endif


EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo GetAllACLLists
	Obtem todas as listas de ACLs do LBS

	Parameters:
		- pTicket	-> ticket de seguranca

	Return:
		- ponteiro para uma estrutura contendo copias das listas
		  de ACLs do LBS ou NULL em caso de erro.

	Comments:
		- a aplicacao DEVE deletar a estrutura retornada por este metodo.

***/
TACL_Lists *
LBSC_Base::GetAllACLLists( const LBSC_Ticket *pTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetAllACLLists") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}

	TACL_Lists	*ptACLListsRet = new TACL_Lists;

#ifdef __TEST
	ChangePointerContext( (void**) &ptACLListsRet );
#endif

	if( !ptACLListsRet ){
		NRETURN( LBSE_NOMEMORY );
	}

	ptACLListsRet->lUserBase = lbscaBaseUserAcl;					// usa o operador = da lista
	ptACLListsRet->lGroupBase = lbscaBaseGroupAcl;					// idem
	ptACLListsRet->lUserField = lbscaFieldUserAcl;					// idem
	ptACLListsRet->lGroupField = lbscaFieldGroupAcl;				// idem
	ptACLListsRet->lUserRecord = lbscaRecordUserAcl;				// idem
	ptACLListsRet->lGroupRecord = lbscaRecordGroupAcl;				// idem
	ptACLListsRet->lUserForm = lbscaFormUserAcl;					// idem
	ptACLListsRet->lGroupForm = lbscaFormGroupAcl;					// idem
	ptACLListsRet->lUserReport = lbscaReportUserAcl;				// idem
	ptACLListsRet->lGroupReport = lbscaReportGroupAcl;				// idem
	ptACLListsRet->strUserName = (char*) LB1.tcrHead.szOwnerName;
	ptACLListsRet->bBaseType = LB1.tcrHead.bBaseType;
	ptACLListsRet->bIsBasePasswdCorrect = bIsBasePasswdCorrect;

	SetError( LBS_OK );
	return( ptACLListsRet );
}



/***
	PUBLIC
	Metodo GetAllRepetitions
	Obtem todas as repeticoes, de varios tipos e tamanhos, 
	de um ou mais registros, de uma so' vez.

	Parameters:
		- pTicket	-> ticket de seguranca
		- iNumRegs	-> numero de registros que devem ser lidos
					   para o LBS obter as repeticoes. O default
					   eh 1 (apenas o registro corrente).

	Return:
		- ponteiro para uma tira de bytes contendo informacoes
		  como descritas no documento de HLD-performance-C/S ou
		  NULL em caso de erro.

	Comments:
		- a aplicacao DEVE deletar o buffer retornado por este metodo.

***/
C_Buffer *
LBSC_Base::GetAllRepetitions( const LBSC_Ticket *pTicket, int iNumRegs )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetAllRepetitions") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// algoritmo? Veja no documento de LLD das alteracoes do
	// LBS para c/s e LBWMonit

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( lbscrCurrRecord.IsUndefined() ){
		NRETURN( LBSE_UNDEFINEDRECORD );
	}

	C_Buffer *pBuf = NULL;
	long lRecordSize = 0;
	long lSuggestedPageSize = 0;
	if ( !GetRecordBuffer( &pBuf, &lRecordSize, &lSuggestedPageSize, TRUE) ) {
		NRETURN( LBSE_NOMEMORY );
	}

	SetError( LBS_OK );
	return( pBuf );
}



/***
	PUBLIC
	Metodo GetAllFieldSlots
	Retorna os slots de todos os campos

	Parameters:
		- pTicket		-> ticket de seguranca

	Return:
		- ponteiro para uma estrutura

	Comments:
		- 

***/
TSlotCache *
LBSC_Base::GetAllFieldSlots( const LBSC_Ticket *pTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetAllFieldSlots") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	TSlotCache	*ptscRet = new TSlotCache;
	if( !ptscRet ){
		NRETURN( LBSE_NOMEMORY );
	}
	ptscRet->iNumberOfFieldSlots = GetNumberOfFields();
	ptscRet->pSlots = new TSlotCacheInfo[ ptscRet->iNumberOfFieldSlots ];
	if( !ptscRet->pSlots ){
		delete ptscRet;
		NRETURN( LBSE_NOMEMORY );
	}
	for( int i = 0; i < ptscRet->iNumberOfFieldSlots; i++ ){
		// pra evitar a carga de todos os dados do registro so porque estamos querendo obter a estrutura
		BOOL bAux = lbscrCurrRecord.bMustLoadData;
		lbscrCurrRecord.bMustLoadData = FALSE;
		LBSC_Field	*pfField = lbscrCurrRecord[ i ];
		// reabilita a carga dos dados dos campos
		lbscrCurrRecord.bMustLoadData = bAux;

		if( !pfField ){
			// deu pau
			delete ptscRet;
			NRETURN( LBSE_ERROR );
		}
		ptscRet->pSlots[ i ].uiId = pfField->GetId();
		ptscRet->pSlots[ i ].iSize = pfField->lSlotSize;
		if( ptscRet->pSlots[ i ].iSize < 0 ){
			if( ptscRet->pSlots[ i ].iSize == LBSE_EMPTYSLOT ){
				ptscRet->pSlots[ i ].pBuff = NULL;
			} else {
				delete ptscRet;
				return( NULL );
			}
		} else {
			ptscRet->pSlots[ i ].pBuff = new char[ ptscRet->pSlots[ i ].iSize ];
			if( !ptscRet->pSlots[ i ].pBuff ){
				delete ptscRet;
				NRETURN( LBSE_NOMEMORY );
			}
			memcpy( ptscRet->pSlots[ i ].pBuff, pfField->pvSlot, pfField->lSlotSize );
		}
	}
	SetError( LBS_OK );
	return( ptscRet );
}



/***
	PUBLIC
	Metodo EnableMultipleRecords
	Habilita a carga de varios registros para a memoria. Aqui no LBS, este metodo
	nao faz nada. Ele serve para os stubs cliente/servidor

	Parameters:
		- iNumRegs		-> numero de registros que devem ser carregados para a memoria
						   quando uma operacao de leitura de registros for realizada

	Return:
		- 

	Comments:
		- 

***/
void
LBSC_Base::EnableMultipleRecords( int /*iNumRegs*/ )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::EnableMultipleRecords") );

	// este metodo eh dummy. esta' implementado nos stubs c/s
}



/***
	PUBLIC
	Metodo DisableMultipleRecords
	Desabilita a carga de varios registros para a memoria. Aqui no LBS, este metodo
	nao faz nada. Ele serve para os stubs cliente/servidor

	Parameters:
		- 

	Return:
		- 

	Comments:
		- 

***/
void
LBSC_Base::DisableMultipleRecords()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DisableMultipleRecords") );

	// este metodo eh dummy. esta' implementado nos stubs c/s
}




/***
	PRIVATE
	Metodo CopyMem
	Copia um buffer para outro, com um tamanho especificado. Se o buffer
	de recepcao for pequeno, este metodo o realocara'.

	Parameters:
		- ppTarget		-> endereco do buffer receptor
		- piOffSet		-> deslocamento dentro do buffer receptor para fazer a
						   copia do buffer de origem
		- pSource		-> buffer de origem
		- iSourceSize	-> tamanho do buffer de origem (numero de butes que devem ser copiados)
		- piTargetSize	-> tamanho maximo do buffer de recepcao (pode ser alterado)

	Return:
		- TRUE em caso de sucesso; FALSE em caso de algum erro.

	Comments:
		- 

***/
BOOL
LBSC_Base::CopyMem( void **ppTarget, int *piOffSet, void *pSource, int iSourceSize, int *piTargetSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CopyMem") );

	if( !ppTarget ){
		return( FALSE );
	}
	if( !(*ppTarget) || (((*piOffSet) + iSourceSize) > (*piTargetSize)) ){
		int	iAux = (*piTargetSize);
		(*piTargetSize) = (*piTargetSize) + max( iSourceSize, 255 );
		(*ppTarget) = LBS_Realloc( (*ppTarget), iAux, (*piTargetSize) );
		if( !(*ppTarget) ){
			return( FALSE );
		}
	}
	memcpy( (char*) (*ppTarget) + (*piOffSet), pSource, iSourceSize );
	(*piOffSet) += iSourceSize;
	return( TRUE );
}




