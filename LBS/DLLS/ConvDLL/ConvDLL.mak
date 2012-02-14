# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ConvDLL - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ConvDLL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ConvDLL - Win32 Release" && "$(CFG)" !=\
 "ConvDLL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ConvDLL.mak" CFG="ConvDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ConvDLL - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConvDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "ConvDLL - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "d:\obj\ConvDll\Release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\release
INTDIR=d:\obj\ConvDll\Release

ALL : "$(OUTDIR)\ConvBase.dll" "..\..\..\..\obj\ConvDll\Release\ConvDLL.pch"

CLEAN : 
	-@erase "..\..\..\..\obj\ConvDll\Release\ConvDLL.pch"
	-@erase "..\..\..\release\ConvBase.dll"
	-@erase "..\..\..\..\obj\ConvDll\Release\LIProg.obj"
	-@erase "..\..\..\..\obj\ConvDll\Release\FBDlgCl.obj"
	-@erase "..\..\..\..\obj\ConvDll\Release\ConvDLL.obj"
	-@erase "..\..\..\..\obj\ConvDll\Release\Convcl.obj"
	-@erase "..\..\..\..\obj\ConvDll\Release\StdAfx.obj"
	-@erase "..\..\..\..\obj\ConvDll\Release\ConvDLL.res"
	-@erase "..\..\..\lib\release\ConvBase.lib"
	-@erase "..\..\..\lib\release\ConvBase.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "." /I "k:\develop\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "BUILDING_CONVBASE_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /I "." /I "k:\develop\include" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D\
 "BUILDING_CONVBASE_DLL" /Fp"$(INTDIR)/ConvDLL.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\ConvDll\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ConvDLL.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ConvDLL.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 k:\develop\lib\release\lifile.lib k:\develop\lib\release\li.lib k:\develop\lib\release\crypt.lib k:\develop\lib\release\lbs.lib k:\develop\lib\release\slot.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\..\release/ConvBase.dll"
LINK32_FLAGS=k:\develop\lib\release\lifile.lib k:\develop\lib\release\li.lib\
 k:\develop\lib\release\crypt.lib k:\develop\lib\release\lbs.lib\
 k:\develop\lib\release\slot.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ConvBase.pdb" /machine:I386 /def:".\ConvDLL.def"\
 /out:"..\..\..\release/ConvBase.dll" /implib:"$(OUTDIR)/ConvBase.lib" 
DEF_FILE= \
	".\ConvDLL.def"
LINK32_OBJS= \
	"$(INTDIR)/LIProg.obj" \
	"$(INTDIR)/FBDlgCl.obj" \
	"$(INTDIR)/ConvDLL.obj" \
	"$(INTDIR)/Convcl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ConvDLL.res"

"$(OUTDIR)\ConvBase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "d:\obj\convdll\debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\debug
INTDIR=d:\obj\convdll\debug

ALL : "$(OUTDIR)\ConvBase.dll" "..\..\..\..\obj\convdll\debug\ConvDLL.pch"\
 "..\..\..\lib\debug\ConvDLL.bsc"

CLEAN : 
	-@erase "..\..\..\..\obj\convdll\debug\vc40.pdb"
	-@erase "..\..\..\..\obj\convdll\debug\vc40.idb"
	-@erase "..\..\..\..\obj\convdll\debug\ConvDLL.pch"
	-@erase "..\..\..\lib\debug\ConvDLL.bsc"
	-@erase "..\..\..\..\obj\convdll\debug\LIProg.sbr"
	-@erase "..\..\..\..\obj\convdll\debug\ConvDLL.sbr"
	-@erase "..\..\..\..\obj\convdll\debug\FBDlgCl.sbr"
	-@erase "..\..\..\..\obj\convdll\debug\Convcl.sbr"
	-@erase "..\..\..\..\obj\convdll\debug\StdAfx.sbr"
	-@erase "..\..\..\debug\ConvBase.dll"
	-@erase "..\..\..\..\obj\convdll\debug\Convcl.obj"
	-@erase "..\..\..\..\obj\convdll\debug\StdAfx.obj"
	-@erase "..\..\..\..\obj\convdll\debug\LIProg.obj"
	-@erase "..\..\..\..\obj\convdll\debug\ConvDLL.obj"
	-@erase "..\..\..\..\obj\convdll\debug\FBDlgCl.obj"
	-@erase "..\..\..\..\obj\convdll\debug\ConvDLL.res"
	-@erase "..\..\..\debug\ConvBase.ilk"
	-@erase "..\..\..\lib\debug\ConvBase.lib"
	-@erase "..\..\..\lib\debug\ConvBase.exp"
	-@erase "..\..\..\lib\debug\ConvBase.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "." /I "k:\develop\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "BUILDING_CONVBASE_DLL" /FR /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "." /I "k:\develop\include"\
 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D\
 "BUILDING_CONVBASE_DLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ConvDLL.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\convdll\debug/
CPP_SBRS=d:\obj\convdll\debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ConvDLL.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ConvDLL.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/LIProg.sbr" \
	"$(INTDIR)/ConvDLL.sbr" \
	"$(INTDIR)/FBDlgCl.sbr" \
	"$(INTDIR)/Convcl.sbr" \
	"$(INTDIR)/StdAfx.sbr"

"..\..\..\lib\debug\ConvDLL.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\lbs.lib k:\develop\lib\debug\slot.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\debug/ConvBase.dll"
LINK32_FLAGS=k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\li.lib\
 k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\lbs.lib\
 k:\develop\lib\debug\slot.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ConvBase.pdb" /debug /machine:I386 /def:".\ConvDLL.def"\
 /out:"..\..\..\debug/ConvBase.dll" /implib:"$(OUTDIR)/ConvBase.lib" 
DEF_FILE= \
	".\ConvDLL.def"
LINK32_OBJS= \
	"$(INTDIR)/Convcl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/LIProg.obj" \
	"$(INTDIR)/ConvDLL.obj" \
	"$(INTDIR)/FBDlgCl.obj" \
	"$(INTDIR)/ConvDLL.res"

"$(OUTDIR)\ConvBase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ConvDLL - Win32 Release"
# Name "ConvDLL - Win32 Debug"

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConvDLL.cpp
DEP_CPP_CONVD=\
	".\StdAfx.h"\
	".\ConvDLL.h"\
	"k:\develop\include\critsect.h"\
	

!IF  "$(CFG)" == "ConvDLL - Win32 Release"


"$(INTDIR)\ConvDLL.obj" : $(SOURCE) $(DEP_CPP_CONVD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"


"$(INTDIR)\ConvDLL.obj" : $(SOURCE) $(DEP_CPP_CONVD) "$(INTDIR)"

"$(INTDIR)\ConvDLL.sbr" : $(SOURCE) $(DEP_CPP_CONVD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConvDLL.def

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /Zp4 /MT /W3 /GX /O2 /I "." /I "k:\develop\include" /D "NDEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D\
 "BUILDING_CONVBASE_DLL" /Fp"$(INTDIR)/ConvDLL.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ConvDLL.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "." /I "k:\develop\include" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D\
 "BUILDING_CONVBASE_DLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ConvDLL.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ConvDLL.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConvDLL.rc
DEP_RSC_CONVDL=\
	".\res\ConvDLL.rc2"\
	

"$(INTDIR)\ConvDLL.res" : $(SOURCE) $(DEP_RSC_CONVDL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Convcl.cpp
DEP_CPP_CONVC=\
	".\StdAfx.h"\
	"k:\develop\include\lbs.h"\
	".\ConvCl.h"\
	".\CVBErr.h"\
	".\fbdlgcl.h"\
	"k:\develop\include\oldtypes.h"\
	"k:\develop\include\lb1cl.h"\
	"k:\develop\include\lb3cl.h"\
	"k:\develop\include\lb4cl.h"\
	"k:\develop\include\oldlb1cl.h"\
	"k:\develop\include\oldlb2cl.h"\
	"k:\develop\include\oldlb3cl.h"\
	"k:\develop\include\oldlb4cl.h"\
	"k:\develop\include\cripto.h"\
	".\LIProg.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\slot.h"\
	"k:\develop\include\funcp.h"\
	"k:\develop\include\sesscl.h"\
	".\cvbclass.h"\
	"k:\develop\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\dynfile.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\oldrecf.h"\
	"k:\develop\include\olddynf.h"\
	"k:\develop\include\slotdefs.h"\
	"k:\develop\include\defclass.h"\
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
	"k:\develop\include\filecl.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\basecl.h"\
	"k:\develop\include\grplist.h"\
	"k:\develop\include\passwdcl.h"\
	"k:\develop\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbslstcl.h"\
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
	"k:\develop\include\groupcl.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\Occurcl.h"\
	"k:\develop\include\occ_list.h"\
	"k:\develop\include\indexsys.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\parser.h"\
	"k:\develop\include\lbsexpol.h"\
	"k:\develop\include\filistcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\template.h"\
	"k:\develop\include\focc_lis.h"\
	"k:\develop\include\termlist.h"\
	"k:\develop\include\rexpr.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\fileconf.h"\
	"k:\develop\include\filedata.h"\
	"k:\develop\include\index.h"\
	"k:\develop\include\phone.h"\
	"k:\develop\include\synonym.h"\
	"k:\develop\include\lockfile.h"\
	"k:\develop\include\list_lst.h"\
	"k:\develop\include\hashtab.h"\
	"k:\develop\include\expr.h"\
	"k:\develop\include\fieldcl.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\listcl.h"\
	"k:\develop\include\rtree.h"\
	"k:\develop\include\eparser.h"\
	"k:\develop\include\hashlist.h"\
	"k:\develop\include\bintree.h"\
	"k:\develop\include\tstring.h"\
	"k:\develop\include\tinterv.h"\
	"k:\develop\include\tlist.h"\
	"k:\develop\include\toplogic.h"\
	"k:\develop\include\toprestr.h"\
	"k:\develop\include\datalist.h"\
	"k:\develop\include\linklist.h"\
	"k:\develop\include\lt.h"\
	"k:\develop\include\tabsymb.h"\
	"k:\develop\include\syn_buf.h"\
	"k:\develop\include\syn_set.h"\
	"k:\develop\include\datacl.h"\
	"k:\develop\include\linkcl.h"\
	"k:\develop\include\session.h"\
	"k:\develop\include\exprlist.h"\
	"k:\develop\include\objstore.h"\
	"k:\develop\include\hole.h"\
	"k:\develop\include\binarycl.h"\
	"k:\develop\include\refercl.h"\
	

!IF  "$(CFG)" == "ConvDLL - Win32 Release"


"$(INTDIR)\Convcl.obj" : $(SOURCE) $(DEP_CPP_CONVC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"


"$(INTDIR)\Convcl.obj" : $(SOURCE) $(DEP_CPP_CONVC) "$(INTDIR)"

"$(INTDIR)\Convcl.sbr" : $(SOURCE) $(DEP_CPP_CONVC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIProg.cpp
DEP_CPP_LIPRO=\
	".\LIProg.h"\
	

!IF  "$(CFG)" == "ConvDLL - Win32 Release"


"$(INTDIR)\LIProg.obj" : $(SOURCE) $(DEP_CPP_LIPRO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"


"$(INTDIR)\LIProg.obj" : $(SOURCE) $(DEP_CPP_LIPRO) "$(INTDIR)"

"$(INTDIR)\LIProg.sbr" : $(SOURCE) $(DEP_CPP_LIPRO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FBDlgCl.cpp
DEP_CPP_FBDLG=\
	".\StdAfx.h"\
	".\ConvDLL.h"\
	".\fbdlgcl.h"\
	

!IF  "$(CFG)" == "ConvDLL - Win32 Release"


"$(INTDIR)\FBDlgCl.obj" : $(SOURCE) $(DEP_CPP_FBDLG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"


"$(INTDIR)\FBDlgCl.obj" : $(SOURCE) $(DEP_CPP_FBDLG) "$(INTDIR)"

"$(INTDIR)\FBDlgCl.sbr" : $(SOURCE) $(DEP_CPP_FBDLG) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
