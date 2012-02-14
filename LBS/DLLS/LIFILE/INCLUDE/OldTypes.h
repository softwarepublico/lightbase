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

