#include "linkedlist.h"

#include "scene/scene.h"
#include "scene/basic_models_data/basicModelsData.h"

void insertNode(Scene *scene, Model *model)
{
    if (scene->head == NULL) // LL is empty i.e. inserting as head node
    {
        Node *node;
        node = (Node *)malloc(sizeof(Node));
        node->prevNode = NULL;
        node->currentModel = model;
        node->nextNode = NULL;
        scene->head = node;
        scene->tail = node;
        // select this node as selected node
        if (scene->selectedNode == NULL)
        {
            scene->selectedNode = node;
        }
        writeLog("Model: %s has been inserted as head node in scene '%s'.", node->currentModel->modelName, scene->sceneName);
    }
    else // LL already available
    {
        Node *node;
        node = (Node *)malloc(sizeof(Node));
        node->prevNode = scene->tail;
        node->currentModel = model;
        node->nextNode = NULL;
        scene->tail->nextNode = node;
        scene->tail = node;
        writeLog("Model: %s has been appended to the linked list in scene '%s'.", node->currentModel->modelName, scene->sceneName);
    }
}

void deleteNode(Scene *scene, Model *model)
{
    if (scene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node from scene '%s' , but linked list is empty.", scene->sceneName);
        return;
    }

    Node *temp = scene->head;
    while (temp)
    {
        if (temp->currentModel == model)
        {
            // deleting head
            if (temp == scene->head)
            {
                // deleting the model
                if (scene->head->currentModel)
                {
                    destroyModel(scene->head->currentModel);
                }
                // breaking the links of the node
                scene->head = scene->head->nextNode;
                if (scene->head)
                {
                    scene->head->prevNode = NULL;
                }
                else // if updated head does not exist
                {
                    scene->tail = NULL;
                }
            }
            // deleting tail
            else if (temp == scene->tail)
            {
                // destroying the model
                if (scene->tail->currentModel)
                {
                    destroyModel(scene->tail->currentModel);
                }
                // breaking the links of node
                scene->tail = temp->prevNode;
                if (scene->tail)
                {
                    scene->tail->nextNode = NULL;
                }
            }
            // deleting middle nodes
            else
            {
                // destroying the model
                if (temp->currentModel)
                {
                    destroyModel(temp->currentModel);
                }
                // breaking the links of node
                temp->prevNode->nextNode = temp->nextNode;
                temp->nextNode->prevNode = temp->prevNode;
            }
            writeLog("Node of Model: %s has been deleted successfully from scene '%s'.", temp->currentModel->modelName, scene->sceneName);
            free(temp);
            temp = NULL;
            return;
        }
        temp = temp->nextNode;
    }
}

void removeSelectedNode(Scene *scene)
{
    if (scene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node from scene '%s', but linked list is empty.", scene->sceneName);
        return;
    }

    // deleting head node
    if (scene->selectedNode == scene->head)
    {
        if (scene->head->nextNode)
        {
            scene->head = scene->head->nextNode;
            scene->head->prevNode = NULL;
            free(scene->selectedNode);
            scene->selectedNode = scene->head;
        }
        else
        {
            free(scene->selectedNode);
            scene->head = NULL;
            scene->selectedNode = NULL;
        }
        return;
    }

    // deleting tail node
    if (scene->selectedNode == scene->tail)
    {
        scene->tail = scene->tail->prevNode;
        scene->tail->nextNode = NULL;
        free(scene->selectedNode);
        scene->selectedNode = scene->tail;
        return;
    }

    // deleting middle nodes
    scene->selectedNode->prevNode->nextNode = scene->selectedNode->nextNode;
    scene->selectedNode->nextNode->prevNode = scene->selectedNode->prevNode;
    Node *temp = scene->selectedNode->nextNode;
    free(scene->selectedNode);
    scene->selectedNode = temp;

    return;
}

void removeAllNodesOfScene(Scene *scene)
{
    Node *temp = scene->head;
    Node *next;

    while (temp)
    {
        next = temp->nextNode;

        destroyModel(temp->currentModel);

        temp->prevNode = NULL;
        temp->nextNode = NULL;
        free(temp);
        temp = next;
    }

    scene->head = NULL;
    scene->tail = NULL;
    scene->selectedNode = NULL;
}

void selectNextNode(Scene *scene)
{
    if (scene->selectedNode && scene->selectedNode->nextNode)
    {
        scene->selectedNode = scene->selectedNode->nextNode;
    }
}

void selectPreviousNode(Scene *scene)
{
    if (scene->selectedNode && scene->selectedNode->prevNode)
    {
        scene->selectedNode = scene->selectedNode->prevNode;
    }
}

void renderNode(Node *node)
{
    if (node)
    {
        drawModel(node->currentModel);
    }
}

void renderAllNodes(Scene *scene)
{
    Node *temp = scene->head;
    while (temp)
    {
        drawModel(temp->currentModel);
        temp = temp->nextNode;
    }
}

void addMultiColoredTriangleToScene(Scene *scene)
{
    // creating triangle model
    Model *triangle;
    triangle = createModel(
        "multi colored-triangle",               // name
        false,                                  // highlight model
        vec3{0.0f, 0.0f, 0.0f},                 // translate
        vec3{0.0f, 0.0f, 0.0f},                 // rotate
        vec3{1.0f, 1.0f, 1.0f},                 // scale
        GL_TRIANGLES,                           // drawMode
        3,                                      // vertexCount
        trianglePosition,                       // position
        triangleColor,                          // per vertex colors
        NULL /*(GLfloat[]){0.0f, 0.0f, 0.0f}*/, // uniform color
        NULL,                                   // texcoords
        NULL                                    // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, triangle);
}

void addTriangleToScene(Scene *scene)
{
    // creating triangle model
    Model *triangle;
    GLfloat uniformTriangleColor[] = {0.65f, 0.65f, 0.625f};
    triangle = createModel(
        "triangle",             // name
        false,                  // highlight model
        vec3{0.0f, 0.0f, 0.0f}, // translate
        vec3{0.0f, 0.0f, 0.0f}, // rotate
        vec3{1.0f, 1.0f, 1.0f}, // scale
        GL_TRIANGLES,           // drawMode
        3,                      // vertexCount
        trianglePosition,       // position
        NULL,                   // per vertex colors
        uniformTriangleColor,   // uniform color
        NULL,                   // texcoords
        NULL                    // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, triangle);
}

void addSquareToScene(Scene *scene)
{
    // creating square model
    Model *square;
    GLfloat squareColor[] = {0.7f, 0.3f, 0.6f};
    square = createModel(
        "square",               // name
        false,                  // highlight model
        vec3{0.0f, 0.0f, 0.0f}, // translate
        vec3{0.0f, 0.0f, 0.0f}, // rotate
        vec3{1.0f, 1.0f, 1.0f}, // scale
        GL_QUADS,               // drawMode
        4,                      // vertexCount
        squarePosition,         // position
        NULL,                   // per vertex colors
        squareColor,            // uniform color
        NULL,                   // texcoords
        NULL                    // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, square);
}

void addPyramidToScene(Scene *scene)
{
    // creating pyramid model
    Model *pyramid;
    GLfloat pyramidColor[] = {0.6f, 0.5f, 0.1f};

    pyramid = createModel(
        "pyramid",              // name
        false,                  // highlight model
        vec3{0.0f, 0.0f, 0.0f}, // translate
        vec3{0.0f, 0.0f, 0.0f}, // rotate
        vec3{1.0f, 1.0f, 1.0f}, // scale
        GL_TRIANGLES,           // drawMode
        12,                     // vertexCount
        pyramidPosition,        // position
        NULL,                   // per vertex colors
        pyramidColor,           // uniform color
        NULL,                   // texcoords
        NULL                    // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, pyramid);
}

void addCubeToScene(Scene *scene)
{
    Model *cube;
    GLfloat cubeColor[] = {0.2f, 0.4f, 0.6f};

    cube = createModel(
        "cube",                 // name
        false,                  // highlight model
        vec3{0.0f, 0.0f, 0.0f}, // translate
        vec3{0.0f, 0.0f, 0.0f}, // rotate
        vec3{1.0f, 1.0f, 1.0f}, // scale
        GL_QUADS,               // drawMode
        24,                     // vertexCount
        cubePosition,           // position
        NULL,                   // per vertex colors
        cubeColor,              // uniform color
        NULL,                   // texcoords
        NULL                    // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, cube);
}

void addSphereToScene(Scene *scene)
{
    // creating sphere model

    // inserting into linkedlist(scene)
    // insertNode(sphere);
}
