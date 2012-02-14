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
// Module: PASSWDCL.H
// Description:
//
//	Methods file for password handling.
//
// Programmer:	Tricia Souto Santos
//
// Last update: 30/09/94
//

#ifndef	_PASSWDCL_H_
#include <passwdcl.h>
#endif
#ifndef	_LBSDEFS_H_
#include <lbsdefs.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include <string.h>
#endif

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif


/***
	Metodo LBSC_Password
	Construtor da classe LBSC_Password

	Parameters:
		- szPassword

	Return:

	Comments:

***/

LBSC_Password::LBSC_Password( const char *szPassword )
{
	strPassword = szPassword;
}


/***
	Metodo ~LBSC_Password
	Destrutor da classe LBSC_Password

	Parameters:

	Return:

	Comments:

***/

LBSC_Password::~LBSC_Password()
{
}


/***
	Metodo Modify
	Modifica a password

	Parameters:
		- szNewPassword

	Return:
		LBS_OK se conseguir modificar ou erro.

	Comments:

***/
int
LBSC_Password::Modify( const char *szNewPassword )
{
	strPassword = szNewPassword;
	return( LBS_OK );
}


/***
	Metodo Verify
	Verifica se a password recebida e igual a corrente

	Parameters:
		- szPassword

	Return:
		- LBS_OK se a password estiver correta ou LBSE_INVALIDPASSWORD,
		  em caso de erro.

	Comments:

***/
int
LBSC_Password::Verify( const char *szPassword )
{
	return( (strPassword == szPassword) ? LBS_OK : LBSE_INVALIDPASSWORD );
}


/***
	Metodo GetPassword
	Obtem a password

	Parameters:

	Return:
		A password.

	Comments:
		- Este metodo retorna uma copia do buffer interno e a
		  aplicacao deve liberar o espaco alocado para a copia.

***/
char *
LBSC_Password::GetPassword()
{
	return( Strdup( strPassword ) );
}

/***
	Metodo GetConstPassword
	Obtem a password

	Parameters:

	Return:
		A password.

	Comments:
		- Este metodo NAO retorna copia. Ele retorna apenas
		  um ponteiro para o buffer interno.

***/
const char *
LBSC_Password::GetConstPassword()
{
	return( strPassword );
}



