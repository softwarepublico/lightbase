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
// Module: DEFCLASS.H
// Description:
//
//	Defines the export/import macros to use the LBS DLL
//	This file must be included by all the files that
//	intend to export classes
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//
// Last update: 19/10/94
//


#ifndef	_LBS_DEFCLASS_H_
#define	_LBS_DEFCLASS_H_

#if defined (BUILDING_LBS_DLL)
#   if defined __BORLANDC__
#      define _LBSCLASS _export
#      define _LBSFUNC  _export
#   else
#      define _LBSCLASS	__declspec( dllexport )
#      define _LBSFUNC  __declspec( dllexport )
#   endif
#elif defined (LBS_DLL)
#   if defined __BORLANDC__
#      define _LBSCLASS _import
#      define _LBSFUNC
#   else
#      define _LBSCLASS	__declspec( dllimport )
#      define _LBSFUNC	__declspec( dllimport )
#   endif
#else
#   define _LBSCLASS
#   define _LBSFUNC
#endif	// BUILDING_LBS_DLL

#if !defined __BORLANDC__
#	pragma warning(disable:4275)
#	pragma warning(disable:4251)
#endif

#endif	//_LBS_DEFCLASS_H_


