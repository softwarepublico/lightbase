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
// Module: FIELDCL.H
// Description:
//
//	Header file for field handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 20/10/94
//

#ifndef	_FIELDCL_H_
#define	_FIELDCL_H_

#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_DATALIST_H_
#include	<datalist.h>
#endif
#ifndef	_LINKLISTCL_H_
#include	<linklist.h>
#endif
#ifndef	_PASSWDCL_H_
#include	<passwdcl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef _CL_STRINGN_
#include	<stringn.h>
#endif


// $$$ API LIGHT-TEXT
#include	<lt.h>
#include	<termlist.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


#define	VALID_DATALIST		(0x01)
#define	ORIGINAL_DATALIST	(0x02)

typedef	enum _srtSortRepType { MASTER_FIELD_SORT, GROUP_FIELD_SORT } SortRepType;


class CritFieldManager : public CritSectManager
{
	void CritSectLog( char *szMsg, char *szFile, int iLine, int iNum );
	unsigned long GetCritSectMask();
	void SetCritSectMask( unsigned long );
	BOOL OrderedDependents();
};
extern CritFieldManager _csFieldMan;

// classe para tratamento de regioes criticas
class	C_GlobalFieldCritSect : public C_CritSect<3>	// 3 = numero de regioes criticas
{
public:
	C_GlobalFieldCritSect()
	{
	}
};


class LBSC_RepSort;


extern	C_GlobalFieldCritSect	*_pcGlobalFieldCritSect;

class _LBSCLASS LBSC_Field
{
	friend	class	_LBSCLASS LBSC_Session;
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Record;
	friend	class	_LBSCLASS LBSC_Data;
	friend	class	_LBSCLASS LBSC_Parser;
	friend	class	_LBSCLASS LBSC_EntParser;
	friend	class	_LBSCLASS LBSC_OLSort;
	friend	class			  LBSC_RepSort;

	private:
		LBSC_Base					*plbscbBase;
		CL_StringN<FIELDNAMESIZE>  	szFieldOrigName;
		CL_StringN<FIELDNAMESIZE>  	szAliasName;
		CL_StringN<DESCRIPTIONSIZE>	szFieldDescription;
		UINT						uiFieldId;
		LBSC_Password				lbscpPassword;
		TFieldType					tftFieldType;
		LBSC_DataList				lbscdlDataList;
		LBSC_DataList				lbscdlOriginalDataList;
		LBSC_DataList				*pDataList;
		long						lFieldSize;
		BOOL						bFlagUpdate;
		BOOL						bFlagStructUpdated;
		UINT						uiFieldAttrib;
		TIndexAttrib				tiaIndexAttrib;
		LTC_TERMLIST				*pltcgwGoWords;
		int							iError;
		int							iGroup;				// numero do grupo ao qual o campo pertence (vide LBW)
		int							iNumberOfUpdates;	// numero de atualizacoes no campo
		long						lSlotSize;			// tamanho do slot do campo
		void						*pvSlot;			// slot
		BOOL						bMustFillOriginalDataList;
		BOOL						bRead;




		int					ModifyPassword( char * );
		int					ModifyAliasName( char * );
		int					ModifyDescription( char * );
		int					ModifySize( long );
		const char			*GetPassword();
		BYTE				GetPasswordType();
		void				Init();
		const void			*GetConstRepByIndex( int );

		int					AddGoWord( char * );
		int					DelGoWord( char * );
		void				SetId( UINT );
		int					IsError();
		void				SetSlot( long, void * );

		BOOL				IsPermOk( BYTE );
		void				SetError( int );
		void				SetDataListTo( int );
		int					WhatDataList();


		// operadores (eram publicos, mas vieram para a area privada para
		// (proibir o uso por causa do RPC)
		int			operator == ( LBSC_Field& b );
		
		LBSC_Data	*operator []( int );

		LBSC_Field&	operator = ( LBSC_Field& );

		LBSC_Field	*operator << ( long );
		LBSC_Field	*operator << ( double );
		LBSC_Field	*operator << ( char * );
		LBSC_Field	*operator << ( void * );
		LBSC_Field	*operator << ( C_Date & );
		LBSC_Field	*operator << ( C_Time & );
		LBSC_Field	*operator << ( LBSC_Binary & );
		LBSC_Field	*operator << ( LBSC_Reference & );
		LBSC_Field	*operator << ( BYTE );
		LBSC_Field	*operator << ( short int );
		LBSC_Field	*operator << ( float );

		void operator = ( long );
		void operator = ( double );
		void operator = ( char * );
		void operator = ( void * );
		void operator = ( C_Date & );
		void operator = ( C_Time & );
		void operator = ( LBSC_Binary &  );
		void operator = ( LBSC_Reference & );
		void operator = ( BYTE );
		void operator = ( short int );
		void operator = ( float );

	public:
					LBSC_Field( char *, char *, char *,
						    TFieldType , long, UINT, UINT,
						    TIndexAttrib tiaIndexAttrib = 0,
						    LBSC_Base * = NULL );
					~LBSC_Field();
		int				Clear();
		int				GetNumberOfRepetition();
		void			*GetRepetitionByIndex( int );
		int				GetRepetitionByVal( void *, BOOL, long = -1 );
		int				AddRepetition( void *, long = -1L );
		int				ModifyRepetitionByIndex( int , void *, long = -1L );
		int				PutRepetition( void *, int , long = -1L );
		int				DeleteRepetitionByIndex( int, BOOL = TRUE, BOOL = FALSE );
		int				CreateLink( char *, char *, BYTE, BOOL );
		int				DeleteLink( char *, char * );
		LBSC_Field 		*Duplicate();
		int				Compare( LBSC_Field *, int );

		TFieldType		GetType();
		const char		*GetAliasName();
		const char		*GetDescription();
		long			GetSize();
		UINT			GetId();

		int				VerifyPassword( char * );

		int				SetIndexAttrib( int );
		TIndexAttrib	GetIndexAttrib();

		// GoWords
		char			*GetFirstGoWord();
		char			*GetNextGoWord();
		char 			*GetCurrentGoWord();
		char			*GetNthGoWord( int );
		char			*SearchGoWord( char * );
		long			GetNbrOfGoWord();
		LBSC_Base		*GetOwnerBase();

		// Atributos
		UINT			GetAttrib();
		void			SetAttrib( UINT );

		// liga o flag de atualizacao do campo (nao atualize bFlagUpdate diretamente,
		// sem usar este metodo)
		void			UpdateFieldFlag( BOOL bFlagUpdatePar, long lIndex = -1 );

		// grupo
		int				GetGroup();

		// ordenacao de repeticoes
		int				SortRepetition( SortRepType stSortType, LBSC_Field *pfMasterField = NULL );

		// verifica se uma dada repeticao eh igual aa ja' existente
		BOOL			IsTheSameRepetition( void *pvRepetition, int iIndex, long lSizePar = -1 );

		// tratamento do numero de vezes em que o campo foi atualizado
		int				GetNumberOfUpdates();
		void			ClearNumberOfUpdates();
		void			IncNumberOfUpdates();

		void			FillOriginalDataList();
};

class	C_FieldCritSect
{
	int			iLastSectUsed;
	LBSC_Field	*pObj;

public:
	C_FieldCritSect( LBSC_Field *pObjPar, int iNumCritSect, char *szFile, int iLinePar )
	{
		if( _pcGlobalFieldCritSect ){
			_pcGlobalFieldCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar, szFile, iLinePar );
			iLastSectUsed = iNumCritSect;
			pObj = pObjPar;
		}
	}
	~C_FieldCritSect()
	{
		if( _pcGlobalFieldCritSect ){
			_pcGlobalFieldCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
	void EnterCriticalSection()
	{
		if( _pcGlobalFieldCritSect ){
			_pcGlobalFieldCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
		}
	}
	void LeaveCriticalSection()
	{
		if( _pcGlobalFieldCritSect ){
			_pcGlobalFieldCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _FIELDCL_H_


