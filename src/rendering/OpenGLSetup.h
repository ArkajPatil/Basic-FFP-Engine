#ifndef OPENGLSETUP_H
#define OPENGLSETUP_H

#include <windows.h>
#include "scene/models.h"

// variables declarations
extern HDC ghdc;

// models declarations
Model *triangle1;
Model *square1;
Model *pyramid1;
Model *cube1;

// functions declarations
int initialize(void);
void printGLInfo(void);
void resize(int width, int height);
void cleanupOpenGL(void);

// local functions declarations
void modelsCreation(void);
void destroyModels(void);

#endif