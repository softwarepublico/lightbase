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
 


/***********************************************************/
LBSC_Base::LBSC_Base() :	cacACL( (LBSC_Base *)this ), 
							crcRep( (LBSC_Base *)this ),
							cfscFieldSlot( (LBSC_Base *)this ),
							cocOccur( (LBSC_Base *)this )
{
	obj = 0;
	szBuffer = NULL;
	strcpy(ServerAddr,"" );
	strcpy(szStopWord,"" );
	lSessionObj = 0;
	pTicket = NULL;
	bListaFisica = TRUE;
	strcpy(szBaseName,"" );
	strcpy(szNavKey,"" );
}
			

/***********************************************************/
LBSC_Base::~LBSC_Base()
{
	if( szBuffer ){
		delete szBuffer;
		szBuffer= NULL;
	}

}

/***********************************************************/
int
LBSC_Base::Compare( LBSC_Base *lbscObj, int i )
{
	return ( lbscObj->obj == obj ); 
}

/***********************************************************/
const LBSC_Field *
LBSC_Base::GetFieldObj( char *szField )
{
	TSRIn_DelFieldGetFieldObj 	InPar;
	LBSC_Field					*pField = new LBSC_Field( szField, 0, this );
	
	if ( !pField ) {	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	memset( (void*) &InPar, 0, sizeof(TSRIn_DelFieldGetFieldObj));

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lFieldId = -1;

	TSROut_GetFieldObj	sOut;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldGetFieldObj 	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldObj(  DupInPar );
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
		delete pField;
		return(	NULL );
	}

	

	if ( sOut.lFieldObj == 0 )	{ // erro no getfieldobj remoto
		return NULL;
	}

	pField->szAliasName 	= (char*)sOut.szFieldName;
	ClntFree ( (void *) sOut.szFieldName ); // libera memoria do RPC
	pField->uiFieldId 		= (UINT)sOut.lFieldId;
	pField->obj 			= sOut.lFieldObj;
	pField->lBaseObj 		= this->obj;

	TSRControlInfo	sControl = ObtemControlInfo();
	pField->SetTimeStamp( sControl.lSvcTimeStamp );
	strcpy( pField->ServerAddr, this->ServerAddr );

	if( flFieldList.Find( pField, CMPFIELDNAME ) ){
		flFieldList.Del();
	}
	flFieldList.Add( pField, TAIL );

	return( flFieldList.Current() );
}

/*****************************************/
const LBSC_Field *
LBSC_Base::GetFieldObj( UINT uiFieldId )
{
	TSRIn_DelFieldGetFieldObj 	InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_DelFieldGetFieldObj));

	LBSC_Field	*pField = new LBSC_Field( "", uiFieldId, this );
	if ( !pField ) {	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		delete pField;
		return( NULL );
	}
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.szField = NULL;
	InPar.lFieldId = (long)uiFieldId;

	TSROut_GetFieldObj	sOut;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldGetFieldObj 	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetFieldObj(  DupInPar );
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

	

	if ( sOut.lFieldObj == 0 )	{ // erro no getfieldobj remoto
		return NULL;
	}

	pField->szAliasName = (char*)sOut.szFieldName;
	ClntFree ( (void *)sOut.szFieldName );	 // libera memoria do RPC
	pField->uiFieldId 	= (UINT)sOut.lFieldId;
	pField->obj 		= sOut.lFieldObj;
	pField->lBaseObj 	= this->obj;
	pField->lSessionObj = this->lSessionObj;
	strcpy( pField->ServerAddr, this->ServerAddr );

	TSRControlInfo	sControl = ObtemControlInfo();
	pField->SetTimeStamp( sControl.lSvcTimeStamp );
	if( flFieldList.Find( pField, CMPFIELDID ) ){
		flFieldList.Del();
	}

	flFieldList.Add( pField, TAIL );

	return( flFieldList.Current() );
}

/*************************************/
BOOL
LBSC_Base::BaseObjOk()
{
	BOOL		bRet;

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

	       		bRet = RPC_Base_BaseObjOk(  DupInPar );
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
LBSC_Base::AddField( const LBSC_Ticket *pTicket, TField *tfField )
{
	int iRet;

	// invalida a cache de slots de campos
	InvalidaFieldSlotCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_AddField InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	= this->obj;
	InPar.tfField	= ( TSRField * )tfField;
	InPar.sTicket	= BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddField DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_AddField(  DupInPar );
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
LBSC_Base::AddField( const LBSC_Ticket *pTicket, char *szFieldAliasName,
		char *szFieldDescription, char *szPassword,
		TFieldType tftFieldType, long lFieldSize,
		TIndexAttrib tiaIndexAttrib, UINT uiFieldAttrib )
{
	int iRet;

	// invalida a cache de slots de campos
	InvalidaFieldSlotCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_AddField InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj				= this->obj;
	InPar.sTicket 				= BuildTickBuff( pTicket );
	InPar.szFieldAliasName		= (unsigned char*)szFieldAliasName;
	InPar.szFieldDescription	= (unsigned char*)szFieldDescription;
	InPar.szPassword			= (unsigned char*)szPassword;
	InPar.ltftFieldType			= ( long )tftFieldType;
	InPar.lFieldSize			= lFieldSize;
	InPar.ltiaIndexAttrib		= ( long )tiaIndexAttrib;
	InPar.lFieldAttrib			= ( long )uiFieldAttrib;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddField DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_AddField(  DupInPar );
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
LBSC_Base::DelField( char *szField )
{
	int iRet;

	// invalida a cache de slots de campos
	InvalidaFieldSlotCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_DelFieldRepetition InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	= this->obj;
	InPar.szField	= (unsigned char*)szField;
	InPar.lFieldId	= -1;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelField(  DupInPar );
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
LBSC_Base::DelField( UINT uiFieldId )
{
	int iRet;

	// invalida a cache de slots de campos
	InvalidaFieldSlotCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_DelFieldRepetition InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szField	=	NULL;
	InPar.lFieldId	=	(long)uiFieldId;


			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelField(  DupInPar );	
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
LBSC_Base::ModifyFieldPassword( char *szFieldAliasName, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldPassword InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.szOldPassword		=	(unsigned char*)szOldPassword;
	InPar.szNewPassword		=	(unsigned char*)szNewPassword;	
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldPassword DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldPassword(  DupInPar );
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
LBSC_Base::ModifyFieldPassword( UINT uiFieldId, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldPassword InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	(long)uiFieldId;
	InPar.szOldPassword		=	(unsigned char*)szOldPassword;
	InPar.szNewPassword		=	(unsigned char*)szNewPassword;	
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldPassword DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldPassword(  DupInPar );
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
LBSC_Base::ModifyFieldName( char *szFieldAliasName, char *szPassword, char *szFieldNewAliasName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldName InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj				=	this->obj;
	InPar.szFieldAliasName		=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId				=	-1;
	InPar.szPassword			=	(unsigned char*)szPassword;
	InPar.szFieldNewAliasName	=	(unsigned char*)szFieldNewAliasName;	

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldName DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldName(  DupInPar );
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
LBSC_Base::ModifyFieldName( UINT uiFieldId, char *szPassword, char *szFieldNewAliasName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldName InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj				=	this->obj;
	InPar.szFieldAliasName		=	NULL;
	InPar.lFieldId				=	(long)uiFieldId;
	InPar.szPassword			=	(unsigned char*)szPassword;
	InPar.szFieldNewAliasName	=	(unsigned char*)szFieldNewAliasName;	
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldName DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldName(  DupInPar );
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
LBSC_Base::ModifyFieldDescription( char *szFieldAliasName, char *szPassword, char *szNewDescription )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	TSRIn_ModifyFieldDescription InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.szNewDescription	=	(unsigned char*)szNewDescription;	



	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldDescription DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldDescription(  DupInPar );
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
LBSC_Base::ModifyFieldDescription( UINT uiFieldId, char *szPassword, char *szFieldNewAliasName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldDescription InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	( long )uiFieldId;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.szNewDescription	=	(unsigned char*)szFieldNewAliasName;	


			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldDescription DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldDescription(  DupInPar );
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
LBSC_Base::ModifyFieldSize( char *szFieldAliasName, char *szPassword, long lNewSize )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.lNewSize			=	lNewSize;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldSize(  DupInPar );
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
LBSC_Base::ModifyFieldSize( UINT uiFieldId, char *szPassword, long lNewSize )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_ModifyFieldSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	( long )uiFieldId;
	InPar.szPassword		=	(unsigned char*)szPassword;
	InPar.lNewSize			=	lNewSize;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldSize(  DupInPar );
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
LBSC_Base::GetNumberOfFields()
{
	int		iRet;

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

	       		iRet = (int)RPC_Base_GetNumberOfFields( DupInPar);
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
LBSC_Base::DelFieldRepetition( char *szField, int iRepNumber, BOOL bShift )
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
	InPar.szField		=	(unsigned char*)szField;
	InPar.lFieldId		=	-1;
	InPar.liRepNumber	=	( long )iRepNumber;
	InPar.bShift		= bShift;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelFieldRepetition(  DupInPar );
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
LBSC_Base::DelFieldRepetition( UINT uiFieldId, int iRepNumber, BOOL bShift )
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
	InPar.bShift		=	bShift;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DelFieldRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelFieldRepetition(  DupInPar );
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
LBSC_Base::GetNumberOfRepetition( char *szFieldAliasName )
{
	int iRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		int iResult = crcRep.GetNumberOfRepetition_Cache( szFieldAliasName, FALSE );
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetNumberOfRepetition InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetNumberOfRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetNumberOfRepetition(  DupInPar );
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
LBSC_Base::GetNumberOfRepetition( UINT uiFieldId )
{
	int iRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		int iResult = crcRep.GetNumberOfRepetition_Cache( &uiFieldId, TRUE );
		if ( iResult != -1 ) {
			return iResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetNumberOfRepetition InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	( long )uiFieldId;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetNumberOfRepetition DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetNumberOfRepetition(  DupInPar );
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
long
LBSC_Base::GetFieldRepetitionSize( char *szFieldAliasName, int iRepetNumber )
{
	long lRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		long lResult = crcRep.GetFieldRepetitionSize_Cache( 
					szFieldAliasName, iRepetNumber, FALSE);
		if ( lResult != -1 ) {
			return lResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetFieldRepetitionSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	(unsigned char*)szFieldAliasName;
	InPar.lFieldId			=	-1;
	InPar.liRepetNumber		=	( long )iRepetNumber;
				
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetFieldRepetitionSize(  DupInPar );
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

/**********************************/
long
LBSC_Base::GetFieldRepetitionSize( UINT uiFieldId, int iRepetNumber )
{
	long lRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		long lResult = crcRep.GetFieldRepetitionSize_Cache( 
					&uiFieldId, iRepetNumber, TRUE);
		if ( lResult != -1 ) {
			return lResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_GetFieldRepetitionSize InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szFieldAliasName	=	NULL;
	InPar.lFieldId			=	( long )uiFieldId;
	InPar.liRepetNumber		=	( long )iRepetNumber;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionSize DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetFieldRepetitionSize(  DupInPar );
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

/*******************************/
/*	06/11/95																			*/	
/*	ATENCAO: Verificar se o RPC destroi a estrutura de retorno. Se sim duplicar o vetor */
/*	de Fields da estrtura antes e retornar a copia.										*/
/*******************************/
TField *
LBSC_Base::GetFields( const LBSC_Ticket *pTicket )
{
	TSROut_GetFields	Ret;

	crcRep.SetFieldsInfo( NULL );

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

	       		Ret = RPC_Base_GetFields(  DupInPar );

				//////////////////////////////////////////////////////
				// ATENCAO: A ESTRUTURA DE RETORNO TEM CAMPOS PASSWORD
				// TEMOS QUE DECRIPTOGRAFAR !!!
				Decriptografa( Ret );	
				//////////////////////////////////////////////////////
											
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

	crcRep.SetFieldsInfo( (TField*)(Ret.psField) );
	
	return( (TField*)(Ret.psField) );
}

/**********************************/
long
LBSC_Base::GetNumRecords( const LBSC_Ticket *pTicket )
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
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetNumRecords(  DupInPar );
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

/**********************************/
long
LBSC_Base::CurrRecNum( const LBSC_Ticket *pTicket )
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
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_CurrRecNum(  DupInPar );
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

/**********************************/
int
LBSC_Base::GetIndexRecNum( const LBSC_Ticket *pTicket, BOOL bIndex )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketBOOLPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lbPar		=	( long )bIndex;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketBOOLPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Base_GetIndexRecNum(  DupInPar );
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
BYTE
LBSC_Base::CurrRecStatus( const LBSC_Ticket *pTicket )
{
	unsigned char bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (BYTE)LBSE_NETERROR );
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

	       		bRet = RPC_Base_CurrRecStatus(  DupInPar );
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

/**********************************/
int
LBSC_Base::LockRecord( const LBSC_Ticket *pTicket, BOOL bUncondit )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	// isso eh um problema so em sockets: uma nova RPC no meio de 
	// outra em andamento detona tudo. Isso pode acontecer no LockRecord
	// por causa do timer da aplicacao
	if ( LBSC_ClntNet::RPCWouldBlock() ) {
		return LBS_OK;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketBOOLPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lbPar		=	( long )bUncondit;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketBOOLPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_LockRecord(  DupInPar );
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
LBSC_Base::ReleaseRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_ReleaseRecord(  DupInPar );
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
LBSC_Base::UpdateRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_UpdateRecord(  DupInPar );
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
LBSC_Base::AppendRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_AppendRecord(  DupInPar );
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
LBSC_Base::ReadRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		if ( crcRep.IsCacheValid() ) {
			return LBS_OK;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_ReadRecord(  DupInPar );
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
LBSC_Base::DeleteRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_DeleteRecord(  DupInPar );
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
LBSC_Base::ClearRecord()
{
	int iRet;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

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

	       		iRet = ( int )RPC_Base_ClearRecord(  DupInPar);
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
LBSC_Base::SetLockTimeOut( const LBSC_Ticket *pTicket, int iNewTimeOut )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_SetLockTimeOut InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.liNewTimeOut	=	( long )iNewTimeOut;
	InPar.sTicket 		= BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetLockTimeOut DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SetLockTimeOut(  DupInPar );
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
LBSC_Base::SetReorganizeRecQuant( const LBSC_Ticket *pTicket, long lNewRecQuant )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_SetReorganizeRecQuant InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.lNewRecQuant	=	lNewRecQuant;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetReorganizeRecQuant DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SetReorganizeRecQuant(  DupInPar );
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
LBSC_Base::FirstRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// atualiza o estado do servidor e invalida as caches
	//	de repeticoes e de ocorrencias
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();
	cocOccur.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_FirstRecord(  DupInPar );
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
LBSC_Base::LastRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// atualiza o estado do servidor e invalida as caches
	//	de repeticoes e de ocorrencias
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();
	cocOccur.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_LastRecord(  DupInPar );
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
LBSC_Base::NextRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();
	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_NextRecord(  DupInPar );
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
LBSC_Base::PreviousRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();
	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_PreviousRecord(  DupInPar );
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
LBSC_Base::NthRecord( const LBSC_Ticket *pTicket, long lPos )
{
	int iRet;

	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();
	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Nth InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liPos		=	lPos;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Nth DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_NthRecord(  DupInPar );
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
LBSC_Base::CurrentRecord( const LBSC_Ticket *pTicket )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		iRet = ( int )RPC_Base_CurrentRecord(  DupInPar );
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

/*******************************/
const LBSC_Occurrence *
LBSC_Base::GetCurrentOccurrence( const LBSC_Ticket *pTicket )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetCurrentOccurrence_Cache();
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetCurrentOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
const LBSC_Occurrence *
LBSC_Base::GetFirstOccurrence( const LBSC_Ticket *pTicket )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetFirstOccurrence_Cache();
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetFirstOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
const LBSC_Occurrence *
LBSC_Base::GetLastOccurrence( const LBSC_Ticket *pTicket )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetLastOccurrence_Cache();
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetLastOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
const LBSC_Occurrence *
LBSC_Base::GetNextOccurrence( const LBSC_Ticket *pTicket )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetNextOccurrence_Cache();
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetNextOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
const LBSC_Occurrence *
LBSC_Base::GetPreviousOccurrence( const LBSC_Ticket *pTicket )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetPreviousOccurrence_Cache();
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetPreviousOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
const LBSC_Occurrence *
LBSC_Base::GetNthOccurrence( const LBSC_Ticket *pTicket, long lPos )
{
	// se estamos na lista fisica, atualizamos o registro corrente
	//	no servidor e invalidamos as caches de repeticoes e de ocorrencias
	if ( bListaFisica ) {	
		crcRep.AtualizaSvcContext();
		crcRep.InvalidaCache();
		cocOccur.InvalidaCache();
	}
	else {
		// tenta primeiro usar a cache 
		if ( cocOccur.UsandoCache() ) {
			LBSC_Occurrence *lbscoOccur = cocOccur.GetNthOccurrence_Cache( lPos );
			//	pode ser que retorne NULL mas nao seja necessario
			//	consultar o servidor: se o erro for igual a LBSE_NOMEMORY
			if ( lbscoOccur ) {
				return lbscoOccur;
			}
		}

	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Nth InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liPos		=	lPos;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_LBSC_Occurrence OutPar;
					
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Nth DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_GetNthOccurrence(  DupInPar );
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

	SetLastError( ( int )OutPar.liLastError );
	lbscOccurrence.Set( ( char * )OutPar.pszTerm, OutPar.lRec, ( int )OutPar.liField, 
						( int )OutPar.liRepetition, ( int )OutPar.liParagraph, 
						( int )OutPar.liPhrase, ( int )OutPar.liSequence);
	ClntFree ( (void *)OutPar.pszTerm ); // deleta o que vem do RPC
	
	if ( !lbscOccurrence.GetTerm() ) {	// erro...
		return NULL;
	}
	return( (const LBSC_Occurrence*)&lbscOccurrence );
}

/**********************************/
long
LBSC_Base::GetNumOccurrences( const LBSC_Ticket *pTicket )
{
	long lRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		lRet = RPC_Base_GetNumOccurrences(  DupInPar );
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
/* Checar se precisa deletar o vetor de ints da estrutura de retorno. 				*/
/* ATENCAO: A aplicacao deve deletar o vetor de inteiros retornado por este metodo 	*/
/**********************************/
int *
LBSC_Base::Search( const LBSC_Ticket *pTicket, char *szBuffer )
{
	// invalida a cache de repeticoes
	crcRep.InvalidaCache();
	// invalida a cache de ocorrencias
	cocOccur.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Search InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szBuffer	=	(unsigned char*)szBuffer;
	InPar.sTicket = BuildTickBuff( pTicket );

	TSROut_Search sOut;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Search DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_Search(  DupInPar );
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

	int *piRet = NULL;
	if( sOut.lArrayLen ){
		piRet = new int[ sOut.lArrayLen ];
		if( piRet ){
			for( int i = 0; i < sOut.lArrayLen; i++ ){
				piRet[ i ] = (int)(sOut.pLong[ i ]);
			}

			if ( sOut.lArrayLen ) {
				ClntFree( (void *)sOut.pLong );	// deleta o que vem do RPC
			}
		}
		else {	// sem memoria, considere um erro de rede; trate-o
			return ( NULL );
		}

	}

	if ( piRet ) {
		bListaFisica = FALSE;
	}
	
	return( piRet );
}

/**********************************/
int
LBSC_Base::SaveOcList( const LBSC_Ticket *pTicket, int iHandle, char *szName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.liHandle	=	( long )iHandle;
	InPar.szName	=	(unsigned char *)szName;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SaveOcList(  DupInPar );
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
LBSC_Base::SortOcList( const LBSC_Ticket *pTicket, int iHandle, char *szExpr, BOOL bCopy )
{                            
	int iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket  = BuildTickBuff( pTicket );
	InPar.liHandle	=	( long )iHandle;
	InPar.szExpr	=	(unsigned char *)szExpr;
	InPar.lbCopy	=	(long)bCopy;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SortOcList(  DupInPar );
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

	if ( iRet > 0 ) {
		bListaFisica = FALSE;
	}

	return( iRet );
} 

/**********************************/
int
LBSC_Base::EnableSecureSort( BOOL bStatus )
{                            
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lStatus	=	( long )bStatus;
				
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_EnableSecureSort(  DupInPar );
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
BOOL
LBSC_Base::SecureSortStatus()
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

	       		bRet = ( BOOL )RPC_Base_SecureSortStatus(  DupInPar);
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
LBSC_Base::LoadOcList( const LBSC_Ticket *pTicket, char *szName )
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

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szName	=	(unsigned char *)szName;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_LoadOcList(  DupInPar );
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

	if ( iRet > 0 ) {
		bListaFisica = FALSE;
	}
	else {
		if ( iRet == 0 ) {
			bListaFisica = TRUE;
		}
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::EnableOcList( const LBSC_Ticket *pTicket, int iHandle )
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

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.liHandle	=	( long )iHandle;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_EnableOcList(  DupInPar );
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

	if ( iRet == 0 ) {
		bListaFisica = (iHandle == 0);
	}
	
	return( iRet );
}

/**********************************/
char *
LBSC_Base::GetCurrentExpression( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetCurrentExpression(  DupInPar );
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

/**********************************/
char *
LBSC_Base::GetOcListExpression( const LBSC_Ticket *pTicket, int iHandle )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liHandle	=	( long )iHandle;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetOcListExpression(  DupInPar );
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

/**********************************/
long
LBSC_Base::GetOLRecNumber( const LBSC_Ticket *pTicket )
{
	long lRet;

	// tenta primeiro usar a cache
	if ( crcRep.UsandoCache() ) {
		long lResult = crcRep.GetOLRecNumber_Cache( pTicket );
		if ( lResult != -1 ) {
			return lResult;
		}
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
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

	       		lRet = RPC_Base_GetOLRecNumber(  DupInPar );
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
int
LBSC_Base::UnloadOcList( const LBSC_Ticket *pTicket, int iHandle )
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

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liHandle	=	iHandle;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_UnloadOcList(  DupInPar );
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
LBSC_Base::DeleteOcList( const LBSC_Ticket *pTicket, char *szName )
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

	TSRIn_OcList InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szName	=	(unsigned char *)szName;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OcList DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_DeleteOcList(  DupInPar );
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
LBSC_Base::DeleteOcRecords( const LBSC_Ticket *pTicket )
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

	       		iRet = ( int )RPC_Base_DeleteOcRecords(  DupInPar );
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

	if ( iRet == LBS_OK || iRet == LBSW_FAILURE ) {
		bListaFisica = TRUE;
	}
	
	return( iRet );
}

/**********************************/
const char *
LBSC_Base::GetCurrentStopWord( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetCurrentStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );

}

/**********************************/
int
LBSC_Base::DelStopWord( const LBSC_Ticket *pTicket, char *szStopWord )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_AddStopWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	= this->obj;
	InPar.szSW	= (unsigned char *)szStopWord;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddStopWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_DelStopWord(  DupInPar );
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
		return( LBSE_NETERROR);	
	}

	
	return( iRet );
}

/**********************************/
const char *
LBSC_Base::GetFirstStopWord( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetFirstStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );
	
}

/**********************************/
const char *
LBSC_Base::GetLastStopWord( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetLastStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );

}

/**********************************/
const char *
LBSC_Base::GetNextStopWord( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetNextStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );

}

/**********************************/
const char *
LBSC_Base::GetPreviousStopWord( const LBSC_Ticket *pTicket )
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

	       		szRet = (char*)RPC_Base_GetPreviousStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );

}

/**********************************/
const char *
LBSC_Base::GetNthStopWord( const LBSC_Ticket *pTicket, int iPos )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Nth InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liPos		=	( long )iPos;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Nth DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetNthStopWord(  DupInPar );
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

	strcpy( szStopWord, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szStopWord );

}

