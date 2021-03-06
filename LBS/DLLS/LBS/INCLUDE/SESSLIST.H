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
// Module: SESSLIST.H
//	LBSC_SessionList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 20/01/96
//


#ifndef	_SESSLIST_H_
#define	_SESSLIST_H_

#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


class _LBSCLASS LBSC_SessionList : LBSC_DList<LBSC_Session>
{
	public:
		BOOL		bIsDying;	// indica se o destrutor da lista esta'
						// sendo executado

				LBSC_SessionList() : LBSC_DList<LBSC_Session>()
				{
					bIsDying = FALSE;
				};
				~LBSC_SessionList()
				{
					EnterCriticalSection( 0 );
						bIsDying = TRUE;
					LeaveCriticalSection( 0 );
				};
		LBSC_DList<LBSC_Session>::NumElem;
		LBSC_DList<LBSC_Session>::Next;
		LBSC_DList<LBSC_Session>::Previous;
		LBSC_DList<LBSC_Session>::First;
		LBSC_DList<LBSC_Session>::Last;
		LBSC_DList<LBSC_Session>::Current;
		LBSC_DList<LBSC_Session>::Nth;
		LBSC_DList<LBSC_Session>::Search;
		LBSC_DList<LBSC_Session>::Find;
		LBSC_DList<LBSC_Session>::Add;
		LBSC_DList<LBSC_Session>::Update;
		LBSC_DList<LBSC_Session>::Del;
		LBSC_DList<LBSC_Session>::DelAll;
		LBSC_DList<LBSC_Session>::Refresh;
		LBSC_DList<LBSC_Session>::GetCurrentIndex;
		LBSC_DList<LBSC_Session>::operator[];
};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _SESSLIST_H_

