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
// Module: GROUPLIST.H
//	LBSC_GroupList class definition file
//
// Programmer:	Tricia Souto Santos
//
// Last revision: 30/09/94
//


#ifndef	_GRPLIST_H_
#define	_GRPLIST_H_

#ifndef	_LBSTEMPLATE_H_
#include <lbstempl.h>
#endif
#ifndef	_GROUPCL_H_
#include <groupcl.h>
#endif

class LBSC_GroupList : LBSC_DList<LBSC_Group>
{
	public:
				LBSC_GroupList() : LBSC_DList<LBSC_Group>(){};
				~LBSC_GroupList(){};
		LBSC_DList<LBSC_Group>::NumElem;
		LBSC_DList<LBSC_Group>::Next;
		LBSC_DList<LBSC_Group>::Previous;
		LBSC_DList<LBSC_Group>::First;
		LBSC_DList<LBSC_Group>::Last;
		LBSC_DList<LBSC_Group>::Current;
		LBSC_DList<LBSC_Group>::Nth;
		LBSC_DList<LBSC_Group>::Search;
		LBSC_DList<LBSC_Group>::Find;
		LBSC_DList<LBSC_Group>::Del;
		LBSC_DList<LBSC_Group>::DelAll;
		LBSC_DList<LBSC_Group>::Add;
		LBSC_DList<LBSC_Group>::Update;
};


#endif // _DATALIST_H_

