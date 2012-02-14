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
// Module: TIMECL.H
// Description:
//
//	Header file for time handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 14/10/94
//


#ifndef	_TIMECL_H_
#define	_TIMECL_H_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined(___DEFS_H)
#include	BORDEFS_H
#endif
#if !defined(__CLASSLIB_TIME_H)
#include	BORTIME_H
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

class C_Time : public TTime
{
	public:
		C_Time():TTime(){};
		C_Time( ClockTy s ):TTime( s ){};
		C_Time( HourTy h, MinuteTy m, SecondTy s = 0 ):TTime( h, m, s ){};
		C_Time( const TDate& td, HourTy h = 0, MinuteTy m = 0, SecondTy s = 0 ):TTime( td, h, m, s ){};

		friend C_Time _BIDSFUNC operator + ( const C_Time _BIDSFAR & t, long s ){ return( *( (C_Time*) &( (TTime) t + s ) ) ); };
		friend C_Time _BIDSFUNC operator + ( long s, const C_Time _BIDSFAR & t ){ return( *( (C_Time*) &( s + (TTime) t ) ) ); };
		friend C_Time operator - ( const C_Time _BIDSFAR & t, long s ){ return( *( (C_Time*) &( (TTime) t - s ) ) ); };

		void Set( char *szBuffer, char *szMask );
		void Get( char *szBuffer, char *szMask );
};

/*****************************************************/
inline void
C_Time::Get( char *szBuffer, char *szMask )
{
	// comparacoes para hora e minuto com dois digitos
	if( strcmp( szMask, "hh:mm:ss" ) == 0 ){
		sprintf( szBuffer, "%02d:%02d:%02d", Hour(), Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "hh:mm" ) == 0 ){
		sprintf( szBuffer, "%02d:%02d", Hour(), Minute() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:mm:ss" ) == 0 ){
		sprintf( szBuffer, "(%cM)%02d:%02d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:mm" ) == 0 ){
		sprintf( szBuffer, "(%cM)%02d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute() );
		return;
	}

	// comparacoes para hora com dois digitos e minuto com um digito
	if( strcmp( szMask, "hh:m:ss" ) == 0 ){
		sprintf( szBuffer, "%02d:%01d:%02d", Hour(), Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "hh:m" ) == 0 ){
		sprintf( szBuffer, "%02d:%01d", Hour(), Minute() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:m:ss" ) == 0 ){
		sprintf( szBuffer, "(%cM)%02d:%01d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:m" ) == 0 ){
		sprintf( szBuffer, "(%cM)%02d:%01d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute() );
		return;
	}

	// comparacoes para hora com um digito e minuto com dois digitos
	if( strcmp( szMask, "h:mm:ss" ) == 0 ){
		sprintf( szBuffer, "%01d:%02d:%02d", Hour(), Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "h:mm" ) == 0 ){
		sprintf( szBuffer, "%01d:%02d", Hour(), Minute() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:mm:ss" ) == 0 ){
		sprintf( szBuffer, "(%cM)%01d:%02d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:mm" ) == 0 ){
		sprintf( szBuffer, "(%cM)%01d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute() );
		return;
	}

	// comparacoes para hora e minuto com um digito
	if( strcmp( szMask, "h:m:ss" ) == 0 ){
		sprintf( szBuffer, "%01d:%01d:%02d", Hour(), Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "h:m" ) == 0 ){
		sprintf( szBuffer, "%01d:%01d", Hour(), Minute() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:m:ss" ) == 0 ){
		sprintf( szBuffer, "(%cM)%01d:%01d:%02d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute(), Second() );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:m" ) == 0 ){
		sprintf( szBuffer, "(%cM)%01d:%01d", ( Hour() / 12 ? 'P' : 'A' ),
			Hour() % 12, Minute() );
		return;
	}

}

/*****************************************************/
inline void
C_Time::Set( char *szBuffer, char *szMask )
{
	int hh, mm, ss;
	// comparacoes para hora e minuto com dois digitos
	if( strcmp( szMask, "hh:mm:ss" ) == 0 ){
		sscanf( szBuffer, "%02d:%02d:%02d", &hh, &mm, &ss );
		(*this) = C_Time( hh, mm, ss );
		return;
	}
	if( strcmp( szMask, "hh:mm" ) == 0 ){
		sscanf( szBuffer, "%02d:%02d", &hh, &mm );
		(*this) = C_Time( hh, mm, 0 );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:mm:ss" ) == 0 ){
		sscanf( szBuffer + 4, "%02d:%02d:%02d", &hh, &mm, &ss );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, ss );
		} else {
			(*this) = C_Time( hh + 12, mm, ss );
		}
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:mm" ) == 0 ){
		sscanf( szBuffer + 4, "%02d:%02d", &hh, &mm );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, 0 );
		} else {
			(*this) = C_Time( hh + 12, mm, 0 );
		}
		return;
	}

	// comparacoes para hora com dois digitos e minuto com um digito
	if( strcmp( szMask, "hh:m:ss" ) == 0 ){
		sscanf( szBuffer, "%02d:%01d:%02d", &hh, &mm, &ss );
		(*this) = C_Time( hh, mm, ss );
		return;
	}
	if( strcmp( szMask, "hh:m" ) == 0 ){
		sscanf( szBuffer, "%02d:%01d", &hh, &mm );
		(*this) = C_Time( hh, mm, 0 );
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:m:ss" ) == 0 ){
		sscanf( szBuffer + 4, "%02d:%01d:%02d", &hh, &mm, &ss );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, ss );
		} else {
			(*this) = C_Time( hh + 12, mm, ss );
		}
		return;
	}
	if( strcmp( szMask, "(AM|PM)hh:m" ) == 0 ){
		sscanf( szBuffer + 4, "%02d:%01d", &hh, &mm );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, 0 );
		} else {
			(*this) = C_Time( hh + 12, mm, 0 );
		}
		return;
	}

	// comparacoes para hora com um digito e minuto com dois digitos
	if( strcmp( szMask, "h:mm:ss" ) == 0 ){
		sscanf( szBuffer, "%01d:%02d:%02d", &hh, &mm, &ss );
		(*this) = C_Time( hh, mm, ss );
		return;
	}
	if( strcmp( szMask, "h:mm" ) == 0 ){
		sscanf( szBuffer, "%01d:%02d", &hh, &mm );
		(*this) = C_Time( hh, mm, 0 );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:mm:ss" ) == 0 ){
		sscanf( szBuffer + 4, "%01d:%02d:%02d", &hh, &mm, &ss );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, ss );
		} else {
			(*this) = C_Time( hh + 12, mm, ss );
		}
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:mm" ) == 0 ){
		sscanf( szBuffer + 4, "%01d:%02d", &hh, &mm );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, 0 );
		} else {
			(*this) = C_Time( hh + 12, mm, 0 );
		}
		return;
	}

	// comparacoes para hora e minuto com um digito
	if( strcmp( szMask, "h:m:ss" ) == 0 ){
		sscanf( szBuffer, "%01d:%01d:%02d", &hh, &mm, &ss );
		(*this) = C_Time( hh, mm, ss );
		return;
	}
	if( strcmp( szMask, "h:m" ) == 0 ){
		sscanf( szBuffer, "%01d:%01d", &hh, &mm );
		(*this) = C_Time( hh, mm, 0 );
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:m:ss" ) == 0 ){
		sscanf( szBuffer + 4, "%01d:%01d:%02d", &hh, &mm, &ss );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, ss );
		} else {
			(*this) = C_Time( hh + 12, mm, ss );
		}
		return;
	}
	if( strcmp( szMask, "(AM|PM)h:m" ) == 0 ){
		sscanf( szBuffer + 4, "%01d:%01d", &hh, &mm );
		if( szBuffer [ 1 ] == 'A' ){
			(*this) = C_Time( hh % 12, mm, 0 );
		} else {
			(*this) = C_Time( hh + 12, mm, 0 );
		}
		return;
	}

}

#define	SECONDTIME( x )		( C_Time( (ClockTy) x ) )

#endif	// _TIMECL_H_
