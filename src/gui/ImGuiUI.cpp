#include "external/imgui/imgui.h"
#include "external/imgui/imgui_stdlib.h"
#include "ImGuiUI.h"

#include "scene/models/models.h"
#include "scene/linkedlist/linkedlist.h"
#include "scene/sceneManager.h"
#include "rendering/renderLoop.h"
#include "windows/Window.h"
#include "scene/scene_loader/SceneLoader.h"

// local variables
// model uniform color
int modelColorR = 0, modelColorG = 0, modelColorB = 0;
float uniformModelScale = 1.0f;
// fonts
ImFont *gLargeFont = nullptr; // global large font

void drawUI()
{
    ImGui::Begin("Engine Controls");

    // Screen Transformations
    if (ImGui::CollapsingHeader("Screen Transformations"))
    {
        fScreenTransformations();
    }

    // Models control
    if (ImGui::CollapsingHeader("Models control"))
    {
        fModelsControls();
    }

    // models transformations
    if (ImGui::CollapsingHeader("Model Transformations"))
    {
        fmodelTransformations();
    }
    // Scenes Management
    if (ImGui::CollapsingHeader("Scenes Management"))
    {
        fSceneManagement();
    }

    ImGui::End();
}

void fSceneManagement(void)
{

    ImGui::Text("Create Scene: ");

    ImGui::InputText("Scene Name", &newSceneName);

    if (ImGui::Button("Create Scene"))
    {
        createScene(newSceneName);
    }

    addVerticalSpace(5.0f);
    ImGui::Text("All Scenes: ");
    for (int i = 0; i < sceneManager->sceneCount; i++)
    {
        bool isSelected = (sceneManager->currentScene == sceneManager->scenesArray[i]);
        std::string sSceneName = sceneManager->scenesArray[i]->sceneName;
        sSceneName = " -> " + sSceneName;
        if (ImGui::Selectable(sSceneName.c_str(), isSelected))
        {
            sceneManager->currentScene = sceneManager->scenesArray[i];
        }
    }

    addVerticalSpace(6.0f);
    ImGui::Text("Save selected scene: ");
    ImGui::SameLine();
    if (ImGui::Button("Save Scene"))
    {
        saveSelectedScene(sceneManager->currentScene);
        giveSavedScenes();
    }

    addVerticalSpace(5.0f);
    ImGui::Text("Delete selected scene: ");
    ImGui::SameLine();
    if (ImGui::Button("Delete Scene"))
    {
        deleteSelectedScene();
    }
    addVerticalSpace(1.0f);
    ImGui::Separator();
    addVerticalSpace(6.0f);

    // loading a scene from 'assets/scenes'
    ImGui::Text("--->> Loading Scene");

    ImGui::Text("Saved Scenes:");

    static short int iSelectedScene = 0;
    for (int i = 0; i < vsSavedScenes.size(); i++)
    {
        bool isSelected = (iSelectedScene == i);
        if (ImGui::Selectable(vsSavedScenes[i].c_str(), isSelected))
        {
            iSelectedScene = i;
        }
    }

    if (ImGui::Button("Load selected Scene"))
    {
        loadSelectedScene(sceneManager->currentScene, iSelectedScene, true);
    }
    if (ImGui::Button("Append selected Scene"))
    {
        loadSelectedScene(sceneManager->currentScene, iSelectedScene, false);
    }
    // saved scene deletion logic
    if (ImGui::Button("Delete selected saved Scene"))
    {
        ImGui::OpenPopup("Delete Scene ?");
    }
    if (ImGui::BeginPopupModal("Delete Scene ?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::TextColored(ImVec4(1, 0.7f, 0.7f, 1), "Are you sure you want to delete this scene '%s' ?", vsSavedScenes[iSelectedScene].c_str());
        ImGui::Separator();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
        ImGui::Text("This action cannot be undone.");
        if (ImGui::Button("Delete", ImVec2(120, 0)))
        {
            deleteSelectedSavedScene(iSelectedScene);
            giveSavedScenes();
            ImGui::CloseCurrentPopup();
        }
        ImGui::PopStyleColor();

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void fmodelTransformations(void)
{
    if (sceneManager->currentScene->selectedNode)
    {
        Model *model = sceneManager->currentScene->selectedNode->currentModel;

        // model position controls
        DrawVec3Control("Position", &model->transform.translate.x, &model->transform.translate.y, &model->transform.translate.z);
        if (ImGui::Button("Reset Translation(0,0,0)"))
        {
            sceneManager->currentScene->selectedNode->currentModel->transform.translate.x = 0.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.translate.y = 0.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.translate.z = 0.0f;
        }
        ImGui::Separator();

        // model rotation controls
        DrawVec3Control("Rotation", &model->transform.rotate.x, &model->transform.rotate.y, &model->transform.rotate.z);
        if (ImGui::Button("Reset Rotation(models) Angles"))
        {
            sceneManager->currentScene->selectedNode->currentModel->transform.rotate.x = 0.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.rotate.y = 0.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.rotate.z = 0.0f;
        }
        ImGui::Separator();

        // model scaling controls
        DrawVec3Control("Scale", &model->transform.scale.x, &model->transform.scale.y, &model->transform.scale.z);
        ImGui::Text("Scale in all axis: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(150);
        if (ImGui::DragFloat("##Model Scaling", &uniformModelScale, 0.1f))
        {
            model->transform.scale.x = uniformModelScale;
            model->transform.scale.y = uniformModelScale;
            model->transform.scale.z = uniformModelScale;
        }
        ImGui::PopItemWidth();

        if (ImGui::Button("Reset Scaling"))
        {
            sceneManager->currentScene->selectedNode->currentModel->transform.scale.x = 1.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.scale.y = 1.0f;
            sceneManager->currentScene->selectedNode->currentModel->transform.scale.z = 1.0f;
            uniformModelScale = 1.0f;
        }
        ImGui::Separator();
        addVerticalSpace(7.0f);
    }
}

void fModelsControls(void)
{
    // add models
    ImGui::Text("Add a shape: ");
    ImGui::SameLine();
    if (ImGui::Button("Triangle"))
    {
        addModelToScene(sceneManager->currentScene, "TRIANGLE");
    }
    ImGui::SameLine();

    if (ImGui::Button("Square"))
    {
        addModelToScene(sceneManager->currentScene, "QUAD");
    }
    ImGui::SameLine();

    if (ImGui::Button("Pyramid"))
    {
        addModelToScene(sceneManager->currentScene, "PYRAMID");
    }
    ImGui::SameLine();

    if (ImGui::Button("Cube"))
    {
        addModelToScene(sceneManager->currentScene, "CUBE");
    }

    if (ImGui::Button("Sphere"))
    {
        addSphereToScene(sceneManager->currentScene);
    }
    addVerticalSpace(5.0f);

    // remove models
    ImGui::Text("Remove selected model: ");
    ImGui::SameLine();
    if (ImGui::Button("Delete"))
    {
        removeSelectedNode(sceneManager->currentScene);
    }
    ImGui::Separator();
    addVerticalSpace(6.0f);

    ImGui::Text("Select Model: ");
    if (ImGui::Button("Previous Model"))
    {
        selectPreviousNode(sceneManager->currentScene);
    }
    ImGui::SameLine();
    if (ImGui::Button("Next Model"))
    {
        selectNextNode(sceneManager->currentScene);
    }

    ImGui::Text("Highlight selected model: ");
    ImGui::SameLine();
    ImGui::Checkbox("Highlight", &gbHighlightSelectedModel);
    ImGui::Text("Visibility of currently selected model: ");
    
    if (sceneManager->currentScene->selectedNode)
    {
        ImGui::SameLine();
        ImGui::Checkbox("Visible", &sceneManager->currentScene->selectedNode->currentModel->isVisible);
    }
    addVerticalSpace(3.0f);
    ImGui::Separator();
    addVerticalSpace(6.0f);
    
    // models displaying
    ImGui::Text("Display models: ");
    // ImGui::SameLine();

    ImGui::Checkbox("Only currently selected", &gbDisplaySelectedModel);
    if (gbDisplaySelectedModel)
    {
        gbDisplayAllModels = false;
        gbDisplayAllVisibleModels = false;
    }

    ImGui::Checkbox("All visible models", &gbDisplayAllVisibleModels);
    if (gbDisplayAllVisibleModels)
    {
        gbDisplaySelectedModel = false;
        gbDisplayAllModels = false;
    }

    ImGui::Checkbox("All models in scene", &gbDisplayAllModels);
    if (gbDisplayAllModels)
    {
        gbDisplaySelectedModel = false;
        gbDisplayAllVisibleModels = false;
    }
    ImGui::Separator();
    addVerticalSpace(8.0f);

    // coloring models
    ImGui::Text("Color the selected model");
    if (sceneManager->currentScene->selectedNode && sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor)
    {
        modelColorR = sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[0] * 255;
        modelColorG = sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[1] * 255;
        modelColorB = sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[2] * 255;

        ImGui::SliderInt(" R ", &modelColorR, 0, 255, "%d");
        ImGui::SliderInt(" G ", &modelColorG, 0, 255, "%d");
        ImGui::SliderInt(" B ", &modelColorB, 0, 255, "%d");

        sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[0] = (float)modelColorR / 255;
        sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[1] = (float)modelColorG / 255;
        sceneManager->currentScene->selectedNode->currentModel->mesh.uniformColor[2] = (float)modelColorB / 255;
    }

    ImGui::Separator();
    addVerticalSpace(8.0f);
}

void fScreenTransformations(void)
{
    ImGui::Checkbox("Grid", &gbShowGrid);
    if (gbShowGrid)
    {
        gbShowAxis = true;
    }
    ImGui::Checkbox("Axis", &gbShowAxis);
    ImGui::Separator();

    // screen translation
    DrawVec3Control("Screen Translations", &gfScreenXTranslation, &gfScreenYTranslation, &gfScreenZTranslation);
    if (ImGui::Button("Reset Translation"))
    {
        gfScreenXTranslation = 2.0f;
        gfScreenYTranslation = 0.0f;
        gfScreenZTranslation = -10.0f;
    }
    ImGui::Separator();

    // screen rotation
    DrawVec3Control("Screen Rotation", &gfScreenXRotationAngle, &gfScreenYRotationAngle, &gfScreenZRotationAngle);
    if (ImGui::Button("Reset Rotation Angles"))
    {
        gfScreenXRotationAngle = 25.0f;
        gfScreenYRotationAngle = 0.0f;
        gfScreenZRotationAngle = 0.0f;
    }
    ImGui::Separator();
    addVerticalSpace(5.0f);
}

void DrawVec3Control(const char *label, float *x, float *y, float *z)
{
    // if (ImGui::TreeNode(label))
    // {
    addVerticalSpace(6.0f);
    ImGui::Text(" ");
    ImGui::SameLine(10);
    ImGui::Text("--->> %s", label);

    ImGui::PushItemWidth(70);

    ImGui::Text(" ");
    ImGui::SameLine(20);

    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::DragFloat(("##X" + std::string(label)).c_str(), x, 0.1f);

    ImGui::SameLine(130);

    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::DragFloat(("##Y" + std::string(label)).c_str(), y, 0.1f);

    ImGui::SameLine(250);

    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::DragFloat(("##Z" + std::string(label)).c_str(), z, 0.1f);

    ImGui::PopItemWidth();
    // ImGui::TreePop();

    addVerticalSpace(6.0f);
}

void addVerticalSpace(float size)
{
    ImGui::Dummy(ImVec2(0.0f, size));
}
