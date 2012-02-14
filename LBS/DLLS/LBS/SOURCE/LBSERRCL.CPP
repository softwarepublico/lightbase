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
// Module: LBSERRCL.CPP
// Description:
//
//	LBSC_Error private class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//		Alessandro A. Jatoba'
//
// Last update: 16/01/96
//

#ifndef _LBSERRCL_H_
#include	<lbserrcl.h>
#endif
#ifndef	_LBSERRTB_H_
#include	<lbserrtb.h>
#endif
#ifndef	_LBSERROR_H_
#include	<lbserror.h>
#endif
#ifndef	_WINDOWS_
#include	<windows.h>
#endif
#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined __STDIO_H && !defined _INC_STDIO
#include	<stdio.h>
#endif
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

// para internacionalizacao
extern	AppParmsMngr	*_pcInter;

char	LBSC_Error::szStaticInterMsg[ MAXERRORMSGSIZE ];

/***
***/
LBSC_Error::LBSC_Error()
{
	szInterMsg[ 0 ] = '\0';
	iErrNum = 0;
}

/***
	LBSC_Error destructor
***/
LBSC_Error::~LBSC_Error()
{
}

/***
***/
void
LBSC_Error::SetError( int iErrNumPar )
{
	// se o erro for negativo, tudo bem, ja' eh um erro LBS;
	// se o erro for positivo, eh porque eh um erro de alguma
	// biblioteca que foi setado e precisa ser convertido para
	// um erro LBS.
	
	if( iErrNumPar > 0 ){
		// HTTP Errors
		switch( iErrNumPar ){
		case 301:	// Operation interrupted
			iErrNum = LBSE_HTTPOPINTERRUPTED;
			break;

		case 302:	// Can't open AttachedFile
			iErrNum = LBSE_HTTPCANTOPENATT;
			break;

		case 151:	// HTTP protocol error.  The error message has the server response.
			iErrNum = LBSE_HTTPPROTOCOLERROR;
			break;

		case 152:	// No server specified in URL
			iErrNum = LBSE_HTTPNOSERVERINURL;
			break;

		case 153:	// Specified URLScheme is invalid.
			iErrNum = LBSE_HTTPINVALIDURLSCHEME;
			break;

		default:
			if( iErrNumPar >= 10004 && iErrNumPar <= 11004 ){
				// Winsock Errors
				iErrNum = LBSE_HTTPURLNOTFOUND;
			}
		}
	} else {
		iErrNum = iErrNumPar;
	}
}

/***
***/
void
LBSC_Error::SetErrorDesc( const char *szErrDesc )
{
	memset( (void*) szInterMsg, 0, MAXERRORMSGSIZE );

	if( szErrDesc ){
		strncpy( szInterMsg, szErrDesc, (MAXERRORMSGSIZE-1) );
	}
}


/***
***/
int
LBSC_Error::LastError()
{
	return( iErrNum );
}

/***
***/
const char *
LBSC_Error::LastErrorDesc()
{
	char	szMsg[ 255 ];
	char	*szErrAux = NULL;

	// se o erro for positivo, entao nao eh um erro LBS e
	// a respectiva mensagem ja' esta' setada em szInterMsg;
	// se o erro for negativo, ai' sim precisamos obter a
	// mensagem adequada.

	if( iErrNum <= 0 ){

		if ( ((-iErrNum) - LBSERROR_OFFSET) >= ERRORTABLESIZE ){	// epa, tem algo eerado...
			if ( iErrNum < -2*(LBSERROR_OFFSET) ) {
				// gambiarra pra tratar chave unica: a indicacao do id do campo que deu erro
				// de chave unica esta no proprio codigo do erro
				iErrNum = LBSE_DUPKEY;
			} else {
				strcpy( szInterMsg, "ERRORTABLE_OVERFLOW" );
				return( (const char*) szInterMsg );
			}
		}

		sprintf( szMsg, "LBSERR_%d", iErrNum == 0 ? iErrNum : ((-iErrNum) - LBSERROR_OFFSET) );
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szErrAux = _pcInter->GetGenMsgsAppVar( szMsg );
		}
		char	szAux[ MAXERRORMSGSIZE ];
		if( iErrNum == LBSE_HTTPPROTOCOLERROR ){
			// o conteudo de szInterMsg eh a mensagem de erro que veio
			// do http server. Vamos guarda-la em uma variavel temporaria.
			strncpy( szAux, szInterMsg, (MAXERRORMSGSIZE-1) );
		}
		memset( (void*) szInterMsg, 0, MAXERRORMSGSIZE );
		if( !szErrAux ){
			// deu pau na internacionalizacao. vamos retornar o conteudo da
			// tabela interna
			strncpy( szInterMsg, _LBS_ErrorTable[ iErrNum == 0 ? iErrNum : ((-iErrNum) - LBSERROR_OFFSET) ], (MAXERRORMSGSIZE-1) );
		} else {
			// conseguimos carregar a mensagem de erro do .ini
			strncpy( szInterMsg, szErrAux, (MAXERRORMSGSIZE-1) );
			delete szErrAux;
		}
		if( iErrNum == LBSE_HTTPPROTOCOLERROR ){
			// concatenar...
			if( strlen( szInterMsg ) < (MAXERRORMSGSIZE-1) ){
				strcat( szInterMsg, " " );
				strncpy( szInterMsg + strlen( szInterMsg ), szAux, (MAXERRORMSGSIZE-1) - strlen( szInterMsg ) );
			}
		}
	}
	return( (const char*) szInterMsg );
}


/**********************************************************
// Function name	: LBSC_Error::LastErrorDesc
// Description	    : 
// Return type		: const char* 
// Argument         : int iNumOfError
**********************************************************/
const char* LBSC_Error::LastErrorDesc( int iNumOfError )
{
	// este metodo eh static e serve para retornar a descricao
	// de um determinado erro.
	// nao serve para codigos de erro que nao sejam LBS.

	char	szMsg[ 255 ];
	char	*szErrAux = NULL;

	if( (iNumOfError <= 0) && (iNumOfError > SOCKERROREND) ){
		sprintf( szMsg, "LBSERR_%d", iNumOfError == 0 ? iNumOfError : ((-iNumOfError) - LBSERROR_OFFSET) );
		if( _pcInter && _pcInter->BuildStatus == CHECKISOK ){
			szErrAux = _pcInter->GetGenMsgsAppVar( szMsg );
		}
		memset( (void*) szStaticInterMsg, 0, MAXERRORMSGSIZE );
		if( !szErrAux ){
			// deu pau na internacionalizacao. vamos retornar o conteudo da
			// tabela interna
			strncpy( szStaticInterMsg, _LBS_ErrorTable[ iNumOfError == 0 ? iNumOfError : ((-iNumOfError) - LBSERROR_OFFSET) ], (MAXERRORMSGSIZE-1) );
		} else {
			// conseguimos carregar a mensagem de erro do .ini
			strncpy( szStaticInterMsg, szErrAux, (MAXERRORMSGSIZE-1) );
			delete szErrAux;
		}
	} else {
		szStaticInterMsg[ 0 ] = '\0';
	}
	return( (const char*) szStaticInterMsg );
}


/***
	PUBLIC
	Metodo LastErrorStatic
	Obtem o ultimo erro, acessando uma variavel estatica (para casos
	em que nao se tenha como acessar o objeto diretamente) Usado apenas 
	pelos stubs de rede e implementado de forma "dummy" aqui para manter a mesma API.

	Parameters:

	Return:
		- sempre LBS_OK (aqui no LBS).

	Comments:
		- 
***/
int 
LBSC_Error::LastErrorStatic()
{
	return LBS_OK;
}

