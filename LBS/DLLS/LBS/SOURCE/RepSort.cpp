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
// Module: REPSORT.CPP
// Description:
//
//	LBSC_RepSort private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 13/07/98
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
#ifndef	_REPSORT_H_
#include	<repsort.h>
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
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif


EXTLOG( _clLBSLog );	// objeto para geracao de log

extern BOOL ClearData( char **, int );

/***
	PUBLIC
	Construtor da classe LBSC_RepSort

	Parameters:
		- pSortFieldPar		-> ponteiro para o objeto LBSC_Field que vai ser ordenado.

	Return:
		-

	Comments:
		- 

***/
LBSC_RepSort::LBSC_RepSort( LBSC_Field *pSortFieldPar ):
		SortObject(), cComp()
{
	// inicializacao dos atributos
	pSortField = pSortFieldPar;
	iIndAtual = 0;

	if( !pSortField ){
		// nao podemos prosseguir sem esta informacao
		SetError( LBSE_BADARG );
		return;
	}

	long	lNumRep = pSortField->GetNumberOfRepetition();
	if( lNumRep <= 0 ){
		SetError( LBSE_EMPTYLIST );
		return;
	}

	// DESCRITOR DA CHAVE DE ORDENACAO:
	//	- %l	-> apontador para o objeto de comparacao (Comparator)
	//			   (util para a CompareRepetition)
	//			   (nao ordenado)
	//	- %l	-> ponteiro para a repeticao, que saira' da lista no final
	//			   do Get e voltara' no Put, em outra posicao da lista
	//			   (util para o PutData)
	//		       (nao ordenado)
	//	- %ns	-> string de tamanho n, que contera' o conteudo de uma repeticao
	//		       (ordenado)
	//			   (na verdade pode ser %l, %w, etc. dependendo do tipo do campo)
	//	- %l	-> numero de ordem da repeticao dentro do campo. Nao eh o numero de
	//			   sequencia na lista, e sim um numero que representa a ordem de atualizacao
	//			   da repeticao. Util para desempate em caso de chaves iguais.

	// espaco para o apontador do objeto comparator
	strcpy( szDescriptor, "%l" );

	// apontador para a repeticao
	strcat( szDescriptor, "%l" );

	// montar o restante da expressao
	switch( pSortField->GetType() ){
	case BINARY_FIELD:
		// campo invalido para ordenacao
		SetError( LBSE_INVALIDFIELDTYPE );
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
			itoa( pSortField->GetType() == ALPHA_FIELD ? pSortField->GetSize() : MAXPATH, szNum, 10 );
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
		SetError( LBSE_ERROR );
		return;
	}

	// inserir o sinal
	strcat( szDescriptor, (pSortField->GetAttrib() & ASC_ORD_FIELD) ? ">" : "<" );

	// inserir numero de ordem de atualizacao, para desempate
	strcat( szDescriptor, (pSortField->GetAttrib() & ASC_ORD_FIELD) ? "%l>" : "%l<" );

	// terminamos de montar a expressao.
	iSizeOfKey = cComp.SetDescriptor( szDescriptor );
	if( cComp.BuildStatus != PARSEOK ){
		// deu pau no objeto comparador
		iSizeOfKey = 0;
		SetError( LBSE_ERROR );
		return;
	}

	// obter no LBS.INI o nome do diretorio de trabalho
	char	szAuxDir[ FULLNAMESIZE ];
	strncpy( szAuxDir, LBSC_ServerConfig::TempDir(), FULLNAMESIZE );

	// inicializar o SortObject
	SetParms( lNumRep );
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
LBSC_RepSort::~LBSC_RepSort()
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
		  LBSC_RepSort.

***/
int
LBSC_RepSort::Compare( void *pvElem1, void *pvElem2 )
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
LBSC_RepSort::GetData( void *&pvDest )
{
	PRINTLOG( _clLBSLog, ("LBSC_RepSort::GetData") );

	if( !pSortField ){
		// este objeto nao esta' em condicoes de uso.
		return( FALSE );
	}

	// para montar a chave a ser ordenada, eh necessario construir um vetor de
	// ponteiros para os objetos que compoem a chave. depois, deve-se passar esse
	// vetor para o objeto comparador gerar um unico buffer (ja' considerando 
	// alinhamento) contendo todos os dados.

	// montando o vetor de ponteiros para os dados...
	char	**szPtData = new char * [ 1 + 1 + 1 + 1 ];
					//  1 = ponteiro para o comparator
					// +1 = apontador para a repeticao
					// +1 = chave
					// +1 = numero de ordem de atualizacao, para desempate
	if( !szPtData ){
		// deu pau
		return( FALSE );
	}
	int		iDataIndex = 0;

	// colocar o ponteiro para o comparator
	szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
	if( !(szPtData[ iDataIndex ]) ){
		// deu pau
		return( ClearData( szPtData, iDataIndex ) );
	}
	Comparator	*pComp = &cComp;
	memcpy( (void*) szPtData[ iDataIndex ], (void*) &pComp, sizeof( long ) );
	iDataIndex++;

	// apontador para a repeticao
	LBSC_Data	*pd = (pSortField->lbscdlDataList)[ iIndAtual ];
	if( !pd ){
		// repeticao inexistentente ou vazia. Erro.
		return( ClearData( szPtData, iDataIndex ) );
	} else {
		szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
		if( !(szPtData[ iDataIndex ]) ){
			// deu pau
			return( ClearData( szPtData, iDataIndex ) );
		}
		memcpy( (void*) szPtData[ iDataIndex ], &pd, sizeof( long ) );
	}

	iDataIndex++;

	if( pd && pd->IsEnabled() ){
		switch ( pSortField->GetType() ) {
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
	} else {
		szPtData[ iDataIndex ] = NULL;
	}

	if( szPtData[ iDataIndex ] ){
		if( pSortField->GetType() == ALPHA_FIELD || pSortField->GetType() == REFERENCED_FIELD || 
						pSortField->GetType() == TEXT_FIELD ){
			// vamos normalizar szPtData[ iDataIndex ] para evitar complicacoes na
			// ordenacao.
			pSortField->plbscbBase->PreStandardize( szPtData[ iDataIndex ], DEFAULTSTANDARDIZERARRAY );
		}
	}

	iDataIndex++;

	// colocar numero de ordem de atualizacao, para desempate
	if( pd ){
		szPtData[ iDataIndex ] = new char[ sizeof( long ) ];
		if( !(szPtData[ iDataIndex ]) ){
			// deu pau
			return( ClearData( szPtData, iDataIndex ) );
		}
		int	iUpdateSeqNumber = pd->GetUpdateSequenceNumber();

		memcpy( (void*) szPtData[ iDataIndex ], &iUpdateSeqNumber, sizeof( long ) );
	} else {
		szPtData[ iDataIndex ] = NULL;
	}

	iDataIndex++;

	// se chegamos aqui, eh porque conseguimos montar o array direitinho.
	// agora vamos empacotar o array, usando o objeto comparador
	char	*pKey = (char*) cComp.BuildKey( (void**) szPtData );

	// detonar o vetor de ponteiros
	ClearData( szPtData, iDataIndex );

	if( pKey ){
		// copiar a chave gerada pelo objeto comparador para o parametro recebido
		pvDest = (void *)pKey;

		// ir para a proxima repeticao
		++iIndAtual;

		if( iIndAtual >= pSortField->GetNumberOfRepetition() ){
			// nao ha' mais dados para ordenar.
			// vamos limpar a lista de repeticoes (sem deletar as mesmas)
			// para que o put as insira com nova ordem.
			if( pSortField->lbscdlDataList.First() ){
				do{
					pSortField->lbscdlDataList.Refresh( NULL );
				} while( pSortField->lbscdlDataList.Next() );
				pSortField->lbscdlDataList.DelAll();
			}
			// zerar iIndAtual para usar no PutData
			iIndAtual = 0;
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
LBSC_RepSort::PutData( void *pvKey )
{
	PRINTLOG( _clLBSLog, ("LBSC_RepSort::PutData") );

	if( !pSortField ){
		// este objeto nao esta' em condicoes de uso.
		return;
	}

	// extrair de pvKey o ponteiro para o comparator
	char *szKey = (char *) pvKey;
	pvKey = (void*) (((char*) pvKey) + sizeof( long ));
	
	// obter o ponteiro para a repeticao
	LBSC_Data	*pd = (LBSC_Data*) (*((long*)pvKey));

	if( pd ){
		// inserir pd na lista de repeticoes do campo pSortField.
		pSortField->IncNumberOfUpdates();
		pSortField->lbscdlDataList.Add( pd, TAIL );
		pSortField->UpdateFieldFlag( TRUE, iIndAtual );
		pd->SetModified( TRUE );
	}
	++iIndAtual;
	delete szKey;
}



/***
	PUBLIC
	Metodo StartSort
	Realiza o processo de ordenacao propriamente dito

	Parameters:
		- 

	Return:
		- FALSE indica que houve problemas.
		- TRUE em caso de sucesso.

	Comments:
		- A ordenacao eh feita pelo metodo StartSort do objeto SortObject.
		- A ordenacao eh feita sobre a propria lista de repeticoes do campo.		  

***/
BOOL
LBSC_RepSort::StartSort()
{
	PRINTLOG( _clLBSLog, ("LBSC_RepSort::StartSort") );

	if( !pSortField ){
		// este objeto nao esta' em condicoes de uso.
		return( NULL );
	}

	iIndAtual = 0;
	BOOL bSortRet = SortObject::StartSort();
	iIndAtual = 0;

	return( bSortRet );
}



