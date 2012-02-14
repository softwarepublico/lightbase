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
/*	Métodos Stubs da classe LBSC_Field						*/
/*	Programadores: 	Renata Catao							*/
/*					Tarcio Rodrigues						*/
/*					Tricia Santos							*/
/*	Ultima alt : 22/11/95									*/
/************************************************************/

#ifndef _MMDEFS_H_
	#include	<mmdefs.h>
#endif	// _MMDEFS_H_

#ifndef __lbsrpc_h__
	#include	<lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _BASECL_H_
	#include	<basecl.h>  
#endif	// _BASECL_H_


#ifndef	_FIELDCL_H_
#include	<fieldcl.h>
#endif
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
 

//
//	Variaveis globais
//
/******
Nao eh necessario: nao estamos usando operadores
LBSC_Data	_GlobalData;
*****/


TSRControlInfo 
LBSC_Field::ObtemControlInfo()
{
	TSRControlInfo sControl;
	memset(&sControl, 0, sizeof(sControl));

	strcpy((char *)sControl.szClientName, szClientName);
	sControl.lClntTimeStamp = lClntTimeStamp;
	sControl.lSvcTimeStamp = lSvcTimeStamp;
	sControl.lObj = lSessionObj;

	return sControl;
}

 


/********************************/
char *
LBSC_Field::GetFirstGoWord()
{
	char *szRet=NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

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

	       		szRet = (char*)RPC_Field_GetFirstGoWord( DupInPar );
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

/********************************/
char *
LBSC_Field::GetNextGoWord()
{
	char *szRet = NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

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

	       		szRet = (char*)RPC_Field_GetNextGoWord(  DupInPar );
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

/********************************/
char *
LBSC_Field::GetCurrentGoWord()
{
	char *szRet = NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

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

	       		szRet = (char*)RPC_Field_GetCurrentGoWord(  DupInPar );
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

/*************************************/
char *
LBSC_Field::GetNthGoWord( int iPos )
{
	char *szRet = NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lFieldObj	=	this->obj;
	InPar.liPos		=	iPos;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Field_GetNthGoWord(  DupInPar );
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

/*************************************/
char *
LBSC_Field::SearchGoWord( char *szGoWord )
{
	char *szRet = NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_GoWord InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lFieldObj	=	this->obj;
	InPar.szGoWord	=	( unsigned char * )szGoWord;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GoWord DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Field_SearchGoWord(  DupInPar );
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

/*************************************/
long
LBSC_Field::GetNbrOfGoWord()
{
	long	lRet;

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

	       		lRet = RPC_Field_GetNbrOfGoWord(  DupInPar );
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

/*************************************/
int
LBSC_Field::Compare( LBSC_Field *plbscfField, int iSearchType )
{
	switch( iSearchType ){
	case CMPFIELDNAME:
		return( (this->szAliasName == ((const char *)plbscfField->szAliasName)) ? 0 : 1 );
	case CMPFIELDID:
		return( this->uiFieldId == plbscfField->uiFieldId ? 0 : 1 );
	default:
		return( 0 );
	}
}

/*************************************/
int
LBSC_Field::Clear()
{
	int iRet;
	
	//	invalida cache de repeticoes
	if ( pOwnerBase ) {
		pOwnerBase->InvalidaRepCache();
	}

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

	       		iRet = (int)RPC_Field_Clear(  DupInPar );
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

/*************************************/
UINT
LBSC_Field::GetId()
{
	UINT uiRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( (UINT) LBSE_NETERROR );
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

	       		uiRet = (UINT)RPC_Field_GetId(  DupInPar );
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
		return(	(UINT) LBSE_NETERROR );	
	}


	
	return( uiRet );
}

char *
LBSC_Field::GetAliasName()
{
	char *szRet = NULL;

	if( !szRet ){
		delete szRet;
		szRet = NULL;
	}

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

	       		szRet = (char*)RPC_Field_GetAliasName(  DupInPar );
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


/**************************************
Nada de Operadores

LBSC_Data&
LBSC_Field::GetDataObj( int iIndex )
{
	LBSC_Data	*pData = new LBSC_Data;

	pData->iServerIndex = iIndex;

	if( pdlDataList ){
		if( pdlDataList->Find( pData, CMPDATANUMBER ) ){
			delete pData;
			return( *(pdlDataList->Current()) );
		}
	}

	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( _GlobalData );
	}
	
	TSRIn_GetDataObj 	InPar;
	long 				lRet;

	InPar.lFieldObj	= this->obj;
	InPar.liIndex		= ( int )iIndex;

	RpcTryExcept{
		Criptografa( InPar );
	       	lRet = RPC_Field_GetDataObj(  InPar );
	}
	RpcExcept(1){
		delete pData;
		return(	_GlobalData );
	}
	RpcEndExcept

	LBSC_ClntNet::FreeRPCHandle();

	if( !pdlDataList ){
		pdlDataList = new LBSC_DataList;
		if( !pdlDataList ){
			delete pData;
			return( _GlobalData );
		}
	}

	pData->obj = lRet;
	pData->iServerIndex = iIndex;
	strcpy( pData->ServerAddr, this->ServerAddr );
	pdlDataList->Add( pData, AFTER );

	return( *(pdlDataList->Current()) );
}
**********************/

/*****************************************
Nada de Operadores

LBSC_Field&
LBSC_Field::operator = ( LBSC_Field& lbscField )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}
	
	TSRIn_Operators 	InPar;

	InPar.lFieldObj	= this->obj;
	InPar.lField		= lbscField.obj;

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Field_Operator_ , Equal( InPar );
	}
	RpcExcept(1){
		return(	*this );
	}
	RpcEndExcept

	LBSC_ClntNet::FreeRPCHandle();
	return( *this );
}
*******************/

/*****************************************
Nada de Operadores

int
LBSC_Field::operator == ( LBSC_Field& lbscField )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
	
	TSRIn_Operators 	InPar;
	int 	iRet;

	InPar.lFieldObj	= this->obj;
	InPar.lField		= lbscField.obj;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Field_Operator_ , EqualEqual( InPar );
	}
	RpcExcept(1){
		return(	LBSE_NETERROR );
	}
	RpcEndExcept

	LBSC_ClntNet::FreeRPCHandle();

	return( iRet );
}
***************/

/*****************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( long lPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return (*this);
	}
	
	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &lPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_LONG;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return(*this);
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return(*this);
}
****************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( double dPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( double );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &dPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DOUBLE;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
**************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( char *szPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = strlen( szPar ) + 1;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	strcpy( (char*)InPar.Rep, szPar );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_STRING;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
*******************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( void *vPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	// Obter o tamanho
	long lRet;
	RpcTryExcept{
	       	lRet = RPC_Field_GetSize(  this->obj );
	}
	RpcExcept(1){
		return( *this );
	}
	RpcEndExcept

	int iRet;
		Criptografa( InPar );
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = lRet;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, vPar, lRet );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_VOID;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;		
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
******************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( C_Date &cdDate )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}
	
	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	long lAux = (long)( cdDate.Hash() );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &lAux, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DATE;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
****************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( C_Time &ctTime )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	long lAux = (long)( ctTime.Seconds() );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_TIME;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	return( *this );
}
**************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( LBSC_Binary &cbBinary )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;

	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = ( 2 * sizeof( int ) ) + cbBinary.iLen + 1;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	sprintf( (char*)InPar.Rep, "%d%d%s", cbBinary.iFormat, cbBinary.iLen, cbBinary.pvBuffer );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BINARY;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
**************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( LBSC_Reference &crReference )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
			
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( int ) + MAXPATH + 1;
	InPar.Rep = new unsigned char[ InPar.lTam ];
	if( !InPar.Rep ){
		return( *this );
	}
	sprintf( (char*)InPar.Rep, "%d%s", crReference.iFormat, crReference.szFileName );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_REFERENCE;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
******************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( BYTE bPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}
					   	
	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &bPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BYTE;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
*******************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( short sPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}
	
	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( short );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &sPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_SHORT;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
*****************/

/*************************************
Nada de Operadores

LBSC_Field& 
LBSC_Field::operator << ( float fPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( *this );
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( float );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return( *this );
	}
	memcpy( InPar.Rep, &fPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_FLOAT;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetition( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return( *this );
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return( *this );
}
******************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( long lPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &lPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_LONG;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
*****************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( double dPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( double );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &dPar, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DOUBLE;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
**************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( char *szPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}
			
	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = strlen( szPar ) + 1;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	strcpy( (char*)InPar.Rep, szPar );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_STRING;

	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
*****************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( void *pvBuffer )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}
	
	long				lSize;
	
	RpcTryExcept{
	       	lSize = RPC_Field_GetSize(  this->obj );
	}
	RpcExcept(1){
		return;
	}
	RpcEndExcept
	
	int iRet;
		Criptografa( InPar );
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base 		= this->lBaseObj;
	InPar.lTam 		= lSize;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, pvBuffer, InPar.lTam );
	InPar.lFieldId	= ( long )uiFieldId;
	InPar.lIndex		= 0;
	InPar.sMethod		= RPC_BASE_PUTFIELDREPETITIONBYINDEX_VOID;

	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
******************/

/*************************************
Nada de Operadores


void
LBSC_Field::operator = ( C_Date & cdDate )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	long lAux = (long)( cdDate.Hash() );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &lAux, InPar.lTam );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DATE;

	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
**********************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( C_Time & ctTime )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( long );
	long lAux = (long)( ctTime.Seconds() );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &lAux, InPar.lTam );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_TIME;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
**********************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( LBSC_Binary & cbBinary )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = ( 2 * sizeof( int ) ) + cbBinary.iLen + 1;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	sprintf( (char*)InPar.Rep, "%d%d%s", cbBinary.iFormat, cbBinary.iLen, cbBinary.pvBuffer );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BINARY;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
**************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( LBSC_Reference & crReference )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( int ) + MAXPATH + 1;
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	sprintf( (char*)InPar.Rep, "%d%s", crReference.iFormat, crReference.szFileName );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_REFERENCE;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
********************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( BYTE bPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &bPar, InPar.lTam );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BYTE;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
********************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( short sPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( short );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &sPar, InPar.lTam );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_SHORT;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
***********************/

/*************************************
Nada de Operadores

void
LBSC_Field::operator = ( float fPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;
	TSRIn_PutFieldRepetition		InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.Base = this->lBaseObj;
	InPar.lTam = sizeof( float );
	InPar.Rep = new unsigned char[InPar.lTam];
	if( !InPar.Rep ){
		return;
	}
	memcpy( InPar.Rep, &fPar, InPar.lTam );
	InPar.lFieldId = ( long )uiFieldId;
	InPar.lIndex = 0;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_FLOAT;
	
	RpcTryExcept{
		Criptografa( InPar );
	       	iRet = (int)RPC_Base_PutFieldRepetitionByIndex( InPar );
	}
	RpcExcept(1){
		delete InPar.Rep;
		return;
	}
	RpcEndExcept

	if( iRet != LBS_OK ){
	}

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.Rep;
	return;
}
********************/

/*************************************
Nada de Operadores

LBSC_Data&
LBSC_Field::operator [] ( int iIndex )
{
	return( GetDataObj( iIndex ) );
}
***************************/
