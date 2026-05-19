==================================================
                BASIC-FFP-ENGINE
==================================================


+---> [ build ]
|       |
|       +--->[ Dear_ImGui_build_Files ]
|       |
|       +---> .obj files
| 
+---> [ logs ]
|       -> LogFile.txt
| 
+---> [ src ]
|       |
|       +--->[ core ]
|       |      |
|       |      +---> main.c
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
|       |
|       +--->[ inputs ]
|       |      |
|       |      +---> inputs.c
|       |      +---> inputs.h
|       |
|       +--->[ rendering ]
|       |      |
|       |      +---> OpenGLSetup.c
|       |      +---> OpenGLSetup.h
|       |      +---> renderLoop.c
|       |      +---> renderLoop.h
|       |
|       +--->[ scene ]
|       |      |
|       |      +--->[ basic_models_data ]
|       |      |      |
|       |      |      +---> basicModelsData.h
|       |      |      +---> basicModelsData.c
|       |      |
|       |      +---> models.c
|       |      +---> models.h
|       |      +---> linkedlist.c
|       |      +---> linkedlist.h
|       |
|       +--->[ utils ]
|       |      |
|       |      +--->[ logging_system ]
|       |      |      |
|       |      |      +---> logger.h
|       |      |      +---> logger.c
|       |      |
|       |      +--->[ my_math_library ]
|       |      |      |
|       |      |      +---> myMath.h
|       |      |      +---> myMath.c
|       |
|       +--->[ windows ]
|       |      |
|       |      +---> resource.h
|       |      +---> Window.h
|       |      +---> Window.c
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