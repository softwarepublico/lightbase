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
// Module: SESSCL14.H
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
#ifndef	_CSTRTOK_H_
#include	<cstrtok.h>
#endif

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/**********************************************************************/
/********** METODOS PARA MANIPULACAO DE DADOS EM UMA UDB **************/
/**********************************************************************/

/***
	PUBLIC
	Metodo AddUser
	Adiciona novos usuarios em uma UDB

	Parameters:
		- pTicket     -> ticket de seguranca
		- szUDBName   -> nome da UDB
		- ptUDBRecord -> array de elementos do tipo TUDBRecord
				 indicando todos os registros que deverao
				 ser adicionados aa UDB. O array deve ser
				 alocado sempre com um elemento a mais do
				 que o numero de registros a ser adicionados.
				 A ultima estrutura do array ficara' zerada
				 e sera' util para este metodo detectar a
				 quantidade de registros que devem ser appendados.
				 O proprio construtor da estrutura TUDBRecord
				 ja' zera todos os elementos, o que significa
				 que nao e' necessario que a aplicacao faca isso.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- O array de estruturas TUDBRecord pode ser deletado pela
		  aplicacao apos o retorno deste metodo.
		- Para adicionar apenas um usuario, basta criar um array de
		  dois elementos, onde o primeiro indica o usuario e o outro
		  deve permanecer zerado.
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados. Portanto, adicione o maximo de usuarios possivel
		  de uma so' vez.
		- So quem pode adicionar novos usuarios sao o dono da UDB ou
		  super-usuarios.

***/
int
LBSC_Session::AddUser( const LBSC_Ticket *pTicket, char *szUDBName, TUDBRecord *ptUDBRecord )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::AddUser") );
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !ptUDBRecord || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base *bUserBase = new LBSC_Base( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase->BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// verificar se o cara que esta' logado eh o dono da UDB
	if( bUserBase->LB1.tcrHead.szOwnerName != plbscuUser->GetUserName() ){
		// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
		if( GetUserType( bUserBase, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara tambem nao eh super usuario
			ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}

	for ( int j=0; !ptUDBRecord[ j ].IsZero(); j++ ) {
		if ( InvalidPasswordFormat( (char*) ptUDBRecord[ j ].szUserPassword ) ) {
			ERETURN( LBSE_INVALIDPASSWORDFORMAT );
		}
	}

	int i = 0;
	int iRet = LBS_OK;
	while( !ptUDBRecord[ i ].IsZero() ){
		// procurar na UDB para ver se o cara a ser adicionado
		// ja' existe.
		if( bUserBase->Locate( pTicket, 1, ENTIRETREE, strupr( (char*) ptUDBRecord[ i ].szUserName ), EQUAL_KEY ) != LBS_OK ){
			bUserBase->ClearRecord();
			LBSC_Field	*pf = (*bUserBase)[ USERBASEUSERNAME ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = strupr( (char*) ptUDBRecord[ i ].szUserName );
			pf = (*bUserBase)[ USERBASEUSERPASSWORD ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = strupr( (char*) ptUDBRecord[ i ].szUserPassword );
			pf = (*bUserBase)[ USERBASEUSERTYPE ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = ptUDBRecord[ i ].lUserType;
			pf = (*bUserBase)[ USERBASEUSERDESCRIPTION ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = (char*) ptUDBRecord[ i ].szUserDescription;
			pf = (*bUserBase)[ USERBASEUSERADDRESS ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = (char*) ptUDBRecord[ i ].szUserAddress;
			pf = (*bUserBase)[ USERBASEUSERPHONE ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = (char*) ptUDBRecord[ i ].szUserPhone;
			pf = (*bUserBase)[ USERBASEGROUPLIST ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = strupr( (char*) ptUDBRecord[ i ].szUserGroup );
			pf = (*bUserBase)[ USERBASEUSERCREATEDATE ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = C_Date();
			pf = (*bUserBase)[ USERBASEUSERUPDATEDATE ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = C_Date();
			pf = (*bUserBase)[ USERBASEPASSWORDCHANGEDATE ];
			if( !pf ){
				delete bUserBase;
				ERETURN( LBSE_BADUSERBASE );
			}
			(*pf) = C_Date();
			iRet = bUserBase->AppendRecord( pTicket );

			if ( iRet == LBS_OK ) {
				AddUserToCache( ptUDBRecord[ i ].szUserName, ptUDBRecord[ i ].szUserPassword, szUDBName, ptUDBRecord[ i ].lUserType );
			} else if ( ptUDBRecord[ 1 ].IsZero() ) {
				// so vou retornar erro se a aplicacao tentou adicionar
				// apenas um usuario. No caso de mais de um, o que deu erro
				// dancou, os outros continuam.
				delete bUserBase;
				ERETURN( iRet );
			}

		} else {
			// so vou retornar erro se a aplicacao tentou adicionar
			// apenas um usuario. No caso de mais de um, o que deu erro
			// dancou, os outros continuam.
			if( ptUDBRecord[ 1 ].IsZero() ){
				delete bUserBase;
				ERETURN( LBSE_USERALREADYEXIST );
			}
		}
		i++;
	}
	delete bUserBase;
	ERETURN( LBS_OK );
}


/***
	PUBLIC
	Metodo DelUser
	Deleta usuarios de uma UDB

	Parameters:
		- pTicket     -> ticket de seguranca
		- szUDBName   -> nome da UDB
		- szUsers     -> string contendo os nomes dos usuarios que
				 serao deletados. Os nomes devem ser separados
				 por um espaco em branco.

	Return:
		- LBS_OK em caso de sucesso ou um valor negativo.
		  Consulte LastError para maiores detalhes sobre o erro,
		  se ocorrer algum.

	Comments:
		- Este metodo e' "meio pesado", pois abre a UDB para atualizar
		  os dados. Portanto, delete o maximo de usuarios possivel
		  de uma so' vez.
		- So' quem pode deletar um usuario de uma UDB e' o dono da UDB.
		- O usuario correntemente logado nao pode ser deletado, sob pena
		  de obter falha nas operacoes subsequentes.
		- So quem pode deletar usuarios sao o dono da UDB ou
		  super-usuarios.

***/
int
LBSC_Session::DelUser( const LBSC_Ticket *pTicket, char *szUDBName, char *szUsers )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::DelUser") );
	if( bIsLogged == FALSE ){
		ERETURN( LBSE_USERNOTLOGGED );
	}
	if( _bInvalidLicence ){
		// a licenca em uso foi invalidada por outra aplicacao.
		// devemos sair do ar e retornar para que o LBS revalide
		// a licenca.
		ERETURN( LBSE_INVALIDLIC );
	}

	if( TicketIsOk( pTicket ) != 0 ){
		ERETURN( LBSE_TICKETNOTOK );
	}
	if( !szUsers || !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	// verificar se o cara que esta' logado eh o dono da UDB
	if( bUserBase.LB1.tcrHead.szOwnerName != plbscuUser->GetUserName() ){
		// o cara nao eh o dono. Vamos verificar se ele e' um super-usuario
		if( GetUserType( &bUserBase, (char*) plbscuUser->GetUserName() ) != MASTER_USER ){
			// o cara tambem nao eh super usuario
			ERETURN( LBSE_USERNOTOWNERBASE );
		}
	}
	// checar se o cara que esta' logado e' um dos caras que vao ser deletados
	if( strstr( strupr( szUsers ), strupr( (char*) plbscuUser->GetUserName() ) ) ){
		// um dos caras e' o correntemente logado
		ERETURN( LBSE_USERLOGGED );
	}

	LBSC_Field	*pfName = bUserBase[ USERBASEUSERNAME ];
	if( pfName ){
		C_StrTok	cStrTok;
		char *szToken = cStrTok.StrTok( szUsers, " " );
		while( szToken ){
			if( bUserBase.Locate( pTicket, pfName->GetId(), ENTIRETREE, strupr( szToken ) ) == LBS_OK ){
				if( bUserBase.LockRecord( pTicket ) == LBS_OK ){
					char szName[USERNAMESIZE + 1];
					bUserBase.GetFieldRepetition( USERBASEUSERNAME, 0, szName );
					char szPwd[PASSWORDSIZE + 1];
					bUserBase.GetFieldRepetition( USERBASEUSERPASSWORD, 0, szPwd );

					bUserBase.DeleteRecord( pTicket );
					bUserBase.ReleaseRecord( pTicket );

					DelUserFromCache( szName, szPwd, szUDBName);
				}
			}
			szToken = cStrTok.StrTok( NULL, " " );
		}
		ERETURN( LBS_OK );
	}
	ERETURN( LBSE_BADUSERBASE );
}

