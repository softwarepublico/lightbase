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

