/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef	_OLDRECFILCL_H_
#include	<oldrecf.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef _CRIPTO_
#include	<cripto.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

long C_OldRecordFile::lNextAppendLocation = 0L;

/********************/
C_OldRecordFile::C_OldRecordFile( void )
{
	lHeadSize = lRecSize = 0;
	lCurPos = lFileSize = -1;
	szHeadKey = NULL;
	szRecKey = NULL;
	iHeadLocked = 0;
}

/********************/
C_OldRecordFile::C_OldRecordFile( char* szFileNamePar, long lHeadSize, long lRecSize,
	char *szHeadKey, char *szRecKey,
	 const char *szMode, int iShFlag ) :
	 szHeadKey( NULL ),
	 szRecKey( NULL )
{
	Open( szFileNamePar, lHeadSize, lRecSize, szHeadKey, szRecKey, szMode, iShFlag );
	iHeadLocked = 0;
}


/********************/
int
C_OldRecordFile::Open( char* szFileNamePar, long lHeadSize, long lRecSize,
	char *szHeadKey, char *szRecKey,
	 const char *szMode, int iShFlag )
{
	if( IsOpen() ){
		return( !OK );
	}
	C_File::Open( szFileNamePar, szMode, iShFlag );
	if( IsOpen() ){
		if( szHeadKey ){
			C_OldRecordFile::szHeadKey = new char [ strlen( szHeadKey ) + 1 ];
			strcpy( C_OldRecordFile::szHeadKey, szHeadKey );
		}
		if( szRecKey ){
			C_OldRecordFile::szRecKey = new char [ strlen( szRecKey ) + 1 ];
			strcpy( C_OldRecordFile::szRecKey, szRecKey );
		}
		C_OldRecordFile::lHeadSize = lHeadSize;
		C_OldRecordFile::lRecSize = lRecSize;
		C_OldRecordFile::lCurPos = -1;
		if( C_File::FileSize() == 0 ){
			if( lHeadSize ){
				char c;
				C_File::Seek( lHeadSize - 1, SEEK_SET );
				C_File::Write( &c, 1 );
			}
		}
		C_OldRecordFile::lFileSize = ( C_File::FileSize() - lHeadSize ) / lRecSize;
		R_Seek( 0 );
		Seek( 0, SEEK_SET );
		return( OK );
	}
	return( !OK );
}

/********************/
int
C_OldRecordFile::R_Seek( long lPos )
{
//	if( lPos >= 0 && lPos < lFileSize ){
	if( lPos >= 0 && lPos <= lCurPos ){
		lCurPos = lPos;
		return OK;
	}
//	if( lPos >= lFileSize ){
	if( lPos >= lCurPos ){
		// vamos verificar se o arquivo cresceu
		// (outro processo pode ter adicionado registros)
		C_OldRecordFile::lFileSize = ( C_File::FileSize() - lHeadSize ) / lRecSize;
		if( lPos < lFileSize ){
			lCurPos = lPos;
			return OK;
		}
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_SeekNext( void )
{
	return R_Seek( lCurPos + 1 );
}

/********************/
int
C_OldRecordFile::R_SeekPrevious( void )
{
	return R_Seek( lCurPos - 1 );
}

/********************/
int
C_OldRecordFile::operator [ ] ( int lPos )
{
	return R_Seek( lPos );
}

/********************/
int
C_OldRecordFile::R_Write( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return C_File::Write( szBuffer, lRecSize );
		}
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_Write( long lPos, void *szBuffer )
{
	if( R_Seek( lPos ) == OK ){
		return R_Write( szBuffer );
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_Append( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( lNextAppendLocation, lNextAppendLocation ? SEEK_SET : SEEK_END ) == OK ){
		int iRet = C_File::Write( szBuffer, lRecSize );
		if( iRet == OK ){
			C_OldRecordFile::lFileSize = ( C_File::FileSize() - lHeadSize ) / lRecSize;
//			lFileSize++;
			lCurPos = lFileSize - 1;
		}
		lNextAppendLocation = 0L;
		return iRet;
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_UndoLastAppend()
{
	C_OldRecordFile::lFileSize = ( C_File::FileSize() - lHeadSize ) / lRecSize;
	if( lNextAppendLocation == 0L ){
		lNextAppendLocation = lFileSize - 1;
	}
	return( OK );
}

/********************/
int
C_OldRecordFile::R_Read( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Read( szBuffer, lRecSize ) );
		}
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_Read( long lPos, void *szBuffer )
{
	if( R_Seek( lPos ) == OK ){
		return R_Read( szBuffer );
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_WriteHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( 0, SEEK_SET ) == OK ){
		return C_File::Write( szBuffer, lHeadSize );
	}
	return !OK;
}

/********************/
int
C_OldRecordFile::R_ReadHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( 0, SEEK_SET ) == OK ){
		return C_File::Read( szBuffer, lHeadSize );
	}
	return !OK;
}

/********************/
long
C_OldRecordFile::R_FileSize( void )
{
	C_OldRecordFile::lFileSize = ( C_File::FileSize() - lHeadSize ) / lRecSize;
	return lFileSize;
}

/********************/
long
C_OldRecordFile::R_CurPos( void )
{
	return lCurPos;
}


/********************/
int
C_OldRecordFile::R_Lock( void )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Lock( lRecSize ) );
		}
	}
	return( !OK );
}

/********************/
int
C_OldRecordFile::R_Release( void )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Release( lRecSize ) );
		}
	}
	return( !OK );
}


/********************/
int
C_OldRecordFile::R_LockHead( void )
{
	if( iHeadLocked ){
		++iHeadLocked;
		return( OK );
	}
	long lAux = C_File::CurPos();
	C_File::Seek( 0, SEEK_SET );
	int iRet = C_File::Lock( lHeadSize );
	C_File::Seek( lAux, SEEK_SET );
	if( iRet == OK ){
		iHeadLocked = 1;
	}
	return( iRet );
}

/********************/
int
C_OldRecordFile::R_ReleaseHead( void )
{
	if( iHeadLocked ){
		if( --iHeadLocked == 0 ){
			long lAux = C_File::CurPos();
			C_File::Seek( 0, SEEK_SET );
			int iRet = C_File::Release( lHeadSize );
			C_File::Seek( lAux, SEEK_SET );
			if( iRet != OK ){
				iHeadLocked = 1;
			}
			return( iRet );
		}
	}
	return( OK );
}


/********************/
void
C_OldRecordFile::R_SetHeadKey( char *szHeadKey )
{
	if( C_OldRecordFile::szHeadKey ){
		delete C_OldRecordFile::szHeadKey;
	}
	C_OldRecordFile::szHeadKey = NULL;
	if( szHeadKey ){
		C_OldRecordFile::szHeadKey = new char [ strlen( szHeadKey ) + 1 ];
		strcpy( C_OldRecordFile::szHeadKey, szHeadKey );
	}
}

/********************/
void
C_OldRecordFile::R_SetRecKey( char *szRecKey )
{
	if( C_OldRecordFile::szRecKey ){
		delete C_OldRecordFile::szRecKey;
	}
	C_OldRecordFile::szRecKey = NULL;
	if( szRecKey ){
		C_OldRecordFile::szRecKey = new char [ strlen( szRecKey ) + 1 ];
		strcpy( C_OldRecordFile::szRecKey, szRecKey );
	}
}


/********************/
C_OldRecordFile::~C_OldRecordFile( void )
{
	if( szHeadKey ){
		delete szHeadKey;
	}
	if( szRecKey ){
		delete szRecKey;
	}
}


/****************************************************/
int
C_OldRecordFile::Search( void *pvBuffer, char (*fCmp) ( void *a, void *b ))
{
	char *szAuxBuffer = new char [ lRecSize ];
	if( szAuxBuffer ){
		long lOldPos = lCurPos;
		for( long l = 0; l < lFileSize; l++ ){
			if( R_Seek( l ) == OK ){
				if( Read( szAuxBuffer, lRecSize ) == OK ){
					if( fCmp( pvBuffer, szAuxBuffer ) == OK ){
						return OK;
					}
				} else {
					break;
				}
			} else {
				break;
			}
		}
		delete szAuxBuffer;
		R_Seek( lOldPos );
		return !OK;
	}
	return !OK;
}

