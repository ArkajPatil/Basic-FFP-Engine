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
GLfloat angleCube =  0.0f;

void display(void)
{
    void modelSelection(void);  // from inputs.h

    // code
    //  clear OpenGL buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);


    // set it to identity matrix
    glLoadIdentity();

    // Translate cube backward
    glTranslatef(0.0f, 0.0f, -10.0f);

    renderNode(scene->selectedNode);
}

void update(void)
{
    // code
    angleCube += 1.0 ;
    if(angleCube >= 360.0)
    {
        angleCube -= 360.0 ;
    }
}
