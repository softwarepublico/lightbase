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

//
// Module: BNETLIST.H
//	LBSC_BaseNetList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 31/07/96
//


#ifndef	_BNETLIST_H_
#define	_BNETLIST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_BaseNetList : public LBSC_DList<TBaseNetInfo>
{
	public:
		int	Save( C_File &cf )
		{
			if( !cf.IsOpen() ){
				// nao deu
				return( !OK );
			}

			// gravar o numero de elementos
			if( cf.Write( &iNumElem, sizeof( iNumElem ) ) != OK ){
				return( !OK );
			}

			// gravar os elementos
			for( int i = 0; i < iNumElem; i++ ){
				if( (*this)[ i ]->Save( cf ) != OK ){
					return( !OK );
				}
			}
			return( OK );
		}

		int	Load( C_File &cf )
		{
			if( !cf.IsOpen() ){
				// nao deu
				return( !OK );
			}

			// deletar os elementos da lista
			if( DelAll() != OK ){
				return( !OK );
			}

			// ler o numero de elementos
			int	iNum;
			if( cf.Read( &iNum, sizeof( iNum ) ) != OK ){
				return( !OK );
			}

			// ler os elementos
			for( int i = 0; i < iNum; i++ ){
				TBaseNetInfo	*pAux = new TBaseNetInfo;

				if( !pAux ){
					// erro
					return( !OK );
				}
				if( pAux->Load( cf ) != OK ){
					return( OK );
				}

				if( Add( pAux, TAIL ) != OK ){
					// erro
					return( !OK );
				}
			}
			return( OK );
		}
};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _BNETLIST_H_

