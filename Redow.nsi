Name "RedowSetup"
OutFile "redow-setup.exe"
RequestExecutionLevel admin
SetCompress force
SetCompressor /SOLID lzma
Unicode true
InstallDir $PROGRAMFILES\Redow


Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles


Section "Install"
    SectionIn RO
    SetOutPath "$INSTDIR"
    File /oname=redow.exe "out\build\x64-Release\redow.exe"
    File /r "bin"
    WriteUninstaller "$INSTDIR\uninstall.exe"

    nsExec::Exec 'sc create Redow binPath="$INSTDIR\redow.exe"'
    nsExec::Exec 'sc config Redow start=AUTO'
    nsExec::Exec 'sc description Redow "Yet a Windows service of Redis."'
    nsExec::Exec 'sc start Redow'
SectionEnd

Section "Uninstall"
    nsExec::Exec "sc stop Redow"
    nsExec::Exec "sc delete Redow"
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r "$INSTDIR"
SectionEnd