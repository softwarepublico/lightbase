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

