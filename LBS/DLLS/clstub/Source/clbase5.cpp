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

/************************************************************/
/*	Procedimentos Métodos Stubs da classe LBSC_Base			*/
/*	Programadores: 	Renata Catao					*/
/*					Tarcio Rodrigues		*/
/*					Tricia Santos			*/
/*	Ultima alt : 21/11/95						*/
/************************************************************/

#ifndef _BASECL_H_
	#include	<basecl.h>  
#endif	// _BASECL_H_

#ifndef _MMDEFS_H_
	#include	<mmdefs.h>
#endif	// _MMDEFS_H_

#ifndef __lbsrpc_h__
	#include	<lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _LBSERROR_H_
	#include	<lbserror.h>
#endif	// _LBSERROR_H_

#ifndef _ERRNO_H_
	#include	<errno.h>
#endif	// _ERRNO_H_


#ifndef	_DEFMAC_H_
#include <defmac.h>
#endif

#ifndef	_BUFFERCL_H_
#include <buffercl.h>
#endif

#ifndef	_FBUFF_H_
#include <fbuff.h>
#endif

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_


#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_


#ifndef	_DUPLICATE_H_
	#include <duplicate.h>
#endif	// _DUPLICATE_H_


//	termina as operacoes de leitura de cache; usado no metodo GetLocalRepCache
#define ENDREAD_CACHE		fclose (fp);	\
							return tBuff;
//	diretorio a partir da qual a cache sera construida (relativo ao
//	diretorio da aplicacao
#define CACHE_ROOT_DIR		"CACHE"

//
//	Prototipos locais
//
void GetAppPath( char * );
int MakeDir( char * );

/**********************************/
char *
LBSC_Base::GetStopWords( const LBSC_Ticket *pTicket )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetStopWords( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	NULL );
	}

	if ( !szRet ) {
		return NULL;
	}

	return( szRet );
}



/***********************************************************/
int
LBSC_Base::ModifyBaseName( char *szNewBaseName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyBaseName InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.TBaseObj.sCtrlInfo = ObtemControlInfo();
	InPar.TBaseObj.lObj	=	this->obj;
	InPar.szNewBaseName	=	(unsigned char *)szNewBaseName;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyBaseName DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_ModifyBaseName(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR);	
	}

	
	return( iRet );
}

/***********************************************************/
int 
LBSC_Base::GetBaseLongName( char *szBaseName )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSROut_GetBaseLongName OutPar;

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj	=	this->obj;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

	       	OutPar = RPC_Base_GetBaseLongName( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
		RpcExcept(1){
			Free( DupInPar );

			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR);	
	}

	strcpy(szBaseName, (char *)OutPar.szBaseLongName);
	ClntFree ( OutPar.szBaseLongName );	 // libera memoria do RPC
	
	return( OutPar.lRet );
}


/***********************************************************/
void	
LBSC_Base::CancelOperation()
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr) ){
		return;
	}
		
	TSRGenericObj InPar;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj	= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			RPC_Base_CancelOperation( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
		RpcExcept(1){
			Free( DupInPar );

			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return;
	}

}


/***********************************************************/
void	
LBSC_Base::GetOpInfo( char *szActionPar, float *pfPercentPar )
{
	if ( !szActionPar || !pfPercentPar ) 
		return;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr) ){
		return;
	}
		
	TSROut_GetOpInfo OutPar;
	TSRGenericObj InPar;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj	= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			OutPar = RPC_Base_GetOpInfo( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
		RpcExcept(1){
			Free( DupInPar );

			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return;
	}

	strcpy( szActionPar, (char *)OutPar.szActionPar );
	*pfPercentPar = OutPar.fPercentPar; 
	
	ClntFree( (void *)OutPar.szActionPar );  // dealoca o que veio do RPC
}


/***********************************************************/
//
//	Retorna unm ponteiro para uma estrutura TACLLists a partir 
//	de um TSROut_ACLLists, detonando-o
//
TACL_Lists *
MakeTACL( TSROut_ACLLists &sRet )
{
	TACL_Lists *ptalList = new TACL_Lists;
	if ( !ptalList ) {
		return NULL;
	}

	LBSC_ACLList *paList = MakeACLList(sRet.togUserBaseBuff);
	if ( paList ) {
		ptalList->lUserBase = *paList;
		delete paList;
	}
	ClntFree( sRet.togUserBaseBuff.szBuffer );

	paList = MakeACLList(sRet.togGroupBaseBuff);
	if ( paList ) {
		ptalList->lGroupBase = *paList;
		delete paList;
	}
	ClntFree( sRet.togGroupBaseBuff.szBuffer );

	paList = MakeACLList(sRet.togUserFieldBuff);
	if ( paList ) {
		ptalList->lUserField = *paList;
		delete paList;
	}
	ClntFree( sRet.togUserFieldBuff.szBuffer );

	paList = MakeACLList(sRet.togGroupFieldBuff);
	if ( paList ) {
		ptalList->lGroupField = *paList;
		delete paList;
	}
	ClntFree( sRet.togGroupFieldBuff.szBuffer );

	paList = MakeACLList(sRet.togUserRecordBuff);
	if ( paList ) {
		ptalList->lUserRecord = *paList;
		delete paList;
	}
	ClntFree( sRet.togUserRecordBuff.szBuffer );

	paList = MakeACLList(sRet.togGroupRecordBuff);
	if ( paList ) {
		ptalList->lGroupRecord = *paList;
		delete paList;
	}
	ClntFree( sRet.togGroupRecordBuff.szBuffer );

	paList = MakeACLList(sRet.togUserFormBuff);
	if ( paList ) {
		ptalList->lUserForm = *paList;
		delete paList;
	}
	ClntFree( sRet.togUserFormBuff.szBuffer );

	paList = MakeACLList(sRet.togGroupFormBuff);
	if ( paList ) {
		ptalList->lGroupForm = *paList;
		delete paList;
	}
	ClntFree( sRet.togGroupFormBuff.szBuffer );

	paList = MakeACLList(sRet.togUserReportBuff);
	if ( paList ) {
		ptalList->lUserReport = *paList;
		delete paList;
	}
	ClntFree( sRet.togUserReportBuff.szBuffer );

	paList = MakeACLList(sRet.togGroupReportBuff);
	if ( paList ) {
		ptalList->lGroupReport = *paList;
		delete paList;
	}
	ClntFree( sRet.togGroupReportBuff.szBuffer );

	ptalList->strUserName = (char *)sRet.szOwnerName ? 
		(char *)sRet.szOwnerName : "";
	ClntFree( sRet.szOwnerName );

	ptalList->bBaseType = (BYTE)sRet.lBaseType;
	ptalList->bIsBasePasswdCorrect = sRet.bIsBasePasswdCorrect;

	return ptalList;
}


/***********************************************************/
TACL_Lists *
LBSC_Base::GetAllACLLists( const LBSC_Ticket *pTicket )
{
#ifdef _DEBUG
	Log("RPC_Base_GetAllACLLists: Inicio");
#endif // _DEBUG

	TSROut_ACLLists	sRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Base_GetAllACLLists( DupInPar );

				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);

		return( NULL );
	}

	// copia a estrutura E detona os buffers alocados pelo stub RPC
	TACL_Lists *ptaNewStruct = MakeTACL( sRet );

#ifdef _DEBUG
	Log("RPC_Base_GetAllACLLists: Fim");
#endif // _DEBUG
	return( ptaNewStruct );
}



/***********************************************************/
C_Buffer *
LBSC_Base::GetAllRepetitions( const LBSC_Ticket *pTicket, int iNumRegs)
{
#ifdef _DEBUG
	Log("RPC_Base_GetAllRepetitions: Inicio");
#endif // _DEBUG

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_AllRepetitions InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lNumRegs	=	iNumRegs;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;

	TSROut_GenericBuffer	OutPar;
	memset(&OutPar, 0, sizeof(OutPar));

	struct stat sAtualBaseInfo;
	memset(&sAtualBaseInfo, 0, sizeof(sAtualBaseInfo));

	// busca a cache local apenas se esta querendo trazer 
	// todos os dados da base
	if ( iNumRegs == -1 ) {
		if ( GetBaseTimeInfo( &sAtualBaseInfo ) != LBS_OK ) { // nao consegue obter as informacoes do servidor
			memset(&sAtualBaseInfo, 0, sizeof(sAtualBaseInfo));
		}
		else {
			OutPar = GetLocalRepCache( sAtualBaseInfo );
		}
	}

	if ( !OutPar.szBuffer )  {	// nao tem cache local; obtem do servidor mesmo
		do {
			TSRIn_AllRepetitions DupInPar;
			RpcTryExcept{
				::Duplicate( InPar, &DupInPar );
					Criptografa( DupInPar );

	       			OutPar = RPC_Base_GetAllRepetitions( DupInPar );

					bNetError = FALSE;
					bRetry = FALSE;

					Free( DupInPar );
			}
			RpcExcept(1){
					Free( DupInPar );

					bRetry = LBSC_ClntNet::EnviaNovaRPC();
					ulExceptionCode = RpcExceptionCode();
				
				
			}
			RpcEndExcept
		} while( bRetry );
		LBSC_ClntNet::FreeRPCHandle();
		if( bNetError ) {

			LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);

			return( NULL );
		}
	}

	C_Buffer *pRet = NULL;
	if ( OutPar.lTamBuff ) { 

		pRet = new C_Buffer( (char *)OutPar.szBuffer, OutPar.lTamBuff );
	} 

	ClntFree( OutPar.szBuffer );

#ifdef _DEBUG
	Log("RPC_Base_GetAllRepetitions: Fim");
#endif // _DEBUG
	return pRet;
}


/***********************************************************/
TSlotCache *
LBSC_Base::GetAllFieldSlots( const LBSC_Ticket *pTicket )
{
	TSROut_GenericBuffer	sRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Base_GetAllFieldSlots( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);

		return( NULL );
	}

	TSlotCache *tscRet = NULL; 
	if ( sRet.lTamBuff ) { 
		tscRet = MakeBaseCacheArray( sRet );
	} 

	ClntFree( sRet.szBuffer );

	return tscRet;
}


COccurList *
LBSC_Base::GetAllOccurrences( const LBSC_Ticket *pTicket )
{
	TSROut_GenericBuffer	sRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Base_GetAllOccurrences( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);

		return( NULL );
	}

	COccurList *pList = NULL; 
	if ( sRet.lTamBuff ) { 
		pList = MakeOccurList( sRet );
	} 

	ClntFree( sRet.szBuffer );

	return pList;
}


/**********************************/
int
LBSC_Base::EnableFastRecord( BOOL bFastRecPar )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_EnableOnLineIndex	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.bEnable	=	bFastRecPar;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_EnableOnLineIndex	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_EnableFastRecord( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}


/***********************************************************/
BOOL			
LBSC_Base::GetGowords( char *szFieldAlias, char **pszGoWord )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szField	=	( unsigned char * )szFieldAlias;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetGowords(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	NULL );
	}

	if ( !szRet ) {
		*pszGoWord = NULL;
		return FALSE;
	}

	*pszGoWord = new char [ strlen(szRet) + 1 ];

	if ( !*pszGoWord ) {
		return FALSE;
	}

	strcpy( *pszGoWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( TRUE );
}


/***********************************************************/
BOOL			
LBSC_Base::SetGowords( char *szFieldAlias, const char *szGoWord )
{
	BOOL bRet = TRUE;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szField	=	( unsigned char * )szFieldAlias;
	InPar.szGoWord	=	( unsigned char * )szGoWord;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_SetGowords(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	NULL );
	}

	return( bRet );
}


/***********************************************************/
int				
LBSC_Base::GetMinkeysize( )
{
	int		iRet = 0;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetMinkeysize( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR);
	}

	return( iRet );
}


/***********************************************************/
int				
LBSC_Base::SetMinkeysize( int iMinKeySize )
{
	int		iRet = 0;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );
	
	InPar.sCtrlInfo		= ObtemControlInfo();
	InPar.lBaseObj		= this->obj;
	InPar.lMinKeySize	= iMinKeySize;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_SetMinkeysize( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR);
	}

	return( iRet );
}


/***********************************************************/
int
LBSC_Base::GetBaseTimeInfo( struct stat *psInfo )
{
	int	iRet = 0;

	if ( !psInfo ) {
		return LBSE_ERROR;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}
	
	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));
	TSROut_GenericBuffer OutPar;
	memset( &OutPar, 0, sizeof(OutPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetBaseTimeInfo( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();

	//
	//	o buffer de retorno do metodo deve ter o "iRet" e 
	//	"pStat"
	//
	if( bNetError || 
			OutPar.lTamBuff != ( sizeof(iRet)+sizeof(*psInfo)) ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	// copia o retorno do metodo
	memcpy(&iRet, OutPar.szBuffer, sizeof(iRet));

	// copia a estrutura com as informacoes em si
	if ( iRet == LBS_OK ) {
		memcpy(psInfo, OutPar.szBuffer+sizeof(iRet), sizeof(*psInfo));
	}

	return( iRet );

}

/***********************************************************/
void 
LBSC_Base::InvalidaRepCache()
{
	crcRep.InvalidaCache();
}

/***********************************************************/
void 
LBSC_Base::InvalidaACLCache()
{
	cacACL.InvalidaCache();
}

/***********************************************************/
void 
LBSC_Base::InvalidaOccurrCache()
{
	cocOccur.InvalidaCache();
}

/***********************************************************/
void 
LBSC_Base::InvalidaFieldSlotCache()
{
	cfscFieldSlot.InvalidaCache();
}

/***********************************************************/
void 
LBSC_Base::EnableMultipleRecords( int iNumRegs )
{
}

/***********************************************************/
void 
LBSC_Base::DisableMultipleRecords()
{
}


/**********************************/
int
LBSC_Base::InsertBlankRepetition( UINT uiFieldId, int iRepNumber )
{
	int iRet;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_DelFieldRepetition InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szField		=	NULL;
	InPar.lFieldId		=	( long )uiFieldId;
	InPar.liRepNumber	=	( long )iRepNumber;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_InsertBlankRepetition(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
		
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/***********************************************************/
//
//	Obtem a cache de repeticoes local; qualquer erro, deve retornar
//	tudo vazio, e desfazer qualquer operacao pendente
//
TSROut_GenericBuffer	
LBSC_Base::GetLocalRepCache( struct stat sAtualBaseInfo )
{
	char szPath[FULLNAMESIZE + 1];
	char szFullPath[FULLNAMESIZE + 1];
	TSROut_GenericBuffer	tBuff;
	memset(&tBuff, 0, sizeof(tBuff));	// inicializa com tudo vazio

	GetAppPath( szPath );

	if ( stricmp((char*)ServerAddr, "") == 0 || stricmp(szBaseName, "") == 0 ||
					stricmp(szNavKey, "") == 0 ) {	// path invalido
		return tBuff;
	}
	sprintf(szFullPath, "%s\\%s\\%s\\%s\\%s", szPath, CACHE_ROOT_DIR, 
				(char*)ServerAddr, szBaseName, szNavKey);

	FILE *fp = fopen(szFullPath, "rb");

	if ( !fp ) {	// falha na abertura
		return tBuff;
	}

	struct stat sCacheBaseInfo;
	if ( fread(&sCacheBaseInfo, sizeof(sCacheBaseInfo), 1, fp) !=
								1 ) {	// nao leu da cache
		ENDREAD_CACHE	
	}

	if ( sAtualBaseInfo.st_mtime != sCacheBaseInfo.st_mtime ) {	// cache invalida
		ENDREAD_CACHE	
	}

	if ( fread(&tBuff.lTamBuff, sizeof(tBuff.lTamBuff), 1, fp) !=
								1 ) {	// nao leu da cache
		ENDREAD_CACHE	
	}

	if ( (tBuff.szBuffer = (unsigned char *)new char[tBuff.lTamBuff]) 
						== NULL ) {	// erro de alocacao
		ENDREAD_CACHE	
	}

	if ( fread(tBuff.szBuffer, tBuff.lTamBuff, 1, fp) !=
								1 ) {	// nao leu da cache
		ENDREAD_CACHE	
	}

	ENDREAD_CACHE	
}

	
/***********************************************************/
void
LBSC_Base::SaveLocalRepCache( TSROut_GenericBuffer tBuff, 
									struct stat sAtualBaseInfo )
{
	char szPath[FULLNAMESIZE + 1] = "";

	if ( stricmp((char*)ServerAddr, "") == 0 || stricmp(szBaseName, "") == 0 ||
					stricmp(szNavKey, "") == 0 ) {	// nada a fazer
		return ;
	}

	GetAppPath( szPath );

	// cria o diretorio do arquivo de cache: dir. app. + 
	//		dir. raiz da cache + servidor + base
	strcat(szPath, "\\");
	strcat(szPath, CACHE_ROOT_DIR);
	strcat(szPath, "\\");
	strcat(szPath, (char *)ServerAddr);
	strcat(szPath, "\\");
	strcat(szPath, szBaseName);
	MakeDir(szPath);

	// cria o arquivo de cache
	strcat(szPath, "\\");
	strcat(szPath, szNavKey);
	FILE *fp = fopen(szPath, "wb");
	if ( !fp ) {	// erro de criacao
		return;
	}

	if ( fwrite( &sAtualBaseInfo, sizeof(sAtualBaseInfo), 1,
				fp ) != 1 ) {	// erro de gravacao
		fclose(fp);
		return;
	}

	if ( fwrite( &tBuff.lTamBuff, sizeof(tBuff.lTamBuff), 1,
				fp ) != 1 ) {	// erro de gravacao
		fclose(fp);
		return;
	}

	if ( fwrite( tBuff.szBuffer, tBuff.lTamBuff, 1,
				fp ) != 1 ) {	// erro de gravacao
		fclose(fp);
		return;
	}

	fclose(fp);
}


void			
LBSC_Base::GetDirBase( char *szBuffer, const char *szUDB, const char *szServer )
{
	char *szRet=NULL;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)szServer ) || !szBuffer ){
		return;
	}

	TSRIn_GetBaseLongName InPar;
	memset(&InPar, 0, sizeof(InPar));

	InPar.szUDBName = (unsigned char *)szUDB;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetBaseLongName DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );
	       		szRet = (char*)RPC_Base_GetDirBase( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( (char *)szServer , ulExceptionCode);
		return;
	}

	if ( !szRet ) {
		return;
	}

	strcpy( szBuffer, szRet );
	ClntFree( szRet );	// detona memoria do RPC
}


void 
GetAppPath( char *szPath )
{
	strcpy(szPath, LBSC_ClntNet::ObtemClientIniName());

	// retira o nome do .INI, deixando so o nome do diretorio
	for( int i = strlen( szPath ) - 1; i >= 0; i-- ) {
		if( szPath[ i ] == '\\' || szPath[ i ] == '/' ) {
		 szPath[ i ] = '\0';
		 break;
		}
	}
}

/***
	NextTok
	Obtem o proximo nome de diretorio de uma string

	Parameters:
		- szStr	-> string da qual os nomes de diretorios serao extraidos.
			   se for NULL, o metodo assume a ultima string != NULL que
			   foi passada (como o strtok)
		- szSeparator -> string de separacao (deve conter apenas um caracter)
				 (funciona como o segundo parametro do strtok)

	Return:
		- nome do diretorio encontrado ou NULL se o fim da string foi atingido

	Comments:
		- 

***/
char *
NextTok( char *szStr, char *szSeparator )
{
	static	char	szConst[ 1024 ];	// guarda a string original
	static	char	szRet[ 1024 ];		// serve para retorno
	static	char	*szBuffer = szStr;	// serve para procurar o szSeparator
	static	int	iPos = 0;

	if( !szSeparator ){
		// resetar
		szBuffer = szStr;
		iPos = 0;
		return( NULL );
	}

	if( szStr ){
		strcpy( szConst, szStr );
		szBuffer = szStr;
	}
	if( szConst[ iPos ] == '\0' ){
		return( NULL );
	}
	do{
		strcpy( szRet, szConst );
		for( ; *szBuffer != *szSeparator && *szBuffer; szBuffer++, iPos++ );
		szRet[ iPos++ ] = '\0';
		szBuffer++;
	} while( *szRet == '\0' || stricmp( szRet, "\\" ) == 0 || szRet[ strlen( szRet ) -1 ] == ':' );
	return( szRet );
}

/***
	MakeDir
	Cria um diretorio

	Parameters:
		- szDirName	-> nome do diretorio a ser criado

	Return:
		- LBS_OK ou erro

	Comments:
		- o diretorio a ser criado pode conter varios niveis e este metodo
		  criara' todos os niveis, ate' o ultimo.
		- se o diretorio ja' existir, o metodo retornara' LBSE_DIREXIST

***/
int
MakeDir( char *szDirName )
{
	if( chdir( szDirName ) == 0 ){
		// ja' existe
		return( LBSE_DIREXIST );
	}

	// resetar o NextTok
	NextTok( szDirName, NULL );

	char	*szName = NextTok( szDirName, "\\" );
	while( szName ){
		mkdir( szName );
		szName = NextTok( NULL, "\\" );
	}
	return( LBS_OK );
}


