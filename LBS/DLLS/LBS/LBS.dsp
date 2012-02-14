# Microsoft Developer Studio Project File - Name="LBS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LBS - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LBS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LBS.mak" CFG="LBS - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LBS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LBS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LBS - Win32 Test" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LBS - Win32 Profile" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LBS - Win32 ReleaseComLog" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LBS - Win32 DebugComLog" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LBS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "/obj/lbs/release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I ".\INCLUDE" /I "K:\DEVELOP\INCLUDE" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_USING_LOG_" /D "MSVC" /D "__64_BIT_DATABASE_ENGINE__" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib appmngr.lib comparator.lib li.lib lt.lib lbstart.lib sort.lib lifile.lib crypt.lib compress.lib wsock32.lib htmltools.lib slot.lib IPWorks.lib lbindex.lib liparser.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release\LBS.dll" /libpath:"k:\develop\lib\release"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\..\..\..\lib\release
ProjDir=.
TargetDir=\DEVTREE_SHARE\devvlad\release
TargetPath=\DEVTREE_SHARE\devvlad\release\LBS.dll
TargetName=LBS
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles I R $(ProjDir)\Lang\Port\*.Ini Lang\Port	call              CopyFiles I R    $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	call CopyFiles L R              $(OutDir)\$(TargetName).lib   	call CopyFiles D R  $(TargetPath)	call           MakeSpecial lbs.mak "LBS - Win32 ReleaseComLog"	rem call CopyFiles L R           $(OutDir)\log\$(TargetName).lib log	rem call CopyFiles D R           $(TargetDir)\log\$(TargetName).dll log	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LBS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "/obj/lbs/debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp4 /MTd /W2 /Gm /GX /ZI /Od /I ".\INCLUDE" /I "..\..\..\include" /I "K:\DEVELOP\INCLUDE" /D "_DEBUG" /D "_" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_CRTDBG_MAP_ALLOC" /D "_USING_LOG_" /D "MSVC" /D "__64_BIT_DATABASE_ENGINE__" /FR /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 li.lib sort.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib appmngr.lib comparator.lib lt.lib lbstart.lib lifile.lib crypt.lib compress.lib wsock32.lib htmltools.lib slot.lib IPWorks.lib lbindex.lib liparser.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug\LBS.dll" /libpath:"..\..\..\lib\debug" /libpath:"k:\develop\lib\release"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
OutDir=.\..\..\..\lib\debug
ProjDir=.
TargetDir=\DEVTREE_SHARE\devvlad\debug
TargetPath=\DEVTREE_SHARE\devvlad\debug\LBS.dll
TargetName=LBS
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles I D $(ProjDir)\Lang\Port\*.Ini Lang\Port	call             CopyFiles I D     $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	call CopyFiles L D             $(OutDir)\$(TargetName).lib    	call CopyFiles D D  $(TargetPath)	call           MakeSpecial lbs.mak "LBS - Win32 DebugComLog"	rem call CopyFiles L D           $(OutDir)\log\$(TargetName).lib log	rem call CopyFiles D D           $(TargetDir)\log\$(TargetName).dll log	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LBS - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\LBS___Wi"
# PROP BASE Intermediate_Dir ".\LBS___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "/obj/lbs/test"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /MTd /W2 /Gm /GX /Zi /Od /I ".\INCLUDE" /I "K:\DEVELOP\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__TEST" /FR /YX /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Zp4 /MTd /W2 /Gm /GX /ZI /Od /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__TEST" /FR /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\appmngr.lib k:\develop\lib\debug\comparator.lib k:\develop\lib\debug\ctawlib.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\lt.lib k:\develop\lib\debug\lbstart.lib k:\develop\lib\debug\sort.lib k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\aviso.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug/LBS.dll" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT BASE LINK32 /profile /map /nodefaultlib
# ADD LINK32 k:\develop\lib\debug\lt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\appmngr.lib k:\develop\lib\debug\comparator.lib k:\develop\lib\debug\ctawlib.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\lbstart.lib k:\develop\lib\debug\sort.lib k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\compress.lib k:\develop\lib\debug\ConvAsc.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug\LBS.dll" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT LINK32 /profile /map /nodefaultlib

!ELSEIF  "$(CFG)" == "LBS - Win32 Profile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\LBS___Wi"
# PROP BASE Intermediate_Dir ".\LBS___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "/obj/lbs/profile"
# PROP Intermediate_Dir "/obj/lbs/profile"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /MTd /W2 /Gm /GX /Zi /Od /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /FR /YX /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Zp4 /MTd /W2 /Gm /GX /ZI /Od /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /FR"..\..\..\profile\LBS.bsc" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\profile\LBS.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\appmngr.lib k:\develop\lib\debug\comparator.lib k:\develop\lib\debug\ctawlib.lib k:\develop\lib\debug\li.lib d:\devadri\lib\debug\lt.lib k:\develop\lib\debug\lbstart.lib k:\develop\lib\debug\sort.lib k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\aviso.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug/LBS.dll" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT BASE LINK32 /profile /map /nodefaultlib
# ADD LINK32 d:\devadri\lib\debug\lt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\debug\appmngr.lib k:\develop\lib\debug\comparator.lib k:\develop\lib\debug\ctawlib.lib k:\develop\lib\debug\li.lib k:\develop\lib\debug\lbstart.lib k:\develop\lib\debug\sort.lib k:\develop\lib\debug\lifile.lib k:\develop\lib\debug\crypt.lib k:\develop\lib\debug\aviso.lib k:\develop\lib\debug\compress.lib k:\develop\lib\debug\ConvAsc.lib /nologo /subsystem:windows /dll /profile /map:"..\..\..\debug\LBS.map" /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug\LBS.dll" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "LBS - Win32 ReleaseComLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\LBS___Wi"
# PROP BASE Intermediate_Dir ".\LBS___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release\log"
# PROP Intermediate_Dir "/obj/lbs/release/log"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /MT /W3 /O2 /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_USING_LOG_" /YX /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_USING_LOG_" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\lib\release\appmngr.lib k:\develop\lib\release\comparator.lib k:\develop\lib\release\ctawlib.lib k:\develop\lib\release\li.lib k:\develop\lib\release\lt.lib k:\develop\lib\release\lbstart.lib k:\develop\lib\release\sort.lib k:\develop\lib\release\lifile.lib k:\develop\lib\release\crypt.lib k:\develop\lib\release\aviso.lib k:\develop\lib\release\compress.lib k:\develop\lib\release\ConvAsc.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release/LBS.dll"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib appmngr.lib comparator.lib ctawlib.lib li.lib lt.lib lbstart.lib sort.lib lifile.lib crypt.lib compress.lib wsock32.lib htmltools.lib slot.lib IPWorks.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release\log\LBS.dll" /libpath:"k:\develop\lib\release\log" /libpath:"k:\develop\lib\release"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\..\..\..\lib\release\log
ProjDir=.
TargetPath=\DEVTREE_SHARE\devvlad\release\log\LBS.dll
TargetName=LBS
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles I R $(ProjDir)\Lang\Port\*.Ini Lang\Port	call              CopyFiles I R    $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	call CopyFiles L R              $(OutDir)\$(TargetName).lib   log	call CopyFiles D R  $(TargetPath) log	echo            ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LBS - Win32 DebugComLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\LBS___Wi"
# PROP BASE Intermediate_Dir ".\LBS___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug\log"
# PROP Intermediate_Dir "/obj/lbs/debug/log"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /MTd /W2 /Gm /GX /Zi /Od /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "_DEBUG" /D "_NEW_DBG_LIGHT_" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_USING_LOG_" /FR /YX /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Zp4 /MTd /W2 /Gm /GX /ZI /Od /I ".\INCLUDE" /I "..\..\libs\ctree" /I "..\..\libs\ctree\wnd3" /I "K:\DEVELOP\INCLUDE" /D "_DEBUG" /D "_NEW_DBG_LIGHT_" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "_USING_LOG_" /FR /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib k:\develop\old\lib\debug\appmngr.lib k:\develop\old\lib\debug\comparator.lib k:\develop\old\lib\debug\ctawlib.lib k:\develop\old\lib\debug\li.lib k:\develop\lib\release\lt.lib k:\develop\old\lib\debug\lbstart.lib k:\develop\old\lib\debug\sort.lib k:\develop\lib\debug\lifile.lib k:\develop\old\lib\debug\crypt.lib k:\develop\old\lib\debug\aviso.lib k:\develop\old\lib\debug\compress.lib k:\develop\old\lib\debug\ConvAsc.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug/LBS.dll" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT BASE LINK32 /profile /map /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib appmngr.lib comparator.lib ctawlib.lib lbstart.lib sort.lib lifile.lib crypt.lib compress.lib li.lib log\lt.lib wsock32.lib slot.lib IPWorks.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB" /nodefaultlib:"LIBC.LIB" /out:"..\..\..\debug\log\LBS.dll" /libpath:"k:\develop\lib\debug" /map:"/tmp/LBS.map" /map:"/tmp/LBS.map"
# SUBTRACT LINK32 /profile /map /nodefaultlib
# Begin Special Build Tool
OutDir=.\..\..\..\lib\debug\log
ProjDir=.
TargetPath=\DEVTREE_SHARE\devvlad\debug\log\LBS.dll
TargetName=LBS
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles I D $(ProjDir)\Lang\Port\*.Ini Lang\Port	call             CopyFiles I D     $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	call CopyFiles L D             $(OutDir)\$(TargetName).lib    log	call CopyFiles D D  $(TargetPath) log	echo            ok.
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "LBS - Win32 Release"
# Name "LBS - Win32 Debug"
# Name "LBS - Win32 Test"
# Name "LBS - Win32 Profile"
# Name "LBS - Win32 ReleaseComLog"
# Name "LBS - Win32 DebugComLog"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\SOURCE\BASECL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\BASEINSTANCE.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\CachBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Context.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\controlfile.cpp
# End Source File
# Begin Source File

SOURCE=.\CRITREG\CRITREG.TXT
# End Source File
# Begin Source File

SOURCE=.\SOURCE\CritSectMan.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DATACL.CPP
# End Source File
# Begin Source File

SOURCE=.\CRITREG\DATACL.TXT
# End Source File
# Begin Source File

SOURCE=.\SOURCE\ENTPARCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\FIELDCL.CPP
# End Source File
# Begin Source File

SOURCE=.\CRITREG\FIELDCR.TXT
# End Source File
# Begin Source File

SOURCE=.\SOURCE\fieldgroup.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\gowords.cpp
# End Source File
# Begin Source File

SOURCE=.\Gowords.lb
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GROUPCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\IDXBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\idxoffcl.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LBFILES.CPP
# End Source File
# Begin Source File

SOURCE=.\Lang\Engl\Lbs.ini
# End Source File
# Begin Source File

SOURCE=.\Lang\Port\LBS.INI
# End Source File
# Begin Source File

SOURCE=.\RESOURCE\LBS.RC
# ADD BASE RSC /l 0x416 /i "RESOURCE"
# ADD RSC /l 0x416 /i "RESOURCE" /i ".\RESOURCE"
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Lbs_Http.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LBSDLL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LBSERRCL.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\LBSLckCl.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LICCTRL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LINKCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\LTBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\NEWLST.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OCBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OCCURCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OLDLBFIL.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OLDVERSIONS.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OLSORT.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OPINFOCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PARSERCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PASSWDCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PRIVBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PUBBASE1.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PUBBASE2.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\RECORD.CPP
# End Source File
# Begin Source File

SOURCE=.\Release.txt
# End Source File
# Begin Source File

SOURCE=.\SOURCE\REPBASE1.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\REPBASE2.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\REPBASE3.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\REPBASE4.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\RepSort.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SERVERCONFIG.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SESSCL1.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl10.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl11.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl12.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl13.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl14.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl15.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl16.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl17.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl18.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl19.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SESSCL2.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl20.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl21.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SESSCL3.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SESSCL4.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl5.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl6.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl7.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl8.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Sesscl9.cpp
# End Source File
# Begin Source File

SOURCE=.\CRITREG\SESSION.TXT
# End Source File
# Begin Source File

SOURCE=.\SOURCE\STRPARCL.CPP
# End Source File
# Begin Source File

SOURCE=.\SOURCE\USRCL.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\INCLUDE\allbasel.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\basecl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\BASEINSTANCE.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\baselist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\btimerl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\clilist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\controlfile.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\datacl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\datalist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\datecl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\defclass.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\deffuncs.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\defmacro.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\entparcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\explist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fieldcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fieldgroup.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\filistcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\funcp.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\glbdata.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\glbfield.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\groupcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\grplist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\idxoffcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\includes.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\indsyscl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LB1CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LB2CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LB3CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LB4CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LBS_Http.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbsdefs.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbse_of.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbserrcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbserror.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbserrtb.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbsexpol.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbslckcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbsollst.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbstempl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lbstypes.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\licctrl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\liclist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\linkcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\linklist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Locklst.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lockstru.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\loglist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Occurcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\oclistcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\OLDLB1CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\OLDLB2CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\OLDLB3CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\OLDLB4CL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\olsort.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\opinfocl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\parsercl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\passwdcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\record.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\serlst.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SERVERCONFIG.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\sesscl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\sesslist.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\stringn.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\strparcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\svbasel.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\timecl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\userdefs.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\usrcl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\usrinfol.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
