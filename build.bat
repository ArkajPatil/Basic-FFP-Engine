echo off

cls

echo.
echo ==============================
echo Building Basic FFP Engine...
echo ==============================

:: creating build folder
if not exist build mkdir build
if not exist logs mkdir logs

echo.
echo --- Cleaning Old Build Files ---
if exist build\*.obj del build\*.obj
if exist build\*.exe del build\*.exe
if exist main.exe del main.exe

echo.
echo --- Compiling Source Files ---
echo.
cl.exe /c /EHsc /Isrc /Iresources /Fobuild\ ^
src/core/main.c ^
src/windows/Window.c ^
src/utils/logging_system/logger.c ^
src/utils/my_math_library/myMath.c ^
src/rendering/OpenGLSetup.c ^
src/rendering/renderLoop.c ^
src/scene/models.c ^
src/scene/linkedlist.c ^
src/scene/basic_models_data/basicModelsData.c ^
src/inputs/inputs.c

echo.
echo --- Compiling Resource Files ---
echo.
rc.exe /Isrc /Iresources src/windows/Window.rc

echo.
echo --- Linking Executable ---
echo.
link.exe ^
build/main.obj ^
build/Window.obj ^
src/windows/Window.res ^
build/logger.obj ^
build/myMath.obj ^
build/OpenGLSetup.obj ^
build/renderLoop.obj ^
build/models.obj ^
build/linkedlist.obj ^
build/basicModelsData.obj ^
build/inputs.obj ^
User32.lib GDI32.lib /SUBSYSTEM:WINDOWS

echo.
echo --- Running Application ---
echo.
main.exe

echo ==============================
echo Build Finished!
echo ==============================
echo.
