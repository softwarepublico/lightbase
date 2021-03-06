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
// Module: USRINFOL.H
//	LBSC_AppUserInfoList class definition file
//	LBSC_AppNetInfoList class definition file
//	LBSC_AppSessionNetInfoList class definition file
//	LBSC_AppBaseNetInfoList class definition file
//
// Programmer:	Adriano Sergio R. Souza
//
// Last revision: 30/08/96
//


#ifndef	_USRINFOL_H_
#define	_USRINFOL_H_

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


class _LBSCLASS LBSC_AppUserInfoList : public LBSC_DList<TAppUserNetInfo>
{
};


class _LBSCLASS LBSC_AppNetInfoList : public LBSC_DList<TAppNetInfo>
{
};


class _LBSCLASS LBSC_AppSessionNetInfoList : public LBSC_DList<TAppSessionNetInfo>
{
};


class _LBSCLASS LBSC_AppBaseNetInfoList : public LBSC_DList<TAppBaseNetInfo>
{
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _USRINFOL_H_

