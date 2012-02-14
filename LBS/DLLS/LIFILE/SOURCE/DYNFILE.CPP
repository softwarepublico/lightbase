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

#ifndef	_DYNFILE_
#include	<dynfile.h>
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

void	GetAppFullPath( char *Path, int Size );

#define	LIFILEINIFILE		"LBFILE.INI"	// .ini de lifile

/**********************/
C_DynamicFile::~C_DynamicFile()
{
	if ( szKey ) {
		delete szKey;
	}
}

/**********************/
C_DynamicFile::C_DynamicFile( char *szFileName, BYTE bMagicNumberPar, char *szKeyPar,
	const char *szMode, int iShFlag )
{
	cdfhHead.bMagicNumber = bMagicNumberPar;
	cdfhHead.tfFirstSpace.lNextFreeSpace = 0L;
	cdfhHead.tfFirstSpace.lSpaceSize = 0L;
	szKey = NULL;
	Open( szFileName, bMagicNumberPar, szKeyPar, szMode, iShFlag );
}

/**********************/
C_DynamicFile::C_DynamicFile( BYTE bMagicNumberPar )
{
	szKey = NULL;
	cdfhHead.bMagicNumber = bMagicNumberPar;
	cdfhHead.tfFirstSpace.lNextFreeSpace = 0L;
	cdfhHead.tfFirstSpace.lSpaceSize = 0L;
}

/**********************/
int
C_DynamicFile::Open( char *szFileName, BYTE bMagicNumberPar, char *szKeyPar,
	const char *szMode, int iShFlag )
{
	if( IsOpen() ){
		return( !OK );
	}
	C_File::Open( szFileName, szMode, iShFlag );
	if( IsOpen() ){
		if ( szKey ) {
			delete szKey;
		}
		szKey = NULL;
		if( szKeyPar ){
			szKey = Strdup( szKeyPar );
			if( szKey ){
				TurnOnCripto( szKey );
			}
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
			cdfhHead.bMagicNumber = bMagicNumberPar;
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
C_DynamicFile::D_GetFreeSpace( long lLen )
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
	while( lLen > tfsFreeSpace.lSpaceSize ){
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
			// chegamos ao fim da lista e nao achamos ninguem livre...
			break;
		}
	}

	if ( lLen > tfsFreeSpace.lSpaceSize ) {
		// nao achou ninguem livre com esse tamanho; bota no fim do arquivo
		if( Seek( 0, SEEK_END ) != OK ){
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
		if( Write( &c, 1 ) != OK ){
			ReleaseHead();
			return( (long) LBSE_ERROR );
		}
		// o comportamento a seguir pode nao ser portavel...
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

	// vamos usar o slot achado...

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
	if( tfNewFreeSpace.lSpaceSize >= D_MinSlotSize() ){
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
C_DynamicFile::D_FreeSpace( long lGap, long lLen )
{
	if( !IsOpen() ){
		return( (long) LBSE_ERROR );
	}
	if( lLen >= D_MinSlotSize() ){
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
C_DynamicFile::WriteHead()
{
	long	lAux = CurPos();

	if( Seek( 0, SEEK_SET ) != OK ){
		return( !OK );
	}
	// o cabecalho deste arquivo nao eh criptografado
	BOOL	bCrip = IsCriptoOn();
	TurnOffCripto();
	int iRet = Write( &cdfhHead, sizeof( cdfhHead ) );
	if( bCrip ){
		TurnOnCripto( szKey ); 
	}
	Seek( lAux, SEEK_SET );
	return( iRet );
}


/**********************/
int
C_DynamicFile::ReadHead()
{
	long	lAux = CurPos();

	if( Seek( 0, SEEK_SET ) != OK ){
		return( !OK );
	}

	// o cabecalho deste arquivo nao eh criptografado
	BOOL	bCrip = IsCriptoOn();
	TurnOffCripto();
	int iRet = Read( &cdfhHead, sizeof( cdfhHead ) );
	if( bCrip ){
		TurnOnCripto( szKey );
	}
	Seek( lAux, SEEK_SET );
	return( iRet );
}



/**********************/
int
C_DynamicFile::LockHead( BOOL bWait )
{
	long	lAux = CurPos();
	if( Seek( 0, SEEK_SET ) == OK ){
		if( Lock( sizeof( cdfhHead ), bWait ) == OK ){
			Seek( lAux, SEEK_SET );
			return( OK );
		}
		// tentar novamente
		Sleep( 1000 );
		if( Lock( sizeof( cdfhHead ), bWait ) == OK ){
			Seek( lAux, SEEK_SET );
			return( OK );
		}
		Seek( lAux, SEEK_SET );
	}
	return( !OK );
}


/**********************/
int
C_DynamicFile::ReleaseHead()
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


/**********************/
long
C_DynamicFile::D_MinSlotSize()
{
	char	szFullIniName[ MAXPATH ];

	GetAppFullPath( szFullIniName, MAXPATH-1 );
	strcat( szFullIniName, LIFILEINIFILE );

	long lMinRecSize = GetPrivateProfileInt( "CONFIG", "MINFREEBLOCKSIZE", 50, szFullIniName );

	if ( lMinRecSize < 0 ) {
		lMinRecSize = 0;
	}
	return sizeof( TFreeSpace ) + lMinRecSize;
}
