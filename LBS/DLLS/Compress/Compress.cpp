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

/*
	Compress.h
	Programador: Katyusco de Farias Santos

	Implementa��o da Classe Compactador
  
*/

#include "Compress.h"
#include <windows.h>
				  
/* 
	Entry Point da DLL 

*/								  
BOOL WINAPI
DllMain( HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	switch( fdwReason ){			  
	case DLL_PROCESS_ATTACH:	// A DLL ESTAH SENDO CARREGADA POR ALGUM PROCESSO
	case DLL_THREAD_ATTACH:		// O PROCESSO CORRENTE ESTAH CRIANDO UM THREAD
	case DLL_THREAD_DETACH:		// UM THREAD ESTAH TERMINANDO
	case DLL_PROCESS_DETACH:	// A DLL ESTAH SENDO LIBERADA POR ALGUM PROCESSO
	return( TRUE );
	}
	return( TRUE );
}

/*
Construtor da classe
*/
Compactador::Compactador( )
{

}

/*
Construtor da classe
*/
void
Compactador::PreenchealmIn( char _huge *psBuffer, int iSizeBuffer )
{
	/* Aloca poteiros */
	/*almIn.Create( );
	memcpy(almIn.mpcUserBuffer, psBuffer, iSizeBuffer);
	almIn.muUserBufferSize = iSizeBuffer;*/
}

/*
Fun��o:
	Comprime uma tira de bytes, devolvendo uma outra tira de bytes como
resultado.
Par�metros:
	char *psBufIn - Apontador para a tira de bytes a ser comprimida;
	char **psBufOut - Ender�o de um apontador para um outro buffer 
	que cont�m o resultado da compress�o de psBufIn;
	int iSizeBufIn - Tamanho de psBufIn;
Retorno:
	Retorna o n�mero de bytes do buffer comprimido(psBufIn)
caso a compress�o tenha ocorrido com sucesso, sen�o retorna 0 (zero).
*/
int
Compactador::Compress (char _huge *psBufIn, unsigned char **psBufOut, int iSizeBufIn)
{
	if ( !psBufIn ) {
			return 0; 
	}
	/* Coloca num objeto de mem�ria o psBufIn */
	/*PreenchealmIn( (char _huge *)psBufIn, iSizeBufIn );*/
	ALMemory		almIn( "", (char _huge *)psBufIn, 
								iSizeBufIn );
	ALMemory		almOut;

	ALGreenleafEngine	algEngine( 2 );

	if  ( algEngine.Compress(almIn, almOut) != AL_SUCCESS ) {
		return 0;
	}
	*psBufOut = (unsigned char *)new char[almOut.muUserBufferSize];
	if ( !*psBufOut ) {
		return 0;
	}
	memcpy( *psBufOut, almOut.mpcUserBuffer, almOut.muUserBufferSize );
	return almOut.muUserBufferSize;
}

/*
Fun��o:
	Descomprime uma tira de bytes, devolvendo uma outra tira de bytes como
resultado.
Par�metros:
	char *psBufIn - Apontador para a tira de bytes a ser descomprimida;
	char **psBufOut - Ender�o de um apontador para um outro buffer 
	que cont�m o resultado da descompress�o de psBufIn;
	int iSizeBufIn - Tamanho de psBufIn;
Retorno:
	Retorna o n�mero de bytes do buffer descomprimido(psBufIn)
caso a descompress�o tenha ocorrido com sucesso, sen�o retorna 0 (zero).
*/
int
Compactador::Uncompress (char _huge *psBufIn,unsigned char **psBufOut, int iSizeBufIn)
{
	if ( !psBufIn ) {
		return(0); 
	}
	/*PreenchealmIn( (char _huge *)psBufIn, iSizeBufIn );*/
	ALMemory		almIn( "", (char _huge *)psBufIn, 
								iSizeBufIn );
	ALMemory		almOut;

	ALGreenleafEngine	algEngine( 2 );

	if ( algEngine.Decompress(almIn, almOut, iSizeBufIn) != AL_SUCCESS) {
		return(0);
	}
	*psBufOut = (unsigned char *)new char[almOut.muUserBufferSize];
	if ( !*psBufOut ) {
		return(0);
	}
	memcpy( *psBufOut, almOut.mpcUserBuffer, almOut.muUserBufferSize );
	return almOut.muUserBufferSize;
}

void
Compactador::LiberaBufOut(unsigned char **psBuf)
{
	if ( *psBuf ) {
		delete (*psBuf);
	}
}
