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
// Module: EXPLIST.H
//	LBSC_ExportList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 07/10/94
//


#ifndef	_EXPORTLIST_H_
#define	_EXPORTLIST_H_

#ifndef	_LBSTEMPLATE_H_
#include <lbstempl.h>
#endif
#ifndef	_LBSTYPES_H_
#include <lbstypes.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_ExportBaseList : LBSC_DList<TExportBase>
{
	public:
				LBSC_ExportBaseList() : LBSC_DList<TExportBase>(){};
				~LBSC_ExportBaseList(){};
		LBSC_DList<TExportBase>::NumElem;
		LBSC_DList<TExportBase>::Next;
		LBSC_DList<TExportBase>::Previous;
		LBSC_DList<TExportBase>::First;
		LBSC_DList<TExportBase>::Last;
		LBSC_DList<TExportBase>::Current;
		LBSC_DList<TExportBase>::Nth;
		LBSC_DList<TExportBase>::Search;
		LBSC_DList<TExportBase>::Find;
		LBSC_DList<TExportBase>::Add;
		LBSC_DList<TExportBase>::Update;
		LBSC_DList<TExportBase>::Del;
		LBSC_DList<TExportBase>::DelAll;
		LBSC_DList<TExportBase>::operator[];
};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _EXPORTLIST_H_

