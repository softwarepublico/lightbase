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
// Module: allbasel.H
//	LBSC_AllBasesList class definition file
//
// Programmer:	Tricia Souto Santos
//
// Last revision: 14/10/94
//


#ifndef	_ALLBASEL_H_
#define	_ALLBASEL_H_

#include <lbstempl.h>
#include <lbstypes.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_AllBasesList : public LBSC_DList<TAllBases>
{
	public:
				LBSC_AllBasesList() : LBSC_DList<TAllBases>(){};
				~LBSC_AllBasesList(){};
		LBSC_DList<TAllBases>::NumElem;
		LBSC_DList<TAllBases>::Next;
		LBSC_DList<TAllBases>::Previous;
		LBSC_DList<TAllBases>::First;
		LBSC_DList<TAllBases>::Last;
		LBSC_DList<TAllBases>::Current;
		LBSC_DList<TAllBases>::Nth;
		LBSC_DList<TAllBases>::Search;
		LBSC_DList<TAllBases>::Find;
		LBSC_DList<TAllBases>::DelAll;
		LBSC_DList<TAllBases>::Add;
		LBSC_DList<TAllBases>::operator[];
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _ALLBASEL_H_

