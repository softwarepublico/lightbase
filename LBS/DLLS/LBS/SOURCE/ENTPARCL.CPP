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
// Module: ENTPARCL.CPP
// Description:
//
//	LBSC_EntParser class methods file. This parser only returns the
//	entire data of each repetition; it doesn't break the repetitions
//	in tokens.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 18/06/95
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
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif

#ifdef __BORLANDC__
#pragma warn -par
#endif

							

/***
	Metodo LBSC_EntParser
	Construtor

	Parameters:
		- plbscBase	-> base sobre a qual o parser vai trabalhar

	Return:
		-

	Comments:
		-

***/

LBSC_EntParser::LBSC_EntParser( LBSC_Base *plbscBase ) 
{
	this->pBase = plbscBase;
	LT_SetParserTerm( NULL );
	LT_SetParserStatus( 0 );
	szTok = new char [ INITIALTERMSIZE +1 ];
	iTermSize = INITIALTERMSIZE;
	szTerm = new char [ iTermSize+1 ];
}
#ifdef __BORLANDC__
#pragma warn .par
#endif

/***
	Metodo ~LBSC_EntParser
	Destrutor

	Parameters:
		-

	Return:
		-

	Comments:
		-

***/
LBSC_EntParser::~LBSC_EntParser()
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
LBSC_EntParser::LT_ParserInit()
{
	if( !pBase || !szTok || !szTerm ){
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
LBSC_EntParser::LT_ParserProcess(LTC_OCCURRENCE *pcoOccurrence)
{
	int				iRet;
	int				iFieldType;
	UINT			uiFieldId;
	static	long	lCurrRepetSize = 0;
	static	long	lRepetPos = 0L;
			// lRepetPos = indice do caracter corrente dentro da
			// repeticao. No caso de campos VALUE_FIELD e DVALUE_FIELD
			// lRepetPos eh usado para pegar somente o valor na primeira
			// vez e apenas setar "fim de processamento" na segunda vez.

	if( !pBase || !szTerm ){
		return( LBSE_ERROR );
	}
	// Pega o tipo do campo
	iFieldType = pBase->GetCurrFieldType();
	if( iFieldType < 0 ){
		return( LBSE_INVALIDFIELDTYPE );
	}
	LT_SetParserTerm( NULL );
	if( lRepetPos == 0L ){
		// Pega o id do campo corrente
		uiFieldId = pBase->GetCurrFieldId();
		LBSC_Field	*pf = ((*pBase).lbscrCurrRecord)( uiFieldId );
		if( !pf || (pf->GetNumberOfRepetition() <= 0) ){
			// nao ha' repeticoes
			LT_SetParserTerm( NULL );
			LT_SetParserStatus( PROCESS_END );
			return( LBS_OK );
		}
		// Pega o tamanho da repeticao corrente
		lCurrRepetSize = pBase->GetFieldRepetitionSize( uiFieldId, -1 );
		// -1 no segundo parametro (acima) indica repeticao corrente
	}

	switch( iFieldType ){
	case REFERENCED_FIELD:
	case ALPHA_FIELD:
		if( lRepetPos == 0L ){
			if( lCurrRepetSize >= iTermSize ){
				// realocar o bufferzao
				delete szTerm;
				iTermSize = lCurrRepetSize + 1;
				szTerm = new char [ iTermSize+1 ];
				if( !szTerm ){
					// fudeu
					return( LBSE_ERROR );
				}
			}
			const char	*szAux = NULL;
			
			LBSC_Field	*pf = ((*pBase).lbscrCurrRecord)( uiFieldId );
			if( pf ){
				if( iFieldType == REFERENCED_FIELD ){
					// no caso de REFERENCED_FIELD devemos tratar o szFileName
					LBSC_Reference *pRef = (LBSC_Reference*) pf->GetConstRepByIndex( -1 );
					if( pRef ){
						szAux = pRef->szFileName;
					}
				} else {
					szAux = (char*) pf->GetConstRepByIndex( -1 );
				}
			}
			if( !szAux || strcmp( szAux, "" ) == 0 ){
				// nao precisamos processar esta repeticao
				LT_SetParserTerm( NULL );
				LT_SetParserStatus( PROCESS_END );
				lCurrRepetSize = 0;
				return( LBS_OK );
			}
			memcpy( szTerm, szAux, min( iTermSize, lCurrRepetSize ) );
			szTerm[ min( iTermSize, lCurrRepetSize ) ] = '\0';

			// vamos "pre-normalizar" a string
			pBase->PreStandardize( szTerm );

			// Vamos setar o termo e o status do parser
			LT_SetParserTerm( szTerm );
			LT_SetParserStatus( WORD_END );
			lRepetPos = strlen( szTerm );
			iRet = LBS_OK;
		} else {
			LT_SetParserStatus( PROCESS_END );
			lRepetPos = 0L;
		}
		break;

	case DATE_FIELD:
		if( lRepetPos == 0L ){
			C_Date	cdDate;

			// Pega a repeticao corrente
			pBase->GetFieldRepetition( uiFieldId, -1, &cdDate );

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
			pBase->GetFieldRepetition( uiFieldId, -1, &ctTime );

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

	default:
		return( LBSE_INVALIDFIELDTYPE );

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
LBSC_EntParser::LT_ParserTerminate()
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
LBSC_EntParser::LT_ParserResetStatus()
{
	LT_SetParserStatus( PROCESS_END );

	return LBS_OK;
}




