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

// arquivo de includes genericos
// 30-08-95
// Adriano Sergio


#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#ifdef __BORLANDC__
#       define  DIR_H           <dir.h>
#       define  VALUES_H        <values.h>
#       define  BORDATE_H       <classlib\\date.h>
#       define  BORTIME_H       <classlib\\time.h>
#       define  BORDEFS_H       <_defs.h>
#       define  MEM_H           <mem.h>
#       define  NULL_H          <_null.h>
#       define  DIRENT_H        <dirent.h>
#elif defined __WATCOMC__
#       define  DIR_H           <direct.h>
#       define  VALUES_H        <limits.h>
#       define  BORDATE_H       <classlib\\date.h>
#       define  BORTIME_H       <classlib\\time.h>
#       define  BORDEFS_H       <stddef.h>
#       define  MEM_H           <mem.h>
#       define  NULL_H          <stddef.h>
#       define  DIRENT_H        <direct.h>
#else
#       define  DIR_H           <direct.h>
#       define  VALUES_H        <limits.h>
#       define  BORDATE_H       <classlib\\date.h>
#       define  BORTIME_H       <classlib\\time.h>
#       define  BORDEFS_H       <classlib\\_defs.h>
#       define  MEM_H           <memory.h>
#       define  NULL_H          <stddef.h>
#       define  DIRENT_H        <direct.h>
#endif


#endif  // _INCLUDES_H_

