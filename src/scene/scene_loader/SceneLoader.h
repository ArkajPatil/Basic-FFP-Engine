#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>

// variables
extern std::vector<std::string> vsSavedScenes;

// functions declarations
void giveSavedScenes(void);
void saveSelectedScene(void);
void loadSelectedScene(void);

#endif