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

#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef _CRIPTO_
#include	<cripto.h>
#endif
#ifndef _STRDUP_H_
#include	<Strdup.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif



long C_RecordFile::lNextAppendLocation = 0L;

/********************/
C_RecordFile::C_RecordFile()
{
	lHeadSize = lRecSize = 0;
	lCurPos = lFileSize = -1;
	szHeadKey = NULL;
	szRecKey = NULL;
	iHeadLocked = 0;
	bMagicNumber = 0;
}

/********************/
C_RecordFile::C_RecordFile( BYTE bMagicNumberPar )
{
	lHeadSize = lRecSize = 0;
	lCurPos = lFileSize = -1;
	szHeadKey = NULL;
	szRecKey = NULL;
	iHeadLocked = 0;
	bMagicNumber = bMagicNumberPar;
}

/********************/
C_RecordFile::C_RecordFile( char* szFileNamePar, BYTE bMagicNumberPar, long lHeadSize, long lRecSize,
	char *szHeadKey, char *szRecKey,
	 const char *szMode, int iShFlag, BOOL bWait ) :
	 szHeadKey( NULL ),
	 szRecKey( NULL )
{
	bMagicNumber = bMagicNumberPar;
	Open( szFileNamePar, lHeadSize, lRecSize, szHeadKey, szRecKey, szMode, iShFlag, bWait );
	iHeadLocked = 0;
}


/********************/
int
C_RecordFile::Open( char* szFileNamePar, BYTE bMagicNumberPar, long lHeadSize, long lRecSize,
	char *szHeadKey, char *szRecKey,
	 const char *szMode, int iShFlag, BOOL bWait )
{
	bMagicNumber = bMagicNumberPar;
	int iRet = Open( szFileNamePar, lHeadSize, lRecSize, szHeadKey, szRecKey, szMode, iShFlag, bWait );
	iHeadLocked = 0;
	return( iRet );
}


/********************/
int
C_RecordFile::Open( char* szFileNamePar, long lHeadSize, long lRecSize,
	char *szHeadKey, char *szRecKey,
	 const char *szMode, int iShFlag, BOOL bWait )
{
	if( IsOpen() ){
		return( !OK );
	}
	C_File::Open( szFileNamePar, szMode, iShFlag, bWait );
	if( IsOpen() ){
		C_File::TurnOffCripto();
		if( C_File::FileSize() == 0 ){
			// arquivo acabou de ser criado. vamos gravar o 
			// numero magico.
			if( C_File::Seek( 0, SEEK_SET ) != OK ){
				C_File::Close();
				return( !OK );
			}
			if( C_File::Write( &bMagicNumber, sizeof( bMagicNumber ) ) != OK ){
				C_File::Close();
				return( !OK );
			}
			if( lHeadSize ){
				char c = 0;
//				C_File::Seek( lHeadSize + sizeof( bMagicNumber ) - 1, SEEK_SET );
//				C_File::Write( &c, 1 );
				C_File::Seek( sizeof( bMagicNumber ), SEEK_SET );
				for( int i = 0; i < lHeadSize; i++ ){
					C_File::Write( &c, 1 );
				}
			}
		} else {
			// arquivo ja' existia. vamos comparar o numero
			// magico dele (apenas se o numero magico indicado
			// for diferente de zero).
			if( bMagicNumber > 0 ){
				if( C_File::Seek( 0, SEEK_SET ) != OK ){
					C_File::Seek( 0, SEEK_SET );
					C_File::Release( sizeof( bMagicNumber )  );
					C_File::Close();
					return( !OK );
				}
				BYTE bMgN;
				if( C_File::Read( &bMgN, sizeof( bMgN ) ) != OK ){
					C_File::Seek( 0, SEEK_SET );
					C_File::Release( sizeof( bMagicNumber )  );
					C_File::Close();
					return( !OK );
				}
				if( bMgN != bMagicNumber ){
					C_File::Close();
					return( !OK );
				}
			}
		}
		if( C_RecordFile::szHeadKey ){
			delete C_RecordFile::szHeadKey;
			C_RecordFile::szHeadKey = NULL;
		}
		if( szHeadKey ){
			C_RecordFile::szHeadKey = new char [ strlen( szHeadKey ) + 1 ];
			strcpy( C_RecordFile::szHeadKey, szHeadKey );
		}
		if( C_RecordFile::szRecKey ){
			delete C_RecordFile::szRecKey;
			C_RecordFile::szRecKey = NULL;
		}
		if( szRecKey ){
			C_RecordFile::szRecKey = new char [ strlen( szRecKey ) + 1 ];
			strcpy( C_RecordFile::szRecKey, szRecKey );
		}
		C_RecordFile::lHeadSize = lHeadSize;
		C_RecordFile::lRecSize = lRecSize;
		C_RecordFile::lCurPos = -1;
		C_RecordFile::lFileSize = ( C_File::FileSize() - lHeadSize - sizeof( bMagicNumber ) ) / lRecSize;
		R_Seek( 0 );
//		Seek( 0, SEEK_SET );
		return( OK );
	}
	return( !OK );
}

/********************/
int
C_RecordFile::R_Seek( long lPos )
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
		C_RecordFile::lFileSize = ( C_File::FileSize() - lHeadSize - sizeof( bMagicNumber ) ) / lRecSize;
		if( lPos < lFileSize ){
			lCurPos = lPos;
			return OK;
		}
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_SeekNext( void )
{
	return R_Seek( lCurPos + 1 );
}

/********************/
int
C_RecordFile::R_SeekPrevious( void )
{
	return R_Seek( lCurPos - 1 );
}

/********************/
int
C_RecordFile::operator [ ] ( int lPos )
{
	return R_Seek( lPos );
}

void
C_RecordFile::TurnOnCriptoRec( void )
{
	szRecKey = Strdup(TURN_ON);
}

void
C_RecordFile::TurnOffCriptoRec( void )
{
	delete szRecKey;
	szRecKey = NULL;
}



/********************/
int
C_RecordFile::R_Write( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return C_File::Write( szBuffer, lRecSize );
		}
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_Write( void *szBuffer, long lOffSet, long lSize )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + (lCurPos * lRecSize) + lOffSet, SEEK_SET ) == OK ){
			return C_File::Write( ((char*) szBuffer) + lOffSet, lSize );
		}
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_Write( long lPos, void *szBuffer )
{
	if( R_Seek( lPos ) == OK ){
		return R_Write( szBuffer );
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_Append( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( 0, SEEK_END ) == OK ){
		int iRet = C_File::Write( szBuffer, lRecSize );
		if( iRet == OK ){
			C_RecordFile::lFileSize = ( C_File::FileSize() - lHeadSize - sizeof( bMagicNumber ) ) / lRecSize;
			lCurPos = lFileSize - 1;
		}
		lNextAppendLocation = 0L;
		return iRet;
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_UndoLastAppend()
{
	return( OK );
}

/********************/
int
C_RecordFile::R_Read( void *szBuffer )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Read( szBuffer, lRecSize ) );
		}
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_Read( void *szBuffer, long lOffSet, long lSize )
{
	if( szRecKey ){
		TurnOnCripto( szRecKey );
	} else {
		TurnOffCripto();
	}
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + (lCurPos * lRecSize) + lOffSet, SEEK_SET ) == OK ){
			return ( C_File::Read( ((char*) szBuffer) + lOffSet, lSize ) );
		}
	}
	return !OK;
}

/********************/
int
C_RecordFile::R_Read( long lPos, void *szBuffer )
{
	if( R_Seek( lPos ) == OK ){
		return R_Read( szBuffer );
	}
	return !OK;
}

void
C_RecordFile::TurnOnCriptoHead( void )
{
	szHeadKey = Strdup(TURN_ON);
}

void
C_RecordFile::TurnOffCriptoHead( void )
{
	delete szHeadKey;
	szHeadKey = NULL;
}


/********************/
int
C_RecordFile::R_WriteHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( sizeof( bMagicNumber ), SEEK_SET ) != OK ){
		return( !OK );
	}
	return C_File::Write( szBuffer, lHeadSize );
}

/********************/
int
C_RecordFile::R_ReadHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( sizeof( bMagicNumber ), SEEK_SET ) != OK ){
		return( !OK );
	}
	return C_File::Read( szBuffer, lHeadSize );
}

/********************/
long
C_RecordFile::R_FileSize( void )
{
	C_RecordFile::lFileSize = ( C_File::FileSize() - lHeadSize - sizeof( bMagicNumber ) ) / lRecSize;
	return lFileSize;
}

/********************/
long
C_RecordFile::R_CurPos( void )
{
	return lCurPos;
}


/********************/
int
C_RecordFile::R_Lock( BOOL bWait )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Lock( lRecSize, bWait ) );
		}
	}
	return( !OK );
}

/********************/
int
C_RecordFile::R_Lock( long lOffSet, long lSize, BOOL bWait )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + (lCurPos * lRecSize) + lOffSet, SEEK_SET ) == OK ){
			return ( C_File::Lock( lSize , bWait ) );
		}
	}
	return( !OK );
}

/********************/
int
C_RecordFile::R_Release( void )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + lCurPos * lRecSize, SEEK_SET ) == OK ){
			return ( C_File::Release( lRecSize ) );
		}
	}
	return( !OK );
}


/********************/
int
C_RecordFile::R_Release( long lOffSet, long lSize )
{
	if( lCurPos >= 0 ){
		if( C_File::Seek( lHeadSize + sizeof( bMagicNumber ) + (lCurPos * lRecSize) + lOffSet, SEEK_SET ) == OK ){
			return ( C_File::Release( lSize ) );
		}
	}
	return( !OK );
}


/********************/
int
C_RecordFile::R_LockHead( BOOL bWait )
{
	if( iHeadLocked ){
		++iHeadLocked;
		return( OK );
	}
	long lAux = C_File::CurPos();
	C_File::Seek( sizeof( bMagicNumber ), SEEK_SET );
	int iRet = C_File::Lock( lHeadSize, bWait );
	C_File::Seek( lAux, SEEK_SET );
	if( iRet == OK ){
		iHeadLocked = 1;
	}
	return( iRet );
}

/********************/
int
C_RecordFile::R_ReleaseHead( void )
{
	if( iHeadLocked ){
		if( --iHeadLocked == 0 ){
			long lAux = C_File::CurPos();
			C_File::Seek( sizeof( bMagicNumber ), SEEK_SET );
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
C_RecordFile::R_SetHeadKey( char *szHeadKey )
{
	if( C_RecordFile::szHeadKey ){
		delete C_RecordFile::szHeadKey;
	}
	C_RecordFile::szHeadKey = NULL;
	if( szHeadKey ){
		C_RecordFile::szHeadKey = new char [ strlen( szHeadKey ) + 1 ];
		strcpy( C_RecordFile::szHeadKey, szHeadKey );
	}
}

/********************/
void
C_RecordFile::R_SetRecKey( char *szRecKey )
{
	if( C_RecordFile::szRecKey ){
		delete C_RecordFile::szRecKey;
	}
	C_RecordFile::szRecKey = NULL;
	if( szRecKey ){
		C_RecordFile::szRecKey = new char [ strlen( szRecKey ) + 1 ];
		strcpy( C_RecordFile::szRecKey, szRecKey );
	}
}


/********************/
C_RecordFile::~C_RecordFile( void )
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
C_RecordFile::Search( void *pvBuffer, char (*fCmp) ( void *a, void *b ))
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

