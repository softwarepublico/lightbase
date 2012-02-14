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
// Module: DATACL.H
//	LBSC_Data class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 28/09/94
//


#ifndef	_DATACL_H_
#define	_DATACL_H_

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_DATECL_H_
#include	<datecl.h>
#endif
#ifndef	_TIMECL_H_
#include	<timecl.h>
#endif
#ifndef	_BINARY_
#include	<binarycl.h>
#endif
#ifndef	_REFERENCE_
#include	<refercl.h>
#endif

class	LBSC_Field;
class	LBSC_RepSort;


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class CritDataManager : public CritSectManager
{
	void CritSectLog( char *szMsg, char *szFile, int iLine, int iNum );
	unsigned long GetCritSectMask();
	void SetCritSectMask( unsigned long );
	BOOL OrderedDependents();
};
extern CritDataManager _csDataMan;

// classe para tratamento de regioes criticas
class	C_GlobalDataCritSect : public C_CritSect<2>	// 2 = numero de regioes criticas
{
public:
	C_GlobalDataCritSect()
	{
	}
};

extern	C_GlobalDataCritSect	*_pcGlobalDataCritSect;

// possiveis status para um objeto LBSC_Data
typedef enum _DATASTATUS { DATA_OK = 0, DATA_HOLE } DATASTATUS;

class _LBSCLASS LBSC_Data
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_DumbParser;
	friend	class	_LBSCLASS LBSC_Field;
	friend	class	_LBSCLASS LBSC_Record;
	friend	class	_LBSCLASS LBSC_Session;
	friend	class			  LBSC_OLSort;
	friend	class			  LBSC_RepSort;

	private:
		BOOL		bModified;
		LBSC_Field	*pfOwnerField;	// ponteiro para o campo dono do dado.
									// usado para que o dado possa enviar
									// notificacoes para o campo dono.
		long		lDataSize;
		void		*pbData;		// se for NULL indica que o dado nao possui valor definido
		int			iSlotSize;		// tamanho do slot em bytes
		int			iDataType;
		int			iRepetNum;		// indice do dado na lista (util apenas para os dados que 
									// estiverem na lista de deletados)
		DATASTATUS	iStatus;		// status do objeto (vide enum acima)
		int			iUpdateSequenceNumber;	// numero de sequencia de atualizacao da repeticao em um field.
											// eh um numero que indica a ordem de atualizacao de uma repeticao
											// (quem foi atualizada por ultimo, quem foi primeiro, etc.)


		const void	*GetConstData();
		BOOL		IsPermOk( BYTE );
		void		SetError( int );
		void		DisableData();
		BOOL		IsEnabled();

		// operadores (eram publicos, mas vieram para a area privada para
		// (proibir o uso por causa do RPC)
		void operator = ( long );
		void operator = ( double );
		void operator = ( char * );
		void operator = ( void * );
		void operator = ( C_Date & );
		void operator = ( C_Time & );
		void operator = ( LBSC_Binary & );
		void operator = ( LBSC_Reference & );
		void operator = ( BYTE );
		void operator = ( short int );
		void operator = ( float );

		LBSC_Data& operator = ( LBSC_Data &b );

		operator long ( void );
		operator double ( void );
		operator char* ( void );
		operator void* ( void );
		operator LBSC_Binary* ( void );
		operator LBSC_Reference* ( void );
		operator JulTy ( void );
//		operator ClockTy ( void );  // $$$ Nao pode ser implementado
					    // $$$ porque ClockTy e JulTy sao
					    // $$$ definidos como unsigned long
					    // $$$ e entao o compilador acusa
					    // $$$ redeclaracao de operador
		operator BYTE ( void );
		operator short int ( void );
		operator float ( void );

	public:
					LBSC_Data( LBSC_Field *, int, void *pvData = NULL, long l = 1L );
					~LBSC_Data();
		void		*GetData();
		long		GetSize();
		int			GetType();
		int			ModifyData( void *, long = -1L );
		int			Compare( LBSC_Data *, int );
		LBSC_Data	*Duplicate();
		int 		Write( C_File * );
		int 		Read( C_File * );
		int 		IsOk( void );
		LBSC_Field	*GetOwnerField();
		void		SetStatus( DATASTATUS );
		DATASTATUS	GetStatus();
		int			GetUpdateSequenceNumber();
		BOOL		IsModified();
		void		SetModified( BOOL );
		int			GetRepetNum() { return iRepetNum; };
		char		*ToString();
		void		TryConvertToTer();
};

class	C_DataCritSect
{
	int			iLastSectUsed;
	LBSC_Data	*pObj;

public:
	C_DataCritSect( LBSC_Data *pObjPar, int iNumCritSect, char *szFile, int iLinePar  )
	{
		if( _pcGlobalDataCritSect ){
			_pcGlobalDataCritSect->EnterCriticalSection( iNumCritSect, (DWORD) pObjPar, szFile, iLinePar );
			iLastSectUsed = iNumCritSect;
			pObj = pObjPar;
		}
	}
	~C_DataCritSect()
	{
		if( _pcGlobalDataCritSect ){
			_pcGlobalDataCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
	void EnterCriticalSection()
	{
		if( _pcGlobalDataCritSect ){
			_pcGlobalDataCritSect->EnterCriticalSection( iLastSectUsed, (DWORD) pObj );
		}
	}
	void LeaveCriticalSection()
	{
		if( _pcGlobalDataCritSect ){
			_pcGlobalDataCritSect->LeaveCriticalSection( iLastSectUsed );
		}
	}
};


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _DATACL_H_


