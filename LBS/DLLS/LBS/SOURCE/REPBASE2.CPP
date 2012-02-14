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
// Module: REPBASE2.CPP
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

// API LIGHT-TEXT
#include	<lt.h>


EXTLOG( _clLBSLog );	// objeto para geracao de log

/******************************************************************************
				GET REPETITION BY VAL
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (string)
	Obtem o indice de uma repeticao tipo string de um campo da base

	Parameters:
		- szField	-> nome do campo
		- szRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, char *szRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( szRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (string)
	Obtem o indice de uma repeticao tipo string de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- szRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, char *szRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( szRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}


/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (void)
	Obtem o indice de uma repeticao tipo void de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pvRep		-> conteudo da repeticao a ser procurado
		- lSize		-> tamanho do parametro anterior
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, void *pvRep, long lSize, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( pvRep, bStart, lSize );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (string)
	Obtem o indice de uma repeticao tipo string de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- szRep		-> conteudo da repeticao a ser procurado
		- lSize		-> tamanho do parametro anterior
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, void *pvRep, long lSize, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( pvRep, bStart, lSize );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (long)
	Obtem o indice de uma repeticao tipo long de um campo da base

	Parameters:
		- szField	-> nome do campo
		- plRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, long *plRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( plRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (long)
	Obtem o indice de uma repeticao tipo long de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- plRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, long *plRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( plRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (double)
	Obtem o indice de uma repeticao tipo double de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pdRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, double *pdRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( pdRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (double)
	Obtem o indice de uma repeticao tipo double de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pdRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, double *pdRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( pdRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (date)
	Obtem o indice de uma repeticao tipo date de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pcdRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, C_Date *pcdRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	JulTy jt = pcdRep->Hash();
	int iRet = pf->GetRepetitionByVal( &jt, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (date)
	Obtem o indice de uma repeticao tipo date de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pcdRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, C_Date *pcdRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	JulTy jt = pcdRep->Hash();
	int iRet = pf->GetRepetitionByVal( &jt, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (time)
	Obtem o indice de uma repeticao tipo time de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pctRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, C_Time *pctRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	ClockTy ct = pctRep->Seconds();
	int iRet = pf->GetRepetitionByVal( &ct, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (time)
	Obtem o indice de uma repeticao tipo time de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pctRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, C_Time *pctRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	ClockTy ct = pctRep->Seconds();
	int iRet = pf->GetRepetitionByVal( &ct, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}


/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (binario)
	Obtem o indice de uma repeticao tipo binario de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pbRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, LBSC_Binary *pbRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( pbRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (binario)
	Obtem o indice de uma repeticao tipo binario de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pbRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, LBSC_Binary *pbRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( pbRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}


/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (referencia)
	Obtem o indice de uma repeticao tipo referencia de um campo da base

	Parameters:
		- szField	-> nome do campo
		- prRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, LBSC_Reference *prRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

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
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( prRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (referencia)
	Obtem o indice de uma repeticao tipo referencia de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- prRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, LBSC_Reference *prRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( prRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}

/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (BYTE)
	Obtem o indice de uma repeticao tipo BYTE de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pbRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, BYTE *pbRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( pbRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (BYTE)
	Obtem o indice de uma repeticao tipo BYTE de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pbRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, BYTE *pbRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( pbRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}


/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (short int)
	Obtem o indice de uma repeticao tipo short int de um campo da base

	Parameters:
		- szField	-> nome do campo
		- psiRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, short int *psiRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( psiRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (short int)
	Obtem o indice de uma repeticao tipo short int de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- psiRep	-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, short int *psiRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( psiRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (float)
	Obtem o indice de uma repeticao tipo float de um campo da base

	Parameters:
		- szField	-> nome do campo
		- pfRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( char *szField, float *pfRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
//	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) ((*this)[ szField ]).GetId(), 
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	int iRet = pf->GetRepetitionByVal( pfRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}



/***
	PUBLIC
	Metodo GetFieldRepetitionByVal (float)
	Obtem o indice de uma repeticao tipo float de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- pfRep		-> conteudo da repeticao a ser procurado
		- bStart	-> indica se a busca deve ser feita a partir
				   do inicio da lista de repeticoes (TRUE, default)
				   ou a partir da posicao corrente (FALSE)

	Return:
		- O indice da repeticao em caso de sucesso.

	Comments:

***/
int
LBSC_Base::GetFieldRepetitionByVal( UINT uiFieldId, float *pfRep, BOOL bStart )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetitionByVal") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int iRet = pf->GetRepetitionByVal( pfRep, bStart );
	SetError( iRet >= 0 ? LBS_OK : iRet );
	return( iRet );
}


/******************************************************************************
				PUT FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo PutFieldRepetition (string)
	Adiciona uma string em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- szRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( char *szField, char *szRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szRepetition ){
		ERETURN( LBSE_BADARG );
	}

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( szRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (string)
	Adiciona uma string em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- szRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, char *szRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !szRepetition ){
		ERETURN( LBSE_BADARG );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( szRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetition (void)
	Adiciona um buffer void em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- pvRepetition	-> repeticao a ser adicionada
		- lSize		-> tamanho da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( char *szField, void *pvRepetition, long lSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !pvRepetition || lSize < 1 ){
		ERETURN( LBSE_BADARG );
	}

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( pvRepetition, TAIL_REPETITION, lSize );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (void)
	Adiciona um buffer void em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- pvRepetition	-> repeticao a ser adicionada
		- lSize		-> tamanho da repeticao

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, void *pvRepetition, long lSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !pvRepetition || lSize < 1 ){
		ERETURN( LBSE_BADARG );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( pvRepetition, TAIL_REPETITION, lSize );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (long)
	Adiciona um numero inteiro em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- lRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, long lRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &lRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (long)
	Adiciona um numero inteiro em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- lRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, long lRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &lRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (double)
	Adiciona um numero double em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- dRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, double dRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &dRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (double)
	Adiciona um numero double em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- dRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, double dRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &dRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (date)
	Adiciona uma data em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- cdRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, C_Date cdRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	JulTy	jtDate = cdRepetition.Hash();

	int	iRet = pf->PutRepetition( &jtDate, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (date)
	Adiciona uma data em um campo da base (no registro corrente)

	Parameters:
		- iFieldID	-> identificador do campo
		- cdRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, C_Date cdRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	JulTy	jtDate = cdRepetition.Hash();

	int	iRet = pf->PutRepetition( &jtDate, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (time)
	Adiciona uma hora em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- ctRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, C_Time ctRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	ClockTy ctTime = ctRepetition.Seconds();

	int	iRet = pf->PutRepetition( &ctTime, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (time)
	Adiciona uma hora em um campo da base (no registro corrente)

	Parameters:
		- iFieldID	-> identificador do campo
		- pctRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, C_Time ctRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	ClockTy ctTime = ctRepetition.Seconds();

	int	iRet = pf->PutRepetition( &ctTime, TAIL_REPETITION );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo PutFieldRepetition (binario)
	Adiciona uma repeticao binaria em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- bRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( char *szField, LBSC_Binary *bRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( bRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (binary)
	Adiciona uma repeticao tipo binary em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- bRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, LBSC_Binary *bRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( bRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetition (referencia)
	Adiciona uma repeticao tipo referencia em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- rRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( char *szField, LBSC_Reference *prRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
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
		iRet = pf->PutRepetition( pRefAux, TAIL_REPETITION );
		if( prRepetition->iFormat == LBSRT_URL ){
			LBSC_Reference::Free( pRefAux );
		}
	} else {
		iRet = pf->PutRepetition( prRepetition, TAIL_REPETITION );
	}
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (reference)
	Adiciona uma repeticao tipo reference em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- rRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.
***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, LBSC_Reference *prRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
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
		iRet = pf->PutRepetition( pRefAux, TAIL_REPETITION );
		if( prRepetition->iFormat == LBSRT_URL ){
			LBSC_Reference::Free( pRefAux );
		}
	} else {
		iRet = pf->PutRepetition( prRepetition, TAIL_REPETITION );
	}
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetition (BYTE)
	Adiciona um BYTE em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- bRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, BYTE bRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &bRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (BYTE)
	Adiciona um BYTE em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- bRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, BYTE bRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &bRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PutFieldRepetition (short int)
	Adiciona um numero short int em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- siRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, short int siRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &siRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (short int)
	Adiciona um numero short int em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- siRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, short int siRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &siRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (float)
	Adiciona um numero float em um campo da base (no registro corrente)

	Parameters:
		- szField	-> nome do campo
		- fRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( char *szField, float fRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord [ szField ];

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &fRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo PutFieldRepetition (float)
	Adiciona um numero float em um campo da base (no registro corrente)

	Parameters:
		- uiFieldId	-> identificador do campo
		- fRepetition	-> repeticao a ser adicionada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- Este metodo age somente em memoria, nao gravando o registro em
		  disco.

***/
int
LBSC_Base::PutFieldRepetition( UINT uiFieldId, float fRepetition )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	int	iRet = pf->PutRepetition( &fRepetition, TAIL_REPETITION );
	ERETURN( iRet );
}

