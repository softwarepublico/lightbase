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


#ifndef _AL_H
#define _AL_H

#include "arclib.h"

/* 
 * Derived classes 
 */

#include "filestor.h"
#include "memstore.h"
#include "copyengn.h"
#include "grenengn.h"
#include "archive.h"

/* 
 * Demo classes and functions 
 */

#if defined( AL_WINDOWS_GUI )
#  include "winmon.h"
#  include "algauge.h"
#  include "alstream.h"
#else
#  include "bargraph.h"
#  include "spinner.h"
#endif

/*
 * Additional classes 
 */
#include "wildcard.h"

#endif /* #ifdef _AL_H */
