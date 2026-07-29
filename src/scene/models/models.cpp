#include "models.h"

// fucntions body
Model *createModel(
    string modelName, string modelType, bool bHighlightModel, bool isVisible, 
    vec3 translate, vec3 rotate, vec3 scale,
    GLenum drawMode, GLint vertexCount, GLfloat *vertices,
    GLfloat *perVertexColors, GLfloat *uniformColor, bool bUniformColoring,
    GLfloat *texcoords, GLfloat *normals)
{
    // Model *model = (Model *)malloc(sizeof(Model));
    Model *model = new Model;

    if (!model)
    {
        return NULL;
    }

    model->modelName = modelName;
    model->modelType = modelType;
    model->bHighlightModel = bHighlightModel;
    model->isVisible = isVisible;
    model->bUniformColoring = bUniformColoring;

    // transformations
    model->transform.translate = translate;
    model->transform.rotate = rotate;
    model->transform.scale = scale;

    // mesh i.e. geometry
    model->mesh.drawMode = drawMode;
    model->mesh.vertexCount = vertexCount;

    // vertices
    model->mesh.vertices = vertices;

    // per vertex colors
    if (perVertexColors)
    {
        int size = vertexCount * 3 * sizeof(GLfloat);
        model->mesh.perVertexColors = (GLfloat *)malloc(size);
        memcpy(model->mesh.perVertexColors, perVertexColors, size);
    }
    else
    {
        model->mesh.perVertexColors = NULL;
    }

    // uniform color ... i.e single color for a model
    if (uniformColor)
    {
        int size = 3 * sizeof(GLfloat);
        model->mesh.uniformColor = (GLfloat *)malloc(size);
        memcpy(model->mesh.uniformColor, uniformColor, size);
    }
    else
    {
        model->mesh.uniformColor = NULL;
    }

    // texcoords
    if (texcoords)
    {
        int size = vertexCount * 2 * sizeof(GLfloat);
        model->mesh.texcoords = (GLfloat *)malloc(size);
        memcpy(model->mesh.texcoords, texcoords, size);
    }
    else
    {
        model->mesh.texcoords = NULL;
    }

    // normals
    if (normals)
    {
        int size = vertexCount * 3 * sizeof(GLfloat);
        model->mesh.normals = (GLfloat *)malloc(size);
        memcpy(model->mesh.normals, normals, size);
    }
    else
    {
        model->mesh.normals = NULL;
    }

    if (model->mesh.uniformColor && model->mesh.perVertexColors)
    {
        writeLog(">>>>> Warning <<<<< :: You tried to give per vertex as well as uniform color to the model: %s.", model->modelName);
    }

    writeLog("Model: %s was created.", model->modelName);
    return model;
}

void destroyModel(Model *&model)
{
    if (model == nullptr)
    {
        return;
    }

    free(model->mesh.vertices);
    free(model->mesh.perVertexColors);
    free(model->mesh.uniformColor);
    free(model->mesh.texcoords);
    free(model->mesh.normals);

    string modelName = model->modelName;

    delete model;
    model = nullptr;

    writeLog(">>>>> SUCCESS <<<<< :: Model: %s was destroyed.", modelName.c_str());
}

void applyTransform(Transform *transform)
{
    glTranslatef(transform->translate.x, transform->translate.y, transform->translate.z);
    glRotatef(transform->rotate.x, 1.0f, 0.0f, 0.0f);
    glRotatef(transform->rotate.y, 0.0f, 1.0f, 0.0f);
    glRotatef(transform->rotate.z, 0.0f, 0.0f, 1.0f);
    glScalef(transform->scale.x, transform->scale.y, transform->scale.z);
}

void drawModel(Model *model)
{
    glPushMatrix();
    applyTransform(&model->transform);

    if (model->bHighlightModel)
    {
        {
            glPushMatrix();
            glBegin(GL_LINES);

            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(9.0f, 0.0f, 0.0f);
            glVertex3f(-9.0f, 0.0f, 0.0f);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 9.0f, 0.0f);
            glVertex3f(0.0f, -9.0f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 9.0f);
            glVertex3f(0.0f, 0.0f, -9.0f);

            glEnd();
            glPopMatrix();
        }
    }

    glBegin(model->mesh.drawMode);

    // checking for uniform color
    if (model->bUniformColoring)
    {
        glColor3f(model->mesh.uniformColor[0], model->mesh.uniformColor[1], model->mesh.uniformColor[2]);
    }

    for (int i = 0; i < (model->mesh.vertexCount); i++)
    {
        // normals
        if (model->mesh.normals)
        {
            glNormal3f(model->mesh.normals[i * 3], model->mesh.normals[i * 3 + 1], model->mesh.normals[i * 3 + 2]);
        }
        // texcoords
        if (model->mesh.texcoords)
        {
            glTexCoord2f(model->mesh.texcoords[i * 2], model->mesh.texcoords[i * 2 + 1]);
        }
        // colors
        // if bUniformColoring = NULL, then color according to per vertex colors
        if (!model->bUniformColoring)
        {
            glColor3f(model->mesh.perVertexColors[i * 3], model->mesh.perVertexColors[i * 3 + 1], model->mesh.perVertexColors[i * 3 + 2]);
        }

        // vertex
        glVertex3f(model->mesh.vertices[i * 3], model->mesh.vertices[i * 3 + 1], model->mesh.vertices[i * 3 + 2]);
    }

    glEnd();
    glPopMatrix();
}
