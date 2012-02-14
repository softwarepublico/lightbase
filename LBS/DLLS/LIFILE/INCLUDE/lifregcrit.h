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

#include	<critsect.h>

// classe para tratamento de regioes criticas
class	C_GlobalFileCritSect : public C_CritSect<2>	// 2 = numero de regioes criticas
{
public:
	C_GlobalFileCritSect()
	{
		UseCriticalSection( TRUE );
	}

};

extern	C_GlobalFileCritSect	*_pcGlobalFileCritSect;

#define	CRITSECT1	1

// classe para tratamento de regioes criticas
class	C_GlobalLogCritSect : public C_CritSect<2>	// 1 = numero de regioes criticas
{
public:
	C_GlobalLogCritSect()
	{
		UseCriticalSection( TRUE );
	}

};

