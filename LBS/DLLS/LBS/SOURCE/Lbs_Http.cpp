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
// Módulo      : LBS_Http.cpp
// Descrição   :
//	
// Programador : Alessandro Araújo Jatobá
//				 Adriano S. R. Souza
//
//			26/10/1998


#ifndef	_LBS_HTTP_H_
#include <LBS_Http.h>
#endif
#include <lbsdefs.h>

#include <SERVERCONFIG.h>

#define MAXREDIRECTCOUNT	5

void *LBS_Realloc( void *pvOrigBuf, int iOldSize, int iNewSize );

LBSC_Http::LBSC_Http()
{
	lContentPos = 0;
	lContentSize = 0;
	szContent = NULL;
	szContentType[ 0 ] = '\0';
	szRedirectLocation = NULL;
	if ( LBSC_ServerConfig::HTTPProxyPort() > 0 ) {
		SetProxyPort( LBSC_ServerConfig::HTTPProxyPort() );
		SetProxyServer( (char *)LBSC_ServerConfig::HTTPProxyServer() );
	}
	lRedirectCount = 0;
}

LBSC_Http::~LBSC_Http()
{
	if( szContent ){
		delete szContent;
		szContent = NULL;
	}
}

const char* LBSC_Http::ContentType()
{
	return( (const char*) szContentType );
}

IPWCALL INT LBSC_Http::FireTransfer(LONG &lBytesTransferred, LPSTR &lpText, USHORT &lenText)
{
	if( !szContent || ((lContentPos + lenText ) > lContentSize) ){
		szContent = (char*)LBS_Realloc( szContent, lContentSize + 1, lContentSize + lenText + 1 );
		lContentSize += lenText;
	}

	if( szContent ){
		memcpy( szContent + lContentPos, lpText, lenText );
		lContentPos += lenText;
		szContent[ lContentPos ] = '\0';
	}
	else {
		lContentSize = 0;
	}
	return 0;
}

IPWCALL INT LBSC_Http::FireStartTransfer()
{
	return 0;
}

IPWCALL INT LBSC_Http::FireHeader(LPSTR &lpszField, LPSTR &lpszValue)
{
	if( stricmp( lpszField, "Content-Length" ) == 0 ){
		lContentPos = 0;
		lContentSize = atoi( lpszValue );
		if ( szContent ) {
			delete szContent;
			szContent = NULL;
		}
		szContent = new char [ lContentSize + 1 ];
		if( szContent ){
			szContent[ 0 ] = '\0';
		}
	} else if( stricmp( lpszField, "Content-Type" ) == 0 ){
		strncpy( szContentType, lpszValue, 127 );
		szContentType[127] = '\0';
	} else if ( stricmp( lpszField, "Location" ) == 0 && lpszValue ){
		long lSize = strlen( lpszValue );
		if ( szRedirectLocation ) {
			delete szRedirectLocation;
			szRedirectLocation = NULL;
		}
		szRedirectLocation = new char [ lSize + 1 ];
		if( szRedirectLocation ){
			strcpy ( szRedirectLocation, lpszValue );
		}
	}
	return 0;
}

IPWCALL INT LBSC_Http::FireError(USHORT &usErrorCode, LPSTR &lpszDescription)
{
	int iErr = usErrorCode;
	return 0;
}

IPWCALL INT LBSC_Http::FireConnected(USHORT &usStatusCode, LPSTR &lpszDescription)
{
	return 0;
}

IPWCALL INT LBSC_Http::FireDisconnected(USHORT &usStatusCode, LPSTR &lpszDescription)
{
	return 0;
}

IPWCALL INT LBSC_Http::FireEndTransfer()
{
	return 0;
}

char *MyStriStr( char *szStr, char *szFind )
{
	if ( !szFind ) {
		return NULL;
	}
	int iLen = strlen(szFind);
	while ( szStr && *szStr != '\0' ) {
		if ( strnicmp( szStr, szFind, iLen ) == 0 ) {
			return szStr;
		}
		szStr++;
	}
	return NULL;
}


IPWCALL INT LBSC_Http::SetAction(INT iAction)
{
	int iErr = HTTP::SetAction( iAction );
	char *szErr = HTTP::GetLastError();
	BOOL bRedirect = (iErr != 0 && szErr) ? 
						( strstr( szErr, "300 " ) || 
						strstr( szErr, "301 " ) ||
						strstr( szErr, "302 " ) ||
						strstr( szErr, "303 " ) ||
						strstr( szErr, "304 " ) ||
						strstr( szErr, "305 " ) ||
						strstr( szErr, "307 " ) ) :
					IsHTMLRedirect();

	if ( bRedirect ) {
		// vamos tratar o redirect

		char *szCurURL = GetURL();

		if ( lRedirectCount < MAXREDIRECTCOUNT && szRedirectLocation && szCurURL ) {

			int iSize = strlen(szCurURL) + strlen(szRedirectLocation) + 10;
			char *szNewURL = new char[ iSize ];
			if ( !szNewURL ) {
				return iErr;
			}
			memset( szNewURL, 0, iSize );

			// tratar o redirect
			lRedirectCount++;
			if ( MyStriStr( szRedirectLocation, "http://" ) ) {
				// novo endereco ja esta completamente especificado
				strcpy( szNewURL, szRedirectLocation );
			} else if ( szRedirectLocation[0] == '/' || strstr (szRedirectLocation, "%5C") ) {
				// novo endereco esta na raiz do servidor atual
				strcpy( szNewURL, "http://" );
				strcat( szNewURL, GetURLServer() );
				strcat( szNewURL, "/" );
				strcat( szNewURL, szRedirectLocation[0] == '/' ? 
										szRedirectLocation+1 : 
										szRedirectLocation+3 );
			} else {
				// novo endereco eh relativo ao diretorio da pagina atual
				strcpy( szNewURL, "http://" );
				strcat( szNewURL, GetURLServer() );

				char *szSlash = strchr( GetURLPath(), '/' );
				char *szLastSlash = szSlash;
				while ( szSlash ) {
					szLastSlash = szSlash;
					szSlash = strchr( szSlash + 1, '/' );
				}

				if ( szLastSlash ) {
					strncat( szNewURL, GetURLPath(), szLastSlash - GetURLPath() + 1);
				}
				strcat( szNewURL, szRedirectLocation );
			}

			LBSC_Http cHttp;
			cHttp.lRedirectCount = lRedirectCount;

			if( cHttp.SetWinsockLoaded( TRUE ) == 0 ){
				if( cHttp.SetURL( szNewURL ) == 0 ) {
					if ( cHttp.SetAction( HTTP_GET ) == 0 ) {
						iErr = 0;
						if ( cHttp.szContent ) {
							lContentSize = cHttp.lContentSize;
							szContent = new char [lContentSize + 1];
							if ( szContent ) {
								strcpy( szContent, cHttp.szContent );
								strcpy( szContentType, cHttp.szContentType );
							}
						}
					}
				}
			}
			delete szNewURL;
		}
	}

	return iErr;
}

BOOL
LBSC_Http::IsHTMLRedirect( void )
{
	char *szInicio = MyStriStr( szContent, "<meta");
	if ( !szInicio ) {
		return FALSE;
	}

	char *szFim = MyStriStr( szInicio+1, ">" );
	if ( !szFim ) {
		return FALSE;
	}

	szInicio = MyStriStr( szInicio+1, "http-equiv" );
	if ( !szInicio || szInicio > szFim ) {
		return FALSE;
	}

	szInicio = MyStriStr( szInicio+1, "refresh" );
	if ( !szInicio || szInicio > szFim ) {
		return FALSE;
	}

	szInicio = MyStriStr( szInicio+1, "url" );
	if ( !szInicio || szInicio > szFim ) {
		return FALSE;
	}

	szInicio = strchr( szInicio+1, '=' );
	if ( !szInicio || szInicio > szFim ) {
		return FALSE;
	}

	int iUrlSize = szFim-szInicio + 1;
	if ( szRedirectLocation ) {
		delete szRedirectLocation;
	}
	szRedirectLocation = new char [iUrlSize];
	if ( !szRedirectLocation ) {
		return FALSE;
	}
	memset( szRedirectLocation, 0, iUrlSize );
	char *szRedirectLocationAux = szRedirectLocation;

	for ( char *szAux = szInicio+1; *szAux && szAux < szFim; szAux++ ) {
		if ( *szAux != ' ' && *szAux != '"' && *szAux != '\'' ) {
			*szRedirectLocationAux++ = *szAux;
		}
	}

	return TRUE;
}
