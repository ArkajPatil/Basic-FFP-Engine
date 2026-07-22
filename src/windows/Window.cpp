// win32 headers

#include <stdio.h>
#include <stdlib.h>

#include "Window.h"
#include "resource.h"
#include "utils/logging_system/logger.h"

// global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // HWND->HANDLE->UINT->Unsigned int

// active window related variable
BOOL gbActiveWindow = FALSE;

// Exit key press related
BOOL gbEscapeKeyIsPressed = FALSE;

// global variable decalrations
BOOL gbFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

HWND ghwnd;

TCHAR szAppName[] = TEXT("Arkaj Patil");

// Entry point function
void createWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow, HWND hwnd)
{
    // local functions declarations
    int initialize(void);
    void display(void);
    void update(void);
    void uninitialize(void);

    // variables for centering the window
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    // Calculate position to center the window
    int screenCenterX = (screenWidth - WIN_WIDTH) / 2;
    int screenCenterY = (screenHeight - WIN_HEIGHT) / 2;

    // varaibles declarations
    ghwnd = hwnd;
    WNDCLASSEX wndclass;

    // window class initialization
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    // registration of window class
    RegisterClassEx(&wndclass);

    // Create window
    ghwnd = CreateWindowEx(WS_EX_APPWINDOW,
                           szAppName,
                           TEXT("OpenGL FFP Engine"),
                           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
                           screenCenterX,
                           screenCenterY,
                           WIN_WIDTH,
                           WIN_HEIGHT,
                           NULL,
                           NULL,
                           hInstance,
                           NULL);
    // ghwnd = hwnd;

    // Show window
    ShowWindow(ghwnd, iCmdShow);

    // Paint background of windoW
    UpdateWindow(ghwnd);

    // set this window as foreground and active window
    SetForegroundWindow(ghwnd);
    SetFocus(ghwnd);

    writeLog(">>>>> SUCCESS <<<<< :: Window creation done Successfully");

}

void toggleFullScreen(void)
{
    // variable declarations
    MONITORINFO mi;

    // code
    if (gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            ZeroMemory((void *)&mi, sizeof(MONITORINFO));
            mi.cbSize = sizeof(MONITORINFO);
            if (GetWindowPlacement(ghwnd, &wpPrev) &&
                GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        // ShowCursor(FALSE);
    }
    else
    {
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        // ShowCursor(TRUE);
    }
}

void cleanupWindow(void)
{
    // code
    // if user is exiting in full screen then restore fullscreen to normal
    if (gbFullScreen == TRUE)
    {
        toggleFullScreen();
        gbFullScreen = FALSE;
    }
}
