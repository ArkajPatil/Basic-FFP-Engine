#include "renderLoop.h"
#include "OpenGLSetup.h"
#include "utils/logging_system/logger.h"
#include "scene/linkedlist.h"
#include "inputs/inputs.h"

// win32 headers
#include <windows.h>

// OpenGL related header file
#include <gl/GL.h>
#include<gl/GLU.h>

// local variable
// GLfloat angleCube =  0.0f;

// variables
bool bShowGrid = false;
// global screen rotation angles
float gfScreenXRotationAngle = 0.0f;
float gfScreenYRotationAngle = 0.0f;
float gfScreenZRotationAngle = 0.0f;
// global float var for scrren translation
float gfScreenXTranslation = 2.0f;
float gfScreenYTranslation = 0.0f;
float gfScreenZTranslation = -10.0f;

void display(void)
{
    // code
    //  clear OpenGL buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);

    // set it to identity matrix
    glLoadIdentity();

    // Translate cube backward
    glTranslatef(gfScreenXTranslation, gfScreenYTranslation, gfScreenZTranslation);

    glRotatef(gfScreenXRotationAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(gfScreenYRotationAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(gfScreenZRotationAngle, 0.0f, 0.0f, 1.0f);

    // grid displaying control
    if(bShowGrid){
        showGrid();
    }

    renderNode(scene->selectedNode);
}

void update(void)
{
    // code
    // angleCube += 1.0 ;
    // if(angleCube >= 360.0)
    // {
    //     angleCube -= 360.0 ;
    // }
}

void showGrid(void)
{
    glPushMatrix();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();
}

