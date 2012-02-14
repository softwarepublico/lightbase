# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=persdll - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to persdll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "persdll - Win32 Release" && "$(CFG)" !=\
 "persdll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "persdll.mak" CFG="persdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "persdll - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "persdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "persdll - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "persdll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "c:\obj\persdll\release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\release
INTDIR=c:\obj\persdll\release

ALL : "$(OUTDIR)\lbstart.dll"

CLEAN : 
	-@erase "..\..\..\release\lbstart.dll"
	-@erase "..\..\..\..\obj\persdll\release\personcl.obj"
	-@erase "..\..\..\lib\release\lbstart.lib"
	-@erase "..\..\..\lib\release\lbstart.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /I "k:\develop\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /Fp"$(INTDIR)/persdll.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=c:\obj\persdll\release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/persdll.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\release\crypt.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\..\release/lbstart.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\release\crypt.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/lbstart.pdb" /machine:I386\
 /out:"..\..\..\release/lbstart.dll" /implib:"$(OUTDIR)/lbstart.lib" 
LINK32_OBJS= \
	"$(INTDIR)/personcl.obj"

"$(OUTDIR)\lbstart.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "persdll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "c:\obj\persdll\debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\debug
INTDIR=c:\obj\persdll\debug

ALL : "$(OUTDIR)\lbstart.dll"

CLEAN : 
	-@erase "..\..\..\..\obj\persdll\debug\vc40.pdb"
	-@erase "..\..\..\..\obj\persdll\debug\vc40.idb"
	-@erase "..\..\..\debug\lbstart.dll"
	-@erase "..\..\..\..\obj\persdll\debug\personcl.obj"
	-@erase "..\..\..\debug\lbstart.ilk"
	-@erase "..\..\..\lib\debug\lbstart.lib"
	-@erase "..\..\..\lib\debug\lbstart.exp"
	-@erase "..\..\..\lib\debug\lbstart.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "k:\develop\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL"\
 /Fp"$(INTDIR)/persdll.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=c:\obj\persdll\debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/persdll.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\crypt.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\debug/lbstart.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\debug\crypt.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/lbstart.pdb" /debug /machine:I386\
 /out:"..\..\..\debug/lbstart.dll" /implib:"$(OUTDIR)/lbstart.lib" 
LINK32_OBJS= \
	"$(INTDIR)/personcl.obj"

"$(OUTDIR)\lbstart.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "persdll - Win32 Release"
# Name "persdll - Win32 Debug"

!IF  "$(CFG)" == "persdll - Win32 Release"

!ELSEIF  "$(CFG)" == "persdll - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\personcl.c
DEP_CPP_PERSO=\
	"k:\develop\include\crypt.h"\
	".\personcl.h"\
	"k:\develop\include\defclass.h"\
	

"$(INTDIR)\personcl.obj" : $(SOURCE) $(DEP_CPP_PERSO) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
