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

#ifndef _CL_STRINGN_
#define _CL_STRINGN_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined __STRING_H && !defined _INC_STRING
#include	<string.h>
#endif
#if !defined(__MEM_H) && !defined _INC_MEMORY
#include	MEM_H
#endif

template<int X>
#ifdef __BORLANDC__
class _LBSCLASS	CL_StringN {
#else
class CL_StringN {
#endif
	private:
		char	szBuffer [ X + 1 ];
	public:
		CL_StringN( void )
		{
			memset( szBuffer, '\0', X + 1 );
		}
		CL_StringN( const char *szText )
		{
			if( szText ){
				strncpy( szBuffer, szText, X );
				szBuffer[ X ] = '\0';
			} else {
				memset( szBuffer, '\0', X + 1 );
			}
		}
		CL_StringN( CL_StringN &b )
		{
			strncpy( szBuffer, b.szBuffer, X );
			szBuffer [ X ] = '\0';
		}
		void	Reset()
		{
			memset( szBuffer, '\0', X + 1 );
		}
		const char *
		operator = ( const char *szText )
		{
			if( szBuffer != szText ){
				Reset();
				if( szText ){
					strncpy( szBuffer, szText, X );
					szBuffer [ X ] = '\0';
				}
			}
			return szBuffer;
		}
		const char *
		operator = ( CL_StringN &c )
		{
			strncpy( szBuffer, c.szBuffer, X );
			szBuffer [ X ] = '\0';
			return szBuffer;
		}
		int
		operator == ( const char *c )
		{
			return c ? strncmp( szBuffer, c ? c : "", X ) == 0 : 0;
		}
		int
		operator == ( char *c )
		{
			return c ? strncmp( szBuffer, c ? c : "", X ) == 0 : 0;
		}
		int
		operator == ( CL_StringN &c )
		{
			return strncmp( szBuffer, c.szBuffer, X ) == 0;
		}
		int
		operator != ( const char *c )
		{
			return c ? strncmp( szBuffer, c ? c : "", X ) != 0 : 0;
		}
		int
		operator != ( char *c )
		{
			return c ? strncmp( szBuffer, c ? c : "", X ) != 0 : 0;
		}
		int
		operator != ( CL_StringN &c )
		{
			return strncmp( szBuffer, c.szBuffer, X ) != 0;
		}
		operator char*( void )
		{
			return szBuffer;
		}
		void Upper( void )
		{
			strupr( szBuffer );
		}
		int
		StrICmp( const char *c )
		{
			return c ? stricmp( szBuffer, c ? c : "" ) == 0 : 0;
		}
		int
		StrICmp( CL_StringN &c )
		{
			return stricmp( szBuffer, c.szBuffer ) == 0;
		}
};

#endif
