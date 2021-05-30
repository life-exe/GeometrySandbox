@echo off

rem Set all paths
SET EnginePath=%~1
SET BuildToolRelativePath=%~2
SET VersionSelector=%~3
SET ProjectPath=%CD%\%~4

rem Change engine version
"%VersionSelector%" /switchversionsilent "%ProjectPath%" "%EnginePath%"

rem Generate project files
"%EnginePath%\%BuildToolRelativePath%" -projectfiles -project="%ProjectPath%" -game -progress
