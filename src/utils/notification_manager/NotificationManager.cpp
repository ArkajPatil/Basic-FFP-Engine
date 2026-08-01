#include <windows.h>
#include <chrono>

#include "NotificationManager.h"

#include "external/imgui/imgui.h"
#include "../../gui/fonts.h"
#include "utils/logging_system/logger.h"

// structs
typedef struct
{
    deque<string> notificationQueue;
} NotificationManager;

NotificationManager notificationManager;

bool bShowNotification = false;
float fAlpha = 1.0f;
auto notificationStartTime = std::chrono::steady_clock::now();
auto currentTime = std::chrono::steady_clock::now();
float elapsedTimeInSeconds = 0.0f;

void createNotification(const string &msg, const string &notifySoundName)
{
    notificationManager.notificationQueue.push_back(msg);

    playNotifySound(notifySoundName);
}

void notificationLoop(void)
{
    if (notificationManager.notificationQueue.size() > 0)
    {
        // start showing new notification
        if (!bShowNotification)
        {
            bShowNotification = true;
            notificationStartTime = std::chrono::steady_clock::now();
        }

        // calculating elapse time
        currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = currentTime - notificationStartTime;
        elapsedTimeInSeconds = std::chrono::duration<float>(elapsedTime).count();

        // start disappering msg
        if (elapsedTimeInSeconds > 3.0f)
        {
            fAlpha -= 0.0009f;
        }

        // stop showing notification & pop the showed notification  after 4.5 elapsed or new notification arrives
        if (elapsedTimeInSeconds > 4.5f || notificationManager.notificationQueue.size() > 1)
        {
            bShowNotification = false;
            fAlpha = 1.0f;
            notificationManager.notificationQueue.pop_front();
            elapsedTimeInSeconds = 0.0f;
        }
    }
    else
    {
        return;
    }
}

void showNotification(void)
{
    if (notificationManager.notificationQueue.size() > 0)
    {
        string msg = notificationManager.notificationQueue.front();

        ImGui::SetNextWindowPos(ImVec2(1250, 60));
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::Begin("Toast",
                     nullptr,
                     ImGuiWindowFlags_NoDecoration |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoBackground);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 1, 0.5, fAlpha));

        ImGui::PushFont(boldFont);

        ImGui::PushTextWrapPos(280.0f); // this limits the text to the right border so that the text does not goes out of the screen
        ImGui::Text(msg.c_str());
        ImGui::PopTextWrapPos();

        ImGui::PopFont();

        ImGui::PopStyleColor();
        ImGui::End();
        ImGui::PopStyleVar();
    }
    else
    {
        return;
    }
}

void playNotifySound(const string &name)
{
    string path;

    if (name == "default" || name == "")
    {
        path = "assets/sounds/" + string("notify1") + ".wav";
    }
    else
    {
        path = "assets/sounds/" + name + ".wav";
    }

    if (!(PlaySound(path.c_str(), NULL, SND_FILENAME | SND_ASYNC)))
    {
        writeLog(">>>>> ERROR <<<<< :: playNotifySound() encounters file name error.");
    }
}
