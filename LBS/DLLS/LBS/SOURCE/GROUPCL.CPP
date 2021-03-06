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
