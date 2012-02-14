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

#ifndef _SESSCL_H_
	#include	<sesscl.h>  
#endif	// _SESSCL_H_

#ifndef _CSTRTOK_H_
	#include	<cstrtok.h>  
#endif	// _CSTRTOK_H_

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

#ifndef _ALLBASEL_H_
	#include <allbasel.h>
#endif	// _ALLBASEL_H_

#ifndef _GETSRVRS_H_
	#include <getsrvrs.h>
#endif	// _GETSRVRS_H_

#ifndef	_BUFFERCL_H_
#include <buffercl.h>
#endif

#ifndef	_FBUFF_H_
#include <fbuff.h>
#endif

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_


#ifndef _ADMDEFS_H_
	#include <admdefs.h>
#endif	// _ADMDEFS_H_

#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_

#ifndef	_DUPLICATE_H_
	#include <duplicate.h>
#endif	// _DUPLICATE_H_
 

//
//	Prototipos internos
//
int MesmosHosts( char *, char * );
int QualIntProto( char * );
const char *QualStrProto( int );



int				
LBSC_Session::SetServerParam( const LBSC_Ticket *pTicket, int iProto, 
								int iOccTmOut )
// houve mudancas; nada de configurar portas
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr) ){
		return( LBSE_NETERROR );
	}
		
	TSRIn_SetSvcParam InPar;
	long lRet;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.lProto = iProto;
	InPar.lOccurTmOut = iOccTmOut;
	InPar.sTicket = BuildTickBuff(pTicket);
	InPar.TSessionObj.sCtrlInfo = ObtemControlInfo();
	InPar.TSessionObj.lObj	= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_SetSvcParam DupInPar;
		RpcTryExcept {
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			lRet = RPC_Session_SetServerParam( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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
		return( LBSE_NETERROR );
	}

	return( lRet );
}

void			
LBSC_Session::GetServerParam( char *szServer, int *piProto, 
							 int *piOccTmOut )
{
	if ( !piProto ) {
		return;
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServer ) ){
		return;
	}
		
	TSRGenericObj InPar;
	TSROut_GetSvcParam OutPar;

	memset( &InPar, 0, sizeof( InPar ));

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRGenericObj DupInPar;
		RpcTryExcept {
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			OutPar = RPC_Session_GetServerParam( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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
		return;
	}

	*piProto = OutPar.lProto;
	*piOccTmOut = OutPar.lOccurTmOut;
}


int				
LBSC_Session::SetClientParam( int iProto, int iTimeout, int, int, 
							 char **pszServers)
{
	// obtem os parametros atuais
	char **pszServersAtual = NULL;
	int iProtoAtual=0;
	GetClientParam( &iProtoAtual, /* dummy */ NULL, /* dummy */ NULL, 
			/* dummy */NULL, /* dummy */&pszServersAtual );
	DeleteVect( pszServersAtual );

	switch ( iProto ) {
	case LBSPROTO_TCPIP:
	case LBSPROTO_NETBEUI:
	case LBSPROTO_NAMEDPIPE:
		break;
	default:
		return LBS_CS_INVALIDPROTO;
	}

	switch ( iTimeout ) {
	case LBS_CS_LOW_TIMEOUT:
	case LBS_CS_MED_TIMEOUT:
	case LBS_CS_HIGH_TIMEOUT:
	case LBS_CS_INF_TIMEOUT:
		break;
	default:
		return LBS_CS_INVALIDTMOUT;
	}

	if ( !pszServers ) {
		return LBS_CS_INVALIDSERVERS;
	}

	char szProfileBuffer[256];
	char szProto[100];
	char szTmOut[100];

	// preparando a secao de timeout e protocolo
	sprintf(szProto, "%s=%s", LBSPROTOKEY, QualStrProto(iProto));
	sprintf(szTmOut, "%s=%d", LBSTMOUTKEY, iTimeout);

	memcpy(szProfileBuffer, szProto, strlen(szProto) + 1);
	int iOffset = strlen(szProto) + 1;

	memcpy(szProfileBuffer + iOffset, szTmOut, strlen(szTmOut) + 1);
	iOffset += strlen(szTmOut) + 1;

	memcpy(szProfileBuffer + iOffset, "", 1);
	WritePrivateProfileSection(CLIENTINILBSSECTION, 
								szProfileBuffer, ObtemClientIniName());

	// da um refresh na lista de handles RPC
	LBSC_ClntNet::LiberaServList();

	if ( iProtoAtual != iProto ) {	// nao importam as portas do .INI
		if ( !AlteraServidores( pszServers ) ) {
			return LBS_CS_INVALIDSERVERS;
		}
	}
	else {	// devo preservar as portas do .INI 
		char **pszNewServers = NULL;
		ObtemMergedServers( pszServers, &pszNewServers );
		if ( !AlteraServidores( pszNewServers ) ) {
			return LBS_CS_INVALIDSERVERS;
		}
		DeleteVect( pszNewServers );
	}

	return LBS_OK;
}


//
//	Faz um merge entre uma lista de servidores e o que ja existe
//	no .INI, mantendo os settings de porta do .INI
//
void				
LBSC_Session::ObtemMergedServers( char **pszServ, char ***pszNewServers)
{
	if ( !pszServ ) 
		return;

	// calculando o numero de elementos de pszServ
	for ( int iNumServ=0; pszServ[iNumServ]; iNumServ++ )
		;
	*pszNewServers = new char *[iNumServ+1]; // mais um pra incluir o NULL
	if ( !*pszNewServers )
		return;

	char **pszServersAtual=NULL;
	LBSC_Session::ObtemServidores( &pszServersAtual );

	//$$$$$$ EDNEY
	if (pszServersAtual){
		for ( int iNew=0; iNew < iNumServ; iNew++ ) {

			(*pszNewServers)[iNew] = NULL;
			// procurando se ja existe no .INI um servidor com esse nome
			for ( int iOld=0; pszServersAtual[iOld]; iOld++ ) {
				char szServAtual[FULLNAMESIZE+1];
				C_StrTok	cstNewTok;

				strcpy(szServAtual, pszServersAtual[iOld]);

				// nome do servidor no .INI pode vir delimitado por virgulas
				if ( stricmp(pszServ[iNew], cstNewTok.StrTok(szServAtual, 
									DELIMSERV_SET) ) == 0 ) { // achou
					(*pszNewServers)[iNew] = StrDup(pszServersAtual[iOld]);
					break;
				}
			}

			if ( !(*pszNewServers)[iNew] ) {	// nao achou no .INI; usa o que foi dado
				(*pszNewServers)[iNew] = StrDup(pszServ[iNew]);
			}
		}
		(*pszNewServers)[iNew] = NULL; // pra fechar o vetor

		DeleteVect(pszServersAtual);
	} else {
		for ( int iNumServ=0; pszServ[iNumServ]; iNumServ++ ){
			(*pszNewServers)[iNumServ] = StrDup(pszServ[iNumServ]);
		}
		(*pszNewServers)[iNumServ] = NULL; // pra fechar o vetor
	}
}


void				
LBSC_Session::GetClientParam( int *piProto, int *piTimeout, int *, int *, char ***pszServers)
{

	char szProto[50];
	char szDefStr[] = "";

	GetPrivateProfileString( CLIENTINILBSSECTION, LBSPROTOKEY, 
					szDefStr, szProto, 50, ObtemClientIniName());
	if ( piProto ) {
		*piProto = QualIntProto(szProto);
	}

	if ( piTimeout ) {
		*piTimeout = GetPrivateProfileInt( CLIENTINILBSSECTION, LBSTMOUTKEY, 
											0, ObtemClientIniName());
	}

	ObtemServidores(pszServers);

	if ( !*pszServers ) {
		return;
	}

	for (int i=0; (*pszServers)[i]; i++) {
		// possivelmente os nomes dos servidores estao separados por virgula
		C_StrTok	cstNewTok;

		char *szAux = StrDup( cstNewTok.StrTok((*pszServers)[i], DELIMSERV_SET) );

		delete (*pszServers)[i];
		(*pszServers)[i] = szAux;
	}

}


LBSC_AppUserInfoList *			
LBSC_Session::GetUsersInfo( const LBSC_Ticket *pTicket )
{
	TSROut_GetUsersInfo	sOut;
	C_Buffer			*pcbRet = NULL;
	TSRIn_TicketPar		InPar;
	

	unsigned long ulExceptionCode = 0;
	memset( (void*) &InPar, 0, sizeof(InPar));
	if( !LBSC_ClntNet::GetRPCHandle( (char *)this->ServerAddr ) ){
		return( NULL );
	}

	InPar.sTicket = BuildTickBuff(pTicket);
	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar		DupInPar;
		RpcTryExcept{
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			sOut = RPC_Session_GetUsersInfo( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
		RpcExcept(1){
			Free( DupInPar );

			bRetry = LBSC_ClntNet::EnviaNovaRPC();
			ulExceptionCode = RpcExceptionCode();
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( (char *)this->ServerAddr  , ulExceptionCode);
		return(	NULL );		
	}
										
	if ( !sOut.lTamBuff ) {
		return ( NULL );
	}

	LBSC_AppUserInfoList	*pList = NULL;
	pcbRet = new C_Buffer( sOut.lTamBuff - sizeof(int) ); // pula o int do cbuffer; Vladimir Catao 29/01/96
	if( !pcbRet ){	// sem memoria, considere um erro de rede; trate-o
		return ( NULL );
	}

	pcbRet->PutData( (void*) (sOut.szBuffer + sizeof(int)), sOut.lTamBuff - sizeof(int)); // pula o int do cbuffer; Vladimir Catao 29/01/96
	pcbRet->Rewind();
	pList = MakeAppUserInfoList( *pcbRet );
	delete pcbRet;
	ClntFree( (void *)sOut.szBuffer );  // dealoca o que veio do RPC

	return( pList );
}

int				
LBSC_Session::UnLockRecord( const LBSC_Ticket * pTicket, long lIdBase )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR);
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;
	InPar.lBaseObj	=	lIdBase;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

	       	iRet = ( int )RPC_Session_UnLockRecord( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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


char * 
LBSC_Session::GetBaseLongName( char *szServerName, char *szUDBName, 
								char *szBaseAliasName )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( szServerName ) ){
		return( NULL );
	}

	TSRIn_GetBaseLongName InPar;
	memset(&InPar, 0, sizeof(InPar));

	InPar.szBaseAliasName = (unsigned char *)szBaseAliasName;
	InPar.szUDBName = (unsigned char *)szUDBName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_GetBaseLongName DupInPar;
		RpcTryExcept{
			Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char *) RPC_Session_GetBaseLongName( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
		return(	NULL );		
	}

	if( szRet ){
		char *szRet2 = StrDup( szRet );
		ClntFree( szRet );	// detona memoria do RPC
		return ( szRet2 );
	} 

	return NULL;
}


BOOL		
LBSC_Session::IsUDBOwner( const LBSC_Ticket * , char *, char * )
{
	// nao ha implementacao no lado cliente; esse metodo so esta 
	// sendo usado no stub servidor
	return FALSE;
}


BOOL				
LBSC_Session::AlteraServidores( char **pszServers )
{
	// preparando a secao de HOSTS
	int iOffset = 0;
	int iBufSize = 0;

	for (int i=0; pszServers[i] != NULL ;i++) {
		char szKey[FULLNAMESIZE];
		sprintf(szKey, "%s%d=%s", HOSTKEY, i+1, pszServers[i]);
		iBufSize += strlen(szKey) + 10;
	}

	char *szProfileBuffer = new char [iBufSize];
	if ( !szProfileBuffer ) {
		return FALSE;
	}

	for (i=0; pszServers[i] != NULL ;i++) {
		char szKey[FULLNAMESIZE];
		sprintf(szKey, "%s%d=%s", HOSTKEY, i+1, pszServers[i]);

		memcpy(szProfileBuffer + iOffset, szKey, strlen(szKey) + 1);
		iOffset += strlen(szKey) + 1;
	}

	if ( !i ) {
		return FALSE;
	}

	memcpy(szProfileBuffer + iOffset, "", 1);
	WritePrivateProfileSection(CLIENTINIHOSTSECTION, 
								szProfileBuffer, ObtemClientIniName());
	return TRUE;
}

void				
LBSC_Session::ObtemServidores( char ***pszServers )
{
	char *szDefStr = "";
	char szHostKey[FULLNAMESIZE];
	char szHost[FULLNAMESIZE];

	for (int iMax=0; ;iMax++) {
		sprintf(szHostKey, "%s%d", HOSTKEY, iMax+1);
		GetPrivateProfileString( CLIENTINIHOSTSECTION, szHostKey, 
				 szDefStr, szHost, HOSTSIZE, ObtemClientIniName() );

		if ( stricmp( szHost, szDefStr ) == 0 )
			break;

	}

	if ( !iMax ) {
		*pszServers = NULL;
		return;
	}
					 
	(*pszServers) = new char *[iMax+1]; // mais um pra incluir o NULL
	for (int i=0; i < iMax; i++) {
		sprintf(szHostKey, "%s%d", HOSTKEY, i+1);
		GetPrivateProfileString( CLIENTINIHOSTSECTION, szHostKey, 
				 szDefStr, szHost, HOSTSIZE, ObtemClientIniName() );

		(*pszServers)[i] = StrDup( szHost );
	}

	(*pszServers)[i] = NULL;
}


void	
LBSC_Session::CancelOperation()
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

			RPC_Session_CancelOperation( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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
LBSC_Session::GetOpInfo( char *szActionPar, float *pfPercentPar )
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

			OutPar = RPC_Session_GetOpInfo( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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


void *
LBSC_Session::Broadcast( int iFilterLevel, LBSC_Session *pOpenSess, int ProcID, void *szUserName )
// o parametro pOpenSess foi incluido por Vladimir Catao em 25.01.96. Identifica a sessao aberta
// na maquina com a que a aplicacao ja esta conectada. Antes de fazer o unicast, cheque se o 
// host remoto eh o da sessao. Se for, ja existe uma sessao remota (criada no start da 
// applicacao); senao abra uma sessao e delete-a apos usa-la. 
{
	char				*szReturn = StrDup( "" );
	char				*szAux, *szAux2;
 	LBSC_AllBasesList	*pReturn = NULL;
	LBSC_AllBasesList	*pAuxList = NULL;
	TSROut_WhatBases	sOut;
	C_Buffer			*pcbRet = NULL;
	LBSC_Session		*pSessLocal = NULL;
	char				szHostAtual[1000] = "";
	C_GSList 			*pcgslServers = NULL;	

	::SetLastError( 0 );		// reseta o erro do sistema
	pcgslServers = new C_GSList;
	if ( !pcgslServers ) {
		// este metodo eh estatico; nao tem como chamar o LastError do LBS
		::SetLastError((DWORD) (LBSE_NOMEMORY | 0x20000000) );	
		return szReturn;
	}

	pcgslServers->GetServers();

	int iNumElem = pcgslServers->NumElem();
	if ( iNumElem <= 0 ) {
		// este metodo eh estatico; nao tem como chamar o LastError do LBS
		::SetLastError((DWORD) (LBSE_LBSINIERROR | 0x20000000) );	
		return szReturn;
	}

	unsigned long ulExceptionCode = 0;
	for( int i=0; i < iNumElem; ++i ){
		strcpy( szHostAtual, (const char*)(*pcgslServers)[ i ] );
		pSessLocal = NULL; 
		if ( pOpenSess != NULL ) {
 			if ( !MesmosHosts( pOpenSess->ServerAddr, szHostAtual ) ) {	// sessao nao aberta
				pSessLocal = LBSC_Session::New( szHostAtual );
				if ( !pSessLocal ) // servidor nao esta no ar
					continue;
			}

		} 

		TSRIn_What InPar;
		memset( (void*) &InPar, 0, sizeof(TSRIn_What));

		RpcTryExcept{
			switch( ProcID ){	
				case WHATS:
					/***********
					Modificado por efeito de performance...

					if( !LBSC_ClntNet::GetRPCHandle( szHostAtual )){
						continue;
					}

					RPC_Session_WhatServers();
					***********/

					// neste ponto o servidor foi atingido
					// portanto o nome eh valido
					szAux = StrDup(szHostAtual);

					break;

				case WHATSFORUSER:
					if( !LBSC_ClntNet::GetRPCHandle( szHostAtual )){
						continue;
					}

					InPar.sCtrlInfo = pSessLocal->ObtemControlInfo();
					InPar.lSessionObj = pSessLocal == NULL ? pOpenSess->obj: pSessLocal->obj;
					InPar.szUserName = (unsigned char*) szUserName;
			 					
					szAux = (char *)RPC_Session_WhatServersForUser( InPar );
					break;

				case WHATB:
					if( !LBSC_ClntNet::GetRPCHandle( szHostAtual )){
						continue;
					}

					InPar.lFilterLevel = iFilterLevel;
					sOut = RPC_Session_WhatBases( InPar ); 

					break;

				case WHATBFORUSER:
					if( !LBSC_ClntNet::GetRPCHandle( szHostAtual )){
						continue;
					}

					InPar.sCtrlInfo = pSessLocal->ObtemControlInfo();
					InPar.lSessionObj = pSessLocal == NULL ? pOpenSess->obj: pSessLocal->obj;
					InPar.szUserName = (unsigned char*) szUserName;
					InPar.lFilterLevel = iFilterLevel;

					sOut = 	RPC_Session_WhatBasesForUser(  InPar );
					break;
			}
		}
		RpcExcept(1){
			LBSC_ClntNet::FreeRPCHandle();
			LBSC_ClntNet::TrataErroRPC( szHostAtual, RpcExceptionCode() );
			continue;
		}
		RpcEndExcept	

		LBSC_ClntNet::FreeRPCHandle();
		if ( pSessLocal ) {	// detona a sessao se ela ja foi aberta
			LBSC_Session::Delete( pSessLocal );
		}

		if( (ProcID == WHATS) || (ProcID == WHATSFORUSER) ){
			if ( !szAux ) {
				continue;
			}

			// o numero 3 a seguir eh para comportar os espacos em branco
			szAux2 = (char*)realloc( (void*) szReturn, strlen(szReturn) + strlen(szAux) + 3 ); 
									
			if( !szAux2 ){
				// Nao podemos mais alocar memoria. Vamos retornar o que temos ateh agora0
				delete pcgslServers;
				return( szReturn );
			}
			szReturn = szAux2;
			strcat( szReturn, szAux );
			strcat( szReturn, " " );
			ClntFree( (void *)szAux );	// libera o que veio do RPC
			szAux = NULL;
		}

		if( (ProcID == WHATB) || (ProcID == WHATBFORUSER) ){
			pcbRet = new C_Buffer( sOut.lTam - sizeof( int ) );
			if( !pcbRet ){	// sem memoria, considere um erro de rede; trate-o
				delete pcgslServers;
				return ( NULL );
			}

			pcbRet->PutData( (void*) (sOut.szBuffer + sizeof( int )), sOut.lTam - sizeof( int ) );
			pcbRet->Rewind();
			pAuxList = MakeAllBasesList( *pcbRet );
			delete pcbRet;
			ClntFree( (void *)sOut.szBuffer );  // dealoca o que veio do RPC

			/* adicionamos a lista pAuxList no final do listão pReturn */
			if ( pAuxList != NULL ) {
				if ( pReturn == NULL ) {
					pReturn = new( LBSC_AllBasesList );
				}
				(*pReturn) << (*pAuxList); 
			}
		}
	}
	
	delete pcgslServers;
	if( (ProcID == WHATS) || (ProcID == WHATSFORUSER) ){
		if ( stricmp(szReturn, "") == 0 ) {
		// este metodo eh estatico; nao tem como chamar o LastError do LBS
			::SetLastError((DWORD) (LBSE_NETERROR | 0x20000000) );	
		}
		return( (void*)szReturn );
	} else {
		return( (void*)pReturn );
	}
}


void	
LBSC_Session::StBreakSecurity( int iSecurityMask, const char *szServer )
{
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)szServer ) ){
		return;
	}
		
	TSRIn_BreakSecurity InPar;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.lSecurityMask = iSecurityMask;
	InPar.sCtrlInfo.lClntTimeStamp = lClntTimeStamp;
	strcpy((char *)InPar.sCtrlInfo.szClientName, szClientName);

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_BreakSecurity DupInPar;
		RpcTryExcept {
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			RPC_Session_StBreakSecurity( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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
	}
}


void	
LBSC_Session::BreakSecurity( int iSecurityMask )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}
		
	TSRIn_BreakSecurity InPar;

	memset( &InPar, 0, sizeof( InPar ));

	InPar.lSecurityMask = iSecurityMask;
	InPar.sCtrlInfo = ObtemControlInfo();

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_BreakSecurity DupInPar;
		RpcTryExcept {
			Duplicate( InPar, &DupInPar );
			Criptografa( DupInPar );

			RPC_Session_BreakSecurity( DupInPar );
			bNetError = FALSE;
			bRetry = FALSE;

			Free( DupInPar );
		}
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
	}
}


/*************************************/
int
LBSC_Session::ValidUser( const LBSC_Ticket *pTicket, const char *szUserName, 
						const char *szPassword )
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
	InPar.szBaseName					=	(unsigned char*)szUserName;

	if ( szPassword ) {
		strncpy( (char *)InPar.szPassword, szPassword, PASSWORDSIZE );
	}

	InPar.lSessionObj					= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_DeleteUDB	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_ValidUser(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
LBSC_Session::GetGroups( const char *szUserName, const char *szUDBName, 
										const char *szServerName )
{
	char	*szRet;

	if ( !szUserName || !szServerName || !szUDBName ) {
		return( NULL );
	}

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)szServerName ) ) {
		return( NULL );
	}

	TSRNetInfo InPar;
	memset(&InPar, 0, sizeof(InPar));

	strcpy( (char *)InPar.strUserName, szUserName);
	strcpy( (char *)InPar.strUDBName, szUDBName);

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRNetInfo DupInPar;
		RpcTryExcept{
			Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char *) RPC_Session_StGetGroups( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
		RpcExcept(1){
				Free( DupInPar );

				bRetry = LBSC_ClntNet::EnviaNovaRPC();
				ulExceptionCode = RpcExceptionCode();
			
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {
		LBSC_ClntNet::TrataErroRPC( (char *)szServerName , ulExceptionCode);
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


//
//	Retorna se duas maquinas sao iguais
//					 
int
MesmosHosts( char *szHost1, char *szHost2 )
{
	if ( szHost1 == NULL || szHost2 == NULL )
		return 0;

	while ( *szHost1 && *szHost2 ) {
		if (toupper(*szHost1++) != toupper(*szHost2++) )
			return 0;
	}

	
	if ( !*szHost1 && !*szHost2 )	// sao iguais
		return 1;

	return 0;
}

//
//	Retorna o int relativo ao string representando o protocolo
//
int
QualIntProto( char *szProto )
{
	if ( !szProto ) {
		return 0;
	}

	if ( stricmp( szProto, TCP_STR ) == 0 ) {
		return LBSPROTO_TCPIP;
	}

	if ( stricmp( szProto, NB_STR ) == 0 ) {
		return LBSPROTO_NETBEUI;
	}

	if ( stricmp( szProto, NP_STR ) == 0 ) {
		return LBSPROTO_NAMEDPIPE;
	}

	return 0;
}


//
//	Retorna o string relativo ao int representando o protocolo
//
const char *
QualStrProto( int iProto )
{
	static char *szProtoStrings[]= {TCP_STR, NB_STR, NP_STR };

	switch ( iProto ) {
	case LBSPROTO_TCPIP:
		return szProtoStrings[0];

	case LBSPROTO_NETBEUI:
		return szProtoStrings[1];

	case LBSPROTO_NAMEDPIPE:
		return szProtoStrings[2];

	default :
		return "";
	}

}


/*************************************/
int
LBSC_Session::SetBaseForMaintenance( const LBSC_Ticket *pTicket, const char *szBaseName, 
									 const char *szUserName, const char *szWarningMsg, BOOL bSet )
{
	int iRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_MaintBase	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.sTicket						= BuildTickBuff( pTicket );
	InPar.szBaseName					= (unsigned char*)szBaseName;
	InPar.szUserName					= (unsigned char*)szUserName;
	InPar.szWarningMsg					= (unsigned char*)szWarningMsg;
	InPar.bSet							= bSet;
	InPar.lSessionObj					= this->obj;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_MaintBase	DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = (int)RPC_Session_SetBaseForMaintenance( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
LBSC_Session::GetDefaultWarningMsg()
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

	       		szRet = (char*) RPC_Session_GetDefaultWarningMsg( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
LBSC_Session::GetBaseWarningMsg( const char *szBaseName )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_What InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_What));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.szDataBaseName = (unsigned char*) szBaseName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_What DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*) RPC_Session_GetBaseWarningMsg( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
LBSC_Session::GeMaintBaseUserName( const char *szBaseName )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_What InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_What));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.szDataBaseName = (unsigned char*) szBaseName;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_What DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*) RPC_Session_GeMaintBaseUserName( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
/*******************************/
/*	21/09/98																			*/	
/*	ATENCAO: Verificar se o RPC destroi a estrutura de retorno. Se sim duplicar o vetor */
/*	de LBSC_MaintBase da estrtura antes e retornar a copia.								*/
/*******************************/
LBSC_MaintBase *
LBSC_Session::GetReservedMaintBases( const LBSC_Ticket *pTicket )
{
	TSROut_MaintBase	Ret;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( NULL );
	}

	TSRIn_TicketPar InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj	=	this->obj;
	InPar.sTicket = BuildTickBuff( pTicket );
			
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_TicketPar DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		Ret = RPC_Session_GetReservedMaintBases(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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

	
	return( (LBSC_MaintBase*)(Ret.psMaintBase) );
}


int 
LBSC_Session::ConvertBase( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_OpenBase InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_OpenBase));
	int iRet = 0;

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		=	this->obj;	
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szBaseName		=	( unsigned char * ) szBaseName;
	InPar.szBasePassword	=	( unsigned char * ) szBasePassword;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OpenBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		iRet = RPC_Session_ConvertBase(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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


BOOL 
LBSC_Session::NeedReprocOnConvert( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword )
{ 
	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return( LBSE_NETERROR );
	}

	TSRIn_OpenBase InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_OpenBase));
	BOOL bRet = TRUE;

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj		=	this->obj;	
	InPar.sTicket = BuildTickBuff( pTicket );
	InPar.szBaseName		=	( unsigned char * ) szBaseName;
	InPar.szBasePassword	=	( unsigned char * ) szBasePassword;

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_OpenBase DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		bRet = RPC_Session_NeedReprocOnConvert(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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

	return( bRet );
}


TInstalInfo	
LBSC_Session::GetInstalInfo( const char * szServer )
{
	TSROut_InstalInfo OutPar;
	TInstalInfo tiiInfo;
	memset( (void*) &OutPar, 0, sizeof(OutPar));
	memset( (void*) &tiiInfo, 0, sizeof(tiiInfo));

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)szServer ) ){
		return( tiiInfo );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		RpcTryExcept{

	       		OutPar = RPC_Session_GetInstalInfo();
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
		LBSC_ClntNet::TrataErroRPC( (char *)szServer  , ulExceptionCode);
		return( tiiInfo );
	}

	tiiInfo.szSerialNum = (char *)OutPar.szSerialNum;
	tiiInfo.szOwnerName = (char *)OutPar.szOwnerName;
	tiiInfo.szCompanyName = (char *)OutPar.szCompanyName;
	return( tiiInfo );
}


const char *
LBSC_Session::GetReinstallPath()
{
	return( szReinstallPath );
}


char *
LBSC_Session::WhatUDBsForUser( const char *szUserName, const char *szPassword, const char *szServer )
{
	char	*szRet;

	unsigned long ulExceptionCode = 0;
	if( !LBSC_ClntNet::GetRPCHandle( (char *)szServer ) ){
		return( NULL );
	}

	TSRIn_UserGenInfos InPar;
	memset( (void*) &InPar, 0, sizeof(TSRIn_UserGenInfos));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lSessionObj = this->obj;
	InPar.szUserName = (unsigned char*)szUserName;

	if ( szPassword ) {
		strncpy( (char *)InPar.szOldPassword, szPassword, PASSWORDSIZE );
	}

	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		TSRIn_UserGenInfos DupInPar;
		RpcTryExcept{
			::Duplicate( InPar, &DupInPar );
				Criptografa( DupInPar );

	       		szRet = (char*) RPC_Session_WhatUDBsForUser(  DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
		}
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
LBSC_Session::GetUDBTimeInfo( struct stat *psInfo )
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

	       		OutPar = RPC_Session_GetUDBTimeInfo( DupInPar );
				bNetError = FALSE;
				bRetry = FALSE;

				Free( DupInPar );
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
	ClntFree( (void *)OutPar.szBuffer );  // dealoca o que veio do RPC

	return( iRet );

}

