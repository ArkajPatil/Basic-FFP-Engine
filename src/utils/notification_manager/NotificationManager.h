#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <iostream>
#include <deque>
using namespace std;

// variables
extern bool bShowNotification;

// functions declarations
void createNotification(const string &msg, const string &notifySoundName = "");
void notificationLoop(void);
void showNotification(void);
void playNotifySound(const string &name = "default");

#endif