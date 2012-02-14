/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o 
título "LICENCA.txt", junto com este programa, se não, escreva para a Fundação do 
Software Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/



#include "arclib.h"
#pragma hdrstop

#define STRICT
#include <windows.h>
#include "algauge.h"

//
// class ALGauge
//
// DESCRIPTION
//
//  This class is confined entirely to this file. To use this control,
//  you need to call the initialization routine.  The initialization 
//  routine registers the gauge class.  Whenever a new gauge object
//  is created, a WM_CREATE message is sent to the window procedure.
//  WM_CREATE then creates an instance of ALGauge.  The ALGauge
//  object keeps track of everything about the particular gauge.
//  The user of the gauge doesn't get to see this class, since his or her
//  interface to the object goes strictly through messages to the 
//  object.  
//
// DATA MEMBERS
//
//   static dwDefaultTextColor        
//   static dwDefaultBackgroundColor
//                              When a new ALGauge object is created, it
//                              is assigned these colors.  In theory, you
//                              can change these colors later with the
//                              right message.
//
//   static szClassName         One instance of the class name.
//
//   static iRegistered         This guy is used to keep track of whether
//                              the class has been registered with Windows.
//
//   iRange                     The range of a gauge is normally 100, meaning
//                              it can have a value ranging from 0 to 100.
//
//   iPosition                  The current position of the gauge, normally
//                              set between 0 and iRange.
//
//   iOrientation               This is set to one of four possible
//                              enumerated constants, indication which
//                              way the gauge fills, left to right,
//                              top to bottom, bottom to top, or right
//                              to left.
//
//   hFont                      The font that that text will be displayed
//                              in.
//
//   dwTextColor                The color the text will be displayed in.
//
//   dwBackgroundColor          The background color of the box.
//
// MEMBER FUNCTIONS
//
//   ALGauge()                  The constructor.  The end user never
//                              gets to call this dude.
//
//   gaugePaint()               This guy gets called from WM_PAINT.
//
// REVISION HISTORY
//
//  May 20, 1994  1.0A  : First release
//

// I'm not entirely sure why we need the _far declaration on the class.
// Watcom doesn't like it, so I am trying it without.  Since the
// pointer is a far  pointer anyway, shouldn't this work without the
// _far type modifier on the class?

#if defined( AL_WATCOM ) || defined( AL_FLAT_MODEL )
class ALGauge {
#else
class _far ALGauge {
#endif
    public :
        ALGauge();
        void gaugePaint( HWND hwnd );
        static DWORD dwDefaultTextColor;
        static DWORD dwDefaultBackgroundColor;
        static char *szClassName;
        static int iRegistered;
        int iRange;
        int iPosition;
        ALGaugeOrientation iOrientation;
        HFONT hFont;
        DWORD dwTextColor;
        DWORD dwBackgroundColor;
};

//
// The static variables for class ALGauge
//
DWORD ALGauge::dwDefaultTextColor = 0;
DWORD ALGauge::dwDefaultBackgroundColor = 0;
int ALGauge::iRegistered = 0;
char * ALGauge::szClassName = "ALGauge";

/* internal function prototypes */
#ifdef AL_BUILDING_DLL
LONG AL_EXPORT CALLBACK gaugeWndProcDll( HWND, UINT, WPARAM, LPARAM );
#else
LONG AL_EXPORT CALLBACK gaugeWndProc( HWND, UINT, WPARAM, LPARAM );
#endif

//
// ALGauge::ALGauge()
//
// ARGUMENTS:
//
//  None.
//
// RETURNS
//
//  No returns from Mr. ctor.
//
// DESCRIPTION
//
//  The constructor is called from the WndProc when the window is first
//  created.  By initializing the member variables, we are all set for
//  the WM_PAINT.
//
// REVISION HISTORY
//
//   May 19, 1994  1.0A  : First release
//

ALGauge::ALGauge()
{
    iRange = 100;
    iPosition = 0;
    iOrientation = ALGaugeOrientLeftToRight;
    dwTextColor = dwDefaultTextColor;
    dwBackgroundColor = dwDefaultBackgroundColor;
}

//
// extern "C" int ALGaugeInit( HINSTANCE hInstance, 
//                             HINSTANCE hPrevInstance )
//
// ARGUMENTS:
//
//  hInstance  :    The instance handle of the running program, as 
//                  passed to WinMain()
//
//  hPrevInstance : The previous instance handle.  See my comments
//                  about this below.  A non-zero value here keeps
//                  me from attempting to register the class.
//
// RETURNS
//
//  1 for success, 0 for failure.
//
// DESCRIPTION
//
//  This function is the only function you have to call to initialize
//  the ALGauge objects.  It registers the class and sets up the
//  WndProc for this type of object.  This code is for the most
//  part either a copy of or closely related to the original Microsoft
//  code on CIS.
//
//  Looking over this function right now, while I am documenting it, I can
//  see that I probably shouldn't be dinking with the hPrevInstance 
//  parameter.  The standalone program that demonstrated this class
//  would have used that to prevent itself from registering twice.  
//  At least when inside the DLL, I prevent that by checking the 
//  iRegistered member.
//
// REVISION HISTORY
//
//   May 19, 1994  1.0A  : First release
//

extern "C" int AL_FUNCTION ALGaugeInit( HINSTANCE hInstance, HINSTANCE hPrevInstance )
{
    WNDCLASS wc;
    HDC hdc;
    
    if ( ALGauge::iRegistered )
        return 1;

    if ( hPrevInstance == 0 ) {
        wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
        wc.hIcon            = NULL;
        wc.lpszMenuName     = NULL;
        wc.lpszClassName    = ALGauge::szClassName;
        wc.hbrBackground    = (HBRUSH) (COLOR_WINDOW + 1);
        wc.hInstance        = hInstance;
#ifdef AL_BUILDING_DLL
        wc.style            = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = gaugeWndProcDll;
#else
        wc.style            = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = (WNDPROC) gaugeWndProc;
#endif
        wc.cbClsExtra       = 0;
#if defined ( AL_WATCOM ) || defined( AL_FLAT_MODEL )
        wc.cbWndExtra       = sizeof( ALGauge * );
#else
        wc.cbWndExtra       = sizeof( ALGauge _far * );
#endif
        if ( !RegisterClass( &wc ) )
            return 0;
    }
    hdc = CreateIC( "DISPLAY", NULL, NULL, NULL );
    if ( !hdc ) {
        UnregisterClass( ALGauge::szClassName, hInstance );
        return 0;
    }
//
// Select colors based on whether this is mono or color
//
    if ( GetDeviceCaps( hdc, BITSPIXEL ) == 1 &&
         GetDeviceCaps( hdc, PLANES ) == 1 ) {
        ALGauge::dwDefaultTextColor = RGB(255, 255, 255);
        ALGauge::dwDefaultBackgroundColor = RGB(0, 0, 0);
    } else {
        ALGauge::dwDefaultTextColor = RGB(0, 0, 255);
        ALGauge::dwDefaultBackgroundColor = RGB(255, 255, 255);
    }
    DeleteDC(hdc);
    return ( ALGauge::iRegistered = 1);
} 


//
// void ALGauge::gaugePaint( HWND hwnd )
//
//
// ARGUMENTS:
//
//  hwnd        :  The handle of the control.
//
// RETURNS
//
//  Nothing.
//
// DESCRIPTION
//
//  This guy is called when the window gets a WM_PAINT message.  How
//  does that work when this is a member function?  Easy, when the
//  window was created, we made a new ALGauge object, and stored its
//  address in the window long word.
//
//  This is mostly Microsoft code.  I worked it over a little bit to
//  get it to work with the ALGauge class, instead of using a bunch
//  of static variables.  I had to muck with it a little bit more to
//  get it to work with Win32s instead of Win16, but that was an easy bit.
//
// REVISION HISTORY
//
//   May 20, 1994  1.0A  : First release
//

void ALGauge::gaugePaint( HWND hwnd )
{
    RECT rc1;
    RECT rc2;
    HFONT hLastFont;
    PAINTSTRUCT ps;
    char ach[ 6 ];

    BeginPaint( hwnd, &ps);
    HDC hdc = ps.hdc;
    SetTextColor( hdc, dwTextColor );
    SetBkColor( hdc, dwBackgroundColor );
    hLastFont = (HFONT) SelectObject( hdc, hFont );

    /* draw black rectangle for gauge */
    GetClientRect(hwnd, &rc1);
    FrameRect( hdc, &rc1, (HBRUSH) GetStockObject( BLACK_BRUSH ) );
    InflateRect( &rc1, -2, -2 );
    rc2 = rc1;

    /* get the range and position, make sure they are valid */
    if ( iRange <= 0 )
        iRange = 1;
    if ( iPosition > iRange )
        iPosition = iRange;
    else if ( iPosition < 0 )
        iPosition = 0;

    /* compute the actual size of the gauge */
    int dx = rc1.right - rc1.left;
    int dy = rc1.bottom - rc1.top;
    int wGomerX = (WORD)((DWORD)iPosition * dx / iRange );
    int wGomerY = (WORD)((DWORD)iPosition * dy / iRange );

    /* get the orientation and mung rects accordingly */
    switch ( iOrientation ) {
        case ALGaugeOrientRightToLeft :
            rc1.left = rc2.right = (short int ) ( rc1.right - wGomerX );
            break;
        case ALGaugeOrientBottomToTop :
            rc1.top = rc2.bottom = (short int) ( rc1.bottom - wGomerY );
            break;
        case ALGaugeOrientTopToBottom :
            rc1.bottom = rc2.top += wGomerY;
            break;
        case ALGaugeOrientLeftToRight :
        default:
            rc1.right = rc2.left += wGomerX;
            break;
    } /* switch () */

    /* select the correct font */

    /* build up a string to blit out--ie the meaning of life: "42%" */
    wsprintf(ach, "%3d%%", (WORD)((DWORD) iPosition * 100 / iRange ) );
    SIZE size;
    GetTextExtentPoint( hdc, ach, wGomerX = lstrlen(ach), &size );
    /*  Draw the finished (ie the percent done) side of box.  If
     *  ZYZG_WW_POSITION is 42, (in range of 0 to 100) this ExtTextOut
     *  draws the meaning of life (42%) bar.
     */

    ExtTextOut( hdc, (short int) (( dx - size.cx ) / 2 + 1 ), // 1 for the fram
                     (short int ) (( dy - size.cy ) / 2 + 1 ),
                     ETO_OPAQUE | ETO_CLIPPED, &rc2, ach, (short int) wGomerX, NULL);
    /*  Reverse fore and back colors for drawing the undone (ie the non-
     *  finished) side of the box.
     */
    SetBkColor( hdc, dwTextColor );
    SetTextColor( hdc, dwBackgroundColor );
    ExtTextOut( hdc, 
                (short int) (( dx - size.cx ) / 2 + 1), // 1 for the frame
                (short int) (( dy - size.cy ) / 2 + 1),
                ETO_OPAQUE | ETO_CLIPPED, 
                &rc1, 
                ach, 
                (short int) wGomerX, 
                NULL );
    SelectObject( hdc, hLastFont );
    EndPaint( hwnd, &ps );
}
  

//
// long ForceRepaint( HWND hwnd )
//
//
// ARGUMENTS:
//
//  hwnd  :  The handle of the bar gauge control.
//
// RETURNS
//
//  0L, always.  So what is the point of having a return?  Not sure,
//  I was just copying it.
//
// DESCRIPTION
//
//  Several of the messages that can be sent to the gauge control change
//  things enough that we want to repaint.  Those routines can call
//  this guy to force it to happen.
//
// REVISION HISTORY
//
//   May 20, 1994  1.0A  : First release
//

long ForceRepaint( HWND hwnd )
{
    RECT rc;

    GetClientRect(hwnd, &rc);
    InflateRect( &rc, ~1, ~1 );
    InvalidateRect( hwnd, &rc, FALSE );
    UpdateWindow( hwnd );
    return 0L;
}

//
// LONG AL_EXPORT CALLBACK gaugeWndProc( HWND hwnd,
//                                       UINT uMsg,
//                                       WPARAM wParam,
//                                       LPARAM lParam)
//
// ARGUMENTS:
//
//  hwnd       :  Standard argument for Windows procedure
//
//  uMsg       :  Standard argument for Windows procedure
//
//  wParam     :  Standard argument for Windows procedure
//
//  lParam     :  Standard argument for Windows procedure
//
// RETURNS
//
//  varies, see code.
//
// DESCRIPTION
//
//  This is the windows procedure for the ALGauge class.  In the
//  demos for ArchiveLib, we pretty much are just going to use
//  the WM_CREATE and WM_PAINT messages.  In theory you could send
//  all these other messages, but that hasn't been tested.  In fact,
//  looking at the code just now, I believe all the messages that
//  can be used to set the position, font, etc, should all be part
//  of the WM_COMMAND case, but that isn't even in there  Try to
//  remember that this is just demo code!
//
// REVISION HISTORY
//
//   May 21, 1994  1.0A  : First release
//
//  July 11, 1994 1.0B  : Modified this function to use AL_EXPORT,
//                        so I could build it under NT.

//
// I change the name for the DLL so that you can link both the DLL and
// the static library without a name conflict.
//
// There is a lot of code in here that is #ifdefed to let me declare the
// class as a far object.  I'm not sure if that is necessary or not.  At
// one time I was sure it was, but I am able to work with it under
// Watcom in small  model.
//
#ifdef AL_BUILDING_DLL
LONG AL_EXPORT CALLBACK gaugeWndProcDll(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
#else
LONG AL_EXPORT CALLBACK gaugeWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
#endif
{
//
// After the window has been created, the pointer to the ALGauge object
// is kept in the windows long word.  I get it here so everyone else
// can have access to it.
//
#if defined ( AL_WATCOM ) || defined( AL_FLAT_MODEL )
    ALGauge *pgauge = (ALGauge *) GetWindowLong( hwnd, 0 );
#else
    ALGauge _far *pgauge = (ALGauge _far *) GetWindowLong( hwnd, 0 );
#endif
    switch (uMsg) {
//
// When I get the WM_CREATE message, I create a new ALGauge object, then
// put its address in the Windows long word.
//
        case WM_CREATE:
#if defined( AL_SYMANTEC ) || defined( AL_WATCOM ) || defined( AL_FLAT_MODEL )
// Not sure about this yet
            pgauge = new ALGauge;
#else
            pgauge = new _far ALGauge;
#endif
            if ( pgauge == 0 )
                return (0L);
            SetWindowLong( hwnd, 0, (LONG) pgauge );
            SendMessage( hwnd, WM_SETFONT, NULL, 0L );
            break;

        case WM_DESTROY:
            if ( pgauge )
#if defined( AL_SYMANTEC ) && !defined( AL_LARGE_DATA )
                delete (void _near  *) pgauge;
#else
                delete pgauge;
#endif
            break;

        case ALGaugeGetPosition :
            return pgauge->iPosition;

        case ALGaugeGetRange :
            return pgauge->iRange;

        case ALGaugeGetOrientation :
            return pgauge->iOrientation;

        case ALGaugeGetForegroundColor :
            return pgauge->dwTextColor;

        case ALGaugeGetBackgroundColor:
            return pgauge->dwBackgroundColor;

        case ALGaugeSetBackgroundColor :
            pgauge->dwBackgroundColor = lParam;
            return 0L;

        case ALGaugeSetForegroundColor :
            pgauge->dwTextColor = lParam;
            return 0L;

        case ALGaugeSetPosition :
            pgauge->iPosition = wParam;
            return ForceRepaint( hwnd );

        case ALGaugeSetRange :
            pgauge->iRange = wParam;
            return ForceRepaint( hwnd );

        case ALGaugeSetOrientation :
            pgauge->iOrientation = (ALGaugeOrientation) wParam;
            return ForceRepaint ( hwnd );

        case ALGaugeSetDeltaPosition :
            pgauge->iPosition += (signed) wParam;
            return ForceRepaint( hwnd );
            
        case WM_PAINT :
            pgauge->gaugePaint( hwnd );
            return (0L);

        case WM_GETFONT :
            if ( pgauge->hFont == GetStockObject(SYSTEM_FONT) )
                return NULL;
            else
                return (WORD) pgauge->hFont;

        case WM_SETFONT :
            if ( wParam == 0 ) 
                pgauge->hFont = (HFONT) GetStockObject( SYSTEM_FONT );
            else
                pgauge->hFont = (HFONT) wParam;
            /* redraw if indicated in message */
            if ( (BOOL) lParam ) {
                InvalidateRect( hwnd, NULL, TRUE );
                UpdateWindow( hwnd );
            }
            return (0L);
    }
    return ( DefWindowProc( hwnd, uMsg, wParam, lParam ) );
}

