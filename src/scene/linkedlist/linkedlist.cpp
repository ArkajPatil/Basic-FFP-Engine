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

bool removeSelectedNode(Scene *scene)
{
    if (scene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node from scene '%s', but linked list is empty.", scene->sceneName);
        return false;
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
        return true;
    }

    // deleting tail node
    if (scene->selectedNode == scene->tail)
    {
        scene->tail = scene->tail->prevNode;
        scene->tail->nextNode = NULL;
        free(scene->selectedNode);
        scene->selectedNode = scene->tail;
        return true;
    }

    // deleting middle nodes
    scene->selectedNode->prevNode->nextNode = scene->selectedNode->nextNode;
    scene->selectedNode->nextNode->prevNode = scene->selectedNode->prevNode;
    Node *temp = scene->selectedNode->nextNode;
    free(scene->selectedNode);
    scene->selectedNode = temp;

    return true;
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

void renderAllVisibleNodes(Scene *scene)
{
    Node *tempNode = scene->head;

    while (tempNode)
    {
        if (tempNode->currentModel->isVisible)
        {
            drawModel(tempNode->currentModel);
        }

        tempNode = tempNode->nextNode;
    }
}

void addSphereToScene(Scene *scene)
{
    // creating sphere model

    // inserting into linkedlist(scene)
    // insertNode(sphere);
}

void addModelToScene(Scene *scene, string modelType)
{
    Model *model;
    float uniformColor[] = {0.55f, 0.75f, 0.75f};

    GLenum drawMode;
    GLint vertexCount;
    float *position;
    float *texcoords;

    if (modelType == "TRIANGLE")
    {
        drawMode = GL_TRIANGLES;
        vertexCount = 3;
        position = trianglePosition;
        texcoords = triangleTexcoords;
    }
    else if (modelType == "QUAD")
    {
        drawMode = GL_QUADS;
        vertexCount = 4;
        position = squarePosition;
        texcoords = squareTexcoords;
    }
    else if (modelType == "PYRAMID")
    {
        drawMode = GL_TRIANGLES;
        vertexCount = 12;
        position = pyramidPosition;
        texcoords = pyramidTexcoords;
    }
    else if (modelType == "CUBE")
    {
        drawMode = GL_QUADS;
        vertexCount = 24;
        position = cubePosition;
        texcoords = cubeTexcoords;
    }
    else
    {
        return;
    }

    model = createModel(
        modelType,              // name
        modelType,              // MODEL TYPE
        false,                  // highlight model
        false,                  // isVisible
        vec3{0.0f, 0.0f, 0.0f}, // translate
        vec3{0.0f, 0.0f, 0.0f}, // rotate
        vec3{1.0f, 1.0f, 1.0f}, // scale
        drawMode,               // drawMode
        vertexCount,            // vertexCount
        position,               // position
        NULL,                   // per vertex colors
        uniformColor,           // uniform color
        true,                   // uniform coloring toggle(bool)
        texcoords,              // texcoords
        NULL                    // normals
    );

    model->mesh.texture = loadTexture("assets/textures/ninja.png");

    // inserting into linkedlist(scene)
    insertNode(scene, model);
}

void addModelToSceneWhileSceneLoading(Scene *scene, string modelType, vec3 translate, vec3 rotate, vec3 scale, float *uniformColor)
{
    Model *model;
    // float uniformColor[] = {0.55f, 0.75f, 0.75f};

    GLenum drawMode;
    GLint vertexCount;
    float *position;

    if (modelType == "TRIANGLE")
    {
        drawMode = GL_TRIANGLES;
        vertexCount = 3;
        position = trianglePosition;
    }
    else if (modelType == "QUAD")
    {
        drawMode = GL_QUADS;
        vertexCount = 4;
        position = squarePosition;
    }
    else if (modelType == "PYRAMID")
    {
        drawMode = GL_TRIANGLES;
        vertexCount = 12;
        position = pyramidPosition;
    }
    else if (modelType == "CUBE")
    {
        drawMode = GL_QUADS;
        vertexCount = 24;
        position = cubePosition;
    }
    else
    {
        return;
    }

    model = createModel(
        modelType,    // name
        modelType,    // MODEL TYPE
        false,        // highlight model
        false,        // isVisible
        translate,    // translate
        rotate,       // rotate
        scale,        // scale
        drawMode,     // drawMode
        vertexCount,  // vertexCount
        position,     // position
        NULL,         // per vertex colors
        uniformColor, // uniform color
        true,         // uniform coloring toggle(bool)
        NULL,         // texcoords
        NULL          // normals
    );

    // inserting into linkedlist(scene)
    insertNode(scene, model);
}
