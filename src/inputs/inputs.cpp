#include "inputs.h"
#include <windows.h>
#include "scene/linkedlist.h"

// global keys handler array
bool keys[256] = {false};

// functions body
void modelSelection(void)
{
    if(keys[VK_LEFT]) {
        selectPreviousNode();
        keys[VK_LEFT] = false;
    }
    if(keys[VK_RIGHT]) {
        selectNextNode();
        keys[VK_RIGHT] = false;
    }
    
}
