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

