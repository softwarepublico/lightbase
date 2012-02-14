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
// Module: OPINFO.H
// Description:
//
//	LBSC_OpInfo class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 04/06/96
//

#ifndef	_OPINFO_H_
#define	_OPINFO_H_

#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_CRITSECT_H_
#include	<critsect.h>
#endif
#ifndef _CL_STRINGN_
#include	<stringn.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif

//template <int NUM_CRITICAL_SECT>
class _LBSCLASS LBSC_OpInfo 
{
private:
	CL_StringN<OPINFOSIZE>	szAction;	// o que esta' acontecendo no momento
	float					fPercent;	// qual o percentual da operacao (1-100)
	BOOL					bCancel;	// eh pra cancelar a operacao?
	int						iNumSteps;	// numero de passos da operacao

protected:
	void	ResetFeedbackInfo();
	void	SetOpInfo( char *szActionPar, float fPercentPar );
	void	SetNumSteps( int iNumStepsPar );
	void	IncStep( char *szActionPar );
	BOOL	OperationCanceled();

public:
			LBSC_OpInfo();
			~LBSC_OpInfo();
	void	CancelOperation();										// cancela a operacao corrente
	void	GetOpInfo( char *szActionPar, float *pfPercentPar );	// obtem o status da operacao corrente
};


#endif	_OPINFO_H_


