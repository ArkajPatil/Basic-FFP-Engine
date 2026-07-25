#include <windows.h>

#include "scene/sceneManager.h"

// variables
SceneManager *sceneManager;
char newSceneName[64];

void initSceneManager(void)
{
    sceneManager = (SceneManager *)malloc(sizeof(SceneManager));
    if (sceneManager == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: SceneManager allocation failed.");
        return;
    }

    sceneManager->currentScene = NULL;
    sceneManager->sceneCount = 0;
    memset(sceneManager->scenesArray, 0, sizeof(sceneManager->scenesArray));

    writeLog(">>>>> SUCCESS <<<<< :: SceneManager allocation successfull.");
}

void initDemoScene(void)
{
    createScene("demo");
}

void createScene(char *sceneName)
{
    Scene *scene;

    scene = (Scene *)malloc(sizeof(Scene));
    if (scene == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: Scene allocation failed.");
        return;
    }

    scene->head = NULL;
    scene->tail = NULL;
    scene->selectedNode = NULL;

    if (strlen(sceneName) == 0)
    {
        snprintf(scene->sceneName, sizeof(scene->sceneName), "Scene %d", sceneManager->sceneCount + 1);
    }
    else
    {
        strncpy(scene->sceneName, sceneName, sizeof(scene->sceneName) - 1);

        scene->sceneName[sizeof(scene->sceneName) - 1] = '\0';
    }

    // adding scene into scenesArray
    if (sceneManager->sceneCount >= MAX_SCENES)
    {
        writeLog(">>>>> ERROR <<<<< :: Maximum number of scenes reached.");
        free(scene);
        return;
    }
    sceneManager->scenesArray[sceneManager->sceneCount] = scene;

    sceneManager->currentScene = scene;
    sceneManager->sceneCount += 1;
    writeLog(">>>>> SUCCESS <<<<< :: Scene '%s' allocation successfull.", scene->sceneName);
}

void deleteSelectedScene(void)
{
    Scene *scene = sceneManager->currentScene;

    removeAllNodesOfScene(scene);

    for (int i = 0; i < sceneManager->sceneCount; i++)
    {
        if (sceneManager->scenesArray[i] == scene)
        {
            for (int j = i; j < sceneManager->sceneCount - 1; j++)
            {
                sceneManager->scenesArray[j] = sceneManager->scenesArray[j + 1];
            }
            sceneManager->scenesArray[sceneManager->sceneCount - 1] = NULL;
            free(scene);
            sceneManager->sceneCount--;
            break;
        }
    }

    if (sceneManager->sceneCount > 0)
    {
        sceneManager->currentScene = sceneManager->scenesArray[0];
    }
    else
    {
        createScene("demo");
    }
}

void saveSelectedScene(void)
{
    Scene *scene = sceneManager->currentScene;
    if(!scene)
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
            tempNode->currentModel->mesh.uniformColor[2] );

        fprintf(pFile, "\t\t}");
        tempNode = tempNode->nextNode;
        if(tempNode) {
            fprintf(pFile, ",\n");
        }
    }

    fprintf(pFile, "\n\t]\n");
    fprintf(pFile, "}");
    fclose(pFile);

    MessageBox(NULL, TEXT("Scene saved successfully."), TEXT("Scene Management"), MB_OK);
}

