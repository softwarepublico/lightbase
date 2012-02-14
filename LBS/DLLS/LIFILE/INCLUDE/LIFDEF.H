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
// Module: LIFDEF.H
// Description:
//
//	Defines the export/import macros to use the LIFILE DLL
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 13/06/96
//


#ifndef	_LIFILE_DEFCLASS_H_
#define	_LIFILE_DEFCLASS_H_

#if defined (BUILDING_LIFILE_DLL)
#   if defined __BORLANDC__
#      define _LIFILECLASS _export
#      define _LIFILEFUNC  _export
#   else
#      define _LIFILECLASS	__declspec( dllexport )
#      define _LIFILEFUNC  __declspec( dllexport )
#   endif
#elif defined (LIFILE_DLL)
#   if defined __BORLANDC__
#      define _LIFILECLASS _import
#      define _LIFILEFUNC
#   else
#      define _LIFILECLASS	__declspec( dllimport )
#      define _LIFILEFUNC	__declspec( dllimport )
#   endif
#else
#   define _LIFILECLASS
#   define _LIFILEFUNC
#endif	// BUILDING_LIFILE_DLL

#if !defined __BORLANDC__
#	pragma warning(disable:4275)
#	pragma warning(disable:4251)
#endif

BOOL _LIFILEFUNC FinishLifile();

#endif	//_LIFILE_DEFCLASS_H_


