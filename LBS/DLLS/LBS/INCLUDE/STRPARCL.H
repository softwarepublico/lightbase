/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o t�tulo
"LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do Software 
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


