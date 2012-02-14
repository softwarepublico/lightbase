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
// Module: LBSTYPES.H
// Description:
//
//	Define data types for Light Base Server
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 26/09/94
//

#ifndef	_LBSTYPES_H_
#define	_LBSTYPES_H_

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef _CL_STRINGN_
#include	<stringn.h>
#endif
#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_STRDUP_H_
#include	<strdup.h>
#endif
#ifndef	_BUFFERCL_H_
#include	<buffercl.h>
#endif

#ifndef	_SERVERCONFIG_H_
#include	<serverconfig.h>
#endif 

class _LBSCLASS LBSC_ServerBasesList;
class _LBSCLASS LBSC_Base;
class _LBSCLASS LBSC_Session;
class _LBSCLASS LBSC_AppUserInfoList;
class _LBSCLASS LBSC_AppNetInfoList;
class _LBSCLASS LBSC_AppSessionNetInfoList;
class _LBSCLASS LBSC_AppBaseNetInfoList;

typedef	int								TAclType;
typedef	int								TAclPerm;
typedef	int								TRepetition;
typedef	BYTE							TFieldType;
typedef	int								TIndexAttrib;
typedef	long							TRecord;
typedef	int								TParagraph;
typedef	int								TPhrase;
typedef	long							TSequence;
typedef	long							TTerm;
typedef	long							TTicket;
typedef	BYTE							TUserType;
typedef CL_StringN<USERNAMESIZE> 		UserSTR;
typedef CL_StringN<DESCRIPTIONSIZE>		DescSTR;
typedef CL_StringN<ADDRESSSIZE>			AddrSTR;
typedef CL_StringN<PHONESIZE>			PhoneSTR;
typedef CL_StringN<PASSWORDSIZE>		PswdSTR;
typedef CL_StringN<FULLNAMESIZE>		FullSTR;
typedef CL_StringN<FULLNAMESIZE>		BaseSTR;
typedef CL_StringN<GROUPNAMESIZE>		GroupSTR;
typedef	CL_StringN<SERVERNAMESIZE>		TMachineAddr;
typedef	CL_StringN<SERIALNUMBERSIZE>	SerialSTR;


extern LBSC_AppNetInfoList *New_LBSC_AppNetInfoList();
extern LBSC_AppSessionNetInfoList *New_LBSC_AppSessionNetInfoList();
extern LBSC_AppBaseNetInfoList *New_LBSC_AppBaseNetInfoList();
extern void	Delete_LBSC_AppNetInfoList( LBSC_AppNetInfoList * );
extern void Delete_LBSC_AppSessionNetInfoList( LBSC_AppSessionNetInfoList * );
extern void Delete_LBSC_AppBaseNetInfoList( LBSC_AppBaseNetInfoList * );
void Equal_LBSC_AppUserInfoList( LBSC_AppUserInfoList *, LBSC_AppUserInfoList * );
void Equal_LBSC_AppNetInfoList( LBSC_AppNetInfoList *, LBSC_AppNetInfoList * );
void Equal_LBSC_AppSessionNetInfoList( LBSC_AppSessionNetInfoList *, LBSC_AppSessionNetInfoList * );
void Equal_LBSC_AppBaseNetInfoList( LBSC_AppBaseNetInfoList *, LBSC_AppBaseNetInfoList * );


// esta estrutura serve para a passagem de parametros para o thread
// que matara eventuais locks pendurados
typedef	struct	_sBaseTimers{
	public:

	LBSC_Base		*pBase;
	LBSC_Session	*pSession;
	DWORD		dwInterval;
	DWORD		dwStartTime;
	long		lLockPos;

	_sBaseTimers() {
		pBase = NULL;
		pSession = NULL;
		dwInterval = 0;
		dwStartTime = 0;
		lLockPos = 0;
	}

	int	Compare( struct _sBaseTimers *psbtBaseTimers, int iType )
	{
		if ( psbtBaseTimers->pBase == pBase &&
				psbtBaseTimers->pSession == pSession &&
				psbtBaseTimers->lLockPos == lLockPos ) {
			return( 0 );
		}
		return( 1 );
	}

	struct _sBaseTimers	*Duplicate()
	{
		return( NULL );	
	}
}		TBaseTimers;

typedef	struct	_sExportBase{
	private:
	CL_StringN<FULLNAMESIZE>	szBaseName;
	CL_StringN<FULLNAMESIZE>	szBaseLongName;
	CL_StringN<PASSWORDSIZE>	szBasePassword;
	BOOL				bReExport;

	public:
	char			*GetBaseName(){ return( (char*) szBaseName ); }
	char			*GetBaseLongName(){ return( (char*) szBaseLongName ); }
	char			*GetBasePassword(){ return( (char*) szBasePassword ); }
	BOOL			IsExportable(){ return( bReExport ); }
	int			SetBaseName( char *szBaseName ){
				this->szBaseName = szBaseName;
				return( LBS_OK );
	}
	int			SetBaseLongName( char *szBaseLongName ){
				this->szBaseLongName = szBaseLongName;
				return( LBS_OK );
	}
	int			SetBasePassword( char *szBasePassword ){
				this->szBasePassword = szBasePassword;
				return( LBS_OK );
	}
	void			SetBaseReExport( BOOL b ){ bReExport = b; }
	int			Compare( struct _sExportBase *sebAux, int iType ){ return( strcmp( szBaseName, sebAux->szBaseName ) ); }
	struct _sExportBase 	*Duplicate(){ return( NULL ); }	//  Implementar
}		TExportBase;

typedef struct _sInstalInfo{				//  estrutura de bases em um servidor
	CL_StringN<FULLNAMESIZE>	szSerialNum;
	CL_StringN<FULLNAMESIZE>	szOwnerName;
	CL_StringN<FULLNAMESIZE>	szCompanyName;
} TInstalInfo;

typedef struct _sServerBases{				//  estrutura de bases em um servidor
	private:
	int				iBaseType;
	CL_StringN<FULLNAMESIZE>	szBaseName;
	CL_StringN<FULLNAMESIZE>	szBaseLongName;
	CL_StringN<FULLNAMESIZE>	szUserBaseName;

	public:
	int	GetBaseType()
	{
		return( iBaseType );
	}
	char	*GetBaseName()
	{
		return( (char*) szBaseName );
	}
	char	*GetBaseLongName()
	{
		return( (char*) szBaseLongName );
	}
	char	*GetUserBaseName()
	{
		return( (char*) szUserBaseName );
	}
	void	SetBaseType( int iBT )
	{
		iBaseType = iBT;
	}
	void	SetBaseName( char *sz )
	{
		szBaseName = sz;
	}
	void	SetBaseLongName( char *sz )
	{
		szBaseLongName = sz;
	}
	void	SetUserBaseName( char *sz )
	{
		szUserBaseName = sz;
	}

	int	Compare( struct _sServerBases *ssbServerBases, int iType )
	{
		return( LBS_OK );			//  talvez precise fazer algo aqui. Nao sei bem o que mas...
	}

	struct _sServerBases	*Duplicate()
	{
		return( NULL );				//  talvez precise fazer algo aqui. Nao sei bem o que mas...
	}

}		TServerBases;

typedef struct _sAllBases{				//  estrutura todas as bases da rede
	TMachineAddr		tmaServer;
	LBSC_ServerBasesList	*plbscsblServerBasesList;

	int	Compare( struct _sAllBases *sabAllBases, int iType )
	{
		return( LBS_OK );			//  talvez precise fazer algo aqui. Nao sei bem o que mas...
	}

	struct _sAllBases	*Duplicate()
	{
		return( NULL );				//  talvez precise fazer algo aqui. Nao sei bem o que mas...
	}
}		TAllBases;

typedef struct _sUserBaseName{
	CL_StringN<FULLNAMESIZE>	szUserBaseName;

	int	Compare( struct _sUserBaseName	*sUserBaseName, int iType )
	{
		return( strcmp( sUserBaseName->szUserBaseName, this->szUserBaseName ) );
	}

	struct _sUserBaseName	*Duplicate()
	{
		return( NULL );				//  talvez precise fazer algo aqui. Nao sei bem o que mas...
	}


	char	*GetUserBaseName()
	{
		return( szUserBaseName );
	}
}		TUserBaseName;


typedef	struct	_sLink{					//  estrutura de um link gravado em LB5
	BOOL	bPropagate;
	BYTE	bLinkType;
	CL_StringN<FULLNAMESIZE>	szBaseName;
	CL_StringN<FIELDNAMESIZE> szFieldAliasName;
}		TLink;

typedef struct	_sFreeSpace{ 				//  nodo da lista de espaco livre
	long			lSpaceSize;
	long			lNextFreeSpace;
}				TFreeSpace;

typedef	struct	_sControlRec_V3 {				//  registro de LB1 (formato anterior a versao 4.*)
	unsigned long	ulCreateDate;
	unsigned long	ulModifyDate;
	CL_StringN<USERNAMESIZE>		szLastModifyUserName;
	CL_StringN<USERNAMESIZE>		szOwnerName;
	BYTE		bRecStatus;
	unsigned long	ulAccess;		// contador de acessos ao registro
	long		lContentPos;
}			TControlRec_V3;

typedef	struct	_sRecordBufferHeader {				//  header de registro em LB4
	long lId;
	long lNumRep;
	long lOffSet;
} TRecordBufferHeader;

typedef	struct	_sControlRecHead {			//  cabecalho de LB1
//	BYTE				bMagicNumber;
	int				iSlotNum;		// number of slots
	int				iCountNum;		// number of counters
	int				iMaxKeySize;		// max size of key
	int				iIntPart;		// number of digits of integer part of a number
	int				iDecPart;		// number of digits of decimal part of a number
	long				lDeletedRecNum;		// number of deleted records
	long				lDeletedRecNumReorg;	// number of deleted records to reorganize the base
	long				lNumRecords;		// Number of records
	long				lLastRecPos;		// Last record position into the control file
	long				lFirstRecActivePos;	// First record active position into the control file
	long				lLastRecActivePos;	// Last record active position into the control file
	unsigned long			ulCreateDate;		// Base creation date
	unsigned long			ulLastModifyDate;	// Last modify date
	UINT				uiLastFieldId;		// last used field id
	BOOL				bIsEncrypt;		// flag to define if this base is encrypted
	BOOL				bReExport;		// flag to define if this base can be re-exported
	BOOL				bBaseIndexed;		// flag to define if the base is indexed
	BOOL				bOnLineIndex;		// if the on-line index is ON
	BYTE				bBaseType;		// Base type
	DWORD				dwBaseId;		// Base id
	DWORD				dwUserBaseId;		// User Base id
	CL_StringN<FULLNAMESIZE>	szUserBase;		// User base full name
	CL_StringN<USERNAMESIZE>	szOwnerName;		// Base owner name
	CL_StringN<USERNAMESIZE>	szLastModifyUserName;	// Name of user who modified the base
	CL_StringN<MAXBASEPASS>		szBasePassword;		// Base password
	CL_StringN<MAXMAINTENANCEPASS>	szMaintenancePassword;	// Maintenance base password

	_sControlRecHead()
	{
		memset( (void*) &iSlotNum, 0, sizeof( _sControlRecHead ) );
	}

}				TControlRecHead;

typedef struct _sContentRecPsw {			//  registro de LB2
	CL_StringN<RECORDPASSWORDSIZE>		szPassword;
	int								iNrFields;
}				TContentRecPsw;

typedef	struct	_sContentRec {				//  registro para cada campo em LB2
	UINT			uiFieldId;
	int			iNumberOfRepetition;
	long			lFirstRepetition;
}				TContentRec;
/*
typedef	struct	_sContentRecHead {			//  cabecalho de LB2
	BYTE			bMagicNumber;
	TFreeSpace		tfsFreeSpace;
}				TContentRecHead;
*/
struct SlotPointer{
	union{
		long	lCount;	// usado quando estamos trabalhando com contadores
		long	lSize;	// usado quando trabalhamos com slots
	} pElem;
	long	lPointer;	// usado quando trabalhamos com slots
	SlotPointer( void )
	{
		pElem.lSize = 0L;
		lPointer = 0L;
	}
};

typedef	struct	_sStructRec {				//  registro de LB3
	CL_StringN<FIELDNAMESIZE>		szFieldAliasName;
	CL_StringN<DESCRIPTIONSIZE> 	szFieldDescription;
	CL_StringN<FIELDPASSWORDSIZE>	szFieldPassword;
	BYTE							bFieldType;
	UINT							uiFieldAttrib;		// mascara de bits para indicar varios estados (vide defines de possiveis estados em userdefs.h)
	long							lFieldSize;
	UINT							uiFieldId;
	TIndexAttrib					tiaIndexAttrib;
	long							lLinkListPointer;
	SlotPointer						spSlot;

	int	Compare( struct	_sStructRec *ssrOther, int iCompType )
	{
		//  FALTA DEFINIR ESTE METODO
		return( 0 );
	}
	struct	_sStructRec *Duplicate()
	{
		//  FALTA DEFINIR ESTE METODO
		return( NULL );
	}
}				TStructRec;

typedef	struct	_sStructHeadRec {			//  cabecalho de LB3
//	BYTE		bMagicNumber;
	int		iNumberOfFields;
	SlotPointer	spSlot[ 1 ];

	static long SizeOf( int iSlotNum )
	{
		return sizeof( _sStructHeadRec ) + sizeof( SlotPointer ) * ( iSlotNum > 0 ? (iSlotNum - 1) : 0 );
	}
	static _sStructHeadRec *Alloc( int iSlotNum )
	{
		_sStructHeadRec	*p = (_sStructHeadRec*) new char [ _sStructHeadRec::SizeOf( iSlotNum ) ];
		if( p ){
			memset( (void*) p, 0, _sStructHeadRec::SizeOf( iSlotNum ) );
		}
		return p;
	}
	static void Free( _sStructHeadRec *pshrHead )
	{
		if( pshrHead ){
			delete (char*) pshrHead;
		}
	}

}				TStructHeadRec;

typedef struct	_sRepetitionRec{ 			//  registro de LB4
	long			lRepetitionSize;
	long			lNextRepetition;
}				TRepetitionRec;
/*
typedef	struct	_sRepetitionRecHead {			//  cabecalho de LB4
	BYTE			bMagicNumber;
	TFreeSpace	tfsFreeSpace;
}				TRepetitionRecHead;
*/
/*
typedef struct	_sLinkRec{ 			//  registro de LB5
	TLink		tlLink;
	long			lNextLink;
}				TLinkRec;

typedef	struct	_sLinkRecHead {			//  cabecalho de LB5
	BYTE			bMagicNumber;
	TFreeSpace	tfsFreeSpace;
}				TLinkRecHead;
*/

typedef	struct	_sBasesFile {				//  registro do arquivo de bases
	CL_StringN<FULLNAMESIZE>	szBaseName;		// alias_name da base
	CL_StringN<FULLNAMESIZE>	szUserBaseName;	// nome da udb
	CL_StringN<FULLNAMESIZE>	szBaseLongName;	// nome longo da base
	BYTE						bBaseType;		// tipo da base
	BOOL						bRecDeleted;	// indica se o registros esta' deletado.
}					TBasesFile;

typedef	struct	_sField{
	CL_StringN<FIELDNAMESIZE>  	szFieldAliasName;
	CL_StringN<DESCRIPTIONSIZE>	szFieldDescription;
	CL_StringN<PASSWORDSIZE> 	szPasswordName;
	TFieldType					tftFieldType;
	long						lFieldSize;
	UINT						uiFieldId;
	TIndexAttrib				tiaIndexAttrib;
	UINT						uiFieldAttrib;

    _sField()
    {
        szFieldAliasName = "";
        szFieldDescription = "";
        szPasswordName = "";
        tftFieldType = 0;
        lFieldSize = 0;
        uiFieldId = 0;
        tiaIndexAttrib = 0;
		uiFieldAttrib = 0;
    }
    void Set( char *szName, char *szDesc, char *szPasswd,
         TFieldType tftType, long lSize, TIndexAttrib tiaIndex, UINT uiFieldAttribPar = 0 )
    {
        szFieldAliasName = szName ? szName : "";
        szFieldDescription = szDesc ? szDesc : "";
        szPasswordName = szPasswd ? szPasswd : "";
        tftFieldType = tftType;
        lFieldSize = lSize;
        uiFieldId = 0;
        tiaIndexAttrib = tiaIndex;
		uiFieldAttrib = uiFieldAttribPar;
    }

	BOOL	IsZero()
	{
		return( (szFieldAliasName.operator == ((const char*) "")) &&
			( szFieldDescription.operator == ((const char*) "")) &&
			( szPasswordName.operator == ((const char*) "" )) &&
			tftFieldType == 0 &&
			lFieldSize == 0 &&
			uiFieldId == 0 &&
			tiaIndexAttrib == 0 &&
			uiFieldAttrib == 0 ? TRUE : FALSE );
	}

	struct _sField operator = ( struct _sField &sOther )
	{
		szFieldAliasName = sOther.szFieldAliasName;
		szFieldDescription = sOther.szFieldDescription;
		szPasswordName = sOther.szPasswordName;
		tftFieldType = sOther.tftFieldType;
		lFieldSize = sOther.lFieldSize;
		uiFieldId = sOther.uiFieldId;
		tiaIndexAttrib = sOther.tiaIndexAttrib;
		uiFieldAttrib = sOther.uiFieldAttrib;

		return( *this );
	}
			
}				TField;

// Nodo da lista de SerialNumbers
typedef	struct _sSerialNumber{
		SerialSTR	strSerialNumber;

		int	Compare( struct _sSerialNumber	*psSerialNumber, int iType )
		{
			return( this->strSerialNumber == psSerialNumber->strSerialNumber ? 0 : 1 );
		}

		struct _sSerialNumber	*Duplicate()
		{
			return( NULL );
		}
}	TSerialNumber;

// Header do arquivo de Imporatacao/Exportacao
typedef	struct _sImpExpFileHeader{
	PswdSTR		strImportPsw;
	BOOL		bChangeOwnerBase;
	int		iNumberOfBases;
}	TImpExpFileHeader;

// Cabecalho de LB1 para exportacao
typedef	struct	_sControlRecHeadExp {			//  cabecalho de LB1
	int				iSlotNum;
	int				iCountNum;
	int				iLockTimeOut;		// Lock timeout
	long				lDeletedRecNumReorg;	// number of deleted records to reorganize the base
	long				lNumRecords;		// Number of records
	BOOL				bIsEncrypt;		// flag to define if this base is encrypted
	BOOL				bReExport;		// flag to define if this base can be re-exported
	BOOL				bBaseIndexed;		// flag to define if the base is indexed or not
	BYTE				bBaseType;		// Base type
	DWORD				dwBaseId;		// Base id
	unsigned long			ulCreateDate;		// Base creation date
	unsigned long			ulLastModifyDate;	// Last modify date
	CL_StringN<MAXMAINTENANCEPASS>	szMaintenancePassword;
	CL_StringN<MAXBASEPASS>		szBasePassword;		// Base password
	CL_StringN<USERNAMESIZE>	szOwnerName;		// Base owner name
	CL_StringN<USERNAMESIZE>	szLastModifyUserName;	// Name of user who modified the base

}				TControlRecHeadExp;

// Registro de LB1 para exportacao
typedef	struct	_sControlRecExp {
	unsigned long					ulCreateDate;
	unsigned long					ulModifyDate;
	CL_StringN<USERNAMESIZE>			szLastModifyUserName;
	CL_StringN<USERNAMESIZE>			szOwnerName;
	CL_StringN<RECORDPASSWORDSIZE>	szPassword;
	BYTE						bRecStatus;
}			TControlRecExp;

// Campo de LB2 para exportacao
typedef	struct	_sContentRecExp {
	UINT			uiFieldId;
	int 			iNumberOfRepetition;
}				TContentRecExp;

// Repeticao de LB4 para exportacao
typedef struct	_sRepetitionRecExp{
	long			lRepetitionSize;
}				TRepetitionRecExp;

// Registro de LB5
typedef struct _sLB5{
	long	lNumRecord;
	long	lLB6Pos;
}	TLB5Record;


typedef struct	_sUDBRecord {
	UserSTR		szUserName;
	PswdSTR		szUserPassword;
	long		lUserType;
	DescSTR		szUserDescription;
	AddrSTR		szUserAddress;
	PhoneSTR	szUserPhone;
	GroupSTR	szUserGroup;

	BOOL IsZero()
	{
		return( szUserName == (char*) "" &&
			szUserPassword == (char*) "" &&
			lUserType == 0 &&
			szUserDescription == (char*) "" &&
			szUserAddress == (char*) "" &&
			szUserPhone == (char*) "" &&
			szUserGroup == (char*) "" ? TRUE : FALSE );
	}
	_sUDBRecord()
	{
		szUserName = "";
		szUserPassword = "";
		lUserType = 0;
		szUserDescription = "";
		szUserAddress = "";
		szUserPhone = "";
		szUserGroup = "";
	}
	void Set( char *szName, char *szPassword, long lType, char *szDescription, 
			  char * szAddress, char * szPhone, char *szGroup )
	{
		szUserName = szName ? szName : "";
		szUserPassword = szPassword ? szPassword : "";
		lUserType = lType;
		szUserDescription = szDescription ? szDescription : "";
		szUserAddress = szAddress ? szAddress : "";
		szUserPhone = szPhone ? szPhone : "";
		szUserGroup = szGroup ? szGroup : "";
	}
}			TUDBRecord;


typedef struct _LockInfo {		// informacao que e' gravada no arquivo de lock
	TMachineAddr	tmaServer;
	UserSTR		szUserName;
	BOOL		bTry;
}		TLockInfo;


typedef	struct _sNetInfo {
	// atributos passados como parametros no construtor
	UserSTR			strUserName;
	PswdSTR			strPasswd;
	BaseSTR			strUDBName;
	TMachineAddr	strServer;
	TMachineAddr	strClient;
	SerialSTR		strClientSN;
	int				iClientLicenses;
	BOOL			bMono;

	BOOL IsZero()
	{
		return( strUserName == (char*) "" &&
			strPasswd == (char*) "" &&
			strUDBName == (char*) "" &&			
			strServer == (char*) "" &&
			strClient == (char*) "" &&
			strClientSN  == (char*) "" ? TRUE : FALSE );
	}

	_sNetInfo()
	{
		strUserName = "";
		strPasswd = "";
		strUDBName = "";
		strServer = "";
		strClient = "";
		strClientSN = "";
		iClientLicenses = 1;
		bMono = FALSE;
	}
	void Set( char *szName, char *szPassword, char *szUDBName, char *szServer, char *szClient, char *szSerialNumber, int iClientLicensesPar = 1, BOOL bMonoPar = FALSE )
	{
		strUserName = szName;
		strPasswd = szPassword;
		strUDBName = szUDBName;
		strServer = szServer;
		strClient = szClient;
		strClientSN = szSerialNumber;
		iClientLicenses = iClientLicensesPar;
		bMono = bMonoPar;
	}
	_sNetInfo( char *szName, char *szPassword, char *szUDBName, char *szServer, char *szClient, char *szSerialNumber, int iClientLicensesPar = 1, BOOL bMonoPar = FALSE )
	{
		strUserName = szName;
		strPasswd = szPassword;
		strUDBName = szUDBName;
		strServer = szServer;
		strClient = szClient;
		strClientSN = szSerialNumber;
		iClientLicenses = iClientLicensesPar;
		bMono = bMonoPar;
	}
	_sNetInfo( _sNetInfo &sniOther )
	{
		strUserName = sniOther.strUserName;
		strPasswd = sniOther.strPasswd;
		strUDBName = sniOther.strUDBName;
		strServer = sniOther.strServer;
		strClient = sniOther.strClient;
		strClientSN = sniOther.strClientSN;
		iClientLicenses = sniOther.iClientLicenses;
		bMono = sniOther.bMono;
	}
	_sNetInfo &operator = ( _sNetInfo &sniOther )
	{
		strUserName = sniOther.strUserName;
		strPasswd = sniOther.strPasswd;
		strUDBName = sniOther.strUDBName;
		strServer = sniOther.strServer;
		strClient = sniOther.strClient;
		strClientSN = sniOther.strClientSN;
		iClientLicenses = sniOther.iClientLicenses;
		bMono = sniOther.bMono;
		return( *this );
	}
	int Load( C_File &cf )
	{
		if( !cf.IsOpen() ){
			return( !OK );
		}

		if( cf.Read( (char*) strUserName, USERNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strPasswd, PASSWORDSIZE+1 ) == OK &&
			cf.Read( (char*) strUDBName, FULLNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strServer, SERVERNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strClient, SERVERNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strClientSN, SERIALNUMBERSIZE+1 ) == OK &&
			cf.Read( &iClientLicenses, sizeof( iClientLicenses ) ) == OK &&
			cf.Read( &bMono, sizeof( bMono ) ) == OK ){
			return( OK );
		}
		return( !OK );
	}

	int Save( C_File &cf )
	{
		if( !cf.IsOpen() ){
			return( !OK );
		}

		if( cf.Write( (char*) strUserName, USERNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strPasswd, PASSWORDSIZE+1 ) == OK &&
			cf.Write( (char*) strUDBName, FULLNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strServer, SERVERNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strClient, SERVERNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strClientSN, SERIALNUMBERSIZE+1 ) == OK &&
			cf.Write( &iClientLicenses, sizeof( iClientLicenses ) ) == OK &&
			cf.Write( &bMono, sizeof( bMono ) ) == OK ){
			return( OK );
		}
		return( !OK );
	}

	int Compare( _sNetInfo *pOther, int iCompType )
	{
		if( !pOther ){
			return( 0 );
		}
		switch( iCompType ){
		case CMPBASICELEM:
			return( strClientSN == pOther->strClientSN &&
				strClient == pOther->strClient &&
				strUserName == pOther->strUserName ? 0 : 1 );

		case CMPSERIALNUM:
			return( strClientSN == pOther->strClientSN ? 0 : 1 );

		case CMPCLIENTNAME:
			return( strClient == pOther->strClient ? 0 : 1 );

		case CMPUSERNAME:
			return( strUserName == pOther->strUserName ? 0 : 1 );

		case CMPTNIPOINTER:
			return( this == pOther ? 0 : 1 );

		}
		return( 0 );
	}
	_sNetInfo *Duplicate( void )
	{
		_sNetInfo	*pNew = new _sNetInfo( *this );
		return( pNew );
	}

}		TNetInfo;


typedef	struct	_sIndexContext {
	long		lCurrRec;
	unsigned long	ulDate;
	unsigned long	ulTime;

	_sIndexContext()
	{
		lCurrRec = 0L;
		ulDate = 0L;
		ulTime = 0L;
	}
}		TIndexContext;


typedef	struct _sBaseInfo {
	BaseSTR			strUDBName;			// nome da UDB da base
	UserSTR			strOwnerName;		// nome do usuario dono da base
	UserSTR			strLastUser;		// nome do usuario que realizou a ultima alteracao na base
	char			*szUsers;			// nomes de todos os usuarios que estao acessando a base no momento
	TMachineAddr	szServerName;		// nome do servidor onde esta' a base
	int				iNumInst;			// numero de instancias da mesma base que estao abertas no momento
	C_Date			dCreateDate;		// data de criacao da base
	C_Date			dLastModifyDate;	// data da ultima alteracao da base
	BYTE			bBaseType;			// tipo da base
	int				iSlotNum;			// quantidade de slots na base
	int				iCountNum;			// quantidade de contadores na base
	int				iMaxKeySize;		// tamanho maximo de uma chave no sistema de indices da base
	int				iIntPart;			// numero de digitos da parte inteira de um valor numerico
	int				iDecPart;			// numero de digitos da parte decimal de um valor numerico
	BOOL			bIsEncrypt;			// se a base eh criptografada
	BOOL			bReExport;			// se a base pode ser exportada

	BOOL IsZero()
	{
		return( strUDBName == (char*) "" &&
			strOwnerName == (char*) "" &&
			strLastUser == (char*) "" &&
			szServerName == (char*) "" &&
			iNumInst == 0 &&
			bBaseType == 0 &&
			iSlotNum == 0 &&
			iCountNum == 0 &&
			iMaxKeySize == 0 &&
			iIntPart == 0 &&
			iDecPart == 0 &&
			bIsEncrypt == 0 &&
			bReExport == 0 ? TRUE : FALSE );
	}
	_sBaseInfo()
	{
		strUDBName = "";
		strOwnerName = "";
		strLastUser = "";
		szUsers = NULL;
		szServerName = "";
		iNumInst = 0;
		dCreateDate = C_Date();
		dLastModifyDate = C_Date();
		bBaseType = 0;
		iSlotNum = 0;
		iCountNum = 0;
		iMaxKeySize = 0;
		iIntPart = 0;
		iDecPart = 0;
		bIsEncrypt = 0;
		bReExport = 0;
	}
	void Set( char *szUDBNamePar, char *szOwnerNamePar, char *szLastUserPar,
		  char *szUsersPar, char *szServerNamePar, int iNumInstPar,
		  unsigned long ulCreateDatePar, unsigned long ulLastModifyDatePar,
		  BYTE bBaseTypePar, int iSlotNumPar, int iCountNumPar, int iMaxKeySizePar,
		  int iIntPartPar, int iDecPartPar, BOOL bIsEncryptPar, BOOL bReExportPar )
	{
		strUDBName = szUDBNamePar;
		strOwnerName = szOwnerNamePar;
		strLastUser = szLastUserPar;
		szUsers = Strdup( szUsersPar );
		szServerName = szServerNamePar;
		iNumInst = iNumInstPar;
		dCreateDate = JULIANDATE( ulCreateDatePar );
		dLastModifyDate = JULIANDATE( ulLastModifyDatePar );
		bBaseType = bBaseTypePar;
		iSlotNum = iSlotNumPar;
		iCountNum = iCountNumPar;
		iMaxKeySize = iMaxKeySizePar;
		iIntPart = iIntPartPar;
		iDecPart = iDecPartPar;
		bIsEncrypt = bIsEncryptPar;
		bReExport = bReExportPar;
	}
	_sBaseInfo( char *szUDBNamePar, char *szOwnerNamePar, char *szLastUserPar,
		  char *szUsersPar, char *szServerNamePar, int iNumInstPar,
		  unsigned long ulCreateDatePar, unsigned long ulLastModifyDatePar,
		  BYTE bBaseTypePar, int iSlotNumPar, int iCountNumPar, int iMaxKeySizePar,
		  int iIntPartPar, int iDecPartPar, BOOL bIsEncryptPar, BOOL bReExportPar )
	{
		strUDBName = szUDBNamePar;
		strOwnerName = szOwnerNamePar;
		strLastUser = szLastUserPar;
		szUsers = Strdup( szUsersPar );
		szServerName = szServerNamePar;
		iNumInst = iNumInstPar;
		dCreateDate = JULIANDATE( ulCreateDatePar );
		dLastModifyDate = JULIANDATE( ulLastModifyDatePar );
		bBaseType = bBaseTypePar;
		iSlotNum = iSlotNumPar;
		iCountNum = iCountNumPar;
		iMaxKeySize = iMaxKeySizePar;
		iIntPart = iIntPartPar;
		iDecPart = iDecPartPar;
		bIsEncrypt = bIsEncryptPar;
		bReExport = bReExportPar;
	}
	~_sBaseInfo()
	{
		if( szUsers ){
			delete szUsers;
			szUsers = NULL;
		}
	}

}		TBaseInfo;

typedef	struct	_sLicInfo {

	SerialSTR	strSerialSvc;
	UserSTR		strUserLogged;

	struct	_sLicInfo()
	{
		strSerialSvc = "";
		strUserLogged = "";
	}
	struct	_sLicInfo( char *szSerial, char *szUser )
	{
		strSerialSvc = szSerial;
		strUserLogged = szUser;
		strUserLogged.Upper();
	}
	void	Set( char *szSerial, char *szUser )
	{
		strSerialSvc = szSerial;
		strUserLogged = szUser;
		strUserLogged.Upper();
	}
	int		Save( C_File &cf )
	{
		if( !cf.IsOpen() ){
			// arquivo fechado
			return( !OK );
		}
		if( cf.Write( (char*) strSerialSvc, SERIALNUMBERSIZE+1 ) == OK &&
			cf.Write( (char*) strUserLogged, USERNAMESIZE+1 ) == OK ){
			return( OK );
		}
		return( !OK );
	}
	int		Load( C_File &cf )
	{
		if( !cf.IsOpen() ){
			// arquivo fechado
			return( !OK );
		}
		if( cf.Read( (char*) strSerialSvc, SERIALNUMBERSIZE+1 ) == OK &&
			cf.Read( (char*) strUserLogged, USERNAMESIZE+1 ) == OK ){
			return( OK );
		}
		return( !OK );
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sLicInfo *pAux, int iType )
	{
		switch( iType ){
		case CMPSERIALNUM:
			return( pAux->strSerialSvc.StrICmp( strSerialSvc ) );
		case CMPUSERNAME:
			return( pAux->strUserLogged.StrICmp( strUserLogged ) );
		case CMPBASICELEM:
			return( (pAux->strSerialSvc.StrICmp( strSerialSvc ) == 0 ) ? 
					((pAux->strUserLogged.StrICmp( strUserLogged ) == 0 ) ? 
					0 : 1) : 1 );
		}
		return( 0 );
	}

	struct _sLicInfo	*Duplicate()
	{
		return( NULL );	
	}

}		TLicInfo;

typedef	struct	_sLicInfoRecClient {

	TMachineAddr	strClient;
	UserSTR			strUserName;
	int				iCount;

	struct	_sLicInfoRecClient()
	{
		strClient = "";
		strUserName = "";
		iCount = 0;
	}
	struct	_sLicInfoRecClient( char *szClientPar, char *szUserPar, int iCountPar )
	{
		Set( szClientPar, szUserPar, iCountPar );
	}
	void	Set( char *szClientPar, char *szUserPar, int iCountPar )
	{
		strClient = szClientPar;
		strUserName = szUserPar;
		iCount = iCountPar;
	}
}		TLicInfoRecClient;

typedef	struct	_sLicInfoRecSerial {

	SerialSTR	strSerialSvc;
	int			iNumUsedLic;

	struct	_sLicInfoRecSerial()
	{
		strSerialSvc = "";
		iNumUsedLic = 0;
	}
	struct	_sLicInfoRecSerial( char *szSerial, int iLic )
	{
		Set( szSerial, iLic );
	}
	void	Set( char *szSerial, int iLic )
	{
		strSerialSvc = szSerial;
		iNumUsedLic = iLic;
	}
}		TLicInfoRecSerial;

typedef	struct _sLicInfoFix {
//	union {
		TLicInfoRecSerial	tLicSerial;
		TLicInfoRecClient	tLicClient;
//	}
	struct	_sLicInfoFix()
	{
		memset( &tLicSerial, 0, sizeof( tLicSerial ) );
		memset( &tLicClient, 0, sizeof( tLicClient ) );
	}

}	TLicInfoFix;

typedef	struct	_sLicInfoHead {

	BOOL		bSomeMonoLog;	// alguem esta' em modo mono?
	BOOL		bCanUse;		// alguem pode usar?
	time_t		tTime;			// data/hora de criacao do arquivo
	long		lNumRec;		// numero de registros com numero de serie existentes no arquivo

	struct	_sLicInfoHead()
	{
		bSomeMonoLog = FALSE;
		bCanUse = TRUE;
		tTime = 0;
		lNumRec = 0;
	}
	struct	_sLicInfoHead( BOOL bMono, BOOL bCan, time_t tTimeAux, long lNumRecPar )
	{
		Set( bMono, bCan, tTimeAux, lNumRecPar );
	}
	void	Set( BOOL bMono, BOOL bCan, time_t tTimeAux, long lNumRecPar )
	{
		bSomeMonoLog = bMono;
		bCanUse = bCan;
		tTime = tTimeAux;
		lNumRec = lNumRecPar;
	}
}		TLicInfoFixHead;

typedef	struct	_sBaseNetInfo {

	BaseSTR		strBaseName;
	UserSTR		strUserLogged;
	BOOL		bDeleted;

	struct	_sBaseNetInfo()
	{
		strBaseName = "";
		strUserLogged = "";
		bDeleted = FALSE;
	}
	struct	_sBaseNetInfo( char *szBase, char *szUser, BOOL bDel = FALSE )
	{
		strBaseName = szBase;
		strUserLogged = szUser;
		bDeleted = bDel;

		strBaseName.Upper();
		strUserLogged.Upper();
	}
	void	Set( char *szBase, char *szUser, BOOL bDel = FALSE )
	{
		strBaseName = szBase;
		strUserLogged = szUser;
		bDeleted = bDel;

		strBaseName.Upper();
		strUserLogged.Upper();
	}
	int		Save( C_File &cf )
	{
		if( !cf.IsOpen() ){
			// arquivo fechado
			return( !OK );
		}
		if( cf.Write( (char*) strBaseName, FULLNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strUserLogged, USERNAMESIZE+1 ) == OK &&
			cf.Write( &bDeleted, sizeof( bDeleted ) == OK ) ){
			return( OK );
		}
		return( !OK );
	}
	int		Load( C_File &cf )
	{
		if( !cf.IsOpen() ){
			// arquivo fechado
			return( !OK );
		}
		if( cf.Read( (char*) strBaseName, FULLNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strUserLogged, USERNAMESIZE+1 ) == OK &&
			cf.Read( &bDeleted, sizeof( bDeleted ) == OK ) ){
			return( OK );
		}
		return( !OK );
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sBaseNetInfo *pAux, int iType )
	{
		switch( iType ){
		case CMPBASENAME:
			return( pAux->strBaseName.StrICmp( strBaseName ) );
		case CMPUSERNAME:
			return( pAux->strUserLogged.StrICmp( strUserLogged ) );
		case CMPBASICELEM:
			return( (pAux->strBaseName.StrICmp( strBaseName ) == 0 ) ? 
					((pAux->strUserLogged.StrICmp( strUserLogged ) == 0 ) ? 
					0 : 1) : 1 );
		}
		return( 0 );
	}

	struct _sBaseNetInfo	*Duplicate()
	{
		return( NULL );	
	}

}		TBaseNetInfo;


typedef struct _sAppUserNetInfo {
public:
	UserSTR				strUserName;
	LBSC_AppNetInfoList	*pclAppInfo;

	_sAppUserNetInfo()
	{
		Reset();
		pclAppInfo = New_LBSC_AppNetInfoList();
	}

	~_sAppUserNetInfo()
	{
		if( pclAppInfo ){
			Delete_LBSC_AppNetInfoList( pclAppInfo );
		}
	}

	void Reset()
	{
		strUserName = (char*) "";
		pclAppInfo = NULL;
	}

	BOOL	IsZero(){
		return( strUserName == (char*) "" &&
			pclAppInfo == NULL ? TRUE : FALSE );
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sAppUserNetInfo *pAux, int iType )
	{
		if( !pAux ){
			return( 1 );
		}
		switch( iType ){
		case CMPUSERNAME:
			return( strUserName == pAux->strUserName ? 0 : 1 );
		}
		return( 0 );
	}

	struct _sAppUserNetInfo *Duplicate()
	{
		_sAppUserNetInfo	*pOther = new _sAppUserNetInfo;

		if( pOther ){
			pOther->strUserName = strUserName;
			Equal_LBSC_AppNetInfoList( pOther->pclAppInfo, pclAppInfo );
		}
		return( pOther );	
	}

} TAppUserNetInfo;

typedef struct _sAppNetInfo {
public:
	FullSTR						strAppName;
	TMachineAddr				strMachineName;
	long						lAppId;
	time_t						tEntryAccess;
	LBSC_AppSessionNetInfoList	*pclSessionInfo;

	_sAppNetInfo()
	{
		Reset();
		pclSessionInfo = New_LBSC_AppSessionNetInfoList();
	}

	~_sAppNetInfo()
	{
		if( pclSessionInfo ){
			Delete_LBSC_AppSessionNetInfoList( pclSessionInfo );
		}
	}

	void Reset()
	{
		strAppName = (char*) "";
		strMachineName = (char*) "";
		pclSessionInfo = NULL;
		tEntryAccess = lAppId = 0;
	}

	BOOL	IsZero(){
		return( strAppName == (char*) "" &&
			strMachineName == (char*) "" &&
			pclSessionInfo == NULL ? TRUE : FALSE );
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sAppNetInfo *pAux, int iType )
	{
		if( !pAux ){
			return( 1 );
		}
		return( strAppName == pAux->strAppName &&
				strMachineName == pAux->strMachineName &&
				lAppId == pAux->lAppId ? 0 : 1 );
	}

	struct _sAppNetInfo *Duplicate()
	{
		_sAppNetInfo	*pOther = new _sAppNetInfo;

		if( pOther ){
			pOther->strAppName = strAppName;
			pOther->strMachineName = strMachineName;
			pOther->lAppId = lAppId;
			pOther->tEntryAccess = tEntryAccess;
			Equal_LBSC_AppSessionNetInfoList( pOther->pclSessionInfo, pclSessionInfo );
		}
		return( pOther );	
	}

} TAppNetInfo;


typedef struct _sAppSessionNetInfo {
private:
	LBSC_Session			*pSession;
public:
	LBSC_AppBaseNetInfoList	*pclBaseInfo;

	_sAppSessionNetInfo()
	{
		Reset();
		pclBaseInfo = New_LBSC_AppBaseNetInfoList();
	}

	~_sAppSessionNetInfo()
	{
		if( pclBaseInfo ){
			Delete_LBSC_AppBaseNetInfoList( pclBaseInfo );
		}
	}

	BOOL	IsZero(){
		return( pSession == NULL && 
			pclBaseInfo == NULL ? TRUE : FALSE );
	}

	BOOL	IsSessionPt( LBSC_Session *pSessionPar )
	{
		return( pSession == pSessionPar );
	}

	void SetSessionPt( LBSC_Session *pSessionPar )
	{
		pSession = pSessionPar;
	}

	unsigned long GetSessionPt()
	{
		return (unsigned long)pSession;
	}

	void Reset()
	{
		pSession = NULL;
		pclBaseInfo = NULL;
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sAppSessionNetInfo *pAux, int iType )
	{
		if( !pAux ){
			return( 1 );
		}
		return( pSession == pAux->pSession ? 0 : 1 );
	}

	struct _sAppSessionNetInfo *Duplicate()
	{
		_sAppSessionNetInfo	*pOther = new _sAppSessionNetInfo;

		if( pOther ){
			pOther->pSession = pSession;
			Equal_LBSC_AppBaseNetInfoList( pOther->pclBaseInfo, pclBaseInfo );
		}
		return( pOther );	
	}

} TAppSessionNetInfo;

typedef struct _sAppBaseNetInfo {
public:
	FullSTR					strBaseLongName;
	BaseSTR					strBaseAliasName;
	long					lCurrRecord;
	BOOL					bRecLocked;
	long					lBaseId;

	_sAppBaseNetInfo()
	{
		Reset();
	}

	BOOL	IsZero()
	{
		return( strBaseLongName == (char*) "" &&
			strBaseAliasName == (char*) "" &&
			lCurrRecord == 0L &&
			lBaseId == 0L &&
			bRecLocked == FALSE ? TRUE : FALSE );
	}

	void Reset()
	{
		lBaseId = 0L;
		strBaseLongName = (char*) "";
		strBaseAliasName = (char*) "";
		lCurrRecord = 0L;
		bRecLocked = FALSE;
	}

	// metodos exigidos para formacao de lista encadeada
	int	Compare( struct _sAppBaseNetInfo *pAux, int iType )
	{
		if( !pAux ){
			return( 1 );
		}
		return(	lBaseId == pAux->lBaseId ? 0 : 1 );
	}

	struct _sAppBaseNetInfo *Duplicate()
	{
		_sAppBaseNetInfo	*pOther = new _sAppBaseNetInfo;

		if( pOther ){
			pOther->strBaseLongName = strBaseLongName;
			pOther->strBaseAliasName = strBaseAliasName;
			pOther->lCurrRecord = lCurrRecord;
			pOther->bRecLocked = bRecLocked;
			pOther->lBaseId = lBaseId;
		}
		return( pOther );	
	}

} TAppBaseNetInfo;


typedef	struct _sClientInfo {
	UserSTR			strUserName;
	TMachineAddr	strClient;
	int				iCount;

	BOOL IsZero()
	{
		return( strUserName == (char*) "" &&
			strClient == (char*) "" &&
			iCount == 0 ? TRUE : FALSE );
	}

	_sClientInfo()
	{
		strUserName = "";
		strClient = "";
		iCount = 0;
	}
	void Set( char *szName, char *szClient, int iCountPar = 1 )
	{
		strUserName = szName;
		strClient = szClient;
		iCount = iCountPar;
	}
	_sClientInfo( char *szName, char *szClient, int iCountPar = 1 )
	{
		Set( szName, szClient, iCountPar );
	}
	_sClientInfo( _sClientInfo &sniOther )
	{
		strUserName = sniOther.strUserName;
		strClient = sniOther.strClient;
		iCount = sniOther.iCount;
	}
	_sClientInfo &operator = ( _sClientInfo &sniOther )
	{
		strUserName = sniOther.strUserName;
		strClient = sniOther.strClient;
		iCount = sniOther.iCount;
		return( *this );
	}
	int Load( C_File &cf )
	{
		if( !cf.IsOpen() ){
			return( !OK );
		}

		if( cf.Read( (char*) strUserName, USERNAMESIZE+1 ) == OK &&
			cf.Read( (char*) strClient, SERVERNAMESIZE+1 ) == OK &&
			cf.Read( &iCount, sizeof( iCount ) ) == OK ){
			return( OK );
		}
		return( !OK );
	}

	int Save( C_File &cf )
	{
		if( !cf.IsOpen() ){
			return( !OK );
		}

		if( cf.Write( (char*) strUserName, USERNAMESIZE+1 ) == OK &&
			cf.Write( (char*) strClient, SERVERNAMESIZE+1 ) == OK &&
			cf.Write( &iCount, sizeof( iCount ) ) == OK ){
			return( OK );
		}
		return( !OK );
	}

	int Compare( _sClientInfo *pOther, int iCompType )
	{
		if( !pOther ){
			return( 0 );
		}
		return( (strUserName == pOther->strUserName) &&
				(strClient == pOther->strClient) ? 0 : 1 );
	}
	_sClientInfo *Duplicate( void )
	{
		_sClientInfo	*pNew = new _sClientInfo( *this );
		return( pNew );
	}

}	TClientInfo;


typedef struct _sSlotCacheInfo
{
	UINT	uiId;				// id do campo	
	int		iSize;				// tamanho do buffer de slot
	char	*pBuff;				// buffer com o conteudo do slot

	_sSlotCacheInfo()
	{
		uiId = 0;
		iSize = 0;
		pBuff = NULL;
	}

	~_sSlotCacheInfo()
	{
		if( pBuff ){
			delete pBuff;
		}
	}

} TSlotCacheInfo;

typedef struct _sSlotCache
{
	int				iNumberOfFieldSlots;		// numero de slots
	TSlotCacheInfo	*pSlots;					// ponteiro para os slots

	_sSlotCache()
	{
		iNumberOfFieldSlots = 0;
		pSlots = NULL;
	}

	~_sSlotCache()
	{
		if( pSlots ){
//			if( iNumberOfFieldSlots > 1 ){
				delete [] pSlots;
//			} else {
//				delete pSlots;
//			}
		}
	}


} TSlotCache;


// estrutura que veio do criador, para controle de grupos
// de campos multivalorados.
typedef struct _CB_Grupos{
#ifdef _AFXDLL
	CString							sGrupo;			// Nome do grupo
#else
	CL_StringN<FIELDGROUPNAMESIZE>	sGrupo;
#endif
	int								iGrupo;			// Numero do grupo
	int								iSort;			// Numero de ordenacao

	struct _CB_Grupos()
	{
		Limpa();
	}

	public:

	int	Compare( struct _CB_Grupos *pcbgrupos, int iType )
	{
		// por enquanto não tem nada a ser comparado.
		if( pcbgrupos ){
			switch( iType ){
			case CMP_GRUPO:
				// comparar o numero do grupo
				return( iGrupo == pcbgrupos->iGrupo ? 0 : 1 );
			default:
				return( 1 );
			}
		}
		return( 0 );
	}

	struct _CB_Grupos	*Duplicate()
	{
		struct _CB_Grupos *novo = new _CB_Grupos;
		novo->sGrupo = sGrupo;
		novo->iGrupo = iGrupo;
		novo->iSort  = iSort;
		return( novo );	
	}

	void Limpa ()
	{
#ifdef _AFXDLL
		sGrupo = _T("");
#else
		sGrupo = "";
#endif
		iGrupo = 1;
		iSort  = -1;
	}

	// retorna o tamanho maximo que esta estrutura pode conter
	static int	GetMaxSize()
	{
		return( FIELDGROUPNAMESIZE +	// tam. max. sGrupo
				sizeof( int ) +
				sizeof( int ) );
	}

	// serializa esta estrutura em um buffer da classe C_Buffer
	// e retorna o numero de bytes que foram utilizados na
	// serializacao.
	int	Serialize( C_Buffer &cbBuf )
	{
		int	iSize = 0;

#ifdef _AFXDLL
		cbBuf.PutData( (char*) (LPCTSTR) sGrupo );
		iSize += sGrupo.GetLength();
#else
		cbBuf.PutData( (char*) sGrupo );
		iSize += strlen( (char*) sGrupo );
#endif

		cbBuf.PutData( &iGrupo );
		iSize += sizeof( iGrupo );

		cbBuf.PutData( &iSort );
		iSize += sizeof( iSort );

		return( iSize );
	}


	// desserializa esta estrutura de um buffer da classe C_Buffer
	// e retorna o numero de bytes que foram utilizados.
	int	Unserialize( C_Buffer &cbBuf )
	{
		int		iSize = 0;
		char	szGrupo[ FIELDGROUPNAMESIZE + 1 ];

		cbBuf.GetData( (char*) szGrupo );
		sGrupo = szGrupo;
#ifdef _AFXDLL
		iSize += sGrupo.GetLength();
#else
		iSize += strlen( (char*) sGrupo );
#endif
		cbBuf.GetData( &iGrupo );
		iSize += sizeof( iGrupo );

		cbBuf.GetData( &iSort );
		iSize += sizeof( iSort );

		return( iSize );
	}


}			CB_Grupos;

typedef struct _sUserUDBInfo
{
	CL_StringN<FULLNAMESIZE>	szUDB;				// udb
	int							iType;				// tipo do usuario na udb
	BOOL						bOldUser;			// indica um usuario cuja senha deve ser corrigida (bug da senha no cliente/servidor)

public:
	_sUserUDBInfo()
	{
		szUDB = "";
		iType = NOP_USER;
		bOldUser = FALSE;
	}
} TUserUDBInfo;

typedef struct _sUserCacheInfo
{
public:
	CL_StringN<USERNAMESIZE> szName;			// nome do usuario
	CL_StringN<PASSWORDSIZE> szPwd;				// password do usuario
	TUserUDBInfo			 tUDBInfo;

	_sUserCacheInfo()
	{
		szName = "";
		szPwd = "";
	}

	struct _sUserCacheInfo &operator = ( struct _sUserCacheInfo &sOther )
	{
		szName = sOther.szName;
		szPwd = sOther.szPwd;
		tUDBInfo = sOther.tUDBInfo;
		return (*this);
	}
} TUserCacheInfo;

#endif	// _LBSTYPES_H_


