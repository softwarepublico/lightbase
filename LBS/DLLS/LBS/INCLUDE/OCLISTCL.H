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
// Module: OcListcl.H
//	LBSC_OcList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//		Trícia Souto Santos
//
// Last revision: 02/09/94
//


#ifndef _LBSC_OCLIST_H_
#define	_LBSC_OCLIST_H_

#ifndef	_OCCURRENCE_H_
#include <Occurcl.h>
#endif

#ifndef         _OCC_LIST
#include	<occ_list.h>
#endif

class LBSC_OcList {
private:
	long lCurPos;
	long lSize;
	long lTotalOccs;
	LTC_OCCURRENCELIST **pOccListVet;

	void Free()
	{
		if ( pOccListVet ) {
			for ( int i=0; i<lSize; i++ ) {
				if ( pOccListVet[i] ) {
					delete pOccListVet[i];
					pOccListVet[i] = NULL;
				}
			}
			delete pOccListVet;
		}
		pOccListVet = NULL;
		lCurPos = 0;
		lSize = 0;
	}
public:
	LBSC_OcList()
	{
		lCurPos = 0;
		lSize = 0;
		pOccListVet = NULL;
		lTotalOccs = 0;
	}
	~LBSC_OcList()
	{
		Free();
	}
	BOOL Init ( long lInitSize ) 
	{
		Free();
		if ( lInitSize <= 0 ) {
			return TRUE;
		}
		pOccListVet = new LTC_OCCURRENCELIST *[lInitSize];

		if ( !pOccListVet ) {
			return FALSE;
		}
		lSize = lInitSize;
		lCurPos = 0;
		lTotalOccs = 0;
		memset( pOccListVet, 0, lSize * sizeof(LTC_OCCURRENCELIST *));
		return TRUE;
	}
	BOOL Shrink ( long lNewSize )
	{
		if ( lNewSize < 0 || lNewSize > lSize || !pOccListVet ) {
			return FALSE;
		}
		if ( lNewSize == lSize ) {
			return TRUE;
		}
		if ( lNewSize == 0 ) {
			Free();
			return TRUE;
		}
		LTC_OCCURRENCELIST **pNewOccListVet = new LTC_OCCURRENCELIST *[lNewSize];

		if ( !pNewOccListVet ) {
			return FALSE;
		}
		memcpy( pNewOccListVet, pOccListVet, lNewSize * sizeof(LTC_OCCURRENCELIST *) );

		for ( int i=lNewSize; i<lSize; i++ ) {
			if ( pOccListVet[i] ) {
				delete pOccListVet[i];
			}
		}
		delete pOccListVet;
		pOccListVet = pNewOccListVet;

		lSize = lNewSize;
		lCurPos = 0;
		return TRUE;
	}

	BOOL Goto ( long lNewPos )
	{
		if ( lNewPos >= lSize || lNewPos < 0 || !pOccListVet ) {
			// posicao invalida ou existe uma inconsistencia
			return FALSE;
		}

		lCurPos = lNewPos;

		return TRUE;
	}

	BOOL Next ()
	{
		if ( lCurPos+1 >= lSize || !pOccListVet ) {
			// ja estamos no fim ou existe uma inconsistencia
			return FALSE;
		}

		lCurPos++;
		if ( pOccListVet[lCurPos] ) {
			(pOccListVet[lCurPos])->LT_GetFirstOccurrence();
		}
		return TRUE;
	}

	BOOL Previous ()
	{
		if ( lCurPos-1 < 0 || !pOccListVet ) {
			// ja estamos no inicio ou existe uma inconsistencia
			return FALSE;
		}

		lCurPos--;

		if ( pOccListVet[lCurPos] ) {
			(pOccListVet[lCurPos])->LT_GetFirstOccurrence();
		}
		return TRUE;
	}

	BOOL First ()
	{
		if ( !pOccListVet ) {
			// existe uma inconsistencia
			return FALSE;
		}
		lCurPos = 0;

		if ( pOccListVet[lCurPos] ) {
			(pOccListVet[lCurPos])->LT_GetFirstOccurrence();
		}
		return TRUE;
	}

	BOOL Last ()
	{
		if ( !pOccListVet ) {
			// existe uma inconsistencia
			return FALSE;
		}
		lCurPos = lSize-1;

		if ( pOccListVet[lCurPos] ) {
			(pOccListVet[lCurPos])->LT_GetFirstOccurrence();
		}
		return TRUE;
	}

	BOOL Add ( LTC_OCCURRENCE *pOcc )
	{
		if ( !pOccListVet ) {
			// existe uma inconsistencia
			return FALSE;
		}

		if ( !pOccListVet[lCurPos] ) {
			pOccListVet[lCurPos] = new LTC_OCCURRENCELIST;
			if ( !pOccListVet[lCurPos] ) {
				return FALSE;
			}
		}

		pOccListVet[lCurPos]->LT_AddOccurrence(pOcc, TAIL );
		lTotalOccs++;
		return TRUE;
	}

	long CurPos()
	{
		return lCurPos;
	}

	BOOL Del () 
	{
		if ( pOccListVet[lCurPos] ) {
			lTotalOccs -= pOccListVet[lCurPos]->LT_GetNumberOfOccurrence();
			delete pOccListVet[lCurPos];
			pOccListVet[lCurPos] = NULL;
		}

		if ( lSize <= 1 ) {
			Free();
			return TRUE;
		}

		LTC_OCCURRENCELIST **pNewOccListVet = new LTC_OCCURRENCELIST *[lSize-1];

		if ( !pNewOccListVet ) {
			return FALSE;
		}

		if ( lCurPos > 0 ) {
			// copia as primeiras posicoes 
			memcpy( pNewOccListVet, pOccListVet, lCurPos * sizeof(LTC_OCCURRENCELIST *) );
		}

		if ( lCurPos < lSize-1 ) {
			// copia as ultimas posicoes 
			memcpy( pNewOccListVet + lCurPos, pOccListVet+lCurPos+1, (lSize-lCurPos-1) * sizeof(LTC_OCCURRENCELIST *) );
		}

		if ( lCurPos == lSize-1 ) {	
			// decrementa a posicao corrente apenas se deletar o ultimo
			lCurPos--;
		}
		lSize--;

		delete pOccListVet;
		pOccListVet = pNewOccListVet;

		if ( pOccListVet[lCurPos] ) {
			(pOccListVet[lCurPos])->LT_GetFirstOccurrence();
		}
		return TRUE;
	}

	LTC_OCCURRENCE	*GetCurrentOccurrence()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetCurrentOccurrence();
	}

	LTC_OCCURRENCE	*GetFirstOccurrence()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetFirstOccurrence();
	}

	LTC_OCCURRENCE	*GetNextOccurrence()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetNextOccurrence();
	}

	LTC_OCCURRENCE	*GetPreviousOccurrence()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetPreviousOccurrence();
	}

	LTC_OCCURRENCE	*GetLastOccurrence()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetLastOccurrence();
	}

	LTC_OCCURRENCE	*NthOccurrence( long lNewPos )
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetOccurrence(lNewPos);
	}

	long GetNumberOfOccurrences()
	{
		if ( !pOccListVet || !pOccListVet[lCurPos] ) {
			return FALSE;
		}

		return (pOccListVet[lCurPos])->LT_GetNumberOfOccurrence();
	}

	long GetTotalNumberOfOccurrences()
	{
		return lTotalOccs;
	}

	long Size()
	{
		return lSize;
	}

	LTC_OCCURRENCELIST *GetLTList()
	{
		if ( !pOccListVet ) {
			return NULL;
		}

		return pOccListVet[lCurPos];
	}

	void SetLTList( LTC_OCCURRENCELIST *pList )
	{
		if ( !pOccListVet ) {
			return;
		}

		if ( pOccListVet[lCurPos] ) {
			lTotalOccs -= (pOccListVet[lCurPos])->LT_GetNumberOfOccurrence();
			if ( lTotalOccs < 0 ) {
				lTotalOccs = 0;
			}
			delete pOccListVet[lCurPos];
		}
		lTotalOccs += pList->LT_GetNumberOfOccurrence();

		pOccListVet[lCurPos] = pList;
	}

	void CreateFullLTList( LTC_OCCURRENCELIST *pList )
	{
		if ( !pOccListVet || !pList ) {
			return;
		}

		long lCur = CurPos();

		for ( long i=0; i<Size(); i++ ) {
			if ( !Goto( i ) ) {
				continue;
			}
			LTC_OCCURRENCE *pOcc = GetFirstOccurrence();
			while ( pOcc ) {
				pList->LT_AddOccurrence( pOcc, TAIL );
				pOcc = GetNextOccurrence();
			}
		}
	}

};

#endif //_LBSC_OCLIST_H_


