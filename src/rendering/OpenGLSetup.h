#ifndef OPENGLSETUP_H
#define OPENGLSETUP_H

#include <windows.h>
#include "scene/models.h"

// variables declarations
extern HDC ghdc;

// models declarations
extern Model *triangle1;
extern Model *square1;
extern Model *pyramid1;
extern Model *cube1;

// functions declarations
int initializeOpenGL(void);
void printGLInfo(void);
void resize(int width, int height);
void cleanupOpenGL(void);

// local functions declarations
void modelsCreation(void);
void destroyModels(void);

#endif