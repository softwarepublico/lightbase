# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=sort - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to sort - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "sort - Win32 Release" && "$(CFG)" != "sort - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "sort.mak" CFG="sort - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sort - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sort - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "sort - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "sort - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "k:\develop\lib\release"
# PROP Intermediate_Dir "d:\obj\sort\release"
# PROP Target_Dir ""
OUTDIR=k:\develop\lib\release
INTDIR=d:\obj\sort\release

ALL : "$(OUTDIR)\sort.lib"

CLEAN : 
	-@erase "k:\develop\lib\release\sort.lib"
	-@erase "..\..\..\..\obj\sort\release\Sort.obj"
	-@erase "..\..\..\..\obj\sort\release\MMFile.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I "." /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp4 /MT /W3 /O2 /I "." /I "k:\develop\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/sort.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\sort\release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/sort.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/sort.lib" 
LIB32_OBJS= \
	"$(INTDIR)/Sort.obj" \
	"$(INTDIR)/MMFile.obj"

"$(OUTDIR)\sort.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sort - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "k:\develop\lib\debug"
# PROP Intermediate_Dir "d:\obj\sort\debug"
# PROP Target_Dir ""
OUTDIR=k:\develop\lib\debug
INTDIR=d:\obj\sort\debug

ALL : "$(OUTDIR)\sort.lib" "$(OUTDIR)\sort.bsc"

CLEAN : 
	-@erase "k:\develop\lib\debug\sort.bsc"
	-@erase "..\..\..\..\obj\sort\debug\MMFile.sbr"
	-@erase "..\..\..\..\obj\sort\debug\Sort.sbr"
	-@erase "k:\develop\lib\debug\sort.lib"
	-@erase "..\..\..\..\obj\sort\debug\MMFile.obj"
	-@erase "..\..\..\..\obj\sort\debug\Sort.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NEW_DBG_LIGHT_" /FR /YX /c
CPP_PROJ=/nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I "k:\develop\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NEW_DBG_LIGHT_" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/sort.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=d:\obj\sort\debug/
CPP_SBRS=d:\obj\sort\debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/sort.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/MMFile.sbr" \
	"$(INTDIR)/Sort.sbr"

"$(OUTDIR)\sort.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/sort.lib" 
LIB32_OBJS= \
	"$(INTDIR)/MMFile.obj" \
	"$(INTDIR)/Sort.obj"

"$(OUTDIR)\sort.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "sort - Win32 Release"
# Name "sort - Win32 Debug"

!IF  "$(CFG)" == "sort - Win32 Release"

!ELSEIF  "$(CFG)" == "sort - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MMFile.cpp
DEP_CPP_MMFIL=\
	"k:\develop\include\lbnewdbg.h"\
	".\mmfile.h"\
	

!IF  "$(CFG)" == "sort - Win32 Release"


"$(INTDIR)\MMFile.obj" : $(SOURCE) $(DEP_CPP_MMFIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sort - Win32 Debug"


"$(INTDIR)\MMFile.obj" : $(SOURCE) $(DEP_CPP_MMFIL) "$(INTDIR)"

"$(INTDIR)\MMFile.sbr" : $(SOURCE) $(DEP_CPP_MMFIL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sort.cpp
DEP_CPP_SORT_=\
	".\Sort.h"\
	".\mmflist.h"\
	"k:\develop\include\lbstempl.h"\
	".\mmfile.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\includes.h"\
	

!IF  "$(CFG)" == "sort - Win32 Release"


"$(INTDIR)\Sort.obj" : $(SOURCE) $(DEP_CPP_SORT_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sort - Win32 Debug"


"$(INTDIR)\Sort.obj" : $(SOURCE) $(DEP_CPP_SORT_) "$(INTDIR)"

"$(INTDIR)\Sort.sbr" : $(SOURCE) $(DEP_CPP_SORT_) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
