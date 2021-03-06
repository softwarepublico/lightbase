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
// Module: LOGLIST.H
//	LBSC_LogList class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 01/02/96
//


#ifndef	_LOGLIST_H_
#define	_LOGLIST_H_

#ifndef	_LBSTEMPLATE_H_
#include	<lbstempl.h>
#endif
#ifndef	_SESSCL_H_
#include	<sesscl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_SESSLIST_H_
#include	<sesslist.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

extern	LBSC_SessionList	*_clSessList;	// lista das sessoes abertas

class _LBSCLASS LBSC_LogList : LBSC_DList<TLoginInfo>
{
	public:
		BOOL		bIsDying;	// indica se o destrutor da lista esta'
						// sendo executado

				LBSC_LogList() : LBSC_DList<TLoginInfo>()
				{
					bIsDying = FALSE;
				};
				~LBSC_LogList()
				{
					EnterCriticalSection( 0 );
						bIsDying = TRUE;
					LeaveCriticalSection( 0 );
				};
		LBSC_DList<TLoginInfo>::NumElem;
		LBSC_DList<TLoginInfo>::Next;
		LBSC_DList<TLoginInfo>::Previous;
		LBSC_DList<TLoginInfo>::First;
		LBSC_DList<TLoginInfo>::Last;
		LBSC_DList<TLoginInfo>::Current;
		LBSC_DList<TLoginInfo>::Nth;
		LBSC_DList<TLoginInfo>::Search;
		LBSC_DList<TLoginInfo>::Find;
		LBSC_DList<TLoginInfo>::Add;
		LBSC_DList<TLoginInfo>::Update;
		LBSC_DList<TLoginInfo>::Del;
		LBSC_DList<TLoginInfo>::DelAll;
		LBSC_DList<TLoginInfo>::Refresh;
		LBSC_DList<TLoginInfo>::GetCurrentIndex;
		LBSC_DList<TLoginInfo>::operator[];

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
				TLoginInfo	*ptlAux = new TLoginInfo;

				if( !ptlAux ){
					// erro
					return( !OK );
				}
				if( ptlAux->Load( cf ) != OK ){
					return( OK );
				}

				// procurar na lista de sessoes para ver se
				// o ptlAux->pOwnerSession eh valido.
				if( !_clSessList && _clSessList->Find( ptlAux->pOwnerSession, CMPSESSIONPOINTER ) ){
					// nao achamos.
					ptlAux->pOwnerSession = NULL;
				}
				if( Add( ptlAux, TAIL ) != OK ){
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


#endif // _LOGLIST_H_

