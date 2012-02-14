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
// Module: SESSCL16.CPP
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

// para controle de invalidacao de licencas
extern	BOOL	_bInvalidLicence;

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	PUBLIC
	Metodo GetUsersData
	Obtem os dados de todos os usuarios de uma UDB.

	Parameters:
		- pTicket     -> ticket de seguranca
		- szUDBName   -> nome da UDB
		- ppUDBReturn -> endereco de uma estrutura TUDBRecord
				 para o retorno dos usuarios
		- pppGrpReturn -> endereco de um char *[] que contera' todos
				  os grupos de todos os usuarios da UDB

	Return:
		- o numero de usuarios da UDB, ou um valor negativo em caso
		  de erro. Consulte LastError para maiores detalhes sobre
		  o erro ocorrido.

	Comments:
		- O array de estruturas TUDBRecord DEVE ser deletado pela
		  aplicacao apos o uso.
		- O array de char * retornado DEVE ser deletado pela aplicacao
		  apos o uso. Para fazer isso, cada um dos elementos do vetor
		  devera' ser deletado e, por fim, o proprio vetor. Ou seja,
		  os elementos Grp[ 0 ], Grp[ 1 ],... Grp[ i ] devem ser
		  deletador um a um e, so' depois, o Grp.
		- O ultimo elemento do array de TUDBRecord contem 0, 0, ..., 0.
		- Para cada elemento de TUDBRecord havera' uma string em
		  pppGrpReturn contendo todos os grupos do usuario, separados
		  por brancos. Isto e', para o elemento TUDBRecord[ 0 ]
		  havera' um elemento Grp[ 0 ] contendo todos os grupos do usuario
		  TUDBRecord[ 0 ].szUserName, separados por espaco em branco.
		- Este metodo e' "bastante pesado", pois abre a UDB para consultar
		  os dados e varre todos os seus registros. Use-o com cuidado.

***/
int
LBSC_Session::GetUsersData( const LBSC_Ticket *pTicket, char *szUDBName, TUDBRecord **ppUDBReturn, char ***pppGrpReturn )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUsersData") );
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
	if( !szUDBName ){
		ERETURN( LBSE_BADARG );
	}

	// abrir a base de usuarios
	LBSC_Base bUserBase( pTicket, szUDBName, this, FALSE, FALSE );
	if( !bUserBase.BaseObjOk() ){
		ERETURN( LBSE_INVALIDUSERBASE );
	}
	if( bUserBase.GetNumActiveRecords( pTicket ) <= 0 ){
		// nao ha' usuarios. Retornar apenas uma estrutura TUDBRecord,
		// contendo 0, 0, ..., 0.
		(*pppGrpReturn) = NULL;
		(*ppUDBReturn) = new TUDBRecord[ 1 ];
		if( !(*ppUDBReturn) ){
			ERETURN( LBSE_NOMEMORY );
		}
		SetError( LBS_OK );
		return( 1 );
	}
	int iSize = bUserBase.GetNumActiveRecords( pTicket ) + 1;
	// alocar o vetor de TUDBRecord
	(*ppUDBReturn) = new TUDBRecord[ iSize ];
	if( !(*ppUDBReturn) ){
		ERETURN( LBSE_NOMEMORY );
	}
	// alocar o array de strings para colocar os grupos de cada usuario
	(*pppGrpReturn) = new char * [ iSize ];
	if( !(*pppGrpReturn) ){
		delete (*ppUDBReturn);
		(*ppUDBReturn) = NULL;
		ERETURN( LBSE_NOMEMORY );
	}
	LBSC_Field	*pf = bUserBase[ USERBASEUSERNAME ];
	if ( !pf ) {
		// deu pau
		delete (*ppUDBReturn);
		(*ppUDBReturn) = NULL;
		delete (*pppGrpReturn);
		(*pppGrpReturn) = NULL;
		ERETURN( LBSE_ERROR );
	}
	bUserBase.SetNavigationByIndex( pTicket, TRUE, pf->uiFieldId, UNIQUETREE );
	if( bUserBase.FirstRecord( pTicket ) != LBS_OK ){
		// deu pau
		delete (*ppUDBReturn);
		(*ppUDBReturn) = NULL;
		delete (*pppGrpReturn);
		(*pppGrpReturn) = NULL;
		bUserBase.SetNavigationByIndex(pTicket, FALSE);
		ERETURN( LBSE_ERROR );
	}
	// zerar a estrutura dos grupos
	for( int i =0; i < iSize; i++ ){
		(*pppGrpReturn)[ i ] = NULL;
	}
	i = 0;
	do{
		LBSC_Field	*pf = bUserBase[ USERBASEUSERNAME ];
		LBSC_Data	*pd = pf ? (*pf)[ 0 ] : NULL;
		
		(*ppUDBReturn)[ i ].szUserName = pd ? (char*) (*pd) : (char*) "";
		pf = bUserBase[ USERBASEUSERPASSWORD ];
		pd = pf ? (*pf)[ 0 ] : NULL;
		(*ppUDBReturn)[ i ].szUserPassword = pd ? (char*) (*pd) : (char*) "";

		pf = bUserBase[ USERBASEUSERTYPE ];
		pd = pf ? (*pf)[ 0 ] : NULL;
		(*ppUDBReturn)[ i ].lUserType = pd ? (long) (*pd) : 0;
		
		pf = bUserBase[ USERBASEUSERDESCRIPTION ];
		pd = pf ? (*pf)[ 0 ] : NULL;
		(*ppUDBReturn)[ i ].szUserDescription = pd ? (char*) (*pd) : (char*) "";
		
		pf = bUserBase[ USERBASEUSERADDRESS ];
		pd = pf ? (*pf)[ 0 ] : NULL;
		(*ppUDBReturn)[ i ].szUserAddress = pd ? (char*) (*pd) : (char*) "";
		
		pf = bUserBase[ USERBASEUSERPHONE ];
		pd = pf ? (*pf)[ 0 ] : NULL;
		(*ppUDBReturn)[ i ].szUserPhone = pd ? (char*) (*pd) : (char*) "";

		// calcular o numero de grupos do usuario corrente
		pf = bUserBase[ USERBASEGROUPLIST ];
		if( pf ){
			int iNumGrp = pf->GetNumberOfRepetition();
			if( iNumGrp > 0 ){
				(*pppGrpReturn)[ i ] = new char[ (iNumGrp * (GROUPNAMESIZE+1)) + 1 ];
				if( (*pppGrpReturn)[ i ] ){
					// preencher a string de grupos do usuario corrente
					((*pppGrpReturn)[ i ])[ 0 ] = '\0';
					pf = bUserBase[ USERBASEGROUPLIST ];
					BOOL bEspacoNoFim = FALSE;
					if( pf ){
						for( int j = 0; j < iNumGrp; j++ ){
							LBSC_Data	*pd = (*pf)[ j ];
							char		*szAux = pd ? (char*) (*pd) : NULL;

							if( szAux ){
								strcat( ((*pppGrpReturn)[ i ]), szAux );
								strcat( ((*pppGrpReturn)[ i ]), " " );
								bEspacoNoFim = TRUE;
							}
						}
					}
					if ( bEspacoNoFim ) {
						((*pppGrpReturn)[ i ])[ strlen( ((*pppGrpReturn)[ i ]) )-1 ] = '\0';
					}
				}
			}
		}
		i++;
	} while( bUserBase.NextRecord( pTicket ) == LBS_OK );
	bUserBase.SetNavigationByIndex(pTicket, FALSE);
	SetError( LBS_OK );
	return( iSize );
}



/***
	PRIVATE
	Metodo GetUserType
	Obtem o tipo de um usuario

	Parameters:
		-
		-

	Return:
		- o tipo do usuario ou um valor negativo indicando erro

	Comments:
		-

***/
long
LBSC_Session::GetUserType( LBSC_Base *pUDB, char *szUserName )
{
	PRINTLOG( _clLBSLog, ("LBSC_Session::GetUserType") );

	if( !pUDB || !szUserName ){
		ERETURN( LBSE_BADARG );
	}
	// procurar o usuario na UDB (a password nao interessa)
	int iRet = FindUser( pUDB, szUserName, "$" );
	if( iRet != LBS_OK && iRet != LBSE_INVALIDPASSWORD ){
		// fudeu
		ERETURN( iRet );
	}
	LBSC_Field	*pf = (*pUDB)[ USERBASEUSERTYPE ];
	if( !pf ){
		ERETURN( LBSE_BADUSERBASE );
	}
	LBSC_Data	*pd = (*pf)[ 0 ];
	if( !pd ){
		ERETURN( LBSE_BADUSERBASE );
	}
	long lType = (long) (*pd);
	SetError( LBS_OK );
	return( lType );
}



