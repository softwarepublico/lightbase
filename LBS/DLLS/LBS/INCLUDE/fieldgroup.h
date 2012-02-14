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


