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
// Module: OLSORT.H
// Description:
//
//	LBSC_OLSort class definition file.
//
// Programmer:	Adriano Sergio R. de Souza*
//
// Last update: 25/01/96
//

#ifndef	_OLSORT_H_
#define	_OLSORT_H_

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
#ifndef	_BASECL_H_
#include	<basecl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define	MAXDESCRIPTORSIZE	(4096)		// tamanho maximo da string de descricao para o
						// objeto comparador
#define	FISIC_OL_OK		(0xFFFFFFFF)	// valor que indica sucesso na ordenacao da LO
						// fisica.

class	LBSC_Base;
class	LBSC_Session;

class LBSC_OLSort : SortObject, public LBSC_Error			// SortObject eh uma classe feita por Jarbas Campos
{
	friend	class	_LBSCLASS LBSC_Session;
	friend	class	_LBSCLASS LBSC_Base;

	private:
		LBSC_OcList		*polNewOcList;				// LO resultante da ordenacao
		LBSC_OcList		*polOldOcList;				// LO a ser ordenada.
		LBSC_Base		*pOwnerBase;				// Ponteiro para a base que estah usando o sort
		char			szOrigExpr[ (MAXDESCRIPTORSIZE/4) ];	// copia da expressao original de sort
		char			szDescriptor[ MAXDESCRIPTORSIZE ];	// descritor resultante do processo de parsing
		Comparator		cComp;					// objeto para comparacao. Implementado por Jarbas Campos
		int			iSizeOfKey;				// tamanho de uma chave depois de serializada
		int			iNumFields;				// quantidade de campos que compoem uma chave
		TControlRec		tcrHead;				// registro de LB1
		BOOL			bFinished;				// informacao de controle para verificar
										// se a base ja' chegou ao fim
		BOOL			bSecureStatus;				// status de seguranca da ordenacao da LO fisica
		BOOL			bCopy;					// indica se a ordenacao vai ser feita em uma copia da LO original
		UINT			uiIdArray[ (MAXDESCRIPTORSIZE/4) ];	// array contendo os id's dos campos que devem formar uma chave
		const LBSC_Ticket	*pTicket;				// ticket para usar metodos de base e de session


		void		*GetFirstOccurrence();
		void		*GetNextOccurrence();

	public:
				LBSC_OLSort( char *, LBSC_OcList *, LBSC_Base *, const LBSC_Ticket *, BOOL, BOOL = FALSE );
				~LBSC_OLSort();
		LBSC_OcList	*StartSort();
		int		Compare( void *, void * );
		BOOL		GetData( void *& );
		void		PutData( void * );
};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _OLSORT_H_


