#include "renderLoop.h"
#include "OpenGLSetup.h"
#include "utils/logging_system/logger.h"

// win32 headers
#include <windows.h>

// OpenGL related header file
#include <gl/GL.h>
#include<gl/GLU.h>

// local variable
GLfloat angleCube =  0.0f;

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
    glTranslatef(0.0f, 0.0f, -8.0f);

    // Rotate Cube
    glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f);
    glRotatef(angleCube, 0.0f, 0.0f, 1.0f);

    // Cube drwing code
    glBegin(GL_QUADS);

    // front face --------------------------------------
    glColor3f(1.0f, 0.0f, 0.0f);
    // right top
    glVertex3f(1.0f, 1.0f, 1.0f);
    // left top
    glVertex3f(-1.0f, 1.0f, 1.0f);
    // left bottom
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // right bottom
    glVertex3f(1.0f, -1.0f, 1.0f);

    // right face ----------------------------------------
    glColor3f(0.0f, 1.0f, 0.0f);
    // right top
    glVertex3f(1.0f, 1.0f, -1.0f);
    // left top
    glVertex3f(1.0f, 1.0f, 1.0f);
    // left bottom
    glVertex3f(1.0f, -1.0f, 1.0f);
    // right bottom
    glVertex3f(1.0f, -1.0f, -1.0f);

    // back face --------------------------------------
    glColor3f(0.0f, 0.0f, 1.0f);
    // right top
    glVertex3f(-1.0f, 1.0f, -1.0f);
    // left top
    glVertex3f(1.0f, 1.0f, -1.0f);
    // left bottom
    glVertex3f(1.0f, -1.0f, -1.0f);
    // right bottom
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // left face --------------------------------------------
    glColor3f(0.0f, 1.0f, 1.0f);
    // right top
    glVertex3f(-1.0f, 1.0f, 1.0f);
    // left top
    glVertex3f(-1.0f, 1.0f, -1.0f);
    // left bottom
    glVertex3f(-1.0f, -1.0f, -1.0f);
    // right bottom
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // top face ()you are watching from front ---------------------
    glColor3f(1.0f, 0.0f, 1.0f);
    // right top
    glVertex3f(1.0f, 1.0f, -1.0f);
    // left top
    glVertex3f(-1.0f, 1.0f, -1.0f);
    // left bottom
    glVertex3f(-1.0f, 1.0f, 1.0f);
    // right bottom
    glVertex3f(1.0f, 1.0f, 1.0f);

    // bottom face ()you are watching from front -------------------
    glColor3f(1.0f, 1.0f, 0.0f);
    // right top
    glVertex3f(1.0f, -1.0f, -1.0f);
    // left top
    glVertex3f(-1.0f, -1.0f, -1.0f);
    // left bottom
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // right bottom
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    glEnd();

    // swap the buffers
    SwapBuffers(ghdc);
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
