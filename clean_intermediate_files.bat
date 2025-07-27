@echo off
echo ******************************************************************************************************************
echo ******************************************** Clean Intermediate Files ********************************************
echo ******************************************************************************************************************
echo.

SET /P AREYOUSURE=Are you sure to delete all Intermediate and DerivedDataCache folders in your project and plugins (y/[N])?
IF /I "%AREYOUSURE%" NEQ "y" GOTO END2

echo.
echo Cleaning your project, please wait...

FOR /d /r %%d IN ("Intermediate","DerivedDataCache") DO @IF EXIST "%%d" rd /s /q "%%d"

echo.
echo Your project has been cleaned up.
echo If there are still problems, ask a GP or GDP.

pause
:END2