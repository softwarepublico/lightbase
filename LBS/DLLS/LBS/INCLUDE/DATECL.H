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
// Module: DATECL.H
// Description:
//
//	Header file for date handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 08/09/95
//


#ifndef	_DATECL_H_
#define	_DATECL_H_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined(___DEFS_H)
#include	BORDEFS_H
#endif
#if !defined( __CLASSLIB__DATE_H )
#include	BORDATE_H
#endif
#if !defined __STDIO_H && !defined _INC_STDIO
#include	<stdio.h>
#endif
#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif

class C_Date : public TDate
{
	public:
		C_Date():TDate(){};
		C_Date( DayTy day, YearTy year ):TDate( day, year ){};
		C_Date( DayTy day, MonthTy month, YearTy year ):TDate( day, month, year ){};
		C_Date( const TTime _BIDSFAR &t ):TDate( t ){};
		friend C_Date _BIDSFUNC operator + ( const C_Date _BIDSFAR & dt, int dd ){ return( *( (C_Date*) &( (TDate) dt + dd ) ) ); };
		friend C_Date _BIDSFUNC operator + ( int dd, const C_Date _BIDSFAR & dt ){ return( *( (C_Date*) &( dd + (TDate) dt ) ) ); };
		friend C_Date _BIDSFUNC operator - ( const C_Date _BIDSFAR & dt, int dd ){ return( *( (C_Date*) &( (TDate) dt - dd ) ) ); };
		void Set( char *szBuffer, char *szMask );
		void Get( char *szBuffer, char *szMask );
};

/*******************************************/
inline void
C_Date::Get( char *szBuffer, char *szMask )
{
	// comparacoes para dia e mes com dois digitos
	if( strcmp( szMask, "dd/mm/yyyy" ) == 0 ){
		sprintf( szBuffer, "%02d/%02d/%04d", DayOfMonth(), Month() , Year() );
		return;
	}
	if( strcmp( szMask, "dd/mm/yy" ) == 0 ){
		sprintf( szBuffer, "%02d/%02d/%02d", DayOfMonth(), Month() , Year() % 100 );
		return;
	}
	if( strcmp( szMask, "mm/dd/yyyy" ) == 0 ){
		sprintf( szBuffer, "%02d/%02d/%04d", Month() , DayOfMonth(), Year() );
		return;
	}
	if( strcmp( szMask, "mm/dd/yy" ) == 0 ){
		sprintf( szBuffer, "%02d/%02d/%02d", Month() , DayOfMonth(), Year() % 100 );
		return;
	}

	// comparacoes para dia com dois digitos e mes com um digito
	if( strcmp( szMask, "dd/m/yyyy" ) == 0 ){
		sprintf( szBuffer, "%02d/%01d/%04d", DayOfMonth(), Month() , Year() );
		return;
	}
	if( strcmp( szMask, "dd/m/yy" ) == 0 ){
		sprintf( szBuffer, "%02d/%01d/%02d", DayOfMonth(), Month() , Year() % 100 );
		return;
	}
	if( strcmp( szMask, "m/dd/yyyy" ) == 0 ){
		sprintf( szBuffer, "%01d/%02d/%04d", Month() , DayOfMonth(), Year() );
		return;
	}
	if( strcmp( szMask, "m/dd/yy" ) == 0 ){
		sprintf( szBuffer, "%01d/%02d/%02d", Month() , DayOfMonth(), Year() % 100 );
		return;
	}

	// comparacoes para dia com um digito e mes com dois digitos
	if( strcmp( szMask, "d/mm/yyyy" ) == 0 ){
		sprintf( szBuffer, "%01d/%02d/%04d", DayOfMonth(), Month() , Year() );
		return;
	}
	if( strcmp( szMask, "d/mm/yy" ) == 0 ){
		sprintf( szBuffer, "%01d/%02d/%02d", DayOfMonth(), Month() , Year() % 100 );
		return;
	}
	if( strcmp( szMask, "mm/d/yyyy" ) == 0 ){
		sprintf( szBuffer, "%02d/%01d/%04d", Month() , DayOfMonth(), Year() );
		return;
	}
	if( strcmp( szMask, "mm/d/yy" ) == 0 ){
		sprintf( szBuffer, "%02d/%01d/%02d", Month() , DayOfMonth(), Year() % 100 );
		return;
	}

	// comparacoes para dia e mes com um digito
	if( strcmp( szMask, "d/m/yyyy" ) == 0 ){
		sprintf( szBuffer, "%01d/%01d/%04d", DayOfMonth(), Month() , Year() );
		return;
	}
	if( strcmp( szMask, "d/m/yy" ) == 0 ){
		sprintf( szBuffer, "%01d/%01d/%02d", DayOfMonth(), Month() , Year() % 100 );
		return;
	}
	if( strcmp( szMask, "m/d/yyyy" ) == 0 ){
		sprintf( szBuffer, "%01d/%01d/%04d", Month() , DayOfMonth(), Year() );
		return;
	}
	if( strcmp( szMask, "m/d/yy" ) == 0 ){
		sprintf( szBuffer, "%01d/%01d/%02d", Month() , DayOfMonth(), Year() % 100 );
		return;
	}
}

/*******************************************/
inline void
C_Date::Set( char *szBuffer, char *szMask )
{
	int 	dd, mm , yy;
	char *szAux = strchr( szBuffer, '/');
	if ( !szAux || !strchr( ++szAux, '/') ) {
		// data invalida;
		(*this) = C_Date( 0, 0, 0 );
		return;
	}

	// comparacoes para dia e mes com dois digitos
	if( strcmp( szMask, "dd/mm/yyyy" ) == 0 ){
		sscanf( szBuffer, "%02d/%02d/%04d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "dd/mm/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%02d/%02d/%02d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}
	if( strcmp( szMask, "mm/dd/yyyy" ) == 0 ){
		sscanf( szBuffer, "%02d/%02d/%04d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "mm/dd/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%02d/%02d/%02d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}

	// comparacoes para dia com dois digitos e mes com um digito
	if( strcmp( szMask, "dd/m/yyyy" ) == 0 ){
		sscanf( szBuffer, "%02d/%01d/%04d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "dd/m/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%02d/%01d/%02d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}
	if( strcmp( szMask, "m/dd/yyyy" ) == 0 ){
		sscanf( szBuffer, "%01d/%02d/%04d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "m/dd/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%01d/%02d/%02d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}

	// comparacoes para dia com um digito e mes com dois digitos
	if( strcmp( szMask, "d/mm/yyyy" ) == 0 ){
		sscanf( szBuffer, "%01d/%02d/%04d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "d/mm/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%01d/%02d/%02d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}
	if( strcmp( szMask, "mm/d/yyyy" ) == 0 ){
		sscanf( szBuffer, "%02d/%01d/%04d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "mm/d/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%02d/%01d/%02d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}

	// comparacoes para dia e mes com um digito
	if( strcmp( szMask, "d/m/yyyy" ) == 0 ){
		sscanf( szBuffer, "%01d/%01d/%04d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "d/m/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%01d/%01d/%02d", &dd, &mm, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}
	if( strcmp( szMask, "m/d/yyyy" ) == 0 ){
		sscanf( szBuffer, "%01d/%01d/%04d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, yy );
		return;
	}
	if( strcmp( szMask, "m/d/yy" ) == 0 ){
		C_Date Today;
		sscanf( szBuffer, "%01d/%01d/%02d", &mm, &dd, &yy );
		(*this) = C_Date( dd, mm, ( Today.Year() - Today.Year() % 100 ) + yy );
		return;
	}
}

#define	JULIANDATE( x )		( ( C_Date( 0, 0 ) - C_Date( 0, 0 ).Hash() ) + (JulTy) x )


#endif	// _DATECL_H_


