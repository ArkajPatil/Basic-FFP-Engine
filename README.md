Hello there,
I am Arkaj, 
just a graphics programming enthusiast.

I started working on this project for learning the OpenGL Fixed Function Pipeline.


# Basic FFP Engine

A small OpenGL Fixed Function Pipeline (FFP) based rendering engine that I am building from scratch to understand how rendering and game engines work internally.

This project started as a very basic Win32 + OpenGL program and slowly grew into a small editor-style engine with scene management, transformations, textures, JSON scene saving/loading, notifications, and other basic engine systems.

The main goal of this project was never to build a production-ready engine.

The main goal was to learn to basics of rendering and engine development.

---

## What is this project?

Basic FFP Engine is a learning-focused rendering engine built using:

- C++
- Win32 API
- OpenGL Fixed Function Pipeline
- Dear ImGui (for UI creation)
- nlohmann/json (for json parsing)
- stb_image (for textures)

The engine currently provides a small runtime editor where models can be created, selected, transformed, colored, textured, saved, and loaded.

---

### Info Folders

This folder contains some extra information about the project.

- `Engine Directory Structure.md`
  - Contains information about the engine's folder and file structure.

- `pushInfo.txt`
  - Contains some notes added while pushing changes to Git.


### Implementation - Screen recordings

This folder contains some screen recording of my Engine.

Please don't mind the quality of video 🙂,
My laptop is not really much powerful to handle rendering and screen recording at the same time. 
So i reduced the screen recodring quality in OBS studio.


## Current Features

### Window & Application

- Win32 window creation
- Fullscreen toggle
- OpenGL context creation
- Window resizing
- OpenGL information logging
- Main game/render loop
- Basic input handling

### Rendering

- OpenGL Fixed Function Pipeline
- Basic model rendering
- Triangle
- Square
- Cube
- Pyramid


### Model System

- Model creation and destruction
- Unified model creation system
- Runtime model selection
- Model visibility control
- Selected-model highlighting
- Local X/Y/Z axis display
- Translation
- Rotation
- Scaling
- Uniform model coloring
- Per-vertex coloring

Note: per vertex color feature is not yet added in Scene loading, so per vertex colors are not stored when scene is stored in 'assets/scenes/'

### Scene System

- Multiple scenes at runtime
- Scene creation
- Scene deletion
- Scene selection
- Scene model linked-list management
- Clear scene loading
- Append scene loading
- Scene saving to JSON
- Scene loading from JSON
- Version-based scene loading
- Scene name preservation
- Saved scene browser

### Texture System

- Texture loading using stb_image
- OpenGL texture creation
- Texture binding/unbinding
- Texture destruction
- Texture coordinates for basic models
- Runtime texture selection
- Runtime texture assignment
- Texture directory scanning
- Texture Manager
- Available texture list
- Loaded texture list
- Duplicate texture loading prevention
- Texture caching/registration through TextureManager
- Texture cleanup during engine shutdown

Currently supported texture formats:

- `.bmp`
- `.png`
- `.jpg`
- `.jpeg`
- `.tga`

One current limitation is that texture loading information is **not stored when saving a scene**.

The scene JSON currently stores the model's basic information such as:
- Model type
- Position
- Rotation
- Scale
- Color

but it does not store which texture was applied to the model.

So after loading a saved scene, textures need to be assigned again.

This is intentionally left for a later version when the resource/material system is improved.


### Editor / ImGui

- Runtime editor interface
- Model navigation
- Add/delete models
- Scene management controls
- Transform controls
- Color controls
- Texture controls
- Grid controls
- Display/visibility controls
- Saved scene browser
- Delete confirmation popup
- Runtime notifications

### Notification System

- Runtime editor notifications
- Notification queue
- Automatic notification timeout
- Notification sounds
- Custom notification UI
- Roboto fonts for editor notifications

### Build System

- Custom `build.bat`
- MSVC compiler
- Incremental Dear ImGui object-file caching
- `/MP` enabled for parallel compilation of source files
- Separate project folders for engine modules

---

## Project Structure

The project is organized into separate modules instead of keeping everything inside one large source file.

```text
Basic-FFP-Engine/
+---> [ build ]
|       |
|       +--->[ Dear_ImGui_build_Files ]
|       |
|       +---> .obj files
| 
+---> [ assets ]
|       |
|       +--->[ fonts ]
|       |
|       +--->[ models ]
|       |
|       +--->[ scenes ]   -> this folder contains scenes saved at runtime
|       |
|       +--->[ sounds ]
|       |
|       +--->[ textures ]
|       
| 
+---> [ logs ]
|       -> LogFile.txt
| 
+---> [ src ]
|       |
|       +--->[ core ]
|       |      |
|       |      +---> main.cpp
|       |
|       +--->[ external ]
|       |      |
|       |      +--->[ imgui ]
|       |             |
|       |             +---> This folder contains all the required files for ImGui from git repo of Dear ImGui
|       |
|       +--->[ gui ]
|       |      |
|       |      +---> ImGuiLayer.cpp
|       |      +---> ImGuiLayer.h
|       |      +---> ImGuiUI.cpp
|       |      +---> ImGuiUI.h
|       |      +---> fonts.cpp
|       |      +---> fonts.h
|       |
|       +--->[ inputs ]
|       |      |
|       |      +---> inputs.cpp
|       |      +---> inputs.h
|       |
|       +--->[ rendering ]
|       |      |
|       |      +--->[ texture ]
|       |      |      |
|       |      |      +---> texture.h
|       |      |      +---> texture.cpp
|       |      |      +---> TextureManager.h
|       |      |      +---> TextureManager.cpp
|       |      | 
|       |      +---> OpenGLSetup.cpp
|       |      +---> OpenGLSetup.h
|       |      +---> renderLoop.cpp
|       |      +---> renderLoop.h
|       |
|       +--->[ scene ]
|       |      |
|       |      +--->[ basic_models_data ]
|       |      |      |
|       |      |      +---> basicModelsData.h
|       |      |      +---> basicModelsData.cpp
|       |      |
|       |      +--->[ models ]
|       |      |      |
|       |      |      +---> models.h
|       |      |      +---> models.cpp
|       |      |
|       |      +--->[ linkedlist ]
|       |      |      |
|       |      |      +---> linkedlist.h
|       |      |      +---> linkedlist.cpp
|       |      |
|       |      |
|       |      +--->[ scene_loader ]
|       |      |      |
|       |      |      +---> SceneLoader.h
|       |      |      +---> SceneLoader.cpp
|       |      |
|       |      +---> scene.h
|       |      +---> sceneManager.h
|       |      +---> sceneManager.cpp
|       |
|       +--->[ utils ]
|       |      |
|       |      +--->[ logging_system ]
|       |      |      |
|       |      |      +---> logger.h
|       |      |      +---> logger.cpp
|       |      |
|       |      +--->[ my_math_library ]
|       |      |      |
|       |      |      +---> myMath.h
|       |      |      +---> myMath.cpp
|       |      |      
|       |      +--->[ notification_manager ]
|       |      |      |
|       |      |      +---> NotificationManager.h
|       |      |      +---> NotificationManager.cpp
|       |
|       +--->[ windows ]
|       |      |
|       |      +---> resource.h
|       |      +---> Window.h
|       |      +---> Window.cpp
|       |      +---> Window.rc
|       |      +---> Window.res
|
+---> [ resources ]
|       |
|       +---> myicon.ico
|
+---> [ info folders ]
|       |
|       +---> Engine Directory Structure.md 
|       +---> pushInfo.txt 
|
|
|
+---> .gitignore
+---> build.bat
```

The exact folder structure may continue to change as the engine develops.

---

# How to Build

The project currently uses the MSVC compiler through `cl.exe`.

Make sure the Visual Studio Developer Command Prompt/environment is available so that `cl.exe`, linker tools, and required Windows libraries can be found.

From the project root, run:

```bat
build.bat
```

The build script handles compiling the engine source files and linking the executable.
(If you are now having tools for compiling the Engine, I am providing the 'main.exe' in root)

---

# How to Run

After a successful build, run the generated executable:

```text
main.exe
```

The engine expects the required assets to be available in the project directories, especially:

```text
assets/
├── scenes/
├── textures/
└── fonts/
```

Run the executable from the project root so relative asset paths such as:

```text
assets/textures/
assets/scenes/
assets/fonts/
```

resolve correctly.

---

# Using the Editor

When the engine starts, the ImGui editor provides controls for working with the scene.

You can:

1. Create models.
2. Select models.
3. Move, rotate, and scale them.
4. Change their colors.
5. Enable textures.
6. Load and bind available textures.
7. Create and manage multiple scenes.
8. Save scenes to JSON.
9. Load previously saved scenes.
10. Append a saved scene to the current scene.
11. Show/hide the grid and axes.

---

# Scene Files

Scenes are saved as JSON files inside:

```text
assets/scenes/
```

The scene format contains information such as:

- Scene name
- Scene version
- Models
- Model type
- Position
- Rotation
- Scale
- Color

The version field was added so the scene loading system can be extended later without breaking older scene files.

---


# Why Fixed Function Pipeline?

I started this project with OpenGL FFP on purpose.

I wanted to first understand what a rendering pipeline is doing before jumping directly into shaders.

The FFP version helped me understand things like:

- Model transformations
- Textures
- Scene management
- CPU-side rendering data
- Resource lifetime

A lot of these concepts will still exist in a Programmable Pipeline renderer.

The main difference is that in the PP renderer, I will have to take control of many of the things OpenGL FFP was doing automatically.

---

# What is NOT in Version 1

I decided to stop Version 1 at this point instead of continuously adding features.

Some features are intentionally being moved to the next stage.

For example:

- Advanced model loading
- Lighting
- Advanced material systems
- Proper texture reference counting
- Advanced resource management
- More complex rendering techniques
- Modern GPU buffer-based rendering

These are better things to work on after moving to the Programmable Pipeline.

---


# Current Status

**Version 1 — FFP Engine**  Done


Now I look forward to start learning the **Core profile of OpenGL**.

Thanks a lot for visiting my project.

