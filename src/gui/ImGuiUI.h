#ifndef IMGUIUI_H
#define IMGUIUI_H

#include <vector> // for giveSavedScenes()


#include "fonts.h"

// variable declarations
extern ImFont *regularFont;
extern ImFont *boldFont;
// functions declarations
void drawUI(void);

// local function declarations
void fSceneManagement(void);
void fModelTransformations(void);
void fTexturesControl(void);
void fModelsColoring(void);
void fModelsControls(void);
void fScreenTransformations(void);
void DrawVec3Control(const char *label, float *x, float *y, float *z);
void addVerticalSpace(float size);

#endif