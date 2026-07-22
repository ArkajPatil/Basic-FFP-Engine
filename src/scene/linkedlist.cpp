#include "linkedlist.h"

#include "scene/basic_models_data/basicModelsData.h"

SceneManager *sceneManager;
char newSceneName[64];

void initSceneManager(void)
{
    sceneManager = (SceneManager *)malloc(sizeof(SceneManager));
    if (sceneManager == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: SceneManager allocation failed.");
        return;
    }

    sceneManager->currentScene = NULL;
    sceneManager->sceneCount = 0;
    memset(sceneManager->scenesArray, 0, sizeof(sceneManager->scenesArray));

    writeLog(">>>>> SUCCESS <<<<< :: SceneManager allocation successfull.");
}

void initDemoScene(void)
{
    createScene("demo");
}

void createScene(char *sceneName)
{
    Scene *scene;

    scene = (Scene *)malloc(sizeof(Scene));
    if (scene == NULL)
    {
        writeLog(">>>>> FATAL <<<<< :: Scene allocation failed.");
        return;
    }

    scene->head = NULL;
    scene->tail = NULL;
    scene->selectedNode = NULL;

    if (strlen(sceneName) == 0)
    {
        snprintf(scene->sceneName, sizeof(scene->sceneName), "Scene %d", sceneManager->sceneCount + 1);
    }
    else
    {
        strncpy(scene->sceneName, sceneName, sizeof(scene->sceneName) - 1);

        scene->sceneName[sizeof(scene->sceneName) - 1] = '\0';
    }

    // adding scene into scenesArray
    if (sceneManager->sceneCount >= MAX_SCENES)
    {
        writeLog(">>>>> ERROR <<<<< :: Maximum number of scenes reached.");
        free(scene);
        return;
    }
    sceneManager->scenesArray[sceneManager->sceneCount] = scene;

    sceneManager->currentScene = scene;
    sceneManager->sceneCount += 1;
    writeLog(">>>>> SUCCESS <<<<< :: Scene '%s' allocation successfull.", scene->sceneName);
}

void deleteScene(void)
{
}

void insertNode(Model *model)
{
    if (sceneManager->currentScene->head == NULL) // LL is empty i.e. inserting as head node
    {
        Node *node;
        node = (Node *)malloc(sizeof(Node));
        node->prevNode = NULL;
        node->currentModel = model;
        node->nextNode = NULL;
        sceneManager->currentScene->head = node;
        sceneManager->currentScene->tail = node;
        // select this node as selected node
        if (sceneManager->currentScene->selectedNode == NULL)
        {
            sceneManager->currentScene->selectedNode = node;
        }
        writeLog("Model: %s has been inserted as head node in scene '%s'.", node->currentModel->modelName, sceneManager->currentScene->sceneName);
    }
    else // LL already available
    {
        Node *node;
        node = (Node *)malloc(sizeof(Node));
        node->prevNode = sceneManager->currentScene->tail;
        node->currentModel = model;
        node->nextNode = NULL;
        sceneManager->currentScene->tail->nextNode = node;
        sceneManager->currentScene->tail = node;
        writeLog("Model: %s has been appended to the linked list in scene '%s'.", node->currentModel->modelName, sceneManager->currentScene->sceneName);
    }
}

void deleteNode(Model *model)
{
    if (sceneManager->currentScene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node from scene '%s' , but linked list is empty.", sceneManager->currentScene->sceneName);
        return;
    }

    Node *temp = sceneManager->currentScene->head;
    while (temp)
    {
        if (temp->currentModel == model)
        {
            // deleting head
            if (temp == sceneManager->currentScene->head)
            {
                // deleting the model
                if (sceneManager->currentScene->head->currentModel)
                {
                    destroyModel(sceneManager->currentScene->head->currentModel);
                }
                // breaking the links of the node
                sceneManager->currentScene->head = sceneManager->currentScene->head->nextNode;
                if (sceneManager->currentScene->head)
                {
                    sceneManager->currentScene->head->prevNode = NULL;
                }
                else // if updated head does not exist
                {
                    sceneManager->currentScene->tail = NULL;
                }
            }
            // deleting tail
            else if (temp == sceneManager->currentScene->tail)
            {
                // destroying the model
                if (sceneManager->currentScene->tail->currentModel)
                {
                    destroyModel(sceneManager->currentScene->tail->currentModel);
                }
                // breaking the links of node
                sceneManager->currentScene->tail = temp->prevNode;
                if (sceneManager->currentScene->tail)
                {
                    sceneManager->currentScene->tail->nextNode = NULL;
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
            writeLog("Node of Model: %s has been deleted successfully from scene '%s'.", temp->currentModel->modelName, sceneManager->currentScene->sceneName);
            free(temp);
            temp = NULL;
            return;
        }
        temp = temp->nextNode;
    }
}

void removeSelectedNode(void)
{
    if (sceneManager->currentScene->head == NULL)
    {
        writeLog(">>>>> ERROR <<<<< :: You tried to delete node from scene '%s', but linked list is empty.", sceneManager->currentScene->sceneName);
        return;
    }

    // deleting head node
    if (sceneManager->currentScene->selectedNode == sceneManager->currentScene->head)
    {
        if (sceneManager->currentScene->head->nextNode)
        {
            sceneManager->currentScene->head = sceneManager->currentScene->head->nextNode;
            sceneManager->currentScene->head->prevNode = NULL;
            free(sceneManager->currentScene->selectedNode);
            sceneManager->currentScene->selectedNode = sceneManager->currentScene->head;
        }
        else
        {
            free(sceneManager->currentScene->selectedNode);
            sceneManager->currentScene->head = NULL;
            sceneManager->currentScene->selectedNode = NULL;
        }
        return;
    }

    // deleting tail node
    if (sceneManager->currentScene->selectedNode == sceneManager->currentScene->tail)
    {
        sceneManager->currentScene->tail = sceneManager->currentScene->tail->prevNode;
        sceneManager->currentScene->tail->nextNode = NULL;
        free(sceneManager->currentScene->selectedNode);
        sceneManager->currentScene->selectedNode = sceneManager->currentScene->tail;
        return;
    }

    // deleting middle nodes
    sceneManager->currentScene->selectedNode->prevNode->nextNode = sceneManager->currentScene->selectedNode->nextNode;
    sceneManager->currentScene->selectedNode->nextNode->prevNode = sceneManager->currentScene->selectedNode->prevNode;
    Node *temp = sceneManager->currentScene->selectedNode->nextNode;
    free(sceneManager->currentScene->selectedNode);
    sceneManager->currentScene->selectedNode = temp;

    return;
}

void selectNextNode(void)
{
    if (sceneManager->currentScene->selectedNode && sceneManager->currentScene->selectedNode->nextNode)
    {
        sceneManager->currentScene->selectedNode = sceneManager->currentScene->selectedNode->nextNode;
    }
}

void selectPreviousNode(void)
{
    if (sceneManager->currentScene->selectedNode && sceneManager->currentScene->selectedNode->prevNode)
    {
        sceneManager->currentScene->selectedNode = sceneManager->currentScene->selectedNode->prevNode;
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
    Node *temp = sceneManager->currentScene->head;
    while (temp)
    {
        drawModel(temp->currentModel);
        temp = temp->nextNode;
    }
}

void addMultiColoredTriangleToScene(void)
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
    insertNode(triangle);
}

void addTriangleToScene(void)
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
    insertNode(triangle);
}

void addSquareToScene(void)
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
    insertNode(square);
}

void addPyramidToScene(void)
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
    insertNode(pyramid);
}

void addCubeToScene(void)
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
    insertNode(cube);
}

void addSphereToScene(void)
{
    // creating sphere model

    // inserting into linkedlist(scene)
    // insertNode(sphere);
}
