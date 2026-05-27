#include "ImGuiUI.h"

#include "external/imgui/imgui.h"

#include "scene/linkedlist.h"

void drawUI()
{
    // ImGui::Begin("FFP Engine");

    // if (ImGui::Button("Previous Model"))
    // {
    //     selectPreviousNode();
    // }

    // if (ImGui::Button("Next Model"))
    // {
    //     selectNextNode();
    // }

    // ImGui::End();

    ImGui::Begin("Engine Debug");

    ImGui::Text("Renderer Stats");

    ImGui::Separator();

    ImGui::Text("FPS: %d", 75);

    bool wireframe = false;
    ImGui::Checkbox("Wireframe", &wireframe);

    float cameraSpeed = 10.0f;
    ImGui::SliderFloat("Camera Speed", &cameraSpeed, 1.0f, 20.0f);
float rotation = 45.0f; ImGui::InputFloat( "Rotation", &rotation );
    if (ImGui::Button("Reload Scene"))
    {
        // reloadScene();
    }

    ImGui::End();
}

