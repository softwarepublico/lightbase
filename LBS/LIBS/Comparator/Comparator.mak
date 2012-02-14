# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=Comparator - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Comparator - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Comparator - Win32 Release" && "$(CFG)" !=\
 "Comparator - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Comparator.mak" CFG="Comparator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Comparator - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Comparator - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "Comparator - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "Comparator - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "k:\develop\lib\release"
# PROP Intermediate_Dir "d:\obj\comparator\release"
# PROP Target_Dir ""
OUTDIR=k:\develop\lib\release
INTDIR=d:\obj\comparator\release

ALL : "$(OUTDIR)\Comparator.lib"

CLEAN : 
	-@erase "k:\develop\lib\release\Comparator.lib"
	-@erase "..\..\..\..\obj\comparator\release\Comparator.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I "." /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /O2 /I "." /I "k:\develop\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/Comparator.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\comparator\release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Comparator.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/Comparator.lib" 
LIB32_OBJS= \
	"$(INTDIR)/Comparator.obj"

"$(OUTDIR)\Comparator.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Comparator - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "k:\develop\lib\debug"
# PROP Intermediate_Dir "d:\obj\comparator\debug"
# PROP Target_Dir ""
OUTDIR=k:\develop\lib\debug
INTDIR=d:\obj\comparator\debug

ALL : "$(OUTDIR)\Comparator.lib" "$(OUTDIR)\Comparator.bsc"

CLEAN : 
	-@erase "k:\develop\lib\debug\Comparator.bsc"
	-@erase "..\..\..\..\obj\comparator\debug\Comparator.sbr"
	-@erase "k:\develop\lib\debug\Comparator.lib"
	-@erase "..\..\..\..\obj\comparator\debug\Comparator.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NEW_DBG_LIGHT_" /FR /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I "k:\develop\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NEW_DBG_LIGHT_" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Comparator.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\comparator\debug/
CPP_SBRS=d:\obj\comparator\debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Comparator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Comparator.sbr"

"$(OUTDIR)\Comparator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/Comparator.lib" 
LIB32_OBJS= \
	"$(INTDIR)/Comparator.obj"

"$(OUTDIR)\Comparator.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "Comparator - Win32 Release"
# Name "Comparator - Win32 Debug"

!IF  "$(CFG)" == "Comparator - Win32 Release"

!ELSEIF  "$(CFG)" == "Comparator - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Comparator.cpp
DEP_CPP_COMPA=\
	"k:\develop\include\lbnewdbg.h"\
	".\comparator.h"\
	

!IF  "$(CFG)" == "Comparator - Win32 Release"


"$(INTDIR)\Comparator.obj" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Comparator - Win32 Debug"


"$(INTDIR)\Comparator.obj" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"

"$(INTDIR)\Comparator.sbr" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
