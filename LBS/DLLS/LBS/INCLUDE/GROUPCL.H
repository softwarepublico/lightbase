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
// Module: GROUPCL.H
// Description:
//
//	LBSC_GROUP class definition group.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 30/09/94
//

#ifndef	_GROUPCL_H_
#define	_GROUPCL_H_

#ifndef	_LBSDEFS_H_
#include <lbsdefs.h>
#endif
#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef	_LBSTYPES_H_
#include <lbstypes.h>
#endif

class	LBSC_Group
{
	public:
		UserSTR		strUserName;
		DescSTR		strDescription;

				LBSC_Group( const char *, const char * );
				~LBSC_Group();
		int		ModifyDescription( const char * );
		int		Compare( LBSC_Group *, int ) { return( LBS_OK ); };
		LBSC_Group	*Duplicate() { return( NULL ); };
};

#endif _GROUPCL_H_
