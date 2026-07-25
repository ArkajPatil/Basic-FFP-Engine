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
extern char newSceneName[64];

// functions declarations
void initSceneManager(void);
void initDemoScene(void);
void createScene(char *sceneName);
void deleteSelectedScene(void);
void removeAllNodesOfScene(Scene *scene);
void saveSelectedScene(void);

#endif