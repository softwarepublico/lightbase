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


#ifndef	_OLDTYPES_H_
#include "oldtypes.h"
#endif
#ifndef	_OLDLB1_
#include	<oldlb1cl.h>
#endif	// _LB1_
#ifndef	_OLDLB2_
#include	<oldlb2cl.h>
#endif	// _LB2_
#ifndef	_OLDLB3_
#include	<oldlb3cl.h>
#endif	// _LB3_
#ifndef	_OLDLB4_
#include	<oldlb4cl.h>
#endif	// _LB4_
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include <LB4Struct.h>



#define	BEFORECRYPTO_MAGICNUMBER	3


/***************************************************************************************/
/*******************************************  LB1  *************************************/
/***************************************************************************************/

C_OldLB1::C_OldLB1( char *szFileName, char *szRecKey, const char *szMode, int iShFlag ):
	C_OldRecordFile( szFileName, sizeof( TOldControlRecHead ),
		sizeof( TControlRec ), LB1HEADKEY, szRecKey, szMode, iShFlag )
{
	R_ReadHead();		
}

C_OldLB1::C_OldLB1()
{
}

int 
C_OldLB1::Open( char *szFileName, char *szRecKey, const char *szMode, int iShFlag )
{
	BOOL bEx = C_File::Exist( szFileName );
	if( C_OldRecordFile::Open( szFileName, sizeof( TOldControlRecHead ),
		sizeof( TControlRec ), LB1HEADKEY, szRecKey, szMode, iShFlag ) == OK ){
		if( bEx ){
			return( R_ReadHead() );
		}
		int i = 0;
		while( R_LockHead() != OK ){
			if( ++i	== 100 ){
				Close();
				return( !OK );
			}
		}
		if( C_OldRecordFile::R_WriteHead( &tcrHead ) == OK ){
			R_ReleaseHead();
			return( OK );
		}
	}
	return( !OK );
}

int	
C_OldLB1::LB1_LockHead()
{
	if( R_LockHead() == OK ){
		if( iHeadLocked == 1 ){
			R_ReadHead();
		}
		return( OK );
	}
	return( E_LOCK );
}

int	
C_OldLB1::LB1_ReleaseHead()
{
	if( iHeadLocked == 1 ){
		C_OldRecordFile::R_WriteHead( &tcrHead );
	}
	return( R_ReleaseHead() );
}

int	
C_OldLB1::R_WriteHead()
{
	if( R_LockHead() == OK ){
		C_OldRecordFile::R_WriteHead( &tcrHead );
		R_ReleaseHead();
		return( OK );
	}
	return( E_LOCK );
}

int	
C_OldLB1::R_WriteHead( TOldControlRecHead *ptAux )
{
	return( C_OldRecordFile::R_WriteHead( ptAux ) );
}

int	
C_OldLB1::R_ReadHead()
{
	return( C_OldRecordFile::R_ReadHead( &tcrHead ) );
}

int	
C_OldLB1::R_ReadHead( TOldControlRecHead *ptAux )
{
	return( C_OldRecordFile::R_ReadHead( ptAux ) );
}


void
C_OldLB1::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Encrypt( pvBuf, szKey, tsSize );
}

void
C_OldLB1::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Decrypt( pvBuf, szKey, tsSize );
}



	
/***************************************************************************************/
/*******************************************  LB2  *************************************/
/***************************************************************************************/

C_OldLB2::C_OldLB2( char *szFileName, char *szKey, const char *szMode, int iShFlag ):
	C_OldDynamicFile( szFileName, BEFORECRYPTO_MAGICNUMBER, szKey, szMode, iShFlag )
{}

C_OldLB2::C_OldLB2()
{
}

int 
C_OldLB2::Open( char *szFileName, char *szKey, const char *szMode, int iShFlag )
{
	return( C_OldDynamicFile::Open( szFileName, BEFORECRYPTO_MAGICNUMBER, szKey, szMode, iShFlag ) );
}


void
C_OldLB2::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Encrypt( pvBuf, szKey, tsSize );
}

void
C_OldLB2::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Decrypt( pvBuf, szKey, tsSize );
}


/***************************************************************************************/
/*******************************************  LB3  *************************************/
/***************************************************************************************/

C_OldLB3::C_OldLB3( char *szFileName, char *szRecKey, const char *szMode, int iShFlag, int iSlotNum ):
	C_OldRecordFile( szFileName, TOldStructHeadRec::SizeOf( iSlotNum ),
		sizeof( TStructRec ), LB3HEADKEY, szRecKey, szMode, iShFlag )
{
}

C_OldLB3::C_OldLB3()
{
}

int 
C_OldLB3::Open( char *szFileName, char *szRecKey, const char *szMode, int iShFlag, int iSlotNum )
{
	int	iRet = C_OldRecordFile::Open( szFileName, TOldStructHeadRec::SizeOf( iSlotNum ),
		sizeof( TStructRec ), LB3HEADKEY, szRecKey, szMode, iShFlag );

	return( iRet );
}

int	
C_OldLB3::LB3_LockHead( TOldStructHeadRec *pAux )
{
	if( R_LockHead() == OK ){
		if( iHeadLocked == 1 ){
			C_OldRecordFile::R_ReadHead( pAux );
			memcpy( &tsHead, pAux, sizeof( tsHead ) );
		}
		return( OK );
	}
	return( E_LOCK );
}

int	
C_OldLB3::LB3_ReleaseHead( TOldStructHeadRec *pAux )
{
	if( iHeadLocked == 1 ){
		memcpy( &tsHead, pAux, sizeof( tsHead ) );
		C_OldRecordFile::R_WriteHead( pAux );
	}
	return( R_ReleaseHead() );
}

void
C_OldLB3::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Encrypt( pvBuf, szKey, tsSize );
}

void
C_OldLB3::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Decrypt( pvBuf, szKey, tsSize );
}



/***************************************************************************************/
/*******************************************  LB4  *************************************/
/***************************************************************************************/


C_OldLB4::C_OldLB4( char *szFileName, char *szKey, const char *szMode, int iShFlag ):
	C_OldDynamicFile( szFileName, BEFORECRYPTO_MAGICNUMBER, szKey, szMode, iShFlag )
{}

C_OldLB4::C_OldLB4()
{
}

int 
C_OldLB4::Open( char *szFileName, char *szKey, const char *szMode, int iShFlag )
{
	return( C_OldDynamicFile::Open( szFileName, BEFORECRYPTO_MAGICNUMBER, szKey, szMode, iShFlag ) );
}


void
C_OldLB4::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Encrypt( pvBuf, szKey, tsSize );
}

void
C_OldLB4::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	C_File::Decrypt( pvBuf, szKey, tsSize );
}


int 
C_LB1_V3::Open( char *szFileName, char *szRecKey, const char *szMode, int iShFlag )
{
	BOOL bEx = C_File::Exist( szFileName );
	if( C_RecordFile::Open( szFileName, sizeof( TControlRecHead ),
		sizeof( TControlRec_V3 ), LB1HEADKEY, szRecKey, szMode, iShFlag ) == OK ){
		if( bEx ){
			int iRet = R_ReadHead();
			return( iRet );
		}
		if( C_RecordFile::R_WriteHead( &tcrHead ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}

