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

#include <windows.h>
#include <stdio.h>
extern "C" {
#include <personcl.h>
}
#include <admdefs.h>
#include <lbsnetcl.h>
#include <clientconfig.h>

BOOL LBSC_ClientConfig::bCache = TRUE;
BOOL LBSC_ClientConfig::bAclCache = TRUE;
BOOL LBSC_ClientConfig::bRepCache = TRUE;
BOOL LBSC_ClientConfig::bSlotCache = TRUE;
BOOL LBSC_ClientConfig::bOccurCache = TRUE;
BOOL LBSC_ClientConfig::bUseAuthentication = TRUE;


void 
LBSC_ClientConfig::Init()
{
	bCache = GetPrivateProfileInt(  CLIENTINILBSSECTION, "CACHE", 1, LBSC_ClntNet::ObtemClientIniName());
	bAclCache = GetPrivateProfileInt(  CLIENTINILBSSECTION, "ACLCACHE", 1, LBSC_ClntNet::ObtemClientIniName());
	bRepCache = GetPrivateProfileInt(  CLIENTINILBSSECTION, "REPCACHE", 1, LBSC_ClntNet::ObtemClientIniName());
	bSlotCache = GetPrivateProfileInt(  CLIENTINILBSSECTION, "SLOTCACHE", 1, LBSC_ClntNet::ObtemClientIniName());
	bOccurCache = GetPrivateProfileInt(  CLIENTINILBSSECTION, "OCCURCACHE", 1, LBSC_ClntNet::ObtemClientIniName());
	bUseAuthentication = GetPrivateProfileInt(  CLIENTINILBSSECTION, "RPCAUTHENTICATION", 0, LBSC_ClntNet::ObtemClientIniName());
}

BOOL 
LBSC_ClientConfig::Cache()
{
	return bCache;
}

BOOL 
LBSC_ClientConfig::AclCache()
{
	return bAclCache;
}

BOOL 
LBSC_ClientConfig::RepCache()
{
	return bRepCache;
}

BOOL 
LBSC_ClientConfig::SlotCache()
{
	return bSlotCache;
}

BOOL 
LBSC_ClientConfig::OccurCache()
{
	return bOccurCache;
}

BOOL 
LBSC_ClientConfig::UseAuthentication()
{
	return bUseAuthentication;
}

