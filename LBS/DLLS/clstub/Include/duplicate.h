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

