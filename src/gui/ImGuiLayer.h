#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include <windows.h>
#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_win32.h"
#include "external/imgui/backends/imgui_impl_opengl2.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);

// functions declarattions
void initializeImGui();
void startImGuiFrame();
void renderImGui();
void cleanupImGui();

#endif