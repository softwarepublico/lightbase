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
// Module: LBFILES.CPP
// Description:
//
//	LB1, 2, 3, 4 class methods file.
//
// Programmer:	Adriano Sergio R. de Souza
//		Alessandro A. Jatoba'
//
// Last update: 16/10/95
//

#ifndef	_LB1_
#include	<lb1cl.h>
#endif	// _LB1_
#ifndef	_LB2_
#include	<lb2cl.h>
#endif	// _LB2_
#ifndef	_LB3_
#include	<lb3cl.h>
#endif	// _LB3_
#ifndef	_LB4_
#include	<lb4cl.h>
#endif	// _LB4_
#ifndef	_CRYPT_H_
extern "C" {
#include	<crypt.h>
}
// para personalizacao
extern "C" {
#include	<personcl.h>
}
#endif

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#include <LB4Struct.h>


#define	LIFILEINIFILE			"LBFILE.INI"	// .ini de lifile

void	GetAppFullPath( char *Path, int Size );

/***************************************************************************************/
/*******************************************  LB1  *************************************/
/***************************************************************************************/

C_LB1::C_LB1( char *szFileName, char *szRecKey, const char *szMode, int iShFlag ):
	C_RecordFile( szFileName, 0, sizeof( TControlRecHead ),
		sizeof( TControlRec ), LB1HEADKEY, szRecKey, szMode, iShFlag )
{
	R_ReadHead();		
}

C_LB1::C_LB1( ) : C_RecordFile( 0 )
{
}

int 
C_LB1::Open( char *szFileName, char *szRecKey, const char *szMode, int iShFlag )
{
	BOOL bEx = C_File::Exist( szFileName );
	if( C_RecordFile::Open( szFileName, sizeof( TControlRecHead ),
		sizeof( TControlRec ), LB1HEADKEY, szRecKey, szMode, iShFlag ) == OK ){
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

/***
	FORMATO DO ARQUIVO DE LOCK UTILIZADO NA COPIA REDE DO LBS:

	O arquivo eh composto de:
		- um numero magico, igual ao da base.
		- um header, que eh um short int, indicando qual o ultimo numero
		  utilizado para entrar na fila
		- registros short int, indicando ordem na fila. nao existem numeros repetidos.
***/
int	
C_LB1::LB1_LockHead( BOOL bRead )
{
	if( iHeadLocked ){
		++iHeadLocked;
		return( OK );
	}
	if( ::GetTypeInt() == PE_REDE  && iHeadLocked < 1 ){
		// entrar no arquivo de lock
		char	szLockFileName[ MAXFILE ];
		short	siHead = 0;
		short	siInfo = 0;
		char	*szAux;
		long	lPos = 0;
		BOOL	bCreated = FALSE;
		int		iRet;

		++iHeadLocked;

		strcpy( szLockFileName, GetFileName() );
		szAux = strrchr( szLockFileName, '.' );
		if( !szAux ){
			strcat( szLockFileName, ".NET" );
		} else {
			strcpy( szAux, ".NET" );
		}

		C_RecordFile	cfNetFile( CRYPTO_MAGICNUMBER );
		
		while( (iRet = cfNetFile.Open( szLockFileName, 
								sizeof( short ), sizeof( short ), 
								NULL, "RECKEY", NULL, 
								SH_DENYNO, TRUE )) == E_LOCK ){
			Sleep( 200 );
		}
		if( iRet != OK ){
			return( iRet );
		}

		// travar o header do arquivo (o primeiro short int)
		while( cfNetFile.R_LockHead() != OK ){
			Sleep( 200 );
		}

		// tentar ler o header. se nao conseguirmos, eh porque ele nao existe e, 
		// portanto, poderemos cria-lo zerado.
		if( cfNetFile.R_ReadHead( &siHead ) != OK ){
			siHead = 0;
			cfNetFile.R_WriteHead( &siHead );
		}

		// incrementar o numero contido no header, para indicar que entramos
		// no arquivo.
		siHead++;

		// procurar um buraco livre no arquivo.
		siInfo = -1;
		if( cfNetFile.R_Seek( 0 ) == OK ){
			while( cfNetFile.R_Read( &siInfo ) == OK ){
				if( siInfo <= 0 ){
					// buraco livre.
					siInfo = siHead;
					cfNetFile.R_Write( &siInfo );
					lPos = cfNetFile.R_CurPos();
					break;
				}
				if(	cfNetFile.R_SeekNext() != OK ){
					// acabou.
					siInfo = -1;
					break;
				}
			}
		}
		if( siInfo <= -1 ){
			// nao ha' buracos livres no arquivo. vamos adicionar uma entrada.
			siInfo = siHead;
			cfNetFile.R_Append( &siInfo );
			lPos = cfNetFile.R_CurPos();
		}

		// regravar o header
		cfNetFile.R_WriteHead( &siHead );

		// liberar o header do arquivo
		cfNetFile.R_ReleaseHead();

		// ficar lendo o arquivo, para ver se chegou a nossa vez.
		while( siInfo > 1 ){
			if( cfNetFile.R_Seek( lPos ) != OK ){
				return( E_REMOVEDFILE );
			}
			cfNetFile.R_Read( &siInfo );
			Sleep( 500 );					// 1/2 segundo
		}

		// chegou a nossa vez...
		if( iHeadLocked == 1 && bRead ){
			R_ReadHead();
		}
		return( OK );
//		if( ::GetTypeInt() == PE_REDE ){
			// bosta. fudeu em alguma coisa. vamos chamar o LB1_Release para poder liberar
			// a fila para que outras aplicacoes possam usar.
//			LB1_ReleaseHead();
//		}
	}
	if( R_LockHead() == OK ){
		if( iHeadLocked == 1 && bRead ){
			R_ReadHead();
		}
		return( OK );
	}
	return( E_LOCK );
}

int	
C_LB1::LB1_ReleaseHead( BOOL bWrite )
{
	int	iRet;

	if( iHeadLocked == 1 && bWrite ){
		C_RecordFile::R_WriteHead( &tcrHead );
	}
	if( ::GetTypeInt() == PE_REDE ){
		if( --iHeadLocked > 0 ){
			return( OK );
		}
		if( iHeadLocked < 0 ){
			iHeadLocked = 0;
		}

		// entrar no arquivo de lock
		char	szLockFileName[ MAXFILE ];
		short	siHead;
		short	siInfo;
		char	*szAux;
		int		iRet;

		strcpy( szLockFileName, GetFileName() );
		szAux = strrchr( szLockFileName, '.' );
		if( !szAux ){
			strcat( szLockFileName, ".NET" );
		} else {
			strcpy( szAux, ".NET" );
		}

		C_RecordFile	cfNetFile( CRYPTO_MAGICNUMBER );
		
		while( (iRet = cfNetFile.Open( szLockFileName, 
								sizeof( short ), sizeof( short ), 
								NULL, "RECKEY", NULL, 
								SH_DENYNO, TRUE )) == E_LOCK ){
			Sleep( 200 );
		}
		if( iRet != OK ){
			return( iRet );
		}

		// travar o header do arquivo (o primeiro short int)
		while( cfNetFile.R_LockHead() != OK ){
			Sleep( 200 );
		}

		// tentar ler o header. se nao conseguirmos, eh porque ele nao existe 
		// (alguem sacaneou e detonou o arquivo). Neste caso, podemos dispensar o
		// restante do procedimento.
		if( cfNetFile.R_ReadHead( &siHead ) == OK ){
			// decrementar o numero contido no header, para indicar que saimos
			// do arquivo.
			--siHead;
			if( siHead < 0 ){
				siHead = 0;
			}

			// decrementar todos os numeros do arquivo.
			if( cfNetFile.R_Seek( 0 ) == OK ){
				while( cfNetFile.R_Read( &siInfo ) == OK ){
					--siInfo;
					if( siInfo < 0 ){
						siInfo = 0;
					}
					cfNetFile.R_Write( &siInfo );
					if(	cfNetFile.R_SeekNext() != OK ){
						// acabou.
						break;
					}
				}
			}

			// regravar o header
			cfNetFile.R_WriteHead( &siHead );

			// liberar o header do arquivo
			cfNetFile.R_ReleaseHead();
		}
	} else {
		iRet = R_ReleaseHead();
	}
	return( iRet );
}

int	
C_LB1::R_WriteHead()
{
	if( R_LockHead() == OK ){
		C_RecordFile::R_WriteHead( &tcrHead );
		R_ReleaseHead();
		return( OK );
	}
	return( E_LOCK );
}

int	
C_LB1::R_WriteHead( TControlRecHead *ptAux )
{
	return( C_RecordFile::R_WriteHead( ptAux ) );
}

int	
C_LB1::LB1_WriteHead()
{
	if( LB1_LockHead( FALSE ) == OK ){
		C_RecordFile::R_WriteHead( &tcrHead );
		LB1_ReleaseHead();
		return( OK );
	}
	return( E_LOCK );
}

int	
C_LB1::R_ReadHead()
{
	int	iRet = C_RecordFile::R_ReadHead( &tcrHead );

	if( iRet == OK ){
		// verificar consistencia do header (a nivel superficial)
		if( tcrHead.bBaseType > USER_BASE ||
			tcrHead.bReExport > 1 || tcrHead.bReExport < 0 || 
			tcrHead.bIsEncrypt > 1 || tcrHead.bIsEncrypt < 0 ||
			tcrHead.bOnLineIndex > 1 || tcrHead.bOnLineIndex < 0 ||
			tcrHead.iSlotNum < 0 || 
			tcrHead.iCountNum < 0 || 
			tcrHead.iMaxKeySize < 0 ||
			tcrHead.iIntPart < 0 ||
			tcrHead.iDecPart < 0 ){
			// aparentemente inconsistente. vou ler novamente.
			Sleep( 1000 );	// 1 segundo
			C_File::PseudoClose();
			return( C_RecordFile::R_ReadHead( &tcrHead ) );
		}
	}
	return( iRet );
}

int	
C_LB1::R_ReadHead( TControlRecHead *ptAux )
{
	return( C_RecordFile::R_ReadHead( ptAux ) );
}


void
C_LB1::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Criptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}

void
C_LB1::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Decriptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}



	
/***************************************************************************************/
/*******************************************  LB2  *************************************/
/***************************************************************************************/

C_LB2::C_LB2( char *szFileName, char *szKey, const char *szMode, int iShFlag ):
	C_DynamicFile( szFileName, CRYPTO_MAGICNUMBER, szKey, szMode, iShFlag )
{}

	C_LB2::C_LB2() : C_DynamicFile( CRYPTO_MAGICNUMBER )
{
}

int 
C_LB2::Open( char *szFileName, char *szKey, const char *szMode, int iShFlag )
{
	return( C_DynamicFile::Open( szFileName, CRYPTO_MAGICNUMBER, szKey, szMode, iShFlag ) );
}


void
C_LB2::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Criptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}

void
C_LB2::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Decriptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}


/***************************************************************************************/
/*******************************************  LB3  *************************************/
/***************************************************************************************/

C_LB3::C_LB3( char *szFileName, char *szRecKey, const char *szMode, int iShFlag, int iSlotNum, int iCountNum ):
	C_RecordFile( szFileName, 0, TStructHeadRec::SizeOf( iSlotNum + iCountNum ),
		sizeof( TStructRec ), LB3HEADKEY, szRecKey, szMode, iShFlag )
{
	iNumSlots = iSlotNum;
	iNumCounters = iCountNum;

	pclCountControl = new TCountLockControl [ iCountNum ];
}

C_LB3::C_LB3() : C_RecordFile( 0 )
{
	iNumSlots = 0;
	iNumCounters = 0;
	pclCountControl = NULL;
}

C_LB3::~C_LB3()
{
	if( pclCountControl ){
		delete [] pclCountControl;
	}
}

int 
C_LB3::Open( char *szFileName, char *szRecKey, const char *szMode, int iShFlag, int iSlotNum, int iCountNum )
{
	iNumSlots = iSlotNum;
	iNumCounters = iCountNum;
	if( !pclCountControl ){
		pclCountControl = new TCountLockControl [ iCountNum ];
	}
	BOOL bEx = C_File::Exist( szFileName );
	int	iRet = C_RecordFile::Open( szFileName, TStructHeadRec::SizeOf( iSlotNum + iCountNum ),
		sizeof( TStructRec ), LB3HEADKEY, szRecKey, szMode, iShFlag );
	if( iRet == OK ){
		if( !bEx ){
			// arquivo acabou de ser criado. vamos gravar um
			// header todo zerado.
			TStructHeadRec	*ptsrStructRecHead = TStructHeadRec::Alloc( iSlotNum + iCountNum );
			if( ptsrStructRecHead ){
				R_WriteHead( ptsrStructRecHead );
				TStructHeadRec::Free( ptsrStructRecHead );
			}
		}
	}
	return( iRet );
}

/**********************************************************
// Function name	: C_LB3::R_WriteHead
// Description	    : 
// Return type		: int 
// Argument         : void *szBuffer
**********************************************************/
int C_LB3::R_WriteHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( sizeof( bMagicNumber ), SEEK_SET ) != OK ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// esta versao nao suporta lock de contadores.
		// a leitura e gravacao do header sao feitas de uma
		// so' vez.
		return C_File::Write( szBuffer, lHeadSize );
	}
	// esta versao suporta lock de contadores. A leitura
	// e gravacao do header devem ser feitas em partes,
	// pois as areas de lock de contadores nao sao necessariamente
	// lidas/gravadas.

	// vamos ler/gravar o header da seguinte forma:
	// primeiro, um bloco que vai do inicio do header ate' o ultimo
	// slot;
	// depois le^/grava o primeiro contador e pula o lPointer desse contador, 
	// que eh a sua area de lock;
	// e assim vai ate' o ultimo contador.
	int		iRet;
	long	lSize = TStructHeadRec::SizeOf( iNumSlots );

	// ler/gravar o primeiro bloco do header
	iRet = C_File::Write( szBuffer, lSize );
	if( iRet != OK ){
		return( iRet );
	}
	// agora tratar os contadores e seus lPointer
	for( int i = 0; i < iNumCounters; i++ ){
		// contador
		iRet = C_File::Write( (void*) ((char*) szBuffer + lSize + (i * sizeof( SlotPointer ) ) ), sizeof( long ) );
		if( iRet != OK ){
			return( iRet );
		}
		// lPointer do contador
		iRet = C_File::Write( (void*) ((char*) szBuffer + lSize + (i * sizeof( SlotPointer ) ) + sizeof( long ) ), sizeof( long ) );
		// Se este objeto estiver com o lock, a operacao deve dar certo; se o lock
		// estiver com outro objeto, a operacao vai falhar. Ai' vamos assumir que a informacao
		// que deveria estar no buffer eh uma sequencia de zeros ( * sizeof(long)).
	}
	return( OK );
}

/**********************************************************
// Function name	: C_LB3::R_ReadHead
// Description	    : 
// Return type		: int 
// Argument         : void *szBuffer
**********************************************************/
int C_LB3::R_ReadHead( void *szBuffer )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( C_File::Seek( sizeof( bMagicNumber ), SEEK_SET ) != OK ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// esta versao nao suporta lock de contadores.
		// a leitura e gravacao do header sao feitas de uma
		// so' vez.
		return C_File::Read( szBuffer, lHeadSize );
	}
	// esta versao suporta lock de contadores. A leitura
	// e gravacao do header devem ser feitas em partes,
	// pois as areas de lock de contadores nao sao necessariamente
	// lidas/gravadas.

	// vamos ler/gravar o header da seguinte forma:
	// primeiro, um bloco que vai do inicio do header ate' o ultimo
	// slot;
	// depois le^/grava o primeiro contador e pula o lPointer desse contador, 
	// que eh a sua area de lock;
	// e assim vai ate' o ultimo contador.
	int		iRet;
	long	lSize = TStructHeadRec::SizeOf( iNumSlots );

	// ler/gravar o primeiro bloco do header
	iRet = C_File::Read( szBuffer, lSize );
	if( iRet != OK ){
		return( iRet );
	}
	// agora tratar os contadores e seus lPointer
	for( int i = 0; i < iNumCounters; i++ ){
		long	lPosAux = CurPos();

		// contador
		iRet = C_File::Read( (void*) ((char*) szBuffer + lSize + (i * sizeof( SlotPointer ) ) ), sizeof( long ) );
		if( iRet != OK ){
			return( iRet );
		}
		// lPointer do contador
		iRet = C_File::Read( (void*) ((char*) szBuffer + lSize + (i * sizeof( SlotPointer ) ) + sizeof( long ) ), sizeof( long ) );
		// Se este objeto estiver com o lock, a operacao deve dar certo; se o lock
		// estiver com outro objeto, a operacao vai falhar. Ai' vamos assumir que a informacao
		// que deveria estar no buffer eh uma sequencia de zeros ( * sizeof(long)).
		if( iRet != OK ){
			memset( (void*) ((char*) szBuffer + lSize + (i * sizeof( SlotPointer ) ) + sizeof( long ) ), 0, sizeof( long ) );
		}
	}
	return( OK );
}

int	
C_LB3::LB3_LockHead( TStructHeadRec *pAux )
{
	if( R_LockHead() == OK ){
		if( iHeadLocked == 1 ){
			R_ReadHead( pAux );
			memcpy( &tsHead, pAux, sizeof( tsHead ) );
		}
		return( OK );
	}
	return( E_LOCK );
}

int	
C_LB3::LB3_ReleaseHead( TStructHeadRec *pAux )
{
	if( iHeadLocked == 1 ){
		memcpy( &tsHead, pAux, sizeof( tsHead ) );
		R_WriteHead( pAux );
	}
	return( R_ReleaseHead() );
}

/*** 
	o metodo abaixo serve para Seek em slots ou contadores
***/
int
C_LB3::SeekOnSlot( int iSlotNum )
{
	//				numero mag.		int do header		num slots * tam. 1 slot
	return( Seek( sizeof( BYTE ) + sizeof( int ) + iSlotNum * sizeof( SlotPointer ), SEEK_SET ) );
}


void
C_LB3::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Criptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}

void
C_LB3::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Decriptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}


/**********************************************************
// Function name	: C_LB3::LockCount
// Description	    : 
// Return type		: int 
// Argument         :  int iCountIndex
// Argument         : BOOL bWait
**********************************************************/
int C_LB3::LockCount( int iCountIndex, BOOL bWait )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( (iCountIndex < 0) || (iCountIndex >= iNumCounters) ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// nao da' para fazer isso nessa versao
		return( !OK );
	}
	if( pclCountControl && pclCountControl[ iCountIndex ].iCountLock > 0 ){
		// o iCountLock foi criado com a intencao de permitirmos que o mesmo thread
		// possa fazer mais de um lock no mesmo contador. Entao iCountLock apenas
		// seria incrementado no LockCount de decrementado no ReleaseCount.
		// Mas depois resolvemos mudar a implementacao para que so' seja permitido
		// fazer LockCount uma vez. Uma tentativa de lock sobre um contador ja' travado
		// resulta em erro, mesmo que essa segunda tentativa seja feita pelo mesmo
		// thread que fez a primeira.
		// (pclCountControl[ iCountIndex ].iCountLock)++;
		return( !OK );
	}
	long	lCountPos = sizeof( bMagicNumber ) + TStructHeadRec::SizeOf( iNumSlots ) + (iCountIndex * sizeof( SlotPointer )) + sizeof( long );

	if( C_File::Seek( lCountPos, SEEK_SET ) == OK ){
		if( C_File::Lock( 1 /* basta um byte */, bWait ) == OK ){
			if( pclCountControl ){
				// incrementar o contador de locks.
				(pclCountControl[ iCountIndex ].iCountLock) = 1;
			}
			// originalmente, disparariamos um release por time-out
			// mas o uso de contadores eh tao limitado dentro do lightbase
			// que nao vale o overhead de recursos para criacao de threads e eventos 
			// so para isso; como nao esta nas maos do desenvolvedor de aplicacoes LightBase
			// e sim de nos mesmos (lado servidor), isso pode ser relevado
			// StartCountLockTimer( iCountIndex );
			return( OK );
		}
	}
	return( !OK );
}

/**********************************************************
// Function name	: C_LB3::ReleaseCount
// Description	    : 
// Return type		: int 
// Argument         : int iCountIndex
**********************************************************/
int C_LB3::ReleaseCount( int iCountIndex )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	int	iRet = PrivReleaseCount( iCountIndex );
	if( pclCountControl && (pclCountControl[ iCountIndex ].iCountLock <= 0) ){
		// ver comentarios para o uso do StartCountLockTimer logo acima
		// as razoes para comentar este codigo sao as mesmas...
		// StopCountLockTimer( iCountIndex );
	}
	return( iRet );
}

/**********************************************************
// Function name	: C_LB3::PrivReleaseCount
// Description	    : 
// Return type		: int 
// Argument         : int iCountIndex
**********************************************************/
int C_LB3::PrivReleaseCount( int iCountIndex )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( (iCountIndex < 0) || (iCountIndex >= iNumCounters) ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// nao da' para fazer isso nessa versao
		return( !OK );
	}

/*	Veja comentario sobre iCountLock no metodo LockCount
	if( pclCountControl && (pclCountControl[ iCountIndex ].iCountLock > 1) ){
		// temos mais de um lock feito. basta decrementar o contador.
		(pclCountControl[ iCountIndex ].iCountLock)--;
		return( OK );
	}
*/
	if( pclCountControl && (pclCountControl[ iCountIndex ].iCountLock <= 0) ){
		// nao ha' release para fazer.
		(pclCountControl[ iCountIndex ].iCountLock) = 0;
		return( !OK );
	}
	long	lCountPos = sizeof( bMagicNumber ) + TStructHeadRec::SizeOf( iNumSlots ) + (iCountIndex * sizeof( SlotPointer )) + sizeof( long );

	if( C_File::Seek( lCountPos, SEEK_SET ) == OK ){
		if( C_File::Release( 1 ) == OK ){
			if( pclCountControl ){
				// zerar o contador.
				(pclCountControl[ iCountIndex ].iCountLock) = 0;
			}
			return( OK );
		}
	}
	return( !OK );
}

/**********************************************************
// Function name	: C_LB3::SaveCount
// Description	    : 
// Return type		: int 
// Argument         :  int iCountIndex
// Argument         : long lCount
**********************************************************/
int C_LB3::SaveCount( int iCountIndex, long lCount )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( (iCountIndex < 0) || (iCountIndex >= iNumCounters) ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// nao da' para fazer isso nessa versao
		return( !OK );
	}
	if( pclCountControl && pclCountControl[ iCountIndex ].iCountLock ){
		// o contador esta' em lock. podemos gravar.
		if( SeekOnSlot( iNumSlots + iCountIndex ) == OK ){
			if( C_File::Write( &lCount, sizeof( lCount ) ) == OK ){
				return( OK );
			}
		}
	}
	return( !OK );
}


/**********************************************************
// Function name	: C_LB3::LoadCount
// Description	    : 
// Return type		: int 
// Argument         :  int iCountIndex
// Argument         : long &lCount
**********************************************************/
int C_LB3::LoadCount( int iCountIndex, long &lCount )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( (iCountIndex < 0) || (iCountIndex >= iNumCounters) ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// nao da' para fazer isso nessa versao
		return( !OK );
	}
	if( SeekOnSlot( iNumSlots + iCountIndex ) == OK ){
		if( C_File::Read( &lCount, sizeof( lCount ) ) == OK ){
			return( OK );
		}
	}
	return( !OK );
}


/**********************************************************
// Function name	: C_LB3::IncCount
// Description	    : 
// Return type		: int 
// Argument         :  int iCountIndex
// Argument         : long lCount
// Argument         : long &lRet
**********************************************************/
int C_LB3::IncCount( int iCountIndex, long lCount, long &lRet )
{
	if( szHeadKey ){
		TurnOnCripto( szHeadKey );
	} else {
		TurnOffCripto();
	}
	if( (iCountIndex < 0) || (iCountIndex >= iNumCounters) ){
		return( !OK );
	}
	if( bMagicNumber < LOCKCOUNT_MAGICNUMBER ){
		// nao da' para fazer isso nessa versao
		return( !OK );
	}
	// so' podemos realizar esta operacao se o contador estiver em lock
	if( pclCountControl && pclCountControl[ iCountIndex ].iCountLock ){
		// beleza. temos um lock.
		// garantimos que o lock nao vai ser quebrado durante esta
		// operacao usando a regiao critica acima (CRITSECT0).
		if( LoadCount( iCountIndex, lRet ) == OK ){
			lRet += lCount;
			if( SaveCount( iCountIndex, lRet ) == OK ){
				return( OK );
			}
		}
	}
	return( !OK );
}

/**********************************************************
// Function name	: C_LB3::DecCount
// Description	    : 
// Return type		: int 
// Argument         :  int iCountIndex
// Argument         : long lCount
// Argument         : long &lRet
**********************************************************/
int C_LB3::DecCount( int iCountIndex, long lCount, long &lRet )
{
	return( IncCount( iCountIndex, -lCount, lRet ) );
}

/**********************************************************
// Function name	: C_LB3::StartCountLockTimer
// Description	    : 
// Return type		: int 
// Argument         : int iCountIndex
**********************************************************/
int C_LB3::StartCountLockTimer( int iCountIndex )
{
	if( !pclCountControl[ iCountIndex ].hCountLockEvent ){
		pclCountControl[ iCountIndex ].hCountLockEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	}	
	if( pclCountControl[ iCountIndex ].hCountLockEvent ){
		TCountLockThreadInfo	*ptAux = new TCountLockThreadInfo;

		if( ptAux ){
			ptAux->pObj = this;
			ptAux->iCountIndex = iCountIndex;
			ptAux->hCountLockEvent = pclCountControl[ iCountIndex ].hCountLockEvent;
			pclCountControl[ iCountIndex ].hLockThread = CreateThread( NULL, 0, CountLockControlFunction, (LPVOID) ptAux, 0, &(ptAux->dwThreadId) );
		}
		return( OK );
	}
	return( !OK );
}

/**********************************************************
// Function name	: C_LB3::StopCountLockTimer
// Description	    : 
// Return type		: int 
// Argument         : int iCountIndex
**********************************************************/
int C_LB3::StopCountLockTimer( int iCountIndex )
{
	if( pclCountControl[ iCountIndex ].hCountLockEvent ){
		// matar o thread que esta' tratando o timer de lock
		SetEvent( pclCountControl[ iCountIndex ].hCountLockEvent );

		// esperar o thread morrer
		WaitForSingleObject( pclCountControl[ iCountIndex ].hLockThread, INFINITE );

		// destruir o evento
		CloseHandle( pclCountControl[ iCountIndex ].hCountLockEvent );
		pclCountControl[ iCountIndex ].hCountLockEvent = NULL;
		return( OK );
	}
	return( !OK );
}

/**********************************************************
// Function name	: CountLockControlFunction
// Description	    : 
// Return type		: DWORD WINAPI 
// Argument         : LPVOID pParam
**********************************************************/
DWORD WINAPI CountLockControlFunction( LPVOID pParam )
{
	if( !pParam ){
		return( 0 );
	}
	TCountLockThreadInfo	*ptAux = (TCountLockThreadInfo*) pParam;

	if( ptAux && ptAux->hCountLockEvent ){
		DWORD	dwRet = 0;
		char	szFullIniName[ MAXPATH ];
		UINT	uiInterval;

		GetAppFullPath( szFullIniName, MAXPATH-1 );
		strcat( szFullIniName, LIFILEINIFILE );

		uiInterval = GetPrivateProfileInt( "CONFIG", "COUNTERLOCKTIMEOUT", 30, szFullIniName );

		uiInterval *= 1000;

		dwRet = WaitForSingleObject( ptAux->hCountLockEvent, uiInterval );
		if( dwRet == WAIT_TIMEOUT ){
			// estourou o tempo. chamar o release
			ptAux->pObj->PrivReleaseCount( ptAux->iCountIndex );
		}
	}
	if( ptAux ){
		delete ptAux;
	}
	return( 0 );
}


/***************************************************************************************/
/*******************************************  LB4  *************************************/
/***************************************************************************************/


C_LB4::C_LB4( char *szFileName, char *szKey, const char *szMode, int iShFlag ):
	C_DynamicFile( szFileName, CRYPTO_MAGICNUMBER, szKey, szMode, iShFlag )
{}

C_LB4::C_LB4() : C_DynamicFile( CRYPTO_MAGICNUMBER )
{
}

int 
C_LB4::Open( char *szFileName, char *szKey, const char *szMode, int iShFlag )
{
	return( C_DynamicFile::Open( szFileName, CRYPTO_MAGICNUMBER, szKey, szMode, iShFlag ) );
}


void
C_LB4::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Criptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}

void
C_LB4::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	::Decriptografa( (char*) pvBuf, (char*) pvBuf + tsSize );
}


void GetAppFullPath( char *Path, int Size )
{
   // Se inicia com aspas, ...
   if ( *GetCommandLine() == '\"' )
      // ... pega a linha a partir do segundo caracter
      strncpy( Path, GetCommandLine() + 1, Size );
   else
      // ... senão, pega a linha completa
      strncpy( Path, GetCommandLine(), Size );
   Path[Size-1] = '\0';

   // Retira o nome do arquivo
   for ( int i = strlen(Path)-1; i >= 0; i-- ) {
      if ( Path[i] == '\\' || Path[i] == '/' ) {
         Path[i+1] = '\0';
         break;
      }
   }
   if ( i < 0 )
      Path[0] = '\0';
}

