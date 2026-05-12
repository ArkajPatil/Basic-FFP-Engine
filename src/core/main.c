#include <windows.h>
#include "windows/Window.h"
#include "utils/logging_system/logger.h"
#include "rendering/OpenGLSetup.h"
#include "rendering/renderLoop.h"
#include "inputs/inputs.h"

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
        MessageBox(NULL, "Log File creation failed.", "File I/O error", MB_OK);
        exit(0);
    }
    else
    {
        writeLog("Program Started Successfully");
    }

    // creating window
    createWindow(hInstance, hPrevInstance, lpszCmdLine, iCmdShow, hwnd);
    writeLog("Window creation done Successfully");

    // initializing OpenGL context
    int result = initialize();
    if (result != 0)
    {
        writeLog(">>>>> ERROR <<<<< ::: initialize () failed");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        writeLog("initialize() completed successfully, OpenGL setup is done.\n");
    }

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

                // rendering loop
                display();
                // update
                update();
            }
        }
    }
    // uninitialize and cleanups
    uninitialize();

    return ((int)msg.wParam);
}

// CAllback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // functions declarations
    void toggleFullScreen(void);
    void resize(int, int);
    void uninitialize(void);

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
        case VK_ESCAPE:
            gbEscapeKeyIsPressed = TRUE;
            writeLog(">>>>>EXITING<<<<< Escape Key pressed");
            break;

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
        case 'F':
        case 'f':
            if (gbFullScreen == FALSE)
            {
                toggleFullScreen();
                gbFullScreen = TRUE;
            }
            else
            {
                toggleFullScreen();
                gbFullScreen = FALSE;
            }
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        uninitialize();
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
    cleanupWindow();
    cleanupOpenGL();
    cleanupLogger();
}

