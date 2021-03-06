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

#ifndef _LB3_
#define _LB3_

#ifndef	_RECFILCL_
#include	<recfilcl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif

typedef	struct _sCountLockControl
{
	int		iCountLock;
	HANDLE	hLockThread;
	HANDLE	hCountLockEvent;

	_sCountLockControl()
	{
		iCountLock = 0;
		hLockThread = NULL;
		hCountLockEvent = NULL;
	}
} TCountLockControl;

DWORD WINAPI CountLockControlFunction( LPVOID );

class _LBSCLASS C_LB3 : public C_RecordFile {
	friend	DWORD WINAPI CountLockControlFunction( LPVOID );

	private:
		int	PrivReleaseCount( int );
		int	StartCountLockTimer( int );
		int	StopCountLockTimer( int );

	public:
		TStructHeadRec		tsHead;
		long				iNumSlots;
		long				iNumCounters;
		TCountLockControl	*pclCountControl;	// array de estruturas de controle dos contadores.

		C_LB3( char *, char *, const char * = NULL, int = SH_DENYNONE, int = 0, int = 0 );
		C_LB3();
		~C_LB3();
		int Open( char *, char *, const char * = NULL, int = SH_DENYNONE, int = 0, int = 0 );
		int	LB3_LockHead( TStructHeadRec * );
		int	LB3_ReleaseHead( TStructHeadRec * );
		int	SeekOnSlot( int );
		int	R_WriteHead( void * );
		int	R_ReadHead( void * );
		int	LockCount( int, BOOL = FALSE );
		int	ReleaseCount( int );
		int SaveCount( int iCountIndex, long lCount );
		int LoadCount( int iCountIndex, long &lCount );
		int IncCount( int iCountIndex, long lCount, long &lRet );
		int DecCount( int iCountIndex, long lCount, long &lRet );

		// overload de metodos virtuais
		void Encrypt( void *, char *, size_t );
		void Decrypt( void *, char *, size_t );

};

typedef	struct _sCountLockThreadInfo
{
	C_LB3	*pObj;
	int		iCountIndex;
	HANDLE	hCountLockEvent;
	DWORD	dwThreadId;

	_sCountLockThreadInfo()
	{
		pObj = NULL;
		iCountIndex = 0;
		hCountLockEvent = NULL;
		dwThreadId = 0;
	}
} TCountLockThreadInfo;

#endif
