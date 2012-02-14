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

#ifndef	_OLDDYNFILE_
#include	<olddynf.h>
#endif
#ifndef _CRIPTO_
#include	<cripto.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/**********************/
C_OldDynamicFile::C_OldDynamicFile( char *szFileName, int iMagNum, char *szKey,
	const char *szMode, int iShFlag )
{
	Open( szFileName, iMagNum, szKey, szMode, iShFlag );
}

/**********************/
C_OldDynamicFile::C_OldDynamicFile()
{
	cdfhHead.iMagicNumber = 0;
	cdfhHead.tfFirstSpace.lNextFreeSpace = 0L;
	cdfhHead.tfFirstSpace.lSpaceSize = 0L;
}

/**********************/
int
C_OldDynamicFile::Open( char *szFileName, int iMagNum, char *szKey,
	const char *szMode, int iShFlag )
{
	if( IsOpen() ){
		return( !OK );
	}
	C_File::Open( szFileName, szMode, iShFlag );
	if( IsOpen() ){
		if( szKey ){
			TurnOnCripto( szKey );
		}
		if( FileSize() != 0 ){
			if( ReadHead() == OK ){
//			if( Seek( 0, SEEK_SET ) == OK ){
//				if( Read( &cdfhHead, sizeof( cdfhHead ) ) == OK ){
////				if( cdfhHead.iMagicNumber != iMagNum ){
////					Close();
////				}
//				} else {
//					Close();
//				}
			} else {
				Close();
			}
		} else {
			cdfhHead.tfFirstSpace.lNextFreeSpace = 0L;
			cdfhHead.tfFirstSpace.lSpaceSize = 0L;
			cdfhHead.iMagicNumber = iMagNum;
			if( WriteHead() != OK ){
				Close();
			}
//			if( Seek( 0, SEEK_SET ) == OK ){
//				if( Write( &cdfhHead, sizeof( cdfhHead ) ) != OK ){
//					Close();
//				}
//			} else {
//				Close();
//			}
		}
		return( OK );
	}
	return( !OK );
}

/**********************/
long
C_OldDynamicFile::D_WriteOnFreeSpace( void *szBuffer, long lLen )
{
	if( !IsOpen() ){
		return( (long) LBSE_ERROR );
	}

	long		lPrevPos = sizeof( int );
	long		lOldPos = CurPos();
	TFreeSpace	tfsFreeSpace;
	TFreeSpace	tfPrevFreeSpace;
	TFreeSpace	tfNewFreeSpace;

	// faz lock no header do arquivo
	if( LockHead() != OK ){
		return( LBSE_ERROR );
	}
	// rele^ o header do arquivo
	if( ReadHead() != OK ){
		return( ReleaseHead() );
	}
	tfsFreeSpace = cdfhHead.tfFirstSpace;
	Seek( sizeof( cdfhHead ), SEEK_SET );
//	while( ( tfsFreeSpace.lSpaceSize <= lLen ) ){
	while( ( tfsFreeSpace.lSpaceSize < lLen ) ){
		tfPrevFreeSpace = tfsFreeSpace;
		lPrevPos = CurPos() - sizeof( TFreeSpace );
		if( tfsFreeSpace.lNextFreeSpace ){
			if( Seek( tfsFreeSpace.lNextFreeSpace, SEEK_SET ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Read( &tfsFreeSpace, sizeof( TFreeSpace ) ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
		} else {
			if( Seek( 0, SEEK_END ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Write( szBuffer, lLen ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			// regrava o header do arquivo
			WriteHead();
			ReleaseHead();
			return CurPos() - lLen;
		}
	}

	/* volta o TFreeSpace analizado */
	if( Seek( -((long)sizeof( TFreeSpace )), SEEK_CUR ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}

	long lReturn = CurPos();

	tfNewFreeSpace.lNextFreeSpace = tfsFreeSpace.lNextFreeSpace;
	tfNewFreeSpace.lSpaceSize = tfsFreeSpace.lSpaceSize - lLen;
	if( Write( szBuffer, lLen ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}
	if( tfNewFreeSpace.lSpaceSize >= sizeof( TFreeSpace ) ){
		tfPrevFreeSpace.lNextFreeSpace += lLen;
		if( Write( &tfNewFreeSpace, sizeof( TFreeSpace ) ) != OK ){
			/* não é fatal não */
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
	} else {
		tfPrevFreeSpace.lNextFreeSpace = tfsFreeSpace.lNextFreeSpace;
	}
	if( Seek( lPrevPos, SEEK_SET ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}
	if( Write( &tfPrevFreeSpace, sizeof( TFreeSpace ) ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}
	if( lPrevPos == sizeof( int ) ){
		/* atualiza a estrutura da cabeca */
		cdfhHead.tfFirstSpace = tfPrevFreeSpace;
	}
	// regrava o header do arquivo
	WriteHead();
	ReleaseHead();
	return lReturn;
}

/**********************/
long
C_OldDynamicFile::D_GetFreeSpace( long lLen )
{
	if( !IsOpen() ){
		return( (long) LBSE_ERROR );
	}

	long		lPrevPos = sizeof( int );
	long		lOldPos = CurPos();
	TFreeSpace	tfsFreeSpace;
	TFreeSpace	tfPrevFreeSpace;
	TFreeSpace	tfNewFreeSpace;
	char 		c = 0;

	// faz lock no header do arquivo
	if( LockHead() != OK ){
		return( LBSE_ERROR );
	}
	// rele^ o header do arquivo
	if( ReadHead() != OK ){
		return( ReleaseHead() );
	}
	tfsFreeSpace = cdfhHead.tfFirstSpace;
	Seek( sizeof( cdfhHead ), SEEK_SET );
//	while( ( tfsFreeSpace.lSpaceSize <= lLen ) ){
	while( ( tfsFreeSpace.lSpaceSize < lLen ) ){
		tfPrevFreeSpace = tfsFreeSpace;
		lPrevPos = CurPos() - sizeof( TFreeSpace );
		if( tfsFreeSpace.lNextFreeSpace ){
			if( Seek( tfsFreeSpace.lNextFreeSpace, SEEK_SET ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Read( &tfsFreeSpace, sizeof( TFreeSpace ) ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
		} else {
			if( Seek( 0, SEEK_END ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Write( &c, 1 ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Seek( lLen - 1, SEEK_CUR ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			if( Write( &c, 1 ) != OK ){
				ReleaseHead();
				return( (long) LBSE_ERROR );
			}
			// regrava o header do arquivo
			WriteHead();
			ReleaseHead();
			return CurPos() - lLen;
		}
	}

	/* volta o TFreeSpace analizado */
	if( Seek( -((long)sizeof( TFreeSpace )), SEEK_CUR ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}

	long lReturn = CurPos();

	tfNewFreeSpace.lNextFreeSpace = tfsFreeSpace.lNextFreeSpace;
	tfNewFreeSpace.lSpaceSize = tfsFreeSpace.lSpaceSize - lLen;
	if( Write( &c, 1, lLen ) < (size_t) lLen ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}
	if( tfNewFreeSpace.lSpaceSize >= sizeof( TFreeSpace ) ){
		tfPrevFreeSpace.lNextFreeSpace += lLen;
		if( Write( &tfNewFreeSpace, sizeof( TFreeSpace ) ) != OK ){
			/* não é fatal não */
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
	} else {
		tfPrevFreeSpace.lNextFreeSpace = tfsFreeSpace.lNextFreeSpace;
	}
	if( Seek( lPrevPos, SEEK_SET ) != OK ){
		ReleaseHead();
		return( (long) LBSE_ERROR );
	}
	if( Write( &tfPrevFreeSpace, sizeof( TFreeSpace ) ) != OK ){
		return( (long) LBSE_ERROR );
		ReleaseHead();
	}
	if( lPrevPos == sizeof( int ) ){
		/* atualiza a estrutura da cabeca */
		cdfhHead.tfFirstSpace = tfPrevFreeSpace;
	}
	// regrava o header do arquivo
	WriteHead();
	ReleaseHead();
	return lReturn;
}

/**********************/
long
C_OldDynamicFile::D_FreeSpace( long lGap, long lLen )
{
	if( !IsOpen() ){
		return( (long) LBSE_ERROR );
	}
	if( lLen >= sizeof( TFreeSpace ) ){
		// faz lock no header do arquivo
		if( LockHead() != OK ){
			return( LBSE_ERROR );
		}
		// rele^ o header do arquivo
		if( ReadHead() != OK ){
			return( ReleaseHead() );
		}
		TFreeSpace	tfNewFreeSpace;

		tfNewFreeSpace.lNextFreeSpace = cdfhHead.tfFirstSpace.lNextFreeSpace;
		tfNewFreeSpace.lSpaceSize = lLen;
		cdfhHead.tfFirstSpace.lNextFreeSpace = lGap;

		if( Seek( lGap, SEEK_SET ) != OK ){
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
		if( Write( &tfNewFreeSpace, sizeof( TFreeSpace ) ) != OK ){
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
//		if( Seek( sizeof( int ), SEEK_SET ) ){ /* Depois do número mágico */
//			ReleaseHead();
//			return( (long) LBSE_FATAL );
//		}
//		if( Write( &(cdfhHead.tfFirstSpace), sizeof( TFreeSpace ) ) != OK ){
//			ReleaseHead();
//			return( (long) LBSE_FATAL );
//		}
		WriteHead();
		ReleaseHead();
	}
	return lGap;
}


/**********************/
int
C_OldDynamicFile::WriteHead()
{
	long	lAux = CurPos();

	if( Seek( 0, SEEK_SET ) != OK ){
		return( !OK );
	}

	if( Write( &cdfhHead, sizeof( cdfhHead ) ) == OK ){
		Seek( lAux, SEEK_SET );
		return( OK );
	}
	Seek( lAux, SEEK_SET );
	return( !OK );
}


/**********************/
int
C_OldDynamicFile::ReadHead()
{
	long	lAux = CurPos();

	if( Seek( 0, SEEK_SET ) != OK ){
		return( !OK );
	}

	if( Read( &cdfhHead, sizeof( cdfhHead ) ) == OK ){
		Seek( lAux, SEEK_SET );
		return( OK );
	}
	Seek( lAux, SEEK_SET );
	return( !OK );
}



/**********************/
int
C_OldDynamicFile::LockHead()
{
	long	lAux = CurPos();
	if( Seek( 0, SEEK_SET ) == OK ){
		if( Lock( sizeof( cdfhHead ) ) == OK ){
			Seek( lAux, SEEK_SET );
			return( OK );
		}
		// tentar novamente
		Sleep( 1000 );
		if( Lock( sizeof( cdfhHead ) ) == OK ){
			Seek( lAux, SEEK_SET );
			return( OK );
		}
		Seek( lAux, SEEK_SET );
	}
	return( !OK );
}


/**********************/
int
C_OldDynamicFile::ReleaseHead()
{
	long	lAux = CurPos();
	if( Seek( 0, SEEK_SET ) == OK ){
		if( Release( sizeof( cdfhHead ) ) == OK ){
			Seek( lAux, SEEK_SET );
			return( OK );
		}
		Seek( lAux, SEEK_SET );
	}
	return( !OK );
}


