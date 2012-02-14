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

#ifndef	_OPINFO_H_
#define	_OPINFO_H_

#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_CRITSECT_H_
#include	<critsect.h>
#endif
#ifndef _CL_STRINGN_
#include	<stringn.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#include	<lbserror.h>
#ifndef _LBSERRCL_H_
#include	<cllbserr.h>
#endif

class _LBSCLASS LBSC_OpInfo : public LBSC_Error
{
public:
	int		iDummy;

			LBSC_OpInfo()
			{
				iDummy = 0;
			}
			~LBSC_OpInfo()
			{
			}
	void	CancelOperation();				// cancela a operacao corrente
	void	GetOpInfo( char *szActionPar, float *pfPercentPar );	// obtem o status da operacao corrente


};

#endif