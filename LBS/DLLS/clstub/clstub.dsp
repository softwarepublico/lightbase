# Microsoft Developer Studio Project File - Name="clstub" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=clstub - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "clstub.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "clstub.mak" CFG="clstub - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clstub - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clstub - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clstub - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\release\dce"
# PROP Intermediate_Dir "\obj\clstub\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MT /W3 /O2 /I ".\include" /I "k:\develop\include" /I "C:\Arquivos de programas\Microsoft Platform SDK\Include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__NOMFC" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ntdsapi.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib alfc.lib appmngr.lib li.lib lifile.lib crypt.lib rpcstuff.lib lbstart.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCMTD.LIB" /out:"..\..\..\release\dce\lbs.dll" /libpath:"k:\develop\lib\release" /libpath:"C:\Arquivos de programas\Microsoft Platform SDK\Lib"
# Begin Special Build Tool
OutDir=.\..\..\..\lib\release\dce
ProjDir=.
TargetPath=\DEVTREE_SHARE\devvlad\release\dce\lbs.dll
TargetName=lbs
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L R $(OutDir)\$(TargetName).lib dce	call         CopyFiles D R    $(TargetPath) dce	call CopyFiles I R      $(ProjDir)\Lang\Port\*.Ini Lang\Port	call CopyFiles I R      $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	echo ok.
# End Special Build Tool

!ELSEIF  "$(CFG)" == "clstub - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\Debug\dce"
# PROP Intermediate_Dir "\obj\clstub\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp4 /MTd /W3 /Gm /ZI /Od /I ".\include" /I "..\..\..\include" /I "k:\develop\include" /I "C:\Arquivos de programas\Microsoft Platform SDK\Include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "BUILDING_LBS_DLL" /D "__NOMFC" /D "_TESTE" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ntdsapi.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib alfc.lib appmngr.lib li.lib lifile.lib crypt.lib rpcstuff.lib lbstart.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libcimt.lib" /out:"..\..\..\Debug\dce\lbs.dll" /libpath:"..\..\..\lib\debug" /libpath:"k:\develop\lib\release" /libpath:"C:\Arquivos de programas\Microsoft Platform SDK\Lib"
# Begin Special Build Tool
OutDir=.\..\..\..\lib\Debug\dce
ProjDir=.
TargetPath=\DEVTREE_SHARE\devvlad\Debug\dce\lbs.dll
TargetName=lbs
SOURCE="$(InputPath)"
PostBuild_Desc=Copiando arquivos...
PostBuild_Cmds=call CopyFiles L D $(OutDir)\$(TargetName).lib 	call CopyFiles D        D     $(TargetPath)	call CopyFiles I D $(ProjDir)\Lang\Port\*.Ini Lang\Port     	call CopyFiles I D $(ProjDir)\Lang\Engl\*.Ini Lang\Engl	echo ok.
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "clstub - Win32 Release"
# Name "clstub - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Source\basecache.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\chkvers_c.c
# End Source File
# Begin Source File

SOURCE=.\Source\clbase1.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clbase2.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clbase3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clbase4.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clbase5.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\cldata.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clfield.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\CLIENT.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\CLIENTCONFIG.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\CLLBSERR.CPP
# End Source File
# Begin Source File

SOURCE=.\Source\clntfuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\cloccurr.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clsess1.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\clsess2.cpp
# End Source File
# Begin Source File

SOURCE=.\RESOURCE\clstub.rc
# ADD BASE RSC /l 0x416 /i "RESOURCE"
# ADD RSC /l 0x416 /i "RESOURCE" /i ".\RESOURCE"
# End Source File
# Begin Source File

SOURCE=.\Source\getsrvrs.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\lbsnetcl.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\lbsrpc_c.c
# End Source File
# Begin Source File

SOURCE=.\Source\opinfocl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\include\basecach.h
# End Source File
# Begin Source File

SOURCE=.\include\basecl.h
# End Source File
# Begin Source File

SOURCE=.\Include\CLIENTCONFIG.H
# End Source File
# Begin Source File

SOURCE=.\include\cllbserr.h
# End Source File
# Begin Source File

SOURCE=.\include\clntfuncs.h
# End Source File
# Begin Source File

SOURCE=.\include\datacl.h
# End Source File
# Begin Source File

SOURCE=.\include\datlstcl.h
# End Source File
# Begin Source File

SOURCE=.\include\duplicate.h
# End Source File
# Begin Source File

SOURCE=.\include\fieldcl.h
# End Source File
# Begin Source File

SOURCE=.\include\fielstcl.h
# End Source File
# Begin Source File

SOURCE=.\include\getsrvrs.h
# End Source File
# Begin Source File

SOURCE=.\include\lbsnetcl.h
# End Source File
# Begin Source File

SOURCE=.\include\MMDEFS.H
# End Source File
# Begin Source File

SOURCE=.\include\occurcl.h
# End Source File
# Begin Source File

SOURCE=.\include\opinfocl.h
# End Source File
# Begin Source File

SOURCE=.\include\SESSCL.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
