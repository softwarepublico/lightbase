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
