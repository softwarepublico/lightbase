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

/************************************************************/
/*	Métodos Stubs da classe LBSC_Data						*/
/*	Programadores: 	Renata Catao							*/
/*					Tarcio Rodrigues						*/
/*					Tricia Santos							*/
/*	Ultima alt : 21/11/95									*/
/************************************************************/

#ifndef _DATACL_H_
	#include <datacl.h>
#endif	// _DATACL_H_

#ifndef _MMDEFS_H_
	#include <MMDEFS.H>
#endif	// _MMDEFS_H_

#ifndef __lbsrpc_h__
	#include <lbsrpc.h>
#endif	// __lbsrpc_h__

#ifndef _DEFMAC_H_
#include	<defmac.h>
#endif

#ifndef _ENCRIPT_H_
	#include <encript.h>
#endif	// _ENCRIPT_H_

#ifndef _SESSCL_H_
	#include <sesscl.h>
#endif	// _SESSCL_H_

// so pra constar...
class COccurList;
class C_Buffer;

#ifndef _CLNTFUNCS_H_
	#include <clntfuncs.h>
#endif	// _CLNTFUNCS_H_



int
LBSC_Data::Compare( LBSC_Data *plbscdData, int iSearchType )
{
	if( iSearchType == CMPDATANUMBER ){
		return( (this->iServerIndex == plbscdData->iServerIndex) ? 0 : 1 );
	}else{
		return( 0 );
	}
}


/****************************/
void *
LBSC_Data::GetData()
{
	return NULL;

/******
ATENCAO: ESTE METODO NAO ESTA SENDO IMPLEMENTADO PELO FATO DE SO SER
USADO COM OPERADORES. Vladimir Catao - 24.09.96

  TSROut_GetData	sOut;

	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return NULL;
	}

	TSRGenericObj InPar;
	memset( &InPar, 0, sizeof(InPar));

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lObj = this->obj;
	
	boolean bNetError = TRUE;
	boolean bRetry = FALSE;
	do {
		RpcTryExcept{
				Criptografa( InPar );
	       		sOut = RPC_Data_GetData(  InPar );
				bNetError = FALSE;
				bRetry = FALSE;
		}
		RpcExcept(1){
			bRetry = LBSC_ClntNet::EnviaNovaRPC();
		}
		RpcEndExcept
	} while( bRetry );
	LBSC_ClntNet::FreeRPCHandle();
	if( bNetError ) {

		LBSC_ClntNet::TrataErroRPC( this->ServerAddr );
		return NULL;	
	}

	char *szData = new char [ sOut.lBufferLen ];
	if ( !szData ) {	// sem memoria, considere um erro de rede; trate-o
		LBSC_ClntNet::TrataErroRPC( this->ServerAddr );
		return ( NULL );
	}

	memcpy( szData, sOut.szBuffer, sOut.lBufferLen );
	ClntFree( (void *) sOut.szBuffer );
	
	return( (void*)szData ); 	

******/
}

/****************************
Nada de operadores

LBSC_Data::operator long ()
{	
	long lAux = *((long*)GetData() );
	return lAux;
}
******************/

/****************************
Nada de operadores

LBSC_Data::operator double ()
{
	double dAux = *((double*)GetData() );
	return dAux;
}
***************/

/****************************
Nada de operadores

LBSC_Data::operator char* ()
{
	return (char *)GetData();
}
*********************/

/****************************
Nada de operadores

LBSC_Data::operator void* ()
{
	return GetData();
}
*********************/

/****************************
Nada de operadores

LBSC_Data::operator LBSC_Binary* ()
{
	return ( LBSC_Binary * )( GetData() );
}
******************/

/****************************
Nada de operadores

LBSC_Data::operator LBSC_Reference* ()
{
	return ( LBSC_Reference * )( GetData() );
}
*******************/

/****************************
Nada de operadores

LBSC_Data::operator JulTy ()
{
	return *((JulTy*)GetData() );
}
*******************/

/****************************
Nada de operadores

LBSC_Data::operator BYTE ()
{
	return *( (BYTE*)GetData() );
}
************************/

/****************************
Nada de operadores

LBSC_Data::operator short ()
{
	return *( (short*)GetData() );
}
**********************/

/****************************
Nada de operadores

LBSC_Data::operator float ()
{
	return *( (float*)GetData() );
}
*********************/

							
/****************************

UFA!!!! ... Daqui pra frente eh um comentario so... (Vladimir Catao, 08.02.96)

void
LBSC_Data::operator = ( long lPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_LONG;
	InPar.lLen		= sizeof( long );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &lPar, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( double dPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_DOUBLE;
	InPar.lLen		= sizeof( double );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &dPar, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( char *szPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_STRING;
	InPar.lLen		= strlen( szPar ) + 1;
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	strcpy( (char*)InPar.szPar, szPar );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( void *pvBuffer )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	int iRet;

	RpcTryExcept{
	       	iRet = (int)RPC_Data_GetSize(  this->obj );
	}
	RpcExcept(1){
		return;
	}
	RpcEndExcept

	Criptografa( InPar );
	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_VOID;
	InPar.lLen 		= (long)iRet;
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, pvBuffer, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( C_Date &cdDate )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_DATE;
	InPar.lLen		= sizeof( long );
	long lAux		= cdDate.Hash();
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &lAux, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( C_Time &ctTime )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_TIME;
	InPar.lLen		= sizeof( long );
	long lAux		= ctTime.Seconds();
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &lAux, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( LBSC_Binary & cbBinary )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_BINARY;
	InPar.lFormat	= (long)cbBinary.iFormat;
	InPar.lLen		= (long)cbBinary.iLen;
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &(cbBinary.pvBuffer), cbBinary.iLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	LBSC_ClntNet::FreeRPCHandle();
	delete InPar.szPar;
	return;
}

/****************************
void
LBSC_Data::operator = ( LBSC_Reference & crReference )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_REFERENCE;
	InPar.lFormat	= (long) crReference.iFormat;
	InPar.lLen		= (long) strlen( crReference.szFileName );
	InPar.szPar		= new unsigned char[ InPar.lLen + 1 ];
	strcpy( (char*)InPar.szPar, crReference.szFileName );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
LBSC_Data&
LBSC_Data::operator = ( LBSC_Data &b )
{
	long lRet;

	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return *this;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_DATA;
	InPar.lLen		= (long)sizeof( long );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	long lAux		= b.obj;
	memcpy( InPar.szPar, &lAux, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return *this;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return *this;
}

/****************************
void
LBSC_Data::operator = ( BYTE bPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_BYTE;
	InPar.lLen		= (long) sizeof( BYTE );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &bPar, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( short sPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_SHORT;
	InPar.lLen		= (long) sizeof( short );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &sPar, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}

/****************************
void
LBSC_Data::operator = ( float fPar )
{
	if( !LBSC_ClntNet::GetRPCHandle( this->ServerAddr ) ){
		return;
	}

	TSRIn_DataOp	InPar;
	memset( &InPar, 0, sizeof( InPar ) );

	InPar.sCtrlInfo = ObtemControlInfo();
	InPar.lDataObj 	= this->obj;
	InPar.sOpType	= DATA_OPERATOR_EQUAL_FLOAT;
	InPar.lLen		= (long) sizeof( float );
	InPar.szPar		= new unsigned char[ InPar.lLen ];
	memcpy( InPar.szPar, &fPar, InPar.lLen );

	RpcTryExcept{
		Criptografa( InPar );
	       	RPC_Data_Operator(  InPar );
	}
	RpcExcept(1){
		delete InPar.szPar;
		return;
	}
	RpcEndExcept

	delete InPar.szPar;
	LBSC_ClntNet::FreeRPCHandle();
	return;
}





*************************************************/
