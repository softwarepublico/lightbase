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

#include <controlfile.h>
#include <sesscl.h>
#include <funcp.h>

// funcoes para comparacao no sort e bsearch
int cmp_by_obj( const void *a, const void *b )
{
	TBasesFile *pBaseA = (TBasesFile*)a;
	TBasesFile *pBaseB = (TBasesFile*)b;
	return stricmp( pBaseA->szBaseName, pBaseB->szBaseName );
}

int cmp_by_name( const void *a, const void *b )
{
	LPCTSTR szName = (LPCTSTR)a;
	TBasesFile *pBase = (TBasesFile*)b;
	return stricmp( szName, pBase->szBaseName );
}


LBSC_ControlFile::LBSC_ControlFile()
{
	lSize = 0;
	pBasesInfo = NULL;
}

LBSC_ControlFile::~LBSC_ControlFile()
{
	if ( pBasesInfo ) {
		delete pBasesInfo;
	}
}

BOOL LBSC_ControlFile::Init()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if ( pBasesInfo ) {
		delete pBasesInfo;
		pBasesInfo = NULL;
	}
	// Abrir o arquivo de bases para para obter todas as bases.
	C_RecordFile	cfBasesFile;
	if ( !Open( cfBasesFile, TRUE ) ) {
		return FALSE;
	}

	lSize = cfBasesFile.R_FileSize();
	pBasesInfo = new TBasesFile[lSize];
	if ( !pBasesInfo ) {
		return FALSE;
	}
	memset( pBasesInfo, 0, lSize*sizeof(TBasesFile) );
	cfBasesFile.R_Seek( 0 );
	for ( int i=0; i<lSize; i++ ) {
		if( cfBasesFile.R_Read( &(pBasesInfo[i]) ) != OK ){
			delete pBasesInfo;
			pBasesInfo = NULL;
			return FALSE;
		}
		cfBasesFile.R_SeekNext();
	} 
	qsort( pBasesInfo, lSize, sizeof( TBasesFile ), cmp_by_obj );
	cfBasesFile.Close();
	return TRUE;
}


BOOL LBSC_ControlFile::Insert( TBasesFile tbNewBaseInfo )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);
	if ( !pBasesInfo ) {
		return FALSE;
	}
	TBasesFile *pFound = (TBasesFile *)bsearch( tbNewBaseInfo.szBaseName, pBasesInfo, lSize, sizeof( TBasesFile ), cmp_by_name );
	if ( pFound && !pFound->bRecDeleted ) {
		return FALSE;
	}
	if ( pFound ) {
		return Set( tbNewBaseInfo );
	} 
	// Abrir o arquivo de bases para para atualiza-lo
	C_RecordFile	cfBasesFile;
	if ( !Open( cfBasesFile, FALSE ) ) {
		return FALSE;
	}
	cfBasesFile.R_Append(&tbNewBaseInfo);
	cfBasesFile.Close();
	return Init();
}

BOOL LBSC_ControlFile::Set( TBasesFile tbNewBaseInfo )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if ( !pBasesInfo ) {
		return FALSE;
	}

	TBasesFile *pBase = (TBasesFile *)bsearch( tbNewBaseInfo.szBaseName, pBasesInfo, lSize, sizeof( TBasesFile ), cmp_by_name );
	if ( !pBase ) {
		return FALSE;
	}

	// Abrir o arquivo de bases para para atualiza-lo
	C_RecordFile	cfBasesFile;
	if ( !Open( cfBasesFile, FALSE ) ) {
		return FALSE;
	}

	cfBasesFile.R_Seek( 0 );
	for ( int i=0; i<lSize; i++ ) {
		TBasesFile tbfAux;
		if( cfBasesFile.R_Read( &(tbfAux) ) == OK ){
			if ( stricmp( tbfAux.szBaseName, pBase->szBaseName ) == 0 ) {
				// achamos
				cfBasesFile.R_Write( &tbNewBaseInfo );
				*pBase = tbNewBaseInfo;
				break;
			}
		}
		cfBasesFile.R_SeekNext();
	} 
	cfBasesFile.Close();
	if ( i >= lSize ) {
		// nao achamos o cara em arquivo
		return FALSE;
	}
	return TRUE;
}

const TBasesFile *LBSC_ControlFile::Get( long lPos )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if ( !pBasesInfo || lPos >= lSize ) {
		return NULL;
	}
	if ( (pBasesInfo[lPos]).bRecDeleted ) {
		return NULL;
	}
	return &(pBasesInfo[lPos]);
}

const TBasesFile *LBSC_ControlFile::Get( char *szBaseName )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if ( !pBasesInfo ) {
		return NULL;
	}
	TBasesFile *pFound = (TBasesFile *)bsearch( szBaseName, pBasesInfo, lSize, sizeof( TBasesFile ), cmp_by_name );
	if ( !pFound || pFound->bRecDeleted ) {
		return NULL;
	}
	return pFound;
}

long LBSC_ControlFile::Size()
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	return lSize;
}

BOOL LBSC_ControlFile::Open( C_RecordFile &crFile, BOOL bReadOnly )
{
	char		szAux[ FILENAMESIZE ];
	char		szFullAux[ FULLNAMESIZE ];
	char		szFNameAux[ FULLNAMESIZE ];

	// pegar o dir_base
	if( LBSC_Session::GetFNameOnProfile( szFullAux, szAux ) != LBS_OK ){
		return FALSE;
	}

	sprintf( szFNameAux, "%s\\%s", szFullAux, szAux );
	// verificar versao do arquivo de controle
	if( GetControlFileVersion( szFNameAux ) != CRYPTO_MAGICNUMBER ){
		return FALSE;
	}
	if ( crFile.Open( szFNameAux, CRYPTO_MAGICNUMBER, 0, 
								 sizeof( TBasesFile ), "HEADKEY", 
								 "RECKEY", bReadOnly ? "rb" : NULL, SH_DENYRW, TRUE ) != OK ) {
		return FALSE;
	}

	if( !crFile.IsOpen() ){
		return FALSE;
	}
	return TRUE;
}


BOOL LBSC_ControlFile::Del( char *szBaseName )
{
	CLBAutoRegCrit	AutoRegCrit(&rcRegCrit);

	if ( !pBasesInfo ) {
		return FALSE;
	}

	TBasesFile *pBase = (TBasesFile *)Get( szBaseName );
	if ( !pBase ) {
		return FALSE;
	}

	pBase->bRecDeleted = TRUE;
	if ( !Set( *pBase ) ) {
		pBase->bRecDeleted = FALSE;
		return FALSE;
	}
	return TRUE;
}
