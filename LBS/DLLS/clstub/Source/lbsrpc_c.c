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

/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 22 12:07:58 2005
 */
/* Compiler settings for lbsrpc.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include <malloc.h>
#include "lbsrpc.h"

#define TYPE_FORMAT_STRING_SIZE   2855                              
#define PROC_FORMAT_STRING_SIZE   651                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: lbsrpc, ver. 17.0,
   GUID={0x9725e2c0,0x72c5,0x11cf,{0x98,0xa2,0x44,0x45,0x53,0x54,0x00,0x00}} */

handle_t _lbsrpc_IfHandle;


static const RPC_CLIENT_INTERFACE lbsrpc___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x9725e2c0,0x72c5,0x11cf,{0x98,0xa2,0x44,0x45,0x53,0x54,0x00,0x00}},{17,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE lbsrpc_v17_0_c_ifspec = (RPC_IF_HANDLE)& lbsrpc___RpcClientInterface;

extern const MIDL_STUB_DESC lbsrpc_StubDesc;

static RPC_BINDING_HANDLE lbsrpc__MIDL_AutoBindHandle;


TSRGenericObj RPC_Session_New( 
    /* [in] */ TSRControlInfo sCtrlInfo)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSRGenericObj _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          0);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sCtrlInfo,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[8] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sCtrlInfo,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[8] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSRGenericObj  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_Session_Delete( 
    /* [in] */ TSRGenericObj DeadSession)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          1);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&DeadSession,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&DeadSession,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


long RPC_Session_DeleteUDB( 
    /* [in] */ TSRIn_DeleteUDB InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          2);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_DeleteDefaultUserBase( 
    /* [in] */ TSRIn_DeleteUDB InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          3);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSRTicket RPC_Session_Login( 
    /* [in] */ TSRIn_Login InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSRTicket _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          4);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[138] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[138] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSRTicket  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_Logout( 
    /* [in] */ TSRGenericObj Session)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          5);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Session,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Session,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_CloseBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          6);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_CreateBaseDef( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          7);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_CreateBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          8);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_DeleteBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          9);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_CreateUDB( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          10);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_AddUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          11);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_OpenBase RPC_Session_OpenBase( 
    /* [in] */ TSRIn_OpenBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_OpenBase _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          12);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[46] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_OpenBase  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[442],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_AddGroupToUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          13);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Session_IsLogged( 
    /* [in] */ TSRGenericObj Session)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          14);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Session,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Session,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatServers( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          15);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[60] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatServersForUser( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          16);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDBLogged( 
    /* [in] */ TSRGenericObj Session)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          17);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Session,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Session,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDBsForUser( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          18);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[80] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_WhatUDB( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          19);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserName( 
    /* [in] */ TSRGenericObj Session)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          20);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Session,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Session,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_ReorganizeBase( 
    /* [in] */ TSRIn_ReorgBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          21);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[582] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[582] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[88] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_TicketIsOk( 
    /* [in] */ TSRIn_GetGroups InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          22);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[94] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetGroups( 
    /* [in] */ TSRIn_GetGroups InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          23);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[100] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_DelUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          24);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UpdateUserPassword( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          25);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[108] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UpdateUserDescription( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          26);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[108] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UpdateUserType( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          27);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[108] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_GetUserType( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          28);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[108] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserDescription( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          29);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[80] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_DelGroupFromUser( 
    /* [in] */ TSRIn_AddDelGroupUser InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          30);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUsers( 
    /* [in] */ TSRIn_GetGroups InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          31);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[608] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[100] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetUsersData RPC_Session_GetUsersData( 
    /* [in] */ TSRIn_UserGenInfos InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetUsersData _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          32);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[514] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[114] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetUsersData  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[678],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_WhatBases RPC_Session_WhatBases( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_WhatBases _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          33);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_WhatBases  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_WhatBases RPC_Session_WhatBasesForUser( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_WhatBases _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          34);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_WhatBases  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_WhatBases RPC_Session_WhatBasesOnServer( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_WhatBases _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          35);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_WhatBases  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_WhatBases RPC_Session_WhatBasesForUserOnServer( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_WhatBases _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          36);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_WhatBases  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_Export( 
    /* [in] */ TSRIn_Export InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          37);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[712] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[712] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_ExportBaseFormat( 
    /* [in] */ TSRIn_Export InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          38);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[712] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[712] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_Import( 
    /* [in] */ TSRIn_Import InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          39);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[784] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[784] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UpdateUserAddress( 
    /* [in] */ TSRIn_UpdateUserAddress InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          40);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[142] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UpdateUserPhone( 
    /* [in] */ TSRIn_UpdateUserAddress InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          41);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[142] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserAddress( 
    /* [in] */ TSRIn_UpdateUserAddress InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          42);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[148] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetUserPhone( 
    /* [in] */ TSRIn_UpdateUserAddress InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          43);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[864] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[148] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_CreateDefaultUserBase( 
    /* [in] */ TSRIn_CreateDefaultUserBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          44);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrComplexStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                    (unsigned char __RPC_FAR *)&InPar,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[922] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrComplexStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                  (unsigned char __RPC_FAR *)&InPar,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[922] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[156] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_RebuildControl( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          45);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[162] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_IncorporateBase( 
    /* [in] */ TSRIn_IncorporateBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          46);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_ClearBase( 
    /* [in] */ TSRIn_IncorporateBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          47);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_RenameBase( 
    /* [in] */ TSRIn_RenameBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          48);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_ReorganizeUDB( 
    /* [in] */ TSRIn_IncorporateBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          49);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[952] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_ReorganizeDefaultUserBase( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          50);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_LeaveBase( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          51);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetDefUserBaseName( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          52);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[60] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_SetServerParam( 
    /* [in] */ TSRIn_SetSvcParam InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          53);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1096] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1096] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[182] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetSvcParam RPC_Session_GetServerParam( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetSvcParam _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          54);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[188] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetSvcParam  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[442],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetUsersInfo RPC_Session_GetUsersInfo( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetUsersInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          55);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[196] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetUsersInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_UnLockRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          56);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_KillSessions( 
    /* [in] */ TSRIn_KillSessions InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          57);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1132] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1132] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_KillServer( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          58);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetBaseLongName( 
    /* [in] */ TSRIn_GetBaseLongName InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          59);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1180] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1180] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[210] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_Session_CancelOperation( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          60);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


TSROut_GetOpInfo RPC_Session_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetOpInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          61);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[218] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetOpInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1210],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_Session_StBreakSecurity( 
    /* [in] */ TSRIn_BreakSecurity InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          62);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void RPC_Session_BreakSecurity( 
    /* [in] */ TSRIn_BreakSecurity InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          63);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


long RPC_Session_ValidUser( 
    /* [in] */ TSRIn_DeleteUDB InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          64);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_StGetGroups( 
    /* [in] */ TSRNetInfo InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          65);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[226] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_SetBaseForMaintenance( 
    /* [in] */ TSRIn_MaintBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          66);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1230] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1230] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[234] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetDefaultWarningMsg( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          67);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GetBaseWarningMsg( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          68);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Session_GeMaintBaseUserName( 
    /* [in] */ TSRIn_What InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          69);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[454] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_MaintBase RPC_Session_GetReservedMaintBases( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_MaintBase _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          70);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[240] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_MaintBase  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1322],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Session_NeedReprocOnConvert( 
    /* [in] */ TSRIn_OpenBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          71);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[248] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


int RPC_Session_ConvertBase( 
    /* [in] */ TSRIn_OpenBase InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    int _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          72);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[392] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[254] );
        
        _RetVal = *(( int __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_InstalInfo RPC_Session_GetInstalInfo( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_InstalInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          73);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[260] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_InstalInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1342],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Error_SetLastError( 
    /* [in] */ TSRSetError sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          74);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1360] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1360] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[264] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Error_LastError( 
    /* [in] */ TSRGenericObj lObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          75);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Error_LastErrorDesc( 
    /* [in] */ TSRGenericObj lObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          76);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetFieldRepetition RPC_Base_GetFieldRepetition( 
    /* [in] */ TSRIn_GetFieldRepetition sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetFieldRepetition _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          77);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1372] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1372] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[270] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetFieldRepetition  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1400],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetFieldRepetitionByVal( 
    /* [in] */ TSRIn_GetFieldRepetitionByVal sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          78);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1432] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1432] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[278] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PutFieldRepetition( 
    /* [in] */ TSRIn_PutFieldRepetition sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          79);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1472] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1472] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[284] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PutFieldRepetitionByIndex( 
    /* [in] */ TSRIn_PutFieldRepetition sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          80);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1472] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1472] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[284] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldRepetition( 
    /* [in] */ TSRIn_ModifyFieldRepetition sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          81);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1522] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1522] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[290] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetFieldObj RPC_Base_GetFieldObj( 
    /* [in] */ TSRIn_DelFieldGetFieldObj sIn)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetFieldObj _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          82);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sIn,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sIn,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[296] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetFieldObj  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1588],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_BaseObjOk( 
    /* [in] */ TSRGenericObj Base)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          83);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Base,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Base,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AddField( 
    /* [in] */ TSRIn_AddField InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          84);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1640] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1640] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[304] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DelField( 
    /* [in] */ TSRIn_DelFieldRepetition InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          85);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[310] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldPassword( 
    /* [in] */ TSRIn_ModifyFieldPassword InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          86);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[316] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldName( 
    /* [in] */ TSRIn_ModifyFieldName InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          87);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[316] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldDescription( 
    /* [in] */ TSRIn_ModifyFieldDescription InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          88);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1742] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[316] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldSize( 
    /* [in] */ TSRIn_ModifyFieldSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          89);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[322] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumberOfFields( 
    /* [in] */ TSRGenericObj Base)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          90);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Base,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Base,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DelFieldRepetition( 
    /* [in] */ TSRIn_DelFieldRepetition InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          91);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[310] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_InsertBlankRepetition( 
    /* [in] */ TSRIn_DelFieldRepetition InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          92);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1714] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[310] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumberOfRepetition( 
    /* [in] */ TSRIn_GetNumberOfRepetition InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          93);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[328] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetFieldRepetitionSize( 
    /* [in] */ TSRIn_GetFieldRepetitionSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          94);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1828] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1828] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[334] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumRecords( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          95);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_CurrRecNum( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          96);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetIndexRecNum( 
    /* [in] */ TSRIn_TicketBOOLPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          97);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


byte RPC_Base_CurrRecStatus( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    byte _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          98);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[340] );
        
        _RetVal = *(( byte __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LockRecord( 
    /* [in] */ TSRIn_TicketBOOLPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          99);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ReleaseRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          100);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_UpdateRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          101);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AppendRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          102);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ReadRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          103);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DeleteRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          104);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ClearRecord( 
    /* [in] */ TSRGenericObj Base)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          105);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Base,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Base,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetLockTimeOut( 
    /* [in] */ TSRIn_SetLockTimeOut InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          106);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetReorganizeRecQuant( 
    /* [in] */ TSRIn_SetReorganizeRecQuant InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          107);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_FirstRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          108);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LastRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          109);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_NextRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          110);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PreviousRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          111);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_NthRecord( 
    /* [in] */ TSRIn_Nth InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          112);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_CurrentRecord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          113);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumOccurrences( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          114);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SaveOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          115);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SortOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          116);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_EnableSecureSort( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          117);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SecureSortStatus( 
    /* [in] */ TSRGenericObj Base)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          118);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&Base,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&Base,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LoadOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          119);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_EnableOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          120);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetOLRecNumber( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          121);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_UnloadOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          122);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DeleteOcList( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          123);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[346] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DeleteOcRecords( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          124);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetNavigationByIndex( 
    /* [in] */ TSRIn_SetNavigationLocate InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          125);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[352] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetNavigationByKey( 
    /* [in] */ TSRIn_SetNavigationLocate InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          126);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[352] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_Locate( 
    /* [in] */ TSRIn_SetNavigationLocate InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          127);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1904] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[352] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumberOfSlots( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          128);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetSlotSize( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          129);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetFieldSlotSize( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          130);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AddGoWord( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          131);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[364] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DelGoWord( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          132);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[364] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetGowords( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          133);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[370] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_SetGowords( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          134);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[378] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetMinkeysize( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          135);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[364] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetMinkeysize( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          136);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[364] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldIndexAttrib( 
    /* [in] */ TSRIn_ModifyFieldIndexAttrib InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          137);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[322] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyFieldAttrib( 
    /* [in] */ TSRIn_ModifyFieldAttrib InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          138);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1790] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[322] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetFields RPC_Base_GetFields( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetFields _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          139);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[384] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetFields  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2010],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetCurrentOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          140);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetFirstOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          141);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetLastOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          142);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetNextOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          143);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetPreviousOccurrence( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          144);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_LBSC_Occurrence RPC_Base_GetNthOccurrence( 
    /* [in] */ TSRIn_Nth InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_LBSC_Occurrence _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          145);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[392] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_LBSC_Occurrence  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2030],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_Search RPC_Base_Search( 
    /* [in] */ TSRIn_Search InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_Search _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          146);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2056] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2056] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[400] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_Search  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2102],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetCurrentExpression( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          147);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetOcListExpression( 
    /* [in] */ TSRIn_OcList InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          148);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1854] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[416] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetCurrentStopWord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          149);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DelStopWord( 
    /* [in] */ TSRIn_AddStopWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          150);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2122] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2122] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[424] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetFirstStopWord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          151);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetLastStopWord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          152);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetNextStopWord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          153);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetPreviousStopWord( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          154);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetNthStopWord( 
    /* [in] */ TSRIn_Nth InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          155);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_SearchStopWord( 
    /* [in] */ TSRIn_SearchStopWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          156);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2158] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2158] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[430] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          157);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[438] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          158);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[438] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DelACLPerm( 
    /* [in] */ TSRIn_ACLPerm InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          159);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2196] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[438] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_EnableOnLineIndex( 
    /* [in] */ TSRIn_EnableOnLineIndex InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          160);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2236] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2236] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[444] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_OnLineIndexStatus( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          161);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_UpdateIndex( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          162);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_IndexAll( 
    /* [in] */ TSRIn_IndexAll InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          163);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2248] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2248] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[450] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetSlot RPC_Base_GetSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetSlot _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          164);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[456] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetSlot  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1400],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PutSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          165);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[464] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetSlot RPC_Base_GetFieldSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetSlot _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          166);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[456] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetSlot  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1400],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PutFieldSlot( 
    /* [in] */ TSRIn_GetSlotPutSlot InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          167);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2274] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[464] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumberOfCounters( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          168);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          169);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_PutCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          170);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_IncCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          171);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DecCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          172);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LockCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          173);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ReleaseCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          174);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNextCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          175);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetPreviousCount( 
    /* [in] */ TSRIn_GetSlotSize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          176);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1944] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyPassword( 
    /* [in] */ TSRIn_ModifyPassword InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          177);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyMaintenancePassword( 
    /* [in] */ TSRIn_ModifyPassword InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          178);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetUserBase( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          179);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetOwnerName( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          180);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetFullBaseName RPC_Base_GetFullBaseName( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetFullBaseName _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          181);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[470] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetFullBaseName  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2302],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetFullBaseName RPC_Base_GetBaseName( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetFullBaseName _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          182);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[470] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetFullBaseName  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2302],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IsEncrypt( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          183);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IsFullAccess( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          184);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


byte RPC_Base_GetBaseType( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    byte _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          185);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[478] );
        
        _RetVal = *(( byte __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetBaseVersion( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          186);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyBaseType( 
    /* [in] */ TSRIn_ModifyBaseType InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          187);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1360] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1360] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[264] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_IndexString( 
    /* [in] */ TSRIn_IndexString InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          188);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2314] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2314] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[484] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_UnindexString( 
    /* [in] */ TSRIn_IndexString InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          189);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2314] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2314] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[484] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IndexSystemOk( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          190);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumberOfStopWords( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          191);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AddStopWord( 
    /* [in] */ TSRIn_AddStopWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          192);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2122] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2122] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[424] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyBaseOwnerName( 
    /* [in] */ TSRIn_ModifyBaseOwnerName InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          193);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


short RPC_Base_GetFieldType( 
    /* [in] */ TSRIn_GetFieldTypeId InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    short _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          194);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2354] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2354] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[490] );
        
        _RetVal = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetFieldId( 
    /* [in] */ TSRIn_GetFieldTypeId InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          195);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2354] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2354] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[496] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetFieldIndexAttrib( 
    /* [in] */ TSRIn_GetFieldIndexAttrib InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          196);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2382] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2382] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[502] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_WhatBases RPC_Base_GetACLListPermission( 
    /* [in] */ TSRIn_GetACLListPerm InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_WhatBases _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          197);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1562] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[508] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_WhatBases  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_ExchangeOperator( 
    /* [in] */ TSRIn_ExchangeOperator InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          198);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2408] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2408] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[516] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SetMask( 
    /* [in] */ TSRIn_Mask InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          199);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[524] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetMask( 
    /* [in] */ TSRIn_Mask InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          200);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[530] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SaveMasks( 
    /* [in] */ TSRIn_Mask InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          201);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[524] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LoadMasks( 
    /* [in] */ TSRIn_Mask InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          202);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2432] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[524] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ClearMasks( 
    /* [in] */ TSRGenericObj BaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          203);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&BaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&BaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AddPhone( 
    /* [in] */ TSRIn_Phone InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          204);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[538] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DeletePhone( 
    /* [in] */ TSRIn_Phone InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          205);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[538] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SavePhone( 
    /* [in] */ TSRIn_Phone InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          206);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[538] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LoadPhone( 
    /* [in] */ TSRIn_Phone InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          207);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[538] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ClearPhone( 
    /* [in] */ TSRGenericObj BaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          208);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&BaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&BaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_FindPhone( 
    /* [in] */ TSRIn_Phone InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          209);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2470] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[538] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_SetStandardizer( 
    /* [in] */ TSRIn_Standardize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          210);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[544] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_Standardize( 
    /* [in] */ TSRIn_Standardize InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          211);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[552] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_AddSynonym( 
    /* [in] */ TSRIn_Synonym InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          212);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[552] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_DeleteSynonym( 
    /* [in] */ TSRIn_Synonym InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          213);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[552] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_SaveSynonym( 
    /* [in] */ TSRIn_Synonym InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          214);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[552] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_LoadSynonym( 
    /* [in] */ TSRIn_Synonym InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          215);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[552] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ClearSynonym( 
    /* [in] */ TSRGenericObj BaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          216);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&BaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&BaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_FindSynonym( 
    /* [in] */ TSRIn_Synonym InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          217);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2528] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[544] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_OLAnd( 
    /* [in] */ TSRIn_OL InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          218);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[558] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_OLOr( 
    /* [in] */ TSRIn_OL InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          219);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[558] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_OLXor( 
    /* [in] */ TSRIn_OL InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          220);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[558] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_OLNot( 
    /* [in] */ TSRIn_OL InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          221);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[558] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IsExportable( 
    /* [in] */ TSRGenericObj BaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          222);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&BaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&BaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_BlockReExport( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          223);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyRecordPassword( 
    /* [in] */ TSRIn_ModifyPassword InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          224);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1022] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IsReadOnly( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          225);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_IsExclusive( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          226);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_Flush( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          227);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[564] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumActiveRecords( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          228);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyMaxKeySize( 
    /* [in] */ TSRIn_CreateCloseDelete InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          229);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[202] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_BaseInfo RPC_Base_GetBaseInfo( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_BaseInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          230);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[570] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_BaseInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2604],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumOLRecords( 
    /* [in] */ TSRIn_OL InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          231);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2576] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[558] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_GetNumRecIndex( 
    /* [in] */ TSRGenericObj lBaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          232);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lBaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lBaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_Base_GetStopIndex( 
    /* [in] */ TSRGenericObj BaseObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          233);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&BaseObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&BaseObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_Base_SetStopIndex( 
    /* [in] */ TSRIn_TicketBOOLPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          234);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


long RPC_Base_ClearBase( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          235);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_MGetFieldRep RPC_Base_MGetFieldRepetition( 
    /* [in] */ TSRIn_MGetPutFieldRep InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_MGetFieldRep _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          236);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2662] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2662] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[584] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_MGetFieldRep  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_MPutFieldRepetition( 
    /* [in] */ TSRIn_MGetPutFieldRep InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          237);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2662] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2662] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[592] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetStopWords( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          238);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[408] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_ModifyBaseName( 
    /* [in] */ TSRIn_ModifyBaseName InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          239);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2712] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2712] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[598] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetBaseLongName RPC_Base_GetBaseLongName( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetBaseLongName _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          240);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[604] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetBaseLongName  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2736],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_Base_CancelOperation( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          241);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


TSROut_GetOpInfo RPC_Base_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetOpInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          242);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[218] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetOpInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1210],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GenericBuffer RPC_Base_GetAllFieldSlots( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GenericBuffer _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          243);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[196] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GenericBuffer  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_ACLLists RPC_Base_GetAllACLLists( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_ACLLists _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          244);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[612] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_ACLLists  ));
        NdrComplexStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                    (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2756],
                                    (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GenericBuffer RPC_Base_GetAllRepetitions( 
    /* [in] */ TSRIn_AllRepetitions InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GenericBuffer _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          245);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2814] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2814] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[620] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GenericBuffer  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GenericBuffer RPC_Base_GetAllOccurrences( 
    /* [in] */ TSRIn_TicketPar InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GenericBuffer _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          246);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[196] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GenericBuffer  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Base_EnableFastRecord( 
    /* [in] */ TSRIn_EnableOnLineIndex InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          247);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2236] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2236] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[444] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GenericBuffer RPC_Base_GetBaseTimeInfo( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GenericBuffer _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          248);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[628] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GenericBuffer  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Base_GetDirBase( 
    /* [in] */ TSRIn_GetBaseLongName InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          249);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1180] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1180] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[210] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetFirstGoWord( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          250);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetNextGoWord( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          251);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetCurrentGoWord( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          252);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetNthGoWord( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          253);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[370] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_SearchGoWord( 
    /* [in] */ TSRIn_GoWord InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          254);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1956] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[370] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Field_GetNbrOfGoWord( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          255);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


/* [string] */ unsigned char __RPC_FAR *RPC_Field_GetAliasName( 
    /* [in] */ TSRGenericObj lFieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    unsigned char __RPC_FAR *_RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          256);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lFieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lFieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        _RetVal = 0;
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                              (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Field_Clear( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          257);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Field_GetId( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          258);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Field_GetSize( 
    /* [in] */ TSRGenericObj FieldObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          259);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&FieldObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&FieldObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Field_VerifyPassword( 
    /* [in] */ TSRIn_VerifyPassword InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          260);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2408] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2408] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[636] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


TSROut_GetData RPC_Data_GetData( 
    /* [in] */ TSRGenericObj DataObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetData _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          261);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&DataObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&DataObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[628] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetData  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Data_GetSize( 
    /* [in] */ TSRGenericObj lDataObj)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          262);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&lDataObj,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&lDataObj,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_OpInfo_CancelOperation( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          263);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


TSROut_GetOpInfo RPC_OpInfo_GetOpInfo( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GetOpInfo _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          264);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[218] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GetOpInfo  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1210],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_SvcInitContext( 
    /* [in] */ TSRClntInitInfo sInitInfo)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          265);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sInitInfo,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2840] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sInitInfo,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2840] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[642] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


boolean RPC_SvcEndContext( 
    /* [in] */ TSRClntInitInfo sCtrlInfo)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    boolean _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          266);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&sCtrlInfo,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2840] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&sCtrlInfo,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2840] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[642] );
        
        _RetVal = *(( boolean __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


void RPC_SvcIsUp( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          267);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


TSROut_GenericBuffer RPC_Session_GetUDBTimeInfo( 
    /* [in] */ TSRGenericObj InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    TSROut_GenericBuffer _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    void __RPC_FAR *_p__RetVal;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          268);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[628] );
        
        _p__RetVal = (void __RPC_FAR *) &_RetVal;
        MIDL_memset(
               _p__RetVal,
               0,
               sizeof( TSROut_GenericBuffer  ));
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&_p__RetVal,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                   (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RPC_Session_KillSessionsEx( 
    /* [in] */ TSRIn_KillSessions InPar)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&lbsrpc_StubDesc,
                          269);
        
        
        _Handle = _lbsrpc_IfHandle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)&InPar,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1132] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)&InPar,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1132] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}

extern MALLOC_FREE_STRUCT _MallocFreeStruct;

static const MIDL_STUB_DESC lbsrpc_StubDesc = 
    {
    (void __RPC_FAR *)& lbsrpc___RpcClientInterface,
    NdrRpcSmClientAllocate,
    NdrRpcSmClientFree,
    &_lbsrpc_IfHandle,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    &_MallocFreeStruct,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static void __RPC_FAR * __RPC_USER
lbsrpc_malloc_wrapper( size_t _Size )
{
    return( malloc( _Size ) );
}

static void  __RPC_USER
lbsrpc_free_wrapper( void __RPC_FAR * _p )
{
    free( _p );
}

static MALLOC_FREE_STRUCT _MallocFreeStruct = 
{
    lbsrpc_malloc_wrapper,
    lbsrpc_free_wrapper
};

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x44,		/* x86, MIPS & PPC Stack size = 68 */
#else
			0x44,		/* Alpha Stack size = 68 */
#endif
/*  2 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/*  4 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/*  6 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/*  8 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 10 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 12 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 14 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 16 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */
/* 18 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 22 */	NdrFcShort( 0x8a ),	/* Type Offset=138 */
/* 24 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 28 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 30 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 32 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x55,		/* x86, MIPS & PPC Stack size = 85 */
#else
			0x56,		/* Alpha Stack size = 86 */
#endif
/* 36 */	NdrFcShort( 0xca ),	/* Type Offset=202 */
/* 38 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 42 */	NdrFcShort( 0x142 ),	/* Type Offset=322 */
/* 44 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 46 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 48 */	NdrFcShort( 0x188 ),	/* Type Offset=392 */
/* 50 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 52 */	NdrFcShort( 0x1ba ),	/* Type Offset=442 */
/* 54 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 56 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 58 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x3,		/* FC_SMALL */
/* 60 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 62 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 64 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 66 */	NdrFcShort( 0x1c6 ),	/* Type Offset=454 */
/* 68 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 70 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 72 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 74 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 76 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 80 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x51,		/* x86, MIPS & PPC Stack size = 81 */
#else
			0x52,		/* Alpha Stack size = 82 */
#endif
/* 82 */	NdrFcShort( 0x202 ),	/* Type Offset=514 */
/* 84 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 86 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 88 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 90 */	NdrFcShort( 0x246 ),	/* Type Offset=582 */
/* 92 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 94 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 96 */	NdrFcShort( 0x260 ),	/* Type Offset=608 */
/* 98 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 100 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 102 */	NdrFcShort( 0x260 ),	/* Type Offset=608 */
/* 104 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 106 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 108 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x51,		/* x86, MIPS & PPC Stack size = 81 */
#else
			0x52,		/* Alpha Stack size = 82 */
#endif
/* 110 */	NdrFcShort( 0x202 ),	/* Type Offset=514 */
/* 112 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 114 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x51,		/* x86, MIPS & PPC Stack size = 81 */
#else
			0x52,		/* Alpha Stack size = 82 */
#endif
/* 116 */	NdrFcShort( 0x202 ),	/* Type Offset=514 */
/* 118 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x5,		/* x86, MIPS & PPC Stack size = 5 */
#else
			0x6,		/* Alpha Stack size = 6 */
#endif
/* 120 */	NdrFcShort( 0x2a6 ),	/* Type Offset=678 */
/* 122 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 124 */	NdrFcShort( 0x1c6 ),	/* Type Offset=454 */
/* 126 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 128 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 130 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4e,		/* x86, MIPS & PPC Stack size = 78 */
#else
			0x4e,		/* Alpha Stack size = 78 */
#endif
/* 132 */	NdrFcShort( 0x2c8 ),	/* Type Offset=712 */
/* 134 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 136 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 138 */	NdrFcShort( 0x310 ),	/* Type Offset=784 */
/* 140 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 142 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 144 */	NdrFcShort( 0x360 ),	/* Type Offset=864 */
/* 146 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 148 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 150 */	NdrFcShort( 0x360 ),	/* Type Offset=864 */
/* 152 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 154 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 156 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x6,		/* x86, MIPS & PPC Stack size = 6 */
#else
			0x6,		/* Alpha Stack size = 6 */
#endif
/* 158 */	NdrFcShort( 0x39a ),	/* Type Offset=922 */
/* 160 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 162 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 164 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 166 */	NdrFcShort( 0x3b8 ),	/* Type Offset=952 */
/* 168 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 170 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 172 */	NdrFcShort( 0x3fe ),	/* Type Offset=1022 */
/* 174 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 176 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 178 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 180 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 182 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 184 */	NdrFcShort( 0x448 ),	/* Type Offset=1096 */
/* 186 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 188 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 190 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 192 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 194 */	NdrFcShort( 0x1ba ),	/* Type Offset=442 */
/* 196 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 198 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 200 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 202 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 204 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 206 */	NdrFcShort( 0x46c ),	/* Type Offset=1132 */
/* 208 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 210 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 212 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */
/* 214 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 216 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 218 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 220 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 222 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 224 */	NdrFcShort( 0x4ba ),	/* Type Offset=1210 */
/* 226 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x75,		/* x86, MIPS & PPC Stack size = 117 */
#else
			0x76,		/* Alpha Stack size = 118 */
#endif
/* 228 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */
/* 230 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 232 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 234 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 236 */	NdrFcShort( 0x4ce ),	/* Type Offset=1230 */
/* 238 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 240 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 242 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 244 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 246 */	NdrFcShort( 0x52a ),	/* Type Offset=1322 */
/* 248 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 250 */	NdrFcShort( 0x188 ),	/* Type Offset=392 */
/* 252 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x3,		/* FC_SMALL */
/* 254 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 256 */	NdrFcShort( 0x188 ),	/* Type Offset=392 */
/* 258 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 260 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0xc4,		/* x86, MIPS & PPC Stack size = 196 */
#else
			0xc4,		/* Alpha Stack size = 196 */
#endif
/* 262 */	NdrFcShort( 0x53e ),	/* Type Offset=1342 */
/* 264 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 266 */	NdrFcShort( 0x550 ),	/* Type Offset=1360 */
/* 268 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 270 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 272 */	NdrFcShort( 0x55c ),	/* Type Offset=1372 */
/* 274 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x3,		/* x86, MIPS & PPC Stack size = 3 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 276 */	NdrFcShort( 0x578 ),	/* Type Offset=1400 */
/* 278 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 280 */	NdrFcShort( 0x598 ),	/* Type Offset=1432 */
/* 282 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 284 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 286 */	NdrFcShort( 0x5c0 ),	/* Type Offset=1472 */
/* 288 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 290 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 292 */	NdrFcShort( 0x5f2 ),	/* Type Offset=1522 */
/* 294 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 296 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x47,		/* x86, MIPS & PPC Stack size = 71 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 298 */	NdrFcShort( 0x61a ),	/* Type Offset=1562 */
/* 300 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x3,		/* x86, MIPS & PPC Stack size = 3 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 302 */	NdrFcShort( 0x634 ),	/* Type Offset=1588 */
/* 304 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4f,		/* x86, MIPS & PPC Stack size = 79 */
#else
			0x50,		/* Alpha Stack size = 80 */
#endif
/* 306 */	NdrFcShort( 0x668 ),	/* Type Offset=1640 */
/* 308 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 310 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 312 */	NdrFcShort( 0x6b2 ),	/* Type Offset=1714 */
/* 314 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 316 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 318 */	NdrFcShort( 0x6ce ),	/* Type Offset=1742 */
/* 320 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 322 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 324 */	NdrFcShort( 0x6fe ),	/* Type Offset=1790 */
/* 326 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 328 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x47,		/* x86, MIPS & PPC Stack size = 71 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 330 */	NdrFcShort( 0x61a ),	/* Type Offset=1562 */
/* 332 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 334 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 336 */	NdrFcShort( 0x724 ),	/* Type Offset=1828 */
/* 338 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 340 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 342 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 344 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x1,		/* FC_BYTE */
/* 346 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 348 */	NdrFcShort( 0x73e ),	/* Type Offset=1854 */
/* 350 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 352 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 354 */	NdrFcShort( 0x770 ),	/* Type Offset=1904 */
/* 356 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 358 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x47,		/* x86, MIPS & PPC Stack size = 71 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 360 */	NdrFcShort( 0x798 ),	/* Type Offset=1944 */
/* 362 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 364 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 366 */	NdrFcShort( 0x7a4 ),	/* Type Offset=1956 */
/* 368 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 370 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 372 */	NdrFcShort( 0x7a4 ),	/* Type Offset=1956 */
/* 374 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 376 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 378 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 380 */	NdrFcShort( 0x7a4 ),	/* Type Offset=1956 */
/* 382 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x3,		/* FC_SMALL */
/* 384 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 386 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 388 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 390 */	NdrFcShort( 0x7da ),	/* Type Offset=2010 */
/* 392 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 394 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 396 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x8,		/* x86, MIPS & PPC Stack size = 8 */
#else
			0x8,		/* Alpha Stack size = 8 */
#endif
/* 398 */	NdrFcShort( 0x7ee ),	/* Type Offset=2030 */
/* 400 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 402 */	NdrFcShort( 0x808 ),	/* Type Offset=2056 */
/* 404 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 406 */	NdrFcShort( 0x836 ),	/* Type Offset=2102 */
/* 408 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 410 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 412 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 414 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 416 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4c,		/* x86, MIPS & PPC Stack size = 76 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 418 */	NdrFcShort( 0x73e ),	/* Type Offset=1854 */
/* 420 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 422 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 424 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 426 */	NdrFcShort( 0x84a ),	/* Type Offset=2122 */
/* 428 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 430 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 432 */	NdrFcShort( 0x86e ),	/* Type Offset=2158 */
/* 434 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 436 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 438 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 440 */	NdrFcShort( 0x894 ),	/* Type Offset=2196 */
/* 442 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 444 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 446 */	NdrFcShort( 0x8bc ),	/* Type Offset=2236 */
/* 448 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 450 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 452 */	NdrFcShort( 0x8c8 ),	/* Type Offset=2248 */
/* 454 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 456 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 458 */	NdrFcShort( 0x8e2 ),	/* Type Offset=2274 */
/* 460 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x3,		/* x86, MIPS & PPC Stack size = 3 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 462 */	NdrFcShort( 0x578 ),	/* Type Offset=1400 */
/* 464 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 466 */	NdrFcShort( 0x8e2 ),	/* Type Offset=2274 */
/* 468 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 470 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 472 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 474 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x43,		/* x86, MIPS & PPC Stack size = 67 */
#else
			0x44,		/* Alpha Stack size = 68 */
#endif
/* 476 */	NdrFcShort( 0x8fe ),	/* Type Offset=2302 */
/* 478 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 480 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 482 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x1,		/* FC_BYTE */
/* 484 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 486 */	NdrFcShort( 0x90a ),	/* Type Offset=2314 */
/* 488 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 490 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 492 */	NdrFcShort( 0x932 ),	/* Type Offset=2354 */
/* 494 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 496 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 498 */	NdrFcShort( 0x932 ),	/* Type Offset=2354 */
/* 500 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 502 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x47,		/* x86, MIPS & PPC Stack size = 71 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 504 */	NdrFcShort( 0x94e ),	/* Type Offset=2382 */
/* 506 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 508 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x47,		/* x86, MIPS & PPC Stack size = 71 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 510 */	NdrFcShort( 0x61a ),	/* Type Offset=1562 */
/* 512 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 514 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 516 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 518 */	NdrFcShort( 0x968 ),	/* Type Offset=2408 */
/* 520 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 522 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 524 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 526 */	NdrFcShort( 0x980 ),	/* Type Offset=2432 */
/* 528 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 530 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 532 */	NdrFcShort( 0x980 ),	/* Type Offset=2432 */
/* 534 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 536 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 538 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4a,		/* x86, MIPS & PPC Stack size = 74 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 540 */	NdrFcShort( 0x9a6 ),	/* Type Offset=2470 */
/* 542 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 544 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 546 */	NdrFcShort( 0x9e0 ),	/* Type Offset=2528 */
/* 548 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 550 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 552 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 554 */	NdrFcShort( 0x9e0 ),	/* Type Offset=2528 */
/* 556 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 558 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x49,		/* x86, MIPS & PPC Stack size = 73 */
#else
			0x4a,		/* Alpha Stack size = 74 */
#endif
/* 560 */	NdrFcShort( 0xa10 ),	/* Type Offset=2576 */
/* 562 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 564 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 566 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 568 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x3,		/* FC_SMALL */
/* 570 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 572 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 574 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x6b,		/* x86, MIPS & PPC Stack size = 107 */
#else
			0x6c,		/* Alpha Stack size = 108 */
#endif
/* 576 */	NdrFcShort( 0xa2c ),	/* Type Offset=2604 */
/* 578 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 580 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 582 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 584 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 586 */	NdrFcShort( 0xa66 ),	/* Type Offset=2662 */
/* 588 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 590 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 592 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4b,		/* x86, MIPS & PPC Stack size = 75 */
#else
			0x4c,		/* Alpha Stack size = 76 */
#endif
/* 594 */	NdrFcShort( 0xa66 ),	/* Type Offset=2662 */
/* 596 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 598 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 600 */	NdrFcShort( 0xa98 ),	/* Type Offset=2712 */
/* 602 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 604 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 606 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 608 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 610 */	NdrFcShort( 0xab0 ),	/* Type Offset=2736 */
/* 612 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 614 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 616 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x17,		/* x86, MIPS & PPC Stack size = 23 */
#else
			0x18,		/* Alpha Stack size = 24 */
#endif
/* 618 */	NdrFcShort( 0xac4 ),	/* Type Offset=2756 */
/* 620 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x48,		/* x86, MIPS & PPC Stack size = 72 */
#else
			0x48,		/* Alpha Stack size = 72 */
#endif
/* 622 */	NdrFcShort( 0xafe ),	/* Type Offset=2814 */
/* 624 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 626 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 628 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x45,		/* x86, MIPS & PPC Stack size = 69 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 630 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 632 */	
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x2,		/* x86, MIPS & PPC Stack size = 2 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 634 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 636 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x46,		/* x86, MIPS & PPC Stack size = 70 */
#else
			0x46,		/* Alpha Stack size = 70 */
#endif
/* 638 */	NdrFcShort( 0x968 ),	/* Type Offset=2408 */
/* 640 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 642 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x83,		/* x86, MIPS & PPC Stack size = 131 */
#else
			0x84,		/* Alpha Stack size = 132 */
#endif
/* 644 */	NdrFcShort( 0xb18 ),	/* Type Offset=2840 */
/* 646 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x3,		/* FC_SMALL */
/* 648 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/*  4 */	NdrFcShort( 0x104 ),	/* 260 */
/*  6 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/*  8 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 10 */	NdrFcShort( 0x110 ),	/* 272 */
/* 12 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 14 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (2) */
/* 16 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 18 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 20 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x114 ),	/* 276 */
/* 24 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 26 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffed ),	/* Offset= -19 (8) */
			0x5b,		/* FC_END */
/* 30 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 32 */	NdrFcShort( 0xb ),	/* 11 */
/* 34 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 36 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 38 */	NdrFcShort( 0x1 ),	/* 1 */
/* 40 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 46 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 48 */	NdrFcShort( 0x130 ),	/* 304 */
/* 50 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 52 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 54 */	NdrFcShort( 0x8 ),	/* 8 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x12, 0x0,	/* FC_UP */
/* 60 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (36) */
/* 62 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 64 */	NdrFcShort( 0x18 ),	/* 24 */
/* 66 */	NdrFcShort( 0x18 ),	/* 24 */
/* 68 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 70 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 72 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 74 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 76 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 78 */	NdrFcShort( 0xffffffd0 ),	/* Offset= -48 (30) */
/* 80 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 82 */	0x3,		/* FC_SMALL */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 84 */	0x3,		/* 3 */
			NdrFcShort( 0xffffffb3 ),	/* Offset= -77 (8) */
			0x5b,		/* FC_END */
/* 88 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 90 */	NdrFcShort( 0x21 ),	/* 33 */
/* 92 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 94 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 96 */	NdrFcShort( 0x105 ),	/* 261 */
/* 98 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 100 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 102 */	NdrFcShort( 0x33 ),	/* 51 */
/* 104 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 106 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 108 */	NdrFcShort( 0x1d4 ),	/* 468 */
/* 110 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 112 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (88) */
/* 114 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 116 */	NdrFcShort( 0xffffffaa ),	/* Offset= -86 (30) */
/* 118 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 120 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (94) */
/* 122 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 124 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (100) */
/* 126 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 128 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (100) */
/* 130 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 132 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (100) */
/* 134 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 136 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 138 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 140 */	NdrFcShort( 0x118 ),	/* 280 */
/* 142 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 144 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 146 */	NdrFcShort( 0x4 ),	/* 4 */
/* 148 */	NdrFcShort( 0x4 ),	/* 4 */
/* 150 */	0x12, 0x0,	/* FC_UP */
/* 152 */	NdrFcShort( 0xffffffd2 ),	/* Offset= -46 (106) */
/* 154 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 156 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 158 */	0x0,		/* 0 */
			NdrFcShort( 0xffffff69 ),	/* Offset= -151 (8) */
			0x5b,		/* FC_END */
/* 162 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 164 */	NdrFcShort( 0x1 ),	/* 1 */
/* 166 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 170 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 172 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 176 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 178 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 180 */	NdrFcShort( 0x4 ),	/* 4 */
/* 182 */	NdrFcShort( 0x4 ),	/* 4 */
/* 184 */	0x12, 0x0,	/* FC_UP */
/* 186 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (162) */
/* 188 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 190 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 192 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 194 */	NdrFcShort( 0x1 ),	/* 1 */
/* 196 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 198 */	NdrFcShort( 0x2c ),	/* 44 */
/* 200 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 202 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 204 */	NdrFcShort( 0x154 ),	/* 340 */
/* 206 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 208 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	0x12, 0x0,	/* FC_UP */
/* 216 */	NdrFcShort( 0xffffff4c ),	/* Offset= -180 (36) */
/* 218 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 220 */	NdrFcShort( 0x10 ),	/* 16 */
/* 222 */	NdrFcShort( 0x10 ),	/* 16 */
/* 224 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 226 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 228 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 230 */	NdrFcShort( 0x14 ),	/* 20 */
/* 232 */	NdrFcShort( 0x14 ),	/* 20 */
/* 234 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 236 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 238 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 240 */	NdrFcShort( 0x18 ),	/* 24 */
/* 242 */	NdrFcShort( 0x18 ),	/* 24 */
/* 244 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 246 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 248 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 250 */	NdrFcShort( 0x1c ),	/* 28 */
/* 252 */	NdrFcShort( 0x1c ),	/* 28 */
/* 254 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 256 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 258 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 260 */	NdrFcShort( 0x28 ),	/* 40 */
/* 262 */	NdrFcShort( 0x28 ),	/* 40 */
/* 264 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 266 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 268 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 270 */	NdrFcShort( 0x30 ),	/* 48 */
/* 272 */	NdrFcShort( 0x30 ),	/* 48 */
/* 274 */	0x12, 0x0,	/* FC_UP */
/* 276 */	NdrFcShort( 0xffffffac ),	/* Offset= -84 (192) */
/* 278 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 280 */	NdrFcShort( 0x40 ),	/* 64 */
/* 282 */	NdrFcShort( 0x40 ),	/* 64 */
/* 284 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 286 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 288 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 290 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 292 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 294 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 296 */	0x8,		/* FC_LONG */
			0x2,		/* FC_CHAR */
/* 298 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 300 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 302 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 304 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 306 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 308 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffed3 ),	/* Offset= -301 (8) */
			0x5b,		/* FC_END */
/* 312 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 314 */	NdrFcShort( 0x1 ),	/* 1 */
/* 316 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 318 */	NdrFcShort( 0x18 ),	/* 24 */
/* 320 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 322 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 324 */	NdrFcShort( 0x130 ),	/* 304 */
/* 326 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 328 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 330 */	NdrFcShort( 0x8 ),	/* 8 */
/* 332 */	NdrFcShort( 0x8 ),	/* 8 */
/* 334 */	0x12, 0x0,	/* FC_UP */
/* 336 */	NdrFcShort( 0xfffffed4 ),	/* Offset= -300 (36) */
/* 338 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 340 */	NdrFcShort( 0xc ),	/* 12 */
/* 342 */	NdrFcShort( 0xc ),	/* 12 */
/* 344 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 346 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 348 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 350 */	NdrFcShort( 0x10 ),	/* 16 */
/* 352 */	NdrFcShort( 0x10 ),	/* 16 */
/* 354 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 356 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 358 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 360 */	NdrFcShort( 0x14 ),	/* 20 */
/* 362 */	NdrFcShort( 0x14 ),	/* 20 */
/* 364 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 366 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 368 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 370 */	NdrFcShort( 0x1c ),	/* 28 */
/* 372 */	NdrFcShort( 0x1c ),	/* 28 */
/* 374 */	0x12, 0x0,	/* FC_UP */
/* 376 */	NdrFcShort( 0xffffffc0 ),	/* Offset= -64 (312) */
/* 378 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 380 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 382 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 384 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 386 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 388 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe83 ),	/* Offset= -381 (8) */
			0x5b,		/* FC_END */
/* 392 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 394 */	NdrFcShort( 0x128 ),	/* 296 */
/* 396 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 398 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 400 */	NdrFcShort( 0x8 ),	/* 8 */
/* 402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 404 */	0x12, 0x0,	/* FC_UP */
/* 406 */	NdrFcShort( 0xfffffe8e ),	/* Offset= -370 (36) */
/* 408 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 410 */	NdrFcShort( 0xc ),	/* 12 */
/* 412 */	NdrFcShort( 0xc ),	/* 12 */
/* 414 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 416 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 418 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 420 */	NdrFcShort( 0x10 ),	/* 16 */
/* 422 */	NdrFcShort( 0x10 ),	/* 16 */
/* 424 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 426 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 428 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 430 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 432 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 434 */	0x3,		/* FC_SMALL */
			0x3,		/* FC_SMALL */
/* 436 */	0x3,		/* FC_SMALL */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 438 */	0x1,		/* 1 */
			NdrFcShort( 0xfffffe51 ),	/* Offset= -431 (8) */
			0x5b,		/* FC_END */
/* 442 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 446 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 448 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 450 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 452 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 454 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 456 */	NdrFcShort( 0x12c ),	/* 300 */
/* 458 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 460 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 464 */	NdrFcShort( 0x8 ),	/* 8 */
/* 466 */	0x12, 0x0,	/* FC_UP */
/* 468 */	NdrFcShort( 0xfffffe50 ),	/* Offset= -432 (36) */
/* 470 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 472 */	NdrFcShort( 0xc ),	/* 12 */
/* 474 */	NdrFcShort( 0xc ),	/* 12 */
/* 476 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 478 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 480 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 482 */	NdrFcShort( 0x10 ),	/* 16 */
/* 484 */	NdrFcShort( 0x10 ),	/* 16 */
/* 486 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 488 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 490 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 492 */	NdrFcShort( 0x14 ),	/* 20 */
/* 494 */	NdrFcShort( 0x14 ),	/* 20 */
/* 496 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 498 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 500 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 502 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 504 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 506 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 508 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 510 */	NdrFcShort( 0xfffffe0a ),	/* Offset= -502 (8) */
/* 512 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 514 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 516 */	NdrFcShort( 0x144 ),	/* 324 */
/* 518 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 520 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 524 */	NdrFcShort( 0x8 ),	/* 8 */
/* 526 */	0x12, 0x0,	/* FC_UP */
/* 528 */	NdrFcShort( 0xfffffe14 ),	/* Offset= -492 (36) */
/* 530 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 532 */	NdrFcShort( 0xc ),	/* 12 */
/* 534 */	NdrFcShort( 0xc ),	/* 12 */
/* 536 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 538 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 540 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 542 */	NdrFcShort( 0x10 ),	/* 16 */
/* 544 */	NdrFcShort( 0x10 ),	/* 16 */
/* 546 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 548 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 550 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 552 */	NdrFcShort( 0x30 ),	/* 48 */
/* 554 */	NdrFcShort( 0x30 ),	/* 48 */
/* 556 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 558 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 560 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 562 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 564 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 566 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 568 */	NdrFcShort( 0xfffffde6 ),	/* Offset= -538 (30) */
/* 570 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 572 */	NdrFcShort( 0xfffffde2 ),	/* Offset= -542 (30) */
/* 574 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 576 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 578 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdc5 ),	/* Offset= -571 (8) */
			0x5b,		/* FC_END */
/* 582 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 584 */	NdrFcShort( 0x120 ),	/* 288 */
/* 586 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 588 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	0x12, 0x0,	/* FC_UP */
/* 596 */	NdrFcShort( 0xfffffdd0 ),	/* Offset= -560 (36) */
/* 598 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 600 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 602 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 604 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdab ),	/* Offset= -597 (8) */
			0x5b,		/* FC_END */
/* 608 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 610 */	NdrFcShort( 0x12c ),	/* 300 */
/* 612 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 614 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 618 */	NdrFcShort( 0x8 ),	/* 8 */
/* 620 */	0x12, 0x0,	/* FC_UP */
/* 622 */	NdrFcShort( 0xfffffdb6 ),	/* Offset= -586 (36) */
/* 624 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 626 */	NdrFcShort( 0xc ),	/* 12 */
/* 628 */	NdrFcShort( 0xc ),	/* 12 */
/* 630 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 632 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 634 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 636 */	NdrFcShort( 0x10 ),	/* 16 */
/* 638 */	NdrFcShort( 0x10 ),	/* 16 */
/* 640 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 642 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 644 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 646 */	NdrFcShort( 0x14 ),	/* 20 */
/* 648 */	NdrFcShort( 0x14 ),	/* 20 */
/* 650 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 652 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 654 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 656 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 658 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 660 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 662 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x2,		/* 2 */
/* 664 */	NdrFcShort( 0xfffffd70 ),	/* Offset= -656 (8) */
/* 666 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 668 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 670 */	NdrFcShort( 0x1 ),	/* 1 */
/* 672 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 674 */	NdrFcShort( 0x8 ),	/* 8 */
/* 676 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 678 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 680 */	NdrFcShort( 0x14 ),	/* 20 */
/* 682 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 684 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 686 */	NdrFcShort( 0xc ),	/* 12 */
/* 688 */	NdrFcShort( 0xc ),	/* 12 */
/* 690 */	0x12, 0x0,	/* FC_UP */
/* 692 */	NdrFcShort( 0xfffffd70 ),	/* Offset= -656 (36) */
/* 694 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 696 */	NdrFcShort( 0x10 ),	/* 16 */
/* 698 */	NdrFcShort( 0x10 ),	/* 16 */
/* 700 */	0x12, 0x0,	/* FC_UP */
/* 702 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (668) */
/* 704 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 706 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 708 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 710 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 712 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 714 */	NdrFcShort( 0x138 ),	/* 312 */
/* 716 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 718 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 724 */	0x12, 0x0,	/* FC_UP */
/* 726 */	NdrFcShort( 0xfffffd4e ),	/* Offset= -690 (36) */
/* 728 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 730 */	NdrFcShort( 0x14 ),	/* 20 */
/* 732 */	NdrFcShort( 0x14 ),	/* 20 */
/* 734 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 736 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 738 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 740 */	NdrFcShort( 0x18 ),	/* 24 */
/* 742 */	NdrFcShort( 0x18 ),	/* 24 */
/* 744 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 746 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 748 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 750 */	NdrFcShort( 0x1c ),	/* 28 */
/* 752 */	NdrFcShort( 0x1c ),	/* 28 */
/* 754 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 756 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 758 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 760 */	NdrFcShort( 0x20 ),	/* 32 */
/* 762 */	NdrFcShort( 0x20 ),	/* 32 */
/* 764 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 766 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 768 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 770 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 772 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 774 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 776 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 778 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 780 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffcfb ),	/* Offset= -773 (8) */
			0x5b,		/* FC_END */
/* 784 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 786 */	NdrFcShort( 0x130 ),	/* 304 */
/* 788 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 790 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 792 */	NdrFcShort( 0x8 ),	/* 8 */
/* 794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 796 */	0x12, 0x0,	/* FC_UP */
/* 798 */	NdrFcShort( 0xfffffd06 ),	/* Offset= -762 (36) */
/* 800 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 802 */	NdrFcShort( 0xc ),	/* 12 */
/* 804 */	NdrFcShort( 0xc ),	/* 12 */
/* 806 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 808 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 810 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 812 */	NdrFcShort( 0x10 ),	/* 16 */
/* 814 */	NdrFcShort( 0x10 ),	/* 16 */
/* 816 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 818 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 820 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 822 */	NdrFcShort( 0x14 ),	/* 20 */
/* 824 */	NdrFcShort( 0x14 ),	/* 20 */
/* 826 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 828 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 830 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 832 */	NdrFcShort( 0x18 ),	/* 24 */
/* 834 */	NdrFcShort( 0x18 ),	/* 24 */
/* 836 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 838 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 840 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 842 */	NdrFcShort( 0x1c ),	/* 28 */
/* 844 */	NdrFcShort( 0x1c ),	/* 28 */
/* 846 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 848 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 850 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 852 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 854 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 856 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 858 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 860 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffcab ),	/* Offset= -853 (8) */
			0x5b,		/* FC_END */
/* 864 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 866 */	NdrFcShort( 0x128 ),	/* 296 */
/* 868 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 870 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	0x12, 0x0,	/* FC_UP */
/* 878 */	NdrFcShort( 0xfffffcb6 ),	/* Offset= -842 (36) */
/* 880 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 882 */	NdrFcShort( 0xc ),	/* 12 */
/* 884 */	NdrFcShort( 0xc ),	/* 12 */
/* 886 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 888 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 890 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 892 */	NdrFcShort( 0x10 ),	/* 16 */
/* 894 */	NdrFcShort( 0x10 ),	/* 16 */
/* 896 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 898 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 900 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 902 */	NdrFcShort( 0x14 ),	/* 20 */
/* 904 */	NdrFcShort( 0x14 ),	/* 20 */
/* 906 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 908 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 912 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 914 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 916 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 918 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc71 ),	/* Offset= -911 (8) */
			0x5b,		/* FC_END */
/* 922 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 924 */	NdrFcShort( 0x18 ),	/* 24 */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0xc ),	/* Offset= 12 (940) */
/* 930 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 932 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 934 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc77 ),	/* Offset= -905 (30) */
			0x3d,		/* FC_STRUCTPAD1 */
/* 938 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 940 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 942 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 944 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 946 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 948 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 950 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 952 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 954 */	NdrFcShort( 0x12c ),	/* 300 */
/* 956 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 960 */	NdrFcShort( 0x8 ),	/* 8 */
/* 962 */	NdrFcShort( 0x8 ),	/* 8 */
/* 964 */	0x12, 0x0,	/* FC_UP */
/* 966 */	NdrFcShort( 0xfffffc5e ),	/* Offset= -930 (36) */
/* 968 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 970 */	NdrFcShort( 0xc ),	/* 12 */
/* 972 */	NdrFcShort( 0xc ),	/* 12 */
/* 974 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 976 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 978 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 980 */	NdrFcShort( 0x10 ),	/* 16 */
/* 982 */	NdrFcShort( 0x10 ),	/* 16 */
/* 984 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 986 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 988 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 990 */	NdrFcShort( 0x14 ),	/* 20 */
/* 992 */	NdrFcShort( 0x14 ),	/* 20 */
/* 994 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 996 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 998 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1000 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1002 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1004 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1006 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1008 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1010 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1012 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1014 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1016 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1018 */	NdrFcShort( 0xfffffc0e ),	/* Offset= -1010 (8) */
/* 1020 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1022 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1024 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1026 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1028 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1032 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1034 */	0x12, 0x0,	/* FC_UP */
/* 1036 */	NdrFcShort( 0xfffffc18 ),	/* Offset= -1000 (36) */
/* 1038 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1040 */	NdrFcShort( 0xc ),	/* 12 */
/* 1042 */	NdrFcShort( 0xc ),	/* 12 */
/* 1044 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1046 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1048 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1050 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1052 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1054 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1056 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1058 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1060 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1062 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1064 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1066 */	NdrFcShort( 0xfffffbde ),	/* Offset= -1058 (8) */
/* 1068 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1070 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1072 */	NdrFcShort( 0x120 ),	/* 288 */
/* 1074 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1076 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1078 */	NdrFcShort( 0xc ),	/* 12 */
/* 1080 */	NdrFcShort( 0xc ),	/* 12 */
/* 1082 */	0x12, 0x0,	/* FC_UP */
/* 1084 */	NdrFcShort( 0xfffffe60 ),	/* Offset= -416 (668) */
/* 1086 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1088 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1090 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1092 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffbc3 ),	/* Offset= -1085 (8) */
			0x5b,		/* FC_END */
/* 1096 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1098 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1100 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1102 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1104 */	NdrFcShort( 0xc ),	/* 12 */
/* 1106 */	NdrFcShort( 0xc ),	/* 12 */
/* 1108 */	0x12, 0x0,	/* FC_UP */
/* 1110 */	NdrFcShort( 0xfffffe46 ),	/* Offset= -442 (668) */
/* 1112 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1114 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1116 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1118 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffbb5 ),	/* Offset= -1099 (20) */
			0x5b,		/* FC_END */
/* 1122 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1124 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1126 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 1128 */	NdrFcShort( 0xc ),	/* 12 */
/* 1130 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1132 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1134 */	NdrFcShort( 0x128 ),	/* 296 */
/* 1136 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1138 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1144 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1146 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1148 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1150 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1152 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1154 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1156 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1158 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1160 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1162 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1164 */	0x12, 0x0,	/* FC_UP */
/* 1166 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (1122) */
/* 1168 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1170 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1172 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1174 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1176 */	NdrFcShort( 0xfffffb7c ),	/* Offset= -1156 (20) */
/* 1178 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1180 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1184 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1186 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1194 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1196 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1198 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1200 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1202 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1204 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1206 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1208 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1210 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1214 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1216 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1222 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1224 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1226 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1228 */	0xa,		/* FC_FLOAT */
			0x5b,		/* FC_END */
/* 1230 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1232 */	NdrFcShort( 0x12c ),	/* 300 */
/* 1234 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1236 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1242 */	0x12, 0x0,	/* FC_UP */
/* 1244 */	NdrFcShort( 0xfffffb48 ),	/* Offset= -1208 (36) */
/* 1246 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1248 */	NdrFcShort( 0xc ),	/* 12 */
/* 1250 */	NdrFcShort( 0xc ),	/* 12 */
/* 1252 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1254 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1256 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1258 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1260 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1262 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1264 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1266 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1268 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1270 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1272 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1274 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1276 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1278 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1280 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1282 */	0x8,		/* FC_LONG */
			0x3,		/* FC_SMALL */
/* 1284 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x3,		/* 3 */
/* 1286 */	NdrFcShort( 0xfffffb02 ),	/* Offset= -1278 (8) */
/* 1288 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1290 */	
			0x15,		/* FC_STRUCT */
			0x0,		/* 0 */
/* 1292 */	NdrFcShort( 0x22b ),	/* 555 */
/* 1294 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1296 */	NdrFcShort( 0xfffffb4e ),	/* Offset= -1202 (94) */
/* 1298 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1300 */	NdrFcShort( 0xfffffb44 ),	/* Offset= -1212 (88) */
/* 1302 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1304 */	NdrFcShort( 0xfffffb46 ),	/* Offset= -1210 (94) */
/* 1306 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1308 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1310 */	NdrFcShort( 0x22b ),	/* 555 */
/* 1312 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1318 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (1290) */
/* 1320 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1322 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1326 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1328 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1330 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1332 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1334 */	0x12, 0x0,	/* FC_UP */
/* 1336 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (1308) */
/* 1338 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1340 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1342 */	
			0x15,		/* FC_STRUCT */
			0x0,		/* 0 */
/* 1344 */	NdrFcShort( 0x30f ),	/* 783 */
/* 1346 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1348 */	NdrFcShort( 0xfffffb1a ),	/* Offset= -1254 (94) */
/* 1350 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1352 */	NdrFcShort( 0xfffffb16 ),	/* Offset= -1258 (94) */
/* 1354 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1356 */	NdrFcShort( 0xfffffb12 ),	/* Offset= -1262 (94) */
/* 1358 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1360 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1362 */	NdrFcShort( 0x118 ),	/* 280 */
/* 1364 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1366 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1368 */	NdrFcShort( 0xfffffab0 ),	/* Offset= -1360 (8) */
/* 1370 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1372 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1374 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1376 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1378 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1380 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1382 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1384 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1386 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1388 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1390 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1392 */	0x6,		/* FC_SHORT */
			0x38,		/* FC_ALIGNM4 */
/* 1394 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1396 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffa93 ),	/* Offset= -1389 (8) */
			0x5b,		/* FC_END */
/* 1400 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1402 */	NdrFcShort( 0xc ),	/* 12 */
/* 1404 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1406 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1408 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1410 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1412 */	0x12, 0x0,	/* FC_UP */
/* 1414 */	NdrFcShort( 0xfffffb1c ),	/* Offset= -1252 (162) */
/* 1416 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1418 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1420 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1422 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1424 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1426 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 1428 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1430 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1432 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1434 */	NdrFcShort( 0x12c ),	/* 300 */
/* 1436 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1438 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1440 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1442 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1444 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1446 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1448 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1450 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1452 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1454 */	0x12, 0x0,	/* FC_UP */
/* 1456 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (1422) */
/* 1458 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1460 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1462 */	0x6,		/* FC_SHORT */
			0x38,		/* FC_ALIGNM4 */
/* 1464 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1466 */	0x3,		/* FC_SMALL */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1468 */	0x3,		/* 3 */
			NdrFcShort( 0xfffffa4b ),	/* Offset= -1461 (8) */
			0x5b,		/* FC_END */
/* 1472 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1474 */	NdrFcShort( 0x12c ),	/* 300 */
/* 1476 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1478 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1480 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1482 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1484 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1486 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1488 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1490 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1492 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1494 */	0x12, 0x0,	/* FC_UP */
/* 1496 */	NdrFcShort( 0xffffffb6 ),	/* Offset= -74 (1422) */
/* 1498 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1500 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1502 */	0x6,		/* FC_SHORT */
			0x38,		/* FC_ALIGNM4 */
/* 1504 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1506 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1508 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffa23 ),	/* Offset= -1501 (8) */
			0x5b,		/* FC_END */
/* 1512 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1514 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1516 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 1518 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1520 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1522 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1524 */	NdrFcShort( 0x12c ),	/* 300 */
/* 1526 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1528 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1530 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1532 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1534 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1536 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1538 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1540 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1542 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1544 */	0x12, 0x0,	/* FC_UP */
/* 1546 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (1512) */
/* 1548 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1550 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1552 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 1554 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 1556 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1558 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff9f1 ),	/* Offset= -1551 (8) */
			0x5b,		/* FC_END */
/* 1562 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1564 */	NdrFcShort( 0x11c ),	/* 284 */
/* 1566 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1568 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1570 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1572 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1574 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1576 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1578 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1580 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1582 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1584 */	NdrFcShort( 0xfffff9d8 ),	/* Offset= -1576 (8) */
/* 1586 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1588 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1590 */	NdrFcShort( 0xc ),	/* 12 */
/* 1592 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1594 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1600 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1602 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1604 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1606 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1608 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1610 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 1612 */	NdrFcShort( 0x41 ),	/* 65 */
/* 1614 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1616 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1618 */	NdrFcShort( 0x80 ),	/* 128 */
/* 1620 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1622 */	NdrFcShort( 0xfffffa02 ),	/* Offset= -1534 (88) */
/* 1624 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1626 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (1610) */
/* 1628 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1630 */	NdrFcShort( 0xfffff9c0 ),	/* Offset= -1600 (30) */
/* 1632 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 1634 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1636 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1638 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1640 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1642 */	NdrFcShort( 0x13c ),	/* 316 */
/* 1644 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1646 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1648 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1650 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1652 */	0x12, 0x0,	/* FC_UP */
/* 1654 */	NdrFcShort( 0xfffff9ae ),	/* Offset= -1618 (36) */
/* 1656 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1658 */	NdrFcShort( 0xc ),	/* 12 */
/* 1660 */	NdrFcShort( 0xc ),	/* 12 */
/* 1662 */	0x12, 0x0,	/* FC_UP */
/* 1664 */	NdrFcShort( 0xffffffd0 ),	/* Offset= -48 (1616) */
/* 1666 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1668 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1670 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1672 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1674 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1676 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1678 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1680 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1682 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1684 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1686 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1688 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1690 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1692 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1694 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1696 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1698 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1700 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1702 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1704 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1706 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1708 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1710 */	NdrFcShort( 0xfffff95a ),	/* Offset= -1702 (8) */
/* 1712 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1714 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1716 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1718 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1720 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1722 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1726 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1728 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1730 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1732 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1734 */	0x8,		/* FC_LONG */
			0x3,		/* FC_SMALL */
/* 1736 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x3,		/* 3 */
/* 1738 */	NdrFcShort( 0xfffff93e ),	/* Offset= -1730 (8) */
/* 1740 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1742 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1744 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1746 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1748 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1750 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1754 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1756 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1758 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1760 */	NdrFcShort( 0xc ),	/* 12 */
/* 1762 */	NdrFcShort( 0xc ),	/* 12 */
/* 1764 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1766 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1768 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1770 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1772 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1774 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1776 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1778 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1780 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1782 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1784 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1786 */	NdrFcShort( 0xfffff90e ),	/* Offset= -1778 (8) */
/* 1788 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1790 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1792 */	NdrFcShort( 0x124 ),	/* 292 */
/* 1794 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1796 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1800 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1802 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1804 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1806 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1808 */	NdrFcShort( 0xc ),	/* 12 */
/* 1810 */	NdrFcShort( 0xc ),	/* 12 */
/* 1812 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1814 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1816 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1818 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1820 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1822 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1824 */	NdrFcShort( 0xfffff8e8 ),	/* Offset= -1816 (8) */
/* 1826 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1828 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1830 */	NdrFcShort( 0x120 ),	/* 288 */
/* 1832 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1834 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1838 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1840 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1842 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1844 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1846 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1848 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1850 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff8cd ),	/* Offset= -1843 (8) */
			0x5b,		/* FC_END */
/* 1854 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1856 */	NdrFcShort( 0x130 ),	/* 304 */
/* 1858 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1860 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1866 */	0x12, 0x0,	/* FC_UP */
/* 1868 */	NdrFcShort( 0xfffff8d8 ),	/* Offset= -1832 (36) */
/* 1870 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1872 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1874 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1876 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1878 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1880 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1882 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1884 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1886 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1888 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1890 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1892 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1894 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1896 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1898 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1900 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff89b ),	/* Offset= -1893 (8) */
			0x5b,		/* FC_END */
/* 1904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1906 */	NdrFcShort( 0x130 ),	/* 304 */
/* 1908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1916 */	0x12, 0x0,	/* FC_UP */
/* 1918 */	NdrFcShort( 0xfffff8a6 ),	/* Offset= -1882 (36) */
/* 1920 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1922 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1924 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1926 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1928 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1930 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1932 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1934 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1936 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1938 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1940 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff873 ),	/* Offset= -1933 (8) */
			0x5b,		/* FC_END */
/* 1944 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1946 */	NdrFcShort( 0x11c ),	/* 284 */
/* 1948 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1950 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1952 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff867 ),	/* Offset= -1945 (8) */
			0x5b,		/* FC_END */
/* 1956 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1958 */	NdrFcShort( 0x12c ),	/* 300 */
/* 1960 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1962 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1964 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1966 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1968 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1970 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1972 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1974 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1976 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1978 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1980 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 1982 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1984 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1986 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1988 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1990 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1992 */	NdrFcShort( 0xfffff840 ),	/* Offset= -1984 (8) */
/* 1994 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1996 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1998 */	NdrFcShort( 0x80 ),	/* 128 */
/* 2000 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2004 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2006 */	NdrFcShort( 0xfffffe7a ),	/* Offset= -390 (1616) */
/* 2008 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2010 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2014 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2016 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2018 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2020 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2022 */	0x12, 0x0,	/* FC_UP */
/* 2024 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (1996) */
/* 2026 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2028 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2030 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2032 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2034 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2036 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2042 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2044 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2046 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2048 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2050 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2052 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2054 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2056 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2058 */	NdrFcShort( 0x120 ),	/* 288 */
/* 2060 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2062 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2064 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2066 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2068 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2070 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2072 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2074 */	NdrFcShort( 0xc ),	/* 12 */
/* 2076 */	NdrFcShort( 0xc ),	/* 12 */
/* 2078 */	0x12, 0x0,	/* FC_UP */
/* 2080 */	NdrFcShort( 0xfffffa7c ),	/* Offset= -1412 (668) */
/* 2082 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2084 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2086 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2088 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff7df ),	/* Offset= -2081 (8) */
			0x5b,		/* FC_END */
/* 2092 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2094 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2096 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2100 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2102 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2106 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2108 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2110 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2112 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2114 */	0x12, 0x0,	/* FC_UP */
/* 2116 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (2092) */
/* 2118 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2120 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2122 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2124 */	NdrFcShort( 0x120 ),	/* 288 */
/* 2126 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2128 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2130 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2134 */	0x12, 0x0,	/* FC_UP */
/* 2136 */	NdrFcShort( 0xfffff7cc ),	/* Offset= -2100 (36) */
/* 2138 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2140 */	NdrFcShort( 0xc ),	/* 12 */
/* 2142 */	NdrFcShort( 0xc ),	/* 12 */
/* 2144 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2146 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2148 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2150 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2152 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2154 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff79d ),	/* Offset= -2147 (8) */
			0x5b,		/* FC_END */
/* 2158 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2160 */	NdrFcShort( 0x124 ),	/* 292 */
/* 2162 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2164 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2166 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2170 */	0x12, 0x0,	/* FC_UP */
/* 2172 */	NdrFcShort( 0xfffff7a8 ),	/* Offset= -2136 (36) */
/* 2174 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2176 */	NdrFcShort( 0xc ),	/* 12 */
/* 2178 */	NdrFcShort( 0xc ),	/* 12 */
/* 2180 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2182 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2184 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2186 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2188 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2190 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2192 */	NdrFcShort( 0xfffff778 ),	/* Offset= -2184 (8) */
/* 2194 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2196 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2198 */	NdrFcShort( 0x12c ),	/* 300 */
/* 2200 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2202 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2204 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2206 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2208 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2210 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2212 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2214 */	NdrFcShort( 0xc ),	/* 12 */
/* 2216 */	NdrFcShort( 0xc ),	/* 12 */
/* 2218 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2220 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2222 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2224 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2226 */	0x8,		/* FC_LONG */
			0x2,		/* FC_CHAR */
/* 2228 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 2230 */	0x3,		/* FC_SMALL */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2232 */	0x3,		/* 3 */
			NdrFcShort( 0xfffff74f ),	/* Offset= -2225 (8) */
			0x5b,		/* FC_END */
/* 2236 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 2238 */	NdrFcShort( 0x118 ),	/* 280 */
/* 2240 */	0x8,		/* FC_LONG */
			0x3,		/* FC_SMALL */
/* 2242 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x3,		/* 3 */
/* 2244 */	NdrFcShort( 0xfffff744 ),	/* Offset= -2236 (8) */
/* 2246 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2248 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2250 */	NdrFcShort( 0x120 ),	/* 288 */
/* 2252 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2254 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2256 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2258 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2260 */	0x12, 0x0,	/* FC_UP */
/* 2262 */	NdrFcShort( 0xfffff74e ),	/* Offset= -2226 (36) */
/* 2264 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2266 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2268 */	0x3,		/* FC_SMALL */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2270 */	0x3,		/* 3 */
			NdrFcShort( 0xfffff729 ),	/* Offset= -2263 (8) */
			0x5b,		/* FC_END */
/* 2274 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2276 */	NdrFcShort( 0x124 ),	/* 292 */
/* 2278 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2280 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2282 */	NdrFcShort( 0xc ),	/* 12 */
/* 2284 */	NdrFcShort( 0xc ),	/* 12 */
/* 2286 */	0x12, 0x0,	/* FC_UP */
/* 2288 */	NdrFcShort( 0xfffff9ac ),	/* Offset= -1620 (668) */
/* 2290 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2292 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2294 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2296 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2298 */	NdrFcShort( 0xfffff70e ),	/* Offset= -2290 (8) */
/* 2300 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2302 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 2304 */	NdrFcShort( 0x10c ),	/* 268 */
/* 2306 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2308 */	NdrFcShort( 0xfffff75a ),	/* Offset= -2214 (94) */
/* 2310 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 2312 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2314 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2316 */	NdrFcShort( 0x12c ),	/* 300 */
/* 2318 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2320 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2326 */	0x12, 0x0,	/* FC_UP */
/* 2328 */	NdrFcShort( 0xfffff70c ),	/* Offset= -2292 (36) */
/* 2330 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2332 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2334 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2336 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2338 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2340 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2342 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2344 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2346 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2348 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2350 */	NdrFcShort( 0xfffff6da ),	/* Offset= -2342 (8) */
/* 2352 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2354 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2356 */	NdrFcShort( 0x120 ),	/* 288 */
/* 2358 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2360 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2362 */	NdrFcShort( 0xc ),	/* 12 */
/* 2364 */	NdrFcShort( 0xc ),	/* 12 */
/* 2366 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2368 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2370 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2372 */	0x6,		/* FC_SHORT */
			0x38,		/* FC_ALIGNM4 */
/* 2374 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2376 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2378 */	NdrFcShort( 0xfffff6be ),	/* Offset= -2370 (8) */
/* 2380 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2382 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2384 */	NdrFcShort( 0x11c ),	/* 284 */
/* 2386 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2388 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2390 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2394 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2396 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2398 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2400 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2402 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2404 */	NdrFcShort( 0xfffff6a4 ),	/* Offset= -2396 (8) */
/* 2406 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2408 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2410 */	NdrFcShort( 0x118 ),	/* 280 */
/* 2412 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2414 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2416 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2418 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2420 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2422 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2424 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2426 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2428 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff68b ),	/* Offset= -2421 (8) */
			0x5b,		/* FC_END */
/* 2432 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2434 */	NdrFcShort( 0x124 ),	/* 292 */
/* 2436 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2438 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2440 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2442 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2444 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2446 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2448 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2452 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2454 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2456 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2458 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2460 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2462 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2464 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2466 */	NdrFcShort( 0xfffff666 ),	/* Offset= -2458 (8) */
/* 2468 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2470 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2472 */	NdrFcShort( 0x128 ),	/* 296 */
/* 2474 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2476 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2478 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2480 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2482 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2484 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2486 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2490 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2492 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2494 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2496 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2498 */	NdrFcShort( 0xc ),	/* 12 */
/* 2500 */	NdrFcShort( 0xc ),	/* 12 */
/* 2502 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2504 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2506 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2508 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2510 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2512 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2514 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2516 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2518 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2520 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2522 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2524 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff62b ),	/* Offset= -2517 (8) */
			0x5b,		/* FC_END */
/* 2528 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2530 */	NdrFcShort( 0x124 ),	/* 292 */
/* 2532 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2534 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2536 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2538 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2540 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2542 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2544 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2550 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2552 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2554 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2556 */	NdrFcShort( 0xc ),	/* 12 */
/* 2558 */	NdrFcShort( 0xc ),	/* 12 */
/* 2560 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2562 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2564 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2566 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2568 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2570 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2572 */	NdrFcShort( 0xfffff5fc ),	/* Offset= -2564 (8) */
/* 2574 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2576 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2578 */	NdrFcShort( 0x124 ),	/* 292 */
/* 2580 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2582 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2586 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2588 */	0x12, 0x0,	/* FC_UP */
/* 2590 */	NdrFcShort( 0xfffff606 ),	/* Offset= -2554 (36) */
/* 2592 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2594 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2596 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2598 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2600 */	NdrFcShort( 0xfffff5e0 ),	/* Offset= -2592 (8) */
/* 2602 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2604 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2606 */	NdrFcShort( 0x1ac ),	/* 428 */
/* 2608 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2610 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2612 */	NdrFcShort( 0x148 ),	/* 328 */
/* 2614 */	NdrFcShort( 0x148 ),	/* 328 */
/* 2616 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2618 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2620 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2622 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff61f ),	/* Offset= -2529 (94) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2626 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff615 ),	/* Offset= -2539 (88) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2630 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff611 ),	/* Offset= -2543 (88) */
			0x38,		/* FC_ALIGNM4 */
/* 2634 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2636 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff617 ),	/* Offset= -2537 (100) */
			0x38,		/* FC_ALIGNM4 */
/* 2640 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2642 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2644 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2646 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2648 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2650 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2652 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 2654 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2656 */	0x18,		/* Corr desc:  field pointer, FC_LONG */
			0x0,		/*  */
/* 2658 */	NdrFcShort( 0xc ),	/* 12 */
/* 2660 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2662 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2664 */	NdrFcShort( 0x12c ),	/* 300 */
/* 2666 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2668 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2674 */	0x12, 0x0,	/* FC_UP */
/* 2676 */	NdrFcShort( 0xfffff5b0 ),	/* Offset= -2640 (36) */
/* 2678 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2680 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2682 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2684 */	0x12, 0x0,	/* FC_UP */
/* 2686 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (2652) */
/* 2688 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2690 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2692 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2694 */	0x12, 0x0,	/* FC_UP */
/* 2696 */	NdrFcShort( 0xfffffb60 ),	/* Offset= -1184 (1512) */
/* 2698 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2700 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2702 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2704 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2706 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2708 */	NdrFcShort( 0xfffff574 ),	/* Offset= -2700 (8) */
/* 2710 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2712 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2714 */	NdrFcShort( 0x118 ),	/* 280 */
/* 2716 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2718 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2724 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2726 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2728 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2730 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2732 */	NdrFcShort( 0xfffff568 ),	/* Offset= -2712 (20) */
/* 2734 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2736 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2740 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2742 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2748 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2750 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2752 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2754 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 2756 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 2758 */	NdrFcShort( 0x5c ),	/* 92 */
/* 2760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2762 */	NdrFcShort( 0x30 ),	/* Offset= 48 (2810) */
/* 2764 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2766 */	NdrFcShort( 0xfffff5de ),	/* Offset= -2594 (172) */
/* 2768 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2770 */	NdrFcShort( 0xfffff5da ),	/* Offset= -2598 (172) */
/* 2772 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2774 */	NdrFcShort( 0xfffff5d6 ),	/* Offset= -2602 (172) */
/* 2776 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2778 */	NdrFcShort( 0xfffff5d2 ),	/* Offset= -2606 (172) */
/* 2780 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2782 */	NdrFcShort( 0xfffff5ce ),	/* Offset= -2610 (172) */
/* 2784 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2786 */	NdrFcShort( 0xfffff5ca ),	/* Offset= -2614 (172) */
/* 2788 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2790 */	NdrFcShort( 0xfffff5c6 ),	/* Offset= -2618 (172) */
/* 2792 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2794 */	NdrFcShort( 0xfffff5c2 ),	/* Offset= -2622 (172) */
/* 2796 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2798 */	NdrFcShort( 0xfffff5be ),	/* Offset= -2626 (172) */
/* 2800 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2802 */	NdrFcShort( 0xfffff5ba ),	/* Offset= -2630 (172) */
/* 2804 */	0x36,		/* FC_POINTER */
			0x8,		/* FC_LONG */
/* 2806 */	0x3,		/* FC_SMALL */
			0x3f,		/* FC_STRUCTPAD3 */
/* 2808 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2810 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 2812 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 2814 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 2816 */	NdrFcShort( 0x120 ),	/* 288 */
/* 2818 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 2820 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 2822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2826 */	0x12, 0x0,	/* FC_UP */
/* 2828 */	NdrFcShort( 0xfffff596 ),	/* Offset= -2666 (162) */
/* 2830 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 2832 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 2834 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 2836 */	0x0,		/* 0 */
			NdrFcShort( 0xfffff4f3 ),	/* Offset= -2829 (8) */
			0x5b,		/* FC_END */
/* 2840 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 2842 */	NdrFcShort( 0x20c ),	/* 524 */
/* 2844 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2846 */	NdrFcShort( 0xfffff4e4 ),	/* Offset= -2844 (2) */
/* 2848 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2850 */	NdrFcShort( 0xfffff4e0 ),	/* Offset= -2848 (2) */
/* 2852 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };
