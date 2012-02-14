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
// Módulo      : LBS_Http.h
// Descrição   :
//	
// Programador : Alessandro Araújo Jatobá
//				 Adriano S. R. Souza
//
//			26/10/1998

#ifndef	_LBS_HTTP_H_
#define	_LBS_HTTP_H_

#include <IPWorks.h>


class LBSC_Http : public HTTP
{
public:
	long	lContentPos;
	long	lContentSize;
	char	*szContent;
	char	*szRedirectLocation;
	char	szContentType[ 128 ];
	long	lRedirectCount;

	LBSC_Http();
	~LBSC_Http();
	const char* ContentType();
    IPWCALL INT SetAction(INT iAction);
	IPWCALL virtual INT FireTransfer(LONG &lBytesTransferred, LPSTR &lpText, USHORT &lenText);
	IPWCALL virtual INT FireStartTransfer();
	IPWCALL virtual INT FireHeader(LPSTR &lpszField, LPSTR &lpszValue);
	IPWCALL virtual INT FireError(USHORT &usErrorCode, LPSTR &lpszDescription);
	IPWCALL virtual INT FireConnected(USHORT &usStatusCode, LPSTR &lpszDescription);
	IPWCALL virtual INT FireDisconnected(USHORT &usStatusCode, LPSTR &lpszDescription);
	IPWCALL virtual INT FireEndTransfer();

private:
	BOOL IsHTMLRedirect( void );
};


#endif	// _LBS_HTTP_H_



