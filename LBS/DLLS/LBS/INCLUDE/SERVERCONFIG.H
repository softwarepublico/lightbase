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

#ifndef	_SERVERCONFIG_H_
#define	_SERVERCONFIG_H_

class LBSC_ServerConfig
{
private:
	static char szLogFileDir[MAXPATH+1];
	static char szDirBase[FULLNAMESIZE+1];
	static char szTempDir[FULLNAMESIZE+1];
	static char szReferenceDirBase[MAXPATH+1];
	static char szAnonymousUserName[USERNAMESIZE+1];
	static char szBasesFileName[FILENAMESIZE+1];
	static char szServerName[SERVERNAMESIZE+1];
	static char szDefUdbName[MAXPATH+1];
	static char szSerial[FULLNAMESIZE+1];
	static char szName[FULLNAMESIZE+1];
	static char szCompany[FULLNAMESIZE+1];
	static BOOL bUsingCompress;
	static BOOL bUserCacheEnabled;
	static int iLockTimeSleep;
	static int iLockTimeOut;
	static int iStopIndex;
	static int iMaxMemForIndex;
	static int iOccTimeOut;
	static int iCounterLockTimeOut;
	static int iHTTPProxyPort;
	static char szHTTPProxyServer[MAXPATH+1];
	static int iMaxInvalidLoginAttempts;
	static int iPasswordExpireInterval;
	static BOOL bPasswordValidation;
	static int iMaxStoredPasswords;
	static int iMaxLogFiles;
	static int iMinUserPasswordSize;
	static BOOL bReadOnlyFileSystem;	

public:

	static void Init();
	static const char *LogFileDir();
	static const char *DirBase();
	static const char *TempDir();
	static const char *ReferenceDirBase();
	static const char *AnonymousUserName();
	static const char *BasesFileName();
	static const char *ServerName();
	static const char *DefUdbName();
	static const char *Serial();
	static const char *Name();
	static const char *Company();
	static BOOL UsingCompress();
	static BOOL UserCacheEnabled();
	static int LockTimeSleep();
	static int LockTimeOut();
	static int StopIndex();
	static int MaxMemForIndex();
	static int OccTimeOut();
	static int CounterLockTimeOut();
	static int HTTPProxyPort();
	static const char *HTTPProxyServer();
	static int MaxInvalidLoginAttempts();
	static int PasswordExpireInterval();
	static BOOL PasswordValidation();
	static int MaxStoredPasswords();
	static int MaxLogFiles();
	static int MinUserPasswordSize();
	static BOOL ReadOnlyFileSystem();	
};

#endif // _SERVERCONFIG_H_