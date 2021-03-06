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

//
// Module: USRCL.CPP
// Description:
//
//	LBSC_USR class methods usr.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 30/09/94
//


#ifndef	_USR_H_
#include <usrcl.h>
#endif
#ifndef	_PASSWDCL_H_
#include <passwdcl.h>
#endif


#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif

/***
	Metodo LBSC_User
	Construtor do objeto LBSC_User

	Parameters:
		-
	Return:
		-
	Comments:
		-

***/

LBSC_User::LBSC_User():
	tutUserType( 0 ),
	lbscpPassword( DEFUSERPASSWORD ),
	plbscglGroupList( NULL ),
	plbscsSession( NULL )
{
}



/***
	Metodo LBSC_User
	Construtor 2 do objeto LBSC_User

	Parameters:
		- szUserName
		- szUserPassword
		- szDescription
		- plbscglGroupList
		- plbscsSession
		- tutUserType

	Return:

	Comments:

***/

LBSC_User::LBSC_User( const char *szUserName, const char *szUserPassword,
			const char *szDescription, LBSC_GroupList *pGroupList,
			LBSC_Session *pSession, TUserType tutUserType ):
	tutUserType( tutUserType ),
	lbscpPassword( szUserPassword )
{
	strUserName = szUserName;
	strDescription = szDescription;
	plbscglGroupList = pGroupList;
	plbscsSession = pSession;
}


/***
	Metodo ~LBSC_User
	Destrutor do objeto LBSC_User

	Parameters:

	Return:

	Comments:

***/


LBSC_User::~LBSC_User()
{
	if( plbscglGroupList ){
		delete plbscglGroupList;
	}
//	if( plbscsSession ){			// NAO DESTRUA!!!!!!
//		delete plbscsSession;
//	}
}


/***
	Metodo ModifyPassword
	Modifica a password do usuario

	Parameters:
		- szNewPassword

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_User::ModifyPassword( const char *szNewPassword )
{
	return( lbscpPassword.Modify( szNewPassword ) );
}


/***
	Metodo GetPassword
	Obtem a password do usuario

	Parameters:

	Return:
		A password do usuario. Disponivel apenas para consulta.

	Comments:

***/
char *
LBSC_User::GetPassword()
{
	return( lbscpPassword.GetPassword() );
}


/***
	Metodo ModifyDescription
	Modifica o atributo descricao do usuario

	Parameters:
		- szDescription

	Return:
		LBS_OK ou erro.

	Comments:

***/
int
LBSC_User::ModifyDescription( const char *szDescription )
{
	strDescription = szDescription;
	return( LBS_OK );
}


/***
	Metodo ModifyType
	Modifica o atributo tipo de usuario do usuario

	Parameters:
		- tutUserType

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_User::ModifyType( TUserType tutUserType )
{
	// $$$ Procurar se o usr corrente � o administrador
	// $$$ Se for
	this->tutUserType = tutUserType;
	return( LBS_OK );
	// $$$ Se nao for
	// return( LBSE_INVALIDUSER );
}


/***
	Metodo AddGroup
	Adiciona um grupo a lista de grupos do usuario

	Parameters:
		- plbscgGroup

	Return:
		LBS_OK se conseguir adicionar ou erro.

	Comments:

***/
int
LBSC_User::AddGroup( LBSC_Group *plbscgGroup )
{
	return( plbscglGroupList->Add( plbscgGroup, AFTER ) );
}


/***
	Metodo DelGroup
	Deleta um grupo da lista de grupos do usuario

	Parameters:

	Return:
		LBS_OK se conseguir deletar ou erro.

	Comments:

***/
int
LBSC_User::DelGroup()
{
	return( plbscglGroupList->Del() );
}


/***
	Metodo NextGroup
	Vai para o proximo nodo da lista de grupos do usuario

	Parameters:

	Return:
		Apontador para objeto LBSC_Group.

	Comments:

***/
LBSC_Group *
LBSC_User::NextGroup()
{
	return( plbscglGroupList->Next() );
}


/***
	Metodo FirstGroup
	Vai para o primeiro nodo da lista de grupos do usuario

	Parameters:

	Return:
		Apontador para objeto LBSC_Group.

	Comments:

***/
LBSC_Group *
LBSC_User::FirstGroup()
{
	return( plbscglGroupList->First() );
}


/***
	Metodo LastGroup
	Vai para o ultimo nodo da lista de grupos do usuario

	Parameters:

	Return:
		Apontador para objeto LBSC_Group.

	Comments:

***/
LBSC_Group *
LBSC_User::LastGroup()
{
	return( plbscglGroupList->Last() );
}


/***
	Metodo NthGroup
	Vai para o n-esimo nodo da lista de grupos do usuario

	Parameters:

	Return:
		Apontador para objeto LBSC_Group.

	Comments:

***/
LBSC_Group *
LBSC_User::NthGroup( int iPos )
{
	return( plbscglGroupList->Nth( iPos ) );
}


/***
	Metodo GetUserType
	Obtem o tipo do usuario

	Parameters:

	Return:
		O tipo do usuario.

	Comments:

***/
TUserType
LBSC_User::GetUserType()
{
	return( tutUserType );
}


/***
	Metodo GetUserName
	Obtem o nome do usuario

	Parameters:

	Return:
		O nome do usuario.

	Comments:

***/
const char *
LBSC_User::GetUserName()
{
	return( (const char*) ((char*) strUserName) );
}


/***
	Metodo SetUserName
	Seta o nome do usuario

	Parameters:
		- O nome do usuario.

	Return:
		-

	Comments:
		-

***/
void
LBSC_User::SetUserName( const char *szUserName )
{
	strUserName = szUserName;
}






