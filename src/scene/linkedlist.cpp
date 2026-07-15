#include "linkedlist.h"

#include "scene/basic_models_data/basicModelsData.h"

Scene *scene;

void initScene(void)
{
    scene = (Scene *)malloc(sizeof(Scene));
    if (scene == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: Scene allocation failed.");
        return;
    }

    scene->head = NULL;
    scene->tail = NULL;
}

void insertNode(Model *model)
{
    if (scene->head == NULL) // LL is empty i.e. instering as head node
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
        writeLog("Model: %s has been inserted as head node.", node->currentModel->modelName);
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
        writeLog("Model: %s has been appended to the linked list.", node->currentModel->modelName);
    }
}

void deleteNode(Model *model)
{
    if (scene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node, but linked list is empty.");
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
            writeLog("Node of Model: %s has been deleted successfully.", temp->currentModel->modelName);
            free(temp);
            temp = NULL;
            return;
        }
        temp = temp->nextNode;
    }
}

void selectNextNode(void)
{
    if (scene->selectedNode && scene->selectedNode->nextNode)
    {
        scene->selectedNode = scene->selectedNode->nextNode;
    }
}

void selectPreviousNode(void)
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

void renderAllNodes(void)
{
    Node *temp = scene->head;
    while (temp)
    {
        if (temp == scene->selectedNode)
        {
            Model *model = scene->selectedNode->currentModel;
            model->transform.scale = vec3{1.5f, 1.5f, 1.5f};
            drawModel(model);
            model->transform.scale = vec3{1.0f, 1.0f, 1.0f};
        }
        else
        {
            drawModel(temp->currentModel);
        }
        temp = temp->nextNode;
    }
}

void addTriangleToScene(void)
{
    // creating triangle model
    Model *triangle;
    triangle = createModel(
        "triangle",            // name
        vec3{0.0f, 0.0f, 0.0f}, // translate
        // (vec3){0.0f, 0.0f, -3.0f},           // translate
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
    insertNode(triangle);
}

void addSquareToScene(void)
{
    // creating square model
    Model *square;
    GLfloat squareColor[] = {0.7f, 0.3f, 0.6f};
    square = createModel(
        "square",                     // name
        vec3{0.0f, 0.0f, 0.0f},   // translate
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

    // inserting into linkedlist(scene)
    insertNode(square);
}


void addPyramidToScene(void)
{
    // creating pyramid model
    Model *pyramid;
    GLfloat pyramidColor[] = {0.6f, 0.5f, 0.1f}; 

    pyramid = createModel(
        "pyramid",                    // name
        vec3{0.0f, 0.0f, 0.0f},  // translate
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

    // inserting into linkedlist(scene)
    insertNode(pyramid);
}


void addCubeToScene(void)
{
    Model *cube;
    GLfloat cubeColor[] = {0.2f, 0.4f, 0.6f};
    
    cube = createModel(
        "cube",                       // name
        vec3{0.0f, 0.0f, 0.0f},   // translate
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

    // inserting into linkedlist(scene)
    insertNode(cube);
}


void addSphereToScene(void)
{
    // creating sphere model
   
    // inserting into linkedlist(scene)
    // insertNode(sphere);
}

