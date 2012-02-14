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

// modulo de alocacao de estruturas que nao puderam
// ser compiladas em LBSTYPES.H

#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_USRINFOL_H_
#include	<usrinfol.h>
#endif
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif

LBSC_AppUserInfoList *
New_LBSC_AppUserInfoList()
{
	return( new LBSC_AppUserInfoList );
}

void
Delete_LBSC_AppUserInfoList( LBSC_AppUserInfoList *pData )
{
	if( pData ){
		delete pData;
	}
}

void
Equal_LBSC_AppUserInfoList( LBSC_AppUserInfoList *pData1, LBSC_AppUserInfoList *pData2 )
{
	(*pData1) = (*pData2);
}

LBSC_AppNetInfoList *
New_LBSC_AppNetInfoList()
{
	return( new LBSC_AppNetInfoList );
}

void
Delete_LBSC_AppNetInfoList( LBSC_AppNetInfoList *pData )
{
	if( pData ){
		delete pData;
	}
}

void
Equal_LBSC_AppNetInfoList( LBSC_AppNetInfoList *pData1, LBSC_AppNetInfoList *pData2 )
{
	(*pData1) = (*pData2);
}

LBSC_AppSessionNetInfoList *
New_LBSC_AppSessionNetInfoList()
{
	return( new LBSC_AppSessionNetInfoList );
}


void
Delete_LBSC_AppSessionNetInfoList( LBSC_AppSessionNetInfoList *pData )
{
	if( pData ){
		delete pData;
	}
}

void
Equal_LBSC_AppSessionNetInfoList( LBSC_AppSessionNetInfoList *pData1, LBSC_AppSessionNetInfoList *pData2 )
{
	(*pData1) = (*pData2);
}

LBSC_AppBaseNetInfoList *
New_LBSC_AppBaseNetInfoList()
{
	return( new LBSC_AppBaseNetInfoList );
}


void
Delete_LBSC_AppBaseNetInfoList( LBSC_AppBaseNetInfoList *pData )
{
	if( pData ){
		delete pData;
	}
}

void
Equal_LBSC_AppBaseNetInfoList( LBSC_AppBaseNetInfoList *pData1, LBSC_AppBaseNetInfoList *pData2 )
{
	(*pData1) = (*pData2);
}

