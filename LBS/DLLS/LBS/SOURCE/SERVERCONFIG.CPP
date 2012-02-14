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
#include <lbsdefs.h>
#include <serverconfig.h>

char LBSC_ServerConfig::szLogFileDir[MAXPATH+1] = { '\0' };
char LBSC_ServerConfig::szDirBase[FULLNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szTempDir[FULLNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szReferenceDirBase[MAXPATH+1] = { '\0' };
char LBSC_ServerConfig::szAnonymousUserName[USERNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szBasesFileName[FILENAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szServerName[SERVERNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szDefUdbName[MAXPATH+1] = { '\0' };
char LBSC_ServerConfig::szSerial[FULLNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szName[FULLNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szCompany[FULLNAMESIZE+1] = { '\0' };
char LBSC_ServerConfig::szHTTPProxyServer[MAXPATH+1] = { '\0' };
BOOL LBSC_ServerConfig::bUsingCompress = FALSE;
BOOL LBSC_ServerConfig::bUserCacheEnabled = TRUE;
int LBSC_ServerConfig::iLockTimeSleep = 0;
int LBSC_ServerConfig::iLockTimeOut = 0;
int LBSC_ServerConfig::iStopIndex = 0;
int LBSC_ServerConfig::iMaxMemForIndex = 0;
int LBSC_ServerConfig::iOccTimeOut = 0;
int LBSC_ServerConfig::iCounterLockTimeOut = 0;
int LBSC_ServerConfig::iHTTPProxyPort = 0;
int LBSC_ServerConfig::iMaxInvalidLoginAttempts = 0;
int LBSC_ServerConfig::iPasswordExpireInterval = 0;
BOOL LBSC_ServerConfig::bPasswordValidation = FALSE;
int LBSC_ServerConfig::iMaxStoredPasswords = 0;
int LBSC_ServerConfig::iMaxLogFiles = 0;
int LBSC_ServerConfig::iMinUserPasswordSize = 0;
BOOL LBSC_ServerConfig::bReadOnlyFileSystem = FALSE;

void 
LBSC_ServerConfig::Init()
{
	GetPrivateProfileString( LBSINILBSSECTION, "LOGFILEDIR", "", szLogFileDir, MAXPATH, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, DIR_BASE_KEY, "", szDirBase, FULLNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, LBSINILIGHTTEMPDIR, "\\tmp", szTempDir, FULLNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, REFERENCEDIRBASE, "", szReferenceDirBase, MAXPATH, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, LBSANONYMOUSNAME, ANONYMOUS_USERNAME, szAnonymousUserName, USERNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, LBSINIBASESFILENAME, LBSINIDEFMSG, szBasesFileName, FILENAMESIZE, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, LBSINISERVERNAME, "LOCALHOST", szServerName, SERVERNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, "DEFUDBNAME", "", szDefUdbName, MAXPATH, LBSINIFILE );
	GetPrivateProfileString( LBSINILBSSECTION, "HTTPPROXYSERVER", "", szHTTPProxyServer, MAXPATH, LBSINIFILE );
	GetPrivateProfileString( "MAIN" /*LBSINIMAINSECTION*/, "SERIAL", "", szSerial, FULLNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( "MAIN" /*LBSINIMAINSECTION*/, "NAME","", szName, FULLNAMESIZE, LBSINIFILE );
	GetPrivateProfileString( "MAIN" /*LBSINIMAINSECTION*/, "COMPANY", "", szCompany, FULLNAMESIZE, LBSINIFILE );

	bUsingCompress = GetPrivateProfileInt( LBSINILBSSECTION, COMPRESSKEY, COMPRESSDEFVAL, LBSINIFILE );
	bUserCacheEnabled = GetPrivateProfileInt( LBSINILBSSECTION, "USERCACHEENABLED", 1, LBSINIFILE );
	iLockTimeSleep = GetPrivateProfileInt( LBSINILBSSECTION, LOCKTIMESLEEPSTR, LOCKTIMESLEEP, LBSINIFILE );
	iLockTimeOut = GetPrivateProfileInt( LBSINILBSSECTION, LOCKTIMEOUTSTR, LOCKTIMEOUT, LBSINIFILE );
	iStopIndex = GetPrivateProfileInt( LBSINILBSSECTION, STOPINDEXSTR, STOPINDEX, LBSINIFILE );
	iMaxMemForIndex = GetPrivateProfileInt( LBSINILBSSECTION, "MAXMEMFORINDEX", 40, LBSINIFILE );
	iOccTimeOut = GetPrivateProfileInt( DCESECTION, LBSOCCTMOUTKEY, 0, LBSINIFILE );
	iCounterLockTimeOut = GetPrivateProfileInt( "CONFIG", "COUNTERLOCKTIMEOUT", 30, GetAppIniPath( "LBFILE" ));
	iHTTPProxyPort = GetPrivateProfileInt( LBSINILBSSECTION, "HTTPPROXYPORT", 0, LBSINIFILE);
	iMaxInvalidLoginAttempts = GetPrivateProfileInt( LBSINISECURITYSECTION, "MAXINVALIDLOGINATTEMPTS", 0, LBSINIFILE);
	iPasswordExpireInterval = GetPrivateProfileInt( LBSINISECURITYSECTION, "PASSWORDEXPIREINTERVAL", 0, LBSINIFILE);
	bPasswordValidation = GetPrivateProfileInt( LBSINISECURITYSECTION, "PASSWORDVALIDATION", 0, LBSINIFILE);
	iMaxStoredPasswords = GetPrivateProfileInt( LBSINISECURITYSECTION, "MAXSTOREDPASSWORDS", 0, LBSINIFILE);
	iMaxLogFiles = GetPrivateProfileInt( LBSINILBSSECTION, "MAXLOGFILES", 0, LBSINIFILE);
	iMinUserPasswordSize = GetPrivateProfileInt( LBSINISECURITYSECTION, "MINUSERPASSWORDSIZE", 0, LBSINIFILE);

	// verificando se o diretorio de bases esta em modo readonly
	// vamos verificar se temos permissao de gravacao no diretorio das bases
	bReadOnlyFileSystem = FALSE;
	char	szAux[ FILENAMESIZE ];
	sprintf( szAux, "%s\\%s", (char*) szDirBase, "ACCESSTEST.TMP" );
	FILE *fp = fopen( szAux, "wb" );
	if ( !fp ){
		bReadOnlyFileSystem = TRUE;
	} else {
		fclose(fp);
		remove( szAux );
	}
}

const char *
LBSC_ServerConfig::LogFileDir()
{
	return szLogFileDir;
}

BOOL
LBSC_ServerConfig::UsingCompress()
{
	return bUsingCompress;
}

int 
LBSC_ServerConfig::LockTimeSleep()
{
	return iLockTimeSleep;
}

int 
LBSC_ServerConfig::LockTimeOut()
{
	return iLockTimeOut;
}

const char *
LBSC_ServerConfig::DirBase()
{
	return szDirBase;
}

int
LBSC_ServerConfig::StopIndex()
{
	return iStopIndex;
}

const char *
LBSC_ServerConfig::TempDir()
{
	return szTempDir;
}

int 
LBSC_ServerConfig::MaxMemForIndex()
{
	return iMaxMemForIndex;
}


const char *
LBSC_ServerConfig::ReferenceDirBase()
{
	return szReferenceDirBase;
}

int
LBSC_ServerConfig::OccTimeOut()
{
	return iOccTimeOut;
}

int 
LBSC_ServerConfig::CounterLockTimeOut()
{
	return iCounterLockTimeOut;
}

const char *
LBSC_ServerConfig::AnonymousUserName()
{
	return szAnonymousUserName;
}

const char *
LBSC_ServerConfig::BasesFileName()
{
	return szBasesFileName;
}

const char *
LBSC_ServerConfig::ServerName()
{
	return szServerName;
}

const char *
LBSC_ServerConfig::DefUdbName() 
{
	return szDefUdbName;
}

BOOL
LBSC_ServerConfig::UserCacheEnabled() 
{
	return bUserCacheEnabled;
}


const char *
LBSC_ServerConfig::Serial()
{
	return szSerial;
}

const char *
LBSC_ServerConfig::Name()
{
	return szName;
}

const char *
LBSC_ServerConfig::Company()
{
	return szCompany;
}

int 
LBSC_ServerConfig::HTTPProxyPort()
{
	return iHTTPProxyPort;
}

const char *
LBSC_ServerConfig::HTTPProxyServer()
{
	return szHTTPProxyServer;
}

int 
LBSC_ServerConfig::MaxInvalidLoginAttempts()
{
	return iMaxInvalidLoginAttempts;
}

int 
LBSC_ServerConfig::PasswordExpireInterval()
{
	return iPasswordExpireInterval;
}

BOOL 
LBSC_ServerConfig::PasswordValidation()
{
	return bPasswordValidation;
}

int 
LBSC_ServerConfig::MaxStoredPasswords()
{
	return iMaxStoredPasswords;
}

int 
LBSC_ServerConfig::MaxLogFiles()
{
	return iMaxLogFiles;
}

int 
LBSC_ServerConfig::MinUserPasswordSize()
{
	return iMinUserPasswordSize;
}

BOOL 
LBSC_ServerConfig::ReadOnlyFileSystem()
{
	return bReadOnlyFileSystem;
}

