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

