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

#ifndef _LBSNETCL_H_
#define _LBSNETCL_H_

#ifdef __NOMFC	// nao usa MFC
#include <windows.h>
#else // __NOMFC

	#ifdef __MFC	// usa MFC
		#include <afxwin.h>
	#else // __MFC
		#error "FUDEU NO INCLUDE DE WINDOWS.H"
	#endif // __MFC

#endif // __NOMFC

#ifndef __lbsrpc_h__
	#include <lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _RPCSERIAL_H_
	#include	<rpcserial.h>
#endif

#ifndef _LBSTEMPLATE_H_
	#include <lbstempl.h>
#endif	// _LBSTEMPLATE_H_


typedef handle_t RPC_HANDLE;

#ifndef	_LBSTYPES_H_
	#include <lbstypes.h>
#endif	// _LBSTYPES_H_
    
// ids das regioes criticas no stub cliente
#define SECTIONID_0		0		// controle do handle RPC
#define SECTIONID_1		1		// controle da lista de servidores

typedef	int (CALLBACK *LBSERRPROC)();

// prototipo da funcao que seta a callback de erro
void SetErrorFunc( LBSERRPROC );

class ServerInfo
{
    friend class LBSC_ClntNet;

    char *szServer;					// servidor
    RPC_HANDLE RpcHandle;			// handle pro servidor
    RPC_HANDLE RpcHandleChkVers;	// handle pro servidor pra checar versao
	int iOpenSessions;

    public:
    	ServerInfo( char *, RPC_HANDLE NewHandle = NULL, RPC_HANDLE NewHandleChqVers = NULL  );
    	~ServerInfo( void );
    	int Compare( ServerInfo *, int );
    	ServerInfo *Duplicate( void );
    	operator const char * (void ) { return szServer; }
};

class C_SInfoList : public LBSC_DList<ServerInfo> 
{
};

    				   
class LBSC_ClntNet {

	   	static boolean GetHandle( char *, long *, int );
		static boolean MakeBinding( const char *szUUID, const char *szProtocolSequence, 
								const char *szServer, const char *szEndPoint, RPC_HANDLE *handle );
		static boolean MustReinstal();
		static void GetServerPort( char *, long * );
		static void SetServerPort( char *, long );

    protected:
		long	obj;
		char	ServerAddr[ SERVERNAMESIZE ];

		static	char *szAppName;
		static	char *szClientName;
		static	long lClntTimeStamp;
		static	char *szReinstallPath; 

    	long	lSvcTimeStamp;
    
		static int OpenSessions( char * );
		static void IncOpenSessions( char * );
		static void DecOpenSessions( char * );
    public:
    	LBSC_ClntNet();
    	~LBSC_ClntNet();
    	static void SetClientInfo();
    	static boolean EnviaNovaRPC();
    	static boolean GetRPCHandle( char * );
    	static void FreeRPCHandle();
    	static int QualNetError( char * );
    	static const char *GetNetErrorDesc();
    	static void TrataErroRPC( char *, unsigned long );
		TSRClntInitInfo ObtemInitInfo();
		static void LiberaServList();
		static	const char *ObtemClientIniName();
    	void SetTimeStamp( long );
		static void SetHandleValue( ServerInfo * );
		boolean RPCWouldBlock();
		static void CleanUp();
    
    #ifdef RPC_SOCK
    
 	static boolean EnviaMetodo( int );
 	boolean EnviaArgs( unsigned char *, long );
 	boolean RecebeArgs( unsigned char ** );

	 	static TSRGenericObj 
    	RPC_Session_New( TSRControlInfo );
    
  		static void 
    	RPC_Session_Delete( /* in */ TSRGenericObj DeadSession );
    
    	long 
    	RPC_Session_DeleteUDB( /* in */ TSRIn_DeleteUDB InPar);
    
  		static long 
    	RPC_Session_DeleteDefaultUserBase( /* in */ TSRIn_DeleteUDB InPar);
    
    	TSRTicket 
    	RPC_Session_Login( /* in */ TSRIn_Login InPar );
    
    	long 
    	RPC_Session_Logout( /* in */ TSRGenericObj Session );
    
    	long 
    	RPC_Session_CloseBase( /* in */ TSRIn_CreateCloseDelete InPar );
    
    	long 
    	RPC_Session_CreateBaseDef( /* in */  TSRIn_CreateCloseDelete InPar );
    
    	long 
    	RPC_Session_CreateBase( /* in */ TSRIn_CreateCloseDelete InPar);
    
    	long 
    	RPC_Session_DeleteBase( /* in */ TSRIn_CreateCloseDelete InPar);
    
    	long 
    	RPC_Session_CreateUDB( /* in */ TSRIn_CreateCloseDelete InPar);
    
    	long 
    	RPC_Session_AddUser( /* in */ TSRIn_AddDelGroupUser InPar );
    
    	TSROut_OpenBase 
    	RPC_Session_OpenBase( /* in */ TSRIn_OpenBase InPar );
    
    	long 
    	RPC_Session_AddGroupToUser( /* in */ TSRIn_AddDelGroupUser InPar );
    
    	boolean 
    	RPC_Session_IsLogged( /* in */ TSRGenericObj Session );
    
	  	static unsigned char *
    	RPC_Session_WhatServers( void );
    
  		static unsigned char *
    	RPC_Session_WhatServersForUser( /* in */ TSRIn_What InPar );
    
    	unsigned char *
    	RPC_Session_WhatUDBLogged( /* in */ TSRGenericObj Session );
    
    	unsigned char *
    	RPC_Session_WhatUDB( /* in */ TSRIn_What InPar );
    
    	unsigned char *
    	RPC_Session_GetUserName( /* in */ TSRGenericObj Session );
    
    	long 
    	RPC_Session_ReorganizeBase( /* in */ TSRIn_ReorgBase InPar );
    
    	long 
    	RPC_Session_TicketIsOk( /* in */ TSRIn_GetGroups InPar );
    
    	unsigned char *
    	RPC_Session_GetGroups( /* in */ TSRIn_GetGroups InPar );
    
    	long 
  		RPC_Session_DelUser ( /* in */ TSRIn_AddDelGroupUser InPar );
    
    	long 
    	RPC_Session_UpdateUserPassword ( /* in */ TSRIn_UserGenInfos InPar );
    
    	long 
    	RPC_Session_UpdateUserDescription( /* in */ TSRIn_UserGenInfos InPar );
    
    	long 
    	RPC_Session_UpdateUserType( /* in */ TSRIn_UserGenInfos InPar );
    
    	long 
    	RPC_Session_GetUserType( /* in */ TSRIn_UserGenInfos InPar );
    
    	unsigned char *
    	RPC_Session_GetUserDescription( /* in */ TSRIn_UserGenInfos InPar );
    
    	long 
    	RPC_Session_DelGroupFromUser( /* in */ TSRIn_AddDelGroupUser InPar ); 
    
    	unsigned char *
    	RPC_Session_GetUsers( /* in */ TSRIn_GetGroups InPar );
    
    	TSROut_GetUsersData 
    	RPC_Session_GetUsersData( /* in */  TSRIn_UserGenInfos InPar );
    
  		static TSROut_WhatBases
    	RPC_Session_WhatBases( /* in */ TSRIn_What InPar );
    
  		static TSROut_WhatBases
    	RPC_Session_WhatBasesForUser( /* in */ TSRIn_What InPar );
    
  		static TSROut_WhatBases
  		RPC_Session_WhatBasesOnServer( /* in */ TSRIn_What InPar );
    
    	TSROut_WhatBases
    	RPC_Session_WhatBasesForUserOnServer( /* in */ TSRIn_What InPar );
    
    	long
    	RPC_Session_Export( /* in */ TSRIn_Export InPar );
    
    	long
    	RPC_Session_ExportBaseFormat( /* in */ TSRIn_Export InPar );
    
    	long
    	RPC_Session_Import( /* in */ TSRIn_Import InPar );
    
    	long
    	RPC_Session_UpdateUserAddress( /* in */ TSRIn_UpdateUserAddress InPar );
    
    	long
    	RPC_Session_UpdateUserPhone( /* in */ TSRIn_UpdateUserAddress InPar );
    
    	unsigned char *
    	RPC_Session_GetUserAddress( /* in */ TSRIn_UpdateUserAddress InPar );
    
    	unsigned char *
    	RPC_Session_GetUserPhone( /* in */ TSRIn_UpdateUserAddress InPar );
    
  		static long
    	RPC_Session_CreateDefaultUserBase( /* in */ TSRIn_CreateDefaultUserBase InPar );
    
  		static long
    	RPC_Session_RebuildControl( void );
    
    	long 
    	RPC_Session_IncorporateBase( /* in */ TSRIn_IncorporateBase InPar );
    
    	long 
    	RPC_Session_ClearBase( /* in */ TSRIn_IncorporateBase InPar );
    
    	long 
    	RPC_Session_RenameBase( /* in */ TSRIn_RenameBase InPar );
    
    	long 
    	RPC_Session_ReorganizeUDB( /* in */ TSRIn_IncorporateBase InPar );
    
    	long 
    	RPC_Session_ReorganizeDefaultUserBase( /* in */ TSRIn_TicketPar InPar );
    
    	long 
    	RPC_Session_LeaveBase( /* in */ TSRIn_CreateCloseDelete InPar );
    
    	static unsigned char *
    	RPC_Session_GetDefUserBaseName ( void );
    
  		long 
    	RPC_Session_KillSessions( /* in */ TSRIn_KillSessions InPar );
    
  		long 
    	RPC_Session_KillServer( /* in */ TSRIn_TicketPar InPar );
    
    	/********************/
    	/* Funcoes de Error */
    	/********************/
    
    	long 
    	RPC_Error_SetLastError( /* in */ TSRSetError sIn );
    
    	long
    	RPC_Error_LastError( /* in */ TSRGenericObj lObj );
    
    	unsigned char *
    	RPC_Error_LastErrorDesc( /* in */ TSRGenericObj lObj );
    
    
    	/*******************/
    	/* Funcoes de Base */
    	/*******************/
    
    	TSROut_GetFieldRepetition
    	RPC_Base_GetFieldRepetition( /* in */ TSRIn_GetFieldRepetition sIn );
    
    	long
    	RPC_Base_GetFieldRepetitionByVal( /* in */ TSRIn_GetFieldRepetitionByVal sIn );
    
    	long
    	RPC_Base_PutFieldRepetition( /* in */ TSRIn_PutFieldRepetition sIn );
    
    	long
    	RPC_Base_PutFieldRepetitionByIndex( /* in */ TSRIn_PutFieldRepetition sIn );
    
    	long
    	RPC_Base_ModifyFieldRepetition( /* in */ TSRIn_ModifyFieldRepetition sIn );
    
    	TSROut_GetFieldObj
    	RPC_Base_GetFieldObj( /* in */ TSRIn_DelFieldGetFieldObj sIn );
    
    	boolean
    	RPC_Base_BaseObjOk( /* in */ TSRGenericObj	Base );
    
    	long
    	RPC_Base_AddField( /* in */ TSRIn_AddField InPar );
    
    	long
    	RPC_Base_DelField( /* in */ TSRIn_DelFieldRepetition InPar );
    
    	long
    	RPC_Base_ModifyFieldPassword( /* in */ TSRIn_ModifyFieldPassword InPar );
    
    	long
    	RPC_Base_ModifyFieldName( /* in */ TSRIn_ModifyFieldName InPar );
    
    	long
    	RPC_Base_ModifyFieldDescription( /* in */ TSRIn_ModifyFieldDescription InPar );
    
    	long
    	RPC_Base_ModifyFieldSize( /* in */ TSRIn_ModifyFieldSize InPar );
    
    	long
    	RPC_Base_GetNumberOfFields( /* in */ TSRGenericObj Base );
    
    	long
    	RPC_Base_DelFieldRepetition( /* in */ TSRIn_DelFieldRepetition InPar );
    
    	long
    	RPC_Base_GetNumberOfRepetition( /* in */ TSRIn_GetNumberOfRepetition InPar );
    
    	long
    	RPC_Base_GetFieldRepetitionSize( /* in */ TSRIn_GetFieldRepetitionSize InPar );
    
    	long
    	RPC_Base_GetNumRecords( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_CurrRecNum( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_GetIndexRecNum( /* in */ TSRIn_TicketBOOLPar InPar );
    
    	byte
    	RPC_Base_CurrRecStatus( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_LockRecord( /* in */ TSRIn_TicketBOOLPar InPar );
    
    	long
    	RPC_Base_ReleaseRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_UpdateRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_AppendRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_ReadRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_DeleteRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_ClearRecord( /* in */ TSRGenericObj Base );
    
    	long
    	RPC_Base_SetLockTimeOut( /* in */ TSRIn_SetLockTimeOut InPar );
    
    	long
    	RPC_Base_SetReorganizeRecQuant( /* in */ TSRIn_SetReorganizeRecQuant InPar );
    
    	long
    	RPC_Base_FirstRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_LastRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_NextRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_PreviousRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_NthRecord( /* in */ TSRIn_Nth InPar );
    
    	long
    	RPC_Base_CurrentRecord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_GetNumOccurrences( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_SaveOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_SortOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_EnableSecureSort( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_SecureSortStatus( /* in */ TSRGenericObj Base );
    
    	long
    	RPC_Base_LoadOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_EnableOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_GetOLRecNumber( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_UnloadOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_DeleteOcList( /* in */ TSRIn_OcList InPar );
    
    	long
    	RPC_Base_DeleteOcRecords( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_SetNavigationByIndex( /* in */ TSRIn_SetNavigationLocate InPar );
    
    	long
    	RPC_Base_SetNavigationByKey( /* in */ TSRIn_SetNavigationLocate InPar );
    
    	long
    	RPC_Base_Locate( /* in */ TSRIn_SetNavigationLocate  InPar );
    
    	long
    	RPC_Base_GetNumberOfSlots( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_GetSlotSize( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_GetFieldSlotSize( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_AddGoWord( /* in */ TSRIn_GoWord InPar );
    
    	long
    	RPC_Base_DelGoWord( /* in */ TSRIn_GoWord InPar );
    
    	long
    	RPC_Base_ModifyFieldIndexAttrib( /* in */ TSRIn_ModifyFieldIndexAttrib InPar );

		long
		RPC_Base_ModifyFieldAttrib( /* in */ TSRIn_ModifyFieldAttrib InPar );
    
    	TSROut_GetFields
    	RPC_Base_GetFields( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetCurrentOccurrence( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetFirstOccurrence( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetLastOccurrence( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetNextOccurrence( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetPreviousOccurrence( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_LBSC_Occurrence
    	RPC_Base_GetNthOccurrence( /* in */ TSRIn_Nth InPar );
    
    	TSROut_Search
    	RPC_Base_Search( /* in */ TSRIn_Search InPar );
    
    	unsigned char *
    	RPC_Base_GetCurrentExpression( /* in */ TSRIn_TicketPar InPar );
    
    	unsigned char *
    	RPC_Base_GetOcListExpression( /* in */ TSRIn_OcList InPar );
    
    	unsigned char *
    	RPC_Base_GetCurrentStopWord( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_DelStopWord( /* in */ TSRIn_AddStopWord InPar );
    
    	unsigned char *
    	RPC_Base_GetFirstStopWord( /* in */ TSRIn_TicketPar InPar );
    
    	unsigned char *
    	RPC_Base_GetLastStopWord( /* in */ TSRIn_TicketPar InPar );
    
    	unsigned char *
    	RPC_Base_GetNextStopWord( /* in */ TSRIn_TicketPar InPar );
    
    	unsigned char *
    	RPC_Base_GetPreviousStopWord( /* in */ TSRIn_TicketPar InPar );
    
    	unsigned char *
    	RPC_Base_GetNthStopWord( /* in */ TSRIn_Nth InPar );
    
    	unsigned char *
    	RPC_Base_SearchStopWord( /* in */ TSRIn_SearchStopWord InPar );
    
    	long
    	RPC_Base_SetACLPerm( /* in */ TSRIn_ACLPerm InPar );
    
    	long
    	RPC_Base_GetACLPerm( /* in */ TSRIn_ACLPerm InPar );
    
    	long
    	RPC_Base_DelACLPerm( /* in */ TSRIn_ACLPerm InPar );
    
    	long
    	RPC_Base_EnableOnLineIndex( /* in */ TSRIn_EnableOnLineIndex InPar );
    
    	long
    	RPC_Base_OnLineIndexStatus( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_UpdateIndex( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_IndexAll( /* in */ TSRIn_IndexAll InPar );
    
    	TSROut_GetSlot
    	RPC_Base_GetSlot( /* in */ TSRIn_GetSlotPutSlot InPar );
    
    	long
    	RPC_Base_PutSlot( /* in */ TSRIn_GetSlotPutSlot InPar );
    
    	TSROut_GetSlot
    	RPC_Base_GetFieldSlot( /* in */ TSRIn_GetSlotPutSlot InPar );
    
    	long
    	RPC_Base_PutFieldSlot( /* in */ TSRIn_GetSlotPutSlot InPar );
    
    	long
    	RPC_Base_GetNumberOfCounters( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_GetCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_PutCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_IncCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_DecCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_LockCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_ReleaseCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_GetNextCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_GetPreviousCount( /* in */ TSRIn_GetSlotSize InPar );
    
    	long
    	RPC_Base_ModifyPassword( /* in */ TSRIn_ModifyPassword InPar );
    
    	long
    	RPC_Base_ModifyMaintenancePassword( /* in */ TSRIn_ModifyPassword InPar );
    
    	unsigned char *
    	RPC_Base_GetUserBase( /* in */ TSRGenericObj lBaseObj );
    
    	unsigned char *
    	RPC_Base_GetOwnerName( /* in */ TSRGenericObj lBaseObj );
    
    	TSROut_GetFullBaseName
    	RPC_Base_GetFullBaseName( /* in */ TSRGenericObj InPar );
    
    	TSROut_GetFullBaseName
    	RPC_Base_GetBaseName( /* in */ TSRGenericObj InPar );
    
    	boolean
    	RPC_Base_IsEncrypt( /* in */ TSRGenericObj lBaseObj );
    
    	boolean
    	RPC_Base_IsFullAccess( /* in */ TSRGenericObj lBaseObj );
    
    	byte
    	RPC_Base_GetBaseType( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_GetBaseVersion( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_ModifyBaseType( /* in */ TSRIn_ModifyBaseType InPar );
    
    	long
    	RPC_Base_IndexString( /* in */ TSRIn_IndexString InPar );
    
    	long
    	RPC_Base_UnindexString( /* in */ TSRIn_IndexString InPar );
    
    	boolean
    	RPC_Base_IndexSystemOk( /* in */ TSRGenericObj lBaseObj );
    
    	long
    	RPC_Base_GetNumberOfStopWords( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_AddStopWord( /* in */ TSRIn_AddStopWord InPar );
    
    	long
    	RPC_Base_ModifyBaseOwnerName( /* in */ TSRIn_ModifyBaseOwnerName InPar );
    
    	short
    	RPC_Base_GetFieldType( /* in */ TSRIn_GetFieldTypeId InPar );
    
    	long
    	RPC_Base_GetFieldId( /* in */ TSRIn_GetFieldTypeId InPar );
    
    	long
    	RPC_Base_GetFieldIndexAttrib( /* in */ TSRIn_GetFieldIndexAttrib InPar );
    
    	TSROut_WhatBases
    	RPC_Base_GetACLListPermission( /* in */ TSRIn_GetACLListPerm InPar );
    
    	unsigned char *
    	RPC_Base_ExchangeOperator( /* in */ TSRIn_ExchangeOperator InPar );
    
    	long
    	RPC_Base_SetMask( /* in */ TSRIn_Mask InPar );
    
    	unsigned char *
    	RPC_Base_GetMask( /* in */ TSRIn_Mask InPar );
    
    	long
    	RPC_Base_SaveMasks( /* in */ TSRIn_Mask InPar );
    
    	long
    	RPC_Base_LoadMasks( /* in */ TSRIn_Mask InPar );
    
    	long
    	RPC_Base_ClearMasks( /* in */ TSRGenericObj BaseObj );
    
    	long
    	RPC_Base_AddPhone( /* in */ TSRIn_Phone InPar );
    
    	long
    	RPC_Base_DeletePhone( /* in */ TSRIn_Phone InPar );
    
    	long
    	RPC_Base_SavePhone( /* in */ TSRIn_Phone InPar );
    
    	long
    	RPC_Base_LoadPhone( /* in */ TSRIn_Phone InPar );
    
    	long
    	RPC_Base_ClearPhone( /* in */ TSRGenericObj BaseObj );
    
    	long
    	RPC_Base_FindPhone( /* in */ TSRIn_Phone InPar );
    
    	unsigned char*
    	RPC_Base_SetStandardizer( /* in */ TSRIn_Standardize	InPar);
    
    	long
    	RPC_Base_Standardize( /* in */ TSRIn_Standardize InPar);
    
    	long
    	RPC_Base_AddSynonym( /* in */ TSRIn_Synonym InPar);
    
    	long
    	RPC_Base_DeleteSynonym( /* in */ TSRIn_Synonym InPar);
    
    	long
    	RPC_Base_SaveSynonym( /* in */ TSRIn_Synonym InPar);
    
    	long
    	RPC_Base_LoadSynonym( /* in */ TSRIn_Synonym InPar);
    
    	long
    	RPC_Base_ClearSynonym( /* in */ TSRGenericObj BaseObj );
    
    	unsigned char *
    	RPC_Base_FindSynonym( /* in */ TSRIn_Synonym InPar);
    
    	long
    	RPC_Base_OLAnd( /* in */ TSRIn_OL	InPar );
    
    	long
    	RPC_Base_OLOr( /* in */ TSRIn_OL	InPar );
    
    	long
    	RPC_Base_OLXor( /* in */ TSRIn_OL	InPar );
    
    	long
    	RPC_Base_OLNot( /* in */ TSRIn_OL	InPar );
    
    	boolean
    	RPC_Base_IsExportable( /* in */ TSRGenericObj BaseObj );
    
    	long
    	RPC_Base_BlockReExport( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_ModifyRecordPassword( /* in */ TSRIn_ModifyPassword InPar );
    
    	boolean
    	RPC_Base_IsReadOnly( /* in */ TSRGenericObj lBaseObj );
    
    	boolean
    	RPC_Base_IsExclusive( /* in */ TSRGenericObj lBaseObj );
    
    	boolean
    	RPC_Base_Flush( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_GetNumActiveRecords( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_ModifyMaxKeySize( /* in */ TSRIn_CreateCloseDelete InPar );
    
    	TSROut_BaseInfo
    	RPC_Base_GetBaseInfo( /* in */ TSRIn_TicketPar InPar );
    
    	long
    	RPC_Base_GetNumOLRecords( /* in */ TSRIn_OL	InPar );
    
    	long
    	RPC_Base_GetNumRecIndex( /* in */ TSRGenericObj lBaseObj );
    
    	boolean
    	RPC_Base_GetStopIndex( /* in */ TSRGenericObj BaseObj );
    
    	void
    	RPC_Base_SetStopIndex( /* in */ TSRIn_TicketBOOLPar InPar );
    
    	long 
    	RPC_Base_ClearBase( /* in */ TSRIn_TicketPar InPar );
    
    	TSROut_MGetFieldRep
    	RPC_Base_MGetFieldRepetition( /* in */ TSRIn_MGetPutFieldRep InPar );
    
    	long
    	RPC_Base_MPutFieldRepetition( /* in */ TSRIn_MGetPutFieldRep InPar );
    
    	/********************/
    	/* Funcoes de Field */
    	/********************/
    
    	unsigned char *
    	RPC_Field_GetFirstGoWord( /* in */ TSRGenericObj FieldObj );
    
    	unsigned char *
    	RPC_Field_GetNextGoWord( /* in */ TSRGenericObj FieldObj );
    
    	unsigned char *
    	RPC_Field_GetCurrentGoWord( /* in */ TSRGenericObj FieldObj );
    
    	unsigned char *
    	RPC_Field_GetNthGoWord( /* in */ TSRIn_GoWord InPar );
    
    	unsigned char *
    	RPC_Field_SearchGoWord( /* in */ TSRIn_GoWord InPar );
    
    	long
    	RPC_Field_GetNbrOfGoWord( /* in */ TSRGenericObj FieldObj );
    
    	unsigned char *
    	RPC_Field_GetAliasName( /* in */ TSRGenericObj lFieldObj );
    
    	long
    	RPC_Field_Clear( /* in */ TSRGenericObj FieldObj );
    
    	long
    	RPC_Field_GetId( /* in */ TSRGenericObj FieldObj );
    
    	long
    	RPC_Field_GetSize( /* in */ TSRGenericObj FieldObj );
    
    	long
    	RPC_Field_VerifyPassword( /* in */ TSRIn_VerifyPassword	InPar );
    

		
		/*******************/
    	/* Funcoes de Data */
    	/*******************/
    
    	TSROut_GetData
    	RPC_Data_GetData( /* in */ TSRGenericObj DataObj );
    
    	long
    	RPC_Data_GetSize( /* in */ TSRGenericObj	lDataObj );
    
    
		/***********
		INICIALIZANDO UM CONTEXTO NO SERVIDOR
		***********/
		static boolean
		RPC_SvcInitContext( /* in */ TSRClntInitInfo sInitInfo );

		/***********
		LIBERANDO UM CONTEXTO NO SERVIDOR
		***********/
		static boolean
		RPC_SvcEndContext( /* in */ TSRClntInitInfo sInitInfo );

		long
		RPC_Session_SetServerParam( TSRIn_SetSvcParam InPar );

		static TSROut_GetSvcParam
		RPC_Session_GetServerParam( TSRGenericObj InPar );

		TSROut_GetUsersInfo
		RPC_Session_GetUsersInfo( TSRIn_TicketPar InPar );

		long
		RPC_Session_UnLockRecord( TSRIn_TicketPar InPar );

		void
		RPC_OpInfo_CancelOperation( TSRGenericObj InPar );

		TSROut_GetOpInfo
		RPC_OpInfo_GetOpInfo( TSRGenericObj InPar );

		unsigned char *
		RPC_Base_GetStopWords( TSRIn_TicketPar InPar );

		long
		RPC_Base_ModifyBaseName( TSRIn_ModifyBaseName InPar );

		static unsigned char *
		RPC_Session_GetBaseLongName( TSRIn_GetBaseLongName InPar );

		TSROut_GetBaseLongName
		RPC_Base_GetBaseLongName( TSRGenericObj InPar );

		static void
		RPC_SvcIsUp( void );

		void
		RPC_Session_CancelOperation( TSRGenericObj InPar );

		TSROut_GetOpInfo
		RPC_Session_GetOpInfo( TSRGenericObj InPar );

		void
		RPC_Base_CancelOperation( TSRGenericObj InPar );

		TSROut_GetOpInfo
		RPC_Base_GetOpInfo( TSRGenericObj InPar );

		TSROut_GenericBuffer
		RPC_Base_GetAllFieldSlots( TSRIn_TicketPar InPar );

		TSROut_ACLLists
		RPC_Base_GetAllACLLists( TSRIn_TicketPar InPar );

		TSROut_GenericBuffer
		RPC_Base_GetAllRepetitions( TSRIn_AllRepetitions InPar );

		TSROut_GenericBuffer
		RPC_Base_GetAllOccurrences( TSRIn_TicketPar InPar );

    	long
    	RPC_Base_EnableFastRecord( /* in */ TSRIn_EnableOnLineIndex InPar );
    
		TSROut_GenericBuffer
		RPC_Base_GetBaseTimeInfo( /*[ in ]*/ TSRGenericObj InPar );

    #endif
    }; 
    
    
#endif
