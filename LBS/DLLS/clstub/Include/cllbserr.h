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



