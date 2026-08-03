#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>
#include <windows.h>
#include <GL/gl.h>

struct Texture // in cpp no need of typedef for struct
{
    GLuint id;

    int width;
    int height;
    int channels;

    std::string path;
};

// fucntions declarations
Texture* loadTexture(const std::string &path);
void bindTexture(const Texture *texture);
void unbindTexture(void);
void destroyTexture(Texture *texture);

#endif