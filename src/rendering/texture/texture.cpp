#include "texture.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define STB_IMAGE_IMPLEMENTATION // aded this to include the implementation part of stb_image.h
#include "external/stb/stb_image.h"

//==================================================================================
// Function : loadTexture()
//
// Purpose:
//      Loads an image from disk, creates an OpenGL texture object,
//      uploads the image to GPU memory, generates mipmaps,
//      and returns a Texture object that can be used for rendering.
//
// Returns:
//      Texture*  -> Successfully created texture.
//      nullptr   -> Image loading failed.
//==================================================================================
Texture* loadTexture(const std::string& path)
{
    Texture* texture = new Texture;      // Allocate a Texture object on the heap.
                                         // It will store texture ID, width,
                                         // height, channels and file path.

    texture->path = path;                // Save image path.
                                         // Useful for debugging or reloading.

                                         stbi_set_flip_vertically_on_load(true);    // Flip images while loading.

    stbi_uc* pixels = stbi_load(          // Load image into RAM.
        path.c_str(),                    // Convert std::string to const char*
                                         // because stb_image is a C library.

        &texture->width,                 // stb_image writes image width here.

        &texture->height,                // stb_image writes image height here.

        &texture->channels,              // Stores ORIGINAL channel count
                                         // (1 = Gray, 3 = RGB, 4 = RGBA).

        STBI_rgb_alpha);                 // Force returned pixels to RGBA.
                                         // Even if image is RGB,
                                         // stb_image adds Alpha = 255.

    if (!pixels)                         // If image loading failed...
    {
        delete texture;                  // Prevent memory leak.

        return nullptr;                  // Notify caller about failure.
    }

    glGenTextures(                        // Create OpenGL texture object.
        1,                               // Number of texture objects to create.
                                         // Here we need only one.

        &texture->id);                   // OpenGL stores generated texture ID here.
                                         // Example: id may become 5.

    glBindTexture(                       // Make texture active.
        GL_TEXTURE_2D,                   // Target texture type.
                                         // Means we are working with a
                                         // standard 2D texture.

        texture->id);                    // Make this the CURRENT active texture.
                                         // Every texture operation after this
                                         // line affects this texture until
                                         // another texture is bound.

    glPixelStorei(                        // Configure pixel layout.
        GL_UNPACK_ALIGNMENT,             // Specifies how pixel rows are arranged
                                         // in CPU memory before uploading.

        1);                             // stb_image stores rows tightly packed.
                                         // So OpenGL should NOT expect padding.

    glTexParameteri(                     // Set texture property.
        GL_TEXTURE_2D,                   // Apply this parameter to current 2D texture.

        GL_TEXTURE_MAG_FILTER,           // Filter used when texture becomes
                                         // larger than its original resolution.

        GL_LINEAR);                      // Blend neighbouring texels to produce
                                         // a smoother enlarged image.

    glTexParameteri(                     // Set texture property.
        GL_TEXTURE_2D,                   // Apply this parameter to current texture.

        GL_TEXTURE_MIN_FILTER,           // Filter used when texture becomes
                                         // smaller than its original resolution.

        GL_LINEAR_MIPMAP_LINEAR);        // Trilinear filtering.
                                         // Uses mipmaps + linear interpolation
                                         // for best visual quality.

    gluBuild2DMipmaps(                   // Upload texture & generate mipmaps.
        GL_TEXTURE_2D,                   // Upload as a 2D texture.

        GL_RGBA,                         // Store texture inside GPU in RGBA format.

        texture->width,                  // Image width.

        texture->height,                 // Image height.

        GL_RGBA,                         // Incoming pixel format is RGBA.

        GL_UNSIGNED_BYTE,                // Each color component occupies
                                         // one unsigned byte (0–255).

        pixels);                         // Address of image pixels stored in RAM.
                                         // OpenGL copies these pixels to GPU and
                                         // automatically generates mipmaps.

    glBindTexture(                        // Unbind current texture.
        GL_TEXTURE_2D,                   // Texture target.

        0);                             // Unbind texture.
                                         // Prevents accidental modification by
                                         // later texture-related OpenGL calls.

    stbi_image_free(                        // Free CPU image memory.
        pixels);                         // Free CPU-side image memory.
                                         // Image now exists inside GPU memory.

    return texture;                      // Return pointer to the created texture.
}

//==============================================================================
// Function : bindTexture()
//
// Purpose:
//      Makes the given texture the currently active texture.
//
// Parameters:
//      texture -> Texture object to bind.
//
// Returns:
//      Nothing.
//==============================================================================
void bindTexture(const Texture *texture)
{
    glBindTexture(                       // Make a texture active.
        GL_TEXTURE_2D,                  // Target: 2D texture.
        texture->id);                   // Texture ID to bind.
                                        // All following texture operations
                                        // affect this texture.
}

//==============================================================================
// Function : unbindTexture()
//
// Purpose:
//      Removes the currently active texture.
//
// Returns:
//      Nothing.
//==============================================================================
void unbindTexture(void)
{
    glBindTexture(                       // Change active texture.
        GL_TEXTURE_2D,                  // Target: 2D texture.
        0);                             // Texture ID 0 means "no texture bound".
                                        // Helps prevent accidental modification.
}

//==============================================================================
// Function : destroyTexture()
//
// Purpose:
//      Deletes the texture from GPU memory and
//      frees the Texture object from CPU memory.
//
// Parameters:
//      texture -> Texture object to destroy.
//
// Returns:
//      Nothing.
//==============================================================================
void destroyTexture(Texture *texture)
{
    if (!texture)                       // Check for nullptr.
    {
        return;                         // Nothing to destroy.
    }

    glDeleteTextures(                   // Delete OpenGL texture object.
        1,                              // Delete one texture.
        &texture->id);                  // Texture ID to delete from GPU memory.

    delete texture;                     // Free Texture object from heap.
}

