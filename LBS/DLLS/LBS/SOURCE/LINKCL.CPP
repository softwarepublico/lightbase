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
// Module: LINKCL.CPP
// Description:
//
//	Methods file for link handling.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 28/09/94
//

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_LINKCL_H_
#include	<linkcl.h>
#endif
#ifndef	_LBSDEFS_H_
#include	<lbsdefs.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif


/***
	Metodo LBSC_Link
	Construtor da classe LBSC_Link

	Parameters:
		- szSlaveBase
		- szMasterBase
		- szSlaveField
		- szMasterField
		- bPropagate
		- bActive
		- bLinkType

	Return:

	Comments:

***/

LBSC_Link::LBSC_Link( char *szSlaveBase, char *szMasterBase, char *szSlaveField,
			char *szMasterField, BOOL bPropagate, BOOL bActive,
			BYTE bLinkType ) :
	bPropagate( bPropagate ),
	bActive( bActive ),
	bLinkType( bLinkType )

{
	this->szSlaveBaseName = szSlaveBase;
	this->szMasterBaseName = szMasterBase;
	this->szSlaveFieldName = szSlaveField;
	this->szMasterFieldName = szMasterField;
}



/***
	Metodo ~LBSC_Link
	Destrutor da classe LBSC_Link

	Parameters:

	Return:

	Comments:

***/

LBSC_Link::~LBSC_Link()
{
}


/***
	Metodo ModifyPropagateFlag
	Modifica o flag de propagacao de um objeto LBSC_Link

	Parameters:
		- bNewFlag

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Link::ModifyPropagateFlag( BOOL bNewFlag )
{
	bPropagate = bNewFlag;
	return( LBS_OK );
}


/***
	Metodo ModifyActiveFlag
	Modifica o flag de status de um objeto LBSC_Link

	Parameters:
		- bNewFlag

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Link::ModifyActiveFlag( BOOL bNewFlag )
{
	bActive = bNewFlag;
	return( LBS_OK );
}


/***
	Metodo SetSlaveBaseAddr
	Seta o endereco o endereco da base escrava

	Parameters:
		- plbscSlaveBase

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Link::SetSlaveBaseAddr( LBSC_Base *plbscSlaveBase )
{
	this->plbscSlaveBase = plbscSlaveBase;
	return( LBS_OK );
}


/***
	Metodo SetMasterBaseAddr
	Seta o endereco o endereco da base mestre

	Parameters:
		- plbscMasterBase

	Return:
		LBS_OK.

	Comments:

***/
int
LBSC_Link::SetMasterBaseAddr( LBSC_Base *plbscMasterBase )
{
	this->plbscMasterBase = plbscMasterBase;
	return( LBS_OK );
}


