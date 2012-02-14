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
//	Construtor; inicializa o controle de alocacao otima
//
RPC::RPC()
{
}

//
//	Copia um buffer auxiliar para Buff, realocando-o e detonando o auxilio
//
boolean
RPC::AtualizaBuff( unsigned char **Buff, long *TamBuff, unsigned char *AuxBuff, long TamAux)
{
	if ( TamAux == 0 )	// nada  a fazer
		 return TRUE;

	long OldTam = *TamBuff;

	*TamBuff += TamAux;
	*Buff = (unsigned char *)LBS_Realloc( *Buff, OldTam, *TamBuff );
	if ( !*Buff ) 
		return FALSE;

	memcpy( *Buff + OldTam, AuxBuff, TamAux);
	delete AuxBuff;

	return TRUE;
}

//
//	Implementacao default se a subclasse nao a redefinir
//
boolean
RPC::EnviaArgs( unsigned char *, long )
{
	return FALSE;
}

//
//	Implementacao default se a subclasse nao a redefinir
//
boolean
RPC::RecebeArgs( unsigned char ** )
{
	return FALSE;
}

//
//	Gera uma excecao em socket
//
void RPC_ENTRY
RPC::SockRpcRaiseException ( RPC_STATUS )
{
	int *pLixo = NULL;

	*pLixo = 100;
}


//
//	Serializando strings; devemos sempre colocar o tamanho 
//	da string antes; um -1 indica NULL. Assim, deve ter um long 
//	mais o tamanho da propria string se for o caso. 
//	Nao eh necessario o '\0'. 
//
void 
RPC::Serializa ( unsigned char *Obj, unsigned char *Buff )
{
	long TamString = (Obj == NULL) ? MARCA_NULL : strlen((char *)Obj); 

	memcpy( Buff, &TamString, sizeof(long));
	if ( Obj )		// se tiver string, copia
		memcpy( Buff + sizeof(long), Obj, TamString);
}

//
//	Serializando uma tira de bytes; usa o TamBuff para saber quanto copiar,
//	se TamBuff==0 nada a fazer. 
//
void 
RPC::Serializa ( unsigned char *Obj, unsigned char *Buff, long TamBuff )
{			
	if ( Obj == NULL || TamBuff == 0 )	// nada a fazer
		return;

	memcpy( Buff, Obj, TamBuff);
}

//
//	Deserializando strings. Devemos sempre ler o tamanho da string antes 
//	e depois a propria string se for o caso, colocando-se o '\0' ao final.
//
boolean 
RPC::Deserializa ( unsigned char **Obj, unsigned char *Buff )
{
	long TamString;

	Deserializa(&TamString, Buff);
	Buff += SizeOf(TamString);
	if ( TamString == MARCA_NULL ) {	// nao temos string
		*Obj = NULL;
		return TRUE;
	}

	*Obj = (unsigned char *) new char[TamString + 1];
	if ( !*Obj )
		return(FALSE);

	memcpy( *Obj, Buff, TamString);
	(*Obj)[TamString] = '\0';	// fecha a string

	return TRUE;
}

//
//	Deserializando strings estaticas. Pode ser um string ou uma tira de bytes,
//	determinado pelo parametro lTamBuff
//
//	Se for string (lTamBuff == 0), devemos sempre ler o tamanho da string antes 
//	e depois a propria string se for o caso, colocando-se o '\0' ao final.
//
//	Se for tira de bytes (lTamBuff != 0 ), le o buffer direto a partir de lTamBuff
//
boolean 
RPC::Deserializa ( unsigned char *Obj, unsigned char *Buff, long lTamBuff )
{
	BOOL bString = (lTamBuff == 0);

	if ( bString ) {
		Deserializa(&lTamBuff, Buff);
		Buff += SizeOf(lTamBuff);
	}

	memcpy( Obj, Buff, lTamBuff);

	if ( bString ) {
		Obj[lTamBuff] = '\0';	// fecha a string
	}

	return TRUE;
}

	
//
//	Deserializando uma tira de bytes. Usa o TamBuff para saber quanto alocar,
//	se TamBuff==0 nada a fazer. 
//
boolean 
RPC::Deserializa ( unsigned char **Obj, unsigned char *Buff, long TamBuff )
{
	if ( TamBuff == 0 )	{ // campo NULL
		*Obj = NULL;
		return TRUE;
	}

	*Obj = (unsigned char *) new char[TamBuff];

	if ( !*Obj )
		return(FALSE);

	memcpy( *Obj, Buff, TamBuff);

	return(TRUE);
}

//
//	Retorna o tamnho ocupado por um string
//
long
RPC::SizeOf( unsigned char *szBuffer )
{
	long lTam = sizeof(long);	// pelo menos um long que eh o tamanho
	if ( szBuffer ) { // tem a string tambem
		lTam += strlen( (char *)szBuffer );
	}

	return lTam;
}

//
//	Retorna o tamnho ocupado por uma tira de bytes
//
long
RPC::SizeOf( unsigned char *, long lTam )
{
	return lTam;
}

void 
RPC::Delete ( unsigned char *Obj ) 
{
	if ( Obj )
		delete Obj;
}



void 
RPC::Serializa ( long Obj, unsigned char *Buff )
{
    memcpy( Buff, &Obj, sizeof(long));
}

boolean 
RPC::Deserializa ( long *Obj, unsigned char *Buff )
{
	*Obj = *(long *)Buff;
	return(TRUE);
}

long
RPC::SizeOf( long )
{
	return sizeof(long);
}

void
RPC::Delete( long )
{
}



void 
RPC::Serializa ( unsigned char Obj, unsigned char *Buff )
{
    memcpy( Buff, &Obj, sizeof(unsigned char));
}

boolean 
RPC::Deserializa ( unsigned char *Obj, unsigned char *Buff )
{
	*Obj = *Buff;
	return TRUE;
}

long
RPC::SizeOf( unsigned char )
{
	return sizeof( unsigned char );
}

void
RPC::Delete( unsigned char )
{
}


void 
RPC::Serializa ( short Obj, unsigned char *Buff )
{
    memcpy( Buff, &Obj, sizeof(short));
}

boolean 
RPC::Deserializa ( short *Obj, unsigned char *Buff )
{
	*Obj = *(short *)Buff;
	return(TRUE);
}

long
RPC::SizeOf( short )
{
	return sizeof( short );
}

void
RPC::Delete( short )
{
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa ( TSRUDBRecord Obj, unsigned char *Buff )
{
	long TamBuff = SizeOf(Obj);
	memcpy(Buff, &Obj, TamBuff);
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa ( TSRUDBRecord *Obj, unsigned char *Buff )
{
	*Obj = *(TSRUDBRecord *)Buff;
	return(TRUE);	
}

long
RPC::SizeOf(TSRUDBRecord)
{
	return sizeof(TSRUDBRecord);
}

void
RPC::Delete( TSRUDBRecord )
{
}

//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRField Obj, unsigned char *Buff ) 
{
	long TamBuff = SizeOf(Obj);
	memcpy( Buff, &Obj, TamBuff);
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa ( TSRField *Obj, unsigned char *Buff )
{
	*Obj = *(TSRField *)Buff;
	return(TRUE);	
}

long
RPC::SizeOf( TSRField )
{
	return sizeof(TSRField);
}

void
RPC::Delete( TSRField )
{
}


void 
RPC::Serializa ( long *Obj, unsigned char *Buff, long lNumElem)
{
	long lTam = SizeOf( Obj, lNumElem);
	memcpy( Buff, Obj, lTam );
}

boolean 
RPC::Deserializa ( long **Obj, unsigned char *Buff, long TamBuff)
{
	if ( TamBuff == 0 )	{ // campo NULL
		*Obj = NULL;
		return TRUE;
	}

	*Obj = new long[TamBuff];	// array de longs

	if ( !*Obj )
		return(FALSE);

	memcpy( *Obj, Buff, TamBuff * sizeof(long));

	return(TRUE);
}

void 
RPC::Delete ( long *Obj ) 
{
	if ( Obj )
		delete Obj;
}

long
RPC::SizeOf( long *, long lNumElem )
{
	return lNumElem * sizeof(long);
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa ( TSRGenericObj Obj, unsigned char *Buff )
{
	memcpy(Buff, &Obj, SizeOf(Obj));
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa ( TSRGenericObj *Obj, unsigned char *Buff )
{
	*Obj = *(TSRGenericObj *)Buff;
	return(TRUE);	
}

long
RPC::SizeOf( TSRGenericObj Obj )
{
	return sizeof(Obj);
}

void
RPC::Delete( TSRGenericObj )
{
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa ( TSRClntInitInfo Obj, unsigned char *Buff )
{
	memcpy(Buff, &Obj, SizeOf(Obj));
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa ( TSRClntInitInfo *Obj, unsigned char *Buff )
{
	*Obj = *(TSRClntInitInfo *)Buff;
	return(TRUE);	
}

long
RPC::SizeOf( TSRClntInitInfo Obj )
{
	return sizeof(Obj);
}

void
RPC::Delete( TSRClntInitInfo )
{
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa ( TSRControlInfo Obj, unsigned char *Buff )
{
	memcpy(Buff, &Obj, SizeOf(Obj));
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa ( TSRControlInfo *Obj, unsigned char *Buff )
{
	*Obj = *(TSRControlInfo *)Buff;
	return(TRUE);	
}

long
RPC::SizeOf( TSRControlInfo Obj )
{
	return sizeof(Obj);
}

void
RPC::Delete( TSRControlInfo )
{
}


void 
RPC::Serializa ( TSRIn_MGetPutFieldRep Obj, unsigned char *Buff )
{
	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);

	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lNumFieldIds, Buff);
	Buff += SizeOf(Obj.lNumFieldIds);

	Serializa( Obj.pFieldIds, Buff, Obj.lNumFieldIds); 	// array de longs
	Buff += SizeOf(Obj.pFieldIds, Obj.lNumFieldIds);

	Serializa( Obj.lTamBuff, Buff);
	Buff += SizeOf(Obj.lTamBuff);

	Serializa( Obj.szBuffer, Buff, Obj.lTamBuff); 	// nao eh um string
	Buff += Obj.lTamBuff;

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);

}

boolean 
RPC::Deserializa( TSRIn_MGetPutFieldRep *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);

	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lNumFieldIds, Buff);
	Buff += SizeOf(Obj->lNumFieldIds);

	if ( !Deserializa( &Obj->pFieldIds, Buff, Obj->lNumFieldIds) ) 	// array de longs
		return FALSE;
	Buff += SizeOf(Obj->pFieldIds, Obj->lNumFieldIds);

	Deserializa( &Obj->lTamBuff, Buff);
	Buff += SizeOf(Obj->lTamBuff);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTamBuff) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lTamBuff;

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);

	return(TRUE);
}

long
RPC::SizeOf( TSRIn_MGetPutFieldRep Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lBaseObj);

	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lNumFieldIds);

	lTam += SizeOf(Obj.pFieldIds, Obj.lNumFieldIds);

	lTam += SizeOf(Obj.lTamBuff);

	lTam += Obj.lTamBuff;

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_MGetPutFieldRep Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.pFieldIds );

	Delete( Obj.szBuffer );
}


long
RPC::SizeOf( TSROut_MGetFieldRep Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lTamBuff);
	lTam += Obj.lTamBuff;

	return (lTam);
}

void 
RPC::Serializa ( TSROut_MGetFieldRep Obj, unsigned char *Buff )
{
	Serializa( Obj.lTamBuff, Buff);
	Buff += SizeOf(Obj.lTamBuff);

	Serializa( Obj.szBuffer, Buff, Obj.lTamBuff); 	// nao eh um string
	Buff += Obj.lTamBuff;
}

boolean 
RPC::Deserializa( TSROut_MGetFieldRep *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lTamBuff, Buff);
	Buff += SizeOf(Obj->lTamBuff);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTamBuff) ) 	// nao eh um string
		return FALSE;
	Buff += Obj->lTamBuff;

	return(TRUE);
}

void 
RPC::Delete ( TSROut_MGetFieldRep Obj ) 
{
	Delete( Obj.szBuffer );
}


//
//	Serializa para um array
//
void 
RPC::Serializa ( TSRField *Obj, unsigned char *Buff, long TamBuff)
{
	memcpy( Buff, Obj, SizeOf(Obj, TamBuff ));
}

//
//	Deserializa para um array
//
boolean 
RPC::Deserializa ( TSRField **Obj, unsigned char *Buff, long TamBuff)
{
	if ( TamBuff == 0 )	{ // campo NULL
		*Obj = NULL;
		return TRUE;
	}

	*Obj = new TSRField[TamBuff];	// array de TSRField

	if ( !*Obj )
		return(FALSE);

	memcpy( *Obj, Buff, TamBuff * sizeof(TSRField));

	return(TRUE);
}

//
//	Calcula para um array
//
long
RPC::SizeOf( TSRField *, long lNumElem )
{
	return lNumElem * sizeof(TSRField);
}


//
//	Serializa para um ponteiro
//
void 
RPC::Serializa ( TSRField *Obj, unsigned char *Buff)
{
	long lTam = Obj ? sizeof(long) + sizeof( TSRField ) : sizeof(long);

	long lTamObj = Obj ? sizeof( TSRField ) : MARCA_NULL;

	memcpy( Buff, &lTamObj, sizeof(long));
	if ( Obj )
		memcpy(Buff + sizeof(long), Obj, lTamObj);
}

//
//	Deserializa para um ponteiro
//
boolean 
RPC::Deserializa ( TSRField **Obj, unsigned char *Buff )
{
	long TamObj=0;
	Deserializa(&TamObj, Buff);
	Buff += sizeof(long);

	if ( TamObj == MARCA_NULL ) {	// campo NULL
		*Obj = NULL;
	}
	else {
		*Obj = new TSRField;
		if ( !*Obj )
			return(FALSE);

		Deserializa(*Obj, Buff);
	}

	return TRUE;
}

//
//	Calcula para um ponteiro
//
long
RPC::SizeOf( TSRField *Obj )
{
	// vai sempre um long; a estrutura vai se o ponteiro nao for NULL
	if ( Obj )
		return (sizeof(long) + sizeof(TSRField));

	return sizeof(long);
}


void 
RPC::Delete ( TSRField *Obj ) 
{
	if ( Obj )
		delete Obj;
}



void 
RPC::Serializa( TSRTicket Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lTickLen, Buff);
	Buff += sizeof(Obj.lTickLen);

	Serializa( Obj.szTickBuff, Buff, Obj.lTickLen); // nao eh um string

}

boolean 
RPC::Deserializa( TSRTicket *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lTickLen, Buff);
	Buff += sizeof(Obj->lTickLen);

	if ( !Deserializa( &Obj->szTickBuff, Buff, Obj->lTickLen) ) // nao eh um string
		return FALSE;

	return(TRUE);
}

long 
RPC::SizeOf( TSRTicket Obj ) 
{
	return ( SizeOf(Obj.lTickLen) + Obj.lTickLen );
}

void 
RPC::Delete ( TSRTicket Obj ) 
{
	if ( Obj.szTickBuff )
		delete Obj.szTickBuff;
}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSRNetInfo Obj, unsigned char *Buff ) 
{
	long lTam = SizeOf( Obj );

	memcpy(Buff, &Obj, lTam);
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSRNetInfo *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRNetInfo *)Buff;
	return TRUE;
}

long
RPC::SizeOf( TSRNetInfo Obj )
{
	return sizeof(Obj);
}

void
RPC::Delete( TSRNetInfo )
{
}



void 
RPC::Serializa( TSRNetInfo *Obj, unsigned char *Buff ) 
{
	long lTamObj = Obj ? sizeof( TSRNetInfo ) : MARCA_NULL;

	memcpy( Buff, &lTamObj, sizeof(long));
	if ( Obj )
		memcpy(Buff + sizeof(long), Obj, lTamObj);
}

boolean 
RPC::Deserializa( TSRNetInfo **Obj, unsigned char *Buff ) 
{
	long TamObj=0;
	Deserializa(&TamObj, Buff);
	Buff += sizeof(long);

	if ( TamObj == MARCA_NULL ) {	// campo NULL
		*Obj = NULL;
	}
	else {
		*Obj = new TSRNetInfo;
		if ( !*Obj )
			return(FALSE);

		Deserializa(*Obj, Buff);
	}

	return TRUE;
}

long
RPC::SizeOf( TSRNetInfo *Obj )
{
	// vai sempre um long; a estrutura vai se o ponteiro nao for NULL
	if ( Obj )
		return (sizeof(long) + sizeof(TSRNetInfo));

	return sizeof(long);
}


void 
RPC::Serializa( TSRIn_Login Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);

	Serializa( Obj.psLoginInf, Buff);
	Buff += SizeOf(Obj.psLoginInf);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

boolean 
RPC::Deserializa( TSRIn_Login *Obj, unsigned char *Buff ) 
{
	Deserializa(&Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);

	if ( !Deserializa(&Obj->psLoginInf, Buff) ) {
		return FALSE;
	}
	Buff += SizeOf(Obj->psLoginInf);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return(TRUE);
}

long
RPC::SizeOf( TSRIn_Login Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lSessionObj);

	lTam += SizeOf(Obj.psLoginInf);

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_Login Obj ) 
{
	if ( Obj.psLoginInf ) {	// campo nao NULL
		delete Obj.psLoginInf;
	}
}


void 
RPC::Serializa( TSRIn_GetGroups Obj, unsigned char *Buff) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szUserName);

	Serializa( Obj.szUserPswd, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szUserPswd);

	Serializa( Obj.szUDBName, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szUDBName);

	Serializa( Obj.bMem, Buff ); 
	Buff += SizeOf(Obj.bMem);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

boolean 
RPC::Deserializa( TSRIn_GetGroups *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szUserName);

	if ( !Deserializa( &Obj->szUserPswd, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szUserPswd);

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szUDBName);

	Deserializa( &Obj->bMem, Buff ); 
	Buff += SizeOf(Obj->bMem);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_GetGroups Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.szUserName);

	lTam += SizeOf(Obj.szUserPswd);

	lTam += SizeOf(Obj.szUDBName);

	lTam += SizeOf(Obj.bMem);

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_GetGroups Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szUserName );  

	Delete( Obj.szUserPswd );

	Delete( Obj.szUDBName );

}


void 
RPC::Serializa( TSRIn_CreateCloseDelete Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lBaseObj, Buff) ;
	Buff += SizeOf(Obj.lBaseObj);

	Serializa( Obj.szBaseName, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szBaseName);

	Serializa( Obj.szLongBaseName, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szLongBaseName);

	Serializa( Obj.szBasePassword, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szBasePassword);

	Serializa( Obj.szMaintenancePassword, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szMaintenancePassword);

	Serializa( Obj.bBaseType, Buff ); 
	Buff += SizeOf(Obj.bBaseType);

	Serializa( Obj.bIsCrypto, Buff ); 
	Buff += SizeOf(Obj.bIsCrypto);

	Serializa( Obj.szUserBaseName, Buff ); // eh um string; 
	Buff += SizeOf(Obj.szUserBaseName);

	Serializa( Obj.lTam, Buff ); 
	Buff += SizeOf(Obj.lTam);

	Serializa( Obj.szBuffer, Buff, Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;
	
	Serializa( Obj.lSlotNum, Buff ); 
	Buff += SizeOf(Obj.lSlotNum);

	Serializa( Obj.lCountNum, Buff ); 
	Buff += SizeOf(Obj.lCountNum);

	Serializa( Obj.lMaxKeySize, Buff ); 
	Buff += SizeOf(Obj.lMaxKeySize);

	Serializa( Obj.szFileName, Buff ); // eh um string
	Buff += SizeOf(Obj.szFileName);

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_CreateCloseDelete *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lBaseObj, Buff) ;
	Buff += SizeOf(Obj->lBaseObj);

	if ( !Deserializa( &Obj->szBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szBaseName);

	if ( !Deserializa( &Obj->szLongBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szLongBaseName);

	if ( !Deserializa( &Obj->szBasePassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szBasePassword);

	if ( !Deserializa( &Obj->szMaintenancePassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szMaintenancePassword);

	Deserializa( &Obj->bBaseType, Buff ); 
	Buff += SizeOf(Obj->bBaseType);

	Deserializa( &Obj->bIsCrypto, Buff ); 
	Buff += SizeOf(Obj->bIsCrypto);

	if ( !Deserializa( &Obj->szUserBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf(Obj->szUserBaseName);

	Deserializa( &Obj->lTam, Buff ); 
	Buff += SizeOf(Obj->lTam);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;
	
	Deserializa( &Obj->lSlotNum, Buff ); 
	Buff += SizeOf(Obj->lSlotNum);

	Deserializa( &Obj->lCountNum, Buff ); 
	Buff += SizeOf(Obj->lCountNum);

	Deserializa( &Obj->lMaxKeySize, Buff ); 
	Buff += SizeOf(Obj->lMaxKeySize);

	if ( !Deserializa( &Obj->szFileName, Buff ) ) // eh um string
		return FALSE;
	Buff += SizeOf(Obj->szFileName);

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return(TRUE);
}

long
RPC::SizeOf( TSRIn_CreateCloseDelete Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lBaseObj);

	lTam += SizeOf(Obj.szBaseName);

	lTam += SizeOf(Obj.szLongBaseName);

	lTam += SizeOf(Obj.szBasePassword);

	lTam += SizeOf(Obj.szMaintenancePassword);

	lTam += SizeOf(Obj.bBaseType);

	lTam += SizeOf(Obj.bIsCrypto);

	lTam += SizeOf(Obj.szUserBaseName);

	lTam += SizeOf(Obj.lTam);

	lTam += Obj.lTam;
	
	lTam += SizeOf(Obj.lSlotNum);

	lTam += SizeOf(Obj.lCountNum);

	lTam += SizeOf(Obj.lMaxKeySize);

	lTam += SizeOf(Obj.szFileName);

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_CreateCloseDelete Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szBaseName );

	Delete( Obj.szLongBaseName );

	Delete( Obj.szBasePassword );

	Delete( Obj.szMaintenancePassword );

	Delete( Obj.szUserBaseName );

	Delete( Obj.szBuffer );

	Delete( Obj.szFileName );

}


void 
RPC::Serializa( TSRIn_AddDelGroupUser Obj, unsigned char *Buff) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szUDBName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUDBName );

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szGroups, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szGroups );

	Serializa( Obj.lTam, Buff ); 
	Buff += SizeOf(Obj.lTam);

	Serializa( Obj.szBuffer, Buff, Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_AddDelGroupUser *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDBName );

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( &Obj->szGroups, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szGroups );

	Deserializa( &Obj->lTam, Buff ); 
	Buff += SizeOf(Obj->lTam);

	if ( !Deserializa( &Obj->szBuffer, Buff, Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}


long
RPC::SizeOf( TSRIn_AddDelGroupUser Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szUDBName );

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szGroups );

	lTam += SizeOf(Obj.lTam);

	lTam += Obj.lTam;

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_AddDelGroupUser Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szUDBName );

	Delete( Obj.szUserName );

	Delete( Obj.szGroups );

	Delete( Obj.szBuffer );

}

void 
RPC::Serializa( TSRIn_UserGenInfos Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szUDBName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUDBName );

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szOldPassword, Buff, PASSWORDSIZE + 1 ); // nao eh string; 
	Buff += SizeOf( Obj.szOldPassword, PASSWORDSIZE + 1 );

	Serializa( Obj.szNewPassword, Buff, PASSWORDSIZE + 1 ); // nao eh um string; 
	Buff += SizeOf( Obj.szNewPassword, PASSWORDSIZE + 1 );

	Serializa( Obj.lNewType, Buff);
	Buff += SizeOf(Obj.lNewType);
	
	Serializa( Obj.szNewDescrip, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewDescrip );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_UserGenInfos *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDBName );

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( Obj->szOldPassword, Buff, PASSWORDSIZE + 1 ) ) // nao eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szOldPassword, PASSWORDSIZE + 1 );

	if ( !Deserializa( Obj->szNewPassword, Buff, PASSWORDSIZE + 1 ) ) // nao eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewPassword, PASSWORDSIZE + 1 );

	Deserializa( &Obj->lNewType, Buff);
	Buff += SizeOf(Obj->lNewType);
	
	if ( !Deserializa( &Obj->szNewDescrip, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewDescrip );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_UserGenInfos Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szUDBName );

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szOldPassword, PASSWORDSIZE + 1 );

	lTam += SizeOf( Obj.szNewPassword, PASSWORDSIZE + 1 );

	lTam += SizeOf(Obj.lNewType);
	
	lTam += SizeOf( Obj.szNewDescrip );

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_UserGenInfos Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szUDBName );

	Delete( Obj.szUserName );

	Delete( Obj.szNewDescrip );

}


void 
RPC::Serializa( TSRIn_OpenBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szBaseName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBaseName );

	Serializa( Obj.szBasePassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBasePassword );

	Serializa( Obj.bExclusive, Buff);
	Buff += SizeOf(Obj.bExclusive);
	
	Serializa( Obj.bReadOnly, Buff);
	Buff += SizeOf(Obj.bReadOnly);
	
	Serializa( Obj.bMaintenance, Buff);
	Buff += SizeOf(Obj.bMaintenance);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_OpenBase *Obj, unsigned char *Buff ) 
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

	Deserializa( &Obj->bExclusive, Buff);
	Buff += SizeOf(Obj->bExclusive);
	
	Deserializa( &Obj->bReadOnly, Buff);
	Buff += SizeOf(Obj->bReadOnly);
	
	Deserializa( &Obj->bMaintenance, Buff);
	Buff += SizeOf(Obj->bMaintenance);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_OpenBase Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szBaseName );

	lTam += SizeOf( Obj.szBasePassword );

	lTam += SizeOf(Obj.bExclusive);
	
	lTam += SizeOf(Obj.bReadOnly);
	
	lTam += SizeOf(Obj.bMaintenance);
	
	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_OpenBase Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szBaseName );

	Delete( Obj.szBasePassword );

}


void 
RPC::Serializa( TSRIn_What Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szDataBaseName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szDataBaseName );

	Serializa( Obj.szUDB, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUDB );

	Serializa( Obj.lFilterLevel, Buff ); // eh um string; 
	Buff += SizeOf( Obj.lFilterLevel );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

boolean 
RPC::Deserializa( TSRIn_What *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( &Obj->szDataBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szDataBaseName );

	if ( !Deserializa( &Obj->szUDB, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDB );

	Deserializa( &Obj->lFilterLevel, Buff ); 
	Buff += SizeOf( Obj->lFilterLevel );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_What Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szDataBaseName );

	lTam += SizeOf( Obj.szUDB );

	lTam += SizeOf( Obj.lFilterLevel );

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_What Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szUserName );

	Delete( Obj.szDataBaseName );

	Delete( Obj.szUDB );

}


void 
RPC::Serializa( TSRIn_ReorgBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
	
}

boolean 
RPC::Deserializa( TSRIn_ReorgBase *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_ReorgBase Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_ReorgBase Obj ) 
{
	Delete( Obj.sTicket );

}


//
//	Estrutura sem ponteiros; serializacao trivial.
//
void 
RPC::Serializa( TSROut_OpenBase Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSROut_OpenBase);

	memcpy(Buff, &Obj, lTam );
}

long
RPC::SizeOf( TSROut_OpenBase Obj )
{
	return sizeof(TSROut_OpenBase);
}

void
RPC::Delete( TSROut_OpenBase )
{
}

//
//	Estrutura sem ponteiros; deserializacao trivial.
//
boolean 
RPC::Deserializa( TSROut_OpenBase *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSROut_OpenBase *)Buff;
	return(TRUE);	
}


void 
RPC::Serializa( TSROut_GetUsersData Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lRet, Buff);
	Buff += SizeOf(Obj.lRet);
	
	Serializa( Obj.lTam, Buff);
	Buff += SizeOf(Obj.lTam);
	
	Serializa( Obj.lGrpTam, Buff);
	Buff += SizeOf(Obj.lGrpTam);
	
	Serializa( Obj.szBuffer, Buff,  Obj.lTam); // nao eh um string; 
	Buff += Obj.lTam;

	Serializa( Obj.szGrpBuf, Buff,  Obj.lGrpTam); // nao eh um string; 
	Buff += Obj.lGrpTam;
}

boolean 
RPC::Deserializa( TSROut_GetUsersData *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lRet, Buff);
	Buff += SizeOf(Obj->lRet);
	
	Deserializa( &Obj->lTam, Buff);
	Buff += SizeOf(Obj->lTam);
	
	Deserializa( &Obj->lGrpTam, Buff);
	Buff += SizeOf(Obj->lGrpTam);
	
	if ( !Deserializa( &Obj->szBuffer, Buff,  Obj->lTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lTam;

	if ( !Deserializa( &Obj->szGrpBuf, Buff,  Obj->lGrpTam) ) // nao eh um string; 
		return FALSE;
	Buff += Obj->lGrpTam;

	return TRUE;
}

long
RPC::SizeOf( TSROut_GetUsersData Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lRet);
	
	lTam += SizeOf(Obj.lTam);
	
	lTam += SizeOf(Obj.lGrpTam);
	
	lTam += Obj.lTam;

	lTam += Obj.lGrpTam;

	return lTam;
}

void 
RPC::Delete ( TSROut_GetUsersData Obj ) 
{
	Delete( Obj.szBuffer );

	Delete( Obj.szGrpBuf );

}


void 
RPC::Serializa( TSRIn_Import Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szNewOwnerName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewOwnerName );

	Serializa( Obj.szNewBasePassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewBasePassword );

	Serializa( Obj.szNewMaintenanceBasePassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewMaintenanceBasePassword );

	Serializa( Obj.szImportPsw, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szImportPsw );

	Serializa( Obj.szFullImportFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFullImportFileName );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_Import *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szNewOwnerName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewOwnerName );

	if ( !Deserializa( &Obj->szNewBasePassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewBasePassword );

	if ( !Deserializa( &Obj->szNewMaintenanceBasePassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewMaintenanceBasePassword );

	if ( !Deserializa( &Obj->szImportPsw, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szImportPsw );

	if ( !Deserializa( &Obj->szFullImportFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFullImportFileName );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_Import Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szNewOwnerName );

	lTam += SizeOf( Obj.szNewBasePassword );

	lTam += SizeOf( Obj.szNewMaintenanceBasePassword );

	lTam += SizeOf( Obj.szImportPsw );

	lTam += SizeOf( Obj.szFullImportFileName );

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_Import Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szNewOwnerName );

	Delete( Obj.szNewBasePassword );

	Delete( Obj.szNewMaintenanceBasePassword );

	Delete( Obj.szImportPsw );

	Delete( Obj.szFullImportFileName );

}


void 
RPC::Serializa( TSRIn_Export Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf( Obj.sTicket );

	Serializa( Obj.lBaseObj, Buff);
	Buff += SizeOf(Obj.lBaseObj);
	
	Serializa( Obj.lExportTam, Buff);
	Buff += SizeOf(Obj.lExportTam);
	
	Serializa( Obj.szExportBuffer, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szExportBuffer );

	Serializa( Obj.szImportPsw, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szImportPsw );

	Serializa( Obj.szFullExportFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szFullExportFileName );

	Serializa( Obj.szEspecificationFileName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szEspecificationFileName );

	Serializa( Obj.lbChangeOwnerName, Buff);
	Buff += SizeOf(Obj.lbChangeOwnerName);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_Export *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf( Obj->sTicket );

	Deserializa( &Obj->lBaseObj, Buff);
	Buff += SizeOf(Obj->lBaseObj);
	
	Deserializa( &Obj->lExportTam, Buff);
	Buff += SizeOf(Obj->lExportTam);
	
	if ( !Deserializa( &Obj->szExportBuffer, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szExportBuffer );

	if ( !Deserializa( &Obj->szImportPsw, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szImportPsw );

	if ( !Deserializa( &Obj->szFullExportFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szFullExportFileName );

	if ( !Deserializa( &Obj->szEspecificationFileName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szEspecificationFileName );

	Deserializa( &Obj->lbChangeOwnerName, Buff);
	Buff += SizeOf(Obj->lbChangeOwnerName);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_Export Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf( Obj.sTicket );

	lTam += SizeOf(Obj.lBaseObj);
	
	lTam += SizeOf(Obj.lExportTam);
	
	lTam += SizeOf( Obj.szExportBuffer );

	lTam += SizeOf( Obj.szImportPsw );

	lTam += SizeOf( Obj.szFullExportFileName );

	lTam += SizeOf( Obj.szEspecificationFileName );

	lTam += SizeOf(Obj.lbChangeOwnerName);
	
	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_Export Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szExportBuffer );

	Delete( Obj.szImportPsw );

	Delete( Obj.szFullExportFileName );

	Delete( Obj.szEspecificationFileName );

}


void 
RPC::Serializa( TSRIn_UpdateUserAddress Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff);
	Buff += SizeOf(Obj.lSessionObj);
	
	Serializa( Obj.sTicket, Buff); 
	Buff += SizeOf(Obj.sTicket);

	Serializa( Obj.szUDBName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUDBName );

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szNewAddr, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szNewAddr );

	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_UpdateUserAddress *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( &Obj->szUDBName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUDBName );

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( &Obj->szNewAddr, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szNewAddr );

	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_UpdateUserAddress Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szUDBName );

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szNewAddr );

	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_UpdateUserAddress Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szUDBName );

	Delete( Obj.szUserName );

	Delete( Obj.szNewAddr );

}


void 
RPC::Serializa( TSRIn_CreateDefaultUserBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.szPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szPassword );

	Serializa( Obj.szMaintPassword, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szMaintPassword );

	Serializa( Obj.szUserName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szUserName );

	Serializa( Obj.szUserPassword, Buff, PASSWORDSIZE + 1 ); // nao eh um string; 
	Buff += SizeOf( Obj.szUserPassword, PASSWORDSIZE + 1 );
}

boolean 
RPC::Deserializa( TSRIn_CreateDefaultUserBase *Obj, unsigned char *Buff ) 
{
	if ( !Deserializa( &Obj->szPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword );

	if ( !Deserializa( &Obj->szMaintPassword, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szMaintPassword );

	if ( !Deserializa( &Obj->szUserName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserName );

	if ( !Deserializa( Obj->szUserPassword, Buff, PASSWORDSIZE + 1 ) ) // nao eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szUserPassword, PASSWORDSIZE + 1 );

	return (TRUE);
}

long
RPC::SizeOf( TSRIn_CreateDefaultUserBase Obj )
{
	long lTam=0;

	lTam += SizeOf( Obj.szPassword );

	lTam += SizeOf( Obj.szMaintPassword );

	lTam += SizeOf( Obj.szUserName );

	lTam += SizeOf( Obj.szUserPassword, PASSWORDSIZE + 1 );

	return lTam;
}

void 
RPC::Delete ( TSRIn_CreateDefaultUserBase Obj ) 
{
	Delete( Obj.szPassword );

	Delete( Obj.szMaintPassword );

	Delete( Obj.szUserName );

}


void 
RPC::Serializa( TSRIn_DeleteUDB Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lSessionObj, Buff ); 
	Buff += SizeOf( Obj.lSessionObj );

	Serializa( Obj.sTicket, Buff ); 
	Buff += SizeOf( Obj.sTicket );

	Serializa( Obj.szPassword, Buff, PASSWORDSIZE + 1 ); // nao eh um string; 
	Buff += SizeOf( Obj.szPassword, PASSWORDSIZE + 1 );

	Serializa( Obj.szBaseName, Buff ); // eh um string; 
	Buff += SizeOf( Obj.szBaseName );

	Serializa( Obj.bForce, Buff);
	Buff += SizeOf(Obj.bForce);
	
	Serializa( Obj.sCtrlInfo, Buff);
	Buff += SizeOf(Obj.sCtrlInfo);
}

boolean 
RPC::Deserializa( TSRIn_DeleteUDB *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lSessionObj, Buff);
	Buff += SizeOf(Obj->lSessionObj);
	
	if ( !Deserializa( &Obj->sTicket, Buff) ) 
		return FALSE;
	Buff += SizeOf(Obj->sTicket);

	if ( !Deserializa( Obj->szPassword, Buff, PASSWORDSIZE + 1 ) ) // nao eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szPassword, PASSWORDSIZE + 1 );

	if ( !Deserializa( &Obj->szBaseName, Buff ) ) // eh um string; 
		return FALSE;
	Buff += SizeOf( Obj->szBaseName );

	Deserializa( &Obj->bForce, Buff);
	Buff += SizeOf(Obj->bForce);
	
	Deserializa( &Obj->sCtrlInfo, Buff);
	Buff += SizeOf(Obj->sCtrlInfo);
	
	return TRUE;
}

long
RPC::SizeOf( TSRIn_DeleteUDB Obj )
{
	long lTam=0;

	lTam += SizeOf(Obj.lSessionObj);
	
	lTam += SizeOf(Obj.sTicket);

	lTam += SizeOf( Obj.szPassword, PASSWORDSIZE + 1 );

	lTam += SizeOf( Obj.szBaseName );

	lTam += SizeOf(Obj.bForce);
	
	lTam += SizeOf(Obj.sCtrlInfo);

	return lTam;
}

void 
RPC::Delete ( TSRIn_DeleteUDB Obj ) 
{
	Delete( Obj.sTicket );

	Delete( Obj.szBaseName );

}

/////////////////////////////////////////////////////////////////
void 
RPC::Serializa( TSRIn_MaintBase Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRIn_MaintBase);

	memcpy(Buff, &Obj, lTam );
}

boolean 
RPC::Deserializa( TSRIn_MaintBase *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRIn_MaintBase *)Buff;
	return TRUE;
}

long
RPC::SizeOf( TSRIn_MaintBase Obj )
{
	return sizeof( TSRIn_MaintBase );
}

void 
RPC::Delete ( TSRIn_MaintBase Obj ) 
{
}

/////////////////////////////////////////////////////////////////
// ESTRUTURA SEM PONTEIROS
void 
RPC::Serializa( TSRMaintBase Obj, unsigned char *Buff ) 
{
	long lTam = sizeof(TSRMaintBase);

	memcpy(Buff, &Obj, lTam );
}

boolean 
RPC::Deserializa( TSRMaintBase *Obj, unsigned char *Buff ) 
{
	*Obj = *(TSRMaintBase *)Buff;
	return TRUE;
}

long
RPC::SizeOf( TSRMaintBase Obj )
{
	return sizeof( TSRMaintBase );
}

void 
RPC::Delete ( TSRMaintBase Obj ) 
{
}

/////////////////////////////////////////////////////////////////
// PARA ARRAY
void 
RPC::Serializa ( TSRMaintBase *Obj, unsigned char *Buff, long TamBuff)
{
	memcpy( Buff, Obj, SizeOf(Obj, TamBuff ));
}

boolean 
RPC::Deserializa ( TSRMaintBase **Obj, unsigned char *Buff, long TamBuff)
{
	if ( TamBuff == 0 )	{ // campo NULL
		*Obj = NULL;
		return TRUE;
	}

	*Obj = new TSRMaintBase[TamBuff];	// array de TSRMaintBase

	if ( !*Obj )
		return(FALSE);

	memcpy( *Obj, Buff, TamBuff * sizeof(TSRField));

	return(TRUE);
}

long
RPC::SizeOf( TSRMaintBase *, long lNumElem )
{
	return lNumElem * sizeof(TSRMaintBase);
}

/////////////////////////////////////////////////////////////////
// PARA PONTEIRO
void 
RPC::Serializa ( TSRMaintBase *Obj, unsigned char *Buff)
{
	long lTam = Obj ? sizeof(long) + sizeof( TSRMaintBase ) : sizeof(long);

	long lTamObj = Obj ? sizeof( TSRMaintBase ) : MARCA_NULL;

	memcpy( Buff, &lTamObj, sizeof(long));
	if ( Obj )
		memcpy(Buff + sizeof(long), Obj, lTamObj);
}

boolean 
RPC::Deserializa ( TSRMaintBase **Obj, unsigned char *Buff )
{
	long TamObj=0;
	Deserializa(&TamObj, Buff);
	Buff += sizeof(long);

	if ( TamObj == MARCA_NULL ) {	// campo NULL
		*Obj = NULL;
	}
	else {
		*Obj = new TSRMaintBase;
		if ( !*Obj )
			return(FALSE);

		Deserializa(*Obj, Buff);
	}

	return TRUE;
}

long
RPC::SizeOf( TSRMaintBase *Obj )
{
	// vai sempre um long; a estrutura vai se o ponteiro nao for NULL
	if ( Obj )
		return (sizeof(long) + sizeof(TSRMaintBase));

	return sizeof(long);
}


void 
RPC::Delete ( TSRMaintBase *Obj ) 
{
	if ( Obj )
		delete Obj;
}


/////////////////////////////////////////////////////////////////
void 
RPC::Serializa( TSROut_MaintBase Obj, unsigned char *Buff ) 
{
	Serializa( Obj.lArrayLen, Buff);
	Buff += SizeOf(Obj.lArrayLen);

	Serializa( Obj.psMaintBase, Buff, Obj.lArrayLen); 	// array de TSRMaintBase
	Buff += SizeOf(Obj.psMaintBase, Obj.lArrayLen );
}

boolean 
RPC::Deserializa( TSROut_MaintBase *Obj, unsigned char *Buff ) 
{
	Deserializa( &Obj->lArrayLen, Buff);
	Buff += SizeOf(Obj->lArrayLen);

	if ( !Deserializa( &Obj->psMaintBase, Buff, Obj->lArrayLen) ) 	// array de TSRMaintBase
		return FALSE;
	Buff += SizeOf(Obj->psMaintBase, Obj->lArrayLen );

	return(TRUE);
}

long
RPC::SizeOf( TSROut_MaintBase Obj )
{
	long lTam=0;
	
	lTam += SizeOf(Obj.lArrayLen);

	lTam += SizeOf(Obj.psMaintBase, Obj.lArrayLen );
	
	return lTam;
}

void 
RPC::Delete ( TSROut_MaintBase Obj ) 
{	
	Delete( Obj.psMaintBase );

}


/***
	Realoca buffers que foram alocados inicialmente com new
	e nao com calloc ou malloc.

	Se houver algum erro, o retorno sera' NULL.
	Se o pvOrigBuf for NULL, esta funcao funcionara' como um new,
	retornando o ponteiro do buffer alocado.
***/
void *
LBS_Realloc( void *pvOrigBuf, int iOldSize, int iNewSize )
{
	void	*pvNewBuf = NULL;

	if( iNewSize <= 0 ){
		return( NULL );
	}
	pvNewBuf = (void*) new char[ iNewSize ];
	if( pvNewBuf ){
		memset( pvNewBuf, 0, iNewSize );
	}
	if( pvOrigBuf && pvNewBuf ){
		if ( iNewSize < iOldSize )
			memcpy( pvNewBuf, pvOrigBuf, iNewSize );
		else
			memcpy( pvNewBuf, pvOrigBuf, iOldSize );

		delete (char*) pvOrigBuf;
	}
	return( pvNewBuf );
}

