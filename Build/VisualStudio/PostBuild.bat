SET outDir=%1
SET libsDir=%2

SET arg1=%libsDir%LULE_Debug\LULE_Debug_x64.dll 
SET arg2=%libsDir%LULE_Multiplatform\LULE_Multiplatform_x64.dll 
echo "OutDir & LibsDir" %outDir% %libsDir%
echo "Copy arg 1 & 2" %arg1% %arg2%

xcopy /y %arg1% %outDir%
xcopy /y %arg2% %outDir%
