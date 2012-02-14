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


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSROut_GetFullBaseName Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSROut_GetFullBaseName);
	memcpy(Buff, &Obj, lTam );
}

long
RPC::SizeOf( TSROut_GetFullBaseName Obj )
{
	return sizeof(TSROut_GetFullBaseName);
}

void
RPC::Delete( TSROut_GetFullBaseName )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSROut_GetFullBaseName *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSROut_GetFullBaseName *)Buff;
	return(TRUE);	
}



//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRIn_ModifyBaseType Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRIn_ModifyBaseType);
	memcpy(Buff, &Obj, lTam );
}

long
RPC::SizeOf( TSRIn_ModifyBaseType Obj )
{
	return sizeof(TSRIn_ModifyBaseType);
}

void
RPC::Delete( TSRIn_ModifyBaseType )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRIn_ModifyBaseType *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRIn_ModifyBaseType *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSRIn_IndexAll Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.bRestoreContext, Buff);
	Buff += SizeOf(Obj.bRestoreContext);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_IndexAll Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.bRestoreContext);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_IndexAll *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->bRestoreContext, Buff);
	Buff += SizeOf(Obj->bRestoreContext);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_IndexAll Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_IndexString Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lRec, Buff);
	Buff += SizeOf(Obj.lRec);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.lRepet, Buff);
	Buff += SizeOf(Obj.lRepet);
	
	Serializa( Obj.szStr, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szStr );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_IndexString Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lRec);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.lRepet);
	
	lTam += SizeOf( Obj.szStr );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_IndexString *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lRec, Buff);
	Buff += SizeOf(Obj->lRec);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->lRepet, Buff);
	Buff += SizeOf(Obj->lRepet);
	
	if ( !Deserializa( &Obj->szStr, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szStr );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_IndexString Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szStr );

}


void 
RPC::Serializa( TSRIn_AddStopWord Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szSW, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szSW );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_AddStopWord Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szSW );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_AddStopWord *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szSW, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szSW );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_AddStopWord Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szSW );

}


void 
RPC::Serializa( TSRIn_ModifyBaseOwnerName Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szOwnerNamePar, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szOwnerNamePar );

	Serializa( Obj.szCurrentPsw, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szCurrentPsw );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyBaseOwnerName Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szOwnerNamePar );

	lTam += SizeOf( Obj.szCurrentPsw );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyBaseOwnerName *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szOwnerNamePar, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOwnerNamePar );

	if ( !Deserializa( &Obj->szCurrentPsw, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szCurrentPsw );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyBaseOwnerName Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szOwnerNamePar );

	Delete( Obj.szCurrentPsw );

}


void 
RPC::Serializa( TSRIn_GetFieldIndexAttrib Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldAliasName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldAliasName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetFieldIndexAttrib Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldAliasName );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldIndexAttrib *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldAliasName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldIndexAttrib Obj ) 
{
	Delete( Obj.szFieldAliasName );

}


void 
RPC::Serializa( TSRIn_GetFieldObj Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lFieldObj, Buff);
	Buff += SizeOf(Obj.lFieldObj);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetFieldObj Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lFieldObj);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldName );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldObj *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lFieldObj, Buff);
	Buff += SizeOf(Obj->lFieldObj);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldObj Obj ) 
{
	Delete( Obj.szFieldName );

}


void 
RPC::Serializa( TSRIn_GetFieldTypeId Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.bTipoGetFieldType, Buff);
	Buff += SizeOf(Obj.bTipoGetFieldType);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.szFieldName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetFieldTypeId Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.bTipoGetFieldType);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf( Obj.szFieldName );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldTypeId *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->bTipoGetFieldType, Buff);
	Buff += SizeOf(Obj->bTipoGetFieldType);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	if ( !Deserializa( &Obj->szFieldName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldTypeId Obj ) 
{
	Delete( Obj.szFieldName );

}


void 
RPC::Serializa( TSRIn_GetFieldRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBase, Buff);
	Buff += SizeOf(Obj.lBase);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sMethod, Buff);
	Buff += SizeOf(Obj.sMethod);
	
	Serializa( Obj.lRepNumber, Buff);
	Buff += SizeOf(Obj.lRepNumber);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetFieldRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBase);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sMethod);
	
	lTam += SizeOf(Obj.lRepNumber);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBase, Buff);
	Buff += SizeOf(Obj->lBase);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sMethod, Buff);
	Buff += SizeOf(Obj->sMethod);
	
	Deserializa( &Obj->lRepNumber, Buff);
	Buff += SizeOf(Obj->lRepNumber);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldRepetition Obj ) 
{
	Delete( Obj.szField );

}


void 
RPC::Serializa( TSRIn_GetFieldRepetitionByVal Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBase, Buff);
	Buff += SizeOf(Obj.lBase);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sMethod, Buff);
	Buff += SizeOf(Obj.sMethod);
	
	Serializa( Obj.lTam, Buff);
	Buff += SizeOf(Obj.lTam);
	
	Serializa( Obj.Rep, Buff, Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;

	Serializa( Obj.bStart, Buff);
	Buff += SizeOf(Obj.bStart);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetFieldRepetitionByVal Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBase);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sMethod);
	
	lTam += SizeOf(Obj.lTam);
	
	lTam += Obj.lTam;

	lTam += SizeOf(Obj.bStart);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetFieldRepetitionByVal *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBase, Buff);
	Buff += SizeOf(Obj->lBase);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sMethod, Buff);
	Buff += SizeOf(Obj->sMethod);
	
	Deserializa( &Obj->lTam, Buff);
	Buff += SizeOf(Obj->lTam);
	
	if ( !Deserializa( &Obj->Rep, Buff, Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;

	Deserializa( &Obj->bStart, Buff);
	Buff += SizeOf(Obj->bStart);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetFieldRepetitionByVal Obj ) 
{
	Delete( Obj.szField );

	Delete( Obj.Rep );

}


void 
RPC::Serializa( TSRIn_PutFieldRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBase, Buff);
	Buff += SizeOf(Obj.lBase);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sMethod, Buff);
	Buff += SizeOf(Obj.sMethod);
	
	Serializa( Obj.lTam, Buff);
	Buff += SizeOf(Obj.lTam);
	
	Serializa( Obj.Rep, Buff, Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;

	Serializa( Obj.lIndex, Buff);
	Buff += SizeOf(Obj.lIndex);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_PutFieldRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBase);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sMethod);
	
	lTam += SizeOf(Obj.lTam);
	
	lTam += Obj.lTam;

	lTam += SizeOf(Obj.lIndex);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_PutFieldRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBase, Buff);
	Buff += SizeOf(Obj->lBase);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sMethod, Buff);
	Buff += SizeOf(Obj->sMethod);
	
	Deserializa( &Obj->lTam, Buff);
	Buff += SizeOf(Obj->lTam);
	
	if ( !Deserializa( &Obj->Rep, Buff, Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;

	Deserializa( &Obj->lIndex, Buff);
	Buff += SizeOf(Obj->lIndex);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_PutFieldRepetition Obj ) 
{
	Delete( Obj.szField );

	Delete( Obj.Rep );

}


void 
RPC::Serializa( TSRIn_ModifyFieldRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBase, Buff);
	Buff += SizeOf(Obj.lBase);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.lRepNumber, Buff);
	Buff += SizeOf(Obj.lRepNumber);
	
	Serializa( Obj.sMethod, Buff);
	Buff += SizeOf(Obj.sMethod);
	
	Serializa( Obj.lTam, Buff);
	Buff += SizeOf(Obj.lTam);
	
	Serializa( Obj.Rep, Buff, Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ModifyFieldRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBase);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.lRepNumber);
	
	lTam += SizeOf(Obj.sMethod);
	
	lTam += SizeOf(Obj.lTam);
	
	lTam += Obj.lTam;

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyFieldRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBase, Buff);
	Buff += SizeOf(Obj->lBase);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->lRepNumber, Buff);
	Buff += SizeOf(Obj->lRepNumber);
	
	Deserializa( &Obj->sMethod, Buff);
	Buff += SizeOf(Obj->sMethod);
	
	Deserializa( &Obj->lTam, Buff);
	Buff += SizeOf(Obj->lTam);
	
	if ( !Deserializa( &Obj->Rep, Buff, Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ModifyFieldRepetition Obj ) 
{
	Delete( Obj.szField );

	Delete( Obj.Rep );

}


void 
RPC::Serializa( TSRIn_GetACLListPerm Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBase, Buff);
	Buff += SizeOf(Obj.lBase);
	
	Serializa( Obj.szName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szName );

	Serializa( Obj.lList, Buff);
	Buff += SizeOf(Obj.lList);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_GetACLListPerm Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBase);
	
	lTam += SizeOf( Obj.szName );

	lTam += SizeOf(Obj.lList);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetACLListPerm *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBase, Buff);
	Buff += SizeOf(Obj->lBase);
	
	if ( !Deserializa( &Obj->szName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szName );

	Deserializa( &Obj->lList, Buff);
	Buff += SizeOf(Obj->lList);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_GetACLListPerm Obj ) 
{
	Delete( Obj.szName );

}


void 
RPC::Serializa( TSRIn_ExchangeOperator Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szNewOp, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewOp );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_ExchangeOperator Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szNewOp );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ExchangeOperator *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szNewOp, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewOp );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_ExchangeOperator Obj ) 
{
	Delete( Obj.szNewOp );

}


void 
RPC::Serializa( TSRIn_Mask Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szMasks, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szMasks );

	Serializa( Obj.szFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFileName );

	Serializa( Obj.liIndex, Buff);
	Buff += SizeOf(Obj.liIndex);
	
	Serializa( Obj.liType, Buff);
	Buff += SizeOf(Obj.liType);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Mask Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szMasks );

	lTam += SizeOf( Obj.szFileName );

	lTam += SizeOf(Obj.liIndex);
	
	lTam += SizeOf(Obj.liType);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Mask *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szMasks, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szMasks );

	if ( !Deserializa( &Obj->szFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFileName );

	Deserializa( &Obj->liIndex, Buff);
	Buff += SizeOf(Obj->liIndex);
	
	Deserializa( &Obj->liType, Buff);
	Buff += SizeOf(Obj->liType);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Mask Obj ) 
{
	Delete( Obj.szMasks );

	Delete( Obj.szFileName );

}


void 
RPC::Serializa( TSRIn_Phone Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szPhoneArray, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPhoneArray );

	Serializa( Obj.szFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFileName );

	Serializa( Obj.szPhoneValue, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPhoneValue );

	Serializa( Obj.szTerm, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szTerm );

	Serializa( Obj.liPhoneNumber, Buff);
	Buff += SizeOf(Obj.liPhoneNumber);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Phone Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szPhoneArray );

	lTam += SizeOf( Obj.szFileName );

	lTam += SizeOf( Obj.szPhoneValue );

	lTam += SizeOf( Obj.szTerm );

	lTam += SizeOf(Obj.liPhoneNumber);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Phone *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szPhoneArray, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPhoneArray );

	if ( !Deserializa( &Obj->szFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFileName );

	if ( !Deserializa( &Obj->szPhoneValue, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPhoneValue );

	if ( !Deserializa( &Obj->szTerm, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szTerm );

	Deserializa( &Obj->liPhoneNumber, Buff);
	Buff += SizeOf(Obj->liPhoneNumber);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Phone Obj ) 
{
	Delete( Obj.szPhoneArray );

	Delete( Obj.szFileName );

	Delete( Obj.szPhoneValue );

	Delete( Obj.szTerm );

}


void 
RPC::Serializa( TSRIn_Standardize Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szStandardizerArray, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szStandardizerArray );

	Serializa( Obj.szContent, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szContent );

	Serializa( Obj.szDestination, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szDestination );

	Serializa( Obj.liSize, Buff);
	Buff += SizeOf(Obj.liSize);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Standardize Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szStandardizerArray );

	lTam += SizeOf( Obj.szContent );

	lTam += SizeOf( Obj.szDestination );

	lTam += SizeOf(Obj.liSize);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Standardize *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szStandardizerArray, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szStandardizerArray );

	if ( !Deserializa( &Obj->szContent, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szContent );

	if ( !Deserializa( &Obj->szDestination, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szDestination );

	Deserializa( &Obj->liSize, Buff);
	Buff += SizeOf(Obj->liSize);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Standardize Obj ) 
{	
	Delete( Obj.szStandardizerArray );

	Delete( Obj.szContent );

	Delete( Obj.szDestination );

}


void 
RPC::Serializa( TSRIn_Synonym Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.szTerm, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szTerm );

	Serializa( Obj.szSynonymArray, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szSynonymArray );

	Serializa( Obj.szFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFileName );

	Serializa( Obj.liFlag, Buff);
	Buff += SizeOf(Obj.liFlag);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Synonym Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf( Obj.szTerm );

	lTam += SizeOf( Obj.szSynonymArray );

	lTam += SizeOf( Obj.szFileName );

	lTam += SizeOf(Obj.liFlag);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Synonym *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->szTerm, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szTerm );

	if ( !Deserializa( &Obj->szSynonymArray, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szSynonymArray );

	if ( !Deserializa( &Obj->szFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFileName );

	Deserializa( &Obj->liFlag, Buff);
	Buff += SizeOf(Obj->liFlag);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Synonym Obj ) 
{	
	Delete( Obj.szTerm );

	Delete( Obj.szSynonymArray );

	Delete( Obj.szFileName );

}


void 
RPC::Serializa( TSRIn_OL Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.liHandle1, Buff);
	Buff += SizeOf(Obj.liHandle1);
	
	Serializa( Obj.liHandle2, Buff);
	Buff += SizeOf(Obj.liHandle2);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_OL Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.liHandle1);
	
	lTam += SizeOf(Obj.liHandle2);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_OL *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->liHandle1, Buff);
	Buff += SizeOf(Obj->liHandle1);
	
	Deserializa( &Obj->liHandle2, Buff);
	Buff += SizeOf(Obj->liHandle2);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_OL Obj ) 
{	
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_Operators Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lFieldObj, Buff);
	Buff += SizeOf(Obj.lFieldObj);
	
	Serializa( Obj.lField, Buff);
	Buff += SizeOf(Obj.lField);
	
	Serializa( Obj.szField, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szField );

	Serializa( Obj.lFieldNumber, Buff);
	Buff += SizeOf(Obj.lFieldNumber);
	
	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_Operators Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lFieldObj);
	
	lTam += SizeOf(Obj.lField);
	
	lTam += SizeOf( Obj.szField );

	lTam += SizeOf(Obj.lFieldNumber);
	
	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_Operators *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lFieldObj, Buff);
	Buff += SizeOf(Obj->lFieldObj);
	
	Deserializa( &Obj->lField, Buff);
	Buff += SizeOf(Obj->lField);
	
	if ( !Deserializa( &Obj->szField, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szField );

	Deserializa( &Obj->lFieldNumber, Buff);
	Buff += SizeOf(Obj->lFieldNumber);
	
	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_Operators Obj ) 
{	
	Delete( Obj.szField );

}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRSetError Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRSetError);
	memcpy(Buff, &Obj, lTam );
}


long
RPC::SizeOf(TSRSetError)
{
	return sizeof(TSRSetError);
}

void
RPC::Delete( TSRSetError )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRSetError *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRSetError *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSROut_Search Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lArrayLen, Buff);
	Buff += SizeOf(Obj.lArrayLen);

	Serializa( Obj.pLong, Buff, Obj.lArrayLen); 	// array de longs
	Buff += SizeOf(Obj.pLong, Obj.lArrayLen);
}

long
RPC::SizeOf( TSROut_Search Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lArrayLen);

	lTam += SizeOf(Obj.pLong, Obj.lArrayLen);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_Search *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lArrayLen, Buff);
	Buff += SizeOf(Obj->lArrayLen);

	if ( !Deserializa( &Obj->pLong, Buff, Obj->lArrayLen) ) 	// array de longs
		return FALSE;
	Buff += SizeOf(Obj->pLong, Obj->lArrayLen);

	return(TRUE);
}

void 
RPC::Delete ( TSROut_Search Obj ) 
{	
	Delete( Obj.pLong );

}


void 
RPC::Serializa( TSROut_GetFields Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lArrayLen, Buff);
	Buff += SizeOf(Obj.lArrayLen);

	Serializa( Obj.psField, Buff, Obj.lArrayLen); 	// array de TSRFields
	Buff += SizeOf(Obj.psField, Obj.lArrayLen );

}

long
RPC::SizeOf( TSROut_GetFields Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lArrayLen);

	lTam += SizeOf(Obj.psField, Obj.lArrayLen );
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetFields *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lArrayLen, Buff);
	Buff += SizeOf(Obj->lArrayLen);

	if ( !Deserializa( &Obj->psField, Buff, Obj->lArrayLen) ) 	// array de TSRFields
		return FALSE;
	Buff += SizeOf(Obj->psField, Obj->lArrayLen );

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetFields Obj ) 
{	
	Delete( Obj.psField );

}


void 
RPC::Serializa( TSROut_LBSC_Occurrence Obj, unsigned char *Buff ) 
{
	Serializa( Obj.pszTerm, Buff ); // eh um string; 
	Buff += SizeOf( Obj.pszTerm );

	Serializa( Obj.lRec, Buff);
	Buff += SizeOf(Obj.lRec);
	
	Serializa( Obj.liField, Buff);
	Buff += SizeOf(Obj.liField);
	
	Serializa( Obj.liRepetition, Buff);
	Buff += SizeOf(Obj.liRepetition);
	
	Serializa( Obj.liParagraph, Buff);
	Buff += SizeOf(Obj.liParagraph);
	
	Serializa( Obj.liPhrase, Buff);
	Buff += SizeOf(Obj.liPhrase);
	
	Serializa( Obj.liSequence, Buff);
	Buff += SizeOf(Obj.liSequence);
	
	Serializa( Obj.liLastError, Buff);
	Buff += SizeOf(Obj.liLastError);
}

long
RPC::SizeOf( TSROut_LBSC_Occurrence Obj )
{
	long lTam=0;
	
	lTam += SizeOf( Obj.pszTerm );

	lTam += SizeOf(Obj.lRec);
	
	lTam += SizeOf(Obj.liField);
	
	lTam += SizeOf(Obj.liRepetition);
	
	lTam += SizeOf(Obj.liParagraph);
	
	lTam += SizeOf(Obj.liPhrase);
	
	lTam += SizeOf(Obj.liSequence);
	
	lTam += SizeOf(Obj.liLastError);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_LBSC_Occurrence *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->pszTerm, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->pszTerm );

	Deserializa( &Obj->lRec, Buff);
	Buff += SizeOf(Obj->lRec);
	
	Deserializa( &Obj->liField, Buff);
	Buff += SizeOf(Obj->liField);
	
	Deserializa( &Obj->liRepetition, Buff);
	Buff += SizeOf(Obj->liRepetition);
	
	Deserializa( &Obj->liParagraph, Buff);
	Buff += SizeOf(Obj->liParagraph);
	
	Deserializa( &Obj->liPhrase, Buff);
	Buff += SizeOf(Obj->liPhrase);
	
	Deserializa( &Obj->liSequence, Buff);
	Buff += SizeOf(Obj->liSequence);
	
	Deserializa( &Obj->liLastError, Buff);
	Buff += SizeOf(Obj->liLastError);
	
	return TRUE;
}

void 
RPC::Delete ( TSROut_LBSC_Occurrence Obj ) 
{	
	Delete( Obj.pszTerm );

}


void 
RPC::Serializa( TSROut_GetSlot Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBufferLen, Buff);
	Buff += SizeOf(Obj.lBufferLen);

	Serializa( Obj.szBuffer, Buff, Obj.lBufferLen); 	// nao eh um string
	Buff += Obj.lBufferLen;

	Serializa( Obj.lRet, Buff);
	Buff += SizeOf(Obj.lRet);
}

long
RPC::SizeOf( TSROut_GetSlot Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBufferLen);

	lTam += Obj.lBufferLen;

	lTam += SizeOf(Obj.lRet);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetSlot *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBufferLen, Buff);
	Buff += SizeOf(Obj->lBufferLen);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lBufferLen) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lBufferLen;

	Deserializa( &Obj->lRet, Buff);
	Buff += SizeOf(Obj->lRet);

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetSlot Obj ) 
{	
	Delete( Obj.szBuffer );

}


void 
RPC::Serializa( TSROut_GetFieldRepetition Obj, unsigned char *Buff ) 
{
	Serializa( Obj.usLen, Buff);
	Buff += SizeOf(Obj.usLen);

	Serializa( Obj.Return, Buff, Obj.usLen); 	// nao eh um string
	Buff += Obj.usLen;

	Serializa( Obj.lRet, Buff);
	Buff += SizeOf(Obj.lRet);
}

long
RPC::SizeOf( TSROut_GetFieldRepetition Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.usLen);

	lTam += Obj.usLen;

	lTam += SizeOf(Obj.lRet);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetFieldRepetition *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->usLen, Buff);
	Buff += SizeOf(Obj->usLen);

	if ( !Deserializa( &Obj->Return, Buff, Obj->usLen) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->usLen;

	Deserializa( &Obj->lRet, Buff);
	Buff += SizeOf(Obj->lRet);

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetFieldRepetition Obj ) 
{	
	Delete( Obj.Return );

}


void 
RPC::Serializa( TSROut_GetFieldObj Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szFieldName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFieldName );

	Serializa( Obj.lFieldId, Buff);
	Buff += SizeOf(Obj.lFieldId);
	
	Serializa( Obj.lFieldObj, Buff);
	Buff += SizeOf(Obj.lFieldObj);
}

long
RPC::SizeOf( TSROut_GetFieldObj Obj )
{
	long lTam=0;
	
	lTam += SizeOf( Obj.szFieldName );

	lTam += SizeOf(Obj.lFieldId);
	
	lTam += SizeOf(Obj.lFieldObj);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetFieldObj *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szFieldName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFieldName );

	Deserializa( &Obj->lFieldId, Buff);
	Buff += SizeOf(Obj->lFieldId);
	
	Deserializa( &Obj->lFieldObj, Buff);
	Buff += SizeOf(Obj->lFieldObj);
	
	return TRUE;
}

void 
RPC::Delete ( TSROut_GetFieldObj Obj ) 
{	
	Delete( Obj.szFieldName );

}


void 
RPC::Serializa( TSROut_BaseInfo Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szUDBName, Buff );
	Buff += SizeOf(Obj.szUDBName);

	Serializa( Obj.szOwnerName, Buff ); 
	Buff += SizeOf(Obj.szOwnerName);

	Serializa( Obj.szLastUser, Buff ); 
	Buff += SizeOf(Obj.szLastUser);

	Serializa( Obj.szUsers, Buff); 
	Buff += SizeOf( Obj.szUsers );

	Serializa( Obj.szServerName, Buff ); 
	Buff += SizeOf(Obj.szServerName);

	Serializa( Obj.lNumInst, Buff);
	Buff += SizeOf(Obj.lNumInst);

	Serializa( Obj.lCreateDate, Buff )  ;
	Buff += SizeOf(Obj.lCreateDate);

	Serializa( Obj.lLastModifyDate, Buff )  ;
	Buff += SizeOf(Obj.lLastModifyDate);

	Serializa( Obj.lBaseType, Buff )  ;
	Buff += SizeOf(Obj.lBaseType);

	Serializa( Obj.lSlotNum, Buff )  ;
	Buff += SizeOf(Obj.lSlotNum);

	Serializa( Obj.lCountNum, Buff )  ;
	Buff += SizeOf(Obj.lCountNum );

	Serializa( Obj.lMaxKeySize, Buff )  ;
	Buff += SizeOf(Obj.lMaxKeySize);

	Serializa( Obj.lIntPart, Buff )  ;
	Buff += SizeOf(Obj.lIntPart);

	Serializa( Obj.lDecPart, Buff )  ;
	Buff += SizeOf(Obj.lDecPart);

	Serializa( Obj.lIsEncrypt, Buff )  ;
	Buff += SizeOf(Obj.lIsEncrypt);

	Serializa( Obj.lReExport, Buff )  ;
	Buff += SizeOf(Obj.lReExport);
}

long
RPC::SizeOf( TSROut_BaseInfo Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.szUDBName);

	lTam += SizeOf(Obj.szOwnerName);

	lTam += SizeOf(Obj.szLastUser);

	lTam += SizeOf( Obj.szUsers );

	lTam += SizeOf(Obj.szServerName);

	lTam += SizeOf(Obj.lNumInst);

	lTam += SizeOf(Obj.lCreateDate);

	lTam += SizeOf(Obj.lLastModifyDate);

	lTam += SizeOf(Obj.lBaseType);

	lTam += SizeOf(Obj.lSlotNum);

	lTam += SizeOf(Obj.lCountNum );

	lTam += SizeOf(Obj.lMaxKeySize);

	lTam += SizeOf(Obj.lIntPart);

	lTam += SizeOf(Obj.lDecPart);

	lTam += SizeOf(Obj.lIsEncrypt);

	lTam += SizeOf(Obj.lReExport);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_BaseInfo *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( Obj->szUDBName, Buff, 0) ) // string estatica; nao precisa alocar
		return FALSE;
	Buff += SizeOf(Obj->szUDBName);

	if ( !Deserializa( Obj->szOwnerName, Buff, 0 ) ) // string estatica; nao precisa alocar
		return FALSE;
	Buff += SizeOf(Obj->szOwnerName);

	if ( !Deserializa( Obj->szLastUser, Buff, 0 ) ) // string estatica; nao precisa alocar
		return FALSE;
	Buff += SizeOf(Obj->szLastUser);

	if ( !Deserializa( &Obj->szUsers, Buff) ) // eh string
		return FALSE;
	Buff += SizeOf( Obj->szUsers );
																	   
	if ( !Deserializa( Obj->szServerName, Buff, 0 ) ) // string estatica; nao precisa alocar
		return FALSE;
	Buff += SizeOf(Obj->szServerName);

	Deserializa( &Obj->lNumInst, Buff);
	Buff += SizeOf(Obj->lNumInst);

	Deserializa( &Obj->lCreateDate, Buff )  ;
	Buff += SizeOf(Obj->lCreateDate);

	Deserializa( &Obj->lLastModifyDate, Buff )  ;
	Buff += SizeOf(Obj->lLastModifyDate);

	Deserializa( &Obj->lBaseType, Buff )  ;
	Buff += SizeOf(Obj->lBaseType);

	Deserializa( &Obj->lSlotNum, Buff )  ;
	Buff += SizeOf(Obj->lSlotNum);

	Deserializa( &Obj->lCountNum, Buff )  ;
	Buff += SizeOf(Obj->lCountNum );

	Deserializa( &Obj->lMaxKeySize, Buff )  ;
	Buff += SizeOf(Obj->lMaxKeySize);

	Deserializa( &Obj->lIntPart, Buff )  ;
	Buff += SizeOf(Obj->lIntPart);

	Deserializa( &Obj->lDecPart, Buff )  ;
	Buff += SizeOf(Obj->lDecPart);

	Deserializa( &Obj->lIsEncrypt, Buff )  ;
	Buff += SizeOf(Obj->lIsEncrypt);

	Deserializa( &Obj->lReExport, Buff )  ;
	Buff += SizeOf(Obj->lReExport);

	return TRUE;
}

void 
RPC::Delete ( TSROut_BaseInfo Obj ) 
{	
	Delete( Obj.szUsers );
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRIn_GetDataObj Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRIn_GetDataObj);
	memcpy(Buff, &Obj, lTam );
}

long 
RPC::SizeOf( TSRIn_GetDataObj )
{
	return sizeof(TSRIn_GetDataObj);
}

void
RPC::Delete( TSRIn_GetDataObj )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRIn_GetDataObj *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRIn_GetDataObj *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSRIn_VerifyPassword Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lFieldObj, Buff);
	Buff += SizeOf(Obj.lFieldObj);

	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_VerifyPassword Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lFieldObj);

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_VerifyPassword *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lFieldObj, Buff);
	Buff += SizeOf(Obj->lFieldObj);

	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_VerifyPassword Obj ) 
{	
	Delete( Obj.szPassword );

}


void 
RPC::Serializa( TSRIn_DataOp Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lDataObj, Buff);
	Buff += SizeOf(Obj.lDataObj);

	Serializa( Obj.sOpType, Buff);
	Buff += SizeOf(Obj.sOpType);

	Serializa( Obj.lFormat, Buff);
	Buff += SizeOf(Obj.lFormat);

	Serializa( Obj.lLen, Buff);
	Buff += SizeOf(Obj.lLen);

	Serializa( Obj.szPar, Buff, Obj.lLen); 	// nao eh um string
	Buff += Obj.lLen;

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_DataOp Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lDataObj);

	lTam += SizeOf(Obj.sOpType);

	lTam += SizeOf(Obj.lFormat);

	lTam += SizeOf(Obj.lLen);

	lTam += Obj.lLen;

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_DataOp *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lDataObj, Buff);
	Buff += SizeOf(Obj->lDataObj);

	Deserializa( &Obj->sOpType, Buff);
	Buff += SizeOf(Obj->sOpType);

	Deserializa( &Obj->lFormat, Buff);
	Buff += SizeOf(Obj->lFormat);

	Deserializa( &Obj->lLen, Buff);
	Buff += SizeOf(Obj->lLen);

	if ( !Deserializa( &Obj->szPar, Buff, Obj->lLen) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lLen;

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return(TRUE);
}

void 
RPC::Delete ( TSRIn_DataOp Obj ) 
{	
	Delete( Obj.szPar );

}


void 
RPC::Serializa( TSROut_GetData Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lBufferLen, Buff);
	Buff += SizeOf(Obj.lBufferLen);

	Serializa( Obj.szBuffer, Buff, Obj.lBufferLen); 	// nao eh um string
	Buff += Obj.lBufferLen;
}

long
RPC::SizeOf( TSROut_GetData Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lBufferLen);

	lTam += Obj.lBufferLen;
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetData *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBufferLen, Buff);
	Buff += SizeOf(Obj->lBufferLen);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lBufferLen) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lBufferLen;

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetData Obj ) 
{	
	Delete( Obj.szBuffer );

}


