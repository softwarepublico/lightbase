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
// Module: svbasel.H
//	LBSC_ServerBasesList class definition file
//
// Programmer:	Tricia Souto Santos
//
// Last revision: 05/10/94
//


#ifndef	_BASENLST_H_
#define	_BASENLST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
/*
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
*/
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif

class LBSC_BaseNameList : LBSC_DList<TUserBaseName>
{
	public:
				LBSC_BaseNameList() : LBSC_DList<TUserBaseName>(){};
				~LBSC_BaseNameList(){};
		LBSC_DList<TUserBaseName>::NumElem;
		LBSC_DList<TUserBaseName>::Next;
		LBSC_DList<TUserBaseName>::Previous;
		LBSC_DList<TUserBaseName>::First;
		LBSC_DList<TUserBaseName>::Last;
		LBSC_DList<TUserBaseName>::Current;
		LBSC_DList<TUserBaseName>::Nth;
		LBSC_DList<TUserBaseName>::Search;
		LBSC_DList<TUserBaseName>::Find;
		LBSC_DList<TUserBaseName>::Del;
		LBSC_DList<TUserBaseName>::DelAll;
		LBSC_DList<TUserBaseName>::Add;
		LBSC_DList<TUserBaseName>::Update;
};


#endif // _BASENLST_H_


