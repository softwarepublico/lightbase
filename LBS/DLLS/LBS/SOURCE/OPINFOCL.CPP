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
// Module: OPINFOCL.CPP
// Description:
//
//	methods file for the LBSC_OpInfo class
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 04/06/96
//

#ifndef	_OPINFO_H_
#include	<opinfocl.h>
#endif

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/***
	PUBLIC
***/
LBSC_OpInfo::LBSC_OpInfo()
{
	ResetFeedbackInfo();
}


/***
	PUBLIC
***/
LBSC_OpInfo::~LBSC_OpInfo()
{
}

/***
	PUBLIC
***/
void
LBSC_OpInfo::CancelOperation()
{
	bCancel = TRUE;
}

/***
	PUBLIC
***/
void
LBSC_OpInfo::GetOpInfo( char *szActionPar, float *pfPercentPar )
{
	if( szActionPar && pfPercentPar ){
		strcpy( szActionPar, (char*) szAction );
		*pfPercentPar = fPercent;
	}
}

/***
	PROTECTED
***/
void
LBSC_OpInfo::SetOpInfo( char *szActionPar, float fPercentPar )
{
	if( fPercentPar < (float) 0.0 ){
		fPercentPar = (float) 0.0;
	}
	if( fPercentPar > (float) 100.0 ){
		fPercentPar = (float) 100.0;
	}
	szAction = szActionPar;
	fPercent = fPercentPar;
}

/***
	PROTECTED
***/
void
LBSC_OpInfo::ResetFeedbackInfo()
{
	szAction = "OK";
	fPercent = (float) 0.0;
	iNumSteps = 1;
	bCancel = FALSE;
}

/***
	PROTECTED
***/
void
LBSC_OpInfo::SetNumSteps( int iNumStepsPar )
{
	iNumSteps = (iNumStepsPar < 1) ? 1 : iNumStepsPar;
}

/***
	PROTECTED
***/
void
LBSC_OpInfo::IncStep( char *szActionPar )
{
	if( !iNumSteps ){
		iNumSteps = 1;
	}
	SetOpInfo( szActionPar, fPercent + ((float) 100.0 / iNumSteps) );
}

/***
	PROTECTED
***/
BOOL
LBSC_OpInfo::OperationCanceled()
{
	return( bCancel );
}


