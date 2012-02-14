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

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif

#ifndef _LB1_
#include	<lb1cl.h>
#endif
#ifndef _LB3_
#include	<lb3cl.h>
#endif
#ifndef _LB4_
#include	<lb4cl.h>
#endif
#ifndef	_ACLLIST_H_
#include	<acllist.h>
#endif
#ifndef _LB3LIST_H_
#include	<lb3list.h>
#endif
#ifndef _LBSC_OCLIST_H_
#include	<oclistcl.h>
#endif
#ifndef	_INDSYSCL_H_
#include	<indsyscl.h>
#endif
#ifndef	_TICKETCL_H_
#include	<ticketcl.h>
#endif
#ifndef	_EXPORTLIST_H_
#include	<explist.h>
#endif
#ifndef	_SERLST_H_
#include	<serlst.h>
#endif
#ifndef _LBSERRCL_H_
#include	<lbserrcl.h>
#endif
#ifndef	_PARSERCL_H_
#include	<parsercl.h>
#endif
#ifndef	_ENTPARCL_H_
#include	<entparcl.h>
#endif
#ifndef	_LBSOLLST_H_
#include	<lbsollst.h>
#endif
#ifndef	_RECORD_H_
#include	<record.h>
#endif
#ifndef	_OPINFO_H_
#include	<opinfocl.h>
#endif
#ifndef	_IDXOFF_H_
#include	<idxoffcl.h>
#endif
#include	<oldlb1cl.h>

#include <regcrit.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class	LBSC_LinkList;

class	LBSC_IndexSystem;
class	_LBSCLASS LBSC_Session;	// nao trocar este prototipo por um include <sesscl.h>.
								// se fizer isso, vai dar pau de compilacao.
class	LBSC_RepSort;
class	BaseInstance;
class	LBSC_BaseTimersList;

#define	LB1		cfBaseControlFile
#define	LB3		cfBaseStructFile
#define	LB4		cfBaseRepetitionFile

#define	ISCOMPONENTLIST( x )			((x == USERFORM) || (x == GROUPFORM) ||	(x == USERREPORT) || (x == GROUPREPORT))

//////////// LOG ////////////////////
typedef	enum _enLogType { OPEN_BASE, READ_RECORD, UPDATE_RECORD, APPEND_RECORD, DELETE_RECORD, SEARCH_OK, SEARCH_ERROR, CLOSE_BASE } LogType;
#define	LOGUSE	PrintLogUse

class CritBaseManager : public CritSectManager
{
	void CritSectLog( char *szMsg, char *szFile, int iLine, int iNum );
	unsigned long GetCritSectMask();
	void SetCritSectMask( unsigned long );
	BOOL OrderedDependents();
};
extern CritBaseManager _csBaseMan;

// classe para tratamento de regioes criticas
class	C_GlobalBaseCritSect : public C_CritSect<20>	// 20 = numero de regioes criticas para tratamento de sessao
{
public:
	C_GlobalBaseCritSect()
	{
		UseCriticalSection( TRUE );
		SetManager( &_csBaseMan );
	}
};

extern	C_GlobalBaseCritSect	*_pcGlobalBaseCritSect;

class _LBSCLASS LBSC_Base :	public LBSC_Error, 
							public LBSC_OpInfo,
							C_LeaveCritSect<C_GlobalBaseCritSect>
{
	friend	class	_LBSCLASS LBSC_Record;
	friend	class	_LBSCLASS LBSC_Session;
	friend	class	_LBSCLASS LBSC_Parser;
	friend	class	_LBSCLASS LBSC_EntParser;
	friend	class	_LBSCLASS LBSC_Field;
	friend	class	_LBSCLASS LBSC_OLSort;
	friend	class	_LBSCLASS LBSC_EntParser;
	friend	class	_LBSCLASS LBSC_OLSort;
	friend	class			  LBSC_RepSort;

	friend	void	ReleaseLocks( LBSC_BaseTimersList *pBaseTimersList );

	private:
		BOOL						bHeaderLocked;			// indica se o header da base esta' travado ou nao
		LBSC_IndexSystem			*plbscisIndexSystem;	// Index System
		LBSC_Parser					lbscpParser;			// Parser
		LBSC_EntParser				epEntParser;			// Parser especial para o indice ENTIRETREE
		int							iLockTimeOut;			// timeout de lock de registro
		long						lLockPos;				// Last lock file position
		UINT						uTimerId;				// timer id for lock-timer
		BOOL						bIsExclusive;			// flag to define if this base is opened in exclusive mode
		BOOL						bIsReadOnly;			// flag to define if this base is opened only for read
		BOOL						bBaseUpdated;			// flag to define if this base is updated
		BOOL						bBaseObjOk;				// OK flag
		BOOL						bPrivateCreation;
		BOOL						bStruct;
		BOOL						bSelfDelete;
		BOOL						bFullAccess;
		BOOL						bSelfReorganize;
		BOOL						bACLChanged;
		CL_StringN <FILENAMESIZE>	szBaseName;				// Base file name
		CL_StringN <FULLNAMESIZE>	szBaseLongName;			// Base long-file name
		CL_StringN <PATHNAMESIZE>	szBasePath;				// Base path
		CL_StringN <FULLNAMESIZE>	szCompleteBaseName;		// Complete Base Name (i.e. base\\viewbase)
		C_Date						cdCreateDate;			// Base creation date
		C_Date						cdLastModifyDate;		// Last modify date
		LBSC_Session				*plbscsOwnerSession;	// Owner session of this base
		C_LB1						cfBaseControlFile;		// File with records information - LB1
		C_LB3						cfBaseStructFile;		// File with the base struct (records format) - LB3
		C_LB4						cfSlotsFile;			// arquivo com os slots (de campo e de base
		BaseInstance				*pBaseInstance;			// Informacoes compartilhadas relativas a base 
		LBSC_ACLList				lbscaBaseUserAcl;		// Base User ACL
		LBSC_ACLList				lbscaBaseGroupAcl;		// Base Group ACL
		LBSC_ACLList				lbscaFieldUserAcl;		// Field User ACL
		LBSC_ACLList				lbscaFieldGroupAcl;		// Field Group ACL
		LBSC_ACLList				lbscaRecordUserAcl;		// Record User ACL
		LBSC_ACLList				lbscaRecordGroupAcl;	// Record Group ACL
		LBSC_ACLList				lbscaFormUserAcl;		// Form User ACL
		LBSC_ACLList				lbscaFormGroupAcl;		// Form Group ACL
		LBSC_ACLList				lbscaReportUserAcl;		// Report User ACL
		LBSC_ACLList				lbscaReportGroupAcl;	// Report Group ACL
		LBSC_Record					lbscrCurrRecord;		// Current record
		LBSC_Occurrence				lbscOcAux;				// Aux occurrence
		void						*pvUserData;			// buffer do usuario; nao tem significado para o LBS
		long						lUserDataSize;			// tamanho do buffer do usuario

		LTC_TERMLIST				*pltctlStopWordList;

		LTC_TERMLIST				*pltcMaskList;			// lista de mascaras
		LTC_PHONE					*pltcPhone;				// conjunto de fonemas
		LTC_SYNONYM					*pltcSynonym;			// conjunto de sinonimos
		int							iNavigationState;		// flag de navegacao. Indica se o caminhamento na base
		int							iSearchType;			// tipo de busca feito no LT_GetKey (igual, maior, menor ... )
															// depende de um indice ou de uma chave ou nenhum desses
		char						*szStdArray;			// String de normalizacao usada pelo sistema de
															// indices no momento de um SetNavigation
		int							iNavigationIndex;		// Indice usado para navegacao nos registros
		UINT						uiNavigationField;		// Campo usado para navegacao nos registros
		char						*szNavigationKey;		// Chave utilizada para navegacao nos registros
		LBSC_OLList					*pcOLList;				// Lista de todas as LO's geradas
		LTC_OCCURRENCELIST			*pOcListOfCurrKey;		// lista de ocorrencias gerada pela chave corrente
															// de navegacao de registros
		int							iIndexTree;				// indice correntemente utilizado para indexacao
		int							iLockTimeSleep;			// tempo de espera para nova tentativa de lock em registro
															// (tempo em milisegundos)
		BOOL						bStopIndex;				// indica se a aplicacao deseja paradas periodicas durante
															// uma indexacao total.
		BOOL						bSecureSort;			// status de seguranca da ordenacao da LO fisica
		BOOL						bAppendingRec;			// indica se um registro esta' sendo adicionado na base 
															// (usado no Append e no UpdateRecord)
		BOOL						bIsBasePasswdCorrect;	// informa se a password da base foi indicada 
															// corretamente no Open da base
		BOOL						bFastRec;				// indica se os registros vao ser gravados no modo "fast" ou nao.
		C_IDXOFF					cfLB5;					// arquivo para log de registros gravados em modo off-line
		BOOL						bUsingCompress;			// indica se a base esta' usando compressao dos dados ou nao
		CL_StringN<FIELDNAMESIZE>	strLogFieldAliasName;	// alias do campo que deve ir para o log de uso.
		int							iOperationLogMask;		// mascara para as operacoes para as quais se quer log de uso
		CL_StringN<FULLNAMESIZE>	szExcludeModulesFromLog;	// modulos a serem excluidos da geracao de log de uso, mesmo com a mascara setada
		CL_StringN<FULLNAMESIZE>	szFieldsForUpdateLog;	// campos para os quais se deve gerar log dos valores anteriores aa alteracao
		CLBRegCrit					rcRegCrit;				// para proteger os atributos da classe de acesso concorrente via metodos publicos
		LBSC_OLSort					*pSortObj;				// ponteiro pro objeto sort que indicara que campos precisa ser ordenados


#ifdef __TEST
		// atributos para tratamento de contextos para testes

		// contexto de ponteiros
		void						**ppCtxPointerArray;
		int							iSizeofPointerArray;
		int							iCurrentPointerArrayPos;
#endif




		// Metodos privados

					LBSC_Base( const LBSC_Ticket *, const char *, const char *, const char *, LBSC_Session *, BOOL, BOOL, BOOL, BOOL = TRUE );
					LBSC_Base( const LBSC_Ticket *, const char *, LBSC_Session *, BOOL = FALSE, BOOL = TRUE, BOOL = FALSE );
					LBSC_Base( const char * );
		void			Init();
		BOOL			BaseIndexed() { return( LB1.tcrHead.bBaseIndexed ); };
		BOOL			BaseStruct();
		int			Delete();
		int			Create( const LBSC_Ticket *, char *, char *, char*,
						BYTE, BOOL, LBSC_Session *,
						char *, TField* = 0, DWORD dwUserBaseIdPar = 0,
						int = 0, int = 0, int = 0 );
		int			ACLFind( const char *, long, char *, int, BYTE, BOOL = TRUE );
		int			ACLGroupFind( const char *, const char *, long, char *, int, BYTE );
		int			GenerateOwnerACL();
		int			VerifyPermission( const char *, long, int, BYTE );
		int			GetBaseFieldList();
		BYTE		GetPasswordType();
		int			ResetLockElapsedTime();
		int			BuildRepetitionFile( long, long, C_LB4 * );
		int			RenameFile( C_File *, C_File *, char *, char * );
		int			KillLockTimer();
		int			OpenAllFiles( BOOL bCheckVersion = TRUE );
		BOOL		ClearMaxRepetitionStatus( LBSC_Occurrence &lbscOc );
		int			CloseAllFiles();
		int			Open( const LBSC_Ticket *, char *, char *, char *, LBSC_Session *, BOOL, BOOL, BOOL, BOOL = TRUE );
		int			Close();
		static		int RemoveDir( char *, BOOL );
		int			VerifyRecordStatus( long );
		BOOL		ValidOccurrence( LTC_OCCURRENCE *pOcc, LTC_OCCURRENCELIST *pOccList );

		DWORD		GetBaseId(){ return( LB1.tcrHead.dwBaseId ); };
		DWORD		GetUserBaseId(){ return( LB1.tcrHead.dwUserBaseId ); };
		void		SetBaseId( DWORD dwNewId ){ LB1.tcrHead.dwBaseId = dwNewId; };
		void		SetUserBaseId( DWORD dwNewId ){ LB1.tcrHead.dwUserBaseId = dwNewId; };
		const char	*GetPassword();
		const char  *GetRecordPassword();
		const char	*GetFieldPassword( char * );
		const char	*GetFieldPassword( UINT );
		void		ClearAllFields();
		int			DelFieldOnFile( UINT );
		int			AppendLastFieldOnFile();
		int			GetCurrFieldType();
		UINT		GetCurrFieldId();
		int			GetFieldRepetition( UINT, int, char ** );
		int			CheckUniqueKey();
		void		SetFullAccessMode( BOOL );
		int			ModifyFieldId( char *, UINT );
		BOOL		IsUDBFixedField( char *szField );
		BOOL		IsUDBFixedField( UINT );

		// metodos para tratamento de stop words
		int			SetStopWord();

		// metodos para tratamento de gowords
		void		SetGowords( LTC_TERMLIST * );

		// Metodos para caminhamento diretamente sobre a base
		int			FirstFRecord( const LBSC_Ticket * );
		int			LastFRecord( const LBSC_Ticket * );
		int			NextFRecord( const LBSC_Ticket * );
		int			PreviousFRecord( const LBSC_Ticket * );
		int			NthFRecord( const LBSC_Ticket *, long );
		int			GotoRec( const LBSC_Ticket *, long );
		int			PrivNextRec( const LBSC_Ticket *, BOOL = FALSE, BOOL = FALSE );
		int			PrivPrevRec( const LBSC_Ticket *, BOOL = FALSE, BOOL = FALSE );

		// Metodos para indexacao/desindexacao
		int			Index( const LBSC_Ticket *, int, BOOL = FALSE );
		int			Unindex( const LBSC_Ticket *, int iType );
		int			ChangeIndex( const LBSC_Ticket *, int, BOOL, BOOL = FALSE  );
		int			IndexLT( LBSC_IndexSystem *, int, long, LBSC_Field *, int, LTC_PARSER * );
		int			UnindexLT( LBSC_IndexSystem *, int, long, LBSC_Field *, int, LTC_PARSER * );
		int			UpdateStatus( const LBSC_Ticket *, BOOL );
		int			WriteRecordInLogFile( const LBSC_Ticket * );
		int			SaveIndexStatus( const LBSC_Ticket * );
		int			LoadIndexStatus( const LBSC_Ticket * );
		int			IndexEmptyLT( LBSC_IndexSystem *, long, LBSC_Field *, int);
		int			UnindexEmptyLT( LBSC_IndexSystem *, long, LBSC_Field *, int);
		BOOL		MustIndexLast( UINT, int );
		BOOL		MustUnIndexLast( UINT, int );


		BOOL		CheckFieldType( UINT, TFieldType );
		int			OpenLogFile( C_IDXOFF & );

		// Metodos de importacao/exportacao
		int			ExportLB3( C_File * );
		int			ExportLB1( const LBSC_Ticket *, C_File *, BOOL );
		int			Export( const LBSC_Ticket *, C_File *, BOOL );

		// Metodos para manipulacao de objetos da API Light Text
		char			*MakeLTString( LTC_TERMLIST * );

		// Tratamento de ACL
		int			SetOwnerBase();

		// tratamento de chaves de indices
		int			GetKey( int );
		int			GetRecPosByKey( int, long *, int = 0 );

		// tratamento de LO's
		LBSC_OcList		*GetCurrentOcList();
		int				ChangeOcList( LBSC_OcList * );
		int				GetAclRestrictExpr( char **pszExpr );
		LTC_OCCURRENCELIST	*GetListOfCurrentKey();
		int				LogicalOp( int, int, int );
		LTC_OCCURRENCE *GetOc( LTC_OCCURRENCELIST *, int );
		int				CreateLbsOccList( LBSC_Expr *, LTC_EXPR * );


		// gera um novo id para field cada vez que eh chamado:
		UINT			GetNewFieldId()
		{
			return( ++(LB1.tcrHead.uiLastFieldId) );
		}

		// obtem a versao do arquivo LB1 de uma base
	static	int				GetBaseVersion( char * );


		// metodos para tratamento de lock
		int			MakeLockFileName( char *, BOOL = TRUE );
		BOOL		ExistLockFile( BOOL = TRUE );
		int			WriteOnLockFile( TLockInfo *, BOOL = TRUE );
		int			ReadFromLockFile( TLockInfo *, BOOL = TRUE );

		// tratamento de lock do header de LB1
		int			LockLB1Header();
		int			ReleaseLB1Header();

		// deleta os arquivos do sistema de indices
		int			RemoveIndexSystem();
		// abre os arquivos do sistema de indices
		BOOL		OpenIndexSystem();
		// cria os arquivos do sistema de indices
		BOOL		CreateIndexSystem();

		// metodos para verificacao de consistencia do header de LB1
		int			CheckLB1Header();
		int			GetLB1BakStruct( TControlRecHead * );
		int			PutLB1BakStruct( TControlRecHead * );

		// metodos para recuperacao de base
		int			Recover( const LBSC_Ticket * );

		// metodo para normalizacao
		int			PreStandardize( char *, char * = PRESTANDARDIZEARRAY );

		// metodo para copia um C_File para outro
		int			CopyFile( C_File *, C_File * );

		// operadores (eram publicos, mas vieram para a area privada para
		// (proibir o uso por causa do RPC)
		LBSC_Field		*operator[]( int );
		LBSC_Field		*operator()( UINT );
		LBSC_Field		*operator[]( char * );

		// tratamento de informacoes para copia REDE
		int				DelBaseInfoFile( BaseSTR & );
		int				AddBaseInfoFile( BaseSTR & );

		// copiar bloco de memoria com protecao de tamanho
		BOOL			CopyMem( void **, int *, void *, int, int * );

		// obtem memoria fisica disponivel
		DWORD			GetPhysMemory();

		// retorna o nome do dono da base
		const char		*GetConstOwnerName();

		// realiza um flush de todo o sistema de indices
		int				FlushIndexSystem( BOOL bCheckAvailMem = FALSE );

		// Metodos para tratamento de contadores
		long			PrivIncCount( int, long = 1 );
		long			PrivDecCount( int, long = 1 );

		// metodo para pegar conteúdo de campos URL
		LBSC_Reference	*FillUrlBuffer( LBSC_Reference * );

		// metodos para salvamento/recuperacao de ACLs
		int				ConvertACLFile();
		int				ClearAllAcls();
		int				SaveAllAcls( BYTE );
		int				LoadAllAcls( BYTE );
		int				GenerateComponentAcls();

		// metodos para geracao de log
		int				PrintLogUse( LogType, long, char *szExtra=NULL );
		void			GetUsageLogParams();
		static	void	GetLogFileName( char *szRet );

		// tratamento de slots
		int				FillFieldsFromSlotInfo();

		// leitura de gowords
		void			FillGowords();

		// ordenacao de campos
		int				SortFields();

		// grupos de campos
		int				PutGroupRepetition( LBSC_Field *pfField, int iIndex );
		int				GetNumberOfGroupRepetition( int iGroup );

		// reprocessamento de registros
		int				ReprocRecords( const LBSC_Ticket *pTicket, BYTE bOldMagicNumber, BYTE bNewMagicNumber );

		// manipulacao de slots de campo em UDBs
		void			AddDefaultUDBSlots();
		void			AddDefaultUDBFieldSlots( const char *szField, int iGroup, BOOL bMultiVal, int iLBWType );

		// metodos para conversao de bases de versoes anteriores a 4.*
		int				ReadRecord_V3( C_LB1_V3 &LB1, C_LB4 &LB4 );
		int				GetSlot_V3( int iIndex, void *, C_LB4 &LB4 );
		long			GetSlotSize_V3( int iIndex, C_LB4 &LB4 );
		int				GetFieldSlot_V3( UINT iUid, void *, C_LB4 &LB4 );
		long			GetFieldSlotSize_V3( UINT iUid, C_LB4 &LB4 );
		BOOL			ValidateFieldRep( long, BOOL, LBSC_Field *, C_LB4 &LB4 );


		// metodos para manipulacao dos dados a partir da versao 4.0
		BYTE			*GetRecordBuffer( C_Buffer **pBuf, long *plRecordSize, long *plSuggestedPageSize, BOOL bSendToClientStub = FALSE );
		long			GetBufferSizeFromRepetition(LBSC_Field *pField, int iRep);
		BOOL			FillBufferFromRepetition(C_Buffer &Buf, LBSC_Field *pField, int iRep);
		BOOL			TryCompressRecordBuffer( C_Buffer &Buf, long *plRecordSize );
		int				ReadRecordData();

		// para manipular a cache de bases
		void			InvalidateCache();

	public:
		// Construtores e destrutores
					LBSC_Base( );
					~LBSC_Base();

		// Estado do objeto apos instanciado
		BOOL			BaseObjOk( void );

		// Metodos para manipulacao de FIELDS
		int			AddField( const LBSC_Ticket *, TField * );
		int			AddField( const LBSC_Ticket *, char *, char *, char *,
						 TFieldType, long, TIndexAttrib, UINT );
		int			DelField( char * );
		int			DelField( UINT );
		int			ModifyFieldPassword( char *, char *, char * );
		int			ModifyFieldPassword( UINT, char *, char * );
		int			ModifyFieldName( char *, char *, char * );
		int			ModifyFieldName( UINT, char *, char * );
		int			ModifyFieldDescription( char *, char *, char * );
		int			ModifyFieldDescription( UINT, char *, char * );
		int			ModifyFieldSize( char *, char *, long );
		int			ModifyFieldSize( UINT, char *, long );
		int			ModifyFieldIndexAttrib( char *, char *, int );
		int			ModifyFieldIndexAttrib( UINT, char *, int );
		int			ModifyFieldAttrib( char *szFieldAliasName, char *szPassword, UINT uiFieldAttribPar );
		int			ModifyFieldAttrib( UINT uiFieldId, char *szPassword, UINT uiFieldAttribPar );
		int			GetNumberOfFields();

		int				GetFieldId( const char * );
		TIndexAttrib	GetFieldIndexAttrib( char * );
		TIndexAttrib	GetFieldIndexAttrib( UINT );
		TFieldType		GetFieldType( char * );
		TFieldType		GetFieldType( UINT );
		int				GetFieldRepetition( char *, int, char * );
		int				GetFieldRepetition( UINT, int, char * );
		int				GetFieldRepetition( char *, int, void * );
		int				GetFieldRepetition( UINT, int, void * );
		int				GetFieldRepetition( char *, int, long * );
		int				GetFieldRepetition( UINT, int, long * );
		int				GetFieldRepetition( char *, int, double * );
		int				GetFieldRepetition( UINT, int, double * );
		int				GetFieldRepetition( char *, int, C_Date * );
		int				GetFieldRepetition( UINT, int, C_Date * );
		int				GetFieldRepetition( char *, int, C_Time * );
		int				GetFieldRepetition( UINT, int, C_Time * );
		int				GetFieldRepetition( char *, int, LBSC_Binary * );
		int				GetFieldRepetition( UINT, int, LBSC_Binary * );
		int				GetFieldRepetition( char *, int, LBSC_Reference * );
		int				GetFieldRepetition( UINT, int, LBSC_Reference * );
		int				GetFieldRepetition( char *, int, BYTE * );
		int				GetFieldRepetition( UINT, int, BYTE * );
		int				GetFieldRepetition( char *, int, short int * );
		int				GetFieldRepetition( UINT, int, short int * );
		int				GetFieldRepetition( char *, int, float * );
		int				GetFieldRepetition( UINT, int, float * );
		void			*MGetFieldRepetition( UINT * );

		int			GetFieldRepetitionByVal( char *, char *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, char *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, void *, long, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, void *, long, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, long *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, long *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, double *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, double *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, C_Date *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, C_Date *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, C_Time *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, C_Time *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, LBSC_Binary *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, LBSC_Binary *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, LBSC_Reference *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, LBSC_Reference *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, BYTE *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, BYTE *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, short int *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, short int *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( char *, float *, BOOL bStart = TRUE );
		int			GetFieldRepetitionByVal( UINT, float *, BOOL bStart = TRUE );

		int			PutFieldRepetition( char *, char * );
		int			PutFieldRepetition( UINT, char * );
		int			PutFieldRepetition( char *, void *, long );
		int			PutFieldRepetition( UINT, void *, long );
		int			PutFieldRepetition( char *, long );
		int			PutFieldRepetition( UINT, long );
		int			PutFieldRepetition( char *, double );
		int			PutFieldRepetition( UINT, double );
		int			PutFieldRepetition( char *, C_Date );
		int			PutFieldRepetition( UINT, C_Date );
		int			PutFieldRepetition( char *, C_Time );
		int			PutFieldRepetition( UINT, C_Time );
		int			PutFieldRepetition( char *, LBSC_Binary * );
		int			PutFieldRepetition( UINT, LBSC_Binary * );
		int			PutFieldRepetition( char *, LBSC_Reference * );
		int			PutFieldRepetition( UINT, LBSC_Reference * );
		int			PutFieldRepetition( char *, BYTE );
		int			PutFieldRepetition( UINT, BYTE );
		int			PutFieldRepetition( char *, short int );
		int			PutFieldRepetition( UINT, short int );
		int			PutFieldRepetition( char *, float );
		int			PutFieldRepetition( UINT, float );
		int			MPutFieldRepetition( const LBSC_Ticket *, void * );

		int			PutFieldRepetitionByIndex( char *, char *, int );
		int			PutFieldRepetitionByIndex( UINT, char *, int );
		int			PutFieldRepetitionByIndex( char *, void *, long, int );
		int			PutFieldRepetitionByIndex( UINT, void *, long, int );
		int			PutFieldRepetitionByIndex( char *, long, int );
		int			PutFieldRepetitionByIndex( UINT, long, int );
		int			PutFieldRepetitionByIndex( char *, double, int );
		int			PutFieldRepetitionByIndex( UINT, double, int );
		int			PutFieldRepetitionByIndex( char *, C_Date, int );
		int			PutFieldRepetitionByIndex( UINT, C_Date, int );
		int			PutFieldRepetitionByIndex( char *, C_Time, int );
		int			PutFieldRepetitionByIndex( UINT, C_Time, int );
		int			PutFieldRepetitionByIndex( char *, LBSC_Binary *, int );
		int			PutFieldRepetitionByIndex( UINT, LBSC_Binary *, int );
		int			PutFieldRepetitionByIndex( char *, LBSC_Reference *, int );
		int			PutFieldRepetitionByIndex( UINT, LBSC_Reference *, int );
		int			PutFieldRepetitionByIndex( char *, BYTE, int );
		int			PutFieldRepetitionByIndex( UINT, BYTE, int );
		int			PutFieldRepetitionByIndex( char *, short int, int );
		int			PutFieldRepetitionByIndex( UINT, short int, int );
		int			PutFieldRepetitionByIndex( char *, float, int );
		int			PutFieldRepetitionByIndex( UINT, float, int );

		int			InsertBlankRepetition( UINT, int );

		int			ModifyFieldRepetition( char *, int, char * );
		int			ModifyFieldRepetition( UINT, int, char * );
		int			ModifyFieldRepetition( char *, int, void *, long );
		int			ModifyFieldRepetition( UINT, int, void *, long );
		int			ModifyFieldRepetition( char *, int, long );
		int			ModifyFieldRepetition( UINT, int, long );
		int			ModifyFieldRepetition( char *, int, double );
		int			ModifyFieldRepetition( UINT, int, double );
		int			ModifyFieldRepetition( char *, int, C_Date );
		int			ModifyFieldRepetition( UINT, int, C_Date );
		int			ModifyFieldRepetition( char *, int, C_Time );
		int			ModifyFieldRepetition( UINT, int, C_Time );
		int			ModifyFieldRepetition( char *, int, LBSC_Binary * );
		int			ModifyFieldRepetition( UINT, int, LBSC_Binary * );
		int			ModifyFieldRepetition( char *, int, LBSC_Reference * );
		int			ModifyFieldRepetition( UINT, int, LBSC_Reference * );
		int			ModifyFieldRepetition( char *, int, BYTE );
		int			ModifyFieldRepetition( UINT, int, BYTE );
		int			ModifyFieldRepetition( char *, int, short int );
		int			ModifyFieldRepetition( UINT, int, short int );
		int			ModifyFieldRepetition( char *, int, float );
		int			ModifyFieldRepetition( UINT, int, float );

		int					DelFieldRepetition( char *, int, BOOL = FALSE );
		int					DelFieldRepetition( UINT, int, BOOL = FALSE );
		int					GetNumberOfRepetition( char * );
		int					GetNumberOfRepetition( UINT );
		long				GetFieldRepetitionSize( char *, int );
		long				GetFieldRepetitionSize( UINT, int );
		const LBSC_Field	*GetFieldObj( char * );
		const LBSC_Field	*GetFieldObj( UINT );
		TField				*GetFields( const LBSC_Ticket * );

		// Metodos para tratamento de registros
		long		GetNumActiveRecords( const LBSC_Ticket * );
		long		GetNumRecords( const LBSC_Ticket * );
		long		CurrRecNum( const LBSC_Ticket * );
		long		GetIndexRecNum( const LBSC_Ticket *, BOOL );
		BYTE		CurrRecStatus( const LBSC_Ticket * );
		int			LockRecord( const LBSC_Ticket *, BOOL = FALSE );
		int			ReleaseRecord( const LBSC_Ticket * );
		int			UpdateRecord( const LBSC_Ticket * );
		int			AppendRecord( const LBSC_Ticket * );
		int			ReadRecord( const LBSC_Ticket * );
		int			DeleteRecord( const LBSC_Ticket * );
		int			ClearRecord();
		int			SetLockTimeOut( const LBSC_Ticket *, int );
		int			SetReorganizeRecQuant( const LBSC_Ticket *, long );
		int			EnableFastRecord( BOOL  );

		// Metodos para caminhamento sobre a LO
		int			FirstRecord( const LBSC_Ticket * );
		int			LastRecord( const LBSC_Ticket * );
		int			NextRecord( const LBSC_Ticket * );
		int			PreviousRecord( const LBSC_Ticket * );
		int			NthRecord( const LBSC_Ticket *, long );
		int			CurrentRecord( const LBSC_Ticket * );

		// Metodos para obtencao de uma ocorrencia a partir de
		// caminhamentos sobre a LO
		const LBSC_Occurrence	*GetCurrentOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence	*GetFirstOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence	*GetLastOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence	*GetNextOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence	*GetPreviousOccurrence( const LBSC_Ticket * );
		const LBSC_Occurrence	*GetNthOccurrence( const LBSC_Ticket *, long );

		// tratamento de LO's
		long			GetNumOccurrences( const LBSC_Ticket * );
		long			GetNumOLRecords( const LBSC_Ticket *, int );
		int				*Search( const LBSC_Ticket *, char * );
		int				SaveOcList( const LBSC_Ticket *, int, char * );
		int				LoadOcList( const LBSC_Ticket *, char * );
		int				SortOcList( const LBSC_Ticket *, int, char *, BOOL = FALSE );
		int				EnableOcList( const LBSC_Ticket *, int );
		char			*GetCurrentExpression( const LBSC_Ticket * );
		char			*GetOcListExpression( const LBSC_Ticket *, int );
		long			GetOLRecNumber( const LBSC_Ticket * );
		int				UnloadOcList( const LBSC_Ticket *, int );
		int				DeleteOcList( const LBSC_Ticket *, char * );
		int				DeleteOcRecords( const LBSC_Ticket * );
		int				EnableSecureSort( BOOL );
		BOOL			SecureSortStatus();


		// Metodos para tratamento de StopWords
		int				AddStopWord( const LBSC_Ticket *, char * );
		char			*GetStopWords( const LBSC_Ticket * );
		int				DelStopWord( const LBSC_Ticket *, char * );
		const char		*GetCurrentStopWord( const LBSC_Ticket * );
		const char		*GetFirstStopWord( const LBSC_Ticket * );
		const char		*GetLastStopWord( const LBSC_Ticket * );
		const char		*GetNextStopWord( const LBSC_Ticket * );
		const char		*GetPreviousStopWord( const LBSC_Ticket * );
		const char		*GetNthStopWord( const LBSC_Ticket *, int );
		const char		*SearchStopWord( const LBSC_Ticket *, const char *, int );
		long			GetNumberOfStopWords( const LBSC_Ticket * );

		// Metodos para tratamento de GoWords
		int				AddGoWord( UINT, char * );
		int				DelGoWord( UINT, char * );
		BOOL			GetGowords( char  *, char **);
		BOOL			SetGowords( char  *, const char *);


		// Metodos para tratamento do Minkeysize
		int				GetMinkeysize( );
		int				SetMinkeysize( int );


		// Metodos para tratamento de ACL's
		int				SetACLPerm( char *, long, char *, BYTE, int );
		int				GetACLPerm( char *, long, char *, int, BOOL = TRUE );
		int				DelACLPerm( char *, long, char *, int );
		LBSC_PermList 	*GetACLListPermission( char *, int );

		// Metodos para tratamento de indexacao
		BOOL			GetStopIndex();
		void			SetStopIndex( BOOL );
		int				EnableOnLineIndex( BOOL );
		BOOL			OnLineIndexStatus();
		int				UpdateIndex( const LBSC_Ticket * );
		int				IndexAll( const LBSC_Ticket *, BOOL = FALSE  );
		int				IndexString( const LBSC_Ticket *, long, UINT, int, char * );
		int				UnindexString( const LBSC_Ticket *, long, UINT, int, char * );
		int				GetNumRecIndex();	// numero de registros que sao indexados
								// incrementalmente de cada vez

		// Metodos que precisamos repassar da API LIght Text
		// para a aplicacao LBS
		char			*ExchangeOperator( char * );
		int				SetMask( char *, int, int = 1 /* Valor default da mascara para lingua Portuguess */ );
		char			*GetMask( int );
		int				SaveMasks( char * );
		int				LoadMasks( char * );
		int				ClearMasks();
		int				AddPhone( char *, int );
		int				DeletePhone( char * );
		int				SavePhone( char * );
		int				LoadPhone( char * );
		int				ClearPhone();
		int				FindPhone( char *, char * );
		char			*SetStandardizer( char * );
		char			*GetStandardizer();
		int				Standardize( char *, char *, int );
		int				AddSynonym( char *, char *, int );
		int				DeleteSynonym( char *, char *, int );
		int				SaveSynonym( char * );
		int				LoadSynonym( char * );
		int				ClearSynonym();
		char			*FindSynonym( char * );
		int				OLAnd( const LBSC_Ticket *, int, int );
		int				OLOr( const LBSC_Ticket *, int, int );
		int				OLXor( const LBSC_Ticket *, int, int );
		int				OLNot( const LBSC_Ticket *, int, int );

		// Setar navegacao por um indice
		int				SetNavigationByIndex( const LBSC_Ticket *, BOOL, UINT uiFieldId = 0, int iIndex = 0, int iType = EQUAL_KEY );

		// Setar navegacao por uma chave
		int				SetNavigationByKey( const LBSC_Ticket *, BOOL, UINT uiFieldId = 0, int iIndex = 0, char *szNavKey = NULL, int iType = EQUAL_KEY );

		// posicionar-se sobre o primeiro registro de uma chave
		int				Locate( const LBSC_Ticket *, UINT, int, char *, int iType = EQUAL_KEY );

		// Metodos para tratamento de SLOTs
		int				GetNumberOfSlots();
		int				GetSlot( int, void * );
		long			GetSlotSize( int );
		int				PutSlot( int, void *, int );
		int				GetFieldSlot( UINT, void * );
		long			GetFieldSlotSize( UINT );
		int				PutFieldSlot( UINT, void *, int );

		// Metodos para tratamento de contadores
		int				GetNumberOfCounters();
		long			GetCount( int );
		int				PutCount( int, long );
		int				IncCount( int, long = 1 );
		int				DecCount( int, long = 1 );
		long			GetNextCount( int );
		long			GetPreviousCount( int );
		int				LockCount( int, BOOL = FALSE );
		int				ReleaseCount( int );


		// Metodos para tratamento de cache em copia c/s
		TACL_Lists		*GetAllACLLists( const LBSC_Ticket * );
		C_Buffer		*GetAllRepetitions( const LBSC_Ticket *, int = 1 );
		TSlotCache		*GetAllFieldSlots( const LBSC_Ticket * );
		void			EnableMultipleRecords( int iNumRegs );
		void			DisableMultipleRecords();

		// Metodos de uso geral
		int				Compare( LBSC_Base *, int );
		LBSC_Base		*Duplicate( void );
		int				ModifyBaseOwnerName( const LBSC_Ticket *, char *, char * );
		int				ModifyPassword( const LBSC_Ticket *, char *, char * );
		int				ModifyMaintenancePassword( const LBSC_Ticket *, char *, char * );
		int				ModifyRecordPassword( const LBSC_Ticket *, char *, char * );
		int				BlockReExport( const LBSC_Ticket * );
		BOOL			IsExportable();
		char			*GetUserBase();
		char			*GetOwnerName();
		int				GetFullBaseName( char * );
		int				GetBaseName( char * );
		int				GetBaseLongName( char * );
		BOOL			IsEncrypt();
		BOOL			IsFullAccess();
		BYTE			GetBaseType();
		int				ModifyBaseType( BYTE );
		int				ModifyBaseName( char *szNewBaseName );
		BOOL			IndexSystemOk();
		BOOL			IsExclusive();
		BOOL			IsReadOnly();
		BOOL			Flush( const LBSC_Ticket * );
		int				ModifyMaxKeySize( const LBSC_Ticket *, int );
		TBaseInfo		*GetBaseInfo( const LBSC_Ticket * );
		int				ClearBase( const LBSC_Ticket * );
		LBSC_Session	*GetOwnerSession();
		int				GetBaseTimeInfo( struct stat * );
		// obtem o nome do dir_base para as bases do LBS
		static	void			GetDirBase( char *szBuffer, const char *szUDB = NULL, const char *szServer = NULL );


		// metodos para feedback
		void						CancelOperation();
		void						GetOpInfo( char *, float * );

		// metodo para obter a versao da base
		int				GetBaseVersion();
		// metodo para obter a versao da UDB
		int				GetUDBVersion();

		// metodo para saber qual o campo que eh ordenado dentro de um grupo
		int				GetGroupSortField( int iGroupPar );



#ifdef __TEST
		// metodos para tratamento de contexto
		// (para teste de unidade)
		void			MakePointerContext( void **, int = 0 );
		void			ChangePointerContext( void ** );
#endif


};

class	C_BaseCritSect
{
	int			iLastSectUsed;
	LBSC_Base	*pObj;

public:
	C_BaseCritSect( LBSC_Base *pObjPar, int iNumCritSect, char *szFile, int iLinePar )
	{
		if( _pcGlobalBaseCritSect ){
			_pcGlobalBaseCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar, szFile, iLinePar  );
			iLastSectUsed = iNumCritSect;
			pObj = pObjPar;
		}
	}


	~C_BaseCritSect()
	{
		if( _pcGlobalBaseCritSect ){
			_pcGlobalBaseCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}

	void EnterCriticalSection()
	{
		if( _pcGlobalBaseCritSect ){
			_pcGlobalBaseCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
		}
	}


	void LeaveCriticalSection()
	{
		if( _pcGlobalBaseCritSect ){
			_pcGlobalBaseCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _BASECL_H_


