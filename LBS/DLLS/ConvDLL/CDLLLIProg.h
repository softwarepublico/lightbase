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
//  LIGHT-INFOCON
//
//  Modulo        : CDLLLIProg.h
//  Descricao     : * Header necessario para o control progress bar 
//					implementado pela LI.
//					* Prototipo da funcao RegisterProgressClass.
//					usada para registrar a classe.
//  Programadores : Alessandro Araujo Jatobá
//  Alteracoes    :
//

#ifndef	_PROGRESS_H_
#define	_PROGRESS_H_

#ifndef __AFXWIN_H__
#include	<afxwin.h>
#endif 
#ifndef _INC_COMMCTRL
#include	<COMMCTRL.H>
#endif 

void RegisterProgressClass( HINSTANCE );

#endif
