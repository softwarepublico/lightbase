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


//
//	Funcoes para criptografar e decritografar estruturas dos stubs
//	de rede. Usa as funcoes de criptografia do LBS. So se criptografa
//	estruturas que tem alguma senha; caso contrario a funcao nao faz nada
//	Tambem permite compactacao/decompactacao de tiras de bytes
//	
//	Vladimir Catao: 23.08.96
//
//

#ifndef _LBNEWDBG_H_
	#include <lbnewdbg.h>
#endif	// _LBNEWDBG_H_

extern "C" {
#ifndef _CRYPT_H_
	#include <crypt.h>
#endif	// _CRYPT_H_
}

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_

#include <arclib.h>
#include <memstore.h>
#include <grenengn.h>

void
Criptografa( TSRClntInitInfo & )
{
}

void
Decriptografa( TSRClntInitInfo & )
{
}

////////////////////////////////////////////////////////


void
Criptografa( TSRControlInfo & )
{
}

void
Decriptografa( TSRControlInfo & )
{
}

////////////////////////////////////////////////////////


void
Criptografa( TSRUDBRecord &InPar )
{
	if ( InPar.szUserPassword ) {
		Criptografa((char *)InPar.szUserPassword, (char *)InPar.szUserPassword + 
				strlen((char *)InPar.szUserPassword));
	}
}

void
Decriptografa( TSRUDBRecord &InPar )
{
	if ( InPar.szUserPassword ) {
		Decriptografa((char *)InPar.szUserPassword, (char *)InPar.szUserPassword + 
				strlen((char *)InPar.szUserPassword));
	}
}

////////////////////////////////////////////////////////


void
Criptografa( TSRField &InPar )
{
	if ( InPar.szPasswordName ) {
		Criptografa((char *)InPar.szPasswordName, (char *)InPar.szPasswordName + 
				strlen((char *)InPar.szPasswordName));
	}
}

void
Decriptografa( TSRField &InPar )
{
	if ( InPar.szPasswordName ) {
		Decriptografa((char *)InPar.szPasswordName, (char *)InPar.szPasswordName + 
				strlen((char *)InPar.szPasswordName));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRTicket &)
{
}

void
Decriptografa( TSRTicket &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRGenericObj &)
{
}

void
Decriptografa( TSRGenericObj &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRNetInfo &InPar )
{
	if ( InPar.strPasswd ) {
		Criptografa( (char *)InPar.strPasswd, (char *)InPar.strPasswd + PASSWORDSIZE + 1 );
	}
}

void
Decriptografa( TSRNetInfo &InPar )
{
	if ( InPar.strPasswd ) {
		Decriptografa( (char *)InPar.strPasswd, (char *)InPar.strPasswd + PASSWORDSIZE + 1 );
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Login &InPar )
{
	if ( InPar.psLoginInf ) {
		Criptografa( *(InPar.psLoginInf) );
	}
}

void
Decriptografa( TSRIn_Login &InPar )
{
	if ( InPar.psLoginInf ) {
		Decriptografa( *(InPar.psLoginInf) );
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetGroups &)
{
}

void
Decriptografa( TSRIn_GetGroups &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_CreateCloseDelete &InPar )
{
	if ( InPar.szBasePassword ) {
		Criptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
	if ( InPar.szMaintenancePassword ) {
		Criptografa( (char *)InPar.szMaintenancePassword, (char *)InPar.szMaintenancePassword + 
				strlen((char *)InPar.szMaintenancePassword));
	}
}

void
Decriptografa( TSRIn_CreateCloseDelete &InPar )
{
	if ( InPar.szBasePassword ) {
		Decriptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
	if ( InPar.szMaintenancePassword ) {
		Decriptografa( (char *)InPar.szMaintenancePassword, (char *)InPar.szMaintenancePassword + 
				strlen((char *)InPar.szMaintenancePassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_AddDelGroupUser &)
{
}

void
Decriptografa( TSRIn_AddDelGroupUser &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_UserGenInfos &InPar )
{
	if ( InPar.szOldPassword ) {
		Criptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + PASSWORDSIZE + 1 );
	}
	if ( InPar.szNewPassword ) {
		Criptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + PASSWORDSIZE + 1 );
	}
}

void
Decriptografa( TSRIn_UserGenInfos &InPar )
{
	if ( InPar.szOldPassword ) {
		Decriptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + PASSWORDSIZE + 1 );
	}
	if ( InPar.szNewPassword ) {
		Decriptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + PASSWORDSIZE + 1 );
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_OpenBase &InPar )
{
	if ( InPar.szBasePassword ) {
		Criptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
}

void
Decriptografa( TSRIn_OpenBase &InPar )
{
	if ( InPar.szBasePassword ) {
		Decriptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_What &)
{
}

void
Decriptografa( TSRIn_What &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ReorgBase &)
{
}

void
Decriptografa( TSRIn_ReorgBase &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSROut_OpenBase &)
{
}

void
Decriptografa( TSROut_OpenBase &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Import &InPar )
{
	if ( InPar.szNewBasePassword ) {
		Criptografa( (char *)InPar.szNewBasePassword, (char *)InPar.szNewBasePassword + 
				strlen((char *)InPar.szNewBasePassword));
	}
	if ( InPar.szNewMaintenanceBasePassword ) {
		Criptografa( (char *)InPar.szNewMaintenanceBasePassword, (char *)InPar.szNewMaintenanceBasePassword + 
				strlen((char *)InPar.szNewMaintenanceBasePassword));
	}
	if ( InPar.szImportPsw ) {
		Criptografa( (char *)InPar.szImportPsw, (char *)InPar.szImportPsw + 
				strlen((char *)InPar.szImportPsw));
	}
}

void
Decriptografa( TSRIn_Import &InPar )
{
	if ( InPar.szNewBasePassword ) {
		Decriptografa( (char *)InPar.szNewBasePassword, (char *)InPar.szNewBasePassword + 
				strlen((char *)InPar.szNewBasePassword));
	}
	if ( InPar.szNewMaintenanceBasePassword ) {
		Decriptografa( (char *)InPar.szNewMaintenanceBasePassword, (char *)InPar.szNewMaintenanceBasePassword + 
				strlen((char *)InPar.szNewMaintenanceBasePassword));
	}
	if ( InPar.szImportPsw ) {
		Decriptografa( (char *)InPar.szImportPsw, (char *)InPar.szImportPsw + 
				strlen((char *)InPar.szImportPsw));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Export &InPar )
{
	if ( InPar.szImportPsw ) {
		Criptografa( (char *)InPar.szImportPsw, (char *)InPar.szImportPsw + 
				strlen((char *)InPar.szImportPsw));
	}
}

void
Decriptografa( TSRIn_Export &InPar )
{
	if ( InPar.szImportPsw ) {
		Decriptografa( (char *)InPar.szImportPsw, (char *)InPar.szImportPsw + 
				strlen((char *)InPar.szImportPsw));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_UpdateUserAddress &)
{
}

void
Decriptografa( TSRIn_UpdateUserAddress &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_CreateDefaultUserBase &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
	if ( InPar.szMaintPassword ) {
		Criptografa( (char *)InPar.szMaintPassword, (char *)InPar.szMaintPassword + 
				strlen((char *)InPar.szMaintPassword));
	}
	if ( InPar.szUserPassword ) {
		Criptografa( (char *)InPar.szUserPassword, (char *)InPar.szUserPassword + PASSWORDSIZE + 1 );
	}
}

void
Decriptografa( TSRIn_CreateDefaultUserBase &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
	if ( InPar.szMaintPassword ) {
		Decriptografa( (char *)InPar.szMaintPassword, (char *)InPar.szMaintPassword + 
				strlen((char *)InPar.szMaintPassword));
	}
	if ( InPar.szUserPassword ) {
		Decriptografa( (char *)InPar.szUserPassword, (char *)InPar.szUserPassword + PASSWORDSIZE + 1 );
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_DeleteUDB &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + PASSWORDSIZE + 1 );
	}
}

void
Decriptografa( TSRIn_DeleteUDB &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + PASSWORDSIZE + 1 );
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_IncorporateBase &InPar )
{
	if ( InPar.szBasePassword ) {
		Criptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
}

void
Decriptografa( TSRIn_IncorporateBase &InPar )
{
	if ( InPar.szBasePassword ) {
		Decriptografa( (char *)InPar.szBasePassword, (char *)InPar.szBasePassword + 
				strlen((char *)InPar.szBasePassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_RenameBase &)
{
}

void
Decriptografa( TSRIn_RenameBase &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_KillSessions &InPar )
{
	Criptografa( InPar.sTicket );
}

void
Decriptografa( TSRIn_KillSessions &InPar )
{
	Decriptografa( InPar.sTicket );
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_SetNavigationLocate &)
{
}

void
Decriptografa( TSRIn_SetNavigationLocate &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_TicketPar &)
{
}

void
Decriptografa( TSRIn_TicketPar &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_AddField &InPar )
{
	if ( InPar.tfField ) {
		Criptografa( *(InPar.tfField) );
	}

	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_AddField &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_DelFieldGetFieldObj &)
{
}

void
Decriptografa( TSRIn_DelFieldGetFieldObj &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldPassword &InPar )
{
	if ( InPar.szOldPassword ) {
		Criptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + 
				strlen((char *)InPar.szOldPassword));
	}
	if ( InPar.szNewPassword ) {
		Criptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + 
				strlen((char *)InPar.szNewPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldPassword &InPar )
{
	if ( InPar.szOldPassword ) {
		Decriptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + 
				strlen((char *)InPar.szOldPassword));
	}
	if ( InPar.szNewPassword ) {
		Decriptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + 
				strlen((char *)InPar.szNewPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldName &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldName &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldDescription &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldDescription &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldSize &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldSize &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_DelFieldRepetition &)
{
}

void
Decriptografa( TSRIn_DelFieldRepetition &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetNumberOfRepetition &)
{
}

void
Decriptografa( TSRIn_GetNumberOfRepetition &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldRepetitionSize &)
{
}

void
Decriptografa( TSRIn_GetFieldRepetitionSize &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFields &)
{
}

void
Decriptografa( TSRIn_GetFields &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSROut_GetFields &InPar )
{
	for ( int i=0; i < InPar.lArrayLen; i++ ) {
		if ( InPar.psField ) {
			Criptografa( *(InPar.psField) );
		}
	}
}

void
Decriptografa( TSROut_GetFields &InPar )
{
	for ( int i=0; i < InPar.lArrayLen; i++ ) {
		if ( InPar.psField ) {
			Decriptografa( *(InPar.psField) );
		}
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_TicketBOOLPar &)
{
}

void
Decriptografa( TSRIn_TicketBOOLPar &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_SetLockTimeOut &)
{
}

void
Decriptografa( TSRIn_SetLockTimeOut &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_SetReorganizeRecQuant &)
{
}

void
Decriptografa( TSRIn_SetReorganizeRecQuant &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Nth &)
{
}

void
Decriptografa( TSRIn_Nth &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Search &)
{
}

void
Decriptografa( TSRIn_Search &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_OcList &)
{
}

void
Decriptografa( TSRIn_OcList &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_SetNavigation &)
{
}

void
Decriptografa( TSRIn_SetNavigation &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetSlotSize &)
{
}

void
Decriptografa( TSRIn_GetSlotSize &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_SearchStopWord &)
{
}

void
Decriptografa( TSRIn_SearchStopWord &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GoWord &)
{
}

void
Decriptografa( TSRIn_GoWord &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldIndexAttrib &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldIndexAttrib &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldAttrib &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_ModifyFieldAttrib &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ACLPerm &)
{
}

void
Decriptografa( TSRIn_ACLPerm &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_EnableOnLineIndex &)
{
}

void
Decriptografa( TSRIn_EnableOnLineIndex &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetSlotPutSlot &)
{
}

void
Decriptografa( TSRIn_GetSlotPutSlot &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyPassword &InPar )
{
	if ( InPar.szOldPassword ) {
		Criptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + 
				strlen((char *)InPar.szOldPassword));
	}
	if ( InPar.szNewPassword ) {
		Criptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + 
				strlen((char *)InPar.szNewPassword));
	}
}

void
Decriptografa( TSRIn_ModifyPassword &InPar )
{
	if ( InPar.szOldPassword ) {
		Decriptografa( (char *)InPar.szOldPassword, (char *)InPar.szOldPassword + 
				strlen((char *)InPar.szOldPassword));
	}
	if ( InPar.szNewPassword ) {
		Decriptografa( (char *)InPar.szNewPassword, (char *)InPar.szNewPassword + 
				strlen((char *)InPar.szNewPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyBaseType &)
{
}

void
Decriptografa( TSRIn_ModifyBaseType &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_IndexAll &)
{
}

void
Decriptografa( TSRIn_IndexAll &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_IndexString &)
{
}

void
Decriptografa( TSRIn_IndexString &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_AddStopWord &)
{
}

void
Decriptografa( TSRIn_AddStopWord &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyBaseOwnerName &InPar )
{
	if ( InPar.szCurrentPsw ) {
		Criptografa( (char *)InPar.szCurrentPsw, (char *)InPar.szCurrentPsw + 
				strlen((char *)InPar.szCurrentPsw));
	}
}

void
Decriptografa( TSRIn_ModifyBaseOwnerName &InPar )
{
	if ( InPar.szCurrentPsw ) {
		Decriptografa( (char *)InPar.szCurrentPsw, (char *)InPar.szCurrentPsw + 
				strlen((char *)InPar.szCurrentPsw));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldIndexAttrib &)
{
}

void
Decriptografa( TSRIn_GetFieldIndexAttrib &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldObj &)
{
}

void
Decriptografa( TSRIn_GetFieldObj &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldTypeId &)
{
}

void
Decriptografa( TSRIn_GetFieldTypeId &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldRepetition &)
{
}

void
Decriptografa( TSRIn_GetFieldRepetition &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetFieldRepetitionByVal &)
{
}

void
Decriptografa( TSRIn_GetFieldRepetitionByVal &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_PutFieldRepetition &)
{
}

void
Decriptografa( TSRIn_PutFieldRepetition &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ModifyFieldRepetition &)
{
}

void
Decriptografa( TSRIn_ModifyFieldRepetition &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetACLListPerm &)
{
}

void
Decriptografa( TSRIn_GetACLListPerm &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_ExchangeOperator &)
{
}

void
Decriptografa( TSRIn_ExchangeOperator &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Mask &)
{
}

void
Decriptografa( TSRIn_Mask &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Phone &)
{
}

void
Decriptografa( TSRIn_Phone &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Standardize &)
{
}

void
Decriptografa( TSRIn_Standardize &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Synonym &)
{
}

void
Decriptografa( TSRIn_Synonym &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_OL &)
{
}

void
Decriptografa( TSRIn_OL &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_Operators &)
{
}

void
Decriptografa( TSRIn_Operators &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_MGetPutFieldRep &)
{
}

void
Decriptografa( TSRIn_MGetPutFieldRep &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_GetDataObj &)
{
}

void
Decriptografa( TSRIn_GetDataObj &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_VerifyPassword &InPar )
{
	if ( InPar.szPassword ) {
		Criptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

void
Decriptografa( TSRIn_VerifyPassword &InPar )
{
	if ( InPar.szPassword ) {
		Decriptografa( (char *)InPar.szPassword, (char *)InPar.szPassword + 
				strlen((char *)InPar.szPassword));
	}
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRIn_DataOp &)
{
}

void
Decriptografa( TSRIn_DataOp &)
{
}

/////////////////////////////////////////////////////////



void
Criptografa( TSRSetError &)
{
}

void
Decriptografa( TSRSetError &)
{
}

/////////////////////////////////////////////////////////



void 
Criptografa( TSRIn_ModifyBaseName & )
{
}

void 
Decriptografa( TSRIn_ModifyBaseName & )
{
}

/////////////////////////////////////////////////////////



void 
Criptografa( TSRIn_SetSvcParam &InPar )
{
	Criptografa( InPar.sTicket );
}

void 
Decriptografa( TSRIn_SetSvcParam &InPar )
{
	Decriptografa( InPar.sTicket);
}

/////////////////////////////////////////////////////////



void 
Criptografa( TSRIn_GetBaseLongName & )
{
}

void 
Decriptografa( TSRIn_GetBaseLongName & )
{
}

/////////////////////////////////////////////////////////



void 
Criptografa( TSRIn_AllRepetitions &InPar )
{
	Criptografa( InPar.sTicket );
}

void 
Decriptografa( TSRIn_AllRepetitions &InPar )
{
	Decriptografa( InPar.sTicket);
}

/////////////////////////////////////////////////////////



void 
Criptografa( TSRIn_BreakSecurity & )
{
}

void 
Decriptografa( TSRIn_BreakSecurity & )
{
}

/////////////////////////////////////////////////////////

void
Criptografa( TSRIn_MaintBase &InPar )
{
}

void
Decriptografa( TSRIn_MaintBase &InPar )
{
}

/////////////////////////////////////////////////////////

void
Criptografa( TSRMaintBase &InPar )
{
}

void
Decriptografa( TSRMaintBase &InPar )
{
}

/////////////////////////////////////////////////////////

void
Criptografa( TSROut_MaintBase &InPar )
{
}

void
Decriptografa( TSROut_MaintBase &InPar )
{
}

/////////////////////////////////////////////////////////

int 
CCompact::Compress( unsigned char *pBuffIn, unsigned char **ppBuffOut, int iSizeIn )
{
	if ( !pBuffIn ) {
		return 0; 
	}

	ALMemory		almMyMemIn( "", (char _huge *)pBuffIn, 
								iSizeIn );
	ALMemory		almMyMemOut;

	ALGreenleafEngine	alcMyEngine( 2 );
	alcMyEngine.Compress(almMyMemIn, almMyMemOut);

	*ppBuffOut = (unsigned char *)new char[almMyMemOut.muUserBufferSize];
	if ( !*ppBuffOut ) {
		return 0;
	}

	memcpy( *ppBuffOut, almMyMemOut.mpcUserBuffer, 
			almMyMemOut.muUserBufferSize );

	return almMyMemOut.muUserBufferSize;
}

int 
CCompact::DeCompress( unsigned char *pBuffIn, unsigned char **ppBuffOut, int iSizeIn )
{

	if ( !pBuffIn ) {
		return 0; 
	}

	ALMemory		almMyMemIn( "", (char _huge *)pBuffIn, 
								iSizeIn );
	ALMemory		almMyMemOut;

	ALGreenleafEngine	alcMyEngine( 2 );
	alcMyEngine.Decompress(almMyMemIn, almMyMemOut);

	*ppBuffOut = (unsigned char *)new char[almMyMemOut.muUserBufferSize];
	if ( !*ppBuffOut ) {
		return 0;
	}

	memcpy( *ppBuffOut, almMyMemOut.mpcUserBuffer, 
			almMyMemOut.muUserBufferSize );

	return almMyMemOut.muUserBufferSize;
}

