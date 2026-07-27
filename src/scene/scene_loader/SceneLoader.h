#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>
#include "scene/scene.h"

// variables
extern std::vector<std::string> vsSavedScenes;

// functions declarations
void loadSelectedScene(Scene *scene, int indexOfSelectedScene);
void giveSavedScenes(void);
void saveSelectedScene(Scene *scene);

#endif