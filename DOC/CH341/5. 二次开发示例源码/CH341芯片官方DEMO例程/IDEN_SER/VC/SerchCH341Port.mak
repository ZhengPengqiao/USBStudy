# Microsoft Developer Studio Generated NMAKE File, Based on SerchCH341Port.dsp
!IF "$(CFG)" == ""
CFG=SerchCH341Port - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SerchCH341Port - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SerchCH341Port - Win32 Release" && "$(CFG)" != "SerchCH341Port - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SerchCH341Port.mak" CFG="SerchCH341Port - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SerchCH341Port - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SerchCH341Port - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SerchCH341Port - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Search & Monitor CH341Ser.exe"


CLEAN :
	-@erase "$(INTDIR)\SerchCH341Port.obj"
	-@erase "$(INTDIR)\SerchCH341Port.pch"
	-@erase "$(INTDIR)\SerchCH341Port.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Search & Monitor CH341Ser.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SerchCH341Port.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SerchCH341Port.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SerchCH341Port.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Search & Monitor CH341Ser.pdb" /machine:I386 /out:"$(OUTDIR)\Search & Monitor CH341Ser.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SerchCH341Port.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SerchCH341Port.res"

"$(OUTDIR)\Search & Monitor CH341Ser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SerchCH341Port - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Search & Monitor CH341Ser.exe"


CLEAN :
	-@erase "$(INTDIR)\SerchCH341Port.obj"
	-@erase "$(INTDIR)\SerchCH341Port.pch"
	-@erase "$(INTDIR)\SerchCH341Port.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Search & Monitor CH341Ser.exe"
	-@erase "$(OUTDIR)\Search & Monitor CH341Ser.ilk"
	-@erase "$(OUTDIR)\Search & Monitor CH341Ser.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SerchCH341Port.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SerchCH341Port.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SerchCH341Port.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Search & Monitor CH341Ser.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Search & Monitor CH341Ser.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SerchCH341Port.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SerchCH341Port.res"

"$(OUTDIR)\Search & Monitor CH341Ser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SerchCH341Port.dep")
!INCLUDE "SerchCH341Port.dep"
!ELSE 
!MESSAGE Warning: cannot find "SerchCH341Port.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SerchCH341Port - Win32 Release" || "$(CFG)" == "SerchCH341Port - Win32 Debug"
SOURCE=.\SerchCH341Port.cpp

"$(INTDIR)\SerchCH341Port.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SerchCH341Port.pch"


SOURCE=.\SerchCH341Port.rc

"$(INTDIR)\SerchCH341Port.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SerchCH341Port - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SerchCH341Port.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SerchCH341Port.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SerchCH341Port - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SerchCH341Port.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SerchCH341Port.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

