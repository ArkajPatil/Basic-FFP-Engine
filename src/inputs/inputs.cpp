#include "inputs.h"
// #include <windows.h>
#include "scene/linkedlist/linkedlist.h"
#include "windows/Window.h"

// global keys handler array
bool keys[256] = {false};

// functions body

void inputsHandling(void)
{
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

    // // full screen toggle handling using Escape key
    // if (keys[VK_ESCAPE] && gbFullScreen == TRUE)
    // {
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

    //     keys[VK_ESCAPE] = false;
    // }

    // Closing Engine
    if (keys[VK_ESCAPE])
    {

        gbEscapeKeyIsPressed = TRUE;
        writeLog(">>>>>EXITING<<<<< Escape Key pressed");

        keys[VK_ESCAPE] = false;
    }
}
