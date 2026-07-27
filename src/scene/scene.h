#ifndef SCENE_H
#define SCENE_H

#include "scene/linkedlist/linkedlist.h"

// scene struct
typedef struct Scene {
    Node *head;
    Node *tail;
    Node *selectedNode;
    string sceneName;
} Scene;

#endif