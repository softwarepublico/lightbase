# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=clstub - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to clstub - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "clstub - Win32 Release" && "$(CFG)" != "clstub - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "clstub.mak" CFG="clstub - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clstub - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clstub - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "clstub - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "clstub - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release\dce"
# PROP Intermediate_Dir "\obj\clstub\release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\release\dce
INTDIR=\obj\clstub\release

ALL : "$(OUTDIR)\lbs.dll"

CLEAN : 
	-@erase "..\..\..\release\dce\lbs.dll"
	-@erase "..\..\..\..\obj\clstub\release\cldata.obj"
	-@erase "..\..\..\..\obj\clstub\release\getsrvrs.obj"
	-@erase "..\..\..\..\obj\clstub\release\clbase5.obj"
	-@erase "..\..\..\..\obj\clstub\release\lbsnetcl.obj"
	-@erase "..\..\..\..\obj\clstub\release\clfield.obj"
	-@erase "..\..\..\..\obj\clstub\release\basecache.obj"
	-@erase "..\..\..\..\obj\clstub\release\clntfuncs.obj"
	-@erase "..\..\..\..\obj\clstub\release\clbase4.obj"
	-@erase "..\..\..\..\obj\clstub\release\opinfocl.obj"
	-@erase "..\..\..\..\obj\clstub\release\clbase3.obj"
	-@erase "..\..\..\..\obj\clstub\release\lbsrpc_c.obj"
	-@erase "..\..\..\..\obj\clstub\release\clsess2.obj"
	-@erase "..\..\..\..\obj\clstub\release\CLIENT.OBJ"
	-@erase "..\..\..\..\obj\clstub\release\clbase2.obj"
	-@erase "..\..\..\..\obj\clstub\release\cloccurr.obj"
	-@erase "..\..\..\..\obj\clstub\release\CLLBSERR.OBJ"
	-@erase "..\..\..\..\obj\clstub\release\clsess1.obj"
	-@erase "..\..\..\..\obj\clstub\release\clbase1.obj"
	-@erase "..\..\..\..\obj\clstub\release\clstub.res"
	-@erase "..\..\..\lib\release\dce\lbs.lib"
	-@erase "..\..\..\lib\release\dce\lbs.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I ".\include" /I " k:\develop\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__NOMFC" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /O2 /I ".\include" /I " k:\develop\include" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__NOMFC"\
 /Fp"$(INTDIR)/clstub.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=\obj\clstub\release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
RSC_PROJ=/l 0x416 /fo"$(INTDIR)/clstub.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/clstub.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib k:\develop\lib\release\alfc.lib k:\develop\lib\release\appmngr.lib k:\develop\lib\release\li.lib k:\develop\lib\release\lifile.lib k:\develop\lib\release\crypt.lib k:\develop\lib\release\rpcstuff.lib k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release\dce/lbs.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib\
 k:\develop\lib\release\alfc.lib k:\develop\lib\release\appmngr.lib\
 k:\develop\lib\release\li.lib k:\develop\lib\release\lifile.lib\
 k:\develop\lib\release\crypt.lib k:\develop\lib\release\rpcstuff.lib\
 k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/lbs.pdb" /machine:I386\
 /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release\dce/lbs.dll"\
 /implib:"$(OUTDIR)/lbs.lib" 
LINK32_OBJS= \
	"$(INTDIR)/cldata.obj" \
	"$(INTDIR)/getsrvrs.obj" \
	"$(INTDIR)/clbase5.obj" \
	"$(INTDIR)/lbsnetcl.obj" \
	"$(INTDIR)/clfield.obj" \
	"$(INTDIR)/basecache.obj" \
	"$(INTDIR)/clntfuncs.obj" \
	"$(INTDIR)/clbase4.obj" \
	"$(INTDIR)/opinfocl.obj" \
	"$(INTDIR)/clbase3.obj" \
	"$(INTDIR)/lbsrpc_c.obj" \
	"$(INTDIR)/clsess2.obj" \
	"$(INTDIR)/CLIENT.OBJ" \
	"$(INTDIR)/clbase2.obj" \
	"$(INTDIR)/cloccurr.obj" \
	"$(INTDIR)/CLLBSERR.OBJ" \
	"$(INTDIR)/clsess1.obj" \
	"$(INTDIR)/clbase1.obj" \
	"$(INTDIR)/clstub.res"

"$(OUTDIR)\lbs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\Debug\dce"
# PROP Intermediate_Dir "\obj\clstub\Debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\Debug\dce
INTDIR=\obj\clstub\Debug

ALL : "$(OUTDIR)\lbs.dll"

CLEAN : 
	-@erase "..\..\..\..\obj\clstub\Debug\vc40.pdb"
	-@erase "..\..\..\..\obj\clstub\Debug\vc40.idb"
	-@erase "..\..\..\Debug\dce\lbs.dll"
	-@erase "..\..\..\..\obj\clstub\Debug\basecache.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clntfuncs.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clbase5.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\CLLBSERR.OBJ"
	-@erase "..\..\..\..\obj\clstub\Debug\clfield.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\opinfocl.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clbase4.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\lbsrpc_c.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\getsrvrs.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clbase3.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\cloccurr.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\CLIENT.OBJ"
	-@erase "..\..\..\..\obj\clstub\Debug\clsess2.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clbase2.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\cldata.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\lbsnetcl.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clsess1.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clbase1.obj"
	-@erase "..\..\..\..\obj\clstub\Debug\clstub.res"
	-@erase "..\..\..\Debug\dce\lbs.ilk"
	-@erase "..\..\..\lib\Debug\dce\lbs.lib"
	-@erase "..\..\..\lib\Debug\dce\lbs.exp"
	-@erase "..\..\..\lib\Debug\dce\lbs.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /Zi /Od /I ".\include" /I " k:\develop\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__NOMFC" /D " _TESTE" /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /Gm /Zi /Od /I ".\include" /I\
 " k:\develop\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "BUILDING_LBS_DLL" /D "__NOMFC" /D " _TESTE" /Fp"$(INTDIR)/clstub.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=\obj\clstub\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
RSC_PROJ=/l 0x416 /fo"$(INTDIR)/clstub.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/clstub.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib k:\develop\lib\release\alfc.lib k:\develop\lib\release\appmngr.lib k:\develop\lib\release\li.lib k:\develop\lib\release\lifile.lib k:\develop\lib\release\crypt.lib ..\..\..\lib\debug\rpcstuff.lib k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libcimt.lib" /out:"..\..\..\Debug\dce/lbs.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib\
 k:\develop\lib\release\alfc.lib k:\develop\lib\release\appmngr.lib\
 k:\develop\lib\release\li.lib k:\develop\lib\release\lifile.lib\
 k:\develop\lib\release\crypt.lib ..\..\..\lib\debug\rpcstuff.lib\
 k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/lbs.pdb" /debug /machine:I386\
 /nodefaultlib:"libcimt.lib" /out:"..\..\..\Debug\dce/lbs.dll"\
 /implib:"$(OUTDIR)/lbs.lib" 
LINK32_OBJS= \
	"$(INTDIR)/basecache.obj" \
	"$(INTDIR)/clntfuncs.obj" \
	"$(INTDIR)/clbase5.obj" \
	"$(INTDIR)/CLLBSERR.OBJ" \
	"$(INTDIR)/clfield.obj" \
	"$(INTDIR)/opinfocl.obj" \
	"$(INTDIR)/clbase4.obj" \
	"$(INTDIR)/lbsrpc_c.obj" \
	"$(INTDIR)/getsrvrs.obj" \
	"$(INTDIR)/clbase3.obj" \
	"$(INTDIR)/cloccurr.obj" \
	"$(INTDIR)/CLIENT.OBJ" \
	"$(INTDIR)/clsess2.obj" \
	"$(INTDIR)/clbase2.obj" \
	"$(INTDIR)/cldata.obj" \
	"$(INTDIR)/lbsnetcl.obj" \
	"$(INTDIR)/clsess1.obj" \
	"$(INTDIR)/clbase1.obj" \
	"$(INTDIR)/clstub.res"

"$(OUTDIR)\lbs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "clstub - Win32 Release"
# Name "clstub - Win32 Debug"

!IF  "$(CFG)" == "clstub - Win32 Release"

!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Source\opinfocl.cpp
DEP_CPP_OPINF=\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	

"$(INTDIR)\opinfocl.obj" : $(SOURCE) $(DEP_CPP_OPINF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\lbsrpc_c.c
DEP_CPP_LBSRP=\
	"k:\develop\include\lbsrpc.h"\
	

"$(INTDIR)\lbsrpc_c.obj" : $(SOURCE) $(DEP_CPP_LBSRP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\lbsnetcl.cpp
DEP_CPP_LBSNE=\
	"k:\develop\include\cstrtok.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbserrtb.h"\
	"k:\develop\include\appmngr.h"\
	"k:\develop\include\admdefs.h"\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\stubcrit.h"\
	"k:\develop\include\getname.h"\
	"k:\develop\include\is32s.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	

"$(INTDIR)\lbsnetcl.obj" : $(SOURCE) $(DEP_CPP_LBSNE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\getsrvrs.cpp
DEP_CPP_GETSR=\
	"k:\develop\include\cstrtok.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\admdefs.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	

"$(INTDIR)\getsrvrs.obj" : $(SOURCE) $(DEP_CPP_GETSR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clsess2.cpp

!IF  "$(CFG)" == "clstub - Win32 Release"

DEP_CPP_CLSES=\
	".\include\SESSCL.H"\
	"k:\develop\include\cstrtok.h"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\allbasel.h"\
	".\include\getsrvrs.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\admdefs.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\passwdcl.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lockstru.h"\
	

"$(INTDIR)\clsess2.obj" : $(SOURCE) $(DEP_CPP_CLSES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

DEP_CPP_CLSES=\
	".\include\SESSCL.H"\
	"k:\develop\include\cstrtok.h"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\allbasel.h"\
	".\include\getsrvrs.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\admdefs.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clsess2.obj" : $(SOURCE) $(DEP_CPP_CLSES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clsess1.cpp

!IF  "$(CFG)" == "clstub - Win32 Release"

DEP_CPP_CLSESS=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\stubcrit.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\passwdcl.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lockstru.h"\
	

"$(INTDIR)\clsess1.obj" : $(SOURCE) $(DEP_CPP_CLSESS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

DEP_CPP_CLSESS=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\stubcrit.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clsess1.obj" : $(SOURCE) $(DEP_CPP_CLSESS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\cloccurr.cpp
DEP_CPP_CLOCC=\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	

"$(INTDIR)\cloccurr.obj" : $(SOURCE) $(DEP_CPP_CLOCC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\CLLBSERR.CPP

!IF  "$(CFG)" == "clstub - Win32 Release"

DEP_CPP_CLLBS=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\fbuff.h"\
	".\include\cllbserr.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\passwdcl.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lockstru.h"\
	

"$(INTDIR)\CLLBSERR.OBJ" : $(SOURCE) $(DEP_CPP_CLLBS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

DEP_CPP_CLLBS=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\fbuff.h"\
	".\include\cllbserr.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\CLLBSERR.OBJ" : $(SOURCE) $(DEP_CPP_CLLBS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\CLIENT.CPP
DEP_CPP_CLIEN=\
	".\include\lbsnetcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\appmngr.h"\
	"k:\develop\include\personcl.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	

"$(INTDIR)\CLIENT.OBJ" : $(SOURCE) $(DEP_CPP_CLIEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clfield.cpp
DEP_CPP_CLFIE=\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	".\include\basecl.h"\
	".\include\fieldcl.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clfield.obj" : $(SOURCE) $(DEP_CPP_CLFIE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\cldata.cpp
DEP_CPP_CLDAT=\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\encript.h"\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	

"$(INTDIR)\cldata.obj" : $(SOURCE) $(DEP_CPP_CLDAT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clbase5.cpp
DEP_CPP_CLBAS=\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\defclass.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\lbstypes.h"\
	".\include\datacl.h"\
	"k:\develop\include\stringn.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clbase5.obj" : $(SOURCE) $(DEP_CPP_CLBAS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clbase4.cpp
DEP_CPP_CLBASE=\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\defclass.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\lbstypes.h"\
	".\include\datacl.h"\
	"k:\develop\include\stringn.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clbase4.obj" : $(SOURCE) $(DEP_CPP_CLBASE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clbase3.cpp
DEP_CPP_CLBASE3=\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\defclass.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\lbstypes.h"\
	".\include\datacl.h"\
	"k:\develop\include\stringn.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clbase3.obj" : $(SOURCE) $(DEP_CPP_CLBASE3) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clbase2.cpp
DEP_CPP_CLBASE2=\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\duplicate.h"\
	".\include\clntfuncs.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\defclass.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\lbstypes.h"\
	".\include\datacl.h"\
	"k:\develop\include\stringn.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clbase2.obj" : $(SOURCE) $(DEP_CPP_CLBASE2) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clbase1.cpp
DEP_CPP_CLBASE1=\
	".\include\basecl.h"\
	".\include\MMDEFS.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defmac.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\encript.h"\
	".\include\clntfuncs.h"\
	".\include\duplicate.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\defclass.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	".\include\basecach.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	"k:\develop\include\lbstypes.h"\
	".\include\datacl.h"\
	"k:\develop\include\stringn.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\lbsmsg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\clbase1.obj" : $(SOURCE) $(DEP_CPP_CLBASE1) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\clntfuncs.cpp
DEP_CPP_CLNTF=\
	"k:\develop\include\SESSCL.H"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\clilist.h"\
	"k:\develop\include\licctrl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\lb3list.h"\
	"k:\develop\include\oclistcl.h"\
	"k:\develop\include\indsyscl.h"\
	"k:\develop\include\ticketcl.h"\
	"k:\develop\include\lbserrcl.h"\
	"k:\develop\include\parsercl.h"\
	"k:\develop\include\entparcl.h"\
	"k:\develop\include\lbsollst.h"\
	"k:\develop\include\record.h"\
	"k:\develop\include\opinfocl.h"\
	"k:\develop\include\idxoffcl.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\slotlist.h"\
	"k:\develop\include\slotnode.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\ctcache.h"\
	"k:\develop\include\ctdata.h"\
	"k:\develop\include\genhash.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\te_token.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\buffercl.h"\
	

"$(INTDIR)\clntfuncs.obj" : $(SOURCE) $(DEP_CPP_CLNTF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE\clstub.rc

!IF  "$(CFG)" == "clstub - Win32 Release"


"$(INTDIR)\clstub.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x416 /fo"$(INTDIR)/clstub.res" /i "RESOURCE" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"


"$(INTDIR)\clstub.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x416 /fo"$(INTDIR)/clstub.res" /i "RESOURCE" /d "_DEBUG"\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\basecache.cpp

!IF  "$(CFG)" == "clstub - Win32 Release"

DEP_CPP_BASEC=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\basecach.h"\
	"k:\develop\include\admdefs.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\baselist.h"\
	"k:\develop\include\usrcl.h"\
	"k:\develop\include\timecl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\fbuff.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\passwdcl.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\usrinfol.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\lockstru.h"\
	

"$(INTDIR)\basecache.obj" : $(SOURCE) $(DEP_CPP_BASEC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

DEP_CPP_BASEC=\
	".\include\SESSCL.H"\
	".\include\basecl.h"\
	".\include\basecach.h"\
	"k:\develop\include\admdefs.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\ticketcl.h"\
	".\include\cllbserr.h"\
	".\include\opinfocl.h"\
	".\include\lbsnetcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\timecl.h"\
	"k:\develop\include\lbsrpc.h"\
	"k:\develop\include\rpcserial.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\permcl.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	".\include\fieldcl.h"\
	".\include\occurcl.h"\
	".\include\fielstcl.h"\
	"k:\develop\include\fbuff.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\include\datacl.h"\
	".\include\datlstcl.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\basecache.obj" : $(SOURCE) $(DEP_CPP_BASEC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
