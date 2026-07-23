#ifndef IMGUIUI_H
#define IMGUIUI_H

// functions declarations
void drawUI(void);

// local function declarations
void fSceneManagement(void);
void fModelsControls(void);
void screenRotationControls(void);
void screenTranslationControls(void);
void DrawVec3Control(const char *label, float *x, float *y, float *z);
void addVerticalSpace(float size);

#endif