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


#ifndef _RPCSERIAL_H_
#define _RPCSERIAL_H_

#ifndef __lbsrpc_h__
	#include <lbsrpc.h>
#endif	// __lbsrpc_h__

#define MARCA_NULL		-1		// indica que o ponteiro (de)serializado eh NULL

void *LBS_Realloc( void *, int, int );	// para nao usar o realloc normal; da pau no delete


class RPC {
private:
	boolean AtualizaBuff( unsigned char **, long *, unsigned char *, long );

public:
	RPC();

	static void	RPC_ENTRY SockRpcRaiseException ( RPC_STATUS );

	virtual boolean EnviaArgs( unsigned char *, long );
	virtual boolean RecebeArgs( unsigned char ** );

	void	Serializa ( long, unsigned char * );
	boolean Deserializa ( long *, unsigned char * );
	long	SizeOf( long );
	void	Delete( long );

	void	Serializa ( float, unsigned char * );
	boolean Deserializa ( float *, unsigned char * );
	long	SizeOf( float );
	void	Delete( float );

	void	Serializa ( unsigned char, unsigned char * );
	boolean Deserializa ( unsigned char *, unsigned char * );
	long	SizeOf( unsigned char );
	void	Delete( unsigned char );

	// serializa strings
	void	Serializa ( unsigned char*, unsigned char * );
	// serializa tira de bytes
	void	Serializa ( unsigned char*, unsigned char *, long );
	// retorna o tamanho ocupado pelo string
	long	SizeOf( unsigned char * );
	// retorna o tamanho ocupado pela tira de bytes
	long	SizeOf( unsigned char *, long );
	// deserializa strings
	boolean Deserializa ( unsigned char **, unsigned char * );
	// deserializa strings estaticas; o parametro adicional (long) serve para indicar se desserializa string ou tira de bytes; default eh string
	boolean Deserializa ( unsigned char *, unsigned char *, long ); 
	// deserializa tira de bytes
	boolean Deserializa ( unsigned char **, unsigned char *, long );
	void	Delete( unsigned char * );

	void	Serializa ( long *, unsigned char *, long );
	boolean Deserializa ( long **, unsigned char *, long );
	void	Delete( long * );
	long	SizeOf( long *, long );

	// serializando um array
	void	Serializa ( TSRField *, unsigned char *, long );
	// serializando um ponteiro
	void	Serializa ( TSRField *, unsigned char * );
	// deserializando um array
	boolean Deserializa ( TSRField **, unsigned char *, long );
	// deserializando um ponteiro
	boolean Deserializa ( TSRField **, unsigned char * );
	void	Delete( TSRField * );
	// calcula para um array
	long	SizeOf( TSRField *, long );
	// calcula para um ponteiro
	long	SizeOf( TSRField * );

	void	Serializa ( short, unsigned char * );
	boolean Deserializa ( short *, unsigned char * );
	long	SizeOf( short );
	void	Delete( short );

	void	Serializa ( TSRUDBRecord, unsigned char * );
	boolean Deserializa ( TSRUDBRecord *, unsigned char * );
	long	SizeOf( TSRUDBRecord );
	void	Delete( TSRUDBRecord );

	void	Serializa( TSRField, unsigned char * ) ;
	boolean Deserializa( TSRField *, unsigned char * ) ;
	long	SizeOf( TSRField );
	void	Delete( TSRField );

	void	Serializa( TSRGenericObj, unsigned char * ) ;
	boolean Deserializa( TSRGenericObj *, unsigned char * ) ;
	long SizeOf( TSRGenericObj );
	void	Delete( TSRGenericObj );
	
	void	Serializa( TSRClntInitInfo, unsigned char * ) ;
	boolean Deserializa( TSRClntInitInfo *, unsigned char * ) ;
	long SizeOf( TSRClntInitInfo );
	void	Delete( TSRClntInitInfo );

	void	Serializa( TSRControlInfo, unsigned char * ) ;
	boolean Deserializa( TSRControlInfo *, unsigned char * ) ;
	long SizeOf( TSRControlInfo );
	void	Delete( TSRControlInfo );

	void	Serializa( TSRTicket, unsigned char * ) ;
	boolean Deserializa( TSRTicket *, unsigned char * ) ;
	void	Delete( TSRTicket );
	long	SizeOf( TSRTicket );

	void	Serializa( TSRNetInfo, unsigned char * ) ;
	boolean Deserializa( TSRNetInfo *, unsigned char * ) ;
	long SizeOf( TSRNetInfo );
	void	Delete( TSRNetInfo );

	void	Serializa( TSRNetInfo *, unsigned char * ) ;
	boolean Deserializa( TSRNetInfo **, unsigned char * ) ;
	long	SizeOf( TSRNetInfo * );
	void	Delete( TSRNetInfo * );

	void	Serializa( TSRIn_Login, unsigned char * ) ;
	boolean Deserializa( TSRIn_Login *, unsigned char * ) ;
	void	Delete( TSRIn_Login );
	long	SizeOf( TSRIn_Login );

	void	Serializa( TSRIn_GetGroups, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetGroups *, unsigned char * ) ;
	void	Delete( TSRIn_GetGroups );
	long	SizeOf( TSRIn_GetGroups );

	void	Serializa( TSRIn_CreateCloseDelete, unsigned char * ) ;
	boolean Deserializa( TSRIn_CreateCloseDelete *, unsigned char * ) ;
	void	Delete( TSRIn_CreateCloseDelete );
	long	SizeOf( TSRIn_CreateCloseDelete );

	void	Serializa( TSRIn_AddDelGroupUser, unsigned char * ) ;
	boolean Deserializa( TSRIn_AddDelGroupUser *, unsigned char * ) ;
	void	Delete( TSRIn_AddDelGroupUser );
	long	SizeOf( TSRIn_AddDelGroupUser );

	void	Serializa( TSRIn_UserGenInfos, unsigned char * ) ;
	boolean Deserializa( TSRIn_UserGenInfos *, unsigned char * ) ;
	void	Delete( TSRIn_UserGenInfos );
	long	SizeOf( TSRIn_UserGenInfos );

	void	Serializa( TSRIn_OpenBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_OpenBase *, unsigned char * ) ;
	void	Delete( TSRIn_OpenBase );
	long	SizeOf( TSRIn_OpenBase );

	void	Serializa( TSRIn_What, unsigned char * ) ;
	boolean Deserializa( TSRIn_What *, unsigned char * ) ;
	void	Delete( TSRIn_What );
	long	SizeOf( TSRIn_What );

	void	Serializa( TSRIn_ReorgBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_ReorgBase *, unsigned char * ) ;
	void	Delete( TSRIn_ReorgBase );
	long	SizeOf( TSRIn_ReorgBase );

	void	Serializa( TSROut_OpenBase, unsigned char * ) ;
	boolean Deserializa( TSROut_OpenBase *, unsigned char * ) ;
	long	SizeOf( TSROut_OpenBase );
	void	Delete( TSROut_OpenBase );

	void	Serializa( TSROut_GetUsersData, unsigned char * ) ;
	boolean Deserializa( TSROut_GetUsersData *, unsigned char * ) ;
	void	Delete( TSROut_GetUsersData );
	long	SizeOf( TSROut_GetUsersData );

	void	Serializa( TSRIn_Import, unsigned char * ) ;
	boolean Deserializa( TSRIn_Import *, unsigned char * ) ;
	void	Delete( TSRIn_Import );
	long	SizeOf( TSRIn_Import );

	void	Serializa( TSRIn_Export, unsigned char * ) ;
	boolean Deserializa( TSRIn_Export *, unsigned char * ) ;
	void	Delete( TSRIn_Export );
	long	SizeOf( TSRIn_Export );

	void	Serializa( TSRIn_UpdateUserAddress, unsigned char * ) ;
	boolean Deserializa( TSRIn_UpdateUserAddress *, unsigned char * ) ;
	void	Delete( TSRIn_UpdateUserAddress );
	long	SizeOf( TSRIn_UpdateUserAddress );

	void	Serializa( TSRIn_RenameBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_RenameBase *, unsigned char * ) ;
	void	Delete( TSRIn_RenameBase );
	long	SizeOf( TSRIn_RenameBase );

	void	Serializa( TSRIn_KillSessions, unsigned char * ) ;
	boolean Deserializa( TSRIn_KillSessions *, unsigned char * ) ;
	void	Delete( TSRIn_KillSessions );
	long	SizeOf( TSRIn_KillSessions );

	void	Serializa( TSRIn_CreateDefaultUserBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_CreateDefaultUserBase *, unsigned char * ) ;
	void	Delete( TSRIn_CreateDefaultUserBase );
	long	SizeOf( TSRIn_CreateDefaultUserBase );

	void	Serializa( TSRIn_DeleteUDB, unsigned char * ) ;
	boolean Deserializa( TSRIn_DeleteUDB *, unsigned char * ) ;
	void	Delete( TSRIn_DeleteUDB );
	long	SizeOf( TSRIn_DeleteUDB );

	void	Serializa( TSRIn_IncorporateBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_IncorporateBase *, unsigned char * ) ;
	void	Delete( TSRIn_IncorporateBase );
	long	SizeOf( TSRIn_IncorporateBase );

	void	Serializa( TSROut_WhatBases, unsigned char * ) ;
	boolean Deserializa( TSROut_WhatBases *, unsigned char * ) ;
	void	Delete( TSROut_WhatBases );
	long	SizeOf( TSROut_WhatBases );

	void	Serializa( TSRIn_SetNavigationLocate, unsigned char * ) ;
	boolean Deserializa( TSRIn_SetNavigationLocate *, unsigned char * ) ;
	void	Delete( TSRIn_SetNavigationLocate );
	long	SizeOf( TSRIn_SetNavigationLocate );

	void	Serializa( TSRIn_TicketPar, unsigned char * ) ;
	boolean Deserializa( TSRIn_TicketPar *, unsigned char * ) ;
	void	Delete( TSRIn_TicketPar );
	long	SizeOf( TSRIn_TicketPar );

	void	Serializa( TSRIn_AddField, unsigned char * ) ;
	boolean Deserializa( TSRIn_AddField *, unsigned char * ) ;
	void	Delete( TSRIn_AddField );
	long	SizeOf( TSRIn_AddField );

	void	Serializa( TSRIn_DelFieldGetFieldObj, unsigned char * ) ;
	boolean Deserializa( TSRIn_DelFieldGetFieldObj *, unsigned char * ) ;
	void	Delete( TSRIn_DelFieldGetFieldObj );
	long	SizeOf( TSRIn_DelFieldGetFieldObj );

	void	Serializa( TSRIn_MGetPutFieldRep, unsigned char * ) ;
	boolean Deserializa( TSRIn_MGetPutFieldRep *, unsigned char * ) ;
	void	Delete( TSRIn_MGetPutFieldRep );
	long	SizeOf( TSRIn_MGetPutFieldRep );

	void	Serializa( TSROut_MGetFieldRep, unsigned char * ) ;
	boolean Deserializa( TSROut_MGetFieldRep *, unsigned char * ) ;
	void	Delete( TSROut_MGetFieldRep );
	long	SizeOf( TSROut_MGetFieldRep );

	void	Serializa( TSRIn_ModifyFieldPassword, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldPassword *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldPassword );
	long	SizeOf( TSRIn_ModifyFieldPassword );

	void	Serializa( TSRIn_ModifyFieldName, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldName *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldName );
	long	SizeOf( TSRIn_ModifyFieldName );

	void	Serializa( TSRIn_ModifyFieldDescription, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldDescription *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldDescription );
	long	SizeOf( TSRIn_ModifyFieldDescription );

	void	Serializa( TSRIn_ModifyFieldSize, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldSize *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldSize );
	long	SizeOf( TSRIn_ModifyFieldSize );

	void	Serializa( TSRIn_DelFieldRepetition, unsigned char * ) ;
	boolean Deserializa( TSRIn_DelFieldRepetition *, unsigned char * ) ;
	void	Delete( TSRIn_DelFieldRepetition );
	long	SizeOf( TSRIn_DelFieldRepetition );

	void	Serializa( TSRIn_GetNumberOfRepetition, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetNumberOfRepetition *, unsigned char * ) ;
	void	Delete( TSRIn_GetNumberOfRepetition );
	long	SizeOf( TSRIn_GetNumberOfRepetition );

	void	Serializa( TSRIn_GetFieldRepetitionSize, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldRepetitionSize *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldRepetitionSize );
	long	SizeOf( TSRIn_GetFieldRepetitionSize );

	void	Serializa( TSRIn_GetFields, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFields *, unsigned char * ) ;
	void	Delete( TSRIn_GetFields );
	long	SizeOf( TSRIn_GetFields );

	void	Serializa( TSRIn_TicketBOOLPar, unsigned char * ) ;
	boolean Deserializa( TSRIn_TicketBOOLPar *, unsigned char * ) ;
	void	Delete( TSRIn_TicketBOOLPar );
	long	SizeOf( TSRIn_TicketBOOLPar );

	void	Serializa( TSRIn_SetLockTimeOut, unsigned char * ) ;
	boolean Deserializa( TSRIn_SetLockTimeOut *, unsigned char * ) ;
	void	Delete( TSRIn_SetLockTimeOut );
	long	SizeOf( TSRIn_SetLockTimeOut );

	void	Serializa( TSRIn_SetReorganizeRecQuant, unsigned char * ) ;
	boolean Deserializa( TSRIn_SetReorganizeRecQuant *, unsigned char * ) ;
	void	Delete( TSRIn_SetReorganizeRecQuant );
	long	SizeOf( TSRIn_SetReorganizeRecQuant );

	void	Serializa( TSRIn_Nth, unsigned char * ) ;
	boolean Deserializa( TSRIn_Nth *, unsigned char * ) ;
	void	Delete( TSRIn_Nth );
	long	SizeOf( TSRIn_Nth );

	void	Serializa( TSRIn_Search, unsigned char * ) ;
	boolean Deserializa( TSRIn_Search *, unsigned char * ) ;
	void	Delete( TSRIn_Search );
	long	SizeOf( TSRIn_Search );

	void	Serializa( TSRIn_OcList, unsigned char * ) ;
	boolean Deserializa( TSRIn_OcList *, unsigned char * ) ;
	void	Delete( TSRIn_OcList );
	long	SizeOf( TSRIn_OcList );

	void	Serializa( TSRIn_SetNavigation, unsigned char * ) ;
	boolean Deserializa( TSRIn_SetNavigation *, unsigned char * ) ;
	void	Delete( TSRIn_SetNavigation );
	long	SizeOf( TSRIn_SetNavigation );

	void	Serializa( TSRIn_GetSlotSize, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetSlotSize *, unsigned char * ) ;
	long	SizeOf( TSRIn_GetSlotSize );
	void	Delete( TSRIn_GetSlotSize );

	void	Serializa( TSRIn_SearchStopWord, unsigned char * ) ;
	boolean Deserializa( TSRIn_SearchStopWord *, unsigned char * ) ;
	void	Delete( TSRIn_SearchStopWord );
	long	SizeOf( TSRIn_SearchStopWord );

	void	Serializa( TSRIn_GoWord, unsigned char * ) ;
	boolean Deserializa( TSRIn_GoWord *, unsigned char * ) ;
	void	Delete( TSRIn_GoWord );
	long	SizeOf( TSRIn_GoWord );

	void	Serializa( TSRIn_ModifyFieldIndexAttrib, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldIndexAttrib *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldIndexAttrib );
	long	SizeOf( TSRIn_ModifyFieldIndexAttrib );

	void	Serializa( TSRIn_ModifyFieldAttrib, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldAttrib *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldAttrib );
	long	SizeOf( TSRIn_ModifyFieldAttrib );

	void	Serializa( TSRIn_ACLPerm, unsigned char * ) ;
	boolean Deserializa( TSRIn_ACLPerm *, unsigned char * ) ;
	void	Delete( TSRIn_ACLPerm );
	long	SizeOf( TSRIn_ACLPerm );

	void	Serializa( TSRIn_EnableOnLineIndex, unsigned char * ) ;
	boolean Deserializa( TSRIn_EnableOnLineIndex *, unsigned char * ) ;
	long	SizeOf( TSRIn_EnableOnLineIndex );
	void	Delete( TSRIn_EnableOnLineIndex );

	void	Serializa( TSRIn_GetSlotPutSlot, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetSlotPutSlot *, unsigned char * ) ;
	void	Delete( TSRIn_GetSlotPutSlot );
	long	SizeOf( TSRIn_GetSlotPutSlot );

	void	Serializa( TSRIn_ModifyPassword, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyPassword *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyPassword );
	long	SizeOf( TSRIn_ModifyPassword );

	void	Serializa( TSROut_GetFullBaseName, unsigned char * ) ;
	boolean Deserializa( TSROut_GetFullBaseName *, unsigned char * ) ;
	long	SizeOf( TSROut_GetFullBaseName );
	void	Delete( TSROut_GetFullBaseName );

	void	Serializa( TSRIn_ModifyBaseType, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyBaseType *, unsigned char * ) ;
	long	SizeOf( TSRIn_ModifyBaseType );
	void	Delete( TSRIn_ModifyBaseType );

	void	Serializa( TSRIn_IndexAll, unsigned char * ) ;
	boolean Deserializa( TSRIn_IndexAll *, unsigned char * ) ;
	void	Delete( TSRIn_IndexAll );
	long	SizeOf( TSRIn_IndexAll );

	void	Serializa( TSRIn_IndexString, unsigned char * ) ;
	boolean Deserializa( TSRIn_IndexString *, unsigned char * ) ;
	void	Delete( TSRIn_IndexString );
	long	SizeOf( TSRIn_IndexString );

	void	Serializa( TSRIn_AddStopWord, unsigned char * ) ;
	boolean Deserializa( TSRIn_AddStopWord *, unsigned char * ) ;
	void	Delete( TSRIn_AddStopWord );
	long	SizeOf( TSRIn_AddStopWord );

	void	Serializa( TSRIn_ModifyBaseOwnerName, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyBaseOwnerName *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyBaseOwnerName );
	long	SizeOf( TSRIn_ModifyBaseOwnerName );

	void	Serializa( TSRIn_GetFieldIndexAttrib, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldIndexAttrib *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldIndexAttrib );
	long	SizeOf( TSRIn_GetFieldIndexAttrib );

	void	Serializa( TSRIn_GetFieldObj, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldObj *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldObj );
	long	SizeOf( TSRIn_GetFieldObj );

	void	Serializa( TSRIn_GetFieldTypeId, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldTypeId *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldTypeId );
	long	SizeOf( TSRIn_GetFieldTypeId );

	void	Serializa( TSRIn_GetFieldRepetition, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldRepetition *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldRepetition );
	long	SizeOf( TSRIn_GetFieldRepetition );

	void	Serializa( TSRIn_GetFieldRepetitionByVal, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetFieldRepetitionByVal *, unsigned char * ) ;
	void	Delete( TSRIn_GetFieldRepetitionByVal );
	long	SizeOf( TSRIn_GetFieldRepetitionByVal );

	void	Serializa( TSRIn_PutFieldRepetition, unsigned char * ) ;
	boolean Deserializa( TSRIn_PutFieldRepetition *, unsigned char * ) ;
	void	Delete( TSRIn_PutFieldRepetition );
	long	SizeOf( TSRIn_PutFieldRepetition );

	void	Serializa( TSRIn_ModifyFieldRepetition, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyFieldRepetition *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyFieldRepetition );
	long	SizeOf( TSRIn_ModifyFieldRepetition );

	void	Serializa( TSRIn_GetACLListPerm, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetACLListPerm *, unsigned char * ) ;
	void	Delete( TSRIn_GetACLListPerm );
	long	SizeOf( TSRIn_GetACLListPerm );

	void	Serializa( TSRIn_ExchangeOperator, unsigned char * ) ;
	boolean Deserializa( TSRIn_ExchangeOperator *, unsigned char * ) ;
	void	Delete( TSRIn_ExchangeOperator );
	long	SizeOf( TSRIn_ExchangeOperator );

	void	Serializa( TSRIn_Mask, unsigned char * ) ;
	boolean Deserializa( TSRIn_Mask *, unsigned char * ) ;
	void	Delete( TSRIn_Mask );
	long	SizeOf( TSRIn_Mask );

	void	Serializa( TSRIn_Phone, unsigned char * ) ;
	boolean Deserializa( TSRIn_Phone *, unsigned char * ) ;
	void	Delete( TSRIn_Phone );
	long	SizeOf( TSRIn_Phone );

	void	Serializa( TSRIn_Standardize, unsigned char * ) ;
	boolean Deserializa( TSRIn_Standardize *, unsigned char * ) ;
	void	Delete( TSRIn_Standardize );
	long	SizeOf( TSRIn_Standardize );

	void	Serializa( TSRIn_Synonym, unsigned char * ) ;
	boolean Deserializa( TSRIn_Synonym *, unsigned char * ) ;
	void	Delete( TSRIn_Synonym );
	long	SizeOf( TSRIn_Synonym );

	void	Serializa( TSRIn_OL, unsigned char * ) ;
	boolean Deserializa( TSRIn_OL *, unsigned char * ) ;
	void	Delete( TSRIn_OL );
	long	SizeOf( TSRIn_OL );

	void	Serializa( TSRIn_Operators, unsigned char * ) ;
	boolean Deserializa( TSRIn_Operators *, unsigned char * ) ;
	void	Delete( TSRIn_Operators );
	long	SizeOf( TSRIn_Operators );

	void	Serializa( TSRSetError, unsigned char * ) ;
	boolean Deserializa( TSRSetError *, unsigned char * ) ;
	void	Delete( TSRSetError );
	long	SizeOf( TSRSetError );

	void	Serializa( TSROut_Search, unsigned char * ) ;
	boolean Deserializa( TSROut_Search *, unsigned char * ) ;
	void	Delete( TSROut_Search );
	long	SizeOf( TSROut_Search );

	void	Serializa( TSROut_GetFields, unsigned char * ) ;
	boolean Deserializa( TSROut_GetFields *, unsigned char * ) ;
	void	Delete( TSROut_GetFields );
	long	SizeOf( TSROut_GetFields );

	void	Serializa( TSROut_LBSC_Occurrence, unsigned char * ) ;
	boolean Deserializa( TSROut_LBSC_Occurrence *, unsigned char * ) ;
	void	Delete( TSROut_LBSC_Occurrence );
	long	SizeOf( TSROut_LBSC_Occurrence );

	void	Serializa( TSROut_GetSlot, unsigned char * ) ;
	boolean Deserializa( TSROut_GetSlot *, unsigned char * ) ;
	void	Delete( TSROut_GetSlot );
	long	SizeOf( TSROut_GetSlot );

	void	Serializa( TSROut_GetFieldRepetition, unsigned char * ) ;
	boolean Deserializa( TSROut_GetFieldRepetition *, unsigned char * ) ;
	void	Delete( TSROut_GetFieldRepetition );
	long	SizeOf( TSROut_GetFieldRepetition );

	void	Serializa( TSROut_GetFieldObj, unsigned char * ) ;
	boolean Deserializa( TSROut_GetFieldObj *, unsigned char * ) ;
	void	Delete( TSROut_GetFieldObj );
	long	SizeOf( TSROut_GetFieldObj );

	void	Serializa( TSROut_BaseInfo, unsigned char * ) ;
	boolean Deserializa( TSROut_BaseInfo *, unsigned char * ) ;
	void	Delete( TSROut_BaseInfo );
	long	SizeOf( TSROut_BaseInfo );

	void	Serializa( TSRIn_GetDataObj, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetDataObj *, unsigned char * ) ;
	long	SizeOf( TSRIn_GetDataObj );
	void	Delete( TSRIn_GetDataObj );

	void	Serializa( TSRIn_VerifyPassword, unsigned char * ) ;
	boolean Deserializa( TSRIn_VerifyPassword *, unsigned char * ) ;
	void	Delete( TSRIn_VerifyPassword );
	long	SizeOf( TSRIn_VerifyPassword );

	void	Serializa( TSRIn_DataOp, unsigned char * ) ;
	boolean Deserializa( TSRIn_DataOp *, unsigned char * ) ;
	void	Delete( TSRIn_DataOp );
	long	SizeOf( TSRIn_DataOp );

	void	Serializa( TSROut_GetData, unsigned char * ) ;
	boolean Deserializa( TSROut_GetData *, unsigned char * ) ;
	void	Delete( TSROut_GetData );
	long	SizeOf( TSROut_GetData );

	void	Serializa( TSROut_GetOpInfo, unsigned char * ) ;
	boolean Deserializa( TSROut_GetOpInfo *, unsigned char * ) ;
	void	Delete( TSROut_GetOpInfo );
	long	SizeOf( TSROut_GetOpInfo );

	void	Serializa( TSROut_GetUsersInfo, unsigned char * ) ;
	boolean Deserializa( TSROut_GetUsersInfo *, unsigned char * ) ;
	void	Delete( TSROut_GetUsersInfo );
	long	SizeOf( TSROut_GetUsersInfo );

	void	Serializa( TSROut_GetSvcParam, unsigned char * ) ;
	boolean Deserializa( TSROut_GetSvcParam *, unsigned char * ) ;
	long	SizeOf( TSROut_GetSvcParam );
	void	Delete( TSROut_GetSvcParam );

	void	Serializa( TSRIn_SetSvcParam, unsigned char * ) ;
	boolean Deserializa( TSRIn_SetSvcParam *, unsigned char * ) ;
	long	SizeOf( TSRIn_SetSvcParam );
	void	Delete( TSRIn_SetSvcParam );

	void	Serializa( TSRIn_ModifyBaseName, unsigned char * ) ;
	boolean Deserializa( TSRIn_ModifyBaseName *, unsigned char * ) ;
	void	Delete( TSRIn_ModifyBaseName );
	long	SizeOf( TSRIn_ModifyBaseName );

	void	Serializa( TSRIn_GetBaseLongName, unsigned char * ) ;
	boolean Deserializa( TSRIn_GetBaseLongName *, unsigned char * ) ;
	void	Delete( TSRIn_GetBaseLongName );
	long	SizeOf( TSRIn_GetBaseLongName );

	void	Serializa( TSROut_GetBaseLongName , unsigned char * ) ;
	boolean Deserializa( TSROut_GetBaseLongName *, unsigned char * ) ;
	void	Delete( TSROut_GetBaseLongName );
	long	SizeOf( TSROut_GetBaseLongName );

	void	Serializa( TSROut_GenericBuffer , unsigned char * ) ;
	boolean Deserializa( TSROut_GenericBuffer *, unsigned char * ) ;
	void	Delete( TSROut_GenericBuffer );
	long	SizeOf( TSROut_GenericBuffer );

	void	Serializa( TSROut_ACLLists, unsigned char * ) ;
	boolean Deserializa( TSROut_ACLLists *, unsigned char * ) ;
	void	Delete( TSROut_ACLLists );
	long	SizeOf( TSROut_ACLLists );

	void	Serializa( TSRIn_AllRepetitions, unsigned char * ) ;
	boolean Deserializa( TSRIn_AllRepetitions *, unsigned char * ) ;
	void	Delete( TSRIn_AllRepetitions );
	long	SizeOf( TSRIn_AllRepetitions );

	void	Serializa( TSRIn_BreakSecurity, unsigned char * ) ;
	boolean Deserializa( TSRIn_BreakSecurity *, unsigned char * ) ;
	void	Delete( TSRIn_BreakSecurity );
	long	SizeOf( TSRIn_BreakSecurity );

	void	Serializa( TSRIn_MaintBase, unsigned char * ) ;
	boolean Deserializa( TSRIn_MaintBase *, unsigned char * ) ;
	long	SizeOf( TSRIn_MaintBase );
	void	Delete( TSRIn_MaintBase );

	// estrutura
	void	Serializa( TSRMaintBase, unsigned char * ) ;
	boolean Deserializa( TSRMaintBase *, unsigned char * ) ;
	long	SizeOf( TSRMaintBase );
	void	Delete( TSRMaintBase );

	// array
	void	Serializa( TSRMaintBase *, unsigned char *, long ) ;
	boolean Deserializa( TSRMaintBase **, unsigned char *, long ) ;
	long	SizeOf( TSRMaintBase *, long );

	// ponteiro
	void	Serializa( TSRMaintBase *, unsigned char *) ;
	boolean Deserializa( TSRMaintBase **, unsigned char * ) ;
	long	SizeOf( TSRMaintBase * );
	void	Delete( TSRMaintBase * );

	void	Serializa( TSROut_MaintBase, unsigned char * ) ;
	boolean Deserializa( TSROut_MaintBase *, unsigned char * ) ;
	long	SizeOf( TSROut_MaintBase );
	void	Delete( TSROut_MaintBase );

};



#endif	// 	_RPCSERIAL_H_