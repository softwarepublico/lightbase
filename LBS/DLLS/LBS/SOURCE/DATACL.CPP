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
// Module: DATACL.CPP
// Description:
//
//	Methods file for data handling.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 28/09/94
//

#if !defined _INCLUDES_H_
#include	<includes.h>
#endif
#if !defined(__MEM_H) && !defined _INC_MEMORY
#include	MEM_H
#endif
#ifndef	_DATACL_H_
#include	<datacl.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef	_FIELDCL_H_
#include	<fieldcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#include "LI_ConvTER.h"

extern	AppParmsMngr	*_pcInter;

#define	SETFIELDUPDATE	{																	\
							if( pfOwnerField ){												\
								/* nao sabemos qual a repeticao do campo foi alterada;	*/	\
								/* vamos so setar o campo como modificado forcando um update fora de faixa...	*/	\
								pfOwnerField->UpdateFieldFlag( TRUE, pfOwnerField->GetNumberOfRepetition() + 1 );	\
								/* ...mas sabemos que esta repeticao foi alterada... */		\
								bModified = TRUE;											\
								iUpdateSequenceNumber = pfOwnerField->GetNumberOfUpdates();	\
							}																\
						}

#define	FILLORIGINALDATALIST	{																	\
							if( pfOwnerField ){												\
								/* vamos forcar que se guarde as repticoes originais do campo	*/	\
								/* para poder desindear depois 	*/	\
								pfOwnerField->FillOriginalDataList();	\
							}																\
						}


/***
	PUBLIC
	Metodo IsOk
	Verifica se o objeto LBSC_Data foi criado com sucesso.

	Parameters:
		
	Return:
		- Retorna LBS_OK se obteve sucesso, outro valor caso contrario

	Comments:

***/
int
LBSC_Data::IsOk( void )
{
	return pbData != NULL;
}


/***
	PUBLIC
	Metodo LBSC_Data
	Construtor da classe LBSC_Data

	Parameters:
		- pfOwner
		- iType
		- pvNewData
		- lSize

	Return:

	Comments:

***/
LBSC_Data::LBSC_Data( LBSC_Field *pfOwner, int iType, void *pvNewData, long lSize ) 
{
	bModified = FALSE;
	iRepetNum = -1;
	iSlotSize = 0;
	pfOwnerField = pfOwner;
	iDataType = iType;
	iStatus = DATA_OK;
	pbData = NULL;
	switch( iDataType ){
	case VALUE_FIELD:
		lDataSize = sizeof( long );
		break;
	case DVALUE_FIELD:
		lDataSize = sizeof( double );
		break;
	case DATE_FIELD:
		lDataSize = sizeof( JulTy );
		break;
	case TIME_FIELD:
		lDataSize = sizeof( ClockTy );
		break;
	case TEXT_FIELD:
		lDataSize = lSize;
		break;
	case ALPHA_FIELD:
		lDataSize = lSize + 1;
		break;
	case BINARY_FIELD:
		// sizeof( buffer ) + sizeof( iFormat ) + sizeof( iLen )
		lDataSize = pvNewData ? (((LBSC_Binary*)pvNewData)->iLen +
					sizeof( int ) + sizeof( int )) : 0;
		break;
	case REFERENCED_FIELD:
		// sizeof( buffer ) + 1 + sizeof( iFormat ) + 
		// sizeof( szFileName )
		lDataSize = pvNewData ? (strlen( ((LBSC_Reference*)pvNewData)->szBuffer ) + 1 +
					sizeof( int ) + MAXPATH) : 0;
		break;
	case BYTE_FIELD:
		lDataSize = sizeof( BYTE );
		break;
	case SINT_FIELD:
		lDataSize = sizeof( short int );
		break;
	case FLOAT_FIELD:
		lDataSize = sizeof( float );
		break;
	}
	if( (lDataSize > 0) && pvNewData ){
		pbData = new char [ lDataSize ];
		if( pbData ){
			memset( pbData, 0, lDataSize );
			if( pvNewData ){
				if( iDataType == ALPHA_FIELD ){
					strncpy( (char*) pbData, (char*) pvNewData, (lDataSize - 1) );
					if( strlen( (char*) pvNewData ) < (size_t) (lDataSize - 1) ){
						((char*) pbData)[ strlen( (char*) pvNewData ) ] = '\0';
					} else {
						((char*) pbData)[ lDataSize - 1 ] = '\0';
					}
				} else {
					memcpy( pbData, pvNewData, lDataSize );
				}
			}
		}
	} else {
		pbData = NULL;
	}
	SETFIELDUPDATE;
}


/***
	PUBLIC
	Metodo ~LBSC_Data
	Destrutor da classe LBSC_Data

	Parameters:

	Return:

	Comments:

***/
LBSC_Data::~LBSC_Data()
{
	if( pbData ){
		delete (char*) pbData;
	}
}

/***
	PUBLIC
	Metodo SetModifyFlag
	Altera o flag de modificacao do dado

	Parameters: bUpdatePar -> TRUE ou FALSE

	Return: TRUE ou FALSE

	Comments:

***/
void
LBSC_Data::SetModified( BOOL bModif )
{
	bModified = bModif;
}

/***
	PUBLIC
	Metodo IsModified
	Retorna o flag de modificacao do dado

	Parameters: 

	Return: TRUE ou FALSE

	Comments:

***/
BOOL
LBSC_Data::IsModified()
{
	return bModified;
}

/***
	PUBLIC
	Metodo GetData
	Obtem o dado

	Parameters:

	Return:
		O apontador para o dado.

	Comments:
		- Este metodo aloca um buffer e faz uma copia do
		  conteudo requerido. A aplicacao que chamar este
		  metodo eh responsavel pela delecao do buffer.

***/
void*
LBSC_Data::GetData()
{
	if( !pbData ){
		return( NULL );
	}
	char	*szAux = new char[ lDataSize ];

	if( szAux ){
		memcpy( (void*) szAux, (const void*) pbData, lDataSize );
	}
	return( (void*) szAux );
}


/***
	PRIVATE
	Metodo GetConstData
	Obtem o dado

	Parameters:

	Return:
		O apontador para o dado. Disponivel apenas para consulta.

	Comments:
		- Este metodo nao faz copia do conteudo. Ele retorna
		  um ponteiro para o buffer interno.

***/
const void*
LBSC_Data::GetConstData()
{
	return( (const void*) pbData );
}


/***
	PUBLIC
	Metodo GetSize
	Obtem o tamanho do dado

	Parameters:

	Return:
		O tamanho do dado. Disponivel apenas para consulta.

	Comments:

***/
long
LBSC_Data::GetSize()
{
	return( (iDataType == ALPHA_FIELD) ? lDataSize - 1 : lDataSize );
}

/***
	PUBLIC
	Metodo GetType
	Obtem o tipo do dado

	Parameters:

	Return:
		O tipo do dado. Disponivel apenas para consulta.

	Comments:

***/
int
LBSC_Data::GetType()
{
	return( iDataType );
}

/***
	PUBLIC
	Metodo ModifyData
	Modifica o objeto LBSC_Data

	Parameters:
		- pbNewData
		- lNewSize

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Data::ModifyData( void *pbNewData, long lNewSize )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	if( !pbNewData ){
		// deletar o dado existente
		if( pbData ){
			delete (char*) pbData;
			pbData = NULL;
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;

		return( LBS_OK );
	}

	switch( iDataType ){
	case ALPHA_FIELD:
		if( !pbData && (lDataSize > 0) ){
			pbData = new char [ lDataSize ];
		}
		break;

	case BINARY_FIELD:
		if( pbData ){
			delete (char*) pbData;
		}
		{
			LBSC_Binary* pcbNewBin = (LBSC_Binary*) pbNewData;
			lDataSize = pcbNewBin->iLen + 2 *sizeof( int );
			pbData = new char [ lDataSize ];
		}
		break;

	case REFERENCED_FIELD:
		if( pbData ){
			delete (char*) pbData;
		}
		{
			LBSC_Reference* pcbNewRef = (LBSC_Reference*) pbNewData;
			lDataSize = strlen( pcbNewRef->szBuffer ) + 1 + sizeof( int ) + MAXPATH;
			pbData = new char [ lDataSize ];
		}
		break;

	case TEXT_FIELD:
		if( (lNewSize != lDataSize) || !pbData ){
			if( pbData ){
				delete (char*) pbData;
			}
			pbData = new char [ lNewSize ];
			lDataSize = lNewSize;
		}
		break;

	default:
		if( !pbData ){
			// o dado esta' desabilitado
			pbData = new char [ this->lDataSize ];
		}
		break;

	}
	if( pbData ){
		if( iDataType == ALPHA_FIELD ){
			strncpy( (char*) pbData, (char*) pbNewData, lDataSize );
			if( strlen( (char*) pbNewData ) < (size_t) (this->lDataSize - 1) ){
				((char*) pbData)[ strlen( (char*) pbNewData ) ] = '\0';
			} else {
				((char*) pbData)[ this->lDataSize - 1 ] = '\0';
			}
		} else {
			memcpy( pbData, pbNewData, lDataSize );
		}
	}

	// ligar o flag de atualizacao no campo dono
	SETFIELDUPDATE;

	return( LBS_OK );
}


/***
	PUBLIC
	Metodo Compare
	Compara o objeto LBSC_Data fornecido com o corrente

	Parameters:
		- plbscData
		- iCompType

	Return:
		O resultado do "memcmp".

	Comments:

***/
#ifdef __BORLANDC__
#pragma warn -par
#endif
int
LBSC_Data::Compare( LBSC_Data *plbscData, int iCompType )
{
	if( !plbscData || (iDataType != plbscData->iDataType) ){
		return( -1 );
	}
	switch( iCompType ){
	case CMPDATASORT:
	case CMPDATA:
		if( pbData && plbscData->pbData ){
			// comparacao determinada pelo conteudo...
			return( (iDataType == ALPHA_FIELD) ?
				memcmp( this->pbData, plbscData->pbData, lDataSize - 1 ) :
				memcmp( this->pbData, plbscData->pbData, lDataSize ) );
		}
		if( !pbData && !plbscData->pbData ){
			// iguais...
			return 0;
		}
		if( pbData && !plbscData->pbData ){
			// o this eh maior...
			return 1;
		}
		// o this eh menor...
		return -1;

	case CMPDATASIZE:
		return( (lDataSize > plbscData->lDataSize) ? 1 : ((lDataSize < plbscData->lDataSize) ? -1 : 0) );

	case CMPREPETNUM:
		return( (iRepetNum > plbscData->iRepetNum) ? 1 : ((iRepetNum < plbscData->iRepetNum) ? -1 : 0) );

	}
	return( 1 );
}
#ifdef __BORLANDC__
#pragma warn +par
#endif

/***
	PUBLIC
	Metodo Duplicate
	Duplica o objeto LBSC_Data corrente

	Parameters:

	Return:
		NULL.

	Comments:

***/
LBSC_Data *
LBSC_Data::Duplicate()
{
	LBSC_Data *pNewData = new LBSC_Data( pfOwnerField, iDataType, pbData, lDataSize );
	if ( !pNewData ) {
		return NULL;
	}

	(*pNewData) = (*this);
	return( pNewData );
}


/***
	PUBLIC
	Metodo Write
	Escreve o dado armazenado em um arquivo

	Parameters:
		- pcFile 

	Return:
		- LBS_OK em caso de sucesso ou erro

	Comments:

***/
int
LBSC_Data::Write( C_File *pcFile )
{
	if( pbData ){
		return pcFile->Write( pbData, lDataSize );
	}
	return LBSE_ERROR;
}

/***
	PUBLIC
	Metodo Read
	Le o dado de um arquivo

	Parameters:
		- pcFile 

	Return:
		- LBS_OK em caso de sucesso ou erro

	Comments:

***/
int
LBSC_Data::Read( C_File *pcFile )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	if( pbData ){
		return pcFile->Read( pbData, lDataSize );
	}
	// ligar o flag de atualizacao no campo dono
	SETFIELDUPDATE;

	return LBSE_ERROR;
}

/***
	PRIVATE
	Operador =
	Associa um numero inteiro long ao valor interno do objeto

	Parameters:
		- lValor -> valor do long a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( long lValor )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == VALUE_FIELD ){
			if( lDataSize == sizeof( long ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((long*)pbData) = lValor;
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador =
	Associa um numero double ao valor interno do objeto

	Parameters:
		- dValor -> valor double a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( double dValor )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == DVALUE_FIELD ){
			if( lDataSize == sizeof( double ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((double*)pbData) = dValor;
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador =
	Associa uma string ao valor interno do objeto

	Parameters:
		- szBuffer -> string a ser associada ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( char *szBuffer )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == ALPHA_FIELD ){
			if( strlen( szBuffer ) + 1 > (size_t) lDataSize ){
				if( pbData ){
					delete (char*) pbData;
				}
				pbData = new char [ strlen( szBuffer ) + 1 ];
			} else {
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
			}
			if( pbData ){
				strncpy( (char*) pbData, szBuffer, lDataSize );
				if( strlen( szBuffer ) < (size_t) (this->lDataSize - 1) ){
					((char*) pbData)[ strlen( szBuffer ) ] = '\0';
				} else {
					((char*) pbData)[ this->lDataSize - 1 ] = '\0';
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador =
	Associa um buffer void ao valor interno do objeto

	Parameters:
		- pvBuffer -> buffer a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( void *pvBuffer )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( !pbData ){
			// o dado esta' desabilitado
			pbData = new char [ this->lDataSize ];
		}
		if( pbData ){
			if( iDataType == TEXT_FIELD ){
				memcpy( pbData, pvBuffer, lDataSize );

			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador =
	Associa uma data ao valor interno do objeto

	Parameters:
		- cdDate -> data a ser associada ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( C_Date &cdDate )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == DATE_FIELD ){
			if( lDataSize == sizeof( JulTy ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((JulTy*)pbData) = cdDate.Hash();
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador =
	Associa um objeto LBSC_Time ao valor interno do objeto

	Parameters:
		- ctTime -> objeto a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( C_Time &ctTime )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == TIME_FIELD ){
			if( lDataSize == sizeof( ClockTy ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((ClockTy*)pbData) = ctTime.Seconds();
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}

/***
	PRIVATE
	Operador =
	Associa um LBSC_Binary ao valor interno do objeto

	Parameters:
		- cbBinary

	Return:

	Comments:



***/
void
LBSC_Data::operator = ( LBSC_Binary & cbBinary )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == BINARY_FIELD ){
			if( pbData ){
				delete (char*) pbData;
			}
			lDataSize = cbBinary.iLen + sizeof( int )
						+ sizeof( int );
			pbData = new char [ lDataSize ];
			if( pbData ){
				memcpy( pbData, &cbBinary, lDataSize );
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}

/***
	PRIVATE
	Operador =
	Associa um LBSC_Reference ao valor interno do objeto

	Parameters:
		- crReference

	Return:

	Comments:



***/
void
LBSC_Data::operator = ( LBSC_Reference & crReference )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == REFERENCED_FIELD ){
			if( pbData ){
				delete (char*) pbData;
			}
			lDataSize = strlen( crReference.szBuffer ) + 1
						+ sizeof( int ) + MAXPATH;
			pbData = new char [ lDataSize ];
			if( pbData ){
				memcpy( pbData, &crReference, lDataSize );
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}

/***
	PRIVATE
	Operador =
	Atribui ao valor interno do objeto um outro objeto do tipo LBSC_Data
	
	Parameters:
		- b : outro objeto do tipo LBSC_Data

	Return:
		- o endereco do this

	Comments:



***/
LBSC_Data&
LBSC_Data::operator = ( LBSC_Data &b )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	if( pbData ){
		iRepetNum = b.iRepetNum;
		iStatus = b.iStatus;
		if( iDataType == b.iDataType ){
			if( lDataSize != b.lDataSize ){
				if( pbData ){
					delete (char*) pbData;
				}
				lDataSize = b.lDataSize;
				pbData = (lDataSize > 0) ? new char [ lDataSize ] : NULL;
			}
			if( pbData && b.pbData ){
				memcpy( pbData, b.pbData, b.lDataSize );
			}
		}
	}
	if ( iStatus != DATA_OK || !b.pbData ) {
		DisableData();
	}
	// ligar o flag de atualizacao no campo dono
	SETFIELDUPDATE;
	iUpdateSequenceNumber = b.iUpdateSequenceNumber;
	return( *this );
}


/***
	PRIVATE
	Operador =
	Associa um numero BYTE ao valor interno do objeto

	Parameters:
		- bValue -> valor BYTE a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void			
LBSC_Data::operator = ( BYTE bValue )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == BYTE_FIELD ){
			if( lDataSize == sizeof( BYTE ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((BYTE*)pbData) = bValue;
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}

/***
	PRIVATE
	Operador =
	Associa um numero short int ao valor interno do objeto

	Parameters:
		- siValue -> valor short int a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( short int siValue )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == SINT_FIELD ){
			if( lDataSize == sizeof( short int ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((short int*)pbData) = siValue;
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}

/***
	PRIVATE
	Operador =
	Associa um numero float ao valor interno do objeto

	Parameters:
		- fValor -> valor float a ser associado ao valor interno

	Return:
		-

	Comments:

***/
void
LBSC_Data::operator = ( float fValue )
{
	// armazenar as repeticoes originais no campo dono
	FILLORIGINALDATALIST

	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_WRITE ) || IsPermOk( ACL_APPEND ) ){
		if( iDataType == FLOAT_FIELD ){
			if( lDataSize == sizeof( float ) ){
				if( !pbData ){
					// o dado esta' desabilitado
					pbData = new char [ this->lDataSize ];
				}
				if( pbData ){
					*((float*)pbData) = fValue;
				}
			}
		}
		// ligar o flag de atualizacao no campo dono
		SETFIELDUPDATE;
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
}


/***
	PRIVATE
	Operador long
	Realiza uma operacao de cast de um objeto data para long
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator long ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == VALUE_FIELD ){
				return *((long*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return 0;
}

/***
	PRIVATE
	Operador double
	Realiza uma operacao de cast de um objeto data para double
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator double ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == DVALUE_FIELD ){
				return *((double*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return 0.0;
}

/***
	PRIVATE
	Operador char*
	Realiza uma operacao de cast de um objeto data para char*
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator char* ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == ALPHA_FIELD || iDataType == TEXT_FIELD ){
				return (char*) pbData;
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return "";
}

/***
	PRIVATE
	Operador void*
	Realiza uma operacao de cast de um objeto data para void*
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator void* ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			return (void*) pbData;
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return( (void*) NULL );
}

/***
	PRIVATE
	Operador LBSC_Binary*
	Realiza uma operacao de cast de um objeto data para LBSC_Binary*
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator LBSC_Binary* ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			return (LBSC_Binary*)pbData;
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return (LBSC_Binary*) NULL;
}

/***
	PRIVATE
	Operador LBSC_Reference*
	Realiza uma operacao de cast de um objeto data para LBSC_Reference*
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator LBSC_Reference* ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			return (LBSC_Reference*)pbData;
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return (LBSC_Reference*) NULL;
}

/***
	PRIVATE
	Operador JulTy
	Realiza uma operacao de cast de um objeto data para JulTy
	
	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator JulTy ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == DATE_FIELD || iDataType == TIME_FIELD ){
				return *((JulTy*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return (JulTy)0;
}

/***
	PRIVATE
	Operador ClockTy
	Realiza uma operacao de cast de um objeto data para ClockTy
	$$$	Este operador nao pode ser definido porque ClockTy eh definido
	$$$	exatamente como JulTy e entao o compilador acusa redeclaracao
	$$$	de operador.
	
	Parameters:

	Return:

	Comments:



***
LBSC_Data::operator ClockTy ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( iDataType == TIME_FIELD ){
			return *((ClockTy*)pbData);
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return (ClockTy)0;
}
***/


/***
	PRIVATE
	Operador BYTE
	Realiza uma operacao de cast de um objeto data para BYTE
	
	Parameters:

	Return:

	Comments:

***/
LBSC_Data::operator BYTE ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == BYTE_FIELD ){
				return *((BYTE*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return 0;
}

/***
	PRIVATE
	Operador short int
	Realiza uma operacao de cast de um objeto data para short int
	
	Parameters:

	Return:

	Comments:

***/
LBSC_Data::operator short int ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == SINT_FIELD ){
				return *((short int*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );		
	}
	return 0;
}

/***
	PRIVATE
	Operador float
	Realiza uma operacao de cast de um objeto data para float

	Parameters:

	Return:

	Comments:



***/
LBSC_Data::operator float ( void )
{
	// o usuario possui permissao para usar este operador?
	if( IsPermOk( ACL_READ ) ){
		if( pbData ){
			if( iDataType == FLOAT_FIELD ){
				return *((float*)pbData);
			}
		} else {
			SetError( LBSE_INVALIDDATA );
		}
	} else {
		SetError( LBSE_NOPERMISSION );
	}
	return (float) 0.0;
}


/***
	PRIVATE
	Metodo IsPermOk
	Verifica se o campo dono deste objeto possui
	a permissao bPerm

	Parameters:
		- bPerm

	Return:
		- BOOL

	Comments:



***/
BOOL
LBSC_Data::IsPermOk( BYTE bPerm )
{
	return(	pfOwnerField ? pfOwnerField->IsPermOk( bPerm ) : TRUE );
}


/***
	PRIVATE
	Metodo SetError
	Seta um erro no field dono deste objeto

	Parameters:	
		- iErr

	Return:

	Comments:

	
***/
void
LBSC_Data::SetError( int iErr )
{
	if( pfOwnerField ){
		pfOwnerField->SetError( iErr );
	}
}



/***
	PRIVATE
	Metodo DisableData
	Desabilita (invalida) o dado.

	Parameters:

	Return:

	Comments:



***/
void
LBSC_Data::DisableData()
{
	if( pbData ){
		delete (char*) pbData;
	}
	pbData = NULL;
}


/***
	PRIVATE
	Metodo IsEnabled
	Verifica se o dado esta' habilitado (valido)

	Parameters:

	Return:
		- BOOL

	Comments:



***/
BOOL
LBSC_Data::IsEnabled()
{
	return( pbData ? TRUE : FALSE );
}

/***
	PUBLIC
	Metodo GetOwnerField
	Retorna o ponteiro para o objeto LBSC_Field que
	eh dono deste LBSC_Data

  	Parameters:

	Return:
		- apontador para LBSC_Field

	Comments:


***/
LBSC_Field *
LBSC_Data::GetOwnerField()
{
	return( pfOwnerField );
}



/**********************************************************
// Function name	: LBSC_Data::SetStatus
// Description	    : 
// Return type		: void 
// Argument         : DATASTATUS iNewStatus
**********************************************************/
void LBSC_Data::SetStatus( DATASTATUS iNewStatus )
{
	iStatus = iNewStatus;
}


/**********************************************************
// Function name	: LBSC_Data::GetStatus
// Description	    : 
// Return type		: DATASTATUS 
**********************************************************/
DATASTATUS LBSC_Data::GetStatus()
{
	return( iStatus );
}

/**********************************************************
// Function name	: LBSC_Data::GetUpdateSequenceNumber
// Description	    : 
// Return type		: 
**********************************************************/
int	LBSC_Data::GetUpdateSequenceNumber()
{
	return( iUpdateSequenceNumber );
}


/**********************************************************
// Function name	: LBSC_Data::ToString
// Description	    : 
// Return type		: 
**********************************************************/
char *LBSC_Data::ToString()
{
	char *szFieldContent = NULL;
	if ( !pbData ) {
		return NULL;
	}
	long lSize = lDataSize;	
	szFieldContent = new char [lSize+1];
	if ( !szFieldContent ) {
		return NULL;
	}
	switch( iDataType ){
	case VALUE_FIELD:
		sprintf( szFieldContent, "%d", (long) (*this) );
		break;
	case DVALUE_FIELD:
		sprintf( szFieldContent, "%f", (double) (*this) );
		break;
	case TEXT_FIELD:
		{
			strncpy( szFieldContent, (char*) (*this), lSize );
			szFieldContent[lSize] = '\0';
			LI_ConvTER licterConvert;
			strcpy( szFieldContent, licterConvert.TerToTxt( szFieldContent, ( long )strlen( szFieldContent ), '\n' ));
		}
		break;
	case ALPHA_FIELD:
		strncpy( szFieldContent, (char*) (*this), lSize );
		break;
	case DATE_FIELD:
		{
			C_Date	cd = JULIANDATE( (JulTy) (*this) );
			char	*szDateMask = NULL;

			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				PRODLANGPARMS *pLangSectVars = _pcInter->GetProdLangParms();

				if( pLangSectVars ){
					szDateMask = pLangSectVars->datemask;
				}
			}

			cd.Get( szFieldContent, szDateMask ? szDateMask : "dd/mm/yyyy" );
		}
		break;
	case TIME_FIELD:
		{
			C_Time	ct = SECONDTIME( (JulTy) (*this) );
			char	*szTimeMask = NULL;

			if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
				PRODLANGPARMS *pLangSectVars = _pcInter->GetProdLangParms();

				if( pLangSectVars ){
					szTimeMask = pLangSectVars->timemask;
				}
			}

			ct.Get( szFieldContent, szTimeMask ? szTimeMask : "hh:mm:ss" );
		}
		break;
	case REFERENCED_FIELD:
		{
			LBSC_Reference	*pr = (LBSC_Reference*) (*this);

			strncpy( szFieldContent, pr ? pr->szFileName : "", lSize );
		}
		break;
	case BYTE_FIELD:
		sprintf( szFieldContent, "%d", (BYTE) (*this) );
		break;
	case SINT_FIELD:
		sprintf( szFieldContent, "%d", (short int) (*this) );
		break;
	case FLOAT_FIELD:
		sprintf( szFieldContent, "%f", (float) (*this) );
		break;
	default:
		delete szFieldContent;
		szFieldContent = NULL;
	}

	return szFieldContent;
}

void LBSC_Data::TryConvertToTer()
{
	if ( pbData && lDataSize > 0 && iDataType == TEXT_FIELD ) {
		char *szFieldContent = new char [lDataSize+1];
		if ( szFieldContent ) {
			strncpy( szFieldContent, (char *)pbData, lDataSize );
			szFieldContent[lDataSize] = '\0';

			if ( !strstr( szFieldContent, TER_FORMAT ) ){
				// precisamos converter de texto para um formato que o ter entenda
				LI_ConvTER		licterConvert;
				const char *szAux = licterConvert.TxtToTer( (char *)szFieldContent );
				if ( szAux ) {
					memset( pbData, 0, lDataSize );
					memcpy( pbData, (void *)szAux, strlen(szAux) );
				} else {
					delete pbData;
					pbData = NULL;
				}
			}
			delete szFieldContent;
		}
	}
}

