echo off

SET outDir=%1
SET libsDir=%2

xcopy /y %libsDir%\LULE_Debug\LULE_Debug_x64.dll %outDir%\
xcopy /y %libsDir%\LULE_Multiplatform\LULE_Multiplatform_x64.dll %outDir%\
