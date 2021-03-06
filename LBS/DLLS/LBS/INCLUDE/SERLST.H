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
// Module: SERLST.H
//	LBSC_SerialNumberList class definition file
//
// Programmer:	Tricia Souto santos
//
// Last revision: 31/01/95
//


#ifndef	_SERLST_H_
#define	_SERLST_H_

#ifndef	_LBSTEMPLATE_H_
#include <lbstempl.h>
#endif
#ifndef	_LBSTYPES_H_
#include <lbstypes.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_SerialNumberList : LBSC_DList<TSerialNumber>
{
	public:
				LBSC_SerialNumberList() : LBSC_DList<TSerialNumber>(){};
				~LBSC_SerialNumberList(){};
		LBSC_DList<TSerialNumber>::NumElem;
		LBSC_DList<TSerialNumber>::Next;
		LBSC_DList<TSerialNumber>::Previous;
		LBSC_DList<TSerialNumber>::First;
		LBSC_DList<TSerialNumber>::Last;
		LBSC_DList<TSerialNumber>::Current;
		LBSC_DList<TSerialNumber>::Nth;
		LBSC_DList<TSerialNumber>::Search;
		LBSC_DList<TSerialNumber>::Find;
		LBSC_DList<TSerialNumber>::Add;
		LBSC_DList<TSerialNumber>::Update;
		LBSC_DList<TSerialNumber>::Del;
		LBSC_DList<TSerialNumber>::DelAll;
		LBSC_DList<TSerialNumber>::operator[];
};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _SERLST_H_
