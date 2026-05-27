#include "inputs.h"
// #include <windows.h>
#include "scene/linkedlist.h"
#include "windows/Window.h"

// global keys handler array
bool keys[256] = {false};

// functions body
void modelSelection(void)
{
    if (keys[VK_LEFT])
    {
        selectPreviousNode();
        keys[VK_LEFT] = false;
    }
    if (keys[VK_RIGHT])
    {
        selectNextNode();
        keys[VK_RIGHT] = false;
    }
}

void inputsHandling(void)
{
    // Closing Engine
    if (keys[VK_SHIFT] && keys[VK_ESCAPE])
    {

        gbEscapeKeyIsPressed = TRUE;
        writeLog(">>>>>EXITING<<<<< Shift + Escape Key pressed");

        keys[VK_ESCAPE] = false;
        keys[VK_SHIFT] = false;
    }

    // full screen toggle handling using 'f' and 'F' keys
    if (keys['f'] || keys['F'])
    {
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
    }
    keys['f'] = false;
    keys['F'] = false;

    // full screen toggle handling using Escape key
    if (keys[VK_ESCAPE] && gbFullScreen == TRUE)
    {
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

        keys[VK_ESCAPE] = false;
    }
}

