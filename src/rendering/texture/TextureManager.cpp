#include "TextureManager.h"
#include "utils/logging_system/logger.h"
#include "utils/notification_manager/NotificationManager.h"


// variables
TextureManager *textureManager;

// Location: - 'rendering/texture/TextureManager.cpp' 
// Purpose: - allocated memory to TextureManager [called at program start]
// Parameters: - none
// Return type: none
void initTextureManager(void)
{
    textureManager = new TextureManager();

    if (!textureManager)
    {
        writeLog(">>>>> ERROR <<<<< :: TextureManager allocation failed.");
        createNotification("TextureManager allocation failed", "error");
    }

    // telling in advance we will be keeping max 10 textures in vector, if exceeded aloud
    textureManager->vtLoadedTextures.reserve(10); // by doing this it allocated spce for 10 elements in advance

    writeLog(">>>>> SUCCESS <<<<< :: TextureManager allocation successful.");
}


// Location: 
// - 'rendering/texture/TextureManager.cpp' 
//
// Purpose:
//  - scans 'assets/textures/' for available textures
//  - only names of suitables images are stored in vector: textureManager->vsAvailableTextures
//
// Parameters:
// - none
//
// Return type:
// - none
void scanTextureDirectory(void)
{
    WIN32_FIND_DATA findData;

    HANDLE hFind = FindFirstFile(TEXT("assets/textures/*"), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        createNotification("ERROR: giveSavedTextures() INVALID_HANDLE_VALUE");
        return;
    }
    

    textureManager->vsAvailableTextures.clear();
    std::string extensionList[] = {".bmp", ".png", ".jpg", ".jpeg", ".tga"};


    do
    {
        std::string name = findData.cFileName;
        for (std::string &extension : extensionList)
        {
            size_t pos = name.rfind(extension);  // find extension from right side instead of left
            if (pos != std::string::npos)
            {
                if (name.length() - pos == extension.length())
                {
                    textureManager->vsAvailableTextures.push_back(name);
                    break;
                }
                else
                {
                    break;
                }
            }
        }

    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}


// Location: 
// - 'rendering/texture/TextureManager.cpp' 
//
// Purpose:
//  - it creates a texture using createTexture() from Texture module
//  - and then register/save it inside vector: vtLoadedTextures
//
// Parameters:
// - takes name of the file inside 'assets/textures/' which you wants to be register
//
// Return type:
// - returns true if successfully create and load texture into vector
// - returns false if texture already registered in vtLoadedTextures
// - returns false if createTexture() fails
bool createAndRegisterTexture(const std::string &name)
{
    std::string path = "assets/textures/" + name;

    for (int i = 0; i < textureManager->vtLoadedTextures.size(); i++)
    {
        if (textureManager->vtLoadedTextures[i]->fileName == name)
        {
            writeLog(">>>>> WARNING <<<<< :: Tried to load texture '%s' but it was already loaded.", name);
            return false;
        }
    }

    Texture *texture = createTexture(path);

    if (!texture)
    {
        writeLog(">>>>> ERROR <<<<< :: createTexture() failed for Texture: '%s'.", name);
        return false;
    }

    texture->fileName = name;

    textureManager->vtLoadedTextures.push_back(texture);

    writeLog(">>>>> SUCCESS <<<<< :: Texture: '%s' loaded successfully.", name);
    return true;
}


// Location: 
// - 'rendering/texture/TextureManager.cpp' 
//
// Purpose:
//  - it destroy the a texture using destroyTexture() from Texture module
//  - remove texture from GPU memory and clears the texture object on CPU memory by destroyTexture()
//  - after destroying the required textures, rearrange the vector vtLoadedTextures
//
// Parameters:
// - takes name of the file inside 'assets/textures/' which you wants to be unload
//
// Return type:
// - returns true if successfully unload the texture
// - returns false if provided texture not registered in vtLoadedTextures
bool unloadTexture(const std::string &name)
{
    int i;
    bool bFound = false;

    for (i = 0; i < textureManager->vtLoadedTextures.size(); i++)
    {
        if (textureManager->vtLoadedTextures[i]->fileName == name)
        {
            bFound = true;
            break;
        }
    }

    if (!bFound)
    {
        writeLog(">>>>> ERROR <<<<< :: Tried to unload Texture: '%s' but currently isn't not loaded.", name);
        return false;
    }

    destroyTexture(textureManager->vtLoadedTextures[i]);
    textureManager->vtLoadedTextures.erase(textureManager->vtLoadedTextures.begin() + i);

    writeLog(">>>>> SUCCESS <<<<< :: Texture: '%s' unloaded successfully.", name);
    return true;
}


// Location: 
// - 'rendering/texture/TextureManager.cpp' 
//
// Purpose:
//  - applies texture to provided model and enables model->mesh.bApplyTexture = true
//
// Parameters:
// - Model *model : model which we wants to get texture applied
// - Texture *texture : desired texture
//
// Return type:
// - returns true if successfully apply the texture to model
// - returns false if invalid arguments are passed
bool applyTextureToModel(Model *model, Texture *texture)
{
    if (texture && model)
    {
        model->mesh.texture = texture;
        model->mesh.bApplyTexture = true;
    }
    else
    {
        writeLog(">>>>> WARNING <<<<< :: Invalid arguments passed to applyTextureToModel().");
        return false;
    }

    return true;
}


// Location: 
// - 'rendering/texture/TextureManager.cpp' 
//
// Purpose:
//  - destroys all loaded textures
//  - deletes TextureManager object
//
// Parameters:
// - none
//
// Return type:
// - none
void cleanupTextureManager(void)
{
    // destroying all loaded textures
    const size_t length = textureManager->vtLoadedTextures.size();
    for(int i = 0; i < length; i++)
    {
        destroyTexture(textureManager->vtLoadedTextures[i]);
    }
    textureManager->vtLoadedTextures.clear();

    delete textureManager;

    writeLog(">>>>> SUCCESS <<<<< :: destroyTextureManager() done.");
}


