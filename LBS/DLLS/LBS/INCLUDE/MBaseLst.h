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
// Module: MBASELST.H
// Description:
//
//	LBSC_MaintBasesList class definition file.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 16/09/98
//

#ifndef	_MBASELST_H_
#define	_MBASELST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_MBASE_H_
#include	<MBase.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


class _LBSCLASS LBSC_MaintBasesList : public LBSC_DList<LBSC_MaintBase>
{
	public:
		LBSC_MaintBasesList() : LBSC_DList<LBSC_MaintBase>()
		{
		};
		~LBSC_MaintBasesList(){};
};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _MBASELST_H_


