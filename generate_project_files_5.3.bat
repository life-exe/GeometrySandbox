@echo off

rem Set all paths
SET EnginePath=c:\Program Files\Epic Games\UE_5.3
SET BuildToolRelativePath=Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe
SET VersionSelector=c:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe
SET ProjectName=GeometrySandbox.uproject

devops/generate_project_files.bat "%EnginePath%" "%BuildToolRelativePath%" "%VersionSelector%" "%ProjectName%"