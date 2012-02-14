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


#ifndef	_SVBASEL_H_
#define	_SVBASEL_H_

#include	<lbstempl.h>
#include	<lbstypes.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_ServerBasesList : LBSC_DList<TServerBases>
{
	public:
				LBSC_ServerBasesList() : LBSC_DList<TServerBases>(){};
				~LBSC_ServerBasesList(){};
		LBSC_DList<TServerBases>::NumElem;
		LBSC_DList<TServerBases>::Next;
		LBSC_DList<TServerBases>::Previous;
		LBSC_DList<TServerBases>::First;
		LBSC_DList<TServerBases>::Last;
		LBSC_DList<TServerBases>::Current;
		LBSC_DList<TServerBases>::Nth;
		LBSC_DList<TServerBases>::Search;
		LBSC_DList<TServerBases>::Find;
		LBSC_DList<TServerBases>::DelAll;
		LBSC_DList<TServerBases>::Add;		
		LBSC_DList<TServerBases>::Del;		
		LBSC_DList<TServerBases>::operator[];		
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _SVBASEL_H_

