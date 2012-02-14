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

#ifndef	_DUPLICATE_H_
	#include <duplicate.h>
#endif	// _DUPLICATE_H_
 
#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_


/***********************************************************/
/***********************************************************/
/************** GetFieldRepetitionByVal ********************/
/***********************************************************/
/***********************************************************/

int
LBSC_Base::GetFieldRepetitionByVal( char *szField, char *szRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = strlen( szRep ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)(InPar.Rep), szRep );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	

	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, char *szRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = strlen( szRep ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)(InPar.Rep), szRep );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}


/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, void *pvRep, long lSize, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[lSize];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRep, lSize );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, void *pvRep, long lSize, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[lSize];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRep, lSize );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, long *plRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;

	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, plRep, sizeof( long ) );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_LONG;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, long *plRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, plRep, sizeof( long ) );
	InPar.lFieldId =(long) uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, double *pdRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pdRep, sizeof( double ) );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, double *pdRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pdRep, sizeof( double ) );
	InPar.lFieldId = (long) uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, C_Date *pcdRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long lDate = (*pcdRep).Hash();
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &lDate, sizeof( long ) );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, C_Date *pcdRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long lDate = (*pcdRep).Hash();
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &lDate, sizeof( long ) );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, C_Time *pctRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long lTime = (*pctRep).Seconds();	
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &lTime, sizeof( long ) );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, C_Time *pctRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long lTime = (*pctRep).Seconds();	
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &lTime, sizeof( long ) );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
	  	return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, LBSC_Binary *pbRep, BOOL bStart )
{
	int 				iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal	InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;

	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRep->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRep->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRep->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRep->pvBuffer), pbRep->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRep->iLen;

	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
	  	return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, LBSC_Binary *pbRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal	InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;

	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRep->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRep->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRep->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRep->pvBuffer), pbRep->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRep->iLen;

	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, LBSC_Reference *prRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = (prRep && prRep->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRep->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRep, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, LBSC_Reference *prRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = (prRep && prRep->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRep->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRep, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, BYTE *pbRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pbRep, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, BYTE *pbRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pbRep, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, short *psRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( short );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, psRep, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, short *psRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( short );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, psRep, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, float *pfRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pfRep, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, float *pfRep, BOOL bStart )
{
	int iRet = LBSE_NETERROR;
	TSRIn_GetFieldRepetitionByVal		InPar;


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( float );
	InPar.Rep =(unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pfRep, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.bStart = bStart;
	InPar.sMethod = RPC_BASE_GETFIELDREPETITIONBYVAL_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetFieldRepetitionByVal		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_GetFieldRepetitionByVal(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/***********************************************************/
/***********************************************************/
/**************** PutFieldRepetition ***********************/
/***********************************************************/
/***********************************************************/

int
LBSC_Base::PutFieldRepetition( char *szField, char *szRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = strlen( szRepetition ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szRepetition );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, char *szRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = strlen( szRepetition ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szRepetition );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, void *pvRepetition, long lSize )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRepetition, lSize );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, void *pvRepetition, long lSize )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRepetition, lSize );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, long plRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &plRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, long plRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &plRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, double pdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, double pdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, C_Date pcdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long) (pcdRepetition.Hash());
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
	  	return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, C_Date pcdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long l = (long)( pcdRepetition.Hash() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, C_Time pctRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, C_Time pctRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, LBSC_Binary *pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;

	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;

	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, LBSC_Binary *pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;


	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;

	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BINARY;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, LBSC_Reference *prRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, LBSC_Reference *prRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, BYTE pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId,  BYTE pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, short psRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( short );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId,  short psRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( short );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_SHORT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( char *szField, float pfRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
	   	return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId,  float pfRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITION_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetition(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );

	}

	
	return( iRet );
}


/***********************************************************/
/***********************************************************/
/************** PutFieldRepetitionByIndex ******************/
/***********************************************************/
/***********************************************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, char *szRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = strlen( szRepetition ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szRepetition );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, char *szRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = strlen( szRepetition ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szRepetition );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_STRING;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, void *pvRepetition, long lSize, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, void *pvRepetition, long lSize, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, long plRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &plRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, long lRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &lRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, double pdRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, double pdRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, C_Date pcdRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long)( pcdRepetition.Hash() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, C_Date pcdRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long l = (long)( pcdRepetition.Hash() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, C_Time pctRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, C_Time pctRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, LBSC_Binary *pbRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
				
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;

	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;

	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BINARY;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, LBSC_Binary *pbRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;


	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;

	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BINARY;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, LBSC_Reference *prRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, LBSC_Reference *prRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_REFERENCE;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, BYTE pbRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, BYTE pbRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
	 	return(	LBSE_NETERROR );

	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, short int psRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( short int );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_SHORT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, short int psRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( short int );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_SHORT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, float pfRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

/**********************************/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, float pfRepetition, int iIndex )
{
	int iRet = LBSE_NETERROR;
	TSRIn_PutFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();


	unsigned long ulExceptionCode = 0;
	memset( &InPar, 0, sizeof( InPar ) );
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.lIndex = (long)iIndex;
	InPar.sMethod = RPC_BASE_PUTFIELDREPETITIONBYINDEX_FLOAT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_PutFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_PutFieldRepetitionByIndex(  DupInPar );
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
	delete InPar.Rep;	// alocado para a RPC

	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	
	}

	
	return( iRet );
}

