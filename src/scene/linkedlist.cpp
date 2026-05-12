#include "linkedlist.h"

Scene *scene;

void initScene(void)
{     
    scene = (Scene *)malloc(sizeof(Scene));
    if(scene == NULL)
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
        if(scene->selectedNode == NULL)
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
                if(scene->head->currentModel)
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
                if(scene->tail->currentModel)
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
                if(temp->currentModel)
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
    if(scene->selectedNode && scene->selectedNode->nextNode)
    {
        scene->selectedNode = scene->selectedNode->nextNode;
    }
}

void selectPreviousNode(void)
{
    if(scene->selectedNode && scene->selectedNode->prevNode)
    {
        scene->selectedNode = scene->selectedNode->prevNode;
    }
}

void renderNode(Node *node)
{
    if(node)
    {
        drawModel(node->currentModel);
    }
}

void renderAllNodes(void)
{
    Node *temp = scene->head;
    while (temp)
    {
        if(temp == scene->selectedNode)
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

