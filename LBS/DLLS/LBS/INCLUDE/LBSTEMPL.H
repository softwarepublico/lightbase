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

// LBS template file

#ifndef	_LBSTEMPLATE_H_
#define	_LBSTEMPLATE_H_

#ifndef	_LBSLIST_H_
#include	<lbslstcl.h>
#endif
#ifndef	_LBSERROR_H_
#include	<lbserror.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif

#ifndef _CRITSECT_H_
#include	<critsect.h>
#endif

/****************************************/
template 	<class OBJ>
class	LBSC_DList : public LBSC_List
{
	public:
			LBSC_DList():LBSC_List(){};
			~LBSC_DList(){ this->DelAll(); }
		int	Update( OBJ *poObj )
		{
				OBJ *poOldObj = (OBJ*) LBSC_List::Update( poObj );
				if( poOldObj ){
					delete poOldObj;
					return( OK );
				}
			return( !OK );
		};
		OBJ	*Refresh( OBJ *poObj )
		{
				OBJ *poOldObj = (OBJ*) LBSC_List::Update( poObj );
			return( poOldObj );
		};
		void	DeleteCurrObj()
		{
				OBJ	*pObj = this->Current();
				if( pObj ){
					delete pObj;
					LBSC_List::SetCurrObj( NULL );
				}
		}
		int 	Compare( void *poObj1, void *poObj2, int iSearchType )
		{
			return( ((OBJ*)poObj1)->Compare( (OBJ*)poObj2, iSearchType ) );
		}
		void	*Duplicate( void *poObj1 )
		{
			return( (void*) ((OBJ*)poObj1)->Duplicate() );
		}

		int	Add( OBJ *poObj, int iMode )
		{
			int	iRet;

				iRet = LBSC_List::Add( poObj, iMode );
			return( iRet );
		}
		int	Del()
		{
			int	iRet;

				this->DeleteCurrObj();
				iRet = LBSC_List::Del();
			return( iRet );
		}
		int	DelAll()
		{
				while( this->Del() != LBSE_EMPTYLIST );
			return( OK );
		};
		OBJ	*Next()
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Next();
			return( pobjRet );
		}
		OBJ	*Previous()
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Previous();
			return( pobjRet );
		}
		
		OBJ	*First()
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::First();
			return( pobjRet );
		}

		OBJ	*Last() 
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Last();
			return( pobjRet );
		}

		OBJ	*Current() 
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Current();
			return( pobjRet );
		}

		OBJ	*Nth( int iPosition )
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Nth( iPosition );
			return( pobjRet );
		}

		OBJ	*operator [ ] ( int iPos )
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Nth( iPos );
			return( pobjRet );
		}

		int	NumElem()
		{
			int	iRet;

				iRet = LBSC_List::NumElem();
			return( iRet );
		}

		int	GetCurrentIndex()
		{
			int	iRet;

				iRet = LBSC_List::GetCurrentIndex();
			return( iRet );
		}

		OBJ 	*Search( OBJ *poObj, int iType, int iSearchArg ) 
		{ 
			OBJ	*pobjRet;

				pobjRet = (OBJ *) LBSC_List::Search( (void *) poObj, iType, iSearchArg );
			return( pobjRet );
		}

		LBSC_DList<OBJ>&	operator = ( LBSC_DList<OBJ> &clOtherList );
		OBJ *			Find( OBJ *pvSearchData, int = 0, BOOL = TRUE );
		int				FindNull( BOOL = TRUE );

		LBSC_DList<OBJ>&	operator << ( LBSC_DList<OBJ> &clOtherList )
		{
			OBJ *obj;

				do{
					obj = clOtherList[ 0 ];
					if( obj ){
						Add( obj, TAIL );
						clOtherList.Refresh( NULL );
						clOtherList.Del();
					}
				} while( obj );
			return (*this);
		}
};

/****************************************/
template<class OBJ>
OBJ *
LBSC_DList<OBJ>::Find( OBJ *pvSearchData, int iSearchArg, BOOL bStart )
{
	int	iCurrIndex;
	OBJ  	*pvAux;
	int   	iResultCompare;

		if( bStart ){
			if( !First() ){
				return( NULL );
			}
		}
		pvAux = Current();
		if( !pvAux ){
			return( NULL );
		}
		iCurrIndex = GetCurrentIndex();
		while( (iResultCompare = Compare( pvAux, pvSearchData, iSearchArg )) != 0 &&
					(pvAux = Next()) != NULL );
		if( iResultCompare == 0 ){
			return( pvAux );
		}
		Nth( iCurrIndex );
	return( NULL );
}

template<class OBJ>
int
LBSC_DList<OBJ>::FindNull( BOOL bStart )
{
		if( bStart ){
			if( !First() ){
				return( !OK );
			}
		}
		while( Next() );
		if( Current() ){
			// NULL nao enontrado
			return( !OK );
		}
	return( OK );
}

/****************************************/
template<class OBJ>
LBSC_DList<OBJ>&
LBSC_DList<OBJ>::operator = ( LBSC_DList<OBJ> &clOtherList )
{
		this->DelAll();
		if( clOtherList.First() ){
			do{
				if( this->Add( ((OBJ *) clOtherList.Current())->Duplicate(), AFTER ) != OK ){
					break;
				}
			} while( clOtherList.Next() );
		}
	return *this;
}

/****************************************/
template	<class OBJ>
class	LBSC_SList : LBSC_List
{
	protected:
		void	DeleteCurrObj()
		{
			if( this->Current() ){
				delete this->Current();
				LBSC_List::SetCurrObj( NULL );
			}
		}
		int 	Compare( void *poObj1, void *poObj2, int iSearchType )
		{
			return( ((OBJ*)poObj1)->Compare( (OBJ*)poObj2, iSearchType ) );
		}
		void	*Duplicate( void *poObj1 )
		{
			return( (void*) ((OBJ*)poObj1)->Duplicate() );
		}

	public:
				LBSC_SList():LBSC_List(){}
				~LBSC_SList(){ this->DelAll(); }
		int	Update( OBJ *poObj )
		{
			OBJ *poOldObj = (OBJ*) LBSC_List::Update( poObj );
			if( poOldObj ){
				delete poOldObj;
				return( OK );
			}
			return( !OK );
		};
		int	Add( OBJ *poObj, int iMode ) 
		{ 
			int	iRet;

			iRet = LBSC_List::Add( poObj, iMode );
			return( iRet );
		}
		int	Del()
		{
			int	iRet;

			this->DeleteCurrObj();
			iRet = LBSC_List::Del();
			return( iRet );
		};
		int	DelAll()
		{
#ifdef __BORLANDC__
#pragma warn -inl
#endif
			while( this->Del() != LBSE_EMPTYLIST );
#ifdef __BORLANDC__
#pragma warn .inl
#endif
			return( OK );
		}

		OBJ	*Next()
		{ 
			OBJ	*pobjRet;

			pobjRet = (OBJ *) LBSC_List::Next();
			return( pobjRet );
		}
		
		OBJ	*First()
		{ 
			OBJ	*pobjRet;

			pobjRet = (OBJ *) LBSC_List::First();
			return( pobjRet );
		}

		OBJ	*Last() 
		{ 
			OBJ	*pobjRet;

			pobjRet = LBSC_List::Last();
			return( pobjRet );
		}

		OBJ	*Current() 
		{ 
			OBJ	*pobjRet;

			pobjRet = LBSC_List::Current();
			return( pobjRet );
		}

		OBJ	*Nth( int iPosition )
		{ 
			OBJ	*pobjRet;

			pobjRet = LBSC_List::Nth();
			return( pobjRet );
		}

		int	NumElem()
		{
			int	iRet;

			iRet = LBSC_List::NumElem();
			return( iRet );
		}

		OBJ 	*Search( OBJ *poObj, int iType, int iSearchArg ) 
		{ 
			OBJ	*pobjRet;

			pobjRet = LBSC_List::Search( (void *) poObj, iType, iSearchArg );
			return( pobjRet );
		}

		LBSC_SList<OBJ>	*DuplicateList()
		{ 
			LBSC_SList<OBJ>	*pobjRet;

			pobjRet = LBSC_List::DuplicateList();
			return( pobjRet );
		}
};



#endif //_LBSTEMPLATE_H_



