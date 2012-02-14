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
// Module: PARSERCL.H
// Description:
//
//	LBSC_Parser class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//
// Last update: 14/11/94
//

#ifndef	_PARSERCL_H_
#define	_PARSERCL_H_

#ifndef	_MACHINE
#include	<machine.h>
#endif
#ifndef	_PARSER
#include	<parser.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_CRITSECT_H_
#include	<critsect.h>
#endif
#ifndef	_TE_TOKEN_H_
#include	<te_token.h>	// GetToken feito por Maurao
#endif
#ifndef	_REFERENCE_
#include	<Refercl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "LIP_Parser.h"
#include "LI_ConvTER.h"

class _LBSCLASS	LBSC_Base;

class CritParserManager : public CritSectManager
{
	void CritSectLog( char *szMsg, char *szFile, int iLine, int iNum );
	unsigned long GetCritSectMask();
	void SetCritSectMask( unsigned long );
	BOOL OrderedDependents();
};
extern CritParserManager _csParserMan;

class _LBSCLASS LBSC_Parser :	public LTC_PARSER
{
		
	private:
		LBSC_Base		*plbscbBase;
		char			*szTok;
		char			*szTerm;
		int				iTermSize;
		BYTE			bProcessReference;
		LI_ConvTER		licterConvert;
		BOOL  			bUniqueIndex;
		long			lCurrRepetSize;
		long			lRepetPos;

		int	GetToken( long *, LTC_OCCURRENCE * );
		int GetUrlBuffer( LBSC_Reference * );
		int GetWordBuffer( LBSC_Reference * );
		int ReallocBuffer();

	public:
		// o LBS utiliza o atributo abaixo para indicar ao 
		// parser se esta' processando uma indexacao ou
		// uma desindexacao
		BOOL	bIndexing;
		LIP_Parser lipParser;

				LBSC_Parser( LBSC_Base * );
				~LBSC_Parser();

		// Os proximos tres metodos se chamao LT_* porque
		// a classe LTC_PARSER os define como virtuais puros
		// e entao temos que defini-los exatamente da mesma
		// forma.
		int		LT_ParserInit();
		int		LT_ParserProcess( LTC_OCCURRENCE * );
		int		LT_ParserTerminate();
		int		LT_ParserResetStatus();
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _PARSERCL_H_


 