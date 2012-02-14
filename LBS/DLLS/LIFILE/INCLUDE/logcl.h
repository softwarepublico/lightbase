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


#ifndef	_LOGCL_H_
#define	_LOGCL_H_

#ifndef	_FILECL_
#include	<filecl.h>
#endif

// para imprimir um log, basta chamar PRINTLOG( "nome_do_modulo", "nome_do_metodo", 
// numero de parametros, parametros_com_nomes_e_valores,
// numero de variaveis_extras, variaveis_extras_com_nomes_e_valores );
#ifdef	_USING_LOG_
	#define	USELOG(x, y)	C_Log	x (y);
	#define	EXTLOG(x)		extern	C_Log	x;
	#define	INITLOG(x)		x .InitLog();
	#define	ENDLOG(x, y)	x .EndLog( y );
	#define	PRINTLOG(x, y)	x .SetParms( __FILE__, __LINE__ ); x .PrintLog y
	#define	FLUSHLOG(x)		x .FlushLog();
#else
	#define	USELOG(x,y)
	#define	EXTLOG(x)
	#define	INITLOG(x)
	#define	ENDLOG(x,y)
	#define	PRINTLOG(x,y)
	#define	FLUSHLOG(x)
#endif

#define	LOGLINESIZE	(1024)

class C_GlobalLogCritSect;
extern	C_GlobalLogCritSect	*_pcGlobalLogCritSect;

class _LIFILECLASS C_Log
{
private:
	char	szModuleName[ 256 ];
	char	szFileName[ 256 ];
	int		iLineNum;
	char 	szBuffer[ LOGLINESIZE ];
	char 	szLine[ LOGLINESIZE ];
	char 	szFmtAux[ LOGLINESIZE * 2 ];
	int		iMypid;
	HANDLE	hWriterEvent ;
	HANDLE	hFlusherEvent;
	HANDLE	hInitEvent;
	void	GetDateTime( char * );
	void	WriteLine( char * );
	void	OpenEvents();
	void	TerminateLog();
	void	OpenFile();

public:
			C_Log( char * );
			~C_Log();
	void	SetParms( char *, int );
	void	PrintLog( char *, ... );
	void	FlushLog();
	void	EndLog( HANDLE );
	void	InitLog();
};

class	C_LogCritSect
{
	int		iLastSectUsed;
	C_Log	*pObj;

public:
	C_LogCritSect( C_Log *pObjPar, int iNumCritSect );
	~C_LogCritSect();
	void EnterCriticalSection();
	void LeaveCriticalSection();
};

class	C_LogMutex
{
	HANDLE	hMutex;

public:
	C_LogMutex()
	{
		hMutex = CreateMutex( NULL, FALSE, "LIFILELOGMUTEX" );
		if( hMutex ){
			WaitForSingleObject( hMutex, INFINITE );
		}
	}
	~C_LogMutex()
	{
		if( hMutex ){
			ReleaseMutex( hMutex );
			CloseHandle( hMutex );
		}
	}
	void EnterMutex()
	{
		if( hMutex ){
			WaitForSingleObject( hMutex, INFINITE );
		}
	}
	void LeaveCriticalSection()
	{
		if( hMutex ){
			ReleaseMutex( hMutex );
		}
	}
};


#endif	// _LOGCL_H_
