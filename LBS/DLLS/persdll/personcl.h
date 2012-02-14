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

#ifndef _PERSONCL_H_
#define _PERSONCL_H_

#include	<windows.h>
#include	<time.h>
#include	<defclass.h>

#define MAXTAG		40
#define MAXDATAINST	8
#define	MAXNOME		80
#define	MAXCOMPANY	80
#define	MAXSIZESERIAL	32
#define	MAXCHECKSUM	2
#define	MAXTIPO		2

#define	MAXNUMTTY	32
#define MAXDATA		32
#define MAXSERIALPART	32


#define	PE_PERS		'1' 
#define PE_ERROR	-1

#define PE_OK		0

#define PE_INSTALA	1
#define PE_TYPE		2
#define PE_ACTKEY	3
#define PE_SERIAL	4
#define PE_PARAM	5
#define PE_TIMEBOMB	6
#define PE_LOCALIZA	7
#define PE_POSERROR	8
#define PE_WRITEERROR	9
#define PE_DATA		10

#define PE_UNKNOWN	1001
#define	PE_REDE		1002
#define	PE_SERVER	1003
#define	PE_MONO		1004
#define	PE_CLIENT	1005
#define	PE_RUNTIME	1006

#define PE_STRREDE	"rd"
#define	PE_STRSERV	"sr"
#define	PE_STRMONO	"mn"
#define	PE_STRCLNT	"cl"
#define	PE_STRRUNT	"rt"


/* definicoes dos offsets dos membros do buffer de personalizacao */
#define	O_TAG		0
#define O_DATAINST	(O_TAG+MAXTAG+1)
#define	O_NOME		(O_DATAINST+MAXDATAINST+1)
#define	O_COMPANY	(O_NOME+MAXNOME+1)
#define	O_SERIE		(O_COMPANY+MAXCOMPANY+1)
#define	O_CHECKSUM	(O_SERIE+MAXSIZESERIAL+1)
#define O_TIPO		(O_CHECKSUM+MAXCHECKSUM) // Nao tem + 1
#define	O_PERS		(O_TIPO+MAXTIPO+1)



#define	TAG(xy)			((xy) + O_TAG)
#define DATAINST(xy)	((xy) + O_DATAINST)
#define	NOME(xy)		((xy) + O_NOME)
#define NAMECOMPANY(xy)	((xy) + O_COMPANY)
#define	SERIE(xy)		((xy) + O_SERIE)
#define	CHECKSUM(xy)	((xy) + O_CHECKSUM)
#define TIPO(xy)		((xy) + O_TIPO)
#define	PERS(xy)		(xy[O_PERS])

typedef char	T_PERS[ O_PERS + 1 ];

typedef struct {
   DWORD wStructLen;   // The length of the structure
   DWORD hWnd;         // Handle to main window
   DWORD wMaxReplaces; // Maximum number of replaces
   DWORD wRepNameWidth;// The width of a replace name
   DWORD wRepStrWidth; // The width of each replace string
   DWORD wCurrReps;    // Current number of replace strings
   char *lpszRepName;  // The actual replace names
   char *lpszRepStr;   // The actual replace values
   DWORD bRunMode;     // The installation mode
   DWORD fLogFile;     // A file handle to the log file
   char *lpszParam;    // String parameter from Wise Installation System
} DLLCALLPARAMS;

typedef DLLCALLPARAMS *LPDLLCALLPARAMS;

int _LBSFUNC			SetType( char *szFileName, char *szType );
int _LBSFUNC			Personalize( char *szFileName, char *szName, char *szCompany, char*szSerial, char *szActKey );
BOOL _LBSFUNC			ValidKey( char *szSerial, char *szActKey );
long _LBSFUNC			GetUsers();
char _LBSFUNC			*GetData();
char _LBSFUNC			*GetType();
char _LBSFUNC			*GetSerialPart();
char _LBSFUNC			*GetSerialNumber();
int _LBSFUNC			CheckForRun();
char _LBSFUNC			*GetName();
char _LBSFUNC			*GetCompany();
char _LBSFUNC			*GetDataInst();
int _LBSFUNC			GetTypeInt();
_LBSFUNC BOOL WINAPI	CheckKey(LPDLLCALLPARAMS parms);
_LBSFUNC BOOL WINAPI	ExecPers(LPDLLCALLPARAMS parms);
long _LBSFUNC 			GetUsersFromSN( char *szSerialAux );
const char _LBSFUNC		*GetAppIniPath( const char *szIni );


static FILE*	localiza( char *szArq, T_PERS tpPers );
static int		IsUncrypt();
static BOOL		ValidType( char *szType );
static int		CmpDatas( time_t t1, time_t t2 );
static int		CalculaDeslocamentos( char *szSerie );
static char*	istrncpychar( register char *dest, register char *orig, register int tam, register int separ );


#endif	// _PERSONCL_H_
