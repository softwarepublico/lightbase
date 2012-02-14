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

#ifndef	_GETSRVRS_H_
#define	_GETSRVRS_H_

#ifdef __NOMFC	// nao usa MFC
	#include <windows.h>
#else // __NOMFC

	#ifdef __MFC	// usa MFC
		#include <afxwin.h>
	#else // __MFC
		#error "FUDEU NO INCLUDE DE WINDOWS.H"
	#endif // __MFC

#endif // __NOMFC

#ifndef _LBSTEMPLATE_H_
	#include <lbstempl.h>
#endif	// _LBSTEMPLATE_H_

class C_GroupServer
{
		char *szServer;
	public:
		C_GroupServer( char *);
		~C_GroupServer( void );

		int Compare( C_GroupServer *cgsOther, int )
		{
			return stricmp(cgsOther->szServer, szServer);
		}
		C_GroupServer *Duplicate( void )
		{
			return NULL;
		}
		operator const char * (void ) { return szServer; }
};

class C_GSList : public LBSC_DList<C_GroupServer> 
{
		void GetServers( NETRESOURCE	*pnrArray );
		void GetGroups( NETRESOURCE	*pnrArray );
	public:
		void GetServers( const char * );
		void GetServers( void );
		void GetAllGroups( void );

		const char * operator [] ( int i ) { return *(Nth( i )); }
};

#endif

