/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 28 19:17:41 2003
 */
/* Compiler settings for chkvers.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "chkvers.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   5                                 

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

/* Standard interface: chkvers, ver. 1.1,
   GUID={0x98f1c230,0x9eb3,0x11d3,{0x91,0xad,0x00,0x60,0x97,0xd3,0x28,0xe5}} */


extern RPC_DISPATCH_TABLE chkvers_v1_1_DispatchTable;

static const RPC_SERVER_INTERFACE chkvers___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x98f1c230,0x9eb3,0x11d3,{0x91,0xad,0x00,0x60,0x97,0xd3,0x28,0xe5}},{1,1}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &chkvers_v1_1_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE chkvers_v1_1_s_ifspec = (RPC_IF_HANDLE)& chkvers___RpcServerInterface;

extern const MIDL_STUB_DESC chkvers_StubDesc;

void __RPC_STUB
chkvers_RPC_MustReinstall(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned char __RPC_FAR *_RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &chkvers_StubDesc);
    
    RpcTryFinally
        {
        
        _RetVal = RPC_MustReinstall();
        
        _StubMsg.BufferLength = 16U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)_RetVal,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
chkvers_RPC_GetMinClientVersion(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned char __RPC_FAR *_RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &chkvers_StubDesc);
    
    RpcTryFinally
        {
        
        _RetVal = RPC_GetMinClientVersion();
        
        _StubMsg.BufferLength = 16U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)_RetVal,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)_RetVal,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC chkvers_StubDesc = 
    {
    (void __RPC_FAR *)& chkvers___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static RPC_DISPATCH_FUNCTION chkvers_table[] =
    {
    chkvers_RPC_MustReinstall,
    chkvers_RPC_GetMinClientVersion,
    0
    };
RPC_DISPATCH_TABLE chkvers_v1_1_DispatchTable = 
    {
    2,
    chkvers_table
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x52,		/* FC_RETURN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/*  4 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */

			0x0
        }
    };
