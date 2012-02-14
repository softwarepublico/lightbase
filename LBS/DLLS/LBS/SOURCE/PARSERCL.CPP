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
// Module: PARSERCL.CPP
// Description:
//
//	LBSC_Parser class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//
// Last update: 24/07/95
//


#ifndef	INITIALTERMSIZE
#define	INITIALTERMSIZE	(256)	// tamanho inicial alocado para armazenar
								// um termo que sera' indexado
#endif

#if !defined __STDLIB_H && !defined _INC_STDLIB
#include	<stdlib.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

#ifndef _INC_MATH
#include	<math.h>
#endif
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif
extern "C" {
#include	<personcl.h>
}
#include        <OCLISTCL.H>
//extern	"C"	yylexmain( char *, long *, char *, int * );

#define	PROCESS_FILE		0x01
#define	PROCESSING_FILE		0x02
#define	PROCESS_FINISHED	0x04


/***
	Metodo LBSC_Parser
	Construtor

	Parameters:
		- plbscbBase	-> base sobre a qual o parser vai trabalhar

	Return:
		-

	Comments:
		-

***/

LBSC_Parser::LBSC_Parser( LBSC_Base *plbscBase )
{
	szTerm = NULL;
	szTok = NULL;
	this->plbscbBase = plbscBase;
	LT_SetParserTerm( NULL );
	LT_SetParserStatus( 0 );
	szTok = new char [ INITIALTERMSIZE +1 ];
	iTermSize = INITIALTERMSIZE;
	szTerm = new char [ iTermSize+1 ];
	bIndexing = TRUE;
	bProcessReference = 0;
	bUniqueIndex = FALSE;
	lCurrRepetSize = 0;
	lRepetPos = 0L;
	// lRepetPos = indice do caracter corrente dentro da
	// repeticao. No caso de campos VALUE_FIELD e DVALUE_FIELD
	// lRepetPos eh usado para pegar somente o valor na primeira
	// vez e apenas setar "fim de processamento" na segunda vez.
}

/***
	Metodo ~LBSC_Parser
	Destrutor

	Parameters:
		-

	Return:
		-

	Comments:
		-

***/
LBSC_Parser::~LBSC_Parser()
{
	if( szTok ){
		delete szTok;
	}
	if( szTerm ){
		delete szTerm;
	}
}


/***
	Metodo LT_ParserInit
	Inicializa o parser

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo faz uso da API LightText da Green Software

***/
int
LBSC_Parser::LT_ParserInit()
{
	if( !plbscbBase || !szTok || !szTerm ){
		return( LBSE_ERROR );
	}
	return( LBS_OK );
}



/***
	Metodo LT_ParserProcess
	Obtem tokens da repeticao corrente do campo corrente do registro
	corrente de uma base.

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo faz uso da API LightText da Green Software

***/
int
LBSC_Parser::LT_ParserProcess(LTC_OCCURRENCE *pcoOccurrence)
{
	int				iRet;
	int				iFieldType;
	long			lFieldValAux;
	BYTE			bFieldValAux;
	short			siFieldValAux;
	double			dFieldValAux;
	float			fFieldValAux;
	UINT			uiFieldId;
	const char		*szAux = NULL;

	if( !plbscbBase || !szTerm ){
		return( LBSE_ERROR );
	}
	iFieldType = plbscbBase->GetCurrFieldType();
	if( iFieldType < 0 ){
		return( iFieldType );
	} 

	LT_SetParserTerm( NULL );
	if( lRepetPos == 0L ){
		// Pega o id do campo corrente
		uiFieldId = plbscbBase->GetCurrFieldId();
		LBSC_Field	*pf = ((*plbscbBase).lbscrCurrRecord)( uiFieldId );
		if( !pf || (pf->GetNumberOfRepetition() <= 0) ){
			// nao ha' repeticoes
			LT_SetParserTerm( NULL );
			LT_SetParserStatus( PROCESS_END );
			return( LBS_OK );
		}
		// Pega o tamanho da repeticao corrente
		lCurrRepetSize = plbscbBase->GetFieldRepetitionSize( uiFieldId, -1 );
		// -1 no segundo parametro (acima) indica repeticao corrente
	}

	switch( iFieldType ){
	case VALUE_FIELD:
	case BYTE_FIELD:
	case SINT_FIELD:
		if( lRepetPos == 0L ){
			// Pega a repeticao corrente
			switch( iFieldType ){
			case VALUE_FIELD:
				plbscbBase->GetFieldRepetition( uiFieldId, -1, &lFieldValAux );
				break;

			case BYTE_FIELD:
				plbscbBase->GetFieldRepetition( uiFieldId, -1, &bFieldValAux );
				lFieldValAux = (long) bFieldValAux;
				break;

			case SINT_FIELD:
				plbscbBase->GetFieldRepetition( uiFieldId, -1, &siFieldValAux );
				lFieldValAux = (long) siFieldValAux;
				break;
			}

			// Converte o valor para uma string e seta o termo e o status
			// do parser.
			ltoa( lFieldValAux, szTerm, 10 );
			LT_SetParserTerm( szTerm );
			LT_SetParserStatus( WORD_END );
			pcoOccurrence->AddSequence( (TUTWOBYTES)1 );
			++lRepetPos;
		} else {
			LT_SetParserStatus( PROCESS_END );
			lRepetPos = 0L;
		}
		break;

	case DVALUE_FIELD:
	case FLOAT_FIELD:
		if( lRepetPos == 0L ){
			// Pega a repeticao corrente
			switch( iFieldType ){
			case DVALUE_FIELD:
				plbscbBase->GetFieldRepetition( uiFieldId, -1, &dFieldValAux );
				// So para garantir que fFieldValAux serah menor dMaxVal
				fFieldValAux = 0;
				break;

			case FLOAT_FIELD:
				plbscbBase->GetFieldRepetition( uiFieldId, -1, &fFieldValAux );
				//dFieldValAux = (double) fFieldValAux;
				// So para garantir que dFieldValAux serah menor dMaxVal
				dFieldValAux = 0;
				break;
			}

			// Converte o valor para uma string e seta o termo e o status
			// do parser.
			double dMaxVal = pow( 10, plbscbBase->LB1.tcrHead.iIntPart );
			if( (dFieldValAux >= dMaxVal) || (fFieldValAux >= dMaxVal) ){
				// nao podemos indexar este valor, pois ele excede o numero
				// de digitos que o sistema de indices suporta
				LT_SetParserStatus( PROCESS_END );
				lRepetPos = 0L;
				break;
			}
			if ( iFieldType == FLOAT_FIELD ) {
				char szAux[INTEGER_PART];
				int iInt = fFieldValAux; //Pegando a parte inteira do numero
				
				sprintf(szAux,"%d", iInt); //Transformado em string
				int iLen = strlen(szAux); //Obtendo o tamanho da string
				iLen  = (iInt < 0.0) ? (iLen - 1) : iLen;
				// Na transformação de um float para string, no máximo a precisão 
				// tem que ser de 7 digitos, e incluindo o ponto decimal, então temos
				// 8 digitos
				int iVal = __min( (iLen + 5), 8);

				_gcvt( fFieldValAux, iVal, szTerm );

				//sprintf( szTerm, "%0.*f", 6, (double)fFieldValAux);
			}
			else { // iFieldType == DVALUE_FIELD
				sprintf( szTerm, "%.*f", plbscbBase->LB1.tcrHead.iDecPart, dFieldValAux);
			}
			LT_SetParserTerm( szTerm );
			LT_SetParserStatus( WORD_END );
			pcoOccurrence->AddSequence( (TUTWOBYTES)1 );
			++lRepetPos;
		} else {
			LT_SetParserStatus( PROCESS_END );
			lRepetPos = 0L;
		}
		break;
	case TEXT_FIELD:
	case ALPHA_FIELD:
		// processar o texto contido no documento
		bProcessReference = 0;
		/* no break*/

	case REFERENCED_FIELD:
		if( bProcessReference ){
			// processar a referencia e depois o conteudo
			// do campo
			switch( bProcessReference ){
			case PROCESS_FILE:
				{
					// preparar para processar o buffer
					// do campo referencia
					lRepetPos = 0L;
					bUniqueIndex = FALSE;
					iRet = LBSE_ERROR;
					LBSC_Field	*pf = ((*plbscbBase).lbscrCurrRecord)( uiFieldId );
					if( pf ){
						LBSC_Reference *pRef = (LBSC_Reference*) pf->GetConstRepByIndex( -1 );
						if( !pRef ){
							// deu merda
							bProcessReference = 0;
							LT_SetParserTerm( NULL );
							LT_SetParserStatus( PROCESS_END );
							lRepetPos = 0L;
							lCurrRepetSize = 0;
							bUniqueIndex = FALSE;
							break;
						}
						switch( pRef->iFormat ){
						case LBSRT_URL:
							iRet = GetUrlBuffer( pRef );
							break;
							
						case LBSRT_WORD:
							iRet = GetWordBuffer( pRef );
							break;
						}
					}
					if( iRet != LBS_OK ){
						// deu pau ou nao ha' nada para processar
						bProcessReference = 0;
						LT_SetParserTerm( NULL );
						LT_SetParserStatus( PROCESS_END );
						lRepetPos = 0L;
						lCurrRepetSize = 0;
						bUniqueIndex = FALSE;
						break;
					}
					// tratar o primeiro token
					plbscbBase->PreStandardize( szTerm );
					lipParser.SetText( szTerm );
					iRet = GetToken( &lRepetPos, pcoOccurrence );
					pcoOccurrence->AddParagraph( (TUTWOBYTES)1 );
					if( iRet != LBS_OK ){
						return( iRet );
					}

					// dar continuidade ao processo
					bProcessReference = PROCESSING_FILE;

					if( LT_GetParserStatus() == PROCESS_END ){
						bProcessReference = 0;
						LT_SetParserTerm( NULL );
						LT_SetParserStatus( PROCESS_END );
						lRepetPos = 0L;
						lCurrRepetSize = 0;
						bUniqueIndex = FALSE;
					}
				} // case PROCESS_FILE
				break;

			case PROCESSING_FILE:
				iRet = GetToken( &lRepetPos, pcoOccurrence );
				pcoOccurrence->AddParagraph( (TUTWOBYTES)1 );
				if( iRet != LBS_OK ){
					return( iRet );
				}
				if( LT_GetParserStatus() == PROCESS_END ){
					bProcessReference = 0;
					lRepetPos = 0L;
					lCurrRepetSize = 0;
					bUniqueIndex = FALSE;
				}
				break;

			case PROCESS_FINISHED:
				bProcessReference = 0;
				LT_SetParserTerm( NULL );
				LT_SetParserStatus( PROCESS_END );
				lRepetPos = 0L;
				lCurrRepetSize = 0;
				bUniqueIndex = FALSE;
				break;
			}
			break;
		}
		if( lRepetPos == 0L ){
			if( ReallocBuffer() != LBS_OK  ){
				return( LBSE_ERROR );
			}
			
			if( iFieldType == REFERENCED_FIELD ){
				// no caso de REFERENCED_FIELD devemos tratar apenas o szFileName
				// e depois o conteudo do szFileName (conteudo do arquivo)
				LBSC_Field	*pf = ((*plbscbBase).lbscrCurrRecord)( uiFieldId );
				if( pf ){
					LBSC_Reference *pRef = (LBSC_Reference*) pf->GetConstRepByIndex( -1 );
					if( pRef ){
						szAux = pRef->szFileName;
					}
				} else {
					szAux = NULL;
				}
				if( szAux && strcmp( szAux, "" ) != 0 ){
					strcpy( szTerm, szAux );
					lipParser.SetText( ( const char * ) szTerm );
				}
			} else {
				LBSC_Field	*pf = ((*plbscbBase).lbscrCurrRecord)( uiFieldId );
				if( pf ){
					szAux = (char*) pf->GetConstRepByIndex( -1 );
					if( szAux && strcmp( szAux, "" ) != 0 ){
						memcpy( szTerm, szAux, min( iTermSize, lCurrRepetSize ) );
						szTerm[ min( iTermSize, lCurrRepetSize ) ] = '\0';
						if ( !lRepetPos ){
							lipParser.SetText( ( const char * ) szTerm );
						}
					}
				} else {
					szAux = NULL;
				}
			}
			if( !szAux || strcmp( szAux, "" ) == 0 ){
				// nao precisamos processar esta repeticao
				LT_SetParserTerm( NULL );
				LT_SetParserStatus( PROCESS_END );
				lCurrRepetSize = 0;
				return( LBS_OK );
			}

			// Pega o proximo token de szTerm a partir
			// da posicao lRepetPos. lRepetPos eh alterado por
			// GetToken e fica apontando para o inicio do proximo
			// token. GetToken ja seta o termo e o status do parser.

			if( ((plbscbBase->iIndexTree == UNIQUETREE) &&  !bUniqueIndex) || 
				((plbscbBase->iIndexTree == ENTIRETREE) &&  !bUniqueIndex) || 
				((plbscbBase->iIndexTree == (UNIQUETREE | ENTIRETREE)) &&  !bUniqueIndex) ){
				// se for SOMENTE o indice UNIQUETREE ou SOMENTE ENTIRETREE, 
				// ou os dois indices,  entao devo apontar para o final do 
				// buffer para nao pegarmos a mesma chave no proximo passo

				if( iFieldType == TEXT_FIELD ){
					// isso nao deveria acontecer, pois campos TEXTO nao deveriam
					// ter indices de chave unica nem entiretree. De toda forma,
					// vamos tratar...
					lRepetPos = lCurrRepetSize;
				} else {
					lipParser.lCountText = lRepetPos = (long) strlen( szTerm );
				}
				
				bUniqueIndex = TRUE;
				plbscbBase->PreStandardize( szTerm, DEFAULTSTANDARDIZERARRAY );
				LT_SetParserTerm( szTerm );
				LT_SetParserStatus( WORD_END );		
				pcoOccurrence->AddSequence( (TUTWOBYTES)1 );
				iRet = LBS_OK;
			} else {
				if( iFieldType == TEXT_FIELD ){
					int		iStatus;
					//aqui trata TER
					//aqui, tem de chamar o ter to txt de li
					strcpy(szTerm, licterConvert.TerToTxt( szTerm, ( long )strlen( szTerm ), '\n' ));
					lipParser.SetText( ( const char * ) szTerm );
					iRet = GetToken( &lRepetPos, pcoOccurrence );

					if( iRet == LBS_OK ){
						// vamos "pre-normalizar" a string retornada
						// pelo parser do TER
						plbscbBase->PreStandardize( szTok );
						LT_SetParserTerm( szTok );
						lRepetPos++;
					}
				} else {
					// vamos fazer uma "pre-normalizacao" da
					// string para retirar os caracteres acentuados.
					// isso eh uma solucao temporaria para resolver
					// um problema do parser (o parser nao consegue
					// reconhecer caracteres acentuados).
					plbscbBase->PreStandardize( szTerm );
					lipParser.SetText( ( const char * ) szTerm );
					iRet = GetToken( &lRepetPos, pcoOccurrence );
				}
				if( iRet != LBS_OK ){
					return( iRet == TER_TOKERROR ? LBSE_ERROR : iRet );
				}
			}
		} else {
			if( iFieldType == TEXT_FIELD ){
				int	iStatus;

				// o GetToken abaixo eh do TE_TOKEN (feito em BSB)
				iRet = GetToken( &lRepetPos, pcoOccurrence );
				
				if( iRet == LBS_OK ){
					// vamos "pre-normalizar" a string retornada
					// pelo parser do TER
					plbscbBase->PreStandardize( szTok );
					LT_SetParserTerm( szTok );
				}
			} else {
				iRet = GetToken( &lRepetPos, pcoOccurrence );
			}
			if( iRet != LBS_OK ){
				return( iRet == TER_TOKERROR ? LBSE_ERROR : iRet );
			}
		}
		if( LT_GetParserStatus() == PROCESS_END ){
			if( iFieldType == REFERENCED_FIELD ){
				// acabamos de indexar a referencia.
				// agora vamos abrir o arquivo para comecar a indexa-lo.
				// (apenas se houver indice adequado para o arquivo)
				uiFieldId = plbscbBase->GetCurrFieldId();
				LBSC_Field	*pf = (*plbscbBase)( uiFieldId );
				if( pf ){
					if( (plbscbBase->iIndexTree != (UNIQUETREE)) &&
						(plbscbBase->iIndexTree != (ENTIRETREE)) &&
						(plbscbBase->iIndexTree != (UNIQUETREE | ENTIRETREE)) ){
						strcpy( szTok, "." );
						LT_SetParserTerm( szTok );
						LT_SetParserStatus( PARAGRAPH_END );
						bProcessReference = PROCESS_FILE;
					}
				}
			}				
			lRepetPos = 0L;
			lCurrRepetSize = 0;
			bUniqueIndex = FALSE;
		}
		break;

	case BINARY_FIELD:
		LT_SetParserStatus( PROCESS_END );
		break;

	case DATE_FIELD:
		if( lRepetPos == 0L ){
			C_Date	cdDate;

			// Pega a repeticao corrente
			plbscbBase->GetFieldRepetition( uiFieldId, -1, &cdDate );

			// Usaremos aqui o formato MM/DD/AAAA para datas.
			// Deveremos oferecer outros formatos nas proximas
			// versoes. Isso deve ser combinado com a GREEN.
			sprintf( szTerm, "%02d/%02d/%04d", cdDate.Month(), cdDate.DayOfMonth(), cdDate.Year() );

			LT_SetParserTerm( szTerm );
			LT_SetParserStatus( WORD_END );
			++lRepetPos;
		} else {
			LT_SetParserStatus( PROCESS_END );
			lRepetPos = 0L;
		}
		break;

	case TIME_FIELD:
		if( lRepetPos == 0L ){
			C_Time	ctTime;

			// Pega a repeticao corrente
			plbscbBase->GetFieldRepetition( uiFieldId, -1, &ctTime );

			// Usaremos aqui o formato HH:MM para horas.
			// Deveremos oferecer outros formatos nas proximas
			// versoes. Isso deve ser combinado com a GREEN.
			sprintf( szTerm, "%02d:%02d", ctTime.Hour(), ctTime.Minute() );

			LT_SetParserTerm( szTerm );
			LT_SetParserStatus( WORD_END );
			++lRepetPos;
		} else {
			LT_SetParserStatus( PROCESS_END );
			lRepetPos = 0L;
		}
		break;

	}
	return( LBS_OK );
}


/***
	Metodo LT_ParserTerminate
	Finaliza o processamento do parser.

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo faz uso da API LightText da Green Software.

***/
int
LBSC_Parser::LT_ParserTerminate()
{
	return( LBS_OK );
}


/***
	Metodo LT_ParserResetStatus
	Reinicializa status de atributos do objeto.

	Parameters:
		-

	Return:
		- LBS_OK 

	Comments:
		- Este metodo eh chamado pela LT em caso de erro durante a
		indexacao de uma tripla campo,registro,repeticao. Inicializa
		atributos internos para dar tudo OK numa nova chamada do parser.

***/
int		
LBSC_Parser::LT_ParserResetStatus()
{
	bProcessReference = 0;
	LT_SetParserStatus( PROCESS_END );
	lRepetPos = 0L;
	lCurrRepetSize = 0;
	bUniqueIndex = FALSE;

	return LBS_OK;
}



/***
	Metodo GetToken
	Este metodo retorna um token de uma string a partir de uma determinada
	posicao.

	Parameters:
		- szStr	-> string da qual o token deve ser obtido.
		- plPos	-> apontador para a posicao a partir da qual a
			   string deve ser lida.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Este metodo altera o parametro plPos, que fica apontando para
		  o proximo token no final do processamento.
		- Este metodo seta o termo e o status do parser para representarem
		  o token lido.
		- Este metodo chama a funcao yylexmain, definida no arquivo pars.c,
		  que eh responsavel pelo trabalho de leitura/obtebcao dos tokens.
		  O arquivo pars.c foi gerado atraves da ferramenta lex e algumas
		  alteracoes foram feitas para permitir a interacao entre esta classe
		  e suas funcoes.

***/
int
LBSC_Parser::GetToken( long *plPos, LTC_OCCURRENCE *pcoOccurrence  )
{
	int	iStatus;
	if( !szTok ){
		return( LBSE_NOMEMORY );
	}
	LIP_Occurrence lipOccAux;
	if(lipParser.GetToken( lipOccAux )>=0){
		*plPos = lipOccAux.lTextPosition + lipOccAux.lTokenSize;
		strcpy( szTok , lipOccAux.GetWord( ) );
		pcoOccurrence->SetSequence( lipOccAux.GetlWord() );
		pcoOccurrence->SetSentence( lipOccAux.GetlSentence() );
		pcoOccurrence->SetParagraph( lipOccAux.GetlParagraph() );
	} 
	// o -1 é pq em LIPParser o 0 é ok!!!
	iStatus = lipParser.GetStatus( ) - 1;	
	//yylexmain( szStr, plPos, szTok, &iStatus );
	if( iStatus == PROCESS_END ){
		LT_SetParserTerm( NULL );
	} else {
		LT_SetParserTerm( szTok );
	}
	LT_SetParserStatus( iStatus );
	return LBS_OK;
}


/**********************************************************
// Function name	: LBSC_Parser::GetUrlBuffer
// Description	    : 
// Return type		: int 
// Argument         : LBSC_Reference *pRef
**********************************************************/
int LBSC_Parser::GetUrlBuffer( LBSC_Reference *pRef )
{
	if( !pRef ){
		return( LBSE_BADARG );
	}
	if( pRef->szBuffer && pRef->szBuffer[0] ){
		lCurrRepetSize = strlen( pRef->szBuffer );
		if( ReallocBuffer() == LBS_OK  ){
			strcpy( szTerm, pRef->szBuffer );
			return( LBS_OK );
		}
	}
	return( LBSE_ERROR );
}


/**********************************************************
// Function name	: LBSC_Parser::GetWordBuffer
// Description	    : 
// Return type		: int 
// Argument         : LBSC_Reference *pRef
**********************************************************/
int LBSC_Parser::GetWordBuffer( LBSC_Reference *pRef )
{
	if( !pRef ){
		return( LBSE_BADARG );
	}
	if( pRef->szBuffer && pRef->szBuffer[0] ){
		lCurrRepetSize = strlen( pRef->szBuffer );
		if( ReallocBuffer() == LBS_OK  ){
			strcpy( szTerm, pRef->szBuffer );
			return( LBS_OK );
		}
	}
	return( LBSE_ERROR );
}

/**********************************************************
// Function name	: LBSC_Parser::ReallocBuffer
// Description	    : 
// Return type		: int 
**********************************************************/
int LBSC_Parser::ReallocBuffer()
{
	if( lCurrRepetSize >= iTermSize ){
		// realocar o bufferzao
		if( szTerm ){
			delete szTerm;
			szTerm = NULL;
		}
		iTermSize = lCurrRepetSize + 1;
		szTerm = new char [ iTermSize+1 ];
		if( !szTerm ){
			// deu pau
			return( LBSE_NOMEMORY );
		}
	}
	return( LBS_OK );
}


