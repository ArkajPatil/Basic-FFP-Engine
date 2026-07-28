#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>
#include "scene/scene.h"

// variables
extern std::vector<std::string> vsSavedScenes;

// functions declarations
void saveSelectedScene(Scene *scene);
void giveSavedScenes(void);
void loadSelectedScene(Scene *scene, int indexOfSelectedScene, bool bFlagClear);
void deleteSelectedSavedScene();


#endif