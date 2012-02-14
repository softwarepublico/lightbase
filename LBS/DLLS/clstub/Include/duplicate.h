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
//	Duplica/detona estruturas utilizando-se dos metodos de 
//	serializacao usados no modulo socket
//
//	Vladimir Catao - 29.10.96
//

#ifndef	_DUPLICATE_H_
	#define _DUPLICATE_H_
#endif	// _DUPLICATE_H_

#include <rpcserial.h>
#include <rpcdce.h>

template <class X>	
void 
Duplicate( X tSource, X *ptDest )
{
	if ( !ptDest ) {
		RpcRaiseException( RPC_S_CALL_FAILED );
	}

	memset( ptDest, 0, sizeof(X) );

	RPC rpcObj;

	unsigned char *szBuff = new unsigned char[rpcObj.SizeOf(tSource)];
	if ( !szBuff ) {
		RpcRaiseException( RPC_S_CALL_FAILED );
	}

	rpcObj.Serializa( tSource, szBuff );
	rpcObj.Deserializa( ptDest, szBuff );
	delete szBuff;
}


template <class X>
void
Free( X tDest )
{
	RPC rpcObj;

	rpcObj.Delete( tDest );
}

