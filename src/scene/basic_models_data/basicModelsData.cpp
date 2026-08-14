#include "basicModelsData.h"

// position arrays for basic shapes
float trianglePosition[] = {
    0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

float squarePosition[] = {
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

float cubePosition[] = {
    // front face -----------------------------------------
    // right top
    1.0f, 1.0f, 1.0f,
    // left top
    -1.0f, 1.0f, 1.0f,
    // left bottom
    -1.0f, -1.0f, 1.0f,
    // right bottom
    1.0f, -1.0f, 1.0f,

    // right face ----------------------------------------
    // right top
    1.0f, 1.0f, -1.0f,
    // left top
    1.0f, 1.0f, 1.0f,
    // left bottom
    1.0f, -1.0f, 1.0f,
    // right bottom
    1.0f, -1.0f, -1.0f,

    // back face --------------------------------------
    // right top
    -1.0f, 1.0f, -1.0f,
    // left top
    1.0f, 1.0f, -1.0f,
    // left bottom
    1.0f, -1.0f, -1.0f,
    // right bottom
    -1.0f, -1.0f, -1.0f,

    // left face --------------------------------------------
    // right top
    -1.0f, 1.0f, 1.0f,
    // left top
    -1.0f, 1.0f, -1.0f,
    // left bottom
    -1.0f, -1.0f, -1.0f,
    // right bottom
    -1.0f, -1.0f, 1.0f,

    // top face ()you are watching from front ---------------------
    // right top
    1.0f, 1.0f, -1.0f,
    // left top
    -1.0f, 1.0f, -1.0f,
    // left bottom
    -1.0f, 1.0f, 1.0f,
    // right bottom
    1.0f, 1.0f, 1.0f,

    // bottom face ()you are watching from front -------------------
    // right top
    1.0f, -1.0f, -1.0f,
    // left top
    -1.0f, -1.0f, -1.0f,
    // left bottom
    -1.0f, -1.0f, 1.0f,
    // right bottom
    1.0f, -1.0f, 1.0f
};

float pyramidPosition[] = {
    // apex
    0.0f, 1.0f, 0.0f,
    // left bottom
    -1.0f, -1.0f, 1.0f,
    // right bottom
    1.0f, -1.0f, 1.0f,

    // right face
    // apex
    0.0f, 1.0f, 0.0f,
    // left bottom
    1.0f, -1.0f, 1.0f,
    // right bottom
    1.0f, -1.0f, -1.0f,

    // back face
    // apex
    0.0f, 1.0f, 0.0f,
    // left bottom
    1.0f, -1.0f, -1.0f,
    // right bottom
    -1.0f, -1.0f, -1.0f,

    // left face
    // apex
    0.0f, 1.0f, 0.0f,
    // left bottom
    -1.0f, -1.0f, -1.0f,
    // right bottom
    -1.0f, -1.0f, 1.0f
};

// texture coordinates arrays
float triangleTexcoords[] = {
    0.5f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 0.0f
};

float squareTexcoords[] = {
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

float cubeTexcoords[] = {
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

float pyramidTexcoords[] = {
    0.5f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 0.0f,

    0.5f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 0.0f,

    0.5f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 0.0f,

    0.5f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 0.0f
};
