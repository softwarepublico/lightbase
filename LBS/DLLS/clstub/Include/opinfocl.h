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