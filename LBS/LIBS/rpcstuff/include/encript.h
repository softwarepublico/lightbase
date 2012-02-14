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


#ifndef _ENCRIPT_H_

#define _ENCRIPT_H_


#ifndef __lbsrpc_h__
	#include <lbsrpc.h>
#endif	// __lbsrpc_h__


void Criptografa( TSRClntInitInfo & );
void Decriptografa( TSRClntInitInfo & );
void Criptografa( TSRControlInfo & );
void Decriptografa( TSRControlInfo & );
void Criptografa( TSRUDBRecord & );
void Decriptografa( TSRUDBRecord & );
void Criptografa( TSRField & );
void Decriptografa( TSRField & );
void Criptografa( TSRTicket & );
void Decriptografa( TSRTicket & );
void Criptografa( TSRGenericObj & );
void Decriptografa( TSRGenericObj & );
void Criptografa( TSRNetInfo & );
void Decriptografa( TSRNetInfo & );
void Criptografa( TSRIn_Login & );
void Decriptografa( TSRIn_Login & );
void Criptografa( TSRIn_GetGroups & );
void Decriptografa( TSRIn_GetGroups & );
void Criptografa( TSRIn_CreateCloseDelete & );
void Decriptografa( TSRIn_CreateCloseDelete & );
void Criptografa( TSRIn_AddDelGroupUser & );
void Decriptografa( TSRIn_AddDelGroupUser & );
void Criptografa( TSRIn_UserGenInfos & );
void Decriptografa( TSRIn_UserGenInfos & );
void Criptografa( TSRIn_OpenBase & );
void Decriptografa( TSRIn_OpenBase & );
void Criptografa( TSRIn_What & );
void Decriptografa( TSRIn_What & );
void Criptografa( TSRIn_ReorgBase & );
void Decriptografa( TSRIn_ReorgBase & );
void Criptografa( TSROut_OpenBase & );
void Decriptografa( TSROut_OpenBase & );
void Criptografa( TSRIn_Import & );
void Decriptografa( TSRIn_Import & );
void Criptografa( TSRIn_Export & );
void Decriptografa( TSRIn_Export & );
void Criptografa( TSRIn_UpdateUserAddress & );
void Decriptografa( TSRIn_UpdateUserAddress & );
void Criptografa( TSRIn_CreateDefaultUserBase & );
void Decriptografa( TSRIn_CreateDefaultUserBase & );
void Criptografa( TSRIn_DeleteUDB & );
void Decriptografa( TSRIn_DeleteUDB & );
void Criptografa( TSRIn_IncorporateBase & );
void Decriptografa( TSRIn_IncorporateBase & );
void Criptografa( TSRIn_RenameBase & );
void Decriptografa( TSRIn_RenameBase & );
void Criptografa( TSRIn_SetNavigationLocate & );
void Decriptografa( TSRIn_SetNavigationLocate & );
void Criptografa( TSRIn_TicketPar & );
void Decriptografa( TSRIn_TicketPar & );
void Criptografa( TSRIn_AddField & );
void Decriptografa( TSRIn_AddField & );
void Criptografa( TSRIn_DelFieldGetFieldObj & );
void Decriptografa( TSRIn_DelFieldGetFieldObj & );
void Criptografa( TSRIn_ModifyFieldPassword & );
void Decriptografa( TSRIn_ModifyFieldPassword & );
void Criptografa( TSRIn_ModifyFieldName & );
void Decriptografa( TSRIn_ModifyFieldName & );
void Criptografa( TSRIn_ModifyFieldDescription & );
void Decriptografa( TSRIn_ModifyFieldDescription & );
void Criptografa( TSRIn_ModifyFieldSize & );
void Decriptografa( TSRIn_ModifyFieldSize & );
void Criptografa( TSRIn_DelFieldRepetition & );
void Decriptografa( TSRIn_DelFieldRepetition & );
void Criptografa( TSRIn_GetNumberOfRepetition & );
void Decriptografa( TSRIn_GetNumberOfRepetition & );
void Criptografa( TSRIn_GetFieldRepetitionSize & );
void Decriptografa( TSRIn_GetFieldRepetitionSize & );
void Criptografa( TSRIn_GetFields & );
void Decriptografa( TSRIn_GetFields & );
void Criptografa( TSRIn_TicketBOOLPar & );
void Decriptografa( TSRIn_TicketBOOLPar & );
void Criptografa( TSRIn_SetLockTimeOut & );
void Decriptografa( TSRIn_SetLockTimeOut & );
void Criptografa( TSRIn_SetReorganizeRecQuant & );
void Decriptografa( TSRIn_SetReorganizeRecQuant & );
void Criptografa( TSRIn_Nth & );
void Decriptografa( TSRIn_Nth & );
void Criptografa( TSRIn_Search & );
void Decriptografa( TSRIn_Search & );
void Criptografa( TSRIn_OcList & );
void Decriptografa( TSRIn_OcList & );
void Criptografa( TSRIn_SetNavigation & );
void Decriptografa( TSRIn_SetNavigation & );
void Criptografa( TSRIn_GetSlotSize & );
void Decriptografa( TSRIn_GetSlotSize & );
void Criptografa( TSRIn_SearchStopWord & );
void Decriptografa( TSRIn_SearchStopWord & );
void Criptografa( TSRIn_GoWord & );
void Decriptografa( TSRIn_GoWord & );
void Criptografa( TSRIn_ModifyFieldIndexAttrib & );
void Decriptografa( TSRIn_ModifyFieldIndexAttrib & );
void Criptografa( TSRIn_ModifyFieldAttrib & );
void Decriptografa( TSRIn_ModifyFieldAttrib & );
void Criptografa( TSRIn_ACLPerm & );
void Decriptografa( TSRIn_ACLPerm & );
void Criptografa( TSRIn_EnableOnLineIndex & );
void Decriptografa( TSRIn_EnableOnLineIndex & );
void Criptografa( TSRIn_GetSlotPutSlot & );
void Decriptografa( TSRIn_GetSlotPutSlot & );
void Criptografa( TSRIn_ModifyPassword & );
void Decriptografa( TSRIn_ModifyPassword & );
void Criptografa( TSRIn_ModifyBaseType & );
void Decriptografa( TSRIn_ModifyBaseType & );
void Criptografa( TSRIn_IndexAll & );
void Decriptografa( TSRIn_IndexAll & );
void Criptografa( TSRIn_IndexString & );
void Decriptografa( TSRIn_IndexString & );
void Criptografa( TSRIn_AddStopWord & );
void Decriptografa( TSRIn_AddStopWord & );
void Criptografa( TSRIn_ModifyBaseOwnerName & );
void Decriptografa( TSRIn_ModifyBaseOwnerName & );
void Criptografa( TSRIn_GetFieldIndexAttrib & );
void Decriptografa( TSRIn_GetFieldIndexAttrib & );
void Criptografa( TSRIn_GetFieldObj & );
void Decriptografa( TSRIn_GetFieldObj & );
void Criptografa( TSRIn_GetFieldTypeId & );
void Decriptografa( TSRIn_GetFieldTypeId & );
void Criptografa( TSRIn_GetFieldRepetition & );
void Decriptografa( TSRIn_GetFieldRepetition & );
void Criptografa( TSRIn_GetFieldRepetitionByVal & );
void Decriptografa( TSRIn_GetFieldRepetitionByVal & );
void Criptografa( TSRIn_PutFieldRepetition & );
void Decriptografa( TSRIn_PutFieldRepetition & );
void Criptografa( TSRIn_ModifyFieldRepetition & );
void Decriptografa( TSRIn_ModifyFieldRepetition & );
void Criptografa( TSRIn_GetACLListPerm & );
void Decriptografa( TSRIn_GetACLListPerm & );
void Criptografa( TSRIn_ExchangeOperator & );
void Decriptografa( TSRIn_ExchangeOperator & );
void Criptografa( TSRIn_Mask & );
void Decriptografa( TSRIn_Mask & );
void Criptografa( TSRIn_Phone & );
void Decriptografa( TSRIn_Phone & );
void Criptografa( TSRIn_Standardize & );
void Decriptografa( TSRIn_Standardize & );
void Criptografa( TSRIn_Synonym & );
void Decriptografa( TSRIn_Synonym & );
void Criptografa( TSRIn_OL & );
void Decriptografa( TSRIn_OL & );
void Criptografa( TSRIn_Operators & );
void Decriptografa( TSRIn_Operators & );
void Criptografa( TSRIn_MGetPutFieldRep & );
void Decriptografa( TSRIn_MGetPutFieldRep & );
void Criptografa( TSRIn_GetDataObj & );
void Decriptografa( TSRIn_GetDataObj & );
void Criptografa( TSRIn_VerifyPassword & );
void Decriptografa( TSRIn_VerifyPassword & );
void Criptografa( TSRIn_DataOp & );
void Decriptografa( TSRIn_DataOp & );
void Criptografa( TSRSetError & );
void Decriptografa( TSRSetError & );
void Criptografa( TSROut_GetFields & );
void Decriptografa( TSROut_GetFields & );
void Criptografa( TSRIn_KillSessions & );
void Decriptografa( TSRIn_KillSessions & );
void Criptografa( TSRIn_ModifyBaseName & );
void Decriptografa( TSRIn_ModifyBaseName & );
void Criptografa( TSRIn_SetSvcParam & );
void Decriptografa( TSRIn_SetSvcParam & );
void Criptografa( TSRIn_GetBaseLongName & );
void Decriptografa( TSRIn_GetBaseLongName & );
void Criptografa( TSRIn_AllRepetitions & );
void Decriptografa( TSRIn_AllRepetitions & );
void Criptografa( TSRIn_BreakSecurity & );
void Decriptografa( TSRIn_BreakSecurity & );
void Criptografa( TSRIn_MaintBase & );
void Decriptografa( TSRIn_MaintBase & );
void Criptografa( TSRMaintBase & );
void Decriptografa( TSRMaintBase & );
void Criptografa( TSROut_MaintBase & );
void Decriptografa( TSROut_MaintBase & );


class CCompact {
public:
	static int	Compress( unsigned char *, unsigned char **, int );
	static int	DeCompress( unsigned char *, unsigned char **, int );
};


#endif	// _ENCRIPT_H_