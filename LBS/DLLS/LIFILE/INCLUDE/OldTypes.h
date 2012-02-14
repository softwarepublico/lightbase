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

// este arquivo define estruturas que sao usadas pelos arquivos do LBS
// que estao no formato velho.


#ifndef	_OLDTYPES_H_
#define	_OLDTYPES_H_

#include	<lbstypes.h>

typedef	struct	_sOldControlRecHead		// cabecalho de LB1
{
	BYTE			bMagicNumber;
	TControlRecHead	tcrHead;

} TOldControlRecHead;

typedef	struct	_sOldStructHeadRec {	//  cabecalho de LB3
	BYTE			bMagicNumber;
	TStructHeadRec	tshRec;

	static long SizeOf( int iSlotNum )
	{
		return sizeof( _sOldStructHeadRec ) + sizeof( SlotPointer ) * ( iSlotNum > 0 ? (iSlotNum - 1) : 0 );
	}
	static _sOldStructHeadRec *Alloc( int iSlotNum )
	{
		_sOldStructHeadRec	*p = (_sOldStructHeadRec*) new char [ _sOldStructHeadRec::SizeOf( iSlotNum ) ];
		if( p ){
			memset( (void*) p, 0, _sOldStructHeadRec::SizeOf( iSlotNum ) );
		}
		return p;
	}
	static void Free( _sOldStructHeadRec *pshrHead )
	{
		if( pshrHead ){
			delete (char*) pshrHead;
		}
	}

} TOldStructHeadRec;



#endif	// _OLDTYPES_H_

