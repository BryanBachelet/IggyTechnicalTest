@echo off
echo *********************************************************************************************************************
echo ******************************************** Clean Unreal Engine Project ********************************************
echo *********************************************************************************************************************
echo.

SET /P AREYOUSURE=Are you sure to delete the Binaries folders in your project and plugins (y/[N])?
IF /I "%AREYOUSURE%" NEQ "y" GOTO END2

echo.
echo Cleaning your project, please wait...

FOR /d /r %%d IN ("Binaries") DO @IF EXIST "%%d" rd /s /q "%%d"
del *.sln

echo.
echo Your project has been cleaned up, read the technical documentation "Reset le C++" to know how to regenerate the cpp files .
echo If there are still problems, ask a GP or GDP.
echo You can also try running the clean_intermediate_files.bat file.
echo You can also try deleting the "Saved" folder (as a last resort).

pause
:END2