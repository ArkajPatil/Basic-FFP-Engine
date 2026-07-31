==================================================
                BASIC-FFP-ENGINE
==================================================


+---> [ build ]
|       |
|       +--->[ Dear_ImGui_build_Files ]
|       |
|       +---> .obj files
| 
+---> [ assets ]
|       |
|       +--->[ models ]
|       |
|       +--->[ scenes ]   -> this folder contains scenes saved at runtime
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
|       +---> Engine Directory Structure.md (this file)
|       +---> pushInfo.txt
|
|
|
+---> .gitignore
+---> build.bat
|

==================================================