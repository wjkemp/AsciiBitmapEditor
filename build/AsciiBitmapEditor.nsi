!include "MUI2.nsh"



;--------------------------------
;General

  ;Name and file
  Name "Ascii Bitmap Editor Installer"
  OutFile "asciibitmapeditor-install.exe"

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\TheNocturnalTree\AsciiBitmapEditor"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\TheNocturnalTree\AsciiBitmapEditor" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  
;--------------------------------
;Languages 
  !insertmacro MUI_LANGUAGE "English"

  
;------------------------------------------------------------------------------
;   Main Installation Section
;------------------------------------------------------------------------------
Section "Installation Files" SecInstallationFiles

    SetOutPath "$INSTDIR"
    SetShellVarContext all
       
    ; Application
	File "..\bin\release\AsciiBitmapEditor.exe"
	File "gpl-3.0.txt"

	CreateDirectory "$SMPROGRAMS\The Nocturnal Tree\Ascii Bitmap Editor"
    CreateShortcut  "$SMPROGRAMS\The Nocturnal Tree\Ascii Bitmap Editor\Ascii Bitmap Editor.lnk" $INSTDIR\AsciiBitmapEditor.exe
    CreateShortcut  "$SMPROGRAMS\The Nocturnal Tree\Ascii Bitmap Editor\Uninstall.lnk" $INSTDIR\uninstall.exe
  
    ; Qt
	File $%QTDIR%\bin\QtCore4.dll
	File $%QTDIR%\bin\QtGui4.dll
	File $%QTDIR%\bin\QtXml4.dll
      
  
    ; Store installation folder
    WriteRegStr HKCU "Software\TheNocturnalTree\AsciiBitmapEditor" "" $INSTDIR
  
    ; Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd


;------------------------------------------------------------------------------
;   Uninstaller
;------------------------------------------------------------------------------
Section "Uninstall"
  
    SetShellVarContext all  
    
    RMDir /r "$SMPROGRAMS\The Nocturnal Tree\Ascii Bitmap Editor"
    RMDir "$SMPROGRAMS\The Nocturnal Tree"
    
    ; Delete individual files
	Delete $INSTDIR\AsciiBitmapEditor.exe
	Delete $INSTDIR\QtCore4.dll
	Delete $INSTDIR\QtGui4.dll
	Delete $INSTDIR\QtXml4.dll
	Delete $INSTDIR\Uninstall.exe     
    RMDir "$INSTDIR"

    ; Delete the registry keys
    DeleteRegKey /ifempty HKCU "Software\TheNocturnalTree\AsciiBitmapEditor"
  
SectionEnd

