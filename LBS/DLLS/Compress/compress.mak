# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=compress - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to compress - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "compress - Win32 Release" && "$(CFG)" !=\
 "compress - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "compress.mak" CFG="compress - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "compress - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "compress - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "compress - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "compress - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\Release"
# PROP Intermediate_Dir "..\..\..\..\obj\Compress\Release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\Release
INTDIR=.\..\..\..\..\obj\Compress\Release

ALL : "$(OUTDIR)\compress.dll"

CLEAN : 
	-@erase "..\..\..\Release\compress.dll"
	-@erase "..\..\..\..\obj\Compress\Release\Compress.obj"
	-@erase "..\..\..\lib\Release\compress.lib"
	-@erase "..\..\..\lib\Release\compress.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "\al101\h" /I " ." /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D " BUILDING_COMPRESS_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /I "\al101\h" /I " ." /I\
 "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 " BUILDING_COMPRESS_DLL" /Fp"$(INTDIR)/compress.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\..\..\..\..\obj\Compress\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/compress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\Release\alfc.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\..\Release/compress.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\Release\alfc.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/compress.pdb" /machine:I386\
 /out:"..\..\..\Release/compress.dll" /implib:"$(OUTDIR)/compress.lib" 
LINK32_OBJS= \
	"$(INTDIR)/Compress.obj"

"$(OUTDIR)\compress.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\Debug"
# PROP Intermediate_Dir "..\..\..\..\obj\Compress\Debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\Debug
INTDIR=.\..\..\..\..\obj\Compress\Debug

ALL : "$(OUTDIR)\compress.dll"

CLEAN : 
	-@erase "..\..\..\..\obj\Compress\Debug\vc40.pdb"
	-@erase "..\..\..\..\obj\Compress\Debug\vc40.idb"
	-@erase "..\..\..\Debug\compress.dll"
	-@erase "..\..\..\..\obj\Compress\Debug\Compress.obj"
	-@erase "..\..\..\Debug\compress.ilk"
	-@erase "..\..\..\lib\Debug\compress.lib"
	-@erase "..\..\..\lib\Debug\compress.exp"
	-@erase "..\..\..\lib\Debug\compress.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "\al101\h" /I " ." /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D " BUILDING_COMPRESS_DLL" /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /Gm /GX /Zi /Od /I "\al101\h" /I " ." /I\
 "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 " BUILDING_COMPRESS_DLL" /Fp"$(INTDIR)/compress.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\..\..\..\obj\Compress\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/compress.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\alfc.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\Debug/compress.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib k:\develop\lib\debug\alfc.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/compress.pdb" /debug /machine:I386\
 /out:"..\..\..\Debug/compress.dll" /implib:"$(OUTDIR)/compress.lib" 
LINK32_OBJS= \
	"$(INTDIR)/Compress.obj"

"$(OUTDIR)\compress.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "compress - Win32 Release"
# Name "compress - Win32 Debug"

!IF  "$(CFG)" == "compress - Win32 Release"

!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Compress.cpp

!IF  "$(CFG)" == "compress - Win32 Release"

DEP_CPP_COMPR=\
	".\Compress.h"\
	".\Defcompr.h"\
	
NODEP_CPP_COMPR=\
	".\aldefs.h"\
	".\arclib.h"\
	".\memstore.h"\
	".\grenengn.h"\
	

"$(INTDIR)\Compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

DEP_CPP_COMPR=\
	".\Compress.h"\
	"k:\develop\include\aldefs.h"\
	"k:\develop\include\arclib.h"\
	"k:\develop\include\memstore.h"\
	"k:\develop\include\grenengn.h"\
	".\Defcompr.h"\
	"k:\develop\include\_debug.h"\
	"k:\develop\include\status.h"\
	"k:\develop\include\objname.h"\
	"k:\develop\include\stor.h"\
	"k:\develop\include\cmpengn.h"\
	"k:\develop\include\monitor.h"\
	"k:\develop\include\arcentry.h"\
	"k:\develop\include\cmpobj.h"\
	"k:\develop\include\archiveb.h"\
	"k:\develop\include\alcxl.h"\
	"k:\develop\include\timedate.h"\
	"k:\develop\include\fileattr.h"\
	"k:\develop\include\alcxlkr.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	
NODEP_CPP_COMPR=\
	"k:\develop\include\alcustom.h"\
	

"$(INTDIR)\Compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
