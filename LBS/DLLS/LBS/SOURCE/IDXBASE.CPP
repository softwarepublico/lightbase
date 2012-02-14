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
// Module: IDXBASE.CPP
// Description:
//
//	LBSC_BASE public class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 26/07/95
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
#ifndef _STRPARCL_H_
#include	<strparcl.h>
#endif
#include	<lt.h>		// $$$ GREEN
extern "C" {
#include	<personcl.h>
}


EXTLOG( _clLBSLog );	// objeto para geracao de log

/**************************************************************************************/
/*************                  PUBLICOS                                     **********/
/**************************************************************************************/

/***
	Metodo IndexString
	Indexa uma determinada string no indice ENTIRETREE.

	Parameters:
		- pTicket	-> ticket de seguranca
		- lRec		-> numero do registro que devera' entrar
				   para o sistema de indices
		- uiField	-> identificador do campo que devera' entrar
				   para o sistema de indices
		- iRepet	-> numero da repeticao que devera' entrar
				   para o sistema de indices
		- szStr		-> string que deve ser indexada

	Return:
		- LBS_OK se a operacao for bem sucedida; valor negativo
		  em caso de erro

	Comments:
		- Este metodo chama o sistema de indices da GREEN passando
		  como parametros para a formacao da ocorrencia o registro,
		  o campo e a repeticao recebidos.
		- A string szStr e' indexada de uma so' vez, nao sendo quebrada
		  em tokens.
		- Os numeros de paragrafo, frase e sequencia, que completam uma
		  ocorrencia, sao gerados internamente pela biblioteca da GREEN.
***/
int
LBSC_Base::IndexString( const LBSC_Ticket *pTicket, long lRec, UINT uiField,
			int iRepet, char *szStr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::IndexString") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !szStr || lRec < 0 || lRec > LB1.tcrHead.lLastRecActivePos || uiField < 1
	    || uiField > LB1.tcrHead.uiLastFieldId || iRepet < 0 ){
		ERETURN( LBSE_BADARG );
	}
	int		iRet;
	LBSC_StrParser	spParser( szStr );

	LBSC_Field	*plbscfAux = (LBSC_Field*) lbscrCurrRecord.Id( uiField );
	if( !plbscfAux ){
		return LBSE_ERROR;
	}
	iRet = IndexLT( plbscisIndexSystem,
			( int ) ENTIRETREE,
			lRec,
			plbscfAux,
			iRepet,
			( LTC_PARSER * ) &spParser );

	ERETURN( iRet == LBS_OK ? LBS_OK : LBSE_ERROR );
}



/***
	Metodo UnindexString
	Desindexa uma determinada string no indice ENTIRETREE.

	Parameters:
		- pTicket	-> ticket de seguranca
		- lRec		-> numero do registro que devera' entrar
				   para o sistema de indices
		- uiField	-> identificador do campo que devera' entrar
				   para o sistema de indices
		- iRepet	-> numero da repeticao que devera' entrar
				   para o sistema de indices
		- szStr		-> string que deve ser indexada

	Return:
		- LBS_OK se a operacao for bem sucedida; valor negativo
		  em caso de erro

	Comments:
		- Este metodo chama o sistema de indices da GREEN passando
		  como parametros para a formacao da ocorrencia o registro,
		  o campo e a repeticao recebidos.
		- A string szStr e' indexada de uma so' vez, nao sendo quebrada
		  em tokens.
		- Os numeros de paragrafo, frase e sequencia, que completam uma
		  ocorrencia, sao gerados internamente pela biblioteca da GREEN.
***/
int
LBSC_Base::UnindexString( const LBSC_Ticket *pTicket, long lRec, UINT uiField,
			int iRepet, char *szStr )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UnindexString") );

	if( !plbscisIndexSystem ){
		ERETURN( LBSE_INVALIDINDEXSYSTEM );
	}
	if( plbscsOwnerSession->TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !szStr || lRec < 0 || lRec > LB1.tcrHead.lLastRecActivePos || uiField < 1
	    || uiField > LB1.tcrHead.uiLastFieldId || iRepet < 0 ){
		ERETURN( LBSE_BADARG );
	}
	int		iRet;
	LBSC_StrParser	spParser( szStr );

	iRet = plbscisIndexSystem->LT_UnindexGroup( ( int ) ENTIRETREE,
						    lRec,
						    uiField,
						    iRepet,
						    ( LTC_PARSER * ) &spParser, STOPWORD );

	ERETURN( iRet == LBS_OK ? LBS_OK : LBSE_ERROR );
}


/***
	PUBLIC
	Metodo GetIndexRecNum
	Obtem o numero de registros que estao indexados ou que NAO ESTAO
	indexados na base.

	Parameters:
		- lbscTicket -> ticket de seguranca
		- bIndex -> indica se o o numero de registros a ser retornado
		  deve ser o numero de registros indexados (TRUE) ou
		  nao indexados (FALSE)

	Return:
		- o numero de registros ou um valor negativo em caso de erro

	Comments:
		- 

***/
long
LBSC_Base::GetIndexRecNum( const LBSC_Ticket *lbscTicket, BOOL bIndex )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetIndexRecNum") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	BOOL		bOpen = cfLB5.IsOpen();
	long		lNumUnindRecs = 0L;

	if( !bOpen ){
		// Abrir LB5
		if( OpenLogFile( cfLB5 ) == LBS_OK ){
			lNumUnindRecs = cfLB5.GetNumRecordsLogged();
		}
		cfLB5.CloseIndex();
	} else {
		lNumUnindRecs = cfLB5.GetNumRecordsLogged();
	}
	SetError( LBS_OK );
	return( bIndex ? (LB1.tcrHead.lNumRecords-lNumUnindRecs) : lNumUnindRecs );
}



/***
	PUBLIC
	Metodo SetStopIndex
	Liga ou desliga o modo de parada automatica de indexacao total, quando
	o limite de registros indexados for atingido.
	A indexacao total de uma base pode ser demorada. O LBS disponibiliza a
	possibilidade de fazer essa indexacao de modo incremental, o que o forca
	a parar a indexacao de vez em quando, salvar o contexto e retornar para
	a aplicacao. A aplicacao decide quando continuar o trabalho de indexacao.

	Para desligar o modo incremental, basta setar StopIndex (este metodo) para
	FALSE.

	Parameters:
		- bNewVal - indica o novo modo de indexacao total (TRUE = incremental).

	Return:
		-

	Comments:
		-

***/
void
LBSC_Base::SetStopIndex( BOOL bNewVal )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetStopIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	bStopIndex = bNewVal;
}

/***
	PUBLIC
	Metodo GetStopIndex
	Obtem o valor do flag de indexacao incremental do LBS.

	Parameters:
		- 

	Return:
		- TRUE, para indicar que o LBS esta' trabalhando no modo incremental;
		  FALSE, para indicar que, quando uma indexacao total for disparada,
		  o LBS ficara' processando ate' o fim.

	Comments:
		-

***/
BOOL
LBSC_Base::GetStopIndex()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetStopIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( bStopIndex );
}


/***
	PUBLIC
	Metodo GetNumRecIndex
	Obtem o numero de registros que devem ser indexados na indexacao incremental

	Parameters:
		- 

	Return:
		- o numero requerido ou um valor negativo em caso de erro.

	Comments:
		- 

***/
int
LBSC_Base::GetNumRecIndex()
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumRecIndex") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	int iStop = LBSC_ServerConfig::StopIndex(); 
	if( iStop > 0 ){
		SetError( LBS_OK );
		return( iStop );
	}
	ERETURN( LBSE_ERROR );
}




/**************************************************************************************/
/*************                  PRIVADOS                                     **********/
/**************************************************************************************/


/***
	PRIVATE
	Metodo SaveIndexStatus
	Salva o status da indexacao que esta' acontecendo.
	Serve como protecao contra uma eventual queda do LBS.

	Parameters:
		- lbscTicket - ticket de acesso

	Return:
		- LBS_OK em caso de sucesso; um valor negativo em caso contrario

	Comments:
		- O contexto e' gravado em disco, no diretorio da base e possui nome
		  fisico igual a INDEX.CTX
		- As informacoes gravadas sao:
			- numero do registro corrente
			- data da gravacao do contexto (informacao de administracao)
			- hora da gravacao do contexto (informacao de administracao)

***/
int
LBSC_Base::SaveIndexStatus( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SaveIndexStatus") );

	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) IDXCONTEXTFILE );

	C_File	cfCtxFile( szAux );

	if( !cfCtxFile.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	TIndexContext	tIC;

	tIC.lCurrRec = CurrRecNum( lbscTicket );	// numero do registro corrente
	tIC.ulDate = C_Date().Hash();			// data da gravacao (apenas para administracao)
	tIC.ulTime = C_Time().Seconds();		// hora da gravacao (apenas para administracao)

	if( cfCtxFile.Seek( 0, SEEK_SET ) != OK ){
		ERETURN( LBSE_ERROR );
	}
	if( cfCtxFile.Write( &tIC, sizeof( tIC ) ) != OK ){
		ERETURN( LBSE_ERROR );
	}

//	o codigo abaixo deve ser comentado se a CTREE estiver no modo "ROBUSTEZ";
//	se a CTREE estiver com bufferizacao, o codigo abaixo deve ser executado, 
//	para forcar um flush.

	return( FlushIndexSystem() );
}



/***
	PRIVATE
	Metodo LoadIndexStatus
	Carrega o status da indexacao que esta' acontecendo.
	Serve como protecao contra uma eventual queda do LBS.

	Parameters:
		- lbscTicket - ticket de acesso

	Return:
		- LBS_OK em caso de sucesso; um valor negativo em caso contrario

	Comments:
		- O contexto e' gravado em disco, no diretorio da base e possui nome
		  fisico igual a INDEX.CTX
		- As informacoes gravadas sao:
			- numero do registro corrente
			- data da gravacao do contexto (informacao de administracao)
			- hora da gravacao do contexto (informacao de administracao)

***/
int
LBSC_Base::LoadIndexStatus( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LoadIndexStatus") );

	char	szAux[ PATHNAMESIZE + FILENAMESIZE + 10 ];
	sprintf( szAux, "%s\\%s", (char*) szBasePath, (char*) IDXCONTEXTFILE );

	C_File	cfCtxFile( szAux );

	if( !cfCtxFile.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	if( cfCtxFile.Seek( 0, SEEK_SET ) != OK ){
		ERETURN( LBSE_ERROR );
	}
	TIndexContext	tIC;
	if( cfCtxFile.Read( &tIC, sizeof( tIC ) ) != OK ){
		ERETURN( LBSE_ERROR );
	}

	int iRet = GotoRec( lbscTicket, tIC.lCurrRec );
	// tIC.ulDate -> ainda nao utilizado
	// tIC.ulTime -> ainda nao utilizado

	ERETURN( iRet );
}


/***
	PRIVATE
	Metodo FlushIndexSystem
	Realiza um flush do sistema de indices. 

	Return:
		- LBS_OK em caso de sucesso; um valor negativo em caso contrario

	Comments:
		- 

***/
int
LBSC_Base::FlushIndexSystem( BOOL )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::FlushIndexSystem") );

	if( !plbscisIndexSystem ){
		return LBSE_ERROR;
	}

	plbscisIndexSystem->LT_Flush();
	ERETURN( LBS_OK  );
}


