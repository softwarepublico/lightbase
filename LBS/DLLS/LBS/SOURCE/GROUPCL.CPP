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
// Module: GROUPCL.H
// Description:
//
//	Methods file for group handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 30/09/94
//

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_GROUPCL_H_
#include 	<groupcl.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif


/***
	Metodo LBSC_Group
	Construtor da classe LBSC_Group

	Parameters:
		- szUserName
		- szDescription

	Return:

	Comments:

***/

LBSC_Group::LBSC_Group( const char *szUserName, const char *szDescription )
{
	LBSC_Group::strUserName = szUserName;
	LBSC_Group::strDescription = szDescription;
}


/***
	Metodo ~LBSC_Group
	Destrutor da classe LBSC_Group

	Parameters:

	Return:

	Comments:

***/

LBSC_Group::~LBSC_Group()
{
}



/***
	Metodo ModifyDescription
	Modifica a descricao de um grupo

	Parameters:
		- szNewDescription

	Return:

	Comments:

***/
int
LBSC_Group::ModifyDescription( const char *szNewDescription )
{
	strDescription = szNewDescription;
	return( LBS_OK );
}
