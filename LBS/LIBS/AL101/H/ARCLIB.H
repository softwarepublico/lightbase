/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o 
t�tulo "LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef _ARCLIB_H
#define _ARCLIB_H

/*
 * Want to customize the workings of our library?  Just define AL_CUSTOM,
 * and then create your own personal version of ALCUSTOM.H. (No, we don't
 * ship a copy of this header file with the library, it is for you to
 * define.  This is a really good way to use products like MEMCHECK or
 * SmartHeap that want to insert an included file in every one of
 * our source files.
 */

#if defined( AL_CUSTOM )
#include "alcustom.h"
#endif

#if defined( __cplusplus )

/* All these includes needed for various library features */

#include "iostream.h"
#include "string.h"

#include "aldefs.h"
#include "_debug.h"

/* Base classes */

#include "status.h"
#include "objname.h"
#include "stor.h"
#include "cmpengn.h"
#include "monitor.h"
#include "arcentry.h"
#include "cmpobj.h"
#include "archiveb.h"

#if defined( AL_SUN4 ) && defined( AL_GCC )

extern "C" int strcasecmp( const char *s1, const char *s2 );

#endif

#else  /* #if defined( __cplusplus )                 */

#include "alcxl.h"  /* Included only if we are compiling C code, not C++ */

#endif /* #if defined( __cplusplus ) ... #else       */

#endif /* ARCLIB_H */
