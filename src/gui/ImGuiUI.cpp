#include "ImGuiUI.h"

#include "external/imgui/imgui.h"

#include "scene/linkedlist.h"
#include "rendering/renderLoop.h"

void drawUI()
{
    ImGui::Begin("Engine Controls");

    // Screen Rotation
    if (ImGui::CollapsingHeader("Screen Rotation"))
    {
        ImGui::Checkbox("Grid", &bShowGrid);
    }

    // adding or deleting shapes
    if (ImGui::CollapsingHeader("Add / Delete Shapes"))
    {
    }

    // Navigation for models
    if (ImGui::CollapsingHeader("Navigation for Models"))
    {
        ImGui::Text("Select Model: ");
        if (ImGui::Button("Previous Model"))
        {
            selectPreviousNode();
        }
        ImGui::SameLine();
        if (ImGui::Button("Next Model"))
        {
            selectNextNode();
        }
    }

    ImGui::End();
}

// ImGui::Text("Renderer Stats");

// ImGui::Separator();

// ImGui::Text("FPS: %d", 75);

// bool wireframe = false;
// ImGui::Checkbox("Wireframe", &wireframe);

// float cameraSpeed = 10.0f;
// ImGui::SliderFloat("Camera Speed", &cameraSpeed, 1.0f, 20.0f);
// float rotation = 45.0f;
// ImGui::InputFloat("Rotation", &rotation);
// if (ImGui::Button("Reload Scene"))
// {
//     // reloadScene();
// }
