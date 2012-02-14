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
// Module: BASECL.H
// Description:
//
//	LBSC_BASE class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//		Tricia Souto Santos
//
// Last update: 29/11/94
//

#ifndef	_BASECL_H_
#define	_BASECL_H_

#include <sys/stat.h>

#ifndef _FIELDCL_H_
#include <fieldcl.h>
#endif
#ifndef	_DDECLIENT_OCCURRENCE_H_
#include <occurcl.h>
#endif
#ifndef	_PERMLIST_H_
#include <permlist.h>
#endif
#ifndef	_TICKETCL_H_
#include <ticketcl.h>
#endif
#ifndef _FIELSTCL_H_
#include <fielstcl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include <defclass.h>
#endif
#ifndef _LBSERRCL_H_
#include <cllbserr.h>
#endif
#ifndef _OPINFO_H_
#include <opinfocl.h>
#endif
#ifndef _LBSNETCL_H_
#include <lbsnetcl.h>
#endif
#ifndef	_FBUFF_H_
#include <fbuff.h>
#endif
#ifndef	_BASECACH_H_
#include <basecach.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class	LBSC_IndexSystem;
class	_LBSCLASS LBSC_Session;	// nao trocar este prototipo por um include <sesscl.h>.
								// se fizer isso, vai dar pau de compilacao.

class _LBSCLASS LBSC_Base : public LBSC_OpInfo
{
	friend	class	_LBSCLASS LBSC_Session;
	friend	class	_LBSCLASS CCache;

	private:

		LBSC_Occurrence		lbscOccurrence;
		LBSC_FieldList		flFieldList;
		char			*szBuffer;
		char			szStopWord[FULLNAMESIZE + 1];
		BOOL			bListaFisica;
		char			szBaseName[FULLNAMESIZE + 1];
		char			szNavKey[FULLNAMESIZE + 1];


		//
		// caches do cliente
		//
		CACL_Cache		cacACL;
		CRep_Cache		crcRep;
		CFieldSlot_Cache	cfscFieldSlot;
		COccur_Cache		cocOccur;

		TSRControlInfo ObtemControlInfo();

	public:

			const LBSC_Ticket		*pTicket;
			LBSC_Base();
			~LBSC_Base();

		LBSC_Base	*Duplicate() { return NULL; };
		int		Compare( LBSC_Base *lbscObj, int i = 0 );
		const LBSC_Ticket *GetTicket() { return pTicket; }

		// $$$ Estado do objeto apos instanciado
		BOOL		BaseObjOk( void );

		// $$$ Metodos para manipulacao de FIELDS
		int		AddField( const LBSC_Ticket *, TField * );
		int		AddField( const LBSC_Ticket *, char *, char *, char *,
						 TFieldType, long, TIndexAttrib, UINT );
		int		DelField( char * );
		int		DelField( UINT );
		int		ModifyFieldPassword( char *, char *, char * );
		int		ModifyFieldPassword( UINT, char *, char * );
		int		ModifyFieldName( char *, char *, char * );
		int		ModifyFieldName( UINT, char *, char * );
		int		ModifyFieldDescription( char *, char *, char * );
		int		ModifyFieldDescription( UINT, char *, char * );
		int		ModifyFieldSize( char *, char *, long );
		int		ModifyFieldSize( UINT, char *, long );
		int		ModifyFieldIndexAttrib( char *, char *, int );
		int		ModifyFieldIndexAttrib( UINT, char *, int );
		int		ModifyFieldAttrib( char *, char *, UINT );
		int		ModifyFieldAttrib( UINT, char *, UINT );
		int		GetNumberOfFields();
		int		GetIndexRecNum( const LBSC_Ticket *, BOOL );


		int		GetFieldId( const char * );
		TFieldType	GetFieldType( char * );
		TFieldType	GetFieldType( UINT );
		TIndexAttrib	GetFieldIndexAttrib( char * );
		TIndexAttrib	GetFieldIndexAttrib( UINT );
		int		GetFieldRepetition( char *, int, char * );
		int		GetFieldRepetition( UINT, int, char * );
		int		GetFieldRepetition( char *, int, void * );
		int		GetFieldRepetition( UINT, int, void * );
		int		GetFieldRepetition( char *, int, long * );
		int		GetFieldRepetition( UINT, int, long * );
		int		GetFieldRepetition( char *, int, double * );
		int		GetFieldRepetition( UINT, int, double * );
		int		GetFieldRepetition( char *, int, C_Date * );
		int		GetFieldRepetition( UINT, int, C_Date * );
		int		GetFieldRepetition( char *, int, C_Time * );
		int		GetFieldRepetition( UINT, int, C_Time * );
		int		GetFieldRepetition( char *, int, LBSC_Binary * );
		int		GetFieldRepetition( UINT, int, LBSC_Binary * );
		int		GetFieldRepetition( char *, int, LBSC_Reference * );
		int		GetFieldRepetition( UINT, int, LBSC_Reference * );
		int		GetFieldRepetition( char *, int, BYTE * );
		int		GetFieldRepetition( UINT, int, BYTE * );
		int		GetFieldRepetition( char *, int, short int * );
		int		GetFieldRepetition( UINT, int, short int * );
		int		GetFieldRepetition( char *, int, float * );
		int		GetFieldRepetition( UINT, int, float * );
		int		GetFieldRepetitionByVal( char *, char *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, char *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, void *, long, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, void *, long, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, long *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, long *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, double *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, double *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, C_Date *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, C_Date *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, C_Time *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, C_Time *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, LBSC_Binary *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, LBSC_Binary *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, LBSC_Reference *, BOOL );
		int		GetFieldRepetitionByVal( UINT, LBSC_Reference *, BOOL );
		int		GetFieldRepetitionByVal( char *, BYTE *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, BYTE *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, short int *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, short int *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( char *, float *, BOOL bStart = TRUE );
		int		GetFieldRepetitionByVal( UINT, float *, BOOL bStart = TRUE );
		int		PutFieldRepetition( char *, char * );
		int		PutFieldRepetition( UINT, char * );
		int		PutFieldRepetition( char *, void *, long );
		int		PutFieldRepetition( UINT, void *, long );
		int		PutFieldRepetition( char *, long );
		int		PutFieldRepetition( UINT, long );
		int		PutFieldRepetition( char *, double );
		int		PutFieldRepetition( UINT, double );
		int		PutFieldRepetition( char *, C_Date );
		int		PutFieldRepetition( UINT, C_Date );
		int		PutFieldRepetition( char *, C_Time );
		int		PutFieldRepetition( UINT, C_Time );
		int		PutFieldRepetition( char *, LBSC_Binary * );
		int		PutFieldRepetition( UINT, LBSC_Binary * );
		int		PutFieldRepetition( char *, LBSC_Reference * );
		int		PutFieldRepetition( UINT, LBSC_Reference * );
		int		PutFieldRepetition( char *, BYTE );
		int		PutFieldRepetition( UINT, BYTE );
		int		PutFieldRepetition( char *, short int );
		int		PutFieldRepetition( UINT, short int );
		int		PutFieldRepetition( char *, float );
		int		PutFieldRepetition( UINT, float );
		int		PutFieldRepetitionByIndex( char *, char *, int );
		int		PutFieldRepetitionByIndex( UINT, char *, int );
		int		PutFieldRepetitionByIndex( char *, void *, long, int );
		int		PutFieldRepetitionByIndex( UINT, void *, long, int );
		int		PutFieldRepetitionByIndex( char *, long, int );
		int		PutFieldRepetitionByIndex( UINT, long, int );
		int		PutFieldRepetitionByIndex( char *, double, int );
		int		PutFieldRepetitionByIndex( UINT, double, int );
		int		PutFieldRepetitionByIndex( char *, C_Date, int );
		int		PutFieldRepetitionByIndex( UINT, C_Date, int );
		int		PutFieldRepetitionByIndex( char *, C_Time, int );
		int		PutFieldRepetitionByIndex( UINT, C_Time, int );
		int		PutFieldRepetitionByIndex( char *, LBSC_Binary *, int );
		int		PutFieldRepetitionByIndex( UINT, LBSC_Binary *, int );
		int		PutFieldRepetitionByIndex( char *, LBSC_Reference *, int );
		int		PutFieldRepetitionByIndex( UINT, LBSC_Reference *, int );
		int		PutFieldRepetitionByIndex( char *, BYTE, int );
		int		PutFieldRepetitionByIndex( UINT, BYTE, int );
		int		PutFieldRepetitionByIndex( char *, short int, int );
		int		PutFieldRepetitionByIndex( UINT, short int, int );
		int		PutFieldRepetitionByIndex( char *, float, int );
		int		PutFieldRepetitionByIndex( UINT, float, int );
		int		MPutFieldRepetition( const LBSC_Ticket *, void * );
		void *	MGetFieldRepetition( UINT * );

		int		ModifyFieldRepetition( char *, int, char * );
		int		ModifyFieldRepetition( UINT, int, char * );
		int		ModifyFieldRepetition( char *, int, void *, long );
		int		ModifyFieldRepetition( UINT, int, void *, long );
		int		ModifyFieldRepetition( char *, int, long );
		int		ModifyFieldRepetition( UINT, int, long );
		int		ModifyFieldRepetition( char *, int, double );
		int		ModifyFieldRepetition( UINT, int, double );
		int		ModifyFieldRepetition( char *, int, C_Date );
		int		ModifyFieldRepetition( UINT, int, C_Date );
		int		ModifyFieldRepetition( char *, int, C_Time );
		int		ModifyFieldRepetition( UINT, int, C_Time );
		int		ModifyFieldRepetition( char *, int, LBSC_Binary * );
		int		ModifyFieldRepetition( UINT, int, LBSC_Binary * );
		int		ModifyFieldRepetition( char *, int, LBSC_Reference *);
		int		ModifyFieldRepetition( UINT, int, LBSC_Reference *);
		int		ModifyFieldRepetition( char *, int, BYTE );
		int		ModifyFieldRepetition( UINT, int, BYTE );
		int		ModifyFieldRepetition( char *, int, short int );
		int		ModifyFieldRepetition( UINT, int, short int );
		int		ModifyFieldRepetition( char *, int, float );
		int		ModifyFieldRepetition( UINT, int, float );

		int		DelFieldRepetition( char *, int, BOOL = FALSE);
		int		DelFieldRepetition( UINT, int, BOOL = FALSE );
		int		InsertBlankRepetition( UINT, int );
		int		GetNumberOfRepetition( char * );
		int		GetNumberOfRepetition( UINT );
		long		GetFieldRepetitionSize( char *, int );
		long		GetFieldRepetitionSize( UINT, int );
		TField		*GetFields( const LBSC_Ticket * );

		const LBSC_Field	*GetFieldObj( char * );
		const LBSC_Field	*GetFieldObj( UINT );

		// $$$ Metodos para tratamento de registros
		long		GetNumRecords( const LBSC_Ticket * );
		long		CurrRecNum( const LBSC_Ticket * );
		BYTE		CurrRecStatus( const LBSC_Ticket * );
		int		LockRecord( const LBSC_Ticket *, BOOL bUncondit = FALSE );
		int		ReleaseRecord( const LBSC_Ticket * );
		int		UpdateRecord( const LBSC_Ticket * );
		int		AppendRecord( const LBSC_Ticket * );
		int		ReadRecord( const LBSC_Ticket * );
		int		DeleteRecord( const LBSC_Ticket * );
		int		ClearRecord();
		int		SetLockTimeOut( const LBSC_Ticket *, int );
		int		SetReorganizeRecQuant( const LBSC_Ticket *, long );

		// $$$ Metodos para caminhamento sobre a LO
		int		FirstRecord( const LBSC_Ticket * );
		int		LastRecord( const LBSC_Ticket * );
		int		NextRecord( const LBSC_Ticket * );
		int		PreviousRecord( const LBSC_Ticket * );
		int		NthRecord( const LBSC_Ticket *, long );
		int		CurrentRecord( const LBSC_Ticket * );

		// $$$ Metodos para obtencao de uma ocorrencia a partir de
		// $$$ caminhamentos sobre a LO
		const LBSC_Occurrence	*GetCurrentOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence 	*GetFirstOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence 	*GetLastOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence 	*GetNextOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence 	*GetPreviousOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence 	*GetNthOccurrence( const LBSC_Ticket *, long );

		// $$$ tratamento de LO's
		long		GetNumOccurrences( const LBSC_Ticket * );
      		long		GetNumOLRecords( const LBSC_Ticket * , int);
		int		*Search( const LBSC_Ticket *, char * );
		int		SaveOcList( const LBSC_Ticket *, int, char * );
		int     	SortOcList( const LBSC_Ticket *, int, char *, BOOL );
		int		EnableSecureSort( BOOL );
		BOOL		SecureSortStatus( );
		int		LoadOcList( const LBSC_Ticket *, char * );
		int		EnableOcList( const LBSC_Ticket *, int );
		char   		*GetCurrentExpression( const LBSC_Ticket * );
		char     	*GetOcListExpression( const LBSC_Ticket *, int );
		long		GetOLRecNumber( const LBSC_Ticket * );
		int		UnloadOcList( const LBSC_Ticket *, int );
		int		DeleteOcList( const LBSC_Ticket *, char * );
		int		DeleteOcRecords( const LBSC_Ticket * );

		// $$$ Metodos para tratamento de StopWords
		int		AddStopWord( const LBSC_Ticket *, char * );
		const char	*GetCurrentStopWord( const LBSC_Ticket * );
		const char	*GetFirstStopWord( const LBSC_Ticket * );
		const char	*GetLastStopWord( const LBSC_Ticket * );
		const char	*GetNextStopWord( const LBSC_Ticket * );
		const char	*GetPreviousStopWord( const LBSC_Ticket * );
		const char	*GetNthStopWord( const LBSC_Ticket *, int );
		const char	*SearchStopWord( const LBSC_Ticket *, const char *, int );
		char		*GetStopWords( const LBSC_Ticket * );
		long		GetNumberOfStopWords( const LBSC_Ticket * );

		// $$$ Metodos para tratamento de GoWords
		int		AddGoWord( UINT, char * );
		int		DelGoWord( UINT, char * );
		BOOL			GetGowords( char  *, char **);
		BOOL			SetGowords( char  *, const char *);

		// Metodos para tratamento do Minkeysize
		int				GetMinkeysize( );
		int				SetMinkeysize( int );

		// $$$ Metodos para tratamento de ACL's
		int		SetACLPerm( char *, long, char *, BYTE, int );
		int		GetACLPerm( char *, long, char *, int, BOOL = TRUE );
		int		DelACLPerm( char *, long, char *, int );
		LBSC_PermList 	*GetACLListPermission( char *, int );

		// Metodos para tratamento de contadores
		int		GetNumberOfCounters();
		long	GetCount( int );
		int		PutCount( int, long );
		int		IncCount( int, long = 1 );
		int		DecCount( int, long = 1 );
		int		LockCount( int, BOOL = FALSE );
		int		ReleaseCount( int );
      
/********************************************
*********************************************
*********************************************

   QUE TAL ISSO? EH FACILMENTE IDENTIFICAVEL?
********************************************
*********************************************
*********************************************/

		long		GetNextCount( int );
		long		GetPreviousCount( int );


		// $$$ Metodos para tratamento de indexacao
		int		EnableOnLineIndex( BOOL );
		BOOL		OnLineIndexStatus();
		int		UpdateIndex( const LBSC_Ticket * );
		int		IndexAll( const LBSC_Ticket *, BOOL = FALSE  );
		int		IndexString( const LBSC_Ticket *, long, UINT, int, char * );
		int		UnindexString( const LBSC_Ticket *, long, UINT, int, char * );

		// $$$ Metodos de uso geral
		int		ModifyBaseOwnerName( const LBSC_Ticket *, char *, char * );
		int		ModifyPassword( const LBSC_Ticket *, char *, char * );
		int		ModifyMaintenancePassword( const LBSC_Ticket *, char *, char * );
		int		ModifyRecordPassword( const LBSC_Ticket *, char *, char * );
		char		*GetUserBase();
		char		*GetOwnerName();
		int		GetFullBaseName( char * );
		int		GetBaseName( char * );
		BOOL		IsEncrypt();
		BOOL		IsFullAccess();
		BYTE		GetBaseType();
		int			GetBaseVersion();
		int		ModifyBaseType( BYTE );
		TBaseInfo	*GetBaseInfo( const LBSC_Ticket * ); 

		// Localizacao de palavras no indice
		int		Locate( const LBSC_Ticket *, UINT, int, char *, int iType = EQUAL_KEY );
		int		SetNavigationByIndex( const LBSC_Ticket *, BOOL, UINT uiFieldId = 0, int iIndex = 0,
						int iType = EQUAL_KEY );
		int		SetNavigationByKey( const LBSC_Ticket *, BOOL, UINT uiFieldId = 0, int iIndex = 0, 
						char *szKey = NULL, int iType = EQUAL_KEY );

		// Slots
		int		GetNumberOfSlots();
		int		GetSlot( int, void * );
		long		GetSlotSize( int );
		int		PutSlot( int, void *, int );
		int		GetFieldSlot( UINT, void * );
		long		GetFieldSlotSize( UINT );
		int		PutFieldSlot( UINT, void *, int );

		BOOL		IndexSystemOk();

		char		*ExchangeOperator( char * );
		int		SetMask( char *, int, int = 1 );
		char		*GetMask( int );
		int		SaveMasks( char * );
		int		LoadMasks( char * );
		int		ClearMasks( char * );
		int		AddPhone( char *, int );
		int		DeletePhone( char * );
		int		SavePhone( char * );
		int		LoadPhone( char * );
		int		ClearPhone();
		int		FindPhone( char *, char * );
		char		*SetStandardizer( char * );
		int		Standardize( char *, char *, int );
		int		AddSynonym( char *, char *, int );
		int		DeleteSynonym( char *, char *, int );
		int		SaveSynonym( char * );
		int		LoadSynonym( char * );
		int		ClearSynonym();
		char		*FindSynonym( char * );
		int		OLAnd( const LBSC_Ticket *, int, int );
		int		OLOr( const LBSC_Ticket *, int, int );
		int		OLXor( const LBSC_Ticket *, int, int );
		int		OLNot( const LBSC_Ticket *, int, int );

		BOOL		IsExportable();
		int		BlockReExport( const LBSC_Ticket * );


		BOOL		IsExclusive();
		BOOL		IsReadOnly();
		BOOL		Flush( LBSC_Ticket * );
		long		GetNumActiveRecords( const LBSC_Ticket * );
		int		ModifyMaxKeySize( const LBSC_Ticket *, int );
		int 		GetNumRecIndex();
		BOOL	 	GetStopIndex();
		void		SetStopIndex( BOOL );
		int			ClearBase( const LBSC_Ticket * );
		int			ModifyBaseName( char * );
		int			GetBaseLongName( char * );
		void	CancelOperation();				// cancela a operacao corrente
		void	GetOpInfo( char *, float * );	// obtem o status da operacao corrente


		/*************
		Nada de Operadores

		LBSC_Field 	&operator[]( int );
		LBSC_Field 	&operator()( UINT );
		LBSC_Field 	&operator[]( char * );

		*************/

		int				DelStopWord( const LBSC_Ticket *, char * );
		TACL_Lists		*GetAllACLLists( const LBSC_Ticket * );
		C_Buffer *GetAllRepetitions( const LBSC_Ticket *, int = 1);
		TSlotCache *GetAllFieldSlots( const LBSC_Ticket *pTicket );
		COccurList *GetAllOccurrences( const LBSC_Ticket *pTicket );
		int EnableFastRecord( BOOL bFastRecPar );
		int GetBaseTimeInfo( struct stat * );
		// obtem o nome do dir_base para as bases do LBS
		static	void			GetDirBase( char *szBuffer, const char *szUDB = NULL, const char *szServer = NULL );

		void InvalidaRepCache();
		void InvalidaACLCache();
		void InvalidaOccurrCache();
		void InvalidaFieldSlotCache();
		void EnableMultipleRecords( int iNumRegs );
		void DisableMultipleRecords();

		TSROut_GenericBuffer GetLocalRepCache( struct stat );
		void SaveLocalRepCache( TSROut_GenericBuffer, struct stat );

};

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _BASECL_H_


