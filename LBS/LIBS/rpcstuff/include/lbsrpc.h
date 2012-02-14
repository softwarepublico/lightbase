/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 22 12:07:58 2005
 */
/* Compiler settings for lbsrpc.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __lbsrpc_h__
#define __lbsrpc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __lbsrpc_INTERFACE_DEFINED__
#define __lbsrpc_INTERFACE_DEFINED__

/* interface lbsrpc */
/* [enable_allocate][implicit_handle][unique][version][uuid] */ 

#define	USERNAMESIZE	( 32 )

#define	DESCRIPTIONSIZE	( 64 )

#define	PASSWORDSIZE	( 10 )

#define	FULLNAMESIZE	( 260 )

#define	GROUPNAMESIZE	( 15 )

#define	SERVERNAMESIZE	( 50 )

#define	SERIALNUMBERSIZE	( 50 )

#define	FIELDNAMESIZE	( 32 )

#define	ADDRESSSIZE	( 100 )

#define	PHONESIZE	( 20 )

#define	WHATS	( 100 )

#define	WHATSFORUSER	( 200 )

#define	WHATB	( 300 )

#define	WHATBFORUSER	( 400 )

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0001
    {
    unsigned char szAppName[ 260 ];
    unsigned char szClientName[ 260 ];
    long lClntTimeStamp;
    }	TSRClntInitInfo;

typedef /*  */ struct  __MIDL_lbsrpc_0002
    {
    unsigned char szClientName[ 260 ];
    long lClntTimeStamp;
    long lSvcTimeStamp;
    long lObj;
    }	TSRControlInfo;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0003
    {
    /* [string] */ unsigned char __RPC_FAR *szActionPar;
    float fPercentPar;
    }	TSROut_GetOpInfo;

typedef /* [public] */ struct  __MIDL_lbsrpc_0004
    {
    unsigned char szUserName[ 33 ];
    unsigned char szUserPassword[ 11 ];
    long lUserType;
    unsigned char szUserDescription[ 65 ];
    unsigned char szUserAddress[ 101 ];
    unsigned char szUserPhone[ 21 ];
    unsigned char szUserGroup[ 16 ];
    }	TSRUDBRecord;

typedef /* [public][public][public][public][public] */ struct  __MIDL_lbsrpc_0005
    {
    unsigned char szFieldAliasName[ 33 ];
    unsigned char szFieldDescription[ 65 ];
    unsigned char szPasswordName[ 11 ];
    unsigned char lFieldType;
    long lFieldSize;
    long lFieldId;
    long lIndexAttrib;
    long lFieldAttrib;
    }	TSRField;

typedef /*  */ struct  __MIDL_lbsrpc_0006
    {
    long lTickLen;
    /* [size_is] */ unsigned char __RPC_FAR *szTickBuff;
    }	TSRTicket;

typedef /*  */ struct  __MIDL_lbsrpc_0007
    {
    long lObj;
    TSRControlInfo sCtrlInfo;
    }	TSRGenericObj;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0008
    {
    unsigned char strUserName[ 33 ];
    unsigned char strPasswd[ 11 ];
    unsigned char strUDBName[ 261 ];
    unsigned char strServer[ 51 ];
    unsigned char strClient[ 51 ];
    unsigned char strClientSN[ 51 ];
    long lClientLicense;
    long lisMono;
    }	TSRNetInfo;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0009
    {
    long lSessionObj;
    TSRNetInfo __RPC_FAR *psLoginInf;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Login;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0010
    {
    long lSecurityMask;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_BreakSecurity;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0011
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szUserPswd;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    short bMem;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetGroups;

typedef /* [public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0012
    {
    long lSessionObj;
    TSRTicket sTicket;
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szBaseName;
    /* [string] */ unsigned char __RPC_FAR *szLongBaseName;
    /* [string] */ unsigned char __RPC_FAR *szBasePassword;
    /* [string] */ unsigned char __RPC_FAR *szMaintenancePassword;
    unsigned char bBaseType;
    long bIsCrypto;
    /* [string] */ unsigned char __RPC_FAR *szUserBaseName;
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    long lSlotNum;
    long lCountNum;
    long lMaxKeySize;
    /* [string] */ unsigned char __RPC_FAR *szFileName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_CreateCloseDelete;

typedef /* [public][public][public][public][public] */ struct  __MIDL_lbsrpc_0013
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szGroups;
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_AddDelGroupUser;

typedef /* [public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0014
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    unsigned char szOldPassword[ 11 ];
    unsigned char szNewPassword[ 11 ];
    long lNewType;
    /* [string] */ unsigned char __RPC_FAR *szNewDescrip;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_UserGenInfos;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0015
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szBaseName;
    /* [string] */ unsigned char __RPC_FAR *szBasePassword;
    boolean bExclusive;
    boolean bReadOnly;
    boolean bMaintenance;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_OpenBase;

typedef /* [public][public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0016
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szDataBaseName;
    /* [string] */ unsigned char __RPC_FAR *szUDB;
    long lFilterLevel;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_What;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0017
    {
    long lSessionObj;
    TSRTicket sTicket;
    long lBaseObj;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ReorgBase;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0018
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szNewOwnerName;
    /* [string] */ unsigned char __RPC_FAR *szNewBasePassword;
    /* [string] */ unsigned char __RPC_FAR *szNewMaintenanceBasePassword;
    /* [string] */ unsigned char __RPC_FAR *szImportPsw;
    /* [string] */ unsigned char __RPC_FAR *szFullImportFileName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Import;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0019
    {
    long lProto;
    long lOccurTmOut;
    TSRTicket sTicket;
    TSRGenericObj TSessionObj;
    }	TSRIn_SetSvcParam;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0020
    {
    long lSessionObj;
    TSRTicket sTicket;
    long lBaseObj;
    long lExportTam;
    /* [string] */ unsigned char __RPC_FAR *szExportBuffer;
    /* [string] */ unsigned char __RPC_FAR *szImportPsw;
    /* [string] */ unsigned char __RPC_FAR *szFullExportFileName;
    /* [string] */ unsigned char __RPC_FAR *szEspecificationFileName;
    long lbChangeOwnerName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Export;

typedef /* [public][public][public][public][public] */ struct  __MIDL_lbsrpc_0021
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szNewAddr;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_UpdateUserAddress;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0022
    {
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    /* [string] */ unsigned char __RPC_FAR *szMaintPassword;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    unsigned char szUserPassword[ 11 ];
    }	TSRIn_CreateDefaultUserBase;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0023
    {
    long lSessionObj;
    TSRTicket sTicket;
    unsigned char szPassword[ 11 ];
    /* [string] */ unsigned char __RPC_FAR *szBaseName;
    boolean bForce;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_DeleteUDB;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0024
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szBaseName;
    /* [string] */ unsigned char __RPC_FAR *szBasePassword;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_IncorporateBase;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0025
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szOldName;
    /* [string] */ unsigned char __RPC_FAR *szNewName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_RenameBase;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0026
    {
    /* [string] */ unsigned char __RPC_FAR *szAppName;
    /* [string] */ unsigned char __RPC_FAR *szClientName;
    long lIdApp;
    TSRTicket sTicket;
    TSRGenericObj TSessionObj;
    }	TSRIn_KillSessions;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0027
    {
    /* [string] */ unsigned char __RPC_FAR *szBaseAliasName;
    /* [string] */ unsigned char __RPC_FAR *szUDBName;
    }	TSRIn_GetBaseLongName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0028
    {
    long lSessionObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szBaseName;
    /* [string] */ unsigned char __RPC_FAR *szUserName;
    /* [string] */ unsigned char __RPC_FAR *szWarningMsg;
    boolean bSet;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_MaintBase;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0029
    {
    long lRet;
    long lTam;
    long lGrpTam;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    /* [size_is] */ unsigned char __RPC_FAR *szGrpBuf;
    }	TSROut_GetUsersData;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0030
    {
    long lTamBuff;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    }	TSROut_GetUsersInfo;

typedef /*  */ struct  __MIDL_lbsrpc_0031
    {
    long lTamBuff;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    }	TSROut_GenericBuffer;

typedef /* [public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0032
    {
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    }	TSROut_WhatBases;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0033
    {
    long lProto;
    long lOccurTmOut;
    }	TSROut_GetSvcParam;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0034
    {
    long lRet;
    long lBaseObj;
    }	TSROut_OpenBase;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0035
    {
    unsigned char szBaseName[ 261 ];
    unsigned char szUserName[ 33 ];
    unsigned char szWarningMsg[ 261 ];
    }	TSRMaintBase;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0036
    {
    long lArrayLen;
    /* [size_is] */ TSRMaintBase __RPC_FAR *psMaintBase;
    }	TSROut_MaintBase;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0037
    {
    unsigned char szSerialNum[ 261 ];
    unsigned char szOwnerName[ 261 ];
    unsigned char szCompanyName[ 261 ];
    }	TSROut_InstalInfo;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0038
    {
    long lBaseObj;
    TSRTicket sTicket;
    long lbNavState;
    long lFieldId;
    long liIndex;
    /* [string] */ unsigned char __RPC_FAR *szNavKey;
    long liType;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_SetNavigationLocate;

typedef /*  */ struct  __MIDL_lbsrpc_0039
    {
    long lBaseObj;
    long lSessionObj;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_TicketPar;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0040
    {
    long lBaseObj;
    TSRTicket sTicket;
    TSRField __RPC_FAR *tfField;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szFieldDescription;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    long ltftFieldType;
    long lFieldSize;
    long ltiaIndexAttrib;
    long lFieldAttrib;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_AddField;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0041
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_DelFieldGetFieldObj;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0042
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szOldPassword;
    /* [string] */ unsigned char __RPC_FAR *szNewPassword;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldPassword;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0043
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    /* [string] */ unsigned char __RPC_FAR *szFieldNewAliasName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0044
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    /* [string] */ unsigned char __RPC_FAR *szNewDescription;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldDescription;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0045
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    long lNewSize;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldSize;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0046
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    long liRepNumber;
    boolean bShift;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_DelFieldRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0047
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    long lFieldId;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetNumberOfRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0048
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    long lFieldId;
    long liRepetNumber;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldRepetitionSize;

typedef /* [public] */ struct  __MIDL_lbsrpc_0049
    {
    long lBaseObj;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFields;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0050
    {
    long lBaseObj;
    long lbPar;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_TicketBOOLPar;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0051
    {
    long lBaseObj;
    long liNewTimeOut;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_SetLockTimeOut;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0052
    {
    long lBaseObj;
    long lNewRecQuant;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_SetReorganizeRecQuant;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0053
    {
    long lBaseObj;
    long liPos;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Nth;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0054
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szBuffer;
    TSRTicket sTicket;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Search;

typedef /* [public][public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0055
    {
    long lBaseObj;
    TSRTicket sTicket;
    long liHandle;
    long lStatus;
    /* [string] */ unsigned char __RPC_FAR *szName;
    /* [string] */ unsigned char __RPC_FAR *szExpr;
    long lbCopy;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_OcList;

typedef /* [public] */ struct  __MIDL_lbsrpc_0056
    {
    long lBaseObj;
    TSRTicket sTicket;
    long lbNavState;
    long lFieldId;
    long liIndex;
    /* [string] */ unsigned char __RPC_FAR *szKey;
    long liType;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_SetNavigation;

typedef /* [public][public][public][public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0057
    {
    long lBaseObj;
    long lId;
    long liIndex;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetSlotSize;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0058
    {
    long lBaseObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szStopWord;
    long liTypeSearch;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_SearchStopWord;

typedef /* [public][public][public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0059
    {
    long lBaseObj;
    long lFieldObj;
    long liPos;
    long lId;
    /* [string] */ unsigned char __RPC_FAR *szGoWord;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lMinKeySize;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GoWord;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0060
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    long liIndexAttrib;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldIndexAttrib;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0061
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    long uiAttrib;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldAttrib;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0062
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szName;
    long lId;
    /* [string] */ unsigned char __RPC_FAR *szId;
    unsigned char bMask;
    long liList;
    boolean bCheckAll;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ACLPerm;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0063
    {
    long lBaseObj;
    boolean bEnable;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_EnableOnLineIndex;

typedef /* [public][public][public][public][public] */ struct  __MIDL_lbsrpc_0064
    {
    long lBaseObj;
    long liIndex;
    long lBufferLen;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    long luiId;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetSlotPutSlot;

typedef /* [public][public][public][public] */ struct  __MIDL_lbsrpc_0065
    {
    long lBaseObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szOldPassword;
    /* [string] */ unsigned char __RPC_FAR *szNewPassword;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyPassword;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0066
    {
    long lBaseObj;
    long lNewBaseType;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyBaseType;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0067
    {
    long lBaseObj;
    TSRTicket sTicket;
    boolean bRestoreContext;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_IndexAll;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0068
    {
    long lBaseObj;
    TSRTicket sTicket;
    long lRec;
    long lFieldId;
    long lRepet;
    /* [string] */ unsigned char __RPC_FAR *szStr;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_IndexString;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0069
    {
    long lBaseObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szSW;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_AddStopWord;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0070
    {
    long lBaseObj;
    TSRTicket sTicket;
    /* [string] */ unsigned char __RPC_FAR *szOwnerNamePar;
    /* [string] */ unsigned char __RPC_FAR *szCurrentPsw;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyBaseOwnerName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0071
    {
    long lBaseObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldAliasName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldIndexAttrib;

typedef /* [public] */ struct  __MIDL_lbsrpc_0072
    {
    long lFieldObj;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldObj;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0073
    {
    long lBaseObj;
    short bTipoGetFieldType;
    long lFieldId;
    /* [string] */ unsigned char __RPC_FAR *szFieldName;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldTypeId;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0074
    {
    long lBase;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    short sMethod;
    long lRepNumber;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0075
    {
    long lBase;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    short sMethod;
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *Rep;
    boolean bStart;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetFieldRepetitionByVal;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0076
    {
    long lBase;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    short sMethod;
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *Rep;
    long lIndex;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_PutFieldRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0077
    {
    long lBase;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldId;
    long lRepNumber;
    short sMethod;
    long lTam;
    /* [size_is] */ unsigned char __RPC_FAR *Rep;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ModifyFieldRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0078
    {
    long lBase;
    /* [string] */ unsigned char __RPC_FAR *szName;
    long lList;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetACLListPerm;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0079
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szNewOp;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_ExchangeOperator;

typedef /* [public][public][public][public][public] */ struct  __MIDL_lbsrpc_0080
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szMasks;
    /* [string] */ unsigned char __RPC_FAR *szFileName;
    long liIndex;
    long liType;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Mask;

typedef /* [public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0081
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szPhoneArray;
    /* [string] */ unsigned char __RPC_FAR *szFileName;
    /* [string] */ unsigned char __RPC_FAR *szPhoneValue;
    /* [string] */ unsigned char __RPC_FAR *szTerm;
    long liPhoneNumber;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Phone;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0082
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szStandardizerArray;
    /* [string] */ unsigned char __RPC_FAR *szContent;
    /* [string] */ unsigned char __RPC_FAR *szDestination;
    long liSize;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Standardize;

typedef /* [public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0083
    {
    long lBaseObj;
    /* [string] */ unsigned char __RPC_FAR *szTerm;
    /* [string] */ unsigned char __RPC_FAR *szSynonymArray;
    /* [string] */ unsigned char __RPC_FAR *szFileName;
    long liFlag;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Synonym;

typedef /* [public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0084
    {
    long lBaseObj;
    TSRTicket sTicket;
    long liHandle1;
    long liHandle2;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_OL;

typedef /* [public] */ struct  __MIDL_lbsrpc_0085
    {
    long lBaseObj;
    long lFieldObj;
    long lField;
    /* [string] */ unsigned char __RPC_FAR *szField;
    long lFieldNumber;
    long lFieldId;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_Operators;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0086
    {
    long lBaseObj;
    TSRTicket sTicket;
    long lNumFieldIds;
    /* [size_is] */ long __RPC_FAR *pFieldIds;
    long lTamBuff;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_MGetPutFieldRep;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0087
    {
    /* [string] */ unsigned char __RPC_FAR *szNewBaseName;
    TSRGenericObj TBaseObj;
    }	TSRIn_ModifyBaseName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0088
    {
    TSRTicket sTicket;
    long lBaseObj;
    long lNumRegs;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_AllRepetitions;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0089
    {
    long lObj;
    long lErrNumPar;
    TSRControlInfo sCtrlInfo;
    }	TSRSetError;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0090
    {
    long lArrayLen;
    /* [size_is] */ long __RPC_FAR *pLong;
    }	TSROut_Search;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0091
    {
    long lArrayLen;
    /* [size_is] */ TSRField __RPC_FAR *psField;
    }	TSROut_GetFields;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0092
    {
    long lTamBuff;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    }	TSROut_MGetFieldRep;

typedef /* [public][public][public][public][public][public][public] */ struct  __MIDL_lbsrpc_0093
    {
    /* [string] */ unsigned char __RPC_FAR *pszTerm;
    long lRec;
    long liField;
    long liRepetition;
    long liParagraph;
    long liPhrase;
    long liSequence;
    long liLastError;
    }	TSROut_LBSC_Occurrence;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0094
    {
    long lBufferLen;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    long lRet;
    }	TSROut_GetSlot;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0095
    {
    long usLen;
    /* [size_is] */ unsigned char __RPC_FAR *Return;
    long lRet;
    }	TSROut_GetFieldRepetition;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0096
    {
    /* [string] */ unsigned char __RPC_FAR *szFieldName;
    long lFieldId;
    long lFieldObj;
    }	TSROut_GetFieldObj;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0097
    {
    unsigned char szUDBName[ 261 ];
    unsigned char szOwnerName[ 33 ];
    unsigned char szLastUser[ 33 ];
    /* [string] */ unsigned char __RPC_FAR *szUsers;
    unsigned char szServerName[ 51 ];
    long lNumInst;
    long lCreateDate;
    long lLastModifyDate;
    long lBaseType;
    long lSlotNum;
    long lCountNum;
    long lMaxKeySize;
    long lIntPart;
    long lDecPart;
    long lIsEncrypt;
    long lReExport;
    }	TSROut_BaseInfo;

typedef /* [public][public][public] */ struct  __MIDL_lbsrpc_0098
    {
    unsigned char szFullBaseName[ 261 ];
    long lRet;
    }	TSROut_GetFullBaseName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0099
    {
    /* [string] */ unsigned char __RPC_FAR *szBaseLongName;
    long lRet;
    }	TSROut_GetBaseLongName;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0100
    {
    TSROut_GenericBuffer togUserBaseBuff;
    TSROut_GenericBuffer togGroupBaseBuff;
    TSROut_GenericBuffer togUserFieldBuff;
    TSROut_GenericBuffer togGroupFieldBuff;
    TSROut_GenericBuffer togUserRecordBuff;
    TSROut_GenericBuffer togGroupRecordBuff;
    TSROut_GenericBuffer togUserFormBuff;
    TSROut_GenericBuffer togGroupFormBuff;
    TSROut_GenericBuffer togUserReportBuff;
    TSROut_GenericBuffer togGroupReportBuff;
    /* [string] */ unsigned char __RPC_FAR *szOwnerName;
    long lBaseType;
    boolean bIsBasePasswdCorrect;
    }	TSROut_ACLLists;

typedef /* [public] */ struct  __MIDL_lbsrpc_0101
    {
    long lFieldObj;
    long liIndex;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_GetDataObj;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0102
    {
    long lFieldObj;
    /* [string] */ unsigned char __RPC_FAR *szPassword;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_VerifyPassword;

typedef /* [public] */ struct  __MIDL_lbsrpc_0103
    {
    long lDataObj;
    short sOpType;
    long lFormat;
    long lLen;
    /* [size_is] */ unsigned char __RPC_FAR *szPar;
    TSRControlInfo sCtrlInfo;
    }	TSRIn_DataOp;

typedef /* [public][public] */ struct  __MIDL_lbsrpc_0104
    {
    long lBufferLen;
    /* [size_is] */ unsigned char __RPC_FAR *szBuffer;
    }	TSROut_GetData;

TSRGenericObj RPC_Session_New( 
    /* [in] */ TSRControlInfo sCtrlInfo);

void RPC_Session_Delete( 
    /* [in] */ TSRGenericObj DeadSession);

long RPC_Session_DeleteUDB( 
    /* [in] */ TSRIn_DeleteUDB InPar);

long RPC_Session_DeleteDefaultUserBase( 
    /* [in] */ TSRIn_DeleteUDB InPar);

TSRTicket RPC_Session_Login( 
    /* [in] */ TSRIn_Login InPar);

long RPC_Session_Logout( 
    /* [in] */ TSRGenericObj Session);

long RPC_Session_CloseBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

long RPC_Session_CreateBaseDef( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

long RPC_Session_CreateBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

long RPC_Session_DeleteBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

long RPC_Session_CreateUDB( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

long RPC_Session_AddUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar);

TSROut_OpenBase RPC_Session_OpenBase( 
    /* [in] */ TSRIn_OpenBase InPar);

long RPC_Session_AddGroupToUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar);

boolean RPC_Session_IsLogged( 
    /* [in] */ TSRGenericObj Session);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatServers( void);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatServersForUser( 
    /* [in] */ TSRIn_What InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDBLogged( 
    /* [in] */ TSRGenericObj Session);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDBsForUser( 
    /* [in] */ TSRIn_UserGenInfos InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDB( 
    /* [in] */ TSRIn_What InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserName( 
    /* [in] */ TSRGenericObj Session);

long RPC_Session_ReorganizeBase( 
    /* [in] */ TSRIn_ReorgBase InPar);

long RPC_Session_TicketIsOk( 
    /* [in] */ TSRIn_GetGroups InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetGroups( 
    /* [in] */ TSRIn_GetGroups InPar);

long RPC_Session_DelUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar);

long RPC_Session_UpdateUserPassword( 
    /* [in] */ TSRIn_UserGenInfos InPar);

long RPC_Session_UpdateUserDescription( 
    /* [in] */ TSRIn_UserGenInfos InPar);

long RPC_Session_UpdateUserType( 
    /* [in] */ TSRIn_UserGenInfos InPar);

long RPC_Session_GetUserType( 
    /* [in] */ TSRIn_UserGenInfos InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserDescription( 
    /* [in] */ TSRIn_UserGenInfos InPar);

long RPC_Session_DelGroupFromUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUsers( 
    /* [in] */ TSRIn_GetGroups InPar);

TSROut_GetUsersData RPC_Session_GetUsersData( 
    /* [in] */ TSRIn_UserGenInfos InPar);

TSROut_WhatBases RPC_Session_WhatBases( 
    /* [in] */ TSRIn_What InPar);

TSROut_WhatBases RPC_Session_WhatBasesForUser( 
    /* [in] */ TSRIn_What InPar);

TSROut_WhatBases RPC_Session_WhatBasesOnServer( 
    /* [in] */ TSRIn_What InPar);

TSROut_WhatBases RPC_Session_WhatBasesForUserOnServer( 
    /* [in] */ TSRIn_What InPar);

long RPC_Session_Export( 
    /* [in] */ TSRIn_Export InPar);

long RPC_Session_ExportBaseFormat( 
    /* [in] */ TSRIn_Export InPar);

long RPC_Session_Import( 
    /* [in] */ TSRIn_Import InPar);

long RPC_Session_UpdateUserAddress( 
    /* [in] */ TSRIn_UpdateUserAddress InPar);

long RPC_Session_UpdateUserPhone( 
    /* [in] */ TSRIn_UpdateUserAddress InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserAddress( 
    /* [in] */ TSRIn_UpdateUserAddress InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserPhone( 
    /* [in] */ TSRIn_UpdateUserAddress InPar);

long RPC_Session_CreateDefaultUserBase( 
    /* [in] */ TSRIn_CreateDefaultUserBase InPar);

long RPC_Session_RebuildControl( void);

long RPC_Session_IncorporateBase( 
    /* [in] */ TSRIn_IncorporateBase InPar);

long RPC_Session_ClearBase( 
    /* [in] */ TSRIn_IncorporateBase InPar);

long RPC_Session_RenameBase( 
    /* [in] */ TSRIn_RenameBase InPar);

long RPC_Session_ReorganizeUDB( 
    /* [in] */ TSRIn_IncorporateBase InPar);

long RPC_Session_ReorganizeDefaultUserBase( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Session_LeaveBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetDefUserBaseName( void);

long RPC_Session_SetServerParam( 
    /* [in] */ TSRIn_SetSvcParam InPar);

TSROut_GetSvcParam RPC_Session_GetServerParam( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GetUsersInfo RPC_Session_GetUsersInfo( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Session_UnLockRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Session_KillSessions( 
    /* [in] */ TSRIn_KillSessions InPar);

long RPC_Session_KillServer( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetBaseLongName( 
    /* [in] */ TSRIn_GetBaseLongName InPar);

void RPC_Session_CancelOperation( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GetOpInfo RPC_Session_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar);

void RPC_Session_StBreakSecurity( 
    /* [in] */ TSRIn_BreakSecurity InPar);

void RPC_Session_BreakSecurity( 
    /* [in] */ TSRIn_BreakSecurity InPar);

long RPC_Session_ValidUser( 
    /* [in] */ TSRIn_DeleteUDB InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_StGetGroups( 
    /* [in] */ TSRNetInfo InPar);

long RPC_Session_SetBaseForMaintenance( 
    /* [in] */ TSRIn_MaintBase InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetDefaultWarningMsg( 
    /* [in] */ TSRGenericObj InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetBaseWarningMsg( 
    /* [in] */ TSRIn_What InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Session_GeMaintBaseUserName( 
    /* [in] */ TSRIn_What InPar);

TSROut_MaintBase RPC_Session_GetReservedMaintBases( 
    /* [in] */ TSRIn_TicketPar InPar);

boolean RPC_Session_NeedReprocOnConvert( 
    /* [in] */ TSRIn_OpenBase InPar);

int RPC_Session_ConvertBase( 
    /* [in] */ TSRIn_OpenBase InPar);

TSROut_InstalInfo RPC_Session_GetInstalInfo( void);

long RPC_Error_SetLastError( 
    /* [in] */ TSRSetError sIn);

long RPC_Error_LastError( 
    /* [in] */ TSRGenericObj lObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Error_LastErrorDesc( 
    /* [in] */ TSRGenericObj lObj);

TSROut_GetFieldRepetition RPC_Base_GetFieldRepetition( 
    /* [in] */ TSRIn_GetFieldRepetition sIn);

long RPC_Base_GetFieldRepetitionByVal( 
    /* [in] */ TSRIn_GetFieldRepetitionByVal sIn);

long RPC_Base_PutFieldRepetition( 
    /* [in] */ TSRIn_PutFieldRepetition sIn);

long RPC_Base_PutFieldRepetitionByIndex( 
    /* [in] */ TSRIn_PutFieldRepetition sIn);

long RPC_Base_ModifyFieldRepetition( 
    /* [in] */ TSRIn_ModifyFieldRepetition sIn);

TSROut_GetFieldObj RPC_Base_GetFieldObj( 
    /* [in] */ TSRIn_DelFieldGetFieldObj sIn);

boolean RPC_Base_BaseObjOk( 
    /* [in] */ TSRGenericObj Base);

long RPC_Base_AddField( 
    /* [in] */ TSRIn_AddField InPar);

long RPC_Base_DelField( 
    /* [in] */ TSRIn_DelFieldRepetition InPar);

long RPC_Base_ModifyFieldPassword( 
    /* [in] */ TSRIn_ModifyFieldPassword InPar);

long RPC_Base_ModifyFieldName( 
    /* [in] */ TSRIn_ModifyFieldName InPar);

long RPC_Base_ModifyFieldDescription( 
    /* [in] */ TSRIn_ModifyFieldDescription InPar);

long RPC_Base_ModifyFieldSize( 
    /* [in] */ TSRIn_ModifyFieldSize InPar);

long RPC_Base_GetNumberOfFields( 
    /* [in] */ TSRGenericObj Base);

long RPC_Base_DelFieldRepetition( 
    /* [in] */ TSRIn_DelFieldRepetition InPar);

long RPC_Base_InsertBlankRepetition( 
    /* [in] */ TSRIn_DelFieldRepetition InPar);

long RPC_Base_GetNumberOfRepetition( 
    /* [in] */ TSRIn_GetNumberOfRepetition InPar);

long RPC_Base_GetFieldRepetitionSize( 
    /* [in] */ TSRIn_GetFieldRepetitionSize InPar);

long RPC_Base_GetNumRecords( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_CurrRecNum( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_GetIndexRecNum( 
    /* [in] */ TSRIn_TicketBOOLPar InPar);

byte RPC_Base_CurrRecStatus( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_LockRecord( 
    /* [in] */ TSRIn_TicketBOOLPar InPar);

long RPC_Base_ReleaseRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_UpdateRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_AppendRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_ReadRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_DeleteRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_ClearRecord( 
    /* [in] */ TSRGenericObj Base);

long RPC_Base_SetLockTimeOut( 
    /* [in] */ TSRIn_SetLockTimeOut InPar);

long RPC_Base_SetReorganizeRecQuant( 
    /* [in] */ TSRIn_SetReorganizeRecQuant InPar);

long RPC_Base_FirstRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_LastRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_NextRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_PreviousRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_NthRecord( 
    /* [in] */ TSRIn_Nth InPar);

long RPC_Base_CurrentRecord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_GetNumOccurrences( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_SaveOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_SortOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_EnableSecureSort( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_SecureSortStatus( 
    /* [in] */ TSRGenericObj Base);

long RPC_Base_LoadOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_EnableOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_GetOLRecNumber( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_UnloadOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_DeleteOcList( 
    /* [in] */ TSRIn_OcList InPar);

long RPC_Base_DeleteOcRecords( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_SetNavigationByIndex( 
    /* [in] */ TSRIn_SetNavigationLocate InPar);

long RPC_Base_SetNavigationByKey( 
    /* [in] */ TSRIn_SetNavigationLocate InPar);

long RPC_Base_Locate( 
    /* [in] */ TSRIn_SetNavigationLocate InPar);

long RPC_Base_GetNumberOfSlots( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_GetSlotSize( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_GetFieldSlotSize( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_AddGoWord( 
    /* [in] */ TSRIn_GoWord InPar);

long RPC_Base_DelGoWord( 
    /* [in] */ TSRIn_GoWord InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetGowords( 
    /* [in] */ TSRIn_GoWord InPar);

boolean RPC_Base_SetGowords( 
    /* [in] */ TSRIn_GoWord InPar);

long RPC_Base_GetMinkeysize( 
    /* [in] */ TSRIn_GoWord InPar);

long RPC_Base_SetMinkeysize( 
    /* [in] */ TSRIn_GoWord InPar);

long RPC_Base_ModifyFieldIndexAttrib( 
    /* [in] */ TSRIn_ModifyFieldIndexAttrib InPar);

long RPC_Base_ModifyFieldAttrib( 
    /* [in] */ TSRIn_ModifyFieldAttrib InPar);

TSROut_GetFields RPC_Base_GetFields( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetCurrentOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetFirstOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetLastOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetNextOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetPreviousOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_LBSC_Occurrence RPC_Base_GetNthOccurrence( 
    /* [in] */ TSRIn_Nth InPar);

TSROut_Search RPC_Base_Search( 
    /* [in] */ TSRIn_Search InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetCurrentExpression( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetOcListExpression( 
    /* [in] */ TSRIn_OcList InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetCurrentStopWord( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_DelStopWord( 
    /* [in] */ TSRIn_AddStopWord InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetFirstStopWord( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetLastStopWord( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetNextStopWord( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetPreviousStopWord( 
    /* [in] */ TSRIn_TicketPar InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetNthStopWord( 
    /* [in] */ TSRIn_Nth InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_SearchStopWord( 
    /* [in] */ TSRIn_SearchStopWord InPar);

long RPC_Base_SetACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar);

long RPC_Base_GetACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar);

long RPC_Base_DelACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar);

long RPC_Base_EnableOnLineIndex( 
    /* [in] */ TSRIn_EnableOnLineIndex InPar);

long RPC_Base_OnLineIndexStatus( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_UpdateIndex( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_IndexAll( 
    /* [in] */ TSRIn_IndexAll InPar);

TSROut_GetSlot RPC_Base_GetSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar);

long RPC_Base_PutSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar);

TSROut_GetSlot RPC_Base_GetFieldSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar);

long RPC_Base_PutFieldSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar);

long RPC_Base_GetNumberOfCounters( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_GetCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_PutCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_IncCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_DecCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_LockCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_ReleaseCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_GetNextCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_GetPreviousCount( 
    /* [in] */ TSRIn_GetSlotSize InPar);

long RPC_Base_ModifyPassword( 
    /* [in] */ TSRIn_ModifyPassword InPar);

long RPC_Base_ModifyMaintenancePassword( 
    /* [in] */ TSRIn_ModifyPassword InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetUserBase( 
    /* [in] */ TSRGenericObj lBaseObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetOwnerName( 
    /* [in] */ TSRGenericObj lBaseObj);

TSROut_GetFullBaseName RPC_Base_GetFullBaseName( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GetFullBaseName RPC_Base_GetBaseName( 
    /* [in] */ TSRGenericObj InPar);

boolean RPC_Base_IsEncrypt( 
    /* [in] */ TSRGenericObj lBaseObj);

boolean RPC_Base_IsFullAccess( 
    /* [in] */ TSRGenericObj lBaseObj);

byte RPC_Base_GetBaseType( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_GetBaseVersion( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_ModifyBaseType( 
    /* [in] */ TSRIn_ModifyBaseType InPar);

long RPC_Base_IndexString( 
    /* [in] */ TSRIn_IndexString InPar);

long RPC_Base_UnindexString( 
    /* [in] */ TSRIn_IndexString InPar);

boolean RPC_Base_IndexSystemOk( 
    /* [in] */ TSRGenericObj lBaseObj);

long RPC_Base_GetNumberOfStopWords( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_AddStopWord( 
    /* [in] */ TSRIn_AddStopWord InPar);

long RPC_Base_ModifyBaseOwnerName( 
    /* [in] */ TSRIn_ModifyBaseOwnerName InPar);

short RPC_Base_GetFieldType( 
    /* [in] */ TSRIn_GetFieldTypeId InPar);

long RPC_Base_GetFieldId( 
    /* [in] */ TSRIn_GetFieldTypeId InPar);

long RPC_Base_GetFieldIndexAttrib( 
    /* [in] */ TSRIn_GetFieldIndexAttrib InPar);

TSROut_WhatBases RPC_Base_GetACLListPermission( 
    /* [in] */ TSRIn_GetACLListPerm InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_ExchangeOperator( 
    /* [in] */ TSRIn_ExchangeOperator InPar);

long RPC_Base_SetMask( 
    /* [in] */ TSRIn_Mask InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetMask( 
    /* [in] */ TSRIn_Mask InPar);

long RPC_Base_SaveMasks( 
    /* [in] */ TSRIn_Mask InPar);

long RPC_Base_LoadMasks( 
    /* [in] */ TSRIn_Mask InPar);

long RPC_Base_ClearMasks( 
    /* [in] */ TSRGenericObj BaseObj);

long RPC_Base_AddPhone( 
    /* [in] */ TSRIn_Phone InPar);

long RPC_Base_DeletePhone( 
    /* [in] */ TSRIn_Phone InPar);

long RPC_Base_SavePhone( 
    /* [in] */ TSRIn_Phone InPar);

long RPC_Base_LoadPhone( 
    /* [in] */ TSRIn_Phone InPar);

long RPC_Base_ClearPhone( 
    /* [in] */ TSRGenericObj BaseObj);

long RPC_Base_FindPhone( 
    /* [in] */ TSRIn_Phone InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_SetStandardizer( 
    /* [in] */ TSRIn_Standardize InPar);

long RPC_Base_Standardize( 
    /* [in] */ TSRIn_Standardize InPar);

long RPC_Base_AddSynonym( 
    /* [in] */ TSRIn_Synonym InPar);

long RPC_Base_DeleteSynonym( 
    /* [in] */ TSRIn_Synonym InPar);

long RPC_Base_SaveSynonym( 
    /* [in] */ TSRIn_Synonym InPar);

long RPC_Base_LoadSynonym( 
    /* [in] */ TSRIn_Synonym InPar);

long RPC_Base_ClearSynonym( 
    /* [in] */ TSRGenericObj BaseObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_FindSynonym( 
    /* [in] */ TSRIn_Synonym InPar);

long RPC_Base_OLAnd( 
    /* [in] */ TSRIn_OL InPar);

long RPC_Base_OLOr( 
    /* [in] */ TSRIn_OL InPar);

long RPC_Base_OLXor( 
    /* [in] */ TSRIn_OL InPar);

long RPC_Base_OLNot( 
    /* [in] */ TSRIn_OL InPar);

boolean RPC_Base_IsExportable( 
    /* [in] */ TSRGenericObj BaseObj);

long RPC_Base_BlockReExport( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_ModifyRecordPassword( 
    /* [in] */ TSRIn_ModifyPassword InPar);

boolean RPC_Base_IsReadOnly( 
    /* [in] */ TSRGenericObj lBaseObj);

boolean RPC_Base_IsExclusive( 
    /* [in] */ TSRGenericObj lBaseObj);

boolean RPC_Base_Flush( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_GetNumActiveRecords( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_ModifyMaxKeySize( 
    /* [in] */ TSRIn_CreateCloseDelete InPar);

TSROut_BaseInfo RPC_Base_GetBaseInfo( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_GetNumOLRecords( 
    /* [in] */ TSRIn_OL InPar);

long RPC_Base_GetNumRecIndex( 
    /* [in] */ TSRGenericObj lBaseObj);

boolean RPC_Base_GetStopIndex( 
    /* [in] */ TSRGenericObj BaseObj);

void RPC_Base_SetStopIndex( 
    /* [in] */ TSRIn_TicketBOOLPar InPar);

long RPC_Base_ClearBase( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_MGetFieldRep RPC_Base_MGetFieldRepetition( 
    /* [in] */ TSRIn_MGetPutFieldRep InPar);

long RPC_Base_MPutFieldRepetition( 
    /* [in] */ TSRIn_MGetPutFieldRep InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetStopWords( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_ModifyBaseName( 
    /* [in] */ TSRIn_ModifyBaseName InPar);

TSROut_GetBaseLongName RPC_Base_GetBaseLongName( 
    /* [in] */ TSRGenericObj InPar);

void RPC_Base_CancelOperation( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GetOpInfo RPC_Base_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GenericBuffer RPC_Base_GetAllFieldSlots( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_ACLLists RPC_Base_GetAllACLLists( 
    /* [in] */ TSRIn_TicketPar InPar);

TSROut_GenericBuffer RPC_Base_GetAllRepetitions( 
    /* [in] */ TSRIn_AllRepetitions InPar);

TSROut_GenericBuffer RPC_Base_GetAllOccurrences( 
    /* [in] */ TSRIn_TicketPar InPar);

long RPC_Base_EnableFastRecord( 
    /* [in] */ TSRIn_EnableOnLineIndex InPar);

TSROut_GenericBuffer RPC_Base_GetBaseTimeInfo( 
    /* [in] */ TSRGenericObj InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetDirBase( 
    /* [in] */ TSRIn_GetBaseLongName InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetFirstGoWord( 
    /* [in] */ TSRGenericObj FieldObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetNextGoWord( 
    /* [in] */ TSRGenericObj FieldObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetCurrentGoWord( 
    /* [in] */ TSRGenericObj FieldObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetNthGoWord( 
    /* [in] */ TSRIn_GoWord InPar);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_SearchGoWord( 
    /* [in] */ TSRIn_GoWord InPar);

long RPC_Field_GetNbrOfGoWord( 
    /* [in] */ TSRGenericObj FieldObj);

/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetAliasName( 
    /* [in] */ TSRGenericObj lFieldObj);

long RPC_Field_Clear( 
    /* [in] */ TSRGenericObj FieldObj);

long RPC_Field_GetId( 
    /* [in] */ TSRGenericObj FieldObj);

long RPC_Field_GetSize( 
    /* [in] */ TSRGenericObj FieldObj);

long RPC_Field_VerifyPassword( 
    /* [in] */ TSRIn_VerifyPassword InPar);

TSROut_GetData RPC_Data_GetData( 
    /* [in] */ TSRGenericObj DataObj);

long RPC_Data_GetSize( 
    /* [in] */ TSRGenericObj lDataObj);

void RPC_OpInfo_CancelOperation( 
    /* [in] */ TSRGenericObj InPar);

TSROut_GetOpInfo RPC_OpInfo_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar);

boolean RPC_SvcInitContext( 
    /* [in] */ TSRClntInitInfo sInitInfo);

boolean RPC_SvcEndContext( 
    /* [in] */ TSRClntInitInfo sCtrlInfo);

void RPC_SvcIsUp( void);

TSROut_GenericBuffer RPC_Session_GetUDBTimeInfo( 
    /* [in] */ TSRGenericObj InPar);

long RPC_Session_KillSessionsEx( 
    /* [in] */ TSRIn_KillSessions InPar);


extern handle_t _lbsrpc_IfHandle;


extern RPC_IF_HANDLE lbsrpc_v17_0_c_ifspec;
extern RPC_IF_HANDLE lbsrpc_v17_0_s_ifspec;
#endif /* __lbsrpc_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
