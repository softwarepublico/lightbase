/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


//
//	Definicoes para o modulo de administracao do LBS Cliente-Servidor
//
//

#ifndef _ADMDEFS_H_
#define _ADMDEFS_H_

#define LBSPORTKEY				"PORTA"
#define LBSPROTOKEY				"PROTOCOLO"
#define LBSTMOUTKEY				"TIMEOUT"
#define CLIENTINILBSSECTION		"CLIENTSECTION"
#define CLIENTININAMESECTION	"NAMESECTION"
#define CLIENTINIFILE			"LBSCLNT.INI"
#define CLIENTINIHOSTSECTION	"HOSTS"
#define LBSDEFPORT32S_TCPIP		10247
#define LBSDEFPORT_TCPIP		10247
#define LBSDEFPORT_NETBEUI		192
#define LBSMAXPORT_TCPIP		10277
#define LBSMAXPORT_NETBEUI		222
#define MAXATTACHRETRIES		7
#define LBSMACHINEKEY			"COMPUTER_NAME"
#define LBSDELTA_PORT			5
#define DELIMSERV_SET			","

#endif	// _ADMDEFS_H_
