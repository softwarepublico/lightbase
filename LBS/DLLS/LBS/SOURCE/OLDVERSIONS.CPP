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
// Module: PUBBASE1.CPP
// Description:
//
//	LBSC_BASE public class methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//		Alessandro A. Jatoba'
//
// Last update: 28/04/97
//

#ifndef __BORLANDC__
#pragma warning(disable:4355)
#endif

#if !defined _INC_ERRNO
#include	<errno.h>
#endif
#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif

#if !defined __STDARG_H && !defined _INC_STDARG
#include	<stdarg.h>
#endif
#if !defined __CTYPE_H && !defined _INC_CTYPE
#include	<ctype.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined __DIRECT_H && !defined _INC_DIRECT
#include	<direct.h>
#endif
#if !defined __DIRENT_H && !defined _INC_DIRECT
#include	DIRENT_H
#endif
#if !defined( __SHARE_H ) && !defined _INC_SHARE
#include	<share.h>
#endif
#ifndef _LB3LIST_H_
#include	<lb3list.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_BASETIMERSLIST_H_
#include	<btimerl.h>
#endif
#ifndef _WINERROR_
#include	<winerror.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef	_LBSLCKCL_H_
#include	<lbslckcl.h>
#endif
extern "C" {
#include	<personcl.h>
}

#include "Compress.h"

#define	COMPRESSED_STATUS		0x01
#define	NOTCOMPRESSED_STATUS	0x00
#define	MINIMAL_COMPRESS_SIZE	(512)

// tamanho de uma repetição que eh um DATA_HOLE
#define DATA_HOLE_SIZE	-1


// $$$ API LIGHT-TEXT
#include	<lt.h>
#include	<exprlist.h>


#ifdef	_DEBUG_CRIT_SECT_

#define	cCS0( x, y )					cCS0( (x), (y), __FILE__, __LINE__ )
#define	cCS1( x, y )					cCS1( (x), (y), __FILE__, __LINE__ )
#define	cCS2( x, y )					cCS2( (x), (y), __FILE__, __LINE__ )
#define	cCS3( x, y )					cCS3( (x), (y), __FILE__, __LINE__ )
#define	cCS4( x, y )					cCS4( (x), (y), __FILE__, __LINE__ )
#define	cCS5( x, y )					cCS5( (x), (y), __FILE__, __LINE__ )
#define	cCS6( x, y )					cCS6( (x), (y), __FILE__, __LINE__ )
#define	cCS7( x, y )					cCS7( (x), (y), __FILE__, __LINE__ )
#define	cCS8( x, y )					cCS8( (x), (y), __FILE__, __LINE__ )
#define	cCS9( x, y )					cCS9( (x), (y), __FILE__, __LINE__ )
#define	cCS10( x, y )					cCS10( (x), (y), __FILE__, __LINE__ )
#define	cCS11( x, y )					cCS11( (x), (y), __FILE__, __LINE__ )
#define	cCS12( x, y )					cCS12( (x), (y), __FILE__, __LINE__ )
#define	cCS13( x, y )					cCS13( (x), (y), __FILE__, __LINE__ )
#define	cCS14( x, y )					cCS14( (x), (y), __FILE__, __LINE__ )
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

int	
LBSC_Base::ReadRecord_V3( C_LB1_V3 &LB1_V3, C_LB4 &LB4 )
{
	BYTE				bStatus = 0;
	Compactador			Compact; // Responsável pela compressão de dados

	TControlRec_V3	tcrControlRec;
	TContentRecPsw	tcrContentRecPsw;
	TRepetitionRec	trrRepetitionRec;

	lbscrCurrRecord.SetIsUndefined( TRUE );

	if( LB1_V3.tcrHead.lNumRecords == 0 ){
		ERETURN( LBS_OK );
	}

	if( LB1_V3.R_Read( &tcrControlRec ) != OK ){
		ERETURN( LBSE_NORECORD );
	}
	lbscrCurrRecord.bStatus = tcrControlRec.bRecStatus;

	if( tcrControlRec.bRecStatus & REC_EXCLUDED ){
		ERETURN( LBSE_EXCLUDEDREC );
	}
	if( !tcrControlRec.lContentPos ){
		ERETURN( LBSE_ZERORECORD );
	}

	lbscrCurrRecord.szOwnerName = tcrControlRec.szOwnerName;
	lbscrCurrRecord.szLastUpdateUserName = tcrControlRec.szLastModifyUserName;
	lbscrCurrRecord.SetCreateDate( tcrControlRec.ulCreateDate );
	lbscrCurrRecord.SetModifyDate( tcrControlRec.ulModifyDate );
	lbscrCurrRecord.SetStatus( tcrControlRec.bRecStatus );

	if( LB4.Seek( tcrControlRec.lContentPos, SEEK_SET ) != OK ){
		ERETURN( LBSE_WRONGRECORD );
	}
	if( LB4.Read( &tcrContentRecPsw, sizeof( tcrContentRecPsw ) ) != OK ){
		ERETURN( LBSE_WRONGRECORD );
	}

	lbscrCurrRecord.Clear();
	lbscrCurrRecord.ulAccess = tcrControlRec.ulAccess;

	if( !LB3.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}

	/// Se o número de campos lido de LB4 for maior que o contido
	/// na estrutura da base este registro esta danificado.
	if ( tcrContentRecPsw.iNrFields > LB3.R_FileSize() ){
		ERETURN( LBSE_WRONGRECORD );
	}
	/// Adriano Lemos, 11 de dezembro de 1999.

	// Vamos ler do disco.
	// primeiro, ler o vetor de campos...
	TContentRec	*ptcrContentRec = new TContentRec[tcrContentRecPsw.iNrFields];
	if ( !ptcrContentRec ) {
		ERETURN( LBSE_NOMEMORY );
	}
	for( int i = 0; i < tcrContentRecPsw.iNrFields; i++ ){
		if( LB4.Read( &(ptcrContentRec[i]), sizeof( TContentRec ) ) != OK ){
			delete ptcrContentRec;
			ERETURN( LBSE_WRONGRECORD );
		}
	}
	for( i = 0; i < tcrContentRecPsw.iNrFields; i++ ){
		TContentRec tcrContentRec = ptcrContentRec[i];
		if( lbscrCurrRecord.Id( tcrContentRec.uiFieldId ) == NULL ){
			// O campo lido nao existe mais na memoria.
			// Devemos pular para o proximo.
			continue;
		}

		// Posiciona a lista de campos no campo que tem o mesmo
		// identificador do campo lido
		LBSC_Field *pcfField = lbscrCurrRecord( tcrContentRec.uiFieldId );
		if( pcfField ){

			pcfField->bMustFillOriginalDataList = FALSE;
			int iNumRep = tcrContentRec.iNumberOfRepetition;
			pcfField->SetDataListTo( VALID_DATALIST );
			long lSpace = tcrContentRec.lFirstRepetition;
			while( lSpace && iNumRep ){
				if( LB4.Seek( lSpace, SEEK_SET ) != OK ){
					delete ptcrContentRec;
					ERETURN( LBSE_WRONGRECORD );
				}
				if( LB4.Read( &trrRepetitionRec,
					sizeof( trrRepetitionRec ) ) != OK ){
					delete ptcrContentRec;
					ERETURN( LBSE_WRONGRECORD );
				}
				BOOL bRepExist = TRUE;
				BOOL bDataHole = FALSE;

				if( trrRepetitionRec.lRepetitionSize == 0 || 
						trrRepetitionRec.lRepetitionSize == DATA_HOLE_SIZE ){
					// repeticao inexistente (ou DATA_HOLE), mas tem que contar na
					// lista de repeticoes do campo.
					bDataHole = (trrRepetitionRec.lRepetitionSize == DATA_HOLE_SIZE);
					trrRepetitionRec.lRepetitionSize = 1;
					bRepExist = FALSE;
				}
				/*
				Inicio Codigo: Katyusco de Farias Santos
				Objetivo: Implementação do mecanismo de compressao de dados durante a
				leitura de um campo.
				*/
				// Verifica se a Base possui ou não o mecanismo de compressão. O objetivo 
				// é garantir a compatibilidade para trás.
				bStatus = 0;
				if( (((pcfField->GetType() == BINARY_FIELD) || 
					  (pcfField->GetType() == TEXT_FIELD )) && 
					  (GetBaseVersion() >= COMPRESS_MAGICNUMBER)) ||
					  ((pcfField->GetType() == REFERENCED_FIELD) && 
					  (GetBaseVersion() >= REFERENCE_MAGICNUMBER)) ){

					// o campo eh um BINARY OU TEXT e base eh maior ou igual a COMPRESS_MAGICNUMBER ou
					// o campo eh um REFERENCE e abase eh um REFERENCE_MAGICNUMBER ou maior
					if( LB4.Read( &bStatus,	sizeof( bStatus ) ) != OK ){
						delete ptcrContentRec;
						ERETURN( LBSE_WRONGRECORD );
					}
				}
				/*
				  Fim Codigo Katysuco F. Santos
				*/

				/// Validação do tamanho da repetição a ser lida.
				int	iBufSize = 0;
				if ( ValidateFieldRep( trrRepetitionRec.lRepetitionSize, (bStatus & COMPRESSED_STATUS), pcfField, LB4 ) ){
					iBufSize = trrRepetitionRec.lRepetitionSize + 1;
				} else {
					/// tamanho da repetição tá errado
					delete ptcrContentRec;
					ERETURN( LBSE_WRONGRECORD );
				}
				char *szBuffer = new char [ iBufSize ];
				if( szBuffer ){
					memset( szBuffer, 0, iBufSize );
					if( LB4.Read( szBuffer,
							trrRepetitionRec.lRepetitionSize ) != OK ){
						delete szBuffer;
						delete ptcrContentRec;
						ERETURN( LBSE_WRONGRECORD );
					}
					/*
					Inicio Codigo: Katyusco de Farias Santos
					Objetivo: Implementação do mecanismo de compressao de dados durante a
					leitura de um campo.
					*/
					unsigned char *psBufOut; // Usado para realizacao da descompressão.
					int iTamBufOut;
					if  ( bStatus & COMPRESSED_STATUS ) {
						if ( (iTamBufOut = Compact.Uncompress( (char *)szBuffer, &psBufOut, trrRepetitionRec.lRepetitionSize) ) == 0 ) {
							delete ptcrContentRec;
							ERETURN( LBSE_WRONGRECORD );
						}
						delete szBuffer;
						trrRepetitionRec.lRepetitionSize = iTamBufOut;
						szBuffer = new char [ iTamBufOut + 1 ];
						memcpy( (void*) szBuffer, (void* )psBufOut, iTamBufOut);
						// Libera a area usada pelo psBufOut
						Compact.LiberaBufOut(&psBufOut);
					}
					/*
					  Fim Codigo Katysuco F. Santos
					*/
					if( pcfField->GetType() == ALPHA_FIELD ){
						szBuffer[ trrRepetitionRec.lRepetitionSize ] = '\0';
					}
					if( lSpace == tcrContentRec.lFirstRepetition ){
						LBSC_Data	*pd = (*pcfField) [ 0 ];

						if( pd ){
							switch( pcfField->GetType() ){
							case TEXT_FIELD:
								pd->ModifyData( szBuffer, trrRepetitionRec.lRepetitionSize );
								break;

							case BINARY_FIELD:
								if( !bRepExist ){
									char	szBin[ 2 * sizeof( int ) ];

									memset( szBin, 0, 2 * sizeof( int ) );
									pd->ModifyData( szBin );
								} else {
									pd->ModifyData( szBuffer );
								}
								break;

							case REFERENCED_FIELD:
								if( !bRepExist ){
									char	szBin[ sizeof( LBSC_Reference ) ];

									memset( szBin, 0, sizeof( LBSC_Reference ) );
									pd->ModifyData( szBin );
								} else {
									if( trrRepetitionRec.lRepetitionSize < sizeof( LBSC_Reference ) ){
										char	szBin[ sizeof( LBSC_Reference ) ];

										memset( szBin, 0, sizeof( LBSC_Reference ) );
										memcpy( szBin, szBuffer, trrRepetitionRec.lRepetitionSize );
										pd->ModifyData( szBin );
									} else {
										pd->ModifyData( szBuffer );
									}
								}
								break;

							default:
								pd->ModifyData( szBuffer );
							}
						}
					} else {
						switch( pcfField->GetType() ){
						case TEXT_FIELD:
							pcfField->AddRepetition( szBuffer, trrRepetitionRec.lRepetitionSize );
							break;

						case BINARY_FIELD:
							if( !bRepExist ){
								char	szBin[ 2 * sizeof( int ) ];

								memset( szBin, 0, 2 * sizeof( int ) );
								pcfField->AddRepetition( szBin );
							} else {
								pcfField->AddRepetition( szBuffer );
							}
							break;

						case REFERENCED_FIELD:
							if( !bRepExist ){
								char	szBin[ sizeof( LBSC_Reference ) ];

								memset( szBin, 0, sizeof( LBSC_Reference ) );
								pcfField->AddRepetition( szBin );
							} else {
								if( trrRepetitionRec.lRepetitionSize < sizeof( LBSC_Reference ) ){
									char	szBin[ sizeof( LBSC_Reference ) ];

									memset( szBin, 0, sizeof( LBSC_Reference ) );
									memcpy( szBin, szBuffer, trrRepetitionRec.lRepetitionSize );
									pcfField->AddRepetition( szBin );
								} else {
									pcfField->AddRepetition( szBuffer );
								}
							}
							break;

						default:
							pcfField->AddRepetition( szBuffer );
						}
					}
					delete szBuffer;
				}
				else {
					// faltou memoria...
					delete ptcrContentRec;
					ERETURN( LBSE_NOMEMORY );
				}

				if( bDataHole ){
					// a repeticao deve ser marcada como um DATA_HOLE
					LBSC_Data	*pd = (*pcfField)[ -1 ];	// -1 indica repeticao corrente.

					if( pd ){
						pd->DisableData();
						pd->SetStatus( DATA_HOLE );
					}
				} else {
					if( !bRepExist ){
						// a repeticao nao deve existir
						pcfField->DeleteRepetitionByIndex( -1, FALSE );
					} else {
						if( (pcfField->GetType() == DATE_FIELD) ){
							// vamos verificar se eh uma data valida.
							unsigned long	*pjt = ((unsigned long*) pcfField->GetConstRepByIndex( -1 ));
							if( pjt && (*pjt == 0) ){
								// data invalida. deletar.
								pcfField->DeleteRepetitionByIndex( -1, FALSE );
							}
						}
					}
				}
				lSpace = trrRepetitionRec.lNextRepetition;
				iNumRep--;
			}

			// acabamos de ler um campo
			if( pcfField->GetAttrib() & DESC_ORD_FIELD ){
				// inverter a ordem de atualizacao das repeticoes
				// (nao eh inverter a ordem das repeticoes dentro da lista
				// e sim inverter o iUpdateSequenceNumber)
				int	iNumRep = pcfField->GetNumberOfRepetition();

				for( int i = 0; i < iNumRep; i++, iNumRep-- ){
					LBSC_Data	*pd1 = pcfField->pDataList->Nth( i );
					LBSC_Data	*pd2 = pcfField->pDataList->Nth( iNumRep-1 );

					if( pd1 && pd2 && (pd1 != pd2) ){
						int	iAux = pd1->iUpdateSequenceNumber;

						pd1->iUpdateSequenceNumber = pd2->iUpdateSequenceNumber;
						pd2->iUpdateSequenceNumber = iAux;
					}
				}
			}
		}
	}
	delete ptcrContentRec;

	// atualizar o flag de alteracao de todos os campos
	int	iNumFields = GetNumberOfFields();
	for( i = 0; i < iNumFields; i ++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];

		if( pf ){
			pf->UpdateFieldFlag( FALSE );
			pf->bMustFillOriginalDataList = TRUE;
			pf->lbscdlOriginalDataList.DelAll();
		}
	}

	lbscrCurrRecord.SetIsUndefined( FALSE );
	ERETURN( LBS_OK );
}

int
LBSC_Base::GetSlot_V3( int iIndex, void *szBuffer, C_LB4 &LB4 )
{

	if( (iIndex < 1 && !bPrivateCreation) || iIndex > LB1.tcrHead.iSlotNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( ptsrStructRecHead->spSlot[ iIndex ].lPointer == 0 ){
		// nao ha' slot gravado ainda
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_EMPTYSLOT );
	}
	if( LB4.Seek( ptsrStructRecHead->spSlot[ iIndex ].lPointer, SEEK_SET ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( LB4.Read( szBuffer, ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	TStructHeadRec::Free( ptsrStructRecHead );
	ERETURN( LBS_OK );
}

long			
LBSC_Base::GetSlotSize_V3( int iIndex, C_LB4 &LB4 )
{
	if( (iIndex < 1 && !bPrivateCreation) || iIndex > LB1.tcrHead.iSlotNum ){
		ERETURN( LBSE_BADARG );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	TStructHeadRec		*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	if( ptsrStructRecHead->spSlot[ iIndex ].lPointer <= 0 ){
		// nao ha' slot gravado ainda
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_EMPTYSLOT );
	}
	long lSize = ptsrStructRecHead->spSlot[ iIndex ].pElem.lSize;
	// checa o arquivo LB4
	if( !LB4.IsOpen() ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_BASENOTOPEN );
	}
	long lfSize		= LB4.FileSize();
	if ( lSize < 0 || 
			lSize > ( lfSize - ptsrStructRecHead->spSlot[ iIndex ].lPointer ) ){
		// O tamanho do slot deste campo está inválido (maior que o possível).
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}

	SetError( LBS_OK );
	TStructHeadRec::Free( ptsrStructRecHead );
	return lSize;
}

int				
LBSC_Base::GetFieldSlot_V3( UINT uiId, void *szBuffer, C_LB4 &LB4 )
{
	// checa se o campo existe em memoria
	// (checa diretamente na lista de campos para nao correr o risco de
	// ser barrado pelas ACLs)
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	if( !pf ){
		return( LBSE_FIELDNOTFOUND );
	}
	// checa o arquivo LB3
	if( !LB3.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	TStructRec	sRec;
	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	int	iNumF = LB3.R_FileSize();
	TStructHeadRec::Free( ptsrStructRecHead );
	// procura em LB3 o campo com id = uiId
	for( int i = 0; i < iNumF; i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &sRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(sRec.uiFieldAttrib & DELETED_FIELD) && ( sRec.uiFieldId == uiId ) ){
			// achei o campo que estava procurando
			if( sRec.spSlot.lPointer == 0 ){
				// nao ha' slot gravado ainda
				ERETURN( LBSE_EMPTYSLOT );
			}
			if( LB4.Seek( sRec.spSlot.lPointer, SEEK_SET ) != OK ){
				ERETURN( LBSE_ERROR );
			}
			if( LB4.Read( szBuffer, sRec.spSlot.pElem.lSize ) != OK ){
				ERETURN( LBSE_ERROR );
			}
			ERETURN( LBS_OK );
		}
	}
	ERETURN( LBSE_FIELDNOTFOUND );
}

long	
LBSC_Base::GetFieldSlotSize_V3( UINT uiId, C_LB4 &LB4 )
{
	// checa se o campo existe em memoria
	// (checa diretamente na lista de campos para nao correr o risco de
	// ser barrado pelas ACLs)
	LBSC_Field	*pf = lbscrCurrRecord( uiId );
	if( !pf ){
		return( LBSE_FIELDNOTFOUND );
	}
	// checa o arquivo LB3
	if( !LB3.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}
	TStructRec	sRec;
	TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( LB1.tcrHead.iSlotNum + LB1.tcrHead.iCountNum );
	if( !ptsrStructRecHead ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( LB3.R_ReadHead( ptsrStructRecHead ) != OK ){
		TStructHeadRec::Free( ptsrStructRecHead );
		ERETURN( LBSE_ERROR );
	}
	int	iNumF = LB3.R_FileSize();
	TStructHeadRec::Free( ptsrStructRecHead );
	// procura em LB3 o campo com id = uiId
	for( int i = 0; i < iNumF; i++ ){
		LB3.R_Seek( i );
		if( LB3.R_Read( &sRec ) != OK ){
			ERETURN( LBSE_ERROR );
		}
		if( !(sRec.uiFieldAttrib & DELETED_FIELD) && ( sRec.uiFieldId == uiId ) ){
			// achei o campo que estava procurando
			if( sRec.spSlot.lPointer <= 0 ){
				// nao ha' slot gravado ainda
				ERETURN( LBSE_EMPTYSLOT );
			}
			// checa o arquivo LB4
			if( !LB4.IsOpen() ){
				ERETURN( LBSE_BASENOTOPEN );
			}
			long lfSize		= LB4.FileSize();
			if ( sRec.spSlot.pElem.lSize < 0 || 
					sRec.spSlot.pElem.lSize > ( lfSize - sRec.spSlot.lPointer ) ){
				// O tamanho do slot deste campo está inválido (maior que o possível).
				ERETURN( LBSE_ERROR );
			}

			SetError( LBS_OK );
			return( sRec.spSlot.pElem.lSize );
		}
	}
	ERETURN( LBSE_FIELDNOTFOUND );
}

BOOL			
LBSC_Base::ValidateFieldRep( long lRepReadSize, BOOL bCompress, LBSC_Field *pField, C_LB4 &LB4 )
{
	if ( lRepReadSize == DATA_HOLE_SIZE ) {
		return TRUE;
	}

	if ( lRepReadSize < 0 ) {
		return FALSE;
	}

	int iBinInfo[2];
	BOOL bRet		= TRUE;
	long lCurPos	= LB4.CurPos();
	long lfSize		= LB4.FileSize();

	switch ( pField->GetType() ){
		case TEXT_FIELD:
		case REFERENCED_FIELD:
			/// validar pelo tamanho do arquivo
			{
				if ( lRepReadSize > ( lfSize - lCurPos ) ){
					bRet = FALSE;
				}
			}
			break;
		case BINARY_FIELD:
			{
				if ( lRepReadSize > ( lfSize - lCurPos ) ){
					bRet = FALSE;
					break;
				}

				long lHeadBinSize = 2 * sizeof( int );
				if ( lRepReadSize <= lHeadBinSize ) {
					// tudo bem... algumas aplicacoes setam isso mesmo
					break;
				}

				if ( LB4.Read( iBinInfo, lHeadBinSize ) != OK ){
					bRet = FALSE;
				} else if ( iBinInfo[1] < ( lRepReadSize - lHeadBinSize ) ){
					bRet = FALSE;
				}
				LB4.Seek( lCurPos, SEEK_SET );
			}
			break;
		case ALPHA_FIELD:
			if (  lRepReadSize > pField->GetSize() ){
				bRet = FALSE;
			}
			break;
		case DATE_FIELD:
			if (  lRepReadSize > (long)DATEFIELDSIZE ){
				bRet = FALSE;
			}
			break;
		case TIME_FIELD:
			if (  lRepReadSize > (long)TIMEFIELDSIZE ){
				bRet = FALSE;
			}
			break;
		case VALUE_FIELD:
			if (  lRepReadSize > (long)(sizeof( long )) ){
				bRet = FALSE;
			}
			break;
		case DVALUE_FIELD:
			if (  lRepReadSize > (long)(sizeof( double )) ){
				bRet = FALSE;
			}
			break;
		case BYTE_FIELD:
			if (  lRepReadSize > (long)(sizeof( byte )) ){
				bRet = FALSE;
			}
			break;
		case SINT_FIELD:
			if (  lRepReadSize > (long)(sizeof( short int )) ){
				bRet = FALSE;
			}
			break;
		case FLOAT_FIELD:
			if (  lRepReadSize > (long)(sizeof( float )) ){
				bRet = FALSE;
			}
			break;
		default:
			/// não eh nenhum dos tipos conhecidos
			bRet = FALSE;
	}

	return( bRet );
}

