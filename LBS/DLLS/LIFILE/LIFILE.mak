# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=LIFILE - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to LIFILE - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LIFILE - Win32 Release" && "$(CFG)" != "LIFILE - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "LIFILE.mak" CFG="LIFILE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LIFILE - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LIFILE - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "LIFILE - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "LIFILE - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "/obj/lifile/release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\release
INTDIR=/obj/lifile/release

ALL : "$(OUTDIR)\LIFILE.dll"

CLEAN : 
	-@erase "..\..\..\release\LIFILE.dll"
	-@erase "..\..\..\..\obj\lifile\release\LIFDLL.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\OLDLBFIL.obj"
	-@erase "..\..\..\..\obj\lifile\release\WDFILECL.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\OLDDYNF.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\RECFILCL.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\DYNFILE.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\logcl.obj"
	-@erase "..\..\..\..\obj\lifile\release\LBFILES.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\OLDRECF.OBJ"
	-@erase "..\..\..\..\obj\lifile\release\LIFILE.res"
	-@erase "..\..\..\lib\release\LIFILE.lib"
	-@erase "..\..\..\lib\release\LIFILE.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I ".\include" /I "k:\develop\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_CFILE_WINDOWS_FILES_" /D "BUILDING_LIFILE_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /O2 /I ".\include" /I "k:\develop\include" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_CFILE_WINDOWS_FILES_" /D\
 "BUILDING_LIFILE_DLL" /Fp"$(INTDIR)/LIFILE.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=/obj/lifile/release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LIFILE.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LIFILE.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\release\li.lib k:\develop\lib\release\crypt.lib k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"..\..\..\release/LIFILE.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\release\li.lib k:\develop\lib\release\crypt.lib\
 k:\develop\lib\release\lbstart.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/LIFILE.pdb" /machine:I386\
 /nodefaultlib:"libcmtd.lib" /def:".\Lifile.def"\
 /out:"..\..\..\release/LIFILE.dll" /implib:"$(OUTDIR)/LIFILE.lib" 
DEF_FILE= \
	".\Lifile.def"
LINK32_OBJS= \
	"$(INTDIR)/LIFDLL.OBJ" \
	"$(INTDIR)/OLDLBFIL.obj" \
	"$(INTDIR)/WDFILECL.OBJ" \
	"$(INTDIR)/OLDDYNF.OBJ" \
	"$(INTDIR)/RECFILCL.OBJ" \
	"$(INTDIR)/DYNFILE.OBJ" \
	"$(INTDIR)/logcl.obj" \
	"$(INTDIR)/LBFILES.OBJ" \
	"$(INTDIR)/OLDRECF.OBJ" \
	"$(INTDIR)/LIFILE.res"

"$(OUTDIR)\LIFILE.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "/obj/lifile/debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\debug
INTDIR=/obj/lifile/debug

ALL : "$(OUTDIR)\LIFILE.dll" "..\..\..\lib\debug\LIFILE.bsc"

CLEAN : 
	-@erase "..\..\..\..\obj\lifile\debug\vc40.pdb"
	-@erase "..\..\..\..\obj\lifile\debug\vc40.idb"
	-@erase "..\..\..\lib\debug\LIFILE.bsc"
	-@erase "..\..\..\..\obj\lifile\debug\RECFILCL.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\LBFILES.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\OLDRECF.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\LIFDLL.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\DYNFILE.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\OLDLBFIL.sbr"
	-@erase "..\..\..\..\obj\lifile\debug\WDFILECL.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\OLDDYNF.SBR"
	-@erase "..\..\..\..\obj\lifile\debug\logcl.sbr"
	-@erase "..\..\..\debug\LIFILE.dll"
	-@erase "..\..\..\..\obj\lifile\debug\WDFILECL.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\OLDDYNF.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\logcl.obj"
	-@erase "..\..\..\..\obj\lifile\debug\RECFILCL.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\LBFILES.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\OLDRECF.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\LIFDLL.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\DYNFILE.OBJ"
	-@erase "..\..\..\..\obj\lifile\debug\OLDLBFIL.obj"
	-@erase "..\..\..\..\obj\lifile\debug\LIFILE.res"
	-@erase "..\..\..\debug\LIFILE.ilk"
	-@erase "..\..\..\lib\debug\LIFILE.lib"
	-@erase "..\..\..\lib\debug\LIFILE.exp"
	-@erase "..\..\..\lib\debug\LIFILE.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I ".\include" /I "k:\develop\include" /D "_NEW_DBG_LIGHT_" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_CFILE_WINDOWS_FILES_" /D "BUILDING_LIFILE_DLL" /FR /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I ".\include" /I\
 "k:\develop\include" /D "_NEW_DBG_LIGHT_" /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_CFILE_WINDOWS_FILES_" /D "BUILDING_LIFILE_DLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/LIFILE.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=/obj/lifile/debug/
CPP_SBRS=/obj/lifile/debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LIFILE.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LIFILE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/RECFILCL.SBR" \
	"$(INTDIR)/LBFILES.SBR" \
	"$(INTDIR)/OLDRECF.SBR" \
	"$(INTDIR)/LIFDLL.SBR" \
	"$(INTDIR)/DYNFILE.SBR" \
	"$(INTDIR)/OLDLBFIL.sbr" \
	"$(INTDIR)/WDFILECL.SBR" \
	"$(INTDIR)/OLDDYNF.SBR" \
	"$(INTDIR)/logcl.sbr"

"..\..\..\lib\debug\LIFILE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\lbstart.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\debug/LIFILE.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\crypt.lib\
 k:\develop\lib\debug\lbstart.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/LIFILE.pdb" /debug /machine:I386\
 /def:".\Lifile.def" /out:"..\..\..\debug/LIFILE.dll"\
 /implib:"$(OUTDIR)/LIFILE.lib" 
DEF_FILE= \
	".\Lifile.def"
LINK32_OBJS= \
	"$(INTDIR)/WDFILECL.OBJ" \
	"$(INTDIR)/OLDDYNF.OBJ" \
	"$(INTDIR)/logcl.obj" \
	"$(INTDIR)/RECFILCL.OBJ" \
	"$(INTDIR)/LBFILES.OBJ" \
	"$(INTDIR)/OLDRECF.OBJ" \
	"$(INTDIR)/LIFDLL.OBJ" \
	"$(INTDIR)/DYNFILE.OBJ" \
	"$(INTDIR)/OLDLBFIL.obj" \
	"$(INTDIR)/LIFILE.res"

"$(OUTDIR)\LIFILE.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "LIFILE - Win32 Release"
# Name "LIFILE - Win32 Debug"

!IF  "$(CFG)" == "LIFILE - Win32 Release"

!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SOURCE\WDFILECL.CPP
DEP_CPP_WDFIL=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\filecl.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	"k:\develop\include\cripto.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\personcl.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	".\include\lifdef.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\WDFILECL.OBJ" : $(SOURCE) $(DEP_CPP_WDFIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\WDFILECL.OBJ" : $(SOURCE) $(DEP_CPP_WDFIL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WDFILECL.SBR" : $(SOURCE) $(DEP_CPP_WDFIL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\RECFILCL.CPP
DEP_CPP_RECFI=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\recfilcl.h"\
	"k:\develop\include\cripto.h"\
	".\include\filecl.h"\
	".\include\lifdef.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\RECFILCL.OBJ" : $(SOURCE) $(DEP_CPP_RECFI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RECFILCL.OBJ" : $(SOURCE) $(DEP_CPP_RECFI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RECFILCL.SBR" : $(SOURCE) $(DEP_CPP_RECFI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\DYNFILE.CPP
DEP_CPP_DYNFI=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\dynfile.h"\
	"k:\develop\include\cripto.h"\
	"k:\develop\include\strdup.h"\
	".\include\filecl.h"\
	"k:\develop\include\lbstypes.h"\
	".\include\lifdef.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\stringn.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\DYNFILE.OBJ" : $(SOURCE) $(DEP_CPP_DYNFI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DYNFILE.OBJ" : $(SOURCE) $(DEP_CPP_DYNFI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DYNFILE.SBR" : $(SOURCE) $(DEP_CPP_DYNFI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\LIFDLL.CPP
DEP_CPP_LIFDL=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\logcl.h"\
	"k:\develop\include\personcl.h"\
	".\include\filecl.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	".\include\lifdef.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\LIFDLL.OBJ" : $(SOURCE) $(DEP_CPP_LIFDL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LIFDLL.OBJ" : $(SOURCE) $(DEP_CPP_LIFDL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LIFDLL.SBR" : $(SOURCE) $(DEP_CPP_LIFDL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Readme.txt

!IF  "$(CFG)" == "LIFILE - Win32 Release"

!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE\LIFILE.RC

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\LIFILE.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/LIFILE.res" /i "RESOURCE" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


"$(INTDIR)\LIFILE.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/LIFILE.res" /i "RESOURCE" /d "_DEBUG"\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\OLDRECF.CPP
DEP_CPP_OLDRE=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\oldrecf.h"\
	"k:\develop\include\cripto.h"\
	".\include\filecl.h"\
	".\include\lifdef.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\OLDRECF.OBJ" : $(SOURCE) $(DEP_CPP_OLDRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\OLDRECF.OBJ" : $(SOURCE) $(DEP_CPP_OLDRE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OLDRECF.SBR" : $(SOURCE) $(DEP_CPP_OLDRE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\OLDLBFIL.cpp
DEP_CPP_OLDLB=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\oldtypes.h"\
	".\include\oldlb1cl.h"\
	".\include\oldlb2cl.h"\
	".\include\oldlb3cl.h"\
	".\include\oldlb4cl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\stringn.h"\
	".\include\filecl.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\lbse_of.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	".\include\lifdef.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbslstcl.h"\
	".\include\oldrecf.h"\
	".\include\olddynf.h"\
	".\include\recfilcl.h"\
	".\include\dynfile.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\OLDLBFIL.obj" : $(SOURCE) $(DEP_CPP_OLDLB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\OLDLBFIL.obj" : $(SOURCE) $(DEP_CPP_OLDLB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OLDLBFIL.sbr" : $(SOURCE) $(DEP_CPP_OLDLB) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\OLDDYNF.CPP
DEP_CPP_OLDDY=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\olddynf.h"\
	"k:\develop\include\cripto.h"\
	".\include\filecl.h"\
	"k:\develop\include\lbstypes.h"\
	".\include\lifdef.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\OLDDYNF.OBJ" : $(SOURCE) $(DEP_CPP_OLDDY) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\OLDDYNF.OBJ" : $(SOURCE) $(DEP_CPP_OLDDY) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OLDDYNF.SBR" : $(SOURCE) $(DEP_CPP_OLDDY) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOURCE\LBFILES.CPP
DEP_CPP_LBFIL=\
	"k:\develop\include\lbnewdbg.h"\
	".\include\lb1cl.h"\
	".\include\lb2cl.h"\
	".\include\lb3cl.h"\
	".\include\lb4cl.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\personcl.h"\
	".\include\recfilcl.h"\
	"k:\develop\include\lbstypes.h"\
	".\include\lifdef.h"\
	".\include\filecl.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\strdup.h"\
	".\include\dynfile.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\LBFILES.OBJ" : $(SOURCE) $(DEP_CPP_LBFIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LBFILES.OBJ" : $(SOURCE) $(DEP_CPP_LBFIL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LBFILES.SBR" : $(SOURCE) $(DEP_CPP_LBFIL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lbfile.ini

!IF  "$(CFG)" == "LIFILE - Win32 Release"

!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\logcl.cpp
DEP_CPP_LOGCL=\
	".\include\logcl.h"\
	"k:\develop\include\cstrtok.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\timecl.h"\
	".\include\filecl.h"\
	".\include\DeviceCl.h"\
	"k:\develop\include\Locklst.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\defmacro.h"\
	".\include\lifdef.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbse_of.h"\
	

!IF  "$(CFG)" == "LIFILE - Win32 Release"


"$(INTDIR)\logcl.obj" : $(SOURCE) $(DEP_CPP_LOGCL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\logcl.obj" : $(SOURCE) $(DEP_CPP_LOGCL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\logcl.sbr" : $(SOURCE) $(DEP_CPP_LOGCL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lifile.def

!IF  "$(CFG)" == "LIFILE - Win32 Release"

!ELSEIF  "$(CFG)" == "LIFILE - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
