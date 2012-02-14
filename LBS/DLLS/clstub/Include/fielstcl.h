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
// Module: fielstCL.H
//	LBSC_FieldCl class definition file
//
// Programmer:	Tricia Souto Santos
//
// Last revision: 09/11/94		   
//

#ifndef	_FIELSTCL_H_
#define	_FIELSTCL_H_

#ifndef	_FIELDCL_H_
#include	<fieldcl.h>
#endif
#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
class LBSC_FieldList : public LBSC_DList<LBSC_Field>
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Record;

//	public:
/****
				LBSC_FieldList() : LBSC_DList<LBSC_Field>(){};
				~LBSC_FieldList(){};
		LBSC_DList<LBSC_Field>::NumElem;
		LBSC_DList<LBSC_Field>::Next;
		LBSC_DList<LBSC_Field>::Previous;
		LBSC_DList<LBSC_Field>::First;
		LBSC_DList<LBSC_Field>::Last;
		LBSC_DList<LBSC_Field>::Current;
		LBSC_DList<LBSC_Field>::Nth;
		LBSC_DList<LBSC_Field>::Search;
		LBSC_DList<LBSC_Field>::Find;
		LBSC_DList<LBSC_Field>::Add;
		LBSC_DList<LBSC_Field>::Del;
		LBSC_DList<LBSC_Field>::DelAll;
****/
};
#endif // _FIELSTCL_H_


