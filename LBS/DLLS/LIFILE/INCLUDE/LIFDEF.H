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


