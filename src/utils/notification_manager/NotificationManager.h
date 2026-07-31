#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <iostream>
#include <deque>
using namespace std;

// variables
extern bool bShowNotification;


// functions declarations
void notificationLoop(void);
void createNotification(string msg);
// void showNotification(string msg);
void showNotification(void);

#endif