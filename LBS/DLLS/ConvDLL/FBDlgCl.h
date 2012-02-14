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

// FBDlgCl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C_FeedBackDlg dialog
#ifndef	_FEEDBACKDLG_H_
#define	_FEEDBACKDLG_H_

//#include	"resource.h"
//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by ConvDLL.rc
//
#define IDS_MSG_CONVERTINGBASE          1
#define CONVM_OK                        2
#define CONVEM_CONTROLNOTFOUND          3
#define CONVEM_CONTROLCONVERROR         4
#define CONVEM_CONTROLOPENERROR         5
#define CONVEM_ERRCONV                  6
#define CONVEM_UNKNOWNBASEVERSION       7
#define CONVEM_NOBASESTOCONV            8
#define CONVEM_FILEREADERR              9
#define CONVEM_NOTTEMPPATH              10
#define CONVEM_NOTNEWPATH               11
#define CONVEM_NOTCREATED               12
#define CONVEM_ALLOCERR                 13
#define CONVEM_FILEIOERR                14
#define CONVEM_FATALERR                 15
#define CONVEM_FILERENERR               16
#define CONVEM_FILEMOVEERR              17
#define CONVEM_FILECREATERR             18
#define IDS_MSG_CONVERTINGCONTROLFILE   19
#define CONVEM_FILEOPENERR              20
#define IDS_MSG_UPDATINGCONTROLFILE     21
#define IDD_FEEDBACKDLG                 130
#define IDC_PROGRESS                    1003
#define IDC_MSGSTATIC                   1004

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_3D_CONTROLS                     1
#define _APS_NEXT_RESOURCE_VALUE        130
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1003
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

class C_FeedBackDlg : public CDialog
{
// Construction
public:
	C_FeedBackDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C_FeedBackDlg)
	enum { IDD = IDD_FEEDBACKDLG };
	CStatic	m_MsgStatic;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_FeedBackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C_FeedBackDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _FEEDBACKDLG_H_

