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
// Module: RECORD.H
// Description:
//
//	Header file for record handling.
//
// Programmer:	Adriano Sergio R. de Souza                            
//		Tricia Souto Santos
//
// Last update: 06/06/95
//


#ifndef	_RECORD_H_
#define	_RECORD_H_

#ifndef	_FILISTCL_H_
#include	<filistcl.h>
#endif
#ifndef	_FILECL_
#include	<filecl.h>
#endif
#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_PASSWDCL_H_
#include        <passwdcl.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef _LB1_
#include	<lb1cl.h>
#endif
#ifndef _FIELDGROUP_H_
#include	<fieldgroup.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

class _LBSCLASS LBSC_Record
{
	friend	class	_LBSCLASS LBSC_Base;
	friend	class	_LBSCLASS LBSC_Session;
	friend	class	_LBSCLASS LBSC_Parser;
	friend	class	_LBSCLASS LBSC_EntParser;

	private:
		LBSC_FieldList			lbscFieldList;	// List of all the base fields
		LBSC_FieldGroupList		lbscflGroupList;
		long				lRecInitPos;		// Arquivo LB2
		LBSC_Base			*plbscbBase;
		C_Date				cdCreateDate;
		C_Date				cdLastUpdateDate;
		CL_StringN<USERNAMESIZE>	szLastUpdateUserName;
		CL_StringN<USERNAMESIZE>	szOwnerName;
		BYTE				bStatus;
		LBSC_Password			lbscpPassword;
		BOOL				bIsUndefined;
		unsigned long			ulAccess;		// contador de acessos ao registro
		C_Buffer			*pRecordBuffer;
		TRecordBufferHeader	*pRecordFieldsHeader;
		long				lNumFieldsRead;
		BOOL				bMustLoadData;
		LBSC_Field			*pCurrField;

		LBSC_Field	**pcSortListByAlias;
		LBSC_Field	**pcSortListById;

		void FillSortLists();
		LBSC_Field * FindByAlias( char * );
		LBSC_Field * FindById( UINT );


					LBSC_Record( LBSC_Base * );
		const char		*GetPassword();
		int			ModifyPassword( char * );
		const char		*GetFieldPassword( char * );
		int			ModifyFieldPassword( char *, char *, char * );
		int			ModifyFieldIndexAttrib( char *, char *, int );
		BOOL			IsLocked(){ return( bStatus & REC_LOCKED ); };
		BOOL			IsUndefined();
		void			SetIsUndefined( BOOL bAux ){ bIsUndefined = bAux; };
		void			SetCreateDate( long );
		void			SetModifyDate( long );
		void			SetStatus( BYTE );
		const LBSC_Field	*GetFieldObj( char * );
		const LBSC_Field	*Id( UINT );
		int			ModifyFieldId( char *, UINT );
		int			ModifyFieldAttrib( char *szFieldName, char *szPassword, UINT uiFieldAttribPar );

		// operadores (eram publicos, mas vieram para a area privada para
		// (proibir o uso por causa do RPC)
		LBSC_Field		*operator []( int );
		LBSC_Field		*operator []( char * );
		LBSC_Field		*operator ()( UINT );
		LBSC_Record& 	operator = ( LBSC_Record& );

		BOOL			SetRecordBuffer( C_Buffer & );
		void			ClearReadStatusFromFields();
		BOOL			FillFieldFromBuffer(LBSC_Field *pField);
		BOOL			FillRepetitionFromBuffer(LBSC_Field *pField, int iRep);
		BOOL			TryUncompressRecordBuffer( C_Buffer &Buf, BYTE **pNewBuf, long *plNewBufSize );
		long			RecordHeaderBufferSize();
		void			StartFillingField( LBSC_Field *pField, long lNumRep );
		void			EndFillingField( LBSC_Field *pf );
		void			FreeRecordBuffers();


	public:
					LBSC_Record();
					~LBSC_Record();
		int			Clear( BOOL bFillOriginalDataList = FALSE );
		int			AddField( LBSC_Field *, int );
		int			ModifyField( char *, LBSC_Field * );
		int			GetNumberOfFields();
		int			Delete( C_LB1 * );
		int			Lock( C_LB1 * );
		int			Release( C_LB1 * );
		int			DelField( char * );
		int			DelField( UINT );
		int			VerifyPassword( char * );
		int			VerifyFieldPassword( char *, char * );

		int 			DelFieldRepetition( char *, int, BOOL = FALSE );
		BYTE			GetStatus();

		long			GetCreateDate();
		long			GetModifyDate();
		char			*GetLastModifyUserName();
		const char		*GetOwnerName();

		LBSC_Field		*NthField( int );
		void			SortFieldLists();
		void			DelSortLists( void );
		void			DelAllFields();
		LBSC_Field		*CurrentField();
		int				GetNumberOfFieldsInGroup( LBSC_FieldGroup *pfGroup );
		LBSC_Field		*GetFieldInGroup( LBSC_FieldGroup *pfGroup, int iPos );

};

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _RECORD_H_


