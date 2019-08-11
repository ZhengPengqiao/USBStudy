# Microsoft Developer Studio Generated NMAKE File, Based on CH341PAR.dsp
!IF "$(CFG)" == ""
CFG=CH341PAR - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CH341PAR - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CH341PAR - Win32 Release" && "$(CFG)" != "CH341PAR - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CH341PAR.mak" CFG="CH341PAR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CH341PAR - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CH341PAR - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CH341PAR - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CH341PAR.exe"


CLEAN :
	-@erase "$(INTDIR)\CH341PAR.obj"
	-@erase "$(INTDIR)\CH341PAR.pch"
	-@erase "$(INTDIR)\CH341PAR.res"
	-@erase "$(INTDIR)\CH341PARDlg.obj"
	-@erase "$(INTDIR)\CtrlSheet.obj"
	-@erase "$(INTDIR)\EeprPage.obj"
	-@erase "$(INTDIR)\EppPage.obj"
	-@erase "$(INTDIR)\I2CSPage.obj"
	-@erase "$(INTDIR)\LEDBTDisp.obj"
	-@erase "$(INTDIR)\MemPage.obj"
	-@erase "$(INTDIR)\OtherPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CH341PAR.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CH341PAR.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CH341PAR.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CH341PAR.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=CH341DLL.LIB /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CH341PAR.pdb" /machine:I386 /out:"$(OUTDIR)\CH341PAR.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CH341PAR.obj" \
	"$(INTDIR)\CH341PARDlg.obj" \
	"$(INTDIR)\CtrlSheet.obj" \
	"$(INTDIR)\EeprPage.obj" \
	"$(INTDIR)\EppPage.obj" \
	"$(INTDIR)\I2CSPage.obj" \
	"$(INTDIR)\LEDBTDisp.obj" \
	"$(INTDIR)\MemPage.obj" \
	"$(INTDIR)\OtherPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CH341PAR.res"

"$(OUTDIR)\CH341PAR.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CH341PAR - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CH341PAR.exe"


CLEAN :
	-@erase "$(INTDIR)\CH341PAR.obj"
	-@erase "$(INTDIR)\CH341PAR.pch"
	-@erase "$(INTDIR)\CH341PAR.res"
	-@erase "$(INTDIR)\CH341PARDlg.obj"
	-@erase "$(INTDIR)\CtrlSheet.obj"
	-@erase "$(INTDIR)\EeprPage.obj"
	-@erase "$(INTDIR)\EppPage.obj"
	-@erase "$(INTDIR)\I2CSPage.obj"
	-@erase "$(INTDIR)\LEDBTDisp.obj"
	-@erase "$(INTDIR)\MemPage.obj"
	-@erase "$(INTDIR)\OtherPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CH341PAR.exe"
	-@erase "$(OUTDIR)\CH341PAR.ilk"
	-@erase "$(OUTDIR)\CH341PAR.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CH341PAR.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CH341PAR.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CH341PAR.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=CH341DLL.LIB /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CH341PAR.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CH341PAR.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CH341PAR.obj" \
	"$(INTDIR)\CH341PARDlg.obj" \
	"$(INTDIR)\CtrlSheet.obj" \
	"$(INTDIR)\EeprPage.obj" \
	"$(INTDIR)\EppPage.obj" \
	"$(INTDIR)\I2CSPage.obj" \
	"$(INTDIR)\LEDBTDisp.obj" \
	"$(INTDIR)\MemPage.obj" \
	"$(INTDIR)\OtherPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CH341PAR.res"

"$(OUTDIR)\CH341PAR.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CH341PAR.dep")
!INCLUDE "CH341PAR.dep"
!ELSE 
!MESSAGE Warning: cannot find "CH341PAR.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CH341PAR - Win32 Release" || "$(CFG)" == "CH341PAR - Win32 Debug"
SOURCE=.\CH341PAR.cpp

"$(INTDIR)\CH341PAR.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\CH341PAR.rc

"$(INTDIR)\CH341PAR.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CH341PARDlg.cpp

"$(INTDIR)\CH341PARDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\CtrlSheet.cpp

"$(INTDIR)\CtrlSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\EeprPage.cpp

"$(INTDIR)\EeprPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\EppPage.cpp

"$(INTDIR)\EppPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\I2CSPage.cpp

"$(INTDIR)\I2CSPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\LEDBTDisp.cpp

"$(INTDIR)\LEDBTDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\MemPage.cpp

"$(INTDIR)\MemPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\OtherPage.cpp

"$(INTDIR)\OtherPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CH341PAR.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CH341PAR - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CH341PAR.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CH341PAR.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CH341PAR - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CH341PAR.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CH341PAR.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

