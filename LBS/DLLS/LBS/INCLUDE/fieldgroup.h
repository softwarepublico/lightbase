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
// Module: FIELDGROUP.H
// Description:
//
//


#ifndef	_FIELDGROUP_H_
#define	_FIELDGROUP_H_

#ifndef	_FILISTCL_H_
#include	<filistcl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

class _LBSCLASS LBSC_FieldGroup
{
	friend	class	_LBSCLASS LBSC_Record;
	LBSC_FieldList	lbscflFieldList;
	public:
		int iGroup;

		LBSC_FieldGroup();
		~LBSC_FieldGroup();

		int Compare( LBSC_FieldGroup *, int );
		LBSC_FieldGroup *Duplicate();
};

class _LBSCLASS LBSC_FieldGroupList: public LBSC_DList<class LBSC_FieldGroup>
{
};

// nao usado por enquanto...
class _LBSCLASS LBSC_FieldGroupVector
{
public:
	LBSC_FieldGroup *pGroups;
	int				iSize;

	LBSC_FieldGroupVector( int iSize );
	~LBSC_FieldGroupVector();
	LBSC_FieldGroup *Find( int iGroup );
	void Sort();
};

#endif	// _FIELDGROUP_H_


