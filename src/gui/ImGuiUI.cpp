#include "ImGuiUI.h"

#include "external/imgui/imgui.h"

#include "scene/linkedlist.h"
#include "rendering/renderLoop.h"

void drawUI()
{
    ImGui::Begin("Engine Controls");

    // Screen Transformations
    if (ImGui::CollapsingHeader("Screen Transformations"))
    {
        ImGui::Checkbox("Grid", &bShowGrid);
        ImGui::Separator();
        addVerticalSpace(15.0f);

        // screen rotation
        screenRotationControls();
        addVerticalSpace(15.0f);

        // screen translation
        screenTranslationControls();
        addVerticalSpace(8.0f);
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

void screenTranslationControls(void)
{
    // screen translation
    float wheel = ImGui::GetIO().MouseWheel;

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
        gfScreenXRotationAngle = 0.0f;
        gfScreenYRotationAngle = 0.0f;
        gfScreenZRotationAngle = 0.0f;
    }
    ImGui::Separator();
}

void addVerticalSpace(float size)
{
    ImGui::Dummy(ImVec2(0.0f, size));
}
