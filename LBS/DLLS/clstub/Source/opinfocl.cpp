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

#ifndef _OPINFOCL_H_
	#include <opinfocl.h>
#endif	// _OPINFOCL_H_

#ifndef _SESSCL_H_
	#include <sesscl.h>
#endif	// _SESSCL_H_

#ifndef __lbsrpc_h__
	#include <lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_

// so pra constar...
class COccurList;
class C_Buffer;

#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_

#ifndef	_DUPLICATE_H_
	#include <duplicate.h>
#endif	// _DUPLICATE_H_
 


void	
LBSC_OpInfo::CancelOperation()
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
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			RPC_OpInfo_CancelOperation( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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


void	
LBSC_OpInfo::GetOpInfo( char *szActionPar, float *pfPercentPar )
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
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			OutPar = RPC_OpInfo_GetOpInfo( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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




