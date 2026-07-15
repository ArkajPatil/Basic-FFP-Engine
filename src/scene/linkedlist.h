#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "models.h"
#include "utils/my_math_library/myMath.h"

// node struct
typedef struct Node {
    struct Node *prevNode;
    Model *currentModel;
    struct Node *nextNode;
} Node ;

// scene struct
typedef struct {
    Node *head;
    Node *tail;
    Node *selectedNode;
} Scene;

extern Scene *scene;

// functions declarations
void initScene(void);
void insertNode(Model *model);
void deleteNode(Model *model);
void removeSelectedNode(void);
void renderAllNodes(void);
void selectNextNode(void);
void selectPreviousNode(void);
void renderNode(Node *node);
void renderAllNodes(void);
void addTriangleToScene(void);
void addSquareToScene(void);
void addPyramidToScene(void);
void addCubeToScene(void);
void addSphereToScene(void);

#endif