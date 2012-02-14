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
// Module: STRLISTCL.H
//	C_STRLIST class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Trícia Souto Santos
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

