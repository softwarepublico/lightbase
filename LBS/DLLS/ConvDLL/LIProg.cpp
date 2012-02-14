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
//  LIGHT-INFOCON
//
//  Modulo        : LIProg.cpp
//  Descricao     : Implementa��o do control progress bar
//					O control progress bar foi necessario pois
//					a versao COMMCTRL nao funcionava em Win32s.
//					Alem disso, o control aqui implementado eh
//					mais bonitinho ....:-)
//  Programadores : Alessandro Araujo Jatob�
//  Alteracoes    :
//

#include	<CDLLLIProg.h>
#include	<stdio.h>

#define	BLUE			RGB( 0, 0, 255 ) 
#define	WHITE			RGB( 255, 255, 255 ) 
#define	PROGRESSCLASS	"LIProgressBar"

/******************/
class LI_ProgressBar
{
	public:
		int		iStyle;
		int		iMin, iMax;
		int		iPos, iStep;
		HBRUSH	hBlueBrs;
		
		LI_ProgressBar( void );
		~LI_ProgressBar( void );
		void Paint( HWND hWnd, HDC hDC );
		void StepIt( HWND );
		void SetStep( int iNewStep ) { iStep = iNewStep; }
		void SetPos( HWND hWnd, int iNewPos );
		void SetRange( HWND hWnd, int iNewMin, int iNewMax );
};

/******************/
LI_ProgressBar::LI_ProgressBar( void )
{
	iStyle = 0;
	iMin = 0;
	iMax = 100;
	iPos = 0;
	iStep = 1;
	hBlueBrs = CreateSolidBrush( BLUE ^ WHITE );
}

/******************/
LI_ProgressBar::~LI_ProgressBar( void )
{
	if( hBlueBrs ){
		DeleteObject( hBlueBrs );
	}
}

/******************/
void
LI_ProgressBar::Paint( HWND hWnd, HDC hDC )
{
	RECT	sRect;
	char	szAux [ 10 ];

	GetClientRect( hWnd, &sRect );

	float	fPer = ((float)iPos / (float)( iMax - iMin ) );
	int		iRight = (int)((float)sRect.right * fPer );

	sprintf( szAux, "%d%%", (int) ( 100 * fPer ) );

	COLORREF hOldColor = SetTextColor( hDC, RGB( 0, 0, 128 ) );
	
	DrawText( hDC, szAux, strlen( szAux ), &sRect, 
		DT_VCENTER | DT_CENTER | DT_SINGLELINE );	

	HBRUSH hOldBrs = (HBRUSH)SelectObject( hDC, hBlueBrs );
	HPEN hOldPen = (HPEN)SelectObject( hDC, GetStockObject( NULL_PEN ) );

	int iOldROP2 = SetROP2( hDC, R2_XORPEN );

	Rectangle( hDC, 0, 0, iRight + 1, sRect.bottom + 1 );

	SetROP2( hDC, iOldROP2 );
	SetTextColor( hDC, hOldColor );
	SelectObject( hDC, hOldBrs );
	SelectObject( hDC, hOldPen );
}

/******************/
void
LI_ProgressBar::StepIt( HWND hWnd )
{
	if( iPos + iStep <= iMax ){
		iPos += iStep;
		InvalidateRect( hWnd, NULL, TRUE );
		UpdateWindow( hWnd );
	}
}

/******************/
void 
LI_ProgressBar::SetPos( HWND hWnd, int iNewPos )
{
	if( iNewPos >= iMin && iNewPos <= iMax ){
		iPos = iNewPos;
		InvalidateRect( hWnd, NULL, TRUE );
		UpdateWindow( hWnd );
	}
}


/******************/
void
LI_ProgressBar::SetRange( HWND hWnd, int iNewMin, int iNewMax )
{
	if( iNewMax > iNewMin ){
		if( iMax != iNewMax || iMin != iNewMin ){
			iMax = iNewMax;
			iPos = iMin = iNewMin;
			InvalidateRect( hWnd, NULL, TRUE );
			UpdateWindow( hWnd );
		}
	}
}


/*************************************/
static LI_ProgressBar*
GetPointer( HWND hWnd )
{
	if ( !IsWindow( hWnd ) )
		return NULL;

	if( sizeof( LI_ProgressBar* ) == sizeof( LONG ) ){
		return (LI_ProgressBar*) GetWindowLong( hWnd, 0 );
	}
	return (LI_ProgressBar*) GetWindowWord( hWnd, 0 );
}

/**************/
LRESULT CALLBACK 
ProgressProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT	ps;
	LI_ProgressBar	*pcpbProg = NULL;

	switch( uMsg ){
	case WM_CREATE:
		pcpbProg = new LI_ProgressBar;
		if( pcpbProg ){
			SetWindowLong( hWnd, 0, (long)pcpbProg );
		}
		break;
	case WM_DESTROY:
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			delete pcpbProg;
		}
		break;
	case WM_PAINT:
		BeginPaint( hWnd, &ps );
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			pcpbProg->Paint( hWnd ,ps.hdc );
		}
		EndPaint( hWnd, &ps );
		break;
	case PBM_SETSTEP:
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			pcpbProg->SetStep( (int) wParam );
		}
		break;
	case PBM_SETPOS:
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			pcpbProg->SetPos( hWnd, (int) wParam );
		}
		break;
	case PBM_STEPIT:
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			pcpbProg->StepIt( hWnd );
		}
		break;
	case PBM_SETRANGE:
		pcpbProg = GetPointer( hWnd );
		if( pcpbProg ){
			pcpbProg->SetRange( hWnd, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
		}
		break;
	}
	return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
}

/**************/
void
RegisterProgressClass( HINSTANCE hInst )
{
	WNDCLASS    wc;

	wc.style         = CS_GLOBALCLASS | CS_DBLCLKS;
	wc.lpfnWndProc   = ProgressProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = sizeof( LI_ProgressBar * );
	wc.hInstance     = hInst;
	wc.hIcon         = NULL;
	wc.hCursor       = NULL;
	wc.hbrBackground = CreateSolidBrush( RGB( 255, 255, 255 ) );
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = PROGRESSCLASS;

	RegisterClass( &wc );
}

