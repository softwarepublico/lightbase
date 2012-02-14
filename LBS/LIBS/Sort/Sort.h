/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo � parte do programa LightBase - Banco de Dados Textual Documental

O LightBase � um software livre; voc� pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o do Software 
Livre (FSF); na vers�o 2 da Licen�a.

Este programa � distribu�do na esperan�a que possa ser �til, mas SEM NENHUMA 
GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O 
EM PARTICULAR. Veja a Licen�a P�blica Geral GNU para maiores detalhes.

Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU versao 2, sob o 
t�tulo "LICENCA.txt", junto com este programa, se n�o, escreva para a Funda��o do 
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
