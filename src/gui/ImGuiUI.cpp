#include "ImGuiUI.h"

#include "external/imgui/imgui.h"

#include "scene/models.h"
#include "scene/linkedlist.h"

#include "rendering/renderLoop.h"

// local variables
// model uniform color
int modelColorR = 0, modelColorG = 0, modelColorB = 0;

void drawUI()
{
    ImGui::Begin("Engine Controls");

    // Screen Transformations
    if (ImGui::CollapsingHeader("Screen Transformations"))
    {
        ImGui::Checkbox("Grid", &gbShowGrid);
        if (gbShowGrid)
        {
            gbShowAxis = true;
        }
        ImGui::Checkbox("Axis", &gbShowAxis);
        ImGui::Separator();
        addVerticalSpace(15.0f);

        // screen rotation
        screenRotationControls();
        addVerticalSpace(15.0f);

        // screen translation
        screenTranslationControls();
        addVerticalSpace(8.0f);
    }

    // Models control
    if (ImGui::CollapsingHeader("Models control"))
    {
        // add models
        ImGui::Text("Add a shape: ");
        ImGui::SameLine();
        if (ImGui::Button("Triangle"))
        {
            addTriangleToScene();
        }
        ImGui::SameLine();

        if (ImGui::Button("Multi-colored-triangle"))
        {
            addMultiColoredTriangleToScene();
        }

        if (ImGui::Button("Square"))
        {
            addSquareToScene();
        }
        ImGui::SameLine();

        if (ImGui::Button("Pyramid"))
        {
            addPyramidToScene();
        }
        ImGui::SameLine();

        if (ImGui::Button("Cube"))
        {
            addCubeToScene();
        }
        ImGui::SameLine();

        if (ImGui::Button("Sphere"))
        {
            addSphereToScene();
        }
        addVerticalSpace(5.0f);

        // remove models
        ImGui::Text("Remove selected model: ");
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            removeSelectedNode();
        }
        ImGui::Separator();
        addVerticalSpace(8.0f);

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

        ImGui::Text("Highlight selected model: ");
        ImGui::SameLine();
        ImGui::Checkbox("Highlight", &gbHighlightSelectedModel);

        // models displaying
        ImGui::Text("Display models: ");
        ImGui::SameLine();
        ImGui::Checkbox("Only selected", &gbDisplaySelectedModel);
        ImGui::SameLine();
        if (gbDisplaySelectedModel)
        {
            gbDisplayAllModels = false;
        }
        ImGui::Checkbox("All", &gbDisplayAllModels);
        if (gbDisplayAllModels)
        {
            gbDisplaySelectedModel = false;
        }
        ImGui::Separator();
        addVerticalSpace(8.0f);

        // coloring models
        ImGui::Text("Color the selected model");
        if (scene->selectedNode && scene->selectedNode->currentModel->mesh.uniformColor)
        {
            modelColorR = scene->selectedNode->currentModel->mesh.uniformColor[0] * 255;
            modelColorG = scene->selectedNode->currentModel->mesh.uniformColor[1] * 255;
            modelColorB = scene->selectedNode->currentModel->mesh.uniformColor[2] * 255;

            ImGui::SliderInt(" R ", &modelColorR, 0, 255, "%d");
            ImGui::SliderInt(" G ", &modelColorG, 0, 255, "%d");
            ImGui::SliderInt(" B ", &modelColorB, 0, 255, "%d");

            scene->selectedNode->currentModel->mesh.uniformColor[0] = (float)modelColorR / 255;
            scene->selectedNode->currentModel->mesh.uniformColor[1] = (float)modelColorG / 255;
            scene->selectedNode->currentModel->mesh.uniformColor[2] = (float)modelColorB / 255;
        }

        ImGui::Separator();
        addVerticalSpace(8.0f);
    }

    // models transformations
    if (ImGui::CollapsingHeader("Models transformations"))
    {
        addVerticalSpace(8.0f);
        if (scene->selectedNode)
        {
            // translation
            ImGui::Text("Model Translation");
            ImGui::SliderFloat("Translate Model in X", &scene->selectedNode->currentModel->transform.translate.x, -50.0f, 50.0f, "%.2f");
            ImGui::SliderFloat("Translate Model in Y", &scene->selectedNode->currentModel->transform.translate.y, -50.0f, 50.0f, "%.2f");
            ImGui::SliderFloat("Translate Model in Z", &scene->selectedNode->currentModel->transform.translate.z, -50.0f, 50.0f, "%.2f");

            if (ImGui::Button("Reset Translation(0,0,0)"))
            {
                scene->selectedNode->currentModel->transform.translate.x = 0.0f;
                scene->selectedNode->currentModel->transform.translate.y = 0.0f;
                scene->selectedNode->currentModel->transform.translate.z = 0.0f;
            }

            ImGui::Separator();
            addVerticalSpace(8.0f);

            // scale
            ImGui::Text("Model Scaling");
            ImGui::SliderFloat("Scale X", &scene->selectedNode->currentModel->transform.scale.x, 0.0f, 5.0f, "%.2f");
            ImGui::SliderFloat("Scale Y", &scene->selectedNode->currentModel->transform.scale.y, 0.0f, 5.0f, "%.2f");
            ImGui::SliderFloat("Scale Z", &scene->selectedNode->currentModel->transform.scale.z, 0.0f, 5.0f, "%.2f");

            if (ImGui::Button("Reset Scaling"))
            {
                scene->selectedNode->currentModel->transform.scale.x = 1.0f;
                scene->selectedNode->currentModel->transform.scale.y = 1.0f;
                scene->selectedNode->currentModel->transform.scale.z = 1.0f;
            }

            ImGui::Separator();
            addVerticalSpace(8.0f);

            // rotation
            float wheel = ImGui::GetIO().MouseWheel;

            ImGui::Text("Model Rotations (hover & control with mouse wheel)");

            ImGui::Selectable("X Rotation Angle :");
            if (ImGui::IsItemHovered())
            {
                if (wheel > 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.x >= 360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.x = 0.0f;
                    }
                }
                if (wheel < 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.x <= -360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.x = 0.0f;
                    }
                }
                scene->selectedNode->currentModel->transform.rotate.x += wheel * 5.0f;
            }
            ImGui::SameLine();
            ImGui::Text("%.0f", scene->selectedNode->currentModel->transform.rotate.x);

            ImGui::Selectable("Y Rotation Angle :");
            if (ImGui::IsItemHovered())
            {
                if (wheel > 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.y >= 360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.y = 0.0f;
                    }
                }
                if (wheel < 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.y <= -360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.y = 0.0f;
                    }
                }
                scene->selectedNode->currentModel->transform.rotate.y += wheel * 5.0f;
            }
            ImGui::SameLine();
            ImGui::Text("%.0f", scene->selectedNode->currentModel->transform.rotate.y);

            ImGui::Selectable("Z Rotation Angle :");
            if (ImGui::IsItemHovered())
            {
                if (wheel > 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.z >= 360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.z = 0.0f;
                    }
                }
                if (wheel < 0)
                {
                    if (scene->selectedNode->currentModel->transform.rotate.z <= -360.0f)
                    {
                        scene->selectedNode->currentModel->transform.rotate.z = 0.0f;
                    }
                }
                scene->selectedNode->currentModel->transform.rotate.z += wheel * 5.0f;
            }
            ImGui::SameLine();
            ImGui::Text("%.0f", scene->selectedNode->currentModel->transform.rotate.z);

            if (ImGui::Button("Reset Rotation Angles"))
            {
                scene->selectedNode->currentModel->transform.rotate.x = 0.0f;
                scene->selectedNode->currentModel->transform.rotate.y = 0.0f;
                scene->selectedNode->currentModel->transform.rotate.z = 0.0f;
            }
        }
        ImGui::Separator();
        addVerticalSpace(8.0f);
    }

    // Scenes Management
    if (ImGui::CollapsingHeader("Scenes Management"))
    {
    }

    ImGui::End();
}

void screenTranslationControls(void)
{
    // screen translation
    ImGui::Text("Screen Translation");

    ImGui::SliderFloat(
        "Translate X",
        &gfScreenXTranslation,
        -20.0f,
        20.0f,
        "%.2f");

    ImGui::SliderFloat(
        "Translate Y",
        &gfScreenYTranslation,
        -20.0f,
        20.0f,
        "%.2f");

    ImGui::SliderFloat(
        "Translate Z",
        &gfScreenZTranslation,
        -50.0f,
        50.0f,
        "%.2f");

    if (ImGui::Button("Reset Translation"))
    {
        gfScreenXTranslation = 2.0f;
        gfScreenYTranslation = 0.0f;
        gfScreenZTranslation = -10.0f;
    }
    ImGui::Separator();
}

void screenRotationControls(void)
{
    // screen rotation
    float wheel = ImGui::GetIO().MouseWheel;

    ImGui::Text("Screen Rotations (hover & control with mouse wheel)");

    ImGui::Selectable("X Rotation Angle : ");
    if (ImGui::IsItemHovered())
    {
        if (wheel > 0)
        {
            if (gfScreenXRotationAngle >= 360.0f)
            {
                gfScreenXRotationAngle = 0.0f;
            }
        }
        if (wheel < 0)
        {
            if (gfScreenXRotationAngle <= -360.0f)
            {
                gfScreenXRotationAngle = 0.0f;
            }
        }
        gfScreenXRotationAngle += wheel * 5.0f;
    }
    ImGui::SameLine();
    ImGui::Text("%.0f", gfScreenXRotationAngle);

    ImGui::Selectable("Y Rotation Angle : ");
    if (ImGui::IsItemHovered())
    {
        if (wheel > 0)
        {
            if (gfScreenYRotationAngle >= 360.0f)
            {
                gfScreenYRotationAngle = 0.0f;
            }
        }
        if (wheel < 0)
        {
            if (gfScreenYRotationAngle <= -360.0f)
            {
                gfScreenYRotationAngle = 0.0f;
            }
        }
        gfScreenYRotationAngle += wheel * 5.0f;
    }
    ImGui::SameLine();
    ImGui::Text("%.0f", gfScreenYRotationAngle);

    ImGui::Selectable("Z Rotation Angle : ");
    if (ImGui::IsItemHovered())
    {
        if (wheel > 0)
        {
            if (gfScreenZRotationAngle >= 360.0f)
            {
                gfScreenZRotationAngle = 0.0f;
            }
        }
        if (wheel < 0)
        {
            if (gfScreenZRotationAngle <= -360.0f)
            {
                gfScreenZRotationAngle = 0.0f;
            }
        }
        gfScreenZRotationAngle += wheel * 5.0f;
    }
    ImGui::SameLine();
    ImGui::Text("%.0f", gfScreenZRotationAngle);

    if (ImGui::Button("Reset Rotation Angles"))
    {
        gfScreenXRotationAngle = 20.0f;
        gfScreenYRotationAngle = -160.0f;
        gfScreenZRotationAngle = 0.0f;
    }
    ImGui::Separator();
}

void addVerticalSpace(float size)
{
    ImGui::Dummy(ImVec2(0.0f, size));
}
