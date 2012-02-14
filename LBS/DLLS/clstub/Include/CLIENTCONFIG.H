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

#ifndef	_CLIENTCONFIG_H_
#define	_CLIENTCONFIG_H_

class LBSC_ClientConfig
{
private:
	static char szLogFileDir[MAXPATH+1];
	static BOOL bCache;
	static BOOL bAclCache;
	static BOOL bRepCache;
	static BOOL bOccurCache;
	static BOOL bSlotCache;
	static BOOL bUseAuthentication;
public:

	static void Init();
	static BOOL Cache();
	static BOOL AclCache();
	static BOOL RepCache();
	static BOOL SlotCache();
	static BOOL OccurCache();
	static BOOL UseAuthentication();
};

#endif // _CLIENTCONFIG_H_