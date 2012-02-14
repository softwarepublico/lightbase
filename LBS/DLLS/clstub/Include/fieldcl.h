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
// Module: FIELDCL.H
// Description:
//
//	Header file for field handling.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 09/11/94
//
// Client Stub

#ifndef	_FIELDCL_H_
#define	_FIELDCL_H_

#ifndef _LBSTYPES_H_
	#include	<lbstypes.h>
#endif	// _LBSTYPES_H_

#ifndef _DATACL_H_
	#include	<datacl.h>
#endif	// _DATACL_H_

#ifndef _DEFCLASS_H_
	#include	<defclass.h>
#endif	// _DEFCLASS_H_

#ifndef _TICKETCL_H_
	#include 	<ticketcl.h>
#endif	// _TICKETCL_H_


#ifndef _CL_STRINGN_
#include	<stringn.h>
#endif
#ifndef _DATLSTCL_H_
#include	<datlstcl.h>
#endif
#ifndef _LBSNETCL_H_
#include <lbsnetcl.h>
#endif

class LBSC_Base;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
			
class _LBSCLASS LBSC_Field: LBSC_ClntNet 
{
	friend	class	_LBSCLASS LBSC_Base;

	private:
		long						obj;
		long						lBaseObj;
		long						lSessionObj;
		char						ServerAddr[ SERVERNAMESIZE ];
		UINT						uiFieldId;
		CL_StringN<FIELDNAMESIZE>  	szAliasName;
		LBSC_DataList				*pdlDataList;
		LBSC_Base					*pOwnerBase;
		UINT						uiFieldAttrib;
		int							iGroup;

	public:
		LBSC_Field( char *szAliasName, UINT uiFieldId, LBSC_Base *pBase ){
			obj = 0;
			pdlDataList = NULL;
			lBaseObj = 0;
			lSessionObj = 0;
			strcpy( ServerAddr, "" );
			this->szAliasName = szAliasName;
			this->uiFieldId	= uiFieldId;
			pOwnerBase = pBase;
			uiFieldAttrib = 0;
			iGroup = 0;
		};

		~LBSC_Field(){
			if( pdlDataList ){
				pdlDataList->DelAll();
				pdlDataList = NULL;
			}
		};

    	TSRControlInfo ObtemControlInfo();

		// GoWords
		char			*GetFirstGoWord();
		char			*GetNextGoWord();
		char 			*GetCurrentGoWord();
		char			*GetNthGoWord( int );
		char			*SearchGoWord( char * );
		char			*GetAliasName();
		long			GetNbrOfGoWord();
		LBSC_Data&		GetDataObj( int );

		
		int				Clear();
		UINT			GetId();
		int				Compare( LBSC_Field *, int );
		
		LBSC_Field		*Duplicate() { return NULL; };

		/********
		Nada de  Operadores

		LBSC_Data&  	operator [] ( int );
		LBSC_Field& 	operator =  ( LBSC_Field& );
		int	    		operator == ( LBSC_Field& b );

		LBSC_Field& operator << ( long );
		LBSC_Field& operator << ( double );
		LBSC_Field& operator << ( char * );
		LBSC_Field& operator << ( void * );
		LBSC_Field& operator << ( C_Date & );
		LBSC_Field& operator << ( C_Time & );
		LBSC_Field& operator << ( LBSC_Binary & );
		LBSC_Field& operator << ( LBSC_Reference & );
		LBSC_Field& operator << ( BYTE );
		LBSC_Field& operator << ( short int );
		LBSC_Field& operator << ( float );

		void operator = ( long );
		void operator = ( double );
		void operator = ( char * );
		void operator = ( void * );
		void operator = ( C_Date & );
		void operator = ( C_Time & );
		void operator = ( LBSC_Binary &  );
		void operator = ( LBSC_Reference & );
		void operator = ( BYTE );
		void operator = ( short int );
		void operator = ( float );

		******************/

};

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif // _FIELDCL_H_


