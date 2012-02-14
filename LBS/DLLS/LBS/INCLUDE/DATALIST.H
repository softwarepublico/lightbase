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
// Module: DATALIST.H
//	LBSC_DataList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 28/09/94
//


#ifndef	_DATALIST_H_
#define	_DATALIST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_DATACL_H_
#include	<datacl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

class LBSC_DataList : public LBSC_DList<LBSC_Data>
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Field;
	friend	class	_LBSCLASS LBSC_Record;

	public:
				LBSC_DataList() : LBSC_DList<LBSC_Data>(){};
				~LBSC_DataList(){};
/***
				int DelAll();
				int NumElem();
				LBSC_Data *Nth( int );
				LBSC_Data *Current();
				int Add( LBSC_Data *, int, int = 0 );
				LBSC_Data *Refresh( LBSC_Data * );
				int Del();
				LBSC_Data *operator [] ( int );
				int GetCurrentIndex();
				operator =
***/
};

#endif // _DATALIST_H_


