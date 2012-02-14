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
// Module: USRCL.H
// Description:
//
//	LBSC_USR class definition usr.
//
// Programmer:	Adriano Sergio R. de Souza
//		Tricia Souto Santos
//
// Last update: 30/09/94
//

#ifndef	_USR_H_
#define	_USR_H_

#ifndef	_LBSTYPES_H_
#include	<lbstypes.h>
#endif
#ifndef	_GRPLIST_H_
#include	<grplist.h>
#endif
#ifndef	_LBS_DEFCLASS_H_
#include	<defclass.h>
#endif
#ifndef	_PASSWDCL_H_
#include	<passwdcl.h>
#endif

class _LBSCLASS LBSC_Session;

class	LBSC_User{

	friend	class	_LBSCLASS LBSC_Session;

	private:
		UserSTR		strUserName;
		DescSTR		strDescription;
		LBSC_Session	*plbscsSession;
		LBSC_Password	lbscpPassword;
		LBSC_GroupList	*plbscglGroupList;
		TUserType	tutUserType;

		LBSC_User( const char *, const char *, const char *,
			LBSC_GroupList *, LBSC_Session *, TUserType );

		void		*Write();
		void		*Delete();
		int		ModifyDescription( const char * );
		int		ModifyType( TUserType );
		int		ModifyPassword( const char * );
		char		*GetPassword();

	public:
				LBSC_User();
				~LBSC_User();
		int		AddGroup( LBSC_Group * );
		int		DelGroup();
		LBSC_Group	*NextGroup();
		LBSC_Group	*FirstGroup();
		LBSC_Group	*LastGroup();
		LBSC_Group	*NthGroup( int );
		TUserType       GetUserType();
		const char	*GetUserName();
		void		SetUserName( const char * );
};


#endif	// _USR_H_



