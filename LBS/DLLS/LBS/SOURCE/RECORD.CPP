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
// Module: RECORD.CPP
// Description:
//
//	Methods file for records handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 05/09/94
//

#if !defined __DOS_H && !defined _INC_DOS
#include	<dos.h>
#endif
#if !defined __IO_H && !defined _INC_IO
#include	<io.h>
#endif
#if !defined(__LOCKING_H) && !defined _INC_LOCKING
#include	<sys\locking.h>
#endif
#ifndef	_RECORD_H_
#include	<record.h>
#endif
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif
#ifndef _INC_ERRNO
#include	<errno.h>
#endif
#include	<baseinstance.h>

#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif

extern	int	errno;

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include <LZO.h>

/***
	PUBLIC
	Metodo LBSC_Record
	Construtor do objeto LBSC_Record

	Parameters:

	Return:

	Comments:

***/

LBSC_Record::LBSC_Record():
	cdCreateDate(),
	cdLastUpdateDate(),
	lbscpPassword( DEFRECORDPASSWORD )
{
	lRecInitPos = 0;
	szLastUpdateUserName = "$$$";
	szOwnerName = "$$$";
	bStatus = 0;
	plbscbBase = NULL;
	bIsUndefined = TRUE;
	pcSortListByAlias = NULL;
	pcSortListById = NULL;
	pRecordBuffer = NULL;
	pRecordFieldsHeader = NULL;
	lNumFieldsRead = 0;
	bMustLoadData = TRUE;
	pCurrField = NULL;
}


/***
	Metodo LBSC_Record
	Construtor 2 do objeto LBSC_Record

	Parameters:
		- plbscbOwnerBase

	Return:

	Comments:

***/
LBSC_Record::LBSC_Record( LBSC_Base *plbscbOwnerBase ):
	cdCreateDate(),
	cdLastUpdateDate(),
	lbscpPassword( DEFRECORDPASSWORD )
{
	lRecInitPos = 0;
	szLastUpdateUserName = "$$$";
	szOwnerName = "$$$";
	bStatus = 0;
	plbscbBase = plbscbOwnerBase;
	bIsUndefined = TRUE;
	pcSortListByAlias = NULL;
	pcSortListById = NULL;
	pRecordBuffer = NULL;
	pRecordFieldsHeader = NULL;
	lNumFieldsRead = 0;
	bMustLoadData = TRUE;
	pCurrField = NULL;
}


/***
	PUBLIC
	Metodo ~LBSC_Record
	Destrutor do objeto LBSC_Record

	Parameters:

	Return:

	Comments:

***/

LBSC_Record::~LBSC_Record()
{
	DelSortLists();
	FreeRecordBuffers();
}


/***
	PUBLIC
	Metodo Clear
	Limpa um objeto LBSC_Record

	Parameters:

	Return:
		- LBS_OK.

	Comments:
		- Todos os campos ficarao com uma repeticao apos a operacao
		  de "limpeza". As repeticoes terao o valor 0 (para cada
		  tipo de dado)

***/
int
LBSC_Record::Clear( BOOL bFillOriginalDataList )
{
	if( lbscFieldList.First() == NULL ){
		return( LBS_OK );
	}
	do{
		lbscFieldList.Current()->bMustFillOriginalDataList = bFillOriginalDataList;
		lbscFieldList.Current()->Clear();
		lbscFieldList.Current()->ClearNumberOfUpdates();
	}while( lbscFieldList.Next() != NULL );
	bStatus = 0;
	bIsUndefined = TRUE;
	ulAccess = 0L;
	FreeRecordBuffers();
	return( LBS_OK );
}


void
LBSC_Record::FreeRecordBuffers()
{
	if ( pRecordBuffer ) {
		delete pRecordBuffer;
	}
	pRecordBuffer = NULL;
	if ( pRecordFieldsHeader ) {
		delete pRecordFieldsHeader;
	}
	pRecordFieldsHeader = NULL;
	lNumFieldsRead = 0;
}


/***
	Metodo GetPassword
	Obtem a password do registro

	Parameters:

	Return:
		A password do registro. Disponivel apenas para consulta.

	Comments:
		- Este metodo retorna uma copia do buffer interno e
		  a aplicacao deve liberar o espaco alocado para a copia.

***/
const char *
LBSC_Record::GetPassword()
{
	return( lbscpPassword.GetConstPassword() );
}



/***
	Metodo ModifyPassword
	Modifica a password do registro

	Parameters:
		- szNewPassword

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyPassword( char *szNewPassword )
{
	if( lbscpPassword.Modify( szNewPassword ) == LBS_OK ){
		return( LBS_OK );
	}
	return( LBSE_ERROR );
}


/***
	Metodo GetFieldPassword
	Obtem a password de um campo

	Parameters:
		- szFieldName

	Return:
		- A password do campo. Disponivel apenas para consulta.

	Comments:
		- Este metodo NAO retorna uma copia do buffer interno.

***/
const char *
LBSC_Record::GetFieldPassword( char *szFieldName )
{
	LBSC_Field *pf = FindByAlias( szFieldName );

	if( pf == NULL ){
		return( NULL );
	}
	return( pf->GetPassword() );
}


/***
	Metodo ModifyFieldPassword
	Modifica a password de um campo

	Parameters:
		- szFieldName
		- szOldPassword
		- szNewPassword

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyFieldPassword( char *szFieldName, char *szOldPassword, char *szNewPassword )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	if( pf->VerifyPassword( szOldPassword ) != LBS_OK ){
		return( LBSE_INVALIDPASSWORD );
	}
	return( pf->ModifyPassword( szNewPassword ) );
}


/***
	Metodo ModifyFieldIndexAttrib
	Modifica os atributos de indexacao de um campo

	Parameters:
		- szFieldName
		- szPassword
		- iIndexAttib

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyFieldIndexAttrib( char *szFieldName, char *szPassword, int iIndexAttib )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	if( pf->VerifyPassword( szPassword ) != LBS_OK ){
		return( LBSE_INVALIDPASSWORD );
	}
	return( pf->SetIndexAttrib( iIndexAttib ) );
}


/***
	Metodo ModifyFieldId
	Modifica o id de um campo

	Parameters:
		- szFieldName
		- uiNewId

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyFieldId( char *szFieldName, UINT uiNewId )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	pf->SetId( uiNewId );
	return( LBS_OK );
}


/***
	Metodo ModifyFieldAttrib
	Modifica os atributos de um campo

	Parameters:
		- szFieldName
		- szPassword
		- uiFieldAttribPar

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyFieldAttrib( char *szFieldName, char *szPassword, UINT uiFieldAttribPar )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	if( pf->VerifyPassword( szPassword ) != LBS_OK ){
		return( LBSE_INVALIDPASSWORD );
	}
	pf->SetAttrib( uiFieldAttribPar );
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo AddField
	Adiciona um campo a lista de campos do registro corrente

	Parameters:
		- lbscField
		- iInsertType

	Return:
		LBS_OK se conseguir inserir ou erro.

	Comments:

***/
int
LBSC_Record::AddField( LBSC_Field *lbscField, int iInsertType )
{
	DelSortLists();	// cache de campos esta invalida
	return( lbscFieldList.Add( lbscField, iInsertType ) );
}


/***
	PUBLIC
	Metodo ModifyField
	Modifica um campo da lista de campos do registro corrente

	Parameters:
		- szOldField	-> nome do campo a ser modificado
		- plbscNewField	-> novo campo

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Record::ModifyField( char *szOldField, LBSC_Field *plbscNewField )
{
	LBSC_Field	lbscfAux( szOldField, "$$$", "$$$", 0, 1, 0, 0 );

	if( lbscFieldList.Find( &lbscfAux, CMPFIELDNAME ) == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	if( lbscFieldList.Del() != LBS_OK ){
		return( LBSE_FIELDNOTDELETED );
	}
	DelSortLists();	// cache de campos esta invalida
	if( lbscFieldList.Current() == lbscFieldList.Last() ){
		return( lbscFieldList.Add( plbscNewField, AFTER ));
	}
	return( lbscFieldList.Add( plbscNewField, BEFORE ) );
}


/***
	PUBLIC
	Metodo DelField
	Deleta um campo da lista de campos do registro corrente

	Parameters:
		- szFieldName	-> nome do campo a ser deletado

	Return:
		- LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_Record::DelField( char *szFieldName )
{
	LBSC_Field	lbscfAux( szFieldName, "$$$", "$$$", 0, 1, 0, 0 );

	if( lbscFieldList.Find( &lbscfAux, CMPFIELDNAME ) == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	DelSortLists();	// cache de campos esta invalida
	return( lbscFieldList.Del() != LBS_OK ? LBSE_FIELDNOTDELETED : LBS_OK );
}

void
LBSC_Record::DelAllFields()
{
	lbscFieldList.DelAll();
}

LBSC_Field *
LBSC_Record::CurrentField()
{
	return pCurrField;
}

/***
	PUBLIC
	Metodo DelField
	Deleta um campo da lista de campos do registro corrente

	Parameters:
		- uiFieldId	-> id do campo a ser deletado

	Return:
		- LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_Record::DelField( UINT uiFieldId )
{
	LBSC_Field	lbscfAux( "$$$", "$$$", "$$$", 0, 1, uiFieldId, 0 );

	if( lbscFieldList.Find( &lbscfAux, CMPFIELDID ) == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	DelSortLists();	// cache de campos esta invalida
	return( lbscFieldList.Del() != LBS_OK ? LBSE_FIELDNOTDELETED : LBS_OK );
}


/***
	PUBLIC
	Metodo GetNumberOfFields
	Obtem o numero de campos da lista de campos do registro corrente

	Parameters:

	Return:
		O numero de campos.

	Comments:

***/
int
LBSC_Record::GetNumberOfFields()
{
	return( lbscFieldList.NumElem() );
}


/***
	PUBLIC
	Metodo VerifyPassword
	Verifica se a password passada como parametro e igual a corrente

	Parameters:
		- szOldPassword

	Return:
		LBS_OK se forem iguais ou outro valor se nao.

	Comments:

***/
int
LBSC_Record::VerifyPassword( char *szOldPassword )
{
	return( lbscpPassword.Verify( szOldPassword ) );
}


/***
	PUBLIC
	Metodo VerifyFieldPassword
	Verifica se a password de um campo passada como parametro e igual a do
	campo corrente

	Parameters:
		- szFieldName	-> nome do campo
		- szOldPassword	-> password a ser checada

	Return:
		- LBS_OK se forem iguais ou outro valor se nao.

	Comments:

***/
int
LBSC_Record::VerifyFieldPassword( char *szFieldName, char *szOldPassword )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}
	return( pf->lbscpPassword.Verify( szOldPassword ) );
}


/***
	PUBLIC
	Metodo DelFieldRepetition
	Deleta uma repeticao de um campo atraves do indice fornecido como parametro

	Parameters:
		- szFieldName
		- iIndex
		- bShift -> indica se as repeticoes restantes devem ser deslocadas
				    uma posicao para ocupar o buraco deixado pela delecao.
					O default eh nao fazer o shift (FALSE).

	Return:
		LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_Record::DelFieldRepetition( char *szFieldName, int iIndex, BOOL bShift )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( LBSE_FIELDNOTFOUND );
	}

	pCurrField = pf;
	if ( !FillFieldFromBuffer(pf) ) {
		return LBSE_WRONGRECORD;
	}

	return( pf->DeleteRepetitionByIndex( iIndex, TRUE, bShift ) );
}


/***
	Metodo GetFieldObj
	Obtem o apontador para o objeto LBSC_Field a partir do nome

	Parameters:
		- szFieldName

	Return:
		Apontador para objeto LBSC_Field

	Comments:

***/
const LBSC_Field *
LBSC_Record::GetFieldObj( char *szFieldName )
{
	LBSC_Field *pf = FindByAlias( szFieldName );
	if( pf == NULL ){
		return( NULL );
	}
	pCurrField = pf;
	if ( !FillFieldFromBuffer(pf) ) {
		return NULL;
	}

	return( pf );
}


/***
	PUBLIC
	Metodo Delete
	Deleta o registro fisicamente

	Parameters:
		- pcfFile

	Return:
		LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_Record::Delete( C_LB1 *pcfFile )
{
	TControlRec	tcrControlRec;

	if ( !( bStatus & REC_LOCKED ) ){
		return( LBSE_RECORDNOTLOCKED );
	}

	if( pcfFile->R_Read( &tcrControlRec ) != OK ){
		return( LBSE_ERROR );
	}

	this->cdLastUpdateDate = JULIANDATE( C_Date().Hash() );
	tcrControlRec.ulModifyDate = this->cdLastUpdateDate.Hash();
	this->bStatus |= REC_EXCLUDED;
	tcrControlRec.bRecStatus = this->bStatus;
	tcrControlRec.bRecStatus &= ~REC_LOCKED;
	tcrControlRec.ulAccess++;

	if( pcfFile->R_Write( &tcrControlRec ) != OK ){
		return( LBSE_ERROR );
	}
	return( LBS_OK );
}



/***
	PUBLIC
	Metodo Lock
	Trava o registro

	Parameters:
		- pcfControlFile

	Return:
		LBS_OK se conseguir travar ou erro.

	Comments:

***/
int
LBSC_Record::Lock( C_LB1 *pcfControlFile ) // #$#
{
	if( bStatus & REC_LOCKED ){	// this record is already locked by this user
		return( LBS_OK );
	}

	// travar apenas os primeiros bytes do registro de LB1,
	// que representam a data de criacao do registro. isso
	// possibilita a leitura do registro por outros modulos.
	if( pcfControlFile->R_Lock( 0, sizeof( unsigned long ) ) == OK ){
		bStatus |= REC_LOCKED;
		return( LBS_OK );
	}
	return( errno == 0 ? EACCES : errno );
}



/***
	PUBLIC
	Metodo Release
	Libera um registro previamente travado

	Parameters:
		- pcfControlFile

	Return:
		LBS_OK se conseguir liberar ou erro.

	Comments:

***/
int
LBSC_Record::Release( C_LB1 *pcfControlFile )
{
	if( ! ( bStatus & REC_LOCKED ) ){
		return( LBS_OK );
	}

	if( pcfControlFile->R_Release( 0, sizeof( unsigned long ) ) == OK ){
		bStatus &= ~REC_LOCKED;
		return( LBS_OK );
	}
	return( errno );
}



/***
	PUBLIC
	Metodo GetStatus
	Obtem o status do registro

	Parameters:

	Return:
		O status do registro.

	Comments:

***/
BYTE
LBSC_Record::GetStatus()
{
	return( bStatus );
}


/***
	Metodo IsUndefined
	Obtem o estado de definicao do registro (se ele estah definido ou nao)

	Parameters:

	Return:
		Estado do registro

	Comments:

***/
BOOL
LBSC_Record::IsUndefined()
{
	return( bIsUndefined );
}



/***
	Metodo Id
	Obtem um campo atraves do seu identificador

	Parameters:
		- uiId	-> identificador do campo que se deseja obter

	Return:
		- o campo encontrado ou NULL se nao existir campo
		  com o Id especificado
		- este metodo altera o campo corrente da lista de campos
***/
const LBSC_Field *
LBSC_Record::Id( UINT uiId )
{
	return( FindById( uiId ) );
}



/***
	PUBLIC
	Metodo NthField
	Obtem o n-esimo campo da lista de campos

	Parameters:
		- iPos	-> posicao na lista

	Return:
		- o campo requerido

	Comments:
		-

***/
LBSC_Field *
LBSC_Record::NthField( int iPos )
{
	LBSC_Field *pAux = lbscFieldList.Nth( iPos );

	if ( !pAux ) {
		return NULL;
	}

	pCurrField = pAux;
	if ( !FillFieldFromBuffer(pAux) ) {
		return NULL;
	}

	return( pAux );
}

/***
***/
long
LBSC_Record::GetCreateDate()
{
	return( cdCreateDate.Hash() );
}

/***
***/
long
LBSC_Record::GetModifyDate()
{
	return( cdLastUpdateDate.Hash() );
}

/***
***/
char *
LBSC_Record::GetLastModifyUserName()
{
	return( (char*) szLastUpdateUserName );
}

/***
***/
const char *
LBSC_Record::GetOwnerName()
{
	return( (const char*) (char*) szOwnerName );
}

/***
***/
void
LBSC_Record::SetCreateDate( long lDate )
{
	cdCreateDate = JULIANDATE( lDate );
}


/***
***/
void
LBSC_Record::SetModifyDate( long lDate )
{
	cdLastUpdateDate = JULIANDATE( lDate );
}

/***
***/
void
LBSC_Record::SetStatus( BYTE bStatus )
{
	this->bStatus = bStatus;
}

/***
	PUBLIC
	Operador ()
	Obtem o campo cujo identificador bate com o parametro passado
	Parameters:
		- uiFieldId	-> identificador do campo a ser obtido
	Return:
		- o campo
	Comments:
		-

***/
LBSC_Field *
LBSC_Record::operator ()( UINT uiFieldId )
{
	LBSC_Field *pAux = (LBSC_Field *) Id( uiFieldId );
	if ( !pAux ) {
		return NULL;
	}

	pCurrField = pAux;
	if ( !FillFieldFromBuffer(pAux) ) {
		return NULL;
	}
	return( pAux );
}



/***
	PUBLIC
	Operador []
	Obtem o n-esimo campo da lista de campos
	Parameters:
		- iFieldNumber	-> indice do campo a ser obtido
	Return:
		- o campo
	Comments:
		-

***/
LBSC_Field *
LBSC_Record::operator []( int iFieldNumber )
{
	LBSC_Field *pf = NULL;
	if( iFieldNumber > -1 ){
		pf = lbscFieldList[ iFieldNumber ];
	} else {
		pf = lbscFieldList.Current();
	}
	if ( !pf ) {
		return NULL;
	}

	pCurrField = pf;
	if ( !FillFieldFromBuffer(pf) ) {
		return NULL;
	}
	return pf;
}

/***
	PUBLIC
	Operador []
	Obtem o n-esimo campo da lista de campos
	Parameters:
		- szFieldAliasName	-> nome do campo
	Return:
		- o campo
	Comments:
		-

***/
LBSC_Field *
LBSC_Record::operator[]( char *szFieldAliasName )
{
	if( !szFieldAliasName ){
		return( NULL );
	}
	return( FindByAlias( szFieldAliasName ) );
}

/***
	PUBLIC
	Operador =
	Faz uma copia do objeto (a = b, onde a eh this)
	Parameters:
		- b	-> objeto de origem
	Return:
		- o objeto a
	Comments:
		- este metodo poderia retornar void, mas com o retorno que ele
		  oferece eh possivel construir expressoes do tipo a = b = c ...

***/
LBSC_Record&
LBSC_Record::operator = ( LBSC_Record& b )
{
	if( this != &b ){
		if( lbscFieldList.NumElem() == b.lbscFieldList.NumElem() ){
			for( int i = 0; i < lbscFieldList.NumElem(); i++ ){
				LBSC_Field	*pf1 = (*this)[ i ];
				LBSC_Field	*pf2 = b[ i ];

				if( pf1 && pf2 ){
					(*pf1) = (*pf2);
				}
			}
		}
		FreeRecordBuffers();
		pRecordBuffer = new C_Buffer( (b.pRecordBuffer)->MyBuffer(), (b.pRecordBuffer)->MyBufLen() );
		lNumFieldsRead = b.lNumFieldsRead;
		pRecordFieldsHeader = new TRecordBufferHeader[lNumFieldsRead];
		memcpy( pRecordFieldsHeader, b.pRecordFieldsHeader, lNumFieldsRead*sizeof(TRecordBufferHeader) );
	}
	this->lRecInitPos = b.lRecInitPos;
	this->cdCreateDate = b.cdCreateDate;
	this->cdLastUpdateDate = b.cdLastUpdateDate;
	this->szLastUpdateUserName = b.szLastUpdateUserName;
	this->plbscbBase = b.plbscbBase;
	this->szOwnerName = b.szOwnerName;
	this->bStatus = b.bStatus;
	this->lbscpPassword.Modify( ( char * )b.lbscpPassword.GetConstPassword() );
	this->bIsUndefined = b.bIsUndefined;

	return *this;
}



int cmp_by_alias( const void *a, const void *b )
{
	LBSC_Field *pFieldA = *((LBSC_Field**)a);
	LBSC_Field *pFieldB = *((LBSC_Field**)b);
	return stricmp( pFieldA->GetAliasName(), pFieldB->GetAliasName() );
}

int cmp_by_id( const void *a, const void *b )
{
	LBSC_Field *pFieldA = *((LBSC_Field**)a);
	LBSC_Field *pFieldB = *((LBSC_Field**)b);
	return pFieldA->GetId() - pFieldB->GetId();
}

int find_by_alias( const void *a, const void *b )
{
	LPCTSTR szFieldAlias = (LPCTSTR)a;
	LBSC_Field *pFieldB = *((LBSC_Field**)b);
	return stricmp( szFieldAlias, pFieldB->GetAliasName() );
}

int find_by_id( const void *a, const void *b )
{
	UINT uiFieldId = *((UINT*)a);
	LBSC_Field *pFieldB = *((LBSC_Field**)b);
	return uiFieldId - pFieldB->GetId();
}


void LBSC_Record::FillSortLists()
{
	for( int i = 0; i < lbscFieldList.NumElem(); i++ ){
		LBSC_Field *pField = lbscFieldList[ i ];
		pcSortListByAlias [ i ] = pField;
		pcSortListById [ i ] = pField;
		if ( pField && pField->GetGroup() > 0 ) {
			LBSC_FieldGroup findGroup;
			findGroup.iGroup = pField->GetGroup();

			LBSC_FieldGroup *pFoundGroup = lbscflGroupList.Find( &findGroup, 0 );
			if ( !pFoundGroup ) {
				pFoundGroup = new LBSC_FieldGroup;
				pFoundGroup->iGroup = pField->GetGroup();
				lbscflGroupList.Add( pFoundGroup, TAIL );
			}
			pFoundGroup->lbscflFieldList.Add( pField, TAIL );
		}
	}
}

void LBSC_Record::SortFieldLists()
{
	DelSortLists();

	int iSize = lbscFieldList.NumElem();

	pcSortListByAlias = new LBSC_Field* [iSize];
	if( !pcSortListByAlias ){
		return;
	}
	pcSortListById = new LBSC_Field* [iSize];
	if( !pcSortListById ){
		delete pcSortListByAlias;
		pcSortListByAlias = NULL;
		return;
	}
	FillSortLists();
	qsort( pcSortListByAlias, iSize, sizeof( LBSC_Field* ), cmp_by_alias );
	qsort( pcSortListById, iSize, sizeof( LBSC_Field* ), cmp_by_id );
}

void LBSC_Record::DelSortLists( void )
{
	if( pcSortListByAlias ){
		delete pcSortListByAlias;
		pcSortListByAlias = NULL;
	}
	if( pcSortListById ){
		delete pcSortListById;
		pcSortListById = NULL;
	}
	lbscflGroupList.DelAll();
}

LBSC_Field *LBSC_Record::FindByAlias( char *szFieldAlias )
{
	LBSC_Field *pf = NULL;
	if ( !pcSortListByAlias ) {
		LBSC_Field	lbscfAux( szFieldAlias, "$$$", "$$$", 0, 1, 0, 0 );
		pf = lbscFieldList.Find( &lbscfAux, CMPFIELDNAME );
		if ( !pf ) {
			return NULL;
		}

		pCurrField = pf;
		if ( !FillFieldFromBuffer(pf) ) {
			return NULL;
		}
		return( pf );
	}

	LBSC_Field **ppField = (LBSC_Field **)bsearch( szFieldAlias, pcSortListByAlias, lbscFieldList.NumElem(), sizeof( LBSC_Field* ), find_by_alias );
	if ( ppField ) {
		pCurrField = *ppField;
		if ( !FillFieldFromBuffer(*ppField) ) {
			return NULL;
		}
		return *ppField;
	}

	return NULL;
}

LBSC_Field *LBSC_Record::FindById( UINT uiFieldId )
{
	LBSC_Field *pf = NULL;
	if ( !pcSortListById ) {
		LBSC_Field	lbscfAux( "$$$", "$$$", "$$$", 0, 1, uiFieldId, 0 );

		pf = lbscFieldList.Find( &lbscfAux, CMPFIELDID );
		if ( !pf ) {
			return NULL;
		}
		pCurrField = pf;
		if ( !FillFieldFromBuffer(pf) ) {
			return NULL;
		}
		return( pf );
	}

	LBSC_Field **ppField = (LBSC_Field **)bsearch( &uiFieldId, pcSortListById, lbscFieldList.NumElem(), sizeof( LBSC_Field* ), find_by_id );
	if ( ppField ) {
		pCurrField = *ppField;
		if ( !FillFieldFromBuffer(*ppField) ) {
			return NULL;
		}
		return *ppField;
	}

	return NULL;
}


int CompareRecordHeaderFunc( const void *Key1, const void *Key2 )
{
	return (((TRecordBufferHeader *)Key1)->lId - ((TRecordBufferHeader *)Key2)->lId);
}


/**
	Gera um registro a partir de um buffer com formato definido no metodo GetRecordBuffer (de LBSC_Base)
**/
BOOL 
LBSC_Record::SetRecordBuffer( C_Buffer &OrigBuf )
{
	BYTE bCompressed = FALSE;
	long lMaxBufSize = 0;
	long lBufSize = 0;

	BYTE *pUncompressedBuf = NULL;
	long lNewBufSize = 0;

	if ( !TryUncompressRecordBuffer( OrigBuf, &pUncompressedBuf, &lNewBufSize ) ) {
		return FALSE;
	}

	pRecordBuffer = new C_Buffer( (char *)pUncompressedBuf, lNewBufSize );
	delete( pUncompressedBuf );
	if ( !pRecordBuffer ) {
		return FALSE;
	}

	pRecordBuffer->Rewind();
	if ( !pRecordBuffer->GetData( (void *)&bCompressed, sizeof(BYTE) ) ) { // esta compactado? 
		return FALSE;
	}
	if ( !pRecordBuffer->GetData( (void *)&lMaxBufSize, sizeof(long) ) ) { // tam. maximo do buffer  
		return FALSE;
	}
	if ( !pRecordBuffer->GetData( (void *)&lBufSize, sizeof(long) ) ) { // tam. efetivo do buffer  
		return FALSE;
	}
	if ( !pRecordBuffer->GetData( (void *)&lNumFieldsRead, sizeof(long) ) ) { // num. de campos 
		return FALSE;
	}

	// header de campos
	pRecordFieldsHeader = new TRecordBufferHeader[lNumFieldsRead];
	if ( !pRecordFieldsHeader ) {
		return FALSE;
	}
	if ( !pRecordBuffer->GetData( (void *)pRecordFieldsHeader, (lNumFieldsRead * sizeof(TRecordBufferHeader)) ) ) {
		delete pRecordFieldsHeader;
		return FALSE;
	}

	// limpa os flags de leitura de todos os campos
	ClearReadStatusFromFields();
	return TRUE;
}


BOOL 
LBSC_Record::FillFieldFromBuffer( LBSC_Field *pField )
{
	if ( pField->bRead || !bMustLoadData ) {
		return TRUE;
	}

	if ( bIsUndefined ) {
		// vamos simular ele como vazio, mas talvez devesse sinalizar erro ....
		StartFillingField( pField, 0 );
		EndFillingField( pField );
		return TRUE;
	}

	if ( !plbscbBase ) {	
		// erro? como tratar?
		StartFillingField( pField, 0 );
		EndFillingField( pField );
		return TRUE;
	}

	if ( !pRecordFieldsHeader || !lNumFieldsRead || !pRecordBuffer ) {
		// vamos tentar carregar os dados
		if ( plbscbBase->ReadRecordData() != LBS_OK ) {
			// erro? como tratar?
			StartFillingField( pField, 0 );
			EndFillingField( pField );
			return TRUE;
		}

		if ( !pRecordFieldsHeader || !lNumFieldsRead || !pRecordBuffer ) {
			// registro vazio...
			StartFillingField( pField, 0 );
			EndFillingField( pField );
			return TRUE;
		}
	}

	TRecordBufferHeader	aux;
	aux.lId = pField->GetId();
	TRecordBufferHeader	*pFound = (TRecordBufferHeader	*)bsearch( (void *)&aux, pRecordFieldsHeader, lNumFieldsRead, sizeof(TRecordBufferHeader), CompareRecordHeaderFunc );
	if ( !pFound ) {
		// esse campo nao estava no registro.. vamos limpa-lo
		StartFillingField( pField, 0 );
		EndFillingField( pField );
		return TRUE;
	}

	if ( !pRecordBuffer->SetMyPos( pFound->lOffSet ) ) {
		return FALSE;
	}
	StartFillingField( pField, pFound->lNumRep );
	for ( int i=0; i<pFound->lNumRep; i++ ) {
		if ( !FillRepetitionFromBuffer(pField, i) ) {
			return FALSE;
		}
	}
	EndFillingField( pField );

	return TRUE;
}


/**
	Gera as repeticoes do campo a partir do buffer armazenado com formato definido no metodo GetRecordBuffer
	OBS: o campo pode nao mais existir na base, mas mesmo assim o buffer deve ser processado
**/
BOOL 
LBSC_Record::FillRepetitionFromBuffer(LBSC_Field *pField, int iRep )
{
	BYTE bIsNull = FALSE;	// eh nulo ?
	if ( !pRecordBuffer->GetData( (void *)&bIsNull, sizeof(BYTE) ) ) {
		return FALSE;
	}

	LBSC_Data *pd = NULL;

	if ( iRep >= pField->GetNumberOfRepetition() ) {	// forca a criacao de uma nova repeticao, se for o caso
		pd = (*pField)[iRep];
	} else {
		pField->IncNumberOfUpdates();
	}

	pd = pField->lbscdlDataList[ iRep ];
	if ( !pd ) {
		return FALSE;
	}

	pd->iUpdateSequenceNumber = iRep + 1;
	if ( bIsNull ) {
		pd->DisableData();
		pd->SetStatus( DATA_HOLE );
		pd->SetModified( FALSE );
		return TRUE;
	}

	long lRepSize = 0;
	switch( pField->GetType() ) {
	case ALPHA_FIELD:
	case TEXT_FIELD:
	case BINARY_FIELD:
	case REFERENCED_FIELD:
		if ( !pRecordBuffer->GetData( (void *)&lRepSize, sizeof(long) ) ) {	// le o tamanho do conteudo
			return FALSE;
		}
		if ( lRepSize == 0 ) {
			pd->DisableData();
			pd->SetStatus( DATA_HOLE );
			pd->SetModified( FALSE );
			return TRUE;
		}
		break;
	default:
		lRepSize = pd->GetSize();
		break;
	}

	if ( pd ) {
		pd->ModifyData( pRecordBuffer->MyBuffer() + pRecordBuffer->MyPos(), lRepSize );
		pd->SetStatus( DATA_OK );
		pd->SetModified( FALSE );
		if ( !pRecordBuffer->SetMyPos( pRecordBuffer->MyPos() + lRepSize ) ) {
			return FALSE;
		}
	}
	return TRUE;
}

BOOL LBSC_Record::TryUncompressRecordBuffer( C_Buffer &Buf, BYTE **pNewBuf, long *plNewBufSize )
{
	Buf.Rewind();
	BYTE bCompressed = TRUE;
	long lMaxBufSize = 0;
	long lCurBufSize = 0;

	if ( !Buf.GetData( &bCompressed, sizeof(BYTE) ) ) {
		return FALSE;
	}
	if ( !Buf.GetData( &lMaxBufSize, sizeof(long) ) ) {
		return FALSE;
	}
	if ( !Buf.GetData( &lCurBufSize, sizeof(long) ) ) {
		return FALSE;
	}
	Buf.Rewind();

	*pNewBuf = new BYTE[lMaxBufSize];
	if ( !bCompressed ) {
		*plNewBufSize = lMaxBufSize;
		memcpy( *pNewBuf, Buf.MyBuffer(), lMaxBufSize );
		return TRUE;
	}

	memcpy( *pNewBuf, Buf.MyBuffer(), RecordHeaderBufferSize() );
	// Descompacta usando a LZO	
	unsigned int NewBufferSize;

	// tem q pular as informacoes do header do buffer
	// Descompacta 
	if ( !LZO_DeCompress((BYTE *)(Buf.MyBuffer()) + RecordHeaderBufferSize(), lCurBufSize - RecordHeaderBufferSize(),
		*pNewBuf + RecordHeaderBufferSize(),&NewBufferSize ) ) {
		delete *pNewBuf;
		*pNewBuf = NULL;
		return FALSE;
    }
	*plNewBufSize = NewBufferSize + RecordHeaderBufferSize();
	return TRUE;
}


long LBSC_Record::RecordHeaderBufferSize()
{
	return (sizeof(BYTE) + sizeof(long) + sizeof(long));
}

void LBSC_Record::StartFillingField( LBSC_Field *pField, long lNumRep ) 
{
	pField->bMustFillOriginalDataList = FALSE;
	while ( pField->GetNumberOfRepetition() > lNumRep ) {
		pField->pDataList->Del();
	}
	pField->ClearNumberOfUpdates();
}

void LBSC_Record::EndFillingField( LBSC_Field *pField ) 
{
	if( pField->GetAttrib() & DESC_ORD_FIELD ){
		// inverter o iUpdateSequenceNumber para poder fazer o desempate correto na ordenacao de repeticoes
		int	iNumRep = pField->GetNumberOfRepetition();

		for( int i = 0; i < iNumRep; i++, iNumRep-- ){
			LBSC_Data	*pd1 = pField->pDataList->Nth( i );
			LBSC_Data	*pd2 = pField->pDataList->Nth( iNumRep-1 );

			if( pd1 && pd2 && (pd1 != pd2) ){
				int	iAux = pd1->iUpdateSequenceNumber;

				pd1->iUpdateSequenceNumber = pd2->iUpdateSequenceNumber;
				pd2->iUpdateSequenceNumber = iAux;
			}
		}
	}
	pField->UpdateFieldFlag( FALSE, pField->GetNumberOfRepetition() + 1 );
	pField->bMustFillOriginalDataList = TRUE;
	pField->lbscdlOriginalDataList.DelAll();
	pField->bRead = TRUE;
}

int LBSC_Record::GetNumberOfFieldsInGroup( LBSC_FieldGroup *pfGroup )
{
	if ( !pfGroup ) {
		return -1;
	}
	return pfGroup->lbscflFieldList.NumElem();
}

LBSC_Field *LBSC_Record::GetFieldInGroup( LBSC_FieldGroup *pfGroup, int iPos )
{
	if ( !pfGroup ) {
		return NULL;
	}
	LBSC_Field *pField = pfGroup->lbscflFieldList[iPos];
	if ( !pField ) {
		return NULL;
	}
	pCurrField = pField;
	if ( !FillFieldFromBuffer(pField) ) {
		return NULL;
	}
	return pField;
}


void LBSC_Record::ClearReadStatusFromFields()
{
	for( int i = 0; i < lbscFieldList.NumElem(); i++ ){
		LBSC_Field *pField = lbscFieldList[ i ];
		if ( pField ) {
			pField->bRead = FALSE;
		}
	}
};
