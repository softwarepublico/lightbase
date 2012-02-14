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
// Module: datlstCL.H
//	LBSC_DataCl class definition file
//
// Programmer:	Tricia Souto Santos
//
// Last revision: 26/11/94		   
//

#ifndef	_DATLSTCL_H_
#define	_DATLSTCL_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_DATACL_H_
#include	<datacl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

class LBSC_DataList : LBSC_DList<LBSC_Data>
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Field;
	friend	class	_LBSCLASS LBSC_Record;

	public:
				LBSC_DataList() : LBSC_DList<LBSC_Data>(){};
				~LBSC_DataList(){};
		LBSC_DList<LBSC_Data>::NumElem;
		LBSC_DList<LBSC_Data>::Next;
		LBSC_DList<LBSC_Data>::Previous;
		LBSC_DList<LBSC_Data>::First;
		LBSC_DList<LBSC_Data>::Last;
		LBSC_DList<LBSC_Data>::Current;
		LBSC_DList<LBSC_Data>::Nth;
		LBSC_DList<LBSC_Data>::Search;
		LBSC_DList<LBSC_Data>::Find;
		LBSC_DList<LBSC_Data>::Add;
		LBSC_DList<LBSC_Data>::Del;
		LBSC_DList<LBSC_Data>::DelAll;
};

#endif // _DATLSTCL_H_


