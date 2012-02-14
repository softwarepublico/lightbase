/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


////////////////////////////////////////////////////////////
//	Metodos de regiao critica
//////////////////////////////////////////////////////////

#include <stdio.h>

#ifndef _LBNEWDBG_H_
	#include <lbnewdbg.h>
#endif	// _LBNEWDBG_H_
#ifndef _STUBCRIT_H_
	#include <stubcrit.h>
#endif	// _STUBCRIT_H_
#ifndef _CRITSECT_H_
	#include <critsect.h>
#endif	// _CRITSECT_H_


//
// Variaveis globais
//
static C_CritSect<MAXSECTIONID> *_pccsSection = NULL;



/**********************************************************/
C_CritSecManager::C_CritSecManager( int iDesiredSection, 
									BOOL bDevoEntrarAgora )
{
	if ( iDesiredSection < 0 || iDesiredSection >= MAXSECTIONID ) {
		iNumAccessedSection = 0;
	}
	else { 
		iNumAccessedSection = iDesiredSection;
	}

	if ( !_pccsSection ) {
		_pccsSection = new C_CritSect<MAXSECTIONID>;
	}

	if ( _pccsSection ) {
		_pccsSection->UseCriticalSection( TRUE );

		if ( bDevoEntrarAgora ) {
			EnterCriticalSection();
		}
	}
}


/**********************************************************/
C_CritSecManager::~C_CritSecManager()
{
	LeaveCriticalSection();
}



/**********************************************************/
void
C_CritSecManager::LeaveCriticalSection()
{
	if ( _pccsSection ) {
		_pccsSection->LeaveCriticalSection( iNumAccessedSection );
	}
}

/**********************************************************/
void
C_CritSecManager::EnterCriticalSection()
{
	if ( _pccsSection ) {
		_pccsSection->EnterCriticalSection( iNumAccessedSection );
	}
}

/**********************************************************/
void
C_CritSecManager::FreeCriticalSection()
{
	if ( _pccsSection ) {
		delete _pccsSection;
		_pccsSection = NULL;
	}
}