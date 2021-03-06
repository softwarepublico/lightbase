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

