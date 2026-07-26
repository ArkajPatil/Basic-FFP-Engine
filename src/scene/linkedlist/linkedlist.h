#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "scene/models/models.h"
#include "utils/my_math_library/myMath.h"

typedef struct Scene Scene;

// node struct
typedef struct Node {
    struct Node *prevNode;
    Model *currentModel;
    struct Node *nextNode;
} Node ;

// variables

// functions declarations
void insertNode(Scene *scene, Model *model);
void deleteNode(Scene *scene, Model *model);
void removeSelectedNode(Scene *scene);

void selectNextNode(Scene *scene);
void selectPreviousNode(Scene *scene);

void renderNode(Node *node);
void renderAllNodes(Scene *scene);

void addTriangleToScene(Scene *scene);
void addSquareToScene(Scene *scene);
void addPyramidToScene(Scene *scene);
void addCubeToScene(Scene *scene);
void addSphereToScene(Scene *scene);

#endif