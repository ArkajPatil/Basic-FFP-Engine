#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <iostream>
using namespace std;
#include <fstream>

#include "SceneLoader.h"

// for scene loading fucntion
#include "external/nlohmann/json.hpp"
using json = nlohmann::json;

// global variables
std::vector<std::string> vsSavedScenes;
// variables

// local functions declarations
void loadSceneV1(Scene *scene, json &sceneData);

void saveSelectedScene(Scene *scene)
{
    if (!scene)
    {
        MessageBox(NULL, TEXT("Current scene is null."), TEXT("Scene saving error"), MB_OK);
        return;
    }
    FILE *pFile; // pointer of file

    string fileName = "assets/scenes/" + scene->sceneName + ".json";

    pFile = fopen(fileName.c_str(), "w");
    if (!pFile)
    {
        MessageBox(NULL, TEXT("File pointer creation failed."), TEXT("File I/O error"), MB_OK);
        return;
    }

    fprintf(pFile, "{\n");
    fprintf(pFile, "\t\"version\" : \"%s\",\n", "1");
    fprintf(pFile, "\t\"sceneName\" : \"%s\",\n", scene->sceneName.c_str());
    fprintf(pFile, "\t\"models\" : [\n");
    ;

    Node *tempNode = scene->head;
    while (tempNode)
    {
        fprintf(pFile, "\t\t{\n");
        fprintf(pFile, "\t\t\t\"modelType\" : \"%s\",\n", tempNode->currentModel->modelType.c_str());

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

    writeLog(">>>>> SUCCESS <<<<< :: Scene '%s' was saved to 'assets/scenes/' successfully.", scene->sceneName);
    PlaySound(TEXT("assets/sounds/Silly.wav"),
              NULL,
              SND_FILENAME | SND_ASYNC);
    MessageBox(NULL, TEXT("Scene saved successfully."), TEXT("Scene Management"), MB_OK);
}

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

void loadSelectedScene(Scene *scene, int indexOfSelectedScene, bool bFlagClear)
{
    std::string path =
        "assets/scenes/" +
        vsSavedScenes[indexOfSelectedScene] +
        ".json";

    std::ifstream file(path); // ➡️ Open the JSON file.

    if (!file.is_open())
    {
        return;
    }

    json sceneData; // ➡️ Create an empty JSON object in memory.

    file >> sceneData; // ➡️ Read the contents of the file, parse the JSON text, and store it in sceneData

    string version = sceneData["version"];

    if (bFlagClear)
    {
        // removing all models/nodes of current scene
        removeAllNodesOfScene(scene);
    }

    if (version == "1")
    {
        loadSceneV1(scene, sceneData);
    }
    PlaySound(TEXT("assets/sounds/yoooo.wav"),
              NULL,
              SND_FILENAME | SND_ASYNC);
}

void loadSceneV1(Scene *scene, json &sceneData)
{
    // creating models
    for (json &modelData : sceneData["models"])
    {
        string modelType = modelData["modelType"];

        // transformations
        Transform t;

        // translation
        auto translate = modelData["position"];
        t.translate.x = translate[0];
        t.translate.y = translate[1];
        t.translate.z = translate[2];
        // rotation
        auto rotate = modelData["rotate"];
        t.rotate.x = rotate[0];
        t.rotate.y = rotate[1];
        t.rotate.z = rotate[2];
        // scale
        auto scale = modelData["scale"];
        t.scale.x = scale[0];
        t.scale.y = scale[1];
        t.scale.z = scale[2];

        // uniform color
        auto color = modelData["color"];
        float uniformColor[3];
        uniformColor[0] = color[0];
        uniformColor[1] = color[1];
        uniformColor[2] = color[2];

        addModelToSceneWhileSceneLoading(scene, modelType, t.translate, t.rotate, t.scale, uniformColor);
    }
}

void deleteSelectedSavedScene()
{
}
