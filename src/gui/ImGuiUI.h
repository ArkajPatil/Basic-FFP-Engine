#ifndef IMGUIUI_H
#define IMGUIUI_H

#include <vector> // for giveSavedScenes()

// variable declarations

// functions declarations
void drawUI(void);

// local function declarations
void fmodelTransformations(void);
void fSceneManagement(void);
void fModelsControls(void);
void fScreenTransformations(void);
void DrawVec3Control(const char *label, float *x, float *y, float *z);
void addVerticalSpace(float size);

#endif