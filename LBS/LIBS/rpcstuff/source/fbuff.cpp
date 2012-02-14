/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


// Funcoes de buffer

#ifndef _LBNEWDBG_H_
	#include <lbnewdbg.h>
#endif	// _LBNEWDBG_H_
#ifndef _LOGCL_H_
	#include <logcl.h>
#endif	// _LOGCL_H_

#ifndef _FBUFF_H_
#include <fbuff.h>
#endif

#define INVALID		-200	// nunca vai haver um id com esse valor (Adriano disse...)
#define INVALPERM	200		// nunca vai haver uma perm com esse valor (Adriano disse...)

//
//	Prototipos locais
//
int SizeOf( TSlotCache & );

// declaracao extern da global para a geracao de logs
EXTLOG(_cLbwLog);

/***
	Monta um objeto C_Buffer contendo uma lista compactada. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui, o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.
***/
int
MakeBufferFromList( LBSC_ExportBaseList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_ExportBaseList)") );

	TExportBase	tebVazio;

	memset( &tebVazio, 0, sizeof(tebVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TExportBase ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void*) &tebVazio, sizeof( TExportBase ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = (pList->NumElem() * sizeof( TExportBase )) +
				sizeof( TExportBase );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TExportBase	*peBases = pList->Current();

			(*ppcb)->PutData( (void*) peBases, sizeof( TExportBase ) );
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void*) &tebVazio, sizeof( TExportBase ) );
	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada.
***/
/******************************************
POR ENQUANTO NAO ESTA SENDO USADO

int
MakeBufferFromList( LBSC_SerialNumberList *pList, C_Buffer **ppcb )
{
	TSerialNumber	tsn;

	tsn.SetSerialNumber( "" );

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TSerialNumber ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void*) &tsn, sizeof( TSerialNumber ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = (pList->NumElem() * sizeof( TSerialNumber )) +
				sizeof( TSerialNumber );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TSerialNumber	*psNumber = pList->Current();

			(*ppcb)->PutData( (void*) psNumber, sizeof( TSerialNumber ) );
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void*) &tsn, sizeof( TSerialNumber ) );
	return( LBS_OK );
}

*****************/


/***
	Monta um objeto C_Buffer contendo uma lista compactada.
	ATENCAO: Modificado por Vladimir Catao em 01.02.96; nao se pode montar um buffer de 
	TAllBases (template da lista). Essa estrutura tem um ponteiro para outra lista. 
	Ao inves, monte no buffer os campos nao ponteiros e chame o MakeBufferFromList
	da outra lista. Assume-se que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_AllBasesList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_AllBasesList)") );

	TMachineAddr	tmaServVazio;	 // unico campo de TAllBases

	tmaServVazio = "";

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TMachineAddr ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (char *)tmaServVazio );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = (pList->NumElem() * sizeof( TMachineAddr )) +
				sizeof( TMachineAddr );

		for( int i = 0; i < pList->NumElem(); i++ ){
			iSize += sizeof( TServerBases );
			if( (*pList)[ i ]->plbscsblServerBasesList ){
				iSize += ((*pList)[ i ]->plbscsblServerBasesList->NumElem() *
					 sizeof( TServerBases ));
			}
		}

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TAllBases	*paBases = pList->Current();

			// ptabBases->tmaServer eh um CString; da pra fazer um sizeof
			(*ppcb)->PutData( (void *)&(paBases->tmaServer), sizeof(paBases->tmaServer) );
			if( MakeBufferFromList( paBases->plbscsblServerBasesList, ppcb ) != LBS_OK ){
				// $$$ Deu pau
				return( LBSE_NOMEMORY );
			}
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (char *) &tmaServVazio );
	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada a partir
	de uma lista LBSC_AppUserInfoList. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_AppUserInfoList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_AppUserInfoList)") );

	TAppUserNetInfo	tauUsrInfoVazio;	 // ultimo elemento (branco)

	if ( tauUsrInfoVazio.pclAppInfo ) {
		delete tauUsrInfoVazio.pclAppInfo;
	}
	memset(&tauUsrInfoVazio, 0, sizeof(tauUsrInfoVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( tauUsrInfoVazio ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void *)&tauUsrInfoVazio, sizeof(tauUsrInfoVazio) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf(pList);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TAppUserNetInfo	*pUsrInfo = pList->Current();

			(*ppcb)->PutData( (void *)pUsrInfo, sizeof(*pUsrInfo) );
			if( MakeBufferFromList( pUsrInfo->pclAppInfo, ppcb ) != LBS_OK ){
				// $$$ Deu pau
				return( LBSE_NOMEMORY );
			}
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void *)&tauUsrInfoVazio, sizeof(tauUsrInfoVazio) );
	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada a partir
	de uma lista LBSC_AppNetInfoList. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_AppNetInfoList	*pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_AppNetInfoList)") );

	TAppNetInfo	tanAppInfoVazio;	 // ultimo elemento (branco)

	if ( tanAppInfoVazio.pclSessionInfo ) {
		delete tanAppInfoVazio.pclSessionInfo;
	}
	memset(&tanAppInfoVazio, 0, sizeof(tanAppInfoVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( tanAppInfoVazio ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void *)&tanAppInfoVazio, sizeof(tanAppInfoVazio) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf(pList);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TAppNetInfo	*pAppInfo = pList->Current();

			(*ppcb)->PutData( (void *)pAppInfo, sizeof(*pAppInfo) );
			if( MakeBufferFromList( pAppInfo->pclSessionInfo, ppcb ) != LBS_OK ){
				// $$$ Deu pau
				return( LBSE_NOMEMORY );
			}
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void *)&tanAppInfoVazio, sizeof(tanAppInfoVazio) );
	return( LBS_OK );
}



/***
	Monta um objeto C_Buffer contendo uma lista compactada a partir
	de uma lista LBSC_AppSessionNetInfoList. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_AppSessionNetInfoList	*pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_AppSessionNetInfoList)") );

	TAppSessionNetInfo	taAppSessInfoVazio;	 // ultimo elemento (branco)

	if ( taAppSessInfoVazio.pclBaseInfo ) {
		delete taAppSessInfoVazio.pclBaseInfo;
	}
	memset(&taAppSessInfoVazio, 0, sizeof(taAppSessInfoVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( taAppSessInfoVazio ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void *)&taAppSessInfoVazio, sizeof(taAppSessInfoVazio) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf(pList);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TAppSessionNetInfo	*pAppSessInfo = pList->Current();

			(*ppcb)->PutData( (void *)pAppSessInfo, sizeof(*pAppSessInfo) );
			if( MakeBufferFromList( pAppSessInfo->pclBaseInfo, ppcb ) != LBS_OK ){
				// $$$ Deu pau
				return( LBSE_NOMEMORY );
			}

		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void *)&taAppSessInfoVazio, sizeof(taAppSessInfoVazio) );
	return( LBS_OK );
}

/***
	Monta um objeto C_Buffer contendo uma lista compactada a partir
	de uma lista LBSC_AppBaseNetInfoList. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_AppBaseNetInfoList	*pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_AppBaseNetInfoList)") );

	TAppBaseNetInfo	tabAppBaseInfoVazio;	 // ultimo elemento (branco)

	memset(&tabAppBaseInfoVazio, 0, sizeof(tabAppBaseInfoVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( tabAppBaseInfoVazio ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void *)&tabAppBaseInfoVazio, sizeof(tabAppBaseInfoVazio) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf(pList);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TAppBaseNetInfo	*pAppBaseInfo = pList->Current();

			(*ppcb)->PutData( (void *)pAppBaseInfo, sizeof(*pAppBaseInfo) );

		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void *)&tabAppBaseInfoVazio, sizeof(tabAppBaseInfoVazio) );
	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada.Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_ServerBasesList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_ServerBasesList)") );

	TServerBases	tsbVazio;

	memset(&tsbVazio, 0, sizeof(tsbVazio));

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TServerBases ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void*) &tsbVazio, sizeof( TServerBases ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = (pList->NumElem() * sizeof( TServerBases )) +
				sizeof( TServerBases );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			TServerBases	*psBases = pList->Current();

			(*ppcb)->PutData( (void*) psBases, sizeof( TServerBases ) );
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void*) &tsbVazio, sizeof( tsbVazio ) );
	return( LBS_OK );
}

/***
	Monta um objeto C_Buffer contendo uma lista LBSC_ACLList. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_ACLList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_ACLList)") );

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( 0 );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		return( LBS_OK );
	}

	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf(pList);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos 
	if( pList->First() ){
		do{
			LBSC_ACL	*plbscACL = pList->Current();
			// plbscACL->szName eh um CString; da pra fazer um sizeof
			(*ppcb)->PutData( (void *)&(plbscACL->szName), sizeof(plbscACL->szName));
			if ( MakeBufferFromList( &plbscACL->lbscplPermList, ppcb) != LBS_OK) {
				return LBSE_NOMEMORY;
			}

		} while( pList->Next() );
	}

	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo.

***/
int
MakeBufferFromList( LBSC_PermList *pList, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(LBSC_PermList)") );

	LBSC_Perm	lbscNullPerm;
	memset((void *)&lbscNullPerm, 0, sizeof(lbscNullPerm));

	lbscNullPerm.lId = INVALID;
	lbscNullPerm.bPermission = INVALPERM;

	if( !pList ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( lbscNullPerm ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		(*ppcb)->PutData( (void*) &lbscNullPerm, sizeof( lbscNullPerm ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		int	iSize = SizeOf( pList );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os nodos mais um contendo 0 no final
	if( pList->First() ){
		do{
			LBSC_Perm	*plbscPerm = pList->Current();
			(*ppcb)->PutData( (void*) plbscPerm, sizeof( *plbscPerm ) );
		} while( pList->Next() );
	}
	(*ppcb)->PutData( (void*) &lbscNullPerm, sizeof( lbscNullPerm ) );

	return( LBS_OK );
}


/***
	Monta um objeto C_Buffer contendo uma array de TFields
***/
int
MakeBufferFromArray( TField *ptfField, C_Buffer **ppcb, int iNumberOfFields )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromArray(TField)") );

	TField	tf;
	int	iSize;

	memset( &tf, 0, sizeof(tf) );

	if( !ptfField ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TField ) + sizeof( int ));
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		iNumberOfFields = 1;
		(*ppcb)->PutData( &iNumberOfFields );
		(*ppcb)->PutData( (void*) &tf, sizeof( TField ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		iSize = (iNumberOfFields * sizeof( TField )) + sizeof( int );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
		(*ppcb)->PutData( &( iNumberOfFields ) );
	}

	// $$$ Preencher o buffer com todos os elementos
	for( int i = 0; i < iNumberOfFields; i++ ){
		(*ppcb)->PutData( &(ptfField[ i ]) );
	}
	return( LBS_OK );
}

/******
	Monta uma estrutura TSlotCache num buffer

******/
int 
MakeBufferFromArray( TSlotCache &tscCache, C_Buffer **pcBuff )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromArray(TSlotCache)") );

	int iSize = 0;
	if( !(*pcBuff) ){
		// $$$ Calcular o tamanho do buffer 
		iSize = SizeOf(tscCache);

		// $$$ Criar um buffer com o tamanho calculado
		*pcBuff = new C_Buffer( iSize );
		if( !*pcBuff ){
			return( LBSE_NOMEMORY );
		}
	}

	// $$$ Preencher o buffer com todos os elementos
	(*pcBuff)->PutData( (void *)&tscCache, sizeof(tscCache) );
	for ( int i=0; i < tscCache.iNumberOfFieldSlots; i++ ) {
		(*pcBuff)->PutData( (void *)&tscCache.pSlots[i], sizeof(tscCache.pSlots[i]) );
		if ( tscCache.pSlots[i].iSize > 0 ) {
			(*pcBuff)->PutData( (void *)tscCache.pSlots[i].pBuff, 
					tscCache.pSlots[i].iSize) ;
		}
	}
	return( LBS_OK );
}


/***
	Pega uma lista contida num buffer.
	O buffer deve ter sido preenchido com um lista do tipo LBSC_ExportBaseList.
***/
int
MakeExportBaseList( LBSC_ExportBaseList *pList, C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeExportBaseList(LBSC_ExportBaseList)") );

	if( !pList ){
		return( LBSE_BADARG );
	}

	pList->DelAll();

	TExportBase	*pteBase = new TExportBase;

	if( !pteBase ){
		return( LBSE_NOMEMORY );
	}
	do{
		if( !cb.GetData( (void*) pteBase, sizeof( TExportBase ) ) ){
			// $$$ deu pau
			return( LBSE_NOMEMORY );
		}
		if( strcmp(pteBase->GetBaseName(), "") == 0 ){
			// $$$ Acabou
			delete pteBase;
			break;
		}
		pList->Add( pteBase, TAIL );
		pteBase = new TExportBase;
		if( !pteBase ){
			// $$$ deu pau
			return( LBSE_NOMEMORY );
		}
	} while( TRUE );
	return( LBS_OK );
}


/***
	Pega uma lista contida no buffer.
	O buffer deve ter sido preenchido com um lista do tipo LBSC_SerialNumberList.
***/
/******************************************
POR ENQUANTO NAO ESTA SENDO USADO

int
MakeSerialNumberList( LBSC_SerialNumberList *pList, C_Buffer &cb )
{
	if( !pList ){
		return( LBSE_BADARG );
	}

	pList->DelAll();

	TSerialNumber	*ptsNumber = new TSerialNumber;

	if( !ptsNumber ){
		return( LBSE_NOMEMORY );
	}
	do{
		if( !cb.GetData( (void*) ptsNumber, sizeof( TSerialNumber ) ) ){
			// $$$ deu pau
			return( LBSE_NOMEMORY );
		}
		if( ptsNumber->GetSerialNumber() == "" ){
			// $$$ Acabou
			delete ptsNumber;
			break;
		}
		pList->Add( ptsNumber, TAIL );
		ptsNumber = new TSerialNumber;
		if( !ptsNumber ){
			// $$$ deu pau
			return( LBSE_NOMEMORY );
		}
	} while( TRUE );
	return( LBS_OK );
}

**************************************/

/***
	Pega um array contido no buffer.
	O buffer deve ter sido preenchido com um array do tipo TField.
***/
TField *
MakeFieldArray( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeFieldArray(C_Buffer)") );

	TField	*ptfFieldArray;
	int	iNumberOfFields;

	cb.GetData( &iNumberOfFields );
	if( !iNumberOfFields ){
		return( NULL );
	}
	if( ( ptfFieldArray = new TField [ iNumberOfFields ] ) == NULL ){
		return( NULL );
	}


	for( int i = 0; i < iNumberOfFields; i++ ){
		if( !cb.GetData( &(ptfFieldArray[ i ]) ) ){
			// $$$ deu pau
			return( NULL );
		}

	}
	return( ptfFieldArray );
}


/***
	Monta uma ServerBasesList a partir de um C_Buffer
	ATENCAO: Modificado por Vladimir Catao em 01.02.96; o buffer representa a lista 
	ServerBasesList, em que cada elemento eh um string e um buffer da lista de TServerBases.
***/
LBSC_AllBasesList *
MakeAllBasesList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeAllBasesList(C_Buffer)") );

	LBSC_AllBasesList *pList = new LBSC_AllBasesList;

	if( !pList ){
		return( NULL );
	}

	TAllBases	*ptabBases = new TAllBases;
	if( !ptabBases ){
		delete pList;
		return( NULL );
	}
	do{
		// ptabBases->tmaServer eh um CString; da pra fazer um sizeof
		if( !cb.GetData( (void *)&(ptabBases->tmaServer), sizeof(ptabBases->tmaServer) ) ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
		if( ptabBases->tmaServer == (char*)"" ){
			// $$$ Acabou
			delete ptabBases;
			break;
		}
		ptabBases->plbscsblServerBasesList = MakeServerBasesList( cb );
		if( !(ptabBases->plbscsblServerBasesList) ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
		pList->Add( ptabBases, TAIL );
		ptabBases = new TAllBases;
		if( !ptabBases ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
	} while( TRUE );

	pList->First();		
	return( pList );
}


/***
	Monta uma LBSC_AppUserInfoList a partir de um C_Buffer
***/
LBSC_AppUserInfoList *
MakeAppUserInfoList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeAppUserInfoList(C_Buffer)") );

	LBSC_AppUserInfoList *pList = new LBSC_AppUserInfoList;

	if( !pList ){
		return( NULL );
	}

	TAppUserNetInfo	*ptaAppUserInfo = new TAppUserNetInfo;
	do{
		if( !ptaAppUserInfo ){
			delete pList;
			return( NULL );
		}
		if( !cb.GetData( (void *)ptaAppUserInfo, sizeof(*ptaAppUserInfo) ) ){
			// $$$ Acabou
			delete ptaAppUserInfo;
			break;
		}
		if( ptaAppUserInfo->IsZero() ) {
			// $$$ Acabou
			delete ptaAppUserInfo;
			break;
		}
		ptaAppUserInfo->pclAppInfo = MakeAppInfoList( cb );
		if( !ptaAppUserInfo->pclAppInfo ){
			// $$$ Acabou
			break;
		}
		pList->Add( ptaAppUserInfo, TAIL );
		ptaAppUserInfo = new TAppUserNetInfo;
	} while( TRUE );

	pList->First();		
	return( pList );
}


/***
	Monta um objeto C_Buffer contendo uma lista compactada. Assume-se
	que o tratamento para lista nula seja feito externamente; aqui o 
	resultado de se passar uma lista nula e uma lista vazia (zero elementos)
	sera o mesmo. Lembrar que vai no buffer a posicao corrente da lista

***/
int
MakeBufferFromList( COccurList *pList, int iCurrIndex, C_Buffer **ppcb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromList(COccurList)") );

	if( !pList ){		
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( 0 );	// buffer de tamanho zero
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		return( LBS_OK );
	}

	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista; inclui tambem
		// $$$ a posicao corrente na lista de ocorrencias
		int	iSize = SizeOf(pList) + sizeof(iCurrIndex);

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
	}

	(*ppcb)->PutData( (void*) &iCurrIndex, sizeof(iCurrIndex));
	// $$$ Preencher o buffer com todos os nodos 
	if( pList->First() ){
		do{
			COccurInfo	*pInfo = pList->Current();

			const char *szTerm = pInfo->lbscoOccurInfo->GetTerm();
			int iStrLen = (szTerm ? strlen(szTerm) + 1: 0 );
			(*ppcb)->PutData( (void*) &iStrLen, sizeof(iStrLen));
			(*ppcb)->PutData( (void*) szTerm, iStrLen );

			long lRec = pInfo->lbscoOccurInfo->GetRecord();
			(*ppcb)->PutData( (void*) &lRec, sizeof(lRec));

			int iField = pInfo->lbscoOccurInfo->GetField();
			(*ppcb)->PutData( (void*) &iField, sizeof(iField));

			int iRep = pInfo->lbscoOccurInfo->GetRepetition();
			(*ppcb)->PutData( (void*) &iRep, sizeof(iRep));

			int iPar = pInfo->lbscoOccurInfo->GetParagraph();
			(*ppcb)->PutData( (void*) &iPar, sizeof(iPar));

			int iPhra = pInfo->lbscoOccurInfo->GetPhrase();
			(*ppcb)->PutData( (void*) &iPhra, sizeof(iPhra));

			int iSeq = pInfo->lbscoOccurInfo->GetSequence();
			(*ppcb)->PutData( (void*) &iSeq, sizeof(iSeq));

		} while( pList->Next() );
	}

	return( LBS_OK );
}



/***
	Monta uma LBSC_AppNetInfoList a partir de um C_Buffer
***/
LBSC_AppNetInfoList	*
MakeAppInfoList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeAppInfoList(C_Buffer)") );

	LBSC_AppNetInfoList *pList = new LBSC_AppNetInfoList;

	if( !pList ){
		return( NULL );
	}

	TAppNetInfo	*ptaAppInfo = new TAppNetInfo;
	do{
		if( !ptaAppInfo ){
			delete pList;
			return( NULL );
		}
		if( !cb.GetData( (void *)ptaAppInfo, sizeof(*ptaAppInfo) ) ){
			// $$$ Acabou
			delete ptaAppInfo;
			break;
		}
		if( ptaAppInfo->IsZero() ) {
			// $$$ Acabou
			delete ptaAppInfo;
			break;
		}
		ptaAppInfo->pclSessionInfo = MakeSessInfoList( cb );
		if( !ptaAppInfo->pclSessionInfo ){
			// $$$ Acabou
			break;
		}
		pList->Add( ptaAppInfo, TAIL );
		ptaAppInfo = new TAppNetInfo;
	} while( TRUE );

	pList->First();		
	return( pList );
}


/***
	Monta uma LBSC_AppSessionNetInfoList a partir de um C_Buffer
***/
LBSC_AppSessionNetInfoList	*
MakeSessInfoList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeSessInfoList(C_Buffer)") );

	LBSC_AppSessionNetInfoList *pList = new LBSC_AppSessionNetInfoList;

	if( !pList ){
		return( NULL );
	}

	TAppSessionNetInfo	*ptAppSessInfo = new TAppSessionNetInfo;
	do{
		if( !ptAppSessInfo ){
			delete pList;
			return( NULL );
		}
		if( !cb.GetData( (void *)ptAppSessInfo, sizeof(*ptAppSessInfo) ) ){
			// $$$ Acabou
			delete ptAppSessInfo;
			break;
		}
		if( ptAppSessInfo->IsZero() ) {
			// $$$ Acabou
			delete ptAppSessInfo;
			break;
		}
		ptAppSessInfo->pclBaseInfo = MakeBaseInfoList( cb );
		if( !ptAppSessInfo->pclBaseInfo ){
			// $$$ Acabou
			break;
		}
		pList->Add( ptAppSessInfo, TAIL );
		ptAppSessInfo = new TAppSessionNetInfo;
	} while( TRUE );

	pList->First();		
	return( pList );
}



/***
	Monta uma LBSC_AppBaseNetInfoList a partir de um C_Buffer
***/
LBSC_AppBaseNetInfoList	*
MakeBaseInfoList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBaseInfoList(C_Buffer)") );

	LBSC_AppBaseNetInfoList *pList = new LBSC_AppBaseNetInfoList;

	if( !pList ){
		return( NULL );
	}

	TAppBaseNetInfo	*ptaBaseInfo = new TAppBaseNetInfo;
	do{
		if( !ptaBaseInfo ){
			delete pList;
			return( NULL );
		}
		if( !cb.GetData( (void *)ptaBaseInfo, sizeof(*ptaBaseInfo) ) ){
			// $$$ Acabou
			delete ptaBaseInfo;
			break;
		}
		if( ptaBaseInfo->IsZero() ) {
			// $$$ Acabou
			delete ptaBaseInfo;
			break;
		}
		pList->Add( ptaBaseInfo, TAIL );
		ptaBaseInfo = new TAppBaseNetInfo;
	} while( TRUE );

	pList->First();		
	return( pList );
}


/***
	Monta uma LBSC_ACLList a partir de um buffer generico
***/
LBSC_ACLList	*
MakeACLList( TSROut_GenericBuffer togBuff )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeACLList(TSROut_GenericBuffer)") );

	if ( togBuff.lTamBuff <= sizeof(int) ) {	// nao existe buffer
		return NULL;
	}

	C_Buffer *pcbBuffer = new C_Buffer( togBuff.lTamBuff - sizeof( int ) );
	if( !pcbBuffer ){	
		return ( NULL );
	}

	pcbBuffer->PutData( (void*) (togBuff.szBuffer + sizeof( int )), togBuff.lTamBuff - sizeof( int ) );
	pcbBuffer->Rewind();

	LBSC_ACLList *pList = new LBSC_ACLList;

	if( !pList ){
		delete pcbBuffer;
		return( NULL );
	}

	LBSC_ACL *plaNewACL = new LBSC_ACL;
	do{
		if( !plaNewACL ){
			delete pList;
			return( NULL );
		}
		// plaNewACL->szName eh um CString; da pra fazer um sizeof
		if( !pcbBuffer->GetData( (void *)&(plaNewACL->szName), sizeof(plaNewACL->szName) ) ){
			// $$$ Acabou
			delete plaNewACL;
			break;
		}
		LBSC_PermList *pPermList = MakePermList( *pcbBuffer );
		if ( !pPermList ) {
			return NULL;
		}
		plaNewACL->lbscplPermList = *pPermList;
		delete pPermList;
		pList->Add( plaNewACL, TAIL );
		plaNewACL = new LBSC_ACL;
	} while( TRUE );

	delete pcbBuffer;
	pList->First();		
	return( pList );
}



/***
	Monta uma ServerBasesList a partir de um C_Buffer
***/
LBSC_ServerBasesList *
MakeServerBasesList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeServerBasesList(C_Buffer)") );

	LBSC_ServerBasesList *pList = new LBSC_ServerBasesList;

	if( !pList ){
		return( NULL );
	}

	TServerBases	*ptsBases = new TServerBases;

	if( !ptsBases ){
		delete pList;
		return( NULL );
	}
	do{
		if( !cb.GetData( (void*) ptsBases, sizeof( TServerBases ) ) ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
		if( strcmp(ptsBases->GetBaseName(), "") == 0 ){
			// $$$ Acabou
			delete ptsBases;
			break;
		}
		pList->Add( ptsBases, TAIL );
		ptsBases = new TServerBases;
		if( !ptsBases ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
	} while( TRUE );

	pList->First();		
	return( pList );

}

/***
	Pega uma lista contida no buffer.
	O buffer deve ter sido preenchido com um lista do tipo LBSC_PermList.
***/
LBSC_PermList *
MakePermList( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakePermList(C_Buffer)") );

	LBSC_PermList *pList = new LBSC_PermList;

	if( !pList ){
		return( NULL );
	}

	LBSC_Perm	*ppPerm = new LBSC_Perm;

	if( !ppPerm ){
		return( NULL );
	}
	do{
		if( !cb.GetData( ppPerm, sizeof(*ppPerm) ) ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}

		if( ( ppPerm->lId == INVALID ) && ( 
					ppPerm->bPermission == INVALPERM ) ){
			// $$$ acabou
			delete ppPerm;
			break;
		}

		pList->Add( ppPerm, TAIL );
		ppPerm = new LBSC_Perm;
		if( !ppPerm ){
			// $$$ deu pau
			delete pList;
			return( NULL );
		}
	} while( TRUE );

	pList->First();		
	return( pList );
}

/***
	Monta um objeto C_Buffer contendo uma array de TUDBRecords
***/
int
MakeBufferFromArray( TUDBRecord *ptrRecord, C_Buffer **ppcb, int iNumberOfRecords )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromArray(TUDBRecord)") );

	TUDBRecord	tr;
	int	iSize;

	tr.szUserName = "";
	tr.szUserPassword = "";
	tr.lUserType = 0;
	tr.szUserDescription = "";
	tr.szUserAddress = "";
	tr.szUserPhone = "";	
	tr.szUserGroup = "";

	if( !ptrRecord ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( TUDBRecord ) + sizeof( int ));
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		iNumberOfRecords = 1;
		(*ppcb)->PutData( &iNumberOfRecords );
		(*ppcb)->PutData( (void*) &tr, sizeof( TUDBRecord ) );
		return( LBS_OK );
	}


	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		iSize = (iNumberOfRecords * sizeof( TUDBRecord )) + sizeof( int );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
		(*ppcb)->PutData( &( iNumberOfRecords ) );
	}

	// $$$ Preencher o buffer com todos os nodos elementos
	for( int i = 0; i < iNumberOfRecords; i++ ){
		(*ppcb)->PutData( &(ptrRecord[ i ]) );
	}
	return( LBS_OK );
}

/***
	Monta um objeto C_Buffer contendo uma array de strings
***/
int
MakeBufferFromArray( char **pszName, C_Buffer **ppcb, int iNumberOfStrings )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBufferFromArray(char)") );

	int	iSize = 0;
	
	if( !pszName ){
		if( !(*ppcb) ){
			*ppcb = new C_Buffer( sizeof( int ) );
			if( !(*ppcb) ){
				*ppcb = NULL;
				return( LBSE_NOMEMORY );
			}
		}
		iNumberOfStrings = 0;
		(*ppcb)->PutData( &iNumberOfStrings );
		return( LBS_OK );
	}
		
	if( !(*ppcb) ){
		// $$$ Calcular o tamanho do buffer que serah necessario para
		// $$$ armazenar todos os nodos da lista
		for( int i = 0; i < iNumberOfStrings; i++ ) {
			if ( pszName[i] ) {
				iSize += strlen( (const char*) pszName[i] ) + 1;
			}
		}

		iSize += (iNumberOfStrings + 1) * sizeof( int );

		// $$$ Criar um buffer com o tamanho calculado
		*ppcb = new C_Buffer( iSize );
		if( !(*ppcb) ){
			*ppcb = NULL;
			return( LBSE_NOMEMORY );
		}
		(*ppcb)->PutData( &( iNumberOfStrings ) );
	}
			
	// $$$ Preencher o buffer com todos os elementos
	int iNameLen;
	for( int i = 0; i < iNumberOfStrings; i++ ){
		iNameLen = (pszName[i] ? strlen( (const char*) pszName[i]) : -1 );
		(*ppcb)->PutData( &iNameLen );
		if ( iNameLen >= 0 ) {
			(*ppcb)->PutData( ( char* ) pszName[ i ] );
		}
	}

	return( LBS_OK );
}


/***
	Pega uma lista contida no buffer.
	O buffer deve ter sido preenchido com um array do tipo TUDBRecord.
***/
TUDBRecord *
MakeRecordArray( C_Buffer &cb )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeRecordArray(C_Buffer)") );

	TUDBRecord	*ptrRecordArray;
	int	iNumberOfRecords;

	cb.GetData( &iNumberOfRecords );
	if( !iNumberOfRecords ){
		return( NULL );
	}
	if( ( ptrRecordArray = new TUDBRecord [ iNumberOfRecords ] ) == NULL ){
		return( NULL );
	}


	for( int i = 0; i < iNumberOfRecords; i++ ){
		if( !cb.GetData( &(ptrRecordArray[ i ]) ) ){
			// $$$ deu pau
			return( NULL );
		}

	}
	return( ptrRecordArray );
}


/***
***/
TSlotCache *
MakeBaseCacheArray( TSROut_GenericBuffer tgbInCache )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeBaseCacheArray(TSROut_GenericBuffer)") );

	if ( !tgbInCache.lTamBuff ) {
		return NULL;
	}

	C_Buffer cBuff( tgbInCache.lTamBuff - sizeof(int) );	// pula o int do cbuffer; 

	cBuff.PutData( (void*) (tgbInCache.szBuffer + sizeof(int)), tgbInCache.lTamBuff - sizeof(int)); // pula o int do cbuffer; 
	cBuff.Rewind();

	TSlotCache *pCache = new TSlotCache;
	if ( !pCache ) {
		return NULL;
	}

	cBuff.GetData( (void *)pCache, sizeof(TSlotCache) );
	if( !pCache->iNumberOfFieldSlots ){
		delete pCache;
		return( NULL );
	}

	if( ( pCache->pSlots = new TSlotCacheInfo[pCache->iNumberOfFieldSlots] ) == NULL ){
		delete pCache;
		return( NULL );
	}

	for( int i = 0; i < pCache->iNumberOfFieldSlots; i++ ){
		if( !cBuff.GetData( (void *)&pCache->pSlots[i], 
					sizeof(pCache->pSlots[i]) ) ) {
			// $$$ deu pau
			delete pCache;
			return( NULL );
		}

		if ( pCache->pSlots[i].iSize <= 0 ) {	// slot vazio
			continue;
		}

		if ( ! (pCache->pSlots[i].pBuff = new char[pCache->pSlots[i].iSize] )) {
			delete pCache;
			return( NULL );
		}
	
		if ( !cBuff.GetData( (void *)pCache->pSlots[i].pBuff, 
					pCache->pSlots[i].iSize ) ) {
			// $$$ deu pau
			delete pCache;
			return( NULL );
		}

	}
	return( pCache );
}


/***
	Pega uma lista contida no buffer.
	O buffer deve ter sido preenchido com um array de Strings.
***/
char **
MakeStringArray( C_Buffer &cb, int	iNumberOfStrings )
{
	// gerando log para o stub servidor
	PRINTLOG(_cLbwLog, ("::MakeStringArray(C_Buffer)") );

	char **pszStringArray;

	if( !cb.GetData( &iNumberOfStrings ) ){
		return( NULL );
	}
	if ( iNumberOfStrings == 0 )
		return NULL;

	pszStringArray = new char*[ iNumberOfStrings ];	
	if( pszStringArray == NULL ) {
		return( NULL );
	}

	int iStrSize;
	for( int i = 0; i < iNumberOfStrings; i++ ) {
		if( !cb.GetData( &iStrSize ) ){
			// $$$ deu pau
			return( NULL );
		}

		if ( iStrSize < 0 ) {	// ponteiro NULL
			pszStringArray[i] = NULL;
		}
		else {
			pszStringArray[i] = new char[iStrSize + 1];
			if ( !pszStringArray[i] ) {
				return( NULL );
			}

			if( !cb.GetData( ( char * )pszStringArray[i] ) ){
				// $$$ deu pau
				return( NULL );
			}
		}
	}

	return( pszStringArray );
}



//
//	Retorna o espaco ocupado pela lista; 
//
int
SizeOf( COccurList *pList )
{
	if ( !pList )
		return 0;

	COccurInfo *pcoiInfo = pList->First();

	int iSize=0;
	while ( pcoiInfo ) {
		//	iSize vai acumular os dados de pcoiInfo->lbscoOccurInfo;
		//	o termo, que eh um string, deve ser precedido de um int
		//	contendo seu tamanho; 
		if ( pcoiInfo->lbscoOccurInfo->GetTerm() ) {
			iSize += strlen( pcoiInfo->lbscoOccurInfo->GetTerm()) + 1 +
						sizeof(int);	// cada string tem o '\0'e um int que eh o tamanho
		}
		else {
			iSize += sizeof(int);
		}

		iSize += (	sizeof(pcoiInfo->lbscoOccurInfo->GetRecord()) +
					sizeof(pcoiInfo->lbscoOccurInfo->GetField()) +
					sizeof(pcoiInfo->lbscoOccurInfo->GetRepetition()) +
					sizeof(pcoiInfo->lbscoOccurInfo->GetParagraph()) +
					sizeof(pcoiInfo->lbscoOccurInfo->GetPhrase()) +
					sizeof(pcoiInfo->lbscoOccurInfo->GetSequence()) );
		pcoiInfo = pList->Next();
	}

	return iSize;
}

//
//	Retorna o espaco ocupado pela lista; assume-se que no final deve
//	haver um item dummy. Assim, o espaco eh equivalente ao numero de 
//	elementos da lista mais um
//
int
SizeOf( LBSC_AppUserInfoList *pList )
{
	if ( !pList )
		return 0;

	TAppUserNetInfo *taUserInfo = pList->First();

	int iSize=0;
	while ( taUserInfo ) {
		// iSize vai acumular os dados de taUserInfo mais o tamanho da sub-lista
		iSize += (sizeof(*taUserInfo) + SizeOf(taUserInfo->pclAppInfo));
		taUserInfo = pList->Next();
	}
	iSize += sizeof(TAppUserNetInfo);	// inclui um branco no fim

	return iSize;
}

//
//	Retorna o espaco ocupado pela lista; assume-se que no final deve
//	haver um item dummy. Assim, o espaco eh equivalente ao numero de 
//	elementos da lista mais um
//
int
SizeOf( LBSC_AppNetInfoList *pList )
{
	if ( !pList )
		return 0;

	TAppNetInfo	*taAppInfo = pList->First();

	int iSize=0;
	while ( taAppInfo ) {
		// iSize vai acumular os dados de taAppInfo mais o tamanho da sub-lista
		iSize += (sizeof(*taAppInfo) + SizeOf(taAppInfo->pclSessionInfo));
		taAppInfo = pList->Next();
	}
	iSize += sizeof(TAppNetInfo);	// inclui um branco no fim

	return iSize;
}

//
//	Retorna o espaco ocupado pela lista; assume-se que no final deve
//	haver um item dummy. Assim, o espaco eh equivalente ao numero de 
//	elementos da lista mais um
//
int
SizeOf( LBSC_AppSessionNetInfoList *pList )
{
	if ( !pList )
		return 0;

	TAppSessionNetInfo	*taSessInfo = pList->First();

	int iSize=0;
	while ( taSessInfo ) {
		// iSize vai acumular os dados de taSessInfo mais o tamanho da sub-lista
		iSize += (sizeof(*taSessInfo) + SizeOf(taSessInfo->pclBaseInfo));
		taSessInfo = pList->Next();
	}
	iSize += sizeof(TAppSessionNetInfo);	// inclui um branco no fim

	return iSize;
}

//
//	Retorna o espaco ocupado pela lista; assume-se que no final deve
//	haver um item dummy. Assim, o espaco eh equivalente ao numero de 
//	elementos da lista mais um
//
int
SizeOf( LBSC_AppBaseNetInfoList *pList )
{
	if ( !pList )
		return 0;

	// teremos o numero de elementos da lista mais um em branco
	return ((pList->NumElem() + 1) * sizeof(TAppBaseNetInfo));
}


//
//
//
int 
SizeOf( LBSC_ACLList *pList ) 
{
	if ( !pList ) {
		return 0;
	}

	LBSC_ACL *laACLInfo = pList->First();

	int iSize=0;
	while ( laACLInfo ) {
		// iSize vai acumular os dados de laACLInfo mais o tamanho da sub-lista
		// laNewACL->szName eh um CString; da pra fazer um sizeof
		iSize += (sizeof(laACLInfo->szName) + SizeOf(&(laACLInfo->lbscplPermList)));
		laACLInfo = pList->Next();
	}
	return iSize;
}


//
//
//
int
SizeOf( LBSC_PermList *pList )
{
	if ( !pList )
		return 0;

	//	tamanho total sera relativo ao 
	//	numero de elementos da lista mais um (inclui um elemento de marca de fim)
	//

	return ((pList->NumElem() + 1) * sizeof(LBSC_Perm));
}

//
//
//
int
SizeOf( TSlotCache &tscCache )
{
	int iSize = sizeof(tscCache);
	for ( int i=0; i < tscCache.iNumberOfFieldSlots; i++ ) {
		iSize += sizeof(TSlotCacheInfo);
		if ( tscCache.pSlots[i].iSize > 0 ) {
			iSize += tscCache.pSlots[i].iSize;
		}
	}

	return iSize;
}


COccurInfo::COccurInfo( LBSC_Occurrence *pOccur )
{
	lbscoOccurInfo = pOccur;
}

COccurInfo::~COccurInfo()
{
	if ( lbscoOccurInfo ) {
		delete lbscoOccurInfo;
	}
}

int 
COccurInfo::Compare(COccurInfo *criOther, int )
{
	if( lbscoOccurInfo->GetRecord() == criOther->lbscoOccurInfo->GetRecord() &&
		lbscoOccurInfo->GetField() == criOther->lbscoOccurInfo->GetField() &&
		lbscoOccurInfo->GetRepetition() == criOther->lbscoOccurInfo->GetRepetition() &&
		lbscoOccurInfo->GetParagraph() == criOther->lbscoOccurInfo->GetParagraph() &&
		lbscoOccurInfo->GetPhrase() == criOther->lbscoOccurInfo->GetPhrase() &&
		lbscoOccurInfo->GetSequence() == criOther->lbscoOccurInfo->GetSequence() ) {

		return 0;
	}

	return 1;
}

COccurInfo *
COccurInfo::Duplicate()
{
	return NULL;
}

