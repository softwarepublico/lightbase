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

// Prototipos das funcoes globais

#ifndef	_FUNCP_H_
#define	_FUNCP_H_

#include	<defclass.h>
#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif

typedef	int (CALLBACK *LBSERRPROC)();

int		_LBSFUNC	StartLBS();
int		_LBSFUNC	EndLBS();
void	_LBSFUNC	SetErrorFunc( LBSERRPROC );

#ifdef __BORLANDC__
void	*_LBSFUNC	LBS_Realloc( void *, int, int );
#else
void	_LBSFUNC	*LBS_Realloc( void *, int, int );
#endif

BOOL	_LBSFUNC	VerifySerialNumber( char * );
int		_LBSFUNC	GetControlFileVersion( char *szFileName );
int		_LBSFUNC	MakeDir( char *szDirName );

#endif	//_FUNCP_H_



