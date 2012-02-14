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
// Module: DEVICECL.H
// Description:
//	Device independent class definition file
//
// Programmer:	Alessandro Jatoba
//
// Last Uptade: 03/05/94
//


#ifndef _DEVICE_
#define _DEVICE_

#ifndef	_INCLUDES_H_
#include	<includes.h>
#endif

#if !defined(__MEM_H) && !defined _INC_MEMORY
#include	MEM_H
#endif
#if !defined __STDIO_H && !defined _INC_STDIO
#include	<stdio.h>
#endif

#ifdef	__MFC
#	ifndef __AFXWIN_H__
#	include	<afxwin.h>
#	endif
#else
#	ifndef __WINDOWS_H     /* prevent multiple includes */
#	include	<windows.h>
#	endif
#endif
#ifndef	_LIFILE_DEFCLASS_H_
#include	<lifdef.h>
#endif

BOOL	CopyClipboard( HWND, UINT, HGLOBAL, BOOL );
HGLOBAL	PasteClipboard( HWND, UINT );

class Device {
	public:
		virtual int Read( void FAR *buffer, size_t size )
		{ return 1; }
		virtual int Write( void FAR *buffer, size_t size )
		{ return 1; }
		int Write( int i )
		{ return Write( &i, sizeof( int ) ); }
};

class Clipboard : public Device {
		HGLOBAL	hBuffer;
		size_t	offset;
	public :
		Clipboard( size_t size )
		{
			hBuffer = GlobalAlloc( GMEM_MOVEABLE, size );
			offset =  0 ;
		}
		Clipboard( HWND hWnd, UINT uFormat )
		{
			offset = 0 ;
			hBuffer = PasteClipboard( hWnd, uFormat );

		}
		int Write( void FAR *buffer, size_t size );
		int Read( void FAR *buffer, size_t size );
		BOOL Copy( HWND hWnd, UINT uFormat, BOOL bEmpty )
		{
			return CopyClipboard( hWnd, uFormat, hBuffer, bEmpty );
                }
		operator HGLOBAL( void ) { return hBuffer; }
};

#endif _DEVICE_
