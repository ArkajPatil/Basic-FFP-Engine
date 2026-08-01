#include <windows.h>

#include "scene/sceneManager.h"
#include <string>
#include "utils/notification_manager/NotificationManager.h"

// variables
SceneManager *sceneManager;
string newSceneName;

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

void createScene(string sceneName)
{
    Scene *scene = new Scene;
    // scene = (Scene *)malloc(sizeof(Scene));

    if (scene == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: Scene allocation failed.");
        return;
    }

    scene->head = NULL;
    scene->tail = NULL;
    scene->selectedNode = NULL;

    // giving name to scene
    if (sceneName.empty())
    {
        short int sceneCount = sceneManager->sceneCount + 1;
        scene->sceneName = "Scene " + std::to_string(sceneCount);
    }
    else
    {
        scene->sceneName = sceneName;
    }

    // adding scene into scenesArray
    if (sceneManager->sceneCount >= MAX_SCENES)
    {
        writeLog(">>>>> ERROR <<<<< :: Maximum number of scenes reached.");
        createNotification("Maximum number of scenes reached.", "error");
        free(scene);
        return;
    }
    sceneManager->scenesArray[sceneManager->sceneCount] = scene;

    sceneManager->currentScene = scene;
    sceneManager->sceneCount += 1;
    writeLog(">>>>> SUCCESS <<<<< :: Scene '%s' allocation successfull.", scene->sceneName);
    string msg = "Scene: '" + scene->sceneName + "' created";
    createNotification(msg);
}

void deleteSelectedScene(void)
{
    Scene *scene = sceneManager->currentScene;
    string msg = "Scene '" +  scene->sceneName + "' deleted";

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

    createNotification(msg, "delete");

    if (sceneManager->sceneCount > 0)
    {
        sceneManager->currentScene = sceneManager->scenesArray[0];
    }
    else
    {
        createScene("demo");
    }
}

