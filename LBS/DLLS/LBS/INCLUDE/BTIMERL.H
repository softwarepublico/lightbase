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
// Module: BASETIMERSLIST.H
//	LBSC_BaseTimersList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last revision: 18/10/94
//


#ifndef	_BASETIMERSLIST_H_
#define	_BASETIMERSLIST_H_

#ifndef	_LBSTEMPLATE_H_
#include <lbstempl.h>
#endif
#ifndef	_LBSTYPES_H_
#include <lbstypes.h>
#endif

class LBSC_BaseTimersList : public LBSC_DList<TBaseTimers>
{
	public:
				LBSC_BaseTimersList() : LBSC_DList<TBaseTimers>(){};
				~LBSC_BaseTimersList(){};
};

#endif // _BASETIMERSLIST_H_


