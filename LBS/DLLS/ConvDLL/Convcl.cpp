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


//#include "resource.h"
#include "stdafx.h"
#include <lbs.h>
#include "ConvCl.h"
#ifndef	_CVBERR_H_
#include "CvbErr.h"
#endif
#include <fbdlgcl.h>
#ifndef	_OLDTYPES_H_
#include "oldtypes.h"
#endif
#ifndef _LB1_
#include <lb1cl.h>
#endif
#ifndef _LB3_
#include <lb3cl.h>
#endif
#ifndef _LB4_
#include <lb4cl.h>
#endif
#ifndef _OLDLB1_
#include "oldlb1cl.h"
#endif
#ifndef _OLDLB2_
#include "oldlb2cl.h"
#endif
#ifndef _OLDLB3_
#include "oldlb3cl.h"
#endif
#ifndef _OLDLB4_
#include "oldlb4cl.h"
#endif
#ifndef _CRIPTO_
#include <cripto.h>
#endif
#include "CDLLLIProg.h"
extern "C" {
#include <crypt.h>
}
#include <slot.h>
extern "C" {
#include	<personcl.h>
}

#include	<math.h>

#define	BASE_CRYPTO3	3
#define	BASE_CRYPTO4	4
#define	BASE_CRYPTO6	6
#define	BASE_VERSAO7	7
#define	BASE_VERSAO8	8
#define	BASE_VERSAO9	9
#define	BASE_VERSAO10	10
#define	BASE_VERSAO11	11
#define	FROM3TO4		3
#define	FROM4TO3		4
#define	OTHER_ENTTRIES	10					// pontos dispersos de atualizacao
											// do progress_control
#define	PROGRESS_SIZE	(90+OTHER_ENTTRIES)	// numero de atualizacoes do
											// progress_control
#define	ROUND( x )		( ((x - floor( x )) >= 0.5) ? ((int) ceil( x )) : ((int) floor( x )) )

// prototipos
//UINT Thread3to4( LPVOID );
//UINT Thread4to3( LPVOID );

typedef	struct	_sBasesFileV3 {					//  registro do arquivo de bases
	CL_StringN<FULLNAMESIZE>	szBaseName;		// alias_name da base
	CL_StringN<FULLNAMESIZE>	szUserBaseName;	// nome da udb
	BYTE						bBaseType;		// tipo da base
	BOOL						bRecDeleted;	// indica se o registros esta' deletado.
}	TBasesFileV3;

static	BOOL	bStarted = FALSE;


/***
	PUBLIC
	Construtor
	Parameters:
		- pWnd	-> janela mae do progress control que aparecera'
				   durante o processod e conversao.
***/
C_ConvBase::C_ConvBase()
{
	if( !bStarted ){
		bStarted = TRUE;
		RegisterProgressClass( ::AfxGetInstanceHandle() );
	}
	bDefUdbConv = FALSE;
	bLBWNamesConv = FALSE;
	bKeepOrig = FALSE;
	memset( szLastError, 0, LASTERRORSIZE );
}

/***
	PUBLIC
***/
C_ConvBase::~C_ConvBase()
{
}

/***
	PUBLIC
	Metodo VerifyConvBase
	Verifica a necessidade de se converter uma base LBS.

	Parameters:
		- szBaseName	- nome da base (sem o path; basta o
						  nome, como LBWD0001)

	Return:
		- TRUE se for necessario converter a base; 
		  FALSE caso contrario.

	Comments:
		-

***/
BOOL C_ConvBase::VerifyConvBase( char *szBaseName )
{
	memset( szLastError, 0, LASTERRORSIZE );
	if( GetBaseVersion( szBaseName ) < BASE_CRYPTO4 ){
		return( TRUE );
	}
	return( FALSE );
}

/***
	PUBLIC
	Metodo ConvertBase
	Converte uma base de dados e suas "sub-bases".

	Parameters:
		- bKeepOrigPar	- indica se os arquivos originais devem ser
						  preservados, com nomes Temp.LB*
		- szBaseName	- nome da base (sem o path; basta o
						  nome, como LBWD0001). Se for NULL,
						  todas as bases serao convertidas.

	Return:
		- CONV_OK em caso de sucesso ou codigo 
		  de erro em caso de falha.

	Comments:
		-

***/
int C_ConvBase::ConvertBase( BOOL bKeepOrigPar, char *szBaseName )
{
	char			szControlFile[ MAXPATH ];
	char			szBaseDir[ MAXPATH ];
	C_FeedBackDlg	cProgDlg;
	CWaitCursor		cWaitCur;

	memset( szLastError, 0, LASTERRORSIZE );
	bKeepOrig = bKeepOrigPar;

	// obter o diretorio base e o nome do arquivo de controle
	// do LBS
	if( !GetBaseDir( szBaseDir ) || !GetControlFileName( szControlFile ) ){
		// nome nao encontrado
		CString	sAux;
		sAux.Format( CONVEM_CONTROLNOTFOUND );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( CONVE_CONTROLNOTFOUND );
	}

	if( szBaseName ){
		strupr( szBaseName );
	}

	cProgDlg.ShowWindow( SW_SHOW );

	// abre o arquivo de controle
	TBasesFile	tbfAux;
	CString		sFileName;
	int			iNumBases = 0;
	
	sFileName.Format( "%s\\%s", (LPCTSTR) szBaseDir, (LPCTSTR) szControlFile );

	// verificar versao do arquivo de controle
	if( GetControlFileVersion( (char*) (LPCSTR) sFileName ) < CRYPTO_MAGICNUMBER ){
		// arquivo de controle com versao errada.
		// converter o arquivo de controle.
		if( ConvertControlFile( sFileName, cProgDlg ) != OK ){
			// deu pau na conversao do arquivo de controle.
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_CONTROLCONVERROR, (char*) (LPCTSTR) sFileName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			cProgDlg.ShowWindow( SW_HIDE );
			return( CONVE_CONTROLCONVERROR );
		}
	}

	C_RecordFile	cfBasesFile( (char*) (LPCSTR) sFileName, CRYPTO_MAGICNUMBER, 0, 
								 sizeof( TBasesFile ), "HEADKEY", 
								 "RECKEY", NULL, SH_DENYRW, TRUE );

	if( !cfBasesFile.IsOpen() ){
		// nao consegui abrir o arquivo de controle
		CString	sAux;
		AfxFormatString1( sAux, CONVEM_CONTROLOPENERROR, (char*) (LPCTSTR) sFileName );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		cProgDlg.ShowWindow( SW_HIDE );
		return( CONVE_CONTROLOPENERROR );
	}
	cfBasesFile.R_Seek( 0 );
	while( cfBasesFile.R_Read( &tbfAux ) == OK ){
		// Pegar nome de uma base
		if( tbfAux.bRecDeleted == TRUE ){
			// registro deletado
			if( cfBasesFile.R_SeekNext() != OK ){
				break;
			}
			continue;
		} else {
			// achei uma base. 
			CString	sBaseName = _T("");
			int		iIndex = 0;
			long	lCurPos = 0;

			switch( GetBaseVersion( (const char*) (char*) tbfAux.szBaseName ) ){
			case BASE_CRYPTO3:
				if( tbfAux.szBaseName == (char*) "DEFUDB" ){
					bDefUdbConv = FALSE;
				}
				if( tbfAux.szBaseName == (char*) "LBWNAMES" ){
					bLBWNamesConv = FALSE;
				}
				if( szBaseName ){
					CString	sAux;

					sBaseName = (char*) tbfAux.szBaseName;
					iIndex = sBaseName.Find( '\\' );
					sAux = iIndex > 0 ? sBaseName.Left( iIndex ) : sBaseName;
					if( sAux != (LPCTSTR) szBaseName ){
						// o usuario indicou uma base especifica e a base
						// encontrada nao eh a indicada. vamos tentar outra.
						if( cfBasesFile.R_SeekNext() != OK ){
							break;
						}
						continue;
					}
				}
				sBaseName = (char*) tbfAux.szBaseName;
				// converter a base
				lCurPos = cfBasesFile.R_CurPos();
				if( !ConvertBase3to4( sBaseName, cProgDlg, cfBasesFile, sFileName ) ){
					// deu merda.
					if( szBaseName ){
						// deveriamos converter apenas uma base
						// e deu merda na conversao. vamos retornar
						// erro.
						CString	sAux;
						AfxFormatString1( sAux, CONVEM_ERRCONV, (char*) (LPCTSTR) szBaseName );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
						cProgDlg.ShowWindow( SW_HIDE );
						return( CONVE_ERRCONV );
					}
				}
				cfBasesFile.R_Seek( lCurPos );
				++iNumBases;
				break;

			case BASE_CRYPTO4:
			case BASE_CRYPTO6:
			case BASE_VERSAO7:
			case BASE_VERSAO8:
			case BASE_VERSAO9:
			case BASE_VERSAO10:
			case BASE_VERSAO11:
				if( tbfAux.szBaseName == (char*) "DEFUDB" ){
					bDefUdbConv = TRUE;
				}
				if( tbfAux.szBaseName == (char*) "LBWNAMES" ){
					bLBWNamesConv = TRUE;
				}
				++iNumBases;
				break;

			default:
				if( szBaseName ){
					CString	sAux;

					sBaseName = szBaseName;
					iIndex = sBaseName.Find( '\\' );
					sAux = iIndex > 0 ? sBaseName.Left( iIndex ) : sBaseName;
					if( sAux == (char*) tbfAux.szBaseName ){
						// a base indicada possui um numero de versao
						// desconhecido por esta aplicacao.
						CString	sAux;
						AfxFormatString1( sAux, CONVEM_UNKNOWNBASEVERSION, (char*) (LPCTSTR) szBaseName );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
						cProgDlg.ShowWindow( SW_HIDE );
						return( CONVE_UNKNOWNBASEVERSION );
					}
				}
			}
		}
		if( cfBasesFile.R_SeekNext() != OK ){
			break;
		}
	}

	// fecha o arquivo de controle
	cfBasesFile.Close();

	// esconde a dialog com o progress_control
	cProgDlg.ShowWindow( SW_HIDE );

	if( !iNumBases ){
		// nenhuma base foi encontrada no arquivo de controle.
		CString	sAux;
		sAux.Format( CONVEM_NOBASESTOCONV );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( CONVE_NOBASESTOCONV );
	}
	CString	sAux;
	sAux.Format( CONVM_OK );
	strcpy( szLastError, (char*) (LPCTSTR) sAux );
	return( CONV_OK );
}

/***
	PRIVATE
***/
BOOL C_ConvBase::GetBaseDir( char *szBaseDir )
{
	// ler o LBS.INI para saber qual e' o diretorio base
	GetPrivateProfileString( LBSINILBSSECTION, DIR_BASE_KEY, 
							 LBSINIDEFMSG, szBaseDir, MAXPATH, 
							 LBSINIFILE );
	if( stricmp( szBaseDir, LBSINIDEFMSG ) == 0 ){
		// nome nao encontrado
		return( FALSE );
	}
	return( TRUE );
}

/***
	PRIVATE
***/
BOOL C_ConvBase::GetControlFileName( char *szFileName )
{
	// ler o LBS.INI para saber o nome do arquivo de controle
	GetPrivateProfileString( LBSINILBSSECTION, LBSINIBASESFILENAME,
							 LBSINIDEFMSG, szFileName, MAXPATH, 
							 LBSINIFILE );

	if( stricmp( szFileName, LBSINIDEFMSG ) == 0 ){
		// nome nao encontrado
		return( FALSE );
	}
	return( TRUE );
}

/***
	PRIVATE
***/
int C_ConvBase::GetControlFileVersion( char *szFileName )
{
	C_File cfBasesFile( szFileName, "rb", SH_DENYRW );
	if( !cfBasesFile.IsOpen() ){
		return( LBSE_NOTOPEN );
	}
	cfBasesFile.Seek( 0, SEEK_SET );

	BYTE	bMagicNum = 0;

	cfBasesFile.Read( &bMagicNum, sizeof( bMagicNum ) );

	return( (int) bMagicNum );
}


/***
	PRIVATE
***/
int C_ConvBase::ConvertControlFile( CString &sFileName, C_FeedBackDlg &cProgDlg )
{
	char			szBaseDir[ MAXPATH ];
	CString			sTmpFileName;
	TBasesFile		tbfAux;
	TBasesFileV3	tbfV3;
	CString			sMsg;

	if( !GetBaseDir( szBaseDir ) ){
		return( !OK );
	}

	// resetar o progress control.
	// vamos dividi-lo em PROGRESS_SIZE partes (isso significa inserir
	// PROGRESS_SIZE pontos de feedback durante o processo).
	cProgDlg.m_Progress.SetRange( 0, PROGRESS_SIZE );
	cProgDlg.m_Progress.SetStep( 1 );
	cProgDlg.m_Progress.SetPos( 0 );

	sMsg.Format( IDS_MSG_CONVERTINGCONTROLFILE );
	cProgDlg.m_MsgStatic.SetWindowText( (LPCTSTR) sMsg );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (1/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	sTmpFileName.Format( "%s\\%s", (LPCTSTR) szBaseDir, (LPCTSTR) "lbscntrl.old" );

	// remover um possivel arquivo temporario
	remove( (LPCTSTR) sTmpFileName );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (2/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// renomear o arquivo de controle para um nome temporario
	if( !MoveFile( (LPCTSTR) sFileName, (LPCTSTR) sTmpFileName ) ){
		// deu pau.
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (3/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// abrir o arquivo temporario
	C_File			cfTmpFile( (LPCTSTR) sTmpFileName, NULL, SH_DENYRW, TRUE );
	if( !cfTmpFile.IsOpen() ){
		// deu pau.

		// renomear o arquivo temporario para o nome correto (original)
		MoveFile( (LPCTSTR) sTmpFileName, (LPCTSTR) sFileName );
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (4/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// criar o arquivo de controle com o formato novo.
	C_RecordFile	cfBasesFile( (char*) (LPCTSTR) sFileName, CRYPTO_MAGICNUMBER, 0, 
								 sizeof( TBasesFile ), "HEADKEY", 
								 "RECKEY", NULL, SH_DENYRW, TRUE );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (5/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	if( !cfBasesFile.IsOpen() ){
		// da~!
		// deletar o novo arquivo (pode ser que ele tenha sido criado,
		// mas nao aberto)
		remove( (LPCTSTR) sFileName );

		// renomear o arquivo temporario para o nome correto (original)
		MoveFile( (LPCTSTR) sTmpFileName, (LPCTSTR) sFileName );
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (6/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// copiar os dados do arquivo temporario para o novo arquivo.
	cfTmpFile.TurnOnCripto( CONTROLFILE_KEY );
	cfTmpFile.Seek( 0, SEEK_SET );

	cfBasesFile.R_Seek( 0 );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (7/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	while( cfTmpFile.Read( &tbfV3, sizeof( TBasesFileV3 ) ) == OK ){
		// copiar a estrutura de versao 3 para a nova
		tbfAux.szBaseName = tbfV3.szBaseName;
		tbfAux.szBaseLongName = tbfV3.szBaseName;
		tbfAux.bBaseType = tbfV3.bBaseType;
		tbfAux.szUserBaseName = tbfV3.szUserBaseName;
		tbfAux.bRecDeleted = tbfV3.bRecDeleted;

		// adicionar o registro no arquivo novo.
		cfBasesFile.R_Append( &tbfAux );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (8/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// fechar os dois arquivos.
	cfBasesFile.Close();

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (9/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	cfTmpFile.Close();

	// avancar o progress_control
	cProgDlg.m_Progress.SetPos( PROGRESS_SIZE );
	if( VerifyCancel() ){
		return( !OK );
	}

	// nao renomear/deletar o arquivo temporario, para possibilitar
	// que o usuario faca uma copia dele.
	return( OK );
}

/***
	PRIVATE
	Metodo GetBaseVersion
	Obtem a versao de uma base. A versao eh o numero magico.

	Parameters:
		- szBaseName	- nome da base (sem o path; basta o
						  nome, como LBWD0001).

	Return:
		- o numero da versao ou -1 em caso de erro.

	Comments:
		-

***/
int C_ConvBase::GetBaseVersion( const char *szBaseName )
{
	char	szBaseDir[ MAXPATH ];

	// pega o diretorio base
	if( !GetBaseDir( szBaseDir ) ){
		// nao encontrado
		CString	sAux;
		sAux.Format( CONVEM_CONTROLNOTFOUND );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( -1 );
	}

	// vamos abrir o arquivo .LB1 da base indicada e pegar seu 
	// primeiro byte. Se ele for igual a 4, e' porque a base possui
	// a versao nova (numero magico = 4, nao criptografado); se
	// o primeiro byte for diferente de 4, estamos tratando de uma
	// base com formato antigo (numero magico eh 3, mas esta' 
	// criptografado, o que resulta em um numero doidao - diferente
	// de 4, conforme observacao "binaria" feita em varias bases).

	CString	sBaseName = szBaseName;
	CString	sFullName;
	int		iIndex = sBaseName.Find( '\\' );

	sFullName.Format( "%s\\%s\\%s.LB1", szBaseDir, szBaseName, (szBaseName + iIndex + 1 ) );

	// abrir o arquivo
	C_File	cFile( sFullName );

	if( !cFile.IsOpen() ){
		// nao consegui abrir o arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILEOPENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( -1 );
	}

	if( cFile.Seek( 0, SEEK_SET ) == OK ){
		BYTE	bFirstByte;
		if( cFile.Read( &bFirstByte, sizeof( bFirstByte ) ) == OK ){
			switch( bFirstByte ){
			case BASE_CRYPTO4:
			case BASE_CRYPTO6:
			case BASE_VERSAO7:
			case BASE_VERSAO8:
			case BASE_VERSAO9:
			case BASE_VERSAO10:
			case BASE_VERSAO11:
				return( bFirstByte );

			default:
				return( BASE_CRYPTO3 );
			}
		}
	}
	// erro de leitura no arquivo
	CString	sAux;
	AfxFormatString1( sAux, CONVEM_FILEREADERR, szBaseName );
	strcpy( szLastError, (char*) (LPCTSTR) sAux );
	return( -1 );
}


/***
	PRIVATE
	Metodo ConvertBase3to4
	Realiza a conversao de uma base.

	Parameters:
		- sBaseName	- nome da base (sem o path; basta o
					  nome, como LBWD0001).

	Return:
		- o numero da versao ou -1 em caso de erro.

	Comments:
		-

***/
BOOL C_ConvBase::ConvertBase3to4( CString &sBaseName, C_FeedBackDlg &cProgDlg, C_RecordFile &cfBasesFile, CString &sFileName )
{
	char				szBaseDir[ MAXPATH ];
	char				szTemp[ MAXPATH ];
	CString				sNewBaseDir;
	CString				sFullLB1Name;
	CString				sFullLB2Name;
	CString				sFullLB3Name;
	CString				sFullLB4Name;
	CString				sFullLB6Name;
	CString				sFullNewLB1Name;
	CString				sFullNewLB3Name;
	CString				sFullNewLB4Name;
	CString				sFullNewLB6Name;
	CString				sTempLB1Name;
	CString				sTempLB2Name;
	CString				sTempLB3Name;
	CString				sTempLB4Name;
	CString				sTempLB6Name;
	CString				sMsg;
	TControlRec			tCR;			// registro de LB1
	TOldStructHeadRec	*ptOldSHR;		// cabecalho do velho LB3
	TStructHeadRec		*ptSHR;			// cabecalho do novo LB3
	TStructRec			tSR;			// registro de LB3
	TContentRecPsw		tCRPsw;			// registro de LB2
	TContentRec			tCRLB2;			// registro de LB2 para cada campo
	TRepetitionRec		tRRLB4;			// registro de LB4

	// resetar o progress control.
	// vamos dividi-lo em PROGRESS_SIZE partes (isso significa inserir
	// PROGRESS_SIZE pontos de feedback durante o processo).
	cProgDlg.m_Progress.SetRange( 0, PROGRESS_SIZE );
	cProgDlg.m_Progress.SetStep( 1 );
	cProgDlg.m_Progress.SetPos( 0 );

	AfxFormatString1( sMsg, IDS_MSG_CONVERTINGBASE, (char*) (LPCTSTR) sBaseName );
	cProgDlg.m_MsgStatic.SetWindowText( (LPCTSTR) sMsg );

	// pega o diretorio base
	if( !GetBaseDir( szBaseDir ) ){
		// nao encontrado
		CString	sAux;
		sAux.Format( CONVEM_CONTROLNOTFOUND );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	int		iIndex = sBaseName.Find( '\\' );
	sFullLB1Name.Format( "%s\\%s\\%s.LB1", szBaseDir, (LPCSTR) sBaseName, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullLB2Name.Format( "%s\\%s\\%s.LB2", szBaseDir, (LPCSTR) sBaseName, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullLB3Name.Format( "%s\\%s\\%s.LB3", szBaseDir, (LPCSTR) sBaseName, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullLB4Name.Format( "%s\\%s\\%s.LB4", szBaseDir, (LPCSTR) sBaseName, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullLB6Name.Format( "%s\\%s\\%s.LB6", szBaseDir, (LPCSTR) sBaseName, (((LPCSTR) sBaseName) + iIndex + 1) );

	// abrir LB1
	C_OldLB1	cOldLB1( (char*) (LPCSTR) sFullLB1Name, NULL );

	if( !cOldLB1.IsOpen() ){
		// deu pau na abertura do arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILEOPENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// verifica se a base esta' criptografada. se estiver,
	// eh necessario informar qual a chave de criptografia
	if( cOldLB1.tcrHead.tcrHead.bIsEncrypt ){
		cOldLB1.R_SetRecKey( LBDEFKEY );
	}

	// obtem um diretorio temporario para criar a nova base.
	if( GetTempPath( MAXPATH, szTemp ) == 0 ){
		// deu pau
		CString	sAux;
		sAux.Format( CONVEM_NOTTEMPPATH );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// tenta criar um diretorio com o nome da base dentro
	// do diretorio temporario
	sNewBaseDir.Format( "%s%s", szTemp, (LPCSTR) sBaseName );
	if( !MakeDir( (char*) (LPCSTR) sNewBaseDir ) ){
		// deu pau
		CString	sAux;
		sAux.Format( CONVEM_NOTNEWPATH );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (1/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( FALSE );
	}

	// criar os arquivos da nova base
	sFullNewLB1Name.Format( "%s\\%s.LB1", (LPCSTR) sNewBaseDir, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullNewLB3Name.Format( "%s\\%s.LB3", (LPCSTR) sNewBaseDir, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullNewLB4Name.Format( "%s\\%s.LB4", (LPCSTR) sNewBaseDir, (((LPCSTR) sBaseName) + iIndex + 1) );
	sFullNewLB6Name.Format( "%s\\%s.LB6", (LPCSTR) sNewBaseDir, (((LPCSTR) sBaseName) + iIndex + 1) );

	/****************************************************************/
	// converter LB1

	C_LB1	cNewLB1( (char*) (LPCSTR) sFullNewLB1Name, cOldLB1.tcrHead.tcrHead.bIsEncrypt ? LBDEFKEY : NULL );

	if( !cNewLB1.IsOpen() ){
		// erro
		CString	sAux;
		AfxFormatString1( sAux, CONVEM_NOTCREATED, (char*) (LPCTSTR) sBaseName );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// atualizar o numero magico do novo LB1
	cNewLB1.bMagicNumber = CRYPTO_MAGICNUMBER;
	cNewLB1.Seek( 0, SEEK_SET );
	cNewLB1.Write( &cNewLB1.bMagicNumber, sizeof( cNewLB1.bMagicNumber ) );

	// ler o cabecalho do LB1 velho
	cOldLB1.R_ReadHead();

	// copiar o old head para o novo, sem copiar o magic number
	memcpy( (void*) &cNewLB1.tcrHead, (void*) &(cOldLB1.tcrHead.tcrHead), sizeof( cNewLB1.tcrHead ) );

	// gravar o header do novo LB1
	cNewLB1.R_WriteHead();

	// calcula o numero de registros do arquivo LB1
	// que devem ser copiados. esse numero deve ser igual aa
	// quantidade de registros fisicos existentes.
	long	lNumLB1Rec = cOldLB1.R_FileSize();

	// agora converte os registros de LB1
	for( long l = 0; l < lNumLB1Rec; l++ ){
		// ler do old LB1
		cOldLB1.R_Seek( l );
		cOldLB1.R_Read( &tCR );

		// gravar no new LB1
		cNewLB1.R_Append( &tCR );
	}


	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (2/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( FALSE );
	}

	/****************************************************************/
	// converter LB6, que contem uma copia do header de LB1

	C_OldLB1	cOldLB6( (char*) (LPCSTR) sFullLB6Name, NULL );
	C_LB1		cNewLB6( (char*) (LPCSTR) sFullNewLB6Name, cOldLB1.tcrHead.tcrHead.bIsEncrypt ? LBDEFKEY : NULL );

	if( !cOldLB6.IsOpen() ){
		// deu pau na abertura do arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILEOPENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}
	if( !cNewLB6.IsOpen() ){
		// erro na criacao do arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILECREATERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// ler o cabecalho do LB6 velho
	cOldLB6.R_ReadHead();

	// copiar o old head para o novo, sem copiar o magic number
	memcpy( (void*) &cNewLB6.tcrHead, (void*) &(cOldLB6.tcrHead.tcrHead), sizeof( cNewLB6.tcrHead ) );

	// gravar o header do novo LB6
	cNewLB6.R_WriteHead();

	// fechar os arquivos LB6, que nao serao mais usados

	cOldLB6.Close();
	cNewLB6.Close();


	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (3/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( FALSE );
	}

	/****************************************************************/
	// agora converter LB3
	C_OldLB3	cOldLB3( (char*) (LPCSTR) sFullLB3Name, cNewLB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, 
					 NULL, SH_DENYNO, cNewLB1.tcrHead.iSlotNum + cNewLB1.tcrHead.iCountNum );
	C_LB3		cNewLB3( (char*) (LPCSTR) sFullNewLB3Name, cNewLB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, 
					 NULL, SH_DENYNO, cNewLB1.tcrHead.iSlotNum, cNewLB1.tcrHead.iCountNum );

	if( !cOldLB3.IsOpen() ){
		// deu pau na abertura do arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILEOPENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}
	if( !cNewLB3.IsOpen() ){
		// erro na criacao do arquivo
		CString	sAux;
		sAux.Format( CONVEM_FILECREATERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	ptOldSHR = TOldStructHeadRec::Alloc( cNewLB1.tcrHead.iSlotNum + cNewLB1.tcrHead.iCountNum );
	if( !ptOldSHR ){
		// erro de alocacao
		CString	sAux;
		sAux.Format( CONVEM_ALLOCERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}
	ptSHR = TStructHeadRec::Alloc( cNewLB1.tcrHead.iSlotNum + cNewLB1.tcrHead.iCountNum );
	if( !ptSHR ){
		// erro de alocacao
		TOldStructHeadRec::Free( ptOldSHR );
		CString	sAux;
		sAux.Format( CONVEM_ALLOCERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// ler o cabecalho do LB3 velho
	cOldLB3.R_ReadHead( ptOldSHR );

	// copiar o old head para o novo, sem copiar o magic number
	memcpy( (void*) ptSHR, (void*) &(ptOldSHR->tshRec), TStructHeadRec::SizeOf( cNewLB1.tcrHead.iSlotNum + cNewLB1.tcrHead.iCountNum ) );

	// gravar o header do novo LB3
	cNewLB3.R_WriteHead( ptSHR );

	// calcular o numero de registros do arquivo LB3
	// que devem ser copiados. esse numero deve ser igual aa
	// quantidade de registros fisicos existentes.
	long	lNumLB3Rec = cOldLB3.R_FileSize();

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (4/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		return( FALSE );
	}

	// criar um vetor contendo todos os identificadores de
	// campos validos. isso sera' util mais adiante, quando
	// formos converter LB2+LB4 em NewLB4
	UINT	*uiFieldArray = new UINT[ lNumLB3Rec ];
	if( !uiFieldArray ){
		// erro de alocacao
		TStructHeadRec::Free( ptSHR );
		TOldStructHeadRec::Free( ptOldSHR );
		CString	sAux;
		sAux.Format( CONVEM_ALLOCERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// em paralelo, devemos ter um array que contenha os 
	// apontadores de LB4 para cada campo do array acima.
	long	*lPtArray = new long[ lNumLB3Rec ];
	if( !lPtArray ){
		// erro de alocacao
		TStructHeadRec::Free( ptSHR );
		TOldStructHeadRec::Free( ptOldSHR );
		delete uiFieldArray;
		CString	sAux;
		sAux.Format( CONVEM_ALLOCERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}
	
	// numero de campos validos
	int	iNumFields = 0;

	// agora converte os registros de LB3
	for( l = 0; l < lNumLB3Rec; l++ ){
		// ler do old LB3
		cOldLB3.R_Seek( l );
		cOldLB3.R_Read( &tSR );

		// se o campo nao estiver deletado, inseri-lo no
		// array de campos
		if( !(tSR.uiFieldAttrib & DELETED_FIELD)){
			uiFieldArray[ iNumFields++ ] = tSR.uiFieldId;
		}

		// gravar no new LB3
		cNewLB3.R_Append( &tSR );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (5/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		return( FALSE );
	}

	/****************************************************************/
	// agora converter LB2+LB4 velhos em apenas LB4 novo

	// abrir LB2 e LB4 velhos e o LB4 novo
	C_OldLB2	cOldLB2( (char*) (LPCSTR) sFullLB2Name, cNewLB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, 
					 NULL, SH_DENYNO );
	C_OldLB4	cOldLB4( (char*) (LPCSTR) sFullLB4Name, cNewLB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, 
					 NULL, SH_DENYNO );
	C_LB4		cNewLB4( (char*) (LPCSTR) sFullNewLB4Name, cNewLB1.tcrHead.bIsEncrypt ? LBDEFKEY : NULL, 
					 NULL, SH_DENYNO );

	if( !cOldLB2.IsOpen() || !cOldLB4.IsOpen() ){
		// deu pau na abertura do arquivo
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		CString	sAux;
		sAux.Format( CONVEM_FILEOPENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}
	if( !cNewLB4.IsOpen() ){
		// erro na criacao do arquivo
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		CString	sAux;
		sAux.Format( CONVEM_FILECREATERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	// o cabecalho do novo LB4 deve nao deve ser copiado, pois
	// possui a lista de buracos livres.

	// variaveis para auxiliar no andamento do progress_control
	float	fProgStep = ((float) lNumLB1Rec) / ((float) (PROGRESS_SIZE-OTHER_ENTTRIES));
	if( fProgStep < 1 && fProgStep != 0 ){
		fProgStep = (1 / fProgStep);
	}
	float	fProgAux = (float) 0.0;
	BOOL	bErr = FALSE;

	// vamos ler o LB2, mas precisamos ler LB1 primeiro, pois e'
	// ele quem aponta para os registros em LB2.
	for( l = 0; l < lNumLB1Rec; l++ ){
		// ler do old LB1
		cOldLB1.R_Seek( l );
		cOldLB1.R_Read( &tCR );

		// verificar se eh um registro valido
		if( tCR.bRecStatus & REC_EXCLUDED ){
			// registro excluido. vamos para o proximo.
			// observe que o novo LB4 NAO deve possuir o mesmo
			// tamanho do velho LB4. Primeiro porque ele contera'
			// todos os registros de OldLB2 + OldLB4; segundo
			// porque ele contera' apenas os registros validos.
			// apenas LB1 e LB3 devem possuir o mesmo numero de
			// registros por causa dos indices (LB1) e por causa dos
			// slots (LB3).
			continue;
		}

		// posicionar-se sobre o registro em OldLB2
		if( cOldLB2.Seek( tCR.lContentPos, SEEK_SET ) != OK ){
			// deu pau.
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}

		// ler o registro psw em OldLB2
		if( cOldLB2.Read( &tCRPsw, sizeof( tCRPsw ) ) != OK ){
			// deu pau.
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}

		// fazer a leitura de OldLB4
		bErr = FALSE;
		int		iNumWFields = 0;				// numero de campos que serao gravados
		long	lOldLB2Pos = cOldLB2.CurPos();	// guarda a posicao de OldLB2
		for( int i = 0; i < tCRPsw.iNrFields; i++ ){
			if( cOldLB2.Read( &tCRLB2, sizeof( tCRLB2 ) ) != OK ){
				// erro.
				bErr = TRUE;
				break;
			}
			// verificar se o campo existe
			if( !FieldInArray( uiFieldArray, tCRLB2.uiFieldId, iNumFields ) ){
				// O campo lido nao existe mais.
				// Devemos pular para o proximo.
				continue;
			}

			// a variavel lSpace eh usada apenas na leitura
			long	lSpace = tCRLB2.lFirstRepetition;

			// as variaveis abaixo sao usadas apenas na gravacao
			long	lNextRep = 0;
			long	lOldRep = 0;

			tCRLB2.lFirstRepetition = 0L;

			// o while abaixo grava todas as repeticoes do campo corrente
			while( lSpace ){
				if( cOldLB4.Seek( lSpace, SEEK_SET ) != OK ){
					bErr = TRUE;
					break;
				}
				if( cOldLB4.Read( &tRRLB4, sizeof( tRRLB4 ) ) != OK ){
					bErr = TRUE;
					break;
				}
				char	*szBuffer = NULL;
				char	szAux[ 2 ];
				if( tRRLB4.lRepetitionSize > 0 ){
					szBuffer = new char [ tRRLB4.lRepetitionSize + 1 ];
					if( !szBuffer ){
						// erro.
						bErr = TRUE;
						break;
					}
				}
				if( cOldLB4.Read( szBuffer ? szBuffer : szAux, szBuffer ? tRRLB4.lRepetitionSize : 1 ) != OK ){
					bErr = TRUE;
					break;
				}
				lSpace = tRRLB4.lNextRepetition;

				// gravar no novo LB4
				tRRLB4.lNextRepetition = 0L;	// valor temporario. depois temos que atualiza-lo.
				lNextRep = cNewLB4.D_GetFreeSpace( szBuffer ? (tRRLB4.lRepetitionSize +	sizeof( tRRLB4 )) :
															  (1 + sizeof( tRRLB4 )) );
				if( lNextRep < 0 ){
					bErr = TRUE;
					break;
				}
				if( tCRLB2.lFirstRepetition == 0L ){
					// primeira repeticao
					tCRLB2.lFirstRepetition = lNextRep;

					// atualiza lOldRep
					lOldRep = lNextRep;
				} else {
					// atualiza a repeticao anterior, para que ela aponte para a nova.
					TRepetitionRec	tAux;

					cNewLB4.Seek( lOldRep, SEEK_SET );
					cNewLB4.Read( &tAux, sizeof( tAux ) );
					tAux.lNextRepetition = lNextRep;
					cNewLB4.Seek( lOldRep, SEEK_SET );
					cNewLB4.Write( &tAux, sizeof( tAux ) );
					
					// atualiza lOldRep
					lOldRep = lNextRep;
				}

				if( cNewLB4.Seek( lNextRep, SEEK_SET ) != OK ){
					bErr = TRUE;
					break;
				}
				// gravar o registro LB4
				if( cNewLB4.Write( &tRRLB4, sizeof( tRRLB4 ) ) != OK ){
					bErr = TRUE;
					break;
				}
				// gravar o buffer que contem os dados do usuario
				if( cNewLB4.Write( szBuffer ? szBuffer : szAux, szBuffer ? tRRLB4.lRepetitionSize : 1 ) != OK ){
					bErr = TRUE;
					break;
				}
				if( szBuffer ){
					delete szBuffer;
					szBuffer = NULL;
				}
			}
			if( bErr ){
				break;
			}
			lPtArray[ iNumWFields++ ] = tCRLB2.lFirstRepetition;
		}

		if( bErr ){
			// deu pau em alguma operacao
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}

		// gravamos as repeticoes de todos os campos (OldLB4 em NewLB4).
		// agora vamos gravar os campos (OldLB4 em NewLB4).

		// voltar OldLB2 para seu ponto inicial
		cOldLB2.Seek( lOldLB2Pos, SEEK_SET );

		// alocar espaco em NewLB4
		long	lLB2Space = cNewLB4.D_GetFreeSpace( sizeof( TContentRecPsw ) + iNumWFields * sizeof( TContentRec ) );

		if( lLB2Space < 0 ){
			// deu pau
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}
		if( cNewLB4.Seek( lLB2Space, SEEK_SET ) != OK ){
			// deu pau
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}

		// gravar o psw em NewLB4
		int iNrFields = tCRPsw.iNrFields;
		if( cNewLB4.Write( &tCRPsw, sizeof( tCRPsw ) ) != OK ){
			// deu pau
			CString	sAux;
			AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
			strcpy( szLastError, (char*) (LPCTSTR) sAux );
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}

		for( i = 0; i < iNrFields; i++ ){
			if( cOldLB2.Read( &tCRLB2, sizeof( tCRLB2 ) ) != OK ){
				// erro.
				bErr = TRUE;
				break;
			}
			// verificar se o campo existe
			if( !FieldInArray( uiFieldArray, tCRLB2.uiFieldId, iNumFields ) ){
				// O campo lido nao existe mais.
				// Devemos pular para o proximo.
				continue;
			}
			// modificar tCRLB2
			tCRLB2.lFirstRepetition = lPtArray[ i ];

			// gravar tCRLB2 em NewLB4
			if( cNewLB4.Write( &tCRLB2, sizeof( tCRLB2 ) ) != OK ){
				// deu pau
				CString	sAux;
				AfxFormatString1( sAux, CONVEM_FILEIOERR, sBaseName );
				strcpy( szLastError, (char*) (LPCTSTR) sAux );
				delete uiFieldArray;
				delete lPtArray;
				TOldStructHeadRec::Free( ptOldSHR );
				TStructHeadRec::Free( ptSHR );
				return( FALSE );
			}
		}

		// agora, fazer o registro corrente de NewLB1 apontar para lLB2Space
		tCR.lContentPos = lLB2Space;
		cNewLB1.R_Seek( l );
		cNewLB1.R_Write( &tCR );

		/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
		fProgAux += fProgStep;
		cProgDlg.m_Progress.SetPos( 5 + (int) ((PROGRESS_SIZE-OTHER_ENTTRIES) * ((float) l / (float) lNumLB1Rec)) );
		if( VerifyCancel() ){
			// cancelar operacao
			delete uiFieldArray;
			delete lPtArray;
			TOldStructHeadRec::Free( ptOldSHR );
			TStructHeadRec::Free( ptSHR );
			return( FALSE );
		}
	}

	// avancar o progress_control
	cProgDlg.m_Progress.SetPos( (PROGRESS_SIZE-OTHER_ENTTRIES) + 5 );
	if( VerifyCancel() ){
		// cancelar operacao
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		return( FALSE );
	}


	/****************************************************************/
	// Copiar os slots de base

	bErr = FALSE;
	cNewLB3.LB3_LockHead( ptSHR );
	for( int i = 0; i < cNewLB1.tcrHead.iSlotNum; i++ ){
		if( ptSHR->spSlot[ i ].lPointer == 0 ){
			// nao ha' dados gravados no slot i
			continue;
		}
		char *szBuffer = new char [ ptSHR->spSlot[ i ].pElem.lSize ];
		if( !szBuffer ){
			// deu pau
			bErr = TRUE;
			break;
		}
		long lPointer = cNewLB4.D_GetFreeSpace( ptSHR->spSlot[ i ].pElem.lSize );
		if( lPointer <= 0 ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		cOldLB4.Seek( ptSHR->spSlot[ i ].lPointer, SEEK_SET );
		if( cOldLB4.Read( szBuffer, ptSHR->spSlot[ i ].pElem.lSize ) != OK ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		cNewLB4.Seek( lPointer, SEEK_SET );
		if( cNewLB4.Write( szBuffer, ptSHR->spSlot[ i ].pElem.lSize ) != OK ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		delete szBuffer;

		// atualizar cNewLB3
		ptSHR->spSlot[ i ].lPointer = lPointer;
	}
	if( bErr ){
		CString	sAux;
		AfxFormatString1( sAux, CONVEM_FILEIOERR, (char*) (LPCTSTR) sBaseName );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		cNewLB3.R_ReleaseHead();
		return( FALSE );
	}
	cNewLB3.LB3_ReleaseHead( ptSHR );

	/****************************************************************/
	// Copiar os slots de campo

	for( l = 0; l < lNumLB3Rec; l++ ){
		// ler do old LB3
		cOldLB3.R_Seek( l );
		cOldLB3.R_Read( &tSR );

		// se o campo estiver deletado, nao interessa
		if( (tSR.uiFieldAttrib & DELETED_FIELD) ){
			continue;
		}

		if( tSR.spSlot.lPointer == 0 ){
			// nao ha' dados gravados no slot
			continue;
		}
		char *szBuffer = new char [ tSR.spSlot.pElem.lSize ];
		if( !szBuffer ){
			// deu pau
			bErr = TRUE;
			break;
		}
		long lPointer = cNewLB4.D_GetFreeSpace( tSR.spSlot.pElem.lSize );
		if( lPointer <= 0 ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		cOldLB4.Seek( tSR.spSlot.lPointer, SEEK_SET );
		if( cOldLB4.Read( szBuffer, tSR.spSlot.pElem.lSize ) != OK ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		cNewLB4.Seek( lPointer, SEEK_SET );
		if( cNewLB4.Write( szBuffer, tSR.spSlot.pElem.lSize ) != OK ){
			// deu pau
			delete szBuffer;
			bErr = TRUE;
			break;
		}
		delete szBuffer;

		// atualizar cNewLB3
		tSR.spSlot.lPointer = lPointer;
		cNewLB3.R_Seek( l );
		if( cNewLB3.R_Write( &tSR ) != OK ){
			// deu pau
			bErr = TRUE;
			break;
		}
	}
	if( bErr ){
		CString	sAux;
		AfxFormatString1( sAux, CONVEM_FILEIOERR, (char*) (LPCTSTR) sBaseName );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		delete uiFieldArray;
		delete lPtArray;
		TOldStructHeadRec::Free( ptOldSHR );
		TStructHeadRec::Free( ptSHR );
		cNewLB3.R_ReleaseHead();
		return( FALSE );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (6/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( FALSE );
	}

	/****************************************************************/
	// tudo convertido

	// deletar tudo que foi alocado
	delete uiFieldArray;
	delete lPtArray;
	TOldStructHeadRec::Free( ptOldSHR );
	TStructHeadRec::Free( ptSHR );


	/****************************************************************/
	// fechar os arquivos

	cOldLB1.Close();
	cOldLB2.Close();
	cOldLB3.Close();
	cOldLB4.Close();

	cNewLB1.Close();
	cNewLB3.Close();
	cNewLB4.Close();


	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (7/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( FALSE );
	}

	/****************************************************************/
	// renomear os arquivos originais para nomes temporarios.
	// A partir daqui nao eh aconselhavel checar o cancel, pois nao podemos
	// deixar as coisas do jeito que estao e o trabalho de desfaze-las 
	// eh muito grande.

	sTempLB1Name.Format( "%s\\%s\\Temp34.LB1", szBaseDir, (LPCSTR) sBaseName );
	sTempLB2Name.Format( "%s\\%s\\Temp34.LB2", szBaseDir, (LPCSTR) sBaseName );
	sTempLB3Name.Format( "%s\\%s\\Temp34.LB3", szBaseDir, (LPCSTR) sBaseName );
	sTempLB4Name.Format( "%s\\%s\\Temp34.LB4", szBaseDir, (LPCSTR) sBaseName );
	sTempLB6Name.Format( "%s\\%s\\Temp34.LB6", szBaseDir, (LPCSTR) sBaseName );

	if( MoveFile( (LPCSTR) sFullLB1Name, (LPCSTR) sTempLB1Name ) ){
		if( MoveFile( (LPCSTR) sFullLB2Name, (LPCSTR) sTempLB2Name ) ){
			if( MoveFile( (LPCSTR) sFullLB3Name, (LPCSTR) sTempLB3Name ) ){
				if( MoveFile( (LPCSTR) sFullLB4Name, (LPCSTR) sTempLB4Name ) ){
					if( !MoveFile( (LPCSTR) sFullLB6Name, (LPCSTR) sTempLB6Name ) ){
						// deu pau.
						// dezfazer os MoveFile anteriores
						if( !MoveFile( (LPCSTR) sTempLB4Name, (LPCSTR) sFullLB4Name ) ||
							!MoveFile( (LPCSTR) sTempLB3Name, (LPCSTR) sFullLB3Name ) ||
							!MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
							!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
							// erro fatal.
							CString	sAux;
							sAux.Format( CONVEM_FATALERR );
							strcpy( szLastError, (char*) (LPCTSTR) sAux );
						} else {
							// nao fatal
							CString	sAux;
							sAux.Format( CONVEM_FILERENERR );
							strcpy( szLastError, (char*) (LPCTSTR) sAux );
						}
						return( FALSE );
					}
				} else {
					// deu pau.
					// dezfazer os MoveFile anteriores
					if( !MoveFile( (LPCSTR) sTempLB3Name, (LPCSTR) sFullLB3Name ) ||
						!MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
						!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
						// erro fatal.
						CString	sAux;
						sAux.Format( CONVEM_FATALERR );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
					} else {
						// nao fatal
						CString	sAux;
						sAux.Format( CONVEM_FILERENERR );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
					}
					return( FALSE );
				}
			} else {
				// deu pau.
				// dezfazer os MoveFile anteriores
				if( !MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
					!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
					// erro fatal.
					CString	sAux;
					sAux.Format( CONVEM_FATALERR );
					strcpy( szLastError, (char*) (LPCTSTR) sAux );
				} else {
					// nao fatal
					CString	sAux;
					sAux.Format( CONVEM_FILERENERR );
					strcpy( szLastError, (char*) (LPCTSTR) sAux );
				}
				return( FALSE );
			}
		} else {
			// deu pau.
			// dezfazer os MoveFile anteriores
			if( !MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
				// erro fatal.
				CString	sAux;
				sAux.Format( CONVEM_FATALERR );
				strcpy( szLastError, (char*) (LPCTSTR) sAux );
			} else {
				// nao fatal
				CString	sAux;
				sAux.Format( CONVEM_FILERENERR );
				strcpy( szLastError, (char*) (LPCTSTR) sAux );
			}
			return( FALSE );
		}
	} else {
		// deu pau
		CString	sAux;
		sAux.Format( CONVEM_FILERENERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (8/PROGRESS_SIZE)

	/****************************************************************/
	// mover os arquivos novos para o diretorio da base

	if( MoveFile( (LPCSTR) sFullNewLB1Name, (LPCSTR) sFullLB1Name ) ){
		if( MoveFile( (LPCSTR) sFullNewLB3Name, (LPCSTR) sFullLB3Name ) ){
			if( MoveFile( (LPCSTR) sFullNewLB4Name, (LPCSTR) sFullLB4Name ) ){
				if( !MoveFile( (LPCSTR) sFullNewLB6Name, (LPCSTR) sFullLB6Name ) ){
					// deu pau.

					// deletar os arquivos novos.
					remove( (LPCSTR) sFullNewLB1Name );
					remove( (LPCSTR) sFullNewLB3Name );
					remove( (LPCSTR) sFullNewLB4Name );

					// dezfazer os MoveFile anteriores
					if( !MoveFile( (LPCSTR) sTempLB4Name, (LPCSTR) sFullLB4Name ) ||
						!MoveFile( (LPCSTR) sTempLB3Name, (LPCSTR) sFullLB3Name ) ||
						!MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
						!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
						// erro fatal.
						CString	sAux;
						sAux.Format( CONVEM_FATALERR );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
					} else {
						// nao fatal
						CString	sAux;
						sAux.Format( CONVEM_FILEMOVEERR );
						strcpy( szLastError, (char*) (LPCTSTR) sAux );
					}
					return( FALSE );
				}
			} else {
				// deu pau.

				// deletar os arquivos novos.
				remove( (LPCSTR) sFullNewLB1Name );
				remove( (LPCSTR) sFullNewLB3Name );

				// dezfazer os MoveFile anteriores
				if( !MoveFile( (LPCSTR) sTempLB3Name, (LPCSTR) sFullLB3Name ) ||
					!MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
					!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
					// erro fatal.
					CString	sAux;
					sAux.Format( CONVEM_FATALERR );
					strcpy( szLastError, (char*) (LPCTSTR) sAux );
				} else {
					// nao fatal
					CString	sAux;
					sAux.Format( CONVEM_FILEMOVEERR );
					strcpy( szLastError, (char*) (LPCTSTR) sAux );
				}
				return( FALSE );
			}
		} else {
			// deu pau.

			// deletar os arquivos novos.
			remove( (LPCSTR) sFullNewLB1Name );

			// dezfazer os MoveFile anteriores
			if( !MoveFile( (LPCSTR) sTempLB2Name, (LPCSTR) sFullLB2Name ) ||
				!MoveFile( (LPCSTR) sTempLB1Name, (LPCSTR) sFullLB1Name ) ){
				// erro fatal.
				CString	sAux;
				sAux.Format( CONVEM_FATALERR );
				strcpy( szLastError, (char*) (LPCTSTR) sAux );
			} else {
				// nao fatal
				CString	sAux;
				sAux.Format( CONVEM_FILEMOVEERR );
				strcpy( szLastError, (char*) (LPCTSTR) sAux );
			}
			return( FALSE );
		}
	} else {
		// deu pau
		CString	sAux;
		sAux.Format( CONVEM_FILEMOVEERR );
		strcpy( szLastError, (char*) (LPCTSTR) sAux );
		return( FALSE );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (9/PROGRESS_SIZE)

	/****************************************************************/
	// Conversão bem sucedida. Vamos deletar os arquivos originais,
	// que agora possuem nomes Temp.LB*
	// (apenas se o usuario nao marcou o botao "Manter originais")

	if( !bKeepOrig ){
		remove( (LPCSTR) sTempLB1Name );
		remove( (LPCSTR) sTempLB2Name );
		remove( (LPCSTR) sTempLB3Name );
		remove( (LPCSTR) sTempLB4Name );
		remove( (LPCSTR) sTempLB6Name );
	}

	/****************************************************************/
	// Remover o diretorio temporario
	rmdir( (LPCSTR) sNewBaseDir );

	/****************************************************************/
	// CONCLUIDO

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (10/PROGRESS_SIZE)

	// resetar o progress control
	cProgDlg.m_Progress.SetPos( 0 );

	// se for possivel, atualizar o arquivo de controle com
	// as descricoes das base obtidas de LBWNames.
	if( sBaseName == "LBWNAMES" ){
		bLBWNamesConv = TRUE;
	}
	if( sBaseName == "DEFUDB" ){
		bDefUdbConv = TRUE;
	}

//	if( bLBWNamesConv && bDefUdbConv ){
//		// atualiza as descricoes de todas as bases
//		PutLongNamesInControlFile( cProgDlg, cfBasesFile );
//	} else {
	{
		// atualiza a descricao da base corrente
		CString				sBaseLongName;
		LBSC_Session		*pSession = LBSC_Session::New();
		const LBSC_Ticket	*pTicket;
		LBSC_Base			*pBase;
		char				szAnonymous[ 128 ];

		if( pSession ){
			// procurar no LBS.INI o nome do usuario anonimo, para 
			// realizar login.
			GetPrivateProfileString( LBSINILBSSECTION, LBSANONYMOUSNAME, ANONYMOUS_USERNAME, szAnonymous, 128, LBSINIFILE );

			TNetInfo			tni( szAnonymous, "", NULL, NULL, NULL, NULL );

			pTicket = pSession->Login( tni );

			if( !pTicket ){
				LBSC_Session::Delete( pSession );
				return( TRUE );
			}

			// fechar o arquivo de controle para que o LBS consiga usa-lo.
			long	lControlPos = cfBasesFile.R_CurPos();
			cfBasesFile.Close();

			// abrir a base
			int	iRet = pSession->OpenBase( pTicket, (char*) (LPCTSTR) sBaseName, "", FALSE, TRUE, FALSE, &pBase );

			// reabrir o arquivo de controle
			cfBasesFile.Open( (char*) (LPCSTR) sFileName, CRYPTO_MAGICNUMBER, 0, 
								 sizeof( TBasesFile ), "HEADKEY", 
								 "RECKEY", NULL, SH_DENYRW, TRUE );
			if( cfBasesFile.IsOpen() ){
				cfBasesFile.R_Seek( lControlPos );
			}

			if( (iRet != LBS_OK && iRet != LBSW_OPENNOIS) || !pBase ){
				// deu merda.
				pSession->Logout();
				LBSC_Session::Delete( pSession );
				return( TRUE );
			}

			// pegar o long name no slot
			SlotBaseManager	sBaseInfo( SLOTDESCRIPTION, pBase );

			SLOTSTRUCT *pSlot = sBaseInfo.GetObjectInfo( BASEDESCRIPTION );

			if( pSlot ){
				sBaseLongName = (char*) pSlot->SlotInformation;
			} else {
				sBaseLongName = sBaseName;
			}

			// fechar a base
			pSession->CloseBase( pTicket, pBase );

			// fazer logout
			pSession->Logout();

			// detonar a sessao LBS
			LBSC_Session::Delete( pSession );

			PutBaseDescription( cfBasesFile, (char*) (LPCTSTR) sBaseName, (char*) (LPCTSTR) sBaseLongName );
		}
	}
	return( TRUE );
}


/***
	PRIVATE
***/
int C_ConvBase::PutLongNamesInControlFile( C_FeedBackDlg &cProgDlg, C_RecordFile &cfBasesFile )
{
	// abrir o arquivo de controle do LBS
	char				szControlFile[ MAXPATH ];
	char				szBaseDir[ MAXPATH ];
	CString				sFileName;
	CString				sMsg;
	
	// resetar o progress control.
	// vamos dividi-lo em PROGRESS_SIZE partes (isso significa inserir
	// PROGRESS_SIZE pontos de feedback durante o processo).
	cProgDlg.m_Progress.SetRange( 0, PROGRESS_SIZE );
	cProgDlg.m_Progress.SetStep( 1 );
	cProgDlg.m_Progress.SetPos( 0 );

	sMsg.Format( IDS_MSG_UPDATINGCONTROLFILE );
	cProgDlg.m_MsgStatic.SetWindowText( (LPCTSTR) sMsg );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (1/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	if( !GetBaseDir( szBaseDir ) || !GetControlFileName( szControlFile ) ){
		return( !OK );
	}
	sFileName.Format( "%s\\%s", (LPCTSTR) szBaseDir, (LPCTSTR) szControlFile );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (2/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// instanciar uma sessao LBS
	LBSC_Session		*pSession = LBSC_Session::New();
	const LBSC_Ticket	*pTicket;
	LBSC_Base			*pBase;
	char				szAnonymous[ 128 ];

	if( !pSession ){
		return( !OK );
	}

	// procurar no LBS.INI o nome do usuario anonimo, para 
	// realizar login.
	GetPrivateProfileString( LBSINILBSSECTION, LBSANONYMOUSNAME, ANONYMOUS_USERNAME, szAnonymous, 128, LBSINIFILE );

	TNetInfo			tni( szAnonymous, "", NULL, NULL, NULL, NULL );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (3/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	pTicket = pSession->Login( tni );

	if( !pTicket ){
		LBSC_Session::Delete( pSession );
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (4/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// abrir a base LBWNAMES
	int	iRet = pSession->OpenBase( pTicket, "LBWNAMES", "", FALSE, TRUE, FALSE, &pBase );

	if( (iRet != LBS_OK && iRet != LBSW_OPENNOIS) || !pBase ){
		// deu merda.
		pSession->Logout();
		LBSC_Session::Delete( pSession );
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (5/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

//	C_RecordFile	cfBasesFile( (char*) (LPCTSTR) sFileName, CRYPTO_MAGICNUMBER, 0, 
//								 sizeof( TBasesFile ), "HEADKEY", 
//								 "RECKEY", NULL, SH_DENYRW, TRUE );
	if( !cfBasesFile.IsOpen() ){
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (6/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// variaveis para auxiliar no andamento do progress_control
	long	lNumRec = pBase->GetNumRecords( pTicket );
	float	fProgStep = ((float) lNumRec) / ((float) (PROGRESS_SIZE-OTHER_ENTTRIES));
	if( fProgStep < 1 && fProgStep != 0 ){
		fProgStep = (1 / fProgStep);
	}
	float	fProgAux = (float) 0.0;
	long	l = 0;

	// navegar todos os registros
	pBase->FirstRecord( pTicket );

	do{
		l++;
		char	szNumber[ 15 ];
		char	szDescrip[ 300 ];

		if( pBase->GetFieldRepetition( (UINT) 1, 0, szNumber ) == LBS_OK ){
			if( stricmp( szNumber, "FREE" ) != 0 ){
				if( pBase->GetFieldRepetition( (UINT) 2, 0, szDescrip ) == LBS_OK ){
					char	szBaseName[ FULLNAMESIZE ];

					sprintf( szBaseName, "LBWD%s", szNumber );

					PutBaseDescription( cfBasesFile, szBaseName, szDescrip );
				}
			}
		}
		/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
		fProgAux += fProgStep;
		cProgDlg.m_Progress.SetPos( 6 + (int) ((PROGRESS_SIZE-OTHER_ENTTRIES) * ((float) l / (float) lNumRec)) );
		if( VerifyCancel() ){
			return( !OK );
		}
	} while( pBase->NextRecord( pTicket ) == LBS_OK );

	// avancar o progress_control
	cProgDlg.m_Progress.SetPos( (PROGRESS_SIZE-OTHER_ENTTRIES) + 6 );
	if( VerifyCancel() ){
		return( !OK );
	}

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (7/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// fechar a base LBWNAMES
	pSession->CloseBase( pTicket, pBase );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (8/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// fazer logout
	pSession->Logout();

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (9/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	// detonar a sessao LBS
	LBSC_Session::Delete( pSession );

	/************** PONTO DE ATUALIZACAO DO PROGRESS_CONTROL  ***/
	cProgDlg.m_Progress.StepIt();	// (10/PROGRESS_SIZE)
	if( VerifyCancel() ){
		// cancelar operacao
		return( !OK );
	}

	return( OK );
}


/***
	PRIVATE
***/
int C_ConvBase::PutBaseDescription( C_RecordFile &cfBasesFile, char *szBaseName, char *szDescrip )
{
	TBasesFile	tbfAux;

	// procurar szBaseName no arquivo de controle
	cfBasesFile.R_Seek( 0 );

	while( cfBasesFile.R_Read( &tbfAux ) == OK ){
		if( tbfAux.bRecDeleted == TRUE ){
			if( cfBasesFile.R_SeekNext() != OK ){
				break;
			}
			continue;
		}
		if( stricmp( (char*) tbfAux.szBaseName, szBaseName ) == 0 ){
			// achamos a base.
			tbfAux.szBaseLongName = szDescrip;
			cfBasesFile.R_Write( &tbfAux );

			return( OK );
		}
		if( cfBasesFile.R_SeekNext() != OK ){
			break;
		}
	}
	// nao encontramos o nome da base.
	return( !OK );
}


/***
	PRIVATE
***/
BOOL C_ConvBase::VerifyCancel()
{
	return( FALSE );
}


/***
	PUBLIC
***/
LPCTSTR C_ConvBase::LastErrorDesc()
{
	return( (LPCTSTR) szLastError );
}


/***
	PRIVATE
***/
BOOL C_ConvBase::MakeDir( char *szDirName )
{
	if( chdir( szDirName ) == 0 ){
		// ja' existe. vamos ver se esta' vazio.
		CString			sAux;
		WIN32_FIND_DATA	wAux;

		sAux.Format( "%s\\*.*", szDirName );
		HANDLE	hDir = FindFirstFile( (LPCSTR) sAux, &wAux );
		if( hDir ){
			// achamos um arquivo. vamos ver se eh diretorio ou
			// arquivo simples. podemos prosseguir enquanto nao
			// encontrarmos arquivos simples. isto e', se todos
			// os arquivos encontrados abaixo de szDirName forem
			// diretorios, esta' tudo bem.
			BOOL	bNext = TRUE;
			while( wAux.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ){
				bNext = FindNextFile( hDir, &wAux );
				if( !bNext ){
					// nao ha' mais arquivos.
					break;
				}
			}
			FindClose( hDir );
			if( bNext ){
				// achamos um arquivo que nao eh diretorio.
				return( FALSE );
			}
		}
		// ok. o diretorio existe, mas esta' limpo.
		return( TRUE );
	}

	// resetar o NextTok
	NextTok( szDirName, NULL );

	char	*szName = NextTok( szDirName, "\\" );
	while( szName ){
		mkdir( szName );
		szName = NextTok( NULL, "\\" );
	}
	return( TRUE );
}

/***
	PRIVATE
***/
char * C_ConvBase::NextTok( char *szStr, char *szSeparator )
{
	static	char	szConst[ 1024 ];	// guarda a string original
	static	char	szRet[ 1024 ];		// serve para retorno
	static	char	*szBuffer = szStr;	// serve para procurar o szSeparator
	static	int		iPos = 0;

	if( !szSeparator ){
		// resetar
		szBuffer = szStr;
		iPos = 0;
		return( NULL );
	}

	if( szStr ){
		strcpy( szConst, szStr );
		szBuffer = szStr;
	}
	if( szConst[ iPos ] == '\0' ){
		return( NULL );
	}
	do{
		strcpy( szRet, szConst );
		for( ; *szBuffer != *szSeparator && *szBuffer; szBuffer++, iPos++ );
		szRet[ iPos++ ] = '\0';
		szBuffer++;
	} while( *szRet == '\0' || strcmp( szRet, "\\" ) == 0 || szRet[ strlen( szRet ) -1 ] == ':' );
	return( szRet );
}

/***
	PRIVATE
***/
BOOL C_ConvBase::FieldInArray( UINT *pArray, UINT uiFieldId, int iArraySize )
{
	for( int j = 0; j < iArraySize; j++ ){
		if( pArray[ j ] == uiFieldId ){
			return( TRUE );
		}
	}
	return( FALSE );
}


