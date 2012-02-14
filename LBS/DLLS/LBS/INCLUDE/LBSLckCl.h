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
// Module: LBSLCKCL.H
// Description:
//
//	Header file for LB1_Lock handling.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 06/12/96
//

#ifndef	_LBSLCKCL_H_
#define	_LBSLCKCL_H_

#ifndef _LB1_
#include	<lb1cl.h>
#endif

class LBSC_LB1_LockHead
{
private:
	BOOL	bIsLocked;
	int		iLastError;
	C_LB1	*pLB1;

public:
			LBSC_LB1_LockHead( C_LB1 &, BOOL = TRUE );
			LBSC_LB1_LockHead();
			~LBSC_LB1_LockHead();
	int		LB1_LockHead( BOOL = TRUE );
	int		LB1_LockHead( C_LB1 &LB1_Par, BOOL = TRUE );

	int		LB1_ReleaseHead();
	BOOL	IsLocked();
	int		LastError();
};

#endif // _LBSLCKCL_H_



