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
// Module: PRINTF.H
// Description:
//
//	Printf function definition file.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 02/01/96
//

#ifndef	_PRINTF_H_
#define	_PRINTF_H_


extern	BOOL	CreateLogWindow( HINSTANCE, char * );
extern	void	DestroyLogWindow();
extern	void	EnableLog( BOOL );
///extern	void	Printf( char *, ... );
/*
BOOL	CreateLogWindow( HINSTANCE, char * );
void	DestroyLogWindow();
void	EnableLog( BOOL );
void	Printf( char *, ... );
*/

#endif	// _PRINTF_H_


