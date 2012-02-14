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
#define _SESSCL_H_

#ifndef	_ALLBASEL_H_
#include <allbasel.h>
#endif
#ifndef	_SVBASEL_H_
#include <svbasel.h>
#endif
#ifndef	_EXPORTLIST_H_
#include <explist.h>
#endif
#ifndef	_SERLST_H_
#include <serlst.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include <defclass.h>
#endif
#ifndef	_LBSDEFS_H_
#include <lbsdefs.h>
#endif
#ifndef	_LBSTYPES_H_
#include <lbstypes.h>
#endif
#ifndef	_TICKETCL_H_
#include <ticketcl.h>
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
#ifndef	_ACLLIST_H_
#include <acllist.h>
#endif	
#ifndef	_PERMLIST_H_
#include <permlist.h>
#endif

class	LBSC_MaintBase;

// Os proximos serao devido a compatibilidade
/*#if !defined( __STDIO_H ) && !defined _INC_STDIO
#include	<stdio.h>
#endif

#ifndef	_BASELIST_H_
#include	<baselist.h>
#endif
#ifndef	_USR_H_
#include	<usrcl.h>
#endif
#ifndef	_TIMECL_H_
#include	<timecl.h>
#endif
*/

typedef long LBSCSESSION;
typedef long LBSCTICKET;
typedef long LBSCBASE;
typedef	int (CALLBACK *LBSERRPROC)();

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_Base;

class _LBSCLASS LBSC_Session : public LBSC_OpInfo {

		
	private:
		const LBSC_Ticket		*pTicket;
		char					szUserName[USERNAMESIZE + 2];
		static void	*Broadcast( int, LBSC_Session *, int , void *);
		static void	ObtemMergedServers( char **, char ***);

	public:
		char *szBuffer;


		LBSC_Session();

		static LBSC_Session	*New( const char *szMachine );
		static void			Delete( LBSC_Session * );
		static int			CreateDefaultUserBase( char *, char *, char *, char *, char * );
		const LBSC_Ticket*		Login( TNetInfo & );
		int					Logout();
		BOOL				IsLogged();
		int					CreateUDB( const LBSC_Ticket *, char *, char *, char *);
		
		int					CreateBase( const LBSC_Ticket *, char *, char *, char *, char *, 
										BYTE, BOOL, char *, TField *, int, int, int = 0 );
		int					CreateBase( const LBSC_Ticket *, char * );
		int					CloseBase( const LBSC_Ticket *, LBSC_Base * );
		int					DeleteBase( const LBSC_Ticket *, char *);
		int					AddUser( const LBSC_Ticket *, char *, TUDBRecord * );
		int					OpenBase( const LBSC_Ticket *, char *, char *, BOOL, BOOL, BOOL, LBSC_Base ** );
		int					AddGroupToUser( const LBSC_Ticket *, char *, char *, char * );
		static	char		*WhatServers();
		char				*WhatServersForUser( char * );
		const char			*GetUserName();
		char				*GetGroups( const LBSC_Ticket *, char *, BOOL = FALSE );
		int					ReorganizeBase( const LBSC_Ticket *, LBSC_Base * );
		int					TicketIsOk( const LBSC_Ticket *lbscTicket );
		char				*WhatUDBLogged();
		char				*WhatUDBsForUser( const char *szUserName, const char *szPassword, const char *szServer );
		char				*WhatUDB( char *, const char * = DEFAULTSERVER );
		int					DelUser( const LBSC_Ticket *, char *, char * );
		int					UpdateUserPassword( const LBSC_Ticket *, char *, char *, char *, char * );
		int					UpdateUserPassword( char *, char *, char *, char *, char * );
		int					UpdateUserType( const LBSC_Ticket *, char *, char *, long );
		long				GetUserType( const LBSC_Ticket *, char *, char * );
		int					UpdateUserDescription( const LBSC_Ticket *, char *, char *, char * );
		char				*GetUserDescription( const LBSC_Ticket *, char *, char * );
		int					DelGroupFromUser( const LBSC_Ticket *, char *, char *, char * );
		char				*GetUsers( const LBSC_Ticket *, char * );
		int					GetUsersData( const LBSC_Ticket *, char *, TUDBRecord **, char ***);
	 	static LBSC_AllBasesList 	*WhatBases( int );
		LBSC_AllBasesList 			*WhatBasesForUser( int, char * = NULL );
		static LBSC_ServerBasesList *WhatBasesOnServer( int, const char *, char * = NULL, char * = NULL );
		LBSC_ServerBasesList 		*WhatBasesForUserOnServer( int, TMachineAddr , char * = NULL );
		int					Export( const LBSC_Ticket *, LBSC_ExportBaseList *, char *, char *, BOOL );
		int					Import( const LBSC_Ticket *, char *, char *, char *, char *, char *);
		int					ExportBaseFormat( const LBSC_Ticket *, LBSC_Base *, char *);

		int					UpdateUserAddress( const LBSC_Ticket *, char *, char *, char * );
		int					UpdateUserPhone( const LBSC_Ticket *, char *, char *, char * );
		char *				GetUserAddress( const LBSC_Ticket *, char *, char * );
		char *				GetUserPhone( const LBSC_Ticket *, char *, char * );
		static int				RebuildControl( char * );
		int					LeaveBase( const LBSC_Ticket *, char * );
		static char *		GetDefUserBaseName( char * );
		int					IncorporateBase( const LBSC_Ticket *, char *, char *, char *, char * );
		int					ClearBase( const LBSC_Ticket *, char * );
		int					RenameBase( const LBSC_Ticket *, char *, char * );
		int					ReorganizeUDB( const LBSC_Ticket *, char * );
		int					ReorganizeDefaultUserBase( const LBSC_Ticket * );
		static int			DeleteDefaultUserBase( char *, char *, BOOL = FALSE );
		int			DeleteUDB( const LBSC_Ticket *, char *, char *, BOOL = FALSE );
		static void		Delete( void * );
		static void		Delete( char * );
		static void		Delete( int * );
		static void		Delete( TField * );
		static void		Delete( TUDBRecord * );
		static void		Delete( LBSC_AllBasesList * );
		static void		Delete( LBSC_ServerBasesList * );
		static void		Delete( LBSC_PermList * );
		static void		Delete( TBaseInfo * );
		static void		Delete( LBSC_Session ** );
		static void		Delete( LBSC_AppUserInfoList * );
		static void		Delete( LBSC_AppNetInfoList * );
		static void		Delete( LBSC_AppSessionNetInfoList * );
		static void		Delete( LBSC_AppBaseNetInfoList * );
		static void		Delete( TACL_Lists * );
		static void		Delete( LBSC_ACLList * );
        static  void    Delete( TSlotCache * );
        static  void    Delete( TSlotCacheInfo * );
        static  void    Delete( LBSC_MaintBase * );
		static const char 		*GetReinstallPath();

		int				KillSessions( const LBSC_Ticket *, char *, char *, long, long );
		static	LBSC_Session **OpenSessions( char *, char *, char *, char *, char * );
		int				KillServer( const LBSC_Ticket *, char * );
		int				SetServerParam( const LBSC_Ticket *, int , int );
		static void		GetServerParam( char *, int *, int * );
		static int		SetClientParam( int, int, int, int, char **);
		static void		GetClientParam( int *, int *, int *, int *, char ***);
		LBSC_AppUserInfoList	*GetUsersInfo( const LBSC_Ticket * );
		int				UnLockRecord( const LBSC_Ticket * , long );
		BOOL			IsUDBOwner( const LBSC_Ticket * , char *, char * );
		static char		*GetBaseLongName( char *, char *, char * );
		static void		ObtemServidores( char *** );
		static BOOL		AlteraServidores( char ** );
		void			CancelOperation();				// cancela a operacao corrente
		void			GetOpInfo( char *, float * );	// obtem o status da operacao corrente
		static void		StBreakSecurity( int , const char *);
		void			BreakSecurity( int );
		int				ValidUser( const LBSC_Ticket *, const char *, const char *);
		static char		*GetGroups( const char *, const char *, const char *);

		// metodos para reservar bases para manutencao
		int				SetBaseForMaintenance( const LBSC_Ticket *pTicket, const char *szBaseName, const char *szUserName, const char *szWarningMsg, BOOL bSet );
		char			*GetDefaultWarningMsg();
		char			*GetBaseWarningMsg( const char *szBaseName );
		char			*GeMaintBaseUserName( const char *szBaseName );
		LBSC_MaintBase	*GetReservedMaintBases( const LBSC_Ticket *pTicket );

		// metodos para conversao de base
		BOOL						NeedReprocOnConvert( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword );
		int							ConvertBase( const LBSC_Ticket *pTicket, char *szBaseName, char *szBasePassword );

		// manipulando informacoes de instalacao da copia 
		static TInstalInfo			GetInstalInfo( const char * szServer );
		int				GetUDBTimeInfo( struct stat * );
};
#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _SESSCL_H_

