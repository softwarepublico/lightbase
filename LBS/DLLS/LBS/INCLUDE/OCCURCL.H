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
// Module: OCCURCL.H
// Description:
//
//	Header file for LBSC_Occurrence class
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 02/09/94
//

#ifndef	_OCCURRENCE_H_
#define	_OCCURRENCE_H_

#ifndef _OCCURREN
#include	<occurren.h>	// GREEN
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_Base;

class _LBSCLASS LBSC_Occurrence
{
	friend	class	_LBSCLASS LBSC_Base;
	private:
		LTC_OCCURRENCE	*pltcOc;

			LBSC_Occurrence( LTC_OCCURRENCE * );
			LBSC_Occurrence( CHARTYPE 	*,
					 TUFOURBYTES,
					 TUTWOBYTES,
					 TUTWOBYTES,
					 TUTWOBYTES,
					 TUTWOBYTES,
					 TUTWOBYTES );
	public:
				LBSC_Occurrence();
				~LBSC_Occurrence();
		int		Compare( LBSC_Occurrence *, int );
		LBSC_Occurrence	*Duplicate() { return( NULL ); };
		long		GetRecord();
		int		GetField();
		int		GetRepetition();
		int		GetParagraph();
		int		GetPhrase();
		int		GetSequence();
		const char	*GetTerm();
		LBSC_Occurrence	&operator = ( LBSC_Occurrence & );
		LBSC_Occurrence	&operator = ( LTC_OCCURRENCE & );
				 operator LTC_OCCURRENCE * ();
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _OCCURRENCE_H_


