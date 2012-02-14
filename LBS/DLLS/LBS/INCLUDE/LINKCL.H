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
// Module: LINKCL.H
// Description:
//
//	Header file for link handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 28/09/94
//

#ifndef	_LINKCL_H_
#define	_LINKCL_H_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_CL_STRINGN_
#include	<stringn.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#if !defined NULL && !defined _INC_STDDEF
#include	NULL_H
#endif

typedef int                 BOOL;
typedef unsigned char       BYTE;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


class _LBSCLASS LBSC_Base;

class _LBSCLASS LBSC_Link
{
	private:
		CL_StringN<FULLNAMESIZE>	szSlaveBaseName;
		CL_StringN<FULLNAMESIZE>	szMasterBaseName;
		CL_StringN<FIELDNAMESIZE>	szSlaveFieldName;
		CL_StringN<FIELDNAMESIZE>	szMasterFieldName;
		BOOL		bPropagate;
		BOOL		bActive;
		BYTE		bLinkType;
		LBSC_Base	*plbscSlaveBase;
		LBSC_Base	*plbscMasterBase;

		int		SetSlaveBaseAddr( LBSC_Base * );
		int		SetMasterBaseAddr( LBSC_Base * );

	public:
					LBSC_Link( char *, char *, char *, char *, BOOL, BOOL, BYTE );
					~LBSC_Link();
		int			ModifyPropagateFlag( BOOL );
		int			ModifyActiveFlag( BOOL );
		int			Compare( LBSC_Link *, int ) { return( 0 ); };
                LBSC_Link		*Duplicate() { return( NULL ); };
};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _LINKCL_H_


