/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o 
t�tulo "LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do 
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
