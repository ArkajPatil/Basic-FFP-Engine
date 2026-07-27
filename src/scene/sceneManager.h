#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene/scene.h"

#define MAX_SCENES 10

typedef struct {
    Scene *currentScene ;
    Scene *scenesArray[MAX_SCENES];
    int sceneCount;
} SceneManager ;

// variables
extern SceneManager *sceneManager ;
extern string newSceneName;

// functions declarations
void initSceneManager(void);
void initDemoScene(void);
void createScene(string sceneName);
void deleteSelectedScene(void);

#endif