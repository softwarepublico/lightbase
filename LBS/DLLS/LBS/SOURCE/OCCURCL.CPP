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
// Module: OCCURCL.CPP
//	LBSC_Occurrence class methods
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last revision: 02/09/94
//


#ifndef	_OCCURRENCE_H_
#include	<occurcl.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif

#ifdef __BORLANDC__
#pragma warn -par
#endif

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/***
	Construtor

	Parameters:

	Return:

	Comments:

***/
LBSC_Occurrence::LBSC_Occurrence()
{
	pltcOc = new LTC_OCCURRENCE;
}


/***
	LBSC_Occurrence	Destructor

	Parameters:

	Return:

	Comments:

***/
LBSC_Occurrence::~LBSC_Occurrence()
{
	if( pltcOc ){
		delete pltcOc;
	}
}

/***
***/
LBSC_Occurrence::LBSC_Occurrence( LTC_OCCURRENCE *pltcOc )
{
	pltcOc = new LTC_OCCURRENCE(
		pltcOc->LT_GetTerm(),
		pltcOc->LT_GetSet(),
		pltcOc->LT_GetGroup(),
		pltcOc->LT_GetSubGroup(),
		pltcOc->LT_GetParagraph(),
		pltcOc->LT_GetSentence(),
		pltcOc->LT_GetSequence()
		);
}


/***
***/
LBSC_Occurrence::LBSC_Occurrence( CHARTYPE 	*pctTerm,
				 TUFOURBYTES	tufbSet,
				 TUTWOBYTES	tutbGroup,
				 TUTWOBYTES	tutbSubGroup,
				 TUTWOBYTES	tutbParagraph,
				 TUTWOBYTES	tutbSentence,
				 TUTWOBYTES	tutbSequence )
{
	pltcOc = new LTC_OCCURRENCE(
		pctTerm,
		tufbSet,
		tutbGroup,
		tutbSubGroup,
		tutbParagraph,
		tutbSentence,
		tutbSequence
	);
}


/***
	Metodo Compare
	Compara um objeto LBSC_Occurrence com o corrente

	Parameters:
		- plbscoOtherOc
		- iCompType

	Return:
		- resultado da comparacao

	Comments:

***/
int
LBSC_Occurrence::Compare( LBSC_Occurrence *plbscoOtherOc, int iCompType = 0 )
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}

// $$$ nao estamos comparando o termo

	LTC_FISICOCCURRENCE	ltcfoAux( plbscoOtherOc->GetRecord(),
					  plbscoOtherOc->GetField(),
					  plbscoOtherOc->GetRepetition(),
					  plbscoOtherOc->GetParagraph(),
					  plbscoOtherOc->GetPhrase(),
					  plbscoOtherOc->GetSequence() );

	return( pltcOc->Compare( &ltcfoAux ) );
}



/***
	Metodo GetRecord
	Retorna o numero do registro referenciado pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero do registro

	Comments:

***/
long
LBSC_Occurrence::GetRecord()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetSet() );
}



/***
	Metodo GetField
	Retorna o numero do campo referenciado pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero do campo

	Comments:

***/
int
LBSC_Occurrence::GetField()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetGroup() );
}



/***
	Metodo GetRepetition
	Retorna o numero da repeticao referenciada pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero da repeticao

	Comments:

***/
int
LBSC_Occurrence::GetRepetition()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetSubGroup() );
}



/***
	Metodo GetParagraph
	Retorna o numero do paragrafo referenciado pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero do paragrafo

	Comments:

***/
int
LBSC_Occurrence::GetParagraph()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetParagraph() );
}



/***
	Metodo GetPhrase
	Retorna o numero da frase referenciada pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero da frase

	Comments:

***/
int
LBSC_Occurrence::GetPhrase()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetSentence() );
}



/***
	Metodo GetSequence
	Retorna o numero da sequencia referenciado pela Ocorrencia

	Parameters:
		-

	Return:
		- Numero da sequencia

	Comments:

***/
int
LBSC_Occurrence::GetSequence()
{
	if( !pltcOc ){
		return( LBSE_ERROR );
	}
	return( pltcOc->LT_GetSequence() );
}



/***
	Metodo GetTerm
	Retorna o termo referenciado pela Ocorrencia

	Parameters:
		-

	Return:
		- Termo (string)

	Comments:

***/
const char *
LBSC_Occurrence::GetTerm()
{
	if( !pltcOc ){
		return( NULL );
	}
	return( pltcOc->LT_GetTerm() );
}



/***
	Operador =
	Realiza a operacao de igualdade entre dois objetos

	Parameters:
		-

	Return:
		- Uma "derreferencia" que pode ser usada para construir
		  expressoes do tipo a = b = c, onde a, b e c sao
		  objetos desta classe

	Comments:

***/
LBSC_Occurrence	&
LBSC_Occurrence::operator = ( LBSC_Occurrence &lbscOcAux )
{
	if( pltcOc ){
		LTC_OCCURRENCE	*pAux = new LTC_OCCURRENCE(
					(CHARTYPE*) lbscOcAux.GetTerm(),
					lbscOcAux.GetRecord(),
					lbscOcAux.GetField(),
					lbscOcAux.GetRepetition(),
					lbscOcAux.GetParagraph(),
					lbscOcAux.GetPhrase(),
					lbscOcAux.GetSequence()
					);
		if( pAux ){
			if( pltcOc ){
				delete pltcOc;
			}
			pltcOc = pAux;
		}
	}
	return( *this );
}


/***
	Operador =
	Realiza a operacao de igualdade entre dois objetos

	Parameters:
		-

	Return:
		- Uma "derreferencia" que pode ser usada para construir
		  expressoes do tipo a = b = c, onde a, b e c sao
		  objetos desta classe

	Comments:

***/
LBSC_Occurrence	&
LBSC_Occurrence::operator = ( LTC_OCCURRENCE &ltcOcAux )
{
	if( pltcOc ){
		LTC_OCCURRENCE	*pAux = new LTC_OCCURRENCE(
					ltcOcAux.LT_GetTerm(),
					ltcOcAux.LT_GetSet(),
					ltcOcAux.LT_GetGroup(),
					ltcOcAux.LT_GetSubGroup(),
					ltcOcAux.LT_GetParagraph(),
					ltcOcAux.LT_GetSentence(),
					ltcOcAux.LT_GetSequence()
					);
		if( pAux ){
			delete pltcOc;
			pltcOc = pAux;
		}
	}
	return( *this );
}

/***
	Operador =
	Retorna o objeto LTC_OCCURRENCE do objeto corrente

	Parameters:
		-

	Return:
		- 

	Comments:
		-

***/

LBSC_Occurrence::operator LTC_OCCURRENCE * ()
{
	return( pltcOc );
}




#ifdef __BORLANDC__
#pragma warn +par
#endif


