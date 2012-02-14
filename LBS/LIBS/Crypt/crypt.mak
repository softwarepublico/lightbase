# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=crypt - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to crypt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "crypt - Win32 Release" && "$(CFG)" != "crypt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "crypt.mak" CFG="crypt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "crypt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "crypt - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "crypt - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "crypt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "c:\obj\crypt\release"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\release
INTDIR=c:\obj\crypt\release

ALL : "$(OUTDIR)\crypt.lib"

CLEAN : 
	-@erase "..\..\..\lib\release\crypt.lib"
	-@erase "..\..\..\..\obj\crypt\release\crypt.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/crypt.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=c:\obj\crypt\release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/crypt.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/crypt.lib" 
LIB32_OBJS= \
	"$(INTDIR)/crypt.obj"

"$(OUTDIR)\crypt.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "crypt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "c:\obj\crypt\debug"
# PROP Target_Dir ""
OUTDIR=.\..\..\..\lib\debug
INTDIR=c:\obj\crypt\debug

ALL : "$(OUTDIR)\crypt.lib"

CLEAN : 
	-@erase "..\..\..\lib\debug\crypt.lib"
	-@erase "..\..\..\..\obj\crypt\debug\crypt.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/crypt.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=c:\obj\crypt\debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/crypt.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/crypt.lib" 
LIB32_OBJS= \
	"$(INTDIR)/crypt.obj"

"$(OUTDIR)\crypt.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "crypt - Win32 Release"
# Name "crypt - Win32 Debug"

!IF  "$(CFG)" == "crypt - Win32 Release"

!ELSEIF  "$(CFG)" == "crypt - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\crypt.c
DEP_CPP_CRYPT=\
	".\crypt.h"\
	

"$(INTDIR)\crypt.obj" : $(SOURCE) $(DEP_CPP_CRYPT) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
