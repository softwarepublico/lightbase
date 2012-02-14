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
// Module: LBSERRCL.CPP
// Description:
//
//	LBSC_Error private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//		Alessandro A. Jatoba'
//
// Last update: 16/01/96
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

#ifndef __LBSRPC_H__
	#include	<lbsrpc.h>
#endif	// __LBSRPC_H__

#ifndef _LBSERROR_H_
	#include	<lbserror.h>
#endif	// _LBSERROR_H_

#ifndef _BUFFERCL_H_
	#include	<buffercl.h>
#endif	// _BUFFERCL_H_

#ifndef _ALLBASEL_H_
	#include    <allbasel.h>
#endif	// _ALLBASEL_H_


#ifndef _FBUFF_H
#include    <fbuff.h>
#endif
#ifndef _LBSERRCL_H_
#include	<cllbserr.h>
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

#ifndef _APPMNGR_H_
	#include <appmngr.h>
#endif	// _APPMNGR_H_

int GetCurrentTLSVal();
void SetCurrentTLSVal( int );
void AllocCurrentTLS();

//
//	Variaveis globais
//
extern const char *_LBS_ErrorTable[];

//	guarda o ultimo erro do LBS
static int _iLastErrorTLSIndex = 0;

extern AppParmsMngr	*_pcInter;	// para internacionalizacao

static char szErrorDesc[MAXERRORMSGSIZE];	// so para o metodo (estatico) LastErrorDesc


TSRControlInfo 
LBSC_Error::ObtemControlInfo()
{
	TSRControlInfo sControl;
	memset(&sControl, 0, sizeof(sControl));

	strcpy((char *)sControl.szClientName, szClientName);
	sControl.lClntTimeStamp = lClntTimeStamp;
	sControl.lSvcTimeStamp = lSvcTimeStamp;
	sControl.lObj = lSessionObj;

	return sControl;
}


/***
***/
int
LBSC_Error::LastError()
{
	int iRet;

	int iNetErr = QualNetError( this->ServerAddr );  // ERRO DE REDE
	if ( iNetErr != LBS_OK ) {
		return iNetErr;
	}

	if ( lLastErr != LBSE_UNAVAILABLE ) {
		return lLastErr;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr) ){
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

		RpcTryExcept {
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );
			iRet = RPC_Error_LastError(  DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
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

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr, ulExceptionCode);
		return ( LBSE_NETERROR );
	}
	

	return( iRet );

}

/***
***/
const char *
LBSC_Error::LastErrorDesc()
{
	char *szRet;

	if ( QualNetError( this->ServerAddr ) != LBS_OK ) { // ERRO DE REDE
		return LBSC_ClntNet::GetNetErrorDesc();
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;

		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );
	       		szRet = (char*)RPC_Error_LastErrorDesc(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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

	strcpy( szDesc, szRet );
	ClntFree( szRet );	// detona memoria do RPC
	return( szDesc );
}



/***
***/
const char *
LBSC_Error::LastErrorDesc( int iNumOfError )
{
	// este metodo eh static e serve para retornar a descricao
	// de um determinado erro. Foi copiado do LBS servidor
	char	szMsg[ 255 ];
	char	*szErrAux = NULL;

	if ( iNumOfError == LBSE_NETERROR ) {
		return LBSC_ClntNet::GetNetErrorDesc();
	}

	sprintf( szMsg, "LBSERR_%d", iNumOfError == 0 ? iNumOfError : ((-iNumOfError) - LBSERROR_OFFSET) );
	if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
		szErrAux = _pcInter->GetGenMsgsAppVar( szMsg );
	}
	if( !szErrAux ){
		// deu pau na internacionalizacao. vamos retornar o conteudo da
		// tabela interna
		return( (const char *)_LBS_ErrorTable[ iNumOfError == 0 ? iNumOfError : ((-iNumOfError) - LBSERROR_OFFSET - 1) ] );
	}
	// conseguimos carregar a mensagem de erro do .ini
	memset( szErrorDesc, 0, MAXERRORMSGSIZE );
	strncpy( szErrorDesc, szErrAux, (MAXERRORMSGSIZE-1) );
	delete szErrAux;
	return( (const char*) szErrorDesc );
}

void 
LBSC_Error::SetLastError( int iErr )
{
	lLastErr = iErr;
}

int 
LBSC_Error::LastErrorStatic()
{
	return QualNetError( NULL );
}


