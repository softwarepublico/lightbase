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

