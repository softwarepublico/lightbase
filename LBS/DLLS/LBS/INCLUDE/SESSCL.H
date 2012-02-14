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
// Module: SESSCL.H
// Description:
//
//	LBSC_Session class definition file.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 19/10/94
//

#ifndef	_SESSCL_H_
#define	_SESSCL_H_

#if !defined( __STDIO_H ) && !defined _INC_STDIO
#include	<stdio.h>
#endif
#ifndef	_BASELIST_H_
#include	<baselist.h>
#endif
#ifndef	_ALLBASEL_H_
#include	<allbasel.h>
#endif
#ifndef	_SVBASEL_H_
#include	<svbasel.h>
#endif
#ifndef	_USR_H_
#include	<usrcl.h>
#endif
#ifndef	_TIMECL_H_
#include	<timecl.h>
#endif
#ifndef	_EXPORTLIST_H_
#include	<explist.h>
#endif
#ifndef	_SERLST_H_
#include	<serlst.h>
#endif
#ifndef	_USRINFOL_H_
#include	<usrinfol.h>
#endif
#ifndef	_CLIENTLIST_H_
#include	<clilist.h>
#endif
#ifndef	_LICCTRL_H_
#include	<licctrl.h>
#endif
#ifndef	_MBASELST_H_
#include	<MBaseLst.h>
#endif
#include	<controlfile.h>


// prototipos
class	LBSC_User;
#ifndef	_LBSTYPES_H_
// se nao ja incluiu este arquivo, nao ha a declaracao desta classe
class	TUserCacheInfo;
#endif
class	LBSC_BaseTimersList;

typedef	struct _sLoginInfo TLoginInfo;

#ifdef __cplusplus
extern "C"					 
{
#endif // __cplusplus

////////////////////////////////////////////////
// funcao para ser disparada como thread
DWORD	ThreadFunc( LPVOID );
////////////////////////////////////////////////

class CritSessManager : public CritSectManager
{
	void CritSectLog( char *szMsg, char *szFile, int iLine, int iNum );
	unsigned long GetCritSectMask();
	void SetCritSectMask( unsigned long );
	BOOL OrderedDependents();
};
extern CritSessManager _csSessMan;


// classe para tratamento de regioes criticas
class	C_GlobalSessCritSect : public C_CritSect<10>	// 10 = numero de regioes criticas para tratamento de sessao
{
public:
	C_GlobalSessCritSect()
	{
		UseCriticalSection( TRUE );
		SetManager( &_csSessMan );
	}
};

extern	C_GlobalSessCritSect	*_pcGlobalSessCritSect;

class _LBSCLASS LBSC_Session :	public LBSC_Error, 
								public LBSC_OpInfo,
								C_LeaveCritSect<C_GlobalSessCritSect>
{
	friend	class				LBSC_LicControl;
	friend	class				LBSC_OLSort;
	friend	class				LBSC_ControlFile;
	friend	class	_LBSCLASS	LBSC_Base;
	friend	void				ReleaseLocks( LBSC_BaseTimersList *pBaseTimersList );
	friend	void	CALLBACK	LicTimerProc( HWND, UINT, UINT, DWORD );
	friend	int					RecoverLicence();
	friend	DWORD				ThreadFunc( LPVOID );

	friend	struct	_sLoginInfo;

	private:


		LBSC_BaseList		lbscblBaseList;
		LBSC_User			*plbscuUser;
		C_Date				cdOpenSessionDate;
		C_Time				ctOpenSessionTime;
		LBSC_Ticket			*plbsctTicket;
		BOOL				bIsLogged;
		BOOL				bIsMono;
		BOOL				bSLogin;
		FullSTR				strUDBLogged;
		TLoginInfo			*pLoginInfo;
		int					iSecurityFlags;
		FullSTR				strAppName;
		long				lAppId;
		unsigned long		ulLastAccess;
		DWORD				dwUserBaseId;
	static	int				iNumLic;			// numero de licencas usadas (do servidor)
	static	int				iUserCacheSize;
	static	TUserCacheInfo	*pUserCache;
	static	LBSC_BaseList	*pLRUBases;
	static	LBSC_ControlFile *pControlFile;
	static					LBSC_Base *NewBaseHandler( const LBSC_Ticket *, const char *, const char *, const char *, LBSC_Session *, BOOL, BOOL, BOOL, BOOL = TRUE );
	static					LBSC_Base *NewBaseHandler( const LBSC_Ticket *, const char *, LBSC_Session *, BOOL = FALSE, BOOL = TRUE, BOOL = FALSE );
	static					LBSC_Base *GetBaseHandler( const char *, LBSC_Session * );
	static					void ReturnBaseHandler( LBSC_Base * );


	static	int				GetFNameOnProfile( char *, char * );
	static	int				InsertBasesInControlFile( C_RecordFile &, char * );

		int					FindUser( LBSC_Base *, const char *, const char * );
		int					FindUser( const char *, const char *, const char * );
		void				Init();
		int					WriteImpExpFileHeader( C_File *, char *, BOOL, int );
		int					ImportBase( const LBSC_Ticket *, C_File *, BOOL, char *, char *, char * );
		int					RenameToOrigFiles( char *, char * );
		int					CopyDir( char *, char *, BOOL = FALSE );
		int					PutBaseInUDB( char *, BYTE, char *, char * );
		int					DelBaseOfUDB( char *, char *, char * );
		BOOL				CheckFieldInCurrentKey( char *, LBSC_Base & );
		long				GetUserType( LBSC_Base *, char * );
		const LBSC_Ticket*	SLogin( TNetInfo & );
		int					BufferToFile( C_File *, C_File *, long );
		int					SetUDBACLs( LBSC_Base *pBase );

		// metodos para manipulacao do slot privado de uma base
		int					PutPrivateSlotInfo( const char *);
		int					GetPrivateSlotInfo( const char *, char * );
		int					GetPrivateSlotSize( const char * );
		const char *		MakePrivateSlotInfo();
		int					SizeofPrivateSlot();
		char *				GetUDBName( const char * );
		int					GetBaseType( const char * );
		int					RenameDirFiles( char * );

		// metodos para obter com seguranca um elemento da lista de sessoes
		int					LockSessList();
		int					ReleaseSessList();
		LBSC_Session		*GetFirstSession();
		LBSC_Session		*GetNextSession();
		LBSC_Session		*GetPreviousSession();
		LBSC_Session		*GetLastSession();

		// metodos para obter com seguranca um elemento da lista de licencas
		int					LockLicList();
		int					ReleaseLicList();
		TLicInfo			*GetFirstLic();
		TLicInfo			*GetNextLic();
		TLicInfo			*GetPreviousLic();
		TLicInfo			*GetLastLic();

		// metodo para reprocessar uma base
		int					ReprocBase( const LBSC_Ticket *, LBSC_Base *, BOOL = TRUE );
		static void			InvalidateCacheInSubDirs( char *szDirName );

		// metodo para obter o nome longo da base no arquivo de controle
		int					GetBaseLongName( C_RecordFile &, char *, char * );

		// metodos para incorporar bases
		int					IncorporateBase3( const LBSC_Ticket *, char *, char *, char *, char * );
		int					IncorporateBase4( const LBSC_Ticket *, char *, char *, char *, char * );

		// reprocessar UDB
		int					ReorganizeUDB( const LBSC_Ticket *, LBSC_Base * );

		// converter grupos de campos multivalorados
		int					ConvertGroupInfo( LBSC_Base *pOrigBase, LBSC_Base *pNewBase = NULL );

		// metodos para conversao de base
		int					ConvertBaseTo( const LBSC_Ticket *pTicket, LBSC_Base *pBase, int iVersionTo );
		int					ConvertUDBTo( const LBSC_Ticket *pTicket, LBSC_Base *pBase, int iVersionTo );

		static int			FindUserInCache( const char *szUserName, const char *szPassword, const char *szUDB );
		void				DelUserFromCache( const char *szUserName, const char *szPassword, const char *szUDB );
		void				DelUDBFromCache( const char *szUDB );
		void				AddUserToCache( const char *szUserName, const char *szPassword, const char *szUDB, int iType );
		static	void		LoadUserCacheFromBases();
		static	BOOL		LoadUserCacheFromFile();
		void				ChangeUserCachePwd( const char *szName, const char *szPwd, const char *szUDB, const char *szNewPwd );
		void				ChangeUserCacheType( const char *szName, const char *szPwd, const char *szUDB, int iNewType );

		static BOOL			ControlFileOK();

		// metodos para verificacoes de seguranca
		int					VerifyLoginAttempts( LBSC_Base *pUserBase, char *szUser );
		BOOL				PasswordExpired( LBSC_Base *pUserBase, char *szUser );
		BOOL				InvalidPasswordFormat( char *szNewPassword );
		BOOL				EqualsStoredPasswords( LBSC_Base *pUserBase, char *szUser, char *szNewPassword );
		BOOL				NeedUptadeUserPassword( LBSC_Base *pUserBase, char *szUser, char *szCheckPassword );
	
	public:

									LBSC_Session();
									~LBSC_Session();
																	  
	static	char                    *getAppDrive( char * );
	static	LBSC_Session			*New( const char * = NULL );
	static	void					Delete( LBSC_Session * );
	static	void					LoadUserCache();
	static	void					SaveUserCache();
	static	void					ClearAll();
	char							*WhatUDBsForUser( const char *szUserName, const char *szPassword, const char *szServer );
	static	char					*WhatServers();
	static	LBSC_AllBasesList		*WhatBases( int );
	static	LBSC_ServerBasesList	*WhatBasesOnServer( int, const char *szServer, char *szUDB = NULL, char *szUser = NULL );
	static	int						CreateDefaultUserBase( char *, char *, char *, char *, char * );
	static	int						RebuildControl( char * );
	static	char					*GetDefUserBaseName( char * );
	static	int						DeleteDefaultUserBase( char *, char *, BOOL = FALSE );
	static	void					Delete( void * );
	static	void					Delete( char * );
	static	void					Delete( int * );
	static	void					Delete( TField * );
	static	void					Delete( TUDBRecord * );
	static	void					Delete( LBSC_AllBasesList * );
	static	void					Delete( LBSC_ServerBasesList * );
	static	void					Delete( LBSC_PermList * );
	static	void					Delete( LBSC_ACLList * );
	static	void					Delete( LBSC_AppUserInfoList * );
	static	void					Delete( LBSC_AppNetInfoList * );
	static	void					Delete( LBSC_AppSessionNetInfoList * );
	static	void					Delete( LBSC_AppBaseNetInfoList * );
	static	void					Delete( TBaseInfo * );
	static	void					Delete( TSlotCache * );
	static	void					Delete( TSlotCacheInfo * );
	static	void					Delete( LBSC_Session ** );
	static	void					Delete( TACL_Lists * );
	static	void					Delete( LBSC_MaintBase * );
	static	void					Delete( C_Buffer * );
	static	int						KillSession( char *, char *, char *, char *, char * );
	static	LBSC_Session			**GetSessions( char *, char *, char *, char *, char * );
	static	char					*GetBaseLongName( char *, char *, char * );
	static	void					StBreakSecurity( int, const char * );
	static	char					*GetGroups( const char *, const char *, const char * );
	static const char 				*GetReinstallPath();


		int							DeleteUDB( const LBSC_Ticket *, char *, char *, BOOL = FALSE );
		char						*WhatServersForUser( char * );
		const LBSC_Ticket			*Login( TNetInfo & );
		int							Logout();
		BOOL						IsLogged();
		BOOL						IsMono();
		LBSC_AllBasesList			*WhatBasesForUser( int, char * );
		LBSC_ServerBasesList		*WhatBasesForUserOnServer( int, const char *, const char * );
		int							CreateBase( const LBSC_Ticket *, char *, char*, char *, char *, 	/* 1 */
												BYTE, BOOL, char *, TField *, int, int, int = 0 );
		int							CreateBase( const LBSC_Ticket *, char * );			/* 2 */
		int							OpenBase( const LBSC_Ticket *, char *, char *, BOOL, BOOL, BOOL, LBSC_Base ** );
		int							CloseBase( const LBSC_Ticket *, LBSC_Base * );
		int							DeleteBase( const LBSC_Ticket *, char * );
		int							ClearBase( const LBSC_Ticket *, char * );
		const char					*GetUserName();
		int							Export( const LBSC_Ticket *, LBSC_ExportBaseList *,
											char *, char *, BOOL );
		int							Import( const LBSC_Ticket *, char *, char *, char *, char *, char * );
		int							ReorganizeBase( const LBSC_Ticket *, LBSC_Base * );
		int							ReorganizeUDB( const LBSC_Ticket *, char * );
		int							ReorganizeDefaultUserBase( const LBSC_Ticket * );
		int							TicketIsOk( const LBSC_Ticket * );
		int							ExportBaseFormat( const LBSC_Ticket *, LBSC_Base *, char * );
		char						*WhatUDBLogged();
		char						*WhatUDB( char *, const char * = DEFAULTSERVER );
		int							CreateUDB( const LBSC_Ticket *, char *, char *, char *);
		char						*GetGroups( const LBSC_Ticket *, char *, BOOL = FALSE );
		int							AddUser( const LBSC_Ticket *, char *, TUDBRecord * );
		int							DelUser( const LBSC_Ticket *, char *, char * );
		int							UpdateUserPassword( const LBSC_Ticket *, char *, char *, char *, char * );
		int							UpdateUserPassword( char *szServer, char *, char *, char *, char * );
		int							UpdateUserType( const LBSC_Ticket *, char *, char *, long );
		long						GetUserType( const LBSC_Ticket *, char *, char * );
		int							UpdateUserDescription( const LBSC_Ticket *, char *, char *, char * );
		int							UpdateUserAddress( const LBSC_Ticket *, char *, char *, char * );
		int							UpdateUserPhone( const LBSC_Ticket *, char *, char *, char * );
		char						*GetUserDescription( const LBSC_Ticket *, char *, char * );
		char						*GetUserAddress( const LBSC_Ticket *, char *, char * );
		char						*GetUserPhone( const LBSC_Ticket *, char *, char * );
		int							AddGroupToUser( const LBSC_Ticket *, char *, char *, char * );
		int							DelGroupFromUser( const LBSC_Ticket *, char *, char *, char * );
		char						*GetUsers( const LBSC_Ticket *, char * );
		int							GetUsersData( const LBSC_Ticket *, char *, TUDBRecord **, char *** );
		int							LeaveBase( const LBSC_Ticket *, char * );
		int							IncorporateBase( const LBSC_Ticket *, char *, char *, char *, char * );
		int							ChangeUDB( const LBSC_Ticket *, char *, char *, char *, char * );
		int							RenameBase( const LBSC_Ticket *, char *, char * );
		BOOL						IsUDBOwner( const LBSC_Ticket *, char * );
		int							ValidUser( const LBSC_Ticket *, const char *, const char * );
		int							GetUDBTimeInfo( struct stat *psInfo );

		// metodos para tratamento de listas
		int							Compare( LBSC_Session *, int );
		LBSC_Session				*Duplicate( void );

		// metodos para sincronizacao com o stub cliente.
		// sao metodos que nao existem de fato no LBS mono, mas
		// sao necessarios porque existem no LBS-client.
		void						KillServer( char * );
		int							SetServerParam( const LBSC_Ticket *, int, int );
		static	void				GetServerParam( char *, int *, int * );
		static	int					SetClientParam( int, int, int, int, char ** );
		static	void				GetClientParam( int *, int *, int *, int *, char *** );
		LBSC_AppUserInfoList		*GetUsersInfo( const LBSC_Ticket * );
		int							UnLockRecord( const LBSC_Ticket *, long );
		int							KillSessions( const LBSC_Ticket *, char *, char *, long, long );
		int							KillServer( const LBSC_Ticket *, char * );
		static	void				EndLbs();

		// metodo para fazer o LBS desligar momentaneamente a
		// checagem de algum tipo de seguranca
		void						BreakSecurity( int );

		// metodos para o servidor setar/obter o nome e o tipo da aplicacao 
		// que esta' mantendo a sessao
		void						SetAppInfo( long lAppId, const char *szAppName );
		void						SetLastAccess( unsigned long ulLastAccess );
		const char					*GetAppName();
		unsigned long				GetLastAccess();
		void						GetClientName( char *szClient );

		// metodos para feedback
		void						CancelOperation();
		void						GetOpInfo( char *, float * );

		// metodos para reservar bases para manutencao
		int							SetBaseForMaintenance( const LBSC_Ticket *pTicketPar, const char *szBaseName, const char *szUserName, const char *szWarningMsg, BOOL bSet );
		char						*GetDefaultWarningMsg();
		char						*GetBaseWarningMsg( const char *szBaseName );
		char						*GeMaintBaseUserName( const char *szBaseName );
		LBSC_MaintBase				*GetReservedMaintBases( const LBSC_Ticket *pTicketPar );

		// metodos para conversao de base
		BOOL						NeedReprocOnConvert( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword );
		int							ConvertBase( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword );
		BOOL						BaseObjOk( LBSC_Base * );


// eh esperado um warning com a definicao abaixo, 
// apesar de não ter nenhum problema, pois o metodo
// eh sempre chamado via C++ (ver help do warning C4190)
#pragma warning( disable : 4190 )

		// manipulando informacoes de instalacao da copia 
		static TInstalInfo			GetInstalInfo( const char * szServer );

// restaurando a verificacao do warning
#pragma warning( default : 4190 )

};

class	C_SessCritSect
{
	int				iLastSectUsed;
	LBSC_Session	*pObj;

public:
	C_SessCritSect( LBSC_Session *pObjPar, int iNumCritSect, char *szFile, int iLinePar )
	{
		if( _pcGlobalSessCritSect ){
			_pcGlobalSessCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar, szFile, iLinePar );
			iLastSectUsed = iNumCritSect;
			pObj = pObjPar;
		}
	}
	~C_SessCritSect()
	{
		if( _pcGlobalSessCritSect ){
			_pcGlobalSessCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
	void EnterCriticalSection()
	{
		if( _pcGlobalSessCritSect ){
			_pcGlobalSessCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
		}
	}
	void LeaveCriticalSection()
	{
		if( _pcGlobalSessCritSect ){
			_pcGlobalSessCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
};

typedef	struct _sLoginInfo {
	TNetInfo		tniInfo;
//	int				iUsedLicenses;		// numero de licencas usadas para o numero de serie
					// nao precisa, porque eh igual ao numero de elementos de clClientList

	LBSC_ClientList	clClientList;		// lista de pares maquina/usuario
	LBSC_Session	*pOwnerSession;

	_sLoginInfo()
	{
		tniInfo.strClientSN = "";
		pOwnerSession = NULL;
//		iUsedLicenses = 1;
//		iClientLicenses = 1;
	}
	_sLoginInfo( TNetInfo &tni, LBSC_Session *pOwner )//, int iLicenses )
	{
		Set( tni, pOwner );//, iLicenses );
	}
	void Set( TNetInfo &tni, LBSC_Session *pOwner )//, int iLicenses )
	{
		tniInfo = tni;
//		iUsedLicenses = iLicenses;
		pOwnerSession = pOwner;
	}
	~_sLoginInfo()
	{
		if( pOwnerSession ){
			pOwnerSession->pLoginInfo = NULL;
		}
	}

	int Load( C_File &cf )
	{/*
		if( !cf.IsOpen() ){
			return( !OK );
		}
		if( tniInfo.Load( cf ) == OK &&
//			cf.Read( &iUsedLicenses, sizeof( iUsedLicenses ) ) == OK &&
			cf.Read( &pOwnerSession, sizeof( pOwnerSession ) ) == OK &&
			clClientList.Read( cf ) == OK ){
			return( OK );
		}*/
		return( !OK );
	}

	int Save( C_File &cf )
	{/*
		if( !cf.IsOpen() ){
			return( !OK );
		}
		if( tniInfo.Save( cf ) == OK &&
//			cf.Write( &iUsedLicenses, sizeof( iUsedLicenses ) ) == OK && 
			cf.Write( &pOwnerSession, sizeof( pOwnerSession ) ) == OK &&
			clClientList.Write( cf ) == OK ){
			return( OK );
		}*/
		return( !OK );
	}

	int Compare( _sLoginInfo *pOther, int iCompType )
	{
		if( !pOther ){
			return( 0 );
		}
		switch( iCompType ){
		case CMPSERIALNUM:
			if( tniInfo.strClientSN == pOther->tniInfo.strClientSN ){
				return( 0 );
			}
			return( 1 );

		case CMPBASICELEM:
			if( tniInfo.strClientSN == pOther->tniInfo.strClientSN ){
				TClientInfo		tci( pOther->tniInfo.strUserName, pOther->tniInfo.strClient );
				if( clClientList.Find( &tci ) ){
					return( 0 );
				}
			}
			return( 1 );

		case CMPSESSIONPOINTER:
			return( pOwnerSession == pOther->pOwnerSession ? 0 : 1 );

		case CMPTNIPOINTER:
			return( this == pOther ? 0 : 1 );

		}
		return( 0 );
	}
	_sLoginInfo *Duplicate( void )
	{
		_sLoginInfo	*pNew = new _sLoginInfo( tniInfo, pOwnerSession );//, iUsedLicenses );
		if( pNew ){
			pNew->clClientList = clClientList;
		}
		return( pNew );
	}


} TLoginInfo;


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _SESSCL_H_

