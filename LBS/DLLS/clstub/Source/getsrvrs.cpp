/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o t�tulo
"LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include <math.h>

#ifndef _CSTRTOK_H_
	#include	<cstrtok.h>  
#endif	// _CSTRTOK_H_

#ifndef _LBSDEFS_H_
	#include <lbsdefs.h>
#endif	// _LBSDEFS_H_

#ifndef _GETSRVRS_H_
	#include <getsrvrs.h>
#endif	// _GETSRVRS_H_

#ifndef _SESSCL_H_
	#include <sesscl.h>
#endif	// _SESSCL_H_


#ifndef _ADMDEFS_H_
	#include <admdefs.h>
#endif	// _ADMDEFS_H_


#ifndef __lbsrpc_h__
	#include	<lbsrpc.h>
#endif	// __lbsrpc_h__

// so pra constar...
class COccurList;
class C_Buffer;

#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_


void
C_GSList::GetServers( NETRESOURCE	*pnrArray )
{
/***
	NETRESOURCE	nrArray [ 5 ];
	HANDLE 		hEnum;
	DWORD		dwEntries = 0xFFFFFFFF;
	DWORD		dwArraySize = 5 * sizeof( NETRESOURCE );
	DWORD 		dwRet;
	
	WNetOpenEnum( RESOURCE_GLOBALNET, RESOURCETYPE_DISK, RESOURCEUSAGE_CONTAINER, 
		pnrArray, &hEnum );
	do{
		dwRet = WNetEnumResource( hEnum, &dwEntries, &nrArray, &dwArraySize );
		if( dwEntries ){						 
			for( int i = 0; i < dwEntries; i++ ){
				if( nrArray [ i ].dwDisplayType == RESOURCEDISPLAYTYPE_SERVER ||
					nrArray [ i ].dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN ){ 
					C_GroupServer *pgs = new C_GroupServer( nrArray [ i ].lpRemoteName );
					if( pgs ){
						if( Add( pgs, TAIL ) != OK ){
							delete pgs;
						}
					}
					if( nrArray [ i ].dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN ){
						GetServers( &(nrArray[ i ]) );
					}
				} else {
					GetServers( &(nrArray[ i ]) );
				}
			}
		}
	} while( dwRet == NO_ERROR || dwRet == ERROR_NO_MORE_ITEMS );
	WNetCloseEnum( hEnum );
*****/

} 

void
C_GSList::GetGroups( NETRESOURCE	*pnrArray )
{
/****
	NETRESOURCE	nrArray [ 5 ];
	HANDLE 		hEnum;
	DWORD		dwEntries = 0xFFFFFFFF;
	DWORD		dwArraySize = 5 * sizeof( NETRESOURCE );
	DWORD 		dwRet;
	
	WNetOpenEnum( RESOURCE_GLOBALNET, RESOURCETYPE_DISK, RESOURCEUSAGE_CONTAINER, 
		pnrArray, &hEnum );
	do{
		dwRet = WNetEnumResource( hEnum, &dwEntries, &nrArray, &dwArraySize );
		if( dwEntries ){						 
			for( int i = 0; i < dwEntries; i++ ){
				if( nrArray [ i ].dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN ){
					C_GroupServer *pgs = new C_GroupServer( nrArray [ i ].lpRemoteName );
					if( pgs ){
						if( Add( pgs, TAIL ) != OK ){
							delete pgs;
						}
					}
				} else {
					GetGroups( &(nrArray[ i ]) );
				}
			}
		}
	} while( dwRet == NO_ERROR || dwRet == ERROR_NO_MORE_ITEMS );
	WNetCloseEnum( hEnum );
****/
} 

void
C_GSList::GetServers( const char *szServer )
{
/*****
	NETRESOURCE nr;
    
    nr.dwScope = RESOURCE_GLOBALNET;
    nr.dwType = RESOURCETYPE_DISK;
    nr.dwDisplayType = RESOURCEDISPLAYTYPE_DOMAIN;
    nr.dwUsage = RESOURCEUSAGE_CONNECTABLE;
    nr.lpLocalName = NULL;
    nr.lpRemoteName = (char*)szServer;
    nr.lpComment = NULL;
    nr.lpProvider = NULL;

	GetServers( &nr );	
****/
} 

void
C_GSList::GetAllGroups( void )
{
	GetGroups( NULL );
}


void
C_GSList::GetServers()
{
	C_GroupServer *cgsNewHost;
	
	First();
	char **pszServers=NULL;

	LBSC_Session::ObtemServidores( &pszServers );

	if ( !pszServers ) {
		return;
	}

	for (int i=0; pszServers[i] != NULL; i++) {
		char szHostInfo[100];
		C_StrTok	cstNewTok;

		strcpy( szHostInfo, pszServers[i]);

		// o nome do servidor pode vir delimitado por uma virgula
		cgsNewHost = new C_GroupServer( cstNewTok.StrTok(szHostInfo, DELIMSERV_SET) );
		if ( cgsNewHost ) {
			Add(cgsNewHost, TAIL);
		}
	}
	
	DeleteVect( pszServers );

	First();
}


C_GroupServer::C_GroupServer( char *szS )
{
	szServer = StrDup( szS );
}


C_GroupServer::~C_GroupServer( void )
{
	if( szServer ){
		delete szServer;
	}
}
