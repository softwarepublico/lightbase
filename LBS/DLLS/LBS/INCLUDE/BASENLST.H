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


