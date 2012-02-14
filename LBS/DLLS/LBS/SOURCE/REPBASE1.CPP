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
// Module: REPBASE1.CPP
// Description:
//
//	public methods file of then LBSC_BASE class
//	Methods with fields or repetitions
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//		Alessandro A. Jatoba'*
//
// Last update: 07/04/95
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

// $$$ API LIGHT-TEXT
#include	<lt.h>


// IMPORTANTE:
// O objeto GLT_Session eh definido automaticamente pela API Light Text e eh
// usado para inicializar algumas coisas assim que este codigo entra no ar.
// Tambem eh usado para manipular sistemas de indices.
// O arquivo lt.h o declara.


// Prototypes

// Global variables


EXTLOG( _clLBSLog );	// objeto para geracao de log

/******************************************************************************
				MODIFY FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldRepetition (string)
	Modifica a repeticao (do tipo string) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- szNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, char *szNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Data	*pd = (*pf)[ iRepetition ];
	if( pd ){
		(*pd) = szNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}


/***
	PUBLIC
	Metodo ModifyFieldRepetition (string)
	Modifica a repeticao (do tipo string) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- szNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, char *szNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data	*pd = (*pf)[iRepetition ];
	if( pd ){
		(*pd) = szNewVal;
		pf->UpdateFieldFlag( TRUE );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (void)
	Modifica a repeticao (do tipo void) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- pvNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, void *pvNewVal, long lNewSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		pd->ModifyData( pvNewVal, lNewSize );
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}


/***
	PUBLIC
	Metodo ModifyFieldRepetition (void)
	Modifica a repeticao (do tipo void) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- pvNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, void *pvNewVal, long lNewSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		pd->ModifyData( pvNewVal, lNewSize );
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (long)
	Modifica a repeticao (do tipo int) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- lNewVal	-> novo valor da repeticao

	Return:
		LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, long lNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = lNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (long)
	Modifica a repeticao (do tipo int) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- lNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, long lNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = lNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (double)
	Modifica a repeticao (do tipo double) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- dNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, double dNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = dNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (double)
	Modifica a repeticao (do tipo double) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- dNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, double dNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = dNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (date)
	Modifica a repeticao (do tipo date) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- cdNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, C_Date cdNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = cdNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (date)
	Modifica a repeticao (do tipo date) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- cdNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, C_Date cdNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = cdNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (time)
	Modifica a repeticao (do tipo time) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- ctNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, C_Time ctNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = ctNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (time)
	Modifica a repeticao (do tipo time) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- ctNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, C_Time ctNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = ctNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}

/***
	PUBLIC
	Metodo ModifyFieldRepetition (binary)
	Modifica a repeticao (do tipo binary) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- bNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, LBSC_Binary *bNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = (*bNewVal);
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (binary)
	Modifica a repeticao (do tipo binary) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- bNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, LBSC_Binary *bNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = (*bNewVal);
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (reference)
	Modifica a repeticao (do tipo reference) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- rNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, LBSC_Reference *prNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = (*prNewVal);
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (reference)
	Modifica a repeticao (do tipo reference) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- rNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, LBSC_Reference *prNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = (*prNewVal);
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}


/***
	PUBLIC
	Metodo ModifyFieldRepetition (BYTE)
	Modifica a repeticao (do tipo BYTE) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- bNewVal	-> novo valor da repeticao

	Return:
		LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, BYTE bNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = bNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (BYTE)
	Modifica a repeticao (do tipo BYTE) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- bNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, BYTE bNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = bNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}

/***
	PUBLIC
	Metodo ModifyFieldRepetition (short int)
	Modifica a repeticao (do tipo short int) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- siNewVal	-> novo valor da repeticao

	Return:
		LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, short int siNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = siNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (short int)
	Modifica a repeticao (do tipo short int) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- siNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, short int siNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = siNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (float)
	Modifica a repeticao (do tipo float) de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepetition	-> numero da repeticao
		- fNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( char *szField, int iRepetition, float fNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord[ szField ];
	
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = fNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}



/***
	PUBLIC
	Metodo ModifyFieldRepetition (float)
	Modifica a repeticao (do tipo float) de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepetition	-> numero da repeticao
		- fNewVal	-> novo valor da repeticao

	Return:
		- LBS_OK se conseguir modificar a repeticao ou erro.

	Comments:

***/
int
LBSC_Base::ModifyFieldRepetition( UINT uiFieldId, int iRepetition, float fNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_WRITE ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Data	*pd = (*pf) [ iRepetition ];
	
	if( pd ){
		(*pd) = fNewVal;
		pf->UpdateFieldFlag( TRUE, iRepetition );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_REPETITIONNOTFOUND );
}

/******************************************************************************
				GET FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldRepetition (string)
	Obtem uma string de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- szReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- A string apontada por szReturn deve ter tamanho suficiente
		  para armazenar o valor de retorno.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, char *szReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	strcpy( szReturn, (char*) pcData->GetConstData() );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (string)
	Obtem uma string de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- szReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- A string apontada por szReturn deve ter tamanho suficiente
		  para armazenar o valor de retorno.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, char *szReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData =  (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != ALPHA_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	strcpy( szReturn, (char*) pcData->GetConstData() );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (void)
	Obtem uma string de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pvReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pvReturn.
		- O buffer apontado por pvReturn deve ter tamanho suficiente
		  para armazenar o valor de retorno.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, void *pvReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != TEXT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pvReturn, (void*) pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (string)
	Obtem uma string de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pvReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pvReturn.
		- O buffer apontado por pvReturn deve ter tamanho suficiente
		  para armazenar o valor de retorno.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, void *pvReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != TEXT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pvReturn, (void*) pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (long)
	Obtem um numero inteiro de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- plReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro piReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, long *plReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != VALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( plReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (long)
	Obtem um numero inteiro de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- plReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro piReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, long *plReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != VALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( plReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (double)
	Obtem um numero double de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pdReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pdReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, double *pdReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != DVALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pdReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (double)
	Obtem um numero double de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pdReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pdReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, double *pdReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != DVALUE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pdReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (date)
	Obtem uma data de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pcdReturn	-> buffer que receberah o valor

	Return:
		LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pcdReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, C_Date *pcdReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != DATE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	*pcdReturn = JULIANDATE( (JulTy) (*pcData) );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (date)
	Obtem uma data de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pcdReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pcdReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, C_Date *pcdReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != DATE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	*pcdReturn = JULIANDATE( (JulTy) (*pcData) );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (time)
	Obtem uma hora de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pctReturn	-> buffer que receberah o valor

	Return:
		LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pctReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, C_Time *pctReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != TIME_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	*pctReturn = SECONDTIME( (JulTy) (*pcData) );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (time)
	Obtem uma hora de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pctReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pctReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, C_Time *pctReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != TIME_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	*pctReturn = SECONDTIME( (JulTy) (*pcData) );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetFieldRepetition (binario)
	Obtem uma string de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pbReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, LBSC_Binary *pbReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != BINARY_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}

	LBSC_Binary *pAux = (LBSC_Binary*) (*pcData);
	if( !pAux ){
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	(*pbReturn) = (*pAux);

	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (binario)
	Obtem uma string de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pbReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, LBSC_Binary *pbReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf)[ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != BINARY_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}

	LBSC_Binary *pAux = (LBSC_Binary*) (*pcData);
	if( !pAux ){
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	(*pbReturn) = (*pAux);
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (referencia)
	Obtem uma repeticao tipo referencia de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- prReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, LBSC_Reference *prReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != REFERENCED_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}

	LBSC_Reference *pAux = (LBSC_Reference*) (*pcData);
	if( !pAux ){
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	(*prReturn) = (*pAux);
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo GetFieldRepetition (referencia)
	Obtem uma repeticao tipo referencia de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- prReturn	-> buffer onde a repeticao serah colocada

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro szReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, LBSC_Reference *prReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != REFERENCED_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}

	LBSC_Reference *pAux = (LBSC_Reference*) (*pcData);
	if( !pAux ){
		ERETURN( LBSE_REPETITIONNOTFOUND );
	}
	(*prReturn) = (*pAux);
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetFieldRepetition (BYTE)
	Obtem um BYTE de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pbReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pbReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, BYTE *pbReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != BYTE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pbReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (BYTE)
	Obtem um BYTE de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pbReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pbReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, BYTE *pbReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != BYTE_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pbReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetFieldRepetition (short int)
	Obtem um numero short int de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- psiReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro psiReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, short int *psiReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != SINT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( psiReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (short int)
	Obtem um numero short int de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- psiReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro psiReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, short int *psiReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != SINT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( psiReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (float)
	Obtem um numero float de um campo da base

	Parameters:
		- szField	-> nome do campo
		- iRepNumber	-> numero da repeticao
		- pfReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pfReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( char *szField, int iRepNumber, float *pfReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

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
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != FLOAT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pfReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo GetFieldRepetition (float)
	Obtem um numero float de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- iRepNumber	-> numero da repeticao
		- pfReturn	-> buffer que receberah o valor

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- O valor eh retornado atraves do parametro pfReturn.
		- O valor de retorno pode ser alterado pelo usuario.

***/
int
LBSC_Base::GetFieldRepetition( UINT uiFieldId, int iRepNumber, float *pfReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
			USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		ERETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Data *pcData = (*pf) [ iRepNumber ];
	if( !pcData ){
		ERETURN( LBSE_INVALIDDATA );
	}
	if( pcData->GetType() != FLOAT_FIELD ){
		ERETURN( LBSE_INVALIDFIELDTYPE );
	}
	memcpy( pfReturn, pcData->GetConstData(), pcData->GetSize() );
	ERETURN( LBS_OK );
}
