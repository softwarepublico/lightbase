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

