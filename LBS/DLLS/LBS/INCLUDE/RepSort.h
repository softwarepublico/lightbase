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
// Module: REPSORT.H
// Description:
//
//	LBSC_RepSort class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 13/07/98
//

#ifndef	_REPSORT_H_
#define	_REPSORT_H_

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#ifndef	_SORT
#include	<sort.h>
#endif
#ifndef	_COMPARATOR
#include	<comparator.h>
#endif
#ifndef _LBSERRCL_H_
#include	<lbserrcl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class LBSC_Field;

class LBSC_RepSort : SortObject, public LBSC_Error	// SortObject eh uma classe feita por Jarbas Campos
{
	private:
		int				iIndAtual;					// indice atual no vetor acima; util para o getdata
		int				iSizeOfKey;					// tamanho de uma chave depois de serializada
		char			szDescriptor[ 512 ];		// descritor para o SortObject
		Comparator		cComp;						// objeto para comparacao. Implementado por Jarbas Campos
		LBSC_Field		*pSortField;				// campo a ser ordenado.

	public:
				LBSC_RepSort( LBSC_Field *pSortFieldPar );
				~LBSC_RepSort();

		BOOL		StartSort();
		int			Compare( void *, void * );
		BOOL		GetData( void *& );
		void		PutData( void * );
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _REPSORT_H_


