# Microsoft Developer Studio Generated NMAKE File, Based on rpcstuff.dsp
!IF "$(CFG)" == ""
CFG=rpcstuff - Win32 DebugComLog
!MESSAGE No configuration specified. Defaulting to rpcstuff - Win32\
 DebugComLog.
!ENDIF 

!IF "$(CFG)" != "rpcstuff - Win32 Release" && "$(CFG)" !=\
 "rpcstuff - Win32 Debug" && "$(CFG)" != "rpcstuff - Win32 DebugComLog" &&\
 "$(CFG)" != "rpcstuff - Win32 ReleaseComLog"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rpcstuff.mak" CFG="rpcstuff - Win32 DebugComLog"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rpcstuff - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "rpcstuff - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "rpcstuff - Win32 DebugComLog" (based on "Win32 (x86) Static Library")
!MESSAGE "rpcstuff - Win32 ReleaseComLog" (based on\
 "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

OUTDIR=.\..\..\..\lib\Release
INTDIR=\obj\rpcstuff\release
# Begin Custom Macros
OutDir=.\..\..\..\lib\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\rpcstuff.lib"

!ELSE 

ALL : "LT - Win32 Release" "$(OUTDIR)\rpcstuff.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LT - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\critsect.obj"
	-@erase "$(INTDIR)\encript.obj"
	-@erase "$(INTDIR)\fbuff.obj"
	-@erase "$(INTDIR)\rpcserial1.obj"
	-@erase "$(INTDIR)\rpcserial2.obj"
	-@erase "$(INTDIR)\rpcserial3.obj"
	-@erase "$(INTDIR)\rpcserial4.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\rpcstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /I "." /I ".\include" /I\
 "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\rpcstuff.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\obj\rpcstuff\release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rpcstuff.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\rpcstuff.lib" 
LIB32_OBJS= \
	"$(INTDIR)\critsect.obj" \
	"$(INTDIR)\encript.obj" \
	"$(INTDIR)\fbuff.obj" \
	"$(INTDIR)\rpcserial1.obj" \
	"$(INTDIR)\rpcserial2.obj" \
	"$(INTDIR)\rpcserial3.obj" \
	"$(INTDIR)\rpcserial4.obj" \
	"$(OUTDIR)\Lt.lib"

"$(OUTDIR)\rpcstuff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

TargetPath=\devadri\lib\Release\rpcstuff.lib
SOURCE=$(InputPath)
PostBuild_Desc=Copiando arquivos...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\..\..\..\lib\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LT - Win32 Release" "$(OUTDIR)\rpcstuff.lib"
   call CopyFiles L R \devadri\lib\Release\rpcstuff.lib
	echo ok.
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

OUTDIR=.\..\..\..\lib\Debug
INTDIR=\obj\rpcstuff\debug
# Begin Custom Macros
OutDir=.\..\..\..\lib\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\rpcstuff.lib"

!ELSE 

ALL : "LT - Win32 Debug" "$(OUTDIR)\rpcstuff.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LT - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\critsect.obj"
	-@erase "$(INTDIR)\encript.obj"
	-@erase "$(INTDIR)\fbuff.obj"
	-@erase "$(INTDIR)\rpcserial1.obj"
	-@erase "$(INTDIR)\rpcserial2.obj"
	-@erase "$(INTDIR)\rpcserial3.obj"
	-@erase "$(INTDIR)\rpcserial4.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\rpcstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I ".\include" /I\
 "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\rpcstuff.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\obj\rpcstuff\debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rpcstuff.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\rpcstuff.lib" 
LIB32_OBJS= \
	"$(INTDIR)\critsect.obj" \
	"$(INTDIR)\encript.obj" \
	"$(INTDIR)\fbuff.obj" \
	"$(INTDIR)\rpcserial1.obj" \
	"$(INTDIR)\rpcserial2.obj" \
	"$(INTDIR)\rpcserial3.obj" \
	"$(INTDIR)\rpcserial4.obj" \
	"$(OUTDIR)\Lt.lib"

"$(OUTDIR)\rpcstuff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

TargetPath=\devadri\lib\Debug\rpcstuff.lib
SOURCE=$(InputPath)
PostBuild_Desc=Copiando arquivos...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\..\..\..\lib\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LT - Win32 Debug" "$(OUTDIR)\rpcstuff.lib"
   call CopyFiles L D \devadri\lib\Debug\rpcstuff.lib
	echo ok.
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

OUTDIR=.\..\..\..\lib\debug\log
INTDIR=\obj\debug\log\rpcstuff
# Begin Custom Macros
OutDir=.\..\..\..\lib\debug\log
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\rpcstuff.lib"

!ELSE 

ALL : "LT - Win32 DebugComLog" "$(OUTDIR)\rpcstuff.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LT - Win32 DebugComLogCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\critsect.obj"
	-@erase "$(INTDIR)\encript.obj"
	-@erase "$(INTDIR)\fbuff.obj"
	-@erase "$(INTDIR)\rpcserial1.obj"
	-@erase "$(INTDIR)\rpcserial2.obj"
	-@erase "$(INTDIR)\rpcserial3.obj"
	-@erase "$(INTDIR)\rpcserial4.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\rpcstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I ".\include" /I\
 "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USING_LOG_"\
 /Fp"$(INTDIR)\rpcstuff.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\obj\debug\log\rpcstuff/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rpcstuff.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\rpcstuff.lib" 
LIB32_OBJS= \
	"$(INTDIR)\critsect.obj" \
	"$(INTDIR)\encript.obj" \
	"$(INTDIR)\fbuff.obj" \
	"$(INTDIR)\rpcserial1.obj" \
	"$(INTDIR)\rpcserial2.obj" \
	"$(INTDIR)\rpcserial3.obj" \
	"$(INTDIR)\rpcserial4.obj" \
	"$(OUTDIR)\Lt.lib"

"$(OUTDIR)\rpcstuff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

TargetPath=\devadri\lib\debug\log\rpcstuff.lib
SOURCE=$(InputPath)
PostBuild_Desc=Copiando arquivos...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\..\..\..\lib\debug\log
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LT - Win32 DebugComLog" "$(OUTDIR)\rpcstuff.lib"
   call CopyFiles L D \devadri\lib\debug\log\rpcstuff.lib log
	echo ok.
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

OUTDIR=.\..\..\..\lib\relase\log
INTDIR=\obj\release\log\rpcstuff

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\lib\release\log\rpcstuff.lib"

!ELSE 

ALL : "LT - Win32 ReleaseComLog" "..\..\..\lib\release\log\rpcstuff.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LT - Win32 ReleaseComLogCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\critsect.obj"
	-@erase "$(INTDIR)\encript.obj"
	-@erase "$(INTDIR)\fbuff.obj"
	-@erase "$(INTDIR)\rpcserial1.obj"
	-@erase "$(INTDIR)\rpcserial2.obj"
	-@erase "$(INTDIR)\rpcserial3.obj"
	-@erase "$(INTDIR)\rpcserial4.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "..\..\..\lib\release\log\rpcstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Zp4 /MT /W3 /GX /O2 /I "." /I ".\include" /I\
 "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USING_LOG_"\
 /Fp"$(INTDIR)\rpcstuff.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=\obj\release\log\rpcstuff/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rpcstuff.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\lib\release\log\rpcstuff.lib" 
LIB32_OBJS= \
	"$(INTDIR)\critsect.obj" \
	"$(INTDIR)\encript.obj" \
	"$(INTDIR)\fbuff.obj" \
	"$(INTDIR)\rpcserial1.obj" \
	"$(INTDIR)\rpcserial2.obj" \
	"$(INTDIR)\rpcserial3.obj" \
	"$(INTDIR)\rpcserial4.obj" \
	"..\..\..\lib\release\Log\Lt.lib"

"..\..\..\lib\release\log\rpcstuff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

TargetPath=\devadri\lib\release\log\rpcstuff.lib
SOURCE=$(InputPath)
PostBuild_Desc=Copiando arquivos...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "LT - Win32 ReleaseComLog"\
 "..\..\..\lib\release\log\rpcstuff.lib"
   call CopyFiles L R \devadri\lib\release\log\rpcstuff.lib log
	echo ok.
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "rpcstuff - Win32 Release" || "$(CFG)" ==\
 "rpcstuff - Win32 Debug" || "$(CFG)" == "rpcstuff - Win32 DebugComLog" ||\
 "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

"LT - Win32 Release" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) /F .\Lt.mak CFG="LT - Win32 Release" 
   cd "..\rpcstuff"

"LT - Win32 ReleaseCLEAN" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\Lt.mak CFG="LT - Win32 Release" RECURSE=1 
   cd "..\rpcstuff"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

"LT - Win32 Debug" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) /F .\Lt.mak CFG="LT - Win32 Debug" 
   cd "..\rpcstuff"

"LT - Win32 DebugCLEAN" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\Lt.mak CFG="LT - Win32 Debug" RECURSE=1 
   cd "..\rpcstuff"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

"LT - Win32 DebugComLog" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) /F .\Lt.mak CFG="LT - Win32 DebugComLog" 
   cd "..\rpcstuff"

"LT - Win32 DebugComLogCLEAN" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\Lt.mak CFG="LT - Win32 DebugComLog"\
 RECURSE=1 
   cd "..\rpcstuff"

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

"LT - Win32 ReleaseComLog" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) /F .\Lt.mak CFG="LT - Win32 ReleaseComLog" 
   cd "..\rpcstuff"

"LT - Win32 ReleaseComLogCLEAN" : 
   cd "\devadri\LBS\LIBS\LT"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\Lt.mak CFG="LT - Win32 ReleaseComLog"\
 RECURSE=1 
   cd "..\rpcstuff"

!ENDIF 

SOURCE=.\source\critsect.cpp

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

DEP_CPP_CRITS=\
	".\include\stubcrit.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lbnewdbg.h"\
	

"$(INTDIR)\critsect.obj" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

DEP_CPP_CRITS=\
	".\include\stubcrit.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lbnewdbg.h"\
	

"$(INTDIR)\critsect.obj" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

DEP_CPP_CRITS=\
	".\include\stubcrit.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lbnewdbg.h"\
	

"$(INTDIR)\critsect.obj" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

DEP_CPP_CRITS=\
	".\include\stubcrit.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\lbnewdbg.h"\
	

"$(INTDIR)\critsect.obj" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\encript.cpp

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

DEP_CPP_ENCRI=\
	".\include\encript.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\_debug.h"\
	"k:\develop\include\aldefs.h"\
	"k:\develop\include\arcentry.h"\
	"k:\develop\include\archiveb.h"\
	"k:\develop\include\arclib.h"\
	"k:\develop\include\cmpengn.h"\
	"k:\develop\include\cmpobj.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\fileattr.h"\
	"k:\develop\include\grenengn.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\memstore.h"\
	"k:\develop\include\monitor.h"\
	"k:\develop\include\objname.h"\
	"k:\develop\include\status.h"\
	"k:\develop\include\stor.h"\
	"k:\develop\include\timedate.h"\
	

"$(INTDIR)\encript.obj" : $(SOURCE) $(DEP_CPP_ENCRI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

DEP_CPP_ENCRI=\
	".\include\encript.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\_debug.h"\
	"k:\develop\include\alcxl.h"\
	"k:\develop\include\alcxlkr.h"\
	"k:\develop\include\aldefs.h"\
	"k:\develop\include\arcentry.h"\
	"k:\develop\include\archiveb.h"\
	"k:\develop\include\arclib.h"\
	"k:\develop\include\cmpengn.h"\
	"k:\develop\include\cmpobj.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\fileattr.h"\
	"k:\develop\include\grenengn.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\memstore.h"\
	"k:\develop\include\monitor.h"\
	"k:\develop\include\objname.h"\
	"k:\develop\include\status.h"\
	"k:\develop\include\stor.h"\
	"k:\develop\include\timedate.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_ENCRI=\
	"k:\develop\include\alcustom.h"\
	

"$(INTDIR)\encript.obj" : $(SOURCE) $(DEP_CPP_ENCRI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

DEP_CPP_ENCRI=\
	".\include\encript.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\_debug.h"\
	"k:\develop\include\aldefs.h"\
	"k:\develop\include\arcentry.h"\
	"k:\develop\include\archiveb.h"\
	"k:\develop\include\arclib.h"\
	"k:\develop\include\cmpengn.h"\
	"k:\develop\include\cmpobj.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\fileattr.h"\
	"k:\develop\include\grenengn.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\memstore.h"\
	"k:\develop\include\monitor.h"\
	"k:\develop\include\objname.h"\
	"k:\develop\include\status.h"\
	"k:\develop\include\stor.h"\
	"k:\develop\include\timedate.h"\
	

"$(INTDIR)\encript.obj" : $(SOURCE) $(DEP_CPP_ENCRI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

DEP_CPP_ENCRI=\
	".\include\encript.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\_debug.h"\
	"k:\develop\include\aldefs.h"\
	"k:\develop\include\arcentry.h"\
	"k:\develop\include\archiveb.h"\
	"k:\develop\include\arclib.h"\
	"k:\develop\include\cmpengn.h"\
	"k:\develop\include\cmpobj.h"\
	"k:\develop\include\crypt.h"\
	"k:\develop\include\fileattr.h"\
	"k:\develop\include\grenengn.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\memstore.h"\
	"k:\develop\include\monitor.h"\
	"k:\develop\include\objname.h"\
	"k:\develop\include\status.h"\
	"k:\develop\include\stor.h"\
	"k:\develop\include\timedate.h"\
	

"$(INTDIR)\encript.obj" : $(SOURCE) $(DEP_CPP_ENCRI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\fbuff.cpp

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

DEP_CPP_FBUFF=\
	".\include\fbuff.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\classlib\_defs.h"\
	"k:\develop\include\classlib\date.h"\
	"k:\develop\include\classlib\defs.h"\
	"k:\develop\include\classlib\resource.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\devicecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbw_exp.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\logcl.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\fbuff.obj" : $(SOURCE) $(DEP_CPP_FBUFF) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

DEP_CPP_FBUFF=\
	".\include\fbuff.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\devicecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbw_exp.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\logcl.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\fbuff.obj" : $(SOURCE) $(DEP_CPP_FBUFF) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

DEP_CPP_FBUFF=\
	".\include\fbuff.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\devicecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbw_exp.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\logcl.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\fbuff.obj" : $(SOURCE) $(DEP_CPP_FBUFF) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

DEP_CPP_FBUFF=\
	".\include\fbuff.h"\
	".\include\lbsrpc.h"\
	"k:\develop\include\aclcl.h"\
	"k:\develop\include\acllist.h"\
	"k:\develop\include\allbasel.h"\
	"k:\develop\include\buffercl.h"\
	"k:\develop\include\classdef.h"\
	"k:\develop\include\classlib\_defs.h"\
	"k:\develop\include\classlib\date.h"\
	"k:\develop\include\classlib\defs.h"\
	"k:\develop\include\classlib\resource.h"\
	"k:\develop\include\const.h"\
	"k:\develop\include\critsect.h"\
	"k:\develop\include\datecl.h"\
	"k:\develop\include\defclass.h"\
	"k:\develop\include\defmacro.h"\
	"k:\develop\include\devicecl.h"\
	"k:\develop\include\explist.h"\
	"k:\develop\include\f_occurr.h"\
	"k:\develop\include\filecl.h"\
	"k:\develop\include\includes.h"\
	"k:\develop\include\lbnewdbg.h"\
	"k:\develop\include\lbsdefs.h"\
	"k:\develop\include\lbse_of.h"\
	"k:\develop\include\lbserror.h"\
	"k:\develop\include\lbslstcl.h"\
	"k:\develop\include\lbstempl.h"\
	"k:\develop\include\lbstypes.h"\
	"k:\develop\include\lbw_exp.h"\
	"k:\develop\include\lifdef.h"\
	"k:\develop\include\locklst.h"\
	"k:\develop\include\lockstru.h"\
	"k:\develop\include\logcl.h"\
	"k:\develop\include\machine.h"\
	"k:\develop\include\occurcl.h"\
	"k:\develop\include\occurren.h"\
	"k:\develop\include\permcl.h"\
	"k:\develop\include\permlist.h"\
	"k:\develop\include\serlst.h"\
	"k:\develop\include\strdup.h"\
	"k:\develop\include\stringn.h"\
	"k:\develop\include\svbasel.h"\
	"k:\develop\include\term.h"\
	"k:\develop\include\userdefs.h"\
	"k:\develop\include\usrinfol.h"\
	

"$(INTDIR)\fbuff.obj" : $(SOURCE) $(DEP_CPP_FBUFF) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\rpcserial1.cpp
DEP_CPP_RPCSE=\
	".\include\lbsrpc.h"\
	".\include\rpcserial.h"\
	

"$(INTDIR)\rpcserial1.obj" : $(SOURCE) $(DEP_CPP_RPCSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\rpcserial2.cpp
DEP_CPP_RPCSER=\
	".\include\lbsrpc.h"\
	".\include\rpcserial.h"\
	

"$(INTDIR)\rpcserial2.obj" : $(SOURCE) $(DEP_CPP_RPCSER) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\rpcserial3.cpp
DEP_CPP_RPCSERI=\
	".\include\lbsrpc.h"\
	".\include\rpcserial.h"\
	

"$(INTDIR)\rpcserial3.obj" : $(SOURCE) $(DEP_CPP_RPCSERI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\rpcserial4.cpp
DEP_CPP_RPCSERIA=\
	".\include\lbsrpc.h"\
	".\include\rpcserial.h"\
	

"$(INTDIR)\rpcserial4.obj" : $(SOURCE) $(DEP_CPP_RPCSERIA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

