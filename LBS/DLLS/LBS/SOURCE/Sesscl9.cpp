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
// Module: SESSCL9.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif
#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_FUNCP_H_
#include	<funcp.h>
#endif
#ifndef	_LICLIST_H_
#include	<liclist.h>
#endif

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
#define	EnterCriticalSection()			EnterCriticalSection( __FILE__, __LINE__ )
#define	LeaveCriticalSection()			LeaveCriticalSection( __FILE__, __LINE__ )

#endif

extern	LBSC_LicList		*_clLicList;	// lista para controle de licencas e usuarios
											// logados. Usada apenas para o LBS tipo REDE.

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PRIVATE
	Metodo ImportBase
	Importa uma base a partir de um arquivo no formato pre-definido de importacao

	Parameters:
		- plbscTicketPar		-> ticket de seguranca
		- pcfImportFile
		- szNewOwnerName
		- szNewBasePassword
		- szUserBase

	Return:
		- LBS_OK se conseguir importar todas as bases ou erro.

	Comments:

***/
int
LBSC_Session::ImportBase( const LBSC_Ticket *plbscTicketPar, C_File *pcfImportFile, BOOL bChangeOwnerBase,
			  char *szNewOwnerName,	char *szNewBasePassword, char *szNewMaintenanceBasePassword )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ImportBase") );
	// algoritmo:
	// . ler o arquivao para encontrar a base
	//	. extrair seu nome
	//	. extrair o flag de criptografia da base
	//	. criar o diretorio para baixar os arquivos
	//	. procurar os arquivos que a compoem
	//	. para cada arquivo:
	//		. extrair seu nome
	//		. extrair seu tamanho
	//		. extrair o proprio arquivo e grava-lo no diretorio criado
	//	. alterar nome do dono e senhas da base
	//	. incorpora-la ao LBS (usando IncorporateBase)
	// . pronto!

	char	szFileName[ FULLNAMESIZE ];	// nome da base
	char	szFullName[ FULLNAMESIZE ];	// nome completo da base
	char	szAux[ FULLNAMESIZE ];		// string auxiliar
	int	iNumFilesFound = 0;
	BOOL	bEncrypt;

	// vamos ler o numero de arquivos encontrados no arquivao
	pcfImportFile->Read( &iNumFilesFound, sizeof( iNumFilesFound ) );

	// agora vamos ler o nome da base no arquivao
	pcfImportFile->Read( szFileName, FILENAMESIZE );

	// ler o flag de criptografia da base
	pcfImportFile->Read( &bEncrypt, sizeof( bEncrypt ) );

	// montar o nome completo, incluindo o diretorio_base
	LBSC_Base::GetDirBase( szAux );
	sprintf( szFullName, "%s\\%s", szAux, szFileName );

	// criar o diretorio para a base
	if( MakeDir( szFullName ) == LBSE_DIREXIST ){
		// diretorio ja' existe
		// temos que abortar o processo
		ERETURN( LBSE_DIREXIST );
	}

	// procurar os arquivos da base e cria-los
	for( int i = 0; i < iNumFilesFound; i++ ){
		// pegar o nome do arquivo
		pcfImportFile->Read( szAux, FULLNAMESIZE );

		// criar o arquivo
		C_File	cFile( szAux, "wb" );
		if( !cFile.IsOpen() ){
			// deu pau na criacao do arquivo.
			// abortar o processo.
			ERETURN( LBSE_FILEERROR );
		}

		// obter seu tamanho
		long	lSize;
		pcfImportFile->Read( &lSize, sizeof( lSize ) );

		// extrair o arquivo do arquivao e grava-lo em disco
		cFile.Seek( 0, SEEK_SET );
		if( BufferToFile( pcfImportFile, &cFile, lSize ) != LBS_OK ){
			// deu pau.
			// abortar processo
			ERETURN( LBSE_ERROR );
		}

		// fechar o arquivo
		cFile.Close();
	}

	// os arquivos da base foram criados.

	if( bChangeOwnerBase ){
		// vamos trocar as passwords e o nome do dono.
		sprintf( szAux, "%s\\%s%s", szFullName, szFileName, CONTROLFILEEXT );
		C_LB1	cLB1( szAux, bEncrypt ? LBDEFKEY : NULL );
		if( !cLB1.IsOpen() ){
			// Alguma coisa saiu errada.
			// Abortar processo.
			ERETURN( LBSE_FILEERROR );
		}
		// ler header de LB1
		if( cLB1.R_ReadHead() != OK ){
			// erro.
			ERETURN( LBSE_FILEERROR );
		}
		cLB1.tcrHead.szOwnerName = szNewOwnerName;
		cLB1.tcrHead.szBasePassword = szNewBasePassword;
		cLB1.tcrHead.szMaintenancePassword = szNewMaintenanceBasePassword;
		// gravar header de LB1
		if( cLB1.LB1_WriteHead() != OK ){
			// erro.
			ERETURN( LBSE_FILEERROR );
		}
		// fechar o arquivo
		cLB1.Close();
	}

	// a base esta' criada.
	// vamos incorpora-la ao arquivo de controle do LBS
	if( IncorporateBase( plbscTicketPar, szFileName, szNewBasePassword, szNewOwnerName, NULL ) != LBS_OK ){
		// deu pau.
		return( LastError() );
	}

	// ok. conseguimos importar a base com sucesso.
	ERETURN( LBS_OK );
}


/***
	PRIVATE
	Metodo PutPrivateSlotInfo
	Seta informacoes do slot-0, que eh o slot reservado para o proprio LBS.

	Parameters:
		- szBaseName -> o nome da base

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- este metodo abre a base em modo privado e seta o slot-0.

***/
int
LBSC_Session::PutPrivateSlotInfo( const char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::PutPrivateSlotInfo") );

	LBSC_Base	*pBase = new LBSC_Base( this->plbsctTicket, szBaseName, this, FALSE, FALSE, FALSE );

	if( !pBase ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !pBase->BaseObjOk() ){
		delete pBase;
		ERETURN( LBSE_ERROR );
	}
	void *pBuffer = (void *) new char [SizeofPrivateSlot()];
	if ( !pBuffer ) {
		delete pBase;
		ERETURN( LBSE_NOMEMORY );
	}
	memcpy( pBuffer, (void*) MakePrivateSlotInfo(), SizeofPrivateSlot() );
	int iRet = pBase->PutSlot( PRIVATESLOT, pBuffer, SizeofPrivateSlot() );
	delete pBuffer;
	delete pBase;
	ERETURN( iRet );
}


/***
	PRIVATE
	Metodo GetPrivateSlotInfo
	Obtem informacoes do slot-0, que eh o slot reservado para o proprio LBS.

	Parameters:
		- szBaseName -> o nome da base
		- szBuffer   -> buffer para conter o retorno. deve ter espaco suficiente 
				para conter a informacao (eh possivel obter o tamanho do
				buffer atraves do metodo GetPrivateSlotSize)

	Return:
		- LBS_OK em caso de sucesso.

	Comments:
		- este metodo abre a base em modo privado e obtem a informacao do slot-0.

***/
int
LBSC_Session::GetPrivateSlotInfo( const char *szBaseName, char *szBuffer )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetPrivateSlotInfo") );

	LBSC_Base	*pBase = new LBSC_Base( this->plbsctTicket, szBaseName, this, FALSE, FALSE, FALSE );

	if( !pBase ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !pBase->BaseObjOk() ){
		delete pBase;
		ERETURN( LBSE_ERROR );
	}
	int iRet = pBase->GetSlot( PRIVATESLOT, (void*) szBuffer );
	delete pBase;
	ERETURN( iRet );
}

/***
	PRIVATE
	Metodo GetPrivateSlotSize
	Obtem o tamanho das informacoes do slot-0, que eh o slot reservado para o proprio LBS.

	Parameters:
		- szBaseName -> o nome da base

	Return:
		- o tamanho da informacao do slot-0

	Comments:
		- este metodo abre a base em modo privado e obtem a informacao do slot-0.

***/
int
LBSC_Session::GetPrivateSlotSize( const char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetPrivateSlotSize") );
	LBSC_Base	*pBase = new LBSC_Base( this->plbsctTicket, szBaseName, this, FALSE, FALSE, FALSE );

	if( !pBase ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !pBase->BaseObjOk() ){
		delete pBase;
		ERETURN( LBSE_ERROR );
	}
	long lSize = pBase->GetSlotSize( PRIVATESLOT );
	delete pBase;
	ERETURN( lSize );
}


/***
	PRIVATE
	Metodo GetUDBName
	Obtem o nome da UDB de uma base

	Parameters:
		- szBaseName -> o nome da base

	Return:
		- o nome da UDB ou NULL em caso de erro

	Comments:
		- este metodo abre a base em modo privado e obtem a informacao
		- o retorno DEVE ser deletado

***/
char *
LBSC_Session::GetUDBName( const char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUDBName") );

	LBSC_Base	*pBase = new LBSC_Base( this->plbsctTicket, szBaseName, this, FALSE, FALSE, FALSE );

	if( !pBase ){
		NRETURN( LBSE_NOMEMORY );
	}
	if( !pBase->BaseObjOk() ){
		delete pBase;
		NRETURN( LBSE_ERROR );
	}
	char	*szUDB = pBase->GetUserBase();
	delete pBase;
	SetError( LBS_OK );
	return( szUDB );
}


/***
	PRIVATE
	Metodo GetBaseType
	Obtem o tipo de uma base

	Parameters:
		- szBaseName -> o nome da base

	Return:
		- o tipo da base ou um valor negativo em caso de erro.

	Comments:
		- este metodo abre a base em modo privado e obtem a informacao

***/
int
LBSC_Session::GetBaseType( const char *szBaseName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetBaseType") );

	LBSC_Base	*pBase = new LBSC_Base( this->plbsctTicket, szBaseName, this, FALSE, FALSE, FALSE );

	if( !pBase ){
		ERETURN( LBSE_NOMEMORY );
	}
	if( !pBase->BaseObjOk() ){
		delete pBase;
		ERETURN( LBSE_ERROR );
	}
	BYTE bType = pBase->GetBaseType();
	delete pBase;
	SetError( LBS_OK );
	return( bType );
}


/***
	PRIVATE
	Metodo MakePrivateSlotInfo
	Constroi um buffer contendo informacoes para o slot privado do LBS

	Parameters:
		- 

	Return:
		- buffer contendo as informacoes de slot

	Comments:
		- o retorno NAO DEVE ser deletado

***/
const char *
LBSC_Session::MakePrivateSlotInfo()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::MakePrivateSlotInfo") );
	return( "LBSBASE" );
}

/***
	PRIVATE
	Metodo SizeofPrivateSlot
	Pbtem o tamanho do conteudo do slot privado

	Parameters:
		- 

	Return:
		- tamanho do conteudo do slot

	Comments:
		- 

***/
int
LBSC_Session::SizeofPrivateSlot()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::SizeofPrivateSlot") );
	return( strlen( "LBSBASE" ) );
}


/***
	PRIVATE
	Metodo LockSessList
	Entra na regiao critica que protege a lista de sessoes

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Session::LockSessList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::LockSessList") );
//	if( _pcGlobalSessCritSect ){
//		_pcGlobalSessCritSect->EnterCriticalSection( CRITSECT3, (DWORD) this );
//		return( LBS_OK );
//	}
	return( LBSE_ERROR );
}

/***
	PRIVATE
	Metodo ReleaseSessList
	Sai da regiao critica que protege a lista de sessoes

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Session::ReleaseSessList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReleaseSessList") );
//	if( _pcGlobalSessCritSect ){
//		_pcGlobalSessCritSect->LeaveCriticalSection( CRITSECT3 );
//		return( LBS_OK );
//	}
	return( LBSE_ERROR );
}

/***
	PRIVATE
	Metodo GetFirstLic
	Obtem o primeiro elemento da lista de licencas _clLicList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
TLicInfo *
LBSC_Session::GetFirstLic()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetFirstLic") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// pega o objeto solicitado
	TLicInfo	*pRet = _clLicList->First();
	return( pRet );
}


/***
	PRIVATE
	Metodo GetNextLic
	Obtem o proximo elemento da lista de licencas _clLicList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
TLicInfo *
LBSC_Session::GetNextLic()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetNextLic") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// pega o objeto solicitado
	TLicInfo	*pRet = _clLicList->Next();
	return( pRet );
}


/***
	PRIVATE
	Metodo GetPreviousLic
	Obtem o elemento anterior da lista de licencas _clLicList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
TLicInfo *
LBSC_Session::GetPreviousLic()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetPreviousLic") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// pega o objeto solicitado
	TLicInfo	*pRet = _clLicList->Previous();
	return( pRet );
}

/***
	PRIVATE
	Metodo GetLastLic
	Obtem o ultimo elemento da lista de licencas _clLicList

	Parameters:
		-

	Return:
		- ponteiro para a sessao

	Comments:
		-

***/
TLicInfo *
LBSC_Session::GetLastLic()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetLastLic") );
	C_SessCritSect	cCS3( this, CRITSECT3 );

	// pega o objeto solicitado
	TLicInfo	*pRet = _clLicList->Last();
	return( pRet );
}

/***
	PRIVATE
	Metodo LockLicList
	Entra na regiao critica que protege a licencas _clLicList

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Session::LockLicList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::LockLicList") );
//	if( _pcGlobalSessCritSect ){
//		_pcGlobalSessCritSect->EnterCriticalSection( CRITSECT3, (DWORD) this );
//		return( LBS_OK );
//	}
	return( LBSE_ERROR );
}

/***
	PRIVATE
	Metodo ReleaseLicList
	Sai da regiao critica que protege a licencas _clLicList

	Parameters:
		-

	Return:
		- LBS_OK em caso de sucesso

	Comments:
		-

***/
int
LBSC_Session::ReleaseLicList()
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::ReleaseLicList") );
//	if( _pcGlobalSessCritSect ){
//		_pcGlobalSessCritSect->LeaveCriticalSection( CRITSECT3 );
//		return( LBS_OK );
//	}
	return( LBSE_ERROR );
}
