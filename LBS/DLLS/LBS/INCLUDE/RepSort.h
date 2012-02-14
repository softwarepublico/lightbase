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


