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
 

TSRControlInfo 
LBSC_Base::ObtemControlInfo()
{
	TSRControlInfo sControl;
	memset(&sControl, 0, sizeof(sControl));

	strcpy((char *)sControl.szClientName, szClientName);
	sControl.lClntTimeStamp = lClntTimeStamp;
	sControl.lSvcTimeStamp = lSvcTimeStamp;
	sControl.lObj = lSessionObj;

	return sControl;
}

 

 /**********************************/
int
LBSC_Base::SetNavigationByIndex( const LBSC_Ticket *pTicket, BOOL bNavState, UINT uiFieldId, int iIndex, int iType )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();
	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();
	// invalida a chave de navegacao
	strcpy(szNavKey, "");

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_SetNavigationLocate InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.lbNavState	=	bNavState;
	InPar.lFieldId		=	(long)uiFieldId;
	InPar.liIndex		=	iIndex;
	InPar.liType		=	iType;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetNavigationLocate DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SetNavigationByIndex( DupInPar );
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

/**********************************/
int
LBSC_Base::SetNavigationByKey( const LBSC_Ticket *pTicket, BOOL bNavState, UINT uiFieldId, int iIndex, char *szKey, int iType )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();
	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();
	// guarda a chave de navegacao
	if ( szKey ) {
		strcpy(szNavKey, szKey);
	}
	else {
		strcpy(szNavKey, "");
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_SetNavigationLocate InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.lbNavState	=	bNavState;
	InPar.lFieldId		=	(long)uiFieldId;
	InPar.liIndex		=	iIndex;
	InPar.szNavKey		=	(unsigned char*)szKey;
	InPar.liType		=	iType;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetNavigationLocate DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SetNavigationByKey( DupInPar );
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

/**********************************/
int
LBSC_Base::Locate( const LBSC_Ticket *pTicket, UINT uiFieldId, int iIndex, char *szKey, int iType )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();
	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_SetNavigationLocate InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.lFieldId		=	(long)uiFieldId;
	InPar.liIndex		=	(long)iIndex;
	InPar.szNavKey		=	(unsigned char*)szKey;
	InPar.liType		=	( long )iType;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetNavigationLocate DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_Locate( DupInPar );
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

/**********************************/
int
LBSC_Base::GetNumberOfSlots()
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_GetNumberOfSlots( DupInPar );
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

/**********************************/
long
LBSC_Base::GetSlotSize( int iIndex )
{
	long	lRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liIndex	=	( long )iIndex;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetSlotSize( DupInPar );
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

	
	return( lRet );
}

/**********************************/
long
LBSC_Base::GetFieldSlotSize( UINT uiId )
{
	long	lRet;

	// tenta primeiro usar a cache
	if ( cfscFieldSlot.UsandoCache() ) {
		long lResult = cfscFieldSlot.GetFieldSlotSize_Cache( uiId );
		if ( lResult != -1 ) {
			return lResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lId		=	(long)uiId;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetFieldSlotSize( DupInPar );
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

	
	return( lRet );
}

/**********************************/
const char *
LBSC_Base::SearchStopWord( const LBSC_Ticket *pTicket, const char *szStopWord, int iTypeSearch )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_SearchStopWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );


	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szStopWord	=	(unsigned char*) StrDup( szStopWord );
	InPar.liTypeSearch	=	( long )iTypeSearch;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SearchStopWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_SearchStopWord( DupInPar );
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

	if( InPar.szStopWord ){
		delete InPar.szStopWord;
	}

	if ( !szRet ) {
		return NULL;
	}

	strcpy( (char *)szStopWord, szRet );
	ClntFree( (void *)szRet );	// detona memoria do RPC
	return( szStopWord );
}

/**********************************/
int
LBSC_Base::AddGoWord( UINT uiId, char *szGoWord )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lId		=	(long)uiId;
	InPar.szGoWord	=	( unsigned char * )szGoWord;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_AddGoWord( DupInPar );
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

/**********************************/
int
LBSC_Base::DelGoWord( UINT uiId, char *szGoWord )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lId		=	(long)uiId;
	InPar.szGoWord	=	(unsigned char*)szGoWord;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelGoWord( DupInPar );
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

/**********************************/
int
LBSC_Base::ModifyFieldIndexAttrib( char *szFieldAliasName, char *szPassword, int iIndexAttrib )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyFieldIndexAttrib InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.liIndexAttrib		=	iIndexAttrib;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldIndexAttrib DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldIndexAttrib( DupInPar );
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

/**********************************/
int
LBSC_Base::ModifyFieldIndexAttrib( UINT uiFieldId, char *szPassword, int iIndexAttrib )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyFieldIndexAttrib InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	uiFieldId;
	InPar.szPassword		=	(unsigned char *)szPassword;
	InPar.liIndexAttrib		=	iIndexAttrib;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldIndexAttrib DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldIndexAttrib( DupInPar );
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

/**********************************/
int
LBSC_Base::ModifyFieldAttrib( char *szFieldAliasName, char *szPassword, UINT uiFieldAttribPar )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyFieldAttrib InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.uiAttrib			=	uiFieldAttribPar;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldAttrib DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldAttrib( DupInPar );
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


/**********************************/
int
LBSC_Base::ModifyFieldAttrib( UINT uiFieldId, char *szPassword, UINT uiFieldAttribPar )
{
	int		iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyFieldAttrib InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	uiFieldId;
	InPar.szPassword		=	(unsigned char *)szPassword;
	InPar.uiAttrib			=	uiFieldAttribPar;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldAttrib DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldAttrib( DupInPar );
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

		
/**********************************/
int
LBSC_Base::SetACLPerm( char *szName, long lId, char *szId, BYTE bMask, int iList )
{
	int		iRet;

	cacACL.InvalidaCache();	// invalida a cache de ACL

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ACLPerm InPar;
	memset( &InPar, 0, sizeof( InPar ) );
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szName	=	(unsigned char *)szName;
	InPar.lId		=	lId;
	InPar.szId		=	(unsigned char *)szId;
	InPar.bMask		=	bMask;
	InPar.liList	=	iList;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ACLPerm DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_SetACLPerm( DupInPar );
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

/**********************************/
int
LBSC_Base::GetACLPerm( char *szName, long lId, char *szId, int iList, BOOL bCheckAll )
{
	int		iRet;

	// tenta primeiro usar a cache
	if ( cacACL.UsandoCache() ) {
		int iResult = cacACL.GetACLPerm_Cache(szName, lId, iList, bCheckAll );
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ACLPerm InPar;
	memset( &InPar, 0, sizeof( InPar ) );
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szName	=	(unsigned char *)szName;
	InPar.lId		=	lId;
	InPar.szId		=	(unsigned char *)szId;
	InPar.liList	=	iList;
	InPar.bCheckAll	=	bCheckAll;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ACLPerm DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetACLPerm( DupInPar );
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

/**********************************/
int
LBSC_Base::DelACLPerm( char *szName, long lId, char *szId, int iList )
{
	int		iRet;

	// invalida a cache de ACL
	cacACL.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ACLPerm InPar;
	memset( &InPar, 0, sizeof( InPar ) );
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szName	=	(unsigned char *)szName;
	InPar.lId		=	lId;
	InPar.szId		=	(unsigned char *)szId;
	InPar.liList	=	iList;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ACLPerm DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelACLPerm( DupInPar );
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

/**********************************/
int
LBSC_Base::EnableOnLineIndex( BOOL bEnable )
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
	InPar.bEnable	=	bEnable;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_EnableOnLineIndex	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_EnableOnLineIndex( DupInPar );
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

/**********************************/
BOOL
LBSC_Base::OnLineIndexStatus()
{
	BOOL bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( FALSE );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_OnLineIndexStatus( DupInPar);
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
		return(	FALSE );
	}

	
	return( bRet );
}

/**********************************/
int
LBSC_Base::UpdateIndex( const LBSC_Ticket *lbscTicket )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket	=	BuildTickBuff( lbscTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_UpdateIndex( DupInPar );
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

/**********************************/
int
LBSC_Base::IndexAll( const LBSC_Ticket *lbscTicket, BOOL bRestoreContext )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_IndexAll InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( lbscTicket );
	InPar.bRestoreContext = bRestoreContext;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IndexAll DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_IndexAll( DupInPar );
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

/**********************************/
int
LBSC_Base::GetSlot( int iIndex, void *szBuffer )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetSlotPutSlot InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.liIndex		=	(long)iIndex;
	InPar.lBufferLen	=	0;
	InPar.szBuffer		=	NULL;
			
	TSROut_GetSlot	sOut;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotPutSlot DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetSlot( DupInPar );
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

	if( sOut.lBufferLen != 0 ){
		memcpy( szBuffer, sOut.szBuffer, sOut.lBufferLen );
		ClntFree ( (void *) sOut.szBuffer ); // libera memoria do RPC
	}

	
	return( sOut.lRet );
}

/**********************************/
int
LBSC_Base::PutSlot( int iIndex, void *szBuffer, int iLen )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetSlotPutSlot InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.liIndex		=	(long)iIndex;
	InPar.lBufferLen	=	iLen;
	InPar.szBuffer		=	(unsigned char*)szBuffer;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotPutSlot DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutSlot( DupInPar );
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

/**********************************/
int
LBSC_Base::GetFieldSlot( UINT uiId, void *szBuffer )
{
	// tenta primeiro usar a cache
	if ( cfscFieldSlot.UsandoCache() ) {
		long iResult = cfscFieldSlot.GetFieldSlot_Cache( uiId, szBuffer );
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetSlotPutSlot InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.lBufferLen	=	0;
	InPar.szBuffer		=	NULL;
	InPar.luiId			=	(long)uiId;
			
	TSROut_GetSlot	sOut;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotPutSlot DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldSlot( DupInPar );
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

	if( sOut.lBufferLen != 0 ){
		memcpy( szBuffer, sOut.szBuffer, sOut.lBufferLen );
		ClntFree ( (void *) sOut.szBuffer ); // libera memoria do RPC
	}

	
	return( sOut.lRet );
}

/**********************************/
int
LBSC_Base::PutFieldSlot( UINT uiId, void *szBuffer, int iLen )
{
	int iRet;

	// invalida a cache de slots de campos
	cfscFieldSlot.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetSlotPutSlot InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.lBufferLen	=	iLen;
	InPar.szBuffer		=	(unsigned char*)szBuffer;
	InPar.luiId			=	(long)uiId;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotPutSlot DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldSlot( DupInPar );
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

/**********************************/
int
LBSC_Base::GetNumberOfCounters()
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetNumberOfCounters( DupInPar);
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

/*********************************/
long
LBSC_Base::GetCount( int iIndex )
{
	long lRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetCount( DupInPar );
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

	
	return( lRet );
}

/*********************************/
int
LBSC_Base::PutCount( int iIndex, long lCount )
{
	int iRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;
	InPar.lId = lCount;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutCount( DupInPar );
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

/*********************************/
int
LBSC_Base::IncCount( int iIndex, long lCount )
{
	int iRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;
	InPar.lId = lCount;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_IncCount( DupInPar );
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

/*********************************/
int
LBSC_Base::DecCount( int iIndex, long lCount )
{
	int iRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;
	InPar.lId = lCount;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DecCount( DupInPar );
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


/*********************************/
int
LBSC_Base::LockCount( int iIndex, BOOL bWait )
{
	int iRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;
	InPar.lId = (long)bWait;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_LockCount( DupInPar );
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


/*********************************/
int
LBSC_Base::ReleaseCount( int iIndex )
{
	int iRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ReleaseCount( DupInPar );
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

/********************************************
*********************************************
*********************************************

   QUE TAL ISSO? EH FACILMENTE IDENTIFICAVEL?
********************************************
*********************************************
*********************************************/


/*********************************/
long			
LBSC_Base::GetNextCount( int iIndex )
{
	long lRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetNextCount( DupInPar );
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

	
	return( lRet );
}

/*********************************/
long			
LBSC_Base::GetPreviousCount( int iIndex )
{
	long lRet;

	TSRIn_GetSlotSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.liIndex = (long)iIndex;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetSlotSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetPreviousCount( DupInPar );
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

	
	return( lRet );
}

/*********************************/
int
LBSC_Base::ModifyPassword( const LBSC_Ticket *pTicket, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	TSRIn_ModifyPassword InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 		= this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szOldPassword = (unsigned char*)szOldPassword;
	InPar.szNewPassword = (unsigned char*)szNewPassword;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyPassword DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyPassword( DupInPar );
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

/*********************************/
int
LBSC_Base::ModifyMaintenancePassword( const LBSC_Ticket *pTicket, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	TSRIn_ModifyPassword InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 		= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szOldPassword = (unsigned char*)szOldPassword;
	InPar.szNewPassword = (unsigned char*)szNewPassword;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyPassword DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyMaintenancePassword( DupInPar );
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

/*********************************/
char *
LBSC_Base::GetUserBase()
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetUserBase( DupInPar);
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

	
	if( szRet ){
		char *szRet2 = StrDup( szRet );
		ClntFree( szRet );	// detona memoria do RPC
		return ( szRet2 );
	} 

	return NULL;
}

/*********************************/
char *
LBSC_Base::GetOwnerName()
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetOwnerName( DupInPar);
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

	
	if( szRet ){
		char *szRet2 = StrDup( szRet );
		ClntFree( szRet );	// detona memoria do RPC
		return ( szRet2 );
	} 

	return NULL;
}

/*********************************/
int
LBSC_Base::GetFullBaseName( char *szFullName )
{
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRGenericObj	InPar;
	TSROut_GetFullBaseName OutPar;

	memset( &InPar, 0, sizeof(InPar) );
	memset( &OutPar, 0, sizeof(OutPar) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj 		= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetFullBaseName( DupInPar );
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

	if ( OutPar.lRet == LBS_OK ) {
		strcpy( szFullName, (char *)OutPar.szFullBaseName);
	}
	
	return( OutPar.lRet );
}

/*********************************/
int
LBSC_Base::GetBaseName( char *szName )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRGenericObj	InPar;
	TSROut_GetFullBaseName OutPar;

	memset( &InPar, 0, sizeof(InPar) );
	memset( &OutPar, 0, sizeof(OutPar) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj 		= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetBaseName( DupInPar );
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

	if ( OutPar.lRet == LBS_OK ) {
		strcpy( szName, (char *)OutPar.szFullBaseName);
	}
	
	return( OutPar.lRet );
}

/*********************************/
BOOL
LBSC_Base::IsEncrypt()
{
	BOOL bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( FALSE );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_IsEncrypt( DupInPar);
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
		return(	FALSE );
	}

	
	return( bRet );
}

/*********************************/
BOOL
LBSC_Base::IsFullAccess()
{
	BOOL bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( FALSE );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_IsFullAccess( DupInPar);
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
		return(	FALSE );
	}

	
	return( bRet );
}

/*********************************/
BYTE
LBSC_Base::GetBaseType()
{
	BYTE bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (BYTE)LBSE_NETERROR );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_GetBaseType( DupInPar);
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
		return(	(BYTE)LBSE_NETERROR );
	}

	
	return( bRet );
}

/*********************************/
int
LBSC_Base::GetBaseVersion()
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (int)LBSE_NETERROR );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Base_GetBaseVersion( DupInPar);
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
		return(	(int)LBSE_NETERROR );
	}

	
	return( iRet );
}


/*********************************/
int
LBSC_Base::ModifyBaseType( BYTE bNewBaseType )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyBaseType	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.lNewBaseType = (long) bNewBaseType;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyBaseType	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyBaseType( DupInPar );
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

/*********************************/
int
LBSC_Base::IndexString( const LBSC_Ticket *pTicket, long lRec, UINT uiField,
			int iRepet, char *szStr )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_IndexString	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 	= this->obj;
	InPar.lRec 		= lRec;
	InPar.lFieldId 	= (long)uiField;
	InPar.lRepet 	= (long)iRepet;
	InPar.szStr 	= (unsigned char *)szStr;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IndexString	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_IndexString( DupInPar );
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

/*********************************/
int
LBSC_Base::UnindexString( const LBSC_Ticket *pTicket, long lRec, UINT uiField,
			int iRepet, char *szStr )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_IndexString	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 	= this->obj;
	InPar.lRec 		= lRec;
	InPar.lFieldId 	= (long)uiField;
	InPar.lRepet 	= (long)iRepet;
	InPar.szStr 	= (unsigned char*)szStr;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IndexString	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_UnindexString( DupInPar );
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

/*********************************/
BOOL
LBSC_Base::IndexSystemOk()
{
	BOOL bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( FALSE );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Base_IndexSystemOk( DupInPar);
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
		return(	FALSE );
	}

	
	return( bRet );
}

/*********************************/
long
LBSC_Base::GetNumberOfStopWords( const LBSC_Ticket *pTicket )
{
	long lRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket	=	BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetNumberOfStopWords( DupInPar );
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

	
	return( lRet );
}

/*********************************/
int
LBSC_Base::AddStopWord( const LBSC_Ticket *pTicket, char *szSW )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_AddStopWord	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 	= this->obj;
	InPar.szSW 		= (unsigned char*)szSW;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddStopWord	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_AddStopWord( DupInPar );
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

/*********************************/
int
LBSC_Base::ModifyBaseOwnerName( const LBSC_Ticket *pTicket, char *szOwnerNamePar, char *szCurrentPsw )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyBaseOwnerName	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 			= this->obj;
	InPar.szOwnerNamePar 	= (unsigned char*)szOwnerNamePar;
	InPar.szCurrentPsw		= (unsigned char*)szCurrentPsw;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyBaseOwnerName	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyBaseOwnerName( DupInPar );
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

int
LBSC_Base::GetFieldId( const char *szFieldNmae )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetFieldTypeId	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 		= this->obj;
	InPar.szFieldName 	= (unsigned char*)szFieldNmae;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldTypeId	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldId( DupInPar );
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

TFieldType	
LBSC_Base::GetFieldType( char *szFieldName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (TFieldType)LBSE_NETERROR );
	}

	TSRIn_GetFieldTypeId	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 		= this->obj;
	InPar.szFieldName 	= (unsigned char*)szFieldName;
	InPar.bTipoGetFieldType = RPC_BASE_GETFIELDTYPE_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldTypeId	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldType( DupInPar );
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
		return(	(TFieldType)LBSE_NETERROR );
	}

	
	return( iRet );

}


TFieldType	
LBSC_Base::GetFieldType( UINT uiFieldId )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (TFieldType)LBSE_NETERROR );
	}

	TSRIn_GetFieldTypeId	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 	= this->obj;
	InPar.lFieldId 	= (long)uiFieldId;
	InPar.bTipoGetFieldType = RPC_BASE_GETFIELDTYPE_UINT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldTypeId	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldType( DupInPar );
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
		return(	(TFieldType)LBSE_NETERROR );
	}

	
	return( iRet );

}

/*********************************/
TIndexAttrib
LBSC_Base::GetFieldIndexAttrib( char *szFieldAliasName )
{
	TIndexAttrib tiaRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetFieldIndexAttrib	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 			= this->obj;
	InPar.lFieldId			= -1;
	InPar.szFieldAliasName 	= (unsigned char*)szFieldAliasName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldIndexAttrib	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		tiaRet = (TIndexAttrib)RPC_Base_GetFieldIndexAttrib( DupInPar );
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

	
	return( tiaRet );
}

/*********************************/
TIndexAttrib
LBSC_Base::GetFieldIndexAttrib( UINT uiFieldId )
{
	TIndexAttrib tiaRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetFieldIndexAttrib	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj 			= this->obj;
	InPar.lFieldId			= (long)uiFieldId;
	InPar.szFieldAliasName 	= NULL;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldIndexAttrib	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		tiaRet = (TIndexAttrib)RPC_Base_GetFieldIndexAttrib( DupInPar );
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

	
	return( tiaRet );
}

/***********************************************************/
/***********************************************************/
/**************** GetFieldRepetition ***********************/
/***********************************************************/
/***********************************************************/

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, char *szReturn )
{
	int	iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;
		
	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, szReturn, bIsFieldId, ALPHA_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj; 
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_STRING;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		strcpy( szReturn, (const char*)sOut.Return );
		ClntFree( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, char *szReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, szReturn, bIsFieldId, ALPHA_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj; 
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		strcpy( szReturn, (const char *)sOut.Return );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, void *pvReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pvReturn, bIsFieldId, TEXT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj; 
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pvReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, void *pvReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pvReturn, bIsFieldId, TEXT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pvReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, long *plReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, plReturn, bIsFieldId, VALUE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( plReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, long *plReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, plReturn, bIsFieldId, VALUE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( plReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, double *pdReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pdReturn, bIsFieldId, DVALUE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char *)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		// checar se eh necessario deletar
		memcpy( pdReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, double *pdReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pdReturn, bIsFieldId, DVALUE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pdReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}


/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, LBSC_Binary *pbReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pbReturn, bIsFieldId, BINARY_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char *)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	if( sOut.Return ){
		pbReturn->iLen = ((LBSC_Binary*)(sOut.Return))->iLen;
		int iii = pbReturn->iLen;
		memcpy( pbReturn, sOut.Return, iii  );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}
	

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, LBSC_Binary *pbReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pbReturn, bIsFieldId, BINARY_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		pbReturn->iLen = ((LBSC_Binary*)(sOut.Return))->iLen;
		memcpy( pbReturn, sOut.Return,  pbReturn->iLen );
		ClntFree ((void *)sOut.Return);	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, LBSC_Reference *prReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, prReturn, bIsFieldId, REFERENCED_FIELD );
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( prReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, LBSC_Reference *prReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, prReturn, bIsFieldId, REFERENCED_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( prReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, BYTE *pbReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pbReturn, bIsFieldId, BYTE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pbReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, BYTE *pbReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pbReturn, bIsFieldId, BYTE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pbReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, short *psReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, psReturn, bIsFieldId, SINT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( psReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *)sOut.Return );	// libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, short *psReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, psReturn, bIsFieldId, SINT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( psReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, float *pfReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pfReturn, bIsFieldId, FLOAT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pfReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, float *pfReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pfReturn, bIsFieldId, FLOAT_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	

	if( sOut.Return ){
		memcpy( pfReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
		iRet = (int)sOut.lRet;
	}

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, C_Date *pcdReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pcdReturn, bIsFieldId, DATE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	if( sOut.usLen ){
		memcpy(pcdReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
	}
	iRet = (int)sOut.lRet;

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, C_Date *pcdReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pcdReturn, bIsFieldId, DATE_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	if( sOut.usLen ){
		memcpy(pcdReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
	}
	iRet = (int)sOut.lRet;

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, C_Time *pctReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = FALSE;
		int iResult = crcRep.GetFieldRepetition_Cache( szField,
						iRepNumber, pctReturn, bIsFieldId, TIME_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	if( sOut.usLen ){
		memcpy(pctReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
	}
	iRet = (int)sOut.lRet;

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, C_Time *pctReturn )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetition		InPar;
	TSROut_GetFieldRepetition	sOut;	

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		BOOL bIsFieldId = TRUE;
		int iResult = crcRep.GetFieldRepetition_Cache( &uiFieldId,
						iRepNumber, pctReturn, bIsFieldId, TIME_FIELD);
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lFieldId = (long)uiFieldId;
	InPar.lRepNumber = (long)iRepNumber;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldRepetition( DupInPar );
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

	if( sOut.usLen ){
		memcpy(pctReturn, sOut.Return, sOut.usLen );
		ClntFree ( (void *) sOut.Return ); // libera memoria do RPC
	}
	iRet = (int)sOut.lRet;

	return( iRet );
}

