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
// Module: lbsollst.H
//	LBSC_OLList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 11/05/95
//


#ifndef	_LBSOLLST_H_
#define	_LBSOLLST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBSEXPOL_H_
#include	<lbsexpol.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_OLList : public LBSC_DList<LBSC_Expr>
{
	public:
/*				LBSC_OLList() : LBSC_DList<LBSC_Expr>(){};
				~LBSC_OLList(){};
		LBSC_DList<LBSC_Expr>::NumElem;
		LBSC_DList<LBSC_Expr>::Next;
		LBSC_DList<LBSC_Expr>::Previous;
		LBSC_DList<LBSC_Expr>::First;
		LBSC_DList<LBSC_Expr>::Last;
		LBSC_DList<LBSC_Expr>::Current;
		LBSC_DList<LBSC_Expr>::GetCurrentIndex;
		LBSC_DList<LBSC_Expr>::DeleteCurrObj;
		LBSC_DList<LBSC_Expr>::Nth;
		LBSC_DList<LBSC_Expr>::Search;
		LBSC_DList<LBSC_Expr>::Find;
		LBSC_DList<LBSC_Expr>::DelAll;
		LBSC_DList<LBSC_Expr>::Del;
		LBSC_DList<LBSC_Expr>::Add;
		LBSC_DList<LBSC_Expr>::operator[];

		~LBSC_OLList()
		{
			LBSC_Expr	*pAux = First();
			while( pAux ){
				if( pAux == (LBSC_Expr*) -1 ){
					SetCurrObj( NULL );
				}
				pAux = Next();
			}

		}

		void	DeleteCurrObj()
		{
			EnterCriticalSection( 0 );
			if( this->Current() ){
				delete this->Current();
				SetCurrObj( (LBSC_Expr*) -1 );
			}
			LeaveCriticalSection( 0 );
		}
*/
		LBSC_Expr	*operator [ ] ( int iPos )
		{ 
			LBSC_Expr	*pobjRet = NULL;

			EnterCriticalSection( 0 );
			pobjRet = (LBSC_Expr *) Nth( iPos );
			LeaveCriticalSection( 0 );
			return( pobjRet );
		}

		LBSC_Expr	*Nth( int iPos )
		{ 
			LBSC_Expr	*pobjRet = NULL;

			EnterCriticalSection( 0 );
			pobjRet = (LBSC_Expr *) LBSC_List::Nth( iPos );
			while( GetCurrentIndex() < iPos ){
				Next();
				pobjRet = Current();
			}
			LeaveCriticalSection( 0 );
			return( pobjRet );
		}
};


#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _LBSOLLST_H_


