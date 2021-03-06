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
// Module: LB3LIST.H
//	C_LB3LIST class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Tr�cia Souto Santos
//
// Last revision: 27/09/94
//


#ifndef _LB3LIST_H_
#define	_LB3LIST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

class C_LB3List : LBSC_DList<TStructRec>
{
	friend	class	_LBSCLASS LBSC_Base;
	
	public:
				C_LB3List() : LBSC_DList<TStructRec>(){};
				~C_LB3List(){};
		LBSC_DList<TStructRec>::NumElem;
		LBSC_DList<TStructRec>::Next;
		LBSC_DList<TStructRec>::Previous;
		LBSC_DList<TStructRec>::First;
		LBSC_DList<TStructRec>::Last;
		LBSC_DList<TStructRec>::Current;
		LBSC_DList<TStructRec>::Nth;
		LBSC_DList<TStructRec>::Search;
		LBSC_DList<TStructRec>::Find;
		LBSC_DList<TStructRec>::Add;
		LBSC_DList<TStructRec>::Del;
		LBSC_DList<TStructRec>::DelAll;
};


#endif //_LB3LIST_H_
