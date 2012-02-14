/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 28 19:15:20 2003
 */
/* Compiler settings for chkvers.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __chkvers_h__
#define __chkvers_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __chkvers_INTERFACE_DEFINED__
#define __chkvers_INTERFACE_DEFINED__

/* interface chkvers */
/* [enable_allocate][implicit_handle][unique][version][uuid] */ 

/* [string] */ unsigned char __RPC_FAR *RPC_MustReinstall( void);

/* [string] */ unsigned char __RPC_FAR *RPC_GetMinClientVersion( void);


extern handle_t _chkvers_IfHandle;


extern RPC_IF_HANDLE chkvers_v1_1_c_ifspec;
extern RPC_IF_HANDLE chkvers_v1_1_s_ifspec;
#endif /* __chkvers_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
