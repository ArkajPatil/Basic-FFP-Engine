#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Global variables (declarations only)
extern BOOL gbFullScreen;
extern DWORD dwStyle;
extern WINDOWPLACEMENT wpPrev;
extern BOOL gbActiveWindow;
extern BOOL gbEscapeKeyIsPressed;

// Window-related globals (FIXED)
extern WNDCLASSEX wndclass;
extern HWND ghwnd;

// Function declarations
void createWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow, HWND hnwd);
void toggleFullScreen(void);
void cleanupWindow(void);
std::string WideToUtf8(const wchar_t* wideString);

#endif
