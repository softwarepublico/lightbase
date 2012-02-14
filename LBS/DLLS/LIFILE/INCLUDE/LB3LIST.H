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
// Module: LB3LIST.H
//	C_LB3LIST class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Trícia Souto Santos
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
