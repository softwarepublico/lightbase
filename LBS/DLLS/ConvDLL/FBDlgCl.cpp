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

// FBDlgCl.cpp : implementation file
//

#include "stdafx.h"
#include "ConvDLL.h"
#include "FBDlgCl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C_FeedBackDlg dialog


C_FeedBackDlg::C_FeedBackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C_FeedBackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C_FeedBackDlg)
	//}}AFX_DATA_INIT
	Create( C_FeedBackDlg::IDD );
//	ShowWindow( SW_SHOW );
	CenterWindow();
}


void C_FeedBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C_FeedBackDlg)
	DDX_Control(pDX, IDC_MSGSTATIC, m_MsgStatic);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C_FeedBackDlg, CDialog)
	//{{AFX_MSG_MAP(C_FeedBackDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_FeedBackDlg message handlers
