#include <windows.h>
#include "windows/Window.h"
#include "utils/logging_system/logger.h"
#include "rendering/OpenGLSetup.h"
#include "rendering/renderLoop.h"
#include "inputs/inputs.h"
#include "gui/ImGuiLayer.h"
#include "scene/sceneManager.h"
#include "scene/scene_loader/SceneLoader.h"
#include "utils/notification_manager/NotificationManager.h"

// global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // HWND->HANDLE->UINT->Unsigned int

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // functions declarations
    void uninitialize(void);

    // varaibles declarations
    BOOL bDone = FALSE;
    MSG msg;
    HWND hwnd = NULL;

    // create log file
    gpFile = fopen("logs/Log File.txt", "w");
    if (gpFile == NULL)
    {
        MessageBox(NULL, TEXT("Log File creation failed."), TEXT("File I/O error"), MB_OK);
        exit(0);
    }
    else
    {
        writeLog(">>>>> SUCCESS <<<<< :: Log File created");
    }

    // creating window
    createWindow(hInstance, hPrevInstance, lpszCmdLine, iCmdShow, hwnd);

    // initializing
    // initializing OpenGL context
    int result = initializeOpenGL();
    if (result != 0)
    {
        writeLog(">>>>> ERROR <<<<< ::: initializeOpenGL() failed");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        writeLog(">>>>> SUCCESS <<<<< :: initializeOpenGL() completed successfully, OpenGL setup is done.");
    }

    // initializing ImGui
    initializeImGui();

    // initializing Scene Manager
    initSceneManager();
    initDemoScene();

    // load the saved scenes from 'assets/scenes' in vector(dynamic list) which is located in SceneManager
    giveSavedScenes(); // this funct load dynamic list(std::vector<std::string> vsSavedScenes) of saved scenes which is located inside SceneLoader
    
    PlaySound(TEXT("assets/sounds/startup.wav"), NULL, SND_FILENAME | SND_ASYNC);

    // Game Loop
    while (bDone == FALSE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bDone = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (gbActiveWindow == TRUE)
            {
                if (gbEscapeKeyIsPressed == TRUE)
                {
                    bDone = TRUE;
                }

                startImGuiFrame();

                // input handling
                inputsHandling();

                // rendering loop
                display();
                // update
                update();

                renderImGui();

                // notification manager
                notificationLoop();

                // swap the buffers
                SwapBuffers(ghdc);
            }
        }
    }
    // uninitialize and cleanups
    uninitialize();

    PlaySound(TEXT("assets/sounds/duck.wav"), NULL, SND_FILENAME | SND_SYNC);

    return ((int)msg.wParam);
}

// Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // functions declarations
    void toggleFullScreen(void);
    void resize(int, int);
    void uninitialize(void);

    // ImGui Integration
    if (ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam))
    {
        return true;
    }

    // code
    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void *)&wpPrev, sizeof(WINDOWPLACEMENT));
        wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;

    case WM_SETFOCUS:
        gbActiveWindow = TRUE;
        break;

    case WM_KILLFOCUS:
        gbActiveWindow = FALSE;
        break;

    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_KEYDOWN:
        keys[wParam] = true;
        switch (wParam)
        {
            // case VK_ESCAPE:
            //     gbEscapeKeyIsPressed = TRUE;
            //     writeLog(">>>>>EXITING<<<<< Escape Key pressed");
            //     break;

        default:
            break;
        }
        break;

    case WM_KEYUP:
        keys[wParam] = false;
        break;

    case WM_CHAR:
        switch (wParam)
        {
            // case 'F':
            // case 'f':
            //     if (gbFullScreen == FALSE)
            //     {
            //         toggleFullScreen();
            //         gbFullScreen = TRUE;
            //     }
            //     else
            //     {
            //         toggleFullScreen();
            //         gbFullScreen = FALSE;
            //     }
            //     break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        break;

    case WM_DESTROY:
        writeLog(">>>>> EXITING <<<<< WM_DESTROY trigerred.");
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void uninitialize(void)
{
    cleanupImGui();

    cleanupOpenGL();

    cleanupWindow();

    cleanupLogger();
}
