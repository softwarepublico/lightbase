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



