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
// Module: LINKLIST.H
//	LBSC_LinkList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 28/09/94
//


#ifndef	_LINKLISTCL_H_
#define	_LINKLISTCL_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LINKCL_H_
#include	<linkcl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

class LBSC_LinkList : LBSC_DList<LBSC_Link>
{
	friend	class	_LBSCLASS LBSC_Field;

	public:
				LBSC_LinkList() : LBSC_DList<LBSC_Link>(){};
				~LBSC_LinkList(){};
		LBSC_DList<LBSC_Link>::NumElem;
		LBSC_DList<LBSC_Link>::Next;
		LBSC_DList<LBSC_Link>::Previous;
		LBSC_DList<LBSC_Link>::First;
		LBSC_DList<LBSC_Link>::Last;
		LBSC_DList<LBSC_Link>::Current;
		LBSC_DList<LBSC_Link>::Nth;
		LBSC_DList<LBSC_Link>::Search;
		LBSC_DList<LBSC_Link>::Find;
		LBSC_DList<LBSC_Link>::Add;
		LBSC_DList<LBSC_Link>::Update;
		LBSC_DList<LBSC_Link>::Del;
		LBSC_DList<LBSC_Link>::DelAll;
};


#endif // _LINKLISTCL_H_
