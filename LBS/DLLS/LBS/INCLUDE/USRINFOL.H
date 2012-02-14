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

