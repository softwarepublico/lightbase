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

#include <windows.h>
#ifndef	_TE_TOKEN_H_
#include <te_token.h>
#endif
#include <stdlib.h>
#include <io.h>

#define	CFMTSIGN	"~`!@#$%^&*()-+|=-TeCfMt"
#define	ST_DATE		1
#define	ST_DATEEX	2
#define	ST_TIME		1
#define	ST_TIMEEX	2

static const char *separators = "~`#%^&*()-+={}[]:\";'<>?,./\\ \r\n\xff\x9\xb6";



/***
***/
C_TERGetToken::C_TERGetToken()
{
	tmp_pvBuffer = NULL;
	pvInitBuffer = NULL;
	iInitBufSize = 0;
	iFmtSignLen = strlen( CFMTSIGN );
}

/***
***/
C_TERGetToken::~C_TERGetToken()
{
}

/***
***/
int
C_TERGetToken::GetToken( const void *pvBuffer, int iBufSize, char *pszRetorno, int *piStatus )
{
	char	*pvInitWord;
	BOOL	ponto;

	if (pvBuffer) {          // Se chamando pela primeira vez, inicia o processo
		tmp_pvBuffer=pvInitBuffer=(char *)pvBuffer;
        	iInitBufSize=iBufSize;
		pvInitWord = NULL;
   	}

	pszRetorno[ 0 ] = '\0';

	// Analiza separadores.
	ponto = FALSE;
	while( strchr( separators, (BYTE)*tmp_pvBuffer ) ) {
		switch( (BYTE)*tmp_pvBuffer )
		{
		case '~':	// Possibilidade de fim de arquivo
			if( !strncmp( tmp_pvBuffer, CFMTSIGN, iFmtSignLen ) )
			{
				*piStatus=TER_TOKENDBUFFER;
				return(TER_TOKOK);
			}
			break;

		case 0xb6:
	      		tmp_pvBuffer++;
	      		*piStatus=TER_TOKPAR;
	      		return(TER_TOKOK);

		case ' ':
			if( ponto )
			{
				*piStatus=TER_TOKPHRASE;
		      		tmp_pvBuffer++;
				return(TER_TOKOK);
			}
			break;

		case '.':
      case '!':
      case '?':
			ponto = TRUE;
			break;

		default:
         if( ponto )
            ponto = FALSE;
			break;
		}
		++tmp_pvBuffer;
		if( (tmp_pvBuffer - pvInitBuffer) > iInitBufSize )
		{
			*piStatus = TER_TOKENDBUFFER;
			return (TER_TOKOK );     // bom para lb dos, que nÃo tem terminador
		}
	}

   if( ponto )
	{
		*piStatus=TER_TOKPHRASE;
		return(TER_TOKOK);
	}

	// separar uma token.

	pvInitWord = tmp_pvBuffer;
	while( TRUE ) 
	{
		// juntar a token.
		char *ptr = strchr( separators, *tmp_pvBuffer );
		if( ptr ){ // Se for separador
			if( *tmp_pvBuffer == '.' ){
				// Se for ponto tem que tomar cuidado.
				ptr = strchr( separators, *(tmp_pvBuffer+1) );
				if( ptr ){
					if( ptr - separators > 27 ){  // é fim de parágrafo ou frase.
						break;
					}
				}
				// Ver se é digito
				if( isdigit( *(tmp_pvBuffer+1) ) ){
					++tmp_pvBuffer;
					continue;
				} else {
					break;
				}
			} else {
				if( *tmp_pvBuffer == '/' ){
					// verificar se eh data
					int	iStatus;
					int	iNumChars = EhData( tmp_pvBuffer, iStatus );
					if( iNumChars > 0 ){
						tmp_pvBuffer += iNumChars;
					}
					break;
				} else {
					if( *tmp_pvBuffer == ':' ){
						// verificar se eh hora
						int	iStatus;
						int	iNumChars = EhHora( tmp_pvBuffer, iStatus );
						if( iNumChars > 0 ){
							tmp_pvBuffer += iNumChars;
						}
						break;
					} else {
						break;
					}
				}
			}
		} else {
			++tmp_pvBuffer;
		}
		if( (tmp_pvBuffer - pvInitBuffer) > iInitBufSize ){
			break;
		}
	}

	if( pvInitWord == tmp_pvBuffer )  // situação esdrúxula
	{
		*piStatus = TER_TOKENDBUFFER;
		return(TER_TOKERROR);
	}

	*piStatus=TER_TOKWORD;

	memcpy( pszRetorno, pvInitWord, tmp_pvBuffer - pvInitWord );
	memset( pszRetorno + (tmp_pvBuffer - pvInitWord), 0, 1 );

	return(TER_TOKOK);
}


/***
	Retorna 0 se o szToken nao caracterizar uma data;
	retorna >0 se o szToken caracterizar uma data;
	iStatus indica (no retorno):
	- ST_DATE	para data valida
	- ST_DATEEX para data seguida de um token qualquer,
				sem separador entre eles (ex.: 12/12/12caca)
***/
int	
C_TERGetToken::EhData( char *szToken, int &iStatus )
{
	char	*szStart = szToken;
	char	*szAux = szToken;
	char	cPara = (char) 182;

	iStatus = ST_DATE;

	// o szToken aponta para a primeira barra depois de algum numero.
	// temos que voltar para o inicio da cadeia para checarmos se o
	// token eh uma data ou nao.
	while( ((*(--szStart)) != cPara) && isdigit( *szStart ) ){
		;
	}
	++szStart;

	// agora szStart aponta para o inicio de uma cadeia que 
	// pode ser uma data.
	while( ((*(++szAux)) != cPara) && isdigit( *szAux ) ){
		;
	}
	if( *szAux != '/' ){
		// nao eh data
		return( 0 );
	}
	while( ((*(++szAux)) != cPara) && isdigit( *szAux ) ){
		;
	}
	if( ((*(szAux)) != cPara) && isalpha( *szAux ) ){
		while( ((*(++szAux)) != cPara) && isalpha( *szAux ) ){
			;
		}
		iStatus = ST_DATEEX;
		return( szAux - szToken );
	}
	if( *szAux == ' ' || *szAux == '\t' || strchr( separators, *szAux ) ){
		int	iLen = szAux - szStart;
		if( iLen >= 5 && iLen <= 10 ){	// tamanhos minimo e maximo para data
			// ok. vamos ver se bate com alguma possivel mascara de data.
			if( (szStart[1] == '/' && szStart[3] == '/') ||		// x/x/...
				(szStart[1] == '/' && szStart[4] == '/') ||		// x/xx/...
				(szStart[2] == '/' && szStart[4] == '/') ||		// xx/x/...
				(szStart[2] == '/' && szStart[5] == '/') ||		// xx/xx/...
				(szStart[4] == '/' && szStart[6] == '/') ||		// xxxx/x/...
				(szStart[4] == '/' && szStart[7] == '/') ){		// xxxx/xx/...
				// eh uma data
				iStatus = ST_DATE;
				return( szAux - szToken );
			}
		}
	}
	return( 0 );
}


/***
	Retorna 0 se o szToken nao caracterizar uma hora;
	retorna >0 se o szToken caracterizar uma hora;
	iStatus indica (no retorno):
	- ST_TIME	para hora valida
	- ST_TIMEEX para hora seguida de um token qualquer,
				sem separador entre eles (ex.: 12:12caca)
***/
int	
C_TERGetToken::EhHora( char *szToken, int &iStatus )
{
	char	*szStart = szToken;
	char	*szAux = szToken;
	char	cPara = (char) 182;

	iStatus = ST_TIME;

	// o szToken aponta para o primeiro ':' depois de algum numero.
	// temos que voltar para o inicio da cadeia para checarmos se o
	// token eh uma hora ou nao.
	while( ((*(--szStart)) != cPara) && isdigit( *szStart ) ){
		;
	}
	++szStart;

	// agora szStart aponta para o inicio de uma cadeia que 
	// pode ser uma hora.
	while( ((*(++szAux)) != cPara) && isdigit( *szAux ) ){
		;
	}
	if( ((*(szAux)) != cPara) && isalpha( *szAux ) ){
		while( ((*(++szAux)) != cPara) && isalpha( *szAux ) ){
			;
		}
		iStatus = ST_TIMEEX;
		return( szAux - szToken );
	}
	if( *szAux == ' ' || *szAux == '\t' || strchr( separators, *szAux ) ){
		int	iLen = szAux - szStart;
		if( iLen >= 3 && iLen <= 5 ){	// tamanhos minimo e maximo para hora
			// ok. vamos ver se bate com alguma possivel mascara de data.
			if( (szStart[1] == ':' ) ||		// x:x...
				(szStart[2] == ':' ) ){		// xx:x...
				// eh uma data
				iStatus = ST_TIME;
				return( szAux - szToken );
			}
		}
	}
	return( 0 );
}


