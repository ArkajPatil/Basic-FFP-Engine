#include "ImGuiLayer.h"

#include "windows/Window.h"
#include "utils/logging_system/logger.h"

#include "scene/linkedlist.h"

void initializeImGui()
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(ghwnd);
    ImGui_ImplOpenGL2_Init();

    writeLog("ImGui Initialization is done.");
}

void startImGuiFrame()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    ImGui::Begin("Model Selector");

    if (ImGui::Button("Previous Model"))
    {
        selectPreviousNode();
    }

    if (ImGui::Button("Next Model"))
    {
        selectNextNode();
    }

    ImGui::End();
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
