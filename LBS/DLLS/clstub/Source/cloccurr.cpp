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
// Module: CLIOCCUR.CPP
// Description:
//
//	Function file for LBSC_Occurrence class
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 26/02/96
//

#ifndef _OCCURRCL_H_
	#include	<occurcl.h>
#endif	// _OCCURRCL_H_

#ifndef __lbsrpc_h__
	#include	<lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _SESSCL_H_
	#include <sesscl.h>
#endif	// _SESSCL_H_

// so pra constar...
class COccurList;
class C_Buffer;

#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_


LBSC_Occurrence::LBSC_Occurrence()
{
	pszTerm = NULL; 
	Set( NULL, 0,0,0,0,0,0 );
}

LBSC_Occurrence::~LBSC_Occurrence()
{
	if( pszTerm ){
		delete pszTerm;
	}
}

void
LBSC_Occurrence::Set( char *sz, long lR, int iF, int iR, int iP, int iPh, int iS )
{
	if ( pszTerm ) {
		delete pszTerm;
	}
	if( sz ){
		pszTerm	= StrDup( sz );
	}else{
		pszTerm	= NULL;
	}
	lRec = lR;
	iField = iF;
	iRepetition = iR;
	iParagraph = iP;
	iPhrase = iPh;
	iSequence = iS;
};

long
LBSC_Occurrence::GetRecord()
{
	return lRec; 
}

int
LBSC_Occurrence::GetField()
{
	return iField;
}

int
LBSC_Occurrence::GetRepetition()
{
	return iRepetition;
}

int
LBSC_Occurrence::GetParagraph()
{
	return iParagraph;
}

int
LBSC_Occurrence::GetPhrase()
{
	return iPhrase;
}

int
LBSC_Occurrence::GetSequence()
{
	return iSequence;
}

const char *
LBSC_Occurrence::GetTerm()
{
	return pszTerm;
}


