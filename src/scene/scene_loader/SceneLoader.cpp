#include <windows.h>
#include <iostream>

#include "SceneLoader.h"
#include "scene/sceneManager.h"

// global variables
std::vector<std::string> vsSavedScenes;
// variables

void giveSavedScenes(void)
{
    WIN32_FIND_DATA findData;

    HANDLE hFind = FindFirstFile(TEXT("assets/scenes/*.json"), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    vsSavedScenes.clear();

    do
    {
        std::string name = findData.cFileName;

        size_t pos = name.find(".json");

        if (pos != std::string::npos)
        {
            name.erase(pos);
        }

        vsSavedScenes.push_back(name);
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}

void saveSelectedScene(void)
{
    Scene *scene = sceneManager->currentScene;
    if (!scene)
    {
        MessageBox(NULL, TEXT("Current scene is null."), TEXT("Scene saving error"), MB_OK);
        return;
    }
    FILE *pFile; // pointer of file

    char fileName[64];
    snprintf(fileName, sizeof(fileName), "assets/scenes/%s.json", scene->sceneName);

    pFile = fopen(fileName, "w");
    if (!pFile)
    {
        MessageBox(NULL, TEXT("File pointer creation failed."), TEXT("File I/O error"), MB_OK);
        return;
    }

    fprintf(pFile, "{\n");
    fprintf(pFile, "\t\"version\" : 1,\n");
    fprintf(pFile, "\t\"sceneName\" : \"%s\",\n", scene->sceneName);
    fprintf(pFile, "\t\"models\" : [\n");
    ;

    Node *tempNode = scene->head;
    while (tempNode)
    {
        fprintf(pFile, "\t\t{\n");
        fprintf(pFile, "\t\t\t\"modelType\" : \"%s\",\n", tempNode->currentModel->modelType);

        // transformations
        Transform t = tempNode->currentModel->transform;
        fprintf(pFile, "\t\t\t\"position\" : [%f, %f, %f],\n",
                t.translate.x, t.translate.y, t.translate.z);
        fprintf(pFile, "\t\t\t\"rotate\" : [%f, %f, %f],\n",
                t.rotate.x, t.rotate.y, t.rotate.z);
        fprintf(pFile, "\t\t\t\"scale\" : [%f, %f, %f],\n",
                t.scale.x, t.scale.y, t.scale.z);

        // uniform color of model
        fprintf(pFile, "\t\t\t\"color\" : [%f, %f, %f]\n",
                tempNode->currentModel->mesh.uniformColor[0],
                tempNode->currentModel->mesh.uniformColor[1],
                tempNode->currentModel->mesh.uniformColor[2]);

        fprintf(pFile, "\t\t}");
        tempNode = tempNode->nextNode;
        if (tempNode)
        {
            fprintf(pFile, ",\n");
        }
    }

    fprintf(pFile, "\n\t]\n");
    fprintf(pFile, "}");
    fclose(pFile);

    MessageBox(NULL, TEXT("Scene saved successfully."), TEXT("Scene Management"), MB_OK);
}

// void loadSelectedScene(void)
// {
//     char path[256];

//     snprintf(path,
//              sizeof(path),
//              "Assets/Scenes/%s.json",
//              savedScenes[selectedScene].c_str());

//     std::ifstream file(path);

//     if (!file.is_open())
//     {
//         return;
//     }

//     json sceneData;

//     file >> sceneData;

//     for (auto &modelData : sceneData["models"])
//     {
//         std::string modelType =
//             modelData["modelType"];
//         node->model.transform.rotate.x =
//             modelData["rotation"][0];
//         node->model.transform.scale.x =
//             modelData["scale"][0];
//         node->model.colors[0].r =
//             modelData["color"][0];
//     }

//     file.close();
// }
