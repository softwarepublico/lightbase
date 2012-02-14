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


#ifndef _SESSCL_H_
	#include	<sesscl.h>  
#endif	// _SESSCL_H_

#ifndef _BASECL_H_
	#include	<basecl.h>  
#endif	// _BASECL_H_

#ifndef	_BASECACH_H_
	#include <basecach.h>
#endif

#ifndef _ADMDEFS_H_
	#include <admdefs.h>
#endif	// _ADMDEFS_H_

#include <clientconfig.h>


////////////////////////////////////////////////////////////////////////
//	CLASSE CCache
////////////////////////////////////////////////////////////////////////

CCache::CCache( LBSC_Base *pBase )
{
	pCache = NULL;
	pOwnerBase = pBase;
	lTentat = 0;
	lMinTentat = MINGENERALCACHE_TENTAT;
}


void 
CCache::InvalidaCache()
{
	lTentat = 0;
	if ( pCache ) {
		DeleteCache();
	}
	if ( pOwnerBase ) {
		pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache
	}
	pCache = NULL;
}


BOOL 
CCache::IsCacheValid()
{
	return pCache != NULL;
}


BOOL 
CCache::UsandoCache()
{
	return LBSC_ClientConfig::Cache();
}

BOOL 
CCache::PodeUsarCache()
{
	lTentat = (lTentat == MAXLONG || lTentat < 0) ? lMinTentat : lTentat+1; 

	return (lTentat >= lMinTentat || pCache != NULL);
}



////////////////////////////////////////////////////////////////////////
//	CLASSE CACL_Cache
////////////////////////////////////////////////////////////////////////

CACL_Cache::~CACL_Cache()
{
	DeleteCache();
	pCache = NULL;
}

BOOL 
CACL_Cache::UsandoCache()
{
	if ( LBSC_ClientConfig::AclCache() ) {
		return CCache::UsandoCache();
	}

	return FALSE;
}

//
//	Atualiza a cache de ACL; havendo algum erro no meio do processamento
//	retorne e deixe a cache invalida
//
void 
CACL_Cache::AtualizaCache()
{
	InvalidaCache();

	if ( !pOwnerBase ) {
		return;
	}

	// chama o servidor para trazer a cache
	TACL_Lists	*ptaclAllACLs = pOwnerBase->GetAllACLLists( 
					pOwnerBase->GetTicket() );

	// testa se o retorno do servidor foi OK
	if ( !ptaclAllACLs ) {
		return;
	}

	// Atualizando o ponteiro da cache 
	pCache = ptaclAllACLs;

}

void 
CACL_Cache::DeleteCache()
{
	if ( !pCache ) {
		return;
	}

	LBSC_Session::Delete((TACL_Lists *)pCache);

	pCache = NULL;
}


//
//	Retorna a máscara de ACL relativa ao usuário ou grupo (szName), 
//	para o campo ou registro (lId), da lista especificada em iList; 
//	em caso de erro, retorna um código do LBS ou -1 se a informação 
//	não estiver disponível na cache. Neste caso a aplicação deve 
//	prosseguir o processamento (chamando o servidor normalmente).
//
int 
CACL_Cache::GetACLPerm_Cache( char *szName, long lId, int iList, BOOL bCheckAll )
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu atualizar a cache
			return -1;
		}
	}

	//	Se deseja ACL de registro retorne -1 ou se o id de campo eh 
	//	ID_BASE ou ID_ASTERISC, sao necessarios tratamentos especiais
	//	(deve-se consultar o servidor)
	if( iList == USERRECORD || iList == GROUPRECORD || lId == ID_BASE
					|| lId == ID_ASTERISK ) {
		return -1;
	}

	TACL_Lists *ptaclAllACLsCache = (TACL_Lists *)pCache;

	// Se a base eh publica, pode tudo
	if ( ptaclAllACLsCache->bBaseType == BASE_PUBLIC ) {
		return ACL_ADM;
	}

	// Se for uma UDB, pergunte ao servidor
	if ( ptaclAllACLsCache->bBaseType == USER_BASE ) {
		return -1;
	}

	if ( ptaclAllACLsCache->bBaseType == BASE_PUBLIC_REC_PRIVATE &&
	    iList != USERRECORD && iList != GROUPRECORD ) {
    	// a base eh publica com restricao de registro e
		// a ACL pedida nao eh de registro
		return ACL_ADM;
	}

	// Se o usuario eh o dono da base, pode tudo
	if ( stricmp( szName, ptaclAllACLsCache->strUserName ) == 0) {
		return ACL_ADM;
	}

	LBSC_ACLList	*plbscalACLList;
	switch ( iList ) {
	case USERBASE:
		plbscalACLList = &ptaclAllACLsCache->lUserBase;
		break;
	case GROUPBASE:
		plbscalACLList = &ptaclAllACLsCache->lGroupBase;
		break;
	case USERFIELD:
		plbscalACLList = &ptaclAllACLsCache->lUserField;
		break;
	case GROUPFIELD:
		plbscalACLList = &ptaclAllACLsCache->lGroupField;
		break;
	case USERRECORD:
		plbscalACLList = &ptaclAllACLsCache->lUserRecord;
		break;
	case GROUPRECORD:
		plbscalACLList = &ptaclAllACLsCache->lGroupRecord;
		break;
	default:
		return -1;	// nao eh nenhuma lista conhecida pela cache
	}

	// procura por szName e lId na lista de ACL; se achar retorne a 
	//permissão do item corrente da lista. 
	if( plbscalACLList->ACLFind( szName, lId ) == LBS_OK ){
		return( plbscalACLList->Current()->lbscplPermList.Current()->bPermission );
	}

	if ( iList == USERRECORD ) {
		return( LBSE_UNDEFINEDACL );	// ACL indefinida
	}

	// nao achamos a ACL na cache; teremos que chamar o servidor mesmo
	return -1;
}



////////////////////////////////////////////////////////////////////////
//	CLASSE CRep_Cache
////////////////////////////////////////////////////////////////////////

//
// Funcoes para pesquisas nos arrays de campos
//
int CompareFieldInfoByAlias( const void *Key1, const void *Key2 )
{
	return strcmp( ((FieldInfoAux *)Key1)->szFieldName, ((FieldInfoAux *)Key2)->szFieldName );
}
int CompareFieldInfoById( const void *Key1, const void *Key2 )
{
	return ( ((FieldInfo *)Key1)->uiId - ((FieldInfo *)Key2)->uiId );
}
int CompareBufferHeader( const void *Key1, const void *Key2 )
{
	return ( ((TRecordBufferHeader *)Key1)->lId - ((TRecordBufferHeader *)Key2)->lId );
}

RepInfo::RepInfo()
{
	pvRep = NULL;
	lMaxSize = 0;
	lCurSize = 0;
}

RepInfo::~RepInfo()
{
	if ( pvRep ) {
		delete pvRep;
	}
}

void RepInfo::FreeRepetition()
{
	if ( pvRep ) {
		delete pvRep;
	}
	pvRep = NULL;
	lMaxSize = 0;
	lCurSize = 0;
}


FieldInfo::FieldInfo()
{
	uiId = 0;
	bFieldType = 0;
	strcpy(szFieldName, "");
	pRepetitions = NULL;
	lNumRep = 0;
	bValid = FALSE;
}

FieldInfo::~FieldInfo()
{
	FreeRepetitions();
}

void FieldInfo::FreeRepetitions()
{
	if ( pRepetitions ) {
		delete [] pRepetitions;
		pRepetitions = NULL;
	}
	bValid = FALSE;
	lNumRep = 0;
}

FieldInfoAux::FieldInfoAux()
{
	lPos = 0;
	strcpy(szFieldName, "");
}


CRep_Cache::CRep_Cache( LBSC_Base *pBase ) : CCache( pBase )
{
	lMinTentat = MINREPCACHE_TENTAT;
	pRecordFieldsHeader = NULL;
	lNumFieldsInHeader = 0;
	pFieldInfoAux = NULL;
	pFieldInfoById = NULL;
	lNumFieldsInBase = 0;
	lRecNum = -1;
}

CRep_Cache::~CRep_Cache()
{
	DeleteCache();
	if ( pFieldInfoAux ) {
		delete pFieldInfoAux;
	}
	pFieldInfoAux = NULL;
	if ( pFieldInfoById ) {
		delete [] pFieldInfoById;
	}
	pFieldInfoById = NULL;

	pCache = NULL;
}

FieldInfo * 
CRep_Cache::GetFieldFromAlias( char *szAlias )
{
	if ( !pFieldInfoAux || !pRecordFieldsHeader ) {
		return NULL;
	}
	FieldInfoAux	fieldAux;
	strncpy( fieldAux.szFieldName, szAlias, FIELDNAMESIZE );
	FieldInfoAux	*pField = (FieldInfoAux *)bsearch( (void *)&fieldAux, pFieldInfoAux, lNumFieldsInBase, sizeof(FieldInfoAux), CompareFieldInfoByAlias );
	if ( !pField ) {
		return NULL;
	}

	return &(pFieldInfoById[pField->lPos]);
}


FieldInfo * 
CRep_Cache::GetFieldFromId( UINT uId )
{
	if ( !pFieldInfoById || !pRecordFieldsHeader ) {
		return NULL;
	}
	FieldInfo	fieldAux;
	fieldAux.uiId = uId;
	FieldInfo	*pField = (FieldInfo *)bsearch( (void *)&fieldAux, pFieldInfoById, lNumFieldsInBase, sizeof(FieldInfo), CompareFieldInfoById );

	return pField;
}

void CRep_Cache::SetFieldsInfo( TField *ptfFields )
{
	if ( pFieldInfoAux ) {
		delete pFieldInfoAux;
	}
	pFieldInfoAux = NULL;
	if ( pFieldInfoById ) {
		delete [] pFieldInfoById;
	}
	pFieldInfoById = NULL;
	lNumFieldsInBase = 0;

	if( !ptfFields ){
		return;
	}

	// primeiro vamos contar a lista de campos...
	for( int i = 0; (!ptfFields[ i ].IsZero()); i++ ){
		;
	}

	if ( i == 0 ) {
		return;
	}
	lNumFieldsInBase = i;

	pFieldInfoAux = new FieldInfoAux[lNumFieldsInBase];
	if ( !pFieldInfoAux ) {
		lNumFieldsInBase = 0;
		return;
	}
	pFieldInfoById = new FieldInfo[lNumFieldsInBase];
	if ( !pFieldInfoById ) {
		delete pFieldInfoAux;
		pFieldInfoAux = NULL;
		lNumFieldsInBase = 0;
		return;
	}

	// agora vamos preenche os buffers
	for( i = 0; i<lNumFieldsInBase; i++ ){
		strncpy( pFieldInfoAux[i].szFieldName, ptfFields[i].szFieldAliasName, FIELDNAMESIZE );
		pFieldInfoAux[i].lPos = i;

		strncpy( pFieldInfoById[i].szFieldName, ptfFields[i].szFieldAliasName, FIELDNAMESIZE );
		pFieldInfoById[i].uiId = ptfFields[i].uiFieldId;
		pFieldInfoById[i].bFieldType = ptfFields[i].tftFieldType;
	}

	qsort( pFieldInfoAux, lNumFieldsInBase, sizeof(FieldInfoAux), CompareFieldInfoByAlias );
	qsort( pFieldInfoById, lNumFieldsInBase, sizeof(FieldInfo), CompareFieldInfoById );
}


/**
	Gera as repeticoes do campo a partir do buffer armazenado com formato definido no metodo GetRecordBuffer
	OBS: o campo pode nao mais existir na base, mas mesmo assim o buffer deve ser processado
**/
BOOL 
CRep_Cache::GetRepetition(int iRep, FieldInfo *pField, void *pvRep, long *plRepSize )
{
	C_Buffer *pRecordBuffer = (C_Buffer *)pCache;
	if ( !pRecordBuffer ) {
		return FALSE;
	}
	if ( !pField->bValid ) {

		TRecordBufferHeader	headerAux;
		headerAux.lId = pField->uiId;
		TRecordBufferHeader	*pHeader = (TRecordBufferHeader *)bsearch( (void *)&headerAux, pRecordFieldsHeader, lNumFieldsInHeader, sizeof(TRecordBufferHeader), CompareBufferHeader );
		if ( !pHeader ) {
			return FALSE;
		}
		if ( pHeader->lNumRep > pField->lNumRep ) {
			// realoca pro novo tamanho
			pField->FreeRepetitions();
			pField->pRepetitions = new RepInfo[pHeader->lNumRep];
			if ( !pField->pRepetitions ) {
				return FALSE;
			}
		}
		pField->lNumRep = pHeader->lNumRep;
		if ( !pRecordBuffer->SetMyPos( pHeader->lOffSet ) ) {
			return FALSE;
		}
		for ( int i=0; i<pField->lNumRep; i++ ) {	
			if ( !Read(pField, i) ) {
				return FALSE;
			}
		}
		pField->bValid = TRUE;
	}
	if ( iRep == -1 ) {	// so pra forcar a leitura
		return TRUE;
	}
	if ( iRep >= pField->lNumRep ) {
		return FALSE;
	}
	if ( plRepSize ) {
		*plRepSize = pField->pRepetitions[iRep].lCurSize;
	}
	if ( pField->pRepetitions[iRep].lCurSize == 0 ) {
		return TRUE;
	}
	if ( pvRep ) {
		memcpy( pvRep, pField->pRepetitions[iRep].pvRep, pField->pRepetitions[iRep].lCurSize );
	}
	return TRUE;
}


BOOL 
CRep_Cache::Read( FieldInfo *pField, int iRep)
{
	BYTE bIsNull = FALSE;	// eh nulo ?
	C_Buffer *pRecordBuffer = (C_Buffer *)pCache;
	if ( !pRecordBuffer ) {
		return FALSE;
	}
	if ( !pRecordBuffer->GetData( (void *)&bIsNull, sizeof(BYTE) ) ) {
		return FALSE;
	}

	if ( bIsNull ) {
		pField->pRepetitions[iRep].lCurSize = 0;
		return TRUE;
	}

	long lRepSize = 0;
	switch( pField->bFieldType ) {
	case ALPHA_FIELD:
	case TEXT_FIELD:
	case BINARY_FIELD:
	case REFERENCED_FIELD:
		if ( !pRecordBuffer->GetData( (void *)&lRepSize, sizeof(long) ) ) {	// le o tamanho do conteudo
			return FALSE;
		}
		break;
	case VALUE_FIELD:
		lRepSize = sizeof( long );
		break;
	case DVALUE_FIELD:
		lRepSize = sizeof( double );
		break;
	case DATE_FIELD:
		lRepSize = sizeof( JulTy );
		break;
	case TIME_FIELD:
		lRepSize = sizeof( ClockTy );
		break;
	case BYTE_FIELD:
		lRepSize = sizeof( BYTE );
		break;
	case SINT_FIELD:
		lRepSize = sizeof( short int );
		break;
	case FLOAT_FIELD:
		lRepSize = sizeof( float );
		break;
	default:
		return FALSE;
	}
	if ( lRepSize == 0 ) {
		pField->pRepetitions[iRep].lCurSize = 0;
		return TRUE;
	}

	if ( lRepSize > pField->pRepetitions[iRep].lMaxSize ) {
		// realoca pro novo tamanho
		pField->pRepetitions[iRep].FreeRepetition();
		pField->pRepetitions[iRep].pvRep = (void *)new char[lRepSize];
		pField->pRepetitions[iRep].lCurSize = pField->pRepetitions[iRep].lMaxSize = lRepSize;
	}
	if ( !pField->pRepetitions[iRep].pvRep ) {
		return FALSE;
	}
	pField->pRepetitions[iRep].lCurSize = lRepSize;

	if ( !pRecordBuffer->GetData( pField->pRepetitions[iRep].pvRep, pField->pRepetitions[iRep].lCurSize ) ) {	// le a repeticao
		return FALSE;
	}
	return TRUE;
}

//
//	Atualizar o contexto no servidor para que o registro corrente la 
//	seja o mesmo que o da cache. So faz isso se o numero de registros
//	na cache for maior que 1.
//
void 
CRep_Cache::AtualizaSvcContext()
{
}


BOOL 
CRep_Cache::UsandoCache()
{
	if ( LBSC_ClientConfig::RepCache() ) {
		return CCache::UsandoCache();
	}

	return FALSE;
}

//
//	Atualiza a cache com uma lista de registros; mapeia o retorno do
//	metodo GetAllRepetitions (que uma tira de bytes) para uma lista
//
void 
CRep_Cache::AtualizaCache()
{
	InvalidaCache();

	if ( !pOwnerBase ) {
		return;
	}

	C_Buffer *pBuff = pOwnerBase->GetAllRepetitions( pOwnerBase->GetTicket(), 
							1 );
	if ( !pBuff ) {
		return;
	}
	
	BYTE bCompressed = FALSE;
	long lMaxBufSize = 0;
	long lBufSize = 0;

	pBuff->Rewind();
	if ( !pBuff->GetData( (void *)&bCompressed, sizeof(BYTE) ) ) { // esta compactado? 
		delete pBuff;
		return;
	}
	if ( !pBuff->GetData( (void *)&lMaxBufSize, sizeof(long) ) ) { // tam. maximo do buffer  
		delete pBuff;
		return;
	}
	if ( !pBuff->GetData( (void *)&lBufSize, sizeof(long) ) ) { // tam. efetivo do buffer  
		delete pBuff;
		return;
	}
	if ( !pBuff->GetData( (void *)&lRecNum, sizeof(long) ) ) { // num registro corrente 
		delete pBuff;
		return;
	}
	if ( !pBuff->GetData( (void *)&lNumFieldsInHeader, sizeof(long) ) ) { // num. de campos 
		delete pBuff;
		return;
	}
	if ( !lNumFieldsInHeader ) {
		delete pBuff;
		return;
	}

	// header de campos
	pRecordFieldsHeader = new TRecordBufferHeader[lNumFieldsInHeader];
	if ( !pRecordFieldsHeader ) {
		delete pBuff;
		InvalidaCache();
		return;
	}
	if ( !pBuff->GetData( (void *)pRecordFieldsHeader, (lNumFieldsInHeader * sizeof(TRecordBufferHeader)) ) ) {
		InvalidaCache();
		delete pBuff;
		return;
	}

	pCache = pBuff;
}

void 
CRep_Cache::DeleteCache()
{
	if ( pCache ) {
		delete (C_Buffer *)pCache;
	}
	pCache = NULL;
	if ( pRecordFieldsHeader ) {
		delete pRecordFieldsHeader;
	}
	pRecordFieldsHeader = NULL;
	lNumFieldsInHeader = 0;
	lRecNum = -1;
	if ( pFieldInfoById ) {
		for ( int i=0; i<lNumFieldsInBase; i++ ) {
			pFieldInfoById[i].bValid = FALSE;
		}
	}
}

int 
CRep_Cache::GetFieldRepetition_Cache( void *pvFieldKey, int iRep, 
				void *pvRet, BOOL bIsFieldId, BYTE bFieldType)
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pvFieldKey || !pvRet ) {
		return -1;
	}

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	FieldInfo *pField = NULL;

	if ( bIsFieldId ) {		// pesquisa por campo
		pField = GetFieldFromId( (*(UINT *)pvFieldKey) );
	}
	else {					// pesquisa por apelido do campo
		pField = GetFieldFromAlias( (char *)pvFieldKey );
	}

	if ( !pField ) {		// nao achou o campo
		// melhor sinalizar pra pedir direto ao servidor
		return -1;
	}

	if ( pField->bFieldType != bFieldType ) { 
		// tipo pedido nao bate com o armazenado
		CLRETURN (LBSE_INVALIDFIELDTYPE);
	}

	long lSize = 0;
	if ( !GetRepetition( iRep, pField, pvRet, &lSize ) ) {
		CLRETURN (LBSE_INVALIDDATA);
	}

	if ( pField->lNumRep < 0 ) {	
		// erro de permissao ao acessar o campo; o codigo esta no numero de repeticoes
		CLRETURN (pField->lNumRep);
	}

	if ( lSize == 0 ) {
		CLRETURN (LBSE_INVALIDDATA);
	}

	CLRETURN (LBS_OK);
}

int 
CRep_Cache::GetNumberOfRepetition_Cache(void *pvFieldKey, BOOL bIsFieldId)
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pvFieldKey ) {
		return -1;
	}

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	FieldInfo *pField = NULL;

	if ( bIsFieldId ) {		// pesquisa por campo
		pField = GetFieldFromId( (*(UINT *)pvFieldKey) );
	}
	else {					// pesquisa por apelido do campo
		pField = GetFieldFromAlias( (char *)pvFieldKey );
	}

	if ( !pField ) {		// nao achou o campo
		// melhor sinalizar pra pedir direto ao servidor
		return -1;
	}

	if ( !GetRepetition( -1, pField, NULL, NULL ) ) {	// so pra forcar a carga dos dados do campo
		CLRETURN (LBSE_INVALIDDATA);
	}

	if ( pField->lNumRep < 0 ) {	
		// erro de permissao ao acessar o campo; o codigo esta no numero de repeticoes
		CLRETURN (pField->lNumRep);
	}

	return (pField->lNumRep);
}

long 
CRep_Cache::GetFieldRepetitionSize_Cache(void *pvFieldKey, int iRep, 
				BOOL bIsFieldId)
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pvFieldKey ) {
		return -1;
	}

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	FieldInfo *pField = NULL;

	if ( bIsFieldId ) {		// pesquisa por campo
		pField = GetFieldFromId( (*(UINT *)pvFieldKey) );
	}
	else {					// pesquisa por apelido do campo
		pField = GetFieldFromAlias( (char *)pvFieldKey );
	}

	if ( !pField ) {		// nao achou o campo
		// melhor sinalizar pra pedir direto ao servidor
		return -1;
	}

	long lSize = 0;
	if ( !GetRepetition( iRep, pField, NULL, &lSize ) ) {
		CLRETURN (LBSE_INVALIDDATA);
	}

	if ( pField->lNumRep < 0 ) {	
		CLRETURN (LBSE_INVALIDDATA);
	}

	if ( lSize == 0 ) {
		CLRETURN (LBSE_INVALIDDATA);
	}

	return lSize;
}

long 
CRep_Cache::GetOLRecNumber_Cache( const LBSC_Ticket *lbscTicket )
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache || lRecNum < 0 ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	return lRecNum;
}



////////////////////////////////////////////////////////////////////////
//	CLASSE CFieldSlot_Cache
////////////////////////////////////////////////////////////////////////

CFieldSlot_Cache::CFieldSlot_Cache( LBSC_Base *pBase ) : CCache( pBase )
{
}

CFieldSlot_Cache::~CFieldSlot_Cache()
{
	DeleteCache();
	pCache = NULL;
}


BOOL 
CFieldSlot_Cache::UsandoCache()
{
	if ( LBSC_ClientConfig::SlotCache() ) {
		return CCache::UsandoCache();
	}

	return FALSE;
}

void 
CFieldSlot_Cache::AtualizaCache()
{
	InvalidaCache();
	// chama o servidor para trazer a cache
	TSlotCache	*ptscSlots = pOwnerBase->GetAllFieldSlots( 
					pOwnerBase->GetTicket() );

	// testa se o retorno do servidor foi OK
	if ( !ptscSlots ) {
		return;
	}

	// Atualizando o ponteiro da cache 
	pCache = ptscSlots;

}


void 
CFieldSlot_Cache::DeleteCache()
{
	if ( pCache ) {
		delete (TSlotCache *)pCache;
	}

	pCache = NULL;
}


int 
CFieldSlot_Cache::GetFieldSlot_Cache( UINT uiId, void *pvBuff )
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pvBuff ) {
		return -1;
	}

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	TSlotCache	*ptscSlots = (TSlotCache *)pCache;
	for ( int i=0; i < ptscSlots->iNumberOfFieldSlots; i++ ) {
		if ( ptscSlots->pSlots[i].uiId == uiId ) {
			if ( ptscSlots->pSlots[i].iSize <= 0 || 
					!ptscSlots->pSlots[i].pBuff ) {
				CLRETURN (LBSE_EMPTYSLOT);	// slot vazio
			} 
			else {
				memcpy( pvBuff, ptscSlots->pSlots[i].pBuff, 
						ptscSlots->pSlots[i].iSize);
				CLRETURN (LBS_OK);	// achou
			}
		}
	}

	CLRETURN (LBSE_FIELDNOTFOUND);	// nao achou
}

long 
CFieldSlot_Cache::GetFieldSlotSize_Cache( UINT uiId)
{
	if ( !PodeUsarCache() ) {
		return -1;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return -1;
		}
	}

	TSlotCache	*ptscSlots = (TSlotCache *)pCache;
	for ( int i=0; i < ptscSlots->iNumberOfFieldSlots; i++ ) {
		if ( ptscSlots->pSlots[i].uiId == uiId ) {
			if ( ptscSlots->pSlots[i].iSize <= 0 || 
					!ptscSlots->pSlots[i].pBuff ) {
				CLRETURN (LBSE_EMPTYSLOT);	// slot vazio
			} 
			else {
				CLRETURN (ptscSlots->pSlots[i].iSize);	// achou
			}
		}
	}

	CLRETURN (LBSE_FIELDNOTFOUND);	// nao achou
}




////////////////////////////////////////////////////////////////////////
//	CLASSE COccur_Cache
////////////////////////////////////////////////////////////////////////

COccur_Cache::COccur_Cache( LBSC_Base *pBase ) : CCache( pBase )
{
}

COccur_Cache::~COccur_Cache()
{
	DeleteCache();
	pCache = NULL;
}

BOOL 
COccur_Cache::UsandoCache()
{
	if ( LBSC_ClientConfig::OccurCache() ) {
		return CCache::UsandoCache();
	}

	return FALSE;
}

void 
COccur_Cache::AtualizaCache()
{
	InvalidaCache();

	if ( !pOwnerBase ) {
		return;
	}

	COccurList *pList = pOwnerBase->GetAllOccurrences( 
									pOwnerBase->GetTicket() );
	if ( !pList ) {
		return;
	}

	pCache = pList;

}

void 
COccur_Cache::DeleteCache()
{
	if ( pCache ) {
		delete ( (COccurList *)pCache );
	}

	pCache = NULL;
}

LBSC_Occurrence *
COccur_Cache::GetFirstOccurrence_Cache()
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !pList->First() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_FIRSTOCCURRENCE );// primeiro registro
	return ( pList->Current()->lbscoOccurInfo );
}

LBSC_Occurrence *
COccur_Cache::GetNextOccurrence_Cache()
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !pList->Next() ) {
		if ( !pList->Current() ) {
			return NULL;
		}

		pOwnerBase->SetLastError( LBSE_LASTOCCURRENCE );// ultimo registro
	}

	return ( pList->Current()->lbscoOccurInfo );
}

LBSC_Occurrence *
COccur_Cache::GetPreviousOccurrence_Cache()
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !pList->Previous() ) {
		if ( !pList->Current() ) {
			return NULL;
		}

		pOwnerBase->SetLastError( LBSE_FIRSTOCCURRENCE );// primeiro registro
	}

	return ( pList->Current()->lbscoOccurInfo );
}

LBSC_Occurrence *
COccur_Cache::GetLastOccurrence_Cache()
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !pList->Last() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_LASTOCCURRENCE );// ultimo registro

	return ( pList->Current()->lbscoOccurInfo );
}

LBSC_Occurrence *
COccur_Cache::GetCurrentOccurrence_Cache()
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !pList->Current() ) {
		return NULL;
	}

	return ( pList->Current()->lbscoOccurInfo );
}

LBSC_Occurrence *
COccur_Cache::GetNthOccurrence_Cache( long lPos )
{
	if ( !PodeUsarCache() ) {
		return NULL;
	}

	pOwnerBase->SetLastError( LBSE_UNAVAILABLE );	// limpa o erro da cache

	if ( !pCache ) {
		AtualizaCache();
		if ( !pCache ) {	// nao conseguiu obter a cache
			return NULL;
		}
	}

	COccurList	*pList = (COccurList *)pCache;

	if ( !(*pList)[lPos] ) {
		pOwnerBase->SetLastError( LBSE_NOMEMORY );
		return NULL;
	}

	return ( pList->Current()->lbscoOccurInfo );
}
