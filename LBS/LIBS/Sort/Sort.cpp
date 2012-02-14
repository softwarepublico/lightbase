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


/************************************************************
//
// Classe: SortObject
//
// M�todos principais da classe (Construtor, Destrutor e Sort)
//
//
**************************************************************/


#include <Sort.h>

int __cdecl
CompareFunc( const void *pvElem1, const void *pvElem2 )
{
	SortKey *pKey1 = (SortKey *)pvElem1;
	SortKey *pKey2 = (SortKey *)pvElem2;

	return ((SortObject *)(pKey1->pSortObject))->Compare( pKey1->pvKey, pKey2->pvKey );
}



BOOL SortObject::StartSort( void )
{
    if( BuildStatus != BUILDISOK ){
        return FALSE;
	}
	pKeys = new SortKey	[nKeys];		
	if ( pKeys == NULL ){
		return FALSE;
	}
	memset( pKeys, 0, sizeof(SortKey) * nKeys );
	SortData();
	DWORD j;
	for( j = 0; j < nKeys; ++j ){
        PutData( pKeys[ j ].pvKey ); 
    }

	return TRUE;
}


BOOL SortObject::SortData( void )
{
	DWORD nk = 0;
	for ( nk = 0; nk < nKeys; nk++ ){
		pKeys[ nk ].pSortObject = (void *)this;
        if( !GetData( pKeys[ nk ].pvKey ) ) break;
    }
    if( !nk )
    {
        return FALSE;
    }
	nKeys = nk;
	BuildStatus = BUILDISOK;
    qsort( (void*) pKeys, (size_t)nKeys, sizeof ( SortKey ) , CompareFunc );
	return TRUE;
}

SortObject::SortObject( DWORD nkeys )
{
	pKeys = NULL;
	SetParms( nkeys );
    BuildStatus = BUILDISOK;
    return;
}

SortObject::SortObject( void )
{
	pKeys = NULL;
    BuildStatus = BUILDFAULT;
    return;

}

BOOL SortObject::SetParms( DWORD nkeys )
{
    nKeys = nkeys;
	BuildStatus = BUILDISOK;
    return TRUE;
}

SortObject::~SortObject( void )
{
	if ( pKeys != NULL ){
		delete pKeys;
	}
}
