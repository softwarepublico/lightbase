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

/***
	Class LockStruct

***/


#ifndef	_LOCKSTRUCT_H_
#define	_LOCKSTRUCT_H_

class	C_File;

class LockStruct{
	public:
		int 	iCount;
		int 	iPos;
		int 	iSize;
		BOOL	bTryUse;	// alguem tentou usar a regiao bloqueada depois que o lock foi feito
		C_File	*pcfFile;

		LockStruct( C_File *pcf, int iPosPar, int iSizePar )
		{
			iCount = 0;
			iPos = iPosPar;
			iSize = iSizePar;
			pcfFile = pcf;
			bTryUse = FALSE;
		};

		LockStruct	*Duplicate(){ return NULL; }
		int		Compare( LockStruct *, int ){ return 0; };
};


#endif	// _LOCKSTRUCT_H_

