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

//
// Module: FILECL.CPP
// Description:
//	File class functions
//
// Programmer:	Marcos Sebastian Alsina
//
// Last Uptade: 08/01/96 -> Adriano Sergio
//

// PARA SETAR O NUMERO MAXIMO DE ARQUIVOS PARA WIN32s SEM ALTERAR ESTE CODIGO,
// BASTA CHAMAR O METODO SetNumFiles32s COM O NUMERO DESEJADO.

// ESTE MODULO UTILIZA FUNCOES DO WINDOWS PARA MANIPULACAO DE ARQUIVOS SE ESTIVER
// RODANDO EM AMBIENTES 32BITS E USA FUNCOES CONVENCIONAIS (sopen, read, etc.) SE
// ESTIVER EM WIN32s.


#ifndef	_FILECL_
#include	<filecl.h>
#endif
#if !defined __DOS_H && !defined _INC_DOS
#include	<dos.h>
#endif
#if !defined __ERRNO_H && !defined _INC_ERRNO
#include	<errno.h>
#endif
#if !defined(__FCNTL_H) && !defined _INC_FCNTL
#include	<fcntl.h>
#endif
#if !defined(__STAT_H) && !defined _INC_STAT
#include	<sys/stat.h>
#endif
#if !defined(__LOCKING_H) && !defined _INC_LOCKING
#include	<sys/locking.h>
#endif
#ifndef _CRIPTO_
#include	<cripto.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#ifndef	_DEFMACRO_H_
#include	<defmacro.h>
#endif
#ifndef	_INC_STDIO
#include	<stdio.h>
#endif

// para personalizacao
extern "C" {
#include	<personcl.h>
}
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif


#define	CONFIG_SESSION		"CONFIG"
#define	WINDOWSIZE_KEY		"WINSIZE"
#define	WINDOWSIZE_DEFAULT	0

#define	PWINVIEW			pWinView + (iHeadSize + 1)

extern int	errno;

#define	MAXOPENFILES	500	// numero maximo de arquivos abertos para sistemas operacionais decentes
#define	NUMOPENFILES32s	5	// numero maximo de arquivos abertos para sistemas Win32s

int		Mode16( const char * );
DWORD	Mode( const char * );
DWORD	ShMode( int );
DWORD	CreateMode( const char * );
void	GetAppFullPath( char *Path, int Size );

// ****************************************************************
// todas as variaveis abaixo devem ser tratadas em regiao critica:

static	C_File	*_cfFiles[ MAXOPENFILES ];
static	int	_iNumXDat = 0;

// numero de arquivos abertos no momento
static	int	_iNumOpenFiles = 0;

// numero maximo de arquivos abertos simultaneamente
int	_iMaxOpenFiles = 0;

// variavel usada para indicacao de plataforma operacional
int	_bIs32s = FALSE;

// arquivo de reserva, para garantir um descritor que sera' usado em casos emergenciais
C_File	*_xFile = NULL;

// determina se os locks devem ser feitos em memoria ou a nivel de
// sistema operacional (neste caso, RealLock)
static	BOOL	_bStaticRealLock = FALSE;

// lista de locks dos arquivos
LockList	*_LockTable[ NUMLIST ];
//LockList	*C_File::_LockTable = NULL; 

// handle do evento de controle de wait de lock
HANDLE	_hWaitLockEvent = NULL;

// todas as variaveis acima devem ser tratadas em regiao critica:
// ****************************************************************
#include	<lifregcrit.h>

extern	C_GlobalFileCritSect	*_pcGlobalFileCritSect;

#ifdef _USE_PRINTF_
extern	void	Printf( char *, ... );
#endif


/*******/
C_File::C_File()
{

	// para usar MMF, a aplicacao deve setar valores corretos para iHeadInit e iHeadSize
	// antes de fazer um open. iHeadInit determina a posicao do primeiro byte do header
	// do arquivo. Isso serve para o caso de o arquivo possuir alguma estrutura antes do
	// header, como um numero magico, por exemplo. iHeadSize determina o tamnho em bytes
	// do header.


	SYSTEM_INFO	si;
	GetSystemInfo( &si );

	iPageSize = si.dwAllocationGranularity;

	hMMF = NULL;
	pHeadView = NULL;
	pWinView = NULL;
	iWinNum = 0;
	iSeekWin = 0;
	iHeadSize = 0;
	iHeadInit = 0;
	iMMFWinSize = 0;

	hFile = INVALID_HANDLE_VALUE;
	iFile = -1;
	cCriptoOn = 0;
	iShFlag = 0;
	iLine = 0;
	dwAccess = 0;
	memset( szMode, 0, 10 );
	memset( szFileName, 0, 256 );
	bReOpen = FALSE;
	dwLastUse = 0;
	lNumLocks = 0;
	bRealLock = FALSE; 
	ListIn();
};


/*******/
C_File::C_File( const char *szNameFile, const char *szModePar, int iShFlagPar, BOOL bWait )
{
	SYSTEM_INFO	si;
	GetSystemInfo( &si );

	iPageSize = si.dwAllocationGranularity;

	hMMF = NULL;
	pHeadView = NULL;
	pWinView = NULL;
	iWinNum = 0;
	iSeekWin = 0;
	iHeadSize = 0;
	iHeadInit = 0;
	iMMFWinSize = 0;

	cCriptoOn = 0;
	iLine = 0;
	dwAccess = 0;
	bReOpen = FALSE;
	dwLastUse = 0;
	lNumLocks = 0;
	hFile = INVALID_HANDLE_VALUE;
	iFile = -1;
	ListIn();
	bRealLock = FALSE; 
	if( Open( szNameFile, szModePar, iShFlagPar, bWait ) == E_NOTOPEN ){
		hFile = INVALID_HANDLE_VALUE;
		iFile = -1;
	}
};


/*******/
C_File::~C_File()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile != -1) || (!_bIs32s && hFile != INVALID_HANDLE_VALUE) ){
		Close();
	}
	ListOut();
};


/*************/
int	
C_File::ListIn()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( this == _xFile ){
		// _xFile nao entra no vetor de arquivos
		return( OK );
	}
	for( int i = 0; i < MAXOPENFILES; i++ ){
		if( _cfFiles[ i ] == NULL ){
			_cfFiles[ i ] = this;
			return( OK );
		}
	}
	return( !OK );
}

/*************/
int	
C_File::ListOut()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	for( int i = 0; i < MAXOPENFILES; i++ ){
		if( _cfFiles[ i ] == this ){
			_cfFiles[ i ] = NULL;
			return( OK );
		}
	}
	return( !OK );
}


/*************/
int	
C_File::CloseSomeFile()
{
	DWORD	dwMin = (DWORD) -1;
	int	iPos = -1;

	C_FileCritSect	cCS0( this, CRITSECT0 );
	for( int i = 0; i < MAXOPENFILES; i++ ){
		if( _cfFiles[ i ] && 
			_cfFiles[ i ]->bReOpen == FALSE &&
			_cfFiles[ i ]->dwLastUse < dwMin && 
			( (_bIs32s && _cfFiles[ i ]->iFile != -1) || 
			(!_bIs32s && _cfFiles[ i ]->hFile != INVALID_HANDLE_VALUE) ) &&
			_cfFiles[ i ]->lNumLocks <= 0 ){
			dwMin = _cfFiles[ i ]->dwLastUse;
			iPos = i;
		}
	}
	if( iPos != -1 ){
		return _cfFiles[ iPos ]->PseudoClose();
	}
	return( !OK );
}


/*************/
int	
C_File::ReOpen( void )
{
#ifdef _USE_PRINTF_
	if( this == _xFile ){
		Printf( "C_File: Vou (re) abrir o _xFile****************************" );
	}
#endif
	if( Open( szFileName, (strcmp( szMode, "" ) == 0) ? NULL : szMode, iShFlag ) == OK ){
		bReOpen = FALSE;
		return Seek( lCurPos, SEEK_SET );
	}
	return( !OK );
}


/***
	Le^ um buffer do arquivo ate' o fim do arquivo ou o tamanho
	do buffer.
	Parameters:
		- pvBuf: Buffer ja' alocado
		- tsSize: tamanho do buffer, em bytes.
	Return:
		- O numero de bytes lidos ou -1 em caso de erro.
***/
int
C_File::ReadBuffer( void FAR *pvBuf, size_t tsSize )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( !pvBuf ){
		return( -1 );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){
			if( !_xFile ){
				return( -1 );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}
	// MMF
	BOOL	bReadHeader = FALSE;
	if( !_bIs32s && hMMF ){
		// preparar leitura a partir do MMF
		if( (CurPos() == iHeadInit)  && ((int) tsSize == iHeadSize) ){
			bReadHeader = TRUE;
			// vamos fazer read no header do arquivo.
			if( !pHeadView ){
				// o header ainda nao esta' mapeado. vamos fazer isso.
				CreateViewOfHead();
			}
		} else {
			if( !pWinView ){
				// o arquivo ainda nao esta' mapeado. vamos fazer isso.
				CreateViewOfFile();
			}
		}
	}

	DWORD	dwReadBytes = 0;
	size_t	tsNumItens = 1;
	for( size_t i = 0; i < tsNumItens; i++ ){
		if( _bIs32s ){
			if( (dwReadBytes = (DWORD) read( iFile, ( char *) pvBuf + tsSize * i, tsSize )) < (DWORD) tsSize ){
				break;
			}
		} else {
			if( bReadHeader ){
				// ler header a partir do MMF.
				memcpy( pvBuf, pHeadView, tsSize );
			} else {
				if( pWinView ){
					// ler a partir do MMF.
					int	iNumBytes = ((iMMFWinSize * iPageSize) - iSeekWin) - (iHeadSize + 1);
					memcpy( (void*) (( char *) pvBuf + tsSize * i), (void*) ((char*) PWINVIEW + iSeekWin), 
							min( iNumBytes, ((int) tsSize) ) );
					if( iNumBytes < ((int) tsSize) ){
						// precisamos mapear outra janela e continuar a leitura
						++iWinNum;	// proxima janela
						CreateViewOfFile();
						if( !pWinView ){
							// mapeamento nao foi feito. vamos assumir fim-de-arquivo.
							break;
						}
						// ler o restante
						memcpy( (void*) ((( char *) pvBuf + tsSize * i) + iNumBytes), (void*) ((char*) PWINVIEW + iSeekWin), 
								(tsSize - iNumBytes) );

						iSeekWin += (tsSize - iNumBytes);
					} else {
						iSeekWin += tsSize;
					}
				} else {
					// ler direto do arquivo
					BOOL	bResult = ReadFile( hFile, ( char *) pvBuf + tsSize * i, tsSize, &dwReadBytes, NULL );
					if( !bResult || ( dwReadBytes  < tsSize ) ){
						break;
					}
				}
			}
		}
	}
	dwLastUse = GetTickCount();
	if( cCriptoOn && i >= tsNumItens ){
		Decrypt( pvBuf, szKey, tsSize * tsNumItens );
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( (int) dwReadBytes );
}

/***
	Read bytes from a file to a buffer.
	Parameters:
		- pvBuf: User buffer. Contains the result of a read.
		- tsSize: Size of iten to read
		- tsNumItens: Number of itens to read
	Return:
		- O numero de itens lidos (nao o numero de bytes). Em caso
		de erro: E_NOTOPEN or E_BUFFNULL or EOF.
***/
size_t
C_File::Read( void FAR *pvBuf, size_t tsSize, size_t tsNumItens )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( !pvBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){
			if( !_xFile ){
				return( 0 );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}
	// MMF
	BOOL	bReadHeader = FALSE;
	if( !_bIs32s && hMMF ){
		// preparar leitura a partir do MMF
		if( (CurPos() == iHeadInit)  && ((int) tsSize == iHeadSize) ){
			bReadHeader = TRUE;
			// vamos fazer read no header do arquivo.
			if( !pHeadView ){
				// o header ainda nao esta' mapeado. vamos fazer isso.
				CreateViewOfHead();
			}
		} else {
			if( !pWinView ){
				// o arquivo ainda nao esta' mapeado. vamos fazer isso.
				CreateViewOfFile();
			}
		}
	}

	for( size_t i = 0; i < tsNumItens; i++ ){
		if( _bIs32s ){
			if( read( iFile, ( char *) pvBuf + tsSize * i, tsSize ) < (int) tsSize ){
				break;
			}
		} else {
			if( bReadHeader ){
				// ler header a partir do MMF.
				memcpy( pvBuf, pHeadView, tsSize );
			} else {
				if( pWinView ){
					// ler a partir do MMF.
					int	iNumBytes = ((iMMFWinSize * iPageSize) - iSeekWin) - (iHeadSize + 1);
					memcpy( (void*) (( char *) pvBuf + tsSize * i), (void*) ((char*) PWINVIEW + iSeekWin), 
							min( iNumBytes, ((int) tsSize) ) );
					if( iNumBytes < ((int) tsSize) ){
						// precisamos mapear outra janela e continuar a leitura
						++iWinNum;	// proxima janela
						CreateViewOfFile();
						if( !pWinView ){
							// mapeamento nao foi feito. vamos assumir fim-de-arquivo.
							break;
						}
						// ler o restante
						memcpy( (void*) ((( char *) pvBuf + tsSize * i) + iNumBytes), (void*) ((char*) PWINVIEW + iSeekWin), 
								(tsSize - iNumBytes) );

						iSeekWin += (tsSize - iNumBytes);
					} else {
						iSeekWin += tsSize;
					}
				} else {
					// ler direto do arquivo
					DWORD	dwReadBytes;
					BOOL	bResult = ReadFile( hFile, ( char *) pvBuf + tsSize * i, tsSize, &dwReadBytes, NULL );
					if( !bResult || ( dwReadBytes  < tsSize ) ){
						break;
					}
				}
			}
		}
	}
	dwLastUse = GetTickCount();
	if( cCriptoOn && i >= tsNumItens ){
		Decrypt( pvBuf, szKey, tsSize * tsNumItens );
	}
	if( i < tsNumItens ){
		i = (size_t) EOF;
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( i );
}

/********/
int
C_File::Read( void FAR *buffer, size_t size )
{
	return Read( buffer, size, 1 ) == 1 ? OK : E_READ;
}

/********/
int
C_File::Write( void FAR *buffer, size_t size )
{
	return Write( buffer, size, 1 ) == 1 ? OK : E_WRITE;
}

/***
	Le uma linha de um arquivo texto. Para de ler quando acha
	um '\n' ou quando le szMaxlen caracteres. O '\n' nao eh
	deixado dentro do buffer. Em seu lugar, este metodo coloca
	um '\0'. Retorna o numero de caracteres lidos, incluindo o
	'\n'.
***/
size_t
C_File::ReadLine( char FAR *szBuf, size_t stMaxLen )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( !szBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( 0 );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}

	// MMF
	if( !_bIs32s && hMMF ){
		// preparar leitura a partir do MMF
		if( !pWinView ){
			// o arquivo ainda nao esta' mapeado. vamos fazer isso.
			CreateViewOfFile();
		}
	}

	for( size_t i = 0; i < stMaxLen; i++ ){
		if( _bIs32s ){
			if( read( iFile, ( char *) szBuf + i, sizeof( char ) ) < sizeof( char ) ){
				if( i == 0 ){
					if( iFlag ){
						PseudoClose();
						_xFile->ReOpen();
					}
					return( (size_t) EOF );
				}
				break;
			}
		} else {
			if( pWinView ){
				// ler a partir do MMF.
				int	iNumBytes = ((iMMFWinSize * iPageSize) - iSeekWin);
				memcpy( (void*) (( char *) szBuf + sizeof( char ) * i), (void*) ((char*) PWINVIEW + iSeekWin), 
						min( iNumBytes, sizeof( char ) ) );
				if( iNumBytes < sizeof( char ) ){
					// precisamos mapear outra janela e continuar a leitura
					++iWinNum;	// proxima janela
					CreateViewOfFile();
					if( !pWinView ){
						// mapeamento nao foi feito. vamos assumir fim-de-arquivo.
						if( i == 0 ){
							if( iFlag ){
								PseudoClose();
								_xFile->ReOpen();
							}
							return( (size_t) EOF );
						}
						break;
					}
					// ler o restante
					memcpy( (void*) ((( char *) szBuf + sizeof( char ) * i) + iNumBytes), (void*) ((char*) PWINVIEW + iSeekWin), 
							(sizeof( char ) - iNumBytes) );

					iSeekWin += (sizeof( char ) - iNumBytes);
				} else {
					iSeekWin += sizeof( char );
				}
			} else {
				DWORD	dwReadBytes;
				BOOL	bResult = ReadFile( hFile, ( char *) szBuf + i, sizeof( char ), &dwReadBytes, NULL );
				if( !bResult || ( dwReadBytes  < sizeof( char ) ) ){
					if( i == 0 ){
						if( iFlag ){
							PseudoClose();
							_xFile->ReOpen();
						}
						return( (size_t) EOF );
					}
					break;
				}
			}
		}
		if( ((char*)szBuf)[ i ] == '\n' ){
			break;
		}
	}
	if( i > 0 ){
		if( ((char*)szBuf)[ i-1 ] == '\r' ){
			--i;
		}
	}
	dwLastUse = GetTickCount();
	((char*)szBuf)[ i ] = '\0';

	// tirar os espacos em branco e tabs do final
	while( i > 0 && (((char*)szBuf)[ i-1 ] == ' ' || ((char*)szBuf)[ i-1 ] == '\t') ){
		((char*)szBuf)[ --i ] = '\0';
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( i );
}


/***
	Grava uma linha em um arquivo texto. No final da linha, coloca um
	'\n'. Retorna OK ou !OK.
***/
size_t
C_File::WriteLine( char FAR *szBuf )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( !szBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( !OK );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}
	char cAuxCripto = cCriptoOn;
	cCriptoOn = FALSE;

	if( Write( szBuf, strlen( szBuf ) ) != OK ){
		if( iFlag ){
			PseudoClose();
			_xFile->ReOpen();
		}
		return( !OK );
	}
	char szTmp[] = "\r\n";
	if( Write( szTmp, strlen( szTmp ) ) != OK ){
		if( iFlag ){
			PseudoClose();
			_xFile->ReOpen();
		}
		return( !OK );
	}
	cCriptoOn = cAuxCripto;
	dwLastUse = GetTickCount();
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( OK );
}


/***
	Write bytes in a file from a given buffer.
	Parameters:
		- pvBuf: User buffer with data to write in file
		- tsSize: Size of iten to write
		- tsNumItens: Number of itens to write
	Return:
		Number of writtem itens in succes or E_NOTOPEN,
		E_BUFFNULL or E_WRITE.
***/
size_t
C_File::Write( void FAR *pvBuf, size_t tsSize, size_t tsNumItens )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );

	size_t	i = 0;
	BOOL	bContinue = TRUE;


#ifdef _USE_PRINTF_
	Printf( "C_File: Estou em Write. (arq %s)", szFileName );
#endif
	int iFlag = FALSE;
	if( !pvBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( 0 );
			}
			_xFile->PseudoClose();
			ReOpen();		   
			iFlag = TRUE;
		}
	}
	LockStruct ls( this, CurPos(), (tsSize * tsNumItens) );
	if( IsLocked( &ls ) ){
		if( iFlag ){
			PseudoClose();
			_xFile->ReOpen();
		}
#ifdef _USE_PRINTF_
		Printf( "C_File: Write: IsLocked." );
#endif
		return( (size_t) E_WRITE );
	}

	if( cCriptoOn ){
		Encrypt( pvBuf, szKey, tsSize );
	}

	// MMF
	BOOL	bWriteHeader = FALSE;
	if( !_bIs32s && hMMF ){
		// preparar gravacao a partir do MMF

		long	lFSize = FileSize();
		long	lCPos = CurPos();
		if( ( lCPos + (int) (tsNumItens * tsSize) ) > lFSize ){
			// este write vai exceder os limites do arquivo. vamos aumentar-lo.
			if( GrowFile( lCPos + (tsNumItens * tsSize) ) != OK ){
				// nao foi possivel aumentar o arquivo.
				bContinue = FALSE;
			}
		}
		if( bContinue ){
			if( (lCPos == iHeadInit)  && (((int) tsSize) == iHeadSize) ){
				bWriteHeader = TRUE;
				// vamos fazer write no header do arquivo.
				if( !pHeadView ){
					// o header ainda nao esta' mapeado. vamos fazer isso.
					CreateViewOfHead();
				}
			} else {
				if( !pWinView ){
					// o arquivo ainda nao esta' mapeado. vamos fazer isso.
					CreateViewOfFile();
				}
			}
		}
	}

	if( bContinue ){
		for( i = 0; i < tsNumItens; i++ ){
			if( _bIs32s ){
				if( write( iFile, pvBuf, (unsigned) tsSize ) < (int) tsSize ){
					break;
				}
			} else {
				if( bWriteHeader ){
					// gravar header no MMF.
					memcpy( pHeadView, pvBuf, tsSize );
				} else {
					if( pWinView ){
						// gravar no MMF.
						int	iNumBytes = ((iMMFWinSize * iPageSize) - iSeekWin) - (iHeadSize + 1);
						memcpy( (void*) ((char*) PWINVIEW + iSeekWin), pvBuf, min( iNumBytes, ((int) tsSize) ) );
						if( iNumBytes < ((int) tsSize) ){
							// precisamos mapear outra janela e continuar a gravacao
							++iWinNum;	// proxima janela
							CreateViewOfFile();
							if( !pWinView ){
								// mapeamento nao foi feito. fudeu.
								break;
							}
							// gravacao do restante
							memcpy( (void*) ((char*) PWINVIEW + iSeekWin), (void*) ((char*) pvBuf + iNumBytes), (tsSize - iNumBytes) );
							iSeekWin += (tsSize - iNumBytes);
						} else {
							iSeekWin += tsSize;
						}
					} else {
						DWORD	dwWrittenBytes;
						BOOL	bResult = WriteFile( hFile, pvBuf, (unsigned) tsSize, &dwWrittenBytes, NULL );
						if( !bResult || ( dwWrittenBytes < tsSize ) ){
							DWORD	dwErr = GetLastError();
							break;
						}
					}
				}
			}
		}
	}
//	if( ::GetTypeInt() == PE_REDE ){
//		Flush();
//	}
	dwLastUse = GetTickCount();
	if( cCriptoOn ){
		Decrypt( pvBuf, szKey, tsSize );
	}
	if( i < tsNumItens ){
#ifdef _USE_PRINTF_
		Printf( "C_File: Write: E_WRITE." );
#endif
		i = (size_t) E_WRITE;
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
#ifdef _USE_PRINTF_
	Printf( "C_File: Write: Vou retornar %d.", i );
#endif
	return( i );
}




/***
	Puts the file pointer in the given place.
	Parameters:
		- lOffset: number of bytes to jump from.
		- iWhence: SEEK_SET, SEEK_CUR or SEEK_END.
        Return: E_NOTOPEN, E_SEEK or OK.
***/
int
C_File::Seek( long lOffset, int iWhence )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( !bReOpen ){
			return( E_NOTOPEN );
		}
		switch( iWhence ){
		case SEEK_SET:
			if( hMMF ){
				// MMF
				SeekMMFWin( lOffset );
			}
			lCurPos = lOffset;
			break;
		case SEEK_CUR:
			lCurPos += lOffset;
			if( hMMF ){
				// MMF
				return( Seek( lCurPos, SEEK_SET ) );
			}
			break;
		case SEEK_END:
			Seek( FileSize() + lOffset, SEEK_SET );
			break;
		default:
			return( E_SEEK );
		}
	} else {
		if( _bIs32s ){
			long lAux = lseek( iFile, lOffset, iWhence );
			if( lAux == -1L ){
				return( E_SEEK );
			}
			lCurPos = lAux;
		} else {
			// fazer o seek no arquivo, mesmo que estejamos trabalhando sobre
			// MMF. Isso e' util para o caso de o arquivo precisar crescer.

			DWORD	dwResult;
		
			dwResult = SetFilePointer( hFile, 
						   lOffset, 
						   NULL, 
						   iWhence == SEEK_SET ? FILE_BEGIN :
						   iWhence == SEEK_CUR ? FILE_CURRENT :
						   FILE_END );
			if( dwResult == 0XFFFFFFFF ){
				// erro
				return( E_SEEK );
			}
			lCurPos = (long) dwResult;

			if( hMMF ){
				// MMF
				SeekMMFWin( lCurPos );
			}
		}
	}
	dwLastUse = GetTickCount();
	return( OK );
}




/***
	Write bytes at the end of a file from a given buffer.
	Parameters:
		- pvBuf: User buffer with data to append to.
		- tsSize: Size of iten to write
		- tsNumItens: Number of itens to write
	Return:
		Number of writtem itens in succes or E_NOTOPEN,
		E_BUFFNULL or E_WRITE.
***/
size_t
C_File::Append( void *pvBuf, size_t tsSize, size_t tsNumItens )
{
	if( !pvBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( Seek( 0, SEEK_END ) != OK ){
		return( (size_t) E_SEEK );
	}
	return Write( pvBuf, tsSize, tsNumItens );
}



/***
	Open a file. If the file exists it is openned "rb+" else
	it is openned "wb+".
	Parameters:
		- szNameFile: Name of file (just the name or full path)
		- szMode
		- iShFlag
	Return:
		E_NOTOPEN or OK (errno e' setado)
***/
int
C_File::Open( const char *szNameFile, const char *szModePar, int iShFlagPar, BOOL bWait )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int		iMode;
	DWORD	dwShMode;
	DWORD	dwCreateMode;

	if( (_bIs32s && iFile != -1) || (!_bIs32s && hFile != INVALID_HANDLE_VALUE) ){
		return( !OK );
	}
	strcpy( szFileName, szNameFile ? szNameFile : "" );
	strcpy( szMode, szModePar ? szModePar : "" );
	iShFlag = iShFlagPar;
	do{
		iMode = Mode16( szModePar );
		dwAccess = Mode( szModePar );
		dwShMode = ShMode( iShFlagPar );
		dwCreateMode = szModePar ? CreateMode( szModePar ) : Exist( szFileName ) ? OPEN_EXISTING : CREATE_ALWAYS;
		if( _bIs32s ){
			if( szModePar != NULL ){
				if( iMode & O_CREAT ){
					iFile = sopen( szNameFile, iMode, iShFlagPar, S_IREAD | S_IWRITE );
				} else {
					iFile = sopen( szNameFile, iMode, iShFlagPar );
				}
			} else {
				if( Exist( szNameFile ) ){
					iFile = sopen( szNameFile, O_BINARY | O_RDWR, iShFlagPar );
				} else {
					iFile = sopen( szNameFile, O_BINARY | O_RDWR | O_CREAT, iShFlagPar, S_IREAD | S_IWRITE );
				}
			}
		} else {
			saSecurity.nLength = sizeof( SECURITY_ATTRIBUTES );
			saSecurity.lpSecurityDescriptor = NULL;
			saSecurity.bInheritHandle = TRUE;
			hFile = CreateFile( szNameFile, dwAccess, dwShMode, &saSecurity, dwCreateMode, 
						(DWORD) (FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_SEQUENTIAL_SCAN),
						NULL );
		}
		if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
			if( _bIs32s ){
				if( errno == EEXIST && (iMode & O_EXCL) ){
					// ************************************************************
					// ATENCAO:
					// ************************************************************
					// nao tentar fechar outro arquivo para re-abrir este se 
					// errno == EEXIST && (iMode & O_EXCL)
					// ************************************************************
					iFile = -1;
					return( !OK );
				}
				if( errno == EACCES && bWait ){
					// o arquivo nao foi aberto porque estah sendo
					// usado por outro processo em modo exclusivo.
					// esperar um pouco e tentar novamente
					Sleep( 1000 );	// 1 segundo
					hFile = INVALID_HANDLE_VALUE;
					iFile = -1;

					// antes de continuar o loop, sair e entrar
					// novamente em regiao critica, para possibilitar
					// outros threads rodarem
					cCS0.LeaveCriticalSection();
					cCS0.EnterCriticalSection();
					continue;
				}
				if( errno != EMFILE ){
					iFile = -1;
					return( !OK );
				}
			} else {
				if( GetLastError() == ERROR_ALREADY_EXISTS && (dwCreateMode == CREATE_NEW) ){
					// ************************************************************
					// ATENCAO:
					// ************************************************************
					// nao tentar fechar outro arquivo para reabrir este se 
					// GetLastError() == ERROR_ALREADY_EXISTS && (dwCreateMode == CREATE_NEW)
					// ************************************************************
					return( !OK );
				}
				if( GetLastError() == ERROR_SHARING_VIOLATION && bWait ){
					// o arquivo nao foi aberto porque estah sendo
					// usado por outro processo em modo exclusivo.
					// esperar um pouco e tentar novamente
					Sleep( 1000 );	// 1 segundo
					hFile = INVALID_HANDLE_VALUE;
					iFile = -1;

					// antes de continuar o loop, sair e entrar
					// novamente em regiao critica, para possibilitar
					// outros threads rodarem
					cCS0.LeaveCriticalSection();
					cCS0.EnterCriticalSection();
					continue;
				}
				if( GetLastError() != ERROR_TOO_MANY_OPEN_FILES ){
#ifdef _USE_PRINTF_
					Printf( "C_File: Deu um erro doidao no Open." );
					Printf( "C_File: Fudeu em <%s>", szNameFile );
#endif
					hFile = INVALID_HANDLE_VALUE;
					iFile = -1;
					return( !OK );
				}
			}
#ifdef _USE_PRINTF_
			Printf( "C_File: Muitos arquivos abertos. Vou terminar." );
#endif
			return( !OK );
		}
	} while ( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) );
	if( this == _xFile ){
		Seek( 0, SEEK_SET );
		char	szCaca[ 50 ];
		sprintf( szCaca, "%d", ++_iNumXDat );
		Write( szCaca, strlen( szCaca ) );
		Seek( 0, SEEK_SET );
		Lock( strlen( szCaca ) );
#ifdef _USE_PRINTF_
		Printf( "C_File: Abri o _xFile****************************" );
#endif
	}
	if( strstr( szMode, "a" ) != NULL ){
		Seek( 0L, SEEK_END );
	}
	Hash();
	_iNumOpenFiles++;
#ifdef _USE_PRINTF_
	Printf( "C_File: Abri o arquivo <%d> (nome = <%s> - handle = <%d>)", _iNumOpenFiles, szNameFile ? szNameFile : "NULL", _bIs32s ? iFile : (int) hFile );
#endif

	// MMF: apenas se nao for 32s e se iHeadSize estiver setado para um valor maior que 0
	if( !_bIs32s && iHeadSize > 0 ){
		// pegar o tamanho da janela no .ini
		char	szFullIniName[ MAXPATH ];

		GetAppFullPath( szFullIniName, MAXPATH );


		iMMFWinSize = GetPrivateProfileInt( CONFIG_SESSION, WINDOWSIZE_KEY, 
											WINDOWSIZE_DEFAULT, szFullIniName );

		// se o tamanho da janela for <= 0, significa que o usuario nao quer usar MMF
		hMMF = NULL;
		if( iMMFWinSize > 0 ){
			hMMF = CreateFileMapping( hFile, NULL,
				(dwAccess & GENERIC_WRITE) ? PAGE_READWRITE : PAGE_READONLY,
				0, 0, NULL );
		}
		pHeadView = NULL;
		pWinView = NULL;
		iWinNum = 0;
		iSeekWin = 0;
	}

	bRealLock = _bStaticRealLock;

	return( OK );
}

/***
	Hash function
***/
int
C_File::Hash()
{
	iLine = 0;
	
	for( char *c = szFileName; *c; c++ ){
		iLine = ( ( iLine += *c ) % NUMLIST );
	}
	return iLine;
}


/***
	Check if a file exists.
	Parameters:
		- szNameFile: The name of file (just the name or full path)
	Return:
		TRUE or FALSE
***/
BOOL
C_File::Exist( const char *szFile )
{
	HANDLE hTmpFile = CreateFile( szFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
						(DWORD) (FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_SEQUENTIAL_SCAN),
						NULL );
	if ( hTmpFile != INVALID_HANDLE_VALUE ) {
		CloseHandle(hTmpFile);
		return TRUE;
	}
	return( FALSE );
}




/***
	Closes a file.
	Parameters:
		- None
	Return:
		- OK or E_CLOSE
***/
int
C_File::Close()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockList &l = *(_LockTable[ iLine ]);
	for( int i = 0; i < l.NumElem(); ){
		LockStruct *lsAux = l [ i ];
		if( lsAux->pcfFile == this ){
			l.Del();
			// desfazer o lock no SO
			RealRelease( lsAux );
		} else {
			i++;
		}
	}
	if( (_bIs32s && iFile != -1) || (!_bIs32s && hFile != INVALID_HANDLE_VALUE) ){
		if( _bIs32s ){
			int i = close( iFile );
			iFile = -1;
			if( i == 0 ){
#ifdef _USE_PRINTF_
				Printf( "C_File: Fechei o arquivo <%d> (handle = <%d>)", _iNumOpenFiles, iFile );
#endif
				--_iNumOpenFiles;
			}
//			GeraLIFILELog();
			TurnOffCripto();
			return( i == 0 ? OK : E_CLOSE );
		} else {
			HANDLE hCloseFile = hFile;
			int i = CloseHandle( hFile );
			hFile = INVALID_HANDLE_VALUE;
			if( i == TRUE ){
#ifdef _USE_PRINTF_
				Printf( "C_File: Fechei o arquivo <%d> (handle = <%d>)", _iNumOpenFiles, (int) hCloseFile );
#endif
				--_iNumOpenFiles;
			}
			// fechar MMF
			if( hMMF ){
				if( pHeadView ){
					UnmapViewOfFile( pHeadView );
					pHeadView = NULL;
				}
				if( pWinView ){
					UnmapViewOfFile( pWinView );
					pWinView = NULL;
				}
				CloseHandle( hMMF );
				hMMF = NULL;
			}
//			GeraLIFILELog();
			TurnOffCripto();
			return( i == TRUE ? OK : E_CLOSE );
		}
	}
//	GeraLIFILELog();
	TurnOffCripto();
	return( OK );
}





/***
***/
static int
Mode16( const char *szMode )
{
	int iMode = O_RDWR | O_BINARY | O_CREAT;

	if( !szMode ){
		return( iMode );
	}

	if( strcmp( szMode, "rb" ) == 0 )
		iMode = O_RDONLY | O_BINARY;
	else if( strcmp( szMode, "rt" ) == 0 )
		iMode = O_RDONLY | O_TEXT;
	else if( strcmp( szMode, "rb+" ) == 0 )
		iMode = O_RDWR | O_BINARY;
	else if( strcmp( szMode, "rt+" ) == 0 )
		iMode = O_RDWR | O_TEXT;
	else if( strcmp( szMode, "wb" ) == 0 )
		iMode = O_RDWR | O_BINARY | O_CREAT;
	else if( strcmp( szMode, "wt" ) == 0 )
		iMode = O_RDWR | O_TEXT | O_CREAT;
	else if( strcmp( szMode, "wb+" ) == 0 )
		iMode = O_RDWR | O_BINARY | O_CREAT;
	else if( strcmp( szMode, "wt+" ) == 0 )
		iMode = O_RDWR | O_TEXT | O_CREAT;

	if( strstr( szMode, "++" ) != NULL ){
		iMode |= O_EXCL;
	}
	return( iMode );
}


/***		      
***/
DWORD
Mode( const char *szMode )
{
	if( !szMode ){
		return( GENERIC_READ | GENERIC_WRITE );
	}

	DWORD dwMode = 0;

	for( int i = 0; i < (int) strlen( szMode ); i++ ){
		switch( szMode[ i ] ){
		case 'a':
			dwMode = GENERIC_READ | GENERIC_WRITE;
			break;

		case 'r':
			dwMode |= GENERIC_READ;
			break;

		case 'w':
			dwMode |= GENERIC_WRITE;
			break;

		case '+':
			dwMode = GENERIC_READ | GENERIC_WRITE;
			break;
		}
	}
	return( dwMode );
}


/***
***/
DWORD
ShMode( int iShFlagPar )
{
	DWORD dwMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	if( iShFlagPar & _SH_DENYRW ){ // Denies read and write access
		dwMode = 0;
		return( dwMode );
	}
	if( iShFlagPar & _SH_DENYWR ){ // Denies write access to file
		dwMode &= ~FILE_SHARE_WRITE;
	}
	if( iShFlagPar & _SH_DENYRD ){ // Denies read access to file
		dwMode &= ~FILE_SHARE_READ;
	}
	return( dwMode );
}


/***
***/
DWORD
CreateMode( const char *szMode )
{
	DWORD dwMode = CREATE_ALWAYS;

	if( !szMode ){
		return( dwMode );
	}

	if( strstr( szMode, "++" ) != NULL )
		dwMode = CREATE_NEW;
	else if( strstr( szMode, "a" ) != NULL )
		dwMode = OPEN_ALWAYS;
	else if( strstr( szMode, "r" ) != NULL )
		dwMode = OPEN_EXISTING;
	else if( strstr( szMode, "w" ) != NULL )
		dwMode = CREATE_ALWAYS;
	return( dwMode );
}


/***
***/
LockStruct *
C_File::GetLock( LockStruct *ls )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockList &l = *(_LockTable[ iLine ]);
	for( int i = 0; i < l.NumElem(); i++ ){
		LockStruct *lsAux = l [ i ];
		if( lsAux->pcfFile == ls->pcfFile && lsAux->iPos == ls->iPos && 
			lsAux->iSize == ls->iSize ){
			return lsAux;
		}
	}
	return NULL;
}


/***
	Retorna TRUE se houve tentativa de lock em uma regiao depois que a mesma
	ja' estava travada.
***/
BOOL
C_File::TryUse()
{
	LockStruct	ls( this, CurPos(), 0L );

	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockList &l = *(_LockTable[ iLine ]);
	for( int i = 0; i < l.NumElem(); i++ ){
		LockStruct *lsAux = l [ i ];
		if( lsAux->pcfFile == ls.pcfFile && lsAux->iPos == ls.iPos && lsAux->bTryUse == TRUE ){
			return( TRUE );
		}
	}
	return( FALSE );
}



/***
***/
int
C_File::DelLock( LockStruct *ls )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockStruct *lsAux = GetLock( ls );
	if( lsAux ){
		if( RealRelease( lsAux ) == OK ){
			if( --lsAux->iCount <= 0 ){
				_LockTable [ iLine ]->Del();
			}
			// dispara o evento de release para que
			// os metodos de lock em wait sejam liberados
			SetEvent( _hWaitLockEvent );
			return( OK );
		}
	} 
	return( !OK );
}



/***
***/
int
C_File::AddLock( LockStruct *ls, BOOL bWait )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockStruct *lsAux = GetLock( ls );
	if( lsAux ){
		lsAux->iCount++;
		if( ls ){
			delete ls;
		}
		return( OK );
	} else {
		if( !IsLocked( ls, TRUE ) ){
			ls->iCount++;
			if( _LockTable [ iLine ]->Add( ls, TAIL ) == OK ){
				if( RealLock( ls, bWait ) == OK ){
					return( OK );
				} else {
					_LockTable [ iLine ]->Refresh( NULL );
					_LockTable [ iLine ]->Del();
				}
			}
		}
	}
	return( !OK );
}




/***
	Metodo Lock
	Trava o registro

	Parameters:
		- pcfControlFile

	Return:
		LBS_OK se conseguir travar ou erro.

	Comments:

***/
int
C_File::Lock( long lSize, BOOL bWait )
{
//	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			return( E_NOTOPEN );
		}
	}

	LockStruct *ls = new LockStruct( this, CurPos(), lSize );
	if( ls ){
		if( AddLock( ls, bWait ) == OK ){
			return( OK );
		}
		delete ls;
	}
	return( !OK );
}



/***
	Metodo Release
	Libera um registro previamente travado

	Parameters:
		- pcfControlFile

	Return:
		LBS_OK se conseguir liberar ou erro.

	Comments:

***/
int
C_File::Release( long lSize )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			return( E_NOTOPEN );
		}
	}
	LockStruct ls( this, CurPos(), lSize );
	return( DelLock( &ls ) );
}


void
C_File::TurnOnCripto( char *szKey )
{
	memset( C_File::szKey, 0, MAXCRIPTOKEY );
	strncpy( C_File::szKey, szKey, MAXCRIPTOKEY );
	cCriptoOn = 1;
}

void
C_File::TurnOffCripto( void )
{
	cCriptoOn = 0;
}



long
C_File::FileSize()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( -1 );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}

	if( _bIs32s ){
		long lCurPosAux = CurPos();
		Seek( 0, SEEK_END );
		long lSize = CurPos();
		Seek( lCurPosAux, SEEK_SET );
		if( iFlag ){
			PseudoClose();
			_xFile->ReOpen();
		}
		return( lSize );
	}
	// guarda a posicao corrente
//	long	lCurPosAux = CurPos();

	DWORD	dwResult = GetFileSize( hFile, NULL );

/*	// vai para o fim do arquivo e pega o numero do ultimo byte
	dwResult = SetFilePointer( hFile, 0, NULL, FILE_END );
/*
	if( dwResult == 0XFFFFFFFF ){
		DWORD	dw = GetLastError();
		char	szErr[ 500 ];

		sprintf( szErr, "Erro no GetFileSize: %d", (int) dw );
		MessageBox( NULL, szErr, "DEBUG - LIFILE", MB_OK );
	}

	// volta para a posicao que estava
	Seek( lCurPosAux, SEEK_SET );
*/
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( (long) dwResult );
}

int
C_File::PseudoClose( void )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		return( OK );
	}
#ifdef _USE_PRINTF_
	if( this == _xFile ){
		Printf( "C_File: Estou (pseudo) fechando o _xFile****************************" );
	}
#endif
	lCurPos = CurPos();
	Close();
	bReOpen = TRUE;
	return( OK );
}



long	
C_File::CurPos()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	int iFlag = FALSE;
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( -1 );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}
	long 	lRet;
	DWORD	dwResult;
	if( _bIs32s ){
		lRet = lseek( iFile, 0, SEEK_CUR );
	} else {
		dwResult = SetFilePointer( hFile, 0, NULL, FILE_CURRENT );
	}
#ifdef _USE_PRINTF_
	Printf( "C_File: CurPos do arquivo %d eh %d", (int) hFile, _bIs32s ? iFile : (int) dwResult );
#endif
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( _bIs32s ? lRet : (long) dwResult );
}


/***
	Retorna TRUE se existir alguma instancia de C_File (que nao esta)
	com lock na regiao definida pelo parametro ls.

	Se retornar FALSE, e' porque nao ha' nenhuma outra instancia de C_File
	travando o arquivo.

	Nao checa se a mesma instancia esta' travando o arquivo.
***/
BOOL 
C_File::IsLocked( LockStruct *ls, BOOL bMark )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	LockList &l = *(_LockTable [ iLine ]);
	for( int i = 0; i< l.NumElem(); i++ ){
		LockStruct *lsAux = l[ i ];
		if( lsAux->pcfFile != ls->pcfFile ){				 // handles diferentes
			if( strcmp( lsAux->pcfFile->szFileName, ls->pcfFile->szFileName ) == 0 ){ // nomes iguais
				if( ( lsAux->iPos >= ls->iPos && lsAux->iPos < ls->iPos + ls->iSize ) || // posicoes
					( ls->iPos >= lsAux->iPos && ls->iPos < lsAux->iPos + lsAux->iSize ) ){ // sobrepostas
					if( bMark ){
						// indica que alguem tentou fazer lock na regiao que esta'
						// travada
						lsAux->bTryUse = TRUE;
					}
					return( TRUE );
				}
			}
		}
	}
	return( FALSE );
}



/***
	CalcMaxOpenFiles
	Calcula o numero maximo de arquivos que podem ser abertos simultaneamente.
	Em Win32s esse numero eh bastante pequeno (+- 15). Como a biblioteca nao podemos
	usar todos os recursos disponiveis (tem que sobrar para os outros), temos que
	impor um limite abaixo disso.
	Em NT e Win95 nao temos esse problema. Ja conseguimos abrir 200 arquivos sem
	problemas.
***/
int
C_File::CalcMaxOpenFiles()
{
	OSVERSIONINFO	osInfo;
	BOOL		bRet;

	osInfo.dwOSVersionInfoSize = sizeof( osInfo );
	bRet = GetVersionEx( &osInfo );
	if( !bRet ){
		// a funcao GetVersionEx nao funcionou. Vamos assumir o numero maximo
		// como sendo MAXOPENFILES
		return( MAXOPENFILES );
	}
	switch( osInfo.dwPlatformId ){
	case 0://VER_PLATFORM_WIN32s: (Win32s)
		// assumiremos um valor default para 32s. Caso seja necessario,
		// a aplicacao pode alterar este valor atraves do metodo
		// SetNumFiles, que so' e' util para Win32s.
		return( NUMOPENFILES32s );

	case 1://VER_PLATFORM_WIN32_WINDOWS: (Windows 95)
	case 2://VER_PLATFORM_WIN32_NT: (Windows NT)
		return( MAXOPENFILES );

	}
	// versao do sistema nao conhecida. Vamos retornar o valor MAXOPENFILES
	return( MAXOPENFILES );
}



/***
	static PUBLIC

	Este metodo seta o numero maximo de arquivos que podem ser abertos
	simultaneamente. So' vale para ambientes 32s. Para NT ou 95, este metodo
	retorna erro.
***/
int
C_File::SetNumFiles32s( int inf )
{
	if( inf <= 0 ){
		return( !OK );
	}

	if( !Is32s() ){
		// plataforma nao eh Win32s
#ifdef _USE_PRINTF_
		Printf( "C_File: Plataforma nao eh Win32s" );
#endif
		return( !OK );
	}
	_iMaxOpenFiles = inf;
#ifdef _USE_PRINTF_
	Printf( "C_File: Setei o numero de arqs p/ 32s <%d>", _iMaxOpenFiles );
#endif
	return( OK );
}

/***
	static PUBLIC
	Is32s
	Verifica se o sistema em uso e' 32s

	Retorna TRUE se o sistema for Win32s e FALSE caso contrario.
***/
BOOL
C_File::Is32s()
{
	OSVERSIONINFO	osInfo;
	osInfo.dwOSVersionInfoSize = sizeof( osInfo );
	if( GetVersionEx( &osInfo ) ){
		if( osInfo.dwPlatformId != 0 ){	// VER_PLATFORM_WIN32s
			// plataforma nao eh Win32s
			return( FALSE );
		}
	}
	return( TRUE );
}


/***
	static PUBLIC
	Get32sVar
	Retorna o conteudo da variavel global _bIs32s
***/
BOOL
C_File::Get32sVar()
{
	return( _bIs32s );
}


/***
	static PUBLIC
	Fecha os arquivos stdin, stdout e stderr
***/
int
C_File::CloseStdFiles()
{
	fclose( stdin );
	fclose( stdout );
	fclose( stderr );
#ifdef _USE_PRINTF_
	Printf( "C_File: Fechei os stdfiles" );
#endif
	return( OK );
}



/***
	IsOpen
***/
BOOL
C_File::IsOpen()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( (_bIs32s && iFile != -1) || (!_bIs32s && hFile != INVALID_HANDLE_VALUE) ){
		return( TRUE );
	}
	if( !bReOpen ){
		return( FALSE );
	}
	return( TRUE );
}

/***
	PUBLIC
	GetHandle
***/
int
C_File::GetHandle()
{
	return( _bIs32s ? iFile : (int) hFile ); 
}


/***
	PUBLIC
	Rewind
***/
int
C_File::Rewind()
{
	return( Seek( 0, SEEK_SET ) );
};


/***
	PUBLIC
	Flush
***/
int
C_File::Flush()
{
	if( !IsOpen() ){
		return( !OK );
	}
	if( _bIs32s ){
		return( _commit( iFile ) == 0 ? OK : !OK );
	}
	return( FlushFileBuffers( hFile ) == TRUE ? OK : !OK );
}



/***
	PUBLIC
	PseudoCloseAllFiles

	Fecha temporariamente todos os arquivos gerenciados pelo C_File
	As informacoes dos arquivos sao mantidas em memoria para que eles
	possam ser reabertos e ter seus contextos reassumidos.
***/
int
C_File::PseudoCloseAllFiles()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	for( int i = 0; i < MAXOPENFILES; i++ ){
		if( _cfFiles[ i ] ){
			_cfFiles[ i ]->PseudoClose();
		}
	}
	return( OK );
}


/***
	PUBLIC
	ReOpenAllFiles

	Reabre todos os arquivos que foram fechados pelo PseudoCloseAllFiles.
	O contexto de cada um deles e' restaurado.
***/
int
C_File::ReOpenAllFiles()
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	for( int i = 0; i < MAXOPENFILES; i++ ){
		if( _cfFiles[ i ] ){
			_cfFiles[ i ]->ReOpen();
		}
	}
	return( OK );
}

/***
	PROTECTED
	Encrypt

	Criptografa buffers de memoria usando a funcao
	Cripto, de LI.LIB
***/
void
C_File::Encrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	Cripto( pvBuf, szKey, tsSize );
}


/***
	PROTECTED
	Decrypt

	Decriptografa buffers de memoria usando a funcao
	Descripto, de LI.LIB
***/
void
C_File::Decrypt( void *pvBuf, char *szKey, size_t tsSize )
{
	Descripto( pvBuf, szKey, tsSize );
}

/***
	PUBLIC
	IsCriptoOn

	Verifica se o esquema de criptografia esta' ligado ou
	desligado.
***/
BOOL
C_File::IsCriptoOn()
{
	return( cCriptoOn );
}

/***
	PRIVATE
	CreateViewOfFile

	Mapeia um pedaco do arquivo em memoria.
***/
void
C_File::CreateViewOfFile()
{
	if( pWinView ){
		// desfazer o mapeamento anterior
		UnmapViewOfFile( pWinView );
	}


	// calcular o tamanho maximo que pode ser mapeado
	long lFSize = FileSize();
	long lSize = lFSize - (iWinNum * iPageSize);

	if( lSize < 0 ){
		// esta situacao nao deveria acontecer
		pWinView = NULL;
		return;
	}
	long lMaxSize = (iMMFWinSize * iPageSize) > lSize ? 0L : (iMMFWinSize * iPageSize);
	
	// mapear o arquivo em memoria
	pWinView = MapViewOfFile( hMMF, (dwAccess & GENERIC_WRITE) ? 
								FILE_MAP_WRITE : FILE_MAP_READ,
								(iWinNum * iPageSize),
								0,
								lMaxSize );
	iSeekWin = 0;
}

/***
	PRIVATE
	CreateViewOfHead

	Mapeia um pedaco do arquivo (o header) em memoria.
***/
void
C_File::CreateViewOfHead()
{
	if( pHeadView ){
		// desfazer o mapeamento anterior
		UnmapViewOfFile( pHeadView );
	}

	// mapear o arquivo em memoria
	pHeadView = MapViewOfFile( hMMF, (dwAccess & GENERIC_WRITE) ? 
								FILE_MAP_WRITE : FILE_MAP_READ,
								iHeadInit,
								0,
								iHeadSize );
}


/***
	PRIVATE
	SeekMMFWin

	Relaliza um seek sobre o mapeamento MMF do arquivo.
	(considera-se que o seek sera' feito sempre a partir do inicio 
	do arquivo - SEEK_SET)
***/
void	
C_File::SeekMMFWin( long lOffset )
{
	if( lOffset >= ((iWinNum+1) * (iPageSize * iMMFWinSize)) ){
		// lOffset esta' depois da janela atual. temos que mapear outra janela.
		// basta zerar o mapeamento atual. quando um read ou write precisar,
		// refaz o mapeamento.
		if( pWinView ){
			UnmapViewOfFile( pWinView );
			pWinView = NULL;
		}
		if( pHeadView ){
			UnmapViewOfFile( pHeadView );
			pHeadView = NULL;
		}
		// recalcula o numero da janela corrente
		iWinNum = lOffset / (iPageSize * iMMFWinSize);
	}
	if( lOffset < (iWinNum * (iPageSize * iMMFWinSize)) ){
		// lOffset esta' antes da janela atual. temos que mapear outra janela.
		// basta zerar o mapeamento atual. quando um read ou write precisar,
		// refaz o mapeamento.
		if( pWinView ){
			UnmapViewOfFile( pWinView );
			pWinView = NULL;
		}
		if( pHeadView ){
			UnmapViewOfFile( pHeadView );
			pHeadView = NULL;
		}
		// recalcula o numero da janela corrente
		iWinNum = lOffset / (iPageSize * iMMFWinSize);
	}
	iSeekWin = (lOffset > (iPageSize * iMMFWinSize)) ? 
				(lOffset - (iWinNum * (iPageSize * iMMFWinSize))) : 
				lOffset;

	// protecao
	if( iSeekWin < 0 ){
		iSeekWin = 0;
	}
}


/***
	PRIVATE
	GrowFile

	Aumenta o tamanho do arquivo para lNewSize bytes.
	E' possivel que os buffers MMF sejam resetados (pWinView e pHeadView).
	E' interessante que o chamador deste metodo reavalie a necessidade de fazer
	um novo mapeamento do arquivo em MMF (refazer pWinView e pHeadView).
***/
int
C_File::GrowFile( long lNewSize )
{
	// guarda posicao atual
	long	lCPos = CurPos();

	// o seek abaixo ja' faz o arquivo crescer
	int		iRet = Seek( lNewSize, SEEK_SET );

	// volta para a posicao que estava
	Seek( lCPos, SEEK_SET );

	return( iRet );
}

/***
	static PUBLIC
	SetRealLock

	Habilita/desabilita o lock a nivel de sistema operacional.
	Quando o lock de SO esta' desabilitado, o C_File controla
	todos os locks em memoria.

	Apenas os arquivos que forem abertos depois da habilitacao
	do RealLock eh que terao seus locks feitos a nivel de SO. Os
	arquivos que ja' estiverem abertos, continuarao a ter os locks
	controlados em memoria.
***/
void
C_File::SetRealLock( BOOL bState )
{
	_bStaticRealLock = bState;
}

/***
	PRIVATE
	RealLock

	Realiza um lock em uma regiao do arquivo, utilizando rotinas
	do Sistema Operacional
***/
int
C_File::RealLock( LockStruct *ls, BOOL bWait )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( !bRealLock ){
		return( OK );
	}
	int	iRet = !OK;
	int	iFlag = FALSE;
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){
			if( !_xFile ){
				return( !OK );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}

	if( ls ){
		if( _bIs32s ){
			long lPos = CurPos();
			if( Seek( ls->iPos, SEEK_SET ) == OK ){
				iRet = locking( iFile, _LK_LOCK, ls->iSize );
			}
			Seek( lPos, SEEK_SET );
		} else {
			if( Seek( ls->iPos, SEEK_SET ) == OK ){
				DWORD	dwErr;

				SetLastError( 0 );
				iRet = LockFile( hFile, ls->iPos, 0, ls->iSize, 0 ) ? OK : !OK;
				dwErr = GetLastError();
				while( bWait && ((dwErr == ERROR_LOCK_FAILED) || (dwErr == ERROR_LOCK_VIOLATION)) ){
					// esperar e tentar novamente.
					cCS0.LeaveCriticalSection();
					Sleep( 1000 );	// 1 segundo
					cCS0.EnterCriticalSection();
					SetLastError( 0 );
					iRet = LockFile( hFile, ls->iPos, 0, ls->iSize, 0 ) ? OK : !OK;
					dwErr = GetLastError();
				}
			}
		}
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( iRet );
}

/***
	PRIVATE
	RealRelease

	Realiza um unlock em uma regiao do arquivo, utilizando rotinas
	do Sistema Operacional
***/
int
C_File::RealRelease( LockStruct *ls )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );
	if( !bRealLock ){
		return( OK );
	}
	int	iRet = !OK;
	int	iFlag = FALSE;
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){
			if( !_xFile ){
				return( !OK );
			}
			_xFile->PseudoClose();
			ReOpen();
			iFlag = TRUE;
		}
	}

	if( ls ){
		if( _bIs32s ){
			long lPos = CurPos();
			if( Seek( ls->iPos, SEEK_SET ) == OK ){
				iRet = locking( iFile, _LK_UNLCK, ls->iSize );
			}
			Seek( lPos, SEEK_SET );
		} else {
			if( Seek( ls->iPos, SEEK_SET ) == OK ){
				iRet = UnlockFile( hFile, ls->iPos, 0, ls->iSize, 0 ) ? OK : !OK;
			}
		}
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
	return( iRet );
}

/***
	Retorna a data de criacao do arquivo
***/
time_t
C_File::GetCreateTime()
{
	struct stat sStatus;
	int	iOLStat = stat( szFileName, &sStatus );
	if( iOLStat == 0 ){
		return( sStatus.st_ctime );
	}
	return( 0 );
}

/***
	Retorna o nome do arquivo
***/
const char *
C_File::GetFileName()
{
	return( szFileName );
}

/***
	Retorna uma estrutura stat com dados 
	sobre o arquivo
***/
int
C_File::GetFileStatInfo( struct stat *psInfo )
{
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( !bReOpen ){
			return( E_NOTOPEN );
		}
	}
	if( !psInfo ){
		return( !OK );
	}
	int	iStat = stat( szFileName, psInfo );
	if( iStat == 0 ){
		return( OK );
	}
	return( !OK );
}

C_FileCritSect::C_FileCritSect( C_File *pObjPar, int iNumCritSect )
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar );
		iLastSectUsed = iNumCritSect;
		pObj = pObjPar;
	}
}

C_FileCritSect::~C_FileCritSect()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->LeaveCriticalSection( iLastSectUsed );
	}
}

void 
C_FileCritSect::EnterCriticalSection()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
	}
}

void 
C_FileCritSect::LeaveCriticalSection()
{
	if( _pcGlobalFileCritSect ){
		_pcGlobalFileCritSect->LeaveCriticalSection( iLastSectUsed );
	}
}

