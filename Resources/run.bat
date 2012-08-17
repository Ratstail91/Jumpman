@ECHO OFF
:lm
CALL "Jumpman.exe"
ECHO Exit code: %ERRORLEVEL%
ECHO Press any key to restart . . . 
PAUSE > NUL
GOTO lm
