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


