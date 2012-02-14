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
 

//
//	Prototipos internos
//
long GetNumFieldIds( UINT * );



void *
LBSC_Base::MGetFieldRepetition( UINT *puiFieldIds )
{
	TSRIn_MGetPutFieldRep	InPar;
	TSROut_MGetFieldRep		OutPar;

	memset( &InPar, 0, sizeof( InPar ) );
	memset( &OutPar, 0, sizeof( OutPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.lNumFieldIds = GetNumFieldIds( puiFieldIds );
	InPar.pFieldIds = (long *)puiFieldIds;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_MGetPutFieldRep	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		OutPar = RPC_Base_MGetFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

	unsigned char *pRet = NULL;
	if ( OutPar.lTamBuff ) { 
		pRet = new unsigned char[OutPar.lTamBuff];
		if ( pRet ) {
			memcpy(pRet, OutPar.szBuffer, OutPar.lTamBuff);
		}
	} 

	ClntFree( OutPar.szBuffer );

	return (void *)pRet;
}

int
LBSC_Base::MPutFieldRepetition( const LBSC_Ticket *lbscTicket, void *pvBuffer )
{
	int iRet = LBSE_NETERROR;
	TSRIn_MGetPutFieldRep		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj = this->obj;
	InPar.sTicket = BuildTickBuff( lbscTicket );
	//
	// tamanho do buffer tah no primeiro int;
	InPar.lTamBuff = *(int *)pvBuffer;
	InPar.szBuffer = (unsigned char *)pvBuffer;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_MGetPutFieldRep		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_MPutFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
/***********************************************************/
/**************** ModifyFieldRepetition ********************/
/***********************************************************/
/***********************************************************/


int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, char *szNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = strlen( szNewVal ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szNewVal );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_STRING;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, char *szNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = strlen( szNewVal ) + 1;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	strcpy( (char*)InPar.Rep, szNewVal );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_STRING;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, void *pvNewVal, long lSize )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvNewVal, lSize );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_VOID;
		
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, void *pvNewVal, long lSize )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = lSize;
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, pvNewVal, lSize );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_VOID;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, long plNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &plNewVal, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_LONG;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, long plNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( long );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &plNewVal, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_LONG;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, double pdNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdNewVal, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, double pdNewVal )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( double );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pdNewVal, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_DOUBLE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, C_Date pcdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long)( pcdRepetition.Hash() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, C_Date pcdRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( long );
	long l = (long)( pcdRepetition.Hash() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_DATE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, C_Time pctRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, C_Time pctRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( long );
	long l = (long)( pctRepetition.Seconds() );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &l, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_TIME;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, LBSC_Binary *pbRepetition )
{
	int 				iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition	InPar;

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
	InPar.lRepNumber = (long)iRep;


	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;

	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_BINARY;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, LBSC_Binary *pbRepetition )
{
	int 				iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition	InPar;

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
	InPar.lRepNumber = (long) iRep;

	InPar.Rep = (unsigned char *) new char[ ( 2 * sizeof( int ) ) + pbRepetition->iLen ];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &(pbRepetition->iFormat), sizeof( int ) );
	memcpy( InPar.Rep + sizeof( int ), &(pbRepetition->iLen), sizeof( int ) );
	memcpy( InPar.Rep + ( 2 * sizeof( int ) ), &(pbRepetition->pvBuffer), pbRepetition->iLen );
  	InPar.lTam = ( 2 * sizeof( int ) ) + pbRepetition->iLen;


	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_BINARY;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, LBSC_Reference *prRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long) iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_REFERENCE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, LBSC_Reference *prRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = (prRepetition && prRepetition->szBuffer) ? 
		sizeof(LBSC_Reference) + strlen(prRepetition->szBuffer) : 0;
	InPar.Rep = InPar.lTam ? (unsigned char *) new char[InPar.lTam] : NULL;
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, prRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_REFERENCE;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, BYTE pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long) iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, BYTE pbRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long) iRep;
	InPar.lTam = sizeof( BYTE );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pbRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_BYTE;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, short int psRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( short int );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_SHORT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, short int psRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( short int );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &psRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_SHORT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( char *szField, int iRep, float pfRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.szField = (unsigned char*)szField;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = -1;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_FLOAT;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRep, float pfRepetition )
{
	int iRet = LBSE_NETERROR;
	TSRIn_ModifyFieldRepetition		InPar;

	// atualiza o estado do servidor e invalida a cache de repeticoes
	crcRep.AtualizaSvcContext();
	crcRep.InvalidaCache();

	memset( &InPar, 0, sizeof( InPar ) );

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}
			
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase = this->obj;
	InPar.lRepNumber = (long)iRep;
	InPar.lTam = sizeof( float );
	InPar.Rep = (unsigned char *) new char[InPar.lTam];
	if ( !InPar.Rep ) {	// sem memoria, considere um erro de rede; trate-o
		return ( LBSE_NETERROR );
	}

	memcpy( InPar.Rep, &pfRepetition, InPar.lTam );
	InPar.lFieldId = (long)uiFieldId;
	InPar.sMethod = RPC_BASE_MODIFYFIELDREPETITION_FLOAT;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyFieldRepetition		DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Base_ModifyFieldRepetition( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_PermList *
LBSC_Base::GetACLListPermission( char *szName, int iList )
{
	TSRIn_GetACLListPerm	InPar;
	TSROut_WhatBases		sOut;
	LBSC_PermList			*pList = NULL;
	C_Buffer				*pcbRet = NULL;

	memset( &InPar, 0, sizeof( InPar ) );
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBase		= this->obj;
	InPar.szName		= (unsigned char*)szName;
	InPar.lList		= (long)iList;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetACLListPerm	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sOut = RPC_Base_GetACLListPermission( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

	

	pcbRet = new C_Buffer( sOut.lTam - sizeof( int ) );
	if(!pcbRet){	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}


	pcbRet->PutData( (void*) (sOut.szBuffer + sizeof( int )), sOut.lTam - sizeof( int ) );
	pcbRet->Rewind();
	pList = MakePermList( *pcbRet );
	delete pcbRet;
	ClntFree( (void *)sOut.szBuffer );  // dealoca o que veio do RPC

	return( pList );
}

/*********************************/
char *
LBSC_Base::ExchangeOperator( char *szNewOp )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_ExchangeOperator	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szNewOp	=	( unsigned char * )szNewOp;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ExchangeOperator	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = ( char * )RPC_Base_ExchangeOperator( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::SetMask( char *szMasks, int iIndex, int iType )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Mask	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szMasks	=	( unsigned char * )szMasks;
	InPar.liIndex	=	( long )iIndex;
	InPar.liType	=	( long )iType;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Mask	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SetMask( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
char *
LBSC_Base::GetMask( int iIndex )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Mask	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.liIndex	=	( long )iIndex;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Mask	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_GetMask( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::SaveMasks( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Mask	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Mask	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SaveMasks( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::LoadMasks( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Mask	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Mask	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_LoadMasks( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::ClearMasks( char *szFileName )
{
	int iRet;

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

	       		iRet = ( int )RPC_Base_ClearMasks( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::AddPhone( char *szPhoneArray, int iPhoneNumber )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Phone	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szPhoneArray	=	( unsigned char * )szPhoneArray;
	InPar.liPhoneNumber	=	( long )iPhoneNumber;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Phone	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_AddPhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::DeletePhone( char *szPhoneArray )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Phone	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szPhoneArray	=	( unsigned char * )szPhoneArray;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Phone	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_DeletePhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::SavePhone( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Phone	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Phone	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SavePhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::LoadPhone( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Phone	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Phone	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_LoadPhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::ClearPhone()
{
	int iRet;

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

	       		iRet = ( int )RPC_Base_ClearPhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::FindPhone( char *szTerm, char *szPhoneValue )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Phone	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szTerm		=	( unsigned char * )szTerm;
	InPar.szPhoneValue	=	( unsigned char * )szPhoneValue;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Phone	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_FindPhone( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
char *
LBSC_Base::SetStandardizer( char *szStandardizerArray )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Standardize	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj			=	this->obj;
	InPar.szStandardizerArray	=	( unsigned char * )szStandardizerArray;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Standardize	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_SetStandardizer( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::Standardize( char *szContent, char *szDestination, int iSize )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Standardize	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szContent		=	( unsigned char * )szContent;
	InPar.szDestination	=	( unsigned char * )szDestination;
	InPar.liSize		=	( long )iSize;
					    	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Standardize	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_Standardize( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::AddSynonym( char *szTerm, char *szSynonymArray, int iFlag )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Synonym	InPar;		    
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szTerm		=	( unsigned char * )szTerm;
	InPar.szSynonymArray	=	( unsigned char * )szSynonymArray;
	InPar.liFlag		=	( long )iFlag;
	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Synonym	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_AddSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::DeleteSynonym( char *szTerm, char *szSynonymArray, int iFlag )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Synonym	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szTerm		=	( unsigned char * )szTerm;
	InPar.szSynonymArray	=	( unsigned char * )szSynonymArray;
	InPar.liFlag		=	( long )iFlag;
	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Synonym	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_DeleteSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::SaveSynonym( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Synonym	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Synonym	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_SaveSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::LoadSynonym( char *szFileName )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_Synonym	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.szFileName	=	( unsigned char * )szFileName;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Synonym	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_LoadSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::ClearSynonym()
{
	int iRet;

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

	       		iRet = ( int )RPC_Base_ClearSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
char *
LBSC_Base::FindSynonym( char *szTerm )
{
	char *szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_Synonym	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.szTerm	=	( unsigned char * )szTerm;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_Synonym	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*)RPC_Base_FindSynonym( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::OLAnd( const LBSC_Ticket *pTicket, int iHandle1, int iHandle2 )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OL	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.liHandle1		=	( long )iHandle1;
	InPar.liHandle2		=	( long )iHandle2;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OL	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_OLAnd( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::OLOr( const LBSC_Ticket *pTicket, int iHandle1, int iHandle2 )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OL	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.liHandle1		=	( long )iHandle1;
	InPar.liHandle2		=	( long )iHandle2;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OL	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_OLOr( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::OLXor( const LBSC_Ticket *pTicket, int iHandle1, int iHandle2 )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OL	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.liHandle1		=	( long )iHandle1;
	InPar.liHandle2		=	( long )iHandle2;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OL	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_OLXor( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::OLNot( const LBSC_Ticket *pTicket, int iHandle1, int iHandle2 )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_OL	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.liHandle1		=	( long )iHandle1;
	InPar.liHandle2		=	( long )iHandle2;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OL	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_OLNot( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
} /***/

/*********************************/
BOOL
LBSC_Base::IsExportable()
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

	       		bRet = ( BOOL )RPC_Base_IsExportable( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
		return( FALSE );
	
	}

	
	return( bRet );
}

/*********************************/
int
LBSC_Base::BlockReExport( const LBSC_Ticket *pTicket)
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
	InPar.sTicket	=	BuildTickBuff( pTicket );
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_BlockReExport( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************/
int
LBSC_Base::ModifyRecordPassword( const LBSC_Ticket *pTicket, char *szOldPassword, char *szNewPassword )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_ModifyPassword InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.szOldPassword	=	( unsigned char * )szOldPassword;
	InPar.szNewPassword	=	( unsigned char * )szNewPassword;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_ModifyPassword DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_ModifyRecordPassword( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

/*********************************
Nada de Operadores

LBSC_Field &
LBSC_Base::operator[]( int iFieldNumber )
{
	LBSC_Field	*pfAux;

	pfAux = (LBSC_Field*)GetFieldObj( iFieldNumber );
	return( *pfAux );
}
*********************/

/*********************************
Nada de Operadores

LBSC_Field &
LBSC_Base::operator()( UINT uiFieldId )
{
	LBSC_Field	*pfAux;

	pfAux = (LBSC_Field*)GetFieldObj( uiFieldId );
	return( *pfAux );
}  
*********************/

/*********************************
Nada de Operadores

LBSC_Field &
LBSC_Base::operator[]( char *szField )
{
	LBSC_Field	*pfAux;

	pfAux = (LBSC_Field*)GetFieldObj( szField );
	return( *pfAux );
}  
*********************/


/*********************************/
BOOL
LBSC_Base::IsExclusive()
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

	       		bRet = RPC_Base_IsExclusive( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::IsReadOnly()
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

	       		bRet = RPC_Base_IsReadOnly( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
BOOL
LBSC_Base::Flush( LBSC_Ticket *pTicket )
{
	BOOL bRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( FALSE );
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

	       		bRet = RPC_Base_Flush( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
long
LBSC_Base::GetNumActiveRecords( const LBSC_Ticket *pctTicket )
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
	InPar.sTicket = BuildTickBuff( pctTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetNumActiveRecords( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::ModifyMaxKeySize( const LBSC_Ticket *pTicket, int iNewKeySize )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_CreateCloseDelete	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		=	this->obj;
	InPar.sTicket		=	BuildTickBuff( pTicket );
	InPar.lMaxKeySize	=	( long )iNewKeySize;

	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_CreateCloseDelete	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = ( int )RPC_Base_ModifyMaxKeySize( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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


/*********************************/
TBaseInfo *
LBSC_Base::GetBaseInfo( const LBSC_Ticket *pctTicket ) 
{
	unsigned long ulExceptionCode = 0;
 	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSROut_BaseInfo	sRet;
	memset( &sRet, 0, sizeof( sRet ) );

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pctTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		sRet = RPC_Base_GetBaseInfo( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

	

	TBaseInfo *sOut;
	sOut = new TBaseInfo( ( char * )sRet.szUDBName, ( char * )sRet.szOwnerName, ( char * )sRet.szLastUser,
		  ( char * )sRet.szUsers, ( char *) sRet.szServerName, ( int )sRet.lNumInst,
		  ( unsigned long )sRet.lCreateDate, ( unsigned long )sRet.lLastModifyDate,
		  ( BYTE )sRet.lBaseType, ( int )sRet.lSlotNum, ( int )sRet.lCountNum, ( int )sRet.lMaxKeySize,
		  ( int )sRet.lIntPart, ( int )sRet.lDecPart, ( BOOL )sRet.lIsEncrypt, ( BOOL )sRet.lReExport );
	
	ClntFree ( (void *) sRet.szUsers );  // libera memoria do RPC

	if ( !sOut ) {	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	return( sOut );
}			 


/**********************************/
long
LBSC_Base::GetNumOLRecords( const LBSC_Ticket *pctTicket, int iHandle )
{
	long lRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

   TSRIn_OL	InPar;
	memset( &InPar, 0, sizeof( InPar ) );
   	
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	   =	this->obj;
	InPar.sTicket     =  BuildTickBuff( pctTicket );
   InPar.liHandle1	=	( long )iHandle;
			
   boolean bNetError = TRUE;
   boolean bRetry = FALSE;
   do {
	   TSRIn_OL	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		lRet = RPC_Base_GetNumOLRecords( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
LBSC_Base::GetNumRecIndex()
{
	int	iRet;

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

	       		iRet = ( int )RPC_Base_GetNumRecIndex( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

	
	return( iRet );
}

/*********************************/
BOOL
LBSC_Base::GetStopIndex()
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

	       		bRet = RPC_Base_GetStopIndex( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
void
LBSC_Base::SetStopIndex( BOOL bIndex )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_TicketBOOLPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj	=	this->obj;
	InPar.lbPar	=	( long )bIndex;
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketBOOLPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		RPC_Base_SetStopIndex( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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


/*************************************/
int
LBSC_Base::ClearBase( const LBSC_Ticket *pctTicket )
{
	int	iRet;

	// invalida a cache de repeticoes
	crcRep.InvalidaCache();

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr)){
		return( LBSE_NETERROR );
	}

	TSRIn_TicketPar InPar;
	memset( (void*) &InPar, 0, sizeof( InPar ));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lBaseObj		= this->obj;
	InPar.sTicket		= BuildTickBuff( pctTicket );	
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	   		iRet = ( int )RPC_Base_ClearBase( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
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


long 
GetNumFieldIds( UINT *pFieldIds )
{
	if ( !pFieldIds ) {
		return 0;
	}

	for (long iNum=0; *pFieldIds != 0; iNum++, pFieldIds++)
		;

	return iNum+1;
}

