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


#ifndef _ALGAUGE_H
#define _ALGAUGE_H

/*
 * These are all the different messages you can send to
 * an ALGauge object.  Our demo programs don't use any of these
 * except ALGaugeSetPosition, so most of these aren't even tested.
 */
typedef enum {
    ALGaugeSetRange       = WM_USER,
    ALGaugeGetRange,
    ALGaugeSetPosition,
    ALGaugeGetPosition,
    ALGaugeSetOrientation,
    ALGaugeGetOrientation,
    ALGaugeSetForegroundColor,
    ALGaugeGetForegroundColor,
    ALGaugeSetBackgroundColor,
    ALGaugeGetBackgroundColor,
    ALGaugeSetDeltaPosition,
} ALGaugeMessages;

/*
 * Send one of these with ALGaugeSetOrientation, to determined which
 * direction the flood fill progresses.
 */

typedef enum {
    ALGaugeOrientLeftToRight,
    ALGaugeOrientRightToLeft,
    ALGaugeOrientBottomToTop,
    ALGaugeOrientTopToBottom,
} ALGaugeOrientation;


/* 
 * public function prototypes 
 */

#ifdef __cplusplus
extern "C"
#endif
int AL_FUNCTION ALGaugeInit( HINSTANCE hInstance, HINSTANCE hPrevInstance );

#endif /* #ifdef _ALGAUGE_H */

