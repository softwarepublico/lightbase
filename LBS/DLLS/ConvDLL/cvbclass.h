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
// Module: CVBCLASS.H
// Description:
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 16/06/96
//


#ifndef	_CVB_DEFCLASS_H_
#define	_CVB_DEFCLASS_H_

#if defined (BUILDING_CONVBASE_DLL)
#	define _CONVBASECLASS	__declspec( dllexport )
#	define _CONVBASEFUNC	__declspec( dllexport )
#else
#	define _CONVBASECLASS
#	define _CONVBASEFUNC
#endif	// BUILDING__CONVBASE_DLL

#endif	//_CVB_DEFCLASS_H_


