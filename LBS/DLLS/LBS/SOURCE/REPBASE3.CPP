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
// Module: REPBASE3.CPP
// Description:
//
//	public methods file of then LBSC_BASE class
//	Methods with fields or repetitions
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 16/05/96
//

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined __STDARG_H && !defined _INC_STDARG
#include	<stdarg.h>
#endif
#if !defined __CTYPE_H && !defined _INC_CTYPE
#include	<ctype.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined __DIRECT_H && !defined _INC_DIRECT
#include	<direct.h>
#endif
#if !defined __DIRENT_H && !defined _INC_DIRECT
#include	DIRENT_H
#endif
#if !defined( __SHARE_H ) && !defined _INC_SHARE
#include	<share.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_BASETIMERSLIST_H_
#include	<btimerl.h>
#endif
#include <baseinstance.h>

// API LIGHT-TEXT
#include	<lt.h>

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

EXTLOG( _clLBSLog );	// objeto para geracao de log

/******************************************************************************
				PUT FIELD REPETITION BY INDEX
******************************************************************************/
/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (string)
	Adiciona uma string em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- szRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, char *szRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szRepetition ){
		return( DelFieldRepetition( szField, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TEXT_FIELD && pf->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) szRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}

	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( szRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (string)
	Adiciona uma string em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- szRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, char *szRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szRepetition ){
		return( DelFieldRepetition( uiFieldId, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TEXT_FIELD && pf->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) szRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}

	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( szRepetition, iIndex );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (void)
	Adiciona um buffer void em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- pvRepetition	-> repeticao a ser adicionada
		- lSize		-> tamanho da repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, void *pvRepetition, long lSize, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TEXT_FIELD && pf->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) pvRepetition, iIndex, lSize ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( pvRepetition, iIndex, lSize );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (void)
	Adiciona um buffer void em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- szRepetition	-> repeticao a ser adicionada
		- lSize		-> tamanho da repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, void *pvRepetition, long lSize, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !pvRepetition ){
		return( DelFieldRepetition( uiFieldId, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TEXT_FIELD && pf->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) pvRepetition, iIndex, lSize ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( pvRepetition, iIndex, lSize );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (long)
	Adiciona um numero inteiro em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- lRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, long lRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != VALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &lRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &lRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (long)
	Adiciona um numero inteiro em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- lRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, long lRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != VALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &lRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &lRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (double)
	Adiciona um numero double em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- dRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, double dRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != DVALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &dRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &dRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (double)
	Adiciona um numero double em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- dRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, double dRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != DVALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &dRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &dRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (date)
	Adiciona uma data em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- cdRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, C_Date cdRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != DATE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	JulTy	jtDate = cdRepetition.Hash();
	if( pf->IsTheSameRepetition( (void*) &jtDate, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	jtDate = cdRepetition.Hash();

	int	iRet = pf->PutRepetition( &jtDate, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (date)
	Adiciona uma data em um campo da base (no registro corrente)

	Parameters:
		- iFieldID	-> identificador do campo
		- cdRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, C_Date cdRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != DATE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	JulTy	jtDate = cdRepetition.Hash();
	if( pf->IsTheSameRepetition( (void*) &jtDate, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	jtDate = cdRepetition.Hash();

	int	iRet = pf->PutRepetition( &jtDate, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (time)
	Adiciona uma hora em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- ctRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, C_Time ctRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TIME_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	ClockTy ctTime = ctRepetition.Seconds();
	if( pf->IsTheSameRepetition( (void*) &ctTime, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	ctTime = ctRepetition.Seconds();

	int	iRet = pf->PutRepetition( &ctTime, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (time)
	Adiciona uma hora em um campo da base (no registro corrente)

	Parameters:
		- iFieldID	-> identificador do campo
		- ctRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, C_Time ctRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != TIME_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	ClockTy ctTime = ctRepetition.Seconds();
	if( pf->IsTheSameRepetition( (void*) &ctTime, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	ctTime = ctRepetition.Seconds();

	int	iRet = pf->PutRepetition( &ctTime, iIndex );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (binary)
	Adiciona uma repeticao tipo binary em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- bRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, LBSC_Binary *bRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bRepetition || bRepetition->iLen <= 0 ){
		return( DelFieldRepetition( szField, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != BINARY_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( bRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (binary)
	Adiciona uma repeticao tipo binary em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- bRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, LBSC_Binary *bRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bRepetition || bRepetition->iLen <= 0 ){
		return( DelFieldRepetition( uiFieldId, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != BINARY_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( bRepetition, iIndex );
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (reference)
	Adiciona uma repeticao tipo reference em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- rRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, LBSC_Reference *prRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !prRepetition ){
		return( DelFieldRepetition( szField, iIndex ) );
	}

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != REFERENCED_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) prRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet;
	if( pf->GetIndexAttrib() & WORDTREE ){
		LBSC_Reference	*pRefAux = prRepetition;
		if( prRepetition->iFormat == LBSRT_URL ){
			// se for URL, entao devemos preencher o szBuffer agora (usar o chupador html)
			if( (pRefAux = FillUrlBuffer( prRepetition )) == NULL ){
				// deu pau
				return( LastError() );
			}
		}
		iRet = pf->PutRepetition( pRefAux, iIndex );
		if( prRepetition->iFormat == LBSRT_URL ){
			LBSC_Reference::Free( pRefAux );
		}
	} else {
		iRet = pf->PutRepetition( prRepetition, iIndex );
	}
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (reference)
	Adiciona uma repeticao tipo reference em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- rRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, LBSC_Reference *prRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !prRepetition ){
		return( DelFieldRepetition( uiFieldId, iIndex ) );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != REFERENCED_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) prRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet;
	if( pf->GetIndexAttrib() & WORDTREE ){
		LBSC_Reference	*pRefAux = prRepetition;
		if( prRepetition->iFormat == LBSRT_URL ){
			// se for URL, entao devemos preencher o szBuffer agora (usar o chupador html)
			if( (pRefAux = FillUrlBuffer( prRepetition )) == NULL ){
				// deu pau
				return( LastError() );
			}
		}
		iRet = pf->PutRepetition( pRefAux, iIndex );
		if( prRepetition->iFormat == LBSRT_URL ){
			LBSC_Reference::Free( pRefAux );
		}
	} else {
		iRet = pf->PutRepetition( prRepetition, iIndex );
	}
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (BYTE)
	Adiciona um BYTE em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- pbRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, BYTE bRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != BYTE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &bRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &bRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (BYTE)
	Adiciona um BYTE em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- bRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, BYTE bRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != BYTE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &bRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &bRepetition, iIndex );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (short int)
	Adiciona um numero short int em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- siRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, short int siRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != SINT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &siRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &siRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (short int)
	Adiciona um numero short int em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- siRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, short int siRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != SINT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &siRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &siRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (float)
	Adiciona um numero float em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- fRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( char *szField, float fRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != FLOAT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &fRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &fRepetition, iIndex );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetitionByIndex (float)
	Adiciona um numero float em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- fRepetition	-> repeticao a ser adicionada
		- iIndex	-> numero da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetitionByIndex( UINT uiFieldId, float fRepetition, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetitionByIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	if( pf->GetType() != FLOAT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	if( pf->IsTheSameRepetition( (void*) &fRepetition, iIndex ) ){
		// o novo dado eh igual ao ja' existente.
		ERETURN( LBS_OK );
	}
	BOOL	bCheckWrite = TRUE;
	if( iIndex < GetNumberOfRepetition( pf->GetId() ) ){
		LBSC_Data *pd = (pf->lbscdlDataList[ iIndex ]);
		if( !pd ){
			ERETURN( LBSE_ERROR );
		}
		bCheckWrite = pd->GetStatus() != DATA_HOLE;
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				(iIndex >= GetNumberOfRepetition( pf->GetId() )) || !bCheckWrite ? 
				ACL_APPEND :
				ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &fRepetition, iIndex );
	ERETURN( iRet );
}


/******************************************************************************
				DEL FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo DelFieldRepetition
	Deleta uma repeticao de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero (indice) da repeticao a ser deletada
		- bShift -> indica se as repeticoes restantes devem ser deslocadas
				    uma posicao para ocupar o buraco deixado pela delecao.
					O default eh nao fazer o shift (FALSE).

	Return:
		- LBS_OK se conseguir deletar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::DelFieldRepetition( char *szField, int iRepNumber, BOOL bShift )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_DEL ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	if(lbscrCurrRecord.DelFieldRepetition( szField, iRepNumber, bShift ) == LBS_OK){
		bBaseUpdated = TRUE;
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}



/***
	PUBLIC
	Metodo DelFieldRepetition
	Deleta uma repeticao de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero (indice) da repeticao a ser deletada
		- bShift -> indica se as repeticoes restantes devem ser deslocadas
				    uma posicao para ocupar o buraco deixado pela delecao.
					O default eh nao fazer o shift (FALSE).

	Return:
		- LBS_OK se conseguir deletar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::DelFieldRepetition( UINT uiFieldId, int iRepNumber, BOOL bShift )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_DEL ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		return( DelFieldRepetition( (char*) plbscfAux->szAliasName, iRepNumber, bShift ) );
	}
	ERETURN( LBSE_ERROR );
}


/******************************************************************************
				GET FIELD REPETITION SIZE
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldRepetitionSize
	Obtem o tamanho de uma repeticao de um campo

	Parameters:
		- szFieldAliasName	-> nome do campo
		- iRepetNumber		-> numero da repeticao

	Return:
		- tamanho da repeticao ou erro

	Comments:
		-

***/
long
LBSC_Base::GetFieldRepetitionSize( char *szFieldAliasName, int iRepetNumber )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionSize 1 %s %s", "FieldName", szFieldAliasName ? szFieldAliasName : "NULL_FIELD" ) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szFieldAliasName ];
	if( pf ){
		if( pf->GetNumberOfRepetition() <= 0 || pf->GetNumberOfRepetition() <= iRepetNumber ){
			ERETURN( LBSE_REPETITIONNOTFOUND );
		}
		LBSC_Data	*pd = (*pf)[ iRepetNumber ];
		if( pd ){
			SetError( LBS_OK );
			return( pd->GetSize() );
		}
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	ERETURN( LBSE_FIELDNOTFOUND );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionSize
	Obtem o tamanho de uma repeticao de um campo

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetNumber	-> numero da repeticao

	Return:
		- tamanho da repeticao ou erro

	Comments:
		-

***/
long
LBSC_Base::GetFieldRepetitionSize( UINT uiFieldId, int iRepetNumber )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionSize 1 %s %d", "FieldId", uiFieldId) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( pf ){
		if( pf->GetNumberOfRepetition() <= 0 || pf->GetNumberOfRepetition() <= iRepetNumber ){
			ERETURN( LBSE_REPETITIONNOTFOUND );
		}
		LBSC_Data	*pd = (*pf)[ iRepetNumber ];
		if( pd ){
			SetError( LBS_OK );
			return( pd->GetSize() );
		}
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	ERETURN( LBSE_FIELDNOTFOUND );
}


/******************************************************************************
				DEL FIELD
******************************************************************************/
/***
	PUBLIC
	Metodo DelField
	Deleta um campo do formato de uma base

	Parameters:
		- szField	-> nome do campo a ser deletado

	Return:
		- LBS_OK se conseguir deletar ou erro.

	Comments:
		- A base deve ser re-estruturada para que a modificacao
		  seja efetuada fisicamente
		- A base nao e reindexada automaticamente.

***/
int
LBSC_Base::DelField( char *szField )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelField") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = (*this)[ szField ];
	if( pf ){
		return( DelField( pf->uiFieldId ) );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}



/***
	PUBLIC
	Metodo DelField
	Deleta um campo do formato de uma base

	Parameters:
		- uiFieldId	-> identificador do campo a ser deletado

	Return:
		- LBS_OK se conseguir deletar ou erro.

	Comments:
		- A base nao e reindexada automaticamente.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.

***/
int
LBSC_Base::DelField( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelField") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	if ( IsUDBFixedField( uiFieldId ) ) {
		ERETURN( LBSE_NOPERMISSION );
	}

	if( lbscrCurrRecord.DelField( uiFieldId ) == LBS_OK ){
		bBaseUpdated = TRUE;

		//  LIGAR FLAG DE DELECAO EM LB3
		if( DelFieldOnFile( uiFieldId ) != LBS_OK ){
			ERETURN( LBSE_ERROR );
		}
		// DELETAR AS ACLs DO CAMPO
		char	*szName = (char*) plbscsOwnerSession->GetUserName();
		DelACLPerm( szName, (long) uiFieldId, NULL, USERFIELD );
		DelACLPerm( szName, (long) uiFieldId, NULL, GROUPFIELD );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}

/******************************************************************************
				MODIFY FIELD PASSWORD
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldPassword
	Modifica a password de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo
		- szOldPassword		-> password antiga do campo
		- szNewPassword		-> nova password do campo

	Return:
		- LBS_OK se conseguir modificar a password do campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.

***/
int
LBSC_Base::ModifyFieldPassword( char *szFieldAliasName, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldPassword") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	TStructRec	tsrRec;
	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(szFieldAliasName) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// $$$ Verificar se szOldPassword bate com a password atual do campo
	// $$$ (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// $$$ Nao eh o dono da base que estah logado

		// Checar permissoes de ACL
//		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szFieldAliasName ]).GetId(), 
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];
		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
	}

	// $$$ MODIFICAR A PASSWORD EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Checa password
				if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
					// $$$ Nao eh o dono da base que estah logado
					if( tsrRec.szFieldPassword != szOldPassword ){
						ERETURN( LBSE_INVALIDPASSWORD );
					}
				}
				// $$$ Modifica password
				tsrRec.szFieldPassword = szNewPassword;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// $$$ MODIFICAR A PASSWORD EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					if( lbscrCurrRecord.ModifyFieldPassword( szFieldAliasName,
						szOldPassword, szNewPassword )
						== LBS_OK ){
						ERETURN( LBS_OK );
					}
					ERETURN( LBSE_FATAL );
				}
				ERETURN( LBSE_FILEERROR );
			}
		}
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo ModifyFieldPassword
	Modifica a password de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- szOldPassword	-> password antiga do campo
		- szNewPassword	-> nova password do campo

	Return:
		- LBS_OK se conseguir modificar a password do campo ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyFieldPassword( UINT uiFieldId, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldPassword") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(uiFieldId) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		int	iRet = ModifyFieldPassword( (char*) plbscfAux->szAliasName, szOldPassword, szNewPassword );
		ERETURN( iRet );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}



/******************************************************************************
				MODIFY FIELD NAME
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldName
	Modifica o AliasName de um campo da base

	Parameters:
		- szFieldAliasName	-> nome atual do campo
		- szPassword		-> password do campo
		- szFieldNewAliasName	-> novo nome para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyFieldName( char *szFieldAliasName, char *szPassword, char *szFieldNewAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	TStructRec	tsrRec;
	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(szFieldAliasName) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// $$$ Verificar se szPassword bate com a password atual do campo
	// $$$ (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// $$$ Nao eh o dono da base que estah logado

		// Checar permissoes de ACL
//		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szFieldAliasName ]).GetId(), 
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];
		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
	}
	// $$$ MODIFICAR O ALIASNAME EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Modifica aliasname
				tsrRec.szFieldAliasName = szFieldNewAliasName;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// $$$ MODIFICAR O ALIASNAME EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					// como vamos mudar os nomes dos campos, eh melhor desabilitar a cache de campos

					lbscrCurrRecord.DelSortLists();
					LBSC_Field *pf = lbscrCurrRecord[ szFieldAliasName ];
					if( !pf ){
						ERETURN( LBSE_FATAL );
					}
					if( pf->ModifyAliasName( szFieldNewAliasName ) == LBS_OK ){
						ERETURN( LBS_OK );
					}
					ERETURN( LBSE_FATAL );
				}
				ERETURN( LBSE_FILEERROR );
			}
		}
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo ModifyFieldName
	Modifica o AliasName de um campo da base

	Parameters:
		- uiFieldId		-> identificador do campo
		- szPassword		-> password do campo
		- szFieldNewAliasName	-> novo nome para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyFieldName( UINT uiFieldId, char *szPassword, char *szFieldNewAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldName") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(uiFieldId) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		int	iRet = ModifyFieldName( (char*) plbscfAux->szAliasName, szPassword, szFieldNewAliasName );
		ERETURN( iRet );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}



/******************************************************************************
				MODIFY FIELD DESCRIPTION
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldDescription
	Modifica a descricao de um campo da base

	Parameters:
		- szFieldAliasName	-> nome atual do campo
		- szPassword		-> password do campo
		- szNewDescription	-> nova descricao para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyFieldDescription( char *szFieldAliasName, char *szPassword, char *szNewDescription )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldDescription") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	TStructRec	tsrRec;
	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// $$$ Verificar se szPassword bate com a password atual do campo
	// $$$ (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// $$$ Nao eh o dono da base que estah logado

		// Checar permissoes de ACL
//		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szFieldAliasName ]).GetId(), 
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];
		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
	}
	// $$$ MODIFICAR A DESCRICAO EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Modifica descricao
				tsrRec.szFieldDescription = szNewDescription;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// $$$ MODIFICAR A DESCRICAO EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					LBSC_Field *pf = lbscrCurrRecord[ szFieldAliasName ];
					if( !pf ){
						ERETURN( LBSE_FATAL );
					}
					if( pf->ModifyDescription( szNewDescription ) == LBS_OK ){
						ERETURN( LBS_OK );
					}
					ERETURN( LBSE_FATAL );
				}
				ERETURN( LBSE_FILEERROR );
			}
		}
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo ModifyFieldDescription
	Modifica a descricao de um campo da base

	Parameters:
		- uiFieldId		-> identificador do campo
		- szPassword		-> password do campo
		- szNewDescription	-> nova descricao para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyFieldDescription( UINT uiFieldId, char *szPassword, char *szNewDescription )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldDescription") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		return( ModifyFieldDescription( (char*) plbscfAux->szAliasName, szPassword, szNewDescription ) );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}



/******************************************************************************
				MODIFY FIELD SIZE
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldSize
	Modifica o tamanho de um campo da base

	Parameters:
		- szFieldAliasName	-> nome atual do campo
		- szPassword		-> password do campo
		- lNewSize		-> novo tamanho para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- Este metodo so tem efeito para campos do tipo ALPHA_FIELD.

***/
int
LBSC_Base::ModifyFieldSize( char *szFieldAliasName, char *szPassword, long lNewSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldSize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	TStructRec	tsrRec;
	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(szFieldAliasName) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// $$$ Verificar se szPassword bate com a password atual do campo
	// $$$ (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// $$$ Nao eh o dono da base que estah logado

		// Checar permissoes de ACL
//		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szFieldAliasName ]).GetId(), 
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];
		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
	}
	// $$$ MODIFICAR A DESCRICAO EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Modifica descricao
				tsrRec.lFieldSize = lNewSize;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// $$$ MODIFICAR A DESCRICAO EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					LBSC_Field *pf = lbscrCurrRecord[ szFieldAliasName ];
					if( !pf ){
						ERETURN( LBSE_FATAL );
					}
					if( pf->ModifySize( lNewSize ) == LBS_OK ){
						ERETURN( LBS_OK );
					}
					ERETURN( LBSE_FATAL );
				}
				ERETURN( LBSE_FILEERROR );
			}
		}
	}
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo ModifyFieldSize
	Modifica o tamanho de um campo da base

	Parameters:
		- uiFieldId		-> identificador do campo
		- szPassword		-> password do campo
		- lNewSize		-> novo tamanho para o campo

	Return:
		- LBS_OK se conseguir modificar o campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- Este metodo so tem efeito para campos do tipo ALPHA_FIELD.

***/
int
LBSC_Base::ModifyFieldSize( UINT uiFieldId, char *szPassword, long lNewSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldSize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bFullAccess ){
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( IsUDBFixedField(uiFieldId) ) {
		ERETURN( LBSE_NOPERMISSION );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( plbscfAux ){
		return( ModifyFieldSize( (char*) plbscfAux->szAliasName, szPassword, lNewSize ) );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}

BOOL LBSC_Base::IsUDBFixedField( UINT uiFieldId )
{
	if( LB1.tcrHead.bBaseType != USER_BASE ){
		return FALSE;
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( FALSE );
	}
	return IsUDBFixedField( pf->szAliasName );
}

BOOL LBSC_Base::IsUDBFixedField( char *szField )
{
	if( LB1.tcrHead.bBaseType != USER_BASE ){
		return FALSE;
	}

	if ( stricmp( szField, USERBASEUSERNAME ) == 0 ||
		stricmp( szField, USERBASEUSERPASSWORD ) == 0 ||
		stricmp( szField, USERBASEUSERTYPE ) == 0 ||
		stricmp( szField, USERBASEUSERDESCRIPTION ) == 0 ||
		stricmp( szField, USERBASEUSERADDRESS ) == 0 ||
		stricmp( szField, USERBASEUSERPHONE ) == 0 ||
		stricmp( szField, USERBASEGROUPLIST ) == 0 ||
		stricmp( szField, USERBASEUSERCREATEDATE ) == 0 ||
		stricmp( szField, USERBASEUSERUPDATEDATE ) == 0 ||
		stricmp( szField, USERBASEACCESSBASES ) == 0 ||
		stricmp( szField, USERBASEACCESSTYPES ) == 0 ||
		stricmp( szField, USERBASELOGINATTEMPTS ) == 0 ||
		stricmp( szField, USERBASEPASSWORDCHANGEDATE ) == 0 ) {
		return TRUE;
	}
	return FALSE;
}

