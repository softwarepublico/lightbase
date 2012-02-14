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

//
// M�dulo      : LBS_Http.h
// Descri��o   :
//	
// Programador : Alessandro Ara�jo Jatob�
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



