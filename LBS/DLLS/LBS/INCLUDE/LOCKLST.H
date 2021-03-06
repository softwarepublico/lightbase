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
// Module: LockLst.H
//	LockList class definition file
//
// Programmer:	
//	Adriano Sergio
//	Alessandro Jatoba'
//
// Last revision: 04/11/95
//


#ifndef	_LOCKLST_H_
#define	_LOCKLST_H_

#include	<lockstru.h>
#include	<lbstempl.h>
#include	<defclass.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LockList : public LBSC_DList<LockStruct>
{
/*	public:
				LockList() : LBSC_DList<LockStruct>(){};
				~LockList(){};
		LBSC_DList<LockStruct>::NumElem;
		LBSC_DList<LockStruct>::Next;
		LBSC_DList<LockStruct>::Previous;
		LBSC_DList<LockStruct>::First;
		LBSC_DList<LockStruct>::Last;
		LBSC_DList<LockStruct>::Current;
		LBSC_DList<LockStruct>::Nth;
		LBSC_DList<LockStruct>::Search;
		LBSC_DList<LockStruct>::Find;
		LBSC_DList<LockStruct>::DelAll;
		LBSC_DList<LockStruct>::Add;
		LBSC_DList<LockStruct>::Del;
		LBSC_DList<LockStruct>::operator[];
*/
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _LOCKLST_H_

