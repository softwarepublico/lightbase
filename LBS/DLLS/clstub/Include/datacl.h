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
// Module: DATACL.H
//	LBSC_Data class definition file
//
// Programmer:	Adriano Sergio R. de Souza
//
// Last revision: 09/11/94
//
// Client Stub

#ifndef	_DATACL_H_
#define	_DATACL_H_

#ifndef _LBSNETCL_H_
#include <lbsnetcl.h>
#endif

#ifndef _FILECL_H_
	#include	<filecl.h>
#endif	// _FILECL_H_

#ifndef _DATECL_H_
	#include	<datecl.h>
#endif	// _DATECL_H_

#ifndef _TIMECL_H_
	#include	<timecl.h>
#endif	// _TIMECL_H_

#ifndef _BINARYCL_H_
	#include	<binarycl.h>
#endif	// _BINARYCL_H_

#ifndef _REFERCL_H_
	#include	<refercl.h>
#endif	// _REFERCL_H_

#ifndef _DEFCLASS_H_
	#include	<defclass.h>
#endif	// _DEFCLASS_H_

#ifndef _LBSDEFS_H_
	#include 	<LBSDEFS.H>
#endif	// _LBSDEFS_H_

#ifndef _LBSTYPES_H_
	#include 	<LBSTYPES.H>
#endif	// _LBSTYPES_H_


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	class _LBSCLASS LBSC_Data : public LBSC_ClntNet 
{
	friend	class _LBSCLASS LBSC_Field;
	
	private:
		long		obj;
		char		ServerAddr[ SERVERNAMESIZE ];
		int			iServerIndex;

	public:
			LBSC_Data()
			{
			 	obj = 0;
				strcpy( ServerAddr, "" );
				iServerIndex = 0;
			};
			~LBSC_Data(){};

		void		*GetData();
		
/*******************************
Nada de operadores

		void operator = ( long );
		void operator = ( double );
		void operator = ( char * );
		void operator = ( void * );
		void operator = ( C_Date & );
		void operator = ( C_Time & );
		void operator = ( LBSC_Binary & );
		void operator = ( LBSC_Reference & );
		void operator = ( BYTE );
		void operator = ( short int );
		void operator = ( float );

		LBSC_Data& operator = ( LBSC_Data & );

		operator long ( void );
		operator double ( void );
		operator char* ( void );
		operator void* ( void );
		operator LBSC_Binary* ( void );
		operator LBSC_Reference* ( void );
		operator JulTy ( void );
		operator BYTE ( void );
		operator short int ( void );
		operator float ( void );
*********************/

		LBSC_Data	*Duplicate() { return NULL; };
		int			Compare( LBSC_Data *, int );
};

/******
Nao eh necessario: nao estamos usando operadores
extern LBSC_Data	_GlobalData;
*****/

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // _DATACL_H_


