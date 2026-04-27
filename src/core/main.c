#include <windows.h>
#include "windows/Window.h"

// global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // HWND->HANDLE->UINT->Unsigned int

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // varaibles declarations
    BOOL bDone = FALSE;
    MSG msg;
    HWND hwnd = NULL;
    
    // creating window
    createWindow(hInstance, hPrevInstance, lpszCmdLine, iCmdShow, hwnd);
    
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
                // // render
                // display();

                // // update
                // update();
            }
        }
    }
    // // uninitialize
    // uninitialize();

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
        switch (wParam)
        {
        case VK_ESCAPE:
            gbEscapeKeyIsPressed = TRUE;
            break;

        default:
            break;
        }
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
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

