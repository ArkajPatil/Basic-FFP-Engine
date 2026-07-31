#include "ImGuiLayer.h"

#include "windows/Window.h"
#include "utils/logging_system/logger.h"

#include "fonts.h"
#include "ImGuiUI.h"

void initializeImGui()
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // fonts
    boldFont = io.Fonts->AddFontFromFileTTF(
    "assets/fonts/Roboto-Bold.ttf",
    25.0f);

    regularFont = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Roboto-Regular.ttf",
        20.0f);

    io.FontDefault = regularFont;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(ghwnd);
    ImGui_ImplOpenGL2_Init();

    writeLog(">>>>> SUCCESS <<<<< :: ImGui Initialization is done.");
}

void startImGuiFrame()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    drawUI();
}

void renderImGui()
{
    ImGui::Render();

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void cleanupImGui()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

    writeLog("Cleaning ImGui is done.");
}
