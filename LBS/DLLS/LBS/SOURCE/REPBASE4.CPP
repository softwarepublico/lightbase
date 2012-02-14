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
// Module: REPBASE4.CPP
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
#ifndef	_BUFFERCL_H_
#include	<buffercl.h>
#endif
#include <baseinstance.h>

// API LIGHT-TEXT
#include	<lt.h>


EXTLOG( _clLBSLog );	// objeto para geracao de log

/******************************************************************************
				MODIFY FIELD INDEX ATTRIB
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldIndexAttrib
	Modifica os atributos de indexacao de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo
		- szPassword		-> password do campo
		- iIndexAttrib		-> mascara com os novos indices

	Return:
		- LBS_OK se conseguir modificar a password do campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.
		- E' aconselhavel reprocessar a base depois de usar este metodo.

***/
int
LBSC_Base::ModifyFieldIndexAttrib( char *szFieldAliasName, char *szPassword, int iIndexAttrib )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldIndexAttrib") );

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
	// Verificar se szPassword bate com a password atual do campo
	// (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// Nao eh o dono da base que estah logado
		// Checar permissoes de ACL
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];

		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
		if( lbscrCurrRecord.VerifyFieldPassword( szFieldAliasName, szPassword ) != LBS_OK ){
			ERETURN( LBSE_INVALIDPASSWORD );
		}
	}

	// MODIFICAR OS ATRIBUTOS DE INDEXACAO EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Checa password
				// Modifica atributos de indexacao
				tsrRec.tiaIndexAttrib = iIndexAttrib;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// $$$ MODIFICAR OS ATRIBUTOS DE INDEXACAO EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					if( lbscrCurrRecord.ModifyFieldIndexAttrib( szFieldAliasName,
						szPassword, iIndexAttrib )
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
	Metodo ModifyFieldIndexAttrib
	Modifica os atributos de indexacao de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo
		- szPassword	-> password do campo
		- iIndexAttrib	-> mascara com os novos indices

	Return:
		- LBS_OK se conseguir modificar a password do campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.
		- E' aconselhavel reprocessar a base depois de usar este metodo.

***/
int
LBSC_Base::ModifyFieldIndexAttrib( UINT uiFieldId, char *szPassword, int iIndexAttrib )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldIndexAttrib") );

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
		int	iRet = ModifyFieldIndexAttrib( (char*) plbscfAux->szAliasName, szPassword, iIndexAttrib );
		ERETURN( iRet );
	}
	ERETURN( LBSE_ERROR );  /// $$$ Falta definir o erro especifico
}


/******************************************************************************
				MODIFY FIELD ID
******************************************************************************/
/***
	PRIVATE
	Metodo ModifyFieldId
	Modifica o identificador de um campo (metodo privado)

	Parameters:
		- szFieldAliasName	-> nome do campo
		- uiNewId		-> novo identificador do campo

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		- Nao pede confirmacao.
		- A alteracao eh feita em memoria e em disco.
		- O numero do Last-Id eh alterado, se o uiNewId for maior que o
		  Last-Id atual.

***/
int
LBSC_Base::ModifyFieldId( char *szFieldAliasName, UINT uiNewId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldId") );

	TStructRec	tsrRec;
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}

	// MODIFICAR O ID EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Modifica id
				tsrRec.uiFieldId = uiNewId;
				if( LB3.R_Write( &tsrRec ) == OK ){

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					// atualiza o Last-Id, se necessario
					if( uiNewId >= LB1.tcrHead.uiLastFieldId ){
						LB1.tcrHead.uiLastFieldId = uiNewId;
						Flush( (const LBSC_Ticket*) plbscsOwnerSession->plbsctTicket );
					}
					// MODIFICAR O ID EM MEMORIA
					// como vamos mudar os nomes dos campos, eh melhor desabilitar a cache de campos
					lbscrCurrRecord.DelSortLists();
					if( lbscrCurrRecord.ModifyFieldId( szFieldAliasName,
						uiNewId ) == LBS_OK ){
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



/******************************************************************************
				MODIFY FIELD ATTRIB
******************************************************************************/
/***
	PUBLIC
	Metodo ModifyFieldAttrib
	Modifica os atributos de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo
		- szPassword		-> password do campo
		- uiFieldAttribPar	-> novos atributos

	Return:
		- LBS_OK se conseguir modificar os atributos do campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.
		- E' aconselhavel reprocessar a base depois de usar este metodo.

***/
int
LBSC_Base::ModifyFieldAttrib( char *szFieldAliasName, char *szPassword, UINT uiFieldAttribPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldAttrib") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	TStructRec	tsrRec;
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
	if ( !pBaseInstance ) {
		ERETURN( LBSE_BASENOTOPEN );
	}

	// vamos validar uiFieldAttribPar
	uiFieldAttribPar &= ~DELETED_FIELD;		// desliga o flag de delecao, caso esteja ligado

	// Verificar se szPassword bate com a password atual do campo
	// (apenas se o usuario nao for o dono da base nem o administrador)
	if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
		// Nao eh o dono da base que estah logado
		// Checar permissoes de ACL
		LBSC_Field	*pf = lbscrCurrRecord[ szFieldAliasName ];

		if( !pf ){
			ERETURN( LBSE_FIELDNOTFOUND );
		}
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_WRITE ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
		if( lbscrCurrRecord.VerifyFieldPassword( szFieldAliasName, szPassword ) != LBS_OK ){
			ERETURN( LBSE_INVALIDPASSWORD );
		}
	}

	// MODIFICAR OS ATRIBUTOS EM DISCO
	for( int i = 0; i < LB3.R_FileSize(); i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &tsrRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(tsrRec.uiFieldAttrib & DELETED_FIELD) ){
			if( tsrRec.szFieldAliasName == szFieldAliasName ){
				// Checa password
				// Modifica atributos de indexacao
				tsrRec.uiFieldAttrib = uiFieldAttribPar;

				if( LB3.R_Write( &tsrRec ) == OK ){
					// MODIFICAR OS ATRIBUTOS EM MEMORIA

					// invalida a cache de campos dessa base
					pBaseInstance->InvalidateBaseStruct();

					if( lbscrCurrRecord.ModifyFieldAttrib( szFieldAliasName,
						szPassword, uiFieldAttribPar ) == LBS_OK ){
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
	Metodo ModifyFieldAttrib
	Modifica os atributos de um campo da base

	Parameters:
		- uiFieldId			-> identificador do campo
		- szPassword		-> password do campo
		- uiFieldAttribPar	-> mascara com os novos indices

	Return:
		- LBS_OK se conseguir modificar os atributos do campo ou erro.

	Comments:
		- Nao pede confirmacao.
		- A base deve estar aberta com FullAccess, o que implica
		  dizer que o usuario passou a senha de manutencao e
		  abriu a base em modo exclusivo.
		- E' aconselhavel reprocessar a base depois de usar este metodo.

***/
int
LBSC_Base::ModifyFieldAttrib( UINT uiFieldId, char *szPassword, UINT uiFieldAttribPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyFieldAttrib") );

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
		int	iRet = ModifyFieldAttrib( (char*) plbscfAux->szAliasName, szPassword, uiFieldAttribPar );
		ERETURN( iRet );
	}
	ERETURN( LBSE_ERROR );  /// Falta definir o erro especifico
}


/******************************************************************************
				GET FIELD INDEX ATTRIB
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldIndexAttrib
	Obtem os atributos de indexacao de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo

	Return:
		- Mascara de bits contendo os indices do campo. Em caso de erro, o
		  retorno e' zero e a aplicacao deve checar LastError().

	Comments:
		-

***/
TIndexAttrib
LBSC_Base::GetFieldIndexAttrib( char *szFieldAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldIndexAttrib") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		SetError( LBSE_OBJNOTOK );
		return( 0 );
	}
	if( !szFieldAliasName ){
		SetError( LBSE_BADARG );
		return( 0 );
	}
	LBSC_Field	*pf = (*this)[ szFieldAliasName ];
	if( pf ){
		return( pf->GetIndexAttrib() );
	}
	return( 0 );
}



/***
	PUBLIC
	Metodo GetFieldIndexAttrib
	Obtem os atributos de indexacao de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo

	Return:
		- Mascara de bits contendo os indices do campo. Em caso de erro, o
		  retorno e' zero e a aplicacao deve checar LastError().

	Comments:
		-

***/
TIndexAttrib
LBSC_Base::GetFieldIndexAttrib( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldIndexAttrib") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		SetError( LBSE_OBJNOTOK );
		return( 0 );
	}
	LBSC_Field	*pf = (*this)( uiFieldId );
	if( pf ){
		return( pf->GetIndexAttrib() );
	}
	return( 0 );
}




/******************************************************************************
				GET FIELD INDEX TYPE
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldType
	Obtem o tipo de um campo da base

	Parameters:
		- szFieldAliasName	-> nome do campo

	Return:
		- Tipo do campo ou valor negativo em caso de erro

	Comments:
		-

***/
TFieldType
LBSC_Base::GetFieldType( char *szFieldAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldType") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		SetError( LBSE_OBJNOTOK );
		return( 0 );
	}
	if( !szFieldAliasName ){
		SetError( LBSE_BADARG );
		return( 0 );
	}
	LBSC_Field	*pf = (*this)[ szFieldAliasName ];
	if( pf ){
		return( pf->GetType() );
	}
	return( (TFieldType) -1 );
}



/***
	PUBLIC
	Metodo GetFieldType
	Obtem o tipo de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo

	Return:
		- Tipo do campo ou valor negativo em caso de erro

	Comments:
		-

***/
TFieldType
LBSC_Base::GetFieldType( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldType") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		SetError( LBSE_OBJNOTOK );
		return( 0 );
	}
	LBSC_Field	*pf = (*this)( uiFieldId );
	if( pf ){
		return( pf->GetType() );
	}
	return( (TFieldType) -1 );
}


/******************************************************************************
				GET NUMBER OF REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo GetNumberOfRepetition
	Obtem o numero de repeticoes de um campo da base

	Parameters:
		- szFieldAliasName

	Return:
		- O numero de repeticoes de um campo.

	Comments:

***/
int
LBSC_Base::GetNumberOfRepetition( char *szFieldAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumberOfRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}

	LBSC_Field	*pf = (*this)[ szFieldAliasName ];
	if( pf ){
		return( pf->GetNumberOfRepetition() );
	}
	ERETURN( LBSE_INVALIDFIELD );
}



/***
	PUBLIC
	Metodo GetNumberOfRepetition
	Obtem o numero de repeticoes de um campo da base

	Parameters:
		- uiFieldId	-> identificador do campo

	Return:
		- O numero de repeticoes de um campo.

	Comments:

***/
int
LBSC_Base::GetNumberOfRepetition( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumberOfRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field	*pf = (*this)( uiFieldId );
	if( pf ){
		return( pf->GetNumberOfRepetition() );
	}
	ERETURN( LBSE_INVALIDFIELD );
}


/******************************************************************************
				GET NUMBER OF FIELDS
******************************************************************************/
/***
	PUBLIC
	Metodo GetNumberOfFields
	Obtem o numero de campos do formato de uma base

	Parameters:

	Return:
		Numero de campos do formato da base.

	Comments:

***/
int
LBSC_Base::GetNumberOfFields()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumberOfFields") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	return( lbscrCurrRecord.GetNumberOfFields() );
}


/******************************************************************************
				OPERATORS
******************************************************************************/
/***
	PUBLIC
	Operador ()
	Obtem campo correspondente ao identificador passado

	Parameters:
		- uiFieldId	-> identificador do campo

	Return:
		- objeto LBSC_Field

	Comments:
		-

***/
LBSC_Field *
LBSC_Base::operator()( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::operator") );

	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );
	if( !pf ){
		NRETURN( LBSE_FIELDNOTFOUND );
	}
	SetError( LBS_OK );
	return( pf );
}



/***
	PUBLIC
	Operador [] (1)
	Obtem o n-esimo campo da lista de campos

	Parameters:
		- iFieldNumber	-> numero do campo

	Return:
		- objeto LBSC_Field

	Comments:
		-

***/
LBSC_Field *
LBSC_Base::operator[]( int iFieldNumber )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::operator") );

	LBSC_Field	*pf = lbscrCurrRecord[ iFieldNumber ];
	if( !pf ){
		NRETURN( LBSE_FIELDNOTFOUND );
	}
	SetError( LBS_OK );
	return( pf );
}




/***
	PUBLIC
	Operador [] (2)
	Obtem o campo correspondente ao nome de campo passado

	Parameters:
		- szFieldAliasName	-> nome do campo

	Return:
		- objeto LBSC_Field

	Comments:
		-

***/
LBSC_Field *
LBSC_Base::operator[]( char *szFieldAliasName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::operator") );

	if( !szFieldAliasName ){
		NRETURN( LBSE_BADARG );
	}
	LBSC_Field *pAux = (LBSC_Field*) GetFieldObj( szFieldAliasName );

	if( !pAux ){
		NRETURN( LBSE_FIELDNOTFOUND );
	}
	SetError( LBS_OK );
	return( pAux );
}



/***
	PUBLIC
	Metodo ClearRecord
	Limpa o registro corrente

	Parameters:

	Return:
		LBS_OK se conseguir limpar o registro ou erro.

	Comments:
		- Nao limpa o registro fisicamente. Para isso e necessario
		  chamar o metodo WriteRecord

***/
int
LBSC_Base::ClearRecord()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearRecord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	BYTE bStatus = 0;
	if ( lbscrCurrRecord.GetStatus() & REC_LOCKED ) {
		bStatus = REC_LOCKED;
	}
	if( lbscrCurrRecord.Clear( TRUE ) == LBS_OK ){
		lbscrCurrRecord.SetStatus( bStatus );
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}

/******************************************************************************
				GET FIELD OBJ
******************************************************************************/
/***
	PUBLIC
	Metodo GetFieldObj
	Obtem do registro corrente um objeto LBSC_Field a partir do nome de um
	campo

	Parameters:
		- szField -> nome do campo a ser obtido

	Return:
		- Apontador para um objeto LBSC_Field.

	Comments:

***/
const LBSC_Field *
LBSC_Base::GetFieldObj( char *szField )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldObj") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field *pf = (LBSC_Field*) lbscrCurrRecord.GetFieldObj( szField );
	if( !pf ){
		SetError( LBSE_FIELDNOTFOUND );
	} else {
		SetError( LBS_OK );
	}
	return( pf );
}



/***
	PUBLIC
	Metodo GetFieldObj
	Obtem do registro corrente um objeto LBSC_Field a partir do nome de um
	campo

	Parameters:
		- uiFieldId	-> identificador do campo a ser obtido

	Return:
		- Apontador para um objeto LBSC_Field.

	Comments:

***/
const LBSC_Field *
LBSC_Base::GetFieldObj( UINT uiFieldId )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFieldObj") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	LBSC_Field *plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiFieldId );
	if( !plbscfAux ){
		NRETURN( LBSE_FIELDNOTFOUND );
	}
	LBSC_Field	*pf = (LBSC_Field*) lbscrCurrRecord.GetFieldObj( (char*) plbscfAux->szAliasName );
	if( !pf ){
		SetError( LBSE_FIELDNOTFOUND );
	} else {
		SetError( LBS_OK );
	}
	return( pf );
}

/***
	PUBLIC
	Metodo GetFields
	Obtem um array de estruturas TField representando os
	campos da base.

	Parameters:
		- lbscTicket	-> ticket de acesso

	Return:
		- apontador para um array de estruturas TField ou
		  NULL em caso de erro.

	Comments:
		- A aplicacao deve liberar a memoria apontada pelo
		  retorno deste metodo.
		- A ultima estrutura do array contem 0 (zero) em todos
		  os campos. A aplicacao pode checar isso atraves do
		  metodo IsZero() da estrutura TField.
		- Este metodo retorna todos os campos da base, independentemente
		  de o usuario possuir acesso ou nao.

***/
TField *
LBSC_Base::GetFields( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFields") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	int	iNumFields = GetNumberOfFields();
	TField	*tf = new TField[ iNumFields + 1 ];
	if( !tf ){
		NRETURN( LBSE_NOMEMORY );
	}
	int j = 0;

	for( int i = 0; i < iNumFields; i++ ){
		// pra evitar a carga de todos os dados do registro so porque estamos querendo obter a estrutura
		BOOL bAux = lbscrCurrRecord.bMustLoadData;
		lbscrCurrRecord.bMustLoadData = FALSE;
		LBSC_Field	*pcfFieldAux = lbscrCurrRecord[ i ];
		// reabilita a carga dos dados dos campos
		lbscrCurrRecord.bMustLoadData = bAux;

		if( !pcfFieldAux ){
			NRETURN( LBSE_FIELDNOTFOUND );
		}

		tf[ j ].szFieldAliasName = pcfFieldAux->szAliasName;
		tf[ j ].szFieldDescription = pcfFieldAux->szFieldDescription;
		tf[ j ].szPasswordName = "";  // nao entregar a password
		tf[ j ].tftFieldType = pcfFieldAux->GetType();
		tf[ j ].lFieldSize = pcfFieldAux->GetSize();
		tf[ j ].uiFieldId = pcfFieldAux->GetId();
		tf[ j ].tiaIndexAttrib = pcfFieldAux->GetIndexAttrib();
		tf[ j ].uiFieldAttrib = pcfFieldAux->GetAttrib();
		j++;
	}
	SetError( LBS_OK );
	return( tf );
}


/******************************************************************************
				MGET FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo MGetFieldRepetition
	Obtem um conjunto de repeticoes, de varios tipos e tamanhos, de uma so' vez.

	Parameters:
		- puiFieldIds	->  vetor de UINTs contendo os identificadores de todos os
							campos desejados. O vetor deve conter um numero 0 (zero)
							no final, para que o LBS conheca a quantidade de campos
							desejados. Se o primeiro valor do vetor for 0 ou se 
							puiFieldIds for NULL, todos os campos da base serao retornados.

	Return:
		- ponteiro para uma tira de bytes contendo:
			- tamanho do buffer, em bytes (int)
			- id do campo 1 (UINT)
			-	num repeticoes (int)
			-		tam. prim. repeticao (int)
			-		prim. repeticao (void*)
			-		tam segunda repeticao (int)
			-		segunda repeticao (void*)
			-		...
			- id do campo 2 (UINT)
			-	num repeticoes (int)
			-		tam. prim. repeticao (int)
			-		prim. repeticao (void*)
			-		tam segunda repeticao (int)
			-		segunda repeticao (void*)
			-		...
			- 0 (indicando que acabou)

		- NULL indicando que houve erro.

	Comments:
		- Todas as repeticoes de cada campo serao retornadas, inclusive as repeticoes vazias
		  (se houver repeticoes validas apos as mesmas)
		- E' importante consultar LastError para verificar se houve alguma anormalidade na
		  execucao do metodo, mesmo que ele retorne != NULL (por exempo, houve negacao de
		  permissao para algum campo solicitado, o que gera um warning).
		- As permissoes de leitura de cada um dos campos eh checada e somente aqueles com
		  permissao positiva eh que farao parte do buffer de retorno.
		- Quando for indicado o tamanho de uma repeticao como sendo 0, a 
		  informacao nao estara' gravada no buffer. Assim, a proxima informacao eh o tamanho
		  da proxima repeticao.
		- Um tamanho de repeticao 0 indica que a repeticao nao existe no LBS

***/
void *
LBSC_Base::MGetFieldRepetition( UINT *puiFieldIds )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::MGetFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	if( lbscrCurrRecord.IsUndefined() ){
		NRETURN( LBSE_ERROR );
	}
	// algoritmo:
	//	- loop para cada um dos campos informados (ou todos os campos, se puiFieldsId[0] == 0)
	//		- verifica permissao do campo
	//		- loop para cada repeticao
	//			- incrementa tamanho do buffer tomando como base o tamanho da repeticao
	//	- aloca o bufferzao de retorno
	//	- loop para cada um dos campos informados (ou todos os campos, se puiFieldsId[0] == 0)
	//		- verifica permissao do campo
	//		- coloca o id do campo no bufferzao
	//		- coloca o numero de repeticoes no bufferzao
	//		- loop para cada uma das repeticoes do campo
	//			- coloca o tamanho da repeticao no bufferzao (se a rep. nao existir, o tam. e' -1)
	//			- coloca a propria repeticao no bufferzao (se ela existir)
	//	- coloca o id 0 (zero) no bufferzao

	UINT	uiFirstField = puiFieldIds ? puiFieldIds[ 0 ] : 0;
	int		iNumFields = GetNumberOfFields();
	int		iBufSize = sizeof( UINT );				// tamanho inicial, suficiente para o ultimo id

	if( uiFirstField ){
		for( iNumFields = 0; puiFieldIds[ iNumFields ]; iNumFields++ );
	}

	if( iNumFields == 0 ){
		// nao ha' campos na base
		NRETURN( LBSE_NOFIELD );
	}
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = uiFirstField ? lbscrCurrRecord( puiFieldIds[ i ] ) : lbscrCurrRecord[ i ];

		if( !pf ){
			// deu pau nesse field. vamos para o proximo.
			continue;
		}
		// Checar permissoes de ACL
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_READ ) != LBS_OK ){
			// usuario nao possui permissao para esse campo.
			// vamos para o proximo.
			continue;
		}
		iBufSize += sizeof( UINT );	// espaco para o identificador do campo f
		iBufSize += sizeof( int );	// espaco para a quantidade de repeticoes de f
		int	iRepNum = pf->GetNumberOfRepetition();
		if( iRepNum ){
			for( int j = 0; j < iRepNum; j++ ){
				LBSC_Data *pd = (*pf)[ j ];

				iBufSize += sizeof( int );	// espaco para o tamanho da repeticao
				if( pd ){
					// repeticao existe.
					iBufSize += pd->GetSize();
				}
			}
		}
	}
					 
	// agora temos o tamanho total do buffer ja' alocado.
	C_Buffer	cBuffer( iBufSize );
	char		*szRet = new char [ cBuffer.BufLen() ];

	if( !szRet ){
		// deu pau. que pena.
		NRETURN( LBSE_NOMEMORY );
	}
	if( iBufSize == sizeof( UINT ) ){
		// nao ha' permissao para nenhum campo.
		// vamos retornar o bufferzao contendo apenas um id de campo, que eh o 0 (zero),
		// indicando que nao ha' campos disponiveis para a aplicacao.
		UINT	uiId = 0;
		cBuffer.PutData( &uiId );

		memcpy( szRet, cBuffer.Buffer(), cBuffer.BufLen() );

		SetError( LBSE_NOPERMISSION );
		return( (void*) szRet );
	}

	// preencher o bufferzao
	for( i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = uiFirstField ? lbscrCurrRecord( puiFieldIds[ i ] ) : lbscrCurrRecord[ i ];

		if( !pf ){
			// deu pau nesse field. vamos para o proximo.
			continue;
		}
		// Checar permissoes de ACL
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, ACL_READ ) != LBS_OK ){
			// usuario nao possui permissao para esse campo.
			// vamos para o proximo.
			continue;
		}
		// copia o id do campo para o bufferzao
		UINT	uiId = pf->GetId();
		if( cBuffer.PutData( &uiId ) == FALSE ){
			// deu pau.
			NRETURN( LBSE_ERROR );
		}

		// copia a quantidade de repeticoes do campo para o bufferzao
		int		iNumRep = pf->GetNumberOfRepetition();

		if( cBuffer.PutData( &iNumRep ) == FALSE ){
			// deu pau
			NRETURN( LBSE_ERROR );
		}

		if( iNumRep ){
			// copia todas as repeticoes de f
			for( int j = 0; j < iNumRep; j++ ){
				LBSC_Data *pd = (*pf)[ j ];

				int	iRepSize;
				if( !pd ){
					// repeticao nao existe.
					iRepSize = 0;
				} else {
					iRepSize = pd->GetSize();
				}
				// copia o tamanho da repeticao do campo para o bufferzao
				if( cBuffer.PutData( &iRepSize ) == FALSE ){
					// deu pau
					NRETURN( LBSE_ERROR );
				}

				if( iRepSize > 0 ){
					// copia a repeticao do campo para o bufferzao
					if( cBuffer.PutData( (void*) pd->GetConstData(), iRepSize ) == FALSE ){
						// deu pau
						NRETURN( LBSE_ERROR );
					}
				}
			}
		}
	}
	// copia o ultimo id de campo para o bufferzao
	UINT	uiId = 0;
	if( cBuffer.PutData( &uiId ) == FALSE ){
		// deu pau
		NRETURN( LBSE_ERROR );
	}

	// copia o conteudo do buffer para uma area alocada que vai ser retornada.
	memcpy( szRet, cBuffer.Buffer(), cBuffer.BufLen() );

	// retorna
	SetError( LBS_OK );
	return( (void*) szRet );
}


/******************************************************************************
				MPUT FIELD REPETITION
******************************************************************************/
/***
	PUBLIC
	Metodo MPutFieldRepetition
	Seta um conjunto de repeticoes, de varios tipos e tamanhos, de uma so' vez.

	Parameters:
		- lbscTicket -> ticket de seguranca
		- pvBuffer	->  buffer contendo os campos e as repeticoes que devem ser setadas.
						o formato desse buffer deve ser o mesmo que e' gerado pelo metodo
						MGetFieldRepetition.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo, indicando 
		  erro ou um aviso de que a operacao nao foi totalmente realizada
		  (codigo LBSW_FAILURE).

	Comments:
		- Leia os comentarios sobre o metodo MGetFieldRepetition.
		- se houver erro durante o procedimento, o registro que esta' em disco e'
		  recarregado para a memoria para que os dados se tornem consistentes.
		- se houver alguma irregularidade no buffer (por exemplo, um dos
		  campos sem permissao), o procedimento tenta continuar e retorna
		  um aviso (LBSW_FAILURE) no final.

***/
int
LBSC_Base::MPutFieldRepetition( const LBSC_Ticket *lbscTicket, void *pvBuffer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::MPutFieldRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( lbscrCurrRecord.IsUndefined() ){
		ERETURN( LBSE_ERROR );
	}
	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !pvBuffer ){
		ERETURN( LBSE_BADARG );
	}
	// algoritmo:
	//	- varrer o buffer procurando identificadores de campo
	//	- para cada identificador de campo encontrado:
	//		- verificar permissoes
	//		- limpar todas as repeticoes do campo
	//		- ler o numero de repeticoes do campo
	//		- para cada repeticao do campo:
	//			- ler a repeticao do buffer
	//			- setar a repeticao no LBS

	C_Buffer	cb( ((char*)pvBuffer) + sizeof( int ), *((int*)pvBuffer) );
	UINT		uiFieldId;
	int			iNumRep;
	int			iRepSize;
	char		*szRep = NULL;
	BOOL		bErr = FALSE;

	// le^ o primeiro identificador de campo
	if( cb.GetData( &uiFieldId ) == FALSE ){
		// deu pau.
		ERETURN( LBSE_ERROR );
	}
	while( uiFieldId > 0 ){
		bErr = FALSE;
		LBSC_Field	*pf = lbscrCurrRecord( uiFieldId );
		if( !pf ){
			// deu pau nesse field.
			bErr = TRUE;
		}
		// Checar permissoes de ACL
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) uiFieldId, 
				USERFIELD, (ACL_WRITE | ACL_APPEND) ) != LBS_OK ){
			// usuario nao possui permissao para esse campo.
			bErr = TRUE;
		}
		if( !bErr ){
			// limpa as repeticoes do campo
			pf->Clear();
		}
		// le^ o numero de repeticoes do campo
		if( cb.GetData( &iNumRep ) == FALSE ){
			// deu pau. este erro eh critico porque nao da'
			// para pular informacoes no buffer e comecar
			// a trabalhar no proximo campo.
			ERETURN( LBSE_ERROR );
		}
		for( int j = 0; j < iNumRep; j++ ){
			// le^ o tamanho da repeticao
			if( cb.GetData( &iRepSize ) == FALSE ){
				// tambem eh um erro critico.
				ReadRecord( lbscTicket );
				ERETURN( LBSE_ERROR );
			}
			if( iRepSize <= 0 ){
				// a repeticao nao existe. vamos para a proxima
				continue;
			}

			szRep = new char[ iRepSize ];
			if( !szRep ){
				// deu pau.
				ReadRecord( lbscTicket );
				ERETURN( LBSE_NOMEMORY );
			}
			if( cb.GetData( (void*) szRep, iRepSize ) == FALSE ){
				// deu pau. erro critico.
				ReadRecord( lbscTicket );
				delete szRep;
				ERETURN( LBSE_ERROR );
			}
			if( !bErr ){
				pf->ModifyRepetitionByIndex( j, (void*) szRep, iRepSize );
			}
			delete szRep;

			// le^ mais um identificador de campo
			if( cb.GetData( &uiFieldId ) == FALSE ){
				// deu pau.
				ERETURN( LBSE_ERROR );
			}
		}
	}
	if( bErr ){
		ERETURN( LBSW_FAILURE );
	}
	ERETURN( LBS_OK );
}



/**********************************************************
// Function name	: LBSC_Base::InsertBlankRepetition
// Description	    : 
// Return type		: int 
// Argument         :  UINT uiFieldId
// Argument         : int iIndex
**********************************************************/
int LBSC_Base::InsertBlankRepetition( UINT uiFieldId, int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::InsertBlankRepetition") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( lbscrCurrRecord.IsUndefined() ){
		ERETURN( LBSE_ERROR );
	}
	LBSC_Field	*pf = lbscrCurrRecord ( uiFieldId );

	if( !pf ){
		return( LastError() );
	}
	if( iIndex < 0 ){
		// indice corrente
		iIndex = pf->lbscdlDataList.GetCurrentIndex();
	}
	if( iIndex >= pf->GetNumberOfRepetition() ){
		ERETURN( LBSE_INVALIDINDEX );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), (long) pf->GetId(), 
				USERFIELD, 
				ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	pf->FillOriginalDataList();

	// faz um shift das repeticoes, abrindo um buraco na posicao iIndex
	int iNumRep = pf->GetNumberOfRepetition();

	if( iNumRep > 0 ){
		LBSC_Data	*pd;

		// preciso criar uma repeticao nova no final
		pd = (*pf)[ iNumRep ];

		// agora preciso deslocar todas as repeticoes para a direita,
		// do iIndex ate' o final da lista
		pf->UpdateFieldFlag( TRUE, iIndex );
		for( int i = iNumRep; i > iIndex; i-- ){
			LBSC_Data	*pdAux = pf->lbscdlDataList[ i - 1 ];

			if ( pdAux ) {
				pdAux->SetModified( TRUE );
			}

			pf->lbscdlDataList[ i ];
			pf->lbscdlDataList.Refresh( pdAux );
		}
		pf->lbscdlDataList[ i ];
		pf->lbscdlDataList.Refresh( pd );

		// agora deixar a repeticao iIndex com um valor
		// que a identifique como um buraco
		pd->SetStatus( DATA_HOLE );

		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}


