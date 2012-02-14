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
#include <baseinstance.h>
#include <olsort.h>

#define	COMPRESSED_STATUS		0x01
#define	NOTCOMPRESSED_STATUS	0x00
#define	MINIMAL_COMPRESS_SIZE	(512)


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

// IMPORTANTE:
// O objeto GLT_Session eh definido automaticamente pela API Light Text e eh
// usado para inicializar algumas coisas assim que este codigo entra no ar.
// Tambem eh usado para manipular sistemas de indices.
// O arquivo lt.h o declara.


// Prototypes
extern	void	Printf( char *, ... );

// Global variables

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

#ifdef __BORLANDC__
#pragma warn -par
#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo LBSC_Base
	Construtor da classe LBSC_Base

	Parameters:
	- bMagic : Numero mágico incial da base.

	Return:

	Comments:

***/

LBSC_Base::LBSC_Base( ) :
	C_LeaveCritSect<C_GlobalBaseCritSect>( _pcGlobalBaseCritSect ),
	lbscrCurrRecord( this ),
	lbscpParser( this ),
	epEntParser( this )
{
	Init();
}

/***
	PUBLIC
	Metodo ~LBSC_Base
	Destrutor da classe LBSC_Base

	Parameters:

	Return:

	Comments:

***/ 
LBSC_Base::~LBSC_Base()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char szAux[ FULLNAMESIZE ];
	memset( szAux, 0, FULLNAMESIZE );

	Close();
	if( bIsExclusive ){	// matar cache sempre q estiver em mono ou modo exclusivo
		InvalidateCache();
		LBSC_Session::InvalidateCacheInSubDirs( szBasePath );
	}
	if( bSelfDelete ){
		// deletar fisicamente os arquivos
		sprintf( szAux, "%s\\%s", (char *)szBasePath, (char *)szBaseName );
		RemoveDir( szBasePath, TRUE );
	}

	bBaseObjOk = FALSE;
	bBaseUpdated = FALSE;
	if( pltcMaskList ){
		delete pltcMaskList;
	}
	if( pltcPhone ){
		delete pltcPhone;
	}
	if( pltcSynonym ){
		delete pltcSynonym;
	}
	if( pcOLList ){
		delete pcOLList;  
	}
	if( szStdArray ){
		delete szStdArray;
	}
	if( pltctlStopWordList ){
		delete pltctlStopWordList;
		pltctlStopWordList = NULL;
	}

//	GeraLog();
}


/***
	PUBLIC
	Metodo SetLockTimeOut
	Modifica o tempo de "lock" de um registro

	Parameters:
		- lbscTicket
		- iNewTimeOut

	Return:
		LBS_OK se conseguir modificar o tempo de "lock" ou erro.

	Comments:

***/
int
LBSC_Base::SetLockTimeOut( const LBSC_Ticket *lbscTicket, int iNewTimeOut )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetLockTimeOut") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( iNewTimeOut > 0 ){
		iLockTimeOut = iNewTimeOut;
		if( lbscrCurrRecord.IsLocked() ){
			return( ResetLockElapsedTime() );
		}
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_BADARG );
}


/***
	PUBLIC
	Metodo SetReorganizeRecQuant
	Modifica o numero de registros deletados para reorganizacao da base

	Parameters:
		- lbscTicket
		- lNewRecQuant

	Return:
		- LBS_OK se conseguir modificar o numero de registros ou erro.

	Comments:
		- Se o parametro lNewRecQuant for 0 (zero) entao a reorganizacao
		  automatica eh desligada ateh que este metodo seja chamado
		  novamente com um numero maior que zero.

***/
int
LBSC_Base::SetReorganizeRecQuant( const LBSC_Ticket *lbscTicket, long lNewRecQuant )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetReorganizeRecQuant") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( lNewRecQuant >= 0 ){
		if ( pBaseInstance && pBaseInstance->DataFileLoaded() ) {

			// a regiao critica abaixo protege toda a operacao de atualizacao de registro
			CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );

			// criar objeto para fazer lock do header de LB1. 
			// O destrutor faz o Release.
			LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

			if( !cLB1_LockHead.IsLocked() ){
				// nao consegui travar o header de LB1
				ERETURN( LBSE_HEADERROR );
			}

			LB1.tcrHead.lDeletedRecNumReorg = lNewRecQuant;
			LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
			LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
			LB1.LB1_WriteHead();
		}

		bBaseUpdated = TRUE;

		bSelfReorganize = ( lNewRecQuant == 0 ) ? FALSE : TRUE;
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_BADARG );
}


/***
	PUBLIC
	Metodo ModifyPassword
	Modifica a password da base

	Parameters:
		- lbscTicket	-> ticket de seguranca
		- szOldPassword	-> password corrente
		- szNewPassword -> nova password

	Return:
		- LBS_OK se conseguir modificar a password ou erro.

	Comments:
		- Nao pede confirmacao.
		- Este metodo so' pode ser usado se a base estiver aberta em
		  modo exclusivo
***/
int
LBSC_Base::ModifyPassword( const LBSC_Ticket *lbscTicket, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyPassword") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}
	// testar se a base esta' em modo exclusivo
	if( !bIsExclusive ){
		// nao esta'
		ERETURN( LBSE_BASENOTEXCLUSIVE );
	}

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( !cLB1_LockHead.IsLocked() ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}

		// Checar password (apenas se o cara logado nao for o dono da base)
		if( LB1.tcrHead.szOwnerName != (char*) plbscsOwnerSession->GetUserName() ){
			// Nao eh o dono da base que estah logado
			if( plbscsOwnerSession->plbscuUser->GetUserType() != MASTER_USER ){
				// tambem nao eh super-usuario
				if( !bFullAccess ){
					// a base nao esta' aberta para manutencao.
					if( LB1.tcrHead.szBasePassword != strupr( szOldPassword ) ){
						ERETURN( LBSE_INVALIDPASSWORD );
					}
				}
			}
		}

		CL_StringN<BASEPASSWORDSIZE>	szBkp;

		szBkp = LB1.tcrHead.szMaintenancePassword;
		LB1.tcrHead.szBasePassword = strupr( szNewPassword );
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();

		if( cLB1_LockHead.LB1_ReleaseHead() != OK ){
			LB1.tcrHead.szBasePassword = szBkp;
			ERETURN( LBSE_ERROR );
		}
	}
	ERETURN( LBS_OK );
}

/***
	PUBLIC
	Metodo ModifyRecordPassword
	Modifica a password do registro corrente da base

	Parameters:
		- lbscTicket;
                - szOldPassword;
		- szNewPassword.

	Return:
		LBS_OK se conseguir modificar a password do registro
		corrente ou erro.

	Comments:
		- Nao pede confirmacao.

***/
int
LBSC_Base::ModifyRecordPassword( const LBSC_Ticket *lbscTicket, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyRecordPassword") );

	ERETURN( LBSE_ERROR );	// nao implementado
}

/***
	PUBLIC
	Metodo ModifyMaintenancePassword
	Modifica a password de manutencao da base.

	Parameters:
		- lbscTicket
		- szOldPassword
                - szNewPassword

	Return:
		- LBS_OK se conseguir ou erro caso contrario.

	Comments:
		- Se o usuario logado for o dono da base ou um MASTER, nao eh necessario indicar a
		  password antiga.
							 

***/
int
LBSC_Base::ModifyMaintenancePassword( const LBSC_Ticket *lbscTicket, char *szOldPassword, char *szNewPassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ModifyMaintenancePassword") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}

	{
		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		if( !cLB1_LockHead.IsLocked() ){
			// nao consegui travar o header de LB1
			ERETURN( LBSE_HEADERROR );
		}
		// verificar se o cara que esta' logado eh o dono da base
		if( LB1.tcrHead.szOwnerName != plbscsOwnerSession->GetUserName() ){
			// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
			if( plbscsOwnerSession->GetUserType( lbscTicket, (char*) LB1.tcrHead.szUserBase, (char*) plbscsOwnerSession->GetUserName() ) != MASTER_USER ){
				// o cara tambem nao eh super usuario.
				// Entao vamos verificar se ele informou a password atual
				if( LB1.tcrHead.szMaintenancePassword != strupr( szOldPassword ) ){
					ERETURN( LBSE_INVALIDPASSWORD );
				}
			}
		}

		CL_StringN<MAXMAINTENANCEPASS>	szMaintBkp;

		szMaintBkp = LB1.tcrHead.szMaintenancePassword;
		LB1.tcrHead.szMaintenancePassword = strupr( szNewPassword );
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();
		LB1.LB1_WriteHead();

		if( cLB1_LockHead.LB1_ReleaseHead() != OK ){
			LB1.tcrHead.szMaintenancePassword = szMaintBkp;
			ERETURN( LBSE_ERROR );
		}
	}
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo AddField
	Adiciona um campo ao formato de uma base

	Parameters:
		- szFieldAliasName	-> alias name do campo
		- szFieldDescription	-> descricao do campo
		- szPassword		-> password
		- tftFieldType		-> tipo do campo
		- lFieldSize		-> tamanho do campo
		- tiaIndexAttrib	-> maskara de bits para indexar o campo

	Return:
		- LBS_OK se conseguir adicionar ou erro.

	Comments:
		- Os novos registro da base terao o novo campo; os registros
		  ja existentes nao terao o novo campo
		- Os registros que ja existem so terao o novo campo
		  quando a base for re-estruturada

***/
int
LBSC_Base::AddField( const LBSC_Ticket *lbscTicket, char *szFieldAliasName,
		char *szFieldDescription, char *szPassword,
		TFieldType tftFieldType, long lFieldSize,
		TIndexAttrib tiaIndexAttrib, UINT uiFieldAttrib )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddField") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !bFullAccess ){
		// a base nao esta' aberta para manutencao
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}

	LBSC_Field	*plbscfField;

	if( tiaIndexAttrib & 0x00008000 ){
		// este campo contem o antigo indice ENTIRETREE.
		// vamos converter para o novo indice (versao 3.3).
		// a conversao aqui eh feita apenas em memoria. quando
		// a base for reprocessada, o arquivo LB3 serqa' corrigido.
		tiaIndexAttrib &= (~0x00008000);
		tiaIndexAttrib |= ENTIRETREE;
	}
	plbscfField = new LBSC_Field(  szFieldAliasName, szFieldDescription, szPassword,
					tftFieldType, lFieldSize, GetNewFieldId(), uiFieldAttrib,
					tiaIndexAttrib, this );
	if( !plbscfField ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( ( lbscrCurrRecord.AddField( plbscfField, TAIL ) ) == LBS_OK ){
		bBaseUpdated = TRUE;

		// FAZER O APPEND DO NOVO CAMPO EM LB3
		if( AppendLastFieldOnFile() != LBS_OK ){
			/* tirar o registro e deletar plbscfField */
			ERETURN( LBSE_ERROR );
		}

		// nao eh necessario entar em regiao critica global porque a base esta 
		// em modo exclusivo
		LB1.LB1_WriteHead();
		// gerar ACL para o dono da base neste campo
		GenerateOwnerACL();
		ERETURN( LBS_OK );
	}
	delete plbscfField;
	ERETURN( LBSE_ERROR );
}



/***
	PUBLIC
	Metodo AddField
	Adiciona um campo ao formato de uma base

	Parameters:
		- lbscTicket : o ticket de seguranca;
                - tfField : apontador para o campo a ser adicionado.

	Return:
		LBS_OK se conseguir adicionar ou erro.

	Comments:
		- O objeto LBSC_Field deve ser instanciado pela aplicacao.
		- Os novos registro da base terao o novo campo; os registros
		  ja existentes so terao o novo campo quando forem reescritos
		  (UpdateRecord)

***/
int
LBSC_Base::AddField( const LBSC_Ticket *lbscTicket, TField *tfField )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddField") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !bFullAccess ){
		// a base nao esta' aberta para manutencao
		ERETURN( LBSE_NOTFULLACCESS );
	}
	if( bIsReadOnly ){
		// a base esta' em modo readonly
		ERETURN( LBSE_BASEREADONLY );
	}
	/* So com a base aberta .FAZER ISSO */
	if( ( bBaseObjOk == FALSE ) && ( bStruct == TRUE ) ){
		ERETURN( LBSE_OBJNOTOK );
	}
	int iRet = AddField( lbscTicket, tfField->szFieldAliasName,
		tfField->szFieldDescription,
		tfField->szPasswordName,
		tfField->tftFieldType,
		tfField->lFieldSize,
		//tfField->uiFieldId,
		tfField->tiaIndexAttrib,
		tfField->uiFieldAttrib );
	ERETURN( iRet );
}


/***
	PUBLIC
	Metodo CurrentRecord
	Obtem o registro corrente da base, que ja estah em memoria

	Parameters:
        	- lbscTicket : ticket de seguranca.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:

***/
int
LBSC_Base::CurrentRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CurrentRecord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( ( bBaseObjOk == FALSE ) || ( lbscrCurrRecord.IsUndefined() ) ){
		ERETURN( LBSE_ERROR );
	}
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo CurrRecStatus
	Obtem o status do registro corrente

	Parameters:
		- lbscTicket : ticket de seguranca

	Return:
		- status do registro corrente

	Comments:
		-

***/
BYTE
LBSC_Base::CurrRecStatus( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CurrRecStatus") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( (BYTE) LBSE_TICKETNOTOK );
	}
	SetError( LBS_OK );
	return( lbscrCurrRecord.GetStatus() );
}



/***
	PUBLIC
	Metodo CurrRecNum
	Retorna o numero de ordem do registro corrente.

	Parameters:
		- lbscTicket : ticket de seguranca

	Return:
		- o numero de ordem do registro corrente ou um erro.

	Comments:
		- O numero de ordem do registro corrente eh calculado
		  em funcao da posicao corrente do arquivo de controle
		  (LB1).

***/
long
LBSC_Base::CurrRecNum( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::CurrRecNum") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	SetError( LBS_OK );
	return( LB1.R_CurPos() );
}




/***
	PUBLIC
	Metodo UpdateRecord
	Escreve o registro corrente na base

	Parameters:

	Return:
		LBS_OK se conseguir escrever o registro ou erro.

	Comments:
		- Nao altera o registro corrente.

***/
int
LBSC_Base::UpdateRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateRecord 1 %s %s", "Base", (char *)szBasePath) );

#ifdef LBS_DEBUG
	Printf( "UpdateRecord" );
#endif // LBS_DEBUG

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);	// TEM QUE SER DECLARADO AQUI SOB RISCO DE DEADLOCK

	TControlRec			tcrControlRec;

	if ( !pBaseInstance || !pBaseInstance->DataFileLoaded() ) {
		ERETURN( LBSE_BASENOTOPEN );	
	}

	// a regiao critica abaixo protege toda a operacao de
	// atualizacao do registro
	CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );
	CPageFile *pDataFile = pBaseInstance->GetDataFile();

	{
		if( _bInvalidLicence ){
			// a licenca em uso foi invalidada por outra aplicacao.
			// devemos sair do ar e retornar para que o LBS revalide
			// a licenca.
			ERETURN( LBSE_INVALIDLIC );
		}

		if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
			ERETURN( LBSE_TICKETNOTOK );
		}

		// se a base estiver aberta para manutencao, entao
		// nao permitiremos que o usuario manipule dados
		if( bFullAccess ){
			ERETURN( LBSE_MAINTMODE );
		}
		if( bIsReadOnly ){
			ERETURN( LBSE_BASEREADONLY );
		}

		PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateRecord_VerificaStatus") );
		if( !bFastRec ){
			if( !( lbscrCurrRecord.GetStatus() & REC_LOCKED ) ){
				ERETURN( LBSE_RECORDNOTLOCKED );
			}
		}

		PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateRecord_VerificaLB1Open") );
		if( !LB1.IsOpen() ){
			ERETURN( LBSE_BASENOTOPEN );	// Base fechada
		}

		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateRecord_LockLB1Header") );

		if( !bAppendingRec && LB1.tcrHead.lNumRecords == 0 ){
			ERETURN( LBSE_ERROR );
		}
		if( bBaseObjOk == FALSE ){
			ERETURN( LBSE_OBJNOTOK );
		}
		// se nenhum campo estiver modificado, retornar OK
		int	iNumFields = GetNumberOfFields();
		for(int i = 0; i < iNumFields; i ++ ){
			LBSC_Field	*pf = lbscrCurrRecord[ i ];

			if( pf && pf->bFlagUpdate ){
				break;
			}
		}
		if( i == iNumFields ){
			ERETURN( LBS_OK );
		}

		if( !bAppendingRec ){
			// verificar se ha' algum campo que deve
			// ser indexado pelo indice de chave-unica e, para esse campo,
			// checar a unicidade da chave no sistema de indices.
			int iUKey = CheckUniqueKey();
			if( iUKey != LBS_OK ){
				return( iUKey );
			}

			// Checar permissoes de ACL
			if( VerifyPermission( plbscsOwnerSession->GetUserName(), ID_ASTERISK, 
						USERFIELD, ACL_WRITE ) != LBS_OK ){
				ERETURN( LBSE_NOPERMISSION );
			}
		}

		lbscrCurrRecord.SetIsUndefined( FALSE );

		// Se a indexacao on-line estiver desligada,
		// devemos jogar o registro em um arquivo de log
		// para depois indexa-lo sob pedido da aplicacao.
		if( !LB1.tcrHead.bOnLineIndex ){
			// jogar registro no arquivo de log
			WriteRecordInLogFile( lbscTicket );
			lbscrCurrRecord.bStatus |= REC_INLOGFILE;
		} else {
			lbscrCurrRecord.bStatus &= ~REC_INLOGFILE;
		}
		lbscrCurrRecord.bStatus &= ~REC_INDEXED; // Desliga flag de indexacao
		lbscrCurrRecord.bStatus &= ~REC_UPDATED; // Desliga flag de atualizacao
		lbscrCurrRecord.szLastUpdateUserName = (char*) plbscsOwnerSession->GetUserName();
		lbscrCurrRecord.cdLastUpdateDate = C_Date();
		lbscrCurrRecord.ulAccess++;

		if( LB1.R_Read( &tcrControlRec ) != OK ){
			lbscrCurrRecord.SetIsUndefined( TRUE );
			ERETURN( LBSE_ERROR );
		}

		FAU fCurLB4Pos = tcrControlRec.fContentPos;
		FAU fDeleteLB4Pos = 0;

		// tratar os campos ordenaveis
		SortFields();

		tcrControlRec.ulModifyDate = lbscrCurrRecord.cdLastUpdateDate.Hash();
		tcrControlRec.bRecStatus = lbscrCurrRecord.bStatus;
		tcrControlRec.bRecStatus &= ~REC_LOCKED;
		tcrControlRec.szLastModifyUserName = lbscrCurrRecord.szLastUpdateUserName;
		tcrControlRec.ulAccess = lbscrCurrRecord.ulAccess;

		long lRecordSize = 0;
		long lSuggestedPageSize = 0;

		C_Buffer *pBuf = NULL;
		if ( !GetRecordBuffer( &pBuf, &lRecordSize, &lSuggestedPageSize) ) {
			lbscrCurrRecord.SetIsUndefined( TRUE );
			ERETURN( LBSE_NOMEMORY );
		}

		if ( tcrControlRec.fContentPos == (FAU)0 || pDataFile->PageSize(tcrControlRec.fContentPos) < lSuggestedPageSize ) {
			fDeleteLB4Pos = fCurLB4Pos;
			tcrControlRec.fContentPos = pDataFile->GetFreePage( lSuggestedPageSize );
		}

		if ( !pDataFile->WritePage( pBuf->MyBuffer(), lRecordSize, tcrControlRec.fContentPos ) ) {
			delete pBuf;
			lbscrCurrRecord.SetIsUndefined( TRUE );
			ERETURN( LBSE_FATAL );
		}
		delete pBuf;
		pBuf = NULL;

		if( LB1.R_Write( &tcrControlRec ) != OK ){
			/* decidir a recuperacao */
			lbscrCurrRecord.SetIsUndefined( TRUE );
			ERETURN( LBSE_FATAL );
		}

		{
			// esse objeto TEM que ser declarado depois das regioes criticas
			// acima, ou ocorre risco de deadlock
			LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

			if( LB1.tcrHead.lFirstRecActivePos == -1 ){
				// $$$ primeiro registro foi gravado
				LB1.tcrHead.lFirstRecActivePos = LB1.tcrHead.lLastRecPos = LB1.tcrHead.lLastRecActivePos = LB1.R_CurPos();
			} else {
				if( LB1.R_CurPos() > LB1.tcrHead.lLastRecActivePos ){
					LB1.tcrHead.lLastRecActivePos = LB1.tcrHead.lLastRecPos = LB1.R_CurPos();
				}
			}

			LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
			LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();

			// agora grava o header...
			LB1.LB1_WriteHead();
		}

		bBaseUpdated = TRUE;

		/* ******************Vou desalocar o espaco ocupado em LB2 e LB4 */

		if ( fDeleteLB4Pos != (FAU)0 ) {
			pDataFile->FreePage( fDeleteLB4Pos );
		}

		// fazer flush dos dados
		if( !bFastRec ){
			LB1.Flush();
			pDataFile->Flush();
		}
	}

	if( LB1.tcrHead.bOnLineIndex ){
		// Desindexa os dados atuais
		if( !bAppendingRec ){
			Unindex( lbscTicket, PARTIAL_INDEX );
		}

		// Indexa o registro
		Index( lbscTicket, PARTIAL_INDEX );
		if ( !bFastRec ) {	
			// indexando registro a registro com bufferizacao desligada
			FlushIndexSystem();
		}
	}

	if( !bAppendingRec ){
		LOGUSE( UPDATE_RECORD, LB1.R_CurPos() + 1 ); // LB1.R_CurPos() retorna zero como posicao inicial 
	}

	// atualizar o flag de alteracao de todos os campos
	for(int i = 0; i < GetNumberOfFields(); i ++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];

		if( pf ){
			pf->UpdateFieldFlag( FALSE );
			pf->bMustFillOriginalDataList = TRUE;
			pf->lbscdlOriginalDataList.DelAll();
		}
	}

	// ok.
	PRINTLOG( _clLBSLog, ("LBSC_Base::UpdateRecord_ReturnOK") );
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo AppendRecord
	Adiciona o registro corrente na base

	Parameters:
        	- lbscTicket : ticket de seguranca.

	Return:
		- LBS_OK se conseguir adicionar o registro ou erro.

	Comments:

***/
int
LBSC_Base::AppendRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AppendRecord 1 %s %s", "Base", (char *)szBasePath) );

#ifdef LBS_DEBUG
	Printf( "AppendRecord" );
#endif // LBS_DEBUG

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);		// TEM QUE SER DECLARADO AQUI SOB RISCO DE DEADLOCK

	if ( !pBaseInstance || !pBaseInstance->DataFileLoaded() ) {
		ERETURN( LBSE_BASENOTOPEN );	
	}

	// a regiao critica abaixo protege toda a operacao de
	// criacao do registro
	CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	// se a base estiver aberta para manutencao, entao
	// nao permitiremos que o usuario manipule dados
	if( bFullAccess ){
		ERETURN( LBSE_MAINTMODE );
	}
	if( bIsReadOnly ){
		ERETURN( LBSE_BASEREADONLY );
	}

	PRINTLOG( _clLBSLog, ("LBSC_Base::AppendRecord_VerificaLB1Open") );

	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}


	// antes de tudo, vamos verificar se ha' algum campo que deve
	// ser indexado pelo indice de chave-unica e, para esse campo,
	// checar a unicidade da chave no sistema de indices.
	bAppendingRec = TRUE;
	int iUKey = CheckUniqueKey();
	bAppendingRec = FALSE;
	if( iUKey != LBS_OK ){
		return( iUKey );
	}

	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), ID_BASE, 
				USERBASE, ACL_APPEND ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	TControlRec	tcrControlRec;
	long 		lControlPos = LB1.R_CurPos();

	lbscrCurrRecord.szOwnerName = (char*) plbscsOwnerSession->GetUserName();
	lbscrCurrRecord.szLastUpdateUserName = (char*) plbscsOwnerSession->GetUserName();
	lbscrCurrRecord.cdCreateDate = C_Date();
	lbscrCurrRecord.cdLastUpdateDate = C_Date();
	lbscrCurrRecord.ulAccess = 0L;
	lbscrCurrRecord.bStatus = 0;

	tcrControlRec.ulCreateDate = lbscrCurrRecord.cdCreateDate.Hash();
	tcrControlRec.fContentPos = 0L;
	tcrControlRec.szOwnerName = lbscrCurrRecord.szOwnerName;
	tcrControlRec.ulAccess = 0L;
	tcrControlRec.bRecStatus = 0;

	if( LB1.R_Append( &tcrControlRec ) != OK ){
		if( LB1.R_Seek( lControlPos ) == OK ){
			ReadRecord( lbscTicket );
		}
		ERETURN( LBSE_ERROR );
	}

	int	iRet = LBS_OK;
	if( !bFastRec ){
		iRet = LockRecord( lbscTicket );
	}
	if( iRet != LBS_OK ){
		LB1.R_UndoLastAppend();
		if( LB1.R_Seek( lControlPos ) == OK ){
			ReadRecord( lbscTicket );
		}
		ERETURN( iRet );
	}

	// forcar a barra para que todos os campos sejam gravados
	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];

		if( pf ){
			pf->UpdateFieldFlag( TRUE );
		}
	}

	// liga flag para indicar ao metodo UpdateRecord que o registro esta' sendo
	// adicionado (append) e nao apenas atualizado
	bAppendingRec = TRUE;
	if( (iRet = UpdateRecord( lbscTicket )) != LBS_OK ){
		bAppendingRec = FALSE;
		LB1.R_UndoLastAppend();
		ERETURN( iRet );
	}
	bAppendingRec = FALSE;

	{
		// esse objeto TEM que ser declarado depois das regioes criticas
		// acima, ou ocorre risco de deadlock
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		LB1.tcrHead.lNumRecords++;
		iRet = LB1.LB1_WriteHead();
		if( iRet != OK ){
			// fudeu!!! Muito estranho!
			if( iRet != E_NEWHEAD ){
				LB1.tcrHead.lNumRecords--;
			}
			LB1.R_UndoLastAppend();
			ERETURN( LBSE_HEADERROR );
		}
	}

	if( !bFastRec ){
		ReleaseRecord( lbscTicket );
	}

	LOGUSE( APPEND_RECORD, LB1.R_CurPos() + 1); // LB1.R_CurPos() retorna zero como posicao inicial

	bBaseUpdated = TRUE;
	
	PRINTLOG( _clLBSLog, ("LBSC_Base::AppendRecord_ReturnOK") );
	ERETURN( LBS_OK );
}



/***
	PUBLIC
	Metodo ReadRecord
	Le um registro da base e o torna o corrente

	Parameters:
		- lbscTicket.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		-

***/
int
LBSC_Base::ReadRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ReadRecord 1 %s %s", "Base", (char *)szBasePath) );

	BYTE				bStatus = 0;

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);		// TEM QUE SER DECLARADO AQUI SOB RISCO DE DEADLOCK

	if ( !pBaseInstance || !pBaseInstance->DataFileLoaded() ) {
		ERETURN( LBSE_BASENOTOPEN );	
	}

	// a regiao critica abaixo protege toda a operacao de
	// leitura do registro
	CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );
	CPageFile *pDataFile = pBaseInstance->GetDataFile();

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// se a base estiver aberta para manutencao, entao
	// nao permitiremos que o usuario manipule dados
	if( bFullAccess ){
		ERETURN( LBSE_MAINTMODE );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}

	TControlRec	tcrControlRec;

	lbscrCurrRecord.SetIsUndefined( TRUE );

	if( LB1.tcrHead.lNumRecords == 0 ){
		// reler o header de LB1
		if( LB1.R_ReadHead() == OK ){
			if( LB1.tcrHead.lNumRecords == 0 ){
				ERETURN( LBSE_NORECORD );
			}
			ERETURN( FirstFRecord( lbscTicket ) );
		}
		ERETURN( LBSE_HEADERROR );
	}

	if( LB1.R_Read( &tcrControlRec ) != OK ){
		DWORD	dw = C_File::Get32sVar() ? (DWORD) errno : GetLastError();
		if( (!C_File::Get32sVar() && dw == ERROR_LOCK_VIOLATION) ||	// Win95, WinNT
			(!C_File::Get32sVar() && dw == ERROR_ACCESS_DENIED) ||	// Netware
			(C_File::Get32sVar() && (int) dw == EACCES) ){			// Win32s

			// se foi erro de lock, tentar novamente, sem ler
			// a data de criacao do registro, que eh a regiao de lock.
			if( LB1.R_Read( &tcrControlRec, sizeof( unsigned long ), 
						sizeof( tcrControlRec ) - sizeof( unsigned long ) ) != OK ){
				ERETURN( LBSE_RECORDLOCKED );
			}
			tcrControlRec.ulCreateDate = 0;	// data de criacao desconhecida.
		} else {
			ERETURN( LBSE_NORECORD );
		}
	}
	tcrControlRec.bRecStatus &= ~REC_LOCKED;
	lbscrCurrRecord.bStatus = tcrControlRec.bRecStatus;

	if( tcrControlRec.bRecStatus & REC_EXCLUDED ){
		ERETURN( LBSE_EXCLUDEDREC );
	}
	if( tcrControlRec.fContentPos == (FAU)0 ){
		ERETURN( LBSE_ZERORECORD );
	}

	lbscrCurrRecord.szOwnerName = tcrControlRec.szOwnerName;
	lbscrCurrRecord.szLastUpdateUserName = tcrControlRec.szLastModifyUserName;
	lbscrCurrRecord.SetCreateDate( tcrControlRec.ulCreateDate );
	lbscrCurrRecord.SetModifyDate( tcrControlRec.ulModifyDate );
	lbscrCurrRecord.SetStatus( tcrControlRec.bRecStatus );

	// Checar permissoes de ACL
	if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ||
	    ( LB1.tcrHead.bBaseType == BASE_PRIVATE_REC_PRIVATE ) ){
	    		// a base possui restricao de registro
		if( VerifyPermission( plbscsOwnerSession->GetUserName(), CurrRecNum( lbscTicket ), 
					USERRECORD, ACL_READ ) != LBS_OK ){
			ERETURN( LBSE_NOPERMISSION );
		}
	}
	// checar se o cara logado possui permissao de leitura para pelo menos um campo da base
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), ID_ASTERISK, 
				USERFIELD, ACL_READ ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}

	lbscrCurrRecord.ulAccess = tcrControlRec.ulAccess;

	if( !LB3.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );
	}

	lbscrCurrRecord.SetIsUndefined( FALSE );
	lbscrCurrRecord.ClearReadStatusFromFields();
	lbscrCurrRecord.FreeRecordBuffers();

	LOGUSE( READ_RECORD, LB1.R_CurPos() + 1); // LB1.R_CurPos() retorna zero como posicao inicial
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DeleteRecord
	Apaga o registro corrente da base

	Parameters:
        	- lbscTicket : ticket de seguranca

	Return:
		LBS_OK se conseguir deletar o registro ou erro.

	Comments:
		- Deleta fisicamente o registro ligando o flag de delecao.
		- Nao pede confirmacao.

***/
int
LBSC_Base::DeleteRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DeleteRecord 1 %s %s", "Base", (char *)szBasePath) );

	int	iRet;

#ifdef LBS_DEBUG
	Printf( "DeleteRecord" );
#endif // LBS_DEBUG

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);		// TEM QUE SER DECLARADO AQUI SOB RISCO DE DEADLOCK

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// se a base estiver aberta para manutencao, entao
	// nao permitiremos que o usuario manipule dados
	if( bFullAccess ){
		ERETURN( LBSE_MAINTMODE );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	// Checar permissoes de ACL
	if( VerifyPermission( plbscsOwnerSession->GetUserName(), ID_BASE, 
				USERBASE, ACL_DEL ) != LBS_OK ){
		ERETURN( LBSE_NOPERMISSION );
	}
	if( lbscrCurrRecord.IsUndefined() ){
		ERETURN( LBSE_UNDEFINEDRECORD );
	}

	if ( !pBaseInstance || !pBaseInstance->DataFileLoaded() ) {
		ERETURN( LBSE_BASENOTOPEN );	
	}

	// a regiao critica abaixo protege toda a operacao de
	// delecao do registro
	CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );
	CPageFile *pDataFile = pBaseInstance->GetDataFile();

	long lCurRecNum = LB1.R_CurPos();

	// guarda informacoes do registro contidas em LB1
	TControlRec	tcrControlRec;
	if( LB1.R_Read( &tcrControlRec ) != OK ){
		ERETURN( LBSE_ERROR );
	}
	// verifica se o registro ja' esta' deletado
	if( tcrControlRec.bRecStatus & REC_EXCLUDED ){
		// o registro ja' esta' deletado.
		// seta-lo como indefinido e retornar erro.
		lbscrCurrRecord.SetIsUndefined( TRUE );
		lbscrCurrRecord.bStatus |= REC_EXCLUDED;
		ERETURN( LBSE_EXCLUDEDREC );
	}
	// forcar a barra para que todos os campos sejam 
	// liberados e desindexados
	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i ++ ){
		LBSC_Field	*pf = lbscrCurrRecord[ i ];
		
		if( pf ){
			pf->UpdateFieldFlag( TRUE );
			pf->bMustFillOriginalDataList = TRUE;
			pf->FillOriginalDataList();
		}
	}

	// deleta o registro (apenas em LB1)
	if( lbscrCurrRecord.Delete( &LB1 ) == LBS_OK ){
		// fazer flush dos dados
		LB1.Flush();

		pDataFile->FreePage( tcrControlRec.fContentPos );
		pDataFile->Flush();

		if( LB1.tcrHead.bOnLineIndex ){
			// Desindexa
			Unindex( lbscTicket, PARTIAL_INDEX );
			FlushIndexSystem();
		}
		
		bBaseUpdated = TRUE;

		// criar objeto para fazer lock do header de LB1. 
		// O destrutor faz o Release.
		// esse objeto TEM que ser declarado depois das regioes criticas
		// acima, ou ocorre risco de deadlock
		LBSC_LB1_LockHead	cLB1_LockHead( LB1 );

		--LB1.tcrHead.lNumRecords;
		++LB1.tcrHead.lDeletedRecNum;

		// libera o lock
		ReleaseRecord( lbscTicket );

		iRet = LBS_OK;

		LOGUSE( DELETE_RECORD, lCurRecNum + 1 ); // LB1.R_CurPos() retorna zero como posicao inicial

		if( LB1.tcrHead.lNumRecords == 0 ){
			LB1.tcrHead.lFirstRecActivePos = LB1.tcrHead.lLastRecActivePos = -1;
			lbscrCurrRecord.Clear();
			lbscrCurrRecord.SetIsUndefined( TRUE );
		} else {
			if( LB1.R_CurPos() == LB1.tcrHead.lFirstRecActivePos ){
				// vai para o proximo registro (deletando a posicao corrente na LO)
				iRet = PrivNextRec( lbscTicket, TRUE );

				long lCurPos = LB1.R_CurPos();	// guarda posicao corrente

				// definir o primeiro registro da base (independe de permissoes)
				while( LB1.R_Seek( ++LB1.tcrHead.lFirstRecActivePos ) == LBS_OK ){
					if( LB1.R_Read( &tcrControlRec ) != OK ){
						ERETURN( LBSE_FATAL );
					}
					if( !(tcrControlRec.bRecStatus & REC_EXCLUDED) ){
						break;
					}
				}
				if( LB1.tcrHead.lFirstRecActivePos > LB1.tcrHead.lLastRecActivePos ){
					// nao ha' mais registros.
					// essa situacao nao deveria acontecer, pois o lNumRecords
					// deveria ser zero e o if para isso ja' e' feito acima
					LB1.tcrHead.lFirstRecActivePos = LB1.tcrHead.lLastRecActivePos = -1;
					lbscrCurrRecord.Clear();
					lbscrCurrRecord.SetIsUndefined( TRUE );
				} else {
					LB1.R_Seek( lCurPos );
				}
			} else {
				if( LB1.R_CurPos() == LB1.tcrHead.lLastRecActivePos ){
					// vai para o registro anterior (deletando a posicao corrente na LO)
					iRet = PrivPrevRec( lbscTicket, TRUE );
					long lCurPos = LB1.R_CurPos();	// guarda posicao corrente

					// definir o ultimo registro da base (independe de permissoes)
					while( LB1.R_Seek( --LB1.tcrHead.lLastRecActivePos ) == LBS_OK ){
						if( LB1.R_Read( &tcrControlRec ) != OK ){
							ERETURN( LBSE_FATAL );
						}
						if( !(tcrControlRec.bRecStatus & REC_EXCLUDED) ){
							break;
						}
					}
					if( LB1.tcrHead.lLastRecActivePos == -1 ){
						// nao ha' mais registros.
						// essa situacao nao deveria acontecer, pois o lNumRecords
						// deveria ser zero e o if para isso ja' e' feito acima
						LB1.tcrHead.lFirstRecActivePos = LB1.tcrHead.lLastRecActivePos = -1;
						lbscrCurrRecord.Clear();
						lbscrCurrRecord.SetIsUndefined( TRUE );
					} else {
						LB1.R_Seek( lCurPos );
					}
				} else {
					// vai para o proximo registro (deletando a posicao corrente na LO)
					if( (iRet = PrivNextRec( lbscTicket, TRUE )) != LBS_OK ){
						// nao deu, vai para o anterior (a posicao corrente na LO ja foi deletada...)
						iRet = PrivPrevRec( lbscTicket );
					}
				}
			}
			if( ( LB1.tcrHead.lDeletedRecNum == LB1.tcrHead.lDeletedRecNumReorg ) && bSelfReorganize ){
				plbscsOwnerSession->ReorganizeBase( lbscTicket, this );
			}
		}
		if( pcOLList && !(FISIC_OC_LIST) ){
			LBSC_Expr *pExpr = pcOLList->Current();
			if( pExpr && pExpr->pOccList->Size() <= 0 ){
				// nao ha' mais registros na LO ativa
				lbscrCurrRecord.Clear();
				lbscrCurrRecord.SetIsUndefined( TRUE );
				iRet = LBS_OK;
			}
		}
		// seta info no cabecalho de LB1
		LB1.tcrHead.ulLastModifyDate = C_Date().Hash();
		LB1.tcrHead.szLastModifyUserName = plbscsOwnerSession->GetUserName();

		// deleta as ACLs do registro (apenas para bases com restricao a
		// registros)
		if( ( LB1.tcrHead.bBaseType == BASE_PUBLIC_REC_PRIVATE ) ||
			( LB1.tcrHead.bBaseType == BASE_PRIVATE_REC_PRIVATE ) ){
			char *szName = (char*) plbscsOwnerSession->GetUserName();
			int iResult; // para depuracao
			
			// seta o nome do dono do registro para ficar igual ao
			// nome do usuario logado, para o metodo abaixo nao
			// dar pau.
			lbscrCurrRecord.szOwnerName = szName;
			iResult = DelACLPerm( szName, lCurRecNum, NULL, USERRECORD );
			iResult = DelACLPerm( szName, lCurRecNum, NULL, GROUPRECORD );
		}

		// agora grava o header...
		LB1.LB1_WriteHead();

		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_ERROR );
}


/***
	PUBLIC
	Metodo LockRecord
	Trava o registro corrente

	Parameters:
		- lbscTicket : ticket de acesso.
		- bUncondit  : indica se o LBS deve verificar se o registro em disco
				e' mais novo do que o em memoria (FALSE, default) ou
				se o lock deve ser feito incondicionalmente (TRUE).

	Return:
		LBS_OK se conseguir travar o registro ou erro.

	Comments:
		- Nao efetua qualquer alteraco feita em qualquer campo.

***/
int
LBSC_Base::LockRecord( const LBSC_Ticket *lbscTicket, BOOL bUncondit )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LockRecord 1 %s %s", "Base", (char *)szBasePath) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	int	iRet;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( bIsReadOnly ){
		ERETURN( LBSE_BASEREADONLY );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}

	{
		lLockPos = -1;
	}

	iRet = lbscrCurrRecord.Lock( &LB1 );
	if( iRet != LBS_OK ){
		// esperar um pouco e tentar novamente
		Sleep( iLockTimeSleep );
		iRet = lbscrCurrRecord.Lock( &LB1 );
	}

	if( iRet == LBS_OK ){
		// antes de continuar, vamos ver se o registro que esta' em disco
		// bate com o que esta' em memoria (o registro em disco pode ser mais
		// novo do que o em memoria)
		TControlRec	tcrControlRec;
		if( LB1.R_Read( &tcrControlRec ) != OK ){
			ERETURN( LBSE_NORECORD );
		}
		if( tcrControlRec.ulAccess != lbscrCurrRecord.ulAccess || tcrControlRec.bRecStatus & REC_EXCLUDED ){
			// o registro de memoria esta' velho em relacao ao do disco
			// liberar o lock que acabamos de fazer
			lbscrCurrRecord.Release( &LB1 );
			ERETURN( LBSE_OLDRECORD );
		}

		// guarda posicao de lock no arquivo
		lLockPos = LB1.R_CurPos();
		// reseta o timer de lock
		ResetLockElapsedTime();
		return( LBS_OK );
	}
	ERETURN( LBSE_RECORDNOTLOCKED );
}


/***
	PUBLIC
	Metodo ReleaseRecord
	Libera o registro corrente previamente travado ("lockado")

	Parameters:
		- lbscTicket.

	Return:
		LBS_OK se conseguir liberar o registro ou erro.

	Comments:
		- Nao efetua qualquer alteraco feita em qualquer campo.

***/
int
LBSC_Base::ReleaseRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ReleaseRecord 1 %s %s", "Base", (char *)szBasePath) );

#ifdef LBS_DEBUG
	Printf( "ReleaseRecord" );
#endif // LBS_DEBUG

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);		// TEM QUE SER DECLARADO AQUI SOB RISCO DE DEADLOCK

	int	iRet;
	long	lAuxPos;

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !LB1.IsOpen() ){
		ERETURN( LBSE_BASENOTOPEN );	// Base fechada
	}
	
	iRet = LBSE_RECORDNOTLOCKED;
	if( lLockPos > -1 ){
		lAuxPos = LB1.R_CurPos();
		LB1.R_Seek( lLockPos );
		iRet = lbscrCurrRecord.Release( &LB1 );
		LB1.R_Seek( lAuxPos );
	}
	if( iRet == LBS_OK ){
		// remove o timer de lock deste registro 
		KillLockTimer();
	}

	lLockPos = -1;

	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo AddStopWord
	Adiciona uma StopWord na lista de stop words da base

	Parameters:
       	- lbscTicket
		- szSW -> stop word a ser adicionada

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo em caso de erro.

	Comments:
		- Este metodo verifica se a palavra a ser adicionada ja' existe.
		  Em caso positivo, o retorno sera' LBSE_DUPLICATE.
		- Este metodo simplesmente adiciona szSW no arquivo STOPWORD.LB
		  e chama o metodo SetStopWord, que remonta a lista interna a
		  partir do arquivo.
		- O parametro szSW pode conter varias stopwords, separadas
		  por "\r\n". Neste caso, este metodo nao verificara' se ha'
		  repeticoes de palavras.

***/
int
LBSC_Base::AddStopWord( const LBSC_Ticket *lbscTicket, char *szSW )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::AddStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !szSW ){
		ERETURN( LBSE_BADARG );
	}
 
	char	szAux[ FULLNAMESIZE ];
	sprintf( szAux,"%s\\%s", (char *) szBasePath, STOPWORDFILENAME );
	C_File 	cfStopWordFile( szAux, "a+" );
	if( !cfStopWordFile.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	if( cfStopWordFile.Seek( 0, SEEK_END ) != OK ){
		ERETURN( LBSE_ERROR );
	}
	if( cfStopWordFile.WriteLine( szSW ) != OK ){
		ERETURN( LBSE_ERROR );
	}

	if ( pBaseInstance ) {
		pBaseInstance->InvalidateBaseStruct();
	}
	cfStopWordFile.Close();
	ERETURN( SetStopWord() );
}


/***
	PUBLIC
	Metodo GetStopWords
	Obtem as StopWords que estao setadas no LBS

	Parameters:
       	- lbscTicket

	Return:
		- uma string contendo as stopwords separadas por "\r\n" ou
		  NULL em caso de erro.

	Comments:
		- a string retornada DEVE ser deletada pela aplicacao.

***/
char *
LBSC_Base::GetStopWords( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetStopWords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	LTC_TERMVECT *pVect = plbscisIndexSystem->LT_GetStopWord();
 	if( !pVect ){
		// nao ha' SW
		NRETURN( LBS_OK );
	}

	// agora, vamos navegar na lista e montar uma string
	// contendo todas as SW, separadas por '\n'
	long lNumElem = pVect->GetSize();
	if( lNumElem == 0 ){
		// nao ha' SW
		NRETURN( LBS_OK );
	}

	char	*szRet = NULL;
	int		iRetSize = 0;
	// loop para contar o tamanho total da string szRet
	for ( int i=0; i<lNumElem; i++ ) {
		char *szSW = pVect->GetTerm(i);
		int	iSWSize = strlen( szSW );
		iRetSize += iSWSize + 1 + 1 + 1; // + ' ' + '\r' + '\n'
	}

	szRet = new char[ iRetSize + 1 ];	// +1 de seguranca
	if( !szRet ){
		// que pena!
		NRETURN( LBSE_NOMEMORY );
	}

	memset( szRet, 0, iRetSize + 1 );

	// agora, vamos montar a string szRet
	for ( i=0; i<lNumElem; i++ ) {
		char *szSW = pVect->GetTerm(i);
		strcat( szRet, szSW );
		strcat( szRet, " \r\n" );
	}

	// retirar os ultimos 3 caracteres, que sao ' ', '\r' e '\n'
	if( szRet && (strlen( szRet ) > 1) ){
		szRet[ strlen( szRet ) - 3 ] = '\0';
	}
	SetError( LBS_OK );
	return( szRet );
}


/***
	PUBLIC
	Metodo DelStopWord
	Deleta uma StopWord da lista de stop-words da base 
	(deleta tambem do arquivo de stop-words)

	Parameters:
        	- lbscTicket
		- szSW -> stop word a ser deletada. Se for NULL, todas serao deletadas.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo em caso de erro.

	Comments:
		- Este metodo simplesmente remove szSW do arquivo STOPWORD.LB
		  (ou todas as palavras do arquivo, se szSW for NULL)
		  e chama o metodo SetStopWord, que remonta a lista interna a
		  partir do arquivo.

***/
int
LBSC_Base::DelStopWord( const LBSC_Ticket *lbscTicket, char *szSW )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::DelStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	char	szAux[ FULLNAMESIZE ];
	if ( pBaseInstance ) {
		pBaseInstance->InvalidateBaseStruct();
	}
	sprintf( szAux,"%s\\%s", (char *) szBasePath, STOPWORDFILENAME );
	if( !szSW ){
		// deletar o arquivo todo
		C_File 	cfStopWordFile( szAux, "wt+" );
		cfStopWordFile.Close();
		ERETURN( SetStopWord() );
	}
	C_File 	cfStopWordFile( szAux, "rt" );
	if( !cfStopWordFile.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	// abre um arquivo temporario
	char	szAux2[ FULLNAMESIZE ];
	sprintf( szAux2,"%s\\%s", (char *) szBasePath, "auxtmp" );
	C_File	cfAux( szAux2, "wt+" );
	if( !cfAux.IsOpen() ){
		ERETURN( LBSE_ERROR );
	}
	if( cfStopWordFile.Seek( 0, SEEK_SET ) != OK ){
		ERETURN( LBSE_ERROR );
	}
	char	szLine[ 256 ];
	while( ((int) cfStopWordFile.ReadLine( szLine, 256 )) > 0 ){
		if( strcmp( szLine, szSW ) == 0 ){
			// esta e' a string que queremos apagar
			continue;
		}
		if( cfAux.WriteLine( szLine ) != OK ){
			ERETURN( LBSE_ERROR );
		}
	}
	// fechar os dois arquivos
	cfStopWordFile.Close();
	cfAux.Close();

	// deletar o arquivo de stop-words
	remove( szAux );

	// renomeia o arquivo auxiliar para o de stop-words
	MoveFile( szAux2, szAux );

	// seta o novo conjunto de stopwords
	ERETURN( SetStopWord() );
}


/***
	PUBLIC
	Metodo GetCurrentStopWord
	Obtem a stop word corrente da lista de stop words da base

	Parameters:
        	lbscTicket

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetCurrentStopWord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetCurrentStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	return( (const char *)(pltctlStopWordList->LT_GetCurrentTerm() ) );
}


/***
	PUBLIC
	Metodo GetFirstStopWord
	Obtem a primeira stop word da lista de stop words da base

	Parameters:

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetFirstStopWord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetFirstStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	return( (const char *)(pltctlStopWordList->LT_GetFirstTerm() ) );
}


/***
	PUBLIC
	Metodo GetLastStopWord
	Obtem a ultima stop word da lista de stop words da base

	Parameters:

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetLastStopWord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetLastStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}

	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	pltctlStopWordList->LT_GetFirstTerm();
	while( pltctlStopWordList->LT_GetNextTerm() );    // $$$ caminha ate o fim da lista

	return( (const char *)(pltctlStopWordList->LT_GetCurrentTerm() ) );
}


/***
	PUBLIC
	Metodo GetNextStopWord
	Obtem a proxima stop word da lista de stop words da base

	Parameters:
		- lbscTicket : ticket de seguranca

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetNextStopWord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNextStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}

	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	return( (const char *)(pltctlStopWordList->LT_GetNextTerm() ) );
}


/***
	PUBLIC
	Metodo GetPreviousStopWord
	Obtem a stop word anterior da lista de stop words da base

	Parameters:
		- lbscTicket.

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetPreviousStopWord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetPreviousStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}

	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	// $$$ A biblioteca LightText nao implementa um metodo para
	// $$$ caminhar para o elemento anterior de uma lista. Entao,
	// $$$ vamos usar um artificio.

	char	*szAux = (char *)(pltctlStopWordList->LT_GetCurrentTerm() );
	char	*szNext = (char *)(pltctlStopWordList->LT_GetFirstTerm() );
	for( int i = 0; strcmp( szAux, szNext ) != 0; i++ ){
		szNext = (char *)(pltctlStopWordList->LT_GetNextTerm() );
		if( !szNext ){
			// $$ um erro muito doido!
			NRETURN( LBSE_ERROR );
		}
	}
	return( (const char *)(pltctlStopWordList->LT_NthTerm( i ) ) );
}


/***
	PUBLIC
	Metodo GetPreviousStopWord
	Obtem a stop word anterior da lista de stop words da base

	Parameters:
		- lbscTicket.

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
long
LBSC_Base::GetNumberOfStopWords( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumberOfStopWords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		ERETURN( LBSE_OBJNOTOK );
	}
	if( !pltctlStopWordList ){
		ERETURN( LBSE_ERROR );
	}
	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( 0L );
	}
	return( pltctlStopWordList->LT_GetNbrOfTerm() );
}



/***
	PUBLIC
	Metodo GetNthStopWord
	Obtem a n-esima stop word da lista de stop words da base

	Parameters:
        	- lbscTicket : ticket de seguranca
		- iPos : a posicao da stop word

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::GetNthStopWord( const LBSC_Ticket *lbscTicket, int iPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNthStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}

	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	return( (const char *)(pltctlStopWordList->LT_NthTerm( (TUFOURBYTES) iPos ) ) );
}


/***
	PUBLIC
	Metodo SearchStopWord
	Verifica se uma stop word existe na lista de stop words da base

	Parameters:
		- lbscTicket
		- szStopWord
		- iTypeSearch // NAO USADO. PASSE 0.

	Return:
		Apontador para a stop word. Disponivel apenas para consulta

	Comments:

***/
const char *
LBSC_Base::SearchStopWord( const LBSC_Ticket *lbscTicket, const char *szStopWord, int iTypeSearch )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SearchStopWord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	SetError( LBS_OK );
	if( !pltctlStopWordList ){
		return( NULL );
	}
	return( (const char *)(pltctlStopWordList->LT_SearchTerm( (CHARTYPE *) szStopWord ) ) );
}


/***
	PUBLIC
	Metodo Search
	Faz uma pesquisa em uma base

	Parameters:
        	- lbscTicket : ticket de seguranca;
		- szBuffer : expressao de consulta.

	Return:
		- um array de handles (int's) das LO's geradas ou
		  NULL em caso de erro. No caso de erro, consulte
		  LastError().

	Comments:
		- Ver tipos de expressao de consulta na API LightText.
		- As referencias a campos da base devem ser feitas pelos respectivos
		  identificadores, e nao pelos nomes.
		- O vetor de handles retornado por este metodo DEVE ser
		  deletado pela aplicacao.

***/
int *
LBSC_Base::Search( const LBSC_Ticket *lbscTicket, char *szBuffer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Search") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	LTC_EXPRLIST	*pExprList;

	DWORD dwIni = GetTickCount();

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		NRETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		NRETURN( LBSE_TICKETNOTOK );
	}
	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	if( !plbscisIndexSystem ){
		NRETURN( LBSE_INVALIDINDEXSYSTEM );
	}

	// vamos fazer uma "pre-normalizacao" da
	// string para retirar os caracteres acentuados.
	// isso eh uma solucao temporaria para resolver
	// um problema do parser (o parser nao consegue
	// reconhecer caracteres acentuados).
	PreStandardize( szBuffer );

	// settando o timeout de lista de ocorrencia
	int iOccTmOut = LBSC_ServerConfig::OccTimeOut();
	LTC_OCCURRENCELIST::LT_SetOccListTmOut( iOccTmOut );	

	char *szExpr = NULL;
	if( GetAclRestrictExpr( &szExpr ) != LBS_OK ){
		NRETURN( LBSE_RESTRICT );
	}

	// resetar informacao de feedback
	ResetFeedbackInfo();
	pExprList = plbscisIndexSystem->LT_Retrieval( szBuffer, szExpr, 
					GetNumRecords( lbscTicket ) );	// GREEN

	if ( szExpr ) {
		delete szExpr;
		szExpr = NULL;
	}

	DWORD dwFin = GetTickCount();

	if( !pExprList ){
		// vamos retornar uma indicacao de que nao ha' ocorrencias
		// (a operacao de consulta resultou em uma LO vazia)
		char *szLogMsg = new char[ strlen(szBuffer) + 100 ];
		if ( szLogMsg ) {
			sprintf( szLogMsg, "%s --> %ds", szBuffer, (dwFin-dwIni)/1000);
			LOGUSE( SEARCH_ERROR, 1, szLogMsg);
			delete szLogMsg;
			szLogMsg = NULL;
		}
		NRETURN( LBSE_EMPTYLIST );
	}

	// testar se o resultado (ou seja, a ultima LO) possui pelo menos um elemento
	LTC_EXPR	*pLTExpr = pExprList->LT_GetLastExpr();

	if ( !pLTExpr ){
		// nao ha' nada na LO resultante
		delete pExprList;
		char *szLogMsg = new char[ strlen(szBuffer) + 100 ];
		if ( szLogMsg ) {
			sprintf( szLogMsg, "%s --> %ds", szBuffer, (dwFin-dwIni)/1000);
			LOGUSE( SEARCH_ERROR, 1, szLogMsg);
			delete szLogMsg;
			szLogMsg = NULL;
		}
		NRETURN( LBSE_EMPTYLIST );
	}

	LTC_OCCURRENCELIST *pOLAux = pLTExpr->LT_GetResultList();
	if( !pOLAux ){
		// nao ha' nada na LO resultante
		delete pExprList;
		char *szLogMsg = new char[ strlen(szBuffer) + 100 ];
		if ( szLogMsg ) {
			sprintf( szLogMsg, "%s --> %ds", szBuffer, (dwFin-dwIni)/1000);
			LOGUSE( SEARCH_ERROR, 1, szLogMsg);
			delete szLogMsg;
			szLogMsg = NULL;
		}
		NRETURN( LBSE_EMPTYLIST );
	}
	LTC_OCCURRENCE *pOcAux = pOLAux->LT_GetFirstOccurrence();
	if( !pOcAux ){
		// nao ha' nada na LO resultante
		delete pExprList;
		char *szLogMsg = new char[ strlen(szBuffer) + 100 ];
		if ( szLogMsg ) {
			sprintf( szLogMsg, "%s --> %ds", szBuffer, (dwFin-dwIni)/1000);
			LOGUSE( SEARCH_ERROR, 1, szLogMsg);
			delete szLogMsg;
			szLogMsg = NULL;
		}
		NRETURN( LBSE_EMPTYLIST );
	}

	int		iCont = 2;	// teremos uma LO apenas como resultado, e a ultima com handle=0
	int	*iHandles = new int[ iCont ];
	if( !iHandles ){
		// que pena!
		delete pExprList;
		NRETURN( LBSE_NOMEMORY );
	}

	pLTExpr = pExprList->LT_GetLastExpr();
	LBSC_Expr *pExpr = new LBSC_Expr;
	pExpr->szExpr = Strdup( pLTExpr->LT_GetExpression() );

	// vamos gerar uma LO decente 
	int iRet = CreateLbsOccList( pExpr, pLTExpr );
	if ( iRet != LBS_OK ) {
		delete pExprList;
		delete pExpr;
		NRETURN( iRet );
	}

	// adiciona a LO na lista de LO's e automaticamente
	// cria um handle para ela.
	if( pcOLList->FindNull() == OK ){
		// achamos um buraco na lista. vamos
		// usa-lo para a nova LO.
		pcOLList->Refresh( pExpr );
	} else {
		pcOLList->Add( pExpr, TAIL );
	}

	// preenche o vetor de retorno com o handle da LO
	// que acabou de ser inserida da lista
	*(iHandles) = pcOLList->GetCurrentIndex();
	*(iHandles+1) = 0;	// ultimo handle = 0

	delete pExprList;

	// Habilita a LO resultante
	if( EnableOcList( lbscTicket, *(iHandles) ) != LBS_OK ){
		if( (*pcOLList)[ *(iHandles) ] ){
			pcOLList->DeleteCurrObj();	// deleta somente o objeto, mas deixa o nodo.
		}
		delete( iHandles );
		NRETURN( LBSE_ENABLE );
	}

	dwFin = GetTickCount();

	char *szLogMsg = new char[ strlen(szBuffer) + 100 ];
	if ( szLogMsg ) {
		sprintf( szLogMsg, "%s --> %ds", szBuffer, (dwFin-dwIni)/1000);
		LOGUSE( SEARCH_OK, 1, szLogMsg);
		delete szLogMsg;
		szLogMsg = NULL;
	}
	SetError( LBS_OK );
	// retorna o vetor de handles, com o ultimo handle do vetor
	// sendo 0, para que a aplicacao possa identificar o tamanho
	// do vetor. O ultimo handle valido (antes do 0) e' o handle
	// da LO resultante.
	return( iHandles );
}


/***
	PUBLIC
	Metodo Duplicate
	Duplica uma base

	Parameters:

	Return:
		Apontador para um novo objeto LBSC_Base.

	Comments:

***/
LBSC_Base *
LBSC_Base::Duplicate( void )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::Duplicate") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( bBaseObjOk == FALSE ){
		NRETURN( LBSE_OBJNOTOK );
	}
	NRETURN( LBSW_NOTREADY );		// $$$ FALTA IMPLEMENTAR
}


/***
	PUBLIC
	Metodo Compare
	Compara dois objetos base

	Parameters:
		- plbscbAux : apontador para o objeto base a ser comparado com o corrente
		- iType : CMPBASENAME - apenas o nome da base

	Return:
		O resultado da comparacao. ( 0 <=> Objetos iguais )
					   ( != 0 <=> Objetos diferentes )

	Comments:

***/
int
LBSC_Base::Compare( LBSC_Base *plbscbAux, int iType )
{
	switch( iType ){
	case CMPBASENAME:
		SetError( LBS_OK );
		return( this->szBaseName == ((const char*)plbscbAux->szBaseName) ? 0 : 1 );
	case CMPBASEPOINTER:
		SetError( LBS_OK );
		return( this == plbscbAux ? 0 : 1 );
	default:
		SetError( LBS_OK );
		return( 0 );
	}
}

/***
	PUBLIC
	Metodo BaseObjOk
	Obtem o status do objeto

	Parameters:

	Return:
		O status do objeto.

	Comments:

***/
BOOL
LBSC_Base::BaseObjOk( void )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	SetError( LBS_OK );
	return( bBaseObjOk );
}

/***
	PUBLIC
	Metodo GetNumActiveRecords
	Obtem o numero de registros ativos da base

	Parameters:
		- lbscTicket.

	Return:
		- Obvio.

	Comments:
		-

***/
long
LBSC_Base::GetNumActiveRecords( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumActiveRecords 2 this %p lbscTicket %p", this, lbscTicket) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	// a LO corrente eh a fisica

	LB1.R_ReadHead();
	SetError( LBS_OK );
	return( LB1.tcrHead.lNumRecords );
}


/***
	PUBLIC
	Metodo GetNumRecords
	Obtem o numero total de registros da base (incluindo os deletados)

	Parameters:
		- lbscTicket.

	Return:
		- Obvio.

	Comments:
		-

***/
long
LBSC_Base::GetNumRecords( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetNumRecords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	long	lRet = LB1.R_FileSize();
	SetError( LBS_OK );
	return( lRet );
}


/***
	PUBLIC
	Metodo FirstRecord
	Obtem o registro referente a primeira posicao da LO

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::FirstRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::FirstRecord 1 %s %s", "Base", (char *)szBasePath) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// Se a lista de ocorrencias for NULL entao
	// devo retornar o primeiro registro da base independente da LO
	if( !plbscolOcurrenceList ){
		return( FirstFRecord( lbscTicket ) );
	}

	plbscolOcurrenceList->First();
	LTC_OCCURRENCE *pltcOcAux = plbscolOcurrenceList->GetFirstOccurrence();
	if( pltcOcAux ){
		// faz release no registro corrente
		ReleaseRecord( lbscTicket );

		int iRet = GotoRec( lbscTicket, (long) pltcOcAux->LT_GetSet() );
		switch( iRet ){
		case LBSE_FATAL:
		case LBSE_EXCLUDEDREC:
			// tentra ir para o proximo registro, lembrando que
			// eh necessario deletar da LO corrente a posicao corrente
			return( PrivNextRec( lbscTicket, TRUE ) );
		}
		ERETURN( iRet );
	}
	ERETURN( LBSE_NORECORD );
}



/***
	PUBLIC
	Metodo LastRecord
	Obtem o registro referente a ultima posicao da LO

	Parameters:
		- lbscTicket : ticket de seguranca.

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::LastRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::LastRecord 1 %s %s", "Base", (char *)szBasePath) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// Se a lista de ocorrencias for NULL entao
	// devo retornar o ultimo registro da base independente da LO
	if( !plbscolOcurrenceList ){
		return( LastFRecord( lbscTicket ) );
	}

	plbscolOcurrenceList->Last();
	LTC_OCCURRENCE *pltcOcAux = plbscolOcurrenceList->GetFirstOccurrence();
	if( pltcOcAux ){
		// faz release no registro corrente
		ReleaseRecord( lbscTicket );

		int iRet = LBS_OK;
		iRet = GotoRec( lbscTicket, (long) pltcOcAux->LT_GetSet() );
		switch( iRet ){
		case LBSE_FATAL:
		case LBSE_EXCLUDEDREC:
			// tentra ir para o registro anterior, lembrando que
			// eh necessario deletar da LO corrente a posicao corrente
			return( PrivPrevRec( lbscTicket, TRUE ) );
		}
		ERETURN( iRet );
	}
	ERETURN( LBSE_NORECORD );
}



/***
	PUBLIC
	Metodo NthRecord
	Obtem o registro referente a n-esima posicao da LO

	Parameters:
		- lPos -> posicao da qual se deseja obter o registro

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::NthRecord( const LBSC_Ticket *lbscTicket, long lPos )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::NthRecord 1 %s %s", "Base", (char *)szBasePath) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	LBSC_OcList	*plbscolOcurrenceList = GetCurrentOcList();

	// Se a lista de ocorrencias for NULL entao
	// devo retornar o n-esimo registro da base independente da LO
	if( !plbscolOcurrenceList ){
		return( NthFRecord( lbscTicket, lPos ) );
	}

	// tratar a LO corrente
	long			lNumRec = 0;
	LTC_OCCURRENCE	*pltcOcAux;

	// guarda a posicao corrente a LO
	long lCurPos = plbscolOcurrenceList->CurPos();

	if ( !plbscolOcurrenceList->Goto( lPos ) ) {
		ERETURN( LBSE_NORECORD );
	}

	pltcOcAux = plbscolOcurrenceList->GetFirstOccurrence();
	if( pltcOcAux ){
		// faz release no registro corrente
		ReleaseRecord( lbscTicket );

		int iRet = GotoRec( lbscTicket, pltcOcAux->LT_GetSet() );
		if( iRet != LBSE_EXCLUDEDREC && iRet != LBSE_FATAL ){
			ERETURN( iRet );
		}
	}
	// volta para a ocorrencia que estava antes de comecar tudo
	plbscolOcurrenceList->Goto( lCurPos );

	ERETURN( LBSE_NORECORD );
}



/***
	PUBLIC
	Metodo NextRecord
	Obtem o proximo registro da LO (o proximo registro, nao a proxima
	ocorrencia)

	Parameters:
		- lbscTicket

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::NextRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::NextRecord 1 %s %s", "Base", (char *)szBaseLongName) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	int	iRet = PrivNextRec( lbscTicket );

//	if( iRet == LBSE_NORECORD ){
//		// nao ha' registros para frente. vamos tentar voltar.
//		iRet = PrivPrevRec( lbscTicket );
//		ERETURN( iRet );
//	}
	ERETURN( iRet );
}

/***
	PUBLIC
	Metodo PreviousRecord
	Obtem o registro anterior da LO (o registro anterior, nao a ocorrencia
	anterior)

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um erro.

	Comments:
		- Altera o registro corrente de uma base.
		- Nao grava as alteracoes feitas no registro corrente antes de
		  caminhar na LO.

***/
int
LBSC_Base::PreviousRecord( const LBSC_Ticket *lbscTicket )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::PreviousRecord 1 %s %s", "Base", (char *)szBaseLongName) );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( plbscsOwnerSession->TicketIsOk( lbscTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}

	int	iRet = PrivPrevRec( lbscTicket );

//	if( iRet == LBSE_NORECORD ){
//		// nao ha' registros para tras. vamos tentar ir para frente.
//		iRet = PrivNextRec( lbscTicket );
//		ERETURN( iRet );
//	}
	ERETURN( iRet );
}



/***
	PUBLIC
	Metodo EnableFastRecord
	Habilita/desabilita a gravacao de registros com velocidade.
	Quando o LBS esta' com essa opcao desabilitada (o default),
	a gravacao de registros eh lenta devido a atualizacoes no
	header de LB1 e de tratamento de lock nos registros. Quando
	a opcao esta' habilitada, esses tratamentos sao ignorados
	e a gravacao de registros fica mais rapida. A desvantagem
	esta' na seguranca dos dados. Se houver queda de energia 
	durante uma gravacao "fast", a integridade do header de LB1
	nao eh garantida.

	Parameters:

	Return:
		- LBS_OK em caso de sucesso ou um codigo erro.

	Comments:
		- 

***/
int
LBSC_Base::EnableFastRecord( BOOL bFastRecPar )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::EnableFastRecord") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if( !bIsExclusive ){
		// a base nao esta' em modo exclusivo
		ERETURN( LBS_OK );
	}

	bFastRec = bFastRecPar;

	if( bFastRec ){
		if( !LB1.tcrHead.bOnLineIndex ){ 
			// abrir o arquivo LB5
			OpenLogFile( cfLB5 );
		}
		plbscisIndexSystem->LT_TurnOnAutoBuffer( LBSC_ServerConfig::MaxMemForIndex() );
	} else {
		if( !LB1.tcrHead.bOnLineIndex ){ 
			// fechar o arquivo LB5
			cfLB5.CloseIndex();
		}
		LB1.Flush();

		if ( pBaseInstance && pBaseInstance->DataFileLoaded() ) {
			// a regiao critica abaixo protege a manipulacao do LB4
			CLBAutoRegCrit	AutoRegCritDataFile( &(pBaseInstance->DataFileCritSect) );
			CPageFile *pDataFile = pBaseInstance->GetDataFile();
			if( pDataFile->IsOpen() ){
				pDataFile->Flush();
			}
		}

		FlushIndexSystem();
		plbscisIndexSystem->LT_TurnOffAutoBuffer();
	}

	ERETURN( LBS_OK );
}


/**********************************************************
// Function name	: LBSC_Base::GetGroupSortField
// Description	    : 
// Return type		: int 
// Argument         : int iGroupPar
**********************************************************/
int LBSC_Base::GetGroupSortField( int iGroupPar )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	// retorna o id do campo que eh ordenado dentro do grupo iGroupPar
	// ou -1 se nao houver nenhum campo ordenado no grupo.

	// varrer todos os campos procurando o primeiro ordenado que
	// pertence ao grupo.
	int	iNumFields = GetNumberOfFields();
	for( int i = 0; i < iNumFields; i++ ){
		LBSC_Field	*pf = (*this)[ i ];

		if( pf && (pf->GetGroup() == iGroupPar) && (pf->GetAttrib() & (ASC_ORD_FIELD | DESC_ORD_FIELD)) ){
			// encontramos
			return( pf->uiFieldId );
		}
	}
	return( -1 );
}

// Carregar a lista de GoWords do arquivo
BOOL LBSC_Base::GetGowords( char  *szFieldAliasName, char ** pszGowords)
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::GetGowords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	szGowordsFileName[ MAXPATH ];
	char	szGWKey[ MAXPATH ];
	char	szGWs[ MAXPATH ];
	int		iGWNum = 0;
	int		TamMax = MAXPATH+1;


	if( ! (*pszGowords = new char[ TamMax ]) ){
		return FALSE;
	}
	strcpy( *pszGowords,"");
		
	//pegar o caminho do arquivo de configuracao
	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	
	sprintf( szGWKey, "%s%d", GWKEY, ++iGWNum );
	GetPrivateProfileString( szFieldAliasName, szGWKey, "", szGWs, MAXPATH-1, szGowordsFileName );
	
	//verificar se existe gowords para aquele campo.
	if( szGWs[0] ){
		
		//pegar as gowords.
		while( szGWs[0] ){
			// gowords encontradas para o campo szGWFieldName.
			// montar a lista interna de gowords para o campo.
			C_StrTok	cStrTok;
			char		*szGW = cStrTok.StrTok( szGWs, "," );
			
			while( szGW ){
				char	c;
				// tirar os espacos e tabs
				while( (*szGW == ' ') || (*szGW == '\t') ){
					++szGW;
				}
				c = szGW[ strlen( szGW ) - 1 ];
				while( (c == ' ') || (c == '\t') ){
					szGW[ strlen( szGW ) - 1 ] = '\0';
					c = szGW[ strlen( szGW ) - 1 ];
				}
				if( *szGW ){
					//reallocar o String das gowords...
					int TamRealoc = strlen(szGW) + strlen (*pszGowords) + strlen("\r\n") + 1; 
					if( TamRealoc > TamMax ){
						if( (*pszGowords = (char*) LBS_Realloc( (void*)*pszGowords, TamMax, TamRealoc*2 )) == NULL ){
							return ( FALSE );
						}
						TamMax = TamRealoc*2;
					}
					szGW = _strupr( szGW );
					strcat( *pszGowords, szGW );
					strcat( *pszGowords, "\r\n" );
				
				}
				szGW = cStrTok.StrTok( NULL, "," );
			}

			// tentar ler outro grupo de gowords
			sprintf( szGWKey, "%s%d", GWKEY, ++iGWNum );
			GetPrivateProfileString( szFieldAliasName, szGWKey, "", szGWs, MAXPATH-1, szGowordsFileName );
		}
	}

	return ( TRUE );
}

// Setar uma nova lista de GoWords 
BOOL LBSC_Base::SetGowords( char  *szFieldAliasName, const char  *szGowords)
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::SetGowords") );

	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	szGowordsFileName[ MAXPATH ];
	int		iFieldNum = 0;  
	
	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
		
	//zerar as entradas ou criar uma nova vazia caso nao exista nehuma chave.
	if( WritePrivateProfileString( szFieldAliasName, NULL, NULL, szGowordsFileName ) == NULL ){
		return FALSE;
	}

	char		szGWKey[ MAXPATH ];
	C_StrTok	cStrTok;
	int			iGWNum = 0;
	char		*szGWs;
	
	szGWs = cStrTok.StrTok( (LPTSTR) szGowords, "\n \r," );
	
	while( szGWs ){
		char		c;

		// tirar os espacos e tabs
		while( (*szGWs == ' ') || (*szGWs == '\t') ){
			++szGWs;
		}
		c = szGWs[ strlen( szGWs ) - 1 ];
		while( (c == ' ') || (c == '\t') ){
			szGWs[ strlen( szGWs ) - 1 ] = '\0';
			c = szGWs[ strlen( szGWs ) - 1 ];
		}

		if( *szGWs ){
			sprintf( szGWKey, "%s%d", GWKEY, ++iGWNum );
			szGWs = _strupr( szGWs );
			if ( WritePrivateProfileString( szFieldAliasName, szGWKey, szGWs, szGowordsFileName ) == NULL ){
				return FALSE;
			}
		}
		szGWs = cStrTok.StrTok( NULL, "\n \r," );
	}
			
	return (TRUE);
}

//pegar o minkeysize do arquivo.lb
//retorna o minkeysize lido.
int LBSC_Base::GetMinkeysize( )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	szGowordsFileName[ MAXPATH ];
	int		iMinKeySize;
	
	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	iMinKeySize = GetPrivateProfileInt( GWMAINSECTION, GWMINKEYSIZE, 0, szGowordsFileName );

	return iMinKeySize;
}

//setar o minkeysize no .lb
int LBSC_Base::SetMinkeysize( int iMinKeySize )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	char	szGowordsFileName[ MAXPATH ];
	char    *minkey = new char[ 10 ];

	
	strcpy( minkey, "");
	sprintf( minkey, "%d", iMinKeySize );

	sprintf( szGowordsFileName, "%s\\%s%s", (char*) szBasePath, (char*) szBaseName, CONFFILEEXT );
	if( ! (WritePrivateProfileString( GWMAINSECTION, GWMINKEYSIZE, minkey, szGowordsFileName)) ){
		return (LBSE_ERROR);
	}
	
	if ( pBaseInstance ) {
		pBaseInstance->MinKeySize = iMinKeySize;
	}
	LBSC_Session::Delete( minkey );

	return (LBS_OK);
}
