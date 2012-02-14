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

/*
	Compress.h
	Programador: Katyusco de Farias Santos

	Implementação da Classe Compactador
  
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
Função:
	Comprime uma tira de bytes, devolvendo uma outra tira de bytes como
resultado.
Parâmetros:
	char *psBufIn - Apontador para a tira de bytes a ser comprimida;
	char **psBufOut - Enderço de um apontador para um outro buffer 
	que contém o resultado da compressão de psBufIn;
	int iSizeBufIn - Tamanho de psBufIn;
Retorno:
	Retorna o número de bytes do buffer comprimido(psBufIn)
caso a compressão tenha ocorrido com sucesso, senão retorna 0 (zero).
*/
int
Compactador::Compress (char _huge *psBufIn, unsigned char **psBufOut, int iSizeBufIn)
{
	if ( !psBufIn ) {
			return 0; 
	}
	/* Coloca num objeto de memória o psBufIn */
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
Função:
	Descomprime uma tira de bytes, devolvendo uma outra tira de bytes como
resultado.
Parâmetros:
	char *psBufIn - Apontador para a tira de bytes a ser descomprimida;
	char **psBufOut - Enderço de um apontador para um outro buffer 
	que contém o resultado da descompressão de psBufIn;
	int iSizeBufIn - Tamanho de psBufIn;
Retorno:
	Retorna o número de bytes do buffer descomprimido(psBufIn)
caso a descompressão tenha ocorrido com sucesso, senão retorna 0 (zero).
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
