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
// Module: LBSLCKCL.CPP
// Description:
//
//	LB1_Lock class methods file.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 06/12/96
//

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_LBSLCKCL_H_
#include	<lbslckcl.h>
#endif

EXTLOG( _clLBSLog );	// objeto para geracao de log

/********************/
LBSC_LB1_LockHead::LBSC_LB1_LockHead()
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::LBSC_LB1_LockHead_1") );

	pLB1 = NULL;
	bIsLocked = FALSE;
	iLastError = !OK;
}

/********************/
LBSC_LB1_LockHead::LBSC_LB1_LockHead( C_LB1 &LB1_Par, BOOL bRead )
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::LBSC_LB1_LockHead_2") );

	pLB1 = &LB1_Par;
	bIsLocked = FALSE;
	iLastError = !OK;
	LB1_LockHead( bRead );
}

/********************/
LBSC_LB1_LockHead::~LBSC_LB1_LockHead()
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::~LBSC_LB1_LockHead") );

	LB1_ReleaseHead();
}

/********************/
int
LBSC_LB1_LockHead::LB1_LockHead( C_LB1 &LB1_Par, BOOL bRead )
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::LB1_LockHead_1") );

	pLB1 = &LB1_Par;
	return( LB1_LockHead( bRead ) );
}

/********************/
int
LBSC_LB1_LockHead::LB1_LockHead( BOOL bRead )
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::LB1_LockHead_2") );

	if( !bIsLocked ){
		iLastError = pLB1 ? pLB1->LB1_LockHead( bRead ) : !OK;
	} else {
		iLastError = OK;
	}
	if( iLastError == OK ){
		bIsLocked = TRUE;
	}
	return( iLastError );
}

/********************/
int
LBSC_LB1_LockHead::LB1_ReleaseHead()
{
	PRINTLOG( _clLBSLog, ("LBSC_LB1_LockHead::LB1_ReleaseHead") );

	if( bIsLocked ){
		iLastError = pLB1 ? pLB1->LB1_ReleaseHead() : !OK;
	} else {
		iLastError = OK;
	}
	if( iLastError == OK ){
		bIsLocked = FALSE;
	}
	return( iLastError );
}

/********************/
BOOL
LBSC_LB1_LockHead::IsLocked()
{
	return( bIsLocked );
}


/********************/
int
LBSC_LB1_LockHead::LastError()
{
	return( iLastError );
}



