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
// Module: STRPARCL.CPP
// Description:
//
//	LBSC_EntParser class methods file. This parser is used only by
//	IndexString method. It returns a string specified by application
//	only once.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 26/07/95
//



#if !defined __STDLIB_H && !defined _INC_STDLIB
#include	<stdlib.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef _STRPARCL_H_
#include	<strparcl.h>
#endif
#ifndef _LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#ifndef _STRDUP_H_
#include	<Strdup.h>
#endif

#ifdef __BORLANDC__
#pragma warn -par
#endif

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/***
	Metodo LBSC_StrParser
	Construtor

	Parameters:
		- szStr	-> string a ser retornada pelo parser quando
			   o LT_ParserProcess for chamado

	Return:
		-

	Comments:
		-

***/

LBSC_StrParser::LBSC_StrParser( char *szStr )
{
	// precisamos fazer uma copia de szStr para podermos
	// setar o termo com LT_SetParserTerm no metodo
	// LT_ParserProcess.
	szBuffer = Strdup( szStr );
	LT_SetParserTerm( NULL );
	LT_SetParserStatus( 0 );
}
#ifdef __BORLANDC__
#pragma warn .par
#endif

/***
	Metodo ~LBSC_StrParser
	Destrutor

	Parameters:
		-

	Return:
		-

	Comments:
		-

***/
LBSC_StrParser::~LBSC_StrParser()
{
	if( szBuffer ){
		delete szBuffer;
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
		-

***/
int
LBSC_StrParser::LT_ParserInit()
{
	if( szBuffer ){
		return( LBS_OK );
	}
	return( LBSE_ERROR );
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
		-

***/
int
LBSC_StrParser::LT_ParserProcess(LTC_OCCURRENCE *pcoOccurrence)
{
	static	long	lRepetPos = 0L;

	if( !szBuffer ){
		return( LBSE_ERROR );
	}
	if( !lRepetPos ){
		LT_SetParserTerm( szBuffer );
		LT_SetParserStatus( WORD_END );
		lRepetPos += strlen( szBuffer );
	} else {
		LT_SetParserTerm( NULL );
		LT_SetParserStatus( PROCESS_END );
		lRepetPos = 0L;
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
		-

***/
int
LBSC_StrParser::LT_ParserTerminate()
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
LBSC_StrParser::LT_ParserResetStatus()
{
	LT_SetParserStatus( PROCESS_END );

	return LBS_OK;
}


