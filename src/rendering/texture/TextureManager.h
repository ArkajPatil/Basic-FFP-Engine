#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include "texture.h"
#include "scene/models/models.h"

typedef struct {
    std::vector<std::string> vsAvailableTextures;   // string vector to store available textures names
    std::vector<Texture*> vtLoadedTextures;  // vector of Texture*
} TextureManager;

extern TextureManager *textureManager;

// functions declarations
void initTextureManager(void);
void scanTextureDirectory(void);
bool createAndRegisterTexture(const std::string &name);
bool unloadTexture(const std::string &name);
bool applyTextureToModel(Model *model, short int iSelected_Loaded_Texture);
void cleanupTextureManager(void);

#endif