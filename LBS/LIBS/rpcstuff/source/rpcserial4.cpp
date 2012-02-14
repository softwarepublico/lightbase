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
//	Vladimir Catao	28/01/97
//

#ifndef _RPCSERIAL_H_
	#include <rpcserial.h>
#endif	// _RPCSERIAL_H_


void 
RPC::Serializa( TSROut_GetOpInfo Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szActionPar, Buff);	// eh um string
	Buff += SizeOf(Obj.szActionPar);

	Serializa( Obj.fPercentPar, Buff ); 	
	Buff += SizeOf(Obj.fPercentPar);
}

long
RPC::SizeOf( TSROut_GetOpInfo Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.szActionPar);

	lTam += SizeOf(Obj.fPercentPar);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetOpInfo *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szActionPar, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szActionPar );

	Deserializa( &Obj->fPercentPar, Buff);
	Buff += SizeOf(Obj->fPercentPar);

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetOpInfo Obj ) 
{	
	Delete( Obj.szActionPar );
}


void 
RPC::Serializa( TSROut_GetUsersInfo Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lTamBuff, Buff);
	Buff += SizeOf(Obj.lTamBuff);

	Serializa( Obj.szBuffer, Buff, Obj.lTamBuff); 	// nao eh um string
	Buff += Obj.lTamBuff;
}

long
RPC::SizeOf( TSROut_GetUsersInfo Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lTamBuff);

	lTam += Obj.lTamBuff;
	
	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetUsersInfo *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lTamBuff, Buff);
	Buff += SizeOf(Obj->lTamBuff);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTamBuff) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lTamBuff;

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GetUsersInfo Obj ) 
{	
	Delete( Obj.szBuffer );

}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSROut_GetSvcParam Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSROut_GetSvcParam);
	memcpy(Buff, &Obj, lTam );
}

long
RPC::SizeOf( TSROut_GetSvcParam Obj )
{
	return sizeof(TSROut_GetSvcParam);
}

void
RPC::Delete( TSROut_GetSvcParam )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSROut_GetSvcParam *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSROut_GetSvcParam *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSRIn_ModifyBaseName Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szNewBaseName, Buff);	// eh um string
	Buff += SizeOf(Obj.szNewBaseName);

	Serializa( Obj.TBaseObj, Buff ); 	
	Buff += SizeOf(Obj.TBaseObj);
}

long
RPC::SizeOf( TSRIn_ModifyBaseName Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.szNewBaseName);

	lTam += SizeOf(Obj.TBaseObj);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_ModifyBaseName *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szNewBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewBaseName );

	Deserializa( &Obj->TBaseObj, Buff);
	Buff += SizeOf(Obj->TBaseObj);

	return(TRUE);

}

void 
RPC::Delete ( TSRIn_ModifyBaseName Obj ) 
{	
	Delete( Obj.szNewBaseName );
}


void 
RPC::Serializa ( float Obj, unsigned char *Buff )
{
    memcpy( Buff, &Obj, sizeof(float));
}

boolean 
RPC::Deserializa ( float *Obj, unsigned char *Buff )
{
	*Obj = *(float *)Buff;
	return(TRUE);
}

long
RPC::SizeOf( float )
{
	return sizeof(float);
}


void 
RPC::Serializa( TSRIn_SetSvcParam Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lProto, Buff);	
	Buff += SizeOf(Obj.lProto);

	Serializa( Obj.lOccurTmOut, Buff);	
	Buff += SizeOf(Obj.lOccurTmOut);

	Serializa( Obj.sTicket, Buff);	
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.TSessionObj, Buff);	
	Buff += SizeOf(Obj.TSessionObj);

}

long
RPC::SizeOf( TSRIn_SetSvcParam Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lProto);

	lTam += SizeOf(Obj.lOccurTmOut);
	
	lTam += SizeOf(Obj.sTicket);
	
	lTam += SizeOf(Obj.TSessionObj);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_SetSvcParam *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lProto, Buff);
	Buff += SizeOf(Obj->lProto);

	Deserializa( &Obj->lOccurTmOut, Buff);
	Buff += SizeOf(Obj->lOccurTmOut);

	Deserializa( &Obj->sTicket, Buff);
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->TSessionObj, Buff);
	Buff += SizeOf(Obj->TSessionObj);

	return(TRUE);

}

void 
RPC::Delete ( TSRIn_SetSvcParam Obj ) 
{	
	Delete( Obj.sTicket );
}


void 
RPC::Serializa( TSRIn_GetBaseLongName Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szBaseAliasName, Buff);	// eh um string
	Buff += SizeOf(Obj.szBaseAliasName);

	Serializa( Obj.szUDBName, Buff);	// eh um string
	Buff += SizeOf(Obj.szUDBName);

}

long
RPC::SizeOf( TSRIn_GetBaseLongName Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.szBaseAliasName);

	lTam += SizeOf(Obj.szUDBName);

	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_GetBaseLongName *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szBaseAliasName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBaseAliasName );

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDBName );

	return(TRUE);

}

void 
RPC::Delete ( TSRIn_GetBaseLongName Obj ) 
{	
	Delete( Obj.szBaseAliasName );

	Delete( Obj.szUDBName );
}


void 
RPC::Serializa( TSROut_GetBaseLongName Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szBaseLongName, Buff);	// eh um string
	Buff += SizeOf(Obj.szBaseLongName);

	Serializa( Obj.lRet, Buff);	
	Buff += SizeOf(Obj.lRet);

}

long
RPC::SizeOf( TSROut_GetBaseLongName Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.szBaseLongName);

	lTam += SizeOf(Obj.lRet);

	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GetBaseLongName *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szBaseLongName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBaseLongName );

	Deserializa( &Obj->lRet, Buff );
	Buff += SizeOf( Obj->lRet );

	return(TRUE);

}

void 
RPC::Delete ( TSROut_GetBaseLongName Obj ) 
{	
	Delete( Obj.szBaseLongName );

}


void 
RPC::Serializa( TSROut_GenericBuffer Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lTamBuff, Buff);
	Buff += SizeOf(Obj.lTamBuff);

	Serializa( Obj.szBuffer, Buff, Obj.lTamBuff); 	// nao eh um string
	Buff += Obj.lTamBuff;

}

long
RPC::SizeOf( TSROut_GenericBuffer Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lTamBuff);

	lTam += Obj.lTamBuff;

	return lTam;
}

boolean 
RPC::Deserializa( TSROut_GenericBuffer *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lTamBuff, Buff);
	Buff += SizeOf(Obj->lTamBuff);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTamBuff) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lTamBuff;

	return(TRUE);
}

void 
RPC::Delete ( TSROut_GenericBuffer Obj ) 
{
	Delete( Obj.szBuffer );

}


void	
RPC::Serializa( TSROut_ACLLists Obj, unsigned char *Buff )
{
	Serializa( Obj.togUserBaseBuff, Buff);	
	Buff += SizeOf(Obj.togUserBaseBuff);

	Serializa( Obj.togGroupBaseBuff, Buff);	
	Buff += SizeOf(Obj.togGroupBaseBuff);

	Serializa( Obj.togUserFieldBuff, Buff);	
	Buff += SizeOf(Obj.togUserFieldBuff);

	Serializa( Obj.togGroupFieldBuff, Buff);	
	Buff += SizeOf(Obj.togGroupFieldBuff);

	Serializa( Obj.togUserRecordBuff, Buff);	
	Buff += SizeOf(Obj.togUserRecordBuff);

	Serializa( Obj.togGroupRecordBuff, Buff);	
	Buff += SizeOf(Obj.togGroupRecordBuff);

	Serializa( Obj.togUserFormBuff, Buff);	
	Buff += SizeOf(Obj.togUserFormBuff);

	Serializa( Obj.togGroupFormBuff, Buff);	
	Buff += SizeOf(Obj.togGroupFormBuff);

	Serializa( Obj.togUserReportBuff, Buff);	
	Buff += SizeOf(Obj.togUserReportBuff);

	Serializa( Obj.togGroupReportBuff, Buff);	
	Buff += SizeOf(Obj.togGroupReportBuff);

	Serializa( Obj.szOwnerName, Buff);	// eh um string
	Buff += SizeOf(Obj.szOwnerName);

	Serializa( Obj.lBaseType, Buff);	
	Buff += SizeOf(Obj.lBaseType);

	Serializa( Obj.bIsBasePasswdCorrect, Buff);	
	Buff += SizeOf(Obj.bIsBasePasswdCorrect);

}

boolean 
RPC::Deserializa( TSROut_ACLLists *Obj, unsigned char *Buff )
{
	Deserializa( &Obj->togUserBaseBuff, Buff);	
	Buff += SizeOf(Obj->togUserBaseBuff);

	Deserializa( &Obj->togGroupBaseBuff, Buff);	
	Buff += SizeOf(Obj->togGroupBaseBuff);

	Deserializa( &Obj->togUserFieldBuff, Buff);	
	Buff += SizeOf(Obj->togUserFieldBuff);

	Deserializa( &Obj->togGroupFieldBuff, Buff);	
	Buff += SizeOf(Obj->togGroupFieldBuff);

	Deserializa( &Obj->togUserRecordBuff, Buff);	
	Buff += SizeOf(Obj->togUserRecordBuff);

	Deserializa( &Obj->togGroupRecordBuff, Buff);	
	Buff += SizeOf(Obj->togGroupRecordBuff);

	Deserializa( &Obj->togUserFormBuff, Buff);	
	Buff += SizeOf(Obj->togUserFormBuff);

	Deserializa( &Obj->togGroupFormBuff, Buff);	
	Buff += SizeOf(Obj->togGroupFormBuff);

	Deserializa( &Obj->togUserReportBuff, Buff);	
	Buff += SizeOf(Obj->togUserReportBuff);

	Deserializa( &Obj->togGroupReportBuff, Buff);	
	Buff += SizeOf(Obj->togGroupReportBuff);

	if ( !Deserializa( &Obj->szOwnerName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOwnerName );

	Deserializa( &Obj->lBaseType, Buff);	
	Buff += SizeOf(Obj->lBaseType);

	Deserializa( &Obj->bIsBasePasswdCorrect, Buff);	
	Buff += SizeOf(Obj->bIsBasePasswdCorrect);

	return TRUE;
}

void	
RPC::Delete( TSROut_ACLLists Obj )
{
	Delete( Obj.togUserBaseBuff );	

	Delete( Obj.togGroupBaseBuff );	

	Delete( Obj.togUserFieldBuff );	

	Delete( Obj.togGroupFieldBuff );	

	Delete( Obj.togUserRecordBuff );	

	Delete( Obj.togGroupRecordBuff );	

	Delete( Obj.togUserFormBuff );	

	Delete( Obj.togGroupFormBuff );	

	Delete( Obj.togUserReportBuff );	

	Delete( Obj.togGroupReportBuff );	

	Delete( Obj.szOwnerName );	// eh um string
}

long	
RPC::SizeOf( TSROut_ACLLists Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.togUserBaseBuff);

	lTam += SizeOf(Obj.togGroupBaseBuff);

	lTam += SizeOf(Obj.togUserFieldBuff);

	lTam += SizeOf(Obj.togGroupFieldBuff);

	lTam += SizeOf(Obj.togUserRecordBuff);

	lTam += SizeOf(Obj.togGroupRecordBuff);

	lTam += SizeOf( Obj.togUserFormBuff );	

	lTam += SizeOf( Obj.togGroupFormBuff );	

	lTam += SizeOf( Obj.togUserReportBuff );	

	lTam += SizeOf( Obj.togGroupReportBuff );	

	lTam += SizeOf(Obj.szOwnerName);

	lTam += SizeOf(Obj.lBaseType);

	lTam += SizeOf(Obj.bIsBasePasswdCorrect);

	return lTam;
}


void 
RPC::Serializa( TSRIn_AllRepetitions Obj, unsigned char *Buff ) 
{
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lNumRegs, Buff);
	Buff += SizeOf(Obj.lNumRegs);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_AllRepetitions Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lBaseObj);

	lTam += SizeOf(Obj.lNumRegs);
	
	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_AllRepetitions *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lNumRegs, Buff);
	Buff += SizeOf(Obj->lNumRegs);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_AllRepetitions Obj ) 
{
	Delete( Obj.sTicket );

}


void 
RPC::Serializa( TSRIn_BreakSecurity Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSecurityMask, Buff); 
	Buff += SizeOf(Obj.lSecurityMask);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

long
RPC::SizeOf( TSRIn_BreakSecurity Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSecurityMask);

	lTam += SizeOf(Obj.sCtrlInfo);
	
	return lTam;
}

boolean 
RPC::Deserializa( TSRIn_BreakSecurity *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSecurityMask, Buff);
	Buff += SizeOf(Obj->lSecurityMask);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

void 
RPC::Delete ( TSRIn_BreakSecurity ) 
{
}


