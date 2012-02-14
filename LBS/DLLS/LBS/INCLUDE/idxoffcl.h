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



#ifndef	_IDXOFF_H_
#define	_IDXOFF_H_

#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif

class	C_IDXOFF
{
private:
	C_RecordFile	cfFile;

public:
	C_IDXOFF();
	~C_IDXOFF();
	int		CreateIndex( char * );
	int		CloseIndex();
	BOOL	IsOpen();
	int		OpenIndex( char * );
	int		GetFirstGroupOfBits( int * );
	int		GetNextGroupOfBits( int * );
	int		GetGroupOfBits( long, int * );
	int		AddBitValue( long );
	int		DelBitValue( long );
	long	GetNumRecordsLogged();

};

#endif // _IDXOFF_H_

