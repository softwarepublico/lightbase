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
// Module: LBSEXPOL.H
// Description:
//
//	Header file for LBSC_Expr class
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 11/05/95
//

#ifndef	_LBSEXPOL_H_
#define	_LBSEXPOL_H_


#ifndef _EXPR
#include	<expr.h>	// GREEN
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifndef _LBSC_OCLIST_H_
#include <oclistcl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


class _LBSCLASS LBSC_Expr 
{
	public:
		LBSC_OcList		*pOccList;
		char			*szExpr;

		LBSC_Expr()
		{ 
			pOccList = NULL; 
			szExpr = NULL;
		}
		~LBSC_Expr()
		{ 
			if ( pOccList ) {
				delete pOccList; 
			}
			if ( szExpr ) {
				delete szExpr;
			}
			pOccList = NULL;
			szExpr = NULL;
		}
		int		Compare( LBSC_Expr *, int ) 
		{ 
			return 0; 
		}
		LBSC_Expr	*Duplicate() 
		{ 
			return( NULL ); 
		}
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _LBSEXPOL_H_




