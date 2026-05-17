#include "ImGuiUI.h"

#include "external/imgui/imgui.h"

#include "scene/linkedlist.h"

void drawUI()
{
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