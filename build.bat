echo off

cls

echo.
echo ==============================
echo Building Basic FFP Engine...
echo ==============================

:: creating important folders
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
cl.exe /MP /c /EHsc /Isrc /Iresources ^
/Isrc/external/imgui ^
/Isrc/external/imgui/backends ^
/Fobuild\ ^
src/core/main.cpp ^
src/windows/Window.cpp ^
src/utils/logging_system/logger.cpp ^
src/utils/my_math_library/myMath.cpp ^
src/rendering/OpenGLSetup.cpp ^
src/rendering/renderLoop.cpp ^
src/scene/models/models.cpp ^
src/scene/linkedlist/linkedlist.cpp ^
src/scene/sceneManager.cpp ^
src/scene/scene_loader/SceneLoader.cpp ^
src/scene/basic_models_data/basicModelsData.cpp ^
src/inputs/inputs.cpp ^
src/gui/ImGuiLayer.cpp ^
src/gui/ImGuiUI.cpp ^
src/gui/fonts.cpp ^
src/utils/notification_manager/NotificationManager.cpp ^
src/rendering/texture/texture.cpp ^
src/rendering/texture/TextureManager.cpp

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
build/sceneManager.obj ^
build/SceneLoader.obj ^
build/basicModelsData.obj ^
build/inputs.obj ^
build/Dear_ImGui_build_Files/imgui.obj ^
build/Dear_ImGui_build_Files/imgui_draw.obj ^
build/Dear_ImGui_build_Files/imgui_tables.obj ^
build/Dear_ImGui_build_Files/imgui_widgets.obj ^
build/Dear_ImGui_build_Files/imgui_demo.obj ^
build/Dear_ImGui_build_Files/imgui_impl_win32.obj ^
build/Dear_ImGui_build_Files/imgui_impl_opengl2.obj ^
build/Dear_ImGui_build_Files/imgui_stdlib.obj ^
build/ImGuiLayer.obj ^
build/ImGuiUI.obj ^
build/NotificationManager.obj ^
build/fonts.obj ^
build/texture.obj ^
build/TextureManager.obj ^
User32.lib GDI32.lib /SUBSYSTEM:WINDOWS

echo.
echo --- Running Application ---
echo.
main.exe

echo ==============================
echo Build Finished!
echo ==============================
echo.
