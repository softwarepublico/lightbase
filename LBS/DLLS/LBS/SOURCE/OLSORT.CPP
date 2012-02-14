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
// Module: OLSORT.CPP
// Description:
//
//	LBSC_OLSort private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 26/03/96
//

#ifndef __BORLANDC__
#pragma warning(disable:4355)
#endif

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include	<baseinstance.h>

#ifndef	_OLSORT_H_
#include	<olsort.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif
extern "C" {
#include	<personcl.h>
}

#define	LASTCHAR( x )		(x[ (strlen( x ) - 1) ])


EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	Funcao para deletar dados alocados pelo GetData.
	Sempre retorna FALSE.
***/
BOOL
ClearData( char **szPtData, int iDataIndex )
{
	if( szPtData ){
		for( int j = 0; j < iDataIndex; j++ ){
			if( szPtData[ j ] ){
				delete szPtData[ j ];
			}
		}
		delete szPtData;
	}
	return( FALSE );
}


/***
	Informacoes para composicao do descritor de chaves para ordenacao:
	- para LO NAO fisica:
		- %l	-> apontador para o objeto de comparacao (Comparator)
				(util para a CompareFunction)
				(nao ordenado)
		- %l	-> posicao do registro na lista original para a repeticao, 
				(util para o PutData)
			   (nao ordenado)
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)
		- ...
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)
		- %l>	-> numero do registro da ocorrencia. usado para diferenciar
			   ocorrencias que possuam mesmo conteudo (string) com diferentes
			   numeros de registro.

	- para LO fisica (sem geracao de copia da LO):
		- %l	-> apontador para o objeto de comparacao (Comparator)
				(util para a CompareFunction)
				(nao ordenado)
		- %ns	-> header de um registro de LB1. n eh o sizeof( TControlRec )
			   (nao ordenado)
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)
		- ...
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)

	- para LO fisica (com geracao de copia da LO):
		- %l	-> apontador para o objeto de comparacao (Comparator)
				(util para a CompareFunction)
				(nao ordenado)
		- %l	-> numero do registro corrente da base.
			   (nao ordenado)
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)
		- ...
		- %ns	-> string de tamanho n, que contera' o conteudo de um campo
			   (ordenado)



	---------------------------------------

	Se a LO a ser ordenada for a fisica e o processo for realizado sobre uma copia
	da mesma, sera' gerada uma LO em memoria que represente a LO fisica. Ou seja,
	sera' gerada uma LO de memoria no caso da ordenacao da LO fisica com duplicacao.


***/
    

/***
	PUBLIC
	Construtor da classe LBSC_OLSort

	Parameters:
		- szMask	-> cadeia de caracteres contendo a mascara dos itens que
				   devem participar da ordenacao. v. doc. sobr obj. compare.
		- polOcList	-> ponteiro para a lista de ocorrencias que sera' ordenada.
				   para indicar a LO fisica, esse parametro devera' ser NULL.
		- pOwnerBasePar	-> ponteiro para o objeto LBSC_Base que vai realizar o sort.
		- pTicketPar	-> ticket de seguranca para que o LBSC_Sort possa utilizar
				   metodos de base e de session sem problemas
		- bSecStatus	-> status de seguranca na ordenacao da LO fisica
		- bCopyPar	-> indica se a ordenacao deve ser feita em uma copia da
				   LO original (valor TRUE) ou sobre a propria (FALSE, default)

	Return:
		-

	Comments:
		- 

***/
LBSC_OLSort::LBSC_OLSort( char *szMask, LBSC_OcList *polOcList, LBSC_Base *pOwnerBasePar, const LBSC_Ticket *pTicketPar, BOOL bSecStatus, BOOL bCopyPar ):
		SortObject(), cComp()
{
	if( !szMask ){
		// erro.
		polOldOcList = polNewOcList = NULL;
		SetError( LBSE_BADARG );
		return;
	}
	// inicializacao dos atributos
	memset( (void*) uiIdArray, 0, sizeof( uiIdArray ) );
	iNumFields = 0;
	pOwnerBase = pOwnerBasePar;
	polOldOcList = polOcList;
	pTicket = pTicketPar;
	bFinished = FALSE;
	bSecureStatus = bSecStatus;
	bCopy = bCopyPar;
	memset( szOrigExpr, 0, (MAXDESCRIPTORSIZE/4) );
	strncpy( szOrigExpr, szMask, (MAXDESCRIPTORSIZE/4) - 1 );

	long	lNumRecords = polOldOcList ? pOwnerBase->GetNumOLRecords( pTicket, -1 ) : pOwnerBase->GetNumActiveRecords( pTicket );
	if( lNumRecords <= 0 ){
		SetError( LBSE_NORECORD );
		return;
	}

	if( !pOwnerBase ){
		// nao podemos prosseguir sem esta informacao
		SetError( LBSE_BADARG );
		return;
	}
	if( polOldOcList || bCopy ){
		// a LO a ser ordenada nao eh a fisica ou a ordenacao vai ser feita
		// sobre uma copia da LO, o que implica em termos que alocar outra,
		// mesmo se a LO original for a fisica
		polNewOcList = new LBSC_OcList;
		if( !polNewOcList ){
			// nao podemos continuar sem essa informacao
			SetError( LBSE_NOMEMORY );
			return;
		}
		if ( !polNewOcList->Init( lNumRecords ) ) {
			delete polNewOcList;
			SetError( LBSE_NOMEMORY );
			return;
		}
	} else {
		polNewOcList = NULL;
	}

	// fazer parsing sobre o szDescriptor (a informacao de localizacao, no inicio do
	// buffer gerado pelo processo de parsing depende de polOcList)
	memset( szDescriptor, 0, MAXDESCRIPTORSIZE );

	// espaco para o apontador do objeto comparator
	strcpy( szDescriptor, "%l" );

	if( polOldOcList ){
		// a LO nao eh a fisica
		strcat( szDescriptor, "%l" );
	} else {
		// a LO eh a fisica. 

		if( bCopy ){
			// numero do registro corrente da base
			strcat( szDescriptor, "%l" );
		} else {
			// vamos montar a string "%ns", onde n eh o sizeof( TControlRec ).
			strcat( szDescriptor, "%" );

			char	szSize[ 30 ];
			char	*szAux;
			itoa( sizeof( TControlRec ), szSize, 10 );
			// retira espacos
			for( szAux = szSize; *szAux == ' '; szAux++ );
			strcat( szDescriptor, szAux );
			strcat( szDescriptor, "s" );
		}
	}

	// montar o restante da expressao
	C_StrTok	cStrTok;
	char		*szAux = cStrTok.StrTok( szMask, " " );
	if( !szAux ){
		// erro
		polOldOcList = NULL;
		if( polNewOcList ){
			delete polNewOcList;
			polNewOcList = NULL;
		}
		SetError( LBSE_EXPRERROR );
		return;
	}
	while( szAux ){
		unsigned char cSignal = LASTCHAR( szAux );
		switch( cSignal ){
		case '<':
		case '>':
			{
				LASTCHAR( szAux ) = '\0';
				int	i = atoi( szAux );
				if( i <= 0 ){
					// valor invalido.
					polOldOcList = NULL;
					if( polNewOcList ){
						delete polNewOcList;
						polNewOcList = NULL;
					}
					SetError( LBSE_EXPRERROR );
					return;
				}
				uiIdArray[ iNumFields ] = (UINT) i;
				LBSC_Field *pf = (*pOwnerBase)( (UINT) i );
				if( !pf || pOwnerBase->LastError() != LBS_OK ){
					// campo invalido
					polOldOcList = NULL;
					if( polNewOcList ){
						delete polNewOcList;
						polNewOcList = NULL;
					}
					SetError( LBSE_EXPRERROR );
					return;
				}
				// pegamos o campo f, para obter dele o tipo de dado
				switch( pf->GetType() ){
				case BINARY_FIELD:
					// campos invalidos para ordenacao
					polOldOcList = NULL;
					if( polNewOcList ){
						delete polNewOcList;
						polNewOcList = NULL;
					}
					SetError( LBSE_EXPRERROR );
					return;

				case VALUE_FIELD:
					strcat( szDescriptor, "%l" );
					break;

				case DVALUE_FIELD:
					strcat( szDescriptor, "%w" );
					break;

				case TEXT_FIELD:
				case REFERENCED_FIELD:
				case ALPHA_FIELD:
					{
						char	szNum[ 10 ];
						char	*szAux;
						itoa( pf->GetType() == ALPHA_FIELD ? pf->GetSize() : MAXPATH, szNum, 10 );
						// retira espacos
						for( szAux = szNum; *szAux == ' '; szAux++ );
						strcat( szDescriptor, "%" );
						strcat( szDescriptor, szAux );
					}
					strcat( szDescriptor, "s" );
					break;

				case DATE_FIELD:
					strcat( szDescriptor, "%u" );
					break;
				case TIME_FIELD:
					strcat( szDescriptor, "%6s" );
					break;
				
				case BYTE_FIELD:
					strcat( szDescriptor, "%c" );
					break;

				case SINT_FIELD:
					strcat( szDescriptor, "%d" );
					break;

				case FLOAT_FIELD:
					strcat( szDescriptor, "%f" );
					break;

				default:
					// erro interno
					polOldOcList = NULL;
					if( polNewOcList ){
						delete polNewOcList;
						polNewOcList = NULL;
					}
					SetError( LBSE_ERROR );
					return;
				}
				// inserir o sinal
				strcat( szDescriptor, " " );
				LASTCHAR( szDescriptor ) = cSignal;
				if( strlen( szDescriptor ) >= (MAXDESCRIPTORSIZE-5) ){
					// estamos quase estourando o limite do buffer
					polOldOcList = NULL;
					if( polNewOcList ){
						delete polNewOcList;
						polNewOcList = NULL;
					}
					SetError( LBSE_ARGTOOLONG );
					return;
				}
			}
			break;

		default:
			// erro na expressao
			polOldOcList = NULL;
			if( polNewOcList ){
				delete polNewOcList;
				polNewOcList = NULL;
			}
			SetError( LBSE_EXPRERROR );
			return;
		}
		++iNumFields;
		szAux = cStrTok.StrTok( NULL, " " );
	}
	if( polOldOcList ){
		// a LO nao eh a fisica
		strcat( szDescriptor, "%l>" );
	}
	// terminamos de montar a expressao.
	iSizeOfKey = cComp.SetDescriptor( szDescriptor );
	if( cComp.BuildStatus != PARSEOK ){
		// deu pau no objeto comparador
		polOldOcList = NULL;
		if( polNewOcList ){
			delete polNewOcList;
			polNewOcList = NULL;
		}
		iSizeOfKey = 0;
		SetError( LBSE_ERROR );
		return;
	}

	// inicializar o SortObject

	SetParms( lNumRecords );
	if( BuildStatus != BUILDISOK ){
		// deu pau
		SetError( LBSE_ERROR );
		return;
	}
	SetError( LBS_OK );
}

/***
	PUBLIC
	Destrutor

	Parameters:
		-

	Return:
		-

	Comments:
		-

***/
LBSC_OLSort::~LBSC_OLSort()
{
}


/***
	PUBLIC
	Metodo Compare
	Compara dois elementos

	Parameters:
		- pvElem1 -> primeiro elemento a ser comparado
		- pvElem2 -> segundo elemento a ser comparado

	Return:
		- <0 indica que pvElem1 eh logicamente menor que pvElem2
		- ==0 indica que os dois elementos sao logicamente iguais
		- >0 indica que pvElem1 eh logicamente maior que pvElem2

	Comments:
		- A comparacao eh feita pelo objeto cComp, atributo da classe
		  LBSC_OLSort.

***/
int
LBSC_OLSort::Compare( void *pvElem1, void *pvElem2 )
{
	return( cComp.BuildStatus == PARSEOK ? cComp.Compare( pvElem1, pvElem2 ) : -1 );
}

/***
	PUBLIC
	Metodo GetData
	Obtem um dado a ser ordenado

	Parameters:
		- pvDest -> buffer que recebera' a chave a ser ordenada

	Return:
		- TRUE para indicar sucesso; FALSE indicando que nao ha' mais
		  dados para ordenacao.

	Comments:
		-

***/
BOOL
LBSC_OLSort::GetData( void *&pvDest )
{
	PRINTLOG( _clLBSLog, ("LBSC_OLSort::GetData") );

	if( (polOldOcList || bCopy) && !polNewOcList ){
		// este objeto nao esta' em condicoes de uso, pois
		// a lista a ser ordenada nao eh a fisica (ou eh, mas foi solicitada
		// uma copia) e o construtor nao
		// conseguiu criar uma nova lista para trabalhar.
		return( FALSE );
	}

	if( bFinished ){
		// nao ha' mais dados para ordenar.
		// vamos aproveitar para posicionar LB1 em seu inicio para que o
		// metodo PutData nao precise se preocupar com isso.
		pOwnerBase->LB1.R_Seek( 0 );
		return( FALSE );
	}

	// para montar a chave a ser ordenada, eh necessario construir um vetor de
	// ponteiros para os objetos que compoem a chave. depois, deve-se passar esse
	// vetor para o objeto comparador gerar um unico buffer (ja' considerando 
	// alinhamento) contendo todos os dados.

	// montando o vetor de ponteiros para os dados...
	char	**szPtData = new char * [ iNumFields + 1 + 1 + (polOldOcList ? 1 : 0) ];	
					// +1 por causa do ponteiro para o comparator
					// +1 por causa do header
					// +1 para o numero do registro da ocorrencia
	if( !szPtData ){
		// deu pau
		return( FALSE );
	}
	long	lOcRecNum;
	int		iDataIndex = 0;
	// montar o header

	// colocar o ponteiro para o comparator
	szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
	if( !(szPtData[ iDataIndex ]) ){
		// deu pau
		return( ClearData( szPtData, iDataIndex ) );
	}
	Comparator	*pComp = &cComp;
	memcpy( (void*) szPtData[ iDataIndex ], (void*) &pComp, sizeof( long ) );

	iDataIndex++;
	if( polOldOcList ){
		// a LO nao eh a fisica
		szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
		lOcRecNum = polOldOcList->CurPos();
		memcpy( (void*) szPtData[ iDataIndex ], (void*)&lOcRecNum, sizeof( long ) );
	} else {
		// a LO eh a fisica. 
		if( bCopy ){
			szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
			if( !(szPtData[ iDataIndex ]) ){
				// deu pau
				return( ClearData( szPtData, iDataIndex ) );
			}
			long	lPos = pOwnerBase->LB1.R_CurPos();
			memcpy( (void*) szPtData[ iDataIndex ], &lPos, sizeof( long ) );
		} else {
			szPtData[ iDataIndex ] = new char[ sizeof( TControlRec ) ];
			if( !(szPtData[ iDataIndex ]) ){
				// deu pau
				return( ClearData( szPtData, iDataIndex ) );
			}
			if( pOwnerBase->LB1.R_Read( &tcrHead ) != OK ){
				// deu pau na leitura do arquivo LB1
				return( ClearData( szPtData, iDataIndex ) );
			}
			memcpy( (void*) szPtData[ iDataIndex ], &tcrHead, sizeof( TControlRec ) );
		}
	}
	iDataIndex++;
	// agora vamos montar o restante do vetor
	for( int i = 0; i < iNumFields; i++ ){
		// pegar o campo
		LBSC_Field	*pf =  (*pOwnerBase)( uiIdArray[ i ] );
		if( !pf || pOwnerBase->LastError() != LBS_OK ){
			// deu pau na obtencao do campo
			return( ClearData( szPtData, iDataIndex ) );
		}
		// pegar o conteudo da primeira repeticao
		LBSC_Data	*pd = (*pf)[ 0 ];
		if( !pd ){
			// nao ha' dados neste campo. vamos simplesmente passar NULL na
			// posicao iDataIndex do array de estruturas
			szPtData[ iDataIndex ] = NULL;
		} else {
			switch ( pf->GetType() ) {
			case REFERENCED_FIELD:
				// no caso de REFERENCED_FIELD, devemos tratar apenas 
				// a parte da referencia ao arquivo (nome do arquivo)

				szPtData[ iDataIndex ] = new char[ MAXPATH ];
				if( szPtData[ iDataIndex ] ){
					LBSC_Reference	*pRef = (LBSC_Reference*) (*pd);
					if( pRef ){
						memcpy( szPtData[ iDataIndex ], pRef->szFileName, MAXPATH );
					} else {
						delete szPtData[ iDataIndex ];
						szPtData[ iDataIndex ] = NULL;
					}
				}
				break;

			case TEXT_FIELD:
				szPtData[ iDataIndex ] = new char[ MAXPATH ];
				if( szPtData[ iDataIndex ] ){
					// montar uma linha de texto (a partir do TER) com
					// no maximo MAXPATH caracteres.
					memset( szPtData[ iDataIndex ], 0, MAXPATH );
					char *szAux = pd->ToString();
					if ( szAux ) {
						strncpy( szPtData[ iDataIndex ], szAux, MAXPATH-1 );
						szPtData[ iDataIndex ][MAXPATH-1] = '\0';
						delete (szAux);
						szAux = NULL;
					}
				}
				break;
			case TIME_FIELD:
				{
					C_Time time( *((unsigned long *)pd->GetConstData()) );
					szPtData[ iDataIndex ] = new char[ 7 ];
					sprintf( szPtData[ iDataIndex ], "%.2d%.2d%.2d", time.Hour(), time.Minute(), time.Second() );
				}
				break;

			default:
				szPtData[ iDataIndex ] = (char*) pd->GetData();	// o GetData retorna uma copia
				break;
			}

			if( !szPtData[ iDataIndex ] ){
				// deu pau na alocacao
				return( ClearData( szPtData, iDataIndex ) );
			}
			if( pf->GetType() == ALPHA_FIELD || pf->GetType() == REFERENCED_FIELD || 
							pf->GetType() == TEXT_FIELD ){
				// vamos normalizar szPtData[ iDataIndex ] para evitar complicacoes na
				// ordenacao.
				pOwnerBase->PreStandardize( szPtData[ iDataIndex ], DEFAULTSTANDARDIZERARRAY );
			}
		}
		iDataIndex++;
	}
	if( polOldOcList ){
		// a LO nao eh a fisica.
		// colocar o numero do registro para eventual desempate de chaves iguais.
		szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
		if( !szPtData[ iDataIndex ] ){
			// deu pau
			return( ClearData( szPtData, iDataIndex ) );
		}
		memcpy( (void*) szPtData[ iDataIndex ], &lOcRecNum, sizeof( long ) );

		iDataIndex++;
	}
	// se chegamos aqui, eh porque conseguimos montar o array direitinho.
	// agora vamos empacotar o array, usando o objeto comparador
	char	*pKey = (char*) cComp.BuildKey( (void**) szPtData );

	// detonar o vetor de ponteiros
	ClearData( szPtData, iDataIndex );

	if( pKey ){
		// copiar a chave gerada pelo objeto comparador para o parametro recebido
		pvDest = (void *)pKey;

		// ir para a proxima ocorrencia
		if( !GetNextOccurrence() ){
			// acabou
			bFinished = TRUE;

			if( !polOldOcList ){
				// a LO nao eh a fisica.
				// nao ha' mais dados para ordenar.
				// vamos aproveitar para posicionar LB1 em seu inicio para que o
				// metodo PutData nao precise se preocupar com isso.
				pOwnerBase->LB1.R_Seek( 0 );
			}

		}

		return( TRUE );
	}
	return( FALSE );

}


/***
	PUBLIC
	Metodo PutData
	Completa o processo de ordenacao.

	Parameters:
		- pvKey -> apontador para a chave que esta' ordenada.

	Return:
		-

	Comments:
		- Este metodo deve obter, dentro da chave apontada por pvKey,
		  informacoes necessarias para inserir essa chave na posicao
		  correta na nova lista de ocorrencias.

***/
void
LBSC_OLSort::PutData( void *pvKey )
{
	PRINTLOG( _clLBSLog, ("LBSC_OLSort::PutData") );

	if( (polOldOcList || bCopy) && !polNewOcList ){
		// este objeto nao esta' em condicoes de uso, pois
		// a lista a ser ordenada nao eh a fisica (ou eh, mas foi solicitada
		// uma copia) e o construtor nao
		// conseguiu criar uma nova lista para trabalhar.
		return;
	}
	// extrair de pvKey o ponteiro para o comparator
	char *szKey = (char *)pvKey;
	pvKey = (void*) (((char*) pvKey) + sizeof( long ));
	
	if( polOldOcList ){
		// a LO nao eh a fisica.
		// extrair de pvKey o ponteiro para a ocorrencia a ser inserida na
		// nova LO
		LTC_OCCURRENCELIST *pList = NULL;
		LTC_OCCURRENCELIST *pDupList = new LTC_OCCURRENCELIST;
		
		long	lAux = 0;
		memcpy( &lAux, pvKey, sizeof( long ) );
		polOldOcList->Goto( lAux );
		pList = polOldOcList->GetLTList();

		if( polNewOcList && pDupList && pList ){
			pDupList->LT_DuplicateList( pList );
			polNewOcList->SetLTList( pDupList );
			polNewOcList->Next();
		}
	} else {
		// a LO eh a fisica.
		if( bCopy ){
			// extrair de pvKey o numero do registro da base
			long	lPos;
			memcpy( &lPos, pvKey, sizeof( long ) );

			// adicionar um nodo na LO que representa a fisica
			if( polNewOcList ){
				LTC_OCCURRENCE	cOc( "", lPos );
				// o metodo LT_AddOccurrence (abaixo) duplica o objeto passado
				// como parametro e insere a copia na lista.
				polNewOcList->Add( &cOc );
				polNewOcList->Next();
			}
		} else {
			// extrair de pvKey o header do registro em LB1
			TControlRec	*ptcRec = (TControlRec *) pvKey;

			if( bSecureStatus ){
				// . pegar o registro corrente (somente de LB1) da base e gravar
				// . em um arquivo de seguranca. Isso serve como prevencao contra
				// . uma eventual queda do sistema durante a ordenacao. Se isso
				// . acontecer, eh possivel recuperar o registro perdido no OpenBase
				char	szFileName[ FULLNAMESIZE ];
				char	szAux[ FULLNAMESIZE ];
				pOwnerBase->GetFullBaseName( szAux );
				sprintf( szFileName, "%s\\SECURE.LB", szAux );
				C_File	cfSecure( szFileName, "w", SH_DENYRW, TRUE );
				if( cfSecure.IsOpen() ){
					long		lPos = pOwnerBase->LB1.R_CurPos();
					TControlRec	tAux;
					if( pOwnerBase->LB1.R_Read( &tAux ) == OK ){
						if( cfSecure.Write( &lPos, sizeof( long ) ) == OK ){
							if( cfSecure.Write( &tAux, sizeof( TControlRec ) ) == OK ){
								cfSecure.Close();

								// gravar sobre o registro corrente de LB1 o ptcRec
								pOwnerBase->LB1.R_Write( ptcRec );

								// ir para o proximo registro de LB1 para que o proximo PutData ja'
								// seja realizado no registro adequado.
								pOwnerBase->NextRecord( pTicket );
							}
						}
					}
				}
			} else {
				// gravar sobre o registro corrente de LB1 o ptcRec
				pOwnerBase->LB1.R_Write( ptcRec );
				// ir para o proximo registro de LB1 para que o proximo PutData ja'
				// seja realizado no registro adequado.
				pOwnerBase->LB1.R_SeekNext();
			}
		}
	}
	delete szKey;
}



/***
	PUBLIC
	Metodo StartSort
	Realiza o processo de ordenacao propriamente dito

	Parameters:
		- 

	Return:
		- NULL indica que houve problemas.
		- FISIC_OL_OK para indicar que a LO fisica foi ordenada com
		  sucesso (se a ordenacao nao gerar uma copia da LO original), ou
		- outro valor representando a nova LO, que foi gerada com sucesso
		  pelo processo de ordenacao.

	Comments:
		- A ordenacao eh feita pelo metodo StartSort do objeto SortObject.
		- No final da ordenacao, a LO velha NAO eh destruida (seja a fisica ou nao).
		  A aplicacao deve deleta-la e remapear os seu apontadores para a 
		  nova LO gerada.
		- No caso da LO fisica, sera' gerado um novo arquivo semelhante a LB1,
		  com nome "LB1.LB1" (caso nao seja solicitada uma copia da LO ordenada). 
		  A aplicacao deve renomea-lo para "nomedabase.LB1"
		  e preencher o seu header com as informacoes que estiverem faltando.
		- As informacoes preenchidas por este objeto no header do arquivo LB1.LB1
		  sao:
		  	- Numero de registros
			- Apontador para o primeiro registro
			- Apontador para o ultimo registro valido
			- Apontador para o ultimo registro fisico

***/
LBSC_OcList *
LBSC_OLSort::StartSort()
{
	PRINTLOG( _clLBSLog, ("LBSC_OLSort::StartSort") );

	if( polOldOcList && !polNewOcList ){
		// este objeto nao esta' em condicoes de uso, pois
		// a lista a ser ordenada nao eh a fisica e o construtor nao
		// conseguiu criar uma nova lista para trabalhar.
		return( NULL );
	}

	// antes de startarmos a ordenacao, vamos nos posicionar no inicio da LO
	if( !GetFirstOccurrence() ){
		// deu pau!
		return( NULL );
	}

	char	szFileName[ FULLNAMESIZE ];
	char	szAux[ FULLNAMESIZE ];
	pOwnerBase->GetFullBaseName( szAux );
	sprintf( szFileName, "%s\\SECURE.LB", szAux );

	BOOL breadonly = pOwnerBase->bIsReadOnly;
	pOwnerBase->bIsReadOnly = TRUE;
	pOwnerBase->pSortObj = this;
	BOOL bSortRet = SortObject::StartSort();
	pOwnerBase->bIsReadOnly = breadonly;
	pOwnerBase->pSortObj = NULL;

	if ( bSortRet ) {
		// o resultado foi ok.
		// remover o arquivo de seguranca
		remove( szFileName );
		if ( polOldOcList ) {
			if ( polNewOcList->Size() > polOldOcList->Size()) {
				// houve delecao de ocorrencias na navegacao da lista; reorganizar a nova lista 
				if ( !polNewOcList->Shrink( polOldOcList->Size() ) ) {
					return NULL;
				}
			}
			polNewOcList->First();
			polOldOcList->First();
			return polNewOcList;
		}

		if ( bCopy && polNewOcList ) {
			polNewOcList->First();
		}
		return( bCopy ? polNewOcList : (LBSC_OcList *) FISIC_OL_OK );
	}
	// deu pau.
	// remover o arquivo de seguranca
	remove( szFileName );
	return( NULL );
}


/***
	PRIVATE
	Metodo GetFirstOccurrence
	Retorna a primeira ocorrencia (independentemente da LO ser a fisica ou nao)

	Parameters:
		-

	Return:
		- ponteiro para uma ocorrencia, se a LO nao for a fisica ou
		  ponteiro para registro de LB1 correspondente ao registo corrente da base,
		  se a LO for a fisica.

	Comments:
		-

***/
void *
LBSC_OLSort::GetFirstOccurrence()
{
	PRINTLOG( _clLBSLog, ("LBSC_OLSort::GetFirstOccurrence") );

	if( polOldOcList ){
		// a LO nao eh a fisica.
		// vamos pegar a primeira LO
		pOwnerBase->FirstRecord( pTicket );
		const LBSC_Occurrence	*pOc = pOwnerBase->GetFirstOccurrence( pTicket );
		int iErr = pOwnerBase->LastError();
		if( iErr != LBS_OK && iErr != LBSE_FIRSTOCCURRENCE ){
			// deu pau
			return( NULL );
		}
		return( (void*) pOc );
	}
	// a LO eh a fisica. 
	if( pOwnerBase->FirstFRecord( pTicket ) != LBS_OK ){
		// deu pau
		return( NULL );
	}
	if( pOwnerBase->LB1.R_Read( &tcrHead ) != OK ){
		// deu pau na leitura do arquivo LB1
		return( NULL );
	}
	return( (void*) &tcrHead );
}


/***
	PRIVATE
	Metodo GetNextOccurrence
	Retorna a proxima ocorrencia (independentemente da LO ser a fisica ou nao)

	Parameters:
		-

	Return:
		- ponteiro para uma ocorrencia, se a LO nao for a fisica ou
		  ponteiro para registro de LB1 correspondente ao registo corrente da base,
		  se a LO for a fisica.

	Comments:
		-

***/
void *
LBSC_OLSort::GetNextOccurrence()
{
	PRINTLOG( _clLBSLog, ("LBSC_OLSort::GetNextOccurrence") );

	if( polOldOcList ){
		// a LO nao eh a fisica.
		// vamos pegar a proxima ocorrencia que tenha o numero 
		// de registro diferente da atual.
		if( pOwnerBase->NextRecord( pTicket ) != LBS_OK ){
			// acabou!
			bFinished = TRUE;
			return( NULL );
		}
		const LBSC_Occurrence	*pOc = pOwnerBase->GetFirstOccurrence( pTicket );
		if( !pOc ){
			// deu pau
			bFinished = TRUE;
			return( NULL );
		}
		return( (void*) pOc );
	}
	// a LO eh a fisica. 
	if( bFinished ){
		// ja acabou a base
		return( NULL );
	}
	if( pOwnerBase->NextFRecord( pTicket ) != LBS_OK ){
		// deu pau
		bFinished = TRUE;
		return( NULL );
	}
	if( pOwnerBase->LB1.R_Read( &tcrHead ) != OK ){
		// deu pau na leitura do arquivo LB1
		return( NULL );
	}
	return( (void*) &tcrHead );
}


