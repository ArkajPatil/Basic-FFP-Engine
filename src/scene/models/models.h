#ifndef MODELS_H
#define MODELS_H

#include<windows.h>
#include<gl/GL.h>

#include<iostream>
using namespace std;

#include "utils/logging_system/logger.h"
#include "utils/my_math_library/myMath.h"

typedef struct {
    GLenum drawMode;
    GLint vertexCount;

    GLfloat *vertices;
    GLfloat *perVertexColors;
    GLfloat *uniformColor;
    GLfloat *texcoords;
    GLfloat *normals;
} Mesh;  // geometry

// creating transform structure
typedef struct {
    vec3 translate;
    vec3 rotate;
    vec3 scale;
} Transform;

// creating Model structure
typedef struct {
    string modelName;
    string modelType;
    Transform transform;
    Mesh mesh;    // pointer to shared geometry
    bool bHighlightModel;
} Model;

//  char *modelType ==> [ TRIANGLE, QUAD, PYRAMID, CUBE ]

// functions
Model *createModel(string modelName, string modelType, bool bHighlightModel, vec3 translate, vec3 rotate, vec3 scale,
                   GLenum drawMode, GLint vertexCount, GLfloat *vertices,
                   GLfloat *perVertexColors, GLfloat *uniformColor, GLfloat *texcoords, GLfloat *normals);
void applyTransform(Transform *transform);
void drawModel(Model *model);
void destroyModel(Model *&model);


#endif

