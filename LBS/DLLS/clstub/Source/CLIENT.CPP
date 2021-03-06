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
    // Module: CLIENT.CPP
    // Description:
    //
    //	Client entry point module
    //
    // Programmer:	Adriano Sergio R. de Souza
    //
    // Last update: 13/04/95
    //
 
#include <windows.h>

#ifndef _LBSNETCL_H_
	#include <lbsnetcl.h>
#endif	// _LBSNETCL_H_

#ifndef _LBSDEFS_H_
	#include	<lbsdefs.h>
#endif	// _LBSDEFS_H_

#ifndef _APPMNGR_H_
	#include	<appmngr.h>
#endif	// _APPMNGR_H_

#include <clientconfig.h>

extern "C" {
#include	<personcl.h>
}

#define	STRCLNT	"cl"

char *GetMyPath( void );


//
//	Variaveis globais
//

// para internacionalizacao
AppParmsMngr	*_pcInter = new AppParmsMngr( "LBW", "LBSCLNT", GetMyPath() );


/***
    DllEntryPoint Function
    Handles the DLL entry end exit

    Parameters:
    	- hInstDLL	-> handle of DLL module
    	- fdwReason	-> why function was called
    	- lpvReserved	-> reserved; must be NULL

    Return:
    	-

    Comments:
    	-

***/
BOOL WINAPI
#ifdef __MFC	// o entry point eh no InitInstance de MFC
MyDllMain( HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved )
#else
DllMain( HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved )
#endif
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

    switch( fdwReason ){
    case DLL_PROCESS_ATTACH:	// $$$ A DLL ESTAH SENDO CARREGADA POR ALGUM PROCESSO

 		wVersionRequested = MAKEWORD( 1, 1 );
 		err = WSAStartup( wVersionRequested, &wsaData );

		LBSC_ClientConfig::Init();
		if ( stricmp(::GetType(), STRCLNT) != 0 ) {
			if( _pcInter->BuildStatus == CHECKISOK ){
//				_pcInter->AppMsgBox( NULL, "LBCLIENTMSG_PERSONERROR", "LBCLIENTMSG_ERRORTITLE", MB_ICONEXCLAMATION | MB_OK );
			} 
			else {
				MessageBox(NULL,"Esta c�pia n�o est� personalizada como c�pia cliente", "Erro", MB_OK | MB_ICONEXCLAMATION);
			}

			return FALSE;
		}

		LBSC_ClntNet::SetClientInfo();

    	return( TRUE );		// $$$ ESTE VALOR EH USADO PELO WINDOWS

    case DLL_THREAD_ATTACH:		// $$$ O PROCESSO CORRENTE ESTAH CRIANDO UM THREAD
    	return( TRUE );		// $$$ ESTE VALOR NAO EH USADO PELO WINDOWS

    case DLL_THREAD_DETACH:		// $$$ UM THREAD ESTAH TERMINANDO
    	return( TRUE );		// $$$ ESTE VALOR NAO EH USADO PELO WINDOWS

    case DLL_PROCESS_DETACH:	// $$$ A DLL ESTAH SENDO LIBERADA POR ALGUM PROCESSO

		WSACleanup();

		LBSC_ClntNet::CleanUp();
    	return( TRUE );		// $$$ ESTE VALOR NAO EH USADO PELO WINDOWS

    }
    return( FALSE );
}


void
MyMsgBox(HWND , LPCTSTR , LPCTSTR ,	UINT )
{
	// a principio nao faco nada...
}


char *
GetMyPath( void )
{
   static char szPath [ 255 + 1 ];
   static int iFirst = 1;
   if( iFirst ){
	   HMODULE  hMod = GetModuleHandle( "LBS.DLL" ); 
	   szPath [ 0 ] = '\0';
	   GetModuleFileName( hMod, szPath, 255 );
	   for( int i = strlen( szPath ) - 1; i >= 0; i-- ) {
	      if( szPath[ i ] == '\\' || szPath[ i ] == '/' ) {
	         szPath[ i ] = '\0';
	         i = 0;
	      }
	   }
	   iFirst = 0;
	}
	return szPath;
}


