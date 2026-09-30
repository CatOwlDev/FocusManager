#define AppName "FocusManager"

#ifndef AppVersion
  #define AppVersion "1.0.0.2"
#endif

#define AppPublisher "CatOwlDev"
#define AppExeName "FocusManager.exe"

[Setup]
AppId={{B7B0E0A6-7C7D-4D54-9D72-7D9F6B3F8A31}}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#AppPublisher}

DefaultDirName={autopf}\FocusManager
DefaultGroupName=FocusManager

OutputDir=..\dist
OutputBaseFilename=FocusManager-Setup-{#AppVersion}

Compression=lzma
SolidCompression=yes

WizardStyle=modern

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

PrivilegesRequired=admin

UninstallDisplayName=FocusManager

[Files]
Source: "..\build\Release\FocusManager.exe"; \
    DestDir: "{app}"; \
    Flags: ignoreversion

[Icons]
Name: "{autoprograms}\FocusManager"; \
    Filename: "{app}\{#AppExeName}"

Name: "{autodesktop}\FocusManager"; \
    Filename: "{app}\{#AppExeName}"; \
    Tasks: desktopicon

[Tasks]
Name: "desktopicon"; \
    Description: "Создать ярлык на рабочем столе"; \
    GroupDescription: "Дополнительные ярлыки:"; \
    Flags: unchecked

[Run]
Filename: "{app}\{#AppExeName}"; \
    Description: "Запустить FocusManager"; \
    Flags: nowait postinstall skipifsilent
