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


