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
// Module: CLIOCCUR.H
// Description:
//
//	Header file for LBSC_Occurrence class
//	It's not the true LBSC_Occurrence class. It's just a "dde-client LBSC_Occurrence class".
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 07/03/95
//

#ifndef	_DDECLIENT_OCCURRENCE_H_
#define	_DDECLIENT_OCCURRENCE_H_

#include	<string.h>

#ifndef _LBS_DEFCLASS_H_
	#include	<defclass.h>
#endif	// _LBS_DEFCLASS_H_


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_Base;

class _LBSCLASS LBSC_Occurrence
{
	friend	class	_LBSCLASS LBSC_Base;
	private:
		char		*pszTerm;
		long		lRec;
		int		iField;
		int		iRepetition;
		int		iParagraph;
		int		iPhrase;
		int		iSequence;

	public:
		LBSC_Occurrence();
		~LBSC_Occurrence();

		void	Set( char *sz, long lR, int iF, int iR, int iP, int iPh, int iS );
		long	GetRecord();
		int		GetField();
		int		GetRepetition();
		int		GetParagraph();
		int		GetPhrase();
		int		GetSequence();
		const char	*GetTerm();
};

	
	

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _DDECLIENT_OCCURRENCE_H_

