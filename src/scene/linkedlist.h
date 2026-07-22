#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAX_SCENES 10

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
    char sceneName[64];
} Scene;

typedef struct {
    Scene *currentScene ;
    Scene *scenesArray[MAX_SCENES];
    int sceneCount;
} SceneManager ;

// variables
extern SceneManager *sceneManager ;
extern char newSceneName[64];

// functions declarations
void initSceneManager(void);
void initDemoScene(void);
void createScene(char *sceneName);
void deleteSelectedScene(void);

void insertNode(Model *model);
void deleteNode(Model *model);
void removeSelectedNode(void);
void removeAllNodesOfScene(Scene *scene);

void selectNextNode(void);
void selectPreviousNode(void);

void renderNode(Node *node);
void renderAllNodes(void);

void addMultiColoredTriangleToScene(void);
void addTriangleToScene(void);
void addSquareToScene(void);
void addPyramidToScene(void);
void addCubeToScene(void);
void addSphereToScene(void);

#endif