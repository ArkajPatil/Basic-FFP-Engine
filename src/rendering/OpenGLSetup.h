#ifndef OPENGLSETUP_H
#define OPENGLSETUP_H

// win32 headers
#include <windows.h>

// varaibles declarations
extern HDC ghdc;

// functions declarations
int initialize(void);
void printGLInfo(void);
void resize(int width, int height);
void cleanupOpenGL(void);

#endif