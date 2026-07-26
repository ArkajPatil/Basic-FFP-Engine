#ifndef IMGUIUI_H
#define IMGUIUI_H

#include <vector> // for giveSavedScenes()

// functions declarations
void drawUI(void);

// local function declarations
std::vector<std::string> giveSavedScenes(void);
void fmodelTransformations(void);
void fSceneManagement(void);
void fModelsControls(void);
void screenRotationControls(void);
void screenTranslationControls(void);
void DrawVec3Control(const char *label, float *x, float *y, float *z);
void addVerticalSpace(float size);

#endif