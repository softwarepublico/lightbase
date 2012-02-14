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
// Module: LICCTRL.H
// Description:
//
//	Methods file for LBSC_LicControl
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 21/10/96
//


#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif
#ifndef	_LOGLIST_H_
#include	<loglist.h>
#endif
#ifndef	_LICCTRL_H_
#include	<licctrl.h>
#endif
// para personalizacao
extern "C" {
#include	<personcl.h>
}

extern	LBSC_SessionList	*_clSessList;	// lista das sessoes abertas (logins feitos)
extern	LBSC_LogList		*_clLoginList;	// lista contendo estruturas TNetInfo de todos
											// os logins efetuados. usada para controle
											// de licencas de clientes.

static	time_t		_tLicFileCreateTimeAux = 0;	// apenas para protecao, caso o parametro passado no construtor seja NULL.

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
***/
LBSC_LicControl::LBSC_LicControl( time_t *ptLicFileCreateTimePar ) : cLicFile( LICFILE_MAGICNUMBER )
{
	ptLicFileCreateTime = ptLicFileCreateTimePar ? ptLicFileCreateTimePar : &_tLicFileCreateTimeAux;
	iMaxLogin = ::GetUsers();	// numero maximo de logins que podemos fazer
	bCanceled = FALSE;
	bSomeMonoLog = FALSE;
	lLicFilePos = -1L;
	bIncSrvLic = FALSE;
	ptni = NULL;
	bDone = FALSE;
}


/***
***/
LBSC_LicControl::~LBSC_LicControl()
{
	if( bDone ){
		if( !bCanceled ){
			if( bControlType == LIC_INC ){
				if( ::GetTypeInt() == PE_REDE ){
					FinishIncNetLicence();
				} else {
					FinishIncCSLicence();
				}
			} else {
				if( ::GetTypeInt() == PE_REDE ){
					FinishDecNetLicence();
				} else {
					FinishDecCSLicence();
				}
			}
		} else {
			if( bControlType == LIC_INC ){
				if( ::GetTypeInt() != PE_REDE ){
					if( _clLoginList->Current() && _clLoginList->Current()->clClientList.Current() ){
						if( --(_clLoginList->Current()->clClientList.Current()->iCount) <= 0 ){
							// tirar o elemento da lista.
							_clLoginList->Current()->clClientList.Del();
							if( _clLoginList->Current()->clClientList.NumElem() <= 0 ){
								// sair da lista
								_clLoginList->Current()->pOwnerSession = NULL;
								_clLoginList->Del();
							}
						}
					}
				}
			}
		}
	}
}

/***
***/
void
LBSC_LicControl::SetMono( BOOL bSomeMonoLogPar )
{
	bSomeMonoLog = bSomeMonoLogPar;
}


/***
***/
int
LBSC_LicControl::IncLicense( int *piNumLicPar, TNetInfo *ptniPar, LBSC_Session *pSession )
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::IncLicense") );

	if( !piNumLicPar || !ptniPar ){
		return( LBSE_BADARG );
	}
	bDone = TRUE;
	piNumLic = piNumLicPar;
	bControlType = LIC_INC;
	ptni = ptniPar;

	// alocar o pLoginInfo de pSession
	pSession->pLoginInfo = new TLoginInfo( (*ptni), pSession );
	if( !pSession->pLoginInfo ){
		// nao conseguimos alocar. entao nao podemos prosseguir.
		return( LBSE_NOMEMORY );
	}

	if( ::GetTypeInt() == PE_REDE ){
		return( IncNetLicence() );				// incrementa licenca de copia rede
	}
	return( IncCSLicence( pSession ) );			// incrementa licenca de copia cliente/servidor
}

/***
***/
int
LBSC_LicControl::DecLicense( int *piNumLicPar, BOOL bIsMono, LBSC_Session *pSession )
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::DecLicense") );

	int	iRet;

	if( !piNumLicPar || !pSession ){
		return( LBSE_BADARG );
	}
	bDone = TRUE;
	piNumLic = piNumLicPar;
	bControlType = LIC_DEC;
	if( ::GetTypeInt() == PE_REDE ){
		iRet = DecNetLicence( bIsMono, pSession );		// decrementa licenca de copia rede
	} else {
		iRet = DecCSLicence( pSession );				// decrementa licenca de copia cliente/servidor
	}

	// deletar o pLoginInfo de pSession
	if( iRet == LBS_OK ){
		if( pSession->pLoginInfo ){
			delete pSession->pLoginInfo;
			pSession->pLoginInfo = NULL;
		}
	}
	return( iRet );
}

/***
***/
int
LBSC_LicControl::IncNetLicence()
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::IncNetLicence") );

	// estamos trabalhando em uma copia rede.
	// vamos abrir o arquivo de licencas.
	char	szDirBase[ FULLNAMESIZE ];
	char	szAux[ FILENAMESIZE ];
	char	szLicFile[ FULLNAMESIZE ];

	bIncSrvLic = FALSE;
	bDone = TRUE;

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		return( LBSE_LBSINIERROR );
	}

	// testar o numero magico do arquivo de licencas
	sprintf( szLicFile, "%s\\%s", szDirBase, LICFILENAME );
	{
		C_File	cfAux( szLicFile, "r", SH_DENYNO );

		if( cfAux.IsOpen() ){
			// ler o primeiro byte, que eh o numero magico.
			BYTE	bMag;

			if( cfAux.Seek( 0, SEEK_SET ) == OK ){
				if( cfAux.Read( &bMag, sizeof( bMag ) ) == OK ){
					if( bMag != LICFILE_MAGICNUMBER ){
						// numero magico invalido.
						return( LBSE_BADLICFILE );
					}
				}
			}
		}
	}

	// tentar NUMTRYLIC vezes abrir o arquivo
	for( int i = 0; i < NUMTRYLIC; i++){
		if( cLicFile.Open( szLicFile, sizeof( TLicInfoFixHead ), sizeof( TLicInfoFix ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cLicFile.IsOpen() ){
		// nao consegui abrir o arquivo de licencas.
		return( LBSE_BUSY );
	}
	long	lFS = cLicFile.R_FileSize();
	if( lFS <= 0 ){
		// acabamos de criar o arquivo. mas sera' que ele nao foi detonado
		// indevidamente pelo usuario? se a variavel ptLicFileCreateTime, que
		// guarda a data de criacao do arquivo for diferente de 0, eh porque
		// ja inicializamos uma vez, o que significa que o arquivo ja existiu
		// em algum momento e foi detonado indevidamente. nao nos resta outra
		// alternativa, a nao ser recusar este login.

		if( (*ptLicFileCreateTime) != 0 ){
			// alguem detonou o arquivo de licencas. vamos detonar
			// todo mundo. NINGUEM MAIS CONSEGUIRA' USAR O LIGHT!!!
			// HA! HA! HA! HA! HA! 
			TLicInfoFixHead	tHead( FALSE, FALSE, 0, 0 );
			cLicFile.R_WriteHead( &tHead );
			cLicFile.Close();
			return( LBSE_FATALLIC );
		}

		// guardar a data de criacao do arquivo de licencas
		(*ptLicFileCreateTime) = cLicFile.GetCreateTime();

		// o arquivo acabou de ser criado.
		TLicInfoFixHead	tHead( bSomeMonoLog, TRUE, (*ptLicFileCreateTime), 1 );

		// vamos reseta-lo
		cLicFile.R_WriteHead( &tHead );

		// gera um registro com o nosso numero de serie para que nenhum processo se
		// confunda, com filesize = 0. esse registro sera' usado no final deste processo,
		// se o login for confirmado. Se o login nao for confirmado, o registro ficara'
		// livre.
		TLicInfoFix	tInfo;
		tInfo.tLicSerial.Set( ::GetSerialNumber(), 0 );
		if( cLicFile.R_Append( &tInfo ) != OK ){
			// deu pau
			return( LBSE_BUSY );
		}
		long	lRecFree = 0;
		lLicFilePos = cLicFile.R_CurPos();
		int	iNumUsers = ::GetUsers();
		if( iNumUsers > 0 ){
			tInfo.tLicClient.Set( (char*) (*ptni).strClient, (char*) (*ptni).strUserName, 0 );
			if( cLicFile.R_Append( &tInfo ) != OK ){
				// deu pau
				return( LBSE_BUSY );
			}
			lRecFree = cLicFile.R_CurPos();
			memset( &tInfo, 0, sizeof( tInfo ) );
			for( int i = 0; i < (iNumUsers-1); i++ ){
				if( cLicFile.R_Append( &tInfo ) != OK ){
					// deu pau
					return( LBSE_BUSY );
				}
			}
		}
		cLicFile.R_Seek( lRecFree );
	} else {
		// ler a variavel que indica se ha' alguem logado
		// em modo monousuario.
		TLicInfoFixHead	tHead;
		if( cLicFile.R_ReadHead( &tHead ) != 0 ){
			// deu pau.
			return( LBSE_BUSY );
		}
		bSomeMonoLog = tHead.bSomeMonoLog;

		if( !tHead.bCanUse ){
			// alguem setou o "bit fatal".
			// ninguem podera' usar as bases enquanto
			// o sistema nao for resetado e o arquivo de
			// licencas deletado.
			return( LBSE_FATALLIC );
		}

		if( bSomeMonoLog ){
			// temos um usuario logado em modo MONO.
			// portanto, nao adianta prosseguir, pois
			// nao eh possivel realizar login quando ha'
			// alguem logado em modo MONO.
 			return( LBSE_MONOMODE );
		}

		// guardar a data de criacao do arquivo de licencas
		(*ptLicFileCreateTime) = tHead.tTime;

		// procurar um elemento no arquivo que contenha o
		// numero de serie deste LBS que estamos trabalhando.
		// recalcular o numero de licencas do servidor
		(*piNumLic) = 0;

		cLicFile.R_Seek( 0 );
		for( int i = 0; i < tHead.lNumRec; i++ ){
			TLicInfoFix	tInfo;
			if( cLicFile.R_Read( &tInfo ) != OK ){
				// deu pau
				return( LBSE_BUSY );
			}
			int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
			if( stricmp( (char*) tInfo.tLicSerial.strSerialSvc, ::GetSerialNumber() ) == 0 ){
				// achamos.
				(*piNumLic) = tInfo.tLicSerial.iNumUsedLic;
				lLicFilePos = cLicFile.R_CurPos();

				// procurar maquina/usuario
				long	lRecFree = 0;
				for( int j = 0; j < iNumUsers; j++ ){
					cLicFile.R_SeekNext();
					if( cLicFile.R_Read( &tInfo ) != OK ){
						// deu pau
						return( LBSE_BUSY );
					}
					// verificar nome da maquina
					if( stricmp( (char*) tInfo.tLicClient.strClient, (char*) (*ptni).strClient ) == 0 ){
						// verificar se a licenca esta' invalida
						if( tInfo.tLicClient.iCount < 0 ){
							// licenca invalida. retornar erro
							return( LBSE_INVALIDLIC );
						}
					}
					if( tInfo.tLicClient.iCount == 0 ){
						if( lRecFree == 0 ){
							// buraco livre. vamos guardar a posicao.
							lRecFree = cLicFile.R_CurPos();
						}
					} else {
						if( stricmp( (char*) tInfo.tLicClient.strClient, (char*) (*ptni).strClient ) == 0 &&
							stricmp( (char*) tInfo.tLicClient.strUserName, (char*) (*ptni).strUserName ) == 0 ){
							// achamos maquina/usuario. para na posicao corrente do arquivo.
							lRecFree = 0;
							break;
						}
					}
				}
				if( lRecFree ){
					// nao encontramos maquina/usuario. vamos criar um novo registro.
					// mas antes vamos verificar se eh possivel incrementar o numero
					// de licencas sem estourar o limite do servidor.
					if( ((*piNumLic)+1) > iMaxLogin ){
						// nao podemos mais fazer login
						return( LBSE_MAXSERVERLOGIN );
					}
					tInfo.tLicClient.Set( (char*) (*ptni).strClient, (char*) (*ptni).strUserName, 0 );
					cLicFile.R_Seek( lRecFree );
					if( cLicFile.R_Write( &tInfo ) != OK ){
						// fudeu.
						return( LBSE_BUSY );
					}
				} else {
					if( j >= iNumUsers ){
						// nao achamos nenhum registro que possamos usar.
						// isso significa que o nosso numero de serie ja' esta' com
						// todas as licencas em uso e que nao podemos continuar o 
						// processo.
						lLicFilePos = -1;
						return( LBSE_MAXSERVERLOGIN );
					}
				}
				break;
			} else {
				// pular os registros que contem marquina/usuario
				int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
				for( int j = 0; j < iNumUsers; j++ ){
					cLicFile.R_SeekNext();
				}
				// proximo registro com numero de serie
				cLicFile.R_SeekNext();
			}
		}
		// se o numero de serie procurado nao for encontrado no
		// arquivo, assuminos que ainda nao ha' licencas usadas
		// para ele. no final deste metodo, adicionamos o novo
		// numero de serie e o num. de licencas (que sera' 1) no
		// arquivo.
	}
	// estamos com o arquivo de licencas aberto e ninguem podera'
	// abri-lo enquanto nao o fecharmos. Entao, vamos processar
	// tudo normalmente e, no final, gravar novas informacoes.
	bIncSrvLic = TRUE;
	return( LBS_OK );
}

/***
***/
int
LBSC_LicControl::IncCSLicence( LBSC_Session *pSession )
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::IncCSLicence") );

	bDone = TRUE;
	TClientInfo		*pNewInfo = NULL;

	// o numero de licencas do cliente ja' eh informado por ele
	// no parametro tniPar
	TLoginInfo	tLogInfo( (*ptni), pSession );

	// se o numero de licencas do servidor for 0 (zero), significa
	// que o servidor nao possui limite de licencas e, portanto, podemos
	// fazer quantos logins forem desejados e suportados pela 
	// memoria do sistema...
	if( iMaxLogin != 0 ){
		// procuraremos na lista de logins por nodos que contenham o mesmo numero de
		// serie do cliente, o mesmo nome do cliente, e o mesmo nome do usuario que
		// estah tentando fazer o login. se encontrarmos algum nodo com tudo isso, podemos
		// fazer o login sem contar mais uma licenca para o servidor.
		if( !(_clLoginList->Find( &tLogInfo, CMPBASICELEM )) ){
			// nao encontramos. vamos contabilizar login no
			// servidor
			if( ((*piNumLic)+1) > iMaxLogin ){
				// nao podemos mais fazer login
				tLogInfo.pOwnerSession = NULL;
				return( LBSE_MAXSERVERLOGIN );
			}
		}
	}

	bIncSrvLic = FALSE;

	// bom, ainda podemos fazer login. Mas sera' que o numero de logins do
	// cliente ja' estourou? Vamos checar...

	// se o numero de licencas do cliente for 0 (zero), significa que o cliente
	// possui numero ilimitado de licencas e, portanto, nao precisamos computar
	// nada. podemos liberar o login.
	if( (*ptni).iClientLicenses != 0 ){
		// procuraremos na lista de logins por nodos que contenham o mesmo numero de
		// serie do cliente, o mesmo nome do cliente, e o mesmo nome do usuario que
		// estah tentando fazer o login. se encontrarmos algum nodo com tudo isso, podemos
		// fazer o login sem contar mais uma licenca para o cliente.
		if( !(_clLoginList->Find( &tLogInfo, CMPBASICELEM )) ){
			// NAO achamos o que estavamos procurando.
			// vamos procurar pelo numero de serie.
			if( _clLoginList->Find( &tLogInfo, CMPSERIALNUM ) ){
				// achamos um numero de serie.
				// vamos verificar se ainda ha' licencas disponiveis:
				tLogInfo.pOwnerSession = NULL;
				int	iUsedLicenses = _clLoginList->Current()->clClientList.NumElem();
				if( (iUsedLicenses + 1) > _clLoginList->Current()->tniInfo.iClientLicenses ){
					// nao podemos fazer login
					return( LBSE_MAXCLIENTLOGIN );
				}
				// encontramos um nodo com o mesmo numero de serie
				// do cliente que esta' tentando fazer o login.
				// Entao, devemos inserir um novo TClientInfo na lista.
				pNewInfo = new TClientInfo( (char*) (*ptni).strUserName, (char*) (*ptni).strClient );
				if( !pNewInfo ){
					// nao conseguimos alocar. entao nao podemos prosseguir.
					return( LBSE_NOMEMORY );
				}
				// criar um novo nodo na lista de TClientInfo.
				if( _clLoginList->Current()->clClientList.Add( pNewInfo, TAIL ) != OK ){
					delete pNewInfo;
					return( LBSE_NOMEMORY );
				}
				bIncSrvLic = TRUE;
			} else {
				// NAO encontramos nenhum nodo com o mesmo numero de serie
				// do cliente que esta' tentando fazer o login.
				// Entao, devemos inserir um novo TLoginInfo na lista.
				tLogInfo.pOwnerSession = NULL;
				TLoginInfo	*pLogInfoAux = new TLoginInfo( (*ptni), pSession );

				// criar um novo nodo na lista de TLoginInfo.
				if( _clLoginList->Add( pLogInfoAux, TAIL ) != OK ){
					delete pLogInfoAux;
					delete pSession->pLoginInfo;
					pSession->pLoginInfo = NULL;
					return( LBSE_NOMEMORY );
				}

				pNewInfo = new TClientInfo( (char*) (*ptni).strUserName, (char*) (*ptni).strClient );
				if( !pNewInfo ){
					// nao conseguimos alocar. entao nao podemos prosseguir.
					_clLoginList->Current()->pOwnerSession = NULL;
					_clLoginList->Del();
					return( LBSE_NOMEMORY );
				}
				// criar um novo nodo na lista de TClientInfo.
				if( _clLoginList->Current()->clClientList.Add( pNewInfo, TAIL ) != OK ){
					delete pNewInfo;
					_clLoginList->Current()->pOwnerSession = NULL;
					_clLoginList->Del();
					return( LBSE_NOMEMORY );
				}
				bIncSrvLic = TRUE;
			}
			// setar o ponteiro da estrutura de informacoes de login para 
			// que o Logout saiba decrementar o numero de licencas corretamente.
		} else {
			// ok. encontramos o que procuravamos. NAO EH NECESSARIO 
			// INCREMENTAR O NUMERO DE LICENCAS.

			// mas, eh necessario procurar o par maquina/usuario e incrementar
			// o contador de logins.
			_clLoginList->Current()->clClientList.Current()->iCount++;
		}
	}
	tLogInfo.pOwnerSession = NULL;
	// se chegamos ateh aqui, temos pelo menos uma licenca de login.
	// podemos prosseguir com o processo.
	return( LBS_OK );
}


/***
***/
int
LBSC_LicControl::UndoProcess()
{
	bCanceled = TRUE;
	return( LBS_OK );
}


/***
***/
int
LBSC_LicControl::FinishIncCSLicence()
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::FinishIncCSLicence") );

	bDone = TRUE;
	if( bIncSrvLic ){
		// contar mais uma licenca do servidor usada.
		(*piNumLic)++;
	}
	return( LBS_OK );
}

/***
***/
int
LBSC_LicControl::FinishIncNetLicence()
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::FinishIncNetLicence") );

	bDone = TRUE;
	// atualizar a lista de licencas em disco, se estivermos
	// trabalhando em copia REDE
	if( ::GetTypeInt() == PE_REDE && cLicFile.IsOpen() && bIncSrvLic ){
		// gravar a variavel que indica se ha' alguem logado
		// em modo monousuario.
		TLicInfoFixHead	tHead( bSomeMonoLog, TRUE, (*ptLicFileCreateTime), 0 );

		if( lLicFilePos > -1 ){
			// atualizar um numero de serie que ja' foi encontrado no inicio deste metodo.
			TLicInfoFix	tInfo;
			if( cLicFile.R_Read( &tInfo ) != OK ){
				// deu pau
				return( LBSE_BUSY );
			}
			tInfo.tLicClient.iCount++;
			if( cLicFile.R_Write( &tInfo ) != OK ){
				// deu pau
				return( LBSE_BUSY );
			}
			if( tInfo.tLicClient.iCount == 1 ){
				// incrementar o numero de licencas.
				cLicFile.R_Seek( lLicFilePos );
				if( cLicFile.R_Read( &tInfo ) != OK ){
					// deu pau
					return( LBSE_BUSY );
				}
				tInfo.tLicSerial.iNumUsedLic++;
				if( cLicFile.R_Write( &tInfo ) != OK ){
					// deu pau
					return( LBSE_BUSY );
				}
			}
		} else {
			// temos que criar um registro com o nosso numero de serie.
			TLicInfoFix	tInfo;

			tInfo.tLicSerial.Set( ::GetSerialNumber(), 1 );
			if( cLicFile.R_Append( &tInfo ) != OK ){
				// deu pau
				return( LBSE_BUSY );
			}
			int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
			if( iNumUsers > 0 ){
				tInfo.tLicClient.Set( (char*) (*ptni).strClient, (char*) (*ptni).strUserName, 1 );
				if( cLicFile.R_Append( &tInfo ) != OK ){
					// deu pau
					return( LBSE_BUSY );
				}
				memset( &tInfo, 0, sizeof( tInfo ) );
				for( int i = 0; i < (iNumUsers-1); i++ ){
					if( cLicFile.R_Append( &tInfo ) != OK ){
						// deu pau
						return( LBSE_BUSY );
					}
				}
			}
		}
		tHead.lNumRec = NumLicRec();
		cLicFile.R_WriteHead( &tHead );
	}
	return( LBS_OK );
}	


/***
***/
int
LBSC_LicControl::DecNetLicence( BOOL bIsMono, LBSC_Session *pSession )
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::DecNetLicence") );

	bDone = TRUE;
	// estamos trabalhando em uma copia rede.
	// vamos abrir o arquivo de licencas.
	char	szDirBase[ FULLNAMESIZE ];
	char	szAux[ FILENAMESIZE ];
	char	szLicFile[ FULLNAMESIZE ];

	// pega o dir_base
	if( LBSC_Session::GetFNameOnProfile( szDirBase, szAux ) != LBS_OK ){
		return( LBSE_LBSINIERROR );
	}

	ptni = &(pSession->pLoginInfo->tniInfo);

	// tentar NUMTRYLIC vezes abrir o arquivo
	sprintf( szLicFile, "%s\\%s", szDirBase, LICFILENAME );
	for( int i = 0; i < NUMTRYLIC; i++){
		if( cLicFile.Open( szLicFile, sizeof( TLicInfoFixHead ), sizeof( TLicInfoFix ),
			"HEADKEY", "RECKEY", NULL, SH_DENYRW ) == OK ){
			break;
		}
		Sleep( 500 );	// 1/2 segundo
	}
	if( !cLicFile.IsOpen() ){
		// nao consegui abrir o arquivo de licencas
		return( LBSE_BUSY );
	}
	if( cLicFile.R_FileSize() > 0 ){
		// ler a variavel que indica se ha' alguem logado
		// em modo monousuario.
		TLicInfoFixHead	tHead;

		if( cLicFile.R_ReadHead( &tHead ) != OK ){
			// deu pau
			return( LBSE_BUSY );
		}
		if( tHead.tTime == (*ptLicFileCreateTime) ){
			bSomeMonoLog = tHead.bSomeMonoLog;

			// rever o valor da variavel de monousuario.
			if( bSomeMonoLog && bIsMono ){
				// quem esta' em mono eh esta sessao que estamos
				// fazendo logout.

				// desligar para regravar.
				bSomeMonoLog = FALSE;
			}

			// ler as licencas
			cLicFile.R_Seek( 0 );
			while( TRUE ){
				TLicInfoFix		tInfo;
				if( cLicFile.R_Read( &tInfo ) != OK ){
					// deu pau
					return( LBSE_BUSY );
				}
				int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
				if( stricmp( (char*) tInfo.tLicSerial.strSerialSvc, ::GetSerialNumber() ) == 0 ){
					// achamos.
					(*piNumLic) = tInfo.tLicSerial.iNumUsedLic;
					lLicFilePos = cLicFile.R_CurPos();

					// procurar maquina/usuario
					long	lRecFree = 0;
					for( int j = 0; j < iNumUsers; j++ ){
						cLicFile.R_SeekNext();
						if( cLicFile.R_Read( &tInfo ) != OK ){
							// deu pau
							return( LBSE_BUSY );
						}
						// verificar nome da maquina
						if( stricmp( (char*) tInfo.tLicClient.strClient, (char*) (*ptni).strClient ) == 0 ){
							// verificar se a licenca esta' invalida
							if( tInfo.tLicClient.iCount < 0 ){
								// licenca invalida. retornar erro
								return( LBSE_INVALIDLIC );
							}
						}
						if( tInfo.tLicClient.iCount > 0 ){
							if( stricmp( (char*) tInfo.tLicClient.strClient, (char*) (*ptni).strClient ) == 0 &&
								stricmp( (char*) tInfo.tLicClient.strUserName, (char*) (*ptni).strUserName ) == 0 ){
								// achamos maquina/usuario. para na posicao corrente do arquivo.
								break;
							}
						}
					}
					if( j >= iNumUsers ){
						return( LBS_OK );
					}
					// decrementar o contador
					--tInfo.tLicClient.iCount;
					// regrava o contador
					cLicFile.R_Write( &tInfo );
					if( tInfo.tLicClient.iCount <= 0 ){
						tInfo.tLicClient.iCount = 0;
						// decrementar numero de licencas do servidor
						if( (*piNumLic) > 0 ){
							--(*piNumLic);
						}

						// decrementar o numero de licencas usadas do numero de serie cliente
						cLicFile.R_Seek( lLicFilePos );
						cLicFile.R_Read( &tInfo );
						tInfo.tLicSerial.iNumUsedLic--;
						cLicFile.R_Write( &tInfo );
					}
					break;
				} else {
					// pular os registros que contem marquina/usuario
					int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
					for( int j = 0; j < iNumUsers; j++ ){
						cLicFile.R_SeekNext();
					}
				}
				if( cLicFile.R_SeekNext() != OK ){
					// acabou o arquivo.
					break;
				}
			}
		} else {
			// alguem detonou o arquivo de licencas. vamos detonar
			// todo mundo. NINGUEM MAIS CONSEGUIRA' USAR O LIGHT!!!
			// HA! HA! HA! HA! HA! 
			TLicInfoFixHead	tHead( FALSE, FALSE, 0, 0 );
			cLicFile.R_WriteHead( &tHead );
			cLicFile.Close();
		}
	} else {
		// alguem detonou o arquivo de licencas. vamos detonar
		// todo mundo. NINGUEM MAIS CONSEGUIRA' USAR O LIGHT!!!
		// HA! HA! HA! HA! HA! 
		TLicInfoFixHead	tHead( FALSE, FALSE, 0, 0 );
		cLicFile.R_WriteHead( &tHead );
		cLicFile.Close();
	} 
	// estamos com o arquivo de licencas aberto e ninguem podera'
	// abri-lo enquanto nao o fecharmos. Entao, vamos processar
	// tudo normalmente e, no final, gravar novas informacoes.
	return( LBS_OK );
}

/***
***/
int
LBSC_LicControl::DecCSLicence( LBSC_Session *pSession )
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::DecCSLicence") );

	if( !pSession->pLoginInfo ){
		return( LBSE_ERROR );
	}
	bDone = TRUE;
	TLoginInfo	tLogInfo( pSession->pLoginInfo->tniInfo, pSession );

	// controle de licencas do servidor e do cliente
	if( (_clLoginList->Find( &tLogInfo, CMPBASICELEM )) ){
		if( --(_clLoginList->Current()->clClientList.Current()->iCount) <= 0 ){	
			// decrementar licenca do servidor
			if( (*piNumLic) > 0 ){
				--(*piNumLic);
			}
			// tirar o elemento da lista.										
			_clLoginList->Current()->clClientList.Del();						
			if( _clLoginList->Current()->clClientList.NumElem() <= 0 ){			
				// sair da lista												
				_clLoginList->Current()->pOwnerSession = NULL;
				_clLoginList->Del();											
			}																	
		}
	}
	tLogInfo.pOwnerSession = NULL;
	return( LBS_OK );
}

/***
***/
int
LBSC_LicControl::FinishDecNetLicence()
{
	bDone = TRUE;
	return( LBS_OK );
}

/***
***/
int
LBSC_LicControl::FinishDecCSLicence()
{
	bDone = TRUE;
	return( LBS_OK );
}

/***
***/
long
LBSC_LicControl::NumLicRec()
{
	PRINTLOG( _clLBSLog, ("LBSC_LicControl::NumLicRec") );

	long	lNumRec = 0;

	bDone = TRUE;
	cLicFile.R_Seek( 0 );
	while( TRUE ){
		TLicInfoFix	tInfo;

		if( cLicFile.R_Read( &tInfo ) != OK ){
			break;
		}
		lNumRec++;

		// pular os registros que contem marquina/usuario
		int	iNumUsers = ::GetUsersFromSN( (char*) tInfo.tLicSerial.strSerialSvc );
		for( int j = 0; j < iNumUsers; j++ ){
			cLicFile.R_SeekNext();
		}
		if( cLicFile.R_SeekNext() != OK ){
			break;
		}
	}
	return( lNumRec );
}


