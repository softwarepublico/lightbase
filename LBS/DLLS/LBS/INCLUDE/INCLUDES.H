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

