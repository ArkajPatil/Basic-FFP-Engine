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
        // char *prefix = " -> " ;
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
