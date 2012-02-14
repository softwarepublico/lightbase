/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o t�tulo
"LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef	_IDXOFF_H_
#include	<idxoffcl.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif

#define	IDXNUM	1000

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/***
***/
C_IDXOFF::C_IDXOFF()
{
}

/***
***/
C_IDXOFF::~C_IDXOFF()
{
	CloseIndex();
}

/***
***/
int
C_IDXOFF::CreateIndex( char *szIndexName )
{
	int	iRet = cfFile.Open( szIndexName, CRYPTO_MAGICNUMBER, 0, sizeof( int ), NULL, NULL, "wb" );
	if( iRet == OK ){
		cfFile.Close();
	}
	return( iRet == OK ? OK : !OK );
}


/***
***/
int
C_IDXOFF::CloseIndex()
{
	cfFile.Close();
	return( OK );
}

/***
***/
BOOL
C_IDXOFF::IsOpen()
{
	return( cfFile.IsOpen() );
}

/***
***/
int
C_IDXOFF::OpenIndex( char *szIndexName )
{
	int	iRet = cfFile.Open( szIndexName, CRYPTO_MAGICNUMBER, 0, sizeof( int ), NULL, NULL, "rb+", SH_DENYRW, TRUE );
	return( iRet == OK ? OK : !OK );
}


/***
	retorna o primeiro grupo de bits do arquivo
***/
int
C_IDXOFF::GetFirstGroupOfBits( int *piRet )
{
	if( cfFile.R_FileSize() > 0 ){
		if( cfFile.R_Seek( 0 ) == OK ){
			if( cfFile.R_Read( piRet ) == OK ){
				return( OK );
			}
		}
	}
	return( !OK );
}



/***
	retorna o proximo grupo de bits do arquivo
***/
int
C_IDXOFF::GetNextGroupOfBits( int *piRet )
{
	if( cfFile.R_SeekNext() == OK ){
		if( cfFile.R_Read( piRet ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}



/***
	retorna o grupo de bits correspondente ao n-esimo registro de LB1
***/
int
C_IDXOFF::GetGroupOfBits( long lLB1Pos, int *piRet )
{
	long	lFilePos = (lLB1Pos / (sizeof( int )*8));

	if( cfFile.R_Seek( lFilePos ) == OK ){
		if( cfFile.R_Read( piRet ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}

/***
	liga um bit em uma posicao do arquivo
	referente ao n-esimo registro de LB1
***/
int
C_IDXOFF::AddBitValue( long lLB1Pos )
{
	long	lFilePos = (lLB1Pos / (sizeof( int )*8));
	long	lFileSize = cfFile.R_FileSize();
	int		lShift = (lLB1Pos % (sizeof(int)*8));
	int		iValue;
	int		iBit = 0x80000000;

	// ligar o bit correto dentro de um grupo de bits
	for( int i = 0; i < lShift; i++ ){
		iBit = ((iBit >> 1) & ~iBit);
	}

	if( lFilePos >= lFileSize ){
		for( long l = lFileSize; l <= lFilePos; l++ ){
			int	iValAux = 0;
			if( cfFile.R_Append( &iValAux ) != OK ){
				return( !OK );
			}
		}
	}
	if( cfFile.R_Seek( lFilePos ) == OK ){
		if( cfFile.R_Read( &iValue ) != OK ){
			return( !OK );
		}
		iValue |= iBit;
		if( cfFile.R_Write( &iValue ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}


/***
	desliga um bit em uma posicao do arquivo
	referente ao n-esimo registro de LB1
***/
int
C_IDXOFF::DelBitValue( long lLB1Pos )
{
	long	lFilePos = (lLB1Pos / (sizeof( int )*8));
	long	lFileSize = cfFile.R_FileSize();
	int		lShift = (lLB1Pos % (sizeof(int)*8));
	int		iValue;
	int		iBit = 0x80000000;

	// ligar o bit correto dentro de um grupo de bits
	for( int i = 0; i < lShift; i++ ){
		iBit = ((iBit >> 1) & ~iBit);
	}
	// inverter os bits
	iBit = ~iBit;

	if( lFilePos >= lFileSize ){
		return( !OK );
	}
	if( cfFile.R_Seek( lFilePos ) == OK ){
		if( cfFile.R_Read( &iValue ) != OK ){
			return( !OK );
		}
		iValue &= iBit;
		if( cfFile.R_Write( &iValue ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}

/***
***/
long
C_IDXOFF::GetNumRecordsLogged()
{
	long	lFileSize = cfFile.R_FileSize();
	return( lFileSize * (sizeof( int )*8) );
/*
	long	lNumBits = lFileSize * (sizeof( int )*8);
	int		iAux;
	int		iBit = 0x00000001;

	if( cfFile.R_Seek( lFileSize - 1 ) != OK ){
		return( 0 );
	}
	if( cfFile.R_Read( &iAux ) != OK ){
		return( 0 );
	}
	int	i = 0;
	do{
		for( i = 0; i < (sizeof( int )*8); i++ ){
			if( iAux & iBit ){
				break;
			}
			iBit = (iBit << 1);
		}
		if( i < (sizeof( int )*8) ){
			break;
		}
		if( cfFile.R_SeekPrevious() != OK ){
			return( 0 );
		}
		if( cfFile.R_Read( &iAux ) != OK ){
			return( 0 );
		}
		lNumBits -= (sizeof( int )*8);
	} while( TRUE );
	return( lNumBits - i );
*/
}

