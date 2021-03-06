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
// Module: STRLISTCL.H
//	C_STRLIST class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Tr�cia Souto Santos
//
// Last revision: 27/09/94
//


#ifndef _STRLIST_H_
#define	_STRLIST_H_

#include <lbstempl.h>

class C_StrList : LBSC_DList<char>
{
	public:
				LBSC_OcList() : LBSC_DList<char>(){};
				~LBSC_OcList() : ~LBSC_DList<char>(){};
		LBSC_DList<char>::NumElem;
		LBSC_DList<char>::Next;
		LBSC_DList<char>::Previous;
		LBSC_DList<char>::First;
		LBSC_DList<char>::Last;
		LBSC_DList<char>::Current;
		LBSC_DList<char>::Nth;
		LBSC_DList<char>::Search;
		LBSC_DList<char>::Add;
		LBSC_DList<char>::Del;
		LBSC_DList<char>::DelAll;
		LBSC_DList<char>::Find;
		LBSC_DList<char>::DeleteObj;
};


#endif //_STRLIST_H_

