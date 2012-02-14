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
// Module: LTBASE.CPP
// Description:
//
//	LBSC_BASE public class methods file.
//	This file implements some methods that need to be passed
//	from LightText API to LBS applications.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 10/03/95
//


#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#include	<lt.h>		// $$$ GREEN
#ifndef   APPMNGRCL
#include	<appmngr.h>
#endif


#define	max( a, b )	(((a) > (b)) ? (a) : (b))

#ifdef	_DEBUG_CRIT_SECT_

#define	cCS0( x, y )					cCS0( (x), (y), __FILE__, __LINE__ )
#define	cCS1( x, y )					cCS1( (x), (y), __FILE__, __LINE__ )
#define	cCS2( x, y )					cCS2( (x), (y), __FILE__, __LINE__ )
#define	cCS3( x, y )					cCS3( (x), (y), __FILE__, __LINE__ )
#define	cCS4( x, y )					cCS4( (x), (y), __FILE__, __LINE__ )
#define	cCS5( x, y )					cCS5( (x), (y), __FILE__, __LINE__ )
#define	cCS6( x, y )					cCS6( (x), (y), __FILE__, __LINE__ )
#define	cCS7( x, y )					cCS7( (x), (y), __FILE__, __LINE__ )
#define	cCS8( x, y )					cCS8( (x), (y), __FILE__, __LINE__ )
#define	cCS9( x, y )					cCS9( (x), (y), __FILE__, __LINE__ )
#define	cCS10( x, y )					cCS10( (x), (y), __FILE__, __LINE__ )
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log


extern	AppParmsMngr	*_pcInter;

/**************************************************************************/
/*********************	EXCHANGE OPERATOR	***************************/
/**************************************************************************/

/***
	PUBLIC
	Metodo ExchangeOperator
	Esta funcao altera mnemonicos para os operadores ou localizadores das
	expressoes, permitindo que o usuario utilize os operadores no seu
	idioma e da maneira com a qual estiver melhor familiarizado. 


	Parameters:
		-szNewOp: Apontador para uma cadeia de caracteres, terminada
		 com '\0', contendo os operadores e/ou localizadores seguidos de seu respectivo mnemonico. 


	Return:
	       - Retorna um apontador para uma cadeia de caracteres, contendo
		os mnemonicos anteriormente setados ou NULL em caso de erro.


	Comments:
		- Ver metodo LT_ExchangeOperator  no manual da GREEN.


***/
char *
LBSC_Base::ExchangeOperator( char *szNewOp )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ExchangeOperator") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	*szAux = GLT_Session->LT_ExchangeOperator( szNewOp );
	SetError( GLT_Session->LT_GetError() );
	return( szAux );
}



/**************************************************************************/
/***************   METODOS DE TRATAMENTO DE MASCARAS	*******************/
/**************************************************************************/

/***
	PUBLIC
	Metodo SetMask
	Define um conjunto de mascaras de reconhecimento de termos que poderao
	ser indexados como data, hora e valor. Esta definicao e feita por sistema
	de indices

	Parameters:
		- szMasks: Apontador para uma cadeia de caracteres com a
		lista de mascaras que sera setado como lista de mascara
		corrente de um determinado sistema de indices;
		- iIndex: Informa para qual indice a lista de mascaras esta
		sendo setada. Podera ser para o indice de Data (DATETREE),
		Hora (TIMETREE) ou Valor (VALUETREE).
		- iTypeOfHeaderMask: Representa o tipo de mascara que deve ser
		settada em função da lingua do produto: Portugues  valor 1 ou 
		Ingles valor 0.

	Return:
		- LBS_OK se conseguir setar ou erro.

	Comments:
        	-

***/
int
LBSC_Base::SetMask( char *szMasks, int iIndex, int iTypeOfHeaderMask )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetMask") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	if( (iIndex != DATETREE) && (iIndex != TIMETREE) && (iIndex != VALUETREE) ){
		ERETURN( LBSE_INVALIDINDEXTYPE );
	}
	if( !pltcMaskList || pltcMaskList->LT_BuildTermList( szMasks ) != LBS_OK ){
		ERETURN( LBSE_ERROR );
	}
	LTC_TERMLIST *pAux = plbscisIndexSystem->LT_SetMask( pltcMaskList, iIndex, iTypeOfHeaderMask );
	if( pAux ){
		delete pAux;
	}
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo GetMask
	Obtem a lista de mascaras setada atualmente no sistema de indices.

	Parameters:
		- iIndex: Informa o indice de onde se quer obter a lista de
		mascaras. Podera ser para o indice de Data (DATETREE), Hora
		(TIMETREE) ou Valor (VALUETREE).

	Return:
		- Uma string com a lista de mascaras ativa para aquele indice,
		separadas por branco.

	Comments:
		- Este metodo retorna um apontador para uma string que a
		aplicacao DEVE deletar quando nao quiser mais usa-la.

***/
char *
LBSC_Base::GetMask( int iIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetMask") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pOldMask;

	if( !plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	if( (iIndex != DATETREE) && (iIndex != TIMETREE) && (iIndex != VALUETREE) ){
		NRETURN( LBSE_INVALIDINDEXTYPE );
	}
	if( pltcMaskList ){
		//Início Katyusco
		int iMaskType = 1; // Portugues
		if ( _pcInter ) {
			PRODMAINPARMS *pcInterMianParms = _pcInter->GetProdMainParms();
			iMaskType = ( strcmp(pcInterMianParms->currlang, "PORTUGUES") == 0 ? 1 : 0 );
		}
		pOldMask = plbscisIndexSystem->LT_SetMask( pltcMaskList, iIndex, iMaskType );
		SetError( LBS_OK );
		return( MakeLTString( pOldMask ) );
	}
	NRETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo SaveMasks
	Salva a lista de mascaras ativa em um arquivo.

	Parameters:
		- szFileName: nome do arquivo( inclusive path ).


	Return:
		- 0 se operacao OK ou negativo caso contrario.


	Comments:
        	-

***/
int
LBSC_Base::SaveMasks( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SaveMasks") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcMaskList ){
		int	iRet = pltcMaskList->LT_SaveTermList( szFileName );
		SetError( pltcMaskList->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo LoadMasks
	Carrega a lista de mascaras a partir de um arquivo.


	Parameters:
		- szFileName: nome do arquivo( inclusive path ).


	Return:
		- 0 se operacao OK ou negativo caso contrario.


	Comments:
        	-


***/
int
LBSC_Base::LoadMasks( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LoadMasks") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcMaskList ){
		pltcMaskList->LT_DelAllTerm();
		int	iRet = pltcMaskList->LT_LoadTermList( szFileName );
		if( iRet != OK ){
			pltcMaskList->LT_DelAllTerm();
			ERETURN( LBSE_ERROR );
		}
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo ClearMasks
	Deleta a lista de mascaras.


	Parameters:


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::ClearMasks()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearMasks") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcMaskList ){
		int	iRet = pltcMaskList->LT_DelAllTerm();
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_NOMEMORY );
}


/**************************************************************************/
/***************   METODOS DE TRATAMENTO DE FONEMAS	*******************/
/**************************************************************************/

/***
	PUBLIC
	Metodo AddPhone
	Adiciona um conjunto de fonemas (szPhoneArray) no objeto LTC_PHONE. 

	Parameters:
		- szPhoneArray: String de caracteres, terminado com '\0', que
		contera as definicoes dos fonemas. Cada definicao (fonema)
		devera estar separada por um caracter branco;
		- iPhoneNumber: Representa o numero fonetico dos fonemas
		setados em szPhoneArray.

	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
        	- Exemplo: informar que as letras S e Z possuem o mesmo fonema:
		  szPhoneArray = "S Z"; iPhoneNumber = 10

***/
int
LBSC_Base::AddPhone( char *szPhoneArray, int iPhoneNumber )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddPhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pltcTermAux = new LTC_TERMLIST;
	if( !pltcTermAux ){
		ERETURN( LBSE_NOMEMORY );
	}

	if( !pltcPhone ){
		delete pltcTermAux;
		ERETURN( LBSE_NOMEMORY );
	}

	if( !plbscisIndexSystem ){
		delete pltcTermAux;
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcTermAux->LT_BuildTermList( szPhoneArray ) != LBS_OK ){
		delete pltcTermAux;
		SetError( pltcTermAux->GetError() );
		return( LBSE_ERROR );
	}

	int iRet = pltcPhone->LT_AddPhone( pltcTermAux, iPhoneNumber );

	if( iRet == 0 ){
		LTC_PHONE *pAux = plbscisIndexSystem->LT_SetPhone( pltcPhone );
		if( pAux ){
			delete pAux;
		}
		SetError( plbscisIndexSystem->GetError() );
	} else {
		SetError( pltcPhone->GetError() );
	}
	delete pltcTermAux;
	return( iRet );
}

/***
	PUBLIC
	Metodo DeletePhone
	Deleta da lista de fonemas as definicoes desejadas. Estas definicoes
	deverao estar na string szPhoneArray separadas por um espaco em branco.


	Parameters:
		- szPhoneArray: String de caracteres, terminado com '\0', que
		contera as definicoes dos fonemas. Cada definicao (fonema) devera 
		estar separada por um caracter branco;


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::DeletePhone( char *szPhoneArray )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DeletePhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pltcTermAux = new LTC_TERMLIST;
	if( !pltcTermAux ){
		ERETURN( LBSE_NOMEMORY );
	}

	if( !pltcPhone ){
		delete pltcTermAux;
		ERETURN( LBSE_NOMEMORY );
	}

	if( !plbscisIndexSystem ){
		delete pltcTermAux;
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcTermAux->LT_BuildTermList( szPhoneArray ) != LBS_OK ){
		delete pltcTermAux;
		SetError( pltcTermAux->GetError() );
		return( LBSE_ERROR );
	}

	int iRet = pltcPhone->LT_DeletePhone( pltcTermAux );

	if( iRet == 0 ){
		LTC_PHONE *pAux = plbscisIndexSystem->LT_SetPhone( pltcPhone );
		if( pAux ){
			delete pAux;
		}
		SetError( plbscisIndexSystem->GetError() );
	} else {
		SetError( pltcPhone->GetError() );
	}
	delete pltcTermAux;
	return( iRet );
}

/***
	PUBLIC
	Metodo SavePhone
	Salva em arquivo o conteudo de um objeto LTC_PHONE, gravando os
	fonemas contidos neste objeto. 


	Parameters:
		- szFileName: nome do arquivo (inclusive path).


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
        	-


***/
int
LBSC_Base::SavePhone( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SavePhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcPhone ){
		int	iRet = pltcPhone->LT_SavePhone( szFileName );
		SetError( pltcPhone->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo LoadPhone
	Carrega um objeto LTC_PHONE armazenado em arquivo, lendo os termos
	que serao adicionados no objeto .


	Parameters:
		- szFileName: nome do arquivo (inclusive path).


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::LoadPhone( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LoadPhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcPhone ){
		int	iRet = pltcPhone->LT_LoadPhone( szFileName );
		SetError( pltcPhone->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo ClearPhone
	Realiza a delecao de todas as definicoes de fonemas feita para o
	objeto LTC_PHONE. Em outras palavras, faz um limpeza geral no objeto
	sem que ele seja destruido. 

	Parameters:


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::ClearPhone()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearPhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcPhone ){
		int iRet = pltcPhone->LT_ClearPhone();
		if( iRet == 0 ){
			LTC_PHONE *pAux = plbscisIndexSystem->LT_SetPhone( NULL );
			if( pAux ){
				delete pAux;
			}
			SetError( plbscisIndexSystem->GetError() );
		} else {
			SetError( pltcPhone->GetError() );
		}
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo FindPhone
	Realiza uma pesquisa fonetica de um termo. Recebe um termo (ptctTerm)
	com parametro e devolve o numero fonetico correspondente a este termo.


	Parameters:
		- szTerm: termo;
		- szPhoneValue: 


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::FindPhone( char *szTerm, char *szPhoneValue )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::FindPhone") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcPhone ){
		int	iRet = pltcPhone->LT_FindPhone( szTerm, szPhoneValue );
		SetError( pltcPhone->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}


/**************************************************************************/
/***************  METODOS DE TRATAMENTO DE NORMALIZADORES *****************/
/**************************************************************************/

/***
	PUBLIC
	Metodo SetStandardizer
	Define um conjunto de caracteres que formarao a tabela de normalizadores
	para o sistema de indices de uma base.


	Parameters:
		- ptctStandardizerArray: Apontador para uma cadeia de caracteres,
		terminada com '\0', contendo os caracteres normalizadores.


	Return:
	       - A tabela de normalizacao atual. (Use LastError() para verificar
	         a ocorrencia de algum erro)

	Comments:
		- A tabela setada por este metodo E' persistente. Ou seja, NAO tem
		  que ser setada toda vez que a base for aberta.
		- O parametro passado deve conter os 256 caracteres da tabela ASCII
		  de acordo com a necessidade de normalizacao da aplicacao. Interna-
		  mente, a LT possui uma tabela ASCII com os 256 caracteres normais,
		  que conhecemos (A, a, ç, ã, ...). Para normalizar os termos que
		  serao indexados/recuperados, eh necessario definir uma nova tabela
		  ASCII paralela aa tabela interna. Assim, para cada caracter da 
		  tabela interna, havera' um correspondente na tabela de normalizacao
		  setada por este medoto. TODOS OS 256 CARACTERES DEVERAO SER PASSADOS
		  COMO PARAMETRO.

***/
char *
LBSC_Base::SetStandardizer( char *szStandardizerArray )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetStandardizer") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if ( !szStandardizerArray ) {
		// temos que setar com o default se nao vier nada
		szStandardizerArray = DEFAULTSTANDARDIZERARRAY;
	}

	char *szAux = plbscisIndexSystem->LT_SetStandardizer( szStandardizerArray );
	int iRet = plbscisIndexSystem->GetError();
	SetError( iRet );
	return( szAux );
}


/***
	PUBLIC
	Metodo GetStandardizer
	Obtem o conjunto atual de caracteres de normalizacao.


	Parameters:
		- 


	Return:
	       - A tabela de normalizacao atual. (Use LastError() para verificar
	         a ocorrencia de algum erro)

	Comments:
		- O retorno eh uma string com 256 caracteres ou NULL.
		- NULL nao significa erro. Para saber se houve erro, eh necessario
		  consultar LastError().
		- A aplicacao DEVE deletar a string quando nao precisar mais dela.

***/
char *
LBSC_Base::GetStandardizer()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetStandardizer") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	// a GREEN nao oferece um metodo para sabermos qual o conjunto de caracteres
	// atual. Para saber essa informacao, setamos o conjunto para NULL e com isso
	// conseguimos obter o conjunto atual. Depois, e' so' setar novamente o
	// conjunto de normalizacao.
	char *szRet = plbscisIndexSystem->LT_SetStandardizer( NULL );
	char *szAux = plbscisIndexSystem->LT_SetStandardizer( szRet );
	if( szAux ){
		delete szAux;
	}
	SetError( plbscisIndexSystem->GetError() );
	return( szRet );
}




/***
	PUBLIC
	Metodo Standardize
	Normaliza a string passada no primeiro parametro, devolvendo uma
	outra string com o resultado da operacao.

	Parameters:
		- szContent: Apontador para uma cadeia de caracteres, contendo
		  a string a ser normalizada;
		- szDestination: Apontador para um buffer para armazenar o
		  resultado da normalizacao;
		- iSize:Tamanho da cadeia apontada por szContent;
	
	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		- Este metodo nao realiza nenhuma operacao sobre o sistema de indices.
		  Ele eh simplesmente um servico oferecido pela API para normalizar
		  strings.


***/
int
LBSC_Base::Standardize( char *szContent, char *szDestination, int iSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Standardize") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	int	iRet = plbscisIndexSystem->LT_Standardize( szContent, szDestination, iSize );
	SetError( plbscisIndexSystem->GetError() );
	return( iRet );
}


/**************************************************************************/
/***************   METODOS DE TRATAMENTO DE SINONIMOS	*******************/
/**************************************************************************/

/***
	PUBLIC
	Metodo AddSynonym
	Adiciona um conjunto de sinonimos (szSynonymArray) para o termo ptctTerm

	Parameters:
		- szTerm: String de caracteres, terminado com '\0', indicando
		qual e o termo que possui o conjunto de sinonimos;
		- szSynonymArray: String de caracteres, terminado com '\0',
		que contera as diversas palavras que sao sinonimos do termo
		passado como parametro. As palavras desta string deverao estar
		separadas por um caracter branco;
		- iFlag: Flag indicativo para a utilizacao, ou nao, de
		bidirecionamento ou associatividade.

	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::AddSynonym( char *szTerm, char *szSynonymArray, int iFlag )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pltcTermAux = new LTC_TERMLIST;
	if( !pltcTermAux ){
		ERETURN( LBSE_NOMEMORY );
	}

	if( !pltcSynonym ){
		delete pltcTermAux;
		ERETURN( LBSE_NOMEMORY );
	}

	if( !plbscisIndexSystem ){
		delete pltcTermAux;
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcTermAux->LT_BuildTermList( szSynonymArray ) != LBS_OK ){
		SetError( pltcTermAux->GetError() );
		delete pltcTermAux;
		return( LBSE_ERROR );
	}

	int iRet = pltcSynonym->LT_AddSynonym( szTerm, pltcTermAux, iFlag );

	if( iRet == 0 ){
		LTC_SYNONYM *pAux = plbscisIndexSystem->LT_SetSynonym( pltcSynonym );
		if( pAux ){
			delete pAux;
		}
		SetError( plbscisIndexSystem->GetError() );
	} else {
		SetError( pltcSynonym->GetError() );
	}
	delete pltcTermAux;
	return( iRet );
}

/***
	PUBLIC
	Metodo DeleteSynonym
	Deleta do objeto LTC_SYNONYM, um conjunto de sinonimos (szSynonymArray)
	anteriormente definido para szTerm. Observe que serao deletadas das
	definicoes dos sinonimos apenas as palavras passadas em szSynonymArray.


	Parameters:
		- szTerm: String de caracteres, terminado com '\0', indicando
		qual e o termo que possui o conjunto de sinonimos;
		- szSynonymArray: String de caracteres, terminado com '\0',
		que contera as diversas palavras que sao sinonimos do termo
		passado como parametro. As palavras desta string deverao estar
		separadas por um caracter branco;
		- iFlag: Flag indicativo para a utilizacao, ou nao, de
		bidirecionamento ou associatividade.


	Return:
		- 0 se operacao OK ou negativo caso contrario.


	Comments:
        	-

***/
int
LBSC_Base::DeleteSynonym( char *szTerm, char *szSynonymArray, int iFlag )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DeleteSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pltcTermAux = new LTC_TERMLIST;
	if( !pltcTermAux ){
		ERETURN( LBSE_NOMEMORY );
	}

	if( !plbscisIndexSystem ){
		delete pltcTermAux;
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcTermAux->LT_BuildTermList( szSynonymArray ) != LBS_OK ){
		SetError( pltcTermAux->GetError() );
		delete pltcTermAux;
		return( LBSE_ERROR );
	}

	if( pltcSynonym ){
		int iRet = pltcSynonym->LT_DeleteSynonym( szTerm, pltcTermAux, iFlag );
		if( iRet == 0 ){
			LTC_SYNONYM *pAux = plbscisIndexSystem->LT_SetSynonym( pltcSynonym );
			if( pAux ){
				delete pAux;
			}
			SetError( plbscisIndexSystem->GetError() );
		} else {
			SetError( pltcSynonym->GetError() );
		}
		delete pltcTermAux;
		return( iRet );
	}
	delete pltcTermAux;
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo SaveSynonym
	Salva em arquivo o conteudo de um objeto LTC_SYNONYM, gravando os
	termos e seus sinonimos contidos neste objeto.


	Parameters:
		- szFileName: nome do arquivo.


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::SaveSynonym( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SaveSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcSynonym ){
		int	iRet = pltcSynonym->LT_SaveSynonym( szFileName );
		SetError( pltcSynonym->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo LoadSynonym
	Carrega um objeto LTC_SYNONYM armazenado em arquivo, lendo os termos
	e seus sinonimos que serao adicionados no objeto .


	Parameters:
		-szFileName: nome do arquivo.


	Return:
		- 0 se operacao OK ou negativo caso contrario.

	Comments:
        	-

***/
int
LBSC_Base::LoadSynonym( char *szFileName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LoadSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( pltcSynonym ){
		int	iRet = pltcSynonym->LT_LoadSynonym( szFileName );
		SetError( pltcSynonym->GetError() );
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo ClearSynonym
	Realiza a delecao de todas as definicoes de sinonimos feita para o
	objeto LTC_SYNONYM.

	Parameters:
		-

	Return:
		0 se operacao OK ou negativo caso contrario.

	Comments:
		-

***/
int
LBSC_Base::ClearSynonym()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ClearSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	if( pltcSynonym ){
		int iRet = pltcSynonym->LT_ClearSynonym();
		if( iRet == 0 ){
			LTC_SYNONYM *pAux = plbscisIndexSystem->LT_SetSynonym( NULL );
			if( pAux ){
				delete pAux;
			}
			SetError( plbscisIndexSystem->GetError() );
		} else {
			SetError( pltcSynonym->GetError() );
		}
		return( iRet );
	}
	ERETURN( LBSE_NOMEMORY );
}

/***
	PUBLIC
	Metodo FindSynonym
	Realiza a pesquisa dos sinonimos de um termo. Recebe um termo (ptctTerm)
	como parametro e devolve um conjunto de sinonimos para este termo.


	Parameters:
		- szTerm: termo.

	Return:
		Retorna um apontador para uma cadeia de caracteres terminada
		com '\0', que contem os sinonimos do termo passado como
		parametro, ou NULL em caso de erro.

	Comments:
		-

***/
char *
LBSC_Base::FindSynonym( char *szTerm )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::FindSynonym") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_TERMLIST	*pOldSynonym;

	if( pltcSynonym ){
		pOldSynonym = pltcSynonym->LT_FindSynonym( szTerm );
		return( MakeLTString( pOldSynonym ) );
	}
	NRETURN( LBSE_NOMEMORY );
}



/**************************************************************************/
/***************   METODOS PARA BATIMENTOS DE LO'S	*******************/
/**************************************************************************/


/***
	PUBLIC
	Metodo OLAnd
	Faz um batimento AND entre duas listas de ocorrencias
        e gera uma terceira lista

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle1 : handle da primeira LO
		- iHandle2 : handle da segunda LO

	Return:
		- o handle da LO gerada ou um erro (valor negativo)

	Comments:
        	- a LO gerada NAO se torna a corrente
                  (ela nao eh habilitada)

***/
int
LBSC_Base::OLAnd( const LBSC_Ticket *lbscTicket, int iHandle1, int iHandle2 )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OLAnd") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	return( LogicalOp( OL_AND, iHandle1, iHandle2 ) );
}


/***
	PUBLIC
	Metodo OLOr
	Faz um batimento OR entre duas listas de ocorrencias
        e gera uma terceira lista

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle1 : handle da primeira LO
		- iHandle2 : handle da segunda LO

	Return:
		- o handle da LO gerada ou um erro (valor negativo)

	Comments:
        	- a LO gerada NAO se torna a corrente
                  (ela nao eh habilitada)

***/
int
LBSC_Base::OLOr( const LBSC_Ticket *lbscTicket, int iHandle1, int iHandle2 )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OLOr") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	return( LogicalOp( OL_OR, iHandle1, iHandle2 ) );
}


/***
	PUBLIC
	Metodo OLXor
	Faz um batimento XOR entre duas listas de ocorrencias
        e gera uma terceira lista

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle1 : handle da primeira LO
		- iHandle2 : handle da segunda LO

	Return:
		- o handle da LO gerada ou um erro (valor negativo)

	Comments:
        	- a LO gerada NAO se torna a corrente
                  (ela nao eh habilitada)

***/
int
LBSC_Base::OLXor( const LBSC_Ticket *lbscTicket, int iHandle1, int iHandle2 )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OLXor") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	return( LogicalOp( OL_XOR, iHandle1, iHandle2 ) );
}


/***
	PUBLIC
	Metodo OLNot
	Faz um batimento NOT entre duas listas de ocorrencias
        e gera uma terceira lista

	Parameters:
		- lbscTicket : o ticket de seguranca
		- iHandle1 : handle da primeira LO
		- iHandle2 : handle da segunda LO

	Return:
		- o handle da LO gerada ou um erro (valor negativo)

	Comments:
        	- a LO gerada NAO se torna a corrente
                  (ela nao eh habilitada)

***/
int
LBSC_Base::OLNot( const LBSC_Ticket *lbscTicket, int iHandle1, int iHandle2 )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::OLNot") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	return( LogicalOp( OL_NOT, iHandle1, iHandle2 ) );
}



/**************************************************************************/
/*********************	METODOS PRIVADOS	***************************/
/**************************************************************************/

/***
	PRIVATE
	- Este metodo retorna um apontador para uma string que a aplicacao
	  DEVE deletar quando nao quiser mais usa-la.
	- A string retornada contem varios termos entre aspas e separadas
	  por um espaco em branco. Por exemplo:
	  szRet = ["maria" "joao" "rio de janeiro" "sao paulo"]
	- pList e' deletado depois que a string de retorno e' montada.
	  (isso significa que o metodo que chamar este nao deve mais
	   considerar pList como um endereco valido)

***/
char *
LBSC_Base::MakeLTString( LTC_TERMLIST *pList )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::MakeLTString") );

	char	*szRet;

	if( pList ){
		// $$$ calcular o tamanho da string que precisamos
		// $$$ alocar
		int	iSize = 0;
		char	*pszAux = pList->LT_GetFirstTerm();

		while( pszAux ){
			iSize += strlen( pszAux ) + 3 * sizeof( char );
			// $$$ o 3 * sizeof( char ) eh para as duas "
			// $$$ e o espaco em branco

			pszAux = pList->LT_GetNextTerm();
		}
		if( iSize ){
			szRet = new char[ iSize ];
			char	*szTemp = new char[ iSize ];
			if( szRet && szTemp ){
				// $$$ montar a string
				szRet[ 0 ] = '\0';
				pszAux = pList->LT_GetFirstTerm();
				while( pszAux ){
					sprintf( szTemp, "%c%s%c ", '"', pszAux, '"' );
					strcat( szRet, szTemp );
					pszAux = pList->LT_GetNextTerm();
				}
			}
			if( szTemp ){
				delete szTemp;
			}
		}
		delete pList;
	}
	SetError( LBS_OK );
	return( szRet );
}


/***
	PRIVATE
	Metodo LogicalOp
	Realiza batimentos entre duas listas de ocorrencias
        e gera uma terceira lista

	Parameters:
		- iOperation : operacao a ser realizada
		- iHandle1 : handle da primeira LO
		- iHandle2 : handle da segunda LO

	Return:
		- o handle da LO gerada ou um erro (valor negativo)

	Comments:
        	- a LO gerada NAO se torna a corrente
                  (ela nao eh habilitada)

***/
int
LBSC_Base::LogicalOp( int iOperation, int iHandle1, int iHandle2 )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LogicalOp") );

	if( iHandle1 == iHandle2 ){	// nao podemos operar uma lista consigo mesma
		ERETURN( LBSE_ERROR );
	}

	// guarda a posicao da LO corrente
	int iCurr = pcOLList->GetCurrentIndex();
	// pega as listas correspondentes aos handles
	// pega a lista 1
	LBSC_Expr *pExprOrig1 = (*pcOLList)[ iHandle1 ];
	if( !pExprOrig1 || !pExprOrig1->szExpr ){
		ERETURN( LBSE_NOMEMORY );
	}
	// pega a lista 2
	LBSC_Expr *pExprOrig2 = (*pcOLList)[ iHandle2 ];
	if( !pExprOrig2 || !pExprOrig2->szExpr ){
		ERETURN( LBSE_NOMEMORY );
	}

	// temos que criar copias das listas e ordena-las em separado por registro
	// o algoritmo de refinamento depende da ordenacao por registro
	LTC_EXPR LTExpr1;
	LTC_EXPR LTExpr2;

	LTC_OCCURRENCELIST *pList1 = LTExpr1.LT_GetResultList();
	LTC_OCCURRENCELIST *pList2 = LTExpr2.LT_GetResultList();

	pExprOrig1->pOccList->CreateFullLTList( pList1 );
	pExprOrig2->pOccList->CreateFullLTList( pList2 );
	if ( !pList1 || !pList2 || pList1->LT_GetNumberOfOccurrence() == 0 ||
					pList2->LT_GetNumberOfOccurrence() == 0 ) {
		ERETURN( LBSE_NOMEMORY );
	}
	if ( !pList1->LT_ListSort() || !pList2->LT_ListSort() ) {
		ERETURN( LBSE_NOMEMORY );
	}

	// cria uma expressao LT vazia, que sera' usada para receber o
	// resultado do batimento
	LTC_EXPR LTExprResult;
	// faz o batimento
	int iRet;
	char *szNewExpr = new char [ strlen( pExprOrig1->szExpr ) +
				     strlen( pExprOrig2->szExpr ) +
				     max( strlen( GLT_Session->LT_GetSymbol( "AND" ) ),
				     max( strlen( GLT_Session->LT_GetSymbol( "OR" ) ),
				     max( strlen( GLT_Session->LT_GetSymbol( "XOR" ) ),
				     max( strlen( GLT_Session->LT_GetSymbol( "NOT" ) ), 0 )))) +
				     10 /* para os caracteres extras adicionados */ ];
	if( !szNewExpr ){
		ERETURN( LBSE_NOMEMORY );
	}
	switch( iOperation ){
	case OL_AND:
		sprintf( szNewExpr, "(%s) %s (%s)", (char*) pExprOrig1->szExpr, (char*) GLT_Session->LT_GetSymbol( "AND" ), (char*) pExprOrig2->szExpr );
		iRet = LTExprResult.LT_ExprAnd( szNewExpr, &LTExpr1, &LTExpr2 );
		break;

	case OL_OR:
		sprintf( szNewExpr, "(%s) %s (%s)", (char*) pExprOrig1->szExpr, (char*) GLT_Session->LT_GetSymbol( "OR" ), (char*) pExprOrig2->szExpr );
		iRet = LTExprResult.LT_ExprOr( szNewExpr, &LTExpr1, &LTExpr2 );
		break;

	case OL_XOR:
		sprintf( szNewExpr, "(%s) %s (%s)", (char*) pExprOrig1->szExpr, (char*) GLT_Session->LT_GetSymbol( "XOR" ), (char*) pExprOrig2->szExpr );
		iRet = LTExprResult.LT_ExprXor( szNewExpr, &LTExpr1, &LTExpr2 );
		break;

	case OL_NOT:
		sprintf( szNewExpr, "(%s) %s (%s)", (char*) pExprOrig1->szExpr, (char*) GLT_Session->LT_GetSymbol( "NOT" ), (char*) pExprOrig2->szExpr );
		iRet = LTExprResult.LT_ExprNot( szNewExpr, &LTExpr1, &LTExpr2 );
		break;

	}

	if( iRet != 0 ){
		// vamos retornar uma indicacao de que nao ha' ocorrencias
		// (a operacao de consulta resultou em uma LO vazia)
		ERETURN( LBSE_EMPTYLIST );
	}

	LBSC_Expr *pNewExpr = new LBSC_Expr;
	if ( !pNewExpr ) {
		ERETURN( LBSE_NOMEMORY );
	}
	pNewExpr->szExpr = szNewExpr;

	// gera a LO no formato registro/lista de ocorrencias (para navegacao corretamente)
	int iCreateOccRet = CreateLbsOccList( pNewExpr, &LTExprResult );
	if ( iCreateOccRet != LBS_OK ) {
		delete pNewExpr;
		ERETURN( iCreateOccRet );
	}
	// adiciona a nova LO na lista de LO's
	pcOLList->Add( pNewExpr, TAIL );
	// pega o handle da LO que foi adicionada na lista
	iRet = pcOLList->GetCurrentIndex();
	// Habilita a LO resultante
	if( EnableOcList( plbscsOwnerSession->plbsctTicket, iRet ) != LBS_OK ){
		if( (*pcOLList)[ iRet ] ){
			pcOLList->DeleteCurrObj();	// deleta somente o objeto, mas deixa o nodo.
		}
		ERETURN( LBSE_ENABLE );
	}

	// retorna o handle da LO resultante do batimento
	SetError( LBS_OK );
	return( iRet );
}




