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
// Module: MBASE.H
// Description:
//
//	LBSC_MaintBase class definition file.
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last update: 16/09/98
//

#ifndef	_MBASE_H_
#define	_MBASE_H_

#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_MaintBase
{
	public:
		BaseSTR		strBaseName;	// nome da base reservada
		UserSTR		strUserName;	// nome do usuario que pode realizar a operacao
		FullSTR		strWarningMsg;	// mensagem apresentada aos usuarios nao autorizados

		LBSC_MaintBase()
		{
			Set( "", "", "" );
		};
		LBSC_MaintBase( const char *szBaseName, const char *szUserName, const char *szWarningMsg )
		{
			Set( szBaseName, szUserName, szWarningMsg );
		};
		~LBSC_MaintBase(){};

		void Set( const char *szBaseName, const char *szUserName, const char *szWarningMsg )
		{
			strBaseName = (char*) szBaseName;
			strUserName = (char*) szUserName;
			strWarningMsg = (char*) szWarningMsg;
		};
		int	Compare( LBSC_MaintBase *pOther, int iType )
		{
			return( pOther ? stricmp( (char*) strBaseName, (char*) pOther->strBaseName ) : 1 );
		}
		LBSC_MaintBase *Duplicate( void )
		{
			LBSC_MaintBase	*pOther = new LBSC_MaintBase( (const char* ) (char*) strBaseName, (const char* ) (char*) strUserName, (const char* ) (char*) strWarningMsg );
			return( pOther );
		}

		BOOL	IsZero()
		{
			return( (strBaseName == "") && (strUserName == "") && (strWarningMsg == "") );
		}

};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _MBASE_H_


