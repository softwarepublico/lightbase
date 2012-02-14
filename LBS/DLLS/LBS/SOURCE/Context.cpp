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
// Module: CONTEXT.CPP
// Description:
//
//	LBSC_BASE context methods file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 03/02/97
//


// este arquivo implementa metodos que alteram contextos 
// de outros para efeito de teste

#ifndef	_LOGCL_H_
#include	<logcl.h>
#endif
#ifndef	_LBNEWDBG_H_
#include	<lbnewdbg.h>
#endif
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif

#ifdef __TEST

EXTLOG( _clLBSLog );	// objeto para geracao de log

/***
	Metodo para setar um vetor contendo o array de valores
	que serao utilizados pelo metodo que estiver em teste.

	Este metodo so' serve para testar ponteiros.

	O array szCtxArray contem varios ponteiros, que serao 
	usados pelo metodo ChangePointerContext.
***/
void
LBSC_Base::MakePointerContext( void **ppCtxArray, int iSizeofArray )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::MakePointerContext") );

	ppCtxPointerArray = ppCtxArray;
	iSizeofPointerArray = iSizeofArray;
	iCurrentPointerArrayPos = 0;
}


/***
	Metodo para modificar um ponteiro dado por um outro
	metodo, que esta' sendo testado.
***/
void
LBSC_Base::ChangePointerContext( void **ppModPt )
{
	PRINTLOG( _clLBSLog, ("LBSC_Base::ChangePointerContext") );

	if( ppModPt && ppCtxPointerArray && (iCurrentPointerArrayPos < iSizeofPointerArray) ){
		*ppModPt = (void*) ((char*) ppCtxPointerArray[ iCurrentPointerArrayPos++ ] );
	}
}

#endif	// __TEST

