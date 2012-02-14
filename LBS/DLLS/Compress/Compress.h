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

	Defini��o da classe Compactador
*/

#include "aldefs.h"
#include "arclib.h"
#include "memstore.h"					  
#include "grenengn.h"

#include "Defcompr.h"

/*class	My_ALMemory : public ALMemory
{
public:
	My_ALMemory(){};
	~My_ALMemory(){};
};
*/

class _COMPRESSCLASS Compactador {
/* Atributos */
//	ALMemory	almIn;	/* Classe que encapsula os dados a serem comprimidos */
//	ALMemory	almOut; /* Classe que encapsula o resulatdo dos dados comprimidos */
//	ALGreenleafEngine	algEngine; /* Classe respons�vel pela compress�o */
/* M�todos Privados */
	void PreenchealmIn(char _huge *psBuffer, int iSizeBuffer);
public:
	Compactador();
	~Compactador(){};
	int Compress(char _huge *psBufIn, unsigned char **psBufOut, int iSizeBufIn);
	int Uncompress(char _huge *psBufIn, unsigned char **psBufOut, int iSizeBufIn);
	void LiberaBufOut(unsigned char **psBuf);
};
