# Microsoft Developer Studio Project File - Name="rpcstuff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=rpcstuff - Win32 DebugComLog
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rpcstuff.mak".
!MESSAGE 
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
!MESSAGE "rpcstuff - Win32 ReleaseComLog" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rpcstuff - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\Release"
# PROP Intermediate_Dir "\obj\rpcstuff\release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x416
# ADD RSC /l 0x416
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=\devvlad\lib\Release\rpcstuff.lib
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L R $(TargetPath)	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\Debug"
# PROP Intermediate_Dir "\obj\rpcstuff\debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x416
# ADD RSC /l 0x416
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=\devvlad\lib\Debug\rpcstuff.lib
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L D $(TargetPath)	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 DebugComLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugComLog"
# PROP BASE Intermediate_Dir "DebugComLog"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug\log"
# PROP Intermediate_Dir "\obj\debug\log\rpcstuff"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MTd /W3 /GX /Z7 /Od /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USING_LOG_" /YX /FD /c
# ADD BASE RSC /l 0x416
# ADD RSC /l 0x416
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=\devvlad\lib\debug\log\rpcstuff.lib
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L D $(TargetPath) log	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "rpcstuff - Win32 ReleaseComLog"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseComLog"
# PROP BASE Intermediate_Dir "ReleaseComLog"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\relase\log"
# PROP Intermediate_Dir "\obj\release\log\rpcstuff"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "." /I ".\include" /I "k:\develop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USING_LOG_" /YX /FD /c
# ADD BASE RSC /l 0x416
# ADD RSC /l 0x416
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\release\log\rpcstuff.lib"
# Begin Special Build Tool
TargetPath=\devvlad\lib\release\log\rpcstuff.lib
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L R $(TargetPath) log	echo ok.
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "rpcstuff - Win32 Release"
# Name "rpcstuff - Win32 Debug"
# Name "rpcstuff - Win32 DebugComLog"
# Name "rpcstuff - Win32 ReleaseComLog"
# Begin Source File

SOURCE=.\source\critsect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\encript.cpp
# End Source File
# Begin Source File

SOURCE=.\source\fbuff.cpp
# End Source File
# Begin Source File

SOURCE=.\source\rpcserial1.cpp
# End Source File
# Begin Source File

SOURCE=.\source\rpcserial2.cpp
# End Source File
# Begin Source File

SOURCE=.\source\rpcserial3.cpp
# End Source File
# Begin Source File

SOURCE=.\source\rpcserial4.cpp
# End Source File
# End Target
# End Project
