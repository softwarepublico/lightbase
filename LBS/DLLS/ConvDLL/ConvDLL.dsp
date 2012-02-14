# Microsoft Developer Studio Project File - Name="ConvDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ConvDLL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ConvDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ConvDLL.mak" CFG="ConvDLL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ConvDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConvDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ConvDLL - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release"
# PROP Intermediate_Dir "\obj\ConvDll\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "." /I "k:\develop\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "BUILDING_CONVBASE_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 lifile.lib li.lib crypt.lib lbs.lib slot.lib lbstart.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\..\release\ConvBase.dll" /libpath:"k:\develop\lib\release"
# Begin Special Build Tool
OutDir=.\..\..\..\lib\release
TargetPath=\devvlad\release\ConvBase.dll
TargetName=ConvBase
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L R $(OutDir)\$(TargetName).lib	call CopyFiles D    R    $(TargetPath)	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ConvDLL - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\debug"
# PROP Intermediate_Dir "\obj\convdll\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /GX /ZI /Od /I "." /I "k:\develop\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "BUILDING_CONVBASE_DLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 lifile.lib li.lib crypt.lib lbs.lib slot.lib lbstart.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\debug\ConvBase.dll" /libpath:"k:\develop\lib\debug"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
OutDir=.\..\..\..\lib\debug
TargetPath=\devvlad\debug\ConvBase.dll
TargetName=ConvBase
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L D $(OutDir)\$(TargetName).lib	call CopyFiles D   D     $(TargetPath)	echo ok.
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ConvDLL - Win32 Release"
# Name "ConvDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Convcl.cpp
# End Source File
# Begin Source File

SOURCE=.\ConvDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\ConvDLL.def
# End Source File
# Begin Source File

SOURCE=.\ConvDLL.rc
# End Source File
# Begin Source File

SOURCE=.\FBDlgCl.cpp
# End Source File
# Begin Source File

SOURCE=.\LIProg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ConvCl.h
# End Source File
# Begin Source File

SOURCE=.\ConvDLL.h
# End Source File
# Begin Source File

SOURCE=.\cvbclass.h
# End Source File
# Begin Source File

SOURCE=.\CVBErr.h
# End Source File
# Begin Source File

SOURCE=.\fbdlgcl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ConvDLL.rc2
# End Source File
# End Group
# End Target
# End Project
