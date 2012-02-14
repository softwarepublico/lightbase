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


#ifndef	_CLOG_H_
#include	<logcl.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif
#ifndef	_DATECL_H_
#include	<datecl.h>
#endif
#ifndef	_TIMECL_H_
#include	<timecl.h>
#endif
#ifndef _INC_PROCESS
#include	<process.h>
#endif
#include	<lifregcrit.h>

void	GetAppFullPath( char *Path, int Size );

#define	LOG_SESSION			"LOG"
#define	LIFILEINIFILE		"LBFILE.INI"	// .ini de lifile
#define	LOG_FILENAMEKEY		"LOGFILENAME"
#define	LOG_FILESIZEKEY		"LOGFILESIZE"
#define	LOG_LEVELKEY		"LOGLEVEL"
#define	LOG_MODULESKEY		"LOGMODULES"
#define	BIGBUFFERLINESIZE	(1024)
#define	BIGBUFFERARRAYSIZE	(1024)
#define	BIGBUFFERSIZE		(BIGBUFFERARRAYSIZE * BIGBUFFERLINESIZE)
#define	FLUSHWAITTIME		(5000)

// atributos estaticos da classe C_Log
// (definidos em um segmento de dados compartilhados)
#pragma data_seg(".shsect")
C_File	*_pLogFile = NULL;
int		_iNumFiles = 0;
int		_iMaxFileSize = 0;
int		_iLevel = 0;
int		_iNumBytesWritten = 0;
char	_szModules[ 4096 ] = "";
char	_szBigBuffer[ BIGBUFFERSIZE ] = "";
int		_iWriter = 1;
int		_iFlusher = 0;
BOOL	_bStopService = FALSE;
BOOL	_bStarted = FALSE;
#pragma data_seg()

C_Log	*_pcGlobalLog = NULL;

// niveis de log
#define	NOLOG		0x00
#define	LOGMODULE	0x01
#define	LOGFUNC		0x02
#define	LOGPARMS	0x04
#define	LOGVARS		0x08


/***
***/
C_Log::C_Log( char *szModule )
{
	C_LogCritSect	cCS0( this, CRITSECT0 );

	strncpy( szModuleName, szModule ? szModule : "", 255 );
	strupr( szModuleName );
	iMypid = _getpid();
	hWriterEvent = NULL;
	hFlusherEvent = NULL;
	hInitEvent = NULL;

	if( !szModuleName[0] ){
		char	szFullIniName[ MAXPATH ];

		GetAppFullPath( szFullIniName, MAXPATH-1 );
		strcat( szFullIniName, LIFILEINIFILE );

		GetPrivateProfileString( LOG_SESSION, LOG_MODULESKEY, "*", _szModules, 4095, szFullIniName );
		if( _szModules[ 0 ] == '\0' ){
			strcpy( _szModules, "*" );
		}
		strupr( _szModules );
		
		_iMaxFileSize = GetPrivateProfileInt( LOG_SESSION, LOG_FILESIZEKEY, 0, szFullIniName );
		_iLevel = GetPrivateProfileInt( LOG_SESSION, LOG_LEVELKEY, 0, szFullIniName );

		if( _iLevel > 0 ){
			_pLogFile = new C_File();
		} else {
			_pLogFile = NULL;
		}
		_bStopService = FALSE;
		memset( _szBigBuffer, 0, BIGBUFFERSIZE );

		// criar o arquivo
		OpenFile();
	}
	OpenEvents();

	if( (!hWriterEvent || !hFlusherEvent || !hInitEvent) && _pLogFile ){
		WriteLine( "UNABLE_TO_START_LOG" );
	}

	++_iNumFiles;
}

/***
***/
C_Log::~C_Log()
{
	C_LogCritSect	cCS0( this, CRITSECT0 );

	--_iNumFiles;

	TerminateLog();
}


/***
***/
void
C_Log::SetParms( char *szFile, int iLine )
{
	char	szDrive[ 256 ];
	char	szDir[ 256 ];
	char	szExt[ 10 ];

	if( _pLogFile && _iLevel && _bStarted ){
		if( (strcmp( _szModules, "*" ) == 0) ||	// todos os modulos devem entrar no log
			(strstr( _szModules, szModuleName )) ){	// o modulo corrente eh um dos pedidos
			if( szFile ){
				_splitpath( szFile, szDrive, szDir, szFileName, szExt );
				strcat( szFileName, szExt );
			} else {
				strncpy( szFileName, "Arquivo desconhecido", 255 );
			}
			iLineNum = iLine;
		}
	}
}

/***
***/
void
C_Log::PrintLog( char *szFmt, ... )
{
	if( _pLogFile && _iLevel && szFmt && _bStarted ){
		if( (strcmp( _szModules, "*" ) == 0) ||	// todos os modulos devem entrar no log
			(strstr( _szModules, szModuleName )) ){	// o modulo corrente eh um dos pedidos
			char		szDateTime[ 100 ];
			int			iNumParms = 0;
			int			iNumVars = 0;
			char		*szTok;
			va_list		argptr;
			C_StrTok	cStrTok;

			C_LogCritSect	cCS0( this, CRITSECT0 );

			memset( szBuffer, 0, LOGLINESIZE );

			GetDateTime( szDateTime );

			// montar o szFmtAux a partir da pilha
			va_start( argptr, szFmt );

			int iMaxLog = LOGLINESIZE-200;
			BOOL bOverFlow = (_vsnprintf( szFmtAux, iMaxLog, szFmt, argptr ) == -1);
			va_end( argptr );

			/////////////
			// montar szBuffer a partir do nivel de log setado
			/////////////

			if( !bOverFlow ){
				// nome da funcao/metodo
				szTok = cStrTok.StrTok( szFmtAux, ", " );
				if( szTok ){
					if( _iLevel & LOGFUNC ){
						strcat( szBuffer, szTok );
						strcat( szBuffer, ", " );
					}
					// numero de parametros 
					szTok = cStrTok.StrTok( NULL, ", " );
				}
				if( szTok ){
					// pegar os parametros
					iNumParms = atoi( szTok );
					if( iNumParms < 0 ){
						iNumParms = 0;
					}
					for( int i = 0; i < iNumParms; i++ ){
						// nome do parametro
						szTok = cStrTok.StrTok( NULL, ", " );
						if( !szTok ){
							return;
						}
						if( _iLevel & LOGPARMS ){
							strcat( szBuffer, szTok );
							strcat( szBuffer, " = " );
						}

						// valor do parametro
						szTok = cStrTok.StrTok( NULL, ", " );
						if( !szTok ){
							return;
						}
						if( _iLevel & LOGPARMS ){
							strcat( szBuffer, szTok );
							strcat( szBuffer, ", " );
						}
					}
					// numero de variaveis
					szTok = cStrTok.StrTok( NULL, ", " );
				}
				if( szTok ){
					// pegar as variaveis
					iNumVars = atoi( szTok );
					if( iNumVars < 0 ){
						iNumVars = 0;
					}
					for( int i = 0; i < iNumVars; i++ ){
						// nome da variavel
						szTok = cStrTok.StrTok( NULL, ", " );
						if( !szTok ){
							return;
						}
						if( _iLevel & LOGVARS ){
							strcat( szBuffer, szTok );
							strcat( szBuffer, " = " );
						}

						// valor da variavel
						szTok = cStrTok.StrTok( NULL, ", " );
						if( !szTok ){
							return;
						}
						if( _iLevel & LOGVARS ){
							strcat( szBuffer, szTok );
							strcat( szBuffer, ", " );
						}
					}
				}
			} else {
				strncpy( szBuffer, szFmtAux, LOGLINESIZE-200 );
				strcat(szBuffer, " *OVERFLOW*  ");
			}

			// retirar a ultima virgula que ficou no buffer
			int	iLen = strlen( szBuffer );
			if( iLen > 2 ){
				szBuffer[ iLen - 2 ] = '\0';
			}

			// montar szLine
			if( _iLevel & LOGMODULE ){
				sprintf( szLine, "%s, %s, %s, (%d), %s", szDateTime, szModuleName, szFileName, iLineNum, szBuffer );
			} else {
				sprintf( szLine, "%s, %s", szDateTime, szBuffer );
			}

			WriteLine( szLine );
		}
	}
}


/***
	monta a data, hora, tickcount e o id do thread corrente
***/
void
C_Log::GetDateTime( char *szDateTime )
{
	if( szDateTime ){
		C_Date		cToday;
		C_Time		cNow;
		DWORD		dwTick = GetTickCount();
		DWORD		dwTId = GetCurrentThreadId();

		// montar a data e hora do log
		sprintf( szDateTime, "%02d/%02d/%04d, %02d:%02d:%02d, (%u), id=%u", cToday.DayOfMonth(), cToday.Month(), cToday.Year(), cNow.Hour(), cNow.Minute(), cNow.Second(), dwTick, dwTId );
	}
}


/***
***/
void
C_Log::FlushLog()
{
	HANDLE	hHandles[ 2 ];
	int	iCurrPos = -1;

	hHandles[ 0 ] = hInitEvent;
	hHandles[ 1 ] = hFlusherEvent;

	while( _pLogFile ){
		// flushar
		if( hFlusherEvent ){
			while( TRUE ){
				if( WaitForMultipleObjects( 2, hHandles, FALSE, FLUSHWAITTIME ) == WAIT_OBJECT_0 ){
					// alguem disparou um InitLog
					OpenFile();
					continue;
				}
				int	iAux = _iWriter > 0 ? (_iWriter-1) : (BIGBUFFERARRAYSIZE-1);
				
				// eh importante nao inverter a ordem dos ifs abaixo.
				// da forma que esta', o servico podera' ser parado
				// sem ter que esperar o buffer esvaziar.
				// se os ifs forem invertidos, o servico somente podera'
				// ser parado quando o buffer estiver vazio.
				if( _bStopService ){
					return;
				}
				if( _iFlusher != iAux ){
					break;
				}
			}
			if( _iFlusher == iCurrPos ){
				_iFlusher = ((++_iFlusher) % BIGBUFFERARRAYSIZE);
			}
			iCurrPos = _iWriter > 0 ? (_iWriter-1) : (BIGBUFFERARRAYSIZE-1);
			while( TRUE ){
				// flushar a linha corrente
				char	*szCurrLine = _szBigBuffer + (_iFlusher * BIGBUFFERLINESIZE);

				if( _iNumBytesWritten > _iMaxFileSize ){
					if( _pLogFile ){
						_pLogFile->Seek( 0, SEEK_SET );
					}
					_iNumBytesWritten = 0;
				}
				if( _pLogFile ){
					_pLogFile->WriteLine( szCurrLine );
				}
				_iNumBytesWritten += (strlen( szCurrLine ) + 2);

				if( _iFlusher == iCurrPos ){
					// flushar o arquivo
//					if( _pLogFile ){
//						_pLogFile->Flush();
//					}

					// mandar um sinal para o WriteLine
					SetEvent( hWriterEvent );

					break;
				}
				// avancar uma linha
				_iFlusher = ((++_iFlusher) % BIGBUFFERARRAYSIZE);
			}
		}
	}
}

/***
	Grava uma linha no _szBigBuffer
***/
void
C_Log::WriteLine( char *szLinePar )
{
	if( !_pLogFile || !_bStarted ){
		return;
	}

	C_LogCritSect	cCS0( this, CRITSECT0 );

	while( _iWriter == _iFlusher ){
		// buffer esta' cheio.
		DWORD	dwRet;
		do {
			// mandar um sinal para o FlushLog
			SetEvent( hFlusherEvent );

			// esperar por um evento
			dwRet = WaitForSingleObject( hWriterEvent, 1000 );
		} while( dwRet == WAIT_TIMEOUT );
	}
	char	*szCurrLine = _szBigBuffer + (_iWriter * BIGBUFFERLINESIZE);

	strcpy( szCurrLine, szLinePar );
	_iWriter = ((++_iWriter) % BIGBUFFERARRAYSIZE );

	// mandar um sinal para o FlushLog
	SetEvent( hFlusherEvent );
}

/***
	O flusher (dog) espera por um sinal FlusherEvent e dispara eventos WriterEvent
	O writer (servidor) espera por um sinal WriterEvent e dispara eventos FlusherEvent
***/
void
C_Log::OpenEvents()
{
	hWriterEvent = OpenEvent( EVENT_ALL_ACCESS, FALSE,"LOGWEVENT" );
	if( !hWriterEvent ){
		hWriterEvent = CreateEvent( NULL, FALSE, FALSE, "LOGWEVENT" );
	}

	hFlusherEvent = OpenEvent( EVENT_ALL_ACCESS, FALSE,	"LOGFEVENT" );
	if( !hFlusherEvent ){
		hFlusherEvent = CreateEvent( NULL, FALSE, FALSE, "LOGFEVENT" );
	}

	hInitEvent = OpenEvent( EVENT_ALL_ACCESS, FALSE, "LOGIEVENT" );
	if( !hInitEvent ){
		hInitEvent = CreateEvent( NULL, FALSE, FALSE, "LOGIEVENT" );
	}
}


/***
***/
void
C_Log::EndLog( HANDLE hThread )
{
	// provocar a morte do thread
	_bStopService = TRUE;

	// esperar o thread morrer
	WaitForSingleObject( hThread, INFINITE );

	// detonar o arquivo
	TerminateLog();
}


/***
***/
void
C_Log::TerminateLog()
{
	if( _pLogFile && !szModuleName[0] ){	// apenas o flusher pode fechar o arquivo
		// gerar ultima linha de log avisando que deu tudo certo
		char		szDateTime[ 100 ];

		GetDateTime( szDateTime );

		sprintf( szLine, "%s ===============WATCHDOG_TERMINANDO_NORMAL====================", szDateTime );

		_pLogFile->WriteLine( szLine );

		delete _pLogFile;
		_pLogFile = NULL;
	}
	if( hWriterEvent ){
		CloseHandle( hWriterEvent );
		hWriterEvent = NULL;
	}
	if( hFlusherEvent ){
		CloseHandle( hFlusherEvent );
		hFlusherEvent = NULL;
	}
	if( hInitEvent ){
		CloseHandle( hInitEvent );
		hInitEvent = NULL;
	}
}

/***
	Fecha o arquivo e abre novamente, com outro nome
***/
void
C_Log::OpenFile()
{
	if( _iLevel <= 0 ){
		return;
	}
	if( !szModuleName[0] ){	// apenas o flusher pode fechar o arquivo
		char	szBufferAux[ 512 ];
		char	szTickCount[ 50 ];
		char	szFullIniName[ MAXPATH ];

		GetAppFullPath( szFullIniName, MAXPATH-1 );
		strcat( szFullIniName, LIFILEINIFILE );

		GetPrivateProfileString( LOG_SESSION, LOG_FILENAMEKEY, "", szBufferAux, 250, szFullIniName );

		if( !(szBufferAux[ 0 ]) ){
			strcpy( szBufferAux, "\\tmp\\lb" );
		}
		sprintf( szTickCount, "%u", GetTickCount() );
		strcat( szBufferAux, szTickCount );
		strcat( szBufferAux, ".log" );

		if( !_pLogFile ){
			_pLogFile = new C_File();
		}
		if( _pLogFile ){
			_bStarted = FALSE;
			_pLogFile->Close();
			_pLogFile->Open( szBufferAux, "wt" );
			_iNumBytesWritten = 0;
			_bStarted = TRUE;
		}
	}
}


/***
	Inicializa o arquivo
***/
void
C_Log::InitLog()
{
	// gerar um evento para o flusher fazer OpenFile
	SetEvent( hInitEvent );
}


C_LogCritSect::C_LogCritSect( C_Log *pObjPar, int iNumCritSect )
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar );
		iLastSectUsed = iNumCritSect;
		pObj = pObjPar;
	}
}

C_LogCritSect::~C_LogCritSect()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->LeaveCriticalSection( iLastSectUsed );
	}
}

void 
C_LogCritSect::EnterCriticalSection()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
	}
}

void 
C_LogCritSect::LeaveCriticalSection()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->LeaveCriticalSection( iLastSectUsed );
	}
}
