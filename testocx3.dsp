# Microsoft Developer Studio Project File - Name="testocx3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=testocx3 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testocx3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testocx3.mak" CFG="testocx3 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testocx3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "testocx3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "testocx3"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "testocx3 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "r:\win32\bin"
# PROP Intermediate_Dir "r:\intermediate\testocx3\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "testocx3 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "r:\win32\bind"
# PROP Intermediate_Dir "r:\intermediate\testocx3\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "testocx3 - Win32 Release"
# Name "testocx3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\lsv2ctl3.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\testocx.cpp
# End Source File
# Begin Source File

SOURCE=.\testocx.rc
# End Source File
# Begin Source File

SOURCE=.\testocxpages.cpp
# End Source File
# Begin Source File

SOURCE=.\testocxsheet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\lsv2ctl3.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\testocx.h
# End Source File
# Begin Source File

SOURCE=.\TestocxPages.h
# End Source File
# Begin Source File

SOURCE=.\testocxsheet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\lsv2ctrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\testocx.rc2
# End Source File
# End Group
# End Target
# End Project
# Section testocx3 : {8E12C344-8B37-11D1-A58F-0000C04372DC}
# 	0:8:Font.cpp:F:\projects\testocx\Font.cpp
# 	0:6:Font.h:F:\projects\testocx\Font.h
# 	0:10:LSV2CTRL.h:F:\projects\testocx\LSV2CTRL.h
# 	0:12:LSV2CTRL.cpp:F:\projects\testocx\LSV2CTRL.cpp
# 	2:21:DefaultSinkHeaderFile:lsv2ctrl.h
# 	2:16:DefaultSinkClass:CLSV2CTRL
# End Section
# Section testocx3 : {1B51A952-69A2-11D3-A692-0000C04372DC}
# 	2:5:Class:CLSV2ctrl
# 	2:10:HeaderFile:lsv2ctrl.h
# 	2:8:ImplFile:lsv2ctrl.cpp
# End Section
# Section testocx3 : {9C784AF0-72BB-11D1-A585-0000C04372DC}
# 	2:23:OLE Control Containment:1
# End Section
# Section testocx3 : {8E12C342-8B37-11D1-A58F-0000C04372DC}
# 	2:5:Class:CLSV2CTRL
# 	2:10:HeaderFile:lsv2ctrl.h
# 	2:8:ImplFile:lsv2ctrl.cpp
# End Section
# Section testocx3 : {56315096-E74E-4689-B57E-2CB336C258E7}
# 	2:5:Class:CLSV2ctl3
# 	2:10:HeaderFile:lsv2ctl3.h
# 	2:8:ImplFile:lsv2ctl3.cpp
# End Section
# Section testocx3 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font1.h
# 	2:8:ImplFile:font1.cpp
# End Section
# Section testocx3 : {F9EE051D-C65D-4480-8E35-76F10FAB15C6}
# 	2:21:DefaultSinkHeaderFile:lsv2ctl3.h
# 	2:16:DefaultSinkClass:CLSV2ctl3
# End Section
# Section OLE Controls
# 	{8E12C344-8B37-11D1-A58F-0000C04372DC}
# 	{1B51A954-69A2-11D3-A692-0000C04372DC}
# End Section
# Section testocx3 : {1B51A954-69A2-11D3-A692-0000C04372DC}
# 	0:8:Font.cpp:F:\projects\testocx\Font1.cpp
# 	0:12:LSV2ctrl_2.h:F:\projects\testocx\LSV2ctrl_2.h
# 	0:6:Font.h:F:\projects\testocx\Font1.h
# 	0:14:LSV2ctrl_2.cpp:F:\projects\testocx\LSV2ctrl_2.cpp
# 	2:21:DefaultSinkHeaderFile:lsv2ctrl.h
# 	2:16:DefaultSinkClass:CLSV2ctrl
# End Section
