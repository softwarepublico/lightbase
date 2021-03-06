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
// Module: MONITCL.H
//	C_Monitor class definition file
//
// Programmer:	Adriano Sergio*
//
// Last revision: 17/05/94
//

#ifndef	_MONITCL_
#define	_MONITCL_

// includes
#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif

// defines
#define	DEFAULTLINELEN		80
#define	DEFAULTNUMLINES		100
#define	MONITORCLASSNAME	"Monitor__Class"
#define	MONITOR_CBCLSEXTRA	(0)
#define	MONITOR_CBWNDEXTRA	(sizeof(this)) //sizeof( C_Monitor* )
#define	MONITOR_PTOBJ		(0)
#define	FIRSTEDITLINE		0

class	C_Monitor{

	private:

		// privated attributes

		int		iX;
		int		iY;
		int		iWidth;
		int		iHeight;
		int		iLineLen;
		int		iNumLines;
		BOOL		bSuccessful;
		HWND		hWndParent;
		HWND		hWndMonitor;
		HINSTANCE	hInstance;
		HLOCAL		hMonitorMem;	// edit control memory
		HLOCAL		hMonitorBuf;	// auxiliary buffer
		int		iCurrLine;
		int		iNumEditLines;
		static	int	iNumObj;

		// privates methods
		BOOL		RegisterMonitorClass();


	public:

		// public attributes


		// public methods

		C_Monitor( HWND, HINSTANCE, int, int, int, int,
			int a = DEFAULTLINELEN, int  b = DEFAULTNUMLINES );
		~C_Monitor();
		BOOL	Successful();
		BOOL	Show();
		BOOL	Hide();
		BOOL	SetMemory();
		void	Clear();
		BOOL	Write( char* );
		void	CopyToClp();
};


#endif	// _MONITCL_

