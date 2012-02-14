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
//	Metodos para serializar e deserializar estruturas do RPC, alem de 
//	envio e recebimento de argumentos via sockets
//
//	OBS: na serializacao alocam-se buffers e na deserializacao assume-se 
//	que se copiara um buffer para uma estrutura valida 
//
//	Vladimir Catao	09/04/96
//

#ifndef _RPCSERIAL_H_
	#include <rpcserial.h>
#endif	// _RPCSERIAL_H_


void 
RPC::Serializa( TSRIn_RenameBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szOldName, Buff );  // eh um string; 
	Buff += SizeOf( Obj.szOldName );

	Serializa( Obj.szNewName, Buff );  // eh um string; 
	Buff += SizeOf( Obj.szNewName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_RenameBase Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szOldName );

	lTam += SizeOf( Obj.szNewName );

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_RenameBase *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szOldName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOldName );

	if ( !Deserializa( &Obj->szNewName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_RenameBase Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szOldName );

	Delete( Obj.szNewName );

}

	
void 
RPC::Serializa( TSRIn_KillSessions Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szAppName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szAppName );

	Serializa( Obj.szClientName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szClientName );

	Serializa( Obj.lIdApp, Buff );  
	Buff += SizeOf( Obj.lIdApp );

	Serializa( Obj.sTicket, Buff );  
	Buff += SizeOf( Obj.sTicket );

	Serializa( Obj.TSessionObj, Buff );  
	Buff += SizeOf( Obj.TSessionObj );

}

long
RPC::SizeOf( TSRIn_KillSessions Obj )
{
	long lTam=0;

	lTam += SizeOf( Obj.szAppName );

	lTam += SizeOf( Obj.szClientName );

	lTam += SizeOf( Obj.lIdApp );

	lTam += SizeOf( Obj.sTicket );

	lTam += SizeOf( Obj.TSessionObj );

	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_KillSessions *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szAppName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szAppName );

	if ( !Deserializa( &Obj->szClientName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szClientName );

	if ( !Deserializa( &Obj->lIdApp, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->lIdApp );

	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->TSessionObj, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->TSessionObj );

	return TRUE;
}

void 
RPC::Delete ( TSRIn_KillSessions Obj ) 
{
	Delete( Obj.szAppName );

	Delete( Obj.szClientName );

	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_IncorporateBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szBaseName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBaseName );

	Serializa( Obj.szBasePassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBasePassword );

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szUDBName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUDBName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_IncorporateBase Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szBaseName );

	lTam += SizeOf( Obj.szBasePassword );

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szUDBName );

	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_IncorporateBase *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBaseName );

	if ( !Deserializa( &Obj->szBasePassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBasePassword );

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDBName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_IncorporateBase Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szBaseName );

	Delete( Obj.szBasePassword );

	Delete( Obj.szUserName );

	Delete( Obj.szUDBName );

}


void 
RPC::Serializa( TSROut_WhatBases Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lTam, Buff);
	Buff += SizeOf(Obj.lTam);

	Serializa( Obj.szBuffer, Buff, Obj.lTam); 	// nao eh um string
	Buff += Obj.lTam;

}

long
RPC::SizeOf( TSROut_WhatBases Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lTam);

	lTam += Obj.lTam;

	return lTam;
}

boolean 
RPC::Deserializa( TSROut_WhatBases *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lTam, Buff);
	Buff += SizeOf(Obj->lTam);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTam) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lTam;

	return(TRUE);
}

void 
RPC::Delete ( TSROut_WhatBases Obj ) 
{
	Delete( Obj.szBuffer );

}


void 
RPC::Serializa( TSRIn_SetNavigationLocate Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lbNavState, Buff);
	Buff += SizeOf(Obj.lbNavState);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.liIndex, Buff);
	Buff += SizeOf(Obj.liIndex);
	
	Serializa( Obj.szNavKey, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNavKey );

	Serializa( Obj.liType, Buff);
	Buff += SizeOf(Obj.liType);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_SetNavigationLocate Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lbNavState);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.liIndex);
	
	lTam += SizeOf( Obj.szNavKey );

	lTam += SizeOf(Obj.liType);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SetNavigationLocate *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lbNavState, Buff);
	Buff += SizeOf(Obj->lbNavState);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->liIndex, Buff);
	Buff += SizeOf(Obj->liIndex);
	
	if ( !Deserializa( &Obj->szNavKey, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNavKey );

	Deserializa( &Obj->liType, Buff);
	Buff += SizeOf(Obj->liType);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_SetNavigationLocate Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szNavKey );

}


void 
RPC::Serializa( TSRIn_TicketPar Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_TicketPar Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_TicketPar *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_TicketPar Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_AddField Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.tfField, Buff); 
	Buff += SizeOf(Obj.tfField);

	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szFieldDescription, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldDescription );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.ltftFieldType, Buff);
	Buff += SizeOf(Obj.ltftFieldType);
	
	Serializa( Obj.lFieldSize, Buff);
	Buff += SizeOf(Obj.lFieldSize);
	
	Serializa( Obj.ltiaIndexAttrib, Buff);
	Buff += SizeOf(Obj.ltiaIndexAttrib);
	
	Serializa( Obj.lFieldAttrib, Buff);
	Buff += SizeOf(Obj.lFieldAttrib);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_AddField Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.tfField);

	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szFieldDescription );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf(Obj.ltftFieldType);
	
	lTam += SizeOf(Obj.lFieldSize);
	
	lTam += SizeOf(Obj.ltiaIndexAttrib);
	
	lTam += SizeOf(Obj.lFieldAttrib);
	
	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_AddField *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa(&Obj->tfField, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->tfField);

	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szFieldDescription, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldDescription );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	Deserializa( &Obj->ltftFieldType, Buff);
	Buff += SizeOf(Obj->ltftFieldType);
	
	Deserializa( &Obj->lFieldSize, Buff);
	Buff += SizeOf(Obj->lFieldSize);
	
	Deserializa( &Obj->ltiaIndexAttrib, Buff);
	Buff += SizeOf(Obj->ltiaIndexAttrib);
	
	Deserializa( &Obj->lFieldAttrib, Buff);
	Buff += SizeOf(Obj->lFieldAttrib);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_AddField Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.tfField );

	Delete( Obj.szFieldAliasName );

	Delete( Obj.szFieldDescription );

	Delete( Obj.szPassword );

}


void 
RPC::Serializa( TSRIn_DelFieldGetFieldObj Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_DelFieldGetFieldObj Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_DelFieldGetFieldObj *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_DelFieldGetFieldObj Obj ) 
{
	Delete( Obj.szField );

}


void 
RPC::Serializa( TSRIn_ModifyFieldPassword Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szOldPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szOldPassword );

	Serializa( Obj.szNewPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewPassword );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

long
RPC::SizeOf( TSRIn_ModifyFieldPassword Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szOldPassword );

	lTam += SizeOf( Obj.szNewPassword );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldPassword *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szOldPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOldPassword );

	if ( !Deserializa( &Obj->szNewPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewPassword );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldPassword Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szOldPassword );

	Delete( Obj.szNewPassword );

}


void 
RPC::Serializa( TSRIn_ModifyFieldName Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.szFieldNewAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldNewAliasName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldName Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf( Obj.szFieldNewAliasName );

	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldName *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	if ( !Deserializa( &Obj->szFieldNewAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldNewAliasName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldName Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szPassword );

	Delete( Obj.szFieldNewAliasName );

}


void 
RPC::Serializa( TSRIn_ModifyFieldDescription Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.szNewDescription, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewDescription );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldDescription Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf( Obj.szNewDescription );

	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldDescription *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	if ( !Deserializa( &Obj->szNewDescription, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewDescription );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldDescription Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szPassword );

	Delete( Obj.szNewDescription );

}


void 
RPC::Serializa( TSRIn_ModifyFieldSize Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.lNewSize, Buff);
	Buff += SizeOf(Obj.lNewSize);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldSize Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf(Obj.lNewSize);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldSize *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	Deserializa( &Obj->lNewSize, Buff);
	Buff += SizeOf(Obj->lNewSize);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldSize Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szPassword );

}


void 
RPC::Serializa( TSRIn_DelFieldRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.liRepNumber, Buff);
	Buff += SizeOf(Obj.liRepNumber);
	
	Serializa( Obj.bShift, Buff);
	Buff += SizeOf(Obj.bShift);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

long
RPC::SizeOf( TSRIn_DelFieldRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.liRepNumber);
	
	lTam += SizeOf(Obj.bShift);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_DelFieldRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->liRepNumber, Buff);
	Buff += SizeOf(Obj->liRepNumber);
	
	Deserializa( &Obj->bShift, Buff);
	Buff += SizeOf(Obj->bShift);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_DelFieldRepetition Obj ) 
{
	Delete( Obj.szField );

}


void 
RPC::Serializa( TSRIn_GetNumberOfRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetNumberOfRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetNumberOfRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetNumberOfRepetition Obj ) 
{
	Delete( Obj.szFieldAliasName );

}


void 
RPC::Serializa( TSRIn_GetFieldRepetitionSize Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.liRepetNumber, Buff);
	Buff += SizeOf(Obj.liRepetNumber);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

long
RPC::SizeOf( TSRIn_GetFieldRepetitionSize Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.liRepetNumber);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldRepetitionSize *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->liRepetNumber, Buff);
	Buff += SizeOf(Obj->liRepetNumber);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldRepetitionSize Obj ) 
{
	Delete( Obj.szFieldAliasName );

}


void 
RPC::Serializa( TSRIn_GetFields Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

long
RPC::SizeOf( TSRIn_GetFields Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFields *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFields Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_TicketBOOLPar Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lbPar, Buff);
	Buff += SizeOf(Obj.lbPar);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_TicketBOOLPar Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lbPar);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_TicketBOOLPar *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lbPar, Buff);
	Buff += SizeOf(Obj->lbPar);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_TicketBOOLPar Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_SetLockTimeOut Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.liNewTimeOut, Buff);
	Buff += SizeOf(Obj.liNewTimeOut);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_SetLockTimeOut Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.liNewTimeOut);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SetLockTimeOut *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->liNewTimeOut, Buff);
	Buff += SizeOf(Obj->liNewTimeOut);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_SetLockTimeOut Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_SetReorganizeRecQuant Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lNewRecQuant, Buff);
	Buff += SizeOf(Obj.lNewRecQuant);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_SetReorganizeRecQuant Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lNewRecQuant);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SetReorganizeRecQuant *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lNewRecQuant, Buff);
	Buff += SizeOf(Obj->lNewRecQuant);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_SetReorganizeRecQuant Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_Nth Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.liPos, Buff);
	Buff += SizeOf(Obj.liPos);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Nth Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.liPos);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Nth *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->liPos, Buff);
	Buff += SizeOf(Obj->liPos);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Nth Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_Search Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szBuffer, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBuffer );

	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Search Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szBuffer );

	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Search *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szBuffer, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBuffer );

	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Search Obj ) 
{
	Delete( Obj.szBuffer );

	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_OcList Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.liHandle, Buff);
	Buff += SizeOf(Obj.liHandle);
	
	Serializa( Obj.lStatus, Buff);
	Buff += SizeOf(Obj.lStatus);
	
	Serializa( Obj.szName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szName );

	Serializa( Obj.szExpr, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szExpr );

	Serializa( Obj.lbCopy, Buff);
	Buff += SizeOf(Obj.lbCopy);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_OcList Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.liHandle);
	
	lTam += SizeOf(Obj.lStatus);
	
	lTam += SizeOf( Obj.szName );

	lTam += SizeOf( Obj.szExpr );

	lTam += SizeOf(Obj.lbCopy);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_OcList *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->liHandle, Buff);
	Buff += SizeOf(Obj->liHandle);
	
	Deserializa( &Obj->lStatus, Buff);
	Buff += SizeOf(Obj->lStatus);
	
	if ( !Deserializa( &Obj->szName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szName );

	if ( !Deserializa( &Obj->szExpr, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szExpr );

	Deserializa( &Obj->lbCopy, Buff);
	Buff += SizeOf(Obj->lbCopy);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_OcList Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szName );

	Delete( Obj.szExpr );

}


void 
RPC::Serializa( TSRIn_SetNavigation Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lbNavState, Buff);
	Buff += SizeOf(Obj.lbNavState);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.liIndex, Buff);
	Buff += SizeOf(Obj.liIndex);
	
	Serializa( Obj.szKey, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szKey );

	Serializa( Obj.liType, Buff);
	Buff += SizeOf(Obj.liType);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_SetNavigation Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lbNavState);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.liIndex);
	
	lTam += SizeOf( Obj.szKey );

	lTam += SizeOf(Obj.liType);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SetNavigation *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lbNavState, Buff);
	Buff += SizeOf(Obj->lbNavState);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->liIndex, Buff);
	Buff += SizeOf(Obj->liIndex);
	
	if ( !Deserializa( &Obj->szKey, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szKey );

	Deserializa( &Obj->liType, Buff);
	Buff += SizeOf(Obj->liType);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_SetNavigation Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szKey );

}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRIn_GetSlotSize Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRIn_GetSlotSize);
	memcpy( Buff, &Obj, lTam );
}

long
RPC::SizeOf( TSRIn_GetSlotSize Obj )
{
	return ( sizeof(Obj) ); 
}

void
RPC::Delete( TSRIn_GetSlotSize )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRIn_GetSlotSize *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRIn_GetSlotSize *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSRIn_SearchStopWord Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szStopWord, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szStopWord );

	Serializa( Obj.liTypeSearch, Buff);
	Buff += SizeOf(Obj.liTypeSearch);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_SearchStopWord Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szStopWord );

	lTam += SizeOf(Obj.liTypeSearch);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SearchStopWord *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szStopWord, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szStopWord );

	Deserializa( &Obj->liTypeSearch, Buff);
	Buff += SizeOf(Obj->liTypeSearch);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_SearchStopWord Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szStopWord );

}


void 
RPC::Serializa( TSRIn_GoWord Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldObj, Buff);
	Buff += SizeOf(Obj.lFieldObj);
	
	Serializa( Obj.liPos, Buff);
	Buff += SizeOf(Obj.liPos);
	
	Serializa( Obj.lId, Buff);
	Buff += SizeOf(Obj.lId);
	
	Serializa( Obj.szGoWord, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szGoWord );

	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lMinKeySize, Buff);
	Buff += SizeOf(Obj.lMinKeySize);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GoWord Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldObj);
	
	lTam += SizeOf(Obj.liPos);
	
	lTam += SizeOf(Obj.lId);
	
	lTam += SizeOf( Obj.szGoWord );

	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lMinKeySize);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GoWord *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldObj, Buff);
	Buff += SizeOf(Obj->lFieldObj);
	
	Deserializa( &Obj->liPos, Buff);
	Buff += SizeOf(Obj->liPos);
	
	Deserializa( &Obj->lId, Buff);
	Buff += SizeOf(Obj->lId);
	
	if ( !Deserializa( &Obj->szGoWord, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szGoWord );

	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lMinKeySize, Buff);
	Buff += SizeOf(Obj->lMinKeySize);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GoWord Obj ) 
{
	Delete( Obj.szGoWord );

	Delete( Obj.szField );
}


void 
RPC::Serializa( TSRIn_ModifyFieldIndexAttrib Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.liIndexAttrib, Buff);
	Buff += SizeOf(Obj.liIndexAttrib);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldIndexAttrib Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf(Obj.liIndexAttrib);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldIndexAttrib *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	Deserializa( &Obj->liIndexAttrib, Buff);
	Buff += SizeOf(Obj->liIndexAttrib);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldIndexAttrib Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szPassword );

}


void 
RPC::Serializa( TSRIn_ModifyFieldAttrib Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.uiAttrib, Buff);
	Buff += SizeOf(Obj.uiAttrib);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldAttrib Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf(Obj.uiAttrib);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldAttrib *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	Deserializa( &Obj->uiAttrib, Buff);
	Buff += SizeOf(Obj->uiAttrib);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldAttrib Obj ) 
{
	Delete( Obj.szFieldAliasName );

	Delete( Obj.szPassword );

}

void 
RPC::Serializa( TSRIn_ACLPerm Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szName );

	Serializa( Obj.lId, Buff);
	Buff += SizeOf(Obj.lId);
	
	Serializa( Obj.szId, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szId );

	Serializa( Obj.bMask, Buff);
	Buff += SizeOf(Obj.bMask);
	
	Serializa( Obj.liList, Buff);
	Buff += SizeOf(Obj.liList);
	
	Serializa( Obj.bCheckAll, Buff);
	Buff += SizeOf(Obj.bCheckAll);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ACLPerm Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.szName);

	lTam += SizeOf(Obj.lId);
	
	lTam += SizeOf(Obj.szId);

	lTam += SizeOf(Obj.bMask);
	
	lTam += SizeOf(Obj.liList);
	
	lTam += SizeOf(Obj.bCheckAll);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ACLPerm *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szName );

	Deserializa( &Obj->lId, Buff);
	Buff += SizeOf(Obj->lId);
	
	if ( !Deserializa( &Obj->szId, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szId );

	Deserializa( &Obj->bMask, Buff);
	Buff += SizeOf(Obj->bMask);
	
	Deserializa( &Obj->liList, Buff);
	Buff += SizeOf(Obj->liList);
	
	Deserializa( &Obj->bCheckAll, Buff);
	Buff += SizeOf(Obj->bCheckAll);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ACLPerm Obj ) 
{
	Delete( Obj.szName );
	Delete( Obj.szId );

}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRIn_EnableOnLineIndex Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRIn_EnableOnLineIndex);
	memcpy(Buff, &Obj, lTam );
}

long 
RPC::SizeOf( TSRIn_EnableOnLineIndex Obj )
{
	return sizeof(TSRIn_EnableOnLineIndex);
}

void
RPC::Delete( TSRIn_EnableOnLineIndex )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRIn_EnableOnLineIndex *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRIn_EnableOnLineIndex *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSRIn_GetSlotPutSlot Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.liIndex, Buff);
	Buff += SizeOf(Obj.liIndex);
	
	Serializa( Obj.lBufferLen, Buff);
	Buff += SizeOf(Obj.lBufferLen);
	
	Serializa( Obj.szBuffer, Buff, Obj.lBufferLen); // nao eh um string; 
	Buff += Obj.lBufferLen;

	Serializa( Obj.luiId, Buff);
	Buff += SizeOf(Obj.luiId);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetSlotPutSlot Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.liIndex);
	
	lTam += SizeOf(Obj.lBufferLen);
	
	lTam += Obj.lBufferLen;

	lTam += SizeOf(Obj.luiId);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetSlotPutSlot *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->liIndex, Buff);
	Buff += SizeOf(Obj->liIndex);
	
	Deserializa( &Obj->lBufferLen, Buff);
	Buff += SizeOf(Obj->lBufferLen);
	
	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lBufferLen) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lBufferLen;

	Deserializa( &Obj->luiId, Buff);
	Buff += SizeOf(Obj->luiId);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetSlotPutSlot Obj ) 
{
	Delete( Obj.szBuffer );

}


void 
RPC::Serializa( TSRIn_ModifyPassword Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szOldPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szOldPassword );

	Serializa( Obj.szNewPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewPassword );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyPassword Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szOldPassword );

	lTam += SizeOf( Obj.szNewPassword );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyPassword *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szOldPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOldPassword );

	if ( !Deserializa( &Obj->szNewPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewPassword );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyPassword Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szOldPassword );

	Delete( Obj.szNewPassword );

}


