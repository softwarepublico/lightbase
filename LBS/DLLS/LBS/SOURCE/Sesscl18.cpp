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

//
// Module: SESSCL18.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif
#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif

#ifdef	_DEBUG_CRIT_SECT_

#define	cCS0( x, y )					cCS0( (x), (y), __FILE__, __LINE__ )
#define	cCS1( x, y )					cCS1( (x), (y), __FILE__, __LINE__ )
#define	cCS2( x, y )					cCS2( (x), (y), __FILE__, __LINE__ )
#define	cCS3( x, y )					cCS3( (x), (y), __FILE__, __LINE__ )
#define	cCS4( x, y )					cCS4( (x), (y), __FILE__, __LINE__ )
#define	cCS5( x, y )					cCS5( (x), (y), __FILE__, __LINE__ )
#define	cCS6( x, y )					cCS6( (x), (y), __FILE__, __LINE__ )
#define	cCS7( x, y )					cCS7( (x), (y), __FILE__, __LINE__ )
#define	cCS8( x, y )					cCS8( (x), (y), __FILE__, __LINE__ )
#define	cCS9( x, y )					cCS9( (x), (y), __FILE__, __LINE__ )
#define	cCS10( x, y )					cCS10( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo RenameBase
	Renomeia uma base

	Parameters:
		- pTicket		-> ticket de seguranca
		- szOldName		-> nome atual da base
		- szNewName		-> novo nome da base

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Session::RenameBase( const LBSC_Ticket *pTicket, char *szOldName, char *szNewName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::RenameBase") );
	// Verifica se o usuario estah logado
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	// Verifica a validade do ticket de seguranca
	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// verifica os parametros
	if( !szOldName || strcmp( szOldName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	if( !szNewName || strcmp( szNewName, "" ) == 0 ){
		ERETURN( LBSE_BADARG );
	}
	TBasesFile	tbfAux;
	char		szDirBase[ PATHNAMESIZE ];
	char		szControlFile[ PATHNAMESIZE ];
	char		szFullOldName[ PATHNAMESIZE ];
	char		szFullNewName[ PATHNAMESIZE ];
	long		lBFilePos = -1;

	// Acessar lbs.ini para pegar o arquivo de controle
	if( GetFNameOnProfile( szDirBase, szControlFile ) != LBS_OK ){
		ERETURN( LBSE_LBSINIERROR );
	}
	if ( !ControlFileOK() ) {
		ERETURN( LBSE_CONTROLFILENOTOK );
	}

	C_SessCritSect	cCS4( this, CRITSECT4 );

	// montar o nome completo da base
	sprintf( szFullOldName, "%s\\%s", szDirBase, szOldName );
	sprintf( szFullNewName, "%s\\%s", szDirBase, szNewName );

	// renomear em disco
	if( !MoveFile( szFullOldName, szFullNewName ) ){
		return( LastError() );
	}
	if( RenameDirFiles( szFullNewName ) != LBS_OK ){
		return( LastError() );
	}

	// renomear a base no arquivo de controle
	const TBasesFile	*ptbfAux = pControlFile->Get( szOldName );
	if ( ptbfAux ) {
		// eh o mesmo que deletar...
		TBasesFile	tbfAux = (*(TBasesFile *)ptbfAux);
		if ( !pControlFile->Del( szOldName ) ) {
			// ih, lascou...
			ERETURN( LBSE_ERROR );
		}
		// .. e inserir com o novo nome
		tbfAux.szBaseName = strupr( szNewName );
		if ( !pControlFile->Insert( tbfAux ) ) {
			// ih, lascou...
			ERETURN( LBSE_ERROR );
		}
	}
	ERETURN( LBS_OK );
}



/******************************************************************/
/******** DELETEs DA VIDA *****************************************/
/******************************************************************/

/***
	static PUBLIC
	Metodo Delete (void*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( void *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (char*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( char *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (int*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( int *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (TField*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TField *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (TUDBRecord*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TUDBRecord *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_AllBasesList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_AllBasesList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_ServerBasesList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_ServerBasesList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (LBSC_PermList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_PermList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_ACLList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_ACLList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (TBaseInfo*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TBaseInfo *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_Session**)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_Session **pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_AppUserInfoList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_AppUserInfoList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_AppNetInfoList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_AppNetInfoList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_AppSessionNetInfoList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_AppSessionNetInfoList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (LBSC_AppBaseNetInfoList*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( LBSC_AppBaseNetInfoList *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (TSlotCache*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TSlotCache *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}


/***
	static PUBLIC
	Metodo Delete (TSlotCacheInfo*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TSlotCacheInfo *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

/***
	static PUBLIC
	Metodo Delete (TACL_Lists*)
	Deleta um ponteiro que foi alocado pelo LBS

	Parameters:
		- pData		-> ponteiro para o dado a ser deletado

	Return:
		- nada

	Comments:
		- 

***/
void
LBSC_Session::Delete( TACL_Lists *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

void
LBSC_Session::Delete( C_Buffer *pData )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::Delete") );
	if( pData ){
		delete pData;
	}
}

