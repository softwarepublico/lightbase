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


/*************************************************************
//
// Classe: SortObject
//
************************************************************/

#ifndef _SORT
#define _SORT

#define BUILDISOK       0
#define FILEERROR       1
#define BUILDFAULT      2

#ifdef _WINDOWS
	#include <windows.h>
#else
	#include <defs.h>
#endif

class SortKey {
public:
	void		*pSortObject;
	void		*pvKey;
};

class SortObject {

    public:
						SortObject( DWORD );
						SortObject( void );
						~SortObject( void );
        BOOL			StartSort( void );
        BOOL			SetParms( DWORD );

		int BuildStatus;

        virtual int		Compare( void *, void * ) { return TRUE; }

    private:
		DWORD			nKeys;
        SortKey			*pKeys;		
		BOOL			SortData( void );

		virtual BOOL	GetData( void *& ) { return FALSE; }
        virtual void	PutData( void * ) { return; }
};

#endif
