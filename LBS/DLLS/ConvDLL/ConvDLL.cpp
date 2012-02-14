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

// ConvDLL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ConvDLL.h"
#include <critsect.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvDLLApp

BEGIN_MESSAGE_MAP(CConvDLLApp, CWinApp)
	//{{AFX_MSG_MAP(CConvDLLApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvDLLApp construction

CConvDLLApp::CConvDLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	// desligar o uso de regioes criticas.
	//	_bCritSectEnabled = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConvDLLApp object

CConvDLLApp theApp;
