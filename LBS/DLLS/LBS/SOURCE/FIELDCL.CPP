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
// Module: FIELDCL.CPP
// Description:
//
//	Methods file for fields handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 06/09/94
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#if !defined(__VALUES_H) && !defined _INC_LIMITS
#include	VALUES_H
#endif
#include	<lt.h>		// GREEN
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef	_DEFMACRO_H_		// usado quando compilando no MSVC20
#include	<defmacro.h>
#endif
#ifndef	_REPSORT_H_
#include	<repsort.h>
#endif


/***
	PUBLIC
	Metodo LBSC_Field
	Construtor da classe LBSC_Field

	Parameters:
		- szAliasName
		- szFieldDescription
		- szPassword
		- tftFieldType
		- lFieldSize
		- uiFieldId
		- uiFieldAttrib
		- tiaIndexAttrib
		- pOwnerBase

	Return:

	Comments:

***/				
LBSC_Field::LBSC_Field( char *szAliasName, char *szFieldDescription, char *szPassword,
			TFieldType tftFieldType, long lFieldSize, UINT uiFieldId, UINT uiFieldAttrib,
			TIndexAttrib tiaIndexAttrib, LBSC_Base *pOwnerBase ) : 
	lbscpPassword( szPassword ),
	lbscdlDataList(),
	lbscdlOriginalDataList()
{
	Init();
	this->szAliasName = szAliasName;
	this->szFieldOrigName = szAliasName;
	this->szFieldDescription = szFieldDescription;
	this->tftFieldType = tftFieldType;
	this->lFieldSize = lFieldSize;
	this->uiFieldId = uiFieldId;
	this->uiFieldAttrib = uiFieldAttrib;
	this->tiaIndexAttrib = (tiaIndexAttrib & ~(REFERENCETREE));
	iGroup = 0;	// valor invalido para grupos
	pltcgwGoWords = new LTC_TERMLIST;
	plbscbBase = pOwnerBase;
	bMustFillOriginalDataList = FALSE;
	bRead = FALSE;
}


/***
	PUBLIC
	Metodo ~LBSC_Field
	Destrutor do objeto LBSC_Field

	Parameters:

	Return:

	Comments:

***/				
LBSC_Field::~LBSC_Field()
{
	if( pltcgwGoWords ){
		delete pltcgwGoWords;
	}
	if ( pvSlot ) {
		delete pvSlot;
	}
}



/***
	PRIVATE
	Metodo Init
	Inicializa o objeto

	Parameters:
		-
	Return:
		-
	Comments:
		-

***/
void
LBSC_Field::Init()
{
	bFlagUpdate = FALSE;
	bFlagStructUpdated = FALSE;
	tiaIndexAttrib = 0;
	uiFieldId = 0;
	lFieldSize = 0L;
	pDataList = &lbscdlDataList;
	iNumberOfUpdates = 0;
	lSlotSize = 0;
	pvSlot = NULL;
}

void
LBSC_Field::SetSlot( long lSize, void *pvNewSlot )
{
	lSlotSize = lSize;
	if ( pvSlot ) {
		delete pvSlot;
	}
	pvSlot = pvNewSlot;
}

/***
	PRIVATE
	Metodo ModifyAliasName
	Modifica o alias name do campo

	Parameters:
		- szNewAliasName

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Field::ModifyAliasName( char *szNewAliasName )
{
	if( szNewAliasName == NULL ){
		return( LBSE_BADARG );
	}
	szAliasName = szNewAliasName;
	bFlagStructUpdated = TRUE;
	return( LBS_OK );
}

/***
	PRIVATE
	Metodo ModifySize
	Modifica o tamanho do campo

	Parameters:
		- lNewSize

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Field::ModifySize( long lNewSize )
{
	lFieldSize = lNewSize;
	bFlagStructUpdated = TRUE;
	return( LBS_OK );
}

/***
	PRIVATE
	Metodo ModifyDescription
	Modifica a descricao do campo

	Parameters:
		- szDescription

	Return:
		- LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Field::ModifyDescription( char *szDescription )
{
	if( szDescription == NULL ){
		return( LBSE_BADARG );
	}
	szFieldDescription = szDescription;
	bFlagStructUpdated = TRUE;
	return( LBS_OK );
}




/***
	PRIVATE
	Metodo ModifyPassword
	Modifica a password

	Parameters:
		- szNewPassword

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Field::ModifyPassword( char *szNewPassword )
{
	if( lbscpPassword.Modify( szNewPassword ) == LBS_OK ){
		return( LBS_OK );
	}
	bFlagStructUpdated = TRUE;
	return( LBSE_ERROR );
}


/***
	PUBLIC
	Metodo VerifyPassword
	Verifica a password

	Parameters:
		- szPassword

	Return:
		O resultado da comparacao.

	Comments:

***/
int
LBSC_Field::VerifyPassword( char *szPassword )
{
	return( lbscpPassword.Verify( szPassword ) );
}



/***
	PUBLIC
	Metodo Clear
	Limpa um objeto LBSC_Field

	Parameters:

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Field::Clear()
{
	FillOriginalDataList();
	if( pDataList->DelAll() != OK ){
		return( LBSE_FIELDNOTCLEANED );
	}

	UpdateFieldFlag( TRUE );
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo GetNumberOfRepetition
	Obtem o numero de repeticoes de um campo

	Parameters:

	Return:
		O numero de repeticoes.

	Comments:

***/
int
LBSC_Field::GetNumberOfRepetition()
{
	return( pDataList->NumElem() );
}


/***
	PUBLIC
	Metodo GetRepetitionByIndex
	Obtem uma repeticao atraves do seu indice

	Parameters:
		- iIndex

	Return:
		O conteudo da repeticao.

	Comments:
		- Este metodo retorna uma copia do buffer interno e
		  a aplicacao deve liberar o espaco alocado para a copia.

***/
void *
LBSC_Field::GetRepetitionByIndex( int iIndex )
{
	if( iIndex > -1 ){
		if( pDataList->Nth( iIndex ) == NULL ){
			return( NULL );
		}
	}
	LBSC_Data	*pData = pDataList->Current();
	return( pData ? pData->GetData() : NULL );
}


/***
	PRIVATE
	Metodo GetConstRepByIndex
	Obtem uma repeticao atraves do seu indice (a repeticao obtida nao
	eh uma copia do dado interno)

	Parameters:
		- iIndex

	Return:
		- O conteudo da repeticao (nao copia).

	Comments:
		- A aplicacao NAO deve deletar o ponteiro retornado
		  por este metodo.

***/
const void *
LBSC_Field::GetConstRepByIndex( int iIndex )
{
	if( iIndex > -1 ){
		if( pDataList->Nth( iIndex ) == NULL ){
			return( NULL );
		}
	}
	LBSC_Data	*pData = pDataList->Current();
	return( pData ? pData->GetConstData() : NULL );
}


/***
	PUBLIC
	Metodo GetRepetitionByVal (time)
	Obtem o indice de uma repeticao atraves do seu conteudo

	Parameters:
		- pvData
		- bStart
		- lSize 

	Return:
		- O indice.

	Comments:

***/
int
LBSC_Field::GetRepetitionByVal( void *pvData, BOOL bStart, long lSize )
{
	switch( tftFieldType ){
	case TEXT_FIELD:
	case ALPHA_FIELD:
		{
			LBSC_Data 	lbscdAux( this, tftFieldType, pvData,
					tftFieldType == TEXT_FIELD ? lSize :
					lFieldSize );
			if( pDataList->Find( &lbscdAux, CMPDATA, bStart ) == NULL ){
				return( LBSE_REPETITIONNOTFOUND );
			}
		}
		break;
	default:
		{
			LBSC_Data 	lbscdAux( this, tftFieldType, pvData );
			if( pDataList->Find( &lbscdAux, CMPDATA, bStart ) == NULL ){
				return( LBSE_REPETITIONNOTFOUND );
			}
		}
		break;
	}
	return( pDataList->GetCurrentIndex() );
}



/***
	PUBLIC
	Metodo AddRepetition
	Adiciona uma repeticao a lista de repticoes de um campo

	Parameters:
		- pbVal
		- lSize
		
	Return:
		LBS_OK se conseguir adicionar ou erro.

	Comments:

***/
int
LBSC_Field::AddRepetition( void *pbVal, long lSize )
{
	LBSC_Data	*plbscdAux;

	if( pDataList->NumElem() >= MAXINT ){
		return( LBSE_REPOVERFLOW );
	}

	IncNumberOfUpdates();

	if( tftFieldType == ALPHA_FIELD ){
		plbscdAux = new LBSC_Data( this, tftFieldType, pbVal, lFieldSize );
	} else {
		plbscdAux = new LBSC_Data( this, tftFieldType, pbVal, lSize );
	}
	if( plbscdAux == NULL ){
		return( LBSE_NOMEMORY );
	}
	if( !plbscdAux->IsOk() ){
		delete plbscdAux;
		return( LBSE_NOMEMORY );
	}
	FillOriginalDataList();
	if( pDataList->Add( plbscdAux, TAIL ) != LBS_OK ){
		delete plbscdAux;
		return( LBSE_NOMEMORY );
	}
	UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo ModifyRepetitionByIndex
	Modifica uma repeticao pelo indice

	Parameters:
		- iIndex
		- pbNewVal
		- lSize

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Field::ModifyRepetitionByIndex( int iIndex, void *pbNewVal, long lSize )
{
	if( pDataList->Nth( iIndex ) == NULL ){
		return( LBSE_POSITIONERROR );
	}
	UpdateFieldFlag( TRUE, iIndex );
	return( pDataList->Current()->ModifyData( pbNewVal, lSize ) );
}



/***
	PUBLIC
	Metodo DeleteRepetitionByIndex
	Deleta uma repeticao pelo indice

	Parameters:
		- iIndex
		- bCopyTo	-> indica se a repeticao deletada deve ser
						copiada para a lista de repeticoes deletadas.
						Isso eh util para poder desindexar a repeticao
						que esta' sendo deletada. Se a copia nao for
						feita, a desindexacao nao sera' possivel.
						Valor default = TRUE.
		- bShift -> indica se as repeticoes restantes devem ser deslocadas
				    uma posicao para ocupar o buraco deixado pela delecao.
					O default eh nao fazer o shift (FALSE).

	Return:
		LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_Field::DeleteRepetitionByIndex( int iIndex, BOOL bCopyTo, BOOL bShift )
{
	LBSC_Data	*d = iIndex == -1 ? lbscdlDataList.Current() : lbscdlDataList.Nth( iIndex );

	if( !d ){
		return( LBSE_POSITIONERROR );
	}

	FillOriginalDataList();

	// invalida a repeticao
	d->DisableData();
	d->SetModified( TRUE );

	if( bShift ){
		// fazer shift das repeticoes seguintes aa iIndex
		int iNumElem = lbscdlDataList.NumElem();
		for( int i = iIndex; i < (iNumElem-1); i++ ){
			LBSC_Data	*pd2 = lbscdlDataList.Nth( i+1 );

			if( pd2 ){
				pd2->SetModified( TRUE );
				lbscdlDataList.Nth( i );
				LBSC_Data	*pd1 = lbscdlDataList.Refresh( pd2 );

				if( pd1 && i == iIndex ) {
					// destruir o elemento que foi deletado
					// (o elemento pd1 eh um LBSC_Data sem informacao)
					delete pd1;
				}
			}
		}
		lbscdlDataList.Last();
		if ( iIndex < (iNumElem-1) ) {
			// se o elemento a ser removido nao for o ultimo, ele ainda eh valido
			// pois foi feito o shift acima
			// entao temos que evitar que seja deletado pela lista
			lbscdlDataList.Refresh( NULL );
		}
		lbscdlDataList.Del();
	}
	bFlagUpdate = TRUE;
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo CreateLink
	Cria um link entre dois campos

	Parameters:
		- szBaseName
		- szAliasName
		- bThisLinkType
		- bPropagate

	Return:
		LBS_OK se conseguir criar o link ou erro.

	Comments:

***/
int
LBSC_Field::CreateLink( char * /*szBaseName*/, char * /*szAliasName*/,
			BYTE /*bThisLinkType*/, BOOL /*bPropagate*/ )
{
	//$$$ FALTA FAZER ESTE METODO
	return( LBS_OK );
}


/***
	PUBLIC
	Metodo DeleteLink
	Desfaz um link entre dois campos

	Parameters:
		- szBaseName
		- szBaseField

	Return:
		LBS_OK se conseguir desfazer o link ou erro.

	Comments:

***/
int
LBSC_Field::DeleteLink( char * /*szBaseName*/, char * /*szBaseField*/ )
{
	//$$$ FALTA FAZER ESTE METODO
	return( LBS_OK );
};


/***
	PUBLIC
	Metodo Duplicate
	Duplica o campo corrente

	Parameters:

	Return:
		Apontador para o novo objeto LBSC_Field

	Comments:

***/
LBSC_Field *
LBSC_Field::Duplicate()
{
	LBSC_Field	*plbscfFieldAux;

	if( ( plbscfFieldAux = new LBSC_Field( szAliasName, szFieldDescription, (char *) lbscpPassword.GetConstPassword(), //*lbscpPassword.GetType(),
		tftFieldType, lFieldSize, uiFieldId, uiFieldAttrib, tiaIndexAttrib ) ) == NULL ){
		return( NULL );
	}
	plbscfFieldAux->bFlagUpdate = this->bFlagUpdate;
	plbscfFieldAux->bFlagStructUpdated = this->bFlagStructUpdated;
	plbscfFieldAux->tiaIndexAttrib = this->tiaIndexAttrib;
	if( pltcgwGoWords ){
		plbscfFieldAux->pltcgwGoWords->LT_Duplicate( pltcgwGoWords );
	}
	plbscfFieldAux->uiFieldId = this->uiFieldId;
	plbscfFieldAux->uiFieldAttrib = uiFieldAttrib;
	plbscfFieldAux->iNumberOfUpdates = iNumberOfUpdates;
	plbscfFieldAux->bMustFillOriginalDataList = bMustFillOriginalDataList;
	plbscfFieldAux->lSlotSize = lSlotSize;
	plbscfFieldAux->iGroup = iGroup;
	plbscfFieldAux->iError = iError;
	plbscfFieldAux->bRead = bRead;
	if ( plbscfFieldAux->pvSlot ) {
		delete plbscfFieldAux->pvSlot;
		plbscfFieldAux->pvSlot = NULL;
	}
	if ( pvSlot && lSlotSize > 0 ) {
		plbscfFieldAux->pvSlot = new char[lSlotSize];
		if ( plbscfFieldAux->pvSlot ) {
			memcpy( plbscfFieldAux->pvSlot, pvSlot, lSlotSize );
		}
	}

	return( plbscfFieldAux );
}


/***
	PUBLIC
	Metodo Compare
	Compara um objeto LBSC_Field com o campo corrente

	Parameters:
		- plbscfField
		- iSearchType

	Return:
		O resultado da comparacao.

	Comments:

***/
int
LBSC_Field::Compare( LBSC_Field *plbscfField, int iSearchType )
{
	char	*szThisPsw, *szFieldPsw;

	switch( iSearchType ){
	case CMPFIELDNAME:
		{
			CL_StringN<FIELDNAMESIZE>	szMe;
			CL_StringN<FIELDNAMESIZE>	szOther;
			szMe = this->szAliasName;
			szMe.Upper();
			szOther = plbscfField->szAliasName;
			szOther.Upper();
			return( szMe == ((const char *)szOther) ? 0 : 1 );
		}
	case CMPFIELDORIGNAME:
		return( (this->szFieldOrigName == ((const char *)plbscfField->szFieldOrigName)) ? 0 : 1 );
	case CMPFIELDDESCRIPTION:
		return( (this->szFieldDescription == ((const char *)plbscfField->szFieldDescription)) ? 0 : 1 );
	case CMPFIELDID:
		return( this->uiFieldId == plbscfField->uiFieldId ? 0 : 1 );
	case CMPFIELDSTRUCT:
		if( this->szFieldOrigName != ((const char *)plbscfField->szFieldOrigName) ){
			return( LBSE_ERROR );
		}
		if( this->szAliasName != ((const char *)plbscfField->szAliasName) ){
			return( LBSE_ERROR );
		}
		if( this->szFieldDescription != ((const char *)szFieldDescription) ){
			return( LBSE_ERROR );
		}
		if( ( szThisPsw = (char *) this->lbscpPassword.GetConstPassword() ) == NULL ){
			return( LBSE_ERROR );
		}
		if( ( szFieldPsw = (char *) plbscfField->lbscpPassword.GetConstPassword() ) == NULL ){
			return( LBSE_ERROR );
		}
		if( strcmp( szThisPsw, szFieldPsw ) != 0 ){
			return( LBSE_ERROR );
		}
		if( this->tftFieldType != plbscfField->tftFieldType ){
			return( LBSE_ERROR );
		}
		if( this->uiFieldAttrib != plbscfField->uiFieldAttrib ){
			return( LBSE_ERROR );
		}
		if( this->lFieldSize != plbscfField->lFieldSize ){
			return( LBSE_ERROR );
		}
		return( 0 );
	default:
		return( 0 );
	}
}


/***
	PUBLIC
	Metodo GetType
	Obtem o tipo do campo

	Parameters:

	Return:
		- O tipo do campo

	Comments:


***/
TFieldType
LBSC_Field::GetType()
{
	return( tftFieldType );
}


/***
	PUBLIC
	Metodo GetAliasName
	Obtem o nome do campo

	Parameters:

	Return:
		- O nome do campo

	Comments:
		- Este metodo retorna o buffer interno, que
		  a aplicacao NAO deve deletar.


***/
const char *
LBSC_Field::GetAliasName()
{
	return( (const char*) (char*) szAliasName );
}


/***
	PUBLIC
	Metodo GetDescription
	Obtem a descricao do campo

	Parameters:

	Return:
		- A descricao do campo

	Comments:
		- Este metodo retorna o buffer interno, que
		  a aplicacao NAO deve deletar.


***/
const char *
LBSC_Field::GetDescription()
{
	return( (const char*) (char*) szFieldDescription );
}



/***
	PUBLIC
	Metodo GetSize
	Obtem o tamanho do campo

	Parameters:

	Return:
		- O tamanho do campo

	Comments:


***/
long
LBSC_Field::GetSize()
{
	return( lFieldSize );
}



/***
	PRIVATE
	Metodo GetPassword
	Obtem a password do campo

	Parameters:

	Return:
		- A password. Disponivel apenas para consulta.

	Comments:
		- Este metodo NAO retorna uma copia do buffer interno.

***/
const char *
LBSC_Field::GetPassword()
{
	return( lbscpPassword.GetConstPassword() );
}

/***
	PRIVATE
	Metodo SetId
	Seta o numero de identificacao do campo

	Parameters:
		- uiNewId	-> novo identificador

	Return:
		-

	Comments:
		-

***/
void
LBSC_Field::SetId( UINT uiNewId )
{
	uiFieldId = uiNewId;
}

/***
	PRIVATE
	Metodo IsError
	Obtem o status de erro atual
	
	Parameters:
		-
	
	Return:
		- o ultimo erro ocorrido em algum metodo desta classe

	Comments:
		- poucos metodos estao usando este sistema de erro.
		  Nao eh recomendavel utilizar este metodo para obter
		  erros (ainda).

***/
int
LBSC_Field::IsError()
{
	return( iError );
}


/***
	PUBLIC
	Metodo GetId
	Obtem o numero de identificacao do campo

	Parameters:

	Return:
		- O numero de identificacao do campo

	Comments:
		-

***/
UINT
LBSC_Field::GetId()
{
	return( uiFieldId );
}

/***
	PUBLIC
	Operador []
	Obtem o n-esimo dado da lista de dados do campo

	Parameters:
		- iPos	-> posicao da lista
	
	Return:
		- um objeto LBSC_Data
	
	Comments:
		-

***/
LBSC_Data *
LBSC_Field::operator []( int iPos )
{
	long 			l = 0l;
	double 			d = 0.0;
	char 			c = 0;
	JulTy 			jt = 0;
	ClockTy 		ct = 0;
	LBSC_Reference	*plbscRef;
	LBSC_Binary		*plbscBin;
	BYTE			b = 0;
	short int		si = 0;
	float			f = (float) 0.0;

	if( iPos == -1 ){
		if( pDataList->NumElem() == 0 ) {
			return(	NULL );
		}
		return( pDataList->Current() );
	}

	if( !((*pDataList)[ iPos ]) ){
		int i = pDataList->NumElem();
		for( ; i <= iPos; i++ ){
			switch( tftFieldType ){
			case VALUE_FIELD:
				AddRepetition( &l );
				break;
			case DVALUE_FIELD:
				AddRepetition( &d );
				break;
			case TEXT_FIELD:
				AddRepetition( (void*) &c, sizeof( char ) );
				break;
			case ALPHA_FIELD:
				AddRepetition( &c );
				break;
			case DATE_FIELD:
				AddRepetition( &jt );
				break;
			case TIME_FIELD:
				AddRepetition( &ct );
				break;
			case BINARY_FIELD:
				plbscBin = LBSC_Binary::Alloc( 0 );
				if( plbscBin ){
					plbscBin->iFormat = 0;
					AddRepetition( plbscBin );
					LBSC_Binary::Free( plbscBin );
				}
				break;
			case REFERENCED_FIELD:
				plbscRef = LBSC_Reference::Alloc( 0 );
				if( plbscRef ){
					plbscRef->iFormat = 0;
					plbscRef->szFileName [ 0 ] = '\0';
					AddRepetition( plbscRef );
					LBSC_Reference::Free( plbscRef );
				}
				break;
			case BYTE_FIELD:
				AddRepetition( &b );
				break;
			case SINT_FIELD:
				AddRepetition( &si );
				break;
			case FLOAT_FIELD:
				AddRepetition( &f );
				break;
			}
			if( i < iPos ){
				((*pDataList)[ i ])->DisableData();
			}
		}
		pDataList->Last();
	}
	if( !pDataList->Current() || !(pDataList->Current()->IsEnabled()) ){
		return NULL;
	}
	if( pDataList->GetCurrentIndex() != iPos ){
		return NULL;
	}
	return( pDataList->Current() );
}

/***
	PUBLIC
	SetIndexAttrib
	Modifica o atributo de indexacao do campo

	Parameters:
		- iAttrib -> Novo valor para o atributo

	Return:
		- Status

	Comments:

***/
int
LBSC_Field::SetIndexAttrib( int iAttrib )
{
	tiaIndexAttrib = iAttrib;
	return( LBS_OK );
}

/***
	PUBLIC
	GetIndexAttrib
	Obtem o atributo de indexacao do campo

	Parameters:

	Return:
		- tiaIndexAttrib
	
	Comments:

***/
TIndexAttrib
LBSC_Field::GetIndexAttrib()
{
	return( tiaIndexAttrib );
}

/***
	PUBLIC
	Operador =
	Faz uma copia do objeto (a = b, onde a eh this)

	Parameters:
		- b	-> objeto de origem
	
	Return:
		- um objeto LBSC_Field
	
	Comments:
		- o retorno deste metodo poderia ser void, mas da
		  forma como estah implementado eh possivel fazer
		  expressoes do tipo a = b = c ...

***/
LBSC_Field&
LBSC_Field::operator = ( LBSC_Field& b )
{
	if( Compare( &b, CMPFIELDSTRUCT ) == 0 ){
		Clear();
		strcpy( this->szFieldOrigName, b.szFieldOrigName );
		strcpy( this->szAliasName, b.szAliasName );
		strcpy( this->szFieldDescription, b.szFieldDescription );
		this->uiFieldId = b.uiFieldId;
		this->lbscpPassword.Modify( ( char * )b.lbscpPassword.GetConstPassword() );
		this->tftFieldType = b.tftFieldType;
		this->lFieldSize = b.lFieldSize;
		this->bFlagUpdate = b.bFlagUpdate;
		this->bFlagStructUpdated = b.bFlagStructUpdated;
		this->tiaIndexAttrib = b.tiaIndexAttrib;
		this->iError = b.iError;
		this->plbscbBase = b.plbscbBase;
		this->uiFieldAttrib = b.uiFieldAttrib;
		this->iGroup = b.iGroup;
		this->bRead = b.bRead;
		this->iNumberOfUpdates = b.iNumberOfUpdates;
		if( b.pltcgwGoWords ){
			this->pltcgwGoWords->LT_Duplicate( b.pltcgwGoWords );
		}

		LBSC_DataList	*pDataListAux = b.pDataList;

		b.pDataList = &b.lbscdlDataList;
		int	iNumElem = b.pDataList->NumElem();
		for( int i = 0; i < iNumElem; i++ ){
			LBSC_Data	*pd1 = (*this)[ i ];
			LBSC_Data	*pd2 = (*b.pDataList)[ i ];

			if( pd1 ) {
				if ( pd2 ){
					(*pd1) = (*pd2);
				} else {
					delete pd1;
					pDataList->Refresh( NULL );
				}
			}
		}

		b.pDataList = &b.lbscdlOriginalDataList;		
		pDataList = &lbscdlOriginalDataList;		
		iNumElem = b.pDataList->NumElem();
		for( i = 0; i < iNumElem; i++ ){
			LBSC_Data	*pd1 = (*this)[ i ];
			LBSC_Data	*pd2 = (*b.pDataList)[ i ];

			if( pd1 ) {
				if ( pd2 ){
					(*pd1) = (*pd2);
				} else {
					delete pd1;
					pDataList->Refresh( NULL );
				}
			}
		}
		b.pDataList = pDataListAux;
		SetDataListTo( b.WhatDataList() );
		bMustFillOriginalDataList = b.bMustFillOriginalDataList;
		lSlotSize = b.lSlotSize;
		if ( pvSlot ) {
			delete pvSlot;
			pvSlot = NULL;
		}
		if ( b.pvSlot && lSlotSize > 0 ) {
			pvSlot = new char[lSlotSize];
			if ( pvSlot ) {
				memcpy( pvSlot, b.pvSlot, lSlotSize );
			}
		}
	}

	bFlagUpdate = TRUE;

	return *this;
}

/***
	PUBLIC
	Operador ==
	Faz a comparacao entre este objeto e outro (a == b, onde a eh this)

	Parameters:
		- b
	
	Return:
		- Retorna 1 caso a == b; 0 caso a != b
	
	Comments:
		-

***/
int
LBSC_Field::operator == ( LBSC_Field& b )
{
	return( Compare( &b, CMPFIELDSTRUCT ) == 0 ? 1 : 0 );
}



/***
	PUBLIC
    Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- l

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
                 da forma como estah implementado eh possivel
                 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( long l )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = l;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- d

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( double d )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = d;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- szNewRepetition

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( char * szNewRepetition )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = szNewRepetition;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}


/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- pvNewRepetition

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( void *pvNewRepetition )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = pvNewRepetition;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}


/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- cdDate

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( C_Date &cdDate )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = cdDate;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- ctTime

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( C_Time &ctTime )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = ctTime;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- cbBinary

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( LBSC_Binary &cbBinary )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = cbBinary;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- crReference

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( LBSC_Reference &crReference )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = crReference;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}

/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- b 

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( BYTE b )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = b;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}


/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- si

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( short int si )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = si;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}


/***
	PUBLIC
	Operador <<
	Adiciona uma repeticao a um campo.

	Parameters:
		- f

	Return:
		- um objeto LBSC_Field

	Comments:
		-o retorno deste metodo poderia ser void, mas
		 da forma como estah implementado eh possivel
		 fazer expressoes do tipo a << b << c ...

***/
LBSC_Field *
LBSC_Field::operator << ( float f )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ pDataList->NumElem() ];
	
	if( pd ){
		(*pd) = f;
		UpdateFieldFlag( TRUE, pDataList->NumElem()-1 );
		return( this );
	}
	return( NULL );
}


/***
	PUBLIC
    Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- l : valor a ser atribuido

	Return:
		- void

	Comments:

***/
void
LBSC_Field::operator = ( long l )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = l;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
    Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- d : valor a ser atribuido

	Return:

	Comments:

***/
void
LBSC_Field::operator = ( double d )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = d;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- szData : valor a ser atribuido

	Return:

	Comments:
		
***/
void
LBSC_Field::operator = ( char * szData )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = szData;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- pvData : valor a ser atribuido

	Return:
	
	Comments:
		
***/
void
LBSC_Field::operator = ( void * pvData )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = pvData;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- cdDate : valor a ser atribuido

	Return:
	
	Comments:
		
***/
void
LBSC_Field::operator = ( C_Date & cdDate )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = cdDate;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
    Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- ctTime : valor a ser atribuido

	Return:

	Comments:
		
***/
void
LBSC_Field::operator = ( C_Time & ctTime )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = ctTime;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- cbBinary : valor a ser atribuido
		
	Return:

	Comments:
	
***/
void
LBSC_Field::operator = ( LBSC_Binary & cbBinary )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = cbBinary;
		UpdateFieldFlag( TRUE, 0 );
	}
}

/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- crReference : valor a ser atribuido

	Return:

	Comments:
	
***/
void
LBSC_Field::operator = ( LBSC_Reference & crReference )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = crReference;
		UpdateFieldFlag( TRUE, 0 );
	}
}


/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- b : valor a ser atribuido

	Return:
		
	Comments:
		
***/
void
LBSC_Field::operator = ( BYTE b )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = b;
		UpdateFieldFlag( TRUE, 0 );
	}
}


/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- si : valor a ser atribuido

	Return:

	Comments:
	
***/
void
LBSC_Field::operator = ( short int si )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = si;
		UpdateFieldFlag( TRUE, 0 );
	}
}


/***
	PUBLIC
	Operador =
	Atribui um valor a primeira repetição de um campo.

	Parameters:
		- f : valor a ser atribuido

	Return:

	Comments:
	
***/
void
LBSC_Field::operator = ( float f )
{
	IncNumberOfUpdates();

	LBSC_Data	*pd = (*this)[ 0 ];
	if( pd ){
		(*pd) = f;
		UpdateFieldFlag( TRUE, 0 );
	}
}


/***
	PRIVATE
	Metodo AddGoWord
	Adiciona uma GoWord na lista de GoWords daquele campo

	Parameters:
		- szGoWord: obvio.

	Return:
		- 0 se conseguir realizar a operacao ou negativo caso contrario.

	Comments:
        
***/
int
LBSC_Field::AddGoWord( char *szGoWord )
{
	int	iRet;

	if( pltcgwGoWords ){
		iRet = pltcgwGoWords->LT_AddTerm( szGoWord );
		return( iRet );
	}
	return( LBSE_ERROR );
}

/***
	PRIVATE
	Metodo DelGoWord
	Deleta uma GoWord na lista de GoWords daquele campo

	Parameters:
		- szGoWord: obvio.

	Return:
		- 0 se conseguir realizar a operacao ou negativo caso contrario.

	Comments:
    
***/
int
LBSC_Field::DelGoWord( char *szGoWord )
{
	int	iRet;

	if( pltcgwGoWords ){
		iRet = pltcgwGoWords->LT_DelTerm( szGoWord );
		return( iRet );
	}
	return( LBSE_ERROR );
}

/***
	PUBLIC
	Metodo GetFirstGoWord
	Obtem a primeira GoWotd da lista de GoWords daquele campo

	Parameters:

	Return:
		- obvio ou NULL.

	Comments:

***/
char *
LBSC_Field::GetFirstGoWord()
{
	return( pltcgwGoWords ? (char *)pltcgwGoWords->LT_GetFirstTerm() : NULL );
}

/***
	PUBLIC
	Metodo GetNextGoWord
	Obtem a proxima GoWord da lista de GoWords daquele campo

	Parameters:

	Return:
		- obvio ou NULL

	Comments:

***/
char *
LBSC_Field::GetNextGoWord()
{
	return( pltcgwGoWords ? (char *)pltcgwGoWords->LT_GetNextTerm() : NULL );
}

/***
	PUBLIC
	Metodo GetCurrentGoWord
	Obtem a GoWord corrente da lista de GoWords daquele campo

	Parameters:

	Return:
		- obvio ou NULL

	Comments:

***/
char *
LBSC_Field::GetCurrentGoWord()
{
	return( pltcgwGoWords ? (char *)pltcgwGoWords->LT_GetCurrentTerm() : NULL );
}

/***
	PUBLIC
	Metodo GetNthGoWord
	Obtem a n-esima GoWotd da lista de GoWords daquele campo

	Parameters:
		- iPos : a posicao na listya de GoWords

	Return:
		- obvio ou NULL

	Comments:


***/
char *
LBSC_Field::GetNthGoWord( int iPos )
{
	return( pltcgwGoWords ? (char *)pltcgwGoWords->LT_NthTerm( ( TUFOURBYTES ) iPos ) : NULL );
}

/***
	PUBLIC
	Metodo SearchGoWord
	Obtem uma GoWord da lista de GoWords daquele campo

	Parameters:
		- szGoWord

	Return:
		- ele mesmo ou NULL

	Comments:


***/
char *
LBSC_Field::SearchGoWord( char *szGoWord )
{
	return( pltcgwGoWords ? (char *)pltcgwGoWords->LT_SearchTerm( ( CHARTYPE * ) szGoWord ) : NULL );
}

/***
	PUBLIC
	Metodo GetNbrOfGoWord
	Obtem o numero de GoWords da lista de GoWords daquele campo

	Parameters:

	Return:
		- obvio

	Comments:


***/
long
LBSC_Field::GetNbrOfGoWord()
{
	return( pltcgwGoWords ? pltcgwGoWords->LT_GetNbrOfTerm() : LBSE_ERROR );
}


/***
	PRIVATE
	Metodo IsPermOk
	Verifica se o campo possui a permissao bPerm

	Parameters:
		- bPerm

	Return:
		- obvio

	Comments:


***/
BOOL
LBSC_Field::IsPermOk( BYTE bPerm )
{
	if( !plbscbBase ){
		return( TRUE );
	}
	int iRet = plbscbBase->VerifyPermission( plbscbBase->plbscsOwnerSession->GetUserName(),
						 this->uiFieldId, USERFIELD, bPerm );
	return(	iRet == LBS_OK ? TRUE : FALSE );
}




/***
	PRIVATE
	Metodo SetError
	Seta um erro na base dona deste objeto

	Parameters:
		- iErr

	Return:
		

	Comments:


***/
void
LBSC_Field::SetError( int iErr )
{
	if( plbscbBase ){
		plbscbBase->SetError( iErr );
	}
}


/***
	PUBLIC
	Metodo GetOwnerBase
	Retorna o apontador para o objeto LBSC_Base que eh
	dono deste field

	Parameters:

	Return:
		- A base.

	Comments:

***/
LBSC_Base *
LBSC_Field::GetOwnerBase()
{
	return( plbscbBase );
}


/***
	PRIVATE
	Metodo SetDataListTo
	Altera a lista de elementos LBSC_Data.

	Parameters:
		- iDataList ->	indica qual a lista deve ser usada. As
						opcoes sao: VALID_DATALIST e ORIGINAL_DATALIST

	Return:
		- 

	Comments:

***/
void
LBSC_Field::SetDataListTo( int iDataList )
{
	switch( iDataList ){
	case ORIGINAL_DATALIST:
		pDataList = &lbscdlOriginalDataList;
		break;
	default:
		pDataList = &lbscdlDataList;
		break;
	}
}



/***
	PRIVATE
	Metodo WhatDataList
	Indica qual a lista de dados esta' setada.

	Parameters:
		- 

	Return:
		- A lista corrente. Os possiveis valores sao:
		  VALID_DATALIST e ORIGINAL_DATALIST

	Comments:

***/
int
LBSC_Field::WhatDataList()
{
	if( pDataList == &lbscdlOriginalDataList ){
		return( ORIGINAL_DATALIST );
	}
	return( VALID_DATALIST );
}


/**********************************************************
// Function name	: LBSC_Field::GetAttrib
// Description	    : 
// Return type		: UINT 
**********************************************************/
UINT LBSC_Field::GetAttrib()
{
	return( uiFieldAttrib );
}


/**********************************************************
// Function name	: LBSC_Field::SetAttrib
// Description	    : 
// Return type		: void 
// Argument         : UINT uiFieldAttribPar
**********************************************************/
void LBSC_Field::SetAttrib( UINT uiFieldAttribPar )
{
	uiFieldAttrib = uiFieldAttribPar;
}


/**********************************************************
// Function name	: LBSC_Field::PutRepetition
// Description	    : 
// Return type		: int -> erro (negativo) ou LBS_OK
// Argument         :  void *pbVal
// Argument         : int iIndex
// Argument         : long lSize
**********************************************************/
int LBSC_Field::PutRepetition( void *pbVal, int iIndex, long lSize )
{
	if( pDataList->NumElem() >= MAXINT ){
		return( LBSE_REPOVERFLOW );
	}

	FillOriginalDataList();
	IncNumberOfUpdates();

	if( iIndex == TAIL_REPETITION ){
		LBSC_Data	*plbscdAux;

		// vamos precisar alocar uma repeticao
		if( tftFieldType == ALPHA_FIELD ){
			plbscdAux = new LBSC_Data( this, tftFieldType, pbVal, lFieldSize );
		} else {
			plbscdAux = new LBSC_Data( this, tftFieldType, pbVal, lSize );
		}
		if( plbscdAux == NULL ){
			return( LBSE_NOMEMORY );
		}
		if( !plbscdAux->IsOk() ){
			delete plbscdAux;
			return( LBSE_NOMEMORY );
		}
		// adicionar a repeticao no final
		if( pDataList->Add( plbscdAux, TAIL ) != LBS_OK ){
			delete plbscdAux;
			return( LBSE_NOMEMORY );
		}

	} else {
		int iMaxRep = GetNumberOfRepetition();
		if ( iIndex >= iMaxRep ) {	// nova repeticao
			for ( int i=iMaxRep; i<iIndex; i++ ) {
				// forcar a criacao da repeticao e deixa-la vazia

				LBSC_Data	*pd = (*this)[i];
				// desabilita, para nao deixar informacao
				// que a aplicacao nao setou.
				if( pd ){
					pd->DisableData();
					// setar como DATA_HOLE para possibilitar o tratamento
					// correto das permissoes nos PutFieldRepetition...
					pd->SetStatus( DATA_HOLE );
				} else {
					return( LBSE_ERROR );
				}
			}
			if ( AddRepetition( pbVal, lSize ) != LBS_OK ) {
				return( LBSE_ERROR );
			}
		} else {
			LBSC_Data *pd = (*pDataList)[ iIndex ];
			if( !pd ){
				return( LBSE_ERROR );
			}
			if( pd->ModifyData( pbVal, lSize ) != LBS_OK ){
				return( LBSE_ERROR );
			}
			pd->SetStatus( DATA_OK );
		}
	}

	// vamos criar repeticoes vazias (caso nao existam) no mesmo 
	// iIndex de todos os campos que estiverem no mesmo grupo que este.
	plbscbBase->PutGroupRepetition( this, iIndex );
	UpdateFieldFlag( TRUE, (iIndex==TAIL_REPETITION) ? pDataList->NumElem()-1 : iIndex );
	return( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Field::GetGroup
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Field::GetGroup()
{
	return( iGroup );
}



/**********************************************************
// Function name	: LBSC_Field::SortRepetition
// Description	    : 
// Return type		: int 
// Argument         :  SortRepType stSortType
// Argument         : LBSC_Field *pfMasterField
**********************************************************/
int LBSC_Field::SortRepetition( SortRepType stSortType, LBSC_Field *pfMasterField )
{
	BOOL	bRep = FALSE;
	int		iNumRep = plbscbBase->GetNumberOfGroupRepetition( iGroup );
	FillOriginalDataList();

	if( iNumRep > 0 ){
		switch( stSortType ){
		case MASTER_FIELD_SORT:
			{
				// enumerar as repeticoes e disparar uma ordenacao
				for( int i = 0; i < iNumRep; i++ ){
					LBSC_Data	*pd = lbscdlDataList[i];

					if( pd ){
						pd->iRepetNum = i;
					} else {
						// forcar a criacao da repeticao e deixa-la vazia
						pd = (*this)[i];
						// desabilita, para nao deixar informacao
						// que a aplicacao nao setou.
						if( pd ){
							pd->DisableData();
							// setar como DATA_HOLE para possibilitar o tratamento
							// correto das permissoes nos PutFieldRepetition...
							pd->SetStatus( DATA_HOLE );
							pd->iRepetNum = i;
						} else {
							return( LBSE_ERROR );
						}
					}
				}
				LBSC_RepSort	rsRepSort( this );

				bRep = rsRepSort.StartSort();
			}
			break;

		case GROUP_FIELD_SORT:
			{
				// disparar uma ordenacao de campos nao ordenados do
				// grupo.
				bRep = TRUE;

				// criar uma lista temporaria
				LBSC_DataList	cdlAuxDataList;

				// transferir os dados da lista original para a temporaria
				for( int i = 0; i < iNumRep; i++ ){
					LBSC_Data	*pd = lbscdlDataList[i];

					if( pd ){
						cdlAuxDataList.Add( pd, TAIL );
					} else {
						// forcar a criacao da repeticao e deixa-la vazia
						pd = (*this)[i];
						// desabilita, para nao deixar informacao
						// que a aplicacao nao setou.
						if( pd ){
							pd->DisableData();
							// setar como DATA_HOLE para possibilitar o tratamento
							// correto das permissoes nos PutFieldRepetition...
							pd->SetStatus( DATA_HOLE );
							cdlAuxDataList.Add( pd, TAIL );
						} else {
							return( LBSE_ERROR );
						}
					}
				}

				// transferir os dados de volta para a lista original, 
				// observando a ordem do iRepetNum do pfMasterField
				for( i = 0; i < iNumRep; i++ ){
					LBSC_Data 	lbscdAux( pfMasterField, pfMasterField->GetType() );

					lbscdAux.iRepetNum = i;

					LBSC_Data	*pdAux = pfMasterField->lbscdlDataList.Find( &lbscdAux, CMPREPETNUM, TRUE );

					if( pdAux ){
						LBSC_Data	*pd = cdlAuxDataList[ i ];

						lbscdlDataList[ pfMasterField->lbscdlDataList.GetCurrentIndex() ];
						lbscdlDataList.Refresh( pd );
						cdlAuxDataList.Refresh( NULL );
					} 
				}

				for( i = 0; i < iNumRep; i++ ){
					LBSC_Data	*pd = cdlAuxDataList[ i ];
					cdlAuxDataList.Refresh( NULL );
				}
			}
			break;
		}
		UpdateFieldFlag( TRUE );
	}
	return( bRep ? LBS_OK : LBSE_ERROR );
}



/**********************************************************
// Function name	: LBSC_Field::IsTheSameRepetition
// Description	    : 
// Return type		: BOOL 
// Argument         :  void *pvRepetition
// Argument         : int iIndex
// Argument         : long lSizePar
**********************************************************/
BOOL LBSC_Field::IsTheSameRepetition( void *pvRepetition, int iIndex, long lSizePar )
{
	LBSC_Data *pd = (*pDataList)[ iIndex ];

	if ( !pvRepetition && !pd ) {
		return TRUE;
	}

	if ( !pvRepetition || !pd || !pd->pbData || pd->GetStatus() == DATA_HOLE ) {
		return FALSE;
	}

	switch( tftFieldType ){
	case VALUE_FIELD:
		return( *((long*) pvRepetition) == (long) (*pd) );

	case DVALUE_FIELD:
		return( *((double*) pvRepetition) == (double) (*pd) );

	case TEXT_FIELD:
		{
			if ( pd->GetSize() != lSizePar ) {
				return FALSE;
			}
			return (memcmp( pvRepetition, (void*)(*pd), pd->GetSize() ) == 0);
		}

	case ALPHA_FIELD:
		return( strcmp( (char*) pvRepetition, (char*) (*pd) ) == 0 );

	case DATE_FIELD:
		return( *((JulTy*) pvRepetition) == (JulTy) (*pd) );

	case TIME_FIELD:
		return( *((JulTy*) pvRepetition) == (JulTy) (*pd) );

	case BINARY_FIELD:
		{
			LBSC_Binary	*pb1 = (LBSC_Binary*) pvRepetition;
			LBSC_Binary	*pb2 = (LBSC_Binary*) (*pd);

			if ( !pb2 || pb1->iLen != pb2->iLen ) {
				return FALSE;
			}

			return( memcmp( pb1, pb2, pb1->iLen + 2 * sizeof( int ) ) == 0 );
		}

	case REFERENCED_FIELD:
		{
			LBSC_Reference	*pr1 = (LBSC_Reference*) pvRepetition;
			LBSC_Reference	*pr2 = (LBSC_Reference*) (*pd);

			if ( !pr2 ) {
				return FALSE;
			}

			if ( stricmp( pr1->szFileName, pr2->szFileName ) != 0 ) {
				return FALSE;
			}
			return (stricmp( pr1->szBuffer, pr2->szBuffer ) == 0);
		}

	case BYTE_FIELD:
		return( *((BYTE*) pvRepetition) == (BYTE) (*pd) );

	case SINT_FIELD:
		return( *((short*) pvRepetition) == (short) (*pd) );

	case FLOAT_FIELD:
		return( *((float*) pvRepetition) == (float) (*pd) );

	}

	return( FALSE );
}



/**********************************************************
// Function name	: LBSC_Field::UpdateFieldFlag
// Description	    : 
// Return type		: void 
// Argument         : BOOL bFlagUpdatePar
**********************************************************/
void LBSC_Field::UpdateFieldFlag( BOOL bFlagUpdatePar, long lIndex )
{
	bFlagUpdate = bFlagUpdatePar;
	if ( lIndex == -1 ) {	// setar como modificadas tambem todas as repeticoes do campo
		int	iNumRep = GetNumberOfRepetition();

		for ( int i=0; i<iNumRep; i++ ) {
			LBSC_Data *pd = (*pDataList)[ i ];
			if ( pd ) {
				pd->SetModified( bFlagUpdate );
			}
		}
	} else {
		// setar como modificada apenas a repeticao especificada
		LBSC_Data *pd = (*pDataList)[ lIndex ];
		if ( pd ) {
			pd->SetModified( bFlagUpdate );
		}
	}
}


/**********************************************************
// Function name	: LBSC_Field::GetNumberOfUpdates
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Field::GetNumberOfUpdates()
{
	return( iNumberOfUpdates );
}


/**********************************************************
// Function name	: LBSC_Field::ClearNumberOfUpdates
// Description	    : 
// Return type		: void 
**********************************************************/
void LBSC_Field::ClearNumberOfUpdates()
{
	iNumberOfUpdates = 0;
}

/**********************************************************
// Function name	: LBSC_Field::IncNumberOfUpdates
// Description	    : 
// Return type		: void 
**********************************************************/
void LBSC_Field::IncNumberOfUpdates()
{
	++iNumberOfUpdates;
}


/**********************************************************
// Function name	: LBSC_Field::FillOriginalDataList
// Description	    : peenche a lista de repeticoes origiais (para poder desindexar mais tarde)
// Return type		: void 
**********************************************************/
void LBSC_Field::FillOriginalDataList()
{
	if ( bMustFillOriginalDataList && (WhatDataList() == VALID_DATALIST) ) {
		bMustFillOriginalDataList = FALSE;
		lbscdlOriginalDataList = lbscdlDataList;
	}
}

