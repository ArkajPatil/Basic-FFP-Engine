#ifndef TEXTURE_H
#define TEXTURE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include<string>
#include <vector>


struct Texture // in cpp no need of typedef for struct
{
    GLuint id;
    std::string fileName;

    int width;
    int height;
    int channels;

    std::string path;
};

// functions declarations
Texture* createTexture(const std::string &path);
void bindTexture(const Texture *texture);
void unbindTexture(void);
void destroyTexture(Texture *texture);


#endif