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
// Module: ENTPARCL.H
// Description:
//
//	LBSC_EntParser class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 26/07/95
//

#ifndef	_STRPARCL_H_
#define	_STRPARCL_H_

#ifndef		_MACHINE
#include	<machine.h>
#endif
#ifndef         _PARSER
#include	<parser.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_StrParser : public LTC_PARSER
{
	private:
		char		*szBuffer;

	public:
				LBSC_StrParser( char * );
				~LBSC_StrParser();

		// $$$ Os proximos tres metodos se chamao LT_* porque
		// $$$ a classe LTC_PARSER os define como virtuais puros
		// $$$ e entao temos que defini-los exatamente da mesma
		// $$$ forma.
		int		LT_ParserInit();
		int		LT_ParserProcess(LTC_OCCURRENCE *);
		int		LT_ParserTerminate();
		int		LT_ParserResetStatus();
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _STRPARCL_H_


