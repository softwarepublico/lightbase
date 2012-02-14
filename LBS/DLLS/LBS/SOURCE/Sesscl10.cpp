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
// Module: SESSCL10.CPP
// Description:
//
//	Methods file for session handling.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 09/12/96
//


#ifndef __BORLANDC__
#pragma warning(disable:4270)
#endif
#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
extern "C" {
#include	<personcl.h>
}

extern	time_t			_tLicFileCreateTime;

#define	K100			(100 * 1024)	// representa 100 Kbytes
#define	MAXLICTIMEBOMB	(16)			// numero maximo de licencas quando
										// o numero de serie eh time-bomb

// variavel que determina se alguma licenca foi invalidada. 
// quando isso acontece, todas as aplicacoes devem sair do ar
// e retornar, para que o LBS revalide a licenca.
BOOL	_bInvalidLicence = FALSE;


										
EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PRIVATE
	Metodo BufferToFile
	Copia uma parte de um arquivo para outro

	Parameters:
		- pcfSourceFile	-> arquivo de onde os dados serao extraidos
		- pcfDestFile	-> arquivo destino
		- lSize		-> numero de bytes que serao copiados

	Return:
		- LBS_OK ou erro

	Comments:
		-

***/
int
LBSC_Session::BufferToFile( C_File *pcfSourceFile, C_File *pcfDestFile, long lSize )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::BufferToFile") );
	if( !pcfDestFile || !pcfSourceFile || !pcfDestFile->IsOpen() || !pcfSourceFile->IsOpen() ){
		return( LBSE_ERROR );
	}

	char	szBuffer[ K100 ];

	// copiar de forma blocada
	while( (lSize-K100) > 0 ){
		if( pcfSourceFile->Read( szBuffer, K100 ) != OK ){
			// deu pau
			return( LBSE_ERROR );
		}
		if( pcfDestFile->Write( szBuffer, K100 ) != OK ){
			// deu pau
			return( LBSE_ERROR );
		}
		lSize -= K100;
	}
	// copia caracter a caracter
	while( lSize ){
		if( pcfSourceFile->Read( szBuffer, 1 ) != OK ){
			// deu pau
			return( LBSE_ERROR );
		}
		if( pcfDestFile->Write( szBuffer, 1 ) != OK ){
			// deu pau
			return( LBSE_ERROR );
		}
		--lSize;
	}
	return( LBS_OK );
}


/***
	PRIVATE
	GetBaseLongName
	Procura um nome longo de base no arquivo de controle, a
	partir de um nome curto.

	Parameters:
		- cfBasesFile	-> arquivo de controle (ja' aberto)
		- szAliasName	-> nome curto da base
		- szLongName	-> buffer onde o long name sera' retornado.

	Return:
		- LBS_OK ou erro.

	Comments:
		- 

***/
int
LBSC_Session::GetBaseLongName( C_RecordFile &cfBasesFile, char *szAliasName, char *szLongName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetBaseLongName") );
	TBasesFile	tbfAux;

	long	lCurPos = cfBasesFile.R_CurPos();

	cfBasesFile.R_Seek( 0 );
	while( cfBasesFile.R_Read( &tbfAux ) == OK ){
		if( stricmp( (char*) tbfAux.szBaseName, szAliasName ) == 0 ){
			// achamos a base
			strcpy( szLongName, (char*) tbfAux.szBaseLongName );
			cfBasesFile.R_Seek( lCurPos );
			return( LBS_OK );
		}
		if( cfBasesFile.R_SeekNext() != OK ){
			break;
		}
	}
	// deu merda
	cfBasesFile.R_Seek( lCurPos );
	strcpy( szLongName, "" );
	return( LBSE_ERROR );
}
