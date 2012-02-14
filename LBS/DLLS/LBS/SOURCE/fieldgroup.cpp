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
// Module: FIELDGROUP.CPP
// Description:
//
//


#include	<fieldgroup.h>

LBSC_FieldGroup::LBSC_FieldGroup()
{
	iGroup = 0;
}

LBSC_FieldGroup::~LBSC_FieldGroup()
{
	// temos que setar referencias nulas para o destrutor da lista nao matar os 
	// objetos field 
	for ( int i=0; i<lbscflFieldList.NumElem(); i++ ) {
		LBSC_Field *pf = lbscflFieldList[i];
		lbscflFieldList.Refresh( NULL );
	}
}

int LBSC_FieldGroup::Compare( LBSC_FieldGroup *pOther, int )
{
	return iGroup - pOther->iGroup;
}

LBSC_FieldGroup *LBSC_FieldGroup::Duplicate()
{
	LBSC_FieldGroup *pNew = new LBSC_FieldGroup;
	if ( pNew ) {
		pNew->iGroup = iGroup;
		pNew->lbscflFieldList = lbscflFieldList;
	}
	return NULL;
}

// ===================================================================
// nao usado ainda....

LBSC_FieldGroupVector::LBSC_FieldGroupVector( int iNewSize ) 
{
	pGroups = new LBSC_FieldGroup[iNewSize];
	if ( pGroups ) {
		iSize = iNewSize;
	}
}


LBSC_FieldGroupVector::~LBSC_FieldGroupVector() 
{
	if ( pGroups ) {
		delete pGroups;
	}
}

int cmp_by_fieldgroup( const void *a, const void *b )
{
	LBSC_FieldGroup *pGroupA = (LBSC_FieldGroup*)a;
	LBSC_FieldGroup *pGroupB = (LBSC_FieldGroup*)b;
	return pGroupA->iGroup - pGroupB->iGroup;
}

int cmp_by_group( const void *a, const void *b )
{
	int iGroup = *((int*)a);
	LBSC_FieldGroup *pGroupB = (LBSC_FieldGroup*)b;
	return iGroup - pGroupB->iGroup;
}


LBSC_FieldGroup *LBSC_FieldGroupVector::Find( int iGroup )
{
	if ( iSize <=0 ) {
		return NULL;
	}
	return ((LBSC_FieldGroup *)bsearch( &iGroup, pGroups, iSize, sizeof( LBSC_FieldGroup ), cmp_by_group ));
}


void LBSC_FieldGroupVector::Sort()
{
	if ( iSize <=0 ) {
		return;
	}
	qsort( pGroups, iSize, sizeof( LBSC_FieldGroup ), cmp_by_fieldgroup );
}

