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
// Module: CLLBSERR.H
// Description:
//
//	LBSCC_Error class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 26/02/96
//

#ifndef _LBSERRCL_H_
#define	_LBSERRCL_H_

#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef _LBSNETCL_H_
#include <lbsnetcl.h>
#endif

//	codigo de erro default da classe LBSC_Error
#define	LBSE_UNAVAILABLE	-510


class _LBSCLASS LBSC_Error : public LBSC_ClntNet 
{
private: 

	char szDesc[MAXERRORMSGSIZE];
	long lLastErr;

protected:

	long	lSessionObj;

   	TSRControlInfo ObtemControlInfo();

public:
		LBSC_Error()
		{
			lLastErr = LBSE_UNAVAILABLE;
		};
		~LBSC_Error(){};
		int		LastError();
		const char	*LastErrorDesc();
		static const char	*LastErrorDesc( int );
		void SetLastError( int iErr );
		static int LastErrorStatic();
};

#endif	// _LBSERRCL_H_



