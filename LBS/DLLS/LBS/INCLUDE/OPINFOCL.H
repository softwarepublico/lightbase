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


