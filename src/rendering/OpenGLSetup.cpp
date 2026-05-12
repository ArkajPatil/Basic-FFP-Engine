#include "OpenGLSetup.h"
#include "utils/logging_system/logger.h"
#include "windows/Window.h"
#include "scene/linkedlist.h"
#include "scene/basic_models_data/basicModelsData.h"


// OpenGL related header file
#include <gl/GL.h>
#include<gl/GLU.h>


// OpenGL related libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// OpenGL related global varialbles
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// models declarations
Model *triangle1;
Model *square1;
Model *pyramid1;
Model *cube1;

int initialize(void)
{
    // function declaration
    void printGLInfo(void);
    void resize(int, int);
    void modelsCreation(void);

    // variables declarations
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex = 0;

    // code
    //  PIXELFORMATDESCRIPTOR initialization
    ZeroMemory((void *)&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;


    // GetDC
    ghdc = GetDC(ghwnd);
    if (ghdc == NULL)
    {
        fprintf(gpFile, "GetDC function failed\n");
        return (-1);
    }

    // Get maching pixel format index using hdc and pfd
    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
    if (iPixelFormatIndex == 0)
    {
        fprintf(gpFile, "ChoosePixelFormat failed\n");
        return (-2);
    }

    // select the pixel format of found index
    if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        fprintf(gpFile, "SetPixelFormat function failed\n");
        return (-3);
    }

    // create rendering context using hdc, pfd, & choosen pixel format index
    ghrc = wglCreateContext(ghdc);
    if (ghrc == NULL)
    {
        fprintf(gpFile, "wglCreateContext() function failed\n");
        return (-4);
    }

    // make this rendering context as current context
    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        fprintf(gpFile, "wglMakeCurrent function failed\n");
        return (-5);
    }

    // print GL info
    printGLInfo();

    // depth related code
    glShadeModel(GL_SMOOTH); //3d object show kartanna smothness cha vichar kr
    glClearDepth(1.0f); 
    glEnable(GL_DEPTH_TEST); //depth test enable kele for resterixer
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);

    // from here onwards OpenGL code starts
    // tell OpenGL to chose the color to clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background

    // warm up resize
    resize(WIN_WIDTH, WIN_HEIGHT);

    // gen models and link them to linked list
    modelsCreation();

    return (0);
}


void printGLInfo(void)
{
    // code
    // print opengl info
    fprintf(gpFile, "OpenGL Information :\n");
    fprintf(gpFile, "********************\n");
    fprintf(gpFile, "OpenGL Vendor : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFile, "OpenGL Version : %s\n", glGetString(GL_VERSION));
    fprintf(gpFile, "********************\n");
}


void resize(int width, int height)
{
    // code
    //  reinitialize height to 1
    if (height <= 0)
    {
        height = 1;
    }

    // set the viewport
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // set matrix projection mode
    glMatrixMode(GL_PROJECTION);

    // set to identity matrix
    glLoadIdentity();

    // do perspective projection
    gluPerspective(
        45.0f, // FOV-Y = Field of View Y
        (GLfloat)width / (GLfloat)height,  // Aspect ratio
        0.1f,    // near
        100.0f);  // far
}

void cleanupOpenGL(void)
{
    // function declarations
    void toggleFullScreen(void);
    void destroyModels(void);

    // destroying nodes of linkedlist
    destroyModels();

    // code
    // make hdc as current context by realizing rendering context as current context
    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    // delete the rendering context
    if (ghrc == 0)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    // release the dc
    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }
}

void modelsCreation(void)
{
    triangle1 = createModel(
        "triangle1",                            // name
        vec3{-4.0f, 2.25f, -10.0f},           // translate
        // (vec3){0.0f, 0.0f, -3.0f},           // translate
        vec3{0.0f, 0.0f, 0.0f},               // rotate
        vec3{1.0f, 1.0f, 1.0f},               // scale
        GL_TRIANGLES,                           // drawMode
        3,                                      // vertexCount
        trianglePosition,                       // position
        triangleColor,                          // per vertex colors
        NULL /*(GLfloat[]){0.0f, 0.0f, 0.0f}*/, // uniform color
        NULL,                                   // texcoords
        NULL                                    // normals
    );

    GLfloat squareColor[] = {0.7f, 0.3f, 0.6f};
    square1 = createModel(
        "square1",                     // name
        vec3{4.0f, 2.25f, -10.0f},   // translate
        vec3{0.0f, 0.0f, 0.0f},      // rotate
        vec3{1.0f, 1.0f, 1.0f},      // scale
        GL_QUADS,                      // drawMode
        4,                             // vertexCount
        squarePosition,                // position
        NULL,                          // per vertex colors
        squareColor, // uniform color
        NULL,                          // texcoords
        NULL                           // normals
    );

    GLfloat pyramidColor[] = {0.6f, 0.5f, 0.1f}; 
    pyramid1 = createModel(
        "pyramid1",                    // name
        vec3{-4.0f, -1.5f, -10.0f},  // translate
        vec3{0.0f, 0.0f, 0.0f},      // rotate
        vec3{1.0f, 1.0f, 1.0f},      // scale
        GL_TRIANGLES,                  // drawMode
        12,                            // vertexCount
        pyramidPosition,               // position
        NULL,                          // per vertex colors
        pyramidColor, // uniform color
        NULL,                          // texcoords
        NULL                           // normals
    );

    GLfloat cubeColor[] = {0.2f, 0.4f, 0.6f};
    cube1 = createModel(
        "cube1",                       // name
        vec3{4.0f, -1.5f, -10.0f},   // translate
        vec3{0.0f, 0.0f, 0.0f},      // rotate
        vec3{1.0f, 1.0f, 1.0f},      // scale
        GL_QUADS,                      // drawMode
        24,                            // vertexCount
        cubePosition,                  // position
        NULL,                          // per vertex colors
        cubeColor, // uniform color
        NULL,                          // texcoords
        NULL                           // normals
    );

    initScene();
    insertNode(triangle1);
    insertNode(square1);
    insertNode(pyramid1);
    insertNode(cube1);
}

void destroyModels(void)
{
    void destroyModel(Model *model);

    // destroying nodes of linkedlist
    if(triangle1)
    {
        deleteNode(triangle1); 
    }
    if(square1)
    {
        deleteNode(square1); 
    }
    if(cube1)
    {
        deleteNode(cube1); 
    }
    if(pyramid1)
    {
        deleteNode(pyramid1); 
    }

}

