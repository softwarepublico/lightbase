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

#include <logcl.h>
#ifndef	_SESSCL_H_
#include <sesscl.h>
#endif
#ifndef	_BASECL_H_
#include <basecl.h>
#endif
#ifndef	_FIELDCL_H_
#include <fieldcl.h>
#endif
#ifndef	_DATACL_H_
#include <datacl.h>
#endif
#ifndef	_PARSERCL_H_
#include <parsercl.h>
#endif
#ifndef	_ENTPARCL_H_
#include <entparcl.h>
#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

//
// Inicializacao das globais com os slots por thread das mascaras de uso de regioes criticas 
//
static DWORD _dwSessCritSectSlot = 0;
static DWORD _dwBaseCritSectSlot = 0;
static DWORD _dwFieldCritSectSlot = 0;
static DWORD _dwDataCritSectSlot = 0;
static DWORD _dwParserCritSectSlot = 0;
static DWORD _dwEntParserCritSectSlot = 0;

CritSessManager _csSessMan;
CritBaseManager _csBaseMan;
CritDataManager _csDataMan;
CritFieldManager _csFieldMan;
CritParserManager _csParserMan;
CritEntParserManager _csEntParserMan;


void BeginAllTlsUsage();
void AllocAllTls();
void AllocTls( DWORD dwTlsSlot );
unsigned long GetTlsVal( DWORD dwTlsSlot );
void SetTlsVal( DWORD dwTlsSlot, unsigned long ulMask );
void FreeAllTls();
void FreeTls( DWORD dwTlsSlot );
void EndAllTlsUsage();
void EndTlsUsage( DWORD dwTlsSlot );


void 
CritSectLog(char *szMsg, char *szFile, int iLine, int iNum )
{
	PRINTLOG( _clLBSLog, ("%s 3 %s %d %s %s %s %d", szMsg, "Regiao", iNum, "Arquivo", (char *)szFile, "Linha", iLine));
}


////////////////////////////////////////////////////////////////////////////
//CritSessManager
////////////////////////////////////////////////////////////////////////////
void 
CritSessManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritSessManager::GetCritSectMask()
{
	return GetTlsVal( _dwSessCritSectSlot );
}

void 
CritSessManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwSessCritSectSlot, ulNewMask );
}

BOOL 
CritSessManager::OrderedDependents()
{
	// consideramos as regioes de Session como prioritarias em relacao a todas as outras 
	// assim, nao podemos ter entrado em nenhuma outra antes de session
	return ( !GetTlsVal( _dwFieldCritSectSlot ) && !GetTlsVal( _dwDataCritSectSlot ) 
		&& !GetTlsVal( _dwParserCritSectSlot ) && !GetTlsVal( _dwEntParserCritSectSlot ) && 
		!GetTlsVal( _dwBaseCritSectSlot ) );
}




////////////////////////////////////////////////////////////////////////////
// CritBaseManager
////////////////////////////////////////////////////////////////////////////
void 
CritBaseManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritBaseManager::GetCritSectMask()
{
	return GetTlsVal( _dwBaseCritSectSlot );
}

void 
CritBaseManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwBaseCritSectSlot, ulNewMask );
}

BOOL 
CritBaseManager::OrderedDependents()
{
	// consideramos as regioes de base como prioritarias em relacao aas de field,
	// data, parser e entparser
	// assim, nao podemos ter entrado em nenhuma dessas antes de base
	return ( !GetTlsVal( _dwFieldCritSectSlot ) && !GetTlsVal( _dwDataCritSectSlot ) && 
		!GetTlsVal( _dwParserCritSectSlot ) && !GetTlsVal( _dwEntParserCritSectSlot ) );
}




////////////////////////////////////////////////////////////////////////////
// CritDataManager
////////////////////////////////////////////////////////////////////////////
void 
CritDataManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritDataManager::GetCritSectMask()
{
	return GetTlsVal( _dwDataCritSectSlot );
}

void 
CritDataManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwDataCritSectSlot, ulNewMask );
}

BOOL 
CritDataManager::OrderedDependents()
{
	// consideramos as regioes de data as de menor prioridade
	return TRUE;
}




////////////////////////////////////////////////////////////////////////////
// CritFieldManager
////////////////////////////////////////////////////////////////////////////
void 
CritFieldManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritFieldManager::GetCritSectMask()
{
	return GetTlsVal( _dwFieldCritSectSlot );
}

void 
CritFieldManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwFieldCritSectSlot, ulNewMask );
}

BOOL 
CritFieldManager::OrderedDependents()
{
	// consideramos as regioes de field como prioritarias em relacao aas de data
	return ( !GetTlsVal( _dwDataCritSectSlot ) );
}




////////////////////////////////////////////////////////////////////////////
// CritParserManager
////////////////////////////////////////////////////////////////////////////
void 
CritParserManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritParserManager::GetCritSectMask()
{
	return GetTlsVal( _dwParserCritSectSlot );
}

void 
CritParserManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwParserCritSectSlot, ulNewMask );
}

BOOL 
CritParserManager::OrderedDependents()
{
	return TRUE;
}




////////////////////////////////////////////////////////////////////////////
// CritEntParserManager
////////////////////////////////////////////////////////////////////////////
void 
CritEntParserManager::CritSectLog( char *szMsg, char *szFile, int iLine, int iNum )
{
	::CritSectLog( szMsg, szFile, iLine, iNum );
}

unsigned long 
CritEntParserManager::GetCritSectMask()
{
	return GetTlsVal( _dwEntParserCritSectSlot );
}

void 
CritEntParserManager::SetCritSectMask( unsigned long ulNewMask )
{
	SetTlsVal( _dwEntParserCritSectSlot, ulNewMask );
}

BOOL 
CritEntParserManager::OrderedDependents()
{
	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	API para usar as areas Tls
/////////////////////////////////////////////////////////////////////////////
void
BeginAllTlsUsage()
{
	/****
	_dwSessCritSectSlot = TlsAlloc();
	_dwBaseCritSectSlot = TlsAlloc();
	_dwFieldCritSectSlot = TlsAlloc();
	_dwDataCritSectSlot = TlsAlloc();
	_dwParserCritSectSlot = TlsAlloc();
	_dwEntParserCritSectSlot = TlsAlloc();

	aparetemente o uso de thread local storages estava gerando leaks; vamos desabilita-lo por desencargo

	AllocAllTls();	// ja vamos alocar todas as areas para o primeiro thread ...
	****/
}

void
AllocAllTls()
{
	AllocTls ( _dwSessCritSectSlot );
	AllocTls ( _dwBaseCritSectSlot );
	AllocTls ( _dwFieldCritSectSlot );
	AllocTls ( _dwDataCritSectSlot );
	AllocTls ( _dwParserCritSectSlot );
	AllocTls ( _dwEntParserCritSectSlot );
}
void
AllocTls( DWORD dwTlsSlot )
{
	if ( !dwTlsSlot ) {
		return;
	}

	unsigned long *pulMask = new unsigned long;
	if ( !pulMask ) {
		return;
	}

	*pulMask = 0;

	TlsSetValue( dwTlsSlot, (LPVOID)pulMask );
}
unsigned long
GetTlsVal( DWORD dwTlsSlot )
{
	if ( !dwTlsSlot ) {
		return 0;
	}

	unsigned long *pulMask = (unsigned long *)TlsGetValue( dwTlsSlot );

	if ( pulMask ) {
		return *pulMask;
	}

	return 0;
}
void
SetTlsVal( DWORD dwTlsSlot, unsigned long ulMask )
{
	if ( !dwTlsSlot ) {
		return;
	}

	unsigned long *pulMask = (unsigned long *)TlsGetValue( dwTlsSlot );

	if ( pulMask ) {
		*pulMask = ulMask;
	}
}
void
FreeAllTls()
{
	FreeTls ( _dwSessCritSectSlot );
	FreeTls ( _dwBaseCritSectSlot );
	FreeTls ( _dwFieldCritSectSlot );
	FreeTls ( _dwDataCritSectSlot );
	FreeTls ( _dwParserCritSectSlot );
	FreeTls ( _dwEntParserCritSectSlot );
}
void
FreeTls( DWORD dwTlsSlot )
{
	if ( !dwTlsSlot ) {
		return;
	}

	unsigned long *pulMask = (unsigned long *)TlsGetValue( dwTlsSlot );

	if ( pulMask ) {
		delete pulMask;
	}

	TlsSetValue( dwTlsSlot, NULL );
}
void
EndAllTlsUsage()
{
	EndTlsUsage ( _dwSessCritSectSlot );
	EndTlsUsage ( _dwBaseCritSectSlot );
	EndTlsUsage ( _dwFieldCritSectSlot );
	EndTlsUsage ( _dwDataCritSectSlot );
	EndTlsUsage ( _dwParserCritSectSlot );
	EndTlsUsage ( _dwEntParserCritSectSlot );
}
void
EndTlsUsage( DWORD dwTlsSlot )
{
	if ( !dwTlsSlot ) {
		return;
	}

	FreeTls( dwTlsSlot );
	TlsFree( dwTlsSlot );
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

