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
// Module: CLSESS.CPP
// Description:
//
//	RPC client stub for SESSION class
//
// Programmers:	Renata Catão
//				Tárcio Rodrigues Bezerra
//				Tricia Souto
//
// Last update: 21/11/95
//

#ifndef _SESSCL_H_
	#include	<SESSCL.H>  
#endif	// _SESSCL_H_

#ifndef _BASECL_H_
	#include	<basecl.h>
#endif	// _BASECL_H_

#ifndef _MMDEFS_H_
	#include 	<MMDEFS.H>
#endif	// _MMDEFS_H_

#ifndef __lbsrpc_h__
	#include	<lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _LBSERROR_H_
	#include	<lbserror.h>
#endif	// _LBSERROR_H_

#ifndef _BUFFERCL_H_
	#include	<buffercl.h>
#endif	// _BUFFERCL_H_

#ifndef _ALLBASEL_H_
	#include    <allbasel.h>
#endif	// _ALLBASEL_H_

#ifndef _LBSTYPES_H_
	#include	<lbstypes.h>
#endif	// _LBSTYPES_H_


#ifndef	_DEFMAC_H_
#include <defmac.h>
#endif

#ifndef _FBUFF_H
#include    <fbuff.h>
#endif

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_

#ifndef _STUBCRIT_H_
	#include <stubcrit.h>
#endif	// _STUBCRIT_H_


#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_

#ifndef	_DUPLICATE_H_
	#include <duplicate.h>
#endif	// _DUPLICATE_H_
 

/*************************************/

LBSC_Session::LBSC_Session()
{
	szBuffer = NULL;
	pTicket = NULL;
	obj = NULL;
	strcpy( ServerAddr,"" );
}

 
LBSC_Session*
LBSC_Session::New( const char *szMachine )
{
	LBSC_Session *pcsSession = new LBSC_Session;
	if ( !pcsSession ) {	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}
		  

	unsigned long ulExceptionCode = 0;
	if( pcsSession ){
		if( !LBSC_ClntNet::GetRPCHandle( (char *)szMachine) ){
			delete pcsSession;
			return( NULL );
		}
		
		boolean bNetError = TRUE;
		boolean bRetry = FALSE;
		TSRGenericObj	OutPar;

		TSRControlInfo InPar = pcsSession->ObtemControlInfo();

		do {
			TSRControlInfo DupInPar;
			RpcTryExcept {
				::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

				TSRClntInitInfo TInit = pcsSession->ObtemInitInfo();

				RPC_SvcInitContext( TInit );

				OutPar = RPC_Session_New( DupInPar );

				if( !OutPar.lObj ){
					delete pcsSession;
					pcsSession = NULL;
				}
				else {	// nova sessao criada
					LBSC_ClntNet::IncOpenSessions( (char *)szMachine );	// incrementa o numero de sessoes com esse servidor

					pcsSession->lSessionObj = pcsSession->obj = OutPar.lObj;
					pcsSession->SetTimeStamp( OutPar.sCtrlInfo.lSvcTimeStamp );
					strcpy( pcsSession->ServerAddr, szMachine );
				}

				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );

			}
			RpcExcept(1) {
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			}
			RpcEndExcept
		} while ( bRetry );

		LBSC_ClntNet::FreeRPCHandle();

		if ( bNetError ) {
			LBSC_ClntNet::TrataErroRPC( ( char * )szMachine , ulExceptionCode);
			delete pcsSession;
			pcsSession = NULL;
		}
			
	}
	return( pcsSession );
}


/*************************************/
void		
LBSC_Session::Delete( LBSC_Session *pcsSession )
{
	if( pcsSession ){
		if( pcsSession->szBuffer ){
			delete pcsSession->szBuffer;
			pcsSession->szBuffer = NULL;
		}
		if( pcsSession->pTicket ){
			delete (LBSC_Ticket*)pcsSession->pTicket;
			pcsSession->pTicket = NULL;
		}

		unsigned long ulExceptionCode = 0;
		if ( !LBSC_ClntNet::GetRPCHandle( pcsSession->ServerAddr) ) {
			delete pcsSession;
			return;
		}

		TSRGenericObj InPar;
		memset( &InPar, 0, sizeof( InPar ));

		InPar.sCtrlInfo = pcsSession->ObtemControlInfo();
		InPar.lObj = pcsSession->obj;

		boolean bNetError = TRUE;
		boolean bRetry = FALSE;

		do {
			TSRGenericObj DupInPar;
			RpcTryExcept {
				::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

				RPC_Session_Delete( DupInPar );

				LBSC_ClntNet::DecOpenSessions( pcsSession->ServerAddr );	// decrementa o numero de sessoes com esse servidor

				if ( LBSC_ClntNet::OpenSessions( pcsSession->ServerAddr ) <= 0 ) {
					// liberou todas as sessoes abertas nesse servidor;
					// libera o contexto tambem.
					TSRClntInitInfo TInit = pcsSession->ObtemInitInfo();

					RPC_SvcEndContext( TInit ); // encerra um contexto remoto
				}

				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
			}
			RpcExcept(1) {
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			}
			RpcEndExcept
		} while ( bRetry );

		LBSC_ClntNet::FreeRPCHandle();
		if ( bNetError ) {
			LBSC_ClntNet::TrataErroRPC( pcsSession->ServerAddr , ulExceptionCode);
		}
		
		delete pcsSession;
	}
}

/*************************************/
int
LBSC_Session::CreateDefaultUserBase( char *szServer, char *szPassword, char *szMaintPassword, 
			char *szUserName, char *szUserPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServer ) ){
		return( LBSE_NETERROR);
	}  

	TSRIn_CreateDefaultUserBase InPar;
	memset( &InPar, 0, sizeof( InPar ));

	InPar.szPassword		= (unsigned char*)szPassword;
	InPar.szMaintPassword	= (unsigned char*)szMaintPassword;
	InPar.szUserName		= (unsigned char*)szUserName;

	if ( szUserPassword ) {
		strncpy( (char *)InPar.szUserPassword, szUserPassword, PASSWORDSIZE );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateDefaultUserBase DupInPar;
		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			iRet = (int)RPC_Session_CreateDefaultUserBase(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( szServer , ulExceptionCode);
		return( LBSE_NETERROR );
	}

	return( iRet );
}


/*************************************/
const LBSC_Ticket*		
LBSC_Session::Login( TNetInfo &SInParam )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr) ){
		return( NULL );
	}
		
	TSRIn_Login InPar;
	TSRTicket sRet;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;
	InPar.psLoginInf	= (TSRNetInfo *) &SInParam; 


	if( pTicket ){
		delete (LBSC_Ticket*)pTicket;
		pTicket = NULL;
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Login DupInPar;
		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

			sRet = RPC_Session_Login( DupInPar );
			pTicket = BuildTicket( sRet );
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

	ClntFree( (void *)sRet.szTickBuff );  // dealoca o que veio do RPC
	return( pTicket );
}

/*************************************/
int			
LBSC_Session::Logout()
{
	int	status;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
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

	       		status = RPC_Session_Logout( DupInPar );
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

	return( status );

}

/*************************************/
int			
LBSC_Session::CreateUDB( const LBSC_Ticket *pctTicket, char *szBaseName, char *szPassword, char *szMaintPassword )
{
	int	status;


	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj			= this->obj;
	InPar.sTicket				= BuildTickBuff( pctTicket );
	InPar.szBaseName			= (unsigned char *) szBaseName;
	InPar.szBasePassword		= (unsigned char *) szPassword;
	InPar.szMaintenancePassword	= (unsigned char *) szMaintPassword;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		status = RPC_Session_CreateUDB(  DupInPar );
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

	return( status );

}

/*************************************/
int			
LBSC_Session::CloseBase( const LBSC_Ticket *pctTicket, LBSC_Base *pcbBase )
{
	int	status;

	//	invalida as caches de base
	if ( pcbBase ) {
		pcbBase->InvalidaRepCache();
		pcbBase->InvalidaACLCache();
		pcbBase->InvalidaFieldSlotCache();
		pcbBase->InvalidaOccurrCache();

		strcpy(pcbBase->szBaseName, "");
		strcpy(pcbBase->szNavKey, "");
	}
	else {
		return LBSE_BASENOTFOUND;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;  
	InPar.lBaseObj	= pcbBase->obj;
	InPar.sTicket = BuildTickBuff( pctTicket );
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		status = RPC_Session_CloseBase(  DupInPar );
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
	delete pcbBase;
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	return( status );
}

/*************************************/
int			
LBSC_Session::DeleteBase( const LBSC_Ticket *pctTicket, char *szBaseName )
{
	int	status;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}
	
	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;  
	InPar.sTicket = BuildTickBuff( pctTicket );
	InPar.szBaseName = (unsigned char *) szBaseName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

			 status = RPC_Session_DeleteBase(  DupInPar );
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

	return( status );
}

/*************************************/
int
LBSC_Session::AddUser( const LBSC_Ticket *pTicket, char *szUDBName, TUDBRecord *ptUDBRecord )
{
	int		status;

	if( !ptUDBRecord || !szUDBName ){
		return( LBSE_BADARG );
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_AddDelGroupUser	InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_AddDelGroupUser));
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szUDBName		=	(unsigned char *) szUDBName;

	C_Buffer	*pBuffer = NULL;

	for( int i = 0; !ptUDBRecord[i].IsZero(); i++ );
	int iArrayLen = i + 1;

	if( MakeBufferFromArray( ptUDBRecord, &pBuffer, iArrayLen ) == LBS_OK ){
			InPar.lTam = pBuffer->MyBufLen();
			InPar.szBuffer = (unsigned char*)pBuffer->MyBuffer();
	} else {
			InPar.lTam = 0;
	}
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddDelGroupUser	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		status = RPC_Session_AddUser(  DupInPar );
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
	delete pBuffer;	// alocado para a RPC

	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	return( status );
}


/*************************************/
int
LBSC_Session::OpenBase( const LBSC_Ticket *pctTicket, char *szBaseName, char *szBasePassword,
			BOOL bExclusive, BOOL bReadOnly, BOOL bMaintenance, LBSC_Base **plbscReturnBase )
	
{
    TSROut_OpenBase sRet;

	if( !( (*plbscReturnBase) = new LBSC_Base ) ){
		// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	// guarda o nome da base
	strcpy((*plbscReturnBase)->szBaseName, szBaseName);

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_OpenBase InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_OpenBase));
	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		=	this->obj;	
	InPar.sTicket = BuildTickBuff( pctTicket );
	InPar.szBaseName		=	( unsigned char * ) szBaseName;
	InPar.szBasePassword	=	( unsigned char * ) szBasePassword;
	InPar.bExclusive		=	bExclusive;
	InPar.bReadOnly			=	bReadOnly;
	InPar.bMaintenance		=	bMaintenance;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OpenBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Session_OpenBase(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		if( *plbscReturnBase ){
			delete (*plbscReturnBase);
			(*plbscReturnBase) = NULL;
		}
		return(	LBSE_NETERROR );
	}

	if( sRet.lBaseObj == 0 ){
		delete (*plbscReturnBase);
		(*plbscReturnBase) = NULL;
	} else {
		(*plbscReturnBase)->obj = sRet.lBaseObj;
		(*plbscReturnBase)->pTicket = pctTicket;
		(*plbscReturnBase)->lSessionObj = obj;
		(*plbscReturnBase)->SetTimeStamp( (ObtemControlInfo()).lSvcTimeStamp );
		strcpy((*plbscReturnBase)->ServerAddr, this->ServerAddr );
	}


	return( (int) sRet.lRet );
}

/*************************************/
int
LBSC_Session::AddGroupToUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szGroups )
{
	int		status;

	if( !szGroups || !szUserName || !szUDBName ){
		return( LBSE_BADARG );
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

 	TSRIn_AddDelGroupUser InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_AddDelGroupUser ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj; 
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szUDBName		=	( unsigned char * ) szUDBName;
	InPar.szUserName	=	( unsigned char * ) szUserName;
	InPar.szGroups		=	( unsigned char * ) szGroups;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddDelGroupUser DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		status = RPC_Session_AddGroupToUser(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );
	}

	return( status );
}

/**********************************/
BOOL
LBSC_Session::IsLogged()
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

	       		bRet = RPC_Session_IsLogged( DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	FALSE );		
	}

	
	return( bRet );
}

/*************************************/
char *
LBSC_Session::WhatServers()
{
	// nao precisa de sessao remota; 
	return( (char*) LBSC_Session::Broadcast( 0, NULL, WHATS, NULL ) );	
}

/*************************************/

char *
LBSC_Session::WhatServersForUser( char *szUserName )
{
	return( (char*) LBSC_Session::Broadcast( 0, this, WHATSFORUSER, szUserName ) );
}

/*************************************/
int
LBSC_Session::CreateBase( const LBSC_Ticket *pTicket, char *szBaseName, char *szLongBaseName, 
			char *szBasePassword, char* szMaintenancePassword, BYTE bBaseType, 
			BOOL bIsCrypto,	char *szUserBaseName, TField *ptfField, int iSlotNum,
			int iCountNum, int iMaxKeySize )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj				=	this->obj;
	InPar.sTicket					=	BuildTickBuff( pTicket );
	InPar.szBaseName				=	( unsigned char	* ) szBaseName;
	InPar.szLongBaseName				=	( unsigned char	* ) szLongBaseName;
	InPar.szBasePassword			=	( unsigned char	* ) szBasePassword;
	InPar.szMaintenancePassword		=	( unsigned char	* ) szMaintenancePassword;
	InPar.bBaseType					=	bBaseType;	
	InPar.bIsCrypto					=	bIsCrypto;
	InPar.szUserBaseName			=	( unsigned char	* ) szUserBaseName;
	InPar.lMaxKeySize				=	( long ) iMaxKeySize;
		
	C_Buffer	*pBuffer = NULL;

	for( int i = 0; !ptfField[i].IsZero(); i++ );
	int iArrayLen = i + 1;

	if( MakeBufferFromArray( ptfField, &pBuffer, iArrayLen ) == LBS_OK ){
			InPar.lTam = pBuffer->MyBufLen();
			InPar.szBuffer = (unsigned char*)pBuffer->MyBuffer();
	} else {
			InPar.lTam = 0;
	}
			
	InPar.lSlotNum	=	( long )iSlotNum;
	InPar.lCountNum	=	( long )iCountNum;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
				::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_CreateBase(  DupInPar );
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
	delete pBuffer;	// alocado para a RPC

	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return( LBSE_NETERROR);		
	}

	return( iRet );
}

/*************************************/
int
LBSC_Session::CreateBase( const LBSC_Ticket *pTicket, char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szFileName	=	(unsigned char *) szFileName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_CreateBaseDef(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return( LBSE_NETERROR);		
	}

	
	return( iRet );
}

/*************************************/
const char *
LBSC_Session::GetUserName()
{
	char	*szRet;

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

	       		szRet = (char *)( RPC_Session_GetUserName(  DupInPar ) );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	NULL );		
	}

	if ( !szRet ) {
		return NULL;
	}
	
	strcpy( szUserName, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szUserName );
}


/*************************************/
int
LBSC_Session::ReorganizeBase( const LBSC_Ticket *pTicket, LBSC_Base *pBase )
{
	int iRet;

	//	invalida as caches de base
	if ( pBase ) {
		pBase->InvalidaRepCache();
		pBase->InvalidaACLCache();
		pBase->InvalidaFieldSlotCache();
		pBase->InvalidaOccurrCache();
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ReorgBase InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_ReorgBase));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.lBaseObj = pBase->obj;    

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ReorgBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_ReorganizeBase(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
int
LBSC_Session::TicketIsOk( const LBSC_Ticket *pTicket )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_GetGroups InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_GetGroups));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetGroups DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_TicketIsOk(  DupInPar);
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
char *
LBSC_Session::WhatUDBLogged()
{
	char	*szRet;

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

	       		szRet = (char *) RPC_Session_WhatUDBLogged( DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
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
LBSC_Session::WhatUDB( char *szDataBaseName, const char *szServer )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_What InPar ;
	memset( (void*) &InPar, 0, sizeof(TSRIn_What));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.szDataBaseName = (unsigned char *) szDataBaseName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_What DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char *) RPC_Session_WhatUDB(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
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
LBSC_Session::GetGroups( const LBSC_Ticket *pTicket, char *szUserName, BOOL bMem )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}
	
	TSRIn_GetGroups InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_GetGroups));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szUserName = (unsigned char *) szUserName;
	InPar.bMem = bMem;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetGroups DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char *) RPC_Session_GetGroups(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	NULL );		
	}

	

	if ( szRet ){
		char *szRet2 = StrDup( szRet );
		ClntFree( szRet );	// detona memoria do RPC
		return ( szRet2 );
	} 

	return NULL;
}


/************************************/
int
LBSC_Session::DelUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUsers )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_AddDelGroupUser InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_AddDelGroupUser));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szUDBName = (unsigned char *) szUDBName;
	InPar.szUserName = (unsigned char *) szUsers;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddDelGroupUser DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_DelUser(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/**************************************/
int
LBSC_Session::UpdateUserPassword( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szUDBName = (unsigned char*)szUDBName;
	InPar.szUserName= (unsigned char*)szUserName;

	if ( szOldPassword ) {
		strncpy( (char *)InPar.szOldPassword, szOldPassword, PASSWORDSIZE );
	}
	if ( szNewPassword ) {
		strncpy( (char *)InPar.szNewPassword, szNewPassword, PASSWORDSIZE );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_UpdateUserPassword( DupInPar);
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/**************************************/
int
LBSC_Session::UpdateUserPassword( char *szServer, char *szUDBName, char *szUserName, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServer ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.szUDBName = (unsigned char*)szUDBName;
	InPar.szUserName= (unsigned char*)szUserName;

	if ( szOldPassword ) {
		strncpy( (char *)InPar.szOldPassword, szOldPassword, PASSWORDSIZE );
	}
	if ( szNewPassword ) {
		strncpy( (char *)InPar.szNewPassword, szNewPassword, PASSWORDSIZE );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_UpdateUserPassword( DupInPar);
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/***********************************/
int
LBSC_Session::UpdateUserType( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, long lNewType )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*)szUDBName;
	InPar.szUserName	= (unsigned char*)szUserName;
	InPar.lNewType 		= lNewType;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_UpdateUserType(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/************************************/
long
LBSC_Session::GetUserType( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	long lRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*)szUDBName;
	InPar.szUserName	= (unsigned char*)szUserName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Session_GetUserType(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( lRet );
}

/************************************/
int
LBSC_Session::UpdateUserDescription( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewDescrip )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*) szUDBName;
	InPar.szUserName	= (unsigned char*) szUserName;
	InPar.szNewDescrip 	= (unsigned char*) szNewDescrip;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_UpdateUserDescription(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
char *
LBSC_Session::GetUserDescription( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*)szUDBName;
	InPar.szUserName	= (unsigned char*)szUserName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*) RPC_Session_GetUserDescription( DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
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
int
LBSC_Session::DelGroupFromUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szGroups )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
 
 	TSRIn_AddDelGroupUser InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_AddDelGroupUser));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*)szUDBName;
	InPar.szUserName 	= (unsigned char*)szUserName;
	InPar.szGroups 		= (unsigned char*)szGroups;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_AddDelGroupUser DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_DelGroupFromUser(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
char *
LBSC_Session::GetUsers( const LBSC_Ticket *pTicket, char *szUDBName )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_GetGroups InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_GetGroups));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*)szUDBName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetGroups DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*) RPC_Session_GetUsers(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
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
int
LBSC_Session::GetUsersData( const LBSC_Ticket *pTicket, char *szUDBName, TUDBRecord **ppUDBReturn, char ***pppGrpReturn )
{
	TSROut_GetUsersData sRet;

	unsigned long ulExceptionCode = 0;
 	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_UserGenInfos InPar; 
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj 	= this->obj;
	InPar.sTicket 		= BuildTickBuff( pTicket );
	InPar.szUDBName 	= (unsigned char*) szUDBName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
 		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Session_GetUsersData(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}
	
	*ppUDBReturn = NULL;
	C_Buffer	*cBuffer = NULL;
	cBuffer = new C_Buffer( sRet.lTam - sizeof( int ) );
	if( !cBuffer ){	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	cBuffer->PutData( (void*)( sRet.szBuffer + sizeof( int) ) , ( sRet.lTam - sizeof( int ) ) );
	cBuffer->Rewind();
	*ppUDBReturn = MakeRecordArray( *cBuffer );
	delete cBuffer;
	ClntFree( (void *)sRet.szBuffer );  // dealoca o que veio do RPC

	*pppGrpReturn = NULL;
	C_Buffer	*cGrpBuf = NULL;
	cGrpBuf = new C_Buffer( sRet.lGrpTam - sizeof( int ) );
	if( !cGrpBuf ){	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	cGrpBuf->PutData( (void*)( sRet.szGrpBuf + sizeof( int) ) , ( sRet.lGrpTam - sizeof( int ) ) );
	cGrpBuf->Rewind();
	*pppGrpReturn = MakeStringArray( *cGrpBuf, ( int )sRet.lRet-1 );
	delete cGrpBuf;
	ClntFree( (void *)sRet.szGrpBuf );  // dealoca o que veio do RPC
	
	return( sRet.lRet );

}

/*************************************/
LBSC_AllBasesList *        // $$$ lista com: nome-da-base + servidor + BU
LBSC_Session::WhatBases( int iFilterLevel )
{
	// nao precisa de sessao remota; 
    return( (LBSC_AllBasesList*) LBSC_Session::Broadcast( iFilterLevel, NULL, WHATB, NULL ) );
}


/*************************************/
LBSC_AllBasesList *
LBSC_Session::WhatBasesForUser( int iFilterLevel, char *szUserName )
{
    return( (LBSC_AllBasesList*) LBSC_Session::Broadcast( iFilterLevel, this, WHATBFORUSER, szUserName ) );
}

/*************************************/

LBSC_ServerBasesList *
LBSC_Session::WhatBasesOnServer( int iFilterLevel, const char *tmaServer, char *szUDB, char *szUserName )
{
	TSROut_WhatBases	sOut;
	C_Buffer			*pcbRet = NULL;
	TSRIn_What		InPar;
	

	unsigned long ulExceptionCode = 0;
	memset( (void*) &InPar, 0, sizeof(InPar));
	if( !LBSC_ClntNet::GetRPCHandle( (char *)tmaServer ) ){
		return( NULL );
	}

	InPar.lFilterLevel = iFilterLevel;
	InPar.szUDB = (unsigned char *)szUDB;
	InPar.szUserName = (unsigned char*)szUserName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_What		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			sOut = RPC_Session_WhatBasesOnServer( DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( (char *)tmaServer  , ulExceptionCode);
		return(	NULL );		
	}

	if ( !sOut.lTam ) {
		return ( NULL );
	}

	// descomprime o que veio do servidor
	unsigned char *szAux=NULL;
	long lTamDecomp = CCompact::DeCompress( sOut.szBuffer, 
					&szAux, sOut.lTam );
	ClntFree( (void *)sOut.szBuffer );  // dealoca o que veio do RPC

	if ( !lTamDecomp ) {
		return ( NULL );
	}

	LBSC_ServerBasesList	*pList = NULL;
	pcbRet = new C_Buffer( lTamDecomp - sizeof(int) ); // pula o int do cbuffer; Vladimir Catao 29/01/96
	if( !pcbRet ){	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	pcbRet->PutData( (void*) (szAux + sizeof(int)), lTamDecomp - sizeof(int)); // pula o int do cbuffer; Vladimir Catao 29/01/96
	pcbRet->Rewind();
	pList = MakeServerBasesList( *pcbRet );	   
	delete pcbRet;
	delete szAux;

	return( pList );
}

/*************************************/
LBSC_ServerBasesList *
LBSC_Session::WhatBasesForUserOnServer( int iFilterLevel, TMachineAddr tmaServer, char *szUserName )
{
	TSROut_WhatBases		sOut;
	LBSC_ServerBasesList	*pList = NULL;
	C_Buffer				*pcbRet = NULL;

	TSRIn_What InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_What));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;
	InPar.lFilterLevel	= iFilterLevel;
	InPar.szUserName	= (unsigned char*)szUserName;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)tmaServer ) ){
		return( NULL );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_What DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );


	       		sOut = RPC_Session_WhatBasesForUserOnServer(  DupInPar );	
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
		LBSC_ClntNet::TrataErroRPC( (char *)tmaServer  , ulExceptionCode);
		return(	NULL );		
	}

	pcbRet = new C_Buffer( sOut.lTam - sizeof( int ));
	if( !pcbRet ){	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	pcbRet->PutData( (void*) (sOut.szBuffer+sizeof( int )), sOut.lTam - sizeof( int ) );
	pcbRet->Rewind();
	pList = MakeServerBasesList( *pcbRet );
	delete pcbRet;
	ClntFree( (void *)sOut.szBuffer );  // dealoca o que veio do RPC

	return( pList );
}

/*************************************/
int
LBSC_Session::Export( const LBSC_Ticket *pctTicket, LBSC_ExportBaseList *peExportBaseList,
			char *szImportPsw, char *szFullExportFileName, BOOL bChangeOwnerName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_Export InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		=	this->obj; 
	InPar.sTicket			=	BuildTickBuff( pctTicket );

	C_Buffer		*pExportBuffer = NULL;

	if( MakeBufferFromList( peExportBaseList, &pExportBuffer ) == LBS_OK ){
		InPar.lExportTam = pExportBuffer->MyBufLen();
		InPar.szExportBuffer = (unsigned char*)pExportBuffer->MyBuffer();
	}
	else {
		InPar.lExportTam = 0;
	}

	InPar.szImportPsw			=	(unsigned char *)szImportPsw; 
	InPar.szFullExportFileName	=	(unsigned char *)szFullExportFileName;  
	InPar.lbChangeOwnerName		=	( long )bChangeOwnerName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Export DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

       		iRet = (int)RPC_Session_Export(  DupInPar );
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
	delete pExportBuffer;	// alocado para a RPC

	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	return( iRet );
}

	
/*************************************/
int
LBSC_Session::Import( const LBSC_Ticket *pTicket, char *szNewOwnerName, char *szNewBasePassword,
			char *szNewMaintenanceBasePassword,
			char *szImportPsw, char *szFullImportFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_Import	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj					=	this->obj;
	InPar.sTicket						=	BuildTickBuff( pTicket );
	InPar.szNewOwnerName				=	(unsigned char*)szNewOwnerName;
	InPar.szNewBasePassword				=	(unsigned char*)szNewBasePassword;
	InPar.szNewMaintenanceBasePassword	=	(unsigned char*)szNewMaintenanceBasePassword;
	InPar.szImportPsw					=	(unsigned char*)szImportPsw;
	InPar.szFullImportFileName			=	(unsigned char*)szFullImportFileName;


	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Import	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_Import(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
int
LBSC_Session::DeleteUDB( const LBSC_Ticket *pTicket, char *szBaseName, char *szPassword, BOOL bForce )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_DeleteUDB	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.sTicket						=	BuildTickBuff( pTicket );
	InPar.szBaseName					=	(unsigned char*)szBaseName;

	if ( szPassword ) {
		strncpy( (char *)InPar.szPassword, szPassword, PASSWORDSIZE );
	}

	InPar.bForce						=	bForce;
	InPar.lSessionObj					= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DeleteUDB	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_DeleteUDB(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
int
LBSC_Session::DeleteDefaultUserBase( char *szServerName, char *szPassword, BOOL bForce )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServerName ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_DeleteUDB	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	if ( szPassword ) {
		strncpy( (char *)InPar.szPassword, szPassword, PASSWORDSIZE );
	}

	InPar.bForce						=	bForce;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DeleteUDB	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_DeleteDefaultUserBase(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( szServerName  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/*************************************/
int
LBSC_Session::ExportBaseFormat( const LBSC_Ticket *pTicket, LBSC_Base *pBase, char *szEspecificationFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_Export InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		=	this->obj; 
	InPar.sTicket			=	BuildTickBuff( pTicket );
	InPar.lBaseObj			= 	pBase->obj;
	InPar.szEspecificationFileName	=	(unsigned char *)szEspecificationFileName;  



	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Export DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_ExportBaseFormat(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/***********************************************************/
int
LBSC_Session::UpdateUserAddress( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewAddr )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_UpdateUserAddress InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj; 
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szUDBName		= 	(unsigned char *)szUDBName;
	InPar.szUserName	=	(unsigned char *)szUserName;  
	InPar.szNewAddr		=	(unsigned char *)szNewAddr;  

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UpdateUserAddress DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_UpdateUserAddress(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/***********************************************************/
int
LBSC_Session::UpdateUserPhone( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName, char *szNewPhone )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_UpdateUserAddress InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj; 
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szUDBName		= 	(unsigned char *)szUDBName;
	InPar.szUserName	=	(unsigned char *)szUserName;  
	InPar.szNewAddr		=	(unsigned char *)szNewPhone;  

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UpdateUserAddress DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_UpdateUserPhone(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );
}

/***********************************************************/
char *
LBSC_Session::GetUserAddress( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	char *szRet = NULL;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_UpdateUserAddress InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj; 
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szUDBName		= 	(unsigned char *)szUDBName;
	InPar.szUserName	=	(unsigned char *)szUserName;  

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UpdateUserAddress DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Session_GetUserAddress(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	NULL );		
	}

	if ( !szRet ) {
		return  NULL;
	}

	char *szRet2 = StrDup( szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return ( szRet2 );
}

/***********************************************************/
char *
LBSC_Session::GetUserPhone( const LBSC_Ticket *pTicket, char *szUDBName, char *szUserName )
{
	char *szRet = NULL;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}											

	TSRIn_UpdateUserAddress InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj; 
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szUDBName		= 	(unsigned char *)szUDBName;
	InPar.szUserName	=	(unsigned char *)szUserName;  

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UpdateUserAddress DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Session_GetUserPhone(  DupInPar );
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
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr  , ulExceptionCode);
		return(	NULL );		
	}

	
	if ( !szRet ) {
		return  NULL;
	}

	char *szRet2 = StrDup( szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return ( szRet2 );
}


/***********************************************************/
int
LBSC_Session::RebuildControl( char *szServer )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServer)){
		return( LBSE_NETERROR );
	}
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		RpcTryExcept{
	       		iRet = ( int )RPC_Session_RebuildControl(   );
				bNetError = FALSE;
				bRetry = FALSE;
		}
		RpcExcept(1){
			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( szServer , ulExceptionCode);
		return(	LBSE_NETERROR );		
	}

	
	return( iRet );

}

/***********************************************************/
int
LBSC_Session::LeaveBase( const LBSC_Ticket *pctTicket, char *szBaseName )
{
	int	iRet;


	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_CreateCloseDelete InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_CreateCloseDelete));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj			= this->obj;
	InPar.sTicket				= BuildTickBuff( pctTicket );
	InPar.szBaseName			= (unsigned char *) szBaseName;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );


	   		iRet = ( int )RPC_Session_LeaveBase(  DupInPar );
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
char *
LBSC_Session::GetDefUserBaseName( char *szServer )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServer ) ){
		return( NULL );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept{

	       		szRet = (char *) RPC_Session_GetDefUserBaseName( );
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
		LBSC_ClntNet::TrataErroRPC( szServer , ulExceptionCode);
		return(	NULL );		
	}

	if( szRet ){
		char *szRet2 = StrDup( szRet );
		ClntFree( szRet );	// detona memoria do RPC
		return ( szRet2 );
	} 

	return NULL;
}


/***********************************************************/
int
LBSC_Session::IncorporateBase( const LBSC_Ticket *pctTicket, char *szBaseName, char *szBasePassword, char *szUserName, char *szUDBName )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_IncorporateBase InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_IncorporateBase ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		= this->obj;
	InPar.sTicket			= BuildTickBuff( pctTicket );
	InPar.szBaseName		= (unsigned char *) szBaseName;
	InPar.szBasePassword	= (unsigned char *) szBasePassword;
	InPar.szUserName		= (unsigned char *) szUserName;
	InPar.szUDBName   	= (unsigned char *) szUDBName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IncorporateBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_IncorporateBase(  DupInPar );
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
int
LBSC_Session::ClearBase( const LBSC_Ticket *pctTicket, char *szBaseName )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_IncorporateBase InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_IncorporateBase ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		= this->obj;
	InPar.sTicket			= BuildTickBuff( pctTicket );
	InPar.szBaseName		= (unsigned char *) szBaseName;
	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IncorporateBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_ClearBase(  DupInPar );
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
int
LBSC_Session::RenameBase( const LBSC_Ticket *pTicket, char *szOldName, char *szNewName )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_RenameBase InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_RenameBase ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;
	InPar.sTicket		= BuildTickBuff( pTicket );
	InPar.szOldName		= (unsigned char *) szOldName;
	InPar.szNewName		= (unsigned char *) szNewName;
	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_RenameBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_RenameBase(  DupInPar );
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
int
LBSC_Session::ReorganizeUDB( const LBSC_Ticket *pTicket, char *szUDBName )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_IncorporateBase InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_IncorporateBase ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;
	InPar.sTicket		= BuildTickBuff( pTicket );
	InPar.szUDBName		= (unsigned char *) szUDBName;
	
	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_IncorporateBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_ReorganizeUDB(  DupInPar );
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
int
LBSC_Session::ReorganizeDefaultUserBase( const LBSC_Ticket *pTicket )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketPar InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_TicketPar ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;
	InPar.sTicket		= BuildTickBuff( pTicket );
		
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_ReorganizeDefaultUserBase(  DupInPar );
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
void
LBSC_Session::Delete( void *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( char *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( int *pObj )
{
	if ( pObj )
		delete pObj;
}


/*************************************/
void		
LBSC_Session::Delete( TField *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( TUDBRecord *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( LBSC_AllBasesList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( LBSC_ServerBasesList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( LBSC_PermList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( LBSC_ACLList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void		
LBSC_Session::Delete( TBaseInfo *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void    
LBSC_Session::Delete( LBSC_AppUserInfoList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void    
LBSC_Session::Delete( LBSC_AppNetInfoList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void    
LBSC_Session::Delete( LBSC_AppSessionNetInfoList *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void    
LBSC_Session::Delete( TACL_Lists *pObj )
{
	if ( pObj )
		delete pObj;
}


/*************************************/
void    
LBSC_Session::Delete( LBSC_AppBaseNetInfoList *pObj )
{
	if ( pObj )
		delete pObj;
}


/*************************************/
void
LBSC_Session::Delete( TSlotCache *pObj )
{
	if ( pObj )
		delete pObj;
}

/*************************************/
void
LBSC_Session::Delete( TSlotCacheInfo *pObj )
{
	if ( pObj )
		delete pObj;
}


/*************************************/
void
LBSC_Session::Delete( LBSC_MaintBase *pObj )
{
	if ( pObj )
		delete pObj;
}


/*************************************/
int
LBSC_Session::KillSessions( const LBSC_Ticket *pTicket, char *szAppName, char *szClientName, long lIdApp, long lSessionId )
{
	int	iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr )){
		return( LBSE_NETERROR );
	}

	TSRIn_KillSessions InPar;
	memset( (void*) &InPar, 0, sizeof( TSRIn_KillSessions ));

	InPar.szAppName	= (unsigned char *)szAppName;
	InPar.szClientName	= ( unsigned char * )szClientName;
	InPar.lIdApp	= lIdApp;
	InPar.TSessionObj.lObj = lSessionId;
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.TSessionObj.sCtrlInfo = ObtemControlInfo();
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_KillSessions DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

	   		iRet = ( int )RPC_Session_KillSessionsEx( DupInPar );
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
LBSC_Session **
LBSC_Session::OpenSessions( char *szServer, char *szClientName, 
						  char *szUserName, char *szUserPasswd, 
						  char *szUDBName )
{
	// Esse metodo so e chamado no servidor; nao tem porque um
	// cliente faze-lo

	return NULL;
}


/*************************************/
int		
LBSC_Session::KillServer( const LBSC_Ticket *pTicket, char *szServer )
{
	long lRet;

	unsigned long ulExceptionCode = 0;
	if ( !LBSC_ClntNet::GetRPCHandle( szServer ) )
		return( LBSE_NETERROR );
	
	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;

		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			lRet = RPC_Session_KillServer( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
		RpcExcept(1) {
			Free( DupInPar );

			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
		}
		RpcEndExcept
	} while( bRetry );
	
	LBSC_ClntNet::FreeRPCHandle();

	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( szServer , ulExceptionCode);
		return( LBSE_NETERROR );
	}
	
	return lRet;	
}






