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

